// Copyright�� 2003 Korea Sorimachi Co.,Ltd. All Rights Reserved. 
//***************************************************************************
// File Name : KHResource.h
// Date      : 
// Creation  : 
// Update    :
// Comment   : ����ȭ�鿡�� ����ϴ� ID ����
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

// �ʱ� ���޴������� ������ �׸� ���ǿ�
typedef struct	tagFORMMNG_INIT
{
	short	nCreateGB;		// ȭ�� ����(0: �Ϲ�, 1: ��ȭ��)
	short	nScreenGB;		// ȭ������� �ʱ����� ������ ���п�(0: �Ϲ�, 1: ����� ����ȭ��)
	short	nCreateType;	// ȭ�� ���� ����(0: �Ϲ�, 1: ������������ ȭ��)
	short	nResize;		// ��Ʈ �������� ����
	short	FontRate;		// �ʱ� ��Ʈ ����
	short	nTabHeight;		// ��ȭ���ΰ�� ���� ����
	short	nMapType;		// ȭ�� Ÿ��(1: �Ϲ�, 2:����)
	short	nFixedFontResize;// ���� ��Ʈ�� ȭ�� ����(0, ���� 1:������)

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
	POINT			pt;				// ����Ǵ� ����
	char			szCode[33];		// �巡�� ����Ÿ
	char			szAcctNo[9];	// ���¹�ȣ
	CStringArray	arDataList;		// ���������� 
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
	short	m_nWidth;				// ���� ��
	short	m_nHeight;				// ���� ����
	short	m_nMaxWidth;			// �ִ� ��
	short	m_nMaxHeight;			// �ִ� ����
	BOOL	m_bMsgDisplay;			// �޼��� ���� ǥ�ÿ���

#if !defined(_WIN32_WCE)
	char	m_szTitleButton[11+1];	// Ÿ��Ʋ �� ��ư ����
	char	m_szScreenType[40+1];	// ȭ������ ���� ex) 1;5,6;4,5,6
	char	m_szMXN[5+1];			// ex) 3,2
#else
	TCHAR	m_szTitleButton[11+1];	// Ÿ��Ʋ �� ��ư ����
	TCHAR	m_szScreenType[40+1];	// ȭ������ ���� ex) 1;5,6;4,5,6
	TCHAR	m_szMXN[5+1];			// ex) 3,2
#endif
} FORMINFO;


//typedef struct	tagSK_ErrorInfo
//{
//	TCHAR	m_erType[10];			// ���а�(���г���)
//	TCHAR	m_erTRCode[5];			// ���� TRCode
//	TCHAR	m_erScrCode[4];			// ���� ȭ���ȣ
//	TCHAR	m_erTitle[40];			// ���� ����
//	TCHAR	m_erContext[200];		// ���� ����
//} SK_ERRORINFO;


//// --> [Edit]  ���� �� 2008/04/01
//typedef struct	tagSM_SIGNALMSGINFO
//{
//	TCHAR	m_sgType[2+1];			//	- ��ȣ����		: ��ȣ �󼼺з�
//	TCHAR	m_sgTime[6+1];			//	- �߻��ð�		: HH:MM:SS
//	TCHAR	m_sgSeqno[8+1];			//	- �Ϸù�ȣ
//	TCHAR	m_sgCodeGb[1+1];		//  - 1:�ڽ���,2:�ڽ���,3:��������,4:ELW
//	TCHAR	m_sgCode[8+1];			//	- �����ڵ�		: �ֽ�(1), ����(2)/�ɼ�(3), ��������(4)
//	TCHAR	m_sgContext[512+1];		//	- ��ȣ����		: ����Ÿ��Ʋ / ���ǳ����
//	TCHAR	m_sgGubun[1+1];			//	- �ŵ��� ����	: �Ϲ�(1) / �ż�(2) / �ŵ�(3)
//	TCHAR	m_sgBlink[2+1];			//	- ��ȣ�Ӽ�		: ������ Ƚ��
//	TCHAR	m_sgContinue[1+1];		//	- ��ȣ�Ӽ�		: ��������
//	TCHAR	m_sgPriority[2+1];		//	- ��ȣ�Ӽ�		: �켱���� 
//	TCHAR	m_sgIcon[2+1];			//	- ��ȣ�Ӽ�		: ǥ��Icon Index
//	TCHAR	m_sgBugaInfo[10+1];		//	- �ΰ�����		: DRFN���� ������ ��ȣ�� ��ȣ��������
//} SM_SIGNALMSGINFO;
//// <-- [Edit]  ���� �� 2008/04/01

//// --> [Edit]  ������ 2008/04/25
//typedef struct	tagSIGNALORDERSINFO
//{
//	long    hDLLWnd;				//	 ȣ���� ��Ʈ�� �ڵ�
//	TCHAR	szWindName[8+1];		// - ��ȣ�̸� ("�ֽĽü�", "���ɽü�", "���ɽ�ž", "���ǰ˻�" .....)
//	TCHAR	szSignalgb[2+1];		// - ��ȣ���� ("��", "��" .....)
//	TCHAR	szPopgb[1+1];			// - �˾�Type(0:�̽���, 1:�˸�â, 2:�ֹ�â,  4:�ڵ��ֹ�)
//	TCHAR	szAcctno[11+1];			// - ���¹�ȣ
//	TCHAR	szCode[12+1];			// - �����ڵ�
//	TCHAR	szLoangb[1+1];			// - �ſ뱸��(0:����, 1:�ſ�)
//	TCHAR	szMemegb[1+1];			// - �Ÿű���(1:�ŵ�, 2:�ż�, 3:����, 4:���, 5:�ſ�ŵ�, 6:�ſ�ż� )
//	TCHAR	szOrdgb[2+1];			// - �ֹ�����(���밡, ���尡,...)
//	TCHAR	szOrdqtygb[1+1];		// - �ֹ���������(0:����, 1:�ݾ�, 2:�ŵ����ɼ���%)
//	TCHAR	szOrdqty[15+1];			// - �ֹ�����
//	TCHAR	szOrdprcgb[1+1];		// - �ֹ��ܰ�����(0:������...(�ε���))
//	TCHAR	szOrdprc[7+1];			// - �ֹ��ܰ�
//	TCHAR	szOrdRow[3+1];			// - ���õ� (��ž �ɸ�) ROW
//	TCHAR	szLoanDate[8+1];		// - ��������
//	TCHAR	szLoanType[1+1];		// - ���ⱸ��	(0:�ڱ�, 1:����)
//	TCHAR	szMsg[512+1];			// - ����MSG
//} SIGNALORDERSINFO;
//// <-- [Edit]  ������ 2008/04/25

/////////////////////////////////////////////////////////////////////////////

typedef	struct tagKSCDIALOGCREATE
{
	long	nFormHwnd;				// ȣ���� ���� �ڵ�
	char	szFileName[10];			// ȣ���� ȭ���8���� 9�ڸ��� ����(Ȯ���� ����)
	char	strTitle[41];			// Ÿ��Ʋ�� ������(������ ȭ�����������.)
	int     nDlgStyle;				// 0:DoMoal 1: Modalless
	int		nCaptionFlg;			// 0: No Caption, 1:Yes Cation
	int		nPosition;				// 0: ȣ��� ���콺 ��ġ �»�
									// 1: ��Ʈ�� �� ������ �߾�
									// 2: ��Ʈ�� �¿� ������ �߾�
									// 3: ȣ��ȭ�� �߾�
									// 4: ������ �߾�
									// 5: Ư�� ��ġ
									// 6: ���콺 ��ġ
	int		nReSize;				// ������ ���� ����
	int		nAutoClose;				// �������� Ŭ���� �ڵ� Close
	HWND    hCtrlWnd;				// ȣ���� ��Ʈ�� �ڵ�
	int		nLeftPos;               // ǥ���� ���� ��ġ
	int		nTopPos;				// ǥ���� �� ��ġ
	long    nRQID;					// ��ȸ���� ID
	char	sData[256];
}KSCDIALOGCREATE;

class CScreenLinkMenu
{
public:
	int		nTitleShowHide;			// Ÿ��Ʋ ǥ�� ����
	int		nTab;					// �� ǥ�� ����
	int		nTabShowHide;			// �� ǥ�� ǥ�� ����
	int		nSDIStyle;				// �������� ����(0:MDIchild, 1: ��������)
	int		nVirtureIndex;			// ����ȭ��ǥ�� ����(nVirtureIndex < 0: �޴� üũ, 0�̻��̸�:üũ����)
	CStringArray saSystemMenu;		// �ý��� ���� ���� �޴� ����Ʈ
	CStringArray saUserMenu;		// ����� ��� ���� �޴� ����Ʈ
};

class CSubTabDragCreate
{
public:
	CString		strScreenID;		// ȭ���ȣ
	CPoint		pt;					// ��ǥ

	CString     strTabName;			// Tab �̸�.
	CString     strJCode;			// �����ڵ�
};

#pragma pack(pop)


// í�ϵ� ȭ�� ���� ����
#define	CHILD_NORMAL		0
#define	CHILD_LINK			1
#define	CHILD_TAB			2
#define	CHILD_AUTO			3
#define	CHILD_COPY			4
#define	CHILD_GDLINK		5

#define	SCREEN_NORMAL		0
#define	SCREEN_USER_SAVE	1


// MDIí�ϵ���  ��������  ����
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

// ���ٿ� �ִ� ��ư�� ���̵�
#define ID_BAR_BUTTON_START			2200
#define ID_BAR_BUTTON_END			2299

// ���ٿ� �ִ� ��ư�� ���̵�
//#define ID_TR_MINISTATE_BTN			2200	// ���� ����� ��ưư
#define		ID_TOOLBARSCRSEARCH		(WM_USER + 3618)	// ȭ��ã���ư
#define		ID_TOOLBAR_CHART		(WM_USER + 3619)	// ���� íƮ
#define		ID_TOOLBAR_ADDTOOL		(WM_USER + 3620)	// ����� ȭ�� ���� �߰�
#define		ID_TOOLBAR_TEXT			(WM_USER + 3621)	// �ؽ�Ʈ ����
#define		ID_TOOLBAR_ICON			(WM_USER + 3622)	// ������ ����
#define		ID_TOOLBAR_SCROLL_UP	(WM_USER + 3623)	// ���� ����
#define		ID_TOOLBAR_SCROLL_DOWN	(WM_USER + 3624)	// ���� ����
#define		ID_TOOLBAR_BANNER		(WM_USER + 3625)	// ���� ����
//LJP 20110801 Start-->
#define		ID_TOOLBAR_ONETEXT		(WM_USER + 3626)	// ���ٷ� ����
#define		ID_TOOLBAR_TWOTEXT		(WM_USER + 3627)	// ���ٷ� ����
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

#define ID_TR_SETUP_BTN				2215	// ����
#define ID_TR_RESIZE				2216	// ȭ��ã��, ȭ������� ������� ��ư  ������
#define ID_TR_APPEND_BTN			2217	// ���ٿ� ǥ�þȵ� ��ư ǥ���ϴ� ��ư
#define ID_TR_SHORT_BTN				2218	// ª�Ժ��� 2011.05 jhj
#define ID_TR_NORMAL_BTN			2219    // ��Ժ��� 2011.05 jhj

#define ID_AUTOHIDE					2220	// �ڵ�����
#define ID_MINIMIZE					2221	// ��� ȭ�� �ּ�ȭ
#define ID_VIRTUAL_BTN1				2222	// ���� ��ũ��
#define ID_VIRTUAL_BTN2				2223
#define ID_VIRTUAL_BTN3				2224
#define ID_VIRTUAL_BTN4				2225

#define ID_SIGNAL_ITEM_BTN			2230	// ��ȣ ������ ��ư
#define ID_SIGNAL_START_BTN			2231
#define ID_SIGNAL_PAUSE_BTN			2232
#define ID_SIGNAL_SETUP_BTN			2233
#define ID_SIGNAL_FOLD_BTN			2234

#define ID_TICKER_SETUP				2235	// ƼĿ ���� ��ư
#define	ID_TICKER_NEWS_BTN			2236
#define	ID_TICKER_NEWS_LISTBOX		2237
#define	ID_TR_DELETE_BTN			2238	// ������� ���� ��ư

#define	ID_MTC_IG_LISTBOX			2500	// �̴�ƼĿ ���ɱ׷� ����Ʈ�ڽ�
#define	ID_MTC_IG_SETUP_BTN			2501	// �̴�ƼĿ ���ɱ׷� ���� ��ư
#define	ID_MTC_JP_LISTBOX			2510	// �̴�ƼĿ ����ü� ����Ʈ�ڽ�
#define	ID_MTC_JP_SEARCH_BTN		2511	// �̴�ƼĿ ����ü� �˻� ��ư
#define	ID_MTC_JP_TITLE_BTN			2512	// �̴�ƼĿ ����ü� ����� ��ư

#define ID_CLOCK_DATE_BTN			2240
#define ID_CLOCK_TIME_BTN			2241

#define ID_CHEGYEL_SETUP			2245
#define ID_CHEGYEL_DELETE			2246
#define ID_CHEGYEL_FOLD				2247

#define ID_TR_MENUCALL_BTN1			2251	// ����� ����ȭ�� ȣ�� ��ư
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

// ���� �׷� ����� ��ư Ŭ���� �˾��޴� ǥ�ÿ� 
#define ID_TB_GROUP_START			2300
#define ID_TB_GROUP_END				2399

#define ID_MYMENU_BTN_START			2400  // �޴� ���ÿ� �޺�	
#define ID_MYMENU_BTN_END			2497  // �޴� ���ÿ� �޺�	

#define ID_MYMENU_BTN_REG_TOOLBAR	2498  // ����ȭ�� å���� �߰�
#define ID_MYMENU_BTN_USERSAVESCR	2499  // ����ȭ�� ���� ���
// ���ٿ��� �˾����� �޴� ȣ���� ���
#define ID_MYMENU_POPUP_START		3000
#define ID_MYMENU_POPUP_END			4000

/****************************************/
/*	Runtime Browser Menu ID Define		*/
/****************************************/
#define IDM_TRMENUSTART					13000	// ���θ޴��� TR�޴� ID ����
#define IDM_TRMENUEND					16000

#define IDM_LAYOUTMENU_START			16001
#define IDM_LAYOUTMENU_END				16100

#define	IDM_USER_TOTAL_SCR_START		16150
#define	IDM_USER_TOTAL_SCR_END			16250

#define	IDM_USER_SCREEN_START			16300
#define	IDM_USER_SCREEN_END				16400

#define	IDM_USER_PROGRAM_START			16501	//	����� ���� �ܺ� ���α׷� �޴� ID ����
#define	IDM_USER_PROGRAM_END			16600


#define IDM_FLAT_MENU_START				17000
#define IDM_FLAT_MENU_END				17999

#define IDM_OPENED_SCREEN_START			18000	// ���� ȭ�� ���
#define IDM_OPENED_SCREEN_END			18499
#define IDM_RUN_RELOGIN					18500	// ���� ��α��� �Ѵ�

#define	IDM_OUTLOOK_MENU			(WM_USER + 111)
#define	IDM_TICKERDIALOGBAR_MENU	(WM_USER + 112)
#define	IDM_TRADEBAR_MENU			(WM_USER + 113)
#define	IDM_VIRTUALSCREENBAR_MENU	(WM_USER + 114)
#define	IDM_WEBBAR_MENU				(WM_USER + 115)
#define	IDM_FULLSCREEN_MENU			(WM_USER + 116)

#define	UM_CHILDSCREEN				(WM_USER + 150)		// �Ϲ� ȭ�� ��ũ��Ʈ�� ȣ���
#define	UM_POPUPSCREEN				(WM_USER + 151)		// �˾� ȭ�� ��ũ��Ʈ�� ȣ���
#define	UM_SMDIALOG_MSG				(WM_USER + 152)		// ���̾�α� ȭ��ó���� �޼��� 
#define	UM_SMDIALOG_MSG2			(WM_USER + 153)		// ���̾�α� ȭ��ó���� �޼���2

#define	UM_KHDIALOG_MSG 			(WM_USER + 154)		// ���̾�α� ȭ��ó����

#define	UM_CHILDSCREENFORNEWSCREEN	(WM_USER + 155)		// ������ �ű�ȭ�� ������

#define	UM_NEW_TAB_DRAG				(WM_USER + 200)
#define	UM_SCREEN_DOWNLOAD			(WM_USER + 201)
#define UM_ALRAM_NOTIFY				(WM_USER + 202)

//������������ == > ����
//���� : ��Ʈ���� ���� ��Ʈ
#define UM_SET_FORMVIEW_FONT_RESIZE (WM_USER + 203)		// wParam -> 0:����, 1:����
//���� == > ������������
//���� : ������ �ڵ� ����
#define UM_SET_FORMVIEW_HWND		(WM_USER + 204)
//���� == > ������������
//���� : ������ �⺻������ ����
#define UM_SET_FORMVIEW_DEF_SIZE	(WM_USER + 205)

// ���� ���ο� ���� �ٴ����� �߰��� childframe�� �ִ����� ������Ų��.
#define UM_SET_FORMMAXSIZE			(WM_USER + 206)

#define UM_KILLUSER					(WM_USER + 207)		// �ٸ� ����ڿ� ���� ���Ḧ ���Ҷ�...

#define UM_GETCOMBOINDEX			(WM_USER + 208)		// �������� �޺��ε��� ����
#define	UM_DND_NOTIFY				(WM_USER + 209)		// �巡�� & ��� ����

#define	UM_GET_OPEN_FILENAME		(WM_USER + 210)		// ����ȭ�鿡�� ������ ���ϸ��� ���ϱ� ���� �޼���

#define	UM_JUMUN_RET				(WM_USER + 211)		// ��ž�ν� �ֹ� Ȯ��â �ֹ���� �뺸��

#define	UM_CALL_FROM_FORM			(WM_USER + 212)		// ���� ���ΰ��� �޼��� ���޿�
#define	UM_GET_GAMSIJONGMOK			(WM_USER + 213)		// ���ο��� ������ �������� ����

#define	UM_REPLACE_MAP				(WM_USER + 214)		// ȭ�� �ʱ�ȭ�ÿ� �������� ����ó�� �Ѵ�(ȭ�� �˾��޴�)
#define	UM_VERSION_DLGMAP			(WM_USER + 215)		// ȭ�� �ʱ�ȭ�ÿ� �������� ����ó�� �Ѵ�(Dll���� ȣ�� �Ѵ�)

#define	UM_SET_TABMENUSCREEN		(WM_USER + 216)		// Tabȭ�鿡�� TabMenu ���ý� Tab������ ����.
#define	UM_CHANGE_TABSCREEN			(WM_USER + 217)		// Tabȭ�鿡�� TRCODE�ٿ��� �Է��� �ڵ� ����

#define	UM_CALL_CTI_INFO			(WM_USER + 218)		// ���� �����ΰ��� ���� ��ȯ��

#define	UM_SETVIEWPROJECTION		(WM_USER + 219)		// ljj 20110512 add ȭ�麸ȣ�� ���� ����(5��)

// �������� ���â���� ȭ�� �����޼��� ȣ���
#define	UM_SCREENCREATE				(WM_USER + 225)
#define	UM_FIDCHANGE				(WM_USER + 226)		// ȭ�鿡�� FID ����� ������ �����쿡�� �����ϴ� �޼���

#define	UM_M_BY_N_INFO				(WM_USER + 227)		// í�ϵ� ȭ���� M * N ������ ����� ����Ʈ�ѿ��� �����Ѵ�.
#define	UM_SCR_COMM_MSG				(WM_USER + 231)		// ��ȸ ���信 ���� �޼��� ���޿�
#define	UM_GET_SCREENLINKMENU		(WM_USER + 235)		// ȭ���� �׸��忡�� ����ȭ�� ����Ʈ ��� ����
#define	UM_GET_MDICHILD_STYLE		(WM_USER + 236)		// ȭ������� ���� ��� ���� �޼���
#define	UM_MDI_MODECHANGE			(WM_USER + 237)		// �������� ��忡�� ��� ��ȯ�� ���� �޼���

#define	UM_MULTICODE_LINK			(WM_USER + 238)		// ��������ȭ�鿡�� ����������  MXNȭ������ �����ϴ� �޼���
#define	UM_CAPTIONCLICK				(WM_USER + 239)		// ��������ȭ�鿡�� ����ϴ�  CAPTION CLICK�޼���

// FORM OCX���� í�ϵ� ��Ʈ�ѿ��� �����ϴ� �޼��� ����(���� ���̺�, ���� �׸��忡�� �����)
#define	UM_EDIT_COPY				(WM_USER + 240)		// ����
#define	UM_EDIT_PASTE				(WM_USER + 241)		// �ٿ� �ֱ�
#define	UM_EDIT_EXCEL_DDE			(WM_USER + 242)		// ���� �ǽð� �ٿ��ֱ� �޴�
#define	UM_EDIT_SELECT_ALL			(WM_USER + 243)		// ��ü ����

#define	UM_EDIT_ACTIVE_CODE			(WM_USER + 244)		// Active ȭ���� ȭ��TR�ڵ�

#define	UM_TREE_LBUTTONUP			(WM_USER + 250)		// ƼĿ �������� ���̾�α� Ʈ����Ʈ���� �޼��� ó����

#define	UM_QUERY_HOTKEY				(WM_USER + 300)		// ���� ����Ű ó���� �����̽� ��뿩�� üũ��

#define UM_TREDIT_FULL				(WM_USER + 301)
#define UM_CHILD_NOTIFY				(WM_USER + 302)

#define	UM_TICKER_SETUP				(WM_USER + 320)
#define	UM_TICKER_APPLY				(WM_USER + 321)

#define	UM_TICKER_APPLY				(WM_USER + 321)

#define	UM_CTI_DATA					(WM_USER + 350)		// CTI����ȭ��� ������ȯ�� ���� �޼���

#define	UM_GAMSI_REAL				(WM_USER + 400)		// ��ž�ν� �ǽð� ����Ÿ ó����
#define	UM_GAMSI_SENDDATA			(WM_USER + 401)		// ��ž�ν� ���� ���� ó����(�׸��� <--> StoplossWnd)
#define	UM_GAMSI_RECVDATA			(WM_USER + 402)		// ��ž�ν� �ʱ� ����Ÿ ��û��(�׸��� <--> StoplossWnd)

#define	UM_CHANGE_PARENT			(WM_USER + 450)		// ��������� ������ ������ ������ �����ϱ�����...

#define	UM_CREATEAFTER				(WM_USER + 500)
#define	UM_TITLE_MSG				(WM_USER + 501)

#define	UM_FILE_UPDOWNLOAD_MSG		(WM_USER + 502)

// ����ȭ�� ����
#define	UM_CHILDMDIACTIVATE			(WM_USER + 521)

#define UM_JONGMOKBAR_CHANGE		(WM_USER + 522)		// ���� ����
#define UM_OPEN_MAP					(WM_USER + 523)		// ���� �̿��� ���� ȭ���� ������ �Ҷ�
#define UM_WATCH_ORDER				(WM_USER + 524)		// �����ֹ����� �޼���

#define UM_CHANGE_REGKW				(WM_USER + 525)		// �������� �׷캯�� ó����
#define UM_JONGMOKCHANGE_REGKW		(WM_USER + 526)		// �������� �׷����񺯰� �� ����� ƼĿ(Main)�� �˷��ֱ� ���� �޼���

#define UM_SUBTAB_DRAGDROP			(WM_USER + 527)		// �����ܿ��� �巡�׵������ ȭ�� ����
#define UM_POPUP_JCODE				(WM_USER + 528)		// �����ڵ� ��Ʈ�ѿ��� �˾� ������� �����ڵ带 �ѱ��. 

// DLL ���� �ʵ��� ������ �����Ҷ� �׸��尡 �� �׷����� �ʴ� ������ �ִ�.
// �̶� �ذ�å���� �����.
// RunFormCtrl.cpp �� Onsize �� �� �޼����� �ְ� Dll ȭ���� ViewWrap.cpp �� .h�� �� �޼����� �޾� "1"�� �����Ѵ�.
// �׷� RunFormCtrl.cpp ���� "OnSizeAfter" �Լ��� Ÿ�� �ʰ�  DLL �� OnSize�� Ÿ�� �Ѿ��.
// "0" �� �����ϴ���, �ش� �޼����� ������ DLL ��  OnSize������ ó���ϸ� �ȵȴ�.
#define UM_DLLSIZE_CONTROL_MSG		(WM_USER + 530)		// �����ڵ� ��Ʈ�ѿ��� �˾� ������� �����ڵ带 �ѱ��. 

#define UM_SETFORMACC_CHANGE		(WM_USER + 531)		// ��  FORM �� �����޺��� ��й�ȣ(�ٸ� ����) ������ �˷��ش�.


#define UM_SM_SIGNAL_MSG			(WM_USER + 550)		// ��ȣó���⿡�� ���� ����Ÿ�� ��ϵ� ��Ʈ�ѿ� �����Ѵ�.
														// wParam = ( 1:��Ʈ���ڵ� ���,  -1:��Ʈ���ڵ� ���� )  
														// lParam = ( ��Ʈ�� -> ����   )��Ʈ���� �ڵ鰪
														// lParam = ( ����   -> ��Ʈ�� )���� ��ȣ�� �����Ѵ�.


#define UM_SM_SIGNALORDER_MSG		(WM_USER + 551)		// ��ȣó���⿡�� ���� ����Ÿ�� ��ϵ� ��Ʈ�ѿ� �����Ѵ�.
														// wParam = ( 1:��Ʈ���ڵ� ���,  -1:��Ʈ���ڵ� ���� )  
														// lParam = ( ��Ʈ�� -> ����   )��Ʈ���� �ڵ鰪
														// lParam = ( ����   -> ��Ʈ�� )���� ��ȣ�� �����Ѵ�.

#define UM_LAYOUT_CHANGE			(WM_USER + 560)		// ������ ���� ���� ����
														// wParam = ( 0 : �������� )  
														// lParam = ( �����ε��� )  

#define UM_POST_FORM_FIRE			(WM_USER + 570)		//2010. 9. 7 ������

#define UM_SET_KW_GROUP_CODE		(WM_USER + 571)		// ���ɱ׷��ڵ� ����
#define UM_GET_KW_GROUP_CODE		(WM_USER + 572)		// ���ɱ׷��ڵ� ���

#define UM_UPLOAD_DB				(WM_USER + 573)		// LJP 20110320
#define UM_EXEC_DEFAULT_VAL			(WM_USER + 574)		//KJI 20110419
#define UM_GET_FONT_INDEX			(WM_USER + 575)		//KJI 20110512 (�������� ��Ʈ���� ����)

// �޴��ٿ��� �޴� ������ ǥ���̹��� ��ȣ
//#define	IMAGE_NONE			0
#define	IMAGE_POPUP			0
#define	IMAGE_NORMAL		1
#define	IMAGE_WEB			2
#define	IMAGE_EXE			3
#define	IMAGE_DISABLE		4


// DsBitmapButton���� ���
//====================================================
#define UM_BTNLDOWN					WM_USER+1101
#define UM_BTNLUP					WM_USER+1102
#define UM_BTNTOBTN					WM_USER+1103
#define UM_MENU_DELETE				WM_USER+1104
#define UM_MENU_RENAME				WM_USER+1105
#define UM_SUBMENUDISP				WM_USER+1106

#define UM_RMOUSECLICK				WM_USER+1107		// 

// DsDragDropTarget���� ���
//====================================================
#define UM_DROPOCCUR				WM_USER+1201
//====================================================

// TabBarWnd���� ���
//====================================================
#define UM_BTNCLICK					WM_USER+1401
#define UM_SENDORDER				WM_USER+1402
#define UM_SENDADD					WM_USER+1403
#define UM_SENDDELETE				WM_USER+1404
#define UM_BUTTONOK					WM_USER+1406
#define UM_OUTLOOKTO				WM_USER+1407
//====================================================

// TreeCtrl���� ���
//====================================================
#define WM_TREEDROP					WM_USER+1601
//====================================================

// captionbutton.cpp ���� ���
#define UM_CBLBUTTONCLICKED			WM_USER+1650			// Ÿ��Ʋ�� ��ư Ŭ���� ���� �޼���

// captionbutton.cpp ���� ���
#define UM_CSYSBLBUTTONCLICKED		WM_USER+1651			// Ÿ��Ʋ�� �ý��۹�ư Ŭ���� ���� �޼���

// �����޴��ٿ��� ���
#define ID_GFX_REMOVEITEM           WM_USER+1652
#define BASISMENU_OUTLOOK			WM_USER+1653			// �ƿ���ٸ� ���� ���� ..

// DsTabCtrl���� ���
//====================================================
#define WM_TABTOTAB					WM_USER+1701
//====================================================

// �ü�ƽĿ���� ���
//====================================================
//#define	WMU_QUOTEUPDATE			WM_USER + 3001
//#define	WMU_QUOTEUPDATE2		WM_USER + 3002
//#define	WMU_GOODBYE_ALLBASE		WM_USER + 3005
//#define WMU_CODECANCEL			WM_USER + 3007
//====================================================

//-------------------------------------------------------------------

//#define ID_SCROLL_PANE                  33030

// ���̾�α� ǥ�� ȿ�� ����
#define AW_HOR_POSITIVE             0x00000001 
#define AW_HOR_NEGATIVE             0x00000002 
#define AW_VER_POSITIVE             0x00000004 
#define AW_VER_NEGATIVE             0x00000008 
#define AW_CENTER                   0x00000010 
#define AW_HIDE                     0x00010000 
#define AW_ACTIVATE                 0x00020000 
#define AW_SLIDE                    0x00040000 
#define AW_BLEND                    0x00080000 


// �������� OSŸ���� �����Ѵ�.
#define OS_ERROR                    0
#define OS_WIN95                    1
#define OS_WIN98                    2
#define OS_WIN2000                  3
#define OS_WINNT                    4
#define OS_WIN32S					5
#define	OS_WINME					6
#define	OS_WINXP					7
// --> [Edit]  BT.Jung 2007/01/11    
#define	OS_VISTA					8		// ��Ÿ
// <-- [Edit]  BT.Jung 2007/01/11

#define CAPTION_HEIGHT				18		// �Ϲ�������(win2000���� XP����)

// From 16-bit windows.h
#define GFSR_SYSTEMRESOURCES		0
#define GFSR_GDIRESOURCES			1
#define GFSR_USERRESOURCES			2


// Builder�� �˾� �޴����� ����ϴ� ID��
//#define IDM_ORDER_TOP				6015
//#define IDM_ORDER_BOTTOM			6016


#endif		//__KHRESOURCE_H__
