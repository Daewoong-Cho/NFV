/*****************************************************************
 * 프로그램명   : N7034.c
 * 작  성  자   : David Cho
 * 기      능   : 지수옵션 민감도 UDP데이타 처리(N7034)
 * PROTOTYPE    :
 *****************************************************************/

#include	"common.h"
#include	"shm_def.h"
#include	"fo.h"
#include	"koscom_fo.h"

#define LOG_FILE  "/home/david/log/proc_trans.log"

extern	int	g_fep_hour;

static int _Debug_Option_Data_N7(char *rcv_data);
static int Update_SHM_OptionMaster(int offset,char *pst);

int proc_N7034(char *org_data)
{
	RCV_STK_N7_03_4 *kos_o_n7;
	STRUC_OPT_MAST	st_mast;

	int	offset = -1;

	if (koshm == NULL)
		koshm = (struct KOSPI200_OPT_INFO *)SetKOSharedMemory ();

	memset(&st_mast, 0x00, sizeof(st_mast));

	kos_o_n7 = (RCV_STK_N7_03_4*)&org_data[0];

	strncpy(st_mast.stnd_iscd, kos_o_n7->s_stnd_iscd, sizeof(kos_o_n7->s_stnd_iscd));
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

	// 전일 확정치 값은 pass
	if(kos_o_n7->s_cofm_cls_code[0] == '1')     {
		return 0;
	}

	// 델타
	st_mast.udp_delta = __Str2Double(kos_o_n7->s_sense_delta, sizeof(kos_o_n7->s_sense_delta), 6);
	if(kos_o_n7->s_sign[0] == '-')
	st_mast.udp_delta *= -1;

	st_mast.delta = st_mast.udp_delta;

	// 세타
	st_mast.theta = __Str2Double(kos_o_n7->s_sense_theta, sizeof(kos_o_n7->s_sense_theta), 6);
	if(kos_o_n7->s_tsign[0] == '-')
	st_mast.theta *= -1;

	//베가 
	st_mast.vega = __Str2Double(kos_o_n7->s_sense_vega, sizeof(kos_o_n7->s_sense_vega), 6);
	if(kos_o_n7->s_vsign[0] == '-')
	st_mast.vega *= -1;

	// 감마
	st_mast.gama = __Str2Double(kos_o_n7->s_sense_gama, sizeof(kos_o_n7->s_sense_gama), 6);
	if(kos_o_n7->s_gsign[0] == '-')
	st_mast.gama *= -1;

	// 로우
	st_mast.rho = __Str2Double(kos_o_n7->s_sense_rho, sizeof(kos_o_n7->s_sense_rho), 6);
	if(kos_o_n7->s_rsign[0] == '-')
	st_mast.rho *= -1;

	/* Update OPTTION SHARED MEMORY */
	Update_SHM_OptionMaster(offset, (char *)&st_mast);


	_Debug_Option_Data_N7(org_data);
#ifdef _DEBUG_
#endif
	
	return SUCCESS;

}

/* 지수옵션 민감도 마스터 업데이트 */
static int Update_SHM_OptionMaster(int offset,char *pst)
{
    STRUC_OPT_MAST      *pst_mast;

    pst_mast = (STRUC_OPT_MAST *)pst;

    if(offset < 0)  return(0);

    koshm->master[offset].delta = pst_mast->delta;
    koshm->master[offset].theta = pst_mast->theta;
    koshm->master[offset].gama  = pst_mast->gama;
    koshm->master[offset].vega  = pst_mast->vega;
    koshm->master[offset].rho   = pst_mast->rho;

    return(1);
}

static int _Debug_Option_Data_N7(char *rcv_data)
{
    RCV_STK_N7_03_4     *n7;

    n7 = (RCV_STK_N7_03_4 *)&rcv_data[0];

    _DispLog(LOG_FILE, "Start............................[N7034]");
    _DispLog(LOG_FILE, "종목코드      [%.*s]", sizeof(n7->s_stnd_iscd), n7->s_stnd_iscd);
    _DispLog(LOG_FILE, "생성일자      [%.*s]", sizeof(n7->s_bsop_date), n7->s_bsop_date);
    _DispLog(LOG_FILE, "생성시각      [%.*s]", sizeof(n7->s_bsop_hour), n7->s_bsop_hour);
    _DispLog(LOG_FILE, "확정여부      [%.*s]", sizeof(n7->s_cofm_cls_code), n7->s_cofm_cls_code);
    _DispLog(LOG_FILE, "기초자산ID    [%.*s]", sizeof(n7->s_unas_cls_code), n7->s_unas_cls_code);
    _DispLog(LOG_FILE, "부호          [%.*s]", sizeof(n7->s_sign), n7->s_sign);
    _DispLog(LOG_FILE, "민감도델타    [%.*s]", sizeof(n7->s_sense_delta), n7->s_sense_delta);
    _DispLog(LOG_FILE, "부호          [%.*s]", sizeof(n7->s_tsign), n7->s_tsign);
    _DispLog(LOG_FILE, "민감도세타    [%.*s]", sizeof(n7->s_sense_theta), n7->s_sense_theta);
    _DispLog(LOG_FILE, "부호          [%.*s]", sizeof(n7->s_vsign), n7->s_vsign);
    _DispLog(LOG_FILE, "민감도베가    [%.*s]", sizeof(n7->s_sense_vega), n7->s_sense_vega);
    _DispLog(LOG_FILE, "부호          [%.*s]", sizeof(n7->s_gsign), n7->s_gsign);
    _DispLog(LOG_FILE, "민감도감마    [%.*s]", sizeof(n7->s_sense_gama), n7->s_sense_gama);
    _DispLog(LOG_FILE, "부호          [%.*s]", sizeof(n7->s_rsign), n7->s_rsign);
    _DispLog(LOG_FILE, "민감도로      [%.*s]", sizeof(n7->s_sense_rho), n7->s_sense_rho);

    return 1;
}
