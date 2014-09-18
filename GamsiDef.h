#if !defined(AFX_GAMSIDEF_H__F8F250A3_2616_4407_A9C3_5DE6DBF244A6__INCLUDED_)
#define AFX_GAMSIDEF_H__F8F250A3_2616_4407_A9C3_5DE6DBF244A6__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#pragma pack(push, 1)

//==========================================================
// 16개의 조건값 정의
#define STOPLOSS	0x00000001	// 스톱로스				0x10
#define SISEGAMSI	0x00000002	// 시세감시             0x20
#define CHART		0x00000004	// 종합차트				0x30
#define ST_CHART	0x00000008	//		예약(시스템 트레이딩)
#define ST_JUMUN	0x00000010  // 스탑주문				0x50
#define GONGSI		0x00000020  // 공시					0x60
#define NEWS		0x00000040  // 뉴스					0x70
#define RESERCH		0x00000080  // 리서치				0x80
#define RESERVE2	0x00000100  //		예약			0x90
#define CONDITION	0x00000200  // 조건검색				0xa0
#define SINGAL		0x00000400  // 특이신호				0xb0
#define CHEGYEL		0x00000800  //		예약(체결정보)	0xc0
#define JANGO		0x00001000  //		예약(잔고평가)	0xd0
#define SPE_GONGJI  0x00002000  //		예약(특수공지)	0xe0
#define RESERVE3	0x00004000  //		예약			0xf0

#define MACRO_JUMUN	0x00008000  // 메크로 주문

// 카테고리셋트용
#define CATE_STOPLOSS		0x10	// 스톱로스				
#define CATE_SISEGAMSI		0x20	// 시세감시
#define CATE_CHART			0x30	// 종합차트				
#define CATE_ST_CHART		0x40	//		예약(시스템차트			
#define CATE_ST_JUMUN		0x50	// 스탑주문				
#define CATE_GONGSI			0x60	// 공시					
#define CATE_NEWS			0x70	// 뉴스					
#define CATE_RESERCH		0x80	// 리서치				
#define CATE_RESERVE2		0x90	//		예약					
#define CATE_CONDITION		0xa0	// 조건검색				
#define CATE_SINGAL			0xb0	// 특이신호				
#define CATE_CHEGYEL		0xc0	//		예약(체결정보				
#define CATE_JANGO			0xd0	//		예약(잔고평가				
#define CATE_SPE_GONGJI 	0xe0	//		예약(특수공지				
#define CATE_RESERVE3		0xf0	//		예약					



#define		UM_CONCHANGE		WM_USER+900

// 주문설정 구조체
typedef struct	tagJUMUN_ITEM
{
	short	nJumunCheck;		// 주문설정 사용 여부 
	short	nAutoJumun;			// 수동자동 구분(0:수동, 1:자동)
	short	nSMS;				// SMS알림
	int		nMemeGB;			// 매매유형(0:시장가, 1: 보통, 2: 조건부)
	int		nMemeCombo;			// 매매유형 조건부 콤보인덱스
	
	int		nValRadio;			// 가격 사용 조건(0: 콤보의 인덱스, 1:금액)
	int		nVal;				// 입력한 가격

	int		nSuRadio;			// 가격 사용 조건(0:청산금액비율, 1: 수량직접입력, 2:금액으로 수량 계산 )
	int 	nSuRyang;			// 입력한 수량
	int 	nSuCheck;			// 매수시 미수 수량 체크용

	// 주문 결과 데이타 표시용
	char	szJumunNo[6];		// 주문 번호
	int		nJumunSu;			// 주문 수량
	int		nJumunVal;			// 주문 가격
	char	reserve[16];		// 예비
} JUMUN_ITEM;

// 시세감시 구조체
typedef struct	tagSISEGAMSI_ITEM
{
	short	nAndOr;		// 
	short	nItem;		// 항목 인덱스
	short	nCon;		// 조건
	double	dVal;		// 저건값
	short	nUse;		// 사용유무
} SISEGAMSI_ITEM;

typedef struct tagSISEGAMSI
{
	char	szKey[11+6+1];		// 계좌번호+종목코드
	char	szGyeja[11+1];		// 계좌번호	
	char	szCode[6+1];		// 종목코드	
	short	nGamsiState;		// 감시상태 체크용(0 감시안함, 1:감시함)

	short	nGamsiFlag;			// 감시걸린후 계속 감시되는 현상을 막기위한 플래그

	short	nMedosu;			// 매도수 조건 구분(1:매도, 2:매수)
	char	reserve[16];		// 예비

	SISEGAMSI_ITEM	item[5];
	JUMUN_ITEM		jumun;
} SISE_GAMSI;

// 스탑주문
typedef struct	tagSTOPJUMUN
{
	char	szKey[11+6+1];		// 계좌번호+종목코드
	char	szGyeja[11+1];		// 계좌번호	
	char	szCode[6+1];		// 종목코드	
	short	nGamsiState;		// 감시상태 체크용(0 감시안함, 1:감시함)

	short	nMedosu;			// 매도수 조건 구분(1:매도, 2:매수)
	short	nItem;				// 비교가격설정
	short	nCon;				// 조건
	int		nVal;				// 기준가격
	char	reserve[16];		// 예비
	JUMUN_ITEM		jumun;
}STOP_JUMUN;


// 스탑로스 
typedef struct	tagSTOP_LOSS_CON
{
	short	nSiseGB;			// 시세구분
	short	nDangaGB;			// 단가구분
	int		nDangaVal;			// 기준단가 입력값

	short	nLossCheck;			// 손실제한 체크
	int		nLossVal;			// 손실 값
	int		nLossCombo;			// 손실 콤보

	short	nProfitCheck;		// 이익체크
	int		nProfitVal;			// 이익금액
	int		nProfitCombo;		// 이익콤보

	short	nTSCheck;			// 이익보존율
	int		nTSVal;				// 이익 보존 값
	int		nTSCombo;			// 이익 보존 콤보

	int		nSonValue;			// 손실 비교값
	int		nIkValue;			// 이익 비교값
	int		nTsValue;			// 이익보존율 비교값
	int		nHighVal;			// 이익보존율 고가 저장용
	int		nIkUpdate;			// 이익실현 갱신 체크용	
	char	reserve[16];		// 예비
}STOP_LOSS_CON;

// 스탑로스 잔고 편입시 조건
typedef struct	tagSTOPLOSS_INPUT
{
	short			nCheck;				// 잔고 편입시 반영여부
	char	reserve[16];		// 예비
	STOP_LOSS_CON	con;
	JUMUN_ITEM		jumun;
}STOPLOSS_INPUT;

// 스탑로스 
typedef struct	tagSTOP_LOSS
{
	char	szKey[11+6+1];		// 계좌번호+종목코드
	char	szGyeja[11+1];		// 계좌번호	
	char	szCode[6+1];		// 종목코드	
	short	nGamsiState;		// 감시상태 체크용(0 감시안함, 1:감시함)
	char	reserve[16];		// 예비

	STOP_LOSS_CON	con;
	JUMUN_ITEM		jumun;
}STOP_LOSS;


// 주문창 설정 구조체
typedef struct	tagJUMUN_WND_INFO
{
	HWND	hParentWnd;
	short	nGubun;				// 0:시세감시매수, 1:시세감시 매도 2:스탑로스, 3:스탑주문, 4:매크로 주문
	char	szGyeja[11+1];		// 계좌번호	
	char	szCode[6+1];		// 종목코드	

	// 매크로 주문 관련 추가사항
	char	szPasswd[8+1];		// 계좌비번	
	short	nMacroIndex;		// 매크로 주문 인덱스

	char	szJumunMsg[80];		// 주문결과 메세지
	JUMUN_ITEM		jumun;
} JUMUN_WND_INFO;


//====================================================================
// 선물 옵션 스탑로스 관련 구조체 선언
//====================================================================


// 선물 주문설정 구조체
typedef struct	tagFU_JUMUN_ITEM
{
	short	nJumunCheck;		// 주문설정 사용 여부 
	short	nAutoJumun;			// 수동자동 구분(0:수동, 1:자동)
	short	nSMS;				// SMS알림
	int		nMemeGB;			// 매매유형(0:시장가, 1: 보통, 2: 조건부)
	
	int		nValRadio;			// 가격 사용 조건(0: 콤보의 인덱스, 1:금액)
	float	fVal;				// 입력한 가격

	int		nSuRadio;			// 가격 사용 조건(0:청산금액비율, 1: 수량직접입력, 2:금액으로 수량 계산 )
	int 	nSuRyang;			// 입력한 수량
	// 주문 결과 데이타 표시용
	char	szJumunNo[7];		// 주문 번호
	int		nJumunSu;			// 주문 수량
	int		nJumunVal;			// 주문 가격
	char	reserve[16];		// 예비

} FU_JUMUN_ITEM;

// 선물 스탑로스 
typedef struct	tagFU_STOP_LOSS_CON
{
	short	nSiseGB;			// 시세구분
	short	nDangaGB;			// 단가구분
	float	fDangaVal;			// 기준단가 입력값

	short	nLossCheck;			// 손실제한 체크
	float	fLossVal;			// 손실 값
	int		nLossCombo;			// 손실 콤보

	short	nProfitCheck;		// 이익체크
	float	fProfitVal;			// 이익금액
	int		nProfitCombo;		// 이익콤보

	short	nTSCheck;			// 이익보존율
	float	fTSVal;				// 이익 보존 값
	int		nTSCombo;			// 이익 보존 콤보

	float	fSonValue;			// 손실 비교값
	float	fIkValue;			// 이익 비교값
	float	fTsValue;			// 이익보존율 비교값
	float	fHighVal;			// 이익보존율 고가 저장용
	int		nIkUpdate;			// 이익실현 갱신 체크용	

	char	reserve[16];		// 예비
}FU_STOP_LOSS_CON;
//====================================================================
// 선물 스탑로스 
//====================================================================
typedef struct	tagFU_STOP_LOSS
{
	char	szKey[11+8+1];		// 계좌번호+종목코드
	char	szGyeja[11+1];		// 계좌번호	
	char	szCode[8+1];		// 종목코드	
	short	nGamsiState;		// 감시상태 체크용(0 감시안함, 1:감시함)
	char	reserve[16];		// 예비

	FU_STOP_LOSS_CON	con;
	FU_JUMUN_ITEM		jumun;
}FU_STOP_LOSS;

// 스탑로스 잔고 편입시 조건
typedef struct	tagFU_STOPLOSS_INPUT
{
	short			nCheck;				// 잔고 편입시 반영여부
	char	reserve[16];		// 예비
	FU_STOP_LOSS_CON	con;
	FU_JUMUN_ITEM		jumun;
}FU_STOPLOSS_INPUT;
//====================================================================
// 스탑주문
//====================================================================
typedef struct	tagFU_STOPJUMUN
{
	char	szKey[11+8+1];		// 계좌번호+종목코드
	char	szGyeja[11+1];		// 계좌번호	
	char	szCode[8+1];		// 종목코드	
	short	nGamsiState;		// 감시상태 체크용(0 감시안함, 1:감시함)

	short	nMedosu;			// 매도수 조건 구분(1:매도, 2:매수)
	short	nItem;				// 비교가격설정
	short	nCon;				// 조건
	float	fVal;				// 기준가격
	
	char	reserve[16];		// 예비

	FU_JUMUN_ITEM	jumun;
}FU_STOP_JUMUN;

//====================================================================
// 주문창 설정 구조체
typedef struct	tagFU_JUMUN_WND_INFO
{
	HWND	hParentWnd;
	short	nGubun;				// 0:매수, 1:매도
	char	szGyeja[11+1];		// 계좌번호	
	char	szCode[8+1];		// 종목코드	

	// 매크로 주문 관련 추가사항
	char	szPasswd[8+1];		// 계좌비번	
	short	nMacroIndex;		// 매크로 주문 인덱스

	char	szJumunMsg[80];		// 주문결과 메세지
	FU_JUMUN_ITEM	jumun;
} FU_JUMUN_WND_INFO;
//====================================================================


// 신호주문 설정 구조체
typedef struct	tagSIGN_JUMUN_ITEM
{
	int		nMemeCombo;			// 매매유형 콤보인덱스
	int		nVal;				// 입력한 가격
	int 	nSuRyang;			// 입력한 수량
	int 	nSuCheck;			// 매수시 미수 수량 체크용
	char	reserve[16];		// 예비
} SIGN_JUMUN_ITEM;

typedef struct	tagSIGN_JUMUN
{
	SIGN_JUMUN_ITEM	medo;
	SIGN_JUMUN_ITEM	mesu;
} SIGN_JUMUN;


#pragma pack(pop)

#endif // !defined(AFX_GAMSIDEF_H__F8F250A3_2616_4407_A9C3_5DE6DBF244A6__INCLUDED_)
