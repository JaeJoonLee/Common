// LogMsg.h: interface for the CLogMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGMSG_H__915313FD_6519_45C4_9469_5B17947EE839__INCLUDED_)
#define AFX_LOGMSG_H__915313FD_6519_45C4_9469_5B17947EE839__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommHeaderDef.h"

class CLogMsg  
{
public:
	CLogMsg();
	CLogMsg(CString strRootPath);
	virtual ~CLogMsg();
	
public:
	CString	 m_strRootPath;
	LANGID	 m_dwLangID;

public:
	void	SetRunPathName(CString strPath)		{ m_strRootPath = strPath;	}
	void	SetLangeMode(LANGID dwLangID)		{ m_dwLangID	= dwLangID;	}

	BOOL	WriteLogMsg(CString strLogMsg, CString& strMsg, int nErrorCode = -1);
    BOOL	SetLogMsgWriteToFile(CString strMsg, int nLogType = LOG_TYPE_COMMS, BOOL bMode = TRUE);
	void	SetWriteConsol(char* lpData, BOOL bTitle = TRUE, BOOL bLine = FALSE);
};

#endif // !defined(AFX_LOGMSG_H__915313FD_6519_45C4_9469_5B17947EE839__INCLUDED_)
