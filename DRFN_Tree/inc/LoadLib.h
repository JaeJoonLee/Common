#ifndef _DRFN_LOAD_LIB_20060714__H_
#define	_DRFN_LOAD_LIB_20060714__H_

#define		CS_LOADERROR		-1
#define		CS_OK				0
#define		CS_ALREADY			1
#define		CS_INPUTERROR		201

////////////////////////////////////////////////////////////////////////////////
class CLoadLib
{
public:
	CLoadLib() {
		m_hLib = NULL;	
		//m_bLoadMsgShow = FALSE;
		m_bLoadMsgShow = TRUE;		//초기 테스트할 때는 보이게 한다.
	}
	~CLoadLib()
	{
		UnLoadLib();
	}
		
	//virtual BOOL LoadProcAddress() { ASSERT(FALSE); return FALSE;}
	virtual BOOL LoadProcAddress() { return TRUE;}
	HMODULE LoadLib()
	{
		CString szDllName = m_szDllName;
		HMODULE		hLib = NULL;
		//AfxMessageBox(szDllName);
		hLib = AfxLoadLibrary(szDllName);
		if(hLib==NULL) {
			CString msg;
			msg.Format("DLL[%s]을 Load할 수 없습니다.", szDllName);
			if(m_bLoadMsgShow)
				AfxMessageBox(msg);

			return NULL;
		}
		m_hLib = hLib;
		if(!LoadProcAddress()) {
			UnLoadLib();
			return NULL;
		}

		return hLib;
	}
	BOOL UnLoadLib()
	{
		if(!m_hLib)
			return TRUE;

		BOOL bResult = AfxFreeLibrary(m_hLib);
		m_hLib = NULL;

		return bResult;
	}

// Attibutes
public:
	HMODULE		m_hLib;
	CString		m_szDllName;
	BOOL		m_bLoadMsgShow;
};



#endif //_DRFN_LOAD_LIB_20060714__H_