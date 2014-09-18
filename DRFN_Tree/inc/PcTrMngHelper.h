#ifndef __PCTRMANAGER__LOADHELPER___HEADER_
#define	__PCTRMANAGER__LOADHELPER___HEADER_

//#include	"PcTrMngHelper.h"
#include "LoadLib.h"
#include "./PcTrComDef.h"
//#include "./EnvDir.h"
#include "../IncSite/FS_Env.h"

/////////////////////////////////////////////////////////////////////////////
//	PCTRMng.dll
/////////////////////////////////////////////////////////////////////////////
typedef	long  (WINAPI * FpGetInferface)(WPARAM wp, LPARAM lp);
typedef	void*  (WINAPI * FpGetPCTrData)(WPARAM wp, LPARAM lp);
typedef	long  (WINAPI * FpSetPCTrData)(WPARAM wp, LPARAM lp);
typedef	long  (WINAPI * FpNotifyPCTrState)(WPARAM wp, LPARAM lp);


class CPCTrMngHelper : public CLoadLib
{
public:
	CPCTrMngHelper () {
		CString strBaseDir;
		//GET_ROOT_DIR(strBaseDir);
		GetDir_DrfnRoot(strBaseDir);

		//m_szDllName = strBaseDir + "\\dev\\PcTrMng.dll";
		m_szDllName.Format("%s%s%s", strBaseDir, gDrfnBin3, "PcTrMng.dll");

		m_fpGetInferface = NULL;
		m_fpGetPCTrData = NULL;
		m_fpSetPCTrData = NULL;
		m_fpNotifyPCTrState = NULL;
		
		LoadLib();
	}
	~CPCTrMngHelper () {
	}
	
	virtual BOOL LoadProcAddress()
	{
		if(!m_hLib)
			return FALSE;
		
		m_fpGetInferface	= (FpGetInferface)::GetProcAddress(m_hLib, "GetInferface");
		m_fpGetPCTrData		= (FpGetPCTrData)::GetProcAddress(m_hLib, "GetPCTrData");
		m_fpSetPCTrData		= (FpSetPCTrData)::GetProcAddress(m_hLib, "SetPCTrData");
		m_fpNotifyPCTrState = (FpNotifyPCTrState)::GetProcAddress(m_hLib, "NotifyPCTrState");

		if( !m_fpGetPCTrData || !m_fpSetPCTrData || !m_fpGetInferface ) { // || !m_fpNotifyPCTrState) {
			TRACE1("%s의 GetProcAddress에서 Load에러 발생", m_szDllName);
			return FALSE;
		}
		return TRUE;
	}

	LONG GetInterface(int nID) 
	{
		return GetInferface((WPARAM)nID, 0); 
	}

	LONG GetInferface(WPARAM wp, LPARAM lp)
	{
		if(m_fpGetInferface) return m_fpGetInferface(wp, lp);
		return NULL;
	}
	
	void* GetPCTrData(WPARAM wp, LPARAM lp)
	{
		if(m_fpGetPCTrData) return m_fpGetPCTrData(wp, lp);
		return NULL;
	}

	long SetPCTrData(WPARAM wp, LPARAM lp)
	{
		if(m_fpSetPCTrData) return m_fpSetPCTrData(wp, lp);
		return NULL;
	}

	// 메인의 상태를 알려준다.
	// 현재는 PCTrMng_ExitInstance 만 사용한다.
	long NotifyPCTrState(WPARAM wp, LPARAM lp)
	{
		if(m_fpNotifyPCTrState) return m_fpNotifyPCTrState(wp, lp);
		return NULL;
	}

public:
	// Variable

	// Function
	FpGetInferface		m_fpGetInferface;
	FpGetPCTrData		m_fpGetPCTrData;
	FpSetPCTrData		m_fpSetPCTrData;
	FpNotifyPCTrState	m_fpNotifyPCTrState;

	// Implementation
public:

};

#endif // __PCTRMANAGER__LOADHELPER___HEADER_

