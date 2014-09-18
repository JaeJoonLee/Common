// BaseCtl.cpp : implementation file
//
//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : basectl.cpp
//  Function      : 
//  System Name   : RunAccountCombo
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
#include "stdafx.h"
#include "BaseCtl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef MULTI_CAPTION_USE				// 다국어 사용 옵션 
#if !defined(_GX_ENABLE_INLINES)
#define GX_INLINE
#include "gxcaptionstyle.inl"
#endif //!_GX_ENABLE_INLINES
#endif
/////////////////////////////////////////////////////////////////////////////
// CBaseCtl

IMPLEMENT_DYNCREATE(CBaseCtl, CWnd)

//******************************************************************
//  Function Name : CBaseCtl
//  Function      : 생성자
//  Param         : 없음
//  Return        : 없음 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CBaseCtl::CBaseCtl()
{
	EnableAutomation();

	EnableConnections();

	m_pPropNotifySink = NULL;

	m_clrWndBackColor = RGB(255,255,255);
	m_clrWndForeColor = RGB(  0,  0,  0);

	m_RuntimeMode = TRUE;

	pFormBase     = NULL;
#ifdef MULTI_CAPTION_USE		// 다국어 사용옵션 
	m_pMultiCaption = NULL;
#endif

	m_nEventLogMode	= 0;

	m_dwBitInfo     = 0;
}

//******************************************************************
//  Function Name : ~CBaseCtl
//  Function      : 소멸자
//  Param         : 없음
//  Return        : 없음 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CBaseCtl::~CBaseCtl()
{
}


//******************************************************************
//  Function Name : OnFinalRelease
//  Function      : 
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CWnd::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CBaseCtl, CWnd)
	//{{AFX_MSG_MAP(CBaseCtl)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_WM_WININICHANGE()
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBaseCtl, CWnd)
	//{{AFX_DISPATCH_MAP(CBaseCtl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IBaseCtl to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {2BC41DC1-422F-11D0-A1A9-000000000000}
static const IID IID_IBaseCtl =
{ 0x2bc41dc1, 0x422f, 0x11d0, { 0xa1, 0xa9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CBaseCtl, CWnd)
	INTERFACE_PART(CBaseCtl, IID_IBaseCtl, Dispatch)
	INTERFACE_PART(CBaseCtl, IID_IProvideClassInfo2, ProvideClassInfo)
	INTERFACE_PART(CBaseCtl, IID_IConnectionPointContainer, ConnPtContainer)
	INTERFACE_PART(CBaseCtl, IID_IProvideClassInfo, ProvideClassInfo)
	INTERFACE_PART(CBaseCtl, IID_IPerPropertyBrowsing, PerPropertyBrowsing)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseCtl message handlers

/////////////////////////////////////////////////////////////////////////////
// Event Map Stuff from CBaseCtl

//******************************************************************
//  Function Name : CBaseCtl 
//  Function      : 
//  Param         : 없음
//  Return        : const 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
const AFX_EVENTMAP CBaseCtl::eventMap = { NULL, NULL };

//******************************************************************
//  Function Name : GetEventMap
//  Function      : 
//  Param         : 없음
//  Return        : const 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
const AFX_EVENTMAP* CBaseCtl::GetEventMap() const
{
	return &eventMap;
}

//******************************************************************
//  Function Name : GetEventMapEntry
//  Function      : 
//  Param         : LPCTSTR pszName, DISPID* pDispid
//  Return        : const 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
const AFX_EVENTMAP_ENTRY* CBaseCtl::GetEventMapEntry(
		LPCTSTR pszName,
		DISPID* pDispid) const
{
	ASSERT(pszName != NULL);
	ASSERT(pDispid != NULL);

	const AFX_EVENTMAP* pEventMap = GetEventMap();
	const AFX_EVENTMAP_ENTRY* pEntry;
	DISPID dispid = MAKELONG(1, 0);

	while (pEventMap != NULL)
	{
		pEntry = pEventMap->lpEntries;

		// Scan entries in this event map

		if (pEntry != NULL)
		{
			while (pEntry->pszName != NULL)
			{
				if (_tcscmp(pEntry->pszName, pszName) == 0)
				{
					if (pEntry->dispid != DISPID_UNKNOWN)
						dispid = pEntry->dispid;

					*pDispid = dispid;
					return pEntry;
				}

				++pEntry;
				++dispid;
			}
		}

		// If we didn't find it, go to the base class's event map

		pEventMap = pEventMap->pfnGetBaseMap();
		dispid = MAKELONG(1, HIWORD(dispid)+1);
	}

	// If we reach here, the event isn't supported

	return NULL;
}

const AFX_EVENTMAP* PASCAL CBaseCtl::GetThisEventMap()
{
	return &CBaseCtl::eventMap;
}

//******************************************************************
//  Function Name : FireEventV
//  Function      : 
//  Param         : DISPID dispid, BYTE* pbParams
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::FireEventV(DISPID dispid, BYTE* pbParams,
	va_list argList)
{
	COleDispatchDriver driver;

	POSITION pos = m_xEventConnPt.GetStartPosition();
	LPDISPATCH pDispatch;
	while (pos != NULL)
	{
		pDispatch = (LPDISPATCH)m_xEventConnPt.GetNextConnection(pos);
		//LJP 20110218 Start-->
		if(pDispatch == NULL)
			continue;
//		ASSERT(pDispatch != NULL);
		//<-- End
		driver.AttachDispatch(pDispatch, FALSE);
		TRY
			driver.InvokeHelperV(dispid, DISPATCH_METHOD, VT_EMPTY, NULL,
				pbParams, argList);
		END_TRY
		driver.DetachDispatch();
	}
}

//******************************************************************
//  Function Name : FireEvent
//  Function      : 
//  Param         : DISPID dispid, BYTE* pbParams, ...
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFX_CDECL CBaseCtl::FireEvent(DISPID dispid, BYTE* pbParams, ...)
{
	va_list argList;
	va_start(argList, pbParams);
	FireEventV(dispid, pbParams, argList);
	va_end(argList);
}

//******************************************************************
//  Function Name : XEventConnPt
//  Function      : 
//  Param         : OnAdvise(BOOL bAdvise
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::XEventConnPt::OnAdvise(BOOL bAdvise)
{
	METHOD_PROLOGUE_EX(CBaseCtl, EventConnPt)
//	pThis->OnEventAdvise(bAdvise);
//	TRACE("Event conn pt advise\n");
}

//******************************************************************
//  Function Name : XEventConnPt
//  Function      : 
//  Param         : 없음
//  Return        : REFIID 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
REFIID CBaseCtl::XEventConnPt::GetIID()
{
	METHOD_PROLOGUE_EX_(CBaseCtl, EventConnPt)
	if (pThis->m_piidEvents != NULL)
		return *(pThis->m_piidEvents);
	else
		return GUID_NULL;
}

//******************************************************************
//  Function Name : XEventConnPt
//  Function      : 
//  Param         : QuerySinkInterface(LPUNKNOWN pUnkSink
//  Return        : LPUNKNOWN 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
LPUNKNOWN CBaseCtl::XEventConnPt::QuerySinkInterface(LPUNKNOWN pUnkSink)
{
	METHOD_PROLOGUE_EX_(CBaseCtl, EventConnPt)

	// First, QI for control-specific IID; failing that, QI for IDispatch
	LPUNKNOWN pUnkReturn = NULL;
	if (FAILED(pUnkSink->QueryInterface(*(pThis->m_piidEvents),
		reinterpret_cast<void**>(&pUnkReturn))))
	{
		pUnkSink->QueryInterface(IID_IDispatch,
			reinterpret_cast<void**>(&pUnkReturn));
	}
	return pUnkReturn;
}

/////////////////////////////////////////////////////////////////////////////
// CBaseCtl::GetConnectionHook - override the connection map

//******************************************************************
//  Function Name : GetConnectionHook
//  Function      : 
//  Param         : REFIID iid
//  Return        : LPCONNECTIONPOINT 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
LPCONNECTIONPOINT CBaseCtl::GetConnectionHook(REFIID iid)
{
	if ((m_piidEvents != NULL) && IsEqualIID(iid, *m_piidEvents))
		return (LPCONNECTIONPOINT)((char*)&m_xEventConnPt +
				offsetof(CConnectionPoint, m_xConnPt));
	else
		return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CBaseCtl::GetExtraConnectionPoints - override the connection map

//******************************************************************
//  Function Name : GetExtraConnectionPoints
//  Function      : 
//  Param         : CPtrArray* pConnPoints
//  Return        : BOOL 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CBaseCtl::GetExtraConnectionPoints(CPtrArray* pConnPoints)
{
	pConnPoints->Add((char*)&m_xEventConnPt +
		offsetof(CConnectionPoint, m_xConnPt));
	return TRUE;
}

//******************************************************************
//  Function Name : GetDispatchIID
//  Function      : 
//  Param         : IID* pIID
//  Return        : BOOL 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CBaseCtl::GetDispatchIID(IID* pIID)
{
	if (m_piidPrimary != NULL)
		*pIID = *m_piidPrimary;

	return (m_piidPrimary != NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CBaseCtl::XProvideClassInfo

//******************************************************************
//  Function Name : AddRef
//  Function      : 
//  Param         : 없음
//  Return        : STDMETHODIMP_
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP_(ULONG) CBaseCtl::XProvideClassInfo::AddRef()
{
	METHOD_PROLOGUE_EX_(CBaseCtl, ProvideClassInfo)
	return (ULONG)pThis->ExternalAddRef();
}

//******************************************************************
//  Function Name : Release
//  Function      : 
//  Param         : 없음
//  Return        : STDMETHODIMP_
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP_(ULONG) CBaseCtl::XProvideClassInfo::Release()
{
	METHOD_PROLOGUE_EX_(CBaseCtl, ProvideClassInfo)
	return (ULONG)pThis->ExternalRelease();
}

//******************************************************************
//  Function Name : QueryInterface
//  Function      : 
//  Param         : REFIID iid, LPVOID* ppvObj
//  Return        : STDMETHODIMP 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP CBaseCtl::XProvideClassInfo::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CBaseCtl, ProvideClassInfo)
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

//******************************************************************
//  Function Name : GetClassInfo
//  Function      : 
//  Param         : PTYPEINFO* ppTypeInfo
//  Return        : STDMETHODIMP 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP CBaseCtl::XProvideClassInfo::GetClassInfo(
	LPTYPEINFO* ppTypeInfo)
{
	METHOD_PROLOGUE_EX_(CBaseCtl, ProvideClassInfo)

	CLSID clsid;
	pThis->GetClassID(&clsid);

	return pThis->GetTypeInfoOfGuid(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),SORT_DEFAULT), clsid, ppTypeInfo);
}

//******************************************************************
//  Function Name : GetGUID
//  Function      : 
//  Param         : DWORD dwGuidKind, GUID* pGUID
//  Return        : STDMETHODIMP 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP CBaseCtl::XProvideClassInfo::GetGUID(DWORD dwGuidKind,
	GUID* pGUID)
{
	METHOD_PROLOGUE_EX_(CBaseCtl, ProvideClassInfo)
//	TRACE("GetGUID in provideclassinfo\n");
	
	if (dwGuidKind == GUIDKIND_DEFAULT_SOURCE_DISP_IID)
	{
		*pGUID = *pThis->m_piidEvents;
		return NOERROR;
	}
	else
	{
		*pGUID = GUID_NULL;
		return E_INVALIDARG;
	}
}

//******************************************************************
//  Function Name : GetClassID
//  Function      : 
//  Param         : LPCLSID pclsid
//  Return        : HRESULT 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
HRESULT CBaseCtl::GetClassID(LPCLSID pclsid)
{
	*pclsid = CLSID_NULL;
	return S_OK;
}

//******************************************************************
//  Function Name : ShowPropertySheet
//  Function      : 
//  Param         : HWND hFormWnd
//  Return        : BOOL 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CBaseCtl::ShowPropertySheet(HWND hFormWnd)
{
	return FALSE;
}

//******************************************************************
//  Function Name : BoundPropertyChanged
//  Function      : 
//  Param         : DISPID dispid
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::BoundPropertyChanged(DISPID dispid)
{
	if (m_pPropNotifySink)
		m_pPropNotifySink->OnChanged(dispid);
}

//******************************************************************
//  Function Name : LoadControl
//  Function      : 
//  Param         : IPropertyBag *pPropBag, IErrorLog *pErrorLog
//  Return        : HRESULT	
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
HRESULT	CBaseCtl::LoadControl(IPropertyBag *pPropBag, IErrorLog *pErrorLog)
{
	if (pPropBag)
		pPropBag->Release();
	return S_OK;
}


//******************************************************************
//  Function Name : AddRef
//  Function      : 
//  Param         : 없음
//  Return        : STDMETHODIMP_
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP_(ULONG) CBaseCtl::XPerPropertyBrowsing::AddRef()
{
	METHOD_PROLOGUE_EX_(CBaseCtl, PerPropertyBrowsing)
	return (ULONG)pThis->ExternalAddRef();
}

//******************************************************************
//  Function Name : Release
//  Function      : 
//  Param         : 없음
//  Return        : STDMETHODIMP_ 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP_(ULONG) CBaseCtl::XPerPropertyBrowsing::Release()
{
	METHOD_PROLOGUE_EX_(CBaseCtl, PerPropertyBrowsing)
	return (ULONG)pThis->ExternalRelease();
}

//******************************************************************
//  Function Name : QueryInterface
//  Function      : 
//  Param         : REFIID iid, LPVOID* ppvObj
//  Return        : STDMETHODIMP 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP CBaseCtl::XPerPropertyBrowsing::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CBaseCtl, PerPropertyBrowsing)
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

//******************************************************************
//  Function Name : GetDisplayString
//  Function      : 
//  Param         : DISPID dispid, BSTR* lpbstr
//  Return        : STDMETHODIMP 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP CBaseCtl::XPerPropertyBrowsing::GetDisplayString(
	DISPID dispid, BSTR* lpbstr)
{
	METHOD_PROLOGUE_EX(CBaseCtl, PerPropertyBrowsing)

	ASSERT_NULL_OR_POINTER(lpbstr, BSTR);

	CString strValue;
	BOOL bSuccess = pThis->OnGetDisplayString(dispid, strValue);

	if (lpbstr != NULL)
		*lpbstr = (bSuccess ? strValue.AllocSysString() : NULL);

	return bSuccess ? S_OK : S_FALSE;
}

//******************************************************************
//  Function Name : OnGetDisplayString
//  Function      : 
//  Param         : DISPID dispid, CString& strValue
//  Return        : BOOL 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CBaseCtl::OnGetDisplayString(DISPID dispid, CString& strValue)
{
	return FALSE;
}

//******************************************************************
//  Function Name : MapPropertyToPage
//  Function      : 
//  Param         : DISPID dispid, LPCLSID lpclsid
//  Return        : STDMETHODIMP 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP CBaseCtl::XPerPropertyBrowsing::MapPropertyToPage(
	DISPID dispid, LPCLSID lpclsid)
{
	METHOD_PROLOGUE_EX(CBaseCtl, PerPropertyBrowsing)

	ASSERT_NULL_OR_POINTER(lpclsid, CLSID);

	CLSID clsid = GUID_NULL;
	BOOL bPageOptional = FALSE;
	BOOL bSuccess = pThis->OnMapPropertyToPage(dispid, &clsid, &bPageOptional);

	if (lpclsid != NULL)
		*lpclsid = (bSuccess ? clsid : GUID_NULL);

	return bSuccess ? (bPageOptional ? S_OK : S_FALSE) :
		PERPROP_E_NOPAGEAVAILABLE;
}

//******************************************************************
//  Function Name : OnMapPropertyToPage
//  Function      : 
//  Param         : DISPID dispid, LPCLSID lpclsid, BOOL* pbPageOptional
//  Return        : BOOL 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CBaseCtl::OnMapPropertyToPage(DISPID dispid, LPCLSID lpclsid, BOOL* pbPageOptional)
{
	return FALSE;
}

inline LPOLESTR AFXAPI _AfxCopyString(LPCTSTR psz)
{
	if (psz == NULL)
		return NULL;

	int cch = lstrlen(psz) + 1;
	LPOLESTR pszCopy = NULL;

	if ((pszCopy = (LPOLESTR)CoTaskMemAlloc(cch * sizeof(OLECHAR))) != NULL)
	{
#ifdef _UNICODE
		wcscpy(pszCopy, psz);
#elif !defined(OLE2ANSI)
		MultiByteToWideChar(CP_ACP, 0, psz, -1, pszCopy, cch);
#else
		lstrcpy(pszCopy, psz);
#endif
	}

	return pszCopy;
}

//******************************************************************
//  Function Name : GetPredefinedStrings
//  Function      : 
//  Param         : DISPID dispid, CALPOLESTR* lpcaStringsOut, CADWORD* lpcaCookiesOut
//  Return        : STDMETHODIMP 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP CBaseCtl::XPerPropertyBrowsing::GetPredefinedStrings(
	DISPID dispid, CALPOLESTR* lpcaStringsOut, CADWORD* lpcaCookiesOut)
{
	METHOD_PROLOGUE_EX(CBaseCtl, PerPropertyBrowsing)

	if ((lpcaStringsOut == NULL) || (lpcaCookiesOut == NULL))
		return E_POINTER;

	ASSERT_POINTER(lpcaStringsOut, CALPOLESTR);
	ASSERT_POINTER(lpcaCookiesOut, CADWORD);

	CStringArray stringArray;
	CDWordArray cookieArray;

	BOOL bSuccess = pThis->OnGetPredefinedStrings(dispid, &stringArray, &cookieArray);

	if (bSuccess)
	{
		// Allocate and fill arrays to return.

		ASSERT(stringArray.GetSize() == cookieArray.GetSize());

		int iElem = 0;
		LPOLESTR lpszCopy;
		ULONG cElems = stringArray.GetSize();

		lpcaStringsOut->pElems = (LPOLESTR*)CoTaskMemAlloc(
			sizeof(LPOLESTR) * cElems);

		if (lpcaStringsOut->pElems == NULL)
			return E_OUTOFMEMORY;

		lpcaCookiesOut->pElems = (DWORD*)CoTaskMemAlloc(
			sizeof(DWORD*) * cElems);

		if (lpcaCookiesOut->pElems == NULL)
		{
			CoTaskMemFree(lpcaStringsOut->pElems);
			return E_OUTOFMEMORY;
		}

		lpcaStringsOut->cElems = cElems;
		lpcaCookiesOut->cElems = cElems;

		for (iElem = 0; iElem < (int)cElems; iElem++)
		{
			lpszCopy = _AfxCopyString(stringArray.GetAt(iElem));

			if (lpszCopy == NULL)
			{
				// cleanup everything allocated so far...
				while (--iElem >= 0)
					CoTaskMemFree(lpcaStringsOut->pElems[iElem]);

				CoTaskMemFree(lpcaCookiesOut->pElems);
				CoTaskMemFree(lpcaStringsOut->pElems);

				return E_OUTOFMEMORY;
			}

			lpcaStringsOut->pElems[iElem] = lpszCopy;
			lpcaCookiesOut->pElems[iElem] = cookieArray.GetAt(iElem);
		}
	}

	return bSuccess ? S_OK : S_FALSE;
}

//******************************************************************
//  Function Name : OnGetPredefinedStrings
//  Function      : 
//  Param         : DISPID dispid, CStringArray* pStringArray, CDWordArray* pCookieArray
//  Return        : BOOL 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CBaseCtl::OnGetPredefinedStrings(DISPID dispid, CStringArray* pStringArray, CDWordArray* pCookieArray)
{
	BOOL bResult = FALSE;

	switch (dispid)
	{
	case DISPID_BORDERSTYLE:
		TRY
		{
			CString str;
			str.LoadString(AFX_IDS_BORDERSTYLE_0);
			pStringArray->Add(str);
			pCookieArray->Add(0);
			str.LoadString(AFX_IDS_BORDERSTYLE_1);
			pStringArray->Add(str);
			pCookieArray->Add(1);
			bResult = TRUE;
		}
		CATCH (CException, e)
		{
			pStringArray->RemoveAll();
			pCookieArray->RemoveAll();
			bResult = FALSE;
		}
		END_CATCH
		break;
	}

	return bResult;
}

//******************************************************************
//  Function Name : GetPredefinedValue
//  Function      : 
//  Param         : DISPID dispid, DWORD dwCookie, VARIANT* lpvarOut
//  Return        : STDMETHODIMP 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
STDMETHODIMP CBaseCtl::XPerPropertyBrowsing::GetPredefinedValue(
	DISPID dispid, DWORD dwCookie, VARIANT* lpvarOut)
{
	METHOD_PROLOGUE_EX(CBaseCtl, PerPropertyBrowsing)

	ASSERT_POINTER(lpvarOut, VARIANT);

	return pThis->OnGetPredefinedValue(dispid, dwCookie, lpvarOut) ?
		S_OK : E_FAIL;
}

//******************************************************************
//  Function Name : OnGetPredefinedValue
//  Function      : 
//  Param         : DISPID dispid, DWORD dwCookie, VARIANT* lpvarOut
//  Return        : BOOL 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CBaseCtl::OnGetPredefinedValue(DISPID dispid, DWORD dwCookie, VARIANT* lpvarOut)
{
	switch (dispid)
	{
	case DISPID_BORDERSTYLE:
		if ((dwCookie == 0) || (dwCookie == 1))
		{
			VariantClear(lpvarOut);
			V_VT(lpvarOut) = VT_I4;
			V_I4(lpvarOut) = dwCookie;
			return TRUE;
		}
		break;
	}

	return FALSE;
}

//******************************************************************
//  Function Name : GetForeColor
//  Function      : 
//  Param         : 없음
//  Return        : COLORREF 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
COLORREF CBaseCtl::GetForeColor()
{
	return m_clrWndForeColor;
}

//******************************************************************
//  Function Name : SetForeColor 
//  Function      : 
//  Param         : COLORREF clrColor
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl:: SetForeColor(COLORREF clrColor)
{
	m_clrWndForeColor = clrColor;
}

//******************************************************************
//  Function Name : GetBackColor
//  Function      : 
//  Param         : 없음
//  Return        : COLORREF 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
COLORREF CBaseCtl::GetBackColor()
{
	return m_clrWndBackColor;
}

//******************************************************************
//  Function Name : SetBackColor
//  Function      : 
//  Param         : COLORREF clrColor
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::SetBackColor(COLORREF clrColor)
{
	m_clrWndBackColor = clrColor;
}

//******************************************************************
//  Function Name : AmbientUserMode
//  Function      : 
//  Param         : 없음
//  Return        : BOOL 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CBaseCtl::AmbientUserMode()
{
	return m_RuntimeMode;
}

//******************************************************************
//  Function Name : GetControlFlags
//  Function      : 
//  Param         : 없음
//  Return        : DWORD 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
DWORD CBaseCtl::GetControlFlags()
{
	return 0;
}

//******************************************************************
//  Function Name : OnInactiveSetCursor
//  Function      : 
//  Param         : LPCRECT lprcBounds, long x, long y, DWORD dwMouseMsg, BOOL bSetAlways
//  Return        : BOOL 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CBaseCtl::OnInactiveSetCursor(LPCRECT lprcBounds, long x, long y, DWORD dwMouseMsg, BOOL bSetAlways)
{
	return FALSE;
}

//******************************************************************
//  Function Name : GetControlSize
//  Function      : 
//  Param         : int* pcx, int* pcy
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::GetControlSize(int* pcx, int* pcy)
{
	if (GetSafeHwnd())
	{
		CBaseCtl::GetClientRect ( m_rcClient );
	}
	*pcx = m_rcClient.Width();
	*pcy = m_rcClient.Height();
}

//******************************************************************
//  Function Name : OnGetData
//  Function      : 
//  Param         : WPARAM wParam, LPARAM lParam
//  Return        : long 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
long CBaseCtl::OnGetData(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

//******************************************************************
//  Function Name : SetPropertyEnable
//  Function      : 
//  Param         : BOOL bEnable, IDispatch *pDispatch 
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::SetPropertyEnable(BOOL bEnable, IDispatch *pDispatch )
{
	USES_CONVERSION;
	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE("Enabled");
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		_variant_t var((long)bEnable);
		SetCtlProperty(var, dwDispID, pDispatch);
	}

}

//******************************************************************
//  Function Name : SetPropertyCaption
//  Function      : 
//  Param         : CString strCaption, IDispatch *pDispatch 
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::SetPropertyCaption(CString strCaption, IDispatch *pDispatch )
{
	USES_CONVERSION;
	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE("Caption");
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		_variant_t var(strCaption);
		SetCtlProperty(var, dwDispID, pDispatch);
	}

}
//******************************************************************
//  Function Name : SetCtlProperty
//  Function      : 
//  Param         : _variant_t &var, DISPID dwDispID, IDispatch *pDispatch
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::SetCtlProperty(_variant_t &var, DISPID dwDispID, IDispatch *pDispatch)
{
		//Invoke변수에 값 할당.
		DISPPARAMS dispparams ;
		DISPID mydispid = DISPID_PROPERTYPUT;

		VARIANT* pArg = new VARIANT[1];
		ASSERT(pArg != NULL);   // should have thrown exception
		dispparams.rgvarg = pArg;

		dispparams.rgvarg[0].vt = var.vt;
		dispparams.rgvarg[0].bstrVal = var.bstrVal;

		dispparams.rgdispidNamedArgs = &mydispid;
		dispparams.cArgs = 1L;
		dispparams.cNamedArgs = 1;

		HRESULT hr;
		//Property 설정 함수 호출.
		hr = pDispatch->Invoke(dwDispID, IID_NULL, MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),SORT_DEFAULT),
			DISPATCH_PROPERTYPUT,&dispparams, NULL, NULL, NULL);
		if (FAILED(hr))
		{
			AfxThrowOleException(hr);
		}

		//메모리 해제.
		VariantClear(pArg);	
		delete[] dispparams.rgvarg;
}


//void CBaseCtl::GetLinkLoadData(LPCTSTR sMainKey)
//{
//}
//void CBaseCtl::GetTabLinkLoadData(LPCTSTR sMainKey, long hLocalLinkInfo)
//{
//}
//void CBaseCtl::GetTabLinkTagData(LPCTSTR sMainKey, LPCTSTR sTag, long hLocalLinkInfo) 
//{
//}
//void CBaseCtl::LinkEndEvent(LPCTSTR sMainKey, LPCTSTR sTag)
//{
//}
//void CBaseCtl::GetLinkTagData(LPCTSTR sMainKey, LPCTSTR sTag); 
//{
//}
//void CBaseCtl::SetLinkTagData(LPCTSTR sMainKey); 
//{
//}

//******************************************************************
//  Function Name : GetPropertyLong
//  Function      : 
//  Param         : int nIndex
//  Return        : long 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 프로퍼티값을 취득한다.
//******************************************************************
long CBaseCtl::GetPropertyLong(int nIndex)
{
	return 0;
}
//******************************************************************
//  Function Name : GetPropertyString
//  Function      : 
//  Param         : int nIndex
//  Return        : CString	
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CString	CBaseCtl::GetPropertyString(int nIndex)			// 프로퍼티값을 취득한다.
{
	return "";
}

//******************************************************************
//  Function Name : OnLButtonDown
//  Function      : 
//  Param         : UINT nFlags, CPoint point
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonDown(nFlags, point);
	SetFocus();
}

//******************************************************************
//  Function Name : OnRButtonDown
//  Function      : 
//  Param         : UINT nFlags, CPoint point
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnRButtonDown(nFlags, point);
	SetFocus();
}

//******************************************************************
//  Function Name : OnWinIniChange
//  Function      : 
//  Param         : LPCTSTR lpszSection
//  Return        : void 
//  Create        : 
//  Update        : 김호겸, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CBaseCtl::OnWinIniChange(LPCTSTR lpszSection)
{
	if ( lpszSection && strlen ( lpszSection ) == 2 )
	{
		TCHAR szLang[3] = { 0 };
		GetLocaleInfo( MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),SORT_DEFAULT), LOCALE_SISO639LANGNAME, szLang, sizeof(szLang));

		// 언어모드 취득
		WORD wLangId = LANGIDFROMLCID(::GetThreadLocale());
		wLangId	 = PRIMARYLANGID(wLangId);
		switch ( wLangId )
		{
		default:
		case LANG_NEUTRAL:
		case LANG_ENGLISH:
			TRACE("[LANG_ENGLISH]\n");
			break;
		case LANG_KOREAN:
			TRACE("[LANG_KOREAN]\n");
			break;
		case LANG_JAPANESE:
			TRACE("[LANG_JAPANESE]\n");
			break;
		}

#ifdef MULTI_CAPTION_USE		// 다국어 사용옵션 
		if ( m_pMultiCaption )
		{
			m_pMultiCaption->SetDefaultCaptionChange ( wLangId );
		}
#endif
		OnLangageModeChange ( wLangId );	
	}
	
}

void CBaseCtl::SetEventLog(CString strLog)
{
	if( m_nEventLogMode == 1)
	{
		// 로그남기자
		SetEventLogWriteToFile(strLog);
	}
}

#define LOG_FILENAME_COMMS		"%s/log/HwEventLogFile%s.log"	// 이벤트 관련 로그 저장

void CBaseCtl::SetEventLogWriteToFile(CString strMsg)
{
	CString	strLog;
	CString strTime;
	
	CString strLogFileName;
	char* pLogBuf;
	int nLogLen;

	CString strRootPath = GetRunTimePath();
	if (strRootPath.IsEmpty())
		return;
	
	// 일자,시간,TYPE,모쥴명,함수명,에러코드,에러 메세지
	CTime theTime = CTime::GetCurrentTime();
	strTime = theTime.Format("%Y/%m/%d,%X,");

	strLog.Format("%sS:", theTime.Format( "%Y/%m/%d,%X," ));
	
	nLogLen = strLog.GetLength() + strMsg.GetLength();
	pLogBuf = new char[nLogLen + 2];
	memcpy(pLogBuf, strLog.GetBuffer(0), strLog.GetLength());
	memcpy(pLogBuf + strLog.GetLength(), strMsg.GetBuffer(0), strMsg.GetLength());
	memcpy(pLogBuf + nLogLen, "\r\n", 2);
	
	nLogLen += 2;

	// 로그 파일명를 체크한다.
	strLogFileName.Format(LOG_FILENAME_COMMS, strRootPath, theTime.Format("%Y%m%d"));
	
	CFile	theFile;
	if (!theFile.Open(strLogFileName.GetBuffer(0), CFile::modeWrite))
	{ 
		if (!theFile.Open(strLogFileName.GetBuffer(0),
						CFile::modeReadWrite | CFile::shareCompat | CFile::modeCreate))
		{
			delete[] pLogBuf;
			return;
		}	
	}

	DWORD lLength = (DWORD)theFile.GetLength();
	theFile.Seek(lLength, CFile::current);
	theFile.Write(pLogBuf, nLogLen);
	theFile.Close();

	delete[] pLogBuf;
}

CString CBaseCtl::GetRunTimePath()
{
	char lpszModulePath[MAX_PATH];

	CString strAppPath = "";

	GetModuleFileName(NULL,lpszModulePath,MAX_PATH);
	*strrchr(lpszModulePath,'\\') = '\0';
	strAppPath = lpszModulePath;			// 실행 디렉터리구하기

	return strAppPath;
}
