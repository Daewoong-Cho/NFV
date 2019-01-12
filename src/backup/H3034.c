/*****************************************************************
 * 프로그램명   : H3034.c
 * 작  성  자   : David Cho
 * 기      능   : 지수옵션 매매증거금기준가 UDP데이타 처리(H3034)
 * PROTOTYPE    :
 *****************************************************************/

#include	"common.h"
#include	"shm_def.h"
#include	"fo.h"
#include	"koscom_fo.h"

#define LOG_FILE  "/home/david/log/proc_trans.log"

extern	int	g_fep_hour;

static int _Debug_Option_Data_H3(char *rcv_data);
static int Update_SHM_OptionDealMaster(int offset,char *pst);

int proc_H3034(char *org_data)
{
	RCV_STK_H3_03_4 *kos_o_h3;
	STRUC_OPT_MAST	st_mast;

	int	offset = -1;

	if (koshm == NULL)
		koshm = (struct KOSPI200_OPT_INFO *)SetKOSharedMemory ();

	memset(&st_mast, 0x00, sizeof(st_mast));

	kos_o_h3 = (RCV_STK_H3_03_4*)&org_data[0];

	strncpy(st_mast.stnd_iscd, kos_o_h3->s_stnd_iscd, sizeof(kos_o_h3->s_stnd_iscd));
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

	st_mast.deal_marg_sdpr = __Str2Double(kos_o_h3->s_deal_marg_stnd_prc, sizeof(kos_o_h3->s_deal_marg_stnd_prc), 8);
	st_mast.deal_marg_sdpr_cls_code[0] = kos_o_h3->s_deal_marg_stnd_prc_cls[0];
	st_mast.evnt_stlm_prc = __Str2Double(kos_o_h3->s_optn_rght_dorm_stlm_prc, sizeof(kos_o_h3->s_optn_rght_dorm_stlm_prc), 8);
	st_mast.evnt_stlm_prc_cls_code[0] = kos_o_h3->s_optn_rght_dorm_stlm_prc_code[0];

	/* Update OPTTION SHARED MEMORY */
	Update_SHM_OptionDealMaster(offset, (char *)&st_mast);


	_Debug_Option_Data_H3(org_data);
#ifdef _DEBUG_
#endif
	
	return SUCCESS;

}

/* 지수옵션 매매증거금기준가 마스터 업데이트 */
static int Update_SHM_OptionDealMaster(int offset,char *pst)
{
    STRUC_OPT_MAST      *pst_mast;

    pst_mast = (STRUC_OPT_MAST *)pst;

    if(offset < 0)  return(0);

    koshm->master[offset].deal_marg_sdpr = pst_mast->deal_marg_sdpr;
    koshm->master[offset].deal_marg_sdpr_cls_code[0] = pst_mast->deal_marg_sdpr_cls_code[0];
    koshm->master[offset].evnt_stlm_prc = pst_mast->evnt_stlm_prc;
    koshm->master[offset].evnt_stlm_prc_cls_code[0] = pst_mast->evnt_stlm_prc_cls_code[0];

    return(1);
}

static int _Debug_Option_Data_H3(char *rcv_data)
{
    RCV_STK_H3_03_4     *dat;

    dat = (RCV_STK_H3_03_4 *)&rcv_data[0];

    _DispLog(LOG_FILE, "Start............................[H3034]");
    _DispLog(LOG_FILE, "deal_marg_sdpr  =[%.*s]", sizeof(dat->s_deal_marg_stnd_prc  ), dat->s_deal_marg_stnd_prc );
    _DispLog(LOG_FILE, "evnt_stlm_prc  =[%.*s]", sizeof(dat->s_optn_rght_dorm_stlm_prc  ), dat->s_optn_rght_dorm_stlm_prc );

    return 1;
}
