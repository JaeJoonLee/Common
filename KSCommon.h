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
// Revision By:  �� â�� Revision Day:  2003��10��21��
// Comments: �������� ���ǰ�  (LinkInfoMenuProc.h)
//*****************************************************************************
#define ID_LINKMENU					33000						// �������� �޴� ID���ۺ�
#define LINKINFO_START				1
#define	LINKINFOR_MAX				40							// �������� ��� ����

// ȭ�� ������ ���콺 ���� �׷� ����Ʈ ���� 
#define UM_PORTFOLIO_REG		   43106					//  Main�� RMenu
#define ID_KWANSIM_LGROUP_START    33501
#define ID_KWANSIM_LGROUP_END      33600

//====================================
// structure ����
//====================================
///// form window����
#define	UM_REALDATA_TIMEOUT		WM_USER + 11			// ȭ�鿡 �ǽð� ����Ÿ ������ ó���� ���� �޼���
#define SD_SELECTDLG			WM_USER + 998
#define SD_SELECT_FID			WM_USER + 999

#define UM_BEGIN_WAITCURSOR		WM_USER + 701	// FormMng�� �𷡽ð� ������ �˸��� �޼���
#define UM_END_WAITCURSOR		WM_USER + 702	// FormMng�� �𷡽ð� ���� �˸��� �޼���
#define UM_FORMMNG_INITDATA		WM_USER + 703	// FormMng�� �ʱ�ȭ �����͸� ���ϴ� �޼���

#define UM_REAL_INTERVAL		WM_USER + 705	// RealTime ���͹��� �����Ѵ�.
#define UM_FORMMNG_REALREG		WM_USER + 706	// FormMng�� �� ��Ʈ���� Real Handle�� ����Ѵ�.
#define UM_SETFOCUS_FORM		WM_USER + 707	// FORM�� ��Ŀ���� �������� FormMng�� ������ �޼���
#define UM_SIZE_AFTER			WM_USER + 708	// ���� ������¡�� ó����
#define UM_REPLACE_FORM			WM_USER + 709	// ���� Replace ó����
#define UM_FORMINFO				WM_USER + 710	// DLL�� ���� ���� ó����

#define UM_GETREQUESTDATA		WM_USER + 711	// DLL�� �׸����� FID������ ���ϴ� �޼���

#define UM_ADDCHILDFORM			WM_USER + 712	// FORM�� CHILDFORM �߰�
#define UM_INSERT_FORM			WM_USER + 713   // View�� FORM�߰�
#define UM_DELETE_FORM			WM_USER + 714   // View�� FORM����
#define UM_DELETE_OLDFORM		WM_USER + 715   // View�� FORM����

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
#define UM_LAYOUTTAB_CHANGEEX   WM_USER + 729		// UM_LAYOUTTAB_CHANGE�� �����ϳ� ȭ����̵�� �����Ѵ�
// <-- [Edit]  BT.Jung 2007/01/08

#define	UM_CALL_LINKINFO_MSG	WM_USER + 730		// ���ϱ׷찣 �������� ����Ÿ ������ ���� �޼���(Form--> MDIChildWnd)
#define	UM_CALL_FORMLINK_MSG	WM_USER + 731		// ���ϱ׷찣 �������� ����Ÿ ������ ���� �޼���(Form--> MDIChildWnd)
#define UM_SETLINKINFO_MSG		WM_USER + 732		// �������� ����Ÿ ����(Form --> View )
#define UM_TABLINKTAGDATA_MSG	WM_USER + 733		// ����ȭ�� ��ȭ�� �������� ��� 
#define UM_SETLOCALTOGLOBAL_MSG	WM_USER + 734		// ��ȭ�� ���������� �۷ι����������� ���� 

#define UM_MN_FORM				WM_USER + 735		// ���� M*N ó����

#define ID_REALDATA_PAINT		WM_USER + 750		// Real Data�� ǥ���϶�� �޽���
#define	UD_TIMER_VALUE			100					// 0.2�� (Ÿ�̸� �ð�)

#define UM_CTRLSIZE				WM_USER + 760		// 
#define UM_GETRECORDSIZE		WM_USER + 7600		// 

// Start 2006-05-17 ���� 2:50:41	�� ����
#define WM_SET_BTNIMAGESIZE		WM_USER + 770		// ��ư�� �̹����� ���� ũ�⸦ �����ϵ��� �Ѵ�.
#define WM_SET_RESIZE_BY_TEXT	WM_USER + 771		// ��Ʈ���� ��(ũ��)�� �ؽ�Ʈ ���̿� ���� �����ϵ��� �Ѵ�.
#define WM_SET_GROUPRADIO_SIZE	WM_USER + 770		// WM_SET_BTNIMAGESIZE�� ��ȣ�� ���� �Ѵ�. �� �Լ��� Ÿ�� �ϱ� ���� 
													// ���� �׷� ũ�⿡ ���� ũ�⸦ �����Ѵ�.
// End   2006-05-17 ���� 2:50:41	�� ����

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
#define		DEF_ACTIVE_FONTINDEX		2  // �� ��Ʈ�ѿ��� Ȱ�� �� �⺻��Ʈ Index 2006-04-12 ���� 8:45:11	 ������ 

// ȭ��Ÿ��Ʋ ��ư
#define DEF_TITLEBUTTON    _T("10011111111")
#define DEF_TITLE_CNT	   11

// �ʿ��ϸ� ������ ����
#define		CTRLNAME_LEN	20			// ������ ���� ȭ�� ���� �������� �ٲ��� ����..
#define		PROPNAME_LEN	24		
#define		VALUE_LEN		24		
#define		SCREENID_LEN	9			
#define		SCREENNAME_LEN	30
#define		VERSION_LEN		2
#define		SCRGUBUN_LEN	2
#define		DOMAINID_LEN	4
#define		CTRLTYPE_LEN	2
#define		TITLEBTN_LEN	DEF_TITLE_CNT		//  9 -> DEF_TITLE_CNT [������] 2010/10/20
#define		SCRTYPE_LEN		40
#define		TABNAME_LEN		40		
// --> [Edit] �ӹμ� 2010/05/14
#define		MODIFIED_USER_LEN 10	//���������ѻ��
// <-- [Edit] �ӹμ� 2010/05/14
#define		TRNAME_LEN		8
#define		RQNAME_LEN		20
#define		TRCODE_LEN		20      // TRCODE ��� ���񽺸��� SERVICE_NAME_LEN
#define		RECORDNAME_LEN	10      // ���ڵ��   

#define		ITEMNAME_LEN	25         

#define		ITEMCAPTION_LEN	40   //caption length
#define		FX_TRCODE_LEN	6    //trcode length
// ��� �ø��� ���� ��� ����
#define		FG_EMPTY		0x00		// Clear


// --> [Edit]  �� �� �� 2006/04/06
#define		RUN_EXTENSION	_T(".map")		// RunFile extension
#define		TRAN_EXTENSION	_T(".tranmap")	// RunFile extension
// <-- [Edit]  �� �� �� 2006/04/06

//===============================
// ���� ���� ����
//===============================

#define  MAP_FILE		_T("01")
#define  LAYOUT_FILE	_T("02")

#define	 MAPFILE_VER	_T("02")
#define  LAYOUT_VER		_T("01")

// ȭ������ ���
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
	// --> [Edit]  �ӹμ� 2010/05/14
	char	sModified_user[MODIFIED_USER_LEN+1];	//���������ѻ��
	char	sAdministrator[MODIFIED_USER_LEN+1];	//ȭ�������
	// <-- [Edit]  �ӹμ� 2010/05/14
}MAPFILE_HEADER;

// ȭ���� ��Ʈ�� �⺻����
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

// �������Ͽ� ��Ʈ���� ������Ƽ ����
typedef struct _PRECOMFILE_PROPERTY_ST		
{
	char		sCtrlName[CTRLNAME_LEN+1];	
	char		sProperty[PROPNAME_LEN+1];  
	BYTE		nVarType;
	char		sValue[VALUE_LEN+1];		
}PRECOMFILE_PROPERTY;


// �����Ͽ� ��Ʈ���� ������Ƽ ����
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
	// --> [Edit]  �ӹμ� 2010/05/14
	char	sModified_user[MODIFIED_USER_LEN+1];	//���������ѻ��
	char	sAdministrator[MODIFIED_USER_LEN+1];	//ȭ�������
	// <-- [Edit]  �ӹμ� 2010/05/14
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

// ����ȭ�� �Ǳ��� ����
typedef struct _LAYOUTFILE_TABDATA_ST
{
	short	nLayoutID;
	short	nParentTabIndex;
	short	nTabCount;
}LAYOUT_TABDATA;

// ����ȭ�� ������(����)
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

// ����ȭ�� �� �⺻����
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
	char	m_sTabName[TABNAME_LEN+1];		// TabName�� FileName�� ���� ���Ǵ� ��찡 ����.

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

// ������ ��� �����׸�
typedef struct  _TR_HEADER_PROP
{
	// TRHeader�� ��Ʈ�� �׸�
	BYTE	ucType;				// 0 - �Ϲ�Ʈ��, 1 - FID
	BYTE	ucCompress;
	BYTE	ucEncrypt;
	BYTE    ucAttribute;
	BYTE	ucBinary;
	BYTE    ucRegReal;
	BYTE    ucCertificate;
	BYTE	ucDataHeader;
	BYTE	ucDataHeaderCnt;
	BYTE    ucReserved;				// ������
	BYTE	ucDataType;				//0-�ü� ������, 1-�ֹ� ������
}TR_HEADER_PROP;

// ����������( ���翡 ���� ���� ����)
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
	BYTE			ucEncrypt;		// ��ȣȭ ����.
	BYTE			ucPublic;		// ����Ű ��������.
	BYTE			ucCompress;		// ���࿩��...
	short			nRqID;			// MinorID --> WINDY
	short			nTimeOut;	
	short			nDataheader;	// ����Ÿ ��� �������	
}TR_HEADER;

// ��ż��� ����
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
	int		nRqNameIndex;	// Name String Table�� Offset��
	int		nTrCodeIndex;   // Name String Table�� Offset��
	int		nRecordIndex;	// Name String Table�� Offset��
	int		nItemIndex;		// Name String Table�� Offset��
	char	cTranType;
	char    cInOutType;

	int		nDataStartOffset;
	int		nLength;
	int		nDataType;
	short	nstrLen;
	short   nDecimalPoint;
	BYTE	nCtrlCount;
	int     *pControlWnd;		// �ش� Control�� Window PTR
	int		*nArrControlIndex;	// �Ҵ�Ǿ��� Control List��....
} FNCOMMINFO;


typedef struct tagCommTrInfo
{
	int     nEncrypt;
	int		nCompress;
	int		nPublic;
	int		nTimeOut;
	BYTE	cDestination;
// --> [Edit]  �̿��� 2008/03/12
//	int		nDataheader; 
//	char	data_trcode[10+1]; //UD_DATAHEADER_TR_LEN + 1];		// �νõ� 
// --> [Edit]  �̿��� 2008/06/03
	char	data_jobchk[1+1];								// �۾�����
// <-- [Edit]  �̿��� 2008/06/03
// <-- [Edit]  �̿��� 2008/03/12
} FNTRINFO;

// TR���ڵ� ����
typedef struct _RQRP_RECORD
{
	char		sRecordName[TRCODE_LEN+RECORDNAME_LEN+1];
	BYTE		nCtrlCnt;
	char**		sCtrlName;
}RQRP_RECORD;

// TR��ż��� ����
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

// ��� ���ڵ� ����
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

// ��� �޸� ����
typedef struct _TRANMEM_INFO__ST
{
	char			sTrCode[TRCODE_LEN+1];
	TR_HEADER_PROP	HeaderProp;

	BYTE			nInRecordCnt;
	BYTE			nOutRecordCnt;

	TRMEM_RECORDINFO*	pInRecord;
	TRMEM_RECORDINFO*	pOutRecord;
}TRANMEM_INFO;

#define	UD_DESC_LEN			30		// ���� ����
#define UD_FID_LEN			5		// FID����

//////////////////////////////////////
// TR�������� ���(*.trn)
typedef struct _TRFILE_HEADER_ST
{
	char			sTrCode[TRCODE_LEN+1];
	char			sTrName[UD_DESC_LEN+1];
	TR_HEADER_PROP	HeaderProp;
}TR_HEADERINFO;

// TR���� ���ڵ�
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

// TR���� ������
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
// ���� ������
typedef struct _REAL_ITEMINFO_ST
{
	char    sFieldName[ITEMNAME_LEN+1];
// --> [Edit]  �̿��� 2007/02/15
// �Ʒ� �ΰ����� �ϳ��� ������ ��
	char	sTip[ITEMCAPTION_LEN+1];
	char	sName[ITEMCAPTION_LEN+1];
// <-- [Edit]  �̿��� 2007/02/15
	char	sForeignTip[ITEMCAPTION_LEN+1];
	BYTE    ucDataType;
	BYTE    ucKeyType;
	short   nDataLen;
}REAL_ITEMINFO;

// �ǽð� ������ ����
typedef struct _REAL_FORMAT
{
	BYTE			ucRealtype;
	char			sTrCode[FX_TRCODE_LEN+1];
// --> [Edit]  �̿��� 2007/02/15
// �Ʒ� �ΰ����� �ϳ��� ������ ��
	char			sTip[ITEMCAPTION_LEN+1];
	char			sName[ITEMCAPTION_LEN+1];
// <-- [Edit]  �̿��� 2007/02/15
	char			sForeignTip[ITEMCAPTION_LEN+1];
	char			nIsFid;
	short			nItemCnt;
	REAL_ITEMINFO*	pItem;
}REAL_FORMAT;

// ���������� 
#define		TAG_LEN		20
typedef struct _FORM_LINKINFO
{
	char		sTag[TAG_LEN+1];
	BYTE		nCtrlCnt;
	char**		sCtrlName;
}FORM_LINKINFO;

// --> [Edit:�̿���] 2004-08-26 
// ����Ʈ ���� ���
//typedef struct _RPTFILE_HEADER_ST
//{
//	char	sVer[VERSION_LEN+1];
//	char	sDomainID[DOMAINID_LEN+1];
//	char	sReportID[SCREENID_LEN+1];
//}RPTFILE_HEADER;
// <-- [Edit:�̿���] 2004-08-26 

/*-------------------------------*/
//Real Index ���� (2004.09.30 Hong~~)
typedef struct tag_REAL_ITEMINDEX
{
	WORD nDataLen;
	WORD nIndex;
	char nAttrIndex;

}REAL_ITEMINDEX;
/*-------------------------------*/

//=================================================
// �ٸ� ��Ʈ���̳� ���̾˷α׿� �����ϱ� ���� ����
//=================================================
struct SD_NOTIFY
{
	CString		m_strSource;
	int			m_nSourceCode;
	CString		m_strReturn;
	int			m_nReturnCode;
};

// ��Ʈ�� ��������
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
	LPTSTR		strTitleName;				// Ÿ��Ʋ��
	int			nColWidth;					// Cell��
	int			nColAlign;					// Cell����
	BOOL		bCheck;						// üũ�ڽ��ΰ�?
}GRIDCONTROL;

class CReplaceInfo
{
public:
	CString strScreenID;
	CString strInitData;
	BOOL	bResize;
};

// ��������� Ʈ�� OCX���� ��ſ�.
enum  NOTIFY_MSG_ROTATOR_TREE_OCX { 
						ROTATOR_TO_TREE_INIT_NOTIFY = 1,
						TREE_TO_ROTATOR_CHANGE_NOTIFY,
						TREECOMBO_TO_TREE_INIT_NOTIFY,
						TREE_TO_TREECOMBO_CHANGE_NOTIFY,
						};

// �ڷ�Ÿ��
#define DT_CHAR				0	// char(8bit)
#define DT_BYTE				1	// unsigned char(8bit)
#define DT_SHORT			2	// int16
#define DT_WORD				3	// unsigned int16
#define DT_LONG				4	// int32
#define DT_DWORD			5	// unsigned int32
#define DT_FLOAT			6	 
#define DT_DOUBLE			7	
#define DT_INT64			8	// __int64(64bit int)
#define DT_STRING			9	// �Ϲ� �ؽ�Ʈ
#define DT_STRINGNUM		10	// ������ �ؽ�Ʈ(��������)
#define DT_INT				11	// int
#define DT_DATE				12	// ��¥��

#define DT_CHAR_VAL			'0'	// char(8bit)
#define DT_BYTE_VAL			'1'	// unsigned char(8bit)
#define DT_SHORT_VAL		'2'	// int16
#define DT_WORD_VAL			'3'	// unsigned int16
#define DT_LONG_VAL			'4'	// int32
#define DT_DWORD_VAL		'5'	// unsigned int32
#define DT_FLOAT_VAL		'6'	 
#define DT_DOUBLE_VAL		'7'	
#define DT_INT64_VAL		'8'	// __int64(64bit int)
#define DT_STRING_VAL		'9'	// �Ϲ� �ؽ�Ʈ
#define DT_STRINGNUM_VAL	'10'	// ������ �ؽ�Ʈ(��������)
#define DT_INT_VAL			'11'	// int
#define DT_DATE_VAL			'12'	// ��¥��


#define KW_PARTITION		"!"	// �������� ������
/*
// --> [Edit]  �ǵ��� 2006/08/16
typedef struct	tagKwDataInfo
{
	long			m_lPrc;				// �ŸŴܰ�
	long			m_lQty;				// ����
//	long			m_lBookMarkColor;	// �ϸ�ũ��
//	long			m_lVolumn;			// �ŷ����̻�
//	long			m_lCondColor;		// ���ǻ�
//	CString			m_strUpPrice;		// ���簡�̻�
//	CString			m_strDownPrice;		// ���簡����	

	CString			m_strCode;			// �����ڵ�
	CString			m_strName;			// �����
	CString			m_strJangGb;		// �屸��
} KwDataInfo;
*/
// --> [Edit]  �ǵ��� 2006/08/16

// --> [Edit]  �ǵ��� 2006/12/13
// ���ɱ׷� Ʈ������

#include "afxtempl.h"
/*
class CKwTreeDataInfo : public CObject
{
public:
	CKwTreeDataInfo() {}
	virtual ~CKwTreeDataInfo() {}

public:
	CString			m_StrName;				// Ʈ����
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
// --> [Edit]  �ǵ��� 2006/12/13

// --> [Edit]  �ǵ��� 2007/03/05
#define COMM_SEPERATOR			"+"	// ��ű�����
#define COMM_SEPERATOR_SUB		'+'	// ��ű�����
// --> [Edit]  �ǵ��� 2007/03/05

//#if !defined(_WIN32_WCE)
#pragma pack(pop)
//#endif


enum DXKeyCodeUseType
{
	dxNotUse,			// ������ 
	dxMainKey			// KeyCode��� 
};

// �� ��Ʈ�Ѻ� ���� ������ ������ ���� 
#define	DEF_FORM_VERSION				MAKELONG(6	,1)

#endif	// __KSCOMMON_H__
