//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (��)�ѱ��Ҹ���ġ        
//******************************************************************
//  File Name     : MainFrm_Thread.cpp
//  Function      : CCommMain Ŭ���� ó��
//  System Name   : HwComms
//  Create        : 2003��7��16��    �� ���� (��) �ѱ� �Ҹ���ġ
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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
//  Create        : ��â�� , 2006/03/22
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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
		// ���ŵ����� Thread�� �����Ѵ�.
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
//  Function      : ���� ������ Threadó���� �����ϴ� �Լ� 
//  Param         : LPVOID pParam  CCommApiWnd������ .
//  Return        : UINT 
//  Create        : 2002��6��28��    ��  â�� (��) �ѱ� �Ҹ���ġ.
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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
//  Function      : ���� ������ Thread�� �ۼ��ϴ� �Լ�.
//  Param         : ����
//  Return        : BOOL 
//  Create        : ��â�� , 2006/03/22
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
BOOL CCommMain::MakeReceiveThread()
{
	// ���ſ� Thread�� �ۼ��Ѵ�.
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
//  Function      : ���� �����Ϳ� Thread ó���� �����ϴ� ��� .
//  Param         : int nType /*= 0*/
//  Return        : void  
//  Create        : ��â�� , 2006/03/22
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
void  CCommMain::ReceiveThreadStop(int nType /*= 0*/)
{
	m_bRecvStop = TRUE;

	// ���� ������ Thrad���� �ñ׷��� �߻��Ѵ�.
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


