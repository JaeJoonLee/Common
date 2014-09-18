#ifndef __LOAD_FOR_TREELISTMANAGER__BY_JUNOK_LEE__HEADER__
#define __LOAD_FOR_TREELISTMANAGER__BY_JUNOK_LEE__HEADER__

// #include "../../_Include/LoadTreeListMng.h"

typedef  LONG (WINAPI* FpTLM_GetInferface)(long);
typedef  LONG (WINAPI* FpTLM_Terminate)(long);

//#include "../ForSite/FS_Env.h"
//#include "../../IncSite/FS_Env.h"	//Solomon-090829

class CTreeListMngLoader
{
public:
	HINSTANCE m_hLib;
	CString m_szLibName;
	FpTLM_GetInferface	m_fpGetInferface;
	FpTLM_Terminate		m_fpTLM_Terminate;

//	Constructor..Destructor..
public:
	CTreeListMngLoader()
	{
		m_hLib = NULL;

		//-->Solomon-090829
		GetDir_DrfnBin(m_szLibName);
		m_szLibName += "\\TreeListMng.dll";
		//	m_szLibName.Format("%s\\%s", szPath, "TreeListMng.dll");
		//<--Solomon-090829

		m_fpGetInferface = NULL;
		m_fpTLM_Terminate = NULL;
	}

	~CTreeListMngLoader()
	{
		CleanAll();
		UnLoadLib();
	}


	HINSTANCE LoadLib()
	{
		HINSTANCE hLib = NULL;
		hLib  = (HINSTANCE) ::LoadLibrary((LPCTSTR)m_szLibName);
		if( hLib == NULL)
		{
			CString szMsg;
			szMsg.Format("%s을 Load할 수 없습니다.", m_szLibName);
			TRACE("%s\n", szMsg);
			// AfxMessageBox(szMsg);
			return NULL;
		}
		m_hLib = hLib;

		LoadProcess();

		return hLib;
	}

	BOOL UnLoadLib()
	{
		if(m_hLib == NULL)  return TRUE;

		BOOL bResult = ::FreeLibrary(m_hLib);
		m_hLib = NULL;

		return bResult;
	}


	void LoadProcess()
	{
		if(!m_hLib)	return ;

		m_fpGetInferface = (FpTLM_GetInferface)::GetProcAddress(m_hLib, "GetInferface");
		m_fpTLM_Terminate  = (FpTLM_Terminate)::GetProcAddress(m_hLib, "Terminate");
	}


	LONG TLM_GetInferface(long pIGateMng)
	{
		if(!m_hLib ||!m_fpGetInferface)	 return NULL;

		return m_fpGetInferface(pIGateMng);
	}

	void CleanAll()
	{
		if(!m_hLib ||!m_fpGetInferface)	 return;

		long dwKey = 0;
		m_fpTLM_Terminate(dwKey);
	}
};


#endif //__LOAD_FOR_TREELISTMANAGER__BY_JUNOK_LEE__HEADER__
