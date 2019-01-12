#ifndef     __KRX_STRUCT_H
#define     __KRX_STRUCT_H
/*------------------------------------------------------------------------
#   System  : David Trading
------------------------------------------------------------------------*/

/*------------------------------------------------------------------------
    Constants and Structures
------------------------------------------------------------------------*/
#define KRX_HEAD_LEN                    (sizeof (KRX_HEADER))   /* 82   */
#define KRX_SESSION_BODY_LEN            (sizeof (KRX_SESSION) - sizeof (KRX_HEADER))   /* 42   */

#define	PROTOCOL_TYPE					"KMAPv1.0"
#define	COMPANY_ID						"00021"
#define	BRANCH_ID						"00021"
#define	ENCRYPT_YN						'Y'

#define	ACNT_NO							"01111038624"
#define	PGM_TRD_TYPE					"00"	//일반
#define	ACNT_TYPE						"41"	//자기일반계좌
#define	ACNT_MARGIN_TYPE				"10"	//사전증거금 일반
#define	COUNTRY_CODE					"999"	//대한민국
#define	IVT_TYPE						"7100"  //기타법인
#define	FI_TYPE							"20"	//외국인비거주
#define	MEDIA_TYPE						'4'		//HTS
#define	ORDER_INFO						"010222244444"		//주문자식별코드

/* KRX 차세대 Header (82bytes)  */
typedef struct {
    char    proto_type[8];           /* 전문유형(API프로토콜의버젼)      */
    char    body_len[6];             /* 메시지길이(Body전체길이)         */
    char    msg_type[11];            /* 메시지타입                       */
                                     /* 세션메시지타입 및 TR Code        */
                                     /* "S"+"CH"+Type(3)+일련번호(5)     */
    char    msg_seq[11];             /* 일련번호                         */
                                     /* 주문요청 Body첫번째항목 일련번호 */
                                     /* 주문응답 채널 최종 처리 일련번호 */
    char    compid[5];				 /* 회원번호                         */
    char    arr_compid[10];          /* 연계시도착회원사번호             */
    char    send_compid[10];         /* 회신시송신회원사번호             */
    char    send_time[17];           /* 전송일시(YYYYMMDDHHMMSSMS)       */
    char    data_cnt[3];             /* 데이터건수                       */
    char    encrypt_yn[1];           /* 암호화유무                       */
} KRX_HEADER;

/* KRX 차세대 Session */
typedef struct {
    KRX_HEADER  header;
    char        data[42];
}   KRX_SESSION;

/* KRX 차세대 매매 - 주문요청 : 호가입력 (300 bytes)  */
typedef struct {
    char    MsgSeq[11];                     /* 메시지 일련번호          */
    char    TrCode[11];                     /* TR code                  */
    char    Regular_Off[1];                 /* 정규시간외               */
    char    MembershipNo[5];                /* 회원번호                 */
    char    BranchNo[5];                    /* 지점번호                 */
    char    OrderNo[10];                    /* 주문번호                 */
    char    OriginalOrderNo[10];            /* 원주문번호               */
    char    ItemCode[12];                   /* 종목코드(표준종목코드)   */
    char    TradeFlag[1];                   /* 매도매수구분             */
    char    New_Modify_Cancel_gbn[1];       /* 정정취소구분코드         */
    char    AccountNo[12];                  /* 계좌번호                 */
    char    OrderQuantity[10];              /* 호가수량                 */
    char    Price[11];                      /* 호가가격                 */
    char    Order_Type[1];                  /* 호가유형                 */
    char    Order_Condition[1];             /* 호가조건                 */
    char    Mm_Order_Type_No[11];           /* 지장조성자 호가구분번호  */
    char    Treasury_Stock_Id[5];           /* 자사주신고서 ID          */
    char    Treasury_Stock_Method[1];       /* 자사주매매 방법코드      */
    char    Ask_Type[2];                    /* 매도유형코드             */
    char    Credit_Type[2];                 /* 신용구분코드             */
    char    Trust_Principal_Type[2];        /* 위탁 자기구분코드        */
    char    Trust_Company_No[5];            /* 위탁사번호               */
    char    Program_Trading_Type[2];        /* PT구분코드               */
    char    Substitute_AccNo[12];           /* 대용주권계좌번호         */
    char    Account_Type[2];                /* 계좌구분코드             */
    char    Account_Margin_Type[2];         /* 계좌증거금 유형코드      */
    char    Country_Code[3];                /* 국가코드                 */
    char    Investor_Type[4];               /* 투자자구분코드           */
    char    Foreign_Investor_Type[2];       /* 외국인투자자 구분코드    */
    char    Order_Mesia_Type[1];            /* 주문매체구분코드         */
    char    Order_Identi[12];               /* 주문자식별정보           */
    char    Order_Date[8];                  /* 호가일자                 */
    char    Member_Order_Time[9];           /* 회원사 주문시각          */
    char    MembershipItem[40];             /* 회원사용영역             */
    char    Filler[73];                     /* Filler                   */
}   TCHODR10001_BODY;

typedef struct {
	KRX_HEADER			header;
	TCHODR10001_BODY		body;
}	TCHODR10001_STRUC;

#endif
