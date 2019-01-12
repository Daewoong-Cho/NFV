/*****************************************************************
 * 프로그램명   : A3034.c
 * 작  성  자   : David Cho
 * 기      능   : 지수옵션 체결 UDP데이타 처리(A0034)
 * PROTOTYPE    :
 *****************************************************************/

#include	"common.h"
#include	"shm_def.h"
#include	"fo.h"
#include	"koscom_fo.h"

#define LOG_FILE  "/home/david/log/proc_trans.log"

extern	int	g_fep_hour;

static int _Debug_Option_Data_A3(char *rcv_data);

static int Update_SHM_OptionMst(int offset,char *pst);
static int Update_SHM_OptionFill(int offset,char *pst);

int proc_A3034(char *org_data)
{
	RCV_STK_A3_03_4 *kos_o_a3;
	STRUC_OPT_MAST	st_mast;
	STRUC_OPT_MAST	st_p_mast;
	STRUC_OPT_FILL	st_fill;

	int	offset = -1;

	if (koshm == NULL)
		koshm = (struct KOSPI200_OPT_INFO *)SetKOSharedMemory ();

	memset(&st_fill, 0x00, sizeof(st_fill));
	memset(&st_mast, 0x00, sizeof(st_mast));

	kos_o_a3 = (RCV_STK_A3_03_4*)&org_data[0];

	strncpy(st_fill.stnd_iscd, kos_o_a3->s_stnd_iscd, sizeof(kos_o_a3->s_stnd_iscd));
	strncpy(st_fill.shrn_iscd, &st_fill.stnd_iscd[3], 8);

	/* offset setting */
	offset = OffsetOptf(st_fill.stnd_iscd); if(offset < 0)
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

	memcpy(&st_p_mast, &st_mast, sizeof(st_p_mast));

	/* Master Setting */
	st_mast.optn_prpr   = __Str2Float(kos_o_a3->s_optn_prpr , sizeof(kos_o_a3->s_optn_prpr), 2);
	st_mast.optn_oprc   = __Str2Float(kos_o_a3->s_optn_oprc , sizeof(kos_o_a3->s_optn_oprc), 2);
	st_mast.optn_hgpr   = __Str2Float(kos_o_a3->s_optn_hgpr , sizeof(kos_o_a3->s_optn_hgpr), 2);
	st_mast.optn_lwpr   = __Str2Float(kos_o_a3->s_optn_lwpr , sizeof(kos_o_a3->s_optn_lwpr), 2);
	st_mast.rgbf_prc	= __Str2Float(kos_o_a3->s_rgbf_prc , sizeof(kos_o_a3->s_rgbf_prc), 2);

    /** 거래량 체크.
      * 총거래량이 직전총거래량보다 작으면, 역전현상으로 간주하고, 체결처리 않고 버린다.
      * 체결수량은 거래소 수신 체결량을 사용않고, 직전 최종거래량과 현재거래량의 차이를 사용한다.
     **/

	st_mast.acml_vol	= __Str2Long(kos_o_a3->s_acml_cntg_qty , sizeof(kos_o_a3->s_acml_cntg_qty));

    if(st_mast.acml_vol <= st_p_mast.acml_vol)
    {
		_DispLog(LOG_FILE, "거래량 역전현상 Skip [A3034] current[%ld] before[%ld]", st_mast.acml_vol, st_p_mast.acml_vol);
        return 1;
    }

	st_mast.acml_tr_pbmn   = __Str2Long(kos_o_a3->s_acml_tr_pbmn , sizeof(kos_o_a3->s_acml_tr_pbmn));

	/* 체결유형코드 */
	memcpy(st_mast.cntg_type_code,kos_o_a3->s_cntg_type_code,sizeof(kos_o_a3->s_cntg_type_code));

	/* Fill Setting */
	st_fill.bsop_hour		= __Str2Int(kos_o_a3->s_cntg_hour , sizeof(kos_o_a3->s_cntg_hour));
	st_fill.stck_prpr		= st_mast.optn_prpr;
	st_fill.cntg_vol		= __Str2Long(kos_o_a3->s_cnqn , sizeof(kos_o_a3->s_cnqn));
	st_fill.acml_vol		= st_mast.acml_vol;
	st_fill.acml_tr_pbmn	= st_mast.acml_tr_pbmn;

	memcpy(st_fill.cntg_type_code,kos_o_a3->s_cntg_type_code,sizeof(kos_o_a3->s_cntg_type_code));

	/* Update OPTTION SHARED MEMORY */
	Update_SHM_OptionMst(offset, (char *)&st_mast);
	Update_SHM_OptionFill(offset, (char *)&st_fill);

#ifdef _DEBUG_
	_Debug_Option_Data_A3(org_data);
	
    _DispHexLog(LOG_FILE, "HEX DUMP", &koshm->master[offset], sizeof(st_mast));
    _DispHexLog(LOG_FILE, "HEX DUMP", &koshm->fill[offset], sizeof(st_fill));

#endif
	return SUCCESS;

}

/* 지수옵션 마스터 업데이트 */
static int Update_SHM_OptionMst(int offset,char *pst)
{
    STRUC_OPT_MAST      *pst_mst;

    pst_mst = (STRUC_OPT_MAST *)pst;

    if(offset < 0)  return (0);

    koshm->master[offset].optn_prpr       = pst_mst->optn_prpr;
    koshm->master[offset].optn_oprc       = pst_mst->optn_oprc;
    koshm->master[offset].optn_hgpr       = pst_mst->optn_hgpr;
    koshm->master[offset].optn_lwpr       = pst_mst->optn_lwpr;
    koshm->master[offset].rgbf_prc        = pst_mst->rgbf_prc;

    koshm->master[offset].acml_vol		 = pst_mst->acml_vol;
    koshm->master[offset].acml_tr_pbmn   = pst_mst->acml_tr_pbmn;

	memcpy(koshm->master[offset].cntg_type_code, pst_mst->cntg_type_code,sizeof(pst_mst->cntg_type_code));

    return(1);
}
/* 지수옵션 체결 업데이트 */
static int Update_SHM_OptionFill(int offset,char *pst)
{
    STRUC_OPT_FILL      *pst_fill;

    pst_fill = (STRUC_OPT_FILL *)pst;

    if(offset < 0)  return (0);

    memcpy(koshm->fill[offset].stnd_iscd,pst_fill->stnd_iscd,sizeof(pst_fill->stnd_iscd)-1);
    memcpy(koshm->fill[offset].shrn_iscd,pst_fill->shrn_iscd,sizeof(pst_fill->shrn_iscd)-1);
    koshm->fill[offset].bsop_hour      = pst_fill->bsop_hour;
    koshm->fill[offset].stck_prpr      = pst_fill->stck_prpr;

    koshm->fill[offset].cntg_vol	   = pst_fill->cntg_vol	;
    koshm->fill[offset].acml_vol	   = pst_fill->acml_vol;
    koshm->fill[offset].acml_tr_pbmn   = pst_fill->acml_tr_pbmn;

	memcpy(koshm->fill[offset].cntg_type_code, pst_fill->cntg_type_code,sizeof(pst_fill->cntg_type_code));

    return(1);
}

/* 거래소 수신데이터 프린트 */
static int _Debug_Option_Data_A3(char *rcv_data)
{
    RCV_STK_A3_03_4     *a3;

    a3  = (RCV_STK_A3_03_4 *)&rcv_data[0];

    _DispLog(LOG_FILE, "Start............................[A3034]");
    _DispLog(LOG_FILE, "stnd_iscd =[%.*s]",sizeof(a3->s_stnd_iscd),a3->s_stnd_iscd);
    _DispLog(LOG_FILE, "stck_prpr =[%.*s]",sizeof(a3->s_optn_prpr),a3->s_optn_prpr);
    _DispLog(LOG_FILE, "cnqn =[%.*s]",sizeof(a3->s_cnqn),a3->s_cnqn);
    _DispLog(LOG_FILE, "acml_vol =[%.*s]",sizeof(a3->s_acml_cntg_qty),a3->s_acml_cntg_qty);
    _DispLog(LOG_FILE, "acml_tr_pbmn =[%.*s]",sizeof(a3->s_acml_tr_pbmn),a3->s_acml_tr_pbmn);

    _DispLog(LOG_FILE, "End..............................\n");

    return 1;
}
