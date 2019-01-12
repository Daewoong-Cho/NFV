/*****************************************************************
 * 프로그램명   : B6034.c
 * 작  성  자   : David Cho
 * 기      능   : 지수옵션 우선호가 UDP데이타 처리(B6034)
 * PROTOTYPE    :
 *****************************************************************/

#include	"common.h"
#include	"shm_def.h"
#include	"fo.h"
#include	"koscom_fo.h"

#define LOG_FILE  "/home/david/log/proc_trans.log"

extern	int	g_fep_hour;

static int _Debug_Option_Data_B6(char *rcv_data);

static int Update_SHM_OptionAsk(int offset,char *pst);
static int Update_SHM_OptionAsk2(int offset,char *pst);

int proc_B6034(char *org_data)
{
	RCV_STK_B6_03_4 *kos_o_b6;
	STRUC_OPT_MAST	st_mast;
	STRUC_OPT_ASK	st_ask;

	int	offset = -1;

	if (koshm == NULL)
		koshm = (struct KOSPI200_OPT_INFO *)SetKOSharedMemory ();

	memset(&st_ask, 0x00, sizeof(st_ask));
	memset(&st_mast, 0x00, sizeof(st_mast));

	kos_o_b6 = (RCV_STK_B6_03_4*)&org_data[0];

	strncpy(st_ask.stnd_iscd, kos_o_b6->s_stnd_iscd, sizeof(kos_o_b6->s_stnd_iscd));
	strncpy(st_ask.shrn_iscd, &st_ask.stnd_iscd[3], 8);

	/* offset setting */
	offset = OffsetOptf(st_ask.stnd_iscd);
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

	st_ask.bsop_hour       = g_fep_hour;
	st_ask.askp_rsqn1      = __Str2Long(kos_o_b6->s_askp_rsqn1,      sizeof(kos_o_b6->s_askp_rsqn1));
	st_ask.bidp_rsqn1      = __Str2Long(kos_o_b6->s_bidp_rsqn1,      sizeof(kos_o_b6->s_bidp_rsqn1));
	st_ask.total_askp_rsqn = __Str2Long(kos_o_b6->s_total_askp_rsqn, sizeof(kos_o_b6->s_total_askp_rsqn));
	st_ask.total_bidp_rsqn = __Str2Long(kos_o_b6->s_total_bidp_rsqn, sizeof(kos_o_b6->s_total_bidp_rsqn));
	st_ask.total_askp_csnu = __Str2Int (kos_o_b6->s_total_askp_csnu, sizeof(kos_o_b6->s_total_askp_csnu));
	st_ask.total_bidp_csnu = __Str2Int (kos_o_b6->s_total_bidp_csnu, sizeof(kos_o_b6->s_total_bidp_csnu));

	st_ask.optn_askp1 = __Str2Float(kos_o_b6->s_optn_askp1, sizeof(kos_o_b6->s_optn_askp1), 2);
	st_ask.optn_askp2 = __Str2Float(kos_o_b6->s_optn_askp2, sizeof(kos_o_b6->s_optn_askp2), 2);
	st_ask.optn_askp3 = __Str2Float(kos_o_b6->s_optn_askp3, sizeof(kos_o_b6->s_optn_askp3), 2);
	st_ask.optn_askp4 = __Str2Float(kos_o_b6->s_optn_askp4, sizeof(kos_o_b6->s_optn_askp4), 2);
	st_ask.optn_askp5 = __Str2Float(kos_o_b6->s_optn_askp5, sizeof(kos_o_b6->s_optn_askp5), 2);
	st_ask.optn_bidp1 = __Str2Float(kos_o_b6->s_optn_bidp1, sizeof(kos_o_b6->s_optn_bidp1), 2);
	st_ask.optn_bidp2 = __Str2Float(kos_o_b6->s_optn_bidp2, sizeof(kos_o_b6->s_optn_bidp2), 2);
	st_ask.optn_bidp3 = __Str2Float(kos_o_b6->s_optn_bidp3, sizeof(kos_o_b6->s_optn_bidp3), 2);
	st_ask.optn_bidp4 = __Str2Float(kos_o_b6->s_optn_bidp4, sizeof(kos_o_b6->s_optn_bidp4), 2);
	st_ask.optn_bidp5 = __Str2Float(kos_o_b6->s_optn_bidp5, sizeof(kos_o_b6->s_optn_bidp5), 2);
	st_ask.askp_rsqn1 = __Str2Long (kos_o_b6->s_askp_rsqn1, sizeof(kos_o_b6->s_askp_rsqn1));
	st_ask.askp_rsqn2 = __Str2Long (kos_o_b6->s_askp_rsqn2, sizeof(kos_o_b6->s_askp_rsqn2));
	st_ask.askp_rsqn3 = __Str2Long (kos_o_b6->s_askp_rsqn3, sizeof(kos_o_b6->s_askp_rsqn3));
	st_ask.askp_rsqn4 = __Str2Long (kos_o_b6->s_askp_rsqn4, sizeof(kos_o_b6->s_askp_rsqn4));
	st_ask.askp_rsqn5 = __Str2Long (kos_o_b6->s_askp_rsqn5, sizeof(kos_o_b6->s_askp_rsqn5));
	st_ask.bidp_rsqn1 = __Str2Long (kos_o_b6->s_bidp_rsqn1, sizeof(kos_o_b6->s_bidp_rsqn1));
	st_ask.bidp_rsqn2 = __Str2Long (kos_o_b6->s_bidp_rsqn2, sizeof(kos_o_b6->s_bidp_rsqn2));
	st_ask.bidp_rsqn3 = __Str2Long (kos_o_b6->s_bidp_rsqn3, sizeof(kos_o_b6->s_bidp_rsqn3));
	st_ask.bidp_rsqn4 = __Str2Long (kos_o_b6->s_bidp_rsqn4, sizeof(kos_o_b6->s_bidp_rsqn4));
	st_ask.bidp_rsqn5 = __Str2Long (kos_o_b6->s_bidp_rsqn5, sizeof(kos_o_b6->s_bidp_rsqn5));
	st_ask.total_askp_5_aspr_rsqn = st_ask.askp_rsqn1 + st_ask.askp_rsqn2 +
									 st_ask.askp_rsqn3 + st_ask.askp_rsqn4 + st_ask.askp_rsqn5;
	st_ask.total_bidp_5_aspr_rsqn = st_ask.bidp_rsqn1 + st_ask.bidp_rsqn2 +
									 st_ask.bidp_rsqn3 + st_ask.bidp_rsqn4 + st_ask.bidp_rsqn5;

	st_ask.askp_csnu1 = __Str2Int(kos_o_b6->s_askp_csnu1, sizeof(kos_o_b6->s_askp_csnu1));
	st_ask.askp_csnu2 = __Str2Int(kos_o_b6->s_askp_csnu2, sizeof(kos_o_b6->s_askp_csnu2));
	st_ask.askp_csnu3 = __Str2Int(kos_o_b6->s_askp_csnu3, sizeof(kos_o_b6->s_askp_csnu3));
	st_ask.askp_csnu4 = __Str2Int(kos_o_b6->s_askp_csnu4, sizeof(kos_o_b6->s_askp_csnu4));
	st_ask.askp_csnu5 = __Str2Int(kos_o_b6->s_askp_csnu5, sizeof(kos_o_b6->s_askp_csnu5));
	st_ask.bidp_csnu1 = __Str2Int(kos_o_b6->s_bidp_csnu1, sizeof(kos_o_b6->s_bidp_csnu1));
	st_ask.bidp_csnu2 = __Str2Int(kos_o_b6->s_bidp_csnu2, sizeof(kos_o_b6->s_bidp_csnu2));
	st_ask.bidp_csnu3 = __Str2Int(kos_o_b6->s_bidp_csnu3, sizeof(kos_o_b6->s_bidp_csnu3));
	st_ask.bidp_csnu4 = __Str2Int(kos_o_b6->s_bidp_csnu4, sizeof(kos_o_b6->s_bidp_csnu4));
	st_ask.bidp_csnu5 = __Str2Int(kos_o_b6->s_bidp_csnu5, sizeof(kos_o_b6->s_bidp_csnu5));
	st_ask.total_askp_5_aspr_csnu = st_ask.askp_csnu1 + st_ask.askp_csnu2 +
									 st_ask.askp_csnu3 + st_ask.askp_csnu4 + st_ask.askp_csnu5;
	st_ask.total_bidp_5_aspr_csnu = st_ask.bidp_csnu1 + st_ask.bidp_csnu2 +
									 st_ask.bidp_csnu3 + st_ask.bidp_csnu4 + st_ask.bidp_csnu5;

#if 0
	st_ask.seln_rsqn_icdc1 = (int)O_ASK_RSQN_CHG(st_ask.optn_askp1, st_p_hoga, st_ask.askp_rsqn1);
	st_ask.seln_rsqn_icdc2 = (int)O_ASK_RSQN_CHG(st_ask.optn_askp2, st_p_hoga, st_ask.askp_rsqn2);
	st_ask.seln_rsqn_icdc3 = (int)O_ASK_RSQN_CHG(st_ask.optn_askp3, st_p_hoga, st_ask.askp_rsqn3);
	st_ask.seln_rsqn_icdc4 = (int)O_ASK_RSQN_CHG(st_ask.optn_askp4, st_p_hoga, st_ask.askp_rsqn4);
	st_ask.seln_rsqn_icdc5 = (int)O_ASK_RSQN_CHG(st_ask.optn_askp5, st_p_hoga, st_ask.askp_rsqn5);

	st_ask.total_seln_5_aspr_rsqn_icdc = (int)(st_ask.total_askp_5_aspr_rsqn - st_p_hoga.total_askp_5_aspr_rsqn);
	st_ask.total_seln_rsqn_icdc        = (int)(st_ask.total_askp_rsqn - st_p_hoga.total_askp_rsqn);

	st_ask.shnu_rsqn_icdc1 = (int)O_BID_RSQN_CHG(st_ask.optn_bidp1, st_p_hoga, st_ask.bidp_rsqn1);
	st_ask.shnu_rsqn_icdc2 = (int)O_BID_RSQN_CHG(st_ask.optn_bidp2, st_p_hoga, st_ask.bidp_rsqn2);
	st_ask.shnu_rsqn_icdc3 = (int)O_BID_RSQN_CHG(st_ask.optn_bidp3, st_p_hoga, st_ask.bidp_rsqn3);
	st_ask.shnu_rsqn_icdc4 = (int)O_BID_RSQN_CHG(st_ask.optn_bidp4, st_p_hoga, st_ask.bidp_rsqn4);
	st_ask.shnu_rsqn_icdc5 = (int)O_BID_RSQN_CHG(st_ask.optn_bidp5, st_p_hoga, st_ask.bidp_rsqn5);

	st_ask.total_shnu_5_aspr_rsqn_icdc = (int)(st_ask.total_bidp_5_aspr_rsqn - st_p_hoga.total_bidp_5_aspr_rsqn);
	st_ask.total_shnu_rsqn_icdc        = (int)(st_ask.total_bidp_rsqn - st_p_hoga.total_bidp_rsqn);

#endif

	/* Update OPTTION SHARED MEMORY */
	if (1)
		Update_SHM_OptionAsk(offset, (char *)&st_ask);
	else
		Update_SHM_OptionAsk2(offset, (char *)&st_ask);

#ifdef _DEBUG_
	_Debug_Option_Data_B6(org_data);
#endif
	
	return SUCCESS;

}

/* 지수옵션 전체 호가 업데이트 */
static int Update_SHM_OptionAsk(int offset,char *pst)
{
    STRUC_OPT_ASK      *pst_ask;

    pst_ask = (STRUC_OPT_ASK *)pst;

    if(offset < 0)  return (0);

    memcpy(koshm->ask[offset].stnd_iscd,pst_ask->stnd_iscd,sizeof(pst_ask->stnd_iscd)-1);
    memcpy(koshm->ask[offset].shrn_iscd,pst_ask->shrn_iscd,sizeof(pst_ask->shrn_iscd)-1);
    koshm->ask[offset].bsop_hour                   = pst_ask->bsop_hour;
    koshm->ask[offset].aspr_srno                   = pst_ask->aspr_srno;
    koshm->ask[offset].optn_askp1                  = pst_ask->optn_askp1;
    koshm->ask[offset].optn_askp2                  = pst_ask->optn_askp2;
    koshm->ask[offset].optn_askp3                  = pst_ask->optn_askp3;
    koshm->ask[offset].optn_askp4                  = pst_ask->optn_askp4;
    koshm->ask[offset].optn_askp5                  = pst_ask->optn_askp5;
    koshm->ask[offset].optn_bidp1                  = pst_ask->optn_bidp1;
    koshm->ask[offset].optn_bidp2                  = pst_ask->optn_bidp2;
    koshm->ask[offset].optn_bidp3                  = pst_ask->optn_bidp3;
    koshm->ask[offset].optn_bidp4                  = pst_ask->optn_bidp4;
    koshm->ask[offset].optn_bidp5                  = pst_ask->optn_bidp5;
    koshm->ask[offset].askp_csnu1                  = pst_ask->askp_csnu1;
    koshm->ask[offset].askp_csnu2                  = pst_ask->askp_csnu2;
    koshm->ask[offset].askp_csnu3                  = pst_ask->askp_csnu3;
    koshm->ask[offset].askp_csnu4                  = pst_ask->askp_csnu4;
    koshm->ask[offset].askp_csnu5                  = pst_ask->askp_csnu5;
    koshm->ask[offset].total_askp_5_aspr_csnu      = pst_ask->total_askp_5_aspr_csnu;
    koshm->ask[offset].total_askp_csnu             = pst_ask->total_askp_csnu;
    koshm->ask[offset].bidp_csnu1                  = pst_ask->bidp_csnu1;
    koshm->ask[offset].bidp_csnu2                  = pst_ask->bidp_csnu2;
    koshm->ask[offset].bidp_csnu3                  = pst_ask->bidp_csnu3;
    koshm->ask[offset].bidp_csnu4                  = pst_ask->bidp_csnu4;
    koshm->ask[offset].bidp_csnu5                  = pst_ask->bidp_csnu5;
    koshm->ask[offset].total_bidp_5_aspr_csnu      = pst_ask->total_bidp_5_aspr_csnu;
    koshm->ask[offset].total_bidp_csnu             = pst_ask->total_bidp_csnu;
    koshm->ask[offset].askp_rsqn1                  = pst_ask->askp_rsqn1;
    koshm->ask[offset].askp_rsqn2                  = pst_ask->askp_rsqn2;
    koshm->ask[offset].askp_rsqn3                  = pst_ask->askp_rsqn3;
    koshm->ask[offset].askp_rsqn4                  = pst_ask->askp_rsqn4;
    koshm->ask[offset].askp_rsqn5                  = pst_ask->askp_rsqn5;
    koshm->ask[offset].total_askp_5_aspr_rsqn      = pst_ask->total_askp_5_aspr_rsqn;
    koshm->ask[offset].total_askp_rsqn             = pst_ask->total_askp_rsqn;
    koshm->ask[offset].bidp_rsqn1                  = pst_ask->bidp_rsqn1;
    koshm->ask[offset].bidp_rsqn2                  = pst_ask->bidp_rsqn2;
    koshm->ask[offset].bidp_rsqn3                  = pst_ask->bidp_rsqn3;
    koshm->ask[offset].bidp_rsqn4                  = pst_ask->bidp_rsqn4;
    koshm->ask[offset].bidp_rsqn5                  = pst_ask->bidp_rsqn5;
    koshm->ask[offset].total_bidp_5_aspr_rsqn      = pst_ask->total_bidp_5_aspr_rsqn;
    koshm->ask[offset].total_bidp_rsqn             = pst_ask->total_bidp_rsqn;
    koshm->ask[offset].seln_rsqn_icdc1             = pst_ask->seln_rsqn_icdc1;
    koshm->ask[offset].seln_rsqn_icdc2             = pst_ask->seln_rsqn_icdc2;
    koshm->ask[offset].seln_rsqn_icdc3             = pst_ask->seln_rsqn_icdc3;
    koshm->ask[offset].seln_rsqn_icdc4             = pst_ask->seln_rsqn_icdc4;
    koshm->ask[offset].seln_rsqn_icdc5             = pst_ask->seln_rsqn_icdc5;
    koshm->ask[offset].total_seln_5_aspr_rsqn_icdc = pst_ask->total_seln_5_aspr_rsqn_icdc;
    koshm->ask[offset].total_seln_rsqn_icdc        = pst_ask->total_seln_rsqn_icdc;
    koshm->ask[offset].shnu_rsqn_icdc1             = pst_ask->shnu_rsqn_icdc1;
    koshm->ask[offset].shnu_rsqn_icdc2             = pst_ask->shnu_rsqn_icdc2;
    koshm->ask[offset].shnu_rsqn_icdc3             = pst_ask->shnu_rsqn_icdc3;
    koshm->ask[offset].shnu_rsqn_icdc4             = pst_ask->shnu_rsqn_icdc4;
    koshm->ask[offset].shnu_rsqn_icdc5             = pst_ask->shnu_rsqn_icdc5;
    koshm->ask[offset].total_shnu_5_aspr_rsqn_icdc = pst_ask->total_shnu_5_aspr_rsqn_icdc;
    koshm->ask[offset].total_shnu_rsqn_icdc        = pst_ask->total_shnu_rsqn_icdc;

    return(1);
}

/* 지수옵션 호가 부분 업데이트 */
static int Update_SHM_OptionAsk2(int offset,char *pst)
{
    STRUC_OPT_ASK      *pst_ask;

    pst_ask = (STRUC_OPT_ASK *)pst;

    if(offset < 0)  return(0);

    memcpy(koshm->ask[offset].stnd_iscd,pst_ask->stnd_iscd,sizeof(pst_ask->stnd_iscd)-1);
    memcpy(koshm->ask[offset].shrn_iscd,pst_ask->shrn_iscd,sizeof(pst_ask->shrn_iscd)-1);
    koshm->ask[offset].bsop_hour       = pst_ask->bsop_hour;
    koshm->ask[offset].aspr_srno       = pst_ask->aspr_srno;
    koshm->ask[offset].total_askp_csnu = pst_ask->total_askp_csnu;
    koshm->ask[offset].total_bidp_csnu = pst_ask->total_bidp_csnu;
    koshm->ask[offset].total_askp_rsqn = pst_ask->total_askp_rsqn;
    koshm->ask[offset].total_bidp_rsqn = pst_ask->total_bidp_rsqn;

    return(1);
}

/* 거래소 수신데이터 프린트 */
static int _Debug_Option_Data_B6(char *rcv_data)
{
    RCV_STK_B6_03_4     *b6;

    b6  = (RCV_STK_B6_03_4 *)&rcv_data[0];

    _DispLog(LOG_FILE, "Start............................[B6034]");
    _DispLog(LOG_FILE, "stnd_iscd =[%.*s]",sizeof(b6->s_stnd_iscd),b6->s_stnd_iscd);
    _DispLog(LOG_FILE, "optn_bidp1 =[%.*s]",sizeof(b6->s_optn_bidp1),b6->s_optn_bidp1);
    _DispLog(LOG_FILE, "optn_askp1 =[%.*s]",sizeof(b6->s_optn_askp1),b6->s_optn_askp1);
    _DispLog(LOG_FILE, "antc_cnpr =[%.*s]",sizeof(b6->s_antc_cnpr),b6->s_antc_cnpr);

    _DispLog(LOG_FILE, "End..............................\n");

    return 1;
}
