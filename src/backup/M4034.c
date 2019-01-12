/*****************************************************************
 * 프로그램명   : M4034.c
 * 작  성  자   : David Cho
 * 기      능   : 지수옵션 공개장운영 UDP데이타 처리(M4034)
 * PROTOTYPE    :
 *****************************************************************/

#include	"common.h"
#include	"shm_def.h"
#include	"fo.h"
#include	"koscom_fo.h"

#define LOG_FILE  "/home/david/log/proc_trans.log"

extern	int	g_fep_hour;

static int _Debug_Option_Data_M4(char *rcv_data);
static int Update_SHM_OptionMaster(int offset,char *pst);

int proc_M4034(char *org_data)
{
	RCV_STK_M4_03_4 *kos_o_m4;
	STRUC_OPT_MAST	st_mast;

	int	offset = -1;

	if (koshm == NULL)
		koshm = (struct KOSPI200_OPT_INFO *)SetKOSharedMemory ();

	memset(&st_mast, 0x00, sizeof(st_mast));

	kos_o_m4 = (RCV_STK_M4_03_4*)&org_data[0];

	strncpy(st_mast.stnd_iscd, kos_o_m4->s_stnd_iscd, sizeof(kos_o_m4->s_stnd_iscd));
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

    //장운영구분
    strncpy(st_mast.mkop_cls_code, kos_o_m4->s_mkop_cls_code, sizeof(st_mast.mkop_cls_code)-1);

    //장상태 구분코드
    strncpy(st_mast.mkop_stat_code, kos_o_m4->s_mrkt_stat_cls_code, sizeof(st_mast.mkop_stat_code)-1);

	/* Update OPTTION SHARED MEMORY */
	Update_SHM_OptionMaster(offset, (char *)&st_mast);


	_Debug_Option_Data_M4(org_data);
#ifdef _DEBUG_
#endif
	
	return SUCCESS;

}

/* 지수옵션 마스터 업데이트 */
static int Update_SHM_OptionMaster(int offset,char *pst)
{
    STRUC_OPT_MAST      *pst_mast;

    pst_mast = (STRUC_OPT_MAST *)pst;

    if(offset < 0)  return(0);

	memcpy(koshm->master[offset].mkop_cls_code,pst_mast->mkop_cls_code,sizeof(pst_mast->mkop_cls_code)-1);
	memcpy(koshm->master[offset].mkop_stat_code,pst_mast->mkop_stat_code,sizeof(pst_mast->mkop_stat_code)-1);

    return(1);
}

static int _Debug_Option_Data_M4(char *rcv_data)
{
    RCV_STK_M4_03_4     *m4;

    m4 = (RCV_STK_M4_03_4 *)&rcv_data[0];

    _DispLog(LOG_FILE, "Start............................[M4034]");
    _DispLog(LOG_FILE, "종목코드       [%.*s]", sizeof(m4->s_stnd_iscd), m4->s_stnd_iscd);
    _DispLog(LOG_FILE, "mkop_cls_code  [%.*s]", sizeof(m4->s_mkop_cls_code), m4->s_mkop_cls_code);
    _DispLog(LOG_FILE, "mkop_stat_code [%.*s]", sizeof(m4->s_mrkt_stat_cls_code), m4->s_mrkt_stat_cls_code);

    return 1;
}
