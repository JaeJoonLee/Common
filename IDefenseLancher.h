// IDefenseLancher.h: interface for the CIDefenseLancher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDEFENSELANCHER_H__0E049B41_E360_4586_8EF4_2D45C02AA03D__INCLUDED_)
#define AFX_IDEFENSELANCHER_H__0E049B41_E360_4586_8EF4_2D45C02AA03D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef  BOOL (*idfAutoStart_t) (char *pClassList, 
								 BOOL bExtend, 
								 int nOption, 
								 int nInstOption, 
								 char* szTitleName,
char* szCompanyName); 

typedef  BOOL (*idfUnloadApp_t) (); 

typedef	 BOOL (*idfVirusStart_t)(char *pSiteName, 
								 BOOL bExtend, 
								 int nOption, 
								 int nInstOption, 
								 char* szTitleName,
								 char *szCompanyName);
								 
class CIDefenseLancher  
{
private:
	HMODULE m_hDll;
public:
	CIDefenseLancher();
	virtual ~CIDefenseLancher();
	
	BOOL Init_Kor();
	BOOL Init_Eng();
	BOOL IdfStop();
	BOOL IdfVirusStart();
};

#endif // !defined(AFX_IDEFENSELANCHER_H__0E049B41_E360_4586_8EF4_2D45C02AA03D__INCLUDED_)

