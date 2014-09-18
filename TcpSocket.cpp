//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : TcpSocket.cpp
//  Function      : 
//  System Name   : HwComms
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
// TcpSocket.cpp : implementation file
//
#include "stdafx.h"
#include "TcpSocket.h"
#include "CommsDef.h"

//-> 2012.02.28 jhj
#include "../TrDll/AIBroker/EnvDir.h"
//<-

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RECEIVE_WAIT_TIME 0	// 퍼포먼스 튜닝 가능(5-20사이)

IMPLEMENT_DYNAMIC(CTcpSocket, CObject)

static char g_szRecvBuf[33 * 1024];
static char	g_szSocketBuff[99000];
static UINT	g_nSocketSize = 0;

DWORD		g_dwSocketBufLen = 0;

//char	src_buf[128];
//char	dest_buf[128];

//-> 2012.02.28 jhj
#define __SOCKET_LOG
#define MAX_BUFSIZ				8192	
#define MAX_BUFLEN				5120
#define MAX_PACKETLEN			4096

#define MAX_PACKETSIZE			99000
/////////////////////////////////////////////////////////////////////////////
// CTcpSocket
//******************************************************************
//  Function Name : CTcpSocket
//  Function      : 생성자
//  Param         : CWnd* pParentWnd /*= NULL*/  부모 윈도우의 포인터 
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CTcpSocket::CTcpSocket(CWnd* pParentWnd /*= NULL*/)
{
	m_bReadSizeDsp		= 0;				// CommsDbg에 소켓 수신사이즈 표시여부
	m_pParentWnd		= pParentWnd;		// 부모 윈도우(CMainFrame)

	m_hSocket			= INVALID_SOCKET;	// 소켓 Instance
	m_strHostAddress	= _T("");			// 서버 IP
	m_nHostPort			= 0;				// 서버 Port
	m_nSocketErrorCode	= 0;				// ::WSAGetLastError()

	m_nRecvThreadID		= 0;				// Receive Thread ID
	m_hRecvStopEvent	= NULL;				// Receive Stop Event Handle
	m_hRecvThread		= NULL;				// Receive Thread Handle

	m_bAllSetCompleted	= FALSE;

	m_hRecvStopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ASSERT(m_hRecvStopEvent);
	SetEvent(m_hRecvStopEvent);
	
	m_bFirstDown = TRUE;

	m_nReceivedFileCount	= 0;
	m_nTotalFileCount		= 0;
	m_bRecvStop				= FALSE;	// 종료시에 사용할 Flag값이다.

	m_bColsolCreate			= FALSE;	
	m_hCommsDbgWnd			= NULL;		// CommsDbgWnd
	m_bIPShare				= FALSE;	// 공유기 사용 여부

	//->2012.02.28 jhj
	m_ucBccType				= PID_ENCCLIENTSET;
	m_nPacketId				= 0x00000100;
	m_lMaxSeq				= 1;
	//<-
}

//******************************************************************
//  Function Name : ~CTcpSocket
//  Function      : 소멸자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CTcpSocket::~CTcpSocket()
{
	if ( m_hRecvStopEvent )
		::CloseHandle( m_hRecvStopEvent );

	if ( m_hRecvThread )
	{
		::CloseHandle( m_hRecvThread ); 
	}
	DisConnectTCPSocket();
}

/////////////////////////////////////////////////////////////////////////////
// CTcpSocket member functions
//******************************************************************
//  Function Name : CreateTCPSocket
//  Function      : TCP/IP소켓을 작성하는 함수 
//  Param         : 없음
//  Return        : BOOL  성공:TRUE
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CTcpSocket::CreateTCPSocket()
{
	m_lDataIndex	= 0 ;

	int nRet;
	ASSERT( m_hSocket == INVALID_SOCKET );
	
	if ( m_hSocket == INVALID_SOCKET )
	{
		// TCP소켓을 작성한다.
		m_hSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if ( m_hSocket == INVALID_SOCKET ) 
		{
			m_nSocketErrorCode = ::WSAGetLastError();
			char   szBuf[1024] = { 0 };
			sprintf( szBuf, "CreateTCPSocket1 ErrorCode...[%d]", m_nSocketErrorCode );
			SetWriteConsol(szBuf);

			return FALSE;
		}
		else
		{
			int nOptVal;
			int nOptLen;
			nOptLen = sizeof(int);

			// 수신용 버퍼 사이즈를 취득한다.
			nRet = getsockopt ( m_hSocket, SOL_SOCKET, SO_RCVBUF, (char *)&nOptVal, &nOptLen);
			if ( nRet == SOCKET_ERROR )
			{
				m_nSocketErrorCode = ::WSAGetLastError();

				char   szBuf[1024] = { 0 };
				sprintf( szBuf, "CreateTCPSocket2 ErrorCode...[%d]", m_nSocketErrorCode );
				SetWriteConsol(szBuf);
			}
			else
			{
				int nRecvBufLen = 16384;	// 16K

				if (m_bIPShare)
				{
					nRecvBufLen = 512;		// 인터넷공유기 사용시
				}

				nRet = setsockopt( m_hSocket, SOL_SOCKET, SO_RCVBUF, (char *)&nRecvBufLen, sizeof(int) );
				TRACE("setsockopt recieve size=[%d]..nRet=[%d]\n", nOptVal, nRet);
			}

			// 송신용 버퍼 사이즈를 취득한다.
			nRet = getsockopt ( m_hSocket, SOL_SOCKET, SO_SNDBUF, (char *)&nOptVal, &nOptLen);
			if ( nRet == SOCKET_ERROR )
			{
				m_nSocketErrorCode = ::WSAGetLastError();

				char   szBuf[1024] = { 0 };
				sprintf( szBuf,"CreateTCPSocket3 ErrorCode...[%d]", m_nSocketErrorCode );
				SetWriteConsol(szBuf);
			}
			else
			{
				int nSendBufLen = 16384;	// 16K
				if(m_bIPShare)
				{
					nSendBufLen = 512;		// 인터넷공유기 사용시
				}
				nRet = setsockopt( m_hSocket, SOL_SOCKET, SO_SNDBUF, (char *)&nSendBufLen, sizeof(int) );
				TRACE("setsockopt Send  size=[%d]..bRet=[%d]\n", nOptVal, nRet);
			}
			// 
			linger sLinger;
			nOptLen = sizeof(struct linger);
			nRet = getsockopt ( m_hSocket, SOL_SOCKET, SO_LINGER, (char *)&sLinger, &nOptLen);
			if ( nRet == SOCKET_ERROR )
			{
				m_nSocketErrorCode = ::WSAGetLastError();

				char   szBuf[1024] = { 0 };
				sprintf( szBuf, "CreateTCPSocket4 ErrorCode...[%d]", m_nSocketErrorCode );
				SetWriteConsol(szBuf);
			}
			else
			{
				if ( sLinger.l_onoff != 0 )
				{
					sLinger.l_onoff		= 0 ;
					sLinger.l_linger	= (u_short)SO_DONTLINGER ;
					setsockopt ( m_hSocket, SOL_SOCKET, SO_LINGER, (char *)&sLinger, nOptLen);
				}
			}

			/////////////////////////////////////////////////////////////////////////
			// Retrieves error status and clear.
			nRet = getsockopt ( m_hSocket, SOL_SOCKET, SO_ERROR, (char *)&nOptVal, &nOptLen);
			if ( nRet == SOCKET_ERROR )
			{
				m_nSocketErrorCode = ::WSAGetLastError();

				char   szBuf[1024] = { 0 };
				sprintf( szBuf, "CreateTCPSocket5 ErrorCode...[%d]", m_nSocketErrorCode );
				SetWriteConsol(szBuf);
			}
			else if ( nOptVal == 0 )
			{
				int nError = 1;
				nRet = setsockopt( m_hSocket, SOL_SOCKET, SO_ERROR, (char *)&nError, sizeof(int) );
				TRACE("setsockopt SO_ERROR size=[%d]..bRet=[%d]\n", nOptVal, nRet);
			}
		}
	}
	return TRUE;
}

void CTcpSocket::SetHostAddressAndPort(CString strHost, int nHostPort)
{
	m_strHostAddress	= strHost;
	m_nHostPort			= nHostPort;
}

//******************************************************************
//  Function Name : ConnectTCPSocket
//  Function      : TCP/IP 소켓으로 서버주소와 포트번호로 연결을 하는 함수 
//  Param         : 없음
//  Return        : BOOL		성공 : TRUE
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CTcpSocket::ConnectTCPSocket( )
{
	CString strText, strIP;
	if (m_pParentWnd->GetSafeHwnd() != NULL)
	{
		strText.Format("서버[IP=%s, Port=%d]로 소켓 접속중...", m_strHostAddress, m_nHostPort);
		CommsDbgLog((LPSTR)(LPCTSTR)strText);
	}

	strIP = m_strHostAddress;

	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0, sizeof(sockaddr_in));

	sockAddr.sin_addr.s_addr = inet_addr(strIP);
	if(INADDR_NONE == sockAddr.sin_addr.s_addr)
	{
		// 도메인 이름일 경우에 서버 IP를 구한다.
		// 테스트시에 98에서 3초정도 걸림.
		// Lookup host
		hostent *Hostent = gethostbyname(strIP);
		if (Hostent == NULL)
		{
			::WSASetLastError(WSAEINVAL);
			m_nSocketErrorCode = WSAEINVAL;
			
			m_pParentWnd->PostMessage(WM_USER_SOCKET_NOTIFY,
									  0L,
									  WSAMAKESELECTREPLY(FD_CONNECT_FAIL, m_nSocketErrorCode));
			return FALSE;
		}
		sockAddr.sin_addr.s_addr = ((struct in_addr FAR *)(Hostent->h_addr))->s_addr;
	}

	// Setup destination socket address
	sockAddr.sin_family			= AF_INET;
	sockAddr.sin_port			= htons((u_short)m_nHostPort);

	int nRet; 
	long lEvent = FD_WRITE | FD_CLOSE | FD_CONNECT;
	nRet = WSAAsyncSelect( m_hSocket, m_pParentWnd->GetSafeHwnd(), WM_USER_SOCKET_NOTIFY, lEvent );
	if ( nRet == SOCKET_ERROR)
	{
		m_nSocketErrorCode = ::WSAGetLastError();
		TRACE(" WSAAsyncSelect..Error Code[%d]\n", m_nSocketErrorCode );			
	}

	nRet = connect(m_hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
	if (nRet == SOCKET_ERROR)
	{
		m_nSocketErrorCode = ::WSAGetLastError();
		if ( m_nSocketErrorCode != WSAEWOULDBLOCK )
		{
			m_pParentWnd->PostMessage(WM_USER_SOCKET_NOTIFY,
									  m_hSocket,
								      WSAMAKESELECTREPLY(FD_CONNECT_FAIL, m_nSocketErrorCode));

			m_hSocket = INVALID_SOCKET;

			CString strTemp;
			strTemp.Format("Socket Error : %d", m_nSocketErrorCode);
			CommsDbgLog((LPSTR)(LPCTSTR)strTemp);
			return FALSE;
		}
	}

//	g_bSocketShutDown = FALSE;
	unsigned long argp = 1;					// Non Blocking 설정
	nRet = ioctlsocket(m_hSocket , FIONBIO , &argp);
	if (nRet == SOCKET_ERROR)
	{
		m_nSocketErrorCode = ::WSAGetLastError();
		TRACE(" ioctlsocket(FIONBIO)..Error Code[%d]\n", m_nSocketErrorCode );			
	}

	DWORD nBytes;
	nRet = ioctlsocket( m_hSocket, FIONREAD, &nBytes);
	if (nRet == SOCKET_ERROR)
	{
		m_nSocketErrorCode = ::WSAGetLastError();
		TRACE(" ioctlsocket(FIONREAD)..Error Code[%d]\n", m_nSocketErrorCode );			
	}

	m_bAllSetCompleted	= FALSE;

	return TRUE;
}


//******************************************************************
//  Function Name : CreateSocketReadThread
//  Function      : 수신스레드를 작성하는 함수 
//  Param         : 없음
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CTcpSocket::CreateSocketReadThread()
{
	if ( !m_hRecvThread )
	{
		BOOL bRet = ResetEvent( m_hRecvStopEvent );
		if ( !bRet )
		{
			TRACE("ResetEvent..ErrorCoe=[%d]\n", ::GetLastError());
		}
		m_hRecvThread = (HANDLE) _beginthreadex(NULL,
												0,
												RecvTCPSocketThread,
												(void*)this,
												CREATE_SUSPENDED,
												&m_nRecvThreadID);

		if ( !m_hRecvThread )
		{
			TRACE(" Thread Fail....\n");
			return FALSE;
		} 
		else 
		{
			SetThreadPriority(m_hRecvThread, THREAD_PRIORITY_HIGHEST  );
			ResumeThread( m_hRecvThread );
		}

		TRACE(" Thread Runing....RecvThread=[0x08lx], RecvThreadID=[%d]\n", m_hRecvThread, m_nRecvThreadID );
		return FALSE;
	}
	else
	{
		TRACE(" !!!Thread Runing....!!!\n");
	}
	return TRUE;
}

//******************************************************************
//  Function Name : RecvTCPSocketThread
//  Function      : 수신스레드를 개시하는 함수 
//  Param         : void* pParam		CTcpSocket* 포인터 
//  Return        : UINT 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
UINT CTcpSocket::RecvTCPSocketThread(void* pParam )
{
	ASSERT(pParam);
	CTcpSocket *pSocket = reinterpret_cast<CTcpSocket *> (pParam);

	pSocket->StartReceive();
	TRACE(" Recv Thread Treminate.... \n");

	return 0;
}

//******************************************************************
//  Function Name : GetSocketInfo 
//  Function      : 소켓 수신버퍼큐에 존재하는 데이터 길이를 취득하는 함수  
//  Param         : DWORD& wSocketBytes		길이 
//  Return        : int  
//  Create        : 2002년5월31일    김  창하 (주) 한국 소리마치
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int  CTcpSocket::GetSocketInfo ( DWORD& wSocketBytes )
{
	if ( m_hSocket == INVALID_SOCKET )
	{
		return SOCKET_ERROR;
	}
	int nRet = ioctlsocket( m_hSocket, FIONREAD, &wSocketBytes);

	return nRet;
}

//******************************************************************
//  Function Name : StartReceive
//  Function      : 실시간으로 소켓에서 데이터를 취득해서 CommApi로 수신데이터를 보내는 기능 
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CTcpSocket::StartReceive()
{
	int	   nSelect;
	int	   nRet;

	DWORD  nBytes;
	ULONG  nCHLength = 0;
	static BOOL	  bFirst = TRUE;

	struct timeval timeout;

	timeout.tv_sec	= 0;
	timeout.tv_usec = 10;							// 0.10

	fd_set		readfds;
	FD_ZERO(&readfds);

	//-> 2012.02.29 jhj
	int nPktSize = 0; 
	//<-

	while (::WaitForSingleObject( m_hRecvStopEvent, RECEIVE_WAIT_TIME )  == WAIT_TIMEOUT)
	{
		FD_ZERO	( &readfds );
		FD_SET	( m_hSocket, &readfds );

		// 수신 데이터가 존재 하는가를 체크한다.
		nSelect = select( 0, &readfds, NULL, NULL, &timeout );
		switch ( nSelect )
		{
		case 0:									// TimeOut
			{
				if (m_bColsolCreate)
				{
					char   szBuf[] = "Socket Ready...";
					SetWriteConsol(szBuf);
				}
				continue;
			}
			break;
		case SOCKET_ERROR:						// Error
			{
				m_nSocketErrorCode = ::WSAGetLastError();
				if (m_bColsolCreate)
				{
					char   szBuf[1024] = { 0 };
					sprintf( szBuf, "ErrorCode...[%d]", m_nSocketErrorCode );
					SetWriteConsol ( szBuf );
				}

				CString strText;
				///#ifdef _REAL_TEST_					
				strText.Format(" select ...SOCKET_ERROR...ERRORCODE=[%d]", m_nSocketErrorCode);
				m_pParentWnd->PostMessage(WM_USER_SOCKET_NOTIFY,
					0L,
					WSAMAKESELECTREPLY(FD_CLOSE, m_nSocketErrorCode));
				//#endif
				if (m_hCommsDbgWnd != NULL && ::IsWindow(m_hCommsDbgWnd))
				{
					CommsDbgLog((LPSTR)(LPCTSTR)strText);
				}

				///////////////////////////////////////////////////////////////////////////////////////
				// 로그파일 작성
				CommsDbgLog((LPSTR)(LPCTSTR)strText );
				///////////////////////////////////////////////////////////////////////////////////////

				FD_CLR( m_hSocket, &readfds );
				SetEvent( m_hRecvStopEvent );
				// 다운로드 끝
			}
			continue;
			break;
		default:
			break;
		}

		// 소켓버퍼에서 수신 데이터 사이즈를 취득한다.
		nRet = ioctlsocket( m_hSocket, FIONREAD, &nBytes);
		if ( nBytes <= 0 )
		{
			g_dwSocketBufLen = 0;
			continue;
		}
		g_dwSocketBufLen = nBytes;

		//////////////////////////////////////////////////////////////
		// 길이 정보를 읽는다.
		//////////////////////////////////////////////////////////////
		nBytes = Receive((char*)g_szSocketBuff + g_nSocketSize, nBytes, 0);
		g_nSocketSize += nBytes;

		if( nBytes == SOCKET_ERROR )
		{
			m_nSocketErrorCode = ::WSAGetLastError();

			///////////////////////////////////////////////////////////////////////////////////////
			// 메인 화면으로 소켓 단절을 통지한다(재 접속 요청)
			ASSERT ( FALSE );
			m_pParentWnd->PostMessage( WM_USER_SOCKET_NOTIFY,
				m_hSocket,
				WSAMAKESELECTREPLY(FD_CLOSE, m_nSocketErrorCode));

			FD_CLR( m_hSocket, &readfds );
			SetEvent( m_hRecvStopEvent );
			continue;
		}

		while(g_nSocketSize > SIZE_DEF_PACKET)
		{
			COMMONHEADER* pCommHeader = (COMMONHEADER*)g_szSocketBuff;

			nCHLength = ntohl(pCommHeader->ulPacketLen);
			nPktSize  = nCHLength;
			nCHLength += SIZE_DEF_PACKET;

			if(nCHLength <= SIZE_DEF_PACKET || nCHLength > g_nSocketSize)
			{
				//////////////////////////////////////////////////////////////////////////
				//-> 2012.02.29 jhj 패킷길이 오류인경우. 서버에 오류로그 전송.
				// 1) Comdbg 로그 기록
				CString strLog;
				strLog.Format("g_nSocketSize[%d] nBytes[%d] nCHLength[%d]", g_nSocketSize, nBytes, nCHLength);
				
				// 2) 정상적인 패킷인 경우 ( 쪼개져서 온경우 ) skip..
				if(nCHLength > SIZE_DEF_PACKET && nCHLength < MAX_PACKETSIZE)
				{
					break;
				}

				WriteErrorLog(strLog);

				BOOL bRecovery = FALSE;
				BYTE chPkt;
				int nState = 0;
				int nRecoveryPos = 0;
				for(int i = 4; i < nBytes; i++)
				{
					chPkt = g_szSocketBuff[i];
					switch(chPkt)
					{
					case 0xFF: // FF
						nState=1;
						break;
					case 0x0d: // CR
						if(nState==1)
							nState++;
						break;
					case 0x0a: // LF
						if(nState==2)
							bRecovery = TRUE;
						break;
					default:
						nState=0;
						break;
					}

					if(bRecovery)
					{
						nRecoveryPos = i + 1;
						break;		// for문을 빠져나감.
					}
				}
				
				strLog.Format("패킷오류 -> Error:%5d\t 복구Pos:%5d\r\n", nBytes, nRecoveryPos);
				WriteErrorLog(strLog);

				// 3) EzNet Smart 처럼 서버에 비정상 Report 제출
				strLog.Format("패킷길이 이상[0x%08X][%u]",(UINT)nPktSize,(UINT)nPktSize);
				SendErrorReport(FALSE,ERP_COMM_LENGTH_CHECK_ERROR,strLog,(BYTE*)g_szSocketBuff,nBytes - nRecoveryPos);
				
				TRY
				{
					// 4) 패킷길이가 비정상적인 경우 받은 패킷은 버린다.
					if(bRecovery)		// 중간에 정상적인 패킷이 존재하면.. 비정상 패킷만 버린다.
					{
						if((g_nSocketSize - nRecoveryPos) > 0 && (g_nSocketSize - nRecoveryPos) < MAX_PACKETSIZE)
						{
							memmove(g_szSocketBuff, &g_szSocketBuff[nRecoveryPos], g_nSocketSize - nRecoveryPos);
							g_nSocketSize -= nRecoveryPos;
						}
						else
							g_nSocketSize = 0;
					}
					else				// 받은 패킷 모두를 버린다.
					{
						if((g_nSocketSize - nBytes) > 0 && (g_nSocketSize - nBytes) < MAX_PACKETSIZE)
						{  // 뒤에 받은 정상적이 패킷은 memmove로 유지
							memmove(g_szSocketBuff, &g_szSocketBuff[nBytes], g_nSocketSize - nBytes);
							g_nSocketSize -= nBytes;				
						}
						else
							g_nSocketSize = 0;
					}
				}
				CATCH(CMemoryException, e)
				{
					char buff[1024];
					memset(buff, 0x00, sizeof(buff));
					e->GetErrorMessage(buff, 1024);
					strLog.Format("%s", buff);
					WriteErrorLog(strLog);

					// 메모리 move하다 오류난 경우는 다 clear 해준다..
					g_nSocketSize = 0;
				}
				END_CATCH
				
				//-> 이럴일은 없을듯 하나 어쨋든 - 이면 0으로 초기화한다.
				if(g_nSocketSize < 0)
					g_nSocketSize = 0;

				break;
			}

			g_dwSocketBufLen = nBytes = nCHLength;
			memcpy(g_szRecvBuf, g_szSocketBuff, nBytes);	// 전송할 데이타 복사

			if (g_nSocketSize - nBytes > 0)
				memmove(g_szSocketBuff, &g_szSocketBuff[nBytes], g_nSocketSize - nBytes);
			g_nSocketSize -= nBytes;

			AddSocketData((UCHAR*)g_szRecvBuf, bFirst, nCHLength);
		}
	}

	TRACE(" StartReceive Thread 종료.....\n");
}


//******************************************************************
//  Function Name : Receive
//  Function      : 소켓에서 지정한 길이단위로 데이터를 취득하는 함수 
//  Param         : void* lpBuf, int nBufLen, int nFlags /*= 0*/
//					void* lpBuf		수신버퍼 포인터 
//					int nBufLen		취득하고자 하는 길이 
//					int nFlags		옵션값 (0:데이터 취득후 버퍼 삭제) 
//  Return        : int				취득한 길이
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int	CTcpSocket::Receive(void* lpBuf, int nBufLen, int nFlags /*= 0*/)
{
	unsigned long nPos = 0,  nTotalLen = 0;	
	int			  nReadLen = 0;

	while( nTotalLen != (unsigned long)nBufLen )
	{
		nReadLen = recv( m_hSocket, (char*)lpBuf + nPos, nBufLen - nTotalLen, 0);
		if ( nReadLen == SOCKET_ERROR || nReadLen == 0 )
		{
			m_nSocketErrorCode = ::WSAGetLastError();
			if ( m_nSocketErrorCode == WSAEWOULDBLOCK )
			{
//				if (g_pMainFrm->m_hCommsDbgWnd != NULL && ::IsWindow( g_pMainFrm->m_hCommsDbgWnd ))
//				{
//					CString strBuf;
//					strBuf.Format("<<<====Socket Read상태 대기모드.....totallen=[%d], curLen=[%d]", nBufLen, nTotalLen);
//
//					g_pMainFrm->CommsDbgLog( (LPSTR)(LPCTSTR)strBuf , LOG_UM);
//				}
				//////////////////////////////////////////////////////////////
				// 20mm sec기다린 후 다시 읽는다.
				//////////////////////////////////////////////////////////////
				while(::WaitForSingleObject( m_hRecvStopEvent, RECEIVE_WAIT_TIME )  == WAIT_TIMEOUT)
				{
					break;
				}
				continue;
			}
			else
			{
				WSACancelBlockingCall();
//TRACE("WSACancelBlockingCall\n");
				return nReadLen;
			}
		}
		if( nReadLen > 0)
		{
			nPos		+= nReadLen;
			nTotalLen	+= nReadLen;
			///////////////////////////////////////////////////////////
			// 한번에 읽은 데이터가 Gateway Header보다 작은 데이터는
			// 없는 걸로 간주한다.
//			if(nReadLen < n_GW_HEADER_SIZE)
//			{
//				break;
//			}
			if(nTotalLen != (unsigned long)nBufLen)
			{
				CString strBuf;
				strBuf.Format("<<<====Socket 재Read상태 ....totallen=[%d], curLen=[%d]", nBufLen, nTotalLen);
				CommsDbgLog( (LPSTR)(LPCTSTR)strBuf , LOG_UM);
				//////////////////////////////////////////////////////////////
				// 20 mm sec기다린 후 다시 읽는다.
				//////////////////////////////////////////////////////////////
				while(::WaitForSingleObject( m_hRecvStopEvent, RECEIVE_WAIT_TIME )  == WAIT_TIMEOUT)
				{
					break;
				}
				continue;
			}
			continue;
		}
	}
//DiffTime = ::GetTickCount() - STime;
//TRACE(" Receive time %d, size %d\n", DiffTime, nReadLen);

	return nTotalLen;
}

//******************************************************************
//  Function Name : Send
//  Function      : 소켓으로 데이터를 송신하는 함수 
//  Param         : const void* lpBuf, int nBufLen, int nFlags /*= 0*/
//					void* lpBuf		송신버퍼 포인터 
//					int nBufLen		송신하는 길이 
//					int nFlags		옵션값 
//  Return        : int				송신한 길이 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int	CTcpSocket::Send(const void* lpBuf, int nBufLen, int nFlags /*= 0*/)
{
	if ( m_hSocket == INVALID_SOCKET )
	{
		return SOCKET_ERROR;
	}

	g_dwSocketBufLen = nBufLen;

	int nWiteLen	= 0;
	int nPos		= 0;
	int nTotalLen	= 0;
	while( true )
	{
		BOOL bRet =  CheckSendable();	// 데이터를 송신 가능한가를 체크하는 함수
		if ( !bRet )
		{
			TRACE(" CheckSendable...Error...\n");

// --> [Edit]  김창하 2005/12/22
			if (m_hCommsDbgWnd != NULL && ::IsWindow(m_hCommsDbgWnd ))
			{
				char szBuf[MAX_PATH];
				sprintf ( szBuf, "*** CheckSendable..Fail *********" );
				CommsDbgLog( szBuf, LOG_UM );
			}
			return 0;
// <-- [Edit]  김창하 2005/12/22
		}

		nWiteLen = send( m_hSocket, (char*)lpBuf + nPos, nBufLen - nTotalLen, 0);
		if( nWiteLen == SOCKET_ERROR )
		{
			m_nSocketErrorCode = ::WSAGetLastError();
			if ( m_nSocketErrorCode == WSAEWOULDBLOCK )
			{
				TRACE(" CTcpSocket::Send WSAEWOULDBLOCK...\n");
			}
			return	nWiteLen;	
		}
		else if( nWiteLen == 0)
		{
			Sleep(5);
			continue;
		}
		
		nTotalLen	+= nWiteLen;
		nPos		+= nWiteLen;

		if( nTotalLen == nBufLen)
		{
			break;
		}
	}
	return nBufLen;
}

//******************************************************************
//  Function Name : GetSockName
//  Function      : 현재 소켓에서 접속주소와 포트번호를 취득하는 함수 
//  Param         : CString& strSocketAddress, UINT& nSocketPort
//					CString& strSocketAddress		서버주소 문자열 
//					UINT& nSocketPort				서버 포트번호 
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CTcpSocket::GetSockName(CString& strSocketAddress, 
							 UINT& nSocketPort)
{
	SOCKADDR_IN sockAddr;
	BOOL		bRet;

	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);

	bRet = (SOCKET_ERROR != getsockname(m_hSocket, (SOCKADDR*)&sockAddr, &nSockAddrLen)); 
 	if ( bRet )
	{
		nSocketPort			= ntohs(sockAddr.sin_port);
		strSocketAddress	= inet_ntoa(sockAddr.sin_addr);
	}
	return bRet;
}


//******************************************************************
//  Function Name : ReceiveStopEvent
//  Function      : 수신스레드를 중단하도록 시그럴을 보내는 함수 
//  Param         : BOOL bSignal /*= TRUE*/	시그럴값(TRUE:중단 , 그외:개시 ) 
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CTcpSocket::ReceiveStopEvent(BOOL bSignal /*= TRUE*/)
{
	if ( m_hRecvStopEvent )
	{
		if ( bSignal )
		{
			// 수신 중단 시그럴을 발생한다.
			BOOL bRet = SetEvent( m_hRecvStopEvent );
			if ( !bRet )
			{
				TRACE(" SetEvent..Error..[%d]\n", ::GetLastError());
			}
		}
		else
		{
			ResetEvent( m_hRecvStopEvent );
		}
		return TRUE;
	}
	return FALSE;
}


//******************************************************************
//  Function Name : DisConnectTCPSocket
//  Function      : 소켓을 단절하는 함수 
//  Param         : 없음
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CTcpSocket::DisConnectTCPSocket()
{
//	char szBuf[512];
//	sprintf(szBuf, "##### CTcpSocket::DisConnectTCPSocket() Call ....  !!!!!");
//	g_pMainFrm->CommsDbgLog(szBuf);

	BOOL bRet = FALSE;
	if ( m_hSocket != INVALID_SOCKET )
	{
	//	g_bSocketShutDown = TRUE;
		WSAAsyncSelect( m_hSocket, m_pParentWnd->GetSafeHwnd(), 0, 0L);

		// 수신 스레이드가 종료되었는가를 체크한다.
		if ( m_hRecvThread )
		{
			DWORD dwExitCode;
			if ( m_hRecvThread )
			{
				::CloseHandle( m_hRecvThread ); 
//	sprintf(szBuf, "##### CTcpSocket::DisConnectTCPSocket() Call ::CloseHandle( m_hRecvThread )....  !!!!!");
//	g_pMainFrm->CommsDbgLog(szBuf);
			}

			// 10초안에 안끊기면 강제로 종료한다.
			if (::GetExitCodeThread(m_hRecvThread, &dwExitCode) && dwExitCode == STILL_ACTIVE)
			{
//	sprintf(szBuf, "##### CTcpSocket::DisConnectTCPSocket() 10초안에 안끊기면 강제로 종료한다.....  !!!!!");
//	g_pMainFrm->CommsDbgLog(szBuf);
				DWORD dwRet = ::WaitForSingleObject (m_hRecvThread, 10000 );
				if ( dwRet == WAIT_TIMEOUT )
				{
//	sprintf(szBuf, "##### CTcpSocket::DisConnectTCPSocket() Call TerminateThread(WAIT_TIMEOUT).....  !!!!!");
//	g_pMainFrm->CommsDbgLog(szBuf);
					TerminateThread( m_hRecvThread, 0 );
				}
			}
			m_hRecvThread = NULL;
		}
		TRACE("DisConnectTCPSocket..\n");

		(bRet = SOCKET_ERROR != shutdown( m_hSocket, both));
		(bRet = SOCKET_ERROR != closesocket( m_hSocket ));
		m_hSocket = INVALID_SOCKET;
	}
	return bRet;
}

#ifdef _DEBUG
//******************************************************************
//  Function Name : AssertValid
//  Function      : 
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CTcpSocket::AssertValid() const
{
	CObject::AssertValid();
}

//******************************************************************
//  Function Name : Dump
//  Function      : 
//  Param         : CDumpContext& dc
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CTcpSocket::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);

	dc << "m_hSocket = ";
	if (m_hSocket == INVALID_SOCKET)
		dc << "INVALID_SOCKET\n";
	else
		dc << m_hSocket << "\n";
}

#endif //_DEBUG



//******************************************************************
//  Function Name : AddSocketData
//  Function      : 
//  Param         : BYTE* lpData, BOOL bFirst, int nLength
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CTcpSocket::AddSocketData(BYTE* lpData, BOOL bFirst, int nLength)
{
	BYTE* pPacketData = new BYTE[nLength+1];
	//memset(pPacketData, 0x00, sizeof(pPacketData));

	if( pPacketData )
	{
		TRY
		{
			memcpy(pPacketData, lpData, nLength);
		}
		CATCH(CMemoryException, e)
		{
			CString strLog(_T(""));
			char buff[1024];
			memset(buff, 0x00, sizeof(buff));
			e->GetErrorMessage(buff, 1024);
			strLog.Format("%s", buff);
			WriteErrorLog(strLog);

			delete [] pPacketData;
			pPacketData = NULL;
			return;
		}
		END_CATCH

		pPacketData[nLength] = 0x00;

		RecvDataPair pairData;
		pairData.first  = bFirst;
		pairData.second = pPacketData;
		SetWriteRecvQueueData( pairData );
	}
}

//******************************************************************
//  Function Name : SetWriteRecvQueueData
//  Function      : 
//  Param         : RecvDataPair &lpData 
//  Return        : int 
//  Create        : 전순모 , 2006/04/10
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int CTcpSocket::SetWriteRecvQueueData( RecvDataPair &lpData ) 
{ 
	m_sect.Lock();

	int nCount = 0;
	m_RecvDataPairQue.push(lpData);
	nCount  = m_RecvDataPairQue.size();
	
	m_sect.Unlock();
	return nCount; 
}

//******************************************************************
//  Function Name : GetReadRecvQueueData
//  Function      : 수신 큐에서 데이터를 취득한다.
//  Param         : RecvDataPair& DataQue
//  Return        : int			나머지 큐 데이터수.
//  Create        : 김창하 , 2006/03/22
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int CTcpSocket::GetReadRecvQueueData(RecvDataPair& DataQue)
{
	m_sect.Lock();
	int nCount  = m_RecvDataPairQue.size();
	if ( nCount > 0 )
	{
		DataQue = m_RecvDataPairQue.front();
		m_RecvDataPairQue.pop();
#ifdef _DEBUG
		COMMONHEADER* pCommHeader = (COMMONHEADER*)(BYTE*)DataQue.second;
	//	TRACE("\n GetReadRecvQueueData() CommandId : %x\n", pCommHeader->cCommandId);
#endif
	}
	m_sect.Unlock();
	return nCount;
}

int CTcpSocket::GetQueueSize()
{
	return m_RecvDataPairQue.size();
}

//******************************************************************
//  Function Name : AllRecvDataQueueClear
//  Function      : 수신 큐 데이터를 클리어 하는 함수.
//  Param         : 없음
//  Return        : void 
//  Create        : 김창하 , 2006/03/22
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CTcpSocket::AllRecvDataQueueClear()
{
	m_sect.Lock();//-------------------------------------
	
	RecvDataPair lpData;
	int nCount = m_RecvDataPairQue.size();
	if ( nCount > 0 )
		TRACE("Last Queue Delete Count...[%d]\n", m_RecvDataPairQue.size());
	else
		return;

	while (!m_RecvDataPairQue.empty())
    {
        lpData = m_RecvDataPairQue.front();
		LPBYTE lpBuf = (BYTE*)lpData.second;
		if ( lpBuf )
			delete[] lpBuf;

        m_RecvDataPairQue.pop();
    }

	m_sect.Unlock();//-------------------------------------
}

//******************************************************************
//  Function Name : ReceiveTick
//  Function      : 
//  Param         : 없음
//  Return        : void 
//  Create        : 전순모 , 2006/04/11
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CTcpSocket::ReceiveTick()
{
	if ( m_bRecvStop )
	{
		// 모든 큐데이터를 삭제한다.
		AllRecvDataQueueClear();
		return;
	}	

	RecvDataPair	pairData;
	int		nFirst;
	BYTE*	pData;

	while ( !m_bRecvStop &&  GetReadRecvQueueData( pairData) >0 )
	{
		nFirst	= pairData.first;
		pData	= pairData.second;

		DataReceive(pData, nFirst);
		
		delete []pData;
	}
}

//*******************************************************************/
/*! Function Name : GetServerIPfromEnpiaDNS
/*! Function      : IP 마스터를 통한 접속IP취득처리
/*! Param         : CString strDomainName
/*! Return        : CString 
/*! Create        : 이용준 , 2008/03/07
/*! Comment       : 
//******************************************************************/
CString CTcpSocket::GetServerIPfromEnpiaDNS(CString strDomainName)
{
	HMODULE hMod = LoadLibrary("HkMsgOem.dll");
	if((hMod == NULL) || (strDomainName.IsEmpty()))
	{
		return _T("");
	}
	struct hostent *hp = gethostbyname(strDomainName);
	FreeLibrary(hMod);

	if(hp == NULL)
	{
		AfxMessageBox("접속서버 IP 취득 실패입니다.");
		return "";
	}

	struct  in_addr sin_addr;
	CString strResult = _T("");
	/////////////////////////////////////
	// 최상위 1건만 사용한다.
	/////////////////////////////////////
	if(hp)	// IPMaster(TM) Client
	{
		memcpy(&(sin_addr), hp->h_addr_list[0], hp->h_length);
		strResult += inet_ntoa(sin_addr);
	}

	return strResult;
}

//*****************************************************************************
// 루    틴    명  :  CheckSendable
// 기          능  :  데이터를 송신 가능한가를 체크하는 함수   
// 입          력  :  없음  
// 출          력  :  int				정상:TRUE
// 작    성    자  :  
// 수  정  이  력  :  
//*****************************************************************************
int CTcpSocket::CheckSendable() 
{ 
   fd_set	writefds; 
   
   int		nSelect; 
   struct	timeval timeout; 

   FD_ZERO(&writefds);
   FD_SET( m_hSocket, &writefds);

   timeout.tv_sec  = 1; 
   timeout.tv_usec = 0; 

   // 송신 가능한가?
   nSelect = select( m_hSocket+1, NULL, &writefds, NULL , &timeout ); 
   FD_CLR( m_hSocket, &writefds);

   return ( nSelect == 1) ? TRUE : FALSE; 
}

BOOL CTcpSocket::IsValidSocketHandle()
{
	if (m_hSocket == INVALID_SOCKET)
		return FALSE;

	return TRUE;
}

void CTcpSocket::SetWriteConsol(char* pBuf)
{
	m_pParentWnd->SendMessage(UM_LOG_CONSOL, (WPARAM)pBuf, (LPARAM)strlen(pBuf));
}


BOOL CTcpSocket::CommsDbgLog(LPSTR lpstr, WORD wDataType)
{
	m_pParentWnd->SendMessage(UM_LOG_COMS_DBG, (WPARAM)lpstr, (LPARAM)wDataType);

	return TRUE;
}

void CTcpSocket::DataReceive(BYTE* pData, int nFirst)
{
	m_pParentWnd->SendMessage(UM_DATA_RECEIVE, (WPARAM)pData, (LPARAM)(BOOL)nFirst);
}


//////////////////////////////////////////////////////////////////////////
//-> 2012.02.28 jhj
BOOL CTcpSocket::RecvDataBlock(char *packetBuf, long nBufSize)
{
	long len = 0, total = 0;
	int nErrorCnt = 0;

	memset(packetBuf, 0x00, nBufSize);
	do 
	{
		len	= recv(m_hSocket, (char*)&packetBuf[total], nBufSize - total, 0);
		if(len <= 0)
		{
			int nCode = WSAGetLastError();
			CString sLog(_T(""));
			sLog.Format("RecvDataBlock -> Error:%5d\tnBuf:%5d\tlen:%5d\r\n", nCode, nBufSize, len);
			WriteErrorLog(sLog);

			if( nCode == WSAENOTSOCK	|| nCode == WSAEOPNOTSUPP	||
				nCode == WSAENETDOWN	|| nCode == WSAENETRESET	||
				nCode == WSAECONNABORTED|| nCode == WSAECONNRESET	||
				nCode == WSAENOTCONN	|| nCode == WSAESHUTDOWN	||
				nCode == WSAETIMEDOUT	|| nCode == WSANOTINITIALISED)
			{
				WSACancelBlockingCall();
				Sleep(20);
				return FALSE;
			}
			else
			{
				Sleep(10);
				nErrorCnt++;			
				if( nErrorCnt > 50)		
					return FALSE;
				continue;
			}
		}

		total += len;

		if(total < nBufSize)
		{
			Sleep(1);
		}
	}while(total < nBufSize);

	return TRUE;
}

//-> EzNetSmart Function 그대로 사용.
BOOL CTcpSocket::SendErrorReport(BOOL bForce,BYTE chType,LPCTSTR lpszErrorReport,BYTE *pRawBuffer,int nRawDataLen)
{
	// 계속 던지면 서버가 미치니까 적당히 던지자...
	time_t t;
	int nTitleLen=0, nLen, nPos=0;
	int nRealRawDataLen=0;
	ERR_REPORT_BUFFER ERB;

	time(&t);
	if ((t!=m_SendErrorReportTime)||(bForce==FALSE)) {
		m_SendErrorReportTime = t;

		memset(&ERB,0,SZ_ERR_REPORT_BUFFER);
		if (lpszErrorReport!=NULL) {
			nTitleLen = lstrlen(lpszErrorReport);
		}
		ERB.szType    = chType;
		ERB.filler_1  = ':';
		if(nTitleLen>0){
			strncpy(ERB.szTitle,lpszErrorReport,MAX_ERR_REPORT_TITLE);
		}
		nRealRawDataLen = nRawDataLen;
		sprintf(ERB.szLenBuffer,"%04d",nRawDataLen);
		if (nRawDataLen>=MAX_ERR_REPORT_RAW_BUFFER) {
			nRealRawDataLen = MAX_ERR_REPORT_RAW_BUFFER;
		}
		sprintf(ERB.szRealLenBuffer,"%04d",nRealRawDataLen);
		if (pRawBuffer!=NULL) {
			memcpy(ERB.pRawDataBuffer,pRawBuffer,nRealRawDataLen);
		}
		m_PacketSendLock.Lock();
		nLen = SZ_HD_ERR_REPORT_BUFFER + nRealRawDataLen;
		SendRawPacket(NULL,PID_ERROR_REPORT,(char*)&ERB,nLen);
		m_PacketSendLock.Unlock();
		return(TRUE);
	}

	return(FALSE);
}

//-> EzNetSmart Function 그대로 사용.( 오류 레포트 전송만 발췌함!)
BOOL CTcpSocket::SendRawPacket(HWND hWnd, unsigned char chPacketType, char *packetBuf, long nBufSiz,unsigned char chChainFlg)
{
	static char	send_buffer[MAX_BUFLEN + DATASTART_POS];
	// MOD NEOFRAME KHY : 20050524
	BOOL	secu = FALSE;			//암호화 여부
	int 	outlen=0;				// Buffer Data Length
	int		nRet=0;					// Result Check
	int		nCTXState=0;

	memcpy(&send_buffer[DATASTART_POS], packetBuf, nBufSiz);

	BYTE chFlag = 0x00;
	// comm header 구성
	send_buffer[HEADLEN_SIZ + 4] = chFlag|chChainFlg;	// 암호화 여부
	send_buffer[HEADLEN_SIZ + 5] = chPacketType;	// packet type
	send_buffer[HEADLEN_SIZ + 6] = '0';				// filler
	send_buffer[HEADLEN_SIZ + 7] = '0';				// filler



	// packet 길이 복사 : 앞에 길이 4 byte 는 제외한다.
	long	nPacketLength = HEADERLEN + nBufSiz;
	nPacketLength = htonl(nPacketLength);
	memcpy(&send_buffer[0], &nPacketLength, SZ_LG);

	// 자료를 받아야할 윈도우를 등록한다.
	// MOD NEOFRAME KHY : 20050524
	if ((chChainFlg==0)||(chChainFlg&PC_PACKS)) 
	{
		m_nPacketId = m_nPacketId + 0x00000001;
	} 
	else if (chChainFlg&PC_COMPRESS) 
	{
		if (!((chChainFlg&PC_PACKE)||(chChainFlg&PC_PACKM))) 
		{
			m_nPacketId = m_nPacketId + 0x00000001;
		}
	}
		// END MOD NEOFRAME KHY : 20050524
	if( m_nPacketId >= 0x11111111)
		m_nPacketId = 0x00001000;
	memcpy(&send_buffer[HEADLEN_SIZ], &m_nPacketId, SZ_LG);

	// window id 복사
	memcpy(&send_buffer[HEADLEN_SIZ + 8], &hWnd, SZ_LG);
	char	*szSendBuf = NULL;		//Data를 만들 준비를 한다.
	szSendBuf = new char[DATASTART_POS + nBufSiz];	//data size만큼 만든다. 
	if( szSendBuf == NULL)
		return FALSE;

	memcpy(&szSendBuf[0], &send_buffer[0], DATASTART_POS + nBufSiz);	//header + data copy
	memcpy(&szSendBuf[HEADLEN_SIZ + 8], &m_lMaxSeq, SZ_LG);
	m_lMaxSeq++;
	if( m_lMaxSeq >= 100000)
		m_lMaxSeq = 1;

	long	size = *(long*)(&szSendBuf[0]);
	size = htonl(size);
	BOOL	sendcheck = FALSE;
	sendcheck = SendDataBlock(szSendBuf, HEADLEN_SIZ + size);
	if( sendcheck != TRUE)
	{
		if( szSendBuf) delete []szSendBuf;
		return FALSE;
	}

	if(szSendBuf) delete []szSendBuf;
	return TRUE;
}

BOOL CTcpSocket::SendDataBlock(char *packetBuf, long nBufSiz)
{
	long	len, total = 0;
	int		nErrorCnt = 0;	//shc 20020103
	long	lCheckLen = 0;	//KJI 20021218 Add

	do
	{	
		//한번에 최대 보낼수 있는 사이즈를 1024로 제한하며 나누어서 보낸다.
		lCheckLen = (nBufSiz - total) > 1024 ? 1024 : (nBufSiz - total);	//KJI 20021218 Add
		
		len = send(m_hSocket, &packetBuf[total], lCheckLen, 0);
		if( len < 0)		//shc 20010910
		{
			int nCode = WSAGetLastError();
			CString sLog(_T(""));
			sLog.Format("SendDataBlock -> Error = %d\r\n", nCode);
			WriteErrorLog(sLog);

			//error code가 틀리다. - send, receive 구분해서 처리.
			if( nCode == WSAENOTSOCK	|| nCode == WSAEOPNOTSUPP	||
				nCode == WSAENETDOWN	|| nCode == WSAENETRESET	||
				nCode == WSAEACCES		|| nCode == WSAECONNRESET	||
				nCode == WSAENOTCONN	|| nCode == WSAESHUTDOWN	||
				nCode == WSAETIMEDOUT	|| nCode == WSANOTINITIALISED)
			{
				WSACancelBlockingCall();
				Sleep(20);
				return FALSE;
			}
			else
			{
				Sleep(10);				//shc 20040106
				nErrorCnt++;
				if( nErrorCnt > 50)
					return FALSE;
				continue;
			}
		}
		else if( len == 0)
		{	//shc 20020103 - 0은 valid한 값이다. looping을 다시돈다.
			Sleep(5);
			continue;
		}

		total += len;

		if( total < nBufSiz)
		{
			Sleep(1);		
		}
	}while( total < nBufSiz);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
void CTcpSocket::WriteErrorLog(CString sLog)
{
#ifdef __SOCKET_LOG
	{
		CString strError, strTm;
		SYSTEMTIME	tm;
		CTime	t = CTime::GetCurrentTime();	//GetCurrentTime을 처리해야 LocalTime을 가져올수 있다. 
		GetLocalTime(&tm);
		strTm.Format("<%02d:%02d:%02d:%03d> : ", tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
		
		strError.Format("%s%s\n", strTm, sLog);

		CString	strDir;
		GET_LOG_DIR(strDir);
		strDir += "\\SocketErr.log";
		FILE *fp = fopen(strDir, "ab");
		if(fp)
		{
			fseek(fp, 0L, SEEK_END);
			fwrite(strError, strlen(strError), 1, fp);
			fclose(fp);
		}

		strError = "[jhj] "+strError;
		OutputDebugString(strError);
	}
#endif
}