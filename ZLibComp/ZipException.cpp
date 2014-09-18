// ZipException.cpp: implementation of the CZipException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZipException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC( CZipException, CException)

CZipException::CZipException(int iCause, LPCTSTR lpszZipName, bool bDuringZip):CException(TRUE)
{
	m_iCause = iCause;

	if (lpszZipName)
		m_szFileName = lpszZipName;

	m_bDuringZip = bDuringZip;
	
}

CZipException::~CZipException()
{

}

void AfxThrowZipException(int iZipError, LPCTSTR lpszZipName, bool bZipFile)
{
	throw new CZipException(CZipException::ZipErrToCause(iZipError), lpszZipName, bZipFile);
}

int CZipException::ZipErrToCause(int iZipError)
{
	switch (iZipError)
	{
	case 2:
		return CZipException::needDict;
	case 1:
		return CZipException::streamEnd;
	case -1:
		return CZipException::errNo;
	case -2:
		return CZipException::streamError;
	case -3:
		return CZipException::dataError;
	case -4:
		return CZipException::memError;
	case -5:
		return CZipException::bufError;
	case -6:
		return CZipException::versionError;
	case -102:
		return CZipException::badFuncParam;
	case -103:
		return CZipException::badZipFile;
	case -105:
		return CZipException::badCrc;
	default:
		return CZipException::generic;
	}
	
}
