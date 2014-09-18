//******************************************************************
// All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : DgnCommApiHelper.cpp
//  Function      : 
//  System Name   : Common
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2009 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
// DgnCommApiHelper.cpp: implementation of the DgnCommApiHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DgnCommApiHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*****************************************************************
//  Function Name : DgnCommApiHelper
//  Function      : 생성자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
DgnCommApiHelper::DgnCommApiHelper()
{
	m_hDgnCommAPILib		= NULL;

	m_lpfnDgnCommInit			= NULL;
	m_lpfnDgnCommTerminate		= NULL;

	m_lpfnDgnCommRequestData	= NULL;
	m_lpfnDgnCommTcpRequestData	= NULL;

	m_lpfnDgnCommReConnect		= NULL;
	m_lpfnDgnCommGetConnectState = NULL;
	m_lpfnDgnCommCommonMsgSend	 = NULL;
	m_lpfnDgnGetCommApiWndHandle = NULL;

	m_bIsInitialized        = FALSE;
	m_szCommonPath[0] = 0x00;

}

//*****************************************************************
//  Function Name : ~DgnCommApiHelper
//  Function      : 소멸자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
DgnCommApiHelper::~DgnCommApiHelper()
{
	if ( m_hDgnCommAPILib )	::FreeLibrary( m_hDgnCommAPILib );
}

//*****************************************************************
//  Function Name : DgnCommApiInitialize
//  Function      : 
//  Param         : int nOption , char* szPath 
//  Return        : int 
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int DgnCommApiHelper::DgnCommApiInitialize( int nOption , char* szPath )
{
	if ( m_bIsInitialized )		return		1;
	
	sprintf ( m_szCommonPath, szPath );

	TCHAR			szCommLib[MAX_PATH];
	sprintf(szCommLib, "%s\\FnDgnCommAPI.dll", m_szCommonPath);
	m_hDgnCommAPILib = ::LoadLibrary( szCommLib );
	if ( m_hDgnCommAPILib == NULL )		return		-1;
	
	if ( m_lpfnDgnCommInit == NULL )		m_lpfnDgnCommInit = (LPDGNCOMMINIT)GetProcAddress(m_hDgnCommAPILib, "DgnCommInit");
	if ( m_lpfnDgnCommInit == NULL )		return	-10;

	m_bIsInitialized = TRUE;
	return m_lpfnDgnCommInit ( nOption );

}

//*****************************************************************
//  Function Name : DgnLoadCommHelper
//  Function      : 
//  Param         : char* szPath 
//  Return        : int	 
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int	 DgnCommApiHelper::DgnLoadCommHelper( char* szPath )
{
	sprintf ( m_szCommonPath, szPath );

	TCHAR			szCommLib[MAX_PATH];
	sprintf(szCommLib, "%s\\FnDgnCommAPI.dll", m_szCommonPath);
	m_hDgnCommAPILib = ::LoadLibrary(szCommLib);
	if ( m_hDgnCommAPILib == NULL )		return		-1;

	return	1;
}

//*****************************************************************
//  Function Name : DgnCommInit
//  Function      : 
//  Param         : int nOption 
//  Return        : int 
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int DgnCommApiHelper::DgnCommInit( int nOption )
{
	if ( m_hDgnCommAPILib == NULL )		return	-10;
	if ( m_lpfnDgnCommInit == NULL )		m_lpfnDgnCommInit = (LPDGNCOMMINIT)GetProcAddress(m_hDgnCommAPILib, "DgnCommInit");
	if ( m_lpfnDgnCommInit == NULL )		return	-10;
	
	return m_lpfnDgnCommInit ( nOption );
}

//*****************************************************************
//  Function Name : DgnCommTerminate
//  Function      : 
//  Param         : BOOL bSocketClose 
//  Return        : void 
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void DgnCommApiHelper::DgnCommTerminate( BOOL bSocketClose )
{
	if ( m_hDgnCommAPILib == NULL )		return;
	if ( m_lpfnDgnCommTerminate == NULL )	m_lpfnDgnCommTerminate = (LPDGNCOMMTERMINATE)GetProcAddress(m_hDgnCommAPILib, "DgnCommTerminate");
	if ( m_lpfnDgnCommTerminate == NULL )	return;
	
	m_lpfnDgnCommTerminate( bSocketClose );
}
	
//*****************************************************************
//  Function Name : DgnCommRequestData
//  Function      : 
//  Param         : HWND hRecvWnd, char* szTrcode, BYTE* lpData, int nDataLen 
//  Return        : int 
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int DgnCommApiHelper::DgnCommRequestData( HWND hRecvWnd, char* szTrcode, BYTE* lpData, int nDataLen )
{
	if ( m_hDgnCommAPILib == NULL )		return	-10;
	if ( m_lpfnDgnCommRequestData == NULL )	m_lpfnDgnCommRequestData = (LPDGNCOMMREQUESTDATA)GetProcAddress(m_hDgnCommAPILib, "DgnCommRequestData");
	if ( m_lpfnDgnCommRequestData == NULL )	return	-10;
	
	return m_lpfnDgnCommRequestData( hRecvWnd, szTrcode, lpData, nDataLen);
}
// jung
//*****************************************************************
//  Function Name : 
//  Function      : 
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************.
void * DgnCommApiHelper::DgnCommTcpRequestData( HWND hRecvWnd, char* szTrcode, BYTE* lpData, int nDataLen)
{
	if ( m_hDgnCommAPILib == NULL )		return	NULL;
	if ( m_lpfnDgnCommTcpRequestData == NULL )	m_lpfnDgnCommTcpRequestData = (LPDGNCOMMTCPREQUESTDATA)GetProcAddress(m_hDgnCommAPILib, "DgnCommTcpRequestData");
	if ( m_lpfnDgnCommTcpRequestData == NULL )	return	NULL;
	
	return m_lpfnDgnCommTcpRequestData( hRecvWnd, szTrcode, lpData, nDataLen);
}

//*****************************************************************
//  Function Name : DgnCommReConnect
//  Function      : 
//  Param         : int nRetryCount /*= 3*/ ,HWND hRecvWnd /*= NULL*/ 
//  Return        : int	
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************.
int	DgnCommApiHelper::DgnCommReConnect( int nRetryCount /*= 3*/ ,HWND hRecvWnd /*= NULL*/ )
{
	if ( m_hDgnCommAPILib == NULL )		return	-10;
	if ( m_lpfnDgnCommReConnect == NULL )	m_lpfnDgnCommReConnect = (LPDGNCOMMRECONNECT)GetProcAddress(m_hDgnCommAPILib, "DgnCommReConnect");
	if ( m_lpfnDgnCommReConnect == NULL )	return	-10;
	
	return m_lpfnDgnCommReConnect(nRetryCount, hRecvWnd );
}

//*****************************************************************
//  Function Name : DgnCommGetConnectState
//  Function      : 
//  Param         : int& nConnect 
//  Return        : int 
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int DgnCommApiHelper::DgnCommGetConnectState(int& nConnect )
{
	if ( m_hDgnCommAPILib == NULL )		return	-10;
	if ( m_lpfnDgnCommGetConnectState == NULL )	m_lpfnDgnCommGetConnectState = (LPDGNCOMMGETCONNECTSTATE)GetProcAddress(m_hDgnCommAPILib, "DgnCommGetConnectState");
	if ( m_lpfnDgnCommGetConnectState == NULL )	return	-10;
	
	return m_lpfnDgnCommGetConnectState( nConnect );
}

//*****************************************************************
//  Function Name : DgnCommCommonMsgSend
//  Function      : 
//  Param         : int nMsgID, WPARAM wParam, LPARAM lParam  
//  Return        : int 
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int DgnCommApiHelper::DgnCommCommonMsgSend( int nMsgID, WPARAM wParam, LPARAM lParam  )
{
	if ( m_hDgnCommAPILib == NULL )		return	-10;
	if ( m_lpfnDgnCommCommonMsgSend == NULL )	m_lpfnDgnCommCommonMsgSend = (LPDGNCOMMCOMMONMSGSEND)GetProcAddress(m_hDgnCommAPILib, "DgnCommCommonMsgSend");
	if ( m_lpfnDgnCommCommonMsgSend == NULL )	return	-10;
	
	return m_lpfnDgnCommCommonMsgSend( nMsgID, wParam, lParam);
}

//*****************************************************************
//  Function Name : DgnCommGetCommsWindowHandle 
//  Function      : 
//  Param         : HWND& hDgnComApiWnd 
//  Return        : int 
//  Create        : 
//  Update        : 김준안, 2009/09/18 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int DgnCommApiHelper::DgnCommGetCommsWindowHandle ( HWND& hDgnComApiWnd )
{
	if ( m_hDgnCommAPILib == NULL )		return	-10;
	if ( m_lpfnDgnGetCommApiWndHandle == NULL )	m_lpfnDgnGetCommApiWndHandle = (LPDGNGETCOMMAPIWNDHANDLE)GetProcAddress(m_hDgnCommAPILib, "DgnGetCommApiWndHandle");
	if ( m_lpfnDgnGetCommApiWndHandle == NULL )	return	-10;
	
	hDgnComApiWnd = m_lpfnDgnGetCommApiWndHandle( );

	return 1;
}
