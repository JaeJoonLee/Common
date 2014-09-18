//===============================
// Data Type
//===============================

#ifndef __KSCOMMON_H__
#define __KSCOMMON_H__

#define	_IMG_UNCHECK		0
#define	_IMG_CHECK			1

//#if !defined(_WIN32_WCE)
#pragma pack(push, 1)
//#endif

//*****************************************************************************
// Revision By:  김 창하 Revision Day:  2003년10월21일
// Comments: 연결정보 정의값  (LinkInfoMenuProc.h)
//*****************************************************************************
#define ID_LINKMENU					33000						// 연결정보 메뉴 ID시작부
#define LINKINFO_START				1
#define	LINKINFOR_MAX				40							// 연결정보 등록 개수

// 화면 오른쪽 마우스 관심 그룹 리스트 연결 
#define UM_PORTFOLIO_REG		   43106					//  Main의 RMenu
#define ID_KWANSIM_LGROUP_START    33501
#define ID_KWANSIM_LGROUP_END      33600

//====================================
// structure 정의
//====================================
///// form window관련
#define	UM_REALDATA_TIMEOUT		WM_USER + 11			// 화면에 실시간 데이타 페인팅 처리를 위한 메세지
#define SD_SELECTDLG			WM_USER + 998
#define SD_SELECT_FID			WM_USER + 999

#define UM_BEGIN_WAITCURSOR		WM_USER + 701	// FormMng에 모래시계 시작을 알리는 메세지
#define UM_END_WAITCURSOR		WM_USER + 702	// FormMng에 모래시계 끝을 알리는 메세지
#define UM_FORMMNG_INITDATA		WM_USER + 703	// FormMng에 초기화 데이터를 셋하는 메세지

#define UM_REAL_INTERVAL		WM_USER + 705	// RealTime 인터벌을 설정한다.
#define UM_FORMMNG_REALREG		WM_USER + 706	// FormMng에 각 컨트롤의 Real Handle을 등록한다.
#define UM_SETFOCUS_FORM		WM_USER + 707	// FORM이 포커스를 가졌을때 FormMng에 보내는 메세지
#define UM_SIZE_AFTER			WM_USER + 708	// 폼의 리사이징시 처리용
#define UM_REPLACE_FORM			WM_USER + 709	// 폼의 Replace 처리용
#define UM_FORMINFO				WM_USER + 710	// DLL용 폼의 정보 처리용

#define UM_GETREQUESTDATA		WM_USER + 711	// DLL용 그리드의 FID정보를 구하는 메세지

#define UM_ADDCHILDFORM			WM_USER + 712	// FORM의 CHILDFORM 추가
#define UM_INSERT_FORM			WM_USER + 713   // View에 FORM추가
#define UM_DELETE_FORM			WM_USER + 714   // View에 FORM삭제
#define UM_DELETE_OLDFORM		WM_USER + 715   // View에 FORM삭제

#define UM_LAYOUTFORM_DISPATCH  WM_USER + 716   
#define	UM_SHOW_LAYOUT			WM_USER + 717
#define	UM_GET_LAYOUTID			WM_USER + 718
#define	UM_GET_FORMCOUNT		WM_USER + 719
#define	UM_GET_MXNINFO			WM_USER + 720

#define UM_DLLVIEW_REG			WM_USER + 721
#define UM_LEFTCLICK			WM_USER + 722

#define UM_LAYOUTTAB_CHANGE     WM_USER + 723
#define	UM_KEYACTION			WM_USER + 724
#define UM_FORMMSGBOX			WM_USER + 725
#define UM_GET_LAYOUTSCREENTYPE	WM_USER + 726
#define UM_ISLAYOUTHIDE			WM_USER + 727
#define UM_LAYOUTTAB_INDEX		WM_USER + 728
// --> [Edit]  BT.Jung 2007/01/08
#define UM_LAYOUTTAB_CHANGEEX   WM_USER + 729		// UM_LAYOUTTAB_CHANGE와 동일하나 화면아이디로 변경한다
// <-- [Edit]  BT.Jung 2007/01/08

#define	UM_CALL_LINKINFO_MSG	WM_USER + 730		// 동일그룹간 연결정보 데이타 전송을 위한 메세지(Form--> MDIChildWnd)
#define	UM_CALL_FORMLINK_MSG	WM_USER + 731		// 동일그룹간 연결정보 데이타 전송을 위한 메세지(Form--> MDIChildWnd)
#define UM_SETLINKINFO_MSG		WM_USER + 732		// 연결정보 데이타 저장(Form --> View )
#define UM_TABLINKTAGDATA_MSG	WM_USER + 733		// 종합화면 탭화면 연결정보 취득 
#define UM_SETLOCALTOGLOBAL_MSG	WM_USER + 734		// 탭화면 연결정보를 글로벌연결정보에 설정 

#define UM_MN_FORM				WM_USER + 735		// 폼의 M*N 처리용

#define ID_REALDATA_PAINT		WM_USER + 750		// Real Data를 표시하라는 메시지
#define	UD_TIMER_VALUE			100					// 0.2초 (타이머 시간)

#define UM_CTRLSIZE				WM_USER + 760		// 
#define UM_GETRECORDSIZE		WM_USER + 7600		// 

// Start 2006-05-17 오후 2:50:41	남 상윤
#define WM_SET_BTNIMAGESIZE		WM_USER + 770		// 버튼의 이미지에 따른 크기를 조절하도록 한다.
#define WM_SET_RESIZE_BY_TEXT	WM_USER + 771		// 컨트롤의 폭(크기)를 텍스트 길이에 따라 조절하도록 한다.
#define WM_SET_GROUPRADIO_SIZE	WM_USER + 770		// WM_SET_BTNIMAGESIZE와 번호를 같게 한다. 한 함수를 타게 하기 위해 
													// 라디오 그룹 크기에 따라 크기를 조절한다.
// End   2006-05-17 오후 2:50:41	남 상윤

#define UM_SCREENNXNFORM_DISPATCH  WM_USER + 772   



#define	SD_SELFIDDLG			1
#define	SD_SELMULTIFIDDLG		2
#define SD_LINKDLG				3

//------ Fid Flag 
#define		FIDFLAG_NOTUSE		0
#define		FIDFLAG_IN			1
#define		FIDFLAG_OUT			2
#define		FIDFLAG_INOUT		3


//------ Appearance Style
#define		APPEARSTYLE_NONE			0
#define		APPEARSTYLE_CONCAVE			1
#define		APPEARSTYLE_CONVEX			2
#define		APPEARSTYLE_BORDER			3

//------ Default Font Index
#define		DEF_FONTINDEX				2
#define		DEF_ACTIVE_FONTINDEX		2  // 탭 컨트롤에서 활성 탭 기본폰트 Index 2006-04-12 오후 8:45:11	 남상윤 

// 화면타이틀 버튼
#define DEF_TITLEBUTTON    _T("10011111111")
#define DEF_TITLE_CNT	   11

// 필요하면 사이즈 변경
#define		CTRLNAME_LEN	20			// 기존에 만든 화면 정보 저정으로 바꾸지 못함..
#define		PROPNAME_LEN	24		
#define		VALUE_LEN		24		
#define		SCREENID_LEN	9			
#define		SCREENNAME_LEN	30
#define		VERSION_LEN		2
#define		SCRGUBUN_LEN	2
#define		DOMAINID_LEN	4
#define		CTRLTYPE_LEN	2
#define		TITLEBTN_LEN	DEF_TITLE_CNT		//  9 -> DEF_TITLE_CNT [박정일] 2010/10/20
#define		SCRTYPE_LEN		40
#define		TABNAME_LEN		40		
// --> [Edit] 임민수 2010/05/14
#define		MODIFIED_USER_LEN 10	//최종수정한사람
// <-- [Edit] 임민수 2010/05/14
#define		TRNAME_LEN		8
#define		RQNAME_LEN		20
#define		TRCODE_LEN		20      // TRCODE 대신 서비스명사용 SERVICE_NAME_LEN
#define		RECORDNAME_LEN	10      // 레코드명   

#define		ITEMNAME_LEN	25         

#define		ITEMCAPTION_LEN	40   //caption length
#define		FX_TRCODE_LEN	6    //trcode length
// 통신 올리기 위한 헤더 정보
#define		FG_EMPTY		0x00		// Clear


// --> [Edit]  박 경 규 2006/04/06
#define		RUN_EXTENSION	_T(".map")		// RunFile extension
#define		TRAN_EXTENSION	_T(".tranmap")	// RunFile extension
// <-- [Edit]  박 경 규 2006/04/06

//===============================
// 파일 포맷 정보
//===============================

#define  MAP_FILE		_T("01")
#define  LAYOUT_FILE	_T("02")

#define	 MAPFILE_VER	_T("02")
#define  LAYOUT_VER		_T("01")

// 화면파일 헤더
typedef struct _MAPFILE_HEADER_ST
{
	BYTE	ucCorp;
//	char	sVer[VERSION_LEN+1];
	short   nMajorVer;
	short   nMinorVer;
	char	sGubun[SCRGUBUN_LEN+1];
	char	sDomainID[DOMAINID_LEN+1];
	char	sScreenID[SCREENID_LEN+1];
	char	sScreenName[SCREENNAME_LEN+1];
	DWORD	nContext_len;
	// --> [Edit]  임민수 2010/05/14
	char	sModified_user[MODIFIED_USER_LEN+1];	//최종수정한사람
	char	sAdministrator[MODIFIED_USER_LEN+1];	//화면관리자
	// <-- [Edit]  임민수 2010/05/14
}MAPFILE_HEADER;

// 화면의 컨트롤 기본정보
typedef struct _MAPFILE_CTRLINFO_ST
{
	char		nTabIndex;
	char		sType[CTRLTYPE_LEN+1];
	short		nXpos;
	short		nYpos;
	short		nWidth;
	short		nHeight;
	char		sParentName[CTRLNAME_LEN+1];
	char		sCtrlName[CTRLNAME_LEN+1];
}MAPFILE_CTRLINFO;	

// 실행파일용 컨트롤의 프로퍼티 정보
typedef struct _PRECOMFILE_PROPERTY_ST		
{
	char		sCtrlName[CTRLNAME_LEN+1];	
	char		sProperty[PROPNAME_LEN+1];  
	BYTE		nVarType;
	char		sValue[VALUE_LEN+1];		
}PRECOMFILE_PROPERTY;


// 맵파일용 컨트롤의 프로퍼티 정보
typedef struct _PRECOMFILE_PROPERTY_MAP
{
	char		sCtrlName[CTRLNAME_LEN+1];
	char		sProperty[PROPNAME_LEN+1];
	BYTE		nVarType;
	int			nDataLen;
}PRECOMFILE_PROPERTY_MAP;

typedef struct _LALYOUTFILE_HEADER_ST
{
	BYTE	ucCorp;
//	char	sVer[VERSION_LEN+1];
	short   nMajorVer;
	short   nMinorVer;
	char	sGubun[SCRGUBUN_LEN+1];
	char	sDomainID[DOMAINID_LEN+1];
	char	sScreenID[SCREENID_LEN+1];
	char	sScreenName[SCREENNAME_LEN+1];
	short	nWidth;
	short	nHeight;
	short	nInitFocus;
	char	szTitleButton[TITLEBTN_LEN+1];
	BYTE	ucMsgDisplay;
	char	szLayoutType[SCRTYPE_LEN+1];
	BYTE    ucSplitFix;
	char	cFirstLayoutType;
	char    szReserve[6];
	// --> [Edit]  임민수 2010/05/14
	char	sModified_user[MODIFIED_USER_LEN+1];	//최종수정한사람
	char	sAdministrator[MODIFIED_USER_LEN+1];	//화면관리자
	// <-- [Edit]  임민수 2010/05/14
}LAYOUT_HEADER;

typedef struct _LALYOUTFILE_DATA_ST
{
	char	nParentID;
	char	nLayoutID;
	BYTE	nCol;
	BYTE	nRow;
	short	nWidth;
	short	nHeight;
	BYTE	nLayoutType;
	BYTE	nFirstTab;
	char	sScreenID[SCREENID_LEN+1];
	BYTE    nOutline;
}LAYOUT_DATA;

// 종합화면 탭구성 정보
typedef struct _LAYOUTFILE_TABDATA_ST
{
	short	nLayoutID;
	short	nParentTabIndex;
	short	nTabCount;
}LAYOUT_TABDATA;

// 종합화면 탭정보(색상)
typedef struct _LAYOUT_TAB_COLOR
{
	BYTE	ucUnLoad;
	short	nBackColor;
	short	nForeColor;
	short	nActiveColor;
	short	nActiveForeColor;
	short	nMarginColor;
	short	nActiveTagColor;
	short	nLineColor;
}LAYOUT_TABCOLOR;

// 종합화면 탭 기본정보
typedef struct _LAYOUT_TAB_PROPERTY
{
	short	nLayoutID;
	BYTE	ucPosition;
	short	nTabHeight;
	short   nTabWidth;
	BYTE	ucEqualDivision;
	BYTE	ucSelTabFixed;
	BYTE	ucHAlign;
	BYTE	ucVAlign;
	short	nFontIndex;
	short	nTabCnt;
	LAYOUT_TABCOLOR* pTabColor;
	short	nTabStyle;
}LAYOUT_TABPROPERTY;

class KS_SCREEN_INFO : public CObject
{
public:
	KS_SCREEN_INFO()
	{
		memset(m_sScreenID, 0x0, sizeof(m_sScreenID));
		memset(m_sTabName, 0x0, sizeof(m_sTabName));

		m_nFuncKey = 0;
		m_nWidth = -1;
		m_nHeight = -1;
	};

	char	m_sScreenID[SCREENID_LEN+1];
	char	m_sTabName[TABNAME_LEN+1];		// TabName과 FileName은 같이 사용되는 경우가 없음.

	unsigned int m_nFuncKey;
	short	m_nWidth;
	short	m_nHeight;	
};

#define TR_NORMAL	0
#define TR_FID		1
//#define TR_BASE21	2
#define TR_WMCA		2

#define RECORD_SINGLE		1
#define RECORD_ARRAY		2

// 공통사용 헤더 정보항목
typedef struct  _TR_HEADER_PROP
{
	// TRHeader에 세트할 항목
	BYTE	ucType;				// 0 - 일반트랜, 1 - FID
	BYTE	ucCompress;
	BYTE	ucEncrypt;
	BYTE    ucAttribute;
	BYTE	ucBinary;
	BYTE    ucRegReal;
	BYTE    ucCertificate;
	BYTE	ucDataHeader;
	BYTE	ucDataHeaderCnt;
	BYTE    ucReserved;				// 여유분
	BYTE	ucDataType;				//0-시세 데이터, 1-주문 데이터
}TR_HEADER_PROP;

// 통신헤더정보( 고객사에 따라 수정 가능)
typedef struct  _TR_HEADER_V1
{
	TR_HEADER_PROP	HeaderProp;
	BYTE			ucRqID;					// MinorID --> WINDY
	short			nTimeOut;	
	BYTE			ucBaseTR[7];
	BYTE			ucProcessGB;
	BYTE			ucBizGB;
}TR_HEADER_V1;


typedef struct  _TR_HEADER
{
	BYTE			ucEncrypt;		// 암호화 여부.
	BYTE			ucPublic;		// 공개키 인증여부.
	BYTE			ucCompress;		// 압축여부...
	short			nRqID;			// MinorID --> WINDY
	short			nTimeOut;	
	short			nDataheader;	// 데이타 헤더 사용유무	
}TR_HEADER;

// 통신설정 정보
typedef struct _COMM_INFO_V1
{
	char		sRQName[TRNAME_LEN+1];
	char		sTRName[TRNAME_LEN+1];
	char		sTRCode[TRCODE_LEN+1];
	TR_HEADER_V1 TrHeader;	
	BYTE		nInCtrlCnt;
	BYTE		nOutCtrlCnt;
	char**		sInCtrlName;
	char**		sOutCtrlName;
}COMM_INFO_V1;

typedef struct _COMM_INFO
{
	char		sRQName[RQNAME_LEN+1];
	char		sTRName[TRNAME_LEN+1];
	char		sTRCode[TRCODE_LEN+1];
	TR_HEADER	TrHeader;	
	BYTE		nInCtrlCnt;
	BYTE		nOutCtrlCnt;
	char**		sInCtrlName;
	char**		sOutCtrlName;
}COMM_INFO;

//  [5/25/2006 activeinfo] 
typedef struct tagFnCommInfo
{
	int		nRqNameIndex;	// Name String Table의 Offset값
	int		nTrCodeIndex;   // Name String Table의 Offset값
	int		nRecordIndex;	// Name String Table의 Offset값
	int		nItemIndex;		// Name String Table의 Offset값
	char	cTranType;
	char    cInOutType;

	int		nDataStartOffset;
	int		nLength;
	int		nDataType;
	short	nstrLen;
	short   nDecimalPoint;
	BYTE	nCtrlCount;
	int     *pControlWnd;		// 해당 Control의 Window PTR
	int		*nArrControlIndex;	// 할당되어진 Control List들....
} FNCOMMINFO;


typedef struct tagCommTrInfo
{
	int     nEncrypt;
	int		nCompress;
	int		nPublic;
	int		nTimeOut;
	BYTE	cDestination;
// --> [Edit]  이용준 2008/03/12
//	int		nDataheader; 
//	char	data_trcode[10+1]; //UD_DATAHEADER_TR_LEN + 1];		// 턱시도 
// --> [Edit]  이용준 2008/06/03
	char	data_jobchk[1+1];								// 작업구분
// <-- [Edit]  이용준 2008/06/03
// <-- [Edit]  이용준 2008/03/12
} FNTRINFO;

// TR레코드 정보
typedef struct _RQRP_RECORD
{
	char		sRecordName[TRCODE_LEN+RECORDNAME_LEN+1];
	BYTE		nCtrlCnt;
	char**		sCtrlName;
}RQRP_RECORD;

// TR통신설정 정보
typedef struct _TRCOMM_INFO_V1
{
	char		  sRQName[TRNAME_LEN+1];
	char		  sTRName[TRNAME_LEN+1];
	char		  sTRCode[TRCODE_LEN+1];
	BYTE		  nInRecordCnt;
	RQRP_RECORD*  pInRecord;
	BYTE		  nOutRecordCnt;
	RQRP_RECORD*  pOutRecord;
}TRCOMM_INFO_V1;

typedef struct _TRCOMM_INFO
{
	char		  sRQName[RQNAME_LEN+1];
	char		  sTRName[TRNAME_LEN+1];
	char		  sTRCode[TRCODE_LEN+1];
	BYTE		  nInRecordCnt;
	RQRP_RECORD*  pInRecord;
	BYTE		  nOutRecordCnt;
	RQRP_RECORD*  pOutRecord;
}TRCOMM_INFO;

typedef struct _TRMEM_ITEMINFO_ST
{
	BYTE    ucDataType;
	short   nDataLen;
	char    nAttribute;
}TRMEM_ITEMINFO;

// 통신 레코드 구조
typedef struct _TRMEM_RECORDINFO_ST
{
	char			sName[TRCODE_LEN+RECORDNAME_LEN+1];
	BYTE			ucGubun;
	BYTE			ucType;
	short			nRepeat;
	BYTE			nRepeatLen;
	BYTE			nItemCnt;
	short			nRecordSize;
	TRMEM_ITEMINFO* pItem;
}TRMEM_RECORDINFO;

// 통신 메모리 구조
typedef struct _TRANMEM_INFO__ST
{
	char			sTrCode[TRCODE_LEN+1];
	TR_HEADER_PROP	HeaderProp;

	BYTE			nInRecordCnt;
	BYTE			nOutRecordCnt;

	TRMEM_RECORDINFO*	pInRecord;
	TRMEM_RECORDINFO*	pOutRecord;
}TRANMEM_INFO;

#define	UD_DESC_LEN			30		// 설명 길이
#define UD_FID_LEN			5		// FID길이

//////////////////////////////////////
// TR정보파일 헤더(*.trn)
typedef struct _TRFILE_HEADER_ST
{
	char			sTrCode[TRCODE_LEN+1];
	char			sTrName[UD_DESC_LEN+1];
	TR_HEADER_PROP	HeaderProp;
}TR_HEADERINFO;

// TR파일 레코드
typedef struct _TRFILE_RECORDINFO_ST
{
	char	sName[TRCODE_LEN+RECORDNAME_LEN+1];
	char	sDesc[UD_DESC_LEN+1];
	BYTE	ucGubun;
	BYTE	ucType;
	short	nItemCnt;
	short	nRepeat;
	short	nRepeatLen;
}TR_RECORDINFO;

// TR파일 아이템
typedef struct _TRFILE_ITEMINFO_ST
{
	char    sFieldName[ITEMNAME_LEN+1];
	char	sTip[ITEMCAPTION_LEN+1];
	char	sForeignTip[ITEMCAPTION_LEN+1];
	BYTE    ucDataType;
	BYTE    ucKeyType;
	short   nDataLen;
}TR_ITEMINFO;

typedef struct _TRTEST_RECORDINFO_ST
{
	char			sName[TRCODE_LEN+RECORDNAME_LEN+1];
	BYTE			ucGubun;
	BYTE			ucType;
	short			nRepeat;
	short			nRepeatLen;
	short			nItemCnt;
	int				nRecordSize;
	TR_ITEMINFO*	pItem;
}TRTEST_RECORDINFO;

typedef struct _TR_TESTINFO
{
	TR_HEADERINFO		Header;
	short				nInRecordCnt;
	TRTEST_RECORDINFO*	pInRecord;
	short				nOutRecordCnt;
	TRTEST_RECORDINFO*  pOutRecord;
}TR_TESTINFO;

/////////////////////////////////////
// 리얼 아이템
typedef struct _REAL_ITEMINFO_ST
{
	char    sFieldName[ITEMNAME_LEN+1];
// --> [Edit]  이용준 2007/02/15
// 아래 두가지중 하나로 통일할 것
	char	sTip[ITEMCAPTION_LEN+1];
	char	sName[ITEMCAPTION_LEN+1];
// <-- [Edit]  이용준 2007/02/15
	char	sForeignTip[ITEMCAPTION_LEN+1];
	BYTE    ucDataType;
	BYTE    ucKeyType;
	short   nDataLen;
}REAL_ITEMINFO;

// 실시간 데이터 포맷
typedef struct _REAL_FORMAT
{
	BYTE			ucRealtype;
	char			sTrCode[FX_TRCODE_LEN+1];
// --> [Edit]  이용준 2007/02/15
// 아래 두가지중 하나로 통일할 것
	char			sTip[ITEMCAPTION_LEN+1];
	char			sName[ITEMCAPTION_LEN+1];
// <-- [Edit]  이용준 2007/02/15
	char			sForeignTip[ITEMCAPTION_LEN+1];
	char			nIsFid;
	short			nItemCnt;
	REAL_ITEMINFO*	pItem;
}REAL_FORMAT;

// 폼연결정보 
#define		TAG_LEN		20
typedef struct _FORM_LINKINFO
{
	char		sTag[TAG_LEN+1];
	BYTE		nCtrlCnt;
	char**		sCtrlName;
}FORM_LINKINFO;

// --> [Edit:이용준] 2004-08-26 
// 레포트 파일 헤더
//typedef struct _RPTFILE_HEADER_ST
//{
//	char	sVer[VERSION_LEN+1];
//	char	sDomainID[DOMAINID_LEN+1];
//	char	sReportID[SCREENID_LEN+1];
//}RPTFILE_HEADER;
// <-- [Edit:이용준] 2004-08-26 

/*-------------------------------*/
//Real Index 관리 (2004.09.30 Hong~~)
typedef struct tag_REAL_ITEMINDEX
{
	WORD nDataLen;
	WORD nIndex;
	char nAttrIndex;

}REAL_ITEMINDEX;
/*-------------------------------*/

//=================================================
// 다른 컨트롤이나 다이알로그에 전달하기 위한 정보
//=================================================
struct SD_NOTIFY
{
	CString		m_strSource;
	int			m_nSourceCode;
	CString		m_strReturn;
	int			m_nReturnCode;
};

// 컨트롤 연결정보
#define LINK_TAG_LEN	20
struct LINK_INFO
{
	char		sTag[LINK_TAG_LEN+1];
	char		sCtrlName[CTRLNAME_LEN+1];	
	BYTE		ucFlag;						// 0x01 - Get, 0x02 - Put, 0x04 - Real
};

//===============================
//===============================
 
typedef struct _GRID_CONTROL
{
	LPTSTR		strTitleName;				// 타이틀명
	int			nColWidth;					// Cell폭
	int			nColAlign;					// Cell정렬
	BOOL		bCheck;						// 체크박스인가?
}GRIDCONTROL;

class CReplaceInfo
{
public:
	CString strScreenID;
	CString strInitData;
	BOOL	bResize;
};

// 돌려보기와 트리 OCX간의 통신용.
enum  NOTIFY_MSG_ROTATOR_TREE_OCX { 
						ROTATOR_TO_TREE_INIT_NOTIFY = 1,
						TREE_TO_ROTATOR_CHANGE_NOTIFY,
						TREECOMBO_TO_TREE_INIT_NOTIFY,
						TREE_TO_TREECOMBO_CHANGE_NOTIFY,
						};

// 자료타입
#define DT_CHAR				0	// char(8bit)
#define DT_BYTE				1	// unsigned char(8bit)
#define DT_SHORT			2	// int16
#define DT_WORD				3	// unsigned int16
#define DT_LONG				4	// int32
#define DT_DWORD			5	// unsigned int32
#define DT_FLOAT			6	 
#define DT_DOUBLE			7	
#define DT_INT64			8	// __int64(64bit int)
#define DT_STRING			9	// 일반 텍스트
#define DT_STRINGNUM		10	// 숫자형 텍스트(우측정렬)
#define DT_INT				11	// int
#define DT_DATE				12	// 날짜형

#define DT_CHAR_VAL			'0'	// char(8bit)
#define DT_BYTE_VAL			'1'	// unsigned char(8bit)
#define DT_SHORT_VAL		'2'	// int16
#define DT_WORD_VAL			'3'	// unsigned int16
#define DT_LONG_VAL			'4'	// int32
#define DT_DWORD_VAL		'5'	// unsigned int32
#define DT_FLOAT_VAL		'6'	 
#define DT_DOUBLE_VAL		'7'	
#define DT_INT64_VAL		'8'	// __int64(64bit int)
#define DT_STRING_VAL		'9'	// 일반 텍스트
#define DT_STRINGNUM_VAL	'10'	// 숫자형 텍스트(우측정렬)
#define DT_INT_VAL			'11'	// int
#define DT_DATE_VAL			'12'	// 날짜형


#define KW_PARTITION		"!"	// 관심종목 구분자
/*
// --> [Edit]  권도성 2006/08/16
typedef struct	tagKwDataInfo
{
	long			m_lPrc;				// 매매단가
	long			m_lQty;				// 수량
//	long			m_lBookMarkColor;	// 북마크색
//	long			m_lVolumn;			// 거래량이상
//	long			m_lCondColor;		// 조건색
//	CString			m_strUpPrice;		// 현재가이상
//	CString			m_strDownPrice;		// 현재가이하	

	CString			m_strCode;			// 종목코드
	CString			m_strName;			// 종목명
	CString			m_strJangGb;		// 장구분
} KwDataInfo;
*/
// --> [Edit]  권도성 2006/08/16

// --> [Edit]  권도성 2006/12/13
// 관심그룹 트리정보

#include "afxtempl.h"
/*
class CKwTreeDataInfo : public CObject
{
public:
	CKwTreeDataInfo() {}
	virtual ~CKwTreeDataInfo() {}

public:
	CString			m_StrName;				// 트리명
	DWORD			m_dwData;
	CString			m_strCode;
};

class CKwTreeInfo : public CTypedPtrArray<CPtrArray, CKwTreeDataInfo*>
{
public:
	CKwTreeInfo() {}
	virtual ~CKwTreeInfo() { RemoveKwTreeInfo(); }

	inline void RemoveKwTreeInfo()
	{
		CKwTreeDataInfo* pKwTreeDataInfo = NULL;
		for( int i = GetSize()-1; i >= 0; i-- )
		{
			pKwTreeDataInfo = (CKwTreeDataInfo*)GetAt(i);
			delete pKwTreeDataInfo;
			pKwTreeDataInfo = NULL;
		}
		RemoveAll();
	}

	CString m_strName;
	DWORD	m_dwData;
};
typedef CTypedPtrMap <CMapStringToOb, CString, CKwTreeInfo*> CKwTreeInfoMap;
*/
// --> [Edit]  권도성 2006/12/13

// --> [Edit]  권도성 2007/03/05
#define COMM_SEPERATOR			"+"	// 통신구분자
#define COMM_SEPERATOR_SUB		'+'	// 통신구분자
// --> [Edit]  권도성 2007/03/05

//#if !defined(_WIN32_WCE)
#pragma pack(pop)
//#endif


enum DXKeyCodeUseType
{
	dxNotUse,			// 사용안함 
	dxMainKey			// KeyCode사용 
};

// 각 컨트롤별 버전 정보를 정의한 정보 
#define	DEF_FORM_VERSION				MAKELONG(6	,1)

#endif	// __KSCOMMON_H__
