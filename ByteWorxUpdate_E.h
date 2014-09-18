/*==============================================================================
*	NAME      : ByteWorxUpdate_E.h
*	DESC      : [ByteWorx Update] DLL Class Attributes/Methods Declaration
*	AUTHOR    : Justin     : 2007/07/05 : Framework Development Team
*	VERIFY    : 
*	HISTORY
*  ---------------------------------------------------------------------------  
*	-- 2007/07/05 : Justin     : Initial Version
*	
==============================================================================*/
#pragma once

#ifdef __BYTEWORXUPDATE_DLL__
#define DLL_ATTR	dllexport
#else
#define	DLL_ATTR	dllimport
#endif

#ifndef LOGLEVELINT
#define LOGLEVELINT
	enum LogLevelInt
	{
		OFF_INT = INT_MAX,
		FATAL_INT = 50000,
		ERROR_INT = 40000,
		WARN_INT = 30000,
		INFO_INT = 20000,
		DEBUG_INT = 10000,
		TRACE_INT = 5000,
		ALL_INT = INT_MIN,
	};
#endif // LOGLEVELINT

extern "C"
{
	void __declspec(DLL_ATTR) BwxSetLogLevel(int nLogLevel/* = INFO_INT*/);

	enum CheckFlags {
		CheckNone = 0x0,
		CheckFull = 0x01,
		CheckExistence = 0x80,
		CheckFullExistence = CheckFull | CheckExistence,
	};

	void __declspec(DLL_ATTR) BwxEnableFastCheck(BOOL bEnable);
	void __declspec(DLL_ATTR) BwxEnableVerifyFiles(BOOL bEnable);

	int	__declspec(DLL_ATTR) BwxCheckVerFiles_2(HWND hProgWnd, UINT iProgMsgID, LPCSTR szProjectName,
											LPCSTR szProjectRootPath, UINT nCheckFlags, LPCSTR szIP,
											UINT iPort, int* rpiStatusCode, LPSTR rpStatusBuf, int iStatusBufSize,
											UINT iTimeout);

	int	__declspec(DLL_ATTR) BwxRealTimeUpdate(HWND hProgWnd, UINT iProgMsgID, LPCSTR szProjectName,
											LPCSTR szProjectRootPath, LPCSTR szShortPath_FileName,
											LPCSTR szIP, UINT iPort, UINT iTimeout);

	int	__declspec(DLL_ATTR) BwxRealTimeUpdate_2(HWND hProgWnd, UINT iProgMsgID, LPCSTR szProjectName,
											LPCSTR szProjectRootPath, LPCSTR szShortPath_FileName,
											LPCSTR szIP, UINT iPort, UINT iTimeout);

	int	__declspec(DLL_ATTR) BwxGetFullFile(HWND hProgWnd, UINT iProgMsgID, LPCSTR szProjectName,
											LPCSTR szProjectRootPath, LPCSTR szShortPath_FileName,
											LPCSTR szIP, UINT iPort, BOOL bMaster, UINT iTimeout);


	int	__declspec(DLL_ATTR) BwxCheckVerFiles_Http(HWND hProgWnd, UINT iProgMsgID, LPCSTR szProjectName,
											LPCSTR szProjectRootPath, UINT nCheckFlags, LPCSTR szUrl,
											int* rpiStatusCode, LPSTR rpStatusBuf, int iStatusBufSize,
											UINT iTimeout);

	int	__declspec(DLL_ATTR) BwxRealTimeUpdate_Http(HWND hProgWnd, UINT iProgMsgID, LPCSTR szProjectName,
											LPCSTR szProjectRootPath, LPCSTR szShortPath_FileName,
											LPCSTR szUrl, UINT iTimeout);

	int	__declspec(DLL_ATTR) BwxRealTimeUpdate_2_Http(HWND hProgWnd, UINT iProgMsgID, LPCSTR szProjectName,
											LPCSTR szProjectRootPath, LPCSTR szShortPath_FileName,
											LPCSTR szUrl, UINT iTimeout);

	int __declspec(DLL_ATTR) BwxGetFullFile_Http(HWND hProgWnd, UINT iProgMsgID, LPCSTR szProjectName,
											LPCSTR szProjectRootPath, LPCSTR szShortPath_FileName,
											LPCSTR szUrl, BOOL bMaster, UINT iTimeout);


	int	__declspec(DLL_ATTR) BwxGetFiles(LPCSTR szSysFolder, UINT iTimeout);

	int	__declspec(DLL_ATTR) BwxCancel();

	void __declspec(DLL_ATTR) BwxClose();


	int	__declspec(DLL_ATTR) BwxCreatePrjMgrReal(HWND hProgWnd, UINT iProgMsgID, LPCSTR szProjectName,
											LPCSTR szProjectRootPath);

	typedef BOOL (CALLBACK* PRJMGRENUMPROC)(LPCSTR szShortPath_FileName, BOOL bNeedUpdate, LPARAM lParam);
	int	__declspec(DLL_ATTR) BwxEnumPrjMgrReal(HWND hProgWnd, UINT iProgMsgID, LPCSTR szProjectName,
											LPCSTR szProjectRootPath,
											PRJMGRENUMPROC lpfn, LPARAM lParam);
}
