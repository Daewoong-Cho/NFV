#ifndef _KOSCOM_FO_H_
#define	_KOSCOM_FO_H_
/*--------------------------------------------------------------------------
 * KOSCOM DATA Structure
 * Name : Koscom_fo.h
 * Date : 
 * By	: David Cho
 *-------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------                
 * 옵션종목정보 데이터      
 * data 구분    : A0        
 * 정보구분 : 03:KOSPI200지수옵션       
 * 시장구분 : 4:지수파생        
 *-------------------------------------------------------------------------*/
typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분  - A0                                                */
    char s_info_cls_code               [  2];       /* 정보 구분    - 03:KOSPI200지수옵션                               */
    char s_mrkt_cls_code               [  1];       /* 시장 구분    - 4:지수파생                                        */
    char s_issu_cnt                    [  5];       /* 종목수                                                           */
    char s_bsop_date                   [  8];       /* 영업일자(입회일자)                                               */
    char s_stnd_iscd                   [ 12];       /* 종목코드                                                         */
    char s_issu_srno                   [  6];       /* 종목SEQ                                                          */
    char s_prod_cls_code               [ 10];       /* 파생품목ID(상품구분코드) - 예) KRIDXFUK2I                        */
    char s_shrn_iscd                   [  9];       /* 종목단축코드-6차                                                 */
    char s_kor_isnm                    [ 80];       /* 종목한글명                                                       */
    char s_kor_shrn_isnm               [ 40];       /* 종목한글약명                                                     */
    char s_eng_isnm                    [ 80];       /* 종목영문명                                                       */
    char s_eng_shrn_isnm               [ 40];       /* 종목영문약명                                                     */
    char s_lstn_date                   [  8];       /* 상장일자                                                         */
    char s_lstn_abrg_date              [  8];       /* 상장폐지일자                                                     */
    char s_spead_stnd_issu_cls_code    [  1];       /* 스프레드기준종목구분코드 - F:원월종목, N:근월종목                */
    char s_last_stlm_mthd_code         [  1];       /* 최종결제방법코드                                                 */
    char s_sign1                       [  1];       /* SIGN부호                                                         */
    char s_optn_mxpr                   [ 12];       /* 상한가-6차                                                       */
    char s_sign2                       [  1];       /* SIGN부호                                                         */
    char s_optn_llam                   [ 12];       /* 하한가-6차                                                       */
    char s_optn_sdpr                   [ 12];       /* 기준가-6차                                                       */
    char s_unas_cls_code               [  3];       /* 기초자산ID                                                       */
    char s_rght_evnt_type_code         [  1];       /* 권리행사유형코드 - A:미국형,E:유럽형,Z:해당없음                  */
    char s_spead_type_code             [  2];       /* 스프레드유형코드 - T0:해당없음       T1:최근월+차근월            */
                                                    /*                    t2:최근월+2차근월 T3:최근월+3차근월           */
                                                    /*                    t4:최근월+4차근월 T5:최근월+5차근월           */
                                                    /*                    t6:최근월+6차근월                             */

    char s_spead_nmsc_iscd             [ 12];       /* 스프레드근월물종목코드                                           */
    char s_spead_fmsc_iscd             [ 12];       /* 스프레드원월물종목코드                                           */
    char s_last_tr_date                [  8];       /* 최종거래일자                                                     */
    char s_last_stlm_date              [  8];       /* 최종결제일자                                                     */
    char s_mmsc_cls_code               [  1];       /* 월물구분코드 1:최근월물, n:n번째도래근월물                       */
    char s_mtrt_date                   [  8];       /* 만기일자                                                         */
    char s_optn_acpr                   [ 17];       /* 행사가격-6차                                                     */
    char s_adjs_cls_code               [  1];       /* 조정구분코드                                                     */
    char s_optn_tr_unit                [ 17];       /* 거래단위-6차 - 1계약에 해당하는 기초자산수량                     */
                                                    /* (3년국채선물:1억원, 달러선물:5만달러)                            */
    char s_tr_mltl                     [ 21];       /* 거래승수-6차 - 약정대금 및 결제시 사용하는 계산승수              */
                                                    /* (KOSPI200선물:50만, KOSPI200옵션:10만,                           */
                                                    /* 국채선물:100만, CD선물:125만)                                    */
    char s_mrkt_prmg_cls_code          [  1];       /* 시장조성구분코드 - 0:미시장조성종목                              */
                                                    /* 1:당일시장조성종목                                               */
                                                    /* 2:과거시장조성종목                                               */
    char s_lstn_type_code              [  1];       /* 상장유형코드 -   1:신규상장                                      */
                                                    /*                  2:추가상장                                      */
                                                    /*                  3:기존종목                                      */
                                                    /*                  4:최초상장                                      */
                                                    /*                  5:종목조정                                      */
                                                    /*                  6:특별설정                                      */
    char s_atm_prc                     [ 12];       /* 등가격 9(10)V9(2) -6차                                           */
    char s_adjs_reas_code              [  2];       /* 조정사유코드 -   00:해당사항없음, 01:권리락, 02:배당락,          */
                                                    /*                  03:분배락, 04:권배락 05:중간배당락,             */
                                                    /*                  06:권리중간배당락, 99:기타                      */
    char s_unas_stnd_iscd              [ 12];       /* 기초자산종목코드 (5차추가)                                       */
    char s_unas_clpr                   [ 12];       /* 기초자산종가 9(10)V9(2) -6차                                     */
    char s_rmnn_dynu                   [  7];       /* 잔존일수                                                         */
    char s_adjs_sdpr                   [ 17];       /* 조정기준가격 9(10)V9(2) -6차 -                                   */
                                                    /* 주식파생상품의 기초주권 조정기준가격                             */
    char s_stnd_prc_cls_code           [  2];       /* 기준가격구분코드-11:전일정산가                                   */
                                                    /* 12:전일기준가(거래성립전 종가미형성)                             */
                                                    /* 13:당일이론가(거래성립전 종가미형성)                             */
                                                    /* 14:전일기세(거래성립전 기세형성)                                 */
                                                    /* 15:당일이론가(거래성립전 기세형성)                               */
                                                    /* 16:조정된 전일정산가                                             */
                                                    /* 17:조정된 전일기준가(거래성립전 종가미형성)                      */
                                                    /* 18:조정된 전일기세(거래성립전 기세형성)                          */
                                                    /* 19:전일 대상자산 종가(이론가없는 상품)                           */
                                                    /* 21:전일증거금기준가                                              */
                                                    /* 22:전일기준가(거래성립전 종가미형성)                             */
                                                    /* 23:당일이론가(거래성립전 종가미형성)                             */
                                                    /* 24:전일기세(거래성립전 기세                                      */
    char s_deal_stnd_prc_cls_code      [  1];       /* 매매용기준가격구분코드- 0:해당없음                               */
                                                    /* 1:실세                                                           */
                                                    /* 2:기세                                                           */
                                                    /* 3:이론가                                                         */
                                                    /* 4:대상자산종가                                                   */
    char s_sign3                       [  1];       /* SIGN부호                                                         */
    char s_prdy_adjs_clpr              [ 17];       /* 전일조정종가 9(9)V9(8) -6차                                      */
    char s_dscs_bltr_trgt_yn           [  1];       /* 협의대량매매대상여부 - Y:협의매매상품, N:대상아님                */
                                                    /* 가능품목:3년물국채선물, 미국달러선물,                            */
                                                    /* 유로선물, 엔선물                                                 */
    char s_prdy_marg_sdpr              [ 17];       /* 전일증거금기준가격-6차                                           */
    char s_prdy_marg_sdpr_cls_code     [  2];       /* 전일증거금기준가격구분코드-6차                                   */
                                                    /* 20:증거금 기준가 없음                                            */
                                                    /* 21:당일종가(실세)                                                */
                                                    /* 22:당일기세(거래성립후기세)                                      */
                                                    /* 23:전일증거금기준가(거래성립후 종가미 형성)                      */
                                                    /* 24:당일이론가(거래성립후 종가미형성)                             */
                                                    /* 25:조정전일증거금기준가(거래성립후종가미형성)                    */
    char s_optn_thpr                   [ 15];       /* 정산이론가격                                                     */
    char s_optn_stnd_thpr              [ 15];       /* 기준이론가격-6차 추가 9(9)V(6)                                   */
    char s_optn_prdy_excl_prc          [ 17];       /* 전일정산가격 9(9)V9(8)-6차                                       */
    char s_trht_yn                     [  1];       /* 거래정지여부 - Y, N                                              */
    char s_crbr_mxpr                   [ 12];       /* Circuit_Breakers상한가 9(10)V9(2) -6차                           */
    char s_crbr_llam                   [ 12];       /* Circuit_Breakers하한가 9(10)V9(2)-6차                            */
    char s_usiq_acpr                   [ 17];       /* 조회용행사가격 9(9)V9(8) -6차                                    */
    char s_atm_cls_code                [  1];       /* ATM구분코드 - 0:선물, 1:ATM, 2:ITM, 3:OTM                        */
    char s_last_tr_day_yn              [  1];       /* 최종거래일여부                                                   */
    char s_dmix_fv_val                 [ 15];       /* 배당가치 9(9)V9(6) -6차 - 주식 및 주가지수 상품에만 적용됨       */
                                                    /* - 선물 : 배당 미래가치                                           */
                                                    /* - 옵션 : 배당 현재가치                                           */
    char s_sign4                       [  1];       /* SIGN부호                                                         */
    char s_optn_prdy_clpr              [ 12];       /* 전일종가 9(10)V9(2) -6차                                         */
    char s_prdy_clpr_cls_code          [  1];       /* 전일종가구분코드 - 1:실세, 2:기세, 3:거래무                      */
    char s_sign5                       [  1];       /* SIGN부호                                                         */
    char s_optn_prdy_oprc              [ 12];       /* 전일시가 9(10)V9(2) -6차                                         */
    char s_sign6                       [  1];       /* SIGN부호                                                         */
    char s_optn_prdy_hgpr              [ 12];       /* 전일고가 9(10)V9(2) -6차                                         */
    char s_sign7                       [  1];       /* SIGN부호                                                         */
    char s_optn_prdy_lwpr              [ 12];       /* 전일저가 9(10)V9(2) -6차                                         */
    char s_frst_cntg_date              [  8];       /* 최초체결일자                                                     */
    char s_prdy_last_cntg_hour         [  8];       /* 전일최종체결시각                                                 */
    char s_prdy_excl_prc               [  2];       /* 전일정산가격구분코드-6차                                         */
                                                    /* 10:정산가없음                                                    */
                                                    /* 11:당일종가(실세)                                                */
                                                    /* 12:당일기세(거래성립후기세)                                      */
                                                    /* 13:전일정산가(거래성립후 종가미형성)                             */
                                                    /* 14:당일이론가(거래성립후 종가미형성)                             */
                                                    /* 15:스프레드분 종가                                               */
                                                    /* 16:조정된 전일 정산가                                            */
                                                    /* 17:대상자산 종가(이론가없는 상품)                                */
    char s_sign14                      [  1];       /* SIGN부호-6차                                                     */
    char s_excl_prc_thpr_dprt          [ 12];       /* 정산가격이론가격괴리율 9(6)V9(6) -9차                            */
    char s_prdy_otst_stpl_qty          [ 10];       /* 전일미결제약정수량-6차                                           */
    char s_sign8                       [  1];       /* SIGN부호                                                         */
    char s_prdy_askp_prc               [ 12];       /* 전일매도우선호가가격-6차                                         */
    char s_sign9                       [  1];       /* SIGN부호                                                         */
    char s_prdy_bidp_prc               [ 12];       /* 전일매수우선호가가격 9(10)V9(2) -6차                             */
    char s_iv                          [ 10];       /* 내재변동성-9차(X(5)->9(6)V9(4)                                   */
    char s_unas_max_flxb_type_code     [  1];       /* 기초자산최대변동폭유형코드 - 1:%, 2:절대값                       */
    char s_unas_max_flxb               [  6];       /* 기초자산최대변동폭 9(4)V9(2) -6차                                */
    char s_sign10                      [  1];       /* SIGN부호                                                         */
    char s_lstn_hgpr                   [ 12];       /* 상장중최고가 9(10)V9(2) -6차                                     */
    char s_sign11                      [  1];       /* SIGN부호                                                         */
    char s_lstn_lwpr                   [ 12];       /* 상장중최저가 9(10)V9(2) -6차                                     */
    char s_sign12                      [  1];       /* SIGN부호                                                         */
    char s_dryy_hgpr                   [ 12];       /* 연중최고가 9(10)V9(2) -6차                                       */
    char s_sign13                      [  1];       /* SIGN부호                                                         */
    char s_dryy_lwpr                   [ 12];       /* 연중최저가 9(10)V9(2) -6차                                       */
    char s_lstn_hgpr_date              [  8];       /* 상장중최고가일자                                                 */
    char s_lstn_lwpr_date              [  8];       /* 상장중최저가일자                                                 */
    char s_dryy_hgpr_date              [  8];       /* 연중최고가일자                                                   */
    char s_dryy_lwpr_date              [  8];       /* 연중최저가일자                                                   */
    char s_anul_stnd_dynu              [  8];       /* 연간기준일수                                                     */
    char s_mntl_tr_dynu                [  8];       /* 월간거래일수                                                     */
    char s_anul_tr_dynu                [  8];       /* 연간거래일수                                                     */
    char s_prdy_cntg_csnu              [ 16];       /* 전일체결건수                                                     */
    char s_prdy_cntg_qty               [ 12];       /* 전일체결수량                                                     */
    char s_prdy_tr_pbmn                [ 22];       /* 전일거래대금 - 단위:원                                           */
    char s_prdy_dscs_bltr_cntg_qty     [ 12];       /* 전일협의대량매매체결수량-6차                                     */
    char s_prdy_dscs_bltr_cntg_pbmn    [ 22];       /* 전일협의대량매매거래대금 - 단위:원                               */
    char s_cd_mnrt                     [  6];       /* CD금리 9(3)V9(3)                                                 */
    char s_otst_limt_cnrc_qty          [  8];       /* 미결제한도계약수-7차 추가                                        */
    char s_blng_prgp_code              [  4];       /* 소속상품군-7차 추가                                              */
    char s_prgp_ofst_rate              [  5];       /* 상품군 옵셋율9(3)V9(2)-7차 추가                                  */
    /*  6차 삭제,8차추가    */
    char s_lmts_aspr_cond_cls_code     [  1];       /* 지정가호가조건구분코드 - 0:불가, 1:가능(FAS,FOK,FAK가능),        */
    char s_mrpr_aspr_cond_cls_code     [  1];       /* 시장가호가조건구분코드 - 2:가능(FAS만가능)                       */
    char s_cndn_lmts_aspr_cls_code     [  1];       /* 조건부지정가호가조건구분코드                                     */
    char s_pmpr_lmts_aspr_cls_code     [  1];       /* 최유리지정가호가조건구분코드                                     */

    /* EFP/FLEX 추가 20090827 CYTECA */
    char s_efp_trgt_yn                 [  1];       /* EFP  거래대상 여부 - Y/N                                         */
    char s_flex_trgt_yn                [  1];       /* FLEX 거래대상 여부 - Y/N                                         */
    char s_efp_prdy_cntg_qty           [ 12];       /* EFP  전일체결수량                                                */
    char s_efp_prdy_tr_pbmn            [ 22];       /* EFP  전일거래대                                                  */
    char s_close_yn                    [  1];       /* 휴장 여부 - Y/N                                                  */
    char s_filler                      [133];       /* 134 -> 133                                                       */
} RCV_STK_A0_03_4 ;

/*--------------------------------------------------------------------------
 * 옵션 우선호가            
 * data 구분    : B6                                    
 * 정보구분 : 03:KOSPI200지수옵션                       
 * 시장구분 : 4:지수파생                                                    
 *-------------------------------------------------------------------------*/
typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분  - B6                                                */
    char s_info_cls_code               [  2];       /* 정보 구분    - 03:KOSPI200지수옵션                               */
    char s_mrkt_cls_code               [  1];       /* 시장 구분    - 4:지수파생                                        */
    char s_stnd_iscd                   [ 12];       /* 종목코드                                                         */
    char s_issu_srno                   [  3];       /* 종목SEQ                                                          */
    char s_mrkt_stat_cls_code          [  2];       /* 장상태구분코드 - *호가가 처리된 장상태                           */
                                                    /* 00 : 초기(장개시전)                                              */
                                                    /* 10 : 시가단일가                                                  */
                                                    /* 11 : 시가단일가연장                                              */
                                                    /* 20 : 장중단일가                                                  */
                                                    /* 21 : 장중단일가연장                                              */
                                                    /* 30 : 종가단일가                                                  */
                                                    /* 40 : 접속                                                        */
                                                    /* 99 : 장종료                                                      */
    char s_total_bidp_rsqn             [  7];       /* 매수총호가잔량                                                   */
    char s_optn_bidp1                  [  5];       /* 매수1단계우선호가가격                                            */
    char s_bidp_rsqn1                  [  7];       /* 매수1단계우선호가잔량                                            */
    char s_optn_bidp2                  [  5];       /* 매수2단계우선호가가격                                            */
    char s_bidp_rsqn2                  [  7];       /* 매수2단계우선호가잔량                                            */
    char s_optn_bidp3                  [  5];       /* 매수3단계우선호가가격                                            */
    char s_bidp_rsqn3                  [  7];       /* 매수3단계우선호가잔량                                            */
    char s_optn_bidp4                  [  5];       /* 매수4단계우선호가가격                                            */
    char s_bidp_rsqn4                  [  7];       /* 매수4단계우선호가잔량                                            */
    char s_optn_bidp5                  [  5];       /* 매수5단계우선호가가격                                            */
    char s_bidp_rsqn5                  [  7];       /* 매수5단계우선호가잔량                                            */
    char s_total_askp_rsqn             [  7];       /* 매도총호가잔량                                                   */
    char s_optn_askp1                  [  5];       /* 매도1단계우선호가가격                                            */
    char s_askp_rsqn1                  [  7];       /* 매도1단계우선호가잔량                                            */
    char s_optn_askp2                  [  5];       /* 매도2단계우선호가가격                                            */
    char s_askp_rsqn2                  [  7];       /* 매도2단계우선호가잔량                                            */
    char s_optn_askp3                  [  5];       /* 매도3단계우선호가가격                                            */
    char s_askp_rsqn3                  [  7];       /* 매도3단계우선호가잔량                                            */
    char s_optn_askp4                  [  5];       /* 매도4단계우선호가가격                                            */
    char s_askp_rsqn4                  [  7];       /* 매도4단계우선호가잔량                                            */
    char s_optn_askp5                  [  5];       /* 매도5단계우선호가가격                                            */
    char s_askp_rsqn5                  [  7];       /* 매도5단계우선호가잔량                                            */
    char s_total_bidp_csnu             [  5];       /* 매수총호가건수                                                   */
    char s_bidp_csnu1                  [  4];       /* 매수1단계우선호가건수                                            */
    char s_bidp_csnu2                  [  4];       /* 매수2단계우선호가건수                                            */
    char s_bidp_csnu3                  [  4];       /* 매수3단계우선호가건수                                            */
    char s_bidp_csnu4                  [  4];       /* 매수4단계우선호가건수                                            */
    char s_bidp_csnu5                  [  4];       /* 매수5단계우선호가건수                                            */
    char s_total_askp_csnu             [  5];       /* 매도총호가건수                                                   */
    char s_askp_csnu1                  [  4];       /* 매도1단계우선호가건수                                            */
    char s_askp_csnu2                  [  4];       /* 매도2단계우선호가건수                                            */
    char s_askp_csnu3                  [  4];       /* 매도3단계우선호가건수                                            */
    char s_askp_csnu4                  [  4];       /* 매도4단계우선호가건수                                            */
    char s_askp_csnu5                  [  4];       /* 매도5단계우선호가건수                                            */
    char s_aspr_acpt_hour              [  8];       /* 호가접수시간                                                     */
    char s_antc_cnpr                   [  5];       /* 예상체결가격                                                     */
                                                    /* 단일가매매시만 제공                                              */
                                                    /* (장상태구분코드:10,20,30,80)                                     */
} RCV_STK_B6_03_4 ;


/*--------------------------------------------------------------------------                            
 * 옵션 체결                                                            
 * data 구분    : A3            
 * 정보구분 : 03:KOSPI200지수옵션                                               
 * 시장구분 : 4:지수파생                                                    
 *-------------------------------------------------------------------------*/
typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분  - A3                                                */
    char s_info_cls_code               [  2];       /* 정보 구분    - 03:KOSPI200지수옵션                               */
    char s_mrkt_cls_code               [  1];       /* 시장 구분    - 4:지수파생                                        */
    char s_stnd_iscd                   [ 12];       /* 종목코드                                                         */
    char s_issu_srno                   [  3];       /* 종목SEQ                                                          */
    char s_optn_prpr                   [  5];       /* 현재가격                                                         */
    char s_cnqn                        [  7];       /* 체결수량                                                         */
    char s_cntg_type_code              [  2];       /* 체결유형코드 - 1)일반매매                                        */
                                                    /* 10 : 시가단일가                                                  */
                                                    /* 11 : 시가단일가연장                                              */
                                                    /* 20 : 장중단일가                                                  */
                                                    /* 21 : 장중단일가연장                                              */
                                                    /* 30 : 종가단일가                                                  */
                                                    /* 40 : 접속                                                        */
    char s_cntg_hour                   [  8];       /* 체결시각                                                         */
    char s_optn_oprc                   [  5];       /* 시가                                                             */
    char s_optn_hgpr                   [  5];       /* 고가                                                             */
    char s_optn_lwpr                   [  5];       /* 저가                                                             */
    char s_rgbf_prc                    [  5];       /* 직전가격                                                         */
    char s_acml_cntg_qty               [  8];       /* 누적체결수량                                                     */
    char s_acml_tr_pbmn                [ 11];       /* 누적거래대금 - 단위:천원                                         */
} RCV_STK_A3_03_4 ;

/*--------------------------------------------------------------------------
 * 옵션 체결+우선호가       
 * data 구분    : G7                        
 * 정보구분 : 03:KOSPI200지수옵션           
 * 시장구분 : 4:지수파생                                                    
 *-------------------------------------------------------------------------*/
    typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분  - G7                                                */
    char s_info_cls_code               [  2];       /* 정보 구분    - 03:KOSPI200지수옵션                               */
    char s_mrkt_cls_code               [  1];       /* 시장 구분    - 4:지수파생                                        */
    char s_stnd_iscd                   [ 12];       /* 종목코드                                                         */
    char s_issu_srno                   [  3];       /* 종목SEQ                                                          */
    char s_optn_prpr                   [  5];       /* 현재가격                                                         */
    char s_cnqn                        [  7];       /* 체결수량                                                         */
    char s_cntg_type_code              [  2];       /* 체결유형코드 - 1)일반매매                                        */
                                                    /* 10 : 시가단일가                                                  */
                                                    /* 11 : 시가단일가연장                                              */
                                                    /* 20 : 장중단일가                                                  */
                                                    /* 21 : 장중단일가연장                                              */
                                                    /* 30 : 종가단일가                                                  */
                                                    /* 40 : 접속                                                        */
    char s_cntg_hour                   [  8];       /* 체결시각                                                         */
    char s_optn_oprc                   [  5];       /* 시가                                                             */
    char s_optn_hgpr                   [  5];       /* 고가                                                             */
    char s_optn_lwpr                   [  5];       /* 저가                                                             */
    char s_rgbf_prc                    [  5];       /* 직전가격                                                         */
    char s_acml_cntg_qty               [  8];       /* 누적체결수량                                                     */
    char s_acml_tr_pbmn                [ 11];       /* 누적거래대금 - 단위:천원                                         */
    char s_mrkt_stat_cls_code          [  2];       /* 장상태구분코드 - *호가가 처리된 장상태                           */
                                                    /* 00 : 초기(장개시전)                                              */
                                                    /* 01 : 시가단일가                                                  */
                                                    /* 11 : 시가단일가연장                                              */
                                                    /* 20 : 장중단일가                                                  */
                                                    /* 21 : 장중단일가연장                                              */
                                                    /* 30 : 종가단일가                                                  */
                                                    /* 40 : 접속                                                        */
    char s_total_bidp_rsqn             [  7];       /* 매수총호가잔량                                                   */
    char s_optn_bidp1                  [  5];       /* 매수1단계우선호가가격                                            */
    char s_bidp_rsqn1                  [  7];       /* 매수1단계우선호가잔량                                            */
    char s_optn_bidp2                  [  5];       /* 매수2단계우선호가가격                                            */
    char s_bidp_rsqn2                  [  7];       /* 매수2단계우선호가잔량                                            */
    char s_optn_bidp3                  [  5];       /* 매수3단계우선호가가격                                            */
    char s_bidp_rsqn3                  [  7];       /* 매수3단계우선호가잔량                                            */
    char s_optn_bidp4                  [  5];       /* 매수4단계우선호가가격                                            */
    char s_bidp_rsqn4                  [  7];       /* 매수4단계우선호가잔량                                            */
    char s_optn_bidp5                  [  5];       /* 매수5단계우선호가가격                                            */
    char s_bidp_rsqn5                  [  7];       /* 매수5단계우선호가잔량                                            */
    char s_total_askp_rsqn             [  7];       /* 매도총호가잔량                                                   */
    char s_optn_askp1                  [  5];       /* 매도1단계우선호가가격                                            */
    char s_askp_rsqn1                  [  7];       /* 매도1단계우선호가잔량                                            */
    char s_optn_askp2                  [  5];       /* 매도2단계우선호가가격                                            */
    char s_askp_rsqn2                  [  7];       /* 매도2단계우선호가잔량                                            */
    char s_optn_askp3                  [  5];       /* 매도3단계우선호가가격                                            */
    char s_askp_rsqn3                  [  7];       /* 매도3단계우선호가잔량                                            */
    char s_optn_askp4                  [  5];       /* 매도4단계우선호가가격                                            */
    char s_askp_rsqn4                  [  7];       /* 매도4단계우선호가잔량                                            */
    char s_optn_askp5                  [  5];       /* 매도5단계우선호가가격                                            */
    char s_askp_rsqn5                  [  7];       /* 매도5단계우선호가잔량                                            */
    char s_total_bidp_csnu             [  5];       /* 매수총호가건수                                                   */
    char s_bidp_csnu1                  [  4];       /* 매수1단계우선호가건수                                            */
    char s_bidp_csnu2                  [  4];       /* 매수2단계우선호가건수                                            */
    char s_bidp_csnu3                  [  4];       /* 매수3단계우선호가건수                                            */
    char s_bidp_csnu4                  [  4];       /* 매수4단계우선호가건수                                            */
    char s_bidp_csnu5                  [  4];       /* 매수5단계우선호가건수                                            */
    char s_total_askp_csnu             [  5];       /* 매도총호가건수                                                   */
    char s_askp_csnu1                  [  4];       /* 매도1단계우선호가건수                                            */
    char s_askp_csnu2                  [  4];       /* 매도2단계우선호가건수                                            */
    char s_askp_csnu3                  [  4];       /* 매도3단계우선호가건수                                            */
    char s_askp_csnu4                  [  4];       /* 매도4단계우선호가건수                                            */
    char s_askp_csnu5                  [  4];       /* 매도5단계우선호가건수                                            */
} RCV_STK_G7_03_4 ;

/*--------------------------------------------------------------------------        
 * 옵션 종목마감                                                        
 * data 구분    : A6                
 * 정보구분 : 03:KOSPI200지수옵션   
 * 시장구분 : 4:지수파생                                                    
 *-------------------------------------------------------------------------*/
    typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분  - A6                                                */
    char s_info_cls_code               [  2];       /* 정보 구분    - 03:KOSPI200지수옵션                               */
    char s_mrkt_cls_code               [  1];       /* 시장 구분    - 4:지수파생                                        */
    char s_stnd_iscd                   [ 12];       /* 종목코드                                                         */
    char s_issu_srno                   [  3];       /* 종목SEQ                                                          */
    char s_optn_clpr                   [  5];       /* 종가                                                             */
    char s_clpr_cls_code               [  1];       /* 종가구분코드 - 1:체결가격,                                       */
                                                    /*              - 2:기세,                                           */
                                                    /*              - 3:거래무-6차                                      */
    char s_acml_cntg_qty               [  8];       /* 누적체결수량-7차 추가                                            */
    char s_acml_tr_pbmn                [ 11];       /* 누적거래대금-7차 추가                                            */
    char s_total_bidp_rsqn             [  7];       /* 매수총호가잔량                                                   */
    char s_optn_bidp1                  [  5];       /* 매수1단계우선호가가격                                            */
    char s_bidp_rsqn1                  [  7];       /* 매수1단계우선호가잔량                                            */
    char s_optn_bidp2                  [  5];       /* 매수2단계우선호가가격                                            */
    char s_bidp_rsqn2                  [  7];       /* 매수2단계우선호가잔량                                            */
    char s_optn_bidp3                  [  5];       /* 매수3단계우선호가가격                                            */
    char s_bidp_rsqn3                  [  7];       /* 매수3단계우선호가잔량                                            */
    char s_optn_bidp4                  [  5];       /* 매수4단계우선호가가격                                            */
    char s_bidp_rsqn4                  [  7];       /* 매수4단계우선호가잔량                                            */
    char s_optn_bidp5                  [  5];       /* 매수5단계우선호가가격                                            */
    char s_bidp_rsqn5                  [  7];       /* 매수5단계우선호가잔량                                            */
    char s_total_askp_rsqn             [  7];       /* 매도총호가잔량                                                   */
    char s_optn_askp1                  [  5];       /* 매도1단계우선호가가격                                            */
    char s_askp_rsqn1                  [  7];       /* 매도1단계우선호가잔량                                            */
    char s_optn_askp2                  [  5];       /* 매도2단계우선호가가격                                            */
    char s_askp_rsqn2                  [  7];       /* 매도2단계우선호가잔량                                            */
    char s_optn_askp3                  [  5];       /* 매도3단계우선호가가격                                            */
    char s_askp_rsqn3                  [  7];       /* 매도3단계우선호가잔량                                            */
    char s_optn_askp4                  [  5];       /* 매도4단계우선호가가격                                            */
    char s_askp_rsqn4                  [  7];       /* 매도4단계우선호가잔량                                            */
    char s_optn_askp5                  [  5];       /* 매도5단계우선호가가격                                            */
    char s_askp_rsqn5                  [  7];       /* 매도5단계우선호가잔량                                            */
    char s_total_bidp_csnu             [  5];       /* 매수총호가건수                                                   */
    char s_bidp_csnu1                  [  4];       /* 매수1단계우선호가건수                                            */
    char s_bidp_csnu2                  [  4];       /* 매수2단계우선호가건수                                            */
    char s_bidp_csnu3                  [  4];       /* 매수3단계우선호가건수                                            */
    char s_bidp_csnu4                  [  4];       /* 매수4단계우선호가건수                                            */
    char s_bidp_csnu5                  [  4];       /* 매수5단계우선호가건수                                            */
    char s_total_askp_csnu             [  5];       /* 매도총호가건수                                                   */
    char s_askp_csnu1                  [  4];       /* 매도1단계우선호가건수                                            */
    char s_askp_csnu2                  [  4];       /* 매도2단계우선호가건수                                            */
    char s_askp_csnu3                  [  4];       /* 매도3단계우선호가건수                                            */
    char s_askp_csnu4                  [  4];       /* 매도4단계우선호가건수                                            */
    char s_askp_csnu5                  [  4];       /* 매도5단계우선호가건수                                            */

} RCV_STK_A6_03_4 ;

/*--------------------------------------------------------------------------                
 * 옵션 장운영
 * data 구분    : A7            
 * 정보구분 : 03:KOSPI200지수옵션
 * 시장구분 : 4:지수파생                                                    
 *-------------------------------------------------------------------------*/
typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분  - A7                                                */
    char s_info_cls_code               [  2];       /* 정보 구분    - 03:KOSPI200지수옵션                               */
    char s_mrkt_cls_code               [  1];       /* 시장 구분    - 4:지수파생                                        */
    char s_mkop_trtm_hour              [  8];       /* 장운영조치시각                                                   */
    char s_mkop_cls_code               [  3];       /* 장운영구분코드                                                   */
    char s_prod_cls_code               [ 10];       /* 상품ID                                                           */
    char s_stnd_iscd                   [ 12];       /* 종목코드                                                         */
    char s_issu_srno                   [  3];       /* 종목 SEQ                                                         */
    char s_mrkt_stat_cls_code          [  2];       /* 장상태구분코드                                                   */
    char s_aspr_en                     [  1];       /* 호가유무 0:호가없음,1:있음                                       */
    char s_total_bidp_rsqn             [  7];       /* 매수총호가잔량                                                   */
    char s_optn_bidp1                  [  5];       /* 매수1단계우선호가가격                                            */
    char s_bidp_rsqn1                  [  7];       /* 매수1단계우선호가잔량                                            */
    char s_optn_bidp2                  [  5];       /* 매수2단계우선호가가격                                            */
    char s_bidp_rsqn2                  [  7];       /* 매수2단계우선호가잔량                                            */
    char s_optn_bidp3                  [  5];       /* 매수3단계우선호가가격                                            */
    char s_bidp_rsqn3                  [  7];       /* 매수3단계우선호가잔량                                            */
    char s_optn_bidp4                  [  5];       /* 매수4단계우선호가가격                                            */
    char s_bidp_rsqn4                  [  7];       /* 매수4단계우선호가잔량                                            */
    char s_optn_bidp5                  [  5];       /* 매수5단계우선호가가격                                            */
    char s_bidp_rsqn5                  [  7];       /* 매수5단계우선호가잔량                                            */
    char s_total_askp_rsqn             [  7];       /* 매도총호가잔량                                                   */
    char s_optn_askp1                  [  5];       /* 매도1단계우선호가가격                                            */
    char s_askp_rsqn1                  [  7];       /* 매도1단계우선호가잔량                                            */
    char s_optn_askp2                  [  5];       /* 매도2단계우선호가가격                                            */
    char s_askp_rsqn2                  [  7];       /* 매도2단계우선호가잔량                                            */
    char s_optn_askp3                  [  5];       /* 매도3단계우선호가가격                                            */
    char s_askp_rsqn3                  [  7];       /* 매도3단계우선호가잔량                                            */
    char s_optn_askp4                  [  5];       /* 매도4단계우선호가가격                                            */
    char s_askp_rsqn4                  [  7];       /* 매도4단계우선호가잔량                                            */
    char s_optn_askp5                  [  5];       /* 매도5단계우선호가가격                                            */
    char s_askp_rsqn5                  [  7];       /* 매도5단계우선호가잔량                                            */
    char s_total_bidp_csnu             [  5];       /* 매수총호가건수                                                   */
    char s_bidp_csnu1                  [  4];       /* 매수1단계우선호가건수                                            */
    char s_bidp_csnu2                  [  4];       /* 매수2단계우선호가건수                                            */
    char s_bidp_csnu3                  [  4];       /* 매수3단계우선호가건수                                            */
    char s_bidp_csnu4                  [  4];       /* 매수4단계우선호가건수                                            */
    char s_bidp_csnu5                  [  4];       /* 매수5단계우선호가건수                                            */
    char s_total_askp_csnu             [  5];       /* 매도총호가건수                                                   */
    char s_askp_csnu1                  [  4];       /* 매도1단계우선호가건수                                            */
    char s_askp_csnu2                  [  4];       /* 매도2단계우선호가건수                                            */
    char s_askp_csnu3                  [  4];       /* 매도3단계우선호가건수                                            */
    char s_askp_csnu4                  [  4];       /* 매도4단계우선호가건수                                            */
    char s_askp_csnu5                  [  4];       /* 매도5단계우선호가건수                                            */
} RCV_STK_A7_03_4 ;

/*--------------------------------------------------------------------------
 * 옵션 공개장운영
 * data 구분    : M4
 * 정보구분 : 03:KOSPI200옵션
 * 시장구분 : 4:지수파생
 *-------------------------------------------------------------------------*/
typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분 - M4                                                 */
    char s_info_cls_code               [  2];       /* 정보 구분 - 03:KOSPI200지수옵션                                  */
    char s_mrkt_cls_code               [  1];       /* 시장 구분   - 4:지수파생                                         */
    char s_mkop_trtm_hour              [  8];       /* 장운영조치시각                                                   */
    char s_mkop_cls_code               [  3];       /* 장운영구분코드                                                   */
    char s_prod_cls_code               [ 10];       /* 상품ID                                                           */
    char s_stnd_iscd                   [ 12];       /* 종목코드                                                         */
    char s_issu_srno                   [  3];       /* 종목SEQ                                                          */
    char s_mrkt_stat_cls_code          [  2];       /* 장상태구분코드 - *호가가 처리된 장상태                           */
                                                    /* 00 : 초기(장개시전)                                              */
                                                    /* 10 : 시가단일가                                                  */
                                                    /* 11 : 시가단일가연장                                              */
                                                    /* 20 : 장중단일가                                                  */
                                                    /* 21 : 장중단일가연장                                              */
                                                    /* 30 : 종가단일가                                                  */
                                                    /* 40 : 접속                                                        */
                                                    /* 80 : 단위매매체결                                                */
                                                    /* 90 : 거래정지                                                    */
                                                    /* 99 : 장종료                                                      */
} RCV_STK_M4_03_4 ;

/*--------------------------------------------------------------------------                            
 * 옵션 투자자 데이터
 * data 구분    : H1        
 * 정보구분 : 03:KOSPI200지수옵션       
 * 시장구분 : 4:지수파생    
 *-------------------------------------------------------------------------*/
typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분  - H1                                                */
    char s_info_cls_code               [  2];       /* 정보 구분    - 03:KOSPI200지수옵션                               */
    char s_mrkt_cls_code               [  1];       /* 시장 구분    - 4:지수파생                                        */
    char s_crtn_date                   [  8];       /* 생성일자                                                         */
    char s_crtn_hour                   [  6];       /* 생성시각                                                         */
    char s_stck_invr_cls_code          [  2];       /* 데이터구분                                                       */
    char s_prod_cls_code               [ 10];       /* 상품ID                                                           */
    char s_optn_cls_code               [  1];       /* 옵션구분                                                         */
    char s_invr_code                   [  4];       /* 투자자유형                                                       */
    char s_shnu_vol                    [  9];       /* 매수 약정수량                                                    */
    char s_seln_vol                    [  9];       /* 매도 약정수량                                                    */
    char s_shnu_tr_pbmn                [ 18];       /* 매수 약정대금                                                    */
    char s_seln_tr_pbmn                [ 18];       /* 매도 약정대금                                                    */
} RCV_STK_H1_03_4 ;


/*--------------------------------------------------------------------------                    
 * 옵션 미결제약정수량 데이터
 * data 구분    : H2                        
 * 정보구분 : 03:KOSPI200지수옵션                                           
 * 시장구분 : 4:지수파생                                                        
 *-------------------------------------------------------------------------*/
typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분  - H2                                                */
    char s_info_cls_code               [  2];       /* 정보 구분    - 03:KOSPI200지수옵션                               */
    char s_mrkt_cls_code               [  1];       /* 시장 구분    - 4:지수파생                                        */
    char s_stnd_iscd                   [ 12];       /* 종목코드                                                         */
    char s_issu_srno                   [  3];       /* 종목SEQ                                                          */
    char s_otst_stpl_cls_code          [  2];       /* 미결제약정구분                                                   */
    char s_tr_date                     [  8];       /* 거래일자                                                         */
    char s_otst_stpl_qty               [  9];       /* 미결제약정수량(단위:계약) - 단위:계약                            */
} RCV_STK_H2_03_4 ;

/*--------------------------------------------------------------------------    
 * 옵션 매매증거금기준가 데이터
 * data 구분    : H3                                            
 * 정보구분 : 03:KOSPI200지수옵션                                           
 * 시장구분 : 4:지수파생                                                    
 *-------------------------------------------------------------------------*/
typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분  - H3                                                */
    char s_info_cls_code               [  2];       /* 정보 구분    - 03:KOSPI200지수옵션                               */
    char s_mrkt_cls_code               [  1];       /* 시장 구분    - 4:지수파생                                        */
    char s_stnd_iscd                   [ 12];       /* 종목코드                                                         */
    char s_issu_srno                   [  3];       /* 종목SEQ                                                          */
    char s_deal_marg_stnd_prc          [ 16];       /* 매매증거금기준가.8                                               */
    char s_deal_marg_stnd_prc_cls      [  1];       /* 매매증거금기준가구분                                             */
    char s_optn_rght_dorm_stlm_prc     [ 16];       /* 옵션권리행사결제가격.8                                           */
    char s_optn_rght_dorm_stlm_prc_code[  1];       /* 옵션권리행사결제가격구분                                         */
} RCV_STK_H3_03_4 ;

/*--------------------------------------------------------------------------                        
 * 지수옵션 민감도 델타 
 * data 구분    : N7    
 * 정보구분 : 03:KOSPI200지수
 * 시장구분 : 4:지수파생
 *-------------------------------------------------------------------------*/
typedef struct {
    char s_data_cls_code               [  2];       /* 데이터 구분  - N7                                                */
    char s_info_cls_code               [  2];       /* 정보 구분    - 03:KOSPI200지수                                   */
    char s_mrkt_cls_code               [  1];       /* 시장 구분    - 4:지수파생                                        */
    char s_stnd_iscd                   [ 12];       /* 종목코드                                                         */
    char s_seqno                       [  7];       /* 종목SEQ                                                          */
    char s_bsop_date                   [  8];       /* 생성일자                                                         */
    char s_bsop_hour                   [  8];       /* 생성시간                                                         */
    char s_cofm_cls_code               [  1];       /* 확정여부                                                         */
                                                    /* 1:전일확정,2:장중산출,E:장중완료,3:당일확정                      */
    char s_unas_cls_code               [  3];       /* 기초자산ID                                                       */
                                                    /* K2I:KOSPI200                                                     */
    char s_sign                        [  1];       /* SIGN부호                                                         */
    char s_sense_delta                 [ 18];       /* 민감도델타 9(12)V9(6)                                            */

    char s_tsign                       [  1];       /* 민감도 쎄타 sign                                                 */
    char s_sense_theta                 [ 18];       /* 민감도 쎄타 9(12)V9(6)                                           */

    char s_vsign                       [  1];       /* 민감도 베가 sign                                                 */
    char s_sense_vega                  [ 18];       /* 민감도 베가 9(12)V9(6)                                           */

    char s_gsign                       [  1];       /* 민감도 감마 sign                                                 */
    char s_sense_gama                  [ 18];       /* 민감도 감마 9(12)V9(6)                                           */

    char s_rsign                       [  1];       /* 민감도 로 sign                                                   */
    char s_sense_rho                   [ 18];       /* 민감도 로 9(12)V9(6)                                             */

} RCV_STK_N7_03_4;

#endif
