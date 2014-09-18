#pragma once

#ifdef __BYTEWORXMVSYSFILES_DLL__
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

typedef struct BWXMFAILOVER
{
	int iErrorIndex;
	LPSTR pszReportError;
	BOOL (CALLBACK *MoveFile)(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName);
} BWXMFAILOVER;

extern "C"
{
	void __declspec(DLL_ATTR) BwxmSetLogLevel(int nLogLevel/* = INFO_INT*/);

	int	__declspec(DLL_ATTR) BwxmGetCount(LPCSTR szSysFolder);
	BOOL __declspec(DLL_ATTR) BwxmFileInfo(LPCSTR szSysFolder, int iIndex, LPSTR rszSourceBuf, int iSourceBufSize, LPSTR rszTargetBuf, int iTargetBufSize);
	BOOL __declspec(DLL_ATTR) BwxmMoveFiles(LPCSTR szSysFolder, BWXMFAILOVER* rpFailOver);
	void __declspec(DLL_ATTR) BwxmClear();
}
