//
#include "stdafx.h"
#include "_external.h"
#include "..\Builder\LinkInfoMng\KSLinkInfoMng.h"

BOOL _external::g_bTreadF	= TRUE;			//기본적으로 체결추이설정 TRUE
CString _external::g_sCommUFNM = GetRunTimePath() + _T("\\system\\CommsU.ini");
CString _external::g_sTreadFNM = GetRunTimePath() + _T("\\system\\TreadU.ini");

_external::_external()
{

}

_external::~_external()
{

}

void _external::__getReadFromEnvFile()
{
	//CommsU.ini 파일에서 체결추이F값을 읽어온다.
	CString sFileName(_T(""));
	
	int iFlag = GetPrivateProfileInt(_T("GRID_TREAD"), _T("Flag"), 1, g_sCommUFNM);
	iFlag ? g_bTreadF = TRUE : g_bTreadF = FALSE;
}

void _external::__setTreadFToFile(CString sTrCode, BOOL bTread)
{
	CString sValue(_T(""));
	bTread ? sValue = "1" : sValue = "0";
	WritePrivateProfileString(_T("CHECKFLAG"), sTrCode, sValue, g_sTreadFNM);
}

// 체결추이 옵션이 적용되는 화면여부.
BOOL _external::__isTreadTRCode(CString sTrCode)
{
	BOOL bRet = FALSE;
	//if(sTrCode.GetLength()>=4)
	//	sTrCode = sTrCode.Left(4);

	GetPrivateProfileInt(_T("TRCODELIST"), sTrCode, 0, g_sTreadFNM) ? bRet = TRUE : bRet = FALSE;
	return bRet;
}

// 거래량컬럼에 해당하는 ItemName
CString _external::__getVolumeName(CString sTrCode)
{
	CString sItemName(_T(""));
	char buff[100];
	memset(buff, 0x00, sizeof(buff));
	GetPrivateProfileString(_T("ITEMNAME"), sTrCode, _T("Lvolume"), buff, sizeof(buff), g_sTreadFNM);
	sItemName.Format("%s", buff);
	return sItemName;
}

int _external::__getTreadFlag(CString sTrCode)
{
	return GetPrivateProfileInt(_T("CHECKFLAG"), sTrCode, 1, g_sTreadFNM);
}
