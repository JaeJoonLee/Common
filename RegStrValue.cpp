///////////////////////////////////////////////////////////////////////////////
//
//	���α׷��� : RegStrValue.cpp 
//	��  ��  �� : ������
//	�ۼ�  ���� : 1999. 8.
//	��      �� : ������Ʈ�� �� ����/������
//	����  ��� : 
//  ����  ���� : 
//
///////////////////////////////////////////////////////////////////////////////
//
//  ����  ���� : 
//		������			������		������� �� ���� 
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
