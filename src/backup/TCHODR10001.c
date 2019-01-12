/*****************************************************************
 * 프로그램명   : TCHODR10001.c
 * 작  성  자   : David Cho
 * 기      능   : 호가 처리(TCHODR10001)
 * PROTOTYPE    :
 *****************************************************************/

#include	"common.h"
#include	"shm_def.h"
#include	"krx.h"

int         fep_hour;
int			fep_date;
extern		int	MSGSEQ;

#define		BODY_LEN	sizeof(TCHODR10001_BODY)

#define LOG_FILE  "/home/david/log/order_trans.log"

int proc_TCHODR10001(char *org_data)
{
	KRX_HEADER			st_header;
	TCHODR10001_BODY	st_order;


	fep_hour = __IntGetTime();
	fep_date = __GetDateInt();

	/* Header */
	memset(&st_header, 0x00, sizeof(st_header));
	Init(&st_header);

	/* Body */
	memset(&st_order, 0x00, sizeof(st_order));

	/* Message Sequence */
	__Long2Str(st_order.MsgSeq, ++MSGSEQ, sizeof(st_order.MsgSeq));

#if 0
	/* TR CODE */
	memcpy(st_order.TrCode, &tr_code, sizeof(st_order.TrCode));

	/* 정규 시간외 구분코드 */
	st_order.Regular_Off[0] =  session_type[0];

	/* 회원번호 */
	memcpy(st_order.MembershipNo, COMPANY_ID, sizeof(st_order.MembershipNo));

	/* 지점번호 */
	memcpy(st_order.BranchNo, BRANCH_ID, sizeof(st_order.BranchNo));

	/* 주문번호 */
	memcpy(st_order.OrderNo, order_id, sizeof(st_order.OrderNo));

	/* 원주문번호 */
	memcpy(st_order.OriginalOrderNo, org_order_id, sizeof(st_order.OriginalOrderNo));

	/* 종목코드 */
	memcpy(st_order.ItemCode, item_code, sizeof(st_order.ItemCode));

	/* 매도매수 구분코드 */
	st_order.TradeFlag[0] = trade_flag[0];

	/* 정정취소 구분코드 */
	st_order.New_Modify_Cancel_gbn[0] = mod_can_code[0];

	/* 계좌번호 */
	memcpy(st_order.AccountNo, ACNT_NO, sizeof(st_order.AccountNo));

	/* 호가수량 */
	memcpy(st_order.OrderQuantity, qty, sizeof(st_order.OrderQuantity));

	/* 호가가격 */
	memcpy(st_order.Price, price, sizeof(st_order.Price));

	/* 호가유형코드 */
	st_order.Order_Type[0] = order_type[0];

	/* 호가조건코드 */
	st_order.Order_Condition[0] = order_con[0]

	/* 시장 조성자 호가 구분번호 */
	memcpy(st_order.Mm_Order_Type_No, mm_type, sizeof(st_order.Mm_Order_Type_No));

	/* 자사주 신고서 ID */
	st_order.Treasury_Stock_Id[0] = '0';

	/* 자사주매매 방법코드 */
	st_order.Treasury_Stock_Method[0] = '0';

	/* 매도유형 코드 */
	memcpy(st_order.Ask_Type, ask_type, sizeof(st_order.Ask_Type));

	/* 신용구분 코드 */
	memcpy(st_order.Credit_Type, "10", sizeof(st_order.Credit_Type));

	/* 위탁 자기구분코드 - 비회원의 자기거래 */
	memcpy(st_order.Trust_Principal_Type, "32", sizeof(st_order.Trust_Principal_Type));

	/* 위탁사번호 */
	memcpy(st_order.Trust_Company_No, 0x00, sizeof(st_order.Trust_Company_No));

	/* PT 구분코드 */
	memcpy(st_order.Program_Trading_Type, PGM_TRD_TYPE, sizeof(st_order.Program_Trading_Type));

	/* 대용주권 계좌번호 */
	memset(st_order.Substitute_AccNo, 0x20, sizeof(st_order.Substitute_AccNo));

	/* 계좌 구분 코드 */
	memcpy(st_order.Account_Type, ACNT_TYPE, sizeof(st_order.Account_Type));

	/* 계좌 증거금 유형코드 */
	memcpy(st_order.Account_Margin_Type, ACNT_MARGIN_TYPE, sizeof(st_order.Account_Margin_Type));

	/* 국가코드 */
	memcpy(st_order.Country_Code, COUNTRY_CODE, sizeof(st_order.Country_Code));

	/* 투자자 구분코드 */
	memcpy(st_order.Investor_Type, IVT_TYPE, sizeof(st_order.Investor_Type));

	/* 외국인 투자자 구분코드 */
	memcpy(st_order.Foreign_Investor_Type, FI_TYPE, sizeof(st_order.Foreign_Investor_Type));

	/* 주문매체 구분코드 */
	st_order.Order_Mesia_Type[0] = MEDIA_TYPE;

	/* 주문자 식별정보 */
	memcpy(st_order.Order_Identi, ORDER_INFO, sizeof(st_order.Order_Identi));

#endif
	/* 호가일자 */
	__Int2Str(st_order.Order_Date, fep_date, sizeof(st_order.Order_Date));

	/* 회원사 주문시각 */
	__Int2Str(st_order.Member_Order_Time, fep_hour, sizeof(st_order.Member_Order_Time));

	/* 회원사용영역 */
	memset(st_order.MembershipItem, 0x20, sizeof(st_order.MembershipItem));

	/* Filler */
	memset(st_order.Filler, 0x20, sizeof(st_order.Filler));

	return SUCCESS;

}

int	Init(KRX_HEADER* st_header)
{

	/* TR Type */
	memcpy(st_header->proto_type, PROTOCOL_TYPE, sizeof(st_header->proto_type));

	/* Body Length */
	__Int2Str(st_header->body_len, BODY_LEN, sizeof(st_header->body_len));

	/* Message Type */
	memcpy(st_header->msg_type, "TCHODR10001", sizeof(st_header->msg_type));

	/* Message Sequence */
	__Long2Str(st_header->msg_seq, MSGSEQ+1, sizeof(st_header->msg_seq));

	/* Company ID */
	memcpy(st_header->compid, COMPANY_ID, sizeof(st_header->compid));

	/* NO-USE */
	memset(st_header->arr_compid, 0x20, sizeof(st_header->compid));

	/* NO-USE */
	memset(st_header->send_compid, 0x20, sizeof(st_header->send_compid));

	/* Send Time */
	__Int2Str(st_header->send_time, fep_hour, sizeof(st_header->send_time));

	/* Data Count */
	memcpy(st_header->data_cnt, "001", sizeof(st_header->data_cnt));
	
	/* Encrypt YN */
	st_header->encrypt_yn[0] = ENCRYPT_YN;

	return SUCCESS;
}
