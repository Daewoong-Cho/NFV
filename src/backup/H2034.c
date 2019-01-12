/*****************************************************************
 * 프로그램명   : H2034.c
 * 작  성  자   : David Cho
 * 기      능   : 지수옵션 미결제약정 UDP데이타 처리(H2034)
 * PROTOTYPE    :
 *****************************************************************/

#include	"common.h"
#include	"shm_def.h"
#include	"fo.h"
#include	"koscom_fo.h"

#define LOG_FILE  "/home/david/log/proc_trans.log"

extern	int	g_fep_hour;

static int _Debug_Option_Data_H2(char *rcv_data);
static int Update_SHM_OptionPrdyMicheMaster(int offset,char *pst);
static int Update_SHM_OptionMicheMaster(int offset,char *pst);

int proc_H2034(char *org_data)
{
	RCV_STK_H2_03_4 *kos_o_h2;
	STRUC_OPT_MAST	st_mast;

	int	offset = -1;

	if (koshm == NULL)
		koshm = (struct KOSPI200_OPT_INFO *)SetKOSharedMemory ();

	memset(&st_mast, 0x00, sizeof(st_mast));

	kos_o_h2 = (RCV_STK_H2_03_4*)&org_data[0];

	strncpy(st_mast.stnd_iscd, kos_o_h2->s_stnd_iscd, sizeof(kos_o_h2->s_stnd_iscd));
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

	/* Update OPTTION SHARED MEMORY */
	//미결제약정 수량
	if (kos_o_h2->s_otst_stpl_cls_code[1] == '0') /* M0 전일 확정 */
	{
		st_mast.prdy_otst_stpl_qty = __Str2Long(kos_o_h2->s_otst_stpl_qty, sizeof(kos_o_h2->s_otst_stpl_qty));
		Update_SHM_OptionPrdyMicheMaster(offset, (char *)&st_mast);
	}
	else
	{
		st_mast.hts_otst_stpl_qty = __Str2Long(kos_o_h2->s_otst_stpl_qty, sizeof(kos_o_h2->s_otst_stpl_qty));
		Update_SHM_OptionMicheMaster(offset, (char *)&st_mast);
	}


	_Debug_Option_Data_H2(org_data);
#ifdef _DEBUG_
#endif
	
	return SUCCESS;

}

/* 지수옵션 미결제약정 전일확정 마스터 업데이트 */
static int Update_SHM_OptionPrdyMicheMaster(int offset,char *pst)
{
    STRUC_OPT_MAST      *pst_mast;

    pst_mast = (STRUC_OPT_MAST *)pst;

    if(offset < 0)  return(0);

    koshm->master[offset].prdy_otst_stpl_qty = pst_mast->prdy_otst_stpl_qty;

    return(1);
}

/* 지수옵션 미결제약정 당일확정 마스터 업데이트 */
static int Update_SHM_OptionMicheMaster(int offset,char *pst)
{
    STRUC_OPT_MAST      *pst_mast;

    pst_mast = (STRUC_OPT_MAST *)pst;

    if(offset < 0)  return(0);

    koshm->master[offset].prdy_otst_stpl_qty = pst_mast->prdy_otst_stpl_qty;

    return(1);
}

static int _Debug_Option_Data_H2(char *rcv_data)
{
    RCV_STK_H2_03_4     *dat;

    dat = (RCV_STK_H2_03_4 *)&rcv_data[0];

    _DispLog(LOG_FILE, "Start............................[H2034]");
    _DispLog(LOG_FILE, "stnd_iscd  =[%.*s]", sizeof(dat->s_stnd_iscd  ), dat->s_stnd_iscd );
    _DispLog(LOG_FILE, "hts_otst_stpl_qty  =[%.*s]", sizeof(dat->s_otst_stpl_qty  ), dat->s_otst_stpl_qty );

    return 1;
}
