// LinkInfoHelper.cpp: implementation of the CLinkInfoHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LinkInfoHelper.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinkInfoHelper::CLinkInfoHelper()
{

	m_hModLib		= NULL;

	m_lpfnLink_CommonLinkData = NULL;
	
	m_bIsInitialized        = FALSE;
	m_szCommonPath[0] = 0x00;
}

CLinkInfoHelper::~CLinkInfoHelper()
{
	if ( m_hModLib )	::FreeLibrary( m_hModLib );

}

int CLinkInfoHelper::Initialize( char* szPath )
{
	if ( m_bIsInitialized )			return		1;
	
	sprintf ( m_szCommonPath, szPath );

	TCHAR			szCommLib[MAX_PATH];
	_stprintf(szCommLib, "%s\\LinkInfoMng.dll", m_szCommonPath);
	m_hModLib = ::LoadLibrary( szCommLib );
	if ( m_hModLib == NULL )		return		-1;
	
	m_bIsInitialized = TRUE;
	return 10;

}

int	 CLinkInfoHelper::LoadCommHelper( char* szPath )
{
	if ( m_bIsInitialized )			return		1;

	sprintf ( m_szCommonPath, szPath );

	TCHAR			szCommLib[MAX_PATH];
	_stprintf(szCommLib, "%s\\LinkInfoMng.dll", m_szCommonPath);
	m_hModLib = ::LoadLibrary(szCommLib);
	if ( m_hModLib == NULL )		return		-1;

	m_bIsInitialized = TRUE;
	return	1;
}

int CLinkInfoHelper::KSLink_CommonLinkData ( LPTSTR lpszBuffer, int nSize  )
{
	if ( m_hModLib == NULL )		return	-10;
	if ( m_lpfnLink_CommonLinkData == NULL )		m_lpfnLink_CommonLinkData = (LPKSLINK_COMMONLINKDATA)GetProcAddress(m_hModLib, "KSLink_CommonLinkData");
	if ( m_lpfnLink_CommonLinkData == NULL )		return	-10;
	
	return m_lpfnLink_CommonLinkData ( lpszBuffer, nSize );
}



