#pragma once

#define	BWX_MAX_PATH		1024

#define _BWX_WPARAM_LEV1		10
#define _BWX_WPARAM_LEV2		20
#define _BWX_WPARAM_LEV3		30
#define _BWX_WPARAM_DOWNLOAD	80
#define _BWX_WPARAM_MOVEFILE	90

enum _BWX_LEV1_MODE
{
	BL1M_DOWNLOAD_STATUS		= 1,
	BL1M_DOWNLOAD_PRJMGR,
	BL1M_READ_LOCAL_PRJMGR,
	BL1M_READ_NEW_PRJMGR,
	BL1M_VERCHECK_PRJMGR,
	BL1M_DOWNLOAD_FILES,
	BL1M_VERUPDATE_FILES,
	BL1M_MOVE_FILES,
	BL1M_MOVE_NEW_PRJMGR,
	BL1M_VERIFY_FILES,
	BL1M_VEREND
};

struct _BWX_LEV1_STATUS
{
	int		iCurr;									// _BVM_LEV1_MODE
	int		iTotal;									// = BTM_VEREND
	int		iRate;									// iCurrMode / iTotalModes
};

struct _BWX_LEV2_STATUS
{
	int		iLev1Mode;
	int		iCurr;
	int		iTotal;
	int		iRate;
	char	szMsg[BWX_MAX_PATH];					// 현재 정보
};

struct _BWX_LEV3_STATUS
{
	int		iCurr;									// 현재 크기
	int		iTotal;									// 총 크기
	int		iRate;									// iCurrSize / iFileSize * 100
};

struct _BWX_DOWNLOAD_STATUS
{
	LPCSTR	pszProjectName;
	LPCSTR	pszServerFilePath;
	LPCSTR	pszLocalFilePath;
};

struct _BWX_MOVEFILE_STATUS
{
	LPCSTR	pszExistingFileName;
	LPCSTR	pszNewFileName;
};
