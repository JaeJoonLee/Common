///////////////////////////////////////////////////////////////////////////////
//
//	프로그램명 : RegStrValue.cpp 
//	작  성  자 : 안정일
//	작성  일자 : 1999. 8.
//	기      능 : 레지스트리 값 세팅/얻어오기
//	실행  방법 : 
//  주의  사항 : 
//
///////////////////////////////////////////////////////////////////////////////
//
//  변경  내역 : 
//		변경일			변경자		변경사유 및 내용 
//
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "afxwin.h"
#include "RegStrValue.h"

void CRegistry::SetStrValue(HKEY hMainKey,CString strKey,CString strSubKey,CString strKeyValue)
{

	HKEY hKey;
	DWORD type; 

	::RegCreateKeyEx(hMainKey,
				 (LPCTSTR)strKey,0,
				 NULL,
				 REG_OPTION_NON_VOLATILE ,
				 KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS ,
				 NULL,
				 &hKey,
				 &type
				 );

	::RegSetValueEx(hKey,
				(LPCTSTR)strSubKey,
				0,
				REG_SZ,
				(const BYTE *)(LPCTSTR)strKeyValue,
				(DWORD) strKeyValue.GetLength()
				);

	::RegCloseKey(hKey);
}

CString CRegistry::GetStrValue(HKEY Hkey,CString strkey, CString strsubkey,CString strRValue)
{
   LONG err;
   HKEY openKey;
   BYTE Data[128];
   DWORD type;
   DWORD size=sizeof(Data);

   err=::RegOpenKey(Hkey,strkey,&openKey);

   if(ERROR ==err)
	 err=::RegQueryValueEx(openKey,strsubkey,0,&type,Data,&size);

	if(err==ERROR_SUCCESS)
	{
	 ::RegCloseKey(openKey);
	 CString str(Data);
	 return str;
	}
	::RegCloseKey(openKey);

	return strRValue;
}
