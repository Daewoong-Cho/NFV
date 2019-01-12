/*****************************************************************
 * 프로그램명   : A0034.c
 * 작  성  자   : David Cho
 * 기      능   : 지수옵션 종목정보 UDP데이타 처리(A0034)
 * PROTOTYPE    : 
 *****************************************************************/

#include	"common.h"
#include	"shm.h"
#include	"fo.h"
#include	"koscom_fo.h"

#define LOG_FILE  "/home/david/log/proc_trans.log"

static int _Debug_Option_Data_A0(char *rcv_data);

extern  int OffsetOptf(char *fullcode);
extern  int AddOpt(CODEIDX_OPT *incd);

int proc_A0034(char *org_data)
{
	RCV_STK_A0_03_4 *kos_o_a0;
	STRUC_OPT_MAST	st_mast;
	int	offset = -1;

	if (koshm == NULL)
		koshm = (struct KOSPI200_OPT_INFO *)SetKOSharedMemory ();

	memset(&st_mast, 0x00, sizeof(st_mast));
#ifdef _DEBUG_
	_DispLog(LOG_FILE, "[INFO] A0034 Run... \n");
#endif

	kos_o_a0 = (RCV_STK_A0_03_4*)&org_data[0];

	/* 옵션 일련번호 */
	st_mast.optn_srno   = __Str2Int(kos_o_a0->s_issu_srno   , sizeof(kos_o_a0->s_issu_srno)); /* 종목일련번호 */
	memcpy(st_mast.stnd_iscd    , kos_o_a0->s_stnd_iscd,    sizeof(kos_o_a0->s_stnd_iscd));
	memcpy(st_mast.shrn_iscd   , kos_o_a0->s_stnd_iscd+3, sizeof(st_mast.shrn_iscd)-2);

	/* 그룹 구분 코드 */
	memcpy(st_mast.grp_cls_code , kos_o_a0->s_prod_cls_code+2,  sizeof(st_mast.grp_cls_code)-1);
	/* 상품 번호 */
	memcpy(st_mast.prod_no      , kos_o_a0->s_prod_cls_code+7,  sizeof(st_mast.prod_no)-1);
	/* 만기 년월 */
	memcpy(st_mast.mtrt_yymm    , kos_o_a0->s_mtrt_date,        sizeof(st_mast.mtrt_yymm)-1);
	/* 장내파생 한글 종목명 */
	memcpy(st_mast.ftop_kor_isnm    , kos_o_a0->s_kor_isnm,     sizeof(st_mast.ftop_kor_isnm)-1);

	/* 장내파생 영문 종목명 */
	memcpy(st_mast.ftop_eng_isnm    , kos_o_a0->s_eng_isnm,     sizeof(st_mast.ftop_eng_isnm)-1);
	/* HTS 옵션 구분 코드 */
	st_mast.hts_optn_cls_code[0]= kos_o_a0->s_stnd_iscd[3];
	/* 권리 행사2 구분 코드 */
	memcpy(st_mast.rght_evnt_cls_code, kos_o_a0->s_rght_evnt_type_code, sizeof(kos_o_a0->s_rght_evnt_type_code));
	/* 행사가 */
	st_mast.acpr        = __Str2Double(kos_o_a0->s_optn_acpr, sizeof(kos_o_a0->s_optn_acpr), 8);//행사가
	/* 조회용행사가 */
	st_mast.usiq_exer_prc   = __Str2Double(kos_o_a0->s_usiq_acpr    , sizeof(kos_o_a0->s_usiq_acpr), 8);
	/* 주식 상장 일자 */
	st_mast.stck_lstn_date  = __Str2Int(kos_o_a0->s_lstn_date   , sizeof(kos_o_a0->s_lstn_date));
	/* 기준 일수 */
	st_mast.stnd_dynu   = (short)__Str2Int(kos_o_a0->s_anul_stnd_dynu, sizeof(kos_o_a0->s_anul_stnd_dynu));
	/* HTS 잔존 일수 */
	st_mast.hts_rmnn_dynu   = (short)__Str2Int(kos_o_a0->s_rmnn_dynu, sizeof(kos_o_a0->s_rmnn_dynu));
	/* 근월물 구분 코드 */
	strncpy(st_mast.nmsc_cls_code, kos_o_a0->s_mmsc_cls_code, sizeof(kos_o_a0->s_mmsc_cls_code));
	/* ATM 구분 코드 */
	memcpy(st_mast.atm_cls_code, kos_o_a0->s_atm_cls_code,  sizeof(kos_o_a0->s_atm_cls_code));
	/* 옵션 최초 거래 일자 */
	st_mast.optn_frst_tr_date = __Str2Int(kos_o_a0->s_frst_cntg_date, sizeof(kos_o_a0->s_frst_cntg_date));
	/* 옵션 최종 거래 일자 */
	st_mast.optn_last_tr_date = __Str2Int(kos_o_a0->s_last_tr_date  , sizeof(kos_o_a0->s_last_tr_date));

	/* 영업일 잔존일수 add 20120710 */
	//st_mast.bsdy_rmnn_dynu = (short)GetBsdyRmnnDynu(st_mast.bsop_date, i_prdy_date, st_mast.optn_last_tr_date);
	
	/* 최종 거래 일자 구분 코드 */
	memcpy(st_mast.last_tr_date_cls_code, kos_o_a0->s_last_tr_day_yn, sizeof(kos_o_a0->s_last_tr_day_yn));
	/* 상장 유형 구분 코드  */
	memcpy(st_mast.lstn_type_cls_code, kos_o_a0->s_lstn_type_code,  sizeof(kos_o_a0->s_lstn_type_code));
	/* 상장 유형 일자 - 삭제 */
	//st_mast.lstn_type_date = __Str2Int(kos_o_a0->s_lstn_date, sizeof(kos_o_a0->s_lstn_date));

	/* 배당가치 : 배당액지수 미래 가치 값 */
	st_mast.dmix_futr_wrth_val = __Str2Double(kos_o_a0->s_dmix_fv_val, sizeof(kos_o_a0->s_dmix_fv_val), 6);

	/* 기준가격구분코드 (매매용아님,상세) */
	memcpy(st_mast.stnd_prc_cls_code, kos_o_a0->s_stnd_prc_cls_code, sizeof(kos_o_a0->s_stnd_prc_cls_code));
	/* 전일종가 구분코드 */
	memcpy(st_mast.prdy_clpr_cls_code, kos_o_a0->s_prdy_clpr_cls_code, sizeof(kos_o_a0->s_prdy_clpr_cls_code));
	/* 옵션 기준가 */
	st_mast.optn_sdpr   = __Str2Float(kos_o_a0->s_optn_sdpr , sizeof(kos_o_a0->s_optn_sdpr), 2);
	/* CD 금리 */
	st_mast.cd_mnrt     = __Str2Float(kos_o_a0->s_cd_mnrt       , sizeof(kos_o_a0->s_cd_mnrt), 3);
	/* 옵션 상한가 */
	st_mast.optn_mxpr   = __Str2Float(kos_o_a0->s_optn_mxpr , sizeof(kos_o_a0->s_optn_mxpr), 2);
	/* 옵션 하한가 */
	st_mast.optn_llam   = __Str2Float(kos_o_a0->s_optn_llam , sizeof(kos_o_a0->s_optn_llam), 2);
	/* 옵션 전일 종가 */
	st_mast.optn_prdy_clpr  = __Str2Float(kos_o_a0->s_optn_prdy_clpr, sizeof(kos_o_a0->s_optn_prdy_clpr), 2);
	/* 전일 거래량 */
	st_mast.prdy_vol    = __Str2Long(kos_o_a0->s_prdy_cntg_qty  , sizeof(kos_o_a0->s_prdy_cntg_qty));
	if(st_mast.optn_sdpr <= 0)
	{
		st_mast.optn_prpr   = st_mast.optn_prdy_clpr;
		st_mast.optn_sdpr   = st_mast.optn_prdy_clpr;
	}
	else
	{
		st_mast.optn_prpr   = st_mast.optn_sdpr;
	}

	/* 전일 거래대금 단위:천원으로 통일.(단윈으로 들어오므로 끝자리3자리 버림). overflow때문에 첫자리도 버림.  */
	st_mast.prdy_tr_pbmn    = __Str2Long(kos_o_a0->s_prdy_tr_pbmn+1 , sizeof(kos_o_a0->s_prdy_tr_pbmn)-4);

	/* 전일 미결제수량으로 당일의 미결제 시고저,현재,직전 수량을 초기화한다. 직전대비등을 제대로 계산위해. */
	st_mast.prdy_otst_stpl_qty  = __Str2Long(kos_o_a0->s_prdy_otst_stpl_qty, sizeof(kos_o_a0->s_prdy_otst_stpl_qty));
	st_mast.hts_otst_stpl_qty   = st_mast.prdy_otst_stpl_qty;
	st_mast.hts_otst_stpl_rgbf_qty  = st_mast.prdy_otst_stpl_qty;
	st_mast.otst_stpl_sta_qty   = st_mast.prdy_otst_stpl_qty;
	st_mast.otst_stpl_hghs_qty  = st_mast.prdy_otst_stpl_qty;
	st_mast.otst_stpl_lwst_qty  = st_mast.prdy_otst_stpl_qty;

	/* 전일증거금기준가구분코드 */
	memcpy(st_mast.prdy_deal_marg_sdpr_cls_code,kos_o_a0->s_prdy_marg_sdpr_cls_code,sizeof(kos_o_a0->s_prdy_marg_sdpr_cls_code));
	/* 전일증거금기준가 */
	st_mast.prdy_deal_marg_sdpr = __Str2Double(kos_o_a0->s_prdy_marg_sdpr, sizeof(kos_o_a0->s_prdy_marg_sdpr), 8);

	/* 전일 협의대량 거래량 */
	st_mast.prdy_dscs_lrqn_vol = __Str2Long(kos_o_a0->s_prdy_dscs_bltr_cntg_qty, sizeof(kos_o_a0->s_prdy_dscs_bltr_cntg_qty));
	/* 전일 협의대량 거래대금 */
	st_mast.prdy_dscs_lrqn_tr_pbmn = __Str2Long(kos_o_a0->s_prdy_dscs_bltr_cntg_pbmn, sizeof(kos_o_a0->s_prdy_dscs_bltr_cntg_pbmn));

	/* 연중 최고가 일자 */
	st_mast.dryy_hgpr_date = __Str2Int(kos_o_a0->s_dryy_hgpr_date, sizeof(kos_o_a0->s_dryy_hgpr_date));
	/* 옵션 연중 최고가 */
	st_mast.optn_dryy_hgpr = __Str2Float(kos_o_a0->s_dryy_hgpr  , sizeof(kos_o_a0->s_dryy_hgpr), 2);

	/* 연중 최저가 일자 */
	st_mast.dryy_lwpr_date = __Str2Int(kos_o_a0->s_dryy_lwpr_date, sizeof(kos_o_a0->s_dryy_lwpr_date));
	/* 옵션 연중 최저가 */
	st_mast.optn_dryy_lwpr = __Str2Float(kos_o_a0->s_dryy_lwpr  , sizeof(kos_o_a0->s_dryy_lwpr), 2);

	/* 상장 최고가 일자 */
	st_mast.lstn_hgpr_date = __Str2Int(kos_o_a0->s_lstn_hgpr_date, sizeof(kos_o_a0->s_lstn_hgpr_date));
	/* 옵션 상장 중 최고가 */
	st_mast.optn_lstn_medm_hgpr = __Str2Float(kos_o_a0->s_lstn_hgpr  , sizeof(kos_o_a0->s_lstn_hgpr), 2);

	/* 상장 최저가 일자 */
	st_mast.lstn_lwpr_date = __Str2Int(kos_o_a0->s_lstn_lwpr_date, sizeof(kos_o_a0->s_lstn_lwpr_date));
	/* 옵션 상장 중 최저가 */
	st_mast.optn_lstn_medm_lwpr = __Str2Float(kos_o_a0->s_lstn_lwpr  , sizeof(kos_o_a0->s_lstn_lwpr), 2);

	/* 내재 변동성 */
	st_mast.hts_ints_vltl  = __Str2Float(kos_o_a0->s_iv, sizeof(kos_o_a0->s_iv), 4);
	st_mast.mkob_ints_vltl = __Str2Float(kos_o_a0->s_iv, sizeof(kos_o_a0->s_iv), 4);

	/* 시장 조성 여부 */
	memcpy(st_mast.mrkt_prmg_yn , kos_o_a0->s_mrkt_prmg_cls_code,   sizeof(kos_o_a0->s_mrkt_prmg_cls_code));
	/* 옵션 거래 단위 */
	st_mast.optn_tr_unit = __Str2Double(kos_o_a0->s_optn_tr_unit, sizeof(kos_o_a0->s_optn_tr_unit), 8); /*거래단위*/

	/* 거래 승수 by atech 20090422 */
	st_mast.tr_mltl = __Str2Double(kos_o_a0->s_tr_mltl, sizeof(kos_o_a0->s_tr_mltl), 8);

	memcpy(st_mast.unas_stnd_iscd   , kos_o_a0->s_unas_stnd_iscd,   sizeof(kos_o_a0->s_unas_stnd_iscd));

	/* 조정 구분 코드 */
	memcpy(st_mast.adjs_cls_code    , kos_o_a0->s_adjs_cls_code,    sizeof(kos_o_a0->s_adjs_cls_code));
	/* 거래 정지 구분 코드 */
	memcpy(st_mast.tr_susp_cls_code, kos_o_a0->s_trht_yn,   sizeof(kos_o_a0->s_trht_yn));   //거래정지여부
	/* 결제 방법 구분 코드 */
	memcpy(st_mast.stlm_mthd_cls_code, kos_o_a0->s_last_stlm_mthd_code,     sizeof(kos_o_a0->s_last_stlm_mthd_code));
	// 협의 대량 거래 대상 여부 : 협의대량매매(통화옵션만 해당)
	memcpy(st_mast.dscs_lrqn_tr_trgt_yn, kos_o_a0->s_dscs_bltr_trgt_yn,     sizeof(kos_o_a0->s_dscs_bltr_trgt_yn));
	/* HTS 이론가 */
	st_mast.hts_thpr = __Str2Float(kos_o_a0->s_optn_thpr, sizeof(kos_o_a0->s_optn_thpr), 6);//이론가
	/* ATM 가격 */
	st_mast.atm_prc = __Str2Double(kos_o_a0->s_atm_prc, sizeof(kos_o_a0->s_atm_prc), 2);//등가격


	st_mast.optn_prdy_unas_prc = __Str2Float(kos_o_a0->s_unas_clpr  , sizeof(kos_o_a0->s_unas_clpr), 2);
	// 전일기초자산 가격으로 장전 기초자산가격 표시 : 20100818 CYTECA
	st_mast.unas_prc = st_mast.optn_prdy_unas_prc;

	st_mast.optn_prdy_clpr = __Str2Float(kos_o_a0->s_prdy_adjs_clpr, sizeof(kos_o_a0->s_prdy_adjs_clpr), 2);

	/* 상장폐지일자 */
	st_mast.lstn_abrg_date = __Str2Int(kos_o_a0->s_lstn_abrg_date, sizeof(kos_o_a0->s_lstn_abrg_date));
	/* 기초자산ID */
	memcpy(st_mast.unas_cls_code,kos_o_a0->s_unas_cls_code, sizeof(kos_o_a0->s_unas_cls_code));
	/* 최종결제일자 */
	st_mast.last_stlm_date = __Str2Int(kos_o_a0->s_last_stlm_date, sizeof(kos_o_a0->s_last_stlm_date));
	/* 조정사유코드 */
	memcpy(st_mast.adjs_reas_code,kos_o_a0->s_adjs_reas_code, sizeof(kos_o_a0->s_adjs_reas_code));
	/* 조정기준가격 9(10)V9(2)  */
	st_mast.adjs_sdpr = __Str2Float(kos_o_a0->s_adjs_sdpr, sizeof(kos_o_a0->s_adjs_sdpr), 2);
	/* 매매용기준가격구분코드 */
	st_mast.deal_stnd_prc_cls_code[0] = kos_o_a0->s_deal_stnd_prc_cls_code[0];
	/* 전일조정종가 */
	st_mast.prdy_adjs_clpr = __Str2Float(kos_o_a0->s_prdy_adjs_clpr, sizeof(kos_o_a0->s_prdy_adjs_clpr), 8);
	/* 기준이론가격 */
	st_mast.optn_stnd_thpr = __Str2Float(kos_o_a0->s_optn_stnd_thpr, sizeof(kos_o_a0->s_optn_stnd_thpr), 6);
	/* 전일시가 */
	st_mast.optn_prdy_oprc = __Str2Float(kos_o_a0->s_optn_prdy_oprc, sizeof(kos_o_a0->s_optn_prdy_oprc), 2);
	/* 전일고가 */
	st_mast.optn_prdy_hgpr = __Str2Float(kos_o_a0->s_optn_prdy_hgpr, sizeof(kos_o_a0->s_optn_prdy_hgpr), 2);
	/* 전일저가 */
	st_mast.optn_prdy_lwpr = __Str2Float(kos_o_a0->s_optn_prdy_lwpr, sizeof(kos_o_a0->s_optn_prdy_lwpr), 2);
	/* 전일최종체결시각 */
	st_mast.prdy_last_cntg_hour = __Str2Int(kos_o_a0->s_prdy_last_cntg_hour, sizeof(kos_o_a0->s_prdy_last_cntg_hour));
	/* 전일매도우선호가가격 */
	st_mast.prdy_askp_prc = __Str2Float(kos_o_a0->s_prdy_askp_prc, sizeof(kos_o_a0->s_prdy_askp_prc), 2);
	/* 전일매수우선호가가격 */
	st_mast.prdy_bidp_prc = __Str2Float(kos_o_a0->s_prdy_bidp_prc, sizeof(kos_o_a0->s_prdy_bidp_prc), 2);
	/* 내재변동성 */
	st_mast.iv = __Str2Float(kos_o_a0->s_iv, sizeof(kos_o_a0->s_iv), 4);
	/* 기초자산최대변동폭유형코드 */
	st_mast.unas_max_flxb_type_code[0] = kos_o_a0->s_unas_max_flxb_type_code[0];
	/* 기초자산최대변동폭 */
	st_mast.unas_max_flxb = __Str2Float(kos_o_a0->s_unas_max_flxb, sizeof(kos_o_a0->s_unas_max_flxb), 4);
	/* 월간거래일수 */
	st_mast.mntl_tr_dynu = (short)__Str2Int(kos_o_a0->s_mntl_tr_dynu, sizeof(kos_o_a0->s_mntl_tr_dynu));
	/* 연간거래일수 */
	st_mast.anul_tr_dynu = (short)__Str2Int(kos_o_a0->s_anul_tr_dynu, sizeof(kos_o_a0->s_anul_tr_dynu));
	/* 전일체결건수 */
	st_mast.prdy_cntg_csnu = __Str2Int(kos_o_a0->s_prdy_cntg_csnu, sizeof(kos_o_a0->s_prdy_cntg_csnu));
	/* 지정가호가조건구분코드 */
	st_mast.lmts_aspr_cond_cls_code[0] = kos_o_a0->s_lmts_aspr_cond_cls_code[0];
	/* 시장가호가조건구분코드 */
	st_mast.mrpr_aspr_cond_cls_code[0] = kos_o_a0->s_mrpr_aspr_cond_cls_code[0];
	/* 조건부지정가호가조건구분코드 */
	st_mast.cndn_lmts_aspr_cls_code[0] = kos_o_a0->s_cndn_lmts_aspr_cls_code[0];
	/* 최유리지정가호가조건구분코드 */
	st_mast.pmpr_lmts_aspr_cls_code[0] = kos_o_a0->s_pmpr_lmts_aspr_cls_code[0];

	memcpy(st_mast.cntg_prgs, "          ", sizeof(st_mast.cntg_prgs)-1);

	/* 휴장 여부 */
	st_mast.close_yn[0] = kos_o_a0->s_close_yn[0];

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

	/* Update OPTTION SHARED MEMORY */
	memcpy(&koshm->master[offset], (char *)&st_mast, sizeof(st_mast));

#ifdef _DEBUG_
	_Debug_Option_Data_A0(org_data);
#endif

	return SUCCESS;

}

/* 거래소 수신데이터 프린트 */
static int _Debug_Option_Data_A0(char *rcv_data)
{
    RCV_STK_A0_03_4     *a0;

    a0  = (RCV_STK_A0_03_4 *)&rcv_data[0];

    _DispLog(LOG_FILE, "Start............................[A0034]");
    _DispLog(LOG_FILE, "shrn_iscd =[%.*s]",sizeof(a0->s_shrn_iscd),a0->s_shrn_iscd);
    _DispLog(LOG_FILE, "kor_isnm =[%.*s]",sizeof(a0->s_kor_isnm),a0->s_kor_isnm);
#ifdef _DEBUG_
    _DispLog(LOG_FILE, "data_cls_code =[%.*s]",sizeof(a0->s_data_cls_code), a0->s_data_cls_code);
    _DispLog(LOG_FILE, "info_cls_code =[%.*s]",sizeof(a0->s_info_cls_code), a0->s_info_cls_code);
    _DispLog(LOG_FILE, "mrkt_cls_code =[%.*s]",sizeof(a0->s_mrkt_cls_code), a0->s_mrkt_cls_code);
    _DispLog(LOG_FILE, "issu_cnt =[%.*s]",sizeof(a0->s_issu_cnt),a0->s_issu_cnt);
    _DispLog(LOG_FILE, "bsop_date =[%.*s]",sizeof(a0->s_bsop_date), a0->s_bsop_date);
    _DispLog(LOG_FILE, "stnd_iscd =[%.*s]",sizeof(a0->s_stnd_iscd),a0->s_stnd_iscd);
    _DispLog(LOG_FILE, "issu_srno =[%.*s]",sizeof(a0->s_issu_srno), a0->s_issu_srno);
    _DispLog(LOG_FILE, "prod_cls_code =[%.*s]",sizeof(a0->s_prod_cls_code), a0->s_prod_cls_code);
    _DispLog(LOG_FILE, "kor_shrn_isnm =[%.*s]",sizeof(a0->s_kor_shrn_isnm), a0->s_kor_shrn_isnm);
    _DispLog(LOG_FILE, "eng_isnm =[%.*s]",sizeof(a0->s_eng_isnm),a0->s_eng_isnm);
    _DispLog(LOG_FILE, "eng_shrn_isnm =[%.*s]",sizeof(a0->s_eng_shrn_isnm), a0->s_eng_shrn_isnm);
    _DispLog(LOG_FILE, "lstn_date =[%.*s]",sizeof(a0->s_lstn_date), a0->s_lstn_date);
    _DispLog(LOG_FILE, "lstn_abrg_date =[%.*s]",sizeof(a0->s_lstn_abrg_date),a0->s_lstn_abrg_date);
    _DispLog(LOG_FILE, "spead_stnd_issu_cls_code =[%.*s]", sizeof(a0->s_spead_stnd_issu_cls_code),a0->s_spead_stnd_issu_cls_code);
    _DispLog(LOG_FILE, "last_stlm_mthd_code =[%.*s]", sizeof(a0->s_last_stlm_mthd_code),a0->s_last_stlm_mthd_code);
    _DispLog(LOG_FILE, "sign1 =[%.*s]",sizeof(a0->s_sign1), a0->s_sign1);
    _DispLog(LOG_FILE, "optn_mxpr =[%.*s]",sizeof(a0->s_optn_mxpr), a0->s_optn_mxpr);
    _DispLog(LOG_FILE, "sign2 =[%.*s]",sizeof(a0->s_sign2), a0->s_sign2);
    _DispLog(LOG_FILE, "optn_llam =[%.*s]",sizeof(a0->s_optn_llam), a0->s_optn_llam);
    _DispLog(LOG_FILE, "optn_sdpr =[%.*s]",sizeof(a0->s_optn_sdpr), a0->s_optn_sdpr);
    _DispLog(LOG_FILE, "unas_cls_code =[%.*s]",sizeof(a0->s_unas_cls_code), a0->s_unas_cls_code);
    _DispLog(LOG_FILE, "rght_evnt_type_code =[%.*s]", sizeof(a0->s_rght_evnt_type_code),a0->s_rght_evnt_type_code);
    _DispLog(LOG_FILE, "spead_type_code =[%.*s]", sizeof(a0->s_spead_type_code),a0->s_spead_type_code);
    _DispLog(LOG_FILE, "spead_nmsc_iscd =[%.*s]", sizeof(a0->s_spead_nmsc_iscd),a0->s_spead_nmsc_iscd);
    _DispLog(LOG_FILE, "spead_fmsc_iscd =[%.*s]", sizeof(a0->s_spead_fmsc_iscd),a0->s_spead_fmsc_iscd);
    _DispLog(LOG_FILE, "last_tr_date =[%.*s]",sizeof(a0->s_last_tr_date),a0->s_last_tr_date);
    _DispLog(LOG_FILE, "last_stlm_date =[%.*s]",sizeof(a0->s_last_stlm_date),a0->s_last_stlm_date);
    _DispLog(LOG_FILE, "mmsc_cls_code =[%.*s]",sizeof(a0->s_mmsc_cls_code), a0->s_mmsc_cls_code);
    _DispLog(LOG_FILE, "mtrt_date =[%.*s]",sizeof(a0->s_mtrt_date), a0->s_mtrt_date);
    _DispLog(LOG_FILE, "optn_acpr =[%.*s]",sizeof(a0->s_optn_acpr), a0->s_optn_acpr);
    _DispLog(LOG_FILE, "adjs_cls_code =[%.*s]",sizeof(a0->s_adjs_cls_code), a0->s_adjs_cls_code);
    _DispLog(LOG_FILE, "optn_tr_unit =[%.*s]",sizeof(a0->s_optn_tr_unit),a0->s_optn_tr_unit);
    _DispLog(LOG_FILE, "tr_mltl =[%.*s]", sizeof(a0->s_tr_mltl),a0->s_tr_mltl);
    _DispLog(LOG_FILE, "mrkt_prmg_cls_code =[%.*s]",sizeof(a0->s_mrkt_prmg_cls_code),a0->s_mrkt_prmg_cls_code);
    _DispLog(LOG_FILE, "lstn_type_code =[%.*s]",sizeof(a0->s_lstn_type_code),a0->s_lstn_type_code);
    _DispLog(LOG_FILE, "atm_prc =[%.*s]", sizeof(a0->s_atm_prc),a0->s_atm_prc);
    _DispLog(LOG_FILE, "adjs_reas_code =[%.*s]",sizeof(a0->s_adjs_reas_code),a0->s_adjs_reas_code);
    _DispLog(LOG_FILE, "unas_stnd_iscd =[%.*s]",sizeof(a0->s_unas_stnd_iscd),a0->s_unas_stnd_iscd);
    _DispLog(LOG_FILE, "unas_clpr =[%.*s]",sizeof(a0->s_unas_clpr), a0->s_unas_clpr);
    _DispLog(LOG_FILE, "rmnn_dynu =[%.*s]",sizeof(a0->s_rmnn_dynu), a0->s_rmnn_dynu);
    _DispLog(LOG_FILE, "adjs_sdpr =[%.*s]",sizeof(a0->s_adjs_sdpr), a0->s_adjs_sdpr);
    _DispLog(LOG_FILE, "stnd_prc_cls_code =[%.*s]",sizeof(a0->s_stnd_prc_cls_code), a0->s_stnd_prc_cls_code);
    _DispLog(LOG_FILE, "deal_stnd_prc_cls_code =[%.*s]",sizeof(a0->s_deal_stnd_prc_cls_code),a0->s_deal_stnd_prc_cls_code);
    _DispLog(LOG_FILE, "sign3 =[%.*s]",sizeof(a0->s_sign3), a0->s_sign3);
    _DispLog(LOG_FILE, "prdy_adjs_clpr =[%.*s]",sizeof(a0->s_prdy_adjs_clpr),a0->s_prdy_adjs_clpr);
    _DispLog(LOG_FILE, "dscs_bltr_trgt_yn =[%.*s]",sizeof(a0->s_dscs_bltr_trgt_yn), a0->s_dscs_bltr_trgt_yn);
    _DispLog(LOG_FILE, "prdy_marg_sdpr =[%.*s]",sizeof(a0->s_prdy_marg_sdpr),a0->s_prdy_marg_sdpr);
    _DispLog(LOG_FILE, "prdy_marg_sdpr_cls_code =[%.*s]",sizeof(a0->s_prdy_marg_sdpr_cls_code),a0->s_prdy_marg_sdpr_cls_code);
    _DispLog(LOG_FILE, "optn_thpr =[%.*s]",sizeof(a0->s_optn_thpr), a0->s_optn_thpr);
    _DispLog(LOG_FILE, "optn_stnd_thpr =[%.*s]",sizeof(a0->s_optn_stnd_thpr), a0->s_optn_stnd_thpr);
    _DispLog(LOG_FILE, "optn_prdy_excl_prc =[%.*s]",sizeof(a0->s_optn_prdy_excl_prc),a0->s_optn_prdy_excl_prc);
    _DispLog(LOG_FILE, "trht_yn =[%.*s]", sizeof(a0->s_trht_yn),a0->s_trht_yn);
    _DispLog(LOG_FILE, "crbr_mxpr =[%.*s]",sizeof(a0->s_crbr_mxpr), a0->s_crbr_mxpr);
    _DispLog(LOG_FILE, "crbr_llam =[%.*s]",sizeof(a0->s_crbr_llam), a0->s_crbr_llam);
    _DispLog(LOG_FILE, "usiq_acpr =[%.*s]",sizeof(a0->s_usiq_acpr), a0->s_usiq_acpr);
    _DispLog(LOG_FILE, "atm_cls_code =[%.*s]",sizeof(a0->s_atm_cls_code),a0->s_atm_cls_code);
    _DispLog(LOG_FILE, "last_tr_day_yn =[%.*s]",sizeof(a0->s_last_tr_day_yn),a0->s_last_tr_day_yn);
    _DispLog(LOG_FILE, "dmix_fv_val =[%.*s]", sizeof(a0->s_dmix_fv_val),a0->s_dmix_fv_val);
    _DispLog(LOG_FILE, "sign4 =[%.*s]",sizeof(a0->s_sign4), a0->s_sign4);
    _DispLog(LOG_FILE, "optn_prdy_clpr =[%.*s]",sizeof(a0->s_optn_prdy_clpr),a0->s_optn_prdy_clpr);
    _DispLog(LOG_FILE, "prdy_clpr_cls_code =[%.*s]",sizeof(a0->s_prdy_clpr_cls_code),a0->s_prdy_clpr_cls_code);
    _DispLog(LOG_FILE, "sign5 =[%.*s]",sizeof(a0->s_sign5), a0->s_sign5);
    _DispLog(LOG_FILE, "optn_prdy_oprc =[%.*s]",sizeof(a0->s_optn_prdy_oprc),a0->s_optn_prdy_oprc);
    _DispLog(LOG_FILE, "sign6 =[%.*s]",sizeof(a0->s_sign6), a0->s_sign6);
    _DispLog(LOG_FILE, "optn_prdy_hgpr =[%.*s]",sizeof(a0->s_optn_prdy_hgpr),a0->s_optn_prdy_hgpr);
    _DispLog(LOG_FILE, "sign7 =[%.*s]",sizeof(a0->s_sign7), a0->s_sign7);
    _DispLog(LOG_FILE, "optn_prdy_lwpr =[%.*s]",sizeof(a0->s_optn_prdy_lwpr),a0->s_optn_prdy_lwpr);
    _DispLog(LOG_FILE, "frst_cntg_date =[%.*s]",sizeof(a0->s_frst_cntg_date),a0->s_frst_cntg_date);
    _DispLog(LOG_FILE, "prdy_last_cntg_hour =[%.*s]", sizeof(a0->s_prdy_last_cntg_hour),a0->s_prdy_last_cntg_hour);
    _DispLog(LOG_FILE, "prdy_excl_prc =[%.*s]",sizeof(a0->s_prdy_excl_prc), a0->s_prdy_excl_prc);
    _DispLog(LOG_FILE, "excl_prc_thpr_dprt =[%.*s]",sizeof(a0->s_excl_prc_thpr_dprt),a0->s_excl_prc_thpr_dprt);
    _DispLog(LOG_FILE, "prdy_otst_stpl_qty =[%.*s]",sizeof(a0->s_prdy_otst_stpl_qty),a0->s_prdy_otst_stpl_qty);
    _DispLog(LOG_FILE, "sign8 =[%.*s]",sizeof(a0->s_sign8), a0->s_sign8);
    _DispLog(LOG_FILE, "prdy_askp_prc =[%.*s]",sizeof(a0->s_prdy_askp_prc), a0->s_prdy_askp_prc);
    _DispLog(LOG_FILE, "sign9 =[%.*s]",sizeof(a0->s_sign9), a0->s_sign9);
    _DispLog(LOG_FILE, "prdy_bidp_prc =[%.*s]",sizeof(a0->s_prdy_bidp_prc), a0->s_prdy_bidp_prc);
    _DispLog(LOG_FILE, "iv =[%.*s]",sizeof(a0->s_iv),a0->s_iv);
    _DispLog(LOG_FILE, "unas_max_flxb_type_code =[%.*s]", sizeof(a0->s_unas_max_flxb_type_code),a0->s_unas_max_flxb_type_code);
    _DispLog(LOG_FILE, "unas_max_flxb =[%.*s]",sizeof(a0->s_unas_max_flxb), a0->s_unas_max_flxb);
    _DispLog(LOG_FILE, "sign10 =[%.*s]",sizeof(a0->s_sign10),a0->s_sign10);
    _DispLog(LOG_FILE, "lstn_hgpr =[%.*s]",sizeof(a0->s_lstn_hgpr), a0->s_lstn_hgpr);
    _DispLog(LOG_FILE, "sign11 =[%.*s]",sizeof(a0->s_sign11),a0->s_sign11);
    _DispLog(LOG_FILE, "lstn_lwpr =[%.*s]",sizeof(a0->s_lstn_lwpr), a0->s_lstn_lwpr);
    _DispLog(LOG_FILE, "sign12 =[%.*s]",sizeof(a0->s_sign12),a0->s_sign12);
    _DispLog(LOG_FILE, "dryy_hgpr =[%.*s]",sizeof(a0->s_dryy_hgpr), a0->s_dryy_hgpr);
    _DispLog(LOG_FILE, "sign13 =[%.*s]",sizeof(a0->s_sign13),a0->s_sign13);
    _DispLog(LOG_FILE, "dryy_lwpr =[%.*s]",sizeof(a0->s_dryy_lwpr), a0->s_dryy_lwpr);
    _DispLog(LOG_FILE, "lstn_hgpr_date =[%.*s]",sizeof(a0->s_lstn_hgpr_date),a0->s_lstn_hgpr_date);
    _DispLog(LOG_FILE, "lstn_lwpr_date =[%.*s]",sizeof(a0->s_lstn_lwpr_date),a0->s_lstn_lwpr_date);
    _DispLog(LOG_FILE, "dryy_hgpr_date =[%.*s]",sizeof(a0->s_dryy_hgpr_date),a0->s_dryy_hgpr_date);
    _DispLog(LOG_FILE, "dryy_lwpr_date =[%.*s]",sizeof(a0->s_dryy_lwpr_date),a0->s_dryy_lwpr_date);
    _DispLog(LOG_FILE, "anul_stnd_dynu =[%.*s]",sizeof(a0->s_anul_stnd_dynu),a0->s_anul_stnd_dynu);
    _DispLog(LOG_FILE, "mntl_tr_dynu =[%.*s]",sizeof(a0->s_mntl_tr_dynu),a0->s_mntl_tr_dynu);
    _DispLog(LOG_FILE, "anul_tr_dynu =[%.*s]",sizeof(a0->s_anul_tr_dynu),a0->s_anul_tr_dynu);
    _DispLog(LOG_FILE, "prdy_cntg_csnu =[%.*s]",sizeof(a0->s_prdy_cntg_csnu),a0->s_prdy_cntg_csnu);
    _DispLog(LOG_FILE, "prdy_cntg_qty =[%.*s]",sizeof(a0->s_prdy_cntg_qty), a0->s_prdy_cntg_qty);
    _DispLog(LOG_FILE, "prdy_tr_pbmn =[%.*s]",sizeof(a0->s_prdy_tr_pbmn),a0->s_prdy_tr_pbmn);
    _DispLog(LOG_FILE, "prdy_dscs_bltr_cntg_qty =[%.*s]", sizeof(a0->s_prdy_dscs_bltr_cntg_qty),a0->s_prdy_dscs_bltr_cntg_qty);
    _DispLog(LOG_FILE, "prdy_dscs_bltr_cntg_pbmn =[%.*s]", sizeof(a0->s_prdy_dscs_bltr_cntg_pbmn),a0->s_prdy_dscs_bltr_cntg_pbmn);
    _DispLog(LOG_FILE, "cd_mnrt =[%.*s]", sizeof(a0->s_cd_mnrt),a0->s_cd_mnrt);
    _DispLog(LOG_FILE, "otst_limt_cnrc_cnt =[%.*s]", sizeof(a0->s_otst_limt_cnrc_qty),a0->s_otst_limt_cnrc_qty);
    _DispLog(LOG_FILE, "blng_prgp_code =[%.*s]", sizeof(a0->s_blng_prgp_code),a0->s_blng_prgp_code);
    _DispLog(LOG_FILE, "prgp_ofst_rate =[%.*s]", sizeof(a0->s_prgp_ofst_rate),a0->s_prgp_ofst_rate);
    _DispLog(LOG_FILE, "s_lmts_aspr_cond_cls_code =[%.*s]", sizeof(a0->s_lmts_aspr_cond_cls_code),a0->s_lmts_aspr_cond_cls_code);
    _DispLog(LOG_FILE, "s_mrpr_aspr_cond_cls_code =[%.*s]", sizeof(a0->s_mrpr_aspr_cond_cls_code),a0->s_mrpr_aspr_cond_cls_code);
    _DispLog(LOG_FILE, "s_cndn_lmts_aspr_cls_code =[%.*s]", sizeof(a0->s_cndn_lmts_aspr_cls_code),a0->s_cndn_lmts_aspr_cls_code);
    _DispLog(LOG_FILE, "s_pmpr_lmts_aspr_cls_code =[%.*s]", sizeof(a0->s_pmpr_lmts_aspr_cls_code),a0->s_pmpr_lmts_aspr_cls_code);
#endif
    _DispLog(LOG_FILE, "End..............................\n");

    return 1;
}
