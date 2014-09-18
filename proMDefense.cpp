// proMDefense.cpp: implementation of the CproMDefense class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "proMDefense.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CproMDefense::CproMDefense()
{
	m_hproMDefense = NULL;
	m_ProcDefense_Init = NULL;
	m_ProcDefense_SendDevice = NULL;
	m_dwProcDefense_Init = NULL;
	m_dwProcDefense_SendDevice = NULL;
	
	m_hproMDefense = LoadLibrary("ProMDefense.dll");
	
	if ( m_hproMDefense )
	{
		m_ProcDefense_Init = (PROCPROINIT)GetProcAddress(m_hproMDefense,"a2");
		m_ProcDefense_SendDevice = (PROCPROSENDDEVICE)GetProcAddress(m_hproMDefense,"a1");
		m_dwProcDefense_Init = (DWORDPROCPROINIT)GetProcAddress(m_hproMDefense,"a4");
		m_dwProcDefense_SendDevice = (DWORDPROCPROSENDDEVICE)GetProcAddress(m_hproMDefense,"a3");

	}

}

CproMDefense::~CproMDefense()
{
	m_ProcDefense_Init = NULL;
	m_ProcDefense_SendDevice = NULL;
	m_dwProcDefense_Init = NULL;
	m_dwProcDefense_SendDevice = NULL;

	if(m_hproMDefense)
	{
		FreeLibrary(m_hproMDefense);
	}
	
}

DWORD CproMDefense::Ready_ProMDefense()
{
	DWORD dwReadyErr = 0;

	if(m_dwProcDefense_Init)
	{
		dwReadyErr = m_dwProcDefense_Init();

		if(dwReadyErr != ERR_PROM_SUCCESS)
		{
			return dwReadyErr;
		}
	}
	if(m_dwProcDefense_SendDevice)
	{
		return m_dwProcDefense_SendDevice(PP_SET_HOOK,0,0,"");
	}
	return ERR_PROM_NOT_INIT;

}

DWORD CproMDefense::End_ProMDefense()
{
	if(m_dwProcDefense_SendDevice)
	{
		return m_dwProcDefense_SendDevice(PP_SET_UNHOOK,0,0,"");
		
	}
	return ERR_PROM_NOT_INIT;
}

DWORD CproMDefense::Insert_Protect_PID(DWORD dwPID)
{
	if(m_dwProcDefense_SendDevice)
	{
		return m_dwProcDefense_SendDevice(PP_INSERT_PID,dwPID,0,"");
		
	}
	return ERR_PROM_NOT_INIT;
}

DWORD CproMDefense::Delete_Protect_PID(DWORD dwPID)
{
	if(m_dwProcDefense_SendDevice)
	{
		return m_dwProcDefense_SendDevice(PP_DELETE_PID,dwPID,0,"");
	}
	return ERR_PROM_NOT_INIT;
}

DWORD CproMDefense::Set_Protect_MSG(DWORD dwPolicy)
{
	if(m_dwProcDefense_SendDevice)
	{
		return m_dwProcDefense_SendDevice(PP_SET_ERRMSG,0,dwPolicy,"");
	}
	return ERR_PROM_NOT_INIT;
}


