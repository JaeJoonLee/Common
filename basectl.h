// CmdTargetPlus.h : header file
//

#ifndef __CBASECTL_H__
#define __CBASECTL_H__

#include <afxpriv.h>
#include <afxctl.h>			// For Event Map things
#include "AtlBase.h"
#include <comdef.h>

#pragma warning (disable:4786)

// ��Ʈ ���̺� ���� 
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

typedef std::vector<char*> CHARVECTOR;
typedef std::vector<std::vector<char*> > CHARVECTOR2;


#define	PROP_CAPTION			10
#define	PROP_ENABLED			11
#define	PROP_VISIBLE			12
#define	PROP_RESIZEMODE			13
#define	PROP_CURRENTTAB			15
#define	PROP_AUTOSAVE			16	
#define	PROP_LINKINFORMATION	17	
#define	PROP_CREATEMODE			18
#define	PROP_FIDFLAG			19
#define	PROP_FID				20
#define	PROP_CONTROLMODE		21
#define	PROP_ITEMINDEX			22
#define	PROP_GETCHECK			23
#define	PROP_OFFVALUE			24
#define	PROP_ONVALUE			25
#define	PROP_CHECKSTATE			26
// --> [Edit]  ������ 2006/03/23
#define PROP_BACKCLR			27
#define PROP_FONT				28
#define PROP_FONT_COLOR			29
#define PROP_TEXT_HALIGN		30 
#define PROP_TEXT_VALIGN		31
#define PROP_APPEAR_STYLE		32
#define PROP_BORDER_COLOR		33
// <-- [Edit]  ������ 2006/03/23
// --> [Edit]  ��â�� 2006/06/22
// Ʈ������ ItemName
#define	PROP_ITEM				34
#define	PROP_FORMWAITCOUNT		35
#define	PROP_PARENTCOLOR		36
#define	PROP_APPLAYREMOVE		37

// <-- [Edit]  ��â�� 2006/06/22
#define	PROP_CONTROLINFO		1000


// --> [Edit]  ������ 2006/04/05
#define LABEL_BORDER_CX			2	// ������ �β�(CX)
#define LABEL_BORDER_CY			2	// ������ �β�(CY)
#define LABEL_BORDER_GAP		1	// 
// <-- [Edit]  ������ 2006/04/05




#define	FUNC_SETFOCUS			1
#define	FUNC_CAPTION			2
#define	FUNC_SETFOCUSCTRL		3
#define	FUNC_EDITFULLCAPTION	4
#define	FUNC_SETAUTOSAVEVALUE	5
#define	FUNC_GETAUTOSAVEVALUE	6
#define	FUNC_GETVALUE			7
#define	FUNC_SETVALUE			8
#define	FUNC_SETVALUECOM		9
//#define	FUNC_GETLASTDATA		10
//#define	FUNC_SETLASTDATA		11
#define	FUNC_CHECKCAPTION		12
#define	FUNC_MOVECONTROLS		13
#define	FUNC_SETCAPTIONCTRL		14
#define	FUNC_RBUTTONCLICK		15

//  [11/2/2006] �Ű��� Cotrol�� PowerDlg Control���� �������� ���ڰ��� �Ѱ��ְ��� �Ҷ� Setting�Ѵ�.
#define	FUNC_GETVALUEPARAM1		16	
#define	FUNC_SETVALUEPARAM1		17

// --> [Edit]  ���̶� 2006/11/16
// �ֺ���ġ ����
#define	FUNC_SET_DEVICECTRL		18
// <-- [Edit]  ���̶� 2006/11/16

// --> [Edit]  ��â�� 2006/12/08
#define	FUNC_SET_DATAINIT		19
#define	FUNC_SET_INTERESTINFOCHANGE		20		// ����ȭ�鿡�� ���񺯰� ���� 
#define	FUNC_SET_GRIDCODECLICK			21		// �ü�ǥȭ��  ���񿬵� 
#define	FUNC_SET_CODELINK				22		// �����޺����� ���̺�� �ڵ忬��ó�� 
#define	FUNC_SET_MARKETLINK				23		// �����޺����� ���̺�� �������ó�� 
#define	FUNC_SET_DEPOSITLINK			33		// �����޺����� ��ư���� ���űݿ���ó�� 
#define	FUNC_SET_FORECOLOR				34		// �����޺����� ����� ���̺� �� ���� 
// <-- [Edit]  ��â�� 2006/12/08


#ifdef MULTI_CAPTION_USE		// �ٱ��� ���ɼ� 
#ifndef _GXCAPTIONSTYLE_H_
#include "gxcaptionstyle.h"		// GxCaptionArray
#endif
#endif

// --> [Edit]  ������ 2006/03/27
	#include ".\ColorTableDef.h"
// <-- [Edit]  ������ 2006/03/27


#define		DEF_BASECTL_FORMEVENT      0x00000001


/////////////////////////////////////////////////////////////////////////////
// CBaseCtl command target
class AFX_EXT_CLASS CBaseCtl : public CWnd
{
	DECLARE_DYNCREATE(CBaseCtl)

public:
	CBaseCtl();           // protected constructor used by dynamic creation
	virtual ~CBaseCtl();

	CBaseCtl*	pFormBase;		// �������� �����

	//SetFormDispatch ó����
	virtual void SetRunFormDispatch(CBaseCtl* pWnd, IDispatch* lpFormDispatch, HWND hFormMngWnd, HWND hChildFormWnd){};
	virtual int	OnFormFireEventSend		( CBaseCtl* pBaseCtl, long nEventID, long nOption, long nRow, long nCol, CString strData ) { return 0;}

// Attributes
public:
	IPropertyNotifySink *	m_pPropNotifySink;
	BOOL					m_RuntimeMode;

	DWORD					m_dwBitInfo;				// ��ɺ�Ʈ����

	DWORD					m_dwOleMisc;

	COLORREF				m_clrWndBackColor;
	COLORREF				m_clrWndForeColor;

	CRect					m_rcClient,
		                    m_rcInitClient;
	COLORREF GetForeColor();
	void	 SetForeColor(COLORREF clrColor);
	COLORREF GetBackColor();
	void	 SetBackColor(COLORREF clrColor);

	BOOL	AmbientUserMode();

	int		m_nEventLogMode;
	void	SetEventLog(CString strLog);
	void	SetEventLogWriteToFile( CString strMsg );		// �α����� ���
	CString GetRunTimePath();

// --> [Edit]  �̵��� 2010/07/30
// 
	CString		m_strControlName;
	CString		m_strScreenNo;
// <-- [Edit]  �̵��� 2010/07/30
// Virtual Interface
public :
	virtual BOOL ShowPropertySheet(HWND hFormWnd);
	virtual BOOL OnGetDisplayString(DISPID dispid, CString& strValue);
	virtual BOOL OnMapPropertyToPage(DISPID dispid, LPCLSID lpclsid, BOOL* pbPageOptional);
	virtual BOOL OnGetPredefinedStrings(DISPID dispid, CStringArray* pStringArray, CDWordArray* pCookieArray);
	virtual BOOL OnGetPredefinedValue(DISPID dispid, DWORD dwCookie, VARIANT* lpvarOut);
	virtual DWORD GetControlFlags();
	virtual BOOL OnInactiveSetCursor(LPCRECT lprcBounds, long x, long y, DWORD dwMouseMsg, BOOL bSetAlways);
	virtual void GetControlSize(int* pcx, int* pcy);

	// ����Ÿ ���� ��� ������
	virtual long OnGetData(WPARAM wParam, LPARAM lParam);
	// Langage Mode Change
	virtual void OnLangageModeChange( WORD wLangID ) { ; }

	// ������Ƽ(Enable, Caption) ��Ʈ��
	void	SetPropertyEnable(BOOL bEnable, IDispatch *pDispatch );
	void	SetPropertyCaption(CString strCaption, IDispatch *pDispatch );
	void	SetCtlProperty(_variant_t &var, DISPID dwDispID, IDispatch *pDispatch);



	// ȭ�� ȣ��� �������� ��Ʈ��
	virtual void LayoutTabGetLinkTagData(LPCTSTR sTag, long hLocalLinkInfo){};
	virtual void LinkEvent(LPCTSTR sTag){}; 
	virtual void GetLinkTagData(LPCTSTR sTag){}; 
	virtual void SetLinkTagData(LPCTSTR sTag){}; 

	virtual int	IsAutoSave() { return FALSE;};				// �ڵ������ ��Ʈ���ΰ�?
	virtual int	IsLinkInformation(){ return FALSE;};		// ���������� ��Ʈ���ΰ�?

	virtual void	SetInterestCodeChange	( CObArray* pAllItemInfo, LPCTSTR  strGroupName , int nOption) { return ;}
	virtual long    GetInterestInfo			( CObArray* pAllItemInfo, LPCTSTR  strGroupName )  { return 0 ;}
	virtual long    GetInterestCodePNbySort ( CObArray* pAllItemInfo, LPCTSTR  strGroupName , LPCTSTR strPage,  LPCTSTR strPN, LPCTSTR strSort_f , long nFlag ) { return 0 ;}

	// ������Ƽ �� ����
	virtual long	GetPropertyLong(int nIndex);			// ������Ƽ���� ����Ѵ�.
	virtual CString	GetPropertyString(int nIndex);			// ������Ƽ���� ����Ѵ�.

	// ����Ʈ�ѿ��� ���� ��Ŀ�� ó���Լ� (Form����ó��)
	virtual long    GetFormScreenVersionInfo() { return 0;}

////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Control Type
	virtual int GetControlType() { return -1; };
	virtual CString	GetCommValue( BOOL& bKeyValue, CString& strMarketKind, int nDataType = 0 ) { return "";};
	virtual BOOL SetAutoTranInfoEx(CObArray* pItemInfo, short nInOutType, short nOption, int& nWidth, int& nHeight, LPCTSTR strTrCode, LPCTSTR strRecName , int  nTranType ) { ASSERT ( FALSE); return FALSE; }

	virtual void SetPreProprtySaveNotify ( ) { ; };

	virtual BOOL SetDesignEditProc ( int nOption , int& nRetValue ){ return FALSE; };

//  ��� ������ ó�� �Լ� 
// --> [Edit]  ��â�� 2006/05/12
	virtual  long  CommGetTranInfo		 ( LPCTSTR strTrCode,    LPCTSTR strRecordName ) { return 0 ;};
	virtual  int   CommGetColumItemArray ( LPCTSTR strTrCodeInfo, CHARVECTOR&  vtColList ) { ASSERT ( FALSE ); return -1;};
	virtual  BOOL  CommSetReplyData		 ( LPCTSTR strTrCodeInfo, CHARVECTOR2 vvRpValueList, int nDataCount, int nColCount, int nOption = 0 ) { ASSERT ( FALSE ); return FALSE;};
// <-- [Edit]  ��â�� 2006/05/12
	
	virtual  BOOL  SetFuctionKeyProcess ( int VK_TYPE, int nFuncIndex = 1 ) { ASSERT ( FALSE ); return FALSE;};


#ifdef MULTI_CAPTION_USE		// �ٱ��� ���ɼ� 
	virtual void SetMultiCaptionProprtyReload ( ) { ; };
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	virtual CString	GetMethodString(int nIndex, CString strMethodName){return "";};	// �޼ҵ� ȣ�⿡ ���� ���� ��ȯ�Ѵ�.
	virtual int	SetMethodString(int nIndex, CString strMethodName, CString strData, long lVal = 0){return FALSE;};	// �޼ҵ� ȣ�⿡ ���� ���� ��ȯ�Ѵ�.
	
	virtual CString GetRequestData (CString strRQName_TRCode,   CString strMarketKind, CString strKeyData, long nType, int nTranKind , CString strQuery ) {return "";};		// ����Ÿ ��û�� ���ڿ� ����
	virtual BOOL	FuncCommRequest(CString strRQNameCtrl, CString strCtrlName, int nPrevNext){return FALSE;};

	virtual void	SetResizeControl(float x, float y){};
	virtual void	ColorChange(){};
	virtual void	OnChangParentColor(){};

	virtual CBaseCtl* GetBaseCtlWnd(CString strCtrlName) { return NULL; };
	virtual void	AddControl(CBaseCtl* pNewCtl, long nType){};

	virtual CString GetLastData(LPCTSTR strPageScrNo, LPCTSTR strPageIndex){return "";} ;
	virtual void	SetLastData(LPCTSTR strPageScrNo, LPCTSTR strPageIndex, LPCTSTR strData){} ;
	
	// ȭ���ȣ�� ��Ʈ���̸��� �Ѱ��ش�.
	virtual void	SetCtrlInfo(LPCTSTR strTrCode, LPCTSTR strCtrlName ){m_strScreenNo = strTrCode; m_strControlName = strCtrlName;}
	

// Operations
public:
	void AFX_CDECL FireEvent(DISPID dispid, BYTE* pbParams, ...);
	void BoundPropertyChanged(DISPID dispid);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseCtl)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:

	virtual void SetFormDispatch(LPDISPATCH lpFormDispath , OLE_HANDLE hFormMngWnd, OLE_HANDLE hChildFormWnd){};

	// Events
	static const AFX_DATA AFX_EVENTMAP_ENTRY _eventEntries[];
	virtual const AFX_EVENTMAP* GetEventMap() const;
	static const AFX_DATA AFX_EVENTMAP eventMap;
	const AFX_EVENTMAP_ENTRY* GetEventMapEntry(LPCTSTR pszName,
		DISPID* pDispid) const;
	static const AFX_EVENTMAP* PASCAL GetThisEventMap();
	void FireEventV(DISPID dispid, BYTE* pbParams, va_list argList);

	// Generated message map functions
	//{{AFX_MSG(CBaseCtl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CBaseCtl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	// Connection point container
	virtual LPCONNECTIONPOINT GetConnectionHook(REFIID iid);
	virtual BOOL GetExtraConnectionPoints(CPtrArray* pConnPoints);

	// Connection point for events - from COleControl
	BEGIN_CONNECTION_PART(CBaseCtl, EventConnPt)
		virtual void OnAdvise(BOOL bAdvise);
		virtual REFIID GetIID();
		virtual LPUNKNOWN QuerySinkInterface(LPUNKNOWN pUnkSink);
	END_CONNECTION_PART(EventConnPt)

	// IProvideClassInfo2
	BEGIN_INTERFACE_PART(ProvideClassInfo, IProvideClassInfo2)
		INIT_INTERFACE_PART(COleControl, ProvideClassInfo)
		STDMETHOD(GetClassInfo)(LPTYPEINFO* ppTypeInfo);
		STDMETHOD(GetGUID)(DWORD dwGuidKind, GUID* pGUID);
	END_INTERFACE_PART_STATIC(ProvideClassInfo)

	BEGIN_INTERFACE_PART(PerPropertyBrowsing, IPerPropertyBrowsing)
		INIT_INTERFACE_PART(COleControl, PerPropertyBrowsing)
		STDMETHOD(GetDisplayString)(DISPID dispid, BSTR* lpbstr);
		STDMETHOD(MapPropertyToPage)(DISPID dispid, LPCLSID lpclsid);
		STDMETHOD(GetPredefinedStrings)(DISPID dispid, CALPOLESTR* lpcaStringsOut, CADWORD* lpcaCookiesOut);
		STDMETHOD(GetPredefinedValue)(DISPID dispid, DWORD dwCookie, VARIANT* lpvarOut);
	END_INTERFACE_PART(PerPropertyBrowsing)

public:
	virtual HRESULT GetClassID(LPCLSID pclsid);
	virtual	HRESULT	LoadControl(IPropertyBag *pPropBag, IErrorLog *pErrorLog);

	BOOL GetDispatchIID(IID* pIID);

	const IID* m_piidEvents;            // IID for control events
	const IID* m_piidPrimary;			// IID for primary idispatch
};

/////////////////////////////////////////////////////////////////////////////

#endif // __CBASECTL_H__
