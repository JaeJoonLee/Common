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
// �ѱ� i-Defense ����
BOOL CIDefenseLancher::Init_Kor()
{
	m_hDll = LoadLibrary(_T("idfapi.dll"));
	if(NULL == m_hDll) 
	{
		return FALSE;
	}
	
	idfAutoStart_t lpidfAutoStart2 = (idfAutoStart_t)GetProcAddress(m_hDll,_T("idfAutoStartEx2")); 

	if(lpidfAutoStart2)
	{                     /* ���縶�� �ٸ�,  */
		lpidfAutoStart2("idefense/koreastock_20110603",
			0,
			1,
			0x00007,
			"��ȭ����|koreastock|hwrun.exe|HwStarter.exe|EZMain.exe|EZLogIn.exe|"	, /* NULL�̸� ȣ�� ���α׷��� Process ID�� �˻��� */
			"��ȭ����");  
	}
	FreeLibrary(m_hDll);
	return TRUE;
}

// ���� i-Defense ����
BOOL CIDefenseLancher::Init_Eng()
{
	m_hDll = LoadLibrary(_T("idfapi.dll"));
	if(NULL == m_hDll) 
	{
		return FALSE;
	}
	
	idfAutoStart_t lpidfAutoStart2 = (idfAutoStart_t)GetProcAddress(m_hDll,_T("idfAutoStartEx2")); 
	
	if(lpidfAutoStart2)
	{                     /* ���縶�� �ٸ�,  */
		lpidfAutoStart2("idefense/koreastock_20110603",
			0,
			1,
			0x0007,
			"��ȭ����|koreastock|hwrun.exe|HwStarter.exe|EZMain.exe|EZLogIn.exe|"	, /* NULL�̸� ȣ�� ���α׷��� Process ID�� �˻��� */
			"��ȭ����"); 
	}
	FreeLibrary(m_hDll);
	return TRUE;
}

// i-Defense ����
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

// ���̷���(������)
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
			"��ȭ����");	//KJI 20091130 (������7 ���� ŷ������ ����)
	}
	FreeLibrary(m_hDll);
	return TRUE;
}