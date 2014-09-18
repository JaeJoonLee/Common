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

#define LOG_FILENAME_COMMS		"%s/log/HwLogFile%s.log"	// ��� ���� �α� ����
#define LOG_FILENAME_STARTER	"%s/log/Starter.log"		// �α��� ���� �α� ����
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
// ��    ƾ    ��  :  WriteLogMsg
// ��          ��  :  ������ ���� �޼�����ȣ�� �ý��ۿ��� �������ڿ��� ����ϴ� �Լ� 
//						(FormatMessage�Լ� ��� )
// ��          ��  :  CString	strLogMsg		
//					  CString&	strErrorMsg
//					  int		nErrorCode
// ��          ��  :  ����
// ��    ��    ��  :  2002��10��30��    ��  â�� (��) �ѱ� �Ҹ���ġ
// ��  ��  ��  ��  :  
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
// ��    ƾ    ��  :  SetLogMsgWriteToFile
// ��          ��  :  �α������� �ۼ��ؼ� �޼����� ���� �Լ� 
// ��          ��  :  CString	strMsg	���� �޼��� ���ڿ�
//					  int		nLogType 0:��ŷα�, 1:�α��� �α�
//				      BOOL		bMode	TRUE:�ý���, FALSE:����� 	
// ��          ��  :  BOOL
// ��    ��    ��  :  2002��10��30��    ��  â�� (��) �ѱ� �Ҹ���ġ
// ��  ��  ��  ��  :  �޼��� ����)�����, �Լ���,�����ڵ�, �����޼��� 
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

	// ���� ��ϵ� �ǽð� ���Ű�� ���Ϸ� �ۼ��Ѵ�.
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

	// ����,�ð�,TYPE,�����,�Լ���,�����ڵ�,���� �޼���
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

	// �α� ���ϸ� üũ�Ѵ�.
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
