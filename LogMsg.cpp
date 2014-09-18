// LogMsg.cpp: implementation of the CLogMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define LOG_FILENAME_COMMS		"%s/log/HwLogFile%s.log"	// 통신 관련 로그 저장
#define LOG_FILENAME_STARTER	"%s/log/Starter.log"		// 로그인 관련 로그 저장
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogMsg::CLogMsg()
{
	m_dwLangID		= ::GetSystemDefaultLangID();
}

CLogMsg::CLogMsg(CString strRootPath)
{
	m_strRootPath	= strRootPath;
	m_dwLangID		= ::GetSystemDefaultLangID();
}

CLogMsg::~CLogMsg()
{

}


//*****************************************************************************
// 루    틴    명  :  WriteLogMsg
// 기          능  :  지정한 에러 메세지번호로 시스템에서 에러문자열을 취득하는 함수 
//						(FormatMessage함수 사용 )
// 입          력  :  CString	strLogMsg		
//					  CString&	strErrorMsg
//					  int		nErrorCode
// 출          력  :  없음
// 작    성    자  :  2002년10월30일    김  창하 (주) 한국 소리마치
// 수  정  이  력  :  
//*****************************************************************************
BOOL CLogMsg::WriteLogMsg(CString strLogMsg, 
						  CString& strErrorMsg, 
						  int nErrorCode/*=-1*/)
{
	if ( nErrorCode > 0  )
	{
		LPVOID lpMsgBuf;
		CString strMsg;
		DWORD	dwRet;
		dwRet = ::FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | 
								  FORMAT_MESSAGE_FROM_SYSTEM | 
								  FORMAT_MESSAGE_IGNORE_INSERTS,
								  NULL, 
								  (DWORD)nErrorCode, 
								  m_dwLangID,
								  (LPTSTR) &lpMsgBuf,
								  0, 
								  NULL);
		if ( dwRet > 0 )
		{
			strMsg.Format( strLogMsg, (DWORD)nErrorCode, (LPCTSTR)lpMsgBuf );
			strMsg.TrimRight("\r\n");

			LocalFree ( lpMsgBuf );
		}
		else
		{
			DWORD dwError = ::GetLastError();
			strMsg.Format(strLogMsg, (DWORD) nErrorCode, "Not Defined Of ErrorCode...");
		}
		strErrorMsg = strMsg;
		strLogMsg   = strMsg;

		return SetLogMsgWriteToFile(strLogMsg);
	}
	return FALSE;
}


//*****************************************************************************
// 루    틴    명  :  SetLogMsgWriteToFile
// 기          능  :  로그파일을 작성해서 메세지를 쓰는 함수 
// 입          력  :  CString	strMsg	에러 메세지 문자열
//					  int		nLogType 0:통신로그, 1:로그인 로그
//				      BOOL		bMode	TRUE:시스템, FALSE:사용자 	
// 출          력  :  BOOL
// 작    성    자  :  2002년10월30일    김  창하 (주) 한국 소리마치
// 수  정  이  력  :  메세지 형식)모쥴명, 함수명,에러코드, 에러메세지 
//*****************************************************************************
BOOL CLogMsg::SetLogMsgWriteToFile(CString strMsg, int nLogType, BOOL bMode /*= TRUE*/)
{
	CString	strLog;
	CString strTime;
	
	CString strLogFileName;
	char* pLogBuf;
	int nLogLen;

	if (m_strRootPath.IsEmpty())
		return FALSE;

	// 현재 등록된 실시간 등록키를 파일로 작성한다.
	if (nLogType ==LOG_TYPE_REGISTERED_REALKEY)
	{		
		CStdioFile dataFile;
		char szFileName[MAX_PATH];
		sprintf_s(szFileName, "%s\\temp\\RealMng.txt", m_strRootPath);
		if (dataFile.Open(szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
		{
			dataFile.WriteString(strMsg);
			dataFile.Close();

			char szExe[MAX_PATH];
			sprintf_s(szExe, "notepad.exe %s", szFileName);
			WinExec(szExe, SW_SHOWNORMAL);
		}
		return FALSE;
	}

	// 일자,시간,TYPE,모쥴명,함수명,에러코드,에러 메세지
	CTime theTime = CTime::GetCurrentTime();
	strTime = theTime.Format("%Y/%m/%d,%X,");

	if (bMode)
		strLog.Format("%sS:", theTime.Format( "%Y/%m/%d,%X," ));
	else
		strLog.Format("%sU:", theTime.Format( "%Y/%m/%d,%X," ));

	nLogLen = strLog.GetLength() + strMsg.GetLength();
	pLogBuf = new char[nLogLen + 2];
	memcpy(pLogBuf, strLog.GetBuffer(0), strLog.GetLength());
	memcpy(pLogBuf + strLog.GetLength(), strMsg.GetBuffer(0), strMsg.GetLength());
	memcpy(pLogBuf + nLogLen, "\r\n", 2);
	
	nLogLen += 2;

	// 로그 파일명를 체크한다.
	if (nLogType == LOG_TYPE_STARTER)
		strLogFileName.Format(LOG_FILENAME_STARTER, m_strRootPath);
	else
		strLogFileName.Format(LOG_FILENAME_COMMS, m_strRootPath, theTime.Format("%Y%m%d"));
	
	CFile	theFile;
	if (!theFile.Open(strLogFileName.GetBuffer(0), CFile::modeWrite))
	{ 
		if (!theFile.Open(strLogFileName.GetBuffer(0),
						CFile::modeReadWrite | CFile::shareCompat | CFile::modeCreate))
		{
			delete[] pLogBuf;
			return FALSE;
		}	
	}

	DWORD lLength = (DWORD)theFile.GetLength();
	theFile.Seek(lLength, CFile::current);
	theFile.Write(pLogBuf, nLogLen);
	theFile.Close();

	delete[] pLogBuf;

	return TRUE;
}
void CLogMsg::SetWriteConsol(char* lpData, 
								BOOL bTitle/* = TRUE*/, 
								BOOL bLine /*= FALSE*/)
{
	if ( bTitle )
	{
		SetConsoleTitle( lpData );
	}
	else
	{
		int nLen = lstrlen( lpData) ;
		HANDLE hOutConsol = ::GetStdHandle(STD_OUTPUT_HANDLE);
		if(  nLen > 0 && hOutConsol != INVALID_HANDLE_VALUE )
		{           
			::WriteConsole( hOutConsol, lpData, nLen, (LPDWORD)&nLen, NULL ) ; 
			if ( bLine )
				::WriteConsole( hOutConsol, "\n",  1,	   (LPDWORD)&nLen, NULL ) ; 
		}
	}
}
