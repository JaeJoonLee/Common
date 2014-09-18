#ifndef _OGDESIGNDEFINE_H_
#define _OGDESIGNDEFINE_H_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define	 USE_DEF_CAPTION_LEN	1	
/*
#define GS						(BYTE)0x1D	// 데이터의 시작 의미(Group Separator)
#define US						(BYTE)0x1F	// 개별의 요소를 분리하는 단위(Unit Separator)
#define FS						(BYTE)0x1E	// 컨트롤 사이의 구분자로 사용 (Field Separator)
#define PS						(BYTE)0x0D	// 복수의 KEY Item이 존재할 때 구분자로 사용.
#define RS						(BYTE)0x0A  // 복수의 레코드가 존재할 때 ROW구분자로 사용.
#define IS						(BYTE)0x7F	// Item과 입력 데이터 사이의 구분자로 사용.

#define _TCH_US					US
#define _TCH_FS					FS
#define _TCH_PS					PS
#define _TCH_RS					RS
#define _TCH_IS					IS
#define _TCH_PERIOD				_T('.')					// (.)
#define _TCH_COMMA				_T(',')					// (,)

#define _COMM_GS				US
#define _COMM_FS				FS
#define _COMM_RS				RS
#define _COMM_IS				IS
#define _COMM_CS				PS
*/

#define _G_TCH_GS				(BYTE)0x1D	// 데이터의 시작 의미(Group Separator)
#define _G_TCH_US				(BYTE)0x1F	// 개별의 요소를 분리하는 단위(Unit Separator)
#define _G_TCH_FS				(BYTE)0x1E	// 컨트롤 사이의 구분자로 사용 (Field Separator)
#define _G_TCH_PS				(BYTE)0x0D	// 복수의 KEY Item이 존재할 때 구분자로 사용.
#define _G_TCH_RS				(BYTE)0x0A  // 복수의 레코드가 존재할 때 ROW구분자로 사용.
#define _G_TCH_IS				(BYTE)0x7F	// Item과 입력 데이터 사이의 구분자로 사용.
#define _TCH_PERIOD			_T('.')					// (.)
#define _TCH_COMMA			_T(',')					// (,)

#define _COMM_GS				(BYTE)0x1F	// 개별의 요소를 분리하는 단위(Unit Separator)
#define _COMM_FS				(BYTE)0x1E	// 컨트롤 사이의 구분자로 사용 (Field Separator)
#define _COMM_RS				(BYTE)0x0A  // 복수의 레코드가 존재할 때 ROW구분자로 사용.
#define _COMM_IS				(BYTE)0x7F	// Item과 입력 데이터 사이의 구분자로 사용.
#define _COMM_CS				(BYTE)0x0D	// 복수의 KEY Item이 존재할 때 구분자로 사용.

#define	MEMO_SYMBOL_SIZE		8

// Designer에서 편집된 내용을 OCX에게 적용하도록 알려주는 메세지.
// OCX 또는 Designer가 자신이 Close될때 연결된 Window에게 Close여부를 알려주는 메세지.
//UINT m_uNotifyControlMsg = ::RegisterWindowMessage("NOTIFY_CONTROL_MSG");
enum  NOTIFY_CONTROL_MSG { 
						DESIGNE_TO_CONTROL_CHANGE_NOTIFY =1,
						CONTROL_TO_DESIGNE_CHANGE_NOTIFY,	
						DESIGNE_TO_CONTROL_CLOSE_NOTIFY,	
						CONTROL_TO_DESIGNE_CLOSE_NOTIFY,
						GRID_CODEIMAGE_DROP_NOTIFY,	
						GRID_GETCORE_FROM_HANDLE,	
						GRID_CONTINUE_EDIT,	
						};
// Version
/*****************************************************/
// Version 2 : ITEM_LEN길이값이 20자리에서 30자리로 변경 
// Version 3 : m_pmapRecordInfo 삭제
// Version 4 : ParentColor Property추가 
// Version 5 : 다중트랜사용 Flag추가
// Version 6 : lMaskInfoUnit추가 
// Version 7 : m_byMultiMarketUse 추가
// Version 8 : AutoOrderInfo, NextHeaderUse 추가
// Version 9 : FixedRowCheck 추가, CaptionTextArray추가
// Version 10 : 52527->52529변경 (GX_IDS_CTRL_TEXTFIT->GX_IDS_CTRL_CBS_DROPDOWNLIST)
// Version 11 : 그리드 Row단위별로 폰트지정 정보 
// Version 12 : 그리드 RealItem  추가
/*****************************************************/
#define	DEF_VERSION					MAKELONG(12,1)


#define ITEM_LEN					30					// Item Name길이
#define REAL_ITEM_LEN				20					// Real Item Name길이
#define CAPTION_LEN					32					// Caption최대길이
#define RECORD_NAME_LEN				16					// Record name 최대길이


#define	UNDEFINE_BKCR				-1
#define	MAX_SHOWHIDE_LEN			7
#define	DEF_MAX_DATACOUNT			20					// 최대 데이터 조회건수 

// OgBase Class
#define	DEF_CTRL_SIZE				CSize(500, 400)	
#define	DEF_ROW_COUNT				2
#define	DEF_COLUMN_COUNT			5
#define	DEF_HIDDEN_ROW_COUNT		1
#define	DEF_HIDDEN_COLUMN_COUNT		1
#define	DEF_COLUMN_WIDHT			80
#define	DEF_ROW_HEIGHT				18						// Default Height Row
#define	DEF_TOOLTIP					0

// Grid Class
#define	DEF_HEADER_ROW_COUNT		1
#define	DEF_HEADER_COLUMN_COUNT		0
#define	DEF_FROZEN_ROW_COUNT		1
#define	DEF_FROZEN_COLUMN_COUNT		0
#define	DEF_SUBITEM_COUNT			1
#define	DEF_BLOCK_COUNT				0

#define	TABLE_CELLBORDER_COLORINDEX		4				// 테이블 기본선색
#define	DEF_TABLE_LINE_COLORINDEX		6				// 테이블 셀보더선색
#define	DEF_TOPUPDATE_CELL_COLORINDEX	72				// 그리드 TopUpDate자동갱신 

#define	DEF_ODD_COLORINDEX				72				// 그리드 홀수 블럭색
#define	DEF_EVEN_COLORINDEX				73				// 그리드 짝수 블럭색
#define	DEF_SELCR_INDEX					77				// 그리드 선택 셀 배경색 
#define	DEF_CTRLBORDER_COLORINDEX		78				// 그리드 보더색
#define	DEF_LINE_COLORINDEX				62				// 그리드 기본선색(세로라인)
#define	DEF_BACKGND_COLORINDEX			61				// 그리드 뒷여벽배경색
#define	DEF_HV_LINE_COLORINDEX			66				// 그리드헤더HV선색.
#define	DEF_HEADER_LEFT_COLORINDEX		67				// 그리드헤더여백(왼쪽)선색 

#define	DEF_BKCR_INDEX					70				// 그리드 Body배경색
#define	DEF_TXCR_INDEX					71				// 그리드 Body글자색

#define GRID_CELLBUTTON_COLOR_INDEX		74				// 그리드 셀 버튼배경색.
#define GRID_MEMOCELL_COLOR_INDEX		94				// 메모표시(셀) 배경색.
#define GRID_UP_COLOR_INDEX				88				// 상승색 
#define GRID_DOWN_COLOR_INDEX			89				// 하락색 
#define GRID_FIXEDROW_LINECOLOR_INDEX	79				// 틀고정색 

#define	DEF_FONTBOLD_INDEX				13				// 폰트 인덱스( 굴림체 9 굵게 )

// Base Item
#define	DEF_FONT_INDEX					2				// 기본 폰트 인덱스( 굴림체 9 보통 )
#define	DEF_HALIGN						DT_RIGHT
#define	DEF_VALIGN						DT_VCENTER

// Grid Header 
#define	HEADER_FONT_INDEX				2
#define	HEADER_BKCR_INDEX				64				// 그리드 헤더 배경색
#define	HEADER_TXCR_INDEX				65				// 그리드 헤더 글자색
#define HEADER_3DHILIGHT_INDEX			68				// 그리드 헤더 하이라이트색
#define HEADER_3DSHADOW_INDEX			69				// 그리드 헤더 세도우색

#define	HEADER_HALIGN					DT_CENTER

// Grid & Table Item
#define	DEF_KEY_INDEX					0
#define	DEF_REAL_BKCR_INDEX				2				// 자동업데이터 배경색 
#define	DEF_REAL_TXCR_INDEX				71				// 그리드 Body글자색 
#define	DEF_SPIN_STEP					1
//#define	DEF_BUTTON_COLORINDEX		71
#define	DEF_CELL_DATATYPE				9				// DT_STRING
#define	DEF_CELL_ATTRINDEX				-1
#define	DEF_CELL_ATTROFFSET				-1

// Table Special Color 
#define	TSC_CAPTION_BACK_INDEX			80				// 테이블 캡션 배경색  
//#define	TSC_COLOR_START_INDEX		100
#define	TSC_OVER_BT_HIGH_CRINDEX		82				// 라인롤오버버튼 하일라이트 
#define	TSC_OVER_BT_SHDW_CRINDEX		83				// 라인롤오버버튼 쉐도우
// 호가 그리드 화면에서 사용하는 색 정보 
#define	TSC_HOGA_BUYGRAPH_CRINDEX		141				// 매수 배경색
#define	TSC_HOGA_SALEGRAPH_CRINDEX		151				// 매도 배경색
#define	TSC_OVER_SALEORDER_CRINDEX		84				// 라인롤오버색매도
#define	TSC_OVER_BUYORDER_CRINDEX		85				// 라인롤오버색매수
#define	TSC_OVER_MID_CRINDEX			86				// 라인롤오버색중간배경
#define	TSC_OVER_MIDLINE_CRINDEX		87				// 라인롤오버색라인
//#define	TSC_MENUCELL_BACK_CRINDEX	22

// Fire Event(Script Event)
#define FE_REAL_BEFORE				0x0001	// 실시간데이터 수신처리 전
#define FE_REAL_AFTER       	    0x0002	// 실시간데이터 수신처리 후
#define FE_IMAGE_DRAG				0x0004	// IMAGE Drag Event
#define FE_IMAGE_DROP				0x0008	// IMAGE Drop Event
#define FE_EDIT_NOCLICK				0x0010	// Edit Cell No Click Event
#define FE_BODYROW_ZERO				0x0020	// 런 모드시 그리드Body수를 0로한다.
#define FE_SELECTLIST_NOMOVE		0x0040	// 리스트 선택 모드에서 이동금지 기능 

//#define FE_ONERECORD_DATA			0x0040	// 서브Row디자인에 데이터는 하나씩 처리 
//#define FE_ONECLICK_IGNORE		0x0040	// 종목연계기능 사용일때 DblClick 발생시 OneClick이벤트 무시한다. 
//#define FE_EDIT_DNG_TYPE1			0x0080	// Call 센터용 Edit 컨트롤용 
//#define FE_REALDATA_FILTER		0x0100	// RealData Filter Event
	
//#define FE_CELL_CLICK				0x0010
//#define FE_CELL_SIZING			0x0020	// Tail용 컨트롤에 이벤트를 알려주기 위해.
//#define FE_EDIT_CHANGE			0x0040	// Code Edit Full Event
//#define FE_SPINEDITT_CHANGE		0x0080	// Spin Edit Change
//#define FE_CELL_ENTER				0x0100	// Cell Enter Event
//#define FE_PRESS_DIRECTIONKEY		0x0200	// 방향키를 누른 경우.
//#define FE_ATM_EVENT				0x0800	// ATM Event
//#define FE_AUTORUN_REAL			0x0800	// AutoRealMode
//#define FE_REALDATA_FILTER		0x1000	// RealData Filter Event
//#define FE_RECV_BEFORE			0x2000	//	
//#define FE_RECV_AFTER             0x4000


// 연결 정보로 방법 지정.
#define	FIRE_LINKINFO_NONE			0
#define	FIRE_LINKINFO_DBCLICK		1
#define	FIRE_LINKINFO_ONECLICK		2


// Base Bool Bit Info
#define BASE_BBIT_USE_FORMULA		0x00000001
#define BASE_BBIT_USE_CELL_DATACNVT	0x00000002
#define BASE_BBIT_USE_COL_DATACNVT	0x00000004
#define BASE_BBIT_USE_SELECTCOLOR	0x00000008
#define BASE_BBIT_USE_CODELINK		0x00000010
#define BASE_BBIT_USE_ORDERLINK		0x00000020
// --> [Edit]  안경환 2010/11/20 // 자동가격마스크추가
//#define BASE_BBIT_USE_NUMBERCOL		0x00000040
#define BASE_BBIT_USE_AUTOPRICE		0x00000040		// 자동가격마스킹 셀 존재여부
// <-- [Edit]  안경환 2010/11/20
#define BASE_BBIT_USE_IMAGEBTN		0x00000080
#define BASE_BBIT_USE_NEXTBTN		0x00000100
#define BASE_BBIT_USE_PREBTN		0x00000200
#define BASE_BBIT_USE_HCHARTBONG	0x00000400		// 가로 봉. 
#define BASE_BBIT_USE_VCHARTBONG	0x00000800		// 세로 봉.
#define BASE_BBIT_USE_KEY			0x00001000		// MainKey사용하는 컬럼이 있음.
#define BASE_BBIT_USE_SUBKEY		0x00002000		// SubKey사용하는 컬럼이 있음.
#define BASE_BBIT_USE_TOOLTIP		0x00004000		// Tooltip사용 하는 컬럼 있음. 
#define BASE_BBIT_USE_CELLTIP		0x00008000		// Celltip사용 하는 컬럼 있음. 
#define BASE_BBIT_USE_AMOUNTGRAPH	0x00010000		// 호가 테이블에서 잔량 그래프를 사용하는지의 유무.
#define BASE_BBIT_MMOVE_OVERCHECK	0x00020000		// 테이블에서 OverCell 표시를 위해서 마우스 체크가 필요한지의 유무.
#define BASE_BBIT_USE_CODEDRAG		0x00040000		// CodeDrag 사용 하는 컬럼 있음. 
#define BASE_BBIT_USE_MEMO			0x00080000		// Memo사용 하는 컬럼 있음. 
#define BASE_BBIT_USE_CELLREF		0x00100000		// 참조사용 하는 컬럼 있음. 
#define BASE_BBIT_MMOVE_EPSCHECK	0x00200000		// 호가 테이블에서 셀 강조를 위해서 마우스 체크가 필요한지의 유무.
#define BASE_BBIT_USE_THIRDKEY		0x00400000		// ThirdKey사용하는 컬럼이 있음.
#define BASE_BBIT_NOUSE_HOGAPRICE_FRAME	0x00800000	// 호가가격에 현재가 외곽선 표시유무 
#define BASE_BBIT_NOUSE_HOGAPRICE	0x01000000		// 호가 테이블에 현재가표시유무. 
#define BASE_BBIT_USE_REG_DATACNVT	0x02000000		// Register Cell. 
#define BASE_BBIT_MULTIREC_USE		0x04000000		// 복수 레코드를 사용하는 경우 
#define BASE_BBIT_MULTIMARKET_USE	0x08000000		// 다중시장 지원

//#define BASE_BBIT_USE_DELAYTIMER	0x00400000		// 실시간 Delay Timer 사용.
//#define BASE_BBIT_IS_SPECIALHOGA	0x00100000		// 호가 테이블에 특별한 그리기 처리가 있는 경우 True..
//#define BASE_BBIT_USE_BOTTOM_TAIL	0x10000000		// 하단 합계행 
//#define BASE_BBIT_USE_TOP_TAIL	0x20000000		// 상단 합계행 

// Grid Bool Bit Info
#define BBIT_USE_SCLDWRQST			0x00000001				// SCROLL ACTION
#define BBIT_USE_BLOCKCOLOR			0x00000002				// Grid Block Color 사용 여부.
#define BBIT_USE_VIRTUAL_STEP1		0x00000004				// Column 스타일과 Cell 스타일을 분리.
#define BBIT_USE_VIRTUAL_STEP2		0x00000008				// 스타일을 생성하지 않고 원본 데이타를 그대로 관리(소트, 컬럼 이동 ...등 안됨).
#define BBIT_USE_3DHEADER			0x00000010				// Grid 3D Header 사용 여부.
#define BBIT_USE_SAMEKEY			0x00000020				// MainKey 중복 여부.
#define BBIT_USE_SAMESUBKEY			0x00000040				// SubKey 중복 여부.
#define BBIT_USE_HEADERMOVE			0x00000080				// Grid 헤더 이동 사용 여부.
#define BBIT_USE_SAVE_COLSIZE		0x00000100				// Grid 컬럼 사이즈 정보 저장 여부.
#define BBIT_USE_ROUNDHEADER		0x00000200				// Round Header
#define BBIT_USE_SAMETHIRDKEY		0x00000400				// ThirdKey 중복 여부.


// Grid Bool Bit Info
//#define TBL_BBIT_IS_HOGATABLE	0x0001
//#define TBL_BBIT_USE_HOGASELECT	0x0002
//#define TBL_BBIT_USE_VIRTUAL_STEP1    0x0004


/*----------------------------------------------*/
// 연결정보 문자열 인덱스중 사용자 설정 인덱스.
/*----------------------------------------------*/
// 삼성선물에선 User Link를 사용하지 않는다.
// 연결화면을 띄울때 넘겨줄 정보로 사용한다.
#define USER_LINKTAG_INDEX			1
/*----------------------------------------------*/

// TableLink Item
#define	DEF_LINKROW					0
#define	DEF_LINKCOL					0

// Mask
#define	DEF_MASK_PLACES				0	
#define	IGNORE_MASK_PLACES			15	// 15인 경우는 소수점 이하 처리를 안한다.
#define	DEF_MASK_BITINFO			0
#define	MAX_FIX_LEN					4	// Prefix. Postfix의 최대 길이.

#define MBS_COMMA				0x00000001	// 콤마사용.
#define MBS_ZERONOTDSP          0x00000002	// 0표시안함.
#define MBS_SIGNNOT				0x00000004	// 부호 표시 안함.
#define MBS_SIGNMINUS           0x00000008	// 부호 (-) 만 표시.
#define MBS_SIGNALL             0x00000010	// 부호 (-, +) 항상 표시.
#define MBS_PREFIX				0x00000020	// Prefix 사용.
#define MBS_POSTFIX				0x00000040	// Postfix 사용.
#define MBS_ZERO_TRIMLEFT		0x00000080	// 앞에 0제거.
//--->	
// 세개 중에서 최대 1개만 선택하여 사용(Or) ...관심 종목의 숫자 단위에서만 적용.
// 비트로 할건 아니지만 남는공간 사용.
//#define MBS_NUMUNIT_10		0x00000100	// 숫자 단위 10		: 숫자형 데이타의 끝의 한자리 제거.
//#define MBS_NUMUNIT_100		0x00000200	// 숫자 단위 100	: 숫자형 데이타의 끝의 두자리 제거.
//#define MBS_NUMUNIT_1000		0x00000400	// 숫자 단위 1000	: 숫자형 데이타의 끝의 세자리 제거.
//<--- 
#define MBS_MAKE_ZEROPLACES		0x00000800	// 소수점이하 자리수 처리가 있을시에 원데이타에 소수점이 없을시 정책.
											// (ex) 소수점이하 자리수 2인경우 입력 데이타가 116일때.
											// True : 116.00, False : 1.16

#define MBS_ROUND				0x00001000	// 반올림.
#define MBS_PARENTHESES			0x00002000	// 괄호 사용.
#define MBS_REMAIN_LASTZERO		0x00004000	// MBS_ZERO_TRIMLEFT를 사용시 모든경우가 0일때 마지막 0은 남길여부.
#define MBS_POINT_NODSP			0x00008000	// .이하 값 표시 안하기
#define MBS_NUM_CHANGE			0x00010000	// 무조건 숫자형으로 변환 
#define MBS_NUM_CHAR_K			0x00020000	// 표시영역 부족시 자동 1000으로 나누어서  K 문자열 덧붙이기 


enum DxFormatIndex			//Mask Format Index
{
	dxFmt_Default = 0,		//	Default
	dxFmt_Num,				// 	Numeric
	dxFmt_HHMMSS,			// 	HH:MM:SS
	dxFmt_HHMM,				// 	HH:MM
	dxFmt_MMSS,				// 	MM:SS
	dxFmt_YYYYMMDD,			// 	YYYY/MM/DD
	dxFmt_YYYYMM,			// 	YYYY/MM
	dxFmt_YYMM,				// 	YY/MM
	dxFmt_YYMMDD,			// 	YY/MM/DD
	dxFmt_MMDD,				// 	MM/DD
	dxFmt_ACC,				//	Account(123-12-12345)
	dxFmt_DDHHMM,			// 	DD/HH:MM
	dxFmt_MMDDHHMM,			// 	MM/DD HH:MM
	dxFmt_YYMMDDHHMM,		// 	YY/MM/DD HH:MM
	dxFmt_YYYYMMDD_YYYYMMDD,// 	YYYY/MM/DD~YYYY/MM/DD
	dxFmt_MASK_FORMAT,		//  Mask Format
	dxFmt_USER_FORMAT,		//  User Format
	dxFmt_SYMBOLNAME,		// 	CodeHelpDll을 통해서 심볼 코드에 해당한는 심볼명을 얻는다.
	dxFmt_POSTNUM,          //  우편번호
	dxFmt_TEL_NUM,			// 	전화번호 (02-1234-****)
	dxFmt_ADDSTRING,		//  스트링에 첨자 붙이기
//	dxFmt_TextTrim,			//  데이터 수신시 좌우 Trim
//	dxFmt_CAPTION_TEXT,		// 	캡션문자열
	dxFmt_DecimalToString,  // (해외)Decimal long data -> string 
	dxFmt_LogToString,	    // (해외)log long data -> string 
	dxFmt_GLToSpotString,	// (해외)수신한 GL 데이터를 현물가 계산하여 표시한다( YEN, SWISS... 통화에 대해 )
	dxFmt_SYSDATE,			//	DB 년월일시분초 (2004/10/10 09:10:10)
	dxFmt_SYSTIMESTEMP,		//	DB 년월일시분초.1/1000초(2004/10/10 09:10:10.999)
};

// Tail Grid Type Def
#define TG_NOTUSE				0x00	// 합계행 미사용
#define TG_BOTTOM				0x01	// 하단 합계행(가로 그리드) ,우측 합계행(세로 그리드)  
#define TG_TOP					0x02	// 상단 합계행(가로 그리드) ,좌측 합계행(세로 그리드) 

// Cell Border
#define CBDR_LEFT				0x0001
#define CBDR_RIGHT			    0x0002
#define CBDR_TOP				0x0004
#define CBDR_BOTTOM				0x0008

// Popup Menu 
#define PM_CTRL_DEF				0x0001		// 컨트롤기본
#define PM_COL_SETUP			0x0002		// 컬럼 설정(항목편집)
#define PM_HOAG_FONT_CHANGE		0x0004		// 호가폰트 편집
#define PM_MULTI_COL_SORT		0x0008		// 다중컬럼소트 
#define PM_USER_MENU_SETUP		0x0010		// 사용자지정메뉴허용
#define PM_SCR_INTEREST			0x0020		// 관심화면 팝업용 
#define PM_BATCH_INTEREST		0x0040		// 관심일괄등록 
#define PM_USER_EDIT			0x0080		// 사용자 편집 (임의 추가가능한 메뉴)
#define PM_HOGA_ORDER			0x0100		// 매도/매수/정정취소

//#define PM_EXCEL_EDIT			0x0010		// 컬럼 편집후 엑셀보내기  
//#define PM_LINK_SCR			0x0080		// 연결화면편집
//#define PM_INIT_SIZE			0x0100		// 처음넓이로


// Additional Request
//#define AR_PRICE_STATE				0x0001	// 가격별 정보(미체결,잔고,감시중,주문선택가격)
//#define AR_ORDER_CONCLUSION			0x0002	// 미체결/체결 데이타 요구.
//#define AR_STOCK_STOPLOSS			0x0004	// 주식 Stoploss
//#define AR_STOCK_ORDER_STOPLOSS		0x0008	// 주식 주문 Stoploss
//#define AR_FUTURE_STOPLOSS			0x0010	// 선물 Stoploss
//#define AR_FUTURE_ORDER_STOPLOSS	0x0020	// 선물 주문 Stoploss

// 호가주문 정보표시 플레그 HO_TABLE_ORDERDATA
#define DISP_ORDER_SELECT	0x00000001 	// 선택가격
#define DISP_ORDER_WATCH	0x00000002 	// 감시가격
#define DISP_ORDER_JANGO	0x00000004 	// 잔고
#define DISP_ORDER_MICHE	0x00000008 	// 미체결

// Structure Size
#define LEN_ITEMBITS					sizeof(ITEMBITS)
#define LEN_GRIDBITS					sizeof(GRIDBITS)
#define LEN_TABLEBITS					sizeof(TABLEBITS)
#ifdef FIXLEN_USE
#define LEN_TRANBITS					sizeof(TRANBITS)
#endif
#define LEN_BASEBITS					sizeof(BASEBITS)
#define LEN_INITINFO					sizeof(INITINFO)
#define LEN_OGBASEITEM					sizeof(OGBASEITEM)
#define LEN_GRIDHEADER					sizeof(GRIDHEADER)
#define LEN_GRIDHEADERINFO(cnt)			sizeof(DWORD) + sizeof(short) + (cnt * LEN_GRIDHEADER)
#define LEN_GRIDBODY					sizeof(GRIDBODY)
#define LEN_GRIDBODYINFO(subcnt,cnt)	sizeof(DWORD) + (sizeof(short) * 2) + ((subcnt* cnt) * LEN_GRIDBODY)
#define LEN_TABLECELL					sizeof(TABLECELL)
#define LEN_TABLECELLINFO(cnt)			sizeof(DWORD) + sizeof(short) + (cnt * LEN_TABLECELL)
#define LEN_CELLLINK					sizeof(CELLLINK)
#define LEN_CELLLINKINFO(cnt)			sizeof(DWORD) + sizeof(short) + (cnt * LEN_CELLLINK)
#define LEN_ITEMSIZE					sizeof(ITEMSIZE)
#define LEN_ITEMSIZEINFO(cnt)			sizeof(DWORD) + sizeof(short) + (cnt * LEN_ITEMSIZE)
#define LEN_CELLRANGE					sizeof(CELLRANGE)
#define LEN_CELLRANGEINFO(cnt)			sizeof(DWORD) + sizeof(short) + (cnt * LEN_CELLRANGE)
#define LEN_MASKINFO					sizeof(MASKINFO)
#define LEN_REFERINFO					sizeof(REFERINFO)
#define LEN_GRIDLINE					sizeof(GRIDLINE)
#define LEN_TBLBORDER					sizeof(TBLBORDER)
#define LEN_BORDERINFO					sizeof(BORDERINFO)
#define LEN_RECITEM						sizeof(RECITEM)
#define LEN_REALCONBITS					sizeof(REALCONBITS)
#define LEN_REALCONITEM					sizeof(REALCONITEM)
#define LEN_RECTYPEBITS					sizeof(RECTYPEBITS)
#define LEN_REALRECTYPE					sizeof(REALRECTYPE)
#define LEN_REALCONINFO(reccnt, cnt)	sizeof(DWORD) + sizeof(BYTE) + sizeof(BYTE) + (reccnt * LEN_REALRECTYPE) + (cnt * LEN_REALCONITEM)
#define LEN_NEWREFERBITS				sizeof(NEWREFERBITS)
#define LEN_NEWREFERCON					sizeof(NEWREFERCON)
#define LEN_NEWREFERTYPE(cnt)			(ITEM_LEN+1) + (sizeof(BYTE)*2) + (cnt * LEN_NEWREFERCON) + sizeof(long)

#define LEN_HOGAORDER					sizeof(HOGAORDER)
#define LEN_ORDERSRC					sizeof(ORDERSRC)
#define LEN_USERCELL					sizeof(USERCELL)
#define LEN_USERCELLINFO(cnt)			sizeof(DWORD) + sizeof(short)+ (2*sizeof(int)) + (cnt * LEN_USERCELL)
#define LEN_USERCELL_POS				sizeof(DWORD) + sizeof(short)+ (2*sizeof(int))


//////////////////////////////////////////////////////
// 호가 주문 정의.
#define	ORDER_NO_LEN					6

#define	HOGA_ORDER_TYPE_SALE			1		//매도주문.
#define	HOGA_ORDER_TYPE_BUY				2		//매수주문.
#define	HOGA_ORDER_TYPE_CORRECT			3		//정정주문.
#define	HOGA_ORDER_TYPE_CANCEL			4		//취소주문.
#define	HOGA_TRADE_TYPE_NORMAL			0		//보통.

#define	HOGA_TRADE_TYPE_MARKET			3		//시장가.
#define	HOGA_TRADE_TYPE_CONDITION		5		//조건부지정가.

// Ocx Control Type
enum DXOcxType
{
	dxHGrid,
	dxVGrid,
	dxTable,
	dxDefault
};

// virtual Mode
enum DXVirtualMode
{
	dxVMNone,
	dxVMStep2,			// 가상모드 
	dxVMStep1,
};

// Grid Data Type
enum DXGridDataType
{
	dxGDTTopInsert,			//(0)시간대별(초, 분)데이터 유형 
	dxGDTTopUpdate,			//(1)일별 데이터 유형 
	dxGDTUpdate,			//(2)시세표데이터 유형(동일종목허용불가)
	dxGDTPortfolio,			//(3)관심종목형(동일종목허용)
	dxGDTRolling,			//(4)Rolling 데이터 유형 
	dxGDTCircular,			//(5)순환 데이터 유형 
	dxGDTAppend,			//(6)시세표 Append 데이터 유형
	dxGDT_InFixedKey,		//(7)고정키를 포함한 테이블유형(실시간등록시 사용할 키가 붙박이로 처리되어 있는경우)
	dxGDT_InVariableKey,	//(8)가변키를 포함한 테이블유형(실시간등록시 사용할 키가 수신데이터에 의해 처리되어 있는경우)
	
	dxGDTRealCondition,		//(9)실시간잔고 유형
	dxGDTOrderConclusion,	//(10)실시간미체결 유형
	dxGDTVertInvestor=20,	//(20)세로형 투자자유형
	dxGDTHerzInvestor,		//(21)가로형 투자자유형
	dxGDTVH_Spread,			//(22)가로세로 스프레드유형  
	dxGDTVH_Matrix,			//(23)가로세로 행렬유형  
	dxGDTVH_VertData,		//(24) 테이블에서 가로 데이터 표시
	dxGDTVH_HerzData,		//(25) 테이블에서 세로 데이터 표시

#if FALSE
	/*---------------------------*/
	// 사용안한다.
	dxGDTTopUpdateInsert,	//일별 데이터 유형 
	dxGDTMemoryData,	//입력 조회 메모리 구성용.
	dxGDTFixPortfolio,	//Fixed 관심종목형.
	dxGDTExpPortfolio,	//Expand 관심종목형.
	dxGDTSymmetry,		//대칭형.
	dxGDTInvestor,		//투자자 Type
	dxGDNewsTitle,      //뉴스 타이틀.
	dxGDTNewsContent,   //뉴스 본문.
	/*---------------------------*/
#endif
};

// Grid Special Content
enum DXGridSpecialContent
{
	dxSCNotUse,			// 사용안함. 
	dxSCInvestor,		// 투자자.
	dxSCIntraKeyUpdate,	// 시간대별 키분리시 항상 TopUpdate
	dxSCIntraKeyInsert,	// 시간대별 키분리시 항상 TopInsert
	dxReverse,			// 수신데이터 역순 표시

	/*---------------------------*/
//	// 사용안한다.
//	dxSCPowerNews,		// 파워 포착.
//	dxSCMultiTrade,		// 멀티 거래원(당일주포) 
//	dxSCNewsTitle,      // 뉴스/시황 타이틀.
//	dxSCSpecialNews,    // 재료주 화면. 
	/*---------------------------*/
};

// Option Calculation Cell
// Max 5bit = 30가지 종류 ->6bit = 60가지.
enum DXOpCalcCell
{
	dxOPNone,				//[ 0] 사용안함
	dxOPTimeCol,			//[ 1] 시간컬럼 정보
	dxOPStart,				//[ 2] 시가
	dxOPHigh,				//[ 3] 고가
	dxOPLow,				//[ 4] 저가
	dxOPEnd,				//[ 5] (현재가)종가
	dxOPBasis,				//[ 6] 기준가(전일종가)
	dxOPMaxPrice,			//[ 7] 상한가
	dxOPMinPrice,			//[ 8] 하한가
	dxOPTheory,				//[ 9] OP이론가
	dxOPDelta,				//[10] OP델타
	dxOPGamma,				//[11] OP감마
	dxOPTheta,				//[12] OP세타
	dxOPVega,				//[13] OP베가
	dxOPRho,				//[14] OP로
	dxOPExpPayoff,			//[15] OP만기손익
	dxOPTheoryPayoff,		//[16] OP이론손익
	dxOPEvalPayoff,			//[17] OP평가손익
	dxOPIV,					//[18] OP내제변동성 컬럼
	dxOPTimeVal,			//[19] OP시간가치 컬럼
	dxOPIVVaule,			//[20] OP내제가치 컬럼
	dxOPDiffRate,			//[21] OP 괴리율
	dxOpCalcHoga,			//[22] 호가(전일종가기준 색상반영셀)
	dxGrphMtlColMaxLeft,	//[23] 그래프 (N개의 컬럼 최대값 기준) N개의 컬럼 값중 최대값 기준으로 각각 셀단위 비율을 그래프로 표시한다.
	dxGrphMtlColMaxRight,	//[24] 그래프 (N개의 컬럼 최대값 기준) N개의 컬럼 값중 최대값 기준으로 각각 셀단위 비율을 그래프로 표시한다.
	dxGrphSnglColMaxLeft,	//[25] 그래프 (1개의 컬럼 최대값 기준) 1개의 컬럼 값중 최대값 기준으로 각각 셀단위 비율을 그래프로 표시한다.
	dxGrphSnglColMaxRight,	//[26] 그래프 (1개의 컬럼 최대값 기준) 1개의 컬럼 값중 최대값 기준으로 각각 셀단위 비율을 그래프로 표시한다.
	dxOPResist2,			//[27] 피봇2차저항")	
	dxOPResist1,			//[28] 피봇1차저항")	
	dxOPPivot,				//[29] 피봇")			
	dxOPSupport1,			//[30] 피봇1차지지")	
	dxOPSupport2,			//[31] 피봇2차지지")	
	dxGraphTotRem,			//[32] 총잔량 비율 그래프")	
	dxOpCellQtyTrend,		//[33] 체결추이(TREND)")	
	
	

	

//	dxOPMaxData,		//[21] Progress 최대값지정(Col)
//	dxOPRowMaxData,		//[22] Progress 최대값지정(Row)
//	dxOPCellMaxData,	//[23] Progress One Cell 100%기준
//	dxOpRefAttribute3,	//[25] Attribute3 Refer셀(1262 데이터에 색정보가 있는경우)	
//	dxOpCellQtyTrend,	//[26] 체결추이(Trend)지정셀
//	dxOpCellQtyBlink,	//[27] 체결추이깜박임지정셀
//	dxOpCellForceMinus,	//[28] 음수부호강제지정셀
//	dxRealAccumulateData,//[29] Real 수신시 데이터 누적셀(이전데이터에 수신데이터를 누적한다.)
//	dxOPRealVolume,		  //[35] 실시간데이터 역전 방지용 거래량 지정셀


//	dxOPHogaPayoff,		//[24] 호가계산기-평가손익"
//	dxOPHogaPayoffRate,	//[25] 호가계산기-수익률
//	dxOPHogaReversAttr,	//[26] 호가테이블Attribute반대셀" 
/*
	dxOPATMDataCell,	//[21] ATM데이터 컬럼 정보.  
	dxOPHangSaCell,		//[22] 행사가 컬럼 정보. 
	dxOPRealMinus,		//[23] 실시간 업데이트시 자신의 값과 실시간 값을 뺀값을 가진다. 
	dxOPRealPlus,		//[24] 실시간 업데이트시 자신의 값과 실시간 값을 더한값을 가진다.
	dxOPDate,			//[26] 일자컬럼지정. 
	dxOPMaxData,		//[27] 최대값컬럼지정. 
	dxOPTreeSum,		//[28] 트리 전체 합계값 (+)컬럼지정. 
	dxOPTreeAvg,		//[29] 트리 전체 평균값  컬럼지정. 
	dxOPMaedoCol,		//[30] 매도수 구분(평가손익데이터)
	dxOPCurPrice,		//[31] 현재가 컬럼(평가손익데이터)
	dxOPOrderQty,		//[32] 주문수량 컬럼(평가손익데이터)
	dxOPAvePrice,		//[33] 평균단가 컬럼(평가손익데이터)
	dxOPValue,			//[34] 옵션가치컬럼(옵션종목만해당)
	dxOPProfitrate,		//[35] 수익률컬럼.
*/

};

// Grid Scroll Mode
enum DXScrollMode
{
	dxScrollAuto,
	dxScrollNotUse,
	dxScrollOnlyH,
	dxScrollOnlyV,
	dxScrollAlways,
	dxScrollAutoH,
	dxScrollAutoV,
	dxScrollAwsV_AtH,
	dxScrollAtV_AwsH, 
};

// Grid Line Mode
enum DXLineMode
{
	dxLineBoth,
	dxLineOnlyH,
	dxLineOnlyV,
	dxLineNotUse,
	dxLineBothEx,
};

// Selection Mode
enum DXSelMode
{
	dxSelTable,
	dxSelListSingle,
	dxSelListMulti,
	dxSelOneCell,
	dxSelNone,
	dxSelTableNoneCell,
	dxSelSelOneCell,	
};

// Resize Header Mode
enum DXRszHdrMode
{
	dxRszHdrNotUse,
	dxRszHdrOnlyRow,
	dxRszHdrOnlyCol,
	dxRszHdrBoth,
	dxRszHdrTblResize,
};

// Tooltip Mode
enum DXTooltipMode
{
	dxTtipNotUse,
	dxTtipOnlyTtip,
	dxTtipOnlyMemo,
	dxTtipBoth,
};

// Tooltip Mode
enum DXGridLineStyle
{
	dxLSSolid		= PS_SOLID,
	dxLSDash		= PS_DASH,		/* -------  */	
	dxLSDot			= PS_DOT,		/* .......  */
	dxLSDashDot		= PS_DASHDOT,	/* _._._._  */
};


// 3D Effect (Only Table)
enum DX3DEffect
{
	dx3DNormal,
	dx3DInsert,
	dx3DRaised,
};

// Sort Mode (Only Grid)
enum DXSortMode
{
	dxSortNotUse,
	dxSortNormal,
	dxSortLooping,
};

// FID Flag
enum DXItemFlag
{
	dxItemNotUse,
	dxItemIn,
	dxItemOut,
	dxItemInOut,
};

enum DXResize
{
//	dxResize,
//	dxMove,
	dxRszNone,
	dxRszHOnly,
	dxRszVOnly,
	dxRszBoth,
	
};

// Scroll Action
enum DXSclAct
{
	dxSActDefault,			//사용안함.
	dxSActDwRqst,			//↓조회.
};

// HeaderType
enum DXHeaderType
{
	dxHNormal       = 0,				// Normal
	dxH3DStyle		= 1,				// 3D Style
	dxHRoundStyle   = 2,				// Round Style
};

/////////////////////////////////////////////////////////////////
// Sign Format
#define SF_USE_SALEBUY_COLOR		0x01		// 매도/매수 글자색 사용..
#define SF_USE_BIT_SIGNCOLOR		0x02		// 양수 빨강색 , 음수 검정색 sign Color를 결정.
#define SF_USE_NEGTIV_SIGNCOLOR		0x04		// Sign Bit없이 순수 데이타의 음수/양수/0 여부로 Sign Color를 결정한다.
#define SF_USE_SYMBOL				0x08		// 대비 기호 사용.
#define SF_USE_ATTR_COLOR			0x10		// 전일대비 기호를 Attribute로 사용
#define SF_USE_ATTR_COLOR2			0x20		// 체결량  Attribute를 사용
//#define SF_USE_TEXTNOTTRIM			0x40		// 서비스 조회응답시 Trim무시 
#define SF_USE_TEXTTRIM				0x40		// 서비스 조회응답시 Trim함
#define SF_USE_TEXTCONVERT			0x80		// Text Convert


// Old Sign Format
// 버젼 처리를 위해서 남겨둔다.
enum DXSign
{
	dxSFmtDefault	= 0,		//사용안함.
	dxSFmtSign		= 1,		//Sign Color(앞의 한자리의 부호를 지우는 경우의 부호색 처리)(++/--)
	dxSFmtSymbol	= 2,		//Bitmap Symbol
	dxSFmtSignalMng	= 3,		//Signal Manager
	dxSFmtNtvSign	= 4,		//Sign Color(앞의 한자리의 부호를 지우지 않는 경우의 부호색 처리)(-)
};
/////////////////////////////////////////////////////////////////

// Control Border Style
enum DXCtrlBorder
{
	dxCBdrNone,
	dxCBdrBorder,
	dxCBdr3D,
	dxCBdrBorder3D,
};

// Drag & Drop Mode
enum DXDnDMode
{
	dxDnDNone,				// 사용안함.
	dxImageDrag_Drop,		// 이미지 Drag&Drop시 자신의 컨트롤에서 종목이동 허용 
	dxDnDAll,				// Drag & Drop (Drag시 삭제 안함)
	dxDnDDrag,				// Drag
	dxDnDDrop,				// Drop
	dxDnDExcel,
	dxDnDAll_Del,			// Drag & Drop (Drag시 삭제)
	dxDnDDrag_Del,			// Drag (Drag시 삭제)
};

// 데이타 변환 설정
enum DXRealHLMode
{
	dxRealHLCell,			// 셀단위 변환.
	dxRealHLCol,			// Row단위 변환.
	dxRealHLNone,			// 변환 하지 않음.
	dxRealHLRegCell,		// Register Cell.
};

// Code Input Control에서 띄울 종목 다이얼로그의 Catalog Mode
enum DXCodeCatalog
{
	dxCatalogFuture,		// 선물.
	dxCatalogOption,		// 옵션.
	dxCatalogStock,			// 주식.
};

////////////////////////
//호가 테이블 전용.
// 매수/매도 주문 셀.
enum DXHogaOrder
{
	dxHGOdrNone,		// None
	dxHGOdrSale,		// Sale Order
	dxHGOdrBuy,			// Buy Order
};

// 호가 막대 그래프.
enum DXHogaGraph
{
	dxHGGrpNone,		// None
	dxHGGrpOwner,		// Graph Start Cell
	dxHGGrpSlave,		// Graph End Cell
	dxHGGrpInOneCell,	// Graph In One Cell
};
/*

// 매수/매도 강조 셀.
enum DXHogaEmphasis
{
	dxHGEpsNone,		// None
	dxHGEpsSale,		// Sale Emphasis
	dxHGEpsBuy,			// Buy Emphasis
	dxHGEpsBoth,		// Both
};
*/

enum GridCellType
{
	Header = 0,
	TgtBody,
	Body,
	Error,
};	

// 컬럼숨기기 정보. 
enum DXColumnHide
{
	dxColShow			= 0,		// 보이기. 
	dxColSystemHide,				// 시스템 숨기기. 
	dxColUserHide,					// 사용자 Show/Hide
};

/*****************************************************************************/
// 실시간 조건 관련.
#define RC_CONDITION_MAX				30
#define RC_VALUE_MAX					10

enum RCOperator
{
	RCOP_EQUAL = 0,
	RCOP_NOT_EQUAL,
	RCOP_DATA_CMP,
	RCOP_AWS_TRUE,
};	

enum RCDefAction
{
	RCDEFAC_INSERT = 0,
	RCDEFAC_ADD,
	RCDEFAC_IGNORE,
};

enum RCAction
{
	RCAC_TOPINSERT = 0,
	RCAC_INSERT,
	RCAC_ADD,
	RCAC_BTMADD,
	RCAC_UPDATE,
	RCAC_DELETE,
	RCAC_IGNORE,
	RCAC_NEXTCON,
	RCAC_UPDATE_INSERT,
};	
/*****************************************************************************/

/*****************************************************************************/
// New 참조 관련
#define NR_CONDITION_MAX				50
#define NR_SYMBOL_MAX					20

enum NRCmpType
{
	NRCT_CONSTANT = 0,			//0:상수 비교.
	NRCT_ITEM,					//1:아이템의 값비교.
	NRCT_CR_COPY,				//2:Target Item의 색상 복사(대체문자는 해당 안됨)
};	

enum NROperator
{
	NROP_GREAT = 0,				// >
	NROP_LESS,					// <
	NROP_EQUAL,					// =
	NROP_GREAT_EQUAL,			// >=
	NROP_LESS_EQUAL,			// <=
	NROP_NOT_EQUAL,				// !=
};	
/*****************************************************************************/
////////////////////////
// Cell Control ID
enum DXCellCtrl
{
	dxCtrlEdit		 = 52512,	//GX_IDS_CTRL_EDIT					(Edit Control)
	dxCtrlStatic	 = 52513,	//GX_IDS_CTRL_STATIC				(Static Text)
	dxCtrlPushBtn	 = 52514,	//GX_IDS_CTRL_PUSHBTN				(Push Button)
	dxCtrlSpin		 = 52519,	//GX_IDS_CTRL_SPINEDIT				(Spin Edit)
	dxCtrlHeader	 = 52520,	//GX_IDS_CTRL_HEADER				(Header)
	dxCtrlCheck		 = 52523,	//GX_IDS_CTRL_CHECKBOX3D			(Checkbox, 3d-Effect)
//	dxCtrlCombo		 = 52527,	//GX_IDS_CTRL_TEXTFIT				(combobox only allows text input which fits the choice list)
	dxCtrlCombo		 = 52529,	//GX_IDS_CTRL_CBS_DROPDOWNLIST		
	dxCtrlProgress	 = 52536,	//GX_IDS_CTRL_PROGRESS				(Progress Control)
	dxCtrlPWEdit	 = 52537,	//GX_IDS_CTRL_PASSWORD				(Password Edit Control)
	dxCtrlJMCombo	 = 61448,	//GX_IDS_CTRL_JMCOMBO				(JMCombo(관심종목용))
	dxCtrlCodeInput  = 61449,	//GX_IDS_CTRL_CELLCODEINPUT			(Code Input Control(선물/옵션용))
	dxCtrlAmountPrgs = 61450,	//GX_IDS_CTRL_AMOUNTPROGRESS		(호가 테이블의 잔량 비교 프로그래스)
	dxCtrlHBongChart = 61451,	//GX_IDS_CTRL_HBONGCHART			(가로 Bong 챠트.)
	dxCtrlBMPBtn	 = 61452,	//GX_IDS_CTRL_NEWBTMBUTTON			(Bitmap Button.)
	dxCtrlVBongChart = 61453,	//GX_IDS_CTRL_VBONGCHART			(세로 Bong 챠트.)
	dxCtrlComboBoxEx  = 61454,	//GX_IDS_CTRL_COMBOX_EX				(ComboBox_Ex Control)
	dxCtrlDateTime    = 52543,	//GX_IDS_CTRL_DATETIME 
};

//#define BASIC_CTRLCNT	3	// static, edit, header 
static int ControlID[] ={ 
							dxCtrlStatic,
							dxCtrlEdit,
							dxCtrlHeader,
							dxCtrlCombo,
							dxCtrlCheck,
							dxCtrlSpin,
							dxCtrlPushBtn,
							dxCtrlProgress,
							dxCtrlPWEdit,
							/*dxCtrlJMCombo,*/
							dxCtrlCodeInput,
							/*dxCtrlAmountPrgs,*/
							dxCtrlHBongChart,
							dxCtrlBMPBtn,
							dxCtrlVBongChart,
							dxCtrlComboBoxEx,
							dxCtrlDateTime,
						};


#endif//_OGDESIGNDEFINE_H_
