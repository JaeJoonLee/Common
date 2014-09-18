// LogEncode.h: interface for the CLogEncode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGENCODE_H__915313FD_6519_45C4_9469_5B17947EE839__INCLUDED_)
#define AFX_LOGENCODE_H__915313FD_6519_45C4_9469_5B17947EE839__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogEncode
{
public:

//	char cEncOldPass[5] = "퇫빓"; // 상용조합형으로 "자동" 
//	char cEncNewPass[2];
	char EncOldPass[10];
	char EncNewPass[10];

	CLogEncode();
	virtual ~CLogEncode();

	void GenNewPassword(int StrLen);
	void EncryptStr(char *pStr, int StrLen);
	void DecryptStr(char *pStr, int StrLen);
};

#endif // !defined(AFX_LOGENCODE_H__915313FD_6519_45C4_9469_5B17947EE839__INCLUDED_)
