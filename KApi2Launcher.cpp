// KDefenseLancher.cpp: implementation of the CKDefenseLancher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KApi2Launcher.h"

#include <io.h>
#include <errno.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKApi2Launcher::CKApi2Launcher() :
	m_hDll(NULL),
	m_lpkdfAutoStart(NULL),
	m_lpkdfAutoStart_h(NULL),
	m_lpkdfGetVersion(NULL),
	m_lpkdfProtectModeOn(NULL),
	m_lpkdfProtectModeCheck(NULL),
#ifdef USE_KDFADDEDITCRTL
	m_lpkdfAddEditCtrl(NULL),
	m_lpkdfDelEditCtrl(NULL),
	m_lpkdfGetPassword(NULL), 
	m_lpkdfSetPassword(NULL), 
#endif
	m_lpkdfSelfCheckIntegrity(NULL),
	m_lpkdfSetImageDir(NULL),
	m_lpkdfExOption(NULL),
	m_bStart(false)
{
	loadKdfLibrary();
}

CKApi2Launcher::~CKApi2Launcher()
{
	kdfAutoStartClean();
}

bool CKApi2Launcher::loadKdfLibrary()
{
	if(m_hDll) return true;

	m_hDll = LoadLibrary(_T("kdfapi2.dll"));

	m_lpkdfAutoStart			= (kdfAutoStart_t)		GetProcAddress(m_hDll, "kdfAutoStart");
	m_lpkdfAutoStart_h			= (kdfAutoStart_h)		GetProcAddress(m_hDll, "kdfAutoStart_h");
	m_lpkdfGetVersion			= (kdfGetVersion_t)		GetProcAddress(m_hDll, "kdfGetVersion");
	m_lpkdfProtectModeOn		= (kdfProtectModeOn_t)	GetProcAddress(m_hDll, "kdfProtectModeOn");
	m_lpkdfProtectModeCheck		= (kdfProtectModeCheck_t)GetProcAddress(m_hDll,"kdfProtectModeCheck");
	m_lpkdfSelfCheckIntegrity	= (kdfSelfCheckIntegrity_t)GetProcAddress(m_hDll, "kdfSelfCheckIntegrity");

	m_lpkdfExOption				= (kdfExOption_t)GetProcAddress(m_hDll, "kdfExOption");
/*
	kdfAutoStartClean_t		lpkdfAutoStartClean
		= (kdfAutoStartClean_t)	GetProcAddress(m_hDll, _T("kdfAutoStartClean"));
*/
	m_lpkdfSetImageDir		= (kdfSetImageDir_t)	GetProcAddress(m_hDll, "kdfSetImageDir");

	m_lpkdfAddEditCtrl			= (kdfAddEditCtrl_t)GetProcAddress(m_hDll, "kdfAddEditCtrl");
	m_lpkdfDelEditCtrl			= (kdfDelEditCtrl_t)GetProcAddress(m_hDll, "kdfDelEditCtrl");
	m_lpkdfGetPassword			= (kdfGetPassword_t)GetProcAddress(m_hDll, "kdfGetPassword");
	m_lpkdfSetPassword			= (kdfSetPassword_t)GetProcAddress(m_hDll, "kdfSetPassword");

	if( m_lpkdfAutoStart == NULL		|| m_lpkdfGetVersion == NULL		||
		m_lpkdfProtectModeOn == NULL	|| m_lpkdfProtectModeCheck == NULL  || m_lpkdfAutoStart_h == NULL)
	{
#ifdef _DEBUG		
		OutputDebugString("[KLauncher] load function fail");
#endif
		this->freeKdfLibrary();
		
		return false;
	}

	return true;
}

void CKApi2Launcher::freeKdfLibrary()
{
	if(m_hDll)
	{
		m_lpkdfAutoStart			= NULL;
		m_lpkdfAutoStart_h			= NULL;
		m_lpkdfGetVersion			= NULL;
		m_lpkdfProtectModeOn		= NULL;
		m_lpkdfProtectModeCheck		= NULL;
		m_lpkdfSelfCheckIntegrity	= NULL;
		m_lpkdfSetImageDir			= NULL;
		m_lpkdfExOption				= NULL;

		m_lpkdfAddEditCtrl			= NULL;
		m_lpkdfDelEditCtrl			= NULL;
		m_lpkdfGetPassword			= NULL;
		m_lpkdfSetPassword			= NULL;

		
		FreeLibrary(m_hDll);
		m_hDll = NULL;
	}
}

bool CKApi2Launcher::kdfAutoStart(CString strRoot)
{
	if(m_hDll == NULL)
	{
		loadKdfLibrary();
		if(m_hDll == NULL) return false;
	}

// --> [Edit] BT.Jung 2009/12/26 버젼변경
	if(m_lpkdfSetImageDir)
	{
		CString strPath;
		if(strRoot.IsEmpty())
		{
			char szPath[1024];
			GetCurrentDirectory(sizeof(szPath), szPath);
			strPath.Format("%s\\image", szPath);
		}else
		{
			strPath.Format("%s\\image", strRoot);
		}

		m_lpkdfSetImageDir((LPSTR)(LPCTSTR)strPath);		// TrayIcon이 있는 폴더를 지정
	}
// <-- [Edit] BT.Jung 2009/12/26

	if(m_lpkdfAutoStart && m_bStart == false)
	{
		//ex1) kdfAutoStart(NULL, FALSE, 0x00010001); // Default Icon 사용(권고사항)
		//ex2) kdfAutoStart(NULL, FALSE, 0x0a010001); // 지정 Tray Icon 사용
		//ex3) kdfAutoStart(NULL, FALSE, 0x00020001); // Icon 사용 안함

		// Param1 : 추가될 SubClassing ClassName
		// Param3 : 상위 16bit - 사이트코드
// --> [Edit] BT.Jung 2009/12/26 버젼변경
//		if(m_lpkdfAutoStart(NULL, FALSE, 0x00010001) == FALSE)
		if(m_lpkdfAutoStart(NULL, FALSE, 0x27040001) == FALSE)
// <-- [Edit] BT.Jung 2009/12/26
		{
#ifdef _DEBUG
			OutputDebugString("[KLauncher] kdfAutoStart fail");
#endif
			return false;
		}
#ifdef _DEBUG
		else OutputDebugString("[KLauncher] kdfAutoStart");
#endif
		m_bStart = true;
	}
	else return false;

	// 확장 Options
	if(m_lpkdfExOption)
	{
		//m_lpkdfExOption(KDFINJ_EXTYPE_PROTECT_HANNUM, 0, 0, 0);				//한글 모드에서 숫자 보호 지원
		m_lpkdfExOption(KDFINJ_EXTYPE_KDFMOD_OPT, 0, 0, 0);
		// m_lpkdfExOption(KDFINJ_EXTYPE_BYPASS_STR, "ABCDEF", 0, 0);		//GetMsg에서 복호화할 문자열 "ABCDEF" 등록

		// m_lpkdfExOption(KDFINJ_EXTYPE_KDFMOD_OPT, 0, 0, 0);				//특수문자의 경우 GetMsg에서 복호화 한다.
		//BOOL bSub = FALSE;
		//m_lpkdfExOption(27, (char*)&bSub, NULL, NULL);

	}

	//-- 현재 보호모드인지 일반모드인지 알아낸다.
	m_bStart = (m_lpkdfProtectModeCheck() == 0)? false:true;

	return m_bStart;
	/*
	if(!m_bStart)
	{
		// 일반모드이면 보호모드로 변경
		if(!m_lpkdfProtectModeOn())
		{
			OutputDebugString("[KLauncher] protect mode on fail");
			return false;
		}
	}

	return true;
	*/
}

//--> 2011.09.14 jhj ThreadID 추가
bool CKApi2Launcher::kdfAutoStartH(CString strRoot, DWORD dwThreadID)
{
	if(m_hDll == NULL)
	{
		loadKdfLibrary();
		if(m_hDll == NULL) return false;
	}

// --> [Edit] BT.Jung 2009/12/26 버젼변경
	if(m_lpkdfSetImageDir)
	{
		CString strPath;
		if(strRoot.IsEmpty())
		{
			char szPath[1024];
			GetCurrentDirectory(sizeof(szPath), szPath);
			strPath.Format("%s\\image", szPath);
		}else
		{
			strPath.Format("%s\\image", strRoot);
		}

		m_lpkdfSetImageDir((LPSTR)(LPCTSTR)strPath);		// TrayIcon이 있는 폴더를 지정
	}
// <-- [Edit] BT.Jung 2009/12/26

	if(m_lpkdfAutoStart_h && m_bStart == false)
	{
		//ex1) kdfAutoStart(NULL, FALSE, 0x00010001); // Default Icon 사용(권고사항)
		//ex2) kdfAutoStart(NULL, FALSE, 0x0a010001); // 지정 Tray Icon 사용
		//ex3) kdfAutoStart(NULL, FALSE, 0x00020001); // Icon 사용 안함

		// Param1 : 추가될 SubClassing ClassName
		// Param3 : 상위 16bit - 사이트코드
// --> [Edit] BT.Jung 2009/12/26 버젼변경
//		if(m_lpkdfAutoStart(NULL, FALSE, 0x00010001) == FALSE)
		if(m_lpkdfAutoStart_h(NULL, FALSE, 0x27040001, dwThreadID) == FALSE)
// <-- [Edit] BT.Jung 2009/12/26
		{
#ifdef _DEBUG
			OutputDebugString("[KLauncher] kdfAutoStart fail");
#endif
			return false;
		}
#ifdef _DEBUG
		else OutputDebugString("[KLauncher] kdfAutoStart");
#endif
		m_bStart = true;
	}
	else return false;

	// 확장 Options
	if(m_lpkdfExOption)
	{
		m_lpkdfExOption(KDFINJ_EXTYPE_KDFMOD_OPT, 0, 0, 0);
	}

	//-- 현재 보호모드인지 일반모드인지 알아낸다.
	m_bStart = (m_lpkdfProtectModeCheck() == 0)? false:true;

	return m_bStart;
}
//<--

bool CKApi2Launcher::kdfAutoStartClean()
{
 	if(m_hDll && m_bStart)
	{
		kdfAutoStartClean_t		lpkdfAutoStartClean
			= (kdfAutoStartClean_t)	GetProcAddress(m_hDll, "kdfAutoStartClean");

		if(lpkdfAutoStartClean)
		{
			lpkdfAutoStartClean();
			freeKdfLibrary();
			m_bStart = false;
			return true;
		}
	}

	return false;
}


void CKApi2Launcher::kdfAddEditCtrl(HWND hWnd, HWND hWnd_main)
{
	if(m_lpkdfAddEditCtrl)
	{
		m_lpkdfAddEditCtrl(hWnd, hWnd_main);
	}
}

int CKApi2Launcher::kdfGetPassword(HWND hWnd, char *pRetBuf, int nRetBufSize)
{
	if(m_lpkdfGetPassword)
	{
		return m_lpkdfGetPassword(hWnd, pRetBuf, nRetBufSize);
	}

	return -1;
}

// 2011.05 jhj 
int CKApi2Launcher::kdfExOption(int nType, char *pOption1, char *pOption2, char *pOption3)
{
	if(m_lpkdfExOption)
	{
		//한글 모드에서 숫자 보호 지원
		return m_lpkdfExOption(nType, pOption1, pOption2, pOption3);
	}
	return 0;
}

//--> 2011.08 jhj error report 
int CKApi2Launcher::kdfSetPassword(HWND hWnd, char *pRetBuf, int nRetBufSize)
{
	if(m_lpkdfSetPassword)
	{
		return m_lpkdfSetPassword(hWnd, pRetBuf, nRetBufSize);
	}

	return -1;
}
//<--