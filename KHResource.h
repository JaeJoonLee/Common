// Copyrightⓒ 2003 Korea Sorimachi Co.,Ltd. All Rights Reserved. 
//***************************************************************************
// File Name : KHResource.h
// Date      : 
// Creation  : 
// Update    :
// Comment   : 메인화면에서 사용하는 ID 정의
//***************************************************************************
#ifndef __KHRESOURCE_H__
#define __KHRESOURCE_H__


///////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)

#define  MAP_SCREEN			1
#define  MAP_LAYOUT_SPLIT	2

#define  CREATE_NORMAL		0
#define  CREATE_TABSCREEN	1

#define  CREATE_LINK		1

#define  INIT_NORMAL		0
#define  INIT_SAVESCREEN	1

// 초기 폼메니져에게 전달할 항목 정의용
typedef struct	tagFORMMNG_INIT
{
	short	nCreateGB;		// 화면 구분(0: 일반, 1: 탭화면)
	short	nScreenGB;		// 화면생성후 초기정보 구성시 구분용(0: 일반, 1: 사용자 저장화면)
	short	nCreateType;	// 화면 생성 구분(0: 일반, 1: 연결정보적용 화면)
	short	nResize;		// 폰트 리사이즈 여부
	short	FontRate;		// 초기 폰트 배율
	short	nTabHeight;		// 탭화면인경우 탭의 높이
	short	nMapType;		// 화면 타입(1: 일반, 2:종합)
	short	nFixedFontResize;// 고정 포트롤 화면 열기(0, 고정 1:가변변)

#if !defined(_WIN32_WCE)
	char	sTrCode[6+1];
#else
	TCHAR	sTrCode[6+1];
#endif
}FORMMNG_INIT;

typedef struct	tagNEW_TAB_DRAG
{
	char	screenID[5];
	int		left;
	int		top;
}NEW_TAB_DRAG;

typedef struct tagDNDData
{
	POINT			pt;				// 드랍되는 지점
	char			szCode[33];		// 드래그 데이타
	char			szAcctNo[9];	// 계좌번호
	CStringArray	arDataList;		// 복수데이터 
} DRAG_DATA_INFO;

//-------------------------------------------------------------------
struct	TOOL_OUTLOOKDRAGDROP
{
	CString	m_Code;
};

struct	TOOL_OUTLOOKDRAGDROP_LAST
{
	UINT	nKindOfData;
	void*	pData;
};

typedef struct	tagFormInfo
{
	short	m_nWidth;				// 폼의 폭
	short	m_nHeight;				// 폼의 높이
	short	m_nMaxWidth;			// 최대 폭
	short	m_nMaxHeight;			// 최대 높이
	BOOL	m_bMsgDisplay;			// 메세지 라인 표시여부

#if !defined(_WIN32_WCE)
	char	m_szTitleButton[11+1];	// 타이틀 바 버튼 정보
	char	m_szScreenType[40+1];	// 화면유형 정보 ex) 1;5,6;4,5,6
	char	m_szMXN[5+1];			// ex) 3,2
#else
	TCHAR	m_szTitleButton[11+1];	// 타이틀 바 버튼 정보
	TCHAR	m_szScreenType[40+1];	// 화면유형 정보 ex) 1;5,6;4,5,6
	TCHAR	m_szMXN[5+1];			// ex) 3,2
#endif
} FORMINFO;


//typedef struct	tagSK_ErrorInfo
//{
//	TCHAR	m_erType[10];			// 구분값(구분내용)
//	TCHAR	m_erTRCode[5];			// 에러 TRCode
//	TCHAR	m_erScrCode[4];			// 에러 화면번호
//	TCHAR	m_erTitle[40];			// 에러 제목
//	TCHAR	m_erContext[200];		// 에러 내용
//} SK_ERRORINFO;


//// --> [Edit]  남궁 중 2008/04/01
//typedef struct	tagSM_SIGNALMSGINFO
//{
//	TCHAR	m_sgType[2+1];			//	- 신호구분		: 신호 상세분류
//	TCHAR	m_sgTime[6+1];			//	- 발생시간		: HH:MM:SS
//	TCHAR	m_sgSeqno[8+1];			//	- 일련번호
//	TCHAR	m_sgCodeGb[1+1];		//  - 1:코스피,2:코스닥,3:프리보드,4:ELW
//	TCHAR	m_sgCode[8+1];			//	- 종목코드		: 주식(1), 선물(2)/옵션(3), 업종지수(4)
//	TCHAR	m_sgContext[512+1];		//	- 신호내용		: 뉴스타이틀 / 조건내용등
//	TCHAR	m_sgGubun[1+1];			//	- 매도수 구분	: 일반(1) / 매수(2) / 매도(3)
//	TCHAR	m_sgBlink[2+1];			//	- 신호속성		: 깜빡임 횟수
//	TCHAR	m_sgContinue[1+1];		//	- 신호속성		: 유지여부
//	TCHAR	m_sgPriority[2+1];		//	- 신호속성		: 우선순위 
//	TCHAR	m_sgIcon[2+1];			//	- 신호속성		: 표시Icon Index
//	TCHAR	m_sgBugaInfo[10+1];		//	- 부가정보		: DRFN에서 보내는 신호중 신호강도정보
//} SM_SIGNALMSGINFO;
//// <-- [Edit]  남궁 중 2008/04/01

//// --> [Edit]  박정일 2008/04/25
//typedef struct	tagSIGNALORDERSINFO
//{
//	long    hDLLWnd;				//	 호출한 컨트롤 핸들
//	TCHAR	szWindName[8+1];		// - 신호이름 ("주식시세", "선옵시세", "선옵스탑", "조건검색" .....)
//	TCHAR	szSignalgb[2+1];		// - 신호구분 ("감", "스" .....)
//	TCHAR	szPopgb[1+1];			// - 팝업Type(0:미실행, 1:알림창, 2:주문창,  4:자동주문)
//	TCHAR	szAcctno[11+1];			// - 계좌번호
//	TCHAR	szCode[12+1];			// - 종목코드
//	TCHAR	szLoangb[1+1];			// - 신용구분(0:현금, 1:신용)
//	TCHAR	szMemegb[1+1];			// - 매매구분(1:매도, 2:매수, 3:정정, 4:취소, 5:신용매도, 6:신용매수 )
//	TCHAR	szOrdgb[2+1];			// - 주문구분(보통가, 시장가,...)
//	TCHAR	szOrdqtygb[1+1];		// - 주문수량구분(0:수량, 1:금액, 2:매도가능수량%)
//	TCHAR	szOrdqty[15+1];			// - 주문수량
//	TCHAR	szOrdprcgb[1+1];		// - 주문단가구분(0:지정가...(인덱스))
//	TCHAR	szOrdprc[7+1];			// - 주문단가
//	TCHAR	szOrdRow[3+1];			// - 감시된 (스탑 걸린) ROW
//	TCHAR	szLoanDate[8+1];		// - 대출일자
//	TCHAR	szLoanType[1+1];		// - 대출구분	(0:자기, 1:유통)
//	TCHAR	szMsg[512+1];			// - 감시MSG
//} SIGNALORDERSINFO;
//// <-- [Edit]  박정일 2008/04/25

/////////////////////////////////////////////////////////////////////////////

typedef	struct tagKSCDIALOGCREATE
{
	long	nFormHwnd;				// 호출한 폼의 핸들
	char	szFileName[10];			// 호출할 화면명8에서 9자리로 변경(확장자 제외)
	char	strTitle[41];			// 타이틀명 지정용(없으면 화면명으로하자.)
	int     nDlgStyle;				// 0:DoMoal 1: Modalless
	int		nCaptionFlg;			// 0: No Caption, 1:Yes Cation
	int		nPosition;				// 0: 호출시 마우스 위치 좌상
									// 1: 컨트롤 상에 위도우 중앙
									// 2: 컨트롤 좌에 위도우 중앙
									// 3: 호출화면 중앙
									// 4: 윈도우 중앙
									// 5: 특정 위치
									// 6: 마우스 위치
	int		nReSize;				// 사이즈 조절 가능
	int		nAutoClose;				// 영역밖을 클릭시 자동 Close
	HWND    hCtrlWnd;				// 호출한 컨트롤 핸들
	int		nLeftPos;               // 표시할 좌측 위치
	int		nTopPos;				// 표시할 상 위치
	long    nRQID;					// 조회응답 ID
	char	sData[256];
}KSCDIALOGCREATE;

class CScreenLinkMenu
{
public:
	int		nTitleShowHide;			// 타이틀 표시 상태
	int		nTab;					// 탭 표시 여부
	int		nTabShowHide;			// 탭 표시 표시 상태
	int		nSDIStyle;				// 독립실행 상태(0:MDIchild, 1: 독립실행)
	int		nVirtureIndex;			// 가상화면표시 상태(nVirtureIndex < 0: 메뉴 체크, 0이상이면:체크해제)
	CStringArray saSystemMenu;		// 시스템 제공 연결 메뉴 리스트
	CStringArray saUserMenu;		// 사용자 등록 연결 메뉴 리스트
};

class CSubTabDragCreate
{
public:
	CString		strScreenID;		// 화면번호
	CPoint		pt;					// 좌표

	CString     strTabName;			// Tab 이름.
	CString     strJCode;			// 종목코드
};

#pragma pack(pop)


// 챠일드 화면 생성 구분
#define	CHILD_NORMAL		0
#define	CHILD_LINK			1
#define	CHILD_TAB			2
#define	CHILD_AUTO			3
#define	CHILD_COPY			4
#define	CHILD_GDLINK		5

#define	SCREEN_NORMAL		0
#define	SCREEN_USER_SAVE	1


// MDI챠일드의  뷰윈도우  구분
#define VIEW_RUN		0
#define VIEW_WEB		1
#define VIEW_TAB		2
#define VIEW_POPUP		3
#define VIEW_SPLITTER	4
#define VIEW_GROUP		5
#define VIEW_REPLACE	6


#define IDS_HOWOO_STARTDOCKING		2001
#define ID_HOWOO_ALLOWDOCKING		2002
#define ID_HOWOO_HIDE				2003
#define ID_HOWOO_MDIFLOAT			2004
#define ID_HOWOO_CUSTOMIZE			2005

// 툴바에 있는 버튼의 아이디
#define ID_BAR_BUTTON_START			2200
#define ID_BAR_BUTTON_END			2299

// 툴바에 있는 버튼의 아이디
//#define ID_TR_MINISTATE_BTN			2200	// 툴바 접기용 버튼튼
#define		ID_TOOLBARSCRSEARCH		(WM_USER + 3618)	// 화면찾기버튼
#define		ID_TOOLBAR_CHART		(WM_USER + 3619)	// 툴바 챠트
#define		ID_TOOLBAR_ADDTOOL		(WM_USER + 3620)	// 사용자 화면 툴바 추가
#define		ID_TOOLBAR_TEXT			(WM_USER + 3621)	// 텍스트 보기
#define		ID_TOOLBAR_ICON			(WM_USER + 3622)	// 아이콘 보기
#define		ID_TOOLBAR_SCROLL_UP	(WM_USER + 3623)	// 위로 보기
#define		ID_TOOLBAR_SCROLL_DOWN	(WM_USER + 3624)	// 위로 보기
#define		ID_TOOLBAR_BANNER		(WM_USER + 3625)	// 베너 보기
//LJP 20110801 Start-->
#define		ID_TOOLBAR_ONETEXT		(WM_USER + 3626)	// 한줄로 보기
#define		ID_TOOLBAR_TWOTEXT		(WM_USER + 3627)	// 두줄로 보기
//<--End


#define ID_TR_EDIT					2201	
#define ID_TR_LIST_BTN				2202	
#define ID_TR_SEARCH_BTN			2203
#define ID_TR_COMMAND_BTN1			2204
#define ID_TR_COMMAND_BTN2			2205
#define ID_TR_COMMAND_BTN3			2206
#define ID_TR_COMMAND_BTN4			2207
#define ID_TR_COMMAND_BTN5			2208
#define ID_TR_COMMAND_BTN6			2209
#define ID_TR_COMMAND_BTN7			2210
#define ID_TR_COMMAND_BTN8			2211
#define ID_TR_COMMAND_BTN9			2212
#define ID_TR_COMMAND_BTN10			2213
#define ID_TR_COMMAND_BTN11			2214

#define ID_TR_SETUP_BTN				2215	// 설정
#define ID_TR_RESIZE				2216	// 화면찾기, 화면저장등 기능툴바 버튼  숨기기용
#define ID_TR_APPEND_BTN			2217	// 툴바에 표시안된 버튼 표현하는 버튼
#define ID_TR_SHORT_BTN				2218	// 짧게보기 2011.05 jhj
#define ID_TR_NORMAL_BTN			2219    // 길게보기 2011.05 jhj

#define ID_AUTOHIDE					2220	// 자동숨김
#define ID_MINIMIZE					2221	// 모든 화면 최소화
#define ID_VIRTUAL_BTN1				2222	// 가상 스크린
#define ID_VIRTUAL_BTN2				2223
#define ID_VIRTUAL_BTN3				2224
#define ID_VIRTUAL_BTN4				2225

#define ID_SIGNAL_ITEM_BTN			2230	// 신호 관리자 버튼
#define ID_SIGNAL_START_BTN			2231
#define ID_SIGNAL_PAUSE_BTN			2232
#define ID_SIGNAL_SETUP_BTN			2233
#define ID_SIGNAL_FOLD_BTN			2234

#define ID_TICKER_SETUP				2235	// 티커 설정 버튼
#define	ID_TICKER_NEWS_BTN			2236
#define	ID_TICKER_NEWS_LISTBOX		2237
#define	ID_TR_DELETE_BTN			2238	// 종목관리 삭제 버튼

#define	ID_MTC_IG_LISTBOX			2500	// 미니티커 관심그룹 리스트박스
#define	ID_MTC_IG_SETUP_BTN			2501	// 미니티커 관심그룹 설정 버튼
#define	ID_MTC_JP_LISTBOX			2510	// 미니티커 종목시세 리스트박스
#define	ID_MTC_JP_SEARCH_BTN		2511	// 미니티커 종목시세 검색 버튼
#define	ID_MTC_JP_TITLE_BTN			2512	// 미니티커 종목시세 종목명 버튼

#define ID_CLOCK_DATE_BTN			2240
#define ID_CLOCK_TIME_BTN			2241

#define ID_CHEGYEL_SETUP			2245
#define ID_CHEGYEL_DELETE			2246
#define ID_CHEGYEL_FOLD				2247

#define ID_TR_MENUCALL_BTN1			2251	// 사용자 저장화면 호출 버튼
#define ID_TR_MENUCALL_BTN2			2252
#define ID_TR_MENUCALL_BTN3			2253
#define ID_TR_MENUCALL_BTN4			2254
#define ID_TR_MENUCALL_BTN5			2255
#define ID_TR_MENUCALL_BTN6			2256
#define ID_TR_MENUCALL_BTN7			2257
#define ID_TR_MENUCALL_BTN8			2258
#define ID_TR_MENUCALL_BTN9			2259
#define ID_TR_MENUCALL_BTN10		2260


#define ID_SIGNAL_CON_CLOSE			2280
#define ID_SIGNAL_CON1				2281
#define ID_SIGNAL_CON2				2282
#define ID_SIGNAL_CON3				2283
#define ID_SIGNAL_CON4				2284
#define ID_SIGNAL_CON5				2285
#define ID_SIGNAL_CON6				2286
#define ID_SIGNAL_CON7				2287
#define ID_SIGNAL_CON8				2288
#define ID_SIGNAL_CON9				2289
#define ID_SIGNAL_CON10				2290

#define	ID_TICKER_MEDO_BTN			2291
#define	ID_TICKER_MESU_BTN			2292

// 툴바 그룹 변경용 버튼 클릭시 팝업메뉴 표시용 
#define ID_TB_GROUP_START			2300
#define ID_TB_GROUP_END				2399

#define ID_MYMENU_BTN_START			2400  // 메뉴 선택용 콤보	
#define ID_MYMENU_BTN_END			2497  // 메뉴 선택용 콤보	

#define ID_MYMENU_BTN_REG_TOOLBAR	2498  // 현재화면 책갈피 추가
#define ID_MYMENU_BTN_USERSAVESCR	2499  // 현재화면 툴바 등록
// 툴바에서 팝업으로 메뉴 호출한 경우
#define ID_MYMENU_POPUP_START		3000
#define ID_MYMENU_POPUP_END			4000

/****************************************/
/*	Runtime Browser Menu ID Define		*/
/****************************************/
#define IDM_TRMENUSTART					13000	// 메인메뉴의 TR메뉴 ID 범위
#define IDM_TRMENUEND					16000

#define IDM_LAYOUTMENU_START			16001
#define IDM_LAYOUTMENU_END				16100

#define	IDM_USER_TOTAL_SCR_START		16150
#define	IDM_USER_TOTAL_SCR_END			16250

#define	IDM_USER_SCREEN_START			16300
#define	IDM_USER_SCREEN_END				16400

#define	IDM_USER_PROGRAM_START			16501	//	사용자 지정 외부 프로그램 메뉴 ID 범위
#define	IDM_USER_PROGRAM_END			16600


#define IDM_FLAT_MENU_START				17000
#define IDM_FLAT_MENU_END				17999

#define IDM_OPENED_SCREEN_START			18000	// 열린 화면 목록
#define IDM_OPENED_SCREEN_END			18499
#define IDM_RUN_RELOGIN					18500	// 메인 재로그인 한다

#define	IDM_OUTLOOK_MENU			(WM_USER + 111)
#define	IDM_TICKERDIALOGBAR_MENU	(WM_USER + 112)
#define	IDM_TRADEBAR_MENU			(WM_USER + 113)
#define	IDM_VIRTUALSCREENBAR_MENU	(WM_USER + 114)
#define	IDM_WEBBAR_MENU				(WM_USER + 115)
#define	IDM_FULLSCREEN_MENU			(WM_USER + 116)

#define	UM_CHILDSCREEN				(WM_USER + 150)		// 일반 화면 스크립트롤 호출용
#define	UM_POPUPSCREEN				(WM_USER + 151)		// 팝업 화면 스크립트롤 호출용
#define	UM_SMDIALOG_MSG				(WM_USER + 152)		// 다이얼로그 화면처리용 메세지 
#define	UM_SMDIALOG_MSG2			(WM_USER + 153)		// 다이얼로그 화면처리용 메세지2

#define	UM_KHDIALOG_MSG 			(WM_USER + 154)		// 다이얼로그 화면처리용

#define	UM_CHILDSCREENFORNEWSCREEN	(WM_USER + 155)		// 무조건 신규화면 생성용

#define	UM_NEW_TAB_DRAG				(WM_USER + 200)
#define	UM_SCREEN_DOWNLOAD			(WM_USER + 201)
#define UM_ALRAM_NOTIFY				(WM_USER + 202)

//프레임윈도우 == > 폼뷰
//내용 : 폰트가변 여부 셋트
#define UM_SET_FORMVIEW_FONT_RESIZE (WM_USER + 203)		// wParam -> 0:고정, 1:가변
//폼뷰 == > 프레임윈도우
//내용 : 윈도우 핸들 저장
#define UM_SET_FORMVIEW_HWND		(WM_USER + 204)
//폼뷰 == > 프레임윈도우
//내용 : 윈도우 기본사이즈 지정
#define UM_SET_FORMVIEW_DEF_SIZE	(WM_USER + 205)

// 뷰의 내부에 폼을 다단으로 추가시 childframe의 최대사이즈를 고정시킨다.
#define UM_SET_FORMMAXSIZE			(WM_USER + 206)

#define UM_KILLUSER					(WM_USER + 207)		// 다른 사용자에 의해 종료를 당할때...

#define UM_GETCOMBOINDEX			(WM_USER + 208)		// 관심종목 콤보인덱스 취득용
#define	UM_DND_NOTIFY				(WM_USER + 209)		// 드래그 & 드랍 지원

#define	UM_GET_OPEN_FILENAME		(WM_USER + 210)		// 종합화면에서 오픈할 파일명을 구하기 위한 메세지

#define	UM_JUMUN_RET				(WM_USER + 211)		// 스탑로스 주문 확인창 주문결과 통보용

#define	UM_CALL_FROM_FORM			(WM_USER + 212)		// 폼과 메인과의 메세지 전달용
#define	UM_GET_GAMSIJONGMOK			(WM_USER + 213)		// 메인에서 설정한 감시종목 취득용

#define	UM_REPLACE_MAP				(WM_USER + 214)		// 화면 초기화시에 맵파일을 버젼처리 한다(화면 팝업메뉴)
#define	UM_VERSION_DLGMAP			(WM_USER + 215)		// 화면 초기화시에 맵파일을 버젼처리 한다(Dll에서 호출 한다)

#define	UM_SET_TABMENUSCREEN		(WM_USER + 216)		// Tab화면에서 TabMenu 선택시 Tab변경을 위해.
#define	UM_CHANGE_TABSCREEN			(WM_USER + 217)		// Tab화면에서 TRCODE바에서 입력한 코드 적용

#define	UM_CALL_CTI_INFO			(WM_USER + 218)		// 폼과 상담메인간의 정보 교환용

#define	UM_SETVIEWPROJECTION		(WM_USER + 219)		// ljj 20110512 add 화면보호기 강제 실행(5분)

// 관심종목 등록창에서 화면 생성메세지 호출시
#define	UM_SCREENCREATE				(WM_USER + 225)
#define	UM_FIDCHANGE				(WM_USER + 226)		// 화면에서 FID 변경시 프레임 윈도우에게 전달하는 메세지

#define	UM_M_BY_N_INFO				(WM_USER + 227)		// 챠일드 화면의 M * N 정보를 취득해 폼콘트롤에게 전달한다.
#define	UM_SCR_COMM_MSG				(WM_USER + 231)		// 조회 응답에 대한 메세지 전달용
#define	UM_GET_SCREENLINKMENU		(WM_USER + 235)		// 화면의 그리드에서 연결화면 리스트 목록 취득용
#define	UM_GET_MDICHILD_STYLE		(WM_USER + 236)		// 화면생성시 생성 방법 취득용 메세지
#define	UM_MDI_MODECHANGE			(WM_USER + 237)		// 독립실행 모드에서 모드 전환을 위한 메세지

#define	UM_MULTICODE_LINK			(WM_USER + 238)		// 관심종목화면에서 복수종목을  MXN화면으로 전달하는 메세지
#define	UM_CAPTIONCLICK				(WM_USER + 239)		// 관심종목화면에서 사용하는  CAPTION CLICK메세지

// FORM OCX에서 챠일드 컨트롤에게 전달하는 메세지 정의(폼과 테이블, 폼과 그리드에서 사용함)
#define	UM_EDIT_COPY				(WM_USER + 240)		// 복사
#define	UM_EDIT_PASTE				(WM_USER + 241)		// 붙여 넣기
#define	UM_EDIT_EXCEL_DDE			(WM_USER + 242)		// 엑셀 실시간 붙여넣기 메뉴
#define	UM_EDIT_SELECT_ALL			(WM_USER + 243)		// 전체 선택

#define	UM_EDIT_ACTIVE_CODE			(WM_USER + 244)		// Active 화면의 화면TR코드

#define	UM_TREE_LBUTTONUP			(WM_USER + 250)		// 티커 뉴스설정 다이얼로그 트리콘트롤의 메세지 처리용

#define	UM_QUERY_HOTKEY				(WM_USER + 300)		// 메인 단축키 처리시 스페이스 사용여부 체크용

#define UM_TREDIT_FULL				(WM_USER + 301)
#define UM_CHILD_NOTIFY				(WM_USER + 302)

#define	UM_TICKER_SETUP				(WM_USER + 320)
#define	UM_TICKER_APPLY				(WM_USER + 321)

#define	UM_TICKER_APPLY				(WM_USER + 321)

#define	UM_CTI_DATA					(WM_USER + 350)		// CTI메인화면과 정보교환을 위한 메세지

#define	UM_GAMSI_REAL				(WM_USER + 400)		// 스탑로스 실시간 데이타 처리용
#define	UM_GAMSI_SENDDATA			(WM_USER + 401)		// 스탑로스 설정 변경 처리용(그리드 <--> StoplossWnd)
#define	UM_GAMSI_RECVDATA			(WM_USER + 402)		// 스탑로스 초기 데이타 요청용(그리드 <--> StoplossWnd)

#define	UM_CHANGE_PARENT			(WM_USER + 450)		// 독립실행시 프레임 윈도우 변경을 통지하기위해...

#define	UM_CREATEAFTER				(WM_USER + 500)
#define	UM_TITLE_MSG				(WM_USER + 501)

#define	UM_FILE_UPDOWNLOAD_MSG		(WM_USER + 502)

// 종합화면 관련
#define	UM_CHILDMDIACTIVATE			(WM_USER + 521)

#define UM_JONGMOKBAR_CHANGE		(WM_USER + 522)		// 종목 변경
#define UM_OPEN_MAP					(WM_USER + 523)		// 메인 이외의 곳에 화면을 열려고 할때
#define UM_WATCH_ORDER				(WM_USER + 524)		// 감시주문설정 메세지

#define UM_CHANGE_REGKW				(WM_USER + 525)		// 관심종목 그룹변경 처리용
#define UM_JONGMOKCHANGE_REGKW		(WM_USER + 526)		// 관심종목 그룹종목변경 후 저장시 티커(Main)에 알려주기 위한 메세지

#define UM_SUBTAB_DRAGDROP			(WM_USER + 527)		// 서브텝에서 드래그드롭으로 화면 생성
#define UM_POPUP_JCODE				(WM_USER + 528)		// 종목코드 컨트롤에서 팝업 윈도우로 종목코드를 넘긴다. 

// DLL 에서 맵들을 사이즈 조절할때 그리드가 잘 그려지지 않는 문제가 있다.
// 이때 해결책으로 만든다.
// RunFormCtrl.cpp 의 Onsize 에 이 메세지를 넣고 Dll 화면의 ViewWrap.cpp 와 .h에 이 메세지를 받아 "1"을 리턴한다.
// 그럼 RunFormCtrl.cpp 에서 "OnSizeAfter" 함수를 타지 않고  DLL 의 OnSize을 타고 넘어간다.
// "0" 을 리턴하던지, 해당 메세지가 없으면 DLL 의  OnSize에서는 처리하면 안된다.
#define UM_DLLSIZE_CONTROL_MSG		(WM_USER + 530)		// 종목코드 컨트롤에서 팝업 윈도우로 종목코드를 넘긴다. 

#define UM_SETFORMACC_CHANGE		(WM_USER + 531)		// 각  FORM 의 계좌콤보의 비밀번호(다른 뭐든) 변경을 알려준다.


#define UM_SM_SIGNAL_MSG			(WM_USER + 550)		// 신호처리기에서 받은 데이타를 등록된 콘트롤에 전달한다.
														// wParam = ( 1:콘트롤핸들 등록,  -1:콘트롤핸들 해제 )  
														// lParam = ( 콘트롤 -> 메인   )콘트롤의 핸들값
														// lParam = ( 메인   -> 콘트롤 )받은 신호를 전달한다.


#define UM_SM_SIGNALORDER_MSG		(WM_USER + 551)		// 신호처리기에서 받은 데이타를 등록된 콘트롤에 전달한다.
														// wParam = ( 1:콘트롤핸들 등록,  -1:콘트롤핸들 해제 )  
														// lParam = ( 콘트롤 -> 메인   )콘트롤의 핸들값
														// lParam = ( 메인   -> 콘트롤 )받은 신호를 전달한다.

#define UM_LAYOUT_CHANGE			(WM_USER + 560)		// 폼에서 받은 유형 변경
														// wParam = ( 0 : 유형변경 )  
														// lParam = ( 유형인덱스 )  

#define UM_POST_FORM_FIRE			(WM_USER + 570)		//2010. 9. 7 변윤식

#define UM_SET_KW_GROUP_CODE		(WM_USER + 571)		// 관심그룹코드 저장
#define UM_GET_KW_GROUP_CODE		(WM_USER + 572)		// 관심그룹코드 얻기

#define UM_UPLOAD_DB				(WM_USER + 573)		// LJP 20110320
#define UM_EXEC_DEFAULT_VAL			(WM_USER + 574)		//KJI 20110419
#define UM_GET_FONT_INDEX			(WM_USER + 575)		//KJI 20110512 (뉴스공시 폰트관련 조정)

// 메뉴바에서 메뉴 아이템 표시이미지 번호
//#define	IMAGE_NONE			0
#define	IMAGE_POPUP			0
#define	IMAGE_NORMAL		1
#define	IMAGE_WEB			2
#define	IMAGE_EXE			3
#define	IMAGE_DISABLE		4


// DsBitmapButton에서 사용
//====================================================
#define UM_BTNLDOWN					WM_USER+1101
#define UM_BTNLUP					WM_USER+1102
#define UM_BTNTOBTN					WM_USER+1103
#define UM_MENU_DELETE				WM_USER+1104
#define UM_MENU_RENAME				WM_USER+1105
#define UM_SUBMENUDISP				WM_USER+1106

#define UM_RMOUSECLICK				WM_USER+1107		// 

// DsDragDropTarget에서 사용
//====================================================
#define UM_DROPOCCUR				WM_USER+1201
//====================================================

// TabBarWnd에서 사용
//====================================================
#define UM_BTNCLICK					WM_USER+1401
#define UM_SENDORDER				WM_USER+1402
#define UM_SENDADD					WM_USER+1403
#define UM_SENDDELETE				WM_USER+1404
#define UM_BUTTONOK					WM_USER+1406
#define UM_OUTLOOKTO				WM_USER+1407
//====================================================

// TreeCtrl에서 사용
//====================================================
#define WM_TREEDROP					WM_USER+1601
//====================================================

// captionbutton.cpp 에서 사용
#define UM_CBLBUTTONCLICKED			WM_USER+1650			// 타이틀바 버튼 클릭에 대한 메세지

// captionbutton.cpp 에서 사용
#define UM_CSYSBLBUTTONCLICKED		WM_USER+1651			// 타이틀바 시스템버튼 클릭에 대한 메세지

// 좌측메뉴바에서 사용
#define ID_GFX_REMOVEITEM           WM_USER+1652
#define BASISMENU_OUTLOOK			WM_USER+1653			// 아웃룩바를 위한 변수 ..

// DsTabCtrl에서 사용
//====================================================
#define WM_TABTOTAB					WM_USER+1701
//====================================================

// 시세틱커에서 사용
//====================================================
//#define	WMU_QUOTEUPDATE			WM_USER + 3001
//#define	WMU_QUOTEUPDATE2		WM_USER + 3002
//#define	WMU_GOODBYE_ALLBASE		WM_USER + 3005
//#define WMU_CODECANCEL			WM_USER + 3007
//====================================================

//-------------------------------------------------------------------

//#define ID_SCROLL_PANE                  33030

// 다이얼로그 표시 효과 정의
#define AW_HOR_POSITIVE             0x00000001 
#define AW_HOR_NEGATIVE             0x00000002 
#define AW_VER_POSITIVE             0x00000004 
#define AW_VER_NEGATIVE             0x00000008 
#define AW_CENTER                   0x00000010 
#define AW_HIDE                     0x00010000 
#define AW_ACTIVATE                 0x00020000 
#define AW_SLIDE                    0x00040000 
#define AW_BLEND                    0x00080000 


// 윈도우의 OS타입을 정의한다.
#define OS_ERROR                    0
#define OS_WIN95                    1
#define OS_WIN98                    2
#define OS_WIN2000                  3
#define OS_WINNT                    4
#define OS_WIN32S					5
#define	OS_WINME					6
#define	OS_WINXP					7
// --> [Edit]  BT.Jung 2007/01/11    
#define	OS_VISTA					8		// 비스타
// <-- [Edit]  BT.Jung 2007/01/11

#define CAPTION_HEIGHT				18		// 일반윈도우(win2000이하 XP제외)

// From 16-bit windows.h
#define GFSR_SYSTEMRESOURCES		0
#define GFSR_GDIRESOURCES			1
#define GFSR_USERRESOURCES			2


// Builder의 팝업 메뉴에서 사용하는 ID들
//#define IDM_ORDER_TOP				6015
//#define IDM_ORDER_BOTTOM			6016


#endif		//__KHRESOURCE_H__
