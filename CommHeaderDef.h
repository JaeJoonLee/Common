#if !defined(_COMMHEADERDEF_H_)
#define _COMMHEADERDEF_H_

#include "KSCommon.h"

#define		WM_RP_RECEIVED				WM_USER + 1000
//#define		TRAN_H_TRCODE_LEN			32				// TrCode값  버퍼길이 정의 
//#define		TRAN_H_CODE_LEN				8				// Code값 버퍼길이 정의 


// 1 Byte Allignment
#pragma pack(push, 1)

// CommsLogin 통신시 메세지 처리
enum {
	ERR_COMM_OK		= 0,
	ERR_COMM_LOGIN,				// 로그인 실패
	ERR_COMM_LOGIN_RCV,			// 로그인 수신후 플래그 정보로 에러처리
	ERR_COMM_CERT,
};

// CommAPI기동 프로그램 종류 정의 
enum  COMMINI_TYPE 
{
	RUN_PROGRAM		= 0,	// Main_Run
	BUILDER_PROGRAM,		// 빌더 프로그램 
	STARTER_PROGRAM,		// 스타터 프로그램
	TRANBUILDER_PROGRAM,	// 트랜빌더 
	STARTER_INDEX_PROGRAM,	//KJI 20110725 (로그인 전에 지수 데이터 처리용)
};


//*****************************************************************************
// Revision By:  김 창하 Revision Day:  2003년8월13일
// Comments: 그리드와 FORM공통 변수사용
// OnRequestActionChanged 이벤트에 대한 변수값 정의 
//*****************************************************************************
enum  ACTIONKEY_STATUS
{
	ACTIONKEY_DEFAULT		 = 0,				// 일반 조회구분값
	ACTIONKEY_PRE_BUTTON,						// 이전 버튼 선택시 조회구분값
	ACTIONKEY_NEXT_BUTTON,						// 다음 버튼 선택시 조회구분값
	ACTIONKEY_PAGEDOWN,							// Page Down 선택시 조회구분값
	ACTIONKEY_PAGEUP,							// Page Up   선택시 조회구분값
	ACTIONKEY_FID_CHANGE,						// FID Drag&drop 발생시 조회구분값
	ACTIONKEY_CODE_CHANGE						// 그리드 내부에서 종목코드 변경시 조회구분값   
};


enum  DATAKIND_STATUS
{
	DATAKIND_RQRP		 = 0,	// 조회요청응답
	DATAKIND_PB,      			// 실시간 데이터
	DATAKIND_MSG,				// 통신 메세지
	DATAKIND_RELEASE,			// 트랜 릴리즈
	DATAKIND_DOWNLOAD ,			// 파일 다운로드
	DATAKIND_DOWNLOAD_STATUS,	// 파일 다운로드 상태정보
	DATAKIND_COMM_DEBUG,		// CommsDbg데이터
	DATAKIND_CERT_DATA,			// 인증서 데이터
	DATAKIND_DATAHEADER_DATA,	// 데이터헤더
	DATAKIND_DOWNLOAD_ERROR,	// 다운로드 에러
	DATAKIND_CERT_ERROR,		// 인증에러
	DATAKIND_SS_ERROR,			// 서버 시스템에러
	DATAKIND_SHAREMEM,			// 공유데이터
	DATAKIND_CERT_DATA2,		// 인증서 데이터(증권금융 일반 법인 인증서 처리용)
	DATAKIND_SERVER_PUSH,		// 서버가 push
	DATAKIND_LOGIN,				// 로그인/공인인증
};

//*****************************************************************************

/*--- message define ---*/
enum    DM_ID           // NEX MESSAGE ID   
{
    DM_RQ_ID,			//  0 Request
    DM_RP_ID,           //  1 Reply
    DM_SB_ID,			//  2 Subscribe
    DM_SBC_ID,			//  3 Subscribe Cancel
    DM_PB_ID,			//  4 Publish
	DM_INFO_ID
};


// 데이터 로그 표시 타이프 
#define LOG_DEBUG		0	// 디버그 전용 데이터
#define LOG_UM			1	// 사용자 메세지
#define LOG_STATUS		2	// 상태 메세지
#define LOG_RQ			3	// 조회
#define LOG_RP			4	// 응답
#define LOG_SB			5	// 리얼 등록
#define LOG_SBC			6	// 리얼 삭제
#define LOG_PB			7	// 리얼
#define LOG_DATA		8	
#define LOG_CERT		9	// 공인인증
#define LOG_ERROR		10
#define LOG_INFO		11
//#define LOG_LOGIN		11
//#define LOG_LOGIN_BP	12
//#define LOG_XECURE	13

#define LOG_TYPE_COMMS					0	// 통신로그
#define LOG_TYPE_STARTER				1	// 스타터 로그인 관련 로그(starter.log에 기록)
#define LOG_TYPE_REGISTERED_REALKEY		2	// 현재 등록된 실시간 등록키를 파일로 작성한다.(notepad 실행)

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// 각 패킷의 유형별 ID(한화증권용) /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define	PID_CONNECT_OLD			0x01	// 초기 접속(고객인증) KJI 20021203 Not Use
//#define	PID_CONNECT				0x18	// 로그인 정보 공통 전달사용 KJI 20021203 Add
#define	PID_CONNECT				0x35	// 로그인 정보 공통 전달사용 KJI 20021203 Add	[PMI] 0x18 -> 0x35로 변경
#define PID_PLOT_CONNECT		0x29	//KJI 20120206 (모의투자 접속처리)
#define	PID_NEWREGISTER			0x02	// 신규등록
#define	PID_TRDATA				0x05	// 일반 TR
#define	PID_ENDVERSION			0x08	// 버전처리 완료			//shc 20011030
#define	PID_REVERSION			0x09	// 종합 버전 번호 요구
#define	PID_POLLING				0x10	// Alive Check - pc 안씀
#define	PID_REGCONCERN			0x11	// 관심 종목 등록
#define	PID_CRCFILEDN			0x12	// JJH 20071117  CRC 파일다운로드

#define	PID_FILEDOWN			0x5f	// FileDownLoad		0x12 -> 0x82 -> 0x82 로 바뀜

#define PID_REQ_CONNECT			0xfb	//KJI 20070619	(버전처리 먼저)
#define PID_ENCXMINIT_SET		0x7d	//KJI 20070618

#define	PID_ENCCLIENTSET_OLD	0x13	// XECURE INIT
#define	PID_ENCCLIENTSET		0x0A	// XECURE INIT		//shc 20040106	BCC 사용set
#define	PID_ENCCLIENTID			0x16	// XECURE ID
#define	PID_ENCCLIENTPWD		0x17	// XECURE PWD
#define	PID_SVRPOLL				0x14	// Alive Check - server
#define	PID_PCCLOSE				0x19	// PC 종료
// ADD NEOFRAME KHY 20050827
#define PID_ERROR_REPORT        0x1d	// PC Error Report 
#define	PID_THREAD_TRDATA       0x1d	// THREAD_TRDATA : 일반 TR PC에서 사용
#define	PID_THREAD_RELEASECODE  0x1f	// THREAD 자동갱신 코드 등록/해제
// END ADD NEOFRAME KHY 20050827

#define	PID_TICKERMSG			0x20	// Ticker Message
#define	PID_POPUPMSG			0x21	// Popup Message
#define	PID_CB					0x22	// CB(Circuit Break)
//#define	PID_BASEPRICE		0x23	// 기준가 통보(신규상장종목은 장시작과 더불어 기준가가 변동되는데 이를 통보
#define	PID_ONLINECONSULT		0x23	// 온라인투자상담 신호
#define	PID_CHEKYOUL			0x24	// 체결통보
#define PID_PLOT_CHEKYOUL		0xC1	//KJI 20120206 (모의투자)
#define	PID_TICKERNEWS			0x25	// Ticker 뉴스
#define	PID_TICKERSIHWANG		0x26	// Ticker 시황
#define	PID_SC					0x27	// SideCar
#define	PID_TICKERKONGJI		PID_TICKERMSG	// Ticker 공지 사항(일단은 TickerMsg와 동일 처리),
#define	PID_TICKERJONG			0x29	// Ticker 종목

#define	PID_RELEASECODE			0x30	// 자동갱신 코드 등록/해제

#define	PID_JISUSISE			0x31	//업종시세
#define	PID_YEJISUSISE			0x40	//예상체결지수			//shc 20030212
#define	PID_JONGSISE			0x32	//주식종목시세 1건		//shc 20011030
#define	PID_JONGHOGA			0x33	//주식종목호가 잔량
#define	PID_JONGMEMBER			0x34	//주식종목 거래원
#define	PID_JONGFORIGN			0x35	//주식종목 외국인
#define	PID_JISUUPDOWN			0x36	//업종등락
#define	PID_JONGCHEGYUL			0x3A	//주식종목체결	20건	//shc 20011030
#define	PID_JONGHOGA_10			0x3B	//주식종목호가 10단계	//shc 20011217
#define	PID_JONGSISECYCLE		0x50	//주식종목시세변동		//shc 20011030
#define PID_JONGRANDOM_END		0x0B	//주식임의종료-예상체결	//shc 20040109
#define PID_JONG_YECHEGYUL		0x3C	//주식종목 예상체결		//ynkim 20061122

//KJI 20060329
#define PID_XRPOWER				0xC8	//세력정보일반
#define PID_XRIO				0xC9	//입출정보
#define PID_XROFFER				0xCA	//매물대
#define PID_XRCHEKYOUL			0xCB	//체결관련
#define	PID_XRFOCUS				0x6a	//호가변동 포착관련

#define PID_TIMEOVERJONGSISE	0x63    //시간외 체결			//KJI 20050516
#define PID_TIMEOVERJONGHOGA	0x64    //시간외 호가			//KJI 20050516
//#define PID_TIMEOVERJONGMEMBER	0x65    //시간외 거래원			//KJI 20050516
//#define	PID_TIMEOVERUPJISU	    0x3E	//시간외업종지수		//KJI 20050516
#define	PID_TIMEOVERJISUUPDOWN	0x3D	//시간외업종등락		//KJI 20050516
//#define	PID_TIMEOVERYEJISUSISE	0x3C	//시간외예상지수		//KJI 20050516

#define	PID_NEWGETSISE			0x37	// 신주인수권종목체결 + ELW
#define	PID_NEWGETHOGA			0x38	// 신주인수권종목호가 + ELW
#define	PID_NEWGETMEMBER		0x39	// 신주인수권종목거래원 + ELW
#define	PID_ELWHOGA_10			0x4C	// ELW 10단계 호가	KJI 20051206
#define PID_ELW_IDX				0x4D	// ELW 투자지표 KJI 20051216
#define PID_ELW_ICHANGE			0x4E	// ELW 내재변동성	KJI 20051229
#define PID_ELW_YECHE			0x3E	// ELW 예상체결 KJI 20061122

#define	PID_FUTURESISE			0x41	// 선물체결
#define	PID_FUTUREHOGA			0x42	// 선물호가
#define	PID_FUTUREMIGYUL		0x48	// 선물미체결
#define	PID_FUTUREBASIS			0x88	// 선물베이시스		//shc 20021127
#define	PID_OPTIONSISE			0x43	// 옵션체결
#define	PID_OPTIONHOGA			0x44	// 옵션호가
#define	PID_OPTIONINVOLA		0x45	// 옵션호가 내재 변동성
#define	PID_OPTIONMIGYUL		0x49	// 옵션미체결
#define	PID_FUTUREOPEN			0x4A	// 선물시가			//shc 20040419
#define	PID_OPTIONOPEN			0x4B	// 옵션시가			//shc 20040419

//KJI 20051025
#define	PID_FSTARSISE			0x5A	// 스타선물체결
#define	PID_FSTARHOGA			0x5B	// 스타선물호가
#define	PID_FSTARMIGYUL			0x5C	// 스타선물미체결
#define	PID_FSTARBASIS			0x5D	// 스타선물베이시스
#define	PID_FSTAROPEN			0x5E	// 스타선물시가

#define	PID_HIYIELDSISE			0x46	// 수익증권 종목체결
#define	PID_HIYIELDHOGA			0x47	// 수익증권 종목호가
#define	PID_BONDSISE			0x51	// 채권 체결
#define	PID_BONDHOGA			0x52	// 채권 호가
#define	PID_QFUTURECHEGYUL		0x53	// KOSDAQ50 선물 체결
#define	PID_QFUTUREHOGA			0x54	// KOSDAQ50 선물 호가
#define	PID_QFUTURESISE			0x55	// KOSDAQ50 선물 시세
#define	PID_QFUTUREMIGYUL		0x56	// KOSDAQ50 선물 미결제수량
#define	PID_EXCHSISE			0x57	// 아시아 환율 /지수시세	   2001.4.24
#define	PID_KOFEXMARKET			0x58	// 코스닥선물 장운영 상태	   2001.6.15 -hidden-			

#define	PID_STOPLOSSAUTO		0x59	// StopLoss 자동주문 응답
#define	PID_STOPLOSSSEMI		0x60	// StopLoss 반자동주문

#define	PID_OTCBBSISE			0x61	// 제3시장 종목 체결
#define	PID_OTCBBHOGA			0x62	// 제3시장 종목 호가

#define PID_QOPTIONCHE			0x69    //KOSDAQ옵션 체결
#define PID_QOPTIONSISE			0x70    //KOSDAQ옵션 시세
#define PID_QOPTIONHOGA			0x71    //KOSDAQ옵션 호가 
#define PID_QOPTIONNJ			0x72    //KOSDAQ옵션 내재변동성
#define PID_QOPTIONMCHE			0x73	//KOSDAQ옵션 미체결

#define PID_JOPTIONSISE			0x74    //주식옵션 시세			//shc 20020110
#define PID_JOPTIONHOGA			0x75    //주식옵션 호가 
#define PID_JOPTIONNJ			0x76    //주식옵션 내재변동성
#define PID_JOPTIONMCHE			0x77	//주식옵션 미체결
#define PID_SC_JOPTION			0x78	//특정 주식옵션종목 SC

//ljj 20080318 add 주식선물 
#define PID_JFUTURESISE			0x79    //주식선물 체결
#define PID_JFUTUREHOGA			0x7a    //주식선물 호가 
#define PID_JFUTUREMCHE			0x7b	//주식선물 미체결
#define PID_JFUTUREBASIS		0x7c    //주식선물 베이시스

#define PID_TUJASISE			0x80	//투자주체별 순매수 자동갱신	//shc 20020404
#define PID_NAVSISE				0x83	//지수 투자신탁 수익증권		//shc 20021022	

#define PID_IPDUP				0x81	// 중복접속 아이피 계좌 통보
#define	PID_OTPSEND				0x97	
#define	PID_SETHWND				0x98	// 통신에 메인 윈도우를 전달
#define	PID_LOGUSERINFO			0x99	// 사용자 정보 (클라이언트에서만 사용)
#define PID_BASEPRC				0x9f	// 기준가 통보 20091014 JJH
#define PID_SINGLESIGN_INFO		0xf0	//KJI 20070704
#define	PID_CONNECTERROR		0xa0
#define	PID_LOGUSERINFOAGAIN	0xa1
#define PID_JDEPOS_REAL			0x0e	//KJI 20041019 (종목별 증거금 실시간 변경)
#define PID_JDEPOS_GROUP_REAL	0x2f	//ljj 20061114(종목별 증거금률군 실시간 변경)
#define	PID_TIMEOVER_REAL		0x0f	//KJI 20050516 (시간외 종목 실시간 변경)

// 2002.06.17 -hidden-
#define PID_TRDATA_TOBP			0xa2	// BP로 패킷을 보내기위함(PC에서만 사용함)
#define PID_BP_LOGUSERINFO		0xa3	// 신업무 사용자의 사용자 정보
#define PID_BP_ERRLOGUSERINFO	0xa4	// 신업무 사용자정보가 에러일때
#define	PID_BP_CHEKYOUL			0xa5	// 신업무 체결통보(PC에서만 사용)
#define	PID_BP_POLLING			0xa6	// 신업무 서버 폴링
#define	PID_BP_POPUPMSG			0xa7	// 신업무 POPUP 메세지 (PC에서만 사용함)
#define PID_TRDATA_XRAY			0xa8	// 호가변동에서만 사용
#define PID_SYSALARM			0xa9	// LJP 20070910 시스템 알람

// CJH 20050711
#define PID_SIGNAL_UAS_FID		0x1a	// PC-사용자별조건검색 mdb서버에서발생FID
#define PID_SIGNAL_SAS_FID		0x1b	// PC-set을 걸건지 판단 후에 재조정 필요mdb서버에서발생FID
// CJH 20050711
#define PID_SIGNAL_NEWS_FID		0x1c	// ADD NEOFRAME KHY 20050721

#define PID_TEMA				0x6e	// 테마실시간
#define NEW_UAS_FID				0x6b	// New User Signal
#define NEW_SAS_FID				0x6c	// New System Signal
#define NEW_CAS_FID				0x6d	// 순간체결량

// ADD NEOFRAME KHY 20050822
#define PID_FO_PCR_FID			0x2a    // PUT_CALL_Premium_Ratio
#define PID_FO_OIX_FID			0x2b    // Future_Min_OIX
#define PID_FO_FOR_FID			0x2c    // Future_Hoga_FOR
#define PID_FO_OI2_FID			0x2d    // OPTION_JISU
#define PID_FO_KP2_FID			0x2e    // KP200_LIVE_JISU

// 상품선물
#define PID_SFUTURESISE			0x8a
#define PID_SFUTUREHOGA			0x8b
#define PID_SFUTUREMCHE			0x8c
#define PID_SFUTUREBASIS		0x8d
#define PID_SFUT_YECHE			0x8e
#define PID_SOPTIONSISE			0x9a
#define PID_SOPTIONHOGA			0x9b
#define PID_SOPTIONNJ			0x9c
#define PID_SOPTIONMCHE			0x9d
#define PID_SOPT_YECHE			0x9e
#define PID_SOBJ_JISU			0x8f

//KJI 20120104 (Buy-In 제도 관련 사항)
#define PID_BUYIN_JONGSISE		0x92	//주식종목체결
#define PID_BUYIN_JONGHOGA		0x93	//주식종목호가
#define	PID_BUYIN_NEWGETSISE	0x94	// 신주인수권종목체결 + ELW
#define	PID_BUYIN_NEWGETHOGA	0x95	// 신주인수권종목호가 + ELW
#define	PID_BUYIN_HIYIELDSISE	0x96	// 수익증권 종목체결
#define	PID_BUYIN_HIYIELDHOGA	0x97	// 수익증권 종목호가

#define	PID_AUTOORDER			0x28	// 서버반자동주문
#define	PID_PLOT_AUTOORDER		0xC2	//KJI 20120206 (모의투자)

#define RECSIZE					3
#define ERRCODE_SIZE			5
#define TRCODE_SIZE				8
#define SCRN_LEN				6
#define POLLING_CHECK_INTERVAL	180		// 3분
#define MSG_SIZE				80		// 서버에서 주는 메세지(에러 포함) 크기

// 압축의 기준이 되는 body 크기
#define COMPRESS_STANDARD_SIZE	4096
// 압축 후 서버로 전송 시 body의 단위
#define COMPRESS_SEND_SIZE		2048

#define MAX_PACKET_SIZE			4096
#define MAX_SEND_SIZE			2048	

#define SZ_BCC_CHECKSUM			4
#define REAL_TYPE_SIZE			4

// Common Header의 cCpFlag 비트별 값
#define FLAG_COMPRESS			0x80	// 압축
#define FLAG_ENCRYPT			0x40	// 암호화
#define FLAG_FIDCOMM			0x20	// FID통신
#define FLAG_COMPRESS_FAILED	0x10	// 압축 후 사이즈가 큰 경우(압축 실패)
#define FLAG_PACKET_BEGIN		0x08	// packet 시작
#define FLAG_PACKET_CONTINUE	0x04	// packet 연속
#define FLAG_PACKET_END			0x02	// packet 끝

//////////////////////////////////////////////////////////////

// 91 ~ 99는 예약된 MinorID
#define MINOR_ENCRYPT		30090	// 암호화 키교환용
#define MINOR_CERTIFICATE	30091	// 인증서 정보 취득
#define MINOR_CERT_VERIFY	30092	// 인증서 검증
#define MINOR_CERTPASSERR	30093	// 인증서 비밀번호 실패
#define MINOR_CERTISSUE		30094	// 인증서 발급
//#define MINOR_TICKER		95	// 티커 요청
//#define MINOR_REALREG		96	// 리얼등록/해지
#define MINOR_AS_LOGIN_DATA	30096	// 로그인 성공 서버 등록
#define MINOR_SETPUBLIC_KEY	30097	// 공인인증 성공 서버 등록
#define MINOR_LOGOUT		30098	// Logout처리
#define MINOR_LOGIN			30099	// Login처리

#define MINOR_CERT_DESTROY	30100	// 공인인증서 폐지 (변윤식 2010. 12. 1)

// --> [Edit]  강지원 2010/07/28	( X-Ray 추가 )
#define MINOR_XRAY			30100	// X-RAY 요청 ID
// <-- [Edit]  강지원 2010/07/28

#define RQ_ID_LOGIN			100		// 로그인의 RQID
#define RQ_ID_CERT			101		// 공인인증의 RQID

// 데이타 헤더 타입 정의
#define FID_HEADER				0		// FID 방식 
#define TR_HTS_G_HEADER			1		// HTS 일반
#define NO_TR_HEADER			2		// TR 헤더가 필요 없는 경우

//로그인유형
#define LOGIN_TYPE_STOCKTOT		'1'	//주식종합형		ljj 20070208 Modify
#define LOGIN_TYPE_CMA			'2'	//CMA 자산관리형	ljj 20070208 Add
#define LOGIN_TYPE_MINI			'3'	//직장인
#define LOGIN_TYPE_TRAD			'4'	//Ez-YesTrader
#define LOGIN_TYPE_EAGLE		'5'	//Eagle				//ljj 20040423 이글
#define LOGIN_TYPE_VIRTUALFUT	'6'	//선물모의투자게임	//shc 20040720
#define LOGIN_TYPE_FUTOPT		'7'	//선물옵션형		ljj 20070208 Modify


/*----------------------------------------------------*/

////////////////////////////////////////////////////////////////
/*
// 계정계 통신의 공통헤더
typedef struct _NEXTKEY_IO
{
	char	KeyValue[16];	// Next를 위한 키값부분
	long	KeyNo;			// 키값 일련번호
	long	Count;			// 총 Read 개수
	long	RequestCnt;		// 총 Client가 요청한 린턴될 개수
}NEXTKEY_IO;
*/

// 데이터 전문에 포함된 구분자 정의 
#define US						(BYTE)0x1F	// 개별의 요소를 분리하는 단위(Unit Separator)
#define FS						(BYTE)0x1E	// 컨트롤 사이의 구분자로 사용 (Field Separator)
#define PS						(BYTE)0x0D	// Out 블럭 구분
#define RS						(BYTE)0x0A  // 레코드 구분
#define IS						(BYTE)0x7F	// FID와 입력 데이터 사이의 구분자로 사용 ( 사용안함 )
#define _TCH_US					US
#define _TCH_FS					FS
#define _TCH_PS					PS
#define _TCH_RS					RS
#define _TCH_IS					IS

//// 데이터 구분자 정의
#define	CDID_R_SISED			0x0101		// 시세 DATA
#define	CDID_R_MULTISISED		0x0181		// 시세 DATA(복수키)

////
#define CDID_DT_RST				0x0201		// DATA 조회
#define CDID_DT_RSP				0x0202		// DATA 응답 
#define CDID_DT_RSET			0x0203		// DATA RESET(화면Close)
#define CDID_CODE_RSET			0x0204		// CODE RESET


#define CDID_TR_RST				0x0211		// TR 조회
#define CDID_TR_RSP				0x0212		// TR 응답 

#define CDID_FILEDOWN_RST		0x0221		// 파일전송요청
#define CDID_FILEDOWN_START		0x0222		// 파일전송개시
#define CDID_FILEDOWN_DATA		0x0223		// 파일본문
#define CDID_FILEDOWN_END		0x0224		// 파일전송종료

#define CDID_FILERECOVERY_RST	0x0241		// 복구전송요청
#define CDID_FILERECOVERY_START	0x0242		// 복구전송개시
#define CDID_FILERECOVERY_DATA	0x0243		// 복구본문
#define CDID_FILERECOVERY_END	0x0244		// 복구전송종료

#define CDID_CONN_CLOSE			0x0433		// 접속단절 요청 

//
#define CDID_STAT_RQ			0x0701		// 상태 의뢰
#define CDID_STAT_RP			0x0702		// 상태 응답(Reply Only)
#define CDID_POLLING_DATA		0x0705		// Polling Data

enum  REQUEST_STATUS
{
	REQUEST_SUCCESS					= (BYTE)0x00,	// 정상
	REQUEST_ERROR_SOCKET			= (BYTE)0x01,	// 소켓송신 에러
	REQUEST_ERROR_NOTCONNECT		= (BYTE)0x02,	// 통신 미연결 상태
	REQUEST_ERROR_ALLOCMEM			= (BYTE)0x03,	// 메모리 에러
	REQUEST_ERROR_FORMAT			= (BYTE)0x04,	// 통신규약 에러
	REQUEST_ERROR_DOWNLOAD			= (BYTE)0x05,	// 다운로드 상태  
	REQUEST_CERT_NOTDEFINE			= (BYTE)0x06,	// 인증서 미정의 
	REQUEST_LOGIN_NOTUNSERINFO		= (BYTE)0x07,	// 유저정보 없음 	
	REQUEST_LOGIN_FAIL				= (BYTE)0x08,	// 승인처리 실패 	
	REQUEST_SENDLEN_OVER			= (BYTE)0x09,	// 데이터 전문길이 초과
	REQUEST_ERROR_NOTCOMPLETE		= (BYTE)0x10,	// 데이터 조회중
	REQUEST_CERT_NOTCOMPLETE		= (BYTE)0x11,	// 인증서 오류
	REQUEST_INVALID_SERVICE			= (BYTE)0x12,	// 서비스명이 틀림
};


// 실시간 등록및 해제용 변수 정의  
enum  REALUPDATE_MSG
{
	REALUPDATE_REISTER,			// 리얼관리 테이블 등록
	REALUPDATE_UNREISTER,		// 리얼관리 테이블 데이터 리셋정보송신
	REALUPDATE_CODE_DELETE		// 리얼관리 테이블 종목코드삭제후 리셋정보송신
								// (포토폴리오형에서 하나의 키값을 삭제) 
};											


//////////////////////////////////////////////////////////////////
// RegisterWindowMessage로 등록된 메세지에 대한 WPARAM값을 
// 정의한 값 
//////////////////////////////////////////////////////////////////
//   HANDLE_CONTROL_MSG							//
// CommsDbg.exe <-> Comms.exe <-> CommAPI.dll
enum  HANDLE_CONTROL_MSG
{ 
	COOMS_WINDOW_HANDLE	= 1,	// Comms의 윈도우 핸들
	COMAPI_WINDOW_HANDLE,		// ComAPI의 윈도우 핸들 
	COMMSDBG_WINDOW_HANDLE,		// ComsDBG의 윈도우 핸들
	STARTER_WINDOW_HANDLE		// Starter의 윈도우 핸들
};

//	SOCKET_NOTIFY_MSG(소켓통지관련)
// Comms.exe->CommAPI.dll
enum  SOCKET_STATUS_MSG
{ 
	SOCKET_CONNECTING =50,		// 소켓 연결 중 
	SOCKET_CONNECTED,			// 소켓 연결 완료
	SOCKET_CLOSED,				// 소켓 단절 상태
	SOCKET_CLOSING,				// 소켓 단절 중
	SOCKET_CONNECT_FAIL,		// 소켓 연결 실패
	SOCKET_RECEIVE_FAIL,		// 데이터 수신 실패
	SOCKET_SEND_FAIL,			// 데이터 송신 실패
	SOCKET_SEND_SUCCESS,		// 데이터 송신 성공
	SOCKET_RECONNECT_REQUEST,	// 재접속 요청
	LOGIN_COMPLETE,				// 승인처리 완료 
	LOGIN_FAIL,					// 승인처리 실패 
	SISE_SOCKET_CONNECTED,		// 소켓 연결 완료
	SISE_SOCKET_CLOSED,			// 소켓 단절 상태
	REVERSION,					// 버전처리 하라는 메세지
	ENDVERSION,					// 버전처리 완료 했다는 메세지
};

// COMMS_PROCCESS_MSG(통신프로그램 기동, 프로그램 종료및 데이터설정및 취득 관련)
// CommAPI.dll -> Comms.exe
//////////////////////////////////////////////////////////////////
enum  COMMS_PROCCESS_MSG
{ 
	COMMS_CONNECT_START = 1,	// TCP 연결시작
	COMMS_RECONNECT_START,		// TCP 재연결 
	COMMS_TERMINATE,			// 프로그램 종료
	GET_SIGNON_DATA,			// 사이온 상태취득
	SET_SIGNON_DATA,			// 사이온 상태설정
	COMMS_CONFIG_CHANGE,		// 통신환경 변경 
	GET_REALKEY_DISPLPAY,		// Real키 리스트요구(디버그용) 
	GET_EXCELDDE_ITEMLIST,		// Excel DDE링크정보(디버그용) 
	SET_CONSOLAPP_CREATE,		// Consol 프로그램 기동 
	GET_USERINFO_DATA,			// 사용자 정보 요구 
	GET_USERINFO_DISPLPAY,		// 사용자 정보리스트 표시(디버그용) 
	COMMS_LANG_CHANGE,			// 언어변경 통지
	COMMS_RECONNECT_REQUEST,  	// TCP 재연결 요청  
	COMMS_COMSTART,  			// 소켓 처음 연결시 수신 정보 취득용
	XECURE_INIT					// xecure init
};


// 쿼리컨트롤 또는 메인에서 조회요청에 대한 조회응답 메세지 정보를 정의한 값
// (수신초과, 모든 템플릿 조회응답 수신완료(조회완료내용)표시  
// CommAPI.dll -> 각 화면 
//////////////////////////////////////////////////////////////////
enum  REPLY_MESSAGE_INFO
{ 
	RP_SUCCESS		= (WORD)0x00,	// 조회정상		정보
	RP_ERROR		= (WORD)0x02,	// 조회에러		정보
	RP_TIMEOUT		= (WORD)0x04	// 수신시간초과 정보
};

// 파일,복구,CL 데이터유형인경우 다운로드 상태값 
enum  DOWNLOAD_MSG_INFO
{
	FILE_DOWN_TIMEOUT  = 130,		// 파일 다운로드 수신시간초과  
	FILE_DOWN_START,				// 파일,복구다운로드  개시
	FILE_DOWN_DATA,					// 파일,복구다운로드  본문 
	FILE_DOWN_END,					// 파일,복구다운로드  종료
	FILE_PCMASTER_START,			// 마스터파일 다운로드  개시
	FILE_PCMASTER_DATA,				// 마스터파일 다운로드  본문 
	FILE_PCMASTER_END,				// 마스터파일 다운로드  종료
	FILE_DOWN_ERROR,				// 에러인 경우(서버 제공 에러코드) 
	FILE_DOWN_SOCKETCLOSED,			// 파일 수신중 소켓 단절된 경우 
	FILE_DOWN_FORMAT_ERROR  = 200,	// 파일개시 응답전문 형식이 맞지 않습니다 
	FILE_DOWN_FILESIZE_ERROR,		// 다운로드한 총 파일사이즈가 일치하지 않습니다
	FILE_DOWN_SEQNUMBER_ERROR,		// 다운로드한 일련번호가 일치하지 않습니다
	FILE_DOWN_LISTFILESIZE_ERROR,	// 목록리스트와 서버로부터 수신한 전체 파일사이즈가 일치하지 않습니다.
	FILE_DOWN_FILEWRITE_ERROR		// 파일 쓰기작업시 시스템에러가 발생 했습니다.
};

// CommAPI용 메세지및 상테코드값 정의 
enum  COMMAPI_MSG_INFO
{
	COMMAPI_USERDATA_NOTFIND = 210,			// 고객정보 데이터 파일에 고객 정보가 없습니다(win.ini)
	COMMAPI_COMMSPRO_NOTFIND,				// 통신 어플리케이션이 존재 하지 않습니다
	COMMAPI_COMMSINIFILE_NOTFIND,			// 통신환경 정보파일이 존재 하지 않습니다
	COMMAPI_SCREENVERFILE_NOTFIND,			// 화면목록 버전파일이 존재 하지 않습니다
	COMMAPI_COMMS_OPENERROR,				// 통신 프로그램을 기동시 에러가 발생 했습니다
	COMMAPI_SCREEN_MAPINFO_ERROR,			// 화면파일을 다운로드한 파일은 화면목록 맵 정보가 없습니다
	COMMAPI_PCMASTERFILE_DOWNLOAD_START,	// 마스터파일 다운로드 중입니다.
	COMMAPI_MENUFILE_DOWNLOAD_START			// 메뉴파일   다운로드 중입니다.
};


// CheckStart용 메세지및 상테코드값 정의 
enum  CHECKSTART_MSG_INFO
{
	CHECKSTART_MACADDRESS_NOTFIND = 250,	// 등록된 MacAddress가 존재하지 않습니다.call센터로 문의바랍니다.
	CHECKSTART_LOGIN_REQUEST,				// 승인처리 요청중 입니다
	CHECKSTART_NOTCOMAPRE_MACADDRESS,		// 서버에 등록된 MacAddress와 단말의MacAddress일치 하지 않습니다. call센터로 문의바랍니다.
	CHECKSTART_NOT_USERPID,					// 고객 PID가 없습니다.Call센터로 문의 바랍니다
	CHECKSTART_LOGIN_COMPLETE,				// 승인처리 완료
	CHECKSTART_VERSIONLIST_RECEIVE,			// 버전목록을 수신중입니다
	CHECKSTART_VERSIONLIST_COMPARE,			// 버전목록을 비교중 입니다
	CHECKSTART_VERSIONLIST_COMPAREERROR,	// 버전목록을 비교중 에러 발생 했습니다
	CHECKSTART_MASTERLIST_COMPARE,			// 마스터목록을 비교중 입니다
	CHECKSTART_MASTERLIST_COMPAREERROR,		// 마스터목록을 비교중 에러 발생 했습니다
	CHECKSTART_CONTROL_REGISTER,			// 컨토롤 등록처리 중입니다
	CHECKSTART_CONTROL_REGISTERERROR,		// 컨토롤 등록시 에러가 발생 했습니다=File[%s],ErrorCode=[%d]
	CHECKSTART_CALLCENTER_TEL,				// Call센터로 문의 바랍니다
	CHECKSTART_NEWFILE_PROCCESS,			// 최신파일 버전처리(다운로드)중 입니다
	CHECKSTART_LANGECHANGE_PROCCESS,		// 언어환경 변경처리중 입니다
	CHECKSTART_LANGECHANGE_CONFIRM,			// 언어환경 변경확인 메세지 
	CHECKSTART_USERLEVEL_ERROR,				// 사용자 등급정보 에러입니다..call센터로 문의바랍니다.
	CHECKSTART_LANGCODE_ERROR,				// 언어코드 정보 에러입니다..call센터로 문의바랍니다.
	CHECKSTART_MENUFILE_NOTFIND				// 버전목록에 등급정보에 따른 메뉴정보가 없습니다..call센터로 문의바랍니다.
};



//////////////////////////////////////////////////////////////////
// ComApi에서 화면,메인으로 데이터를 전달하기위한 사용자 메세지 정의값 
//////////////////////////////////////////////////////////////////
#define WM_BEGIN_WAIT_CURSOR		WM_USER + 600	// CommApi에서 Form Wnd에 있는 BeginWaitCursor를 기동하게 한다.
#define WM_END_WAIT_CURSOR			WM_USER + 601	// CommApi에서 Form Wnd에 있는 EndWaitCursor를 기동하게 한다.
#define WM_GET_DATA					WM_USER + 602	// 화면에게 조회응답데이터(RP) 처리를 하도록하는 메세지 
#define WM_GET_MSG					WM_USER + 603	// CommApi에서 Form Wnd에 메세지를 보낸다.
#define WM_GET_RELEASE				WM_USER + 604	// CommApi에서 Form Wnd에 트랜종료를 보낸다.
#define WM_GET_BROD					WM_USER + 605	// 화면에게 실시간데이터(PB)처리를 하도록하는 메세지 
#define WM_GET_CONTRACT				WM_USER + 606	// 컨트롤에서 체결데이터를 받는다.
#define WM_RESET_DATA				WM_USER + 620	// 조회요청에 대한 조회응답 메세지 정보를 처리를 하도록하는 메세지
// 파일 다운로드
#define WM_FILE_DOWNLOAD			WM_USER + 621
#define WM_FILE_DOWNLOAD_CANCEL		WM_USER + 622
#define WM_FILE_DOWNLOAD_COMMAND	WM_USER + 623
#define WM_FILE_DOWNLOAD_REQUEST	WM_USER + 624

#define WM_REPLY_MSGINFO			WM_USER + 625	// 조회요청에 대한 조회응답 메세지 정보를 처리 하도록하는 메세지 
#define WM_COMMAND_MSGDATA			WM_USER + 626

#define WM_REALDATA_RECEIVED		WM_USER + 627
#define WM_WATING_TCP_DOWNLOAD		WM_USER + 628
#define WM_USER_ABORT_FLAG			WM_USER + 629

#define WM_SIGNALDATA_RECEIVED		WM_USER + 630
#define WM_MEMODATA_CHANGED			WM_USER + 631
#define WM_WATCHDATA_CHANGED		WM_USER + 633
#define WM_JANGO_RECEIVED_OK		WM_USER + 634
#define WM_GET_FREESTYLE			WM_USER + 635

#define WMU_NOCONNECT_ACK			WM_USER + 636

#define UM_GET_TREE_COMM_DATA		WM_USER + 637	// 트리에서 통신을 통해 종목을 가져오는 경우

// 파일 다운로드시 데이터 종류를 정의값 
#define	MAIN_VERSION_FILE		0			// 메인용 다운로드(호출한 화면에서 파일을 작성) 
#define SCREEN_VERSION_FILE		1			// 화면용 다운로드(CommAPI에서 파일작성) 
#define MENU_DATA_FILE			2			// 제어전문으로 요청한 메뉴 파일 다운로드(CommAPI에서 파일작성) 
#define COMMAPI_DATA_FILE		3			// 무조건 COMMAPI에서  수신한 데이터를 작성한다.
#define PCMASTER_DATA_FILE		4			// 제어전문으로 요청한 PC마스터 파일 다운로드  
#define RECOVERY_DATA_FILE		5			// 복구데이터 다운로드(호출한 화면에서 파일을 작성) 

#define	IDS_MENU_FILENAME					_T("menu/menu.dat")


// Little_edian ->Big_edian
inline void ConvertBigEndian ( short& d )
{
	short s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[1];
	pd[1] = ps[0];
}

inline void ConvertBigEndian ( WORD& d )
{
	WORD s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[1];
	pd[1] = ps[0];
}

inline void ConvertBigEndian ( int& d )
{
	int s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[3];
	pd[1] = ps[2];
	pd[2] = ps[1];
	pd[3] = ps[0];
}

inline void ConvertBigEndian ( DWORD& d )
{
	DWORD s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[3];
	pd[1] = ps[2];
	pd[2] = ps[1];
	pd[3] = ps[0];
}

inline void ConvertBigEndian ( long& d )
{
	long s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[3];
	pd[1] = ps[2];
	pd[2] = ps[1];
	pd[3] = ps[0];
}

inline void ConvertBigEndian ( float& d )
{
	float s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[3];
	pd[1] = ps[2];
	pd[2] = ps[1];
	pd[3] = ps[0];
}

inline void ConvertBigEndian ( double& d )
{
	double s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[7];
	pd[1] = ps[6];
	pd[2] = ps[5];
	pd[3] = ps[4];
	pd[4] = ps[3];
	pd[5] = ps[2];
	pd[6] = ps[1];
	pd[7] = ps[0];
}
inline void ConvertBigEndian ( __int64& d )
{
	__int64 s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[7];
	pd[1] = ps[6];
	pd[2] = ps[5];
	pd[3] = ps[4];
	pd[4] = ps[3];
	pd[5] = ps[2];
	pd[6] = ps[1];
	pd[7] = ps[0];
}
inline void ConvertLittleEndian ( float& d )
{
	float s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[3] = ps[0];
	pd[2] = ps[1];
	pd[1] = ps[2];
	pd[0] = ps[3];
}


inline void ConvertLittleEndian ( double& d )
{
	double s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[7] = ps[0];
	pd[6] = ps[1];
	pd[5] = ps[2];
	pd[4] = ps[3];
	pd[3] = ps[4];
	pd[2] = ps[5];
	pd[1] = ps[6];
	pd[0] = ps[7];
}
inline void ConvertLittleEndian ( __int64& d )
{
	__int64 s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[7] = ps[0];
	pd[6] = ps[1];
	pd[5] = ps[2];
	pd[4] = ps[3];
	pd[3] = ps[4];
	pd[2] = ps[5];
	pd[1] = ps[6];
	pd[0] = ps[7];
}



//--------------------------------------------

inline short ConvertBigEndianRet ( short s )
{
	ConvertBigEndian( s );
	return s; 
}

inline WORD ConvertBigEndianRet ( WORD s )
{
	ConvertBigEndian( s );
	return s; 
}

inline int ConvertBigEndianRet ( int s )
{
	ConvertBigEndian( s );
	return s;
}

inline DWORD ConvertBigEndianRet ( DWORD s )
{
	ConvertBigEndian( s );
	return s;
}

inline long ConvertBigEndianRet ( long s )
{
	ConvertBigEndian( s );
	return s;
}

inline float ConvertBigEndianRet ( float s )
{
	ConvertBigEndian( s );
	return s;
}

inline double ConvertBigEndianRet ( double s )
{
	ConvertBigEndian( s );
	return s;
}

inline __int64 ConvertBigEndianRet ( __int64 s )
{
	ConvertBigEndian( s );
	return s;
}

#pragma pack(pop)

#endif // !defined(_COMMHEADERDEF_H_)
