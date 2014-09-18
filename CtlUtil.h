#ifndef __CTLUTIL_H__
#define __CTLUTIL_H__

#include "AtlBase.h"
#include <comdef.h>

#define		TYPE_TEXT			0
#define		TYPE_CHECK			1
#define		TYPE_RADIO			2
#define		TYPE_CBINDEX		3
#define		TYPE_LBINDEX		4
#define		TYPE_COLORINDEX		5

struct DDP_DATA : public CObject
{
	DDP_DATA(int nFuncType, int nCtrlId, LPVOID lpMember,
		UINT nType, DISPID nDispID);

	int		m_nFuncType;
	int     m_nCtrlId;
	LPVOID  m_lpMember;
	UINT    m_nType;
	DISPID	m_nDispID;
};

void SetPropText(CString &strPropName, BYTE strData, IDispatch *pDispatch);
void SetPropText(CString &strPropName, short strData, IDispatch *pDispatch);
void SetPropText(CString &strPropName, int strData, IDispatch *pDispatch);
void SetPropText(CString &strPropName, long strData, IDispatch *pDispatch);
void SetPropText(CString &strPropName, float strData, IDispatch *pDispatch);
void SetPropText(CString &strPropName, double strData, IDispatch *pDispatch);
void SetPropText(CString &strPropName, CString strData, IDispatch *pDispatch);

void SetCtlProperty(_variant_t &var, DISPID dwDispID, IDispatch *pDispatch);

void GetPropText(CString &strPropName, BYTE *pstrData, IDispatch *pDispatch);
void GetPropText(CString &strPropName, short *pstrData, IDispatch *pDispatch);
void GetPropText(CString &strPropName, int *pstrData, IDispatch *pDispatch);
void GetPropText(CString &strPropName, long *pstrData, IDispatch *pDispatch);
void GetPropText(CString &strPropName, float *pstrData, IDispatch *pDispatch);
void GetPropText(CString &strPropName, double *pstrData, IDispatch *pDispatch);
void GetPropText(CString &strPropName, CString *strData, IDispatch *pDispatch);

// simple text operations
void AFXAPI DDP_Text(CDataExchange*pDX, int id, BYTE& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_Text(CDataExchange*pDX, int id, short& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_Text(CDataExchange*pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_Text(CDataExchange*pDX, int id, UINT& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_Text(CDataExchange*pDX, int id, long& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_Text(CDataExchange*pDX, int id, DWORD& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_Text(CDataExchange*pDX, int id, float& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_Text(CDataExchange*pDX, int id, double& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_Text(CDataExchange*pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_Check(CDataExchange*pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_Radio(CDataExchange*pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_LBString(CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_LBStringExact(CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_LBIndex(CDataExchange* pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_CBString(CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_CBStringExact(CDataExchange* pDX, int id, CString& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDP_CBIndex(CDataExchange* pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch);
// --> [Edit]  ±Ë√¢«œ 2006/05/02
void AFXAPI DDP_COLOR_CBIndex(CDataExchange* pDX, int id, int& member, LPCTSTR pszPropName, IDispatch *pDispatch);
void AFXAPI DDX_COLOR_CBIndex(CDataExchange* pDX, int nIDC, int& index);
// <-- [Edit]  ±Ë√¢«œ 2006/05/02

void AFXAPI DDP_PostProcessing(CDataExchange *pDX, IDispatch *pDispatch);
void AFXAPI DDP_ArrayClean();


/////////////////////////////////////////////////////////////////////////////
// Property-exchange (PX_) helper functions

BOOL AFXAPI PX_Short(IPropertyBag* pPX, LPCTSTR pszPropName, short& sValue, short sDefault);
BOOL AFXAPI PX_UShort(IPropertyBag* pPX, LPCTSTR pszPropName, USHORT& usValue, USHORT usDefault);
BOOL AFXAPI PX_Long(IPropertyBag* pPX, LPCTSTR pszPropName, long& lValue, long lDefault);
BOOL AFXAPI PX_ULong(IPropertyBag* pPX, LPCTSTR pszPropName, ULONG& ulValue, ULONG ulDefault);
BOOL AFXAPI PX_Color(IPropertyBag* pPX, LPCTSTR pszPropName, OLE_COLOR& clrValue, OLE_COLOR clrDefault);
BOOL AFXAPI PX_Bool(IPropertyBag* pPX, LPCTSTR pszPropName, BOOL& bValue, BOOL bDefault);
BOOL AFXAPI PX_String(IPropertyBag* pPX, LPCTSTR pszPropName, CString& strValue, const CString& strDefault);
BOOL AFXAPI PX_String(IPropertyBag* pPX, LPCTSTR pszPropName, CString& strValue, LPCTSTR lpszDefault);
BOOL AFXAPI PX_Currency(IPropertyBag* pPX, LPCTSTR pszPropName, CY& cyValue, CY cyDefault);
BOOL AFXAPI PX_Float(IPropertyBag* pPX, LPCTSTR pszPropName, float& floatValue, float floatDefault);
BOOL AFXAPI PX_Double(IPropertyBag* pPX, LPCTSTR pszPropName, double& doubleValue, double doubleDefault);
BOOL AFXAPI PX_ExchangeProp(IPropertyBag* pPX, LPCTSTR pszPropName, CComVariant &var);

#endif // __CTLUTIL_H__
