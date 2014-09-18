// MacAddress.h: interface for the CMacAddress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MACADDRESS_H__3002E419_B62A_4C81_A05A_D9D18D5BF1C8__INCLUDED_)
#define AFX_MACADDRESS_H__3002E419_B62A_4C81_A05A_D9D18D5BF1C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMacAddress  
{
public:
	CMacAddress();
	virtual ~CMacAddress();

	CString GetMacAddress(CString strIP);
	BOOL GetMacAddress(BYTE *byteMacAddress, CString strIP=_T(""));
	CString GetMacAddress();

private:
	CString getIP();
	CString RegGetIP();
	CString GetStrValue(HKEY Hkey,CString strkey, CString strsubkey,CString strRValue);
};

#endif // !defined(AFX_MACADDRESS_H__3002E419_B62A_4C81_A05A_D9D18D5BF1C8__INCLUDED_)
