#ifndef	_FO_H_
#define	_FO_H_

/*-------------------------------------------------------------------------- 
 * 옵션 마스터
 * STRUC_OPT_MAST
 *-------------------------------------------------------------------------*/

typedef struct {
    char    stnd_iscd[12+1];                    /*  NOT_NULL 표준 종목코드                      */
    char    shrn_iscd[9+1];                     /*  NOT_NULL 단축 종목코드                      */
    int     bsop_date;                          /*  NOT_NULL 주식 영업 일자                     */
    char    prod_no[3+1];                       /*  NOT_NULL 거래 대상 상품 코드                */
    int     optn_srno;                          /*  종목 일련번호                               */
    char    grp_cls_code[3+1];                  /*  그룹 구분 코드                              */
    char    ftop_kor_isnm[80+1];                /*  한글 종목명                                 */
    char    ftop_eng_isnm[80+1];                /*  영문 종목명                                 */
    int     stck_lstn_date;                     /*  상장 일자                                   */
    int     lstn_abrg_date;                     /*  상장폐지일자                                */
    char    stlm_mthd_cls_code[1+1];            /*  결제 방법 구분 코드                         */
    char    unas_cls_code[3+1];                 /*  기초자산ID                                  */
    char    rght_evnt_cls_code[1+1];            /*  권리 행사2 구분 코드                        */
    int     optn_last_tr_date;                  /*  최종 거래 일자                              */
    int     last_stlm_date;                     /*  최종결제일자                                */
    char    nmsc_cls_code[1+1];                 /*  근월물 구분 코드(1:최근월물,n:n째월물)      */
    char    mtrt_yymm[6+1];                     /*  만기 년월                                   */
    double  acpr;                               /*  행사가                                      */
    char    adjs_cls_code[1+1];                 /*  조정 구분 코드                              */
    double  optn_tr_unit;                       /*  거래 단위                                   */
    double  tr_mltl;                            /*  거래승수                                    */
    char    mrkt_prmg_yn[1+1];                  /*  시장 조성 여부                              */
    char    lstn_type_cls_code[1+1];            /*  상장 유형 구분 코드                         */
    double  atm_prc;                            /*  ATM 가격                                    */
    char    adjs_reas_code[2+1];                /*  조정사유코드                                */
                                                /*      00:해당사항없음, 01:권리락, 02:배당락,  */
                                                /*      03:분배락, 04:권배락 05:중간배당락,     */
                                                /*      06:권리중간배당락, 99:기타              */
    char    unas_stnd_iscd[12+1];               /*  기초자산 표준 종목코드                      */
    float   optn_prdy_unas_prc;                 /*  전일 기초자산 가격                          */
    short   hts_rmnn_dynu;                      /*  잔존 일수                                   */
    float   adjs_sdpr;                          /*  조정기준가격 9(10)V9(2)                     */
                                                /*  주식파생상품의 기초주권 조정기준가격        */
    char    stnd_prc_cls_code[2+1];             /*  기준 가격 구분 코드                         */
    char    deal_stnd_prc_cls_code[1+1];        /*  매매용기준가격구분코드                      */
                                                /*      0:해당없음 1:실세 2:기세                */
                                                /*      3:이론가 4:대상자산종가                 */
    float   prdy_adjs_clpr;                     /*  전일조정종가    9(9)V9(8) (6, 7차 적용)     */
    char    dscs_lrqn_tr_trgt_yn[1+1];          /*  협의 대량 거래 대상 여부                    */
    double  prdy_deal_marg_sdpr;                /*  전일 매매 증거금 기준가                     */
    char    prdy_deal_marg_sdpr_cls_code[2+1];  /*  전일 매매 증거금 기준가 구분 코드:1->2변경  */
    float   hts_thpr;                           /*  정산 이론가                                 */
    float   optn_stnd_thpr;                     /*  기준이론가격-6차 추가 9(9)V(6)              */
    char    tr_susp_cls_code[2+1];              /*  거래 정지 구분 코드                         */
    double  usiq_exer_prc;                      /*  조회용 행사1 가격                           */
    char    atm_cls_code[1+1];                  /*  ATM 구분 코드                               */
    char    last_tr_date_cls_code[1+1];         /*  최종 거래 일자 구분 코드                    */
    double  dmix_futr_wrth_val;                 /*  배당액지수 미래 가치 값                     */
    float   optn_prdy_clpr;                     /*  전일 종가                                   */
    char    prdy_clpr_cls_code[1+1];            /*  전일 종가 구분 코드                         */
    float   optn_prdy_oprc;                     /*  전일시가  9(10)V9(2) (6, 7차 적용)          */
    float   optn_prdy_hgpr;                     /*  전일고가  9(10)V9(2) (6, 7차 적용)          */
    float   optn_prdy_lwpr;                     /*  전일저가  9(10)V9(2) (6, 7차 적용)          */
    int     optn_frst_tr_date;                  /*  최초 거래 일자                              */
    int     prdy_last_cntg_hour;                /*  전일최종체결시각                            */
    long    prdy_otst_stpl_qty;                 /*  전일 미결제 약정 수량                       */
    float   prdy_askp_prc;                      /*  전일매도우선호가가격  9(10)V9(2)            */
    float   prdy_bidp_prc;                      /*  전일매수우선호가가격  9(10)V9(2)            */
    float   iv;                                 /*  내재변동성-9차(X(5)->9(6)V9(4)              */
    char    unas_max_flxb_type_code[1+1];       /*  기초자산최대변동폭유형코드                  */
    float   unas_max_flxb;                      /*  기초자산최대변동폭  9(4)V9(2)               */
    float   optn_lstn_medm_hgpr;                /*  상장 중 고가                                */
    float   optn_lstn_medm_lwpr;                /*  상장 중 저가                                */
    float   optn_dryy_hgpr;                     /*  연중 고가                                   */
    float   optn_dryy_lwpr;                     /*  연중 저가                                   */
    int     lstn_hgpr_date;                     /*  상장 고가 일자                              */
    int     lstn_lwpr_date;                     /*  상장 저가 일자                              */
    int     dryy_hgpr_date;                     /*  연중 고가 일자                              */
    int     dryy_lwpr_date;                     /*  연중 저가 일자                              */
    short   stnd_dynu;                          /*  연간기준 일수                               */
    short   mntl_tr_dynu;                       /*  월간거래일수                                */
    short   anul_tr_dynu;                       /*  연간거래일수                                */
    int     prdy_cntg_csnu;                     /*  전일체결건수                                */
    long    prdy_vol;                           /*  전일 거래량                                 */
    long    prdy_tr_pbmn;                       /*  전일 거래 대금                              */
    long    prdy_dscs_lrqn_vol;                 /*  전일 협의 대량 거래량                       */
    long    prdy_dscs_lrqn_tr_pbmn;             /*  전일 협의 대량 거래 대금                    */
    float   cd_mnrt;                            /*  CD 금리                                     */
    char    lmts_aspr_cond_cls_code[1+1];       /*  지정가호가조건구분코드                      */
    char    mrpr_aspr_cond_cls_code[1+1];       /*  시장가호가조건구분코드                      */
    char    cndn_lmts_aspr_cls_code[1+1];       /*  조건부지정가호가조건구분코드                */
    char    pmpr_lmts_aspr_cls_code[1+1];       /*  최유리지정가호가조건구분코드                */
    char    hts_optn_cls_code[1+1];             /*  구분 코드                                   */
    char    mkop_cls_code[3+1];                 /*  장운영 구분 코드         add                */
    char    mkop_stat_code[2+1];                /*  장운영 상태 코드                            */

    int     bsop_hour;                          /*  최종 시간                                   */
    float   optn_prpr;                          /*  현재가                                      */
    float   optn_oprc;                          /*  시가                                        */
    float   optn_hgpr;                          /*  고가                                        */
    float   optn_lwpr;                          /*  저가                                        */
    char    prdy_vrss_sign[1+1];                /*  전일 대비 부호                              */
    float   optn_prdy_vrss;                     /*  전일 대비                                   */
    float   prdy_ctrt;                          /*  전일 대비율                                 */
    long    last_cnqn;                          /*  최종 체결량 (순매수량)                      */
    long    acml_vol;                           /*  누적 거래량                                 */
    long    acml_tr_pbmn;                       /*  누적 거래 대금                              */
    int     oprc_hour;                          /*  시가 시간                                   */
    int     hgpr_hour;                          /*  고가 시간                                   */
    int     lwpr_hour;                          /*  저가 시간                                   */
    float   optn_mxpr;                          /*  상한가                                      */
    float   optn_llam;                          /*  하한가                                      */
    float   optn_sdpr;                          /*  기준가                                      */
    float   rgbf_prc;                           /*  직전가격                                    */
    long    hts_otst_stpl_qty;                  /*  미결제 약정 수량                            */
    long    otst_stpl_sta_qty;                  /*  미결제 약정 시작 수량                       */
    long    otst_stpl_hghs_qty;                 /*  미결제 약정 최고2 수량                      */
    long    otst_stpl_lwst_qty;                 /*  미결제 약정 최저 수량                       */
    int     hts_otst_stpl_qty_icdc;             /*  미결제 약정 수량 증감                       */
                                                /*      미결제자동갱신을 체결때만 하기로 하여,  */
                                                /*      이항목은 미결제 전일대비로 사용함. 0    */
    long    hts_otst_stpl_rgbf_qty;             /*  미결제 약정 직전 수량(체결수신기준)         */
    long    d2_bef_otst_stpl_qty;               /*  전전일 미결제 약정 수량 9.16 add            */
    float   antc_prc;                           /*  예상 가격                                   */
    long    seln_vol;                           /*  매도 거래량                                 */
    long    shnu_vol;                           /*  매수 거래량                                 */
    int     seln_cntg_csnu;                     /*  매도 체결 건수                              */
    int     shnu_cntg_csnu;                     /*  매수 체결 건수                              */
    long    seln_cntg_smtn;                     /*  매도 체결 합계                              */
    long    shnu_cntg_smtn;                     /*  매수 체결 합계                              */
    long    dscs_lrqn_vol;                      /*  협의 대량 거래량                            */
    long    dscs_lrqn_tr_pbmn;                  /*  협의 대량 거래 대금                         */
    char    cntg_type_code[2+1];                /*  체결유형코드 - 1)일반매매                   */
    char    deal_cntg_mthd_code[1+1];           /*  매매 체결 방법 코드                         */

    double  deal_marg_sdpr;                     /*  매매 증거금 기준가                          */
    char    deal_marg_sdpr_cls_code[1+1];       /*  매매 증거금 기준가 구분 코드                */
    double  evnt_stlm_prc;                      /*  행사2 결제 가격                             */
    char    evnt_stlm_prc_cls_code[1+1];        /*  행사2 결제 가격 구분 코드                   */

    int     lstn_type_date;                     /*  상장 유형 일자                              */
    float   optn_prdy_thpr;                     /*  전일 이론가                                 */
    float   prdy_ints_vltl;                     /*  전일 내재변동성     2008.8.25 add           */
    char    unas_shrn_iscd[9+1];                /*  기초자산 단축 종목코드                      */
    float   unas_prc;                           /*  기초자산 가격 (별도데몬으로처리)            */
    float   unas_hist_vltl;                     /*  기초자산 역사적 변동성                      */
    float   hts_ints_vltl;                      /*  내재변동성                                  */
    float   prit;                               /*  패리티                                      */
    float   delta;                              /*  델타                                        */
    float   gama;                               /*  감마                                        */
    float   theta;                              /*  세타                                        */
    float   vega;                               /*  베가                                        */
    float   rho;                                /*  로우                                        */
    int     smns_hour_srno;                     /*  동시간 체결 일련번호                        */
    float   mkob_ints_vltl;                     /*  장전내재변동성                              */
    float   clop_avrg_ints_vltl;                /*  콜 평균 내재 변동성                         */
    float   ptop_avrg_ints_vltl;                /*  풋 평균 내재 변동성                         */
    char    cntg_prgs[10+1];                    /*  체결틱 추이 size변경 7->10 20120710         */
    int     data_srno;                          /*  데이타 일련 번호                            */
    int     fill_int;
    long    lrqn_vol;                           /*  대량매매 누적거래량                         */
    long    lrqn_tr_pbmn;                       /*  대량매매 누적거래대금                       */

#if 0
    // Zis 20110316 : 1분틱을 마스터에 적용함. (종목코드, 단축코드, 영업일 컬럼은 제외)
    int     min_bsop_hour;                      /*  NOT_NULL 영업 시간                          */
    float   min_optn_prpr;                      /*  현재가                                      */
    float   min_optn_oprc;                      /*  시가                                        */
    float   min_optn_hgpr;                      /*  고가                                        */
    float   min_optn_lwpr;                      /*  저가                                        */
    char    min_prdy_vrss_sign[1+1];            /*  전일 대비 부호                              */
    float   min_optn_prdy_vrss;                 /*  전일 대비                                   */
    float   min_prdy_ctrt;                      /*  전일 대비율                                 */
    char    min_cntg_cls_code[1+1];             /*  체결 구분 코드                              */
    long    min_cnqn;                           /*  체결량                                      */
    long    min_acml_vol;                       /*  누적 거래량                                 */
    long    min_acml_tr_pbmn;                   /*  누적 거래 대금                              */
    long    min_otst_stpl_sta_qty;              /*  미결제 약정 시작 수량                       */
    long    min_otst_stpl_hghs_qty;             /*  미결제 약정 최고2 수량                      */
    long    min_otst_stpl_lwst_qty;             /*  미결제 약정 최저 수량                       */
    long    min_hts_otst_stpl_qty;              /*  미결제 약정 수량                            */
    long    min_seln_cntg_smtn;                 /*  매도 체결 합계                              */
    long    min_shnu_cntg_smtn;                 /*  매수 체결 합계                              */
    int     min_seln_cntg_csnu;                 /*  매도 체결 건수                              */
    int     min_shnu_cntg_csnu;                 /*  매수 체결 건수                              */
    float   min_optn_askp;                      /*  매도호가                                    */
    float   min_optn_bidp;                      /*  매수호가                                    */
    long    min_total_askp_rsqn;                /*  총 매도호가 잔량                            */
    int     min_total_askp_csnu;                /*  총 매도호가 건수                            */
    long    min_total_bidp_rsqn;                /*  총 매수호가 잔량                            */
    int     min_total_bidp_csnu;                /*  총 매수호가 건수                            */
    float   min_unas_prc;                       /*  기초자산 가격                               */
    char    min_unas_prdy_vrss_sign[1+1];       /*  기초자산 전일 대비 부호                     */
    float   min_unas_prdy_vrss;                 /*  기초자산 전일 대비                          */
    long    min_unas_acml_vol;                  /*  기초자산 누적거래량                         */
    float   min_hts_thpr;                       /*  이론가                                      */
    float   min_hts_ints_vltl;                  /*  내재 변동성                                 */
    float   min_prit;                           /*  패리티                                      */
    float   min_delta;                          /*  델타                                        */
    float   min_gama;                           /*  감마                                        */
    float   min_theta;                          /*  세타                                        */
    float   min_vega;                           /*  베가                                        */
    float   min_rho;                            /*  로우                                        */
    long    min_askp_rsqn1;                     /*  매도호가 잔량1                              */
    long    min_bidp_rsqn1;                     /*  매수호가 잔량1                              */
    float   min_unas_hist_vltl;                 /*  기초자산 역사적 변동성                      */
    float   min_clop_avrg_ints_vltl;            /*  콜 평균 내재 변동성                         */
    float   min_ptop_avrg_ints_vltl;            /*  풋 평균 내재 변동성                         */
    long    min_stck_data_srno;                 /*  데이터 일련번호                             */

#endif
    double  udp_delta;                          /*  UDP 수신 민감도델타(N7034) -20110705        */
    float   unas_hist_vltl_20;                  /*  기초자산 역사적 변동성 --DEL                */
    float   unas_hist_vltl_60;                  /*  기초자산 역사적 변동성 --DEL                */
    float   unas_hist_vltl_90;                  /*  기초자산 역사적 변동성 --DEL                */
    float   unas_hist_vltl_120;                 /*  기초자산 역사적 변동성 --DEL                */
    float   unas_hist_vltl_250;                 /*  기초자산 역사적 변동성 --DEL                */
    double  d4_clpr_smtn;                       /*  4일 종가 합계                               */
    double  d9_clpr_smtn;                       /*  9일 종가 합계                               */
    double  d19_clpr_smtn;                      /*  19일 종가 합계                              */
    // add 20120625
    int     dstr_rvok_hour;                     /*  배분 해제 시간                              */
    char    dstr_aply_cls_code[1+1];            /*  배분 적용 구분 코드 1 배분개시, 2 배분해제  */
    char    dstr_pros_cls_code[1+1];            /*  배분 처리 구분 코드                         */
                                                /*  1 매수상한, 2 매수하한,                     */
                                                /*  3 매도상한, 4 매도하한                      */
    short   bsdy_rmnn_dynu;                     /*  영업일 잔존 일수 add 20120710               */
    char    antc_cls_code[1+1];                 /*  예상 구분 코드 0:정규장, 1:예상             */
    // add 20121113
    double  d2_clpr_smtn;                       /*  2일 종가 합계                               */
    char    close_yn[1+1];                      /*  휴장 여부 - Y/N                             */
    float   askp_ints_vltl;                     /*  매도호가 내재 변동성                        */
    float   bidp_ints_vltl;                     /*  매수호가 내재 변동성                        */

    int     filler[20];                         /* 23->20                 add 20130125          */
} STRUC_OPT_MAST;

/*--------------------------------------------------------------------------
* 호가 Structure
* STRUC_ASK
*-------------------------------------------------------------------------*/

typedef struct
{
    char    stnd_iscd[12+1];                /*  NOT_NULL 표준 종목코드                      */
    char    shrn_iscd[9+1];             /*  NOT_NULL 단축 종목코드                      */
    int     bsop_hour;                          /*  최종 시간                                   */
    float   optn_askp1;                         /*  매도호가1                                   */
    float   optn_askp2;                         /*  매도호가2                                   */
    float   optn_askp3;                         /*  매도호가3                                   */
    float   optn_askp4;                         /*  매도호가4                                   */
    float   optn_askp5;                         /*  매도호가5                                   */
    float   optn_bidp1;                         /*  매수호가1                                   */
    float   optn_bidp2;                         /*  매수호가2                                   */
    float   optn_bidp3;                         /*  매수호가3                                   */
    float   optn_bidp4;                         /*  매수호가4                                   */
    float   optn_bidp5;                         /*  매수호가5                                   */
    int     askp_csnu1;                         /*  매도호가 건수1                              */
    int     askp_csnu2;                         /*  매도호가 건수2                              */
    int     askp_csnu3;                         /*  매도호가 건수3                              */
    int     askp_csnu4;                         /*  매도호가 건수4                              */
    int     askp_csnu5;                         /*  매도호가 건수5                              */
    int     total_askp_5_aspr_csnu;             /*  총 매도호가 5 호가 건수                     */
    int     total_askp_csnu;                    /*  총 매도호가 건수                            */
    int     bidp_csnu1;                         /*  매수호가 건수1                              */
    int     bidp_csnu2;                         /*  매수호가 건수2                              */
    int     bidp_csnu3;                         /*  매수호가 건수3                              */
    int     bidp_csnu4;                         /*  매수호가 건수4                              */
    int     bidp_csnu5;                         /*  매수호가 건수5                              */
    int     total_bidp_5_aspr_csnu;             /*  총 매수호가 5 호가 건수                     */
    int     total_bidp_csnu;                    /*  총 매수호가 건수                            */
    long    askp_rsqn1;                         /*  매도호가 잔량1                              */
    long    askp_rsqn2;                         /*  매도호가 잔량2                              */
    long    askp_rsqn3;                         /*  매도호가 잔량3                              */
    long    askp_rsqn4;                         /*  매도호가 잔량4                              */
    long    askp_rsqn5;                         /*  매도호가 잔량5                              */
    long    total_askp_5_aspr_rsqn;             /*  총 매도호가 5 호가 잔량                     */
    long    total_askp_rsqn;                    /*  총 매도호가 잔량                            */
    long    bidp_rsqn1;                         /*  매수호가 잔량1                              */
    long    bidp_rsqn2;                         /*  매수호가 잔량2                              */
    long    bidp_rsqn3;                         /*  매수호가 잔량3                              */
    long    bidp_rsqn4;                         /*  매수호가 잔량4                              */
    long    bidp_rsqn5;                         /*  매수호가 잔량5                              */
    long    total_bidp_5_aspr_rsqn;             /*  총매수호가 5 호가 잔량                      */
    long    total_bidp_rsqn;                    /*  총 매수호가 잔량                            */
    int     seln_rsqn_icdc1;                    /*  매도 잔량 증감1                             */
    int     seln_rsqn_icdc2;                    /*  매도 잔량 증감2                             */
    int     seln_rsqn_icdc3;                    /*  매도 잔량 증감3                             */
    int     seln_rsqn_icdc4;                    /*  매도 잔량 증감4                             */
    int     seln_rsqn_icdc5;                    /*  매도 잔량 증감5                             */
    int     total_seln_5_aspr_rsqn_icdc;        /*  총 매도 5 호가 잔량 증감                    */
    int     total_seln_rsqn_icdc;               /*  총 매도 잔량 증감                           */
    int     shnu_rsqn_icdc1;                    /*  매수 잔량 증감1                             */
    int     shnu_rsqn_icdc2;                    /*  매수 잔량 증감2                             */
    int     shnu_rsqn_icdc3;                    /*  매수 잔량 증감3                             */
    int     shnu_rsqn_icdc4;                    /*  매수 잔량 증감4                             */
    int     shnu_rsqn_icdc5;                    /*  매수 잔량 증감5                             */
    int     total_shnu_5_aspr_rsqn_icdc;        /*  총 매수 5 호가 잔량 증감                    */
    int     total_shnu_rsqn_icdc;               /*  총 매수 잔량 증감                           */
    int     aspr_srno;                          /*  호가 일련번호                               */

    int     filler[5];
} STRUC_OPT_ASK;

typedef struct
{
    char    stnd_iscd[12+1];                    /*  NOT_NULL    표준 종목코드                   */
    char    shrn_iscd[9+1];						/*  NOT_NULL    유가증권 단축 종목코드          */
    int     bsop_date;                          /*  NOT_NULL    주식 영업 일자                  */
    int     bsop_hour;                          /*  NOT_NULL    주식 체결 시간                  */
    long    stck_data_srno;                     /*  주식 데이터 일련번호                        */
    char    new_mkop_cls_code[2+1];             /*  신 장운영 구분 코드                         */
                                                /*  정규시간외 구분 코드                        */
    char    cntg_type_code[2+1];                /*  체결 유형 코드                              */
    float   stck_prpr;                          /*  주식 현재가                                 */
    char    prdy_vrss_sign[1+1];                /*  전일 대비 부호                              */
    int     prdy_vrss;                          /*  전일 대비                                   */
    float   prdy_ctrt;                          /*  전일 대비율                                 */
    long    acml_vol;                           /*  누적 거래량                                 */
    long    acml_tr_pbmn;                       /*  누적 거래 대금                              */
    long    cntg_vol;                           /*  체결 거래량                                 */
    long    cntg_tr_pbmn;                       /*  체결 거래 대금                              */
    char    cntg_cls_code[1+1];                 /*  체결 구분 코드                              */
    int     askp1;                              /*  매도호가1                                   */
    int     bidp1;                              /*  매수호가1                                   */
    int     askp2;                              /*  매도호가2                                   */
    int     bidp2;                              /*  매수호가2                                   */
    int     askp3;                              /*  매도호가3                                   */
    int     bidp3;                              /*  매수호가3                                   */
    long    askp_rsqn1;                         /*  매도호가 잔량1                              */
    long    bidp_rsqn1;                         /*  매수호가 잔량1                              */
    long    askp_rsqn2;                         /*  매도호가 잔량2                              */
    long    bidp_rsqn2;                         /*  매수호가 잔량2                              */
    long    askp_rsqn3;                         /*  매도호가 잔량3                              */
    long    bidp_rsqn3;                         /*  매수호가 잔량3                              */
    long    total_askp_rsqn;                    /*  총 매도호가 잔량                            */
    long    total_bidp_rsqn;                    /*  총 매수호가 잔량                            */
    long    seln_cntg_smtn;                     /*  매도 체결 합계                              */
    long    shnu_cntg_smtn;                     /*  매수 체결 합계                              */
    long    seln_tr_pbmn;                       /*  매도 거래 대금(누적)                        */
    long    shnu_tr_pbmn;                       /*  매수 거래 대금(누적)                        */
    long    seln_cnqn;                          /*  매도 체결량                                 */
    long    shnu_cnqn;                          /*  매수 체결량                                 */
    int     seln_cntg_csnu;                     /*  매도 체결 건수                              */
    int     shnu_cntg_csnu;                     /*  매수 체결 건수                              */
    char    askp_agrm_yn[1+1];                  /*  매도호가 일치 여부                          */
    char    hour_cls_code[1+1];                 /*  시간 구분 코드                              */
    float   acml_prtt_rate;                     /*  누적 계수                                   */
    int     smns_hour_srno;                     /*  NOT_NULL    동일 시간 일련번호              */
    char    cond_lrqn_cls_yn[1+1];              /*  조건 대량 여부  - Del                       */
    long    stnr_cntg_smtn;                     /*  보합 체결 합계                              */
    int     stnr_cntg_csnu;                     /*  보합 체결 건수                              */
    char    rgbf_cntg_cls_code[1+1];            /*  직전 체결 구분 코드                         */
                                                /*  1:상승 2:하락 ' ':보합                      */
} STRUC_OPT_FILL;

#endif
