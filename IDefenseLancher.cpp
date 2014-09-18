// IDefenseLancher.cpp: implementation of the CIDefenseLancher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "findTest.h"
#include "IDefenseLancher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIDefenseLancher::CIDefenseLancher()
{
	m_hDll = NULL;
}

CIDefenseLancher::~CIDefenseLancher()
{

}
// 한글 i-Defense 실행
BOOL CIDefenseLancher::Init_Kor()
{
	m_hDll = LoadLibrary(_T("idfapi.dll"));
	if(NULL == m_hDll) 
	{
		return FALSE;
	}
	
	idfAutoStart_t lpidfAutoStart2 = (idfAutoStart_t)GetProcAddress(m_hDll,_T("idfAutoStartEx2")); 

	if(lpidfAutoStart2)
	{                     /* 고객사마다 다름,  */
		lpidfAutoStart2("idefense/koreastock_20110603",
			0,
			1,
			0x00007,
			"한화증권|koreastock|hwrun.exe|HwStarter.exe|EZMain.exe|EZLogIn.exe|"	, /* NULL이면 호출 프로그램의 Process ID로 검사함 */
			"한화증권");  
	}
	FreeLibrary(m_hDll);
	return TRUE;
}

// 영문 i-Defense 실행
BOOL CIDefenseLancher::Init_Eng()
{
	m_hDll = LoadLibrary(_T("idfapi.dll"));
	if(NULL == m_hDll) 
	{
		return FALSE;
	}
	
	idfAutoStart_t lpidfAutoStart2 = (idfAutoStart_t)GetProcAddress(m_hDll,_T("idfAutoStartEx2")); 
	
	if(lpidfAutoStart2)
	{                     /* 고객사마다 다름,  */
		lpidfAutoStart2("idefense/koreastock_20110603",
			0,
			1,
			0x0007,
			"한화증권|koreastock|hwrun.exe|HwStarter.exe|EZMain.exe|EZLogIn.exe|"	, /* NULL이면 호출 프로그램의 Process ID로 검사함 */
			"한화증권"); 
	}
	FreeLibrary(m_hDll);
	return TRUE;
}

// i-Defense 종료
BOOL CIDefenseLancher::IdfStop()
{
	m_hDll = LoadLibrary(_T("idfapi.dll"));
	if(NULL == m_hDll) 
	{
		return FALSE;
	}
	
	idfUnloadApp_t  lpidfUnloadApp = (idfUnloadApp_t)GetProcAddress(m_hDll,_T("idfUnloadApp")); 
	
	if(lpidfUnloadApp)
	{                     
		lpidfUnloadApp();
	}
	FreeLibrary(m_hDll);
	return TRUE;
}

// 바이러스(무료백신)
BOOL CIDefenseLancher::IdfVirusStart()
{
	m_hDll = LoadLibrary(_T("idfapi.dll"));
	if(NULL == m_hDll) 
	{
		return FALSE;
	}
	
	idfVirusStart_t lpidfVirusStart2 = (idfVirusStart_t)GetProcAddress(m_hDll, _T("idfVirusStartEx2"));
	
	if(lpidfVirusStart2)
	{                     
		lpidfVirusStart2("idefense/koreastock_20110603", 
			0, 
			1, 
			0x001, 
			"", 
			"한화증권");	//KJI 20091130 (원도우7 관련 킹스에서 수정)
	}
	FreeLibrary(m_hDll);
	return TRUE;
}