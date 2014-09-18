//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : MainFrm_Thread.cpp
//  Function      : CCommMain 클래스 처리
//  System Name   : HwComms
//  Create        : 2003년7월16일    유 광식 (주) 한국 소리마치
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************

#include "stdafx.h"
#include "CommMain.h"
//#include "Shlwapi.h"		// Shell Light-weight Utility Library
							// Contains utility functions for handling paths, urls, 
							// strings, registry entries and color settings 
//#include "CommHeaderDef.h"		// 
//#include "KHresource.h"		// 


//******************************************************************
//  Function Name : SetThreadInitSetThreadInit
//  Function      : 
//  Param         : BOOL BOOL bCreate 
//  Return        : void 
//  Create        : 김창하 , 2006/03/22
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CCommMain::SetThreadInit(BOOL bCreate)
{
	if (bCreate)
	{
		m_hRecvEndThread = CreateEvent(NULL, FALSE, FALSE, NULL);
		ASSERT(m_hRecvEndThread);
		SetEvent(m_hRecvEndThread);
		MakeReceiveThread();
	}
	else
	{
		// 수신데이터 Thread를 종료한다.
		if (m_pRecvTickThread)
		{
			ReceiveThreadStop();
		}

		if (m_hRecvEndThread)
		{
			::CloseHandle(m_hRecvEndThread);
			m_hRecvEndThread  = NULL;
		}
	}
}

//******************************************************************
//  Function Name : ReceiveThreadStart
//  Function      : 수신 데이터 Thread처리를 시작하는 함수 
//  Param         : LPVOID pParam  CCommApiWnd포인터 .
//  Return        : UINT 
//  Create        : 2002년6월28일    김  창하 (주) 한국 소리마치.
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : WaitForSingleObject
//******************************************************************
UINT ReceiveThreadStart(LPVOID pParam)
{
	CCommMain* pMain = (CCommMain*) pParam;
	DWORD deRet;
	while ( !pMain->m_bRecvStop )
	{
		deRet = ::WaitForSingleObject( pMain->m_hRecvEndThread, 10  );
		if ( deRet == WAIT_TIMEOUT )
		{
			if(pMain->m_pTcpSocket)
				pMain->m_pTcpSocket->ReceiveTick();
		}
		else
		{
			pMain->m_bRecvStop = true;
		}
	}	
    TRACE(" pMain ReceiveThreadStart...End\n");

	return 0;
}

//******************************************************************
//  Function Name : MakeReceiveThread
//  Function      : 수신 데이터 Thread를 작성하는 함수.
//  Param         : 없음
//  Return        : BOOL 
//  Create        : 김창하 , 2006/03/22
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CCommMain::MakeReceiveThread()
{
	// 수신용 Thread를 작성한다.
	m_bRecvStop = false;
	ResetEvent( m_hRecvEndThread );

	m_pRecvTickThread = ::AfxBeginThread(ReceiveThreadStart,
									 this,
									 THREAD_PRIORITY_TIME_CRITICAL, 
									 0,
									 CREATE_SUSPENDED);
	if (m_pRecvTickThread != NULL )
	{
		TRACE(_T("AfxBeginThread: 0x%08lX\n"),  m_pRecvTickThread->m_nThreadID );
		m_pRecvTickThread->m_bAutoDelete = FALSE;
		// start
		m_pRecvTickThread->ResumeThread();
	}
	else
	{
		AfxMessageBox(" pMain AfxBeginThread ...Create Error!!!") ;
		return FALSE;
	}
	return TRUE;
}

//******************************************************************
//  Function Name : ReceiveThreadStop
//  Function      : 수신 데이터용 Thread 처리를 종료하는 기능 .
//  Param         : int nType /*= 0*/
//  Return        : void  
//  Create        : 김창하 , 2006/03/22
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void  CCommMain::ReceiveThreadStop(int nType /*= 0*/)
{
	m_bRecvStop = TRUE;

	// 수신 데이터 Thrad종료 시그럴을 발생한다.
	if ( m_hRecvEndThread )
	{
		::SetEvent( m_hRecvEndThread );
		::CloseHandle( m_hRecvEndThread );
		m_hRecvEndThread = NULL;
	}

	if ( m_pRecvTickThread && m_pRecvTickThread->m_hThread )
	{
		DWORD dwExitCode;
		if (::GetExitCodeThread( m_pRecvTickThread->m_hThread, &dwExitCode ) &&
				dwExitCode == STILL_ACTIVE)
		{
			DWORD dwRet = ::WaitForSingleObject( m_pRecvTickThread->m_hThread, 10000 );
			if ( dwRet == WAIT_TIMEOUT )
			{
				TerminateThread( m_pRecvTickThread->m_hThread, 0 );
			}
		}
		
		if ( m_pRecvTickThread )
			delete m_pRecvTickThread;

		m_pRecvTickThread = NULL;
	}
}


