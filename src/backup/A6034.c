/*****************************************************************
 * 프로그램명   : A6034.c
 * 작  성  자   : David Cho
 * 기      능   : 지수옵션 종목마감 UDP데이타 처리(A6034)
 * PROTOTYPE    :
 *****************************************************************/

#include	"common.h"
#include	"shm_def.h"
#include	"fo.h"
#include	"koscom_fo.h"

#define LOG_FILE  "/home/david/log/proc_trans.log"

extern	int	g_fep_hour;

static int _Debug_Option_Data_A6(char *rcv_data);
static int Update_SHM_OptionCloseMaster(int offset,char *pst);

int proc_A6034(char *org_data)
{
	RCV_STK_A6_03_4 *kos_o_a6;
	STRUC_OPT_MAST	st_mast;

	int	offset = -1;

	if (koshm == NULL)
		koshm = (struct KOSPI200_OPT_INFO *)SetKOSharedMemory ();

	memset(&st_mast, 0x00, sizeof(st_mast));

	kos_o_a6 = (RCV_STK_A6_03_4*)&org_data[0];

	strncpy(st_mast.stnd_iscd, kos_o_a6->s_stnd_iscd, sizeof(kos_o_a6->s_stnd_iscd));
	strncpy(st_mast.shrn_iscd, &st_mast.stnd_iscd[3], 8);

	/* offset setting */
	offset = OffsetOptf(st_mast.stnd_iscd);
	if(offset < 0)
	{
		CODEIDX_OPT  codeidx;
		memset(&codeidx, 0x00, sizeof(CODEIDX_OPT));
		memcpy(codeidx.stnd_iscd, st_mast.stnd_iscd, sizeof(st_mast.stnd_iscd)-1);
		memcpy(codeidx.shrn_iscd, st_mast.shrn_iscd, sizeof(st_mast.shrn_iscd)-1);

		offset = AddOpt(&codeidx);
		if(offset < 0)
		{
			_DispLog(LOG_FILE, "AddOpt Error[%s:%s]", st_mast.stnd_iscd, st_mast.shrn_iscd);
		}

		_DispLog(LOG_FILE, "AddOpt Insert[%s:%s] offset[%d]", st_mast.stnd_iscd, st_mast.shrn_iscd, offset);
	}

	st_mast.bsop_hour       = g_fep_hour;
	st_mast.bsop_date   = __GetDateInt();

	st_mast.optn_prpr = __Str2Float(kos_o_a6->s_optn_clpr, sizeof(kos_o_a6->s_optn_clpr), 2);
	st_mast.optn_prdy_vrss = st_mast.optn_prpr - st_mast.optn_sdpr; //diff price
	/* 시스템의 소숫점이하 계산 오차때문에 추가함. */
	st_mast.optn_prdy_vrss = round(st_mast.optn_prdy_vrss*100) / 100.;
	st_mast.prdy_ctrt = __D2DRate(st_mast.optn_prdy_vrss, st_mast.optn_sdpr);   //diff rate
	if (st_mast.optn_prdy_vrss > 0)     st_mast.prdy_vrss_sign[0] = VRSS_SIGN_ASCENT;
	else if (st_mast.optn_prdy_vrss <0) st_mast.prdy_vrss_sign[0] = VRSS_SIGN_DESCENT;
	else                                st_mast.prdy_vrss_sign[0] = VRSS_SIGN_STEADY;

	if ( st_mast.optn_prdy_vrss > 0 || st_mast.optn_prdy_vrss < 0 ) {
	    if (st_mast.optn_mxpr == st_mast.optn_prpr) st_mast.prdy_vrss_sign[0] = VRSS_SIGN_HIGHEST;
	    if (st_mast.optn_llam == st_mast.optn_prpr) st_mast.prdy_vrss_sign[0] = VRSS_SIGN_LOWEST;
	}

	st_mast.acml_vol = __Str2Long(kos_o_a6->s_acml_cntg_qty, sizeof(kos_o_a6->s_acml_cntg_qty));
	st_mast.acml_tr_pbmn = __Str2Long(kos_o_a6->s_acml_tr_pbmn, sizeof(kos_o_a6->s_acml_tr_pbmn)) * 1000;
	strcpy(st_mast.mkop_stat_code, "99");

	/* Update OPTTION SHARED MEMORY */
	Update_SHM_OptionCloseMaster(offset, (char *)&st_mast);

#ifdef _DEBUG_
	_Debug_Option_Data_A6(org_data);
#endif
	
	return SUCCESS;

}

/* 지수옵션 장마감 마스터 업데이트 */
static int Update_SHM_OptionCloseMaster(int offset,char *pst)
{
    STRUC_OPT_MAST      *pst_mast;

    pst_mast = (STRUC_OPT_MAST *)pst;

    if(offset < 0)  return(0);

    memcpy(koshm->master[offset].mkop_stat_code,pst_mast->mkop_stat_code,sizeof(pst_mast->mkop_stat_code)-1);
    koshm->master[offset].optn_prpr        = pst_mast->optn_prpr        ;
    koshm->master[offset].optn_prdy_vrss   = pst_mast->optn_prdy_vrss   ;
    koshm->master[offset].prdy_ctrt        = pst_mast->prdy_ctrt        ;
    koshm->master[offset].prdy_vrss_sign[0]= pst_mast->prdy_vrss_sign[0];
    koshm->master[offset].acml_vol         = pst_mast->acml_vol         ;
    koshm->master[offset].acml_tr_pbmn     = pst_mast->acml_tr_pbmn     ;
#if 0
	작업안된 부분
    koshm->master[offset].unas_prc         = pst_mast->unas_prc         ;
    koshm->master[offset].hts_ints_vltl    = pst_mast->hts_ints_vltl    ;
    koshm->master[offset].hts_thpr         = pst_mast->hts_thpr         ;
    koshm->master[offset].prit             = pst_mast->prit             ;
    koshm->master[offset].delta            = pst_mast->delta            ;
    koshm->master[offset].gama             = pst_mast->gama             ;
    koshm->master[offset].theta            = pst_mast->theta            ;
    koshm->master[offset].vega             = pst_mast->vega             ;
    koshm->master[offset].rho              = pst_mast->rho              ;
    koshm->master[offset].unas_hist_vltl   = pst_mast->unas_hist_vltl   ;
    koshm->master[offset].askp_ints_vltl   = pst_mast->askp_ints_vltl   ;
    koshm->master[offset].bidp_ints_vltl   = pst_mast->bidp_ints_vltl   ;
#endif

    return(1);
}

static int _Debug_Option_Data_A6(char *rcv_data)
{
    RCV_STK_A6_03_4     *dat;

    dat = (RCV_STK_A6_03_4 *)&rcv_data[0];

    _DispLog(LOG_FILE, "Start............................");
    _DispLog(LOG_FILE, "data_cls_code  =[%.*s]", sizeof(dat->s_data_cls_code  ), dat->s_data_cls_code );
    _DispLog(LOG_FILE, "info_cls_code  =[%.*s]", sizeof(dat->s_info_cls_code  ), dat->s_info_cls_code );
    _DispLog(LOG_FILE, "mrkt_cls_code  =[%.*s]", sizeof(dat->s_mrkt_cls_code  ), dat->s_mrkt_cls_code );
    _DispLog(LOG_FILE, "stnd_iscd      =[%.*s]", sizeof(dat->s_stnd_iscd      ), dat->s_stnd_iscd     );
    _DispLog(LOG_FILE, "optn_srno      =[%.*s]", sizeof(dat->s_issu_srno      ), dat->s_issu_srno     );
    _DispLog(LOG_FILE, "optn_prpr      =[%.*s]", sizeof(dat->s_optn_clpr      ), dat->s_optn_clpr     );
    _DispLog(LOG_FILE, "s_clpr_cls_code=[%.*s]", sizeof(dat->s_clpr_cls_code  ), dat->s_clpr_cls_code );
    _DispLog(LOG_FILE, "acml_vol       =[%.*s]", sizeof(dat->s_acml_cntg_qty  ), dat->s_acml_cntg_qty );
    _DispLog(LOG_FILE, "acml_tr_pbmn   =[%.*s]", sizeof(dat->s_acml_tr_pbmn   ), dat->s_acml_tr_pbmn  );

    return 1;
}
