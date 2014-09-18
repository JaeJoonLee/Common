//******************************************************************
// All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : CtlUtil.cpp
//  Function      : 
//  System Name   : Common
//  Create        : 김창하, 2006/05/02
//  Update        : 김준안, 2009/09/18 VS 2009 Upgrade를 위한 작업
//  Comment       : 비스타 UAC처리
//					http://www.codeguru.com/controls/xpstyle.html
//******************************************************************
#include "stdafx.h"
#include "CtlUtil.h"
#include <AfxPriv.h>

// --> [Edit]  김창하 2006/05/02
#include "..\controls\\GDIMgr\ColorPickerCB.h"
// <-- [Edit]  김창하 2006/05/02


#define BUFMAX	32767

CObArray	m_ArrayDDPData;

//*****************************************************************
//  Function Name : SetPropText
//  Function      : 
//  Param         : CString &strPropName, BYTE strData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SetPropText(CString &strPropName, BYTE strData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(strPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		_variant_t var(strData);
		SetCtlProperty(var, dwDispID, pDispatch);
	}
}

//*****************************************************************
//  Function Name : SetPropText
//  Function      : 
//  Param         : CString &strPropName, short strData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SetPropText(CString &strPropName, short strData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(strPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		_variant_t var(strData);
		SetCtlProperty(var, dwDispID, pDispatch);
	}
}

//*****************************************************************
//  Function Name : SetPropText
//  Function      : 
//  Param         : CString &strPropName, int strData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SetPropText(CString &strPropName, int strData, IDispatch *pDispatch)
{
	SetPropText(strPropName, (long) strData, pDispatch);
}

//*****************************************************************
//  Function Name : SetPropText
//  Function      : 
//  Param         : CString &strPropName, long strData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SetPropText(CString &strPropName, long strData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(strPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		_variant_t var(strData);
		SetCtlProperty(var, dwDispID, pDispatch);
	}
}

//*****************************************************************
//  Function Name : SetPropText
//  Function      : 
//  Param         : CString &strPropName, float strData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SetPropText(CString &strPropName, float strData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(strPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		_variant_t var(strData);
		SetCtlProperty(var, dwDispID, pDispatch);
	}
}

//*****************************************************************
//  Function Name : SetPropText
//  Function      : 
//  Param         : CString &strPropName, double strData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************

void SetPropText(CString &strPropName, double strData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(strPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		_variant_t var(strData);
		SetCtlProperty(var, dwDispID, pDispatch);
	}
}

//*****************************************************************
//  Function Name : SetPropText
//  Function      : 
//  Param         : CString &strPropName, CString strData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SetPropText(CString &strPropName, CString strData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(strPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		_variant_t var(strData);
		SetCtlProperty(var, dwDispID, pDispatch);
	}
}

//*****************************************************************
//  Function Name : SetCtlProperty
//  Function      : 
//  Param         : _variant_t &var, DISPID dwDispID, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SetCtlProperty(_variant_t &var, DISPID dwDispID, IDispatch *pDispatch)
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

//*****************************************************************
//  Function Name : GetPropText
//  Function      : 
//  Param         : CString &strPropName, BYTE *pstrData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void GetPropText(CString &strPropName, BYTE *pstrData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	COleDispatchDriver PropDispDriver;
	LPCOLESTR lpOleStr = T2COLE(strPropName);
	DISPID dwDispID;
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),SORT_DEFAULT), &dwDispID)))
	{
		PropDispDriver.AttachDispatch(pDispatch, FALSE);
		PropDispDriver.GetProperty(dwDispID, VT_I1, pstrData);
		PropDispDriver.DetachDispatch();
	}
}

//*****************************************************************
//  Function Name : GetPropText
//  Function      : 
//  Param         : CString &strPropName, short *pstrData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void GetPropText(CString &strPropName, short *pstrData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	COleDispatchDriver PropDispDriver;
	LPCOLESTR lpOleStr = T2COLE(strPropName);
	DISPID dwDispID;
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),SORT_DEFAULT), &dwDispID)))
	{
		PropDispDriver.AttachDispatch(pDispatch, FALSE);
		PropDispDriver.GetProperty(dwDispID, VT_I2, pstrData);
		PropDispDriver.DetachDispatch();
	}
}

//*****************************************************************
//  Function Name : GetPropText
//  Function      : 
//  Param         : CString &strPropName, int *pstrData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void GetPropText(CString &strPropName, int *pstrData, IDispatch *pDispatch)
{
	GetPropText(strPropName, (long *)pstrData, pDispatch);
}

//*****************************************************************
//  Function Name : GetPropText
//  Function      : 
//  Param         : CString &strPropName, long *pstrData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void GetPropText(CString &strPropName, long *pstrData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	COleDispatchDriver PropDispDriver;
	LPCOLESTR lpOleStr = T2COLE(strPropName);
	DISPID dwDispID;
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),SORT_DEFAULT), &dwDispID)))
	{
		PropDispDriver.AttachDispatch(pDispatch, FALSE);
		PropDispDriver.GetProperty(dwDispID, VT_I4, pstrData);
		PropDispDriver.DetachDispatch();
	}
}

//*****************************************************************
//  Function Name : GetPropText
//  Function      : 
//  Param         : CString &strPropName, float *pstrData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void GetPropText(CString &strPropName, float *pstrData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	COleDispatchDriver PropDispDriver;
	LPCOLESTR lpOleStr = T2COLE(strPropName);
	DISPID dwDispID;
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),SORT_DEFAULT), &dwDispID)))
	{
		PropDispDriver.AttachDispatch(pDispatch, FALSE);
		PropDispDriver.GetProperty(dwDispID, VT_R4, pstrData);
		PropDispDriver.DetachDispatch();
	}
}

//*****************************************************************
//  Function Name : GetPropText
//  Function      : 
//  Param         : CString &strPropName, double *pstrData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void GetPropText(CString &strPropName, double *pstrData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	COleDispatchDriver PropDispDriver;
	LPCOLESTR lpOleStr = T2COLE(strPropName);
	DISPID dwDispID;
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),SORT_DEFAULT), &dwDispID)))
	{
		PropDispDriver.AttachDispatch(pDispatch, FALSE);
		PropDispDriver.GetProperty(dwDispID, VT_R8, pstrData);
		PropDispDriver.DetachDispatch();
	}
}

//*****************************************************************
//  Function Name : GetPropText
//  Function      : 
//  Param         : CString &strPropName, CString *pstrData, IDispatch *pDispatch
//  Return        : void
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void GetPropText(CString &strPropName, CString *pstrData, IDispatch *pDispatch)
{
	USES_CONVERSION;
	COleDispatchDriver PropDispDriver;
	LPCOLESTR lpOleStr = T2COLE(strPropName);
	DISPID dwDispID;
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),SORT_DEFAULT), &dwDispID)))
	{
		PropDispDriver.AttachDispatch(pDispatch, FALSE);
		PropDispDriver.GetProperty(dwDispID, VT_BSTR, pstrData);
		PropDispDriver.DetachDispatch();
	}
}



//*****************************************************************
//  Function Name : DDP_DATADDP_DATA
//  Function      : 
//  Param         : nFuncType, int nCtrlId, LPVOID lpMember, UINT nType, DISPID	nDispID
//  Return        : DDP_DATA
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
DDP_DATA::DDP_DATA(int nFuncType, int nCtrlId, LPVOID lpMember, UINT nType, DISPID	nDispID) :
	m_nFuncType(nFuncType),
	m_nCtrlId(nCtrlId),
	m_lpMember(lpMember),
	m_nType(nType),
	m_nDispID(nDispID)
{
} 

//*****************************************************************
//  Function Name : DDP_Text
//  Function      : 
//  Param         : CDataExchange*pDX, int id, BYTE& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Text(CDataExchange*pDX, int id, BYTE& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_I1, &member);
			PropDispDriver.DetachDispatch();

			strWindowText.Format("%d", member);
			::SetWindowText(hWndCtrl, strWindowText);
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_TEXT, id, (LPVOID)&member, VT_I1, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);

/*
			LPSTR lpBuff = strWindowText.GetBuffer(BUFMAX);
			::GetWindowText(hWndCtrl, lpBuff, BUFMAX);
			strWindowText.ReleaseBuffer();

			member = atoi(strWindowText);

			_variant_t var(member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}

//*****************************************************************
//  Function Name : DDP_Text
//  Function      : 
//  Param         : CDataExchange*pDX, int id, short& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Text(CDataExchange*pDX, int id, short& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_I2, &member);
			PropDispDriver.DetachDispatch();

			strWindowText.Format("%d", member);
			::SetWindowText(hWndCtrl, strWindowText);
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_TEXT, id, (LPVOID)&member, VT_I2, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);
/*
			LPSTR lpBuff = strWindowText.GetBuffer(BUFMAX);
			::GetWindowText(hWndCtrl, lpBuff, BUFMAX);
			strWindowText.ReleaseBuffer();

			member = atoi(strWindowText);

			_variant_t var(member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}

//*****************************************************************
//  Function Name : DDP_Text
//  Function      : 
//  Param         : CDataExchange*pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Text(CDataExchange*pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	DDP_Text(pDX, id, (long&)member, pszPropName, pDispatch);
}

//*****************************************************************
//  Function Name : DDP_Text
//  Function      : 
//  Param         : CDataExchange*pDX, int id, UINT& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Text(CDataExchange*pDX, int id, UINT& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	DDP_Text(pDX, id, (long&)member, pszPropName, pDispatch);
}

//*****************************************************************
//  Function Name : DDP_Text
//  Function      : 
//  Param         : CDataExchange*pDX, int id, long& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Text(CDataExchange*pDX, int id, long& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_I4, &member);
			PropDispDriver.DetachDispatch();

			strWindowText.Format("%d", member);
			::SetWindowText(hWndCtrl, strWindowText);
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_TEXT, id, (LPVOID)&member, VT_I4, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);
/*
			LPSTR lpBuff = strWindowText.GetBuffer(BUFMAX);
			::GetWindowText(hWndCtrl, lpBuff, BUFMAX);
			strWindowText.ReleaseBuffer();

			member = atoi(strWindowText);

			_variant_t var(member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}

//*****************************************************************
//  Function Name : DDP_Text
//  Function      : 
//  Param         : CDataExchange*pDX, int id, DWORD& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Text(CDataExchange*pDX, int id, DWORD& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	DDP_Text(pDX, id, (long&)member, pszPropName, pDispatch);
}

//*****************************************************************
//  Function Name : DDP_Text
//  Function      : 
//  Param         : CDataExchange*pDX, int id, float& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Text(CDataExchange*pDX, int id, float& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_R4, &member);
			PropDispDriver.DetachDispatch();

			strWindowText.Format("%f", member);
			::SetWindowText(hWndCtrl, strWindowText);
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_TEXT, id, (LPVOID)&member, VT_R4, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);
/*
			LPSTR lpBuff = strWindowText.GetBuffer(BUFMAX);
			::GetWindowText(hWndCtrl, lpBuff, BUFMAX);
			strWindowText.ReleaseBuffer();

			member = (float)atof(strWindowText);

			_variant_t var(member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}

//*****************************************************************
//  Function Name : DDP_Text
//  Function      : 
//  Param         : CDataExchange*pDX, int id, double& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Text(CDataExchange*pDX, int id, double& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_R8, &member);
			PropDispDriver.DetachDispatch();

			strWindowText.Format("%f", member);
			::SetWindowText(hWndCtrl, strWindowText);
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_TEXT, id, (LPVOID)&member, VT_R8, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);
/*
			LPSTR lpBuff = strWindowText.GetBuffer(BUFMAX);
			::GetWindowText(hWndCtrl, lpBuff, BUFMAX);
			strWindowText.ReleaseBuffer();

			member = atof(strWindowText);

			_variant_t var(member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}

//*****************************************************************
//  Function Name : DDP_Text
//  Function      : 
//  Param         : CDataExchange*pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Text(CDataExchange*pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_BSTR, &member);
			PropDispDriver.DetachDispatch();

			::SetWindowText(hWndCtrl, member);
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_TEXT, id, (LPVOID)&member, VT_BSTR, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);
/*
			LPSTR lpBuff = strWindowText.GetBuffer(BUFMAX);
			::GetWindowText(hWndCtrl, lpBuff, BUFMAX);
			strWindowText.ReleaseBuffer();

			member = strWindowText;

			_variant_t var(member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}

//*****************************************************************
//  Function Name : DDP_LBString
//  Function      : 
//  Param         : CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_LBString(CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	DDP_Text(pDX, id, member, pszPropName, pDispatch);
}

//*****************************************************************
//  Function Name : DDP_LBStringExact
//  Function      : 
//  Param         : CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_LBStringExact(CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	DDP_Text(pDX, id, member, pszPropName, pDispatch);
}

//*****************************************************************
//  Function Name : DDP_CBString
//  Function      : 
//  Param         : CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_CBString(CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	DDP_Text(pDX, id, member, pszPropName, pDispatch);
}

//*****************************************************************
//  Function Name : DDP_CBStringExact
//  Function      : 
//  Param         : CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_CBStringExact(CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	DDP_Text(pDX, id, member, pszPropName, pDispatch);
}

//*****************************************************************
//  Function Name : DDP_LBIndex
//  Function      : 
//  Param         : CDataExchange* pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_LBIndex(CDataExchange* pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_I4, &member);
			PropDispDriver.DetachDispatch();

			SendMessage(hWndCtrl, LB_SETCURSEL, member, 0L);
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_LBINDEX, id, (LPVOID)&member, VT_I4, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);
/*
			member = (int)::SendMessage(hWndCtrl, LB_GETCURSEL, 0, 0L);

			_variant_t var((short)member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}
//*****************************************************************
//  Function Name : DDX_COLOR_CBIndex
//  Function      : 
//  Param         : CDataExchange* pDX, int nIDC, int& index
//  Return        : void AFXAPI 
//  Create        : 김창하, 2006/05/02
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDX_COLOR_CBIndex(CDataExchange* pDX, int nIDC, int& index)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);

	CColorPickerCB* pPicker = (CColorPickerCB*) CWnd::FromHandle(hWndCtrl);
	if ( pDX->m_bSaveAndValidate )		// Get
	{
		index = pPicker->GetCurSel();
	}
	else								// Set
	{
		pPicker->SetCurSel( index );
	}

#if FALSE
	if (pDX->m_bSaveAndValidate)
		index = (int)::SendMessage(hWndCtrl, CB_GETCURSEL, 0, 0L);
	else

		::SendMessage(hWndCtrl, CB_SETCURSEL, (WPARAM)index, 0L);
#endif
}

//*****************************************************************
//  Function Name : DDP_COLOR_CBIndex
//  Function      : 
//  Param         : CDataExchange* pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI 
//  Create        : 김창하, 2006/05/02
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_COLOR_CBIndex(CDataExchange* pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

// --> [Edit]  김창하 2006/05/02
	CColorPickerCB* pPicker = (CColorPickerCB*) CWnd::FromHandle(hWndCtrl);
	ASSERT ( pPicker);
// <-- [Edit]  김창하 2006/05/02

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_I4, &member);
			PropDispDriver.DetachDispatch();
			
			pPicker->SetCurSel( member );
//			SendMessage(hWndCtrl, CB_SETCURSEL, member, 0L);
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_COLORINDEX, id, (LPVOID)&member, VT_I4, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);
/*
			member = (int)::SendMessage(hWndCtrl, CB_GETCURSEL, 0, 0L);

			_variant_t var((short)member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}

//*****************************************************************
//  Function Name : DDP_CBIndex
//  Function      : 
//  Param         : CDataExchange* pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_CBIndex(CDataExchange* pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_I4, &member);
			PropDispDriver.DetachDispatch();

			SendMessage(hWndCtrl, CB_SETCURSEL, member, 0L);
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_CBINDEX, id, (LPVOID)&member, VT_I4, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);
/*
			member = (int)::SendMessage(hWndCtrl, CB_GETCURSEL, 0, 0L);

			_variant_t var((short)member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}

//*****************************************************************
//  Function Name : DDP_Check
//  Function      : 
//  Param         : CDataExchange*pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Check(CDataExchange*pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			BOOL bTemp = FALSE;
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_BOOL, &bTemp);
			PropDispDriver.DetachDispatch();

			if (bTemp)
			{
				member = 1;
			}
			else
			{
				member = 0;
			}
			SendMessage(hWndCtrl, BM_SETCHECK, member, 0L);
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_CHECK, id, (LPVOID)&member, VT_I4, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);
/*
			member = (int)::SendMessage(hWndCtrl, BM_GETCHECK, 0, 0L);

			_variant_t var((short)member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}

//*****************************************************************
//  Function Name : DDP_Radio
//  Function      : 
//  Param         : CDataExchange*pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch
//  Return        : void AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_Radio(CDataExchange*pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch)
{
	USES_CONVERSION;

	COleDispatchDriver PropDispDriver;
	CString strWindowText;
	HWND hWndCtrl = pDX->PrepareCtrl(id);

	DISPID dwDispID;

	LPCOLESTR lpOleStr = T2COLE(pszPropName);
	if (SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
	{
		if (pDX->m_bSaveAndValidate == 0)
		{
			PropDispDriver.AttachDispatch(pDispatch, FALSE);
			PropDispDriver.GetProperty(dwDispID, VT_I4, &member);
			PropDispDriver.DetachDispatch();

			int iButton = 0;
			do
			{
				if (::SendMessage(hWndCtrl, WM_GETDLGCODE, 0, 0L) & DLGC_RADIOBUTTON)
				{
					// select button
					::SendMessage(hWndCtrl, BM_SETCHECK, (iButton == member), 0L);
				}
				else
				{
					TRACE0("Warning: skipping non-radio button in group.\n");
				}
				hWndCtrl = ::GetWindow(hWndCtrl, GW_HWNDNEXT);
				iButton++;

			} while (hWndCtrl != NULL &&
				!(GetWindowLong(hWndCtrl, GWL_STYLE) & WS_GROUP));
		}
		else
		{
			DDP_DATA * pDDP_DATA = new DDP_DATA(TYPE_RADIO, id, (LPVOID)&member, VT_I4, dwDispID);
			m_ArrayDDPData.Add((CObject *)pDDP_DATA);
/*
			member = -1;

			int iButton = 0;
			do
			{
				if (::SendMessage(hWndCtrl, WM_GETDLGCODE, 0, 0L) & DLGC_RADIOBUTTON)
				{
					// control in group is a radio button
					if (::SendMessage(hWndCtrl, BM_GETCHECK, 0, 0L) != 0)
					{
						ASSERT(member == -1);    // only set once
						member = iButton;
					}
					iButton++;
				}
				else
				{
					TRACE0("Warning: skipping non-radio button in group.\n");
				}
				hWndCtrl = ::GetWindow(hWndCtrl, GW_HWNDNEXT);

			} while (hWndCtrl != NULL &&
				!(GetWindowLong(hWndCtrl, GWL_STYLE) & WS_GROUP));

			_variant_t var((short)member);
			SetCtlProperty(var, dwDispID, pDispatch);
*/
		}
	}
}


//*****************************************************************
//  Function Name : DDP_PostProcessing
//  Function      : 
//  Param         : CDataExchange *pDX, IDispatch *pDispatch
//  Return        : void AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_PostProcessing(CDataExchange *pDX, IDispatch *pDispatch)
{
	if (pDX->m_bSaveAndValidate == 1)
	{
		int nCount = m_ArrayDDPData.GetSize();
		DDP_DATA * pDDPDATA;
		short member = -1;
		int iButton = 0;
		for (int i = 0; i < nCount; i++)
		{
			pDDPDATA = (DDP_DATA *)m_ArrayDDPData.GetAt(i);
			
			HWND hWndCtrl = pDX->PrepareCtrl(pDDPDATA->m_nCtrlId);
			if (hWndCtrl == NULL)
				continue;

			_variant_t var;
			switch(pDDPDATA->m_nFuncType)
			{
				case TYPE_TEXT:
					switch(pDDPDATA->m_nType)
					{
						case VT_I1:
							var = *((BYTE *)pDDPDATA->m_lpMember);
							break;
						case VT_I2:
							var = *((short *)pDDPDATA->m_lpMember);
							break;
						case VT_I4:
							var = *((long *)pDDPDATA->m_lpMember);
							break;
						case VT_R4:
							var = *((float *)pDDPDATA->m_lpMember);
							break;
						case VT_R8:
							var = *((double *)pDDPDATA->m_lpMember);
							break;
						case VT_BSTR:
							var = *(CString *)pDDPDATA->m_lpMember;
							break;
						default :
							continue;
							break;
					}
					break;
				case TYPE_CHECK:
					*((short *)pDDPDATA->m_lpMember) = (short)::SendMessage(hWndCtrl, BM_GETCHECK, 0, 0L);
					var = *((short *)pDDPDATA->m_lpMember);
					break;
// --> [Edit]  김창하 2006/05/02
				case TYPE_COLORINDEX:
					{
						CColorPickerCB* pPicker = (CColorPickerCB*) CWnd::FromHandle(hWndCtrl);
						int nColorIndex(-1);
						nColorIndex = pPicker->GetCurSel();

						*((short *)pDDPDATA->m_lpMember) = (short)nColorIndex;
						var = *((short *)pDDPDATA->m_lpMember);
					}
					break;
// <-- [Edit]  김창하 2006/05/02
				case TYPE_CBINDEX:
					*((short *)pDDPDATA->m_lpMember) = (short)::SendMessage(hWndCtrl, CB_GETCURSEL, 0, 0L);
					var = *((short *)pDDPDATA->m_lpMember);
					break;
				case TYPE_LBINDEX:
					*((short *)pDDPDATA->m_lpMember) = (short)::SendMessage(hWndCtrl, LB_GETCURSEL, 0, 0L);
					var = *((short *)pDDPDATA->m_lpMember);
					break;
				case TYPE_RADIO:
					member = -1;
					iButton = 0;
					do
					{
						if (::SendMessage(hWndCtrl, WM_GETDLGCODE, 0, 0L) & DLGC_RADIOBUTTON)
						{
							// control in group is a radio button
							if (::SendMessage(hWndCtrl, BM_GETCHECK, 0, 0L) != 0)
							{
								ASSERT(member == -1);    // only set once
								member = iButton;
							}
							iButton++;
						}
						else
						{
							TRACE0("Warning: skipping non-radio button in group.\n");
						}
						hWndCtrl = ::GetWindow(hWndCtrl, GW_HWNDNEXT);

					} while (hWndCtrl != NULL &&
						!(GetWindowLong(hWndCtrl, GWL_STYLE) & WS_GROUP));

					*((short *)pDDPDATA->m_lpMember) = member;
					var = *((short *)pDDPDATA->m_lpMember);
					break;
				default:
					continue;
					break;
			}
			SetCtlProperty(var, pDDPDATA->m_nDispID, pDispatch);
		}
		
		DDP_ArrayClean();
	}
}

//*****************************************************************
//  Function Name : DDP_ArrayClean
//  Function      : 
//  Param         : 없음
//  Return        : void AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void AFXAPI DDP_ArrayClean()
{
	int nCount = m_ArrayDDPData.GetSize();
	DDP_DATA * pDDPDATA;
	for (int i = 0; i < nCount; i++)
	{
		pDDPDATA = (DDP_DATA *)m_ArrayDDPData.GetAt(i);
		delete pDDPDATA;
	}
	m_ArrayDDPData.RemoveAll();
}

//*****************************************************************
//  Function Name : PX_Short
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, short& sValue, short sDefault
//  Return        : BOOL AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_Short(IPropertyBag* pPX, LPCTSTR pszPropName, short& sValue, short sDefault)
{
	CComVariant var(sValue);

	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE)
	{
		sValue = var.iVal;
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_UShort
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, USHORT& sValue, USHORT sDefault
//  Return        : BOOL AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_UShort(IPropertyBag* pPX, LPCTSTR pszPropName, USHORT& sValue, USHORT sDefault)
{
	CComVariant var(sValue);
	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE)
	{
		sValue = var.iVal;
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_Long
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, long& sValue, long sDefault
//  Return        : BOOL AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_Long(IPropertyBag* pPX, LPCTSTR pszPropName, long& sValue, long sDefault)
{
	CComVariant var(sValue);
	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE)
	{
		sValue = var.lVal;
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_ULong
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, ULONG& sValue, ULONG sDefault
//  Return        : BOOL AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_ULong(IPropertyBag* pPX, LPCTSTR pszPropName, ULONG& sValue, ULONG sDefault)
{
	CComVariant var((long)sValue);
	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE)
	{
		sValue = var.lVal;
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_Color
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, OLE_COLOR& sValue, OLE_COLOR sDefault
//  Return        : BOOL AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_Color(IPropertyBag* pPX, LPCTSTR pszPropName, OLE_COLOR& sValue, OLE_COLOR sDefault)
{
	CComVariant var((long)sValue);
	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE)
	{
		sValue = var.lVal;
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_Bool
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, BOOL& sValue, BOOL sDefault
//  Return        : BOOL AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_Bool(IPropertyBag* pPX, LPCTSTR pszPropName, BOOL& sValue, BOOL sDefault)
{
	CComVariant var(sValue);
	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE)
	{
		if (var.boolVal)
		{
			sValue = TRUE;
		}
		else
		{
			sValue = FALSE;
		}
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_String
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, CString& sValue, const CString & sDefault
//  Return        : BOOL AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_String(IPropertyBag* pPX, LPCTSTR pszPropName, CString& sValue, const CString & sDefault)
{
	CComVariant var(sValue);
	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE && var.vt == VT_BSTR)
	{
		sValue = var.bstrVal;
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_String
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, CString& sValue, LPCTSTR sDefault
//  Return        : BOOL AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_String(IPropertyBag* pPX, LPCTSTR pszPropName, CString& sValue, LPCTSTR sDefault)
{
	CComVariant var(sValue);
	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE)
	{
		sValue = var.bstrVal;
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_Currency
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, CY& sValue, CY sDefault
//  Return        : BOOL AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_Currency(IPropertyBag* pPX, LPCTSTR pszPropName, CY& sValue, CY sDefault)
{
	CComVariant var(sValue);
	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE)
	{
		sValue = var.cyVal;
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_Float
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, float& sValue, float sDefault
//  Return        : BOOL AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_Float(IPropertyBag* pPX, LPCTSTR pszPropName, float& sValue, float sDefault)
{
	CComVariant var(sValue);
	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE)
	{
		sValue = var.fltVal;
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_Double
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, double& sValue, double sDefault
//  Return        : BOOL AFXAPI
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_Double(IPropertyBag* pPX, LPCTSTR pszPropName, double& sValue, double sDefault)
{
	CComVariant var(sValue);
	BOOL bRet;
	bRet = PX_ExchangeProp(pPX, pszPropName, var);
	if (bRet == TRUE)
	{
		sValue = var.dblVal;
		
	}
	else
	{
		sValue = sDefault;
	}
	var.Clear();
	return bRet;
}

//*****************************************************************
//  Function Name : PX_ExchangeProp
//  Function      : 
//  Param         : IPropertyBag* pPX, LPCTSTR pszPropName, CComVariant &var
//  Return        : BOOL AFXAPI 
//  Create        : 
//  Update        : 김준안, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL AFXAPI PX_ExchangeProp(IPropertyBag* pPX, LPCTSTR pszPropName, CComVariant &var)
{
	USES_CONVERSION;

	if (pPX == NULL)
	{
		return FALSE;
	}

	HRESULT hr = pPX->Read(T2OLE(pszPropName), &var, NULL);
	if (FAILED(hr))
	{
		return FALSE;
	}
	
	return TRUE;
}
