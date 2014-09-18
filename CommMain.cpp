// D:\한화증권\소스\src\Common\CommMain.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CommMain.h"
#include "complzo.h"
#include "PacketMngr.h"

#include "../TrDll/CheJanStruct.h"

// 속도 차원에서 글로벌로...
//BYTE g_pbySendEncrypTemp;		// Encryption Buffer
//BYTE* g_pbySendCompressTemp;	// Compress Buffer

// CommApi에게 통신상태를 알려주기 위한 메세지 정의
extern UINT g_uSocketNotifyMsg;

UINT		g_unAbnormalPacketCount = 0;

#define		MAX_COMM_SIZE			8192

#define		UM_WNDCHECKTIMER		100
#define		DEF_WINDOW_CHECK_TIME	20000			//	30초 단위로 체크한다.
// CCommMain

IMPLEMENT_DYNAMIC(CCommMain, CWnd)

CCommMain::CCommMain(CWnd* pParentWnd,
					  COMMS_CONFIG* pCommsConfig,
					 CDWordArray* pArrCommApiWnd,
					 CLogMsg* pLogMsg)
{
	m_pParentWnd			= pParentWnd;
	m_hCommsDbgWnd			= NULL;
	m_pCommsConfig			= pCommsConfig;
	m_pLogMsg				= pLogMsg;
	m_pArrCommApiWnd		= pArrCommApiWnd;

	m_hLoginCommApiWnd		= NULL;
	m_pTcpSocket			= NULL;		// 소켓 초기화
	m_pCtx					= NULL;

//	m_nReConnect			= 0;		// 재접속 요청 상태
	m_nPollTime				= 0;		// 폴링 체크용
	m_bConnect				= FALSE;	// 연결상태 값
	m_nRetryCount			= 1;		// 재 접속 수
	m_bConnectSubPort		= FALSE;	// sub port로 접속 인가
	m_nSignOn				= 0;		// 로그온 상태 (0:미 로그온,1: 로그온 완료, 2: 인증완료)
	m_nRetryConnectTimer	= 0;		// 재 연결 타이머 아이디값 
	m_nOneSecondTimer		= 0;		// 1초 타이머 (RQ/RP 타임아웃체크)
	m_bColsolCreate			= FALSE;	// Consol생성 여부
	m_bReadSizeDsp			= 0;		// CommsDbg에 수신데이터 사이즈 표시 여부
	m_bUseCompress			= TRUE;
	
	m_bToBPServer			= FALSE;	// BP 서버 접속인지

	m_nRePortPosition		= 0;
	m_nTotalRetryCount		= 0;

	m_nWndCheckTimer		= 0;

	//KJI 20110520
	m_hRecvEndThread		= NULL;
	m_pRecvTickThread		= NULL;
}

CCommMain::~CCommMain()
{
	if (m_pSendPacket != NULL)
		delete[] m_pSendPacket;
}


BEGIN_MESSAGE_MAP(CCommMain, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
		
	ON_MESSAGE(WM_COPYDATA,				OnCopyData)
	ON_MESSAGE(WM_USER_SOCKET_NOTIFY,	OnSocketNotify)

	ON_MESSAGE(UM_LOG_CONSOL,			OnSetWriteConsol)	// consol에 로그 기록 하기 위해
	ON_MESSAGE(UM_LOG_COMS_DBG,			OnCommsDbgLog)		// ComsDbg에 로그를 기록 하기 위해
	ON_MESSAGE(UM_DATA_RECEIVE,			OnDataReceive)		// 수신 완료 패킷 처리를 위해
	ON_MESSAGE(UM_WND_STATE_CHECK,		OnRemoveCommApiCheck)// CommApi 체크후 남아있는 CommApi가 없을경우 종료하는 메시지

END_MESSAGE_MAP()


void CCommMain::SetCommsDbgWndHandle(HWND hCommsDbgWnd)
{
	m_hCommsDbgWnd = hCommsDbgWnd;
	m_RequestDataObList.m_hCommsDbg = m_hCommsDbgWnd;
}
// CCommMain 메시지 처리기입니다.


int CCommMain::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
SetWriteLog("====================================");
SetWriteLog("========= (소켓 연결 시작) =========");
SetWriteLog("====================================");

	// 데이타 버퍼 메모리 할당 
	m_pSendPacket		= new BYTE[MAX_PACKET_SIZE];

	// 자신의 윈도우 핸들을 설정한다.
	m_hCommsWnd		= GetSafeHwnd();
	
	InitialLZO();

	return 0;
}

void CCommMain::OnDestroy()
{
	SetThreadInit( FALSE );

	HostDisconnect();

	if (m_pTcpSocket)
	{
		delete m_pTcpSocket;
		m_pTcpSocket	= NULL;
	}

	if (m_nRetryConnectTimer)
	{
		KillTimer(m_nRetryConnectTimer);
		m_nRetryConnectTimer = 0;
	}

	if (m_nOneSecondTimer)
	{
		KillTimer(m_nOneSecondTimer);
		m_nOneSecondTimer = 0;
	}

	if (m_nWndCheckTimer)
	{
		KillTimer(m_nWndCheckTimer);
		m_nWndCheckTimer = 0;
	}

	CWnd::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CCommMain::OnTimer(UINT_PTR nIDEvent)
{
	// 재 접속 타이머인 경우 
	if (nIDEvent == m_nRetryConnectTimer)
	{
		if (m_nRetryConnectTimer)
		{
			KillTimer(m_nRetryConnectTimer);
			m_nRetryConnectTimer = 0;
		}

		if (m_bConnect)
		{
			// 재접속 횟수
			m_nRetryCount = 0;
		}
		else
		{
// --> [Edit]  강지원 2011/04/12 ( 재접속 수정 )
			m_pTcpSocket->DisConnectTCPSocket();
			RetryConnectToServer(0);

			//KJI 20110516
			if (m_nRetryCount != 0 || m_nTotalRetryCount != 0 )
			{
				// 접속 시도 하기
				HostConnect();
			}	
// <-- [Edit]  강지원 2011/04/12
		}
	}
	// RQ/RP 채크
	else if (nIDEvent == m_nOneSecondTimer)
	{
		////////////////////// Time out처리 ///////////////////
		m_RequestDataObList.DecreaseTimer(m_hCommsWnd, FALSE);
					
		////////////////////// 폴링 체크 ////////////////////
		m_nPollTime++;
		// 180 = 60 * 3 : 3분동안 데이터 송수신이 없다면...
		if (m_nPollTime > POLLING_CHECK_INTERVAL)
		{
			char cCommandId;
			// BP 서버 접속인 경우
			if (m_bToBPServer)
				cCommandId	= (BYTE)PID_BP_POLLING;
			else
				cCommandId	= (BYTE)PID_POLLING;
			CPacketMngr PacketMngr;
			PacketMngr.SendCopyData(GetSafeHwnd(), cCommandId, NULL, 0);

			m_nPollTime = 0;			// 폴링 체크용
		}
	}
	// 키 교환TimeOut발생 
	else if (nIDEvent == m_nKeyChangeTimer)
	{
		KillTimer(m_nKeyChangeTimer);
		m_nKeyChangeTimer = 0;
		
		// 각 화면으로 타임아웃 발생을 통지한다.
		SendSocketNotifyToAllCommApi(LOGIN_FAIL);
	}
// --> [Edit]  강지원 2010/12/19
	// Commapi가 비정상 종료되었을때 통신모듈을 종료한다.
	else if (nIDEvent == m_nWndCheckTimer)
	{
		// ComApi에 보내기........
		HWND hCommAPIWnd = NULL;
		long lRet;
		BOOL bFlag = FALSE;

//// --> [Edit]  강지원 2010/12/20
////#ifdef	_DEBUG
//		// 임시
//		CString strMsg = "";
//		strMsg.Format("핸들 갯수.. %d", m_pArrCommApiWnd->GetSize());
//		AfxMessageBox(strMsg);
////#endif
//// <-- [Edit]  강지원 2010/12/20

		for (int nCnt = m_pArrCommApiWnd->GetSize() - 1; nCnt >= 0; nCnt--)
		{
			hCommAPIWnd = (HWND)(*m_pArrCommApiWnd)[nCnt];

			if (!::IsWindow(hCommAPIWnd))
			{
//// --> [Edit]  강지원 2010/12/20
////#ifdef	_DEBUG
//				// 임시
//				CString strMsg = "";
//				strMsg.Format("핸들 삭제... %x", hCommAPIWnd);
//				AfxMessageBox(strMsg);
////#endif
//// <-- [Edit]  강지원 2010/12/20

				m_pArrCommApiWnd->RemoveAt(nCnt);
				PostMessage(UM_WND_STATE_CHECK);
			}
		}
	}
// <-- [Edit]  강지원 2010/12/19

	

	CWnd::OnTimer(nIDEvent);
}

long CCommMain::OnCopyData(UINT wParam, long lParam)
{
	BOOL	bDataDelete	= FALSE;
	int		nKind		= LOWORD(wParam);
	BOOL	bReturn;
	long	lRet;
	lRet = (long)REQUEST_SUCCESS;

	// 데이터 구분자를 취득한다.
	// CommsDbg로 데이터를 표시한다.
	PCOPYDATASTRUCT pcds	= (PCOPYDATASTRUCT)lParam;
	HWND hCommApi			= (HWND)pcds->dwData;	// CommApi윈도우 핸들
	long nBufLen			= pcds->cbData;			// 데이터 길이 = RQ_COMMINFO_SIZE + body
	int nBodyLen;		// body
	int nSendDataSize;	// 헤더 + body
	int nHeaderSize;

	COMMONHEADER* pCommonHeader;	// 공통헤더

	// 로그만 남기는 경우다.. 서버로는 전송 하지 않는다.
	if (nKind == DATAKIND_COMM_DEBUG)
	{
		WORD	wDataGubun  = HIWORD(wParam);	// 데이터 구분자
		SendToDebugWindow(m_hCommsDbgWnd, nBufLen, pcds->lpData, wDataGubun);
		return REQUEST_SUCCESS;
	}
	
	// 통신이 연결 되어 있는 상태인가?
	if (!m_bConnect)
		return REQUEST_ERROR_NOTCONNECT;

	REQUEST_COMMINFO* pRqCommInfo;
	BYTE *pData;
	pRqCommInfo	= (REQUEST_COMMINFO*)pcds->lpData;
	pData		= (((BYTE*)pcds->lpData) + RQ_COMMINFO_SIZE);
	nBodyLen	= nBufLen - RQ_COMMINFO_SIZE;
	
	/////////////////////////////////// 공통헤더 만들기 //////////////////////////////////
	// TR 인 경우 TR 헤더를 추가 해야 한다.
	if (pRqCommInfo->cMsgId == DM_RQ_ID && pRqCommInfo->TrHeader.nDataheader != NO_TR_HEADER)
		nHeaderSize = HEADER_SIZE;
	// TR 아닌 경우
	else
		nHeaderSize = COMMON_HEADER_SIZE;
	
	nSendDataSize = nHeaderSize + nBodyLen;
	// 전체 send 할 데이터
	BYTE* pSendPacket = new BYTE[nSendDataSize];
	memset(pSendPacket, 0x00, nSendDataSize);
	// 공통 헤더
	pCommonHeader = (COMMONHEADER*)pSendPacket;
	// body
	memcpy(pSendPacket + nHeaderSize, pData, nBodyLen);

	// Common Header - SIZE_DEF_PACKET(nPacketLen 제외) + Tr Header + body
	pCommonHeader->ulPacketLen	= htonl(nHeaderSize - SIZE_DEF_PACKET + nBodyLen);
	// 서버에서 pCommonHeader->ulRqId 값을 다른 용도로 사용하고 있어서
	// pCommonHeader->ulWinHwnd에 pRqCommInfo->cRqId를 넣는다.
	pCommonHeader->ulRqId		= pRqCommInfo->cRqId;
	pCommonHeader->ulWinHwnd	= pRqCommInfo->cRqId;
	pCommonHeader->cCommandId	= pRqCommInfo->cCommandId;
	
	// bit단위 처리
	// 압축 | 암호화 | 미사용 | 압축 후 사이즈가 큰 경우 | packet시작 | packet연속 | packet끝 | 0x01
	pCommonHeader->cCpFlag = 0x00;
	// 로그인은 암호화를 무시
	if (pCommonHeader->cCommandId != PID_CONNECT &&
		pCommonHeader->cCommandId != PID_PLOT_CONNECT)	//KJI 20120206 (모의투자 접속처리)
	{
		// 암호화 여부.
		if (pRqCommInfo->TrHeader.ucEncrypt == '1' && m_pCommsConfig->m_bUseEncrypt)
			pCommonHeader->cCpFlag |= FLAG_ENCRYPT;
	}

	// 에러 flag
	pCommonHeader->cErrComm		= '0';
	// 목적지 서버
	pCommonHeader->cServerType	= pRqCommInfo->cJobChk[0];

	/////////////////////////////////////// TR 요청인 경우 ///////////////////////////////////////
	if (pRqCommInfo->cMsgId == DM_RQ_ID)
	{
		BOOL bAddRequest = TRUE;
	
		// 응답이 필요 없는 경우....
		if (pRqCommInfo->TrHeader.nRqID == MINOR_AS_LOGIN_DATA ||	// 로그인정상 통보 전송
			pRqCommInfo->TrHeader.nRqID == MINOR_SETPUBLIC_KEY)		// 공인인증 성공인경우는 무조건 보내고 말자.
		{
			bAddRequest = FALSE;
		}
		
		CRequestData* pRequestData = NULL;
		CString strWndSeqID;

		if (bAddRequest)
		{
			pRequestData = new CRequestData;
			if (!pRequestData)
			{
				if (pSendPacket != NULL)
					delete[] pSendPacket;

				return 6L; // 메모리 에러
			}
			// HWND, MinorID 세트
			pRequestData->m_ulWinHwnd		= (long)pRqCommInfo->hRQRPWnd;
			pRequestData->m_ulRqId			= pRqCommInfo->cRqId;				// ComApi에서 부여한 RqId
			pRequestData->m_hCommAPIWnd		= (HWND)hCommApi;					// CommApi window Handle
			pRequestData->m_wOriginTimeOut	= pRqCommInfo->TrHeader.nTimeOut;	// Time Out
			pRequestData->m_wLeftTimeOut	= pRqCommInfo->TrHeader.nTimeOut;	// Time Out
			pRequestData->m_nSize			= 0;								// 초기 Receive사이즈 초기화
			pRequestData->m_lpData			= NULL;								// Receive Buf초기화
			pRequestData->m_bFirstPacket	= FALSE;
			memcpy(pRequestData->m_ucTrCode, pRqCommInfo->cTrCode, TRCODE_SIZE);

			// ComApi에서 새로 생성한 RqId
			strWndSeqID.Format("%04d", pRqCommInfo->cRqId);		
			m_RequestDataObList.AddData(strWndSeqID, pRequestData);
		}

		// TR헤더가 있는 경우
		if (pRqCommInfo->TrHeader.nDataheader != NO_TR_HEADER)
		{
			// Tr 헤더
			TRHEADER* pTrHeader	= (TRHEADER*)(pSendPacket + COMMON_HEADER_SIZE);
		
			///////////////////////////////////// TR 헤더 /////////////////////////////////
			memcpy(pTrHeader->cTRCode, pRqCommInfo->cTrCode, sizeof(pRqCommInfo->cTrCode));
			pTrHeader->cBenefit		= pRqCommInfo->cBenefit;		// 수익증권여부(Y:수익증권, N:아님)
			pTrHeader->cNextPrev	= pRqCommInfo->cContChk[0];		// TR조회시 이전/다음을 표시하는값,
											// SERVER: 이전, 이후 버튼 enable 여부
											// CLIENT: 이전, 이후 data 요청(data 항목에 필요시 종목코드를 올린다)
											// 0:전후 Disable, 1:전Enable, 2:후Enable, 3:전후Enable
											// 옵션 data가 있을 경우 : 옵션 data 다음에 온다(이전 이후 key data가)
											// 옵션 data가 없을 경우 : data 부분에 온다.
			
			pTrHeader->cTrErrorFlag = '0';	// '0':정상, '1':에러 ==> 메세지code로 pc에서 출력
											// '2':정상, '3':에러 ==> Data 부분에 80 Byte의 메세지 출력[MSG(80 Byte) + Data]
			pTrHeader->ulTrBodySize = htonl(nBodyLen);	// C->S(옵션길이:이전이후 key data가 있을 경우도 포함)
											// S->C(압축전의 전체 data 길이)

			pTrHeader->cErrCode[0]	= pRqCommInfo->cJobChk[0];	// 에러코드 첫번째에 목적지 구분(서버 구분)을 넣는다.
			memcpy(pTrHeader->cErrCode + 1, pRqCommInfo->sSCRN, 4);		
		}		
	}
	// 서버로 전송
	bReturn = fnSend(pSendPacket, nSendDataSize, pRqCommInfo->cMsgId);

	if (pSendPacket != NULL)
		delete[] pSendPacket;

	return lRet;
}

//******************************************************************
//  Function Name : OnSocketNotify
//  Function      : 소켓에서 소켓상태 통지를 취득해서 처리하는 함수
//  Param         : WPARAM wParam, LPARAM lParam
//					WPARAM wParam		소켓번호 
//					LPARAM lParam		부가정보 
//  Return        : long 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
long CCommMain::OnSocketNotify(WPARAM wParam, LPARAM lParam)
{
	CString strMsg;
	int nSocket = (int)wParam;
	
	// 소켓 에러 코드를 취득한다.
	int nErrorCode = WSAGETSELECTERROR(lParam);
	switch (WSAGETSELECTEVENT(lParam))
	{
		case FD_CONNECT:			// 소켓연결
		case FD_CONNECT_SUCCESS:	// 소켓연결 성공
		{
			if (nErrorCode == 0)
			{
// --> [Edit]  강지원 2011/04/12 ( 재접속 수정 )
				if (m_nRetryConnectTimer)
				{
					KillTimer(m_nRetryConnectTimer);
					m_nRetryConnectTimer = 0;
				}
// <-- [Edit]  강지원 2011/04/12

//---->	//KMG 2012.06.19 접속포트변경 : ip툴팁에 사용하기위해 세팅
				if( m_pTcpSocket->GetHostPort() == m_pCommsConfig->m_nSubPort )
					m_pCommsConfig->m_bUseSubPort = TRUE;
				else	m_pCommsConfig->m_bUseSubPort = FALSE;
//<---

				m_bConnect = TRUE;
				// 소켓 Read용 Thread를 작성한다.
				m_pTcpSocket->CreateSocketReadThread();
			}
			else
			{
				m_bConnect = FALSE;
				m_pTcpSocket->DisConnectTCPSocket();

				//KJI 20110523 (에러 바로 리턴시 처리)
				if (m_nRetryConnectTimer)
				{
					KillTimer(m_nRetryConnectTimer);
					m_nRetryConnectTimer = 0;
				}

				//KJI 20110523
				m_pTcpSocket->DisConnectTCPSocket();
				RetryConnectToServer(0);

				//KJI 20110516
				if (m_nRetryCount != 0 || m_nTotalRetryCount != 0 )
				{
					// 접속 시도 하기
					HostConnect();
				}
//				RetryConnectToServer(nErrorCode);
			}
			break;
		}
		// 소켓연결 실패 
		case FD_CONNECT_FAIL:
		{
			m_bConnect = FALSE;

			//KJI 20110523 (에러 바로 리턴시 처리)
			if (m_nRetryConnectTimer)
			{
				KillTimer(m_nRetryConnectTimer);
				m_nRetryConnectTimer = 0;
			}

			m_pTcpSocket->DisConnectTCPSocket();
			RetryConnectToServer(0);

			//KJI 20110516
			if (m_nRetryCount != 0 || m_nTotalRetryCount != 0 )
			{
				// 접속 시도 하기
				HostConnect();
			}	
	
			break;
		}
		// 데이터 송신 가능 
		case FD_WRITE:
		{
			TRACE("Socket Send Ready Ok...\n");
		//	if (g_bSocketShutDown == TRUE )
			if (!m_pTcpSocket->IsValidSocketHandle())
			{
				ASSERT(FALSE);
				return 0L;
			}

			m_nRetryCount = 0;
			if (nErrorCode == 0)
			{
				m_bConnect = TRUE;

				m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CONNECTED);

				// Timeout 체크 타이머 기동
				if (m_nOneSecondTimer)
				{
					KillTimer(m_nOneSecondTimer); // 1초 타이머 지운다..
					m_nOneSecondTimer = 0;
				}
				m_nOneSecondTimer = SetTimer(UM_ONESECONDTIMER, 1000, NULL); // 1초 타이머 설정한다..
			}

			if (m_hCommsDbgWnd)
				CommsDbgLog((LPSTR)(LPCTSTR)"@@@ [FD_WRITE] Socket Send Ready Ok...");
			
			SendSocketNotifyToAllCommApi(SOCKET_CONNECTED);	// 통신이 연결되었음을 알리자.
			break;
		}
		// 비정상적으로 단절된 경우
		case FD_CLOSE:
		{
			m_bConnect = FALSE;

			Sleep(1000);
			m_nSignOn  = -1;	// 로그인 상태를 초기화 한다.

			ASSERT(m_pTcpSocket);
			if (m_pTcpSocket)
				m_pTcpSocket->DisConnectTCPSocket();

			m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CLOSED);
			SendSocketNotifyToAllCommApi(SOCKET_CLOSED);
		
			if (m_pCommsConfig->m_bLogWrite)	// 로그 작성 
			{
				CString strSocketMsg;
				strMsg = "Comms,OnSocketNotify SOCKET_CLOSED ,%d,%s";
				WriteLogMsg( strMsg , strSocketMsg, (DWORD)nErrorCode);

				CommsDbgLog((LPSTR)(LPCTSTR)strSocketMsg );
			}

			if (m_hCommsDbgWnd)
			{
				CString strText;
				strText.Format(" @@@ [FD_CLOSE] 통신이 단절 되었습니다... ErrorCode=[%d]", nErrorCode );
				CommsDbgLog((LPSTR)(LPCTSTR)strText);
			}

			break;
		}
	}
	return 0L;
}

//*****************************************************************************
// 루    틴    명  :  HostConnect
// 기          능  :  접속서버와 소켓 연결을 시작한다.
// 입          력  :  없음 
// 출          력  :  BOOL
//						TRUE: 연결 완료, FALSE:연결 실패
// 작    성    자  :  
// 수  정  이  력  :  
//*****************************************************************************
BOOL CCommMain::HostConnect(BOOL bInitThread)
{	
	ASSERT(m_hCommsWnd);

	// 이미 접속된 상태인가를 체크한다.
	if (m_bConnect)
		return TRUE;
	else
// --> [Edit]  강지원 2011/04/12 ( 재접속 수정 )
		m_nRetryConnectTimer = SetTimer(UM_RECONNECT_TIMER, m_pCommsConfig->m_nKeyChangeTimeOut * 1000, 0);	
// <-- [Edit]  강지원 2011/04/12

	if (m_nOneSecondTimer)
	{
		KillTimer(m_nOneSecondTimer);	// 1초 타이머 지운다..
		m_nOneSecondTimer = 0;
	}

	if ( m_nWndCheckTimer == 0 )
	{
		m_nWndCheckTimer = SetTimer(UM_WNDCHECKTIMER, DEF_WINDOW_CHECK_TIME, NULL); // 30초 타이머를 설정한다. 나중에 바꾸자...
	}
	
	///////////////////////////////////////////////////
	// 이전에 이미 소켓이 연결되어 있으면 해제하고,
	// 다시 접속을 연결한다.

	if (m_pTcpSocket)
		m_pTcpSocket->DisConnectTCPSocket();
	else
	{
		m_pTcpSocket = new CTcpSocket(this);
		m_pTcpSocket->SetHostAddressAndPort(m_pCommsConfig->GetMainIP(), m_pCommsConfig->GetMainPort());
//		m_pTcpSocket->SetHostAddressAndPort(m_pCommsConfig->m_strMainIP, m_pCommsConfig->m_nMainPort);

		if ( m_pCommsConfig->m_nMessageOpen == 1 )
		{
			CString strMsg = "";
			strMsg.Format("Connect IP = %s, Port = %d", m_pCommsConfig->GetMainIP(), m_pCommsConfig->GetMainPort());
			AfxMessageBox(strMsg);
		}
	}

	BOOL bRet = FALSE;
	// 소켓을 작성한다
	bRet = m_pTcpSocket->CreateTCPSocket();

	// 서버와 접속을 시도한다.
	if (bRet)
		bRet = m_pTcpSocket->ConnectTCPSocket();
	else
		SetWriteLog((LPSTR)"Comms::CreateTCPSocket함수 Error...");
	
	if (!bRet)
	{
		return FALSE;
	}

	if (bInitThread)
		SetThreadInit(TRUE);

	return TRUE;
}

//******************************************************************
//  Function Name : HostDisconnect
//  Function      : 접속 서버와 소켓을 단절하는 함수 
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CCommMain::HostDisconnect()
{
	if (m_pTcpSocket)
	{
		m_pTcpSocket->ReceiveStopEvent();
		Sleep(10);

		m_pTcpSocket->DisConnectTCPSocket();

		delete m_pTcpSocket; 
		m_pTcpSocket	= NULL;
	}
}


//******************************************************************
//  Function Name : fnSend
//  Function      : 한번에 보낼 크기로 데이타를 서버로 보낸다.
//  Param         : AS_SOCK_PACKET* lpPacket, int nSendLen
//  Return        : BOOL 
//  Create        : 이용준 , 2008/04/08
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CCommMain::fnSend(BYTE* lpPacket, int nSendLen, BYTE cMsgId)
{
	int		nSendBodySize		= nSendLen - COMMON_HEADER_SIZE;	// 실제 데이타 길이(공통 헤더 제외)
	BYTE*	lpSendBodyBuffer	=  lpPacket + COMMON_HEADER_SIZE;	// 실제 데이타
	COMMONHEADER* pCommHeader	= (COMMONHEADER*)lpPacket;
	CString strTemp;
	int		nRetLen;
	int		nRet			= 0;
	int		nCTXState		= 0;
	BOOL	bInsertChain	= FALSE;
	
#ifdef _WRITE_LOG_TYPE_STARTER_
	// 로그 파일 기록
	CString strLog;
	strLog = CString((char*)lpPacket, nSendLen);
	SetWriteLog(strLog);
#endif

	// 암호화 전 데이타를 Dbg로 보낸다.(Polling은 보내지 말자)
	WORD wKind = 0x00;
	if (m_hCommsDbgWnd != NULL && ::IsWindow(m_hCommsDbgWnd) &&
		pCommHeader->cCommandId != PID_SVRPOLL && pCommHeader->cCommandId != PID_BP_POLLING)
	{
		if (cMsgId == DM_RQ_ID)
			wKind = LOG_RQ;
		else if (cMsgId == DM_SB_ID)
			wKind = LOG_SB;
		else if (cMsgId == DM_SBC_ID)
			wKind = LOG_SBC;
		else if (cMsgId == DM_INFO_ID)
			wKind = LOG_INFO;
		
		if (wKind > 0)
			SendToDebugWindow((HWND)m_hCommsDbgWnd, nSendLen, lpPacket, wKind);
	}

	switch (pCommHeader->cCommandId)
	{
		// 로그온
		case PID_CONNECT:
		case PID_PLOT_CONNECT:	//KJI 20120206 (모의투자 접속처리)
			nCTXState = 5;
			break;				
		default:
			nCTXState = 6;
			break;
	}

	BYTE* pbySendCompressTemp	= NULL;
	BYTE* pbySendEncrypTemp		= NULL;
	
	///////////////////////////////// 압축 체크 ///////////////////////////////
	// body의 길이가 4k가 넘으면 압축(암호화는 안함, Chain 헤더 추가, 분할 전송)
	// TR인 경우만 만족 한다.
	if (nSendBodySize > COMPRESS_STANDARD_SIZE)
	{
		ULONG ulBodySize;
		pbySendCompressTemp = new BYTE[nSendBodySize * 2];	// 우선 2배 크기로 했음......................
		memset(pbySendCompressTemp, 0x00, sizeof(pbySendCompressTemp));	//압축 버퍼
		ulBodySize = htonl(nSendBodySize);
		memcpy(pbySendCompressTemp, &ulBodySize, 4);
		nRetLen = CompressLZO(lpSendBodyBuffer, pbySendCompressTemp + 4, nSendBodySize) + 4;
		if (nRetLen > 0)
		{
			// 압축 크기가 작은 경우만 압축해서 보내다.
			if (nSendBodySize > nRetLen)
			{
				pCommHeader->cCpFlag |= FLAG_COMPRESS;
				lpSendBodyBuffer	= pbySendCompressTemp;
				nSendBodySize		= nRetLen;
			}
			// 압축 후 사이즈가 더 큰 경우 압축 하지 말고 보낸다.
			else
			{
				pCommHeader->cCpFlag &= ~FLAG_COMPRESS;
				pCommHeader->cCpFlag |= FLAG_COMPRESS_FAILED;
			}
		}
		// 압축이 안된 경우
		else
		{
			pCommHeader->cCpFlag &= ~FLAG_COMPRESS;
			pCommHeader->cCpFlag |= FLAG_COMPRESS_FAILED;
		}
		// 압축은 무조건 암호화 안한다.
		pCommHeader->cCpFlag &= ~FLAG_ENCRYPT;
		bInsertChain = TRUE;
	}
	
	////////////////////// 암호화 체크(로그인은 무조건 암호화 한다) /////////////////////
	if (pCommHeader->cCpFlag & FLAG_ENCRYPT || pCommHeader->cCommandId == PID_CONNECT ||
		pCommHeader->cCommandId == PID_PLOT_CONNECT)	//KJI 20120206 (모의투자 접속처리)
	{
		pbySendEncrypTemp = new BYTE[nSendBodySize + 1024];
		memset(pbySendEncrypTemp, 0x00, sizeof(pbySendEncrypTemp));
		// 헤더는 암호화 하지 않는다.
		nRetLen = Encrypt(lpSendBodyBuffer, nSendBodySize, pbySendEncrypTemp);
		
		if (nRetLen > 0)
		{
			if (pbySendEncrypTemp[0] != 0)
			{
				lpSendBodyBuffer	= pbySendEncrypTemp;
				nSendBodySize		= nRetLen;
			}
			else
			{
				pCommHeader->cCpFlag &= ~FLAG_ENCRYPT;
			}
		}
		// 암호화 실패 시 어찌 할지.....................................................
		else
		{
			return FALSE;
			pCommHeader->cCpFlag &= ~FLAG_ENCRYPT;
		}
	}

	//////////////////// 실제 전송될 데이타 //////////////////
	CLIENT_CHAIN_PKT Chain;
	int nHeaderSize;
	int nPacketCnt;		// 보내는 Data의 회수 - 1
	int nRemainData;	// 마지막 패킷의 데이터 크기
	
	// 공통 헤더
	memcpy(m_pSendPacket, pCommHeader, COMMON_HEADER_SIZE);
	pCommHeader = (COMMONHEADER*)m_pSendPacket;

	// 분할 전송(2048 단위로 전송)
	if (bInsertChain)
	{
		nPacketCnt	= nSendBodySize / MAX_SEND_SIZE;	// 보내는 Data의 회수 - 1
		nRemainData	= nSendBodySize % MAX_SEND_SIZE;	// 마지막 패킷의 데이터 크기
		
		if (nRemainData > 0)
			nPacketCnt++;
		nHeaderSize = COMMON_HEADER_SIZE + sizeof(CLIENT_CHAIN_PKT);
		// chain 값 셋팅
		SYSTEMTIME tm;
		GetLocalTime(&tm);

		memset(&Chain, 0x00, sizeof(CLIENT_CHAIN_PKT));
		// Chain TR 헤더(TR 헤더 크기 - 3)
		memcpy(Chain.TrHeader, lpPacket + COMMON_HEADER_SIZE, CHAIN_TR_HEADER_SIZE);
		
		strTemp.Format("%d", nSendLen - COMMON_HEADER_SIZE);
		memcpy(Chain.cOrgSize, strTemp, strTemp.GetLength());		// 압축 전 크기
	
		strTemp.Format("%d", nSendBodySize);
		memcpy(Chain.cCompressSize,	strTemp, strTemp.GetLength());	// 압축 후 크기

		strTemp.Format("%d", MAX_SEND_SIZE);
		memcpy(Chain.cBlockSize, strTemp, strTemp.GetLength());		// send 단위(2048)
		sprintf_s(Chain.cUniqID,		"%02d%02d%02d%03d%05d", tm.wHour,tm.wMinute,tm.wSecond,tm.wMilliseconds,rand());
	}
	// 한방 전송
	else
	{
		nPacketCnt = 1;
		nRemainData = nSendBodySize;
		nHeaderSize = COMMON_HEADER_SIZE;
	}

	int nSendSize;
	int nPacketIndex;
	int nOffset = 0;
	// 마지막 패킷을 제외 하고 전송(chain이 있는 경우다)
	for (nPacketIndex = 0; nPacketIndex < nPacketCnt - 1; nPacketIndex++) 
	{
//		pCommHeader->cCpFlag = 0x00;	//LJP 20110401 6698에서 압축시 압축플래그 안 맞아서 수정함.
		// 처음 패킷
		if (nPacketIndex == 0)
			pCommHeader->cCpFlag |= FLAG_PACKET_BEGIN;
		// 중간 패킷
		else
		{
			// 2011.05.16 jhj 
			pCommHeader->cCpFlag &= ~FLAG_PACKET_BEGIN;
			pCommHeader->cCpFlag |= FLAG_PACKET_CONTINUE;
		}
		
		// chain 값 채우기
		strTemp.Format("%d", nPacketIndex);
		memcpy(Chain.cFrameNo,		strTemp, strTemp.GetLength());

		strTemp.Format("%d", MAX_SEND_SIZE);
		memcpy(Chain.cFrameSize,	strTemp, strTemp.GetLength());

		// chain
		memcpy(m_pSendPacket + COMMON_HEADER_SIZE, &Chain, sizeof(CLIENT_CHAIN_PKT));

		// body copy			
		memcpy(m_pSendPacket + nHeaderSize, lpSendBodyBuffer + nOffset, MAX_SEND_SIZE);
		nSendSize = nHeaderSize + MAX_SEND_SIZE;				
		
		pCommHeader->ulPacketLen = htonl(nSendSize - SIZE_DEF_PACKET);
		nRet = SendDataToServer(m_pSendPacket, nSendSize, cMsgId);
		if (nRet == FALSE)
		{
			// 에러 처리할것
		//	return FALSE;
		}
		
		nOffset += MAX_SEND_SIZE;
	}

	// 마지막 패킷 전송
	// 서버에서 한 패킷인 경우 압축여부를 비트로 검사안하는 경우가 있어서 FLAG_PACKET_END를 보내면 안된다.
	// 프로토콜에 대한 정의를왜 만들어 쓰는지 모르겠름 젠장 단말이 봉이야
	if (nPacketCnt > 1)
	{
		// 2011.05.16 jhj 
		pCommHeader->cCpFlag &= ~FLAG_PACKET_BEGIN;
		pCommHeader->cCpFlag &= ~FLAG_PACKET_CONTINUE;

		pCommHeader->cCpFlag |= FLAG_PACKET_END;
	}
	
	// 분할 전송이 아닌 경우는 nRemainData가 0일 수 있다.(No body로 헤더만 보내는 경우 있음)
	if ((bInsertChain && nRemainData > 0) || bInsertChain == FALSE)
	{
		// 분할 전송 시 chain 값 채우기
		if (bInsertChain)
		{
			// 2011.05.16 jhj 초기화 추가 . 패킷블럭사이즈가 1000 보다 작은경우 클리어 안해줘서. 596 인 경우 5968 로 전송되는 오류수정함.!!!
			strTemp.Format("%d", nPacketIndex);
			memset(Chain.cFrameNo, 0x00, sizeof(Chain.cFrameNo));
			memcpy(Chain.cFrameNo,		strTemp, strTemp.GetLength());

			strTemp.Format("%d", nRemainData);
			memset(Chain.cFrameSize, 0x00, sizeof(Chain.cFrameSize));
			memcpy(Chain.cFrameSize,	strTemp, strTemp.GetLength());

			// chain
			memcpy(m_pSendPacket + COMMON_HEADER_SIZE, &Chain, sizeof(CLIENT_CHAIN_PKT));
		}

		memcpy(m_pSendPacket + nHeaderSize, lpSendBodyBuffer + nOffset, nRemainData);
		nSendSize = nHeaderSize + nRemainData;
		pCommHeader->ulPacketLen = htonl(nSendSize - SIZE_DEF_PACKET);

		nRet = SendDataToServer(m_pSendPacket, nSendSize, cMsgId);

		if (nRet == FALSE)
		{
			// 에러 처리할것
		//	return FALSE;
		}
	}

	
	if (pbySendCompressTemp != NULL)
		delete pbySendCompressTemp;
	
	if (pbySendEncrypTemp != NULL)
		delete pbySendEncrypTemp;
		
    return TRUE;
}

//******************************************************************
//  Function Name : SendDataToServer 
//  Function      : 
//  Param         : char* lpData, int nSendLen, int nSendDbg
//  Return        : long 
//  Create        : 이용준 , 2007/05/22
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
long CCommMain::SendDataToServer (BYTE* lpData, int nSendLen, BYTE cMsgId, int nSendDbg)
{
	if (m_bConnect == FALSE || m_pTcpSocket == NULL)
		return FALSE;

	if (nSendDbg)
	{
		// 암호화 전 데이타를 Dbg로 보낸다.
		if (m_hCommsDbgWnd != NULL && ::IsWindow(m_hCommsDbgWnd))
		{
			WORD wKind = 0x00;
			
			if (cMsgId == DM_RQ_ID)
				wKind = LOG_RQ;
			else if (cMsgId == DM_SB_ID)
				wKind = LOG_SB;
			else if (cMsgId == DM_SBC_ID)
				wKind = LOG_SBC;
			else if (cMsgId == DM_INFO_ID)
				wKind = LOG_INFO;
			
			if (wKind > 0)
				SendToDebugWindow((HWND)m_hCommsDbgWnd, nSendLen, lpData, wKind);
		}
	}
	
	int nRet = m_pTcpSocket->Send(lpData, nSendLen);

	if (nRet != nSendLen)
		nRet = REQUEST_ERROR_SOCKET;
	else
		nRet = REQUEST_SUCCESS;

	m_nPollTime = 0;			// 폴링 체크용

	return nRet;
}

//******************************************************************
//  Function Name : DataReceive
//  Function      : 데이타 수신 처리
//  Param         : BYTE* lpData, BOOL bFirst
//  Return        : void 
//  Create        : 이용준 , 2007/09/18
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CCommMain::DataReceive(BYTE* lpData, BOOL bFirst)
{
	m_nPollTime = 0;			// 폴링 체크용

	int i;
	int nPacketLen;
	DWORD dwDataLen;

	COMMONHEADER* pCommonHeader = (COMMONHEADER*)lpData;
	nPacketLen	= ntohl(pCommonHeader->ulPacketLen);
	dwDataLen	= nPacketLen + SIZE_DEF_PACKET;
	
	if(nPacketLen > MAX_COMM_SIZE || nPacketLen < SIZE_DEF_PACKET)
		return;

	// (BP 쪽은 처리하지 않도록 한다.)
	if (m_pCommsConfig->m_bBccUse == TRUE)
	{
		// BCC체크는 서버에서 
		BYTE	ucBcc = 0;
		for (i = 0; i < (int)(dwDataLen - SZ_BCC_CHECKSUM); i++)
			ucBcc ^= lpData[i];

		if (ucBcc < 0x20)	// space를 더한해서 문자로 만든다.
			ucBcc += 0x20;

		if (ucBcc != (BYTE)lpData[dwDataLen - SZ_BCC_CHECKSUM])
		{	// 맨뒤의 FF, CR, LF제외
#ifdef _DEBUG
			CString strmsg;
			strmsg.Format("BCC CHECK 오류[!0x%02X]", ucBcc);
			AfxMessageBox(strmsg);
#endif
			return;
		}
		// bcc 만큼의 길이를 뺀다. 
		dwDataLen -= SZ_BCC_CHECKSUM;
		pCommonHeader->ulPacketLen = htonl(nPacketLen - SZ_BCC_CHECKSUM);
	}

	switch (pCommonHeader->cCommandId)
	{
		// RP
		case PID_TRDATA:
			RcvRp((UCHAR*)lpData, dwDataLen);
			return;
	//	case AS_MESSAGE_DATA:
	//		MsgSendToCommApiWindow((UCHAR*)lpData, dwDataLen);
	//		return;
	//	case AS_RELEASE_FUNC:
	//		ReleaseSendToCommApiWindow((UCHAR*)lpData, dwDataLen);
	//		return;
	//	case AS_SISE_DATA:		//시세
	//		RcvPb((UCHAR*)lpData, dwDataLen);
	//		return;
	//	case AS_PUSH_DATA:		//주문체결
	//		RcvPb((UCHAR*)lpData, dwDataLen);
	//		return;
		////////////////////// Xecure 암호처리 Command /////////////////////
		case PID_ENCCLIENTSET:
		case PID_ENCCLIENTSET_OLD:
		case PID_ENCCLIENTID:
		case PID_ENCCLIENTPWD:
		case PID_ENCXMINIT_SET:
			XecureReceive((UCHAR*)lpData, dwDataLen);
			return;
		// 서버에서 버전 정보를 클라언트에 보낸다.
		case PID_REVERSION:
		{
			COPYDATASTRUCT    send_data;
			send_data.dwData	= DATAKIND_SERVER_PUSH;	// 데이터 구분자 
			send_data.cbData	= dwDataLen;			// 데이터 길이 
			send_data.lpData	= lpData;
			// 로그인 ComApi로 보낸다.
			if (m_hLoginCommApiWnd != NULL)
			{
				::SendMessage(m_hLoginCommApiWnd,
							  WM_COPYDATA,
							  (int)DATAKIND_SERVER_PUSH,
							  (LPARAM)&send_data);
			}
			return;
		}
		// 로그인
		case PID_FILEDOWN:
		case PID_CONNECT:
		case PID_PLOT_CONNECT:	//KJI 20120206 (모의투자 접속처리)
		{
			RcvRp((UCHAR*)lpData, dwDataLen);
			return;
		}
		case PID_SVRPOLL:
		case PID_BP_POLLING:
		{
			CPacketMngr PacketMngr;
			PacketMngr.SendCopyData(GetSafeHwnd(), pCommonHeader->cCommandId, NULL, 0);
			return;
		}
	//	case AS_SYSTEM_ERROR:
//		{
//			RcvSystemError((UCHAR*)lpData, dwDataLen);
//			return;
//		}
		/*
		default:
		{
			CString strmsg;
			strmsg.Format("[warning] 정의되지 않은 메시지 수신 [Command Id = %d]", pCommonHeader->cCommandId);
			AfxMessageBox(strmsg);
			return;
		}
		*/
	}

	// 위에서 PID로 다 처리 하고 나머지 모든 PID는 실시간 데이타로 보자.
	// 윈도우 핸들이 없으면 자동갱신으로 보자
	// RcvPb()에서 정의되지 않은 PID를 버린다.
	if (pCommonHeader->ulWinHwnd == NULL)
		RcvPb((UCHAR*)lpData, dwDataLen);
	// 이것은 일단 이상한 패킷으로 본다.
	else
		g_unAbnormalPacketCount++;
}



//******************************************************************
//  Function Name : RcvRp
//  Function      : 데이타 수신 처리를한다.
//  Param         : BYTE* lpData, DWORD dwDataLen
//  Return        : void 
//  Create        : 이용준 , 2008/02/25
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CCommMain::RcvRp(BYTE* lpData, DWORD dwDataLen)
{
	COMMONHEADER* pCommHeader = (COMMONHEADER*)lpData;

#ifdef _DEBUG
	if (dwDataLen != ntohl(pCommHeader->ulPacketLen) + SIZE_DEF_PACKET)
	{
		AfxMessageBox("받은 데이타 길이가 이상함");
		return;
	}
#endif

	CString sWINIDSEQNO;
	ULONG ulRqId;
	// pCommHeader->ulRqId 대신 nWindowId를 사용한다.
	// nPUniqueKey는 서버에서 다른 용도로 사용 하고 있어서
	ulRqId = pCommHeader->ulWinHwnd;
	sWINIDSEQNO.Format("%04d", ulRqId);

	if ( ulRqId == 0 )
	{
		//	예외처리 ( 리얼인데 TR처럼 오는 경우 )
		//----BP 서버에서 보낸 실시간 데이터는 예외적으로 아래처럼 처리 해야 한다
		// BP 서버에서 보낸 실시간 데이터는 앞부분에 서비스명이 있다.
		CString strRealType = "";
		CString strTrCode = CString((char*)lpData + COMMON_HEADER_SIZE, TRCODE_SIZE);
		int nOffSize = 0;

		// 체결통보 (996Q-현물/ 997Q-선물)
		if (strTrCode == "CN996Q00" || strTrCode == "CN997Q00")
		{

			//	굳이 이글에서 체결통보 오는데 타입을 따로 할 필요가 있을까? 그냥 HTS와 동일한 타입으로 보내면 될것 같은데...
//			strRealType.Format("%04d", PID_BP_CHEKYOUL);
			strRealType.Format("%04d", PID_CHEKYOUL);
//			DWORD nSendDataLen = (dwDataLen - HEADER_SIZE) + REAL_TYPE_SIZE;	// ComApi로 보낼 데이타의 길이 = 리얼 타입(4) + 실제 데이타

			BYTE* pPBData = new BYTE[1024];
//			memset( pPBData, 0x00, sizeof(pPBData));
			int nLen = ConclusionRealProcessForBP(strTrCode, lpData, dwDataLen, pPBData);
			
			// 2011.03.11 jhj
			if(nLen == 0)
				return;

			//BYTE* pPBData = new BYTE[nSendDataLen + 1];
			//memset( pPBData, 0x00, sizeof(pPBData));
			memcpy(pPBData, strRealType, strRealType.GetLength());
			nLen += REAL_TYPE_SIZE;
//			memcpy(pPBData + REAL_TYPE_SIZE, (BYTE*)(lpData + nOffSize), (dwDataLen - HEADER_SIZE));

			SendRealDataToCommApiWindow(pPBData, nLen);
			delete []pPBData;
		}
		else if (strTrCode == "CN994Q00")
		{
			strRealType.Format("%04d", PID_SYSALARM);
			//			DWORD nSendDataLen = (dwDataLen - HEADER_SIZE) + REAL_TYPE_SIZE;	// ComApi로 보낼 데이타의 길이 = 리얼 타입(4) + 실제 데이타

			BYTE* pPBData = new BYTE[1024];
			//			memset( pPBData, 0x00, sizeof(pPBData));
			int nLen = ConclusionRealProcessForBP(strTrCode, lpData, dwDataLen, pPBData);

			// 2011.03.11 jhj
			if(nLen == 0)
				return;

			//BYTE* pPBData = new BYTE[nSendDataLen + 1];
			//memset( pPBData, 0x00, sizeof(pPBData));
			memcpy(pPBData, strRealType, strRealType.GetLength());
			nLen += REAL_TYPE_SIZE;
			//			memcpy(pPBData + REAL_TYPE_SIZE, (BYTE*)(lpData + nOffSize), (dwDataLen - HEADER_SIZE));

			SendRealDataToCommApiWindow(pPBData, nLen);
			delete []pPBData;

			/*
			BYTE* pPBData = new BYTE[1024];
			memset(pPBData, 0x00, sizeof(pPBData));

			//memcpy(pPBData, lpData , 166 );
			memcpy(pPBData+157 , pPBData + 164, 1);
			memcpy(pPBData+158 , pPBData + 165, 1);
			memcpy(pPBData+159 , pPBData + 166, 1);

			memcpy(pPBData, strRealType, strRealType.GetLength());
	
			SendRealDataToCommApiWindow(pPBData, strRealType.GetLength()+REAL_TYPE_SIZE);
			delete [] pPBData;
			*/
		}

	}
	else
	{
		m_RequestDataObList.AddData(sWINIDSEQNO, lpData, dwDataLen);

		// 패킷의 시작, 중간이 아니면 마지막 패킷으로 간주 한다.
		// 압축하다말고 시작이 없이 날라온 packet 은 한개짜리 packet 으로 취급
		if (((pCommHeader->cCpFlag & FLAG_PACKET_BEGIN) == 0) &&
			((pCommHeader->cCpFlag & FLAG_PACKET_CONTINUE) == 0))// ||
//			pCommHeader->cCpFlag & FLAG_COMPRESS_FAILED)
		{
			ReleaseSendToCommApiWindow(ulRqId);
		}
	}
}

//******************************************************************
//  Function Name : ReleaseSendToCommApiWindow
//  Function      : 트랜 종료 처리를 한다.
//  Param         : PVOID lpData, DWORD dwDataLen
//  Return        : BOOL 
//  Create        : 이용준 , 2008/02/25
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CCommMain::ReleaseSendToCommApiWindow(ULONG ulRqId)
{
	COMMONHEADER* pCommHeader;
	CString sWINIDSEQNO;
	sWINIDSEQNO.Format("%04d", ulRqId);

	CRequestData* pRequestData = m_RequestDataObList.GetData(sWINIDSEQNO);
	if (pRequestData == NULL)
	{
		return FALSE;
	}

	// CommAPi의 핸들을 얻는다.
	HWND dwTempWnd = m_RequestDataObList.GetHwnd(sWINIDSEQNO);
	if (pRequestData->m_nSize <= 0 || pRequestData->m_lpData == NULL || dwTempWnd == NULL)
	{
		// IO테이블 삭제한다.
		m_RequestDataObList.RemoveData(sWINIDSEQNO);
		return FALSE;
	}

	//////////////////// 압축 해제, 복호화 처리 한다. ////////////////////
	int nTempSize;
	int nBodySize;
	int nSendDataSize;

	BYTE* pbyDecompressTemp = NULL;
	BYTE* pbyDecryptTemp	= NULL;
	BYTE* pbySendData		= NULL;
	
	BYTE* pbyReceiveData	= pRequestData->m_lpData;
	BYTE* pbyReceiveBody	= pRequestData->m_lpData + COMMON_HEADER_SIZE;
	nBodySize				= pRequestData->m_nSize - COMMON_HEADER_SIZE;

	pCommHeader				= (COMMONHEADER*)pRequestData->m_lpData;
	
	BOOL bDataCheck = FALSE;
	
	CString strTmp;	//LJP 20120517
	// 압축해제
	if (pCommHeader->cCpFlag & FLAG_COMPRESS)
	{
		TRY 
		{
			int nRealBodySize;
			bDataCheck = TRUE;
			// 압축전 크기
			memcpy(&nRealBodySize, pbyReceiveBody, 4);
			nTempSize = ntohl(nRealBodySize);
			//LJP 20120517 Start-->
//			strTmp.Format("[LJP]nTempSize01 : %d", nTempSize);
//			OutputDebugString(strTmp);
			BOOL bBigBody = FALSE;
			if(nBodySize > nTempSize)
			{
				bBigBody = TRUE;
				strTmp.Format("[LJP]nBodySize : %d, nTempSize :%d", nBodySize, nTempSize);
				OutputDebugString(strTmp);
				SetWriteLog(strTmp);
			}
			if((nTempSize <= 0) || (nTempSize > (6803456 - 16))/* || (nBodySize > nTempSize)*/)
			{
				strTmp.Format("[LJP]nTempSize02 : %d", nTempSize);
				OutputDebugString(strTmp);
				SetWriteLog(strTmp);
				m_RequestDataObList.RemoveData(sWINIDSEQNO);
				return FALSE;
			}
			
			//<--End
			pbyDecompressTemp = new BYTE[nTempSize + COMMON_HEADER_SIZE + 4096];
			memset(pbyDecompressTemp, 0x00, sizeof(pbyDecompressTemp));

			// COMMONHEADER 와 Body 사이에 4바이트가 압축전 body길이를 나타낸다.
//			strTmp.Format("[LJP]nTempSize2 : %d, nBodySize2 : %d", nTempSize, nBodySize);
//			OutputDebugString(strTmp);
			nBodySize = DecompressLZO(pbyReceiveBody + 4, pbyDecompressTemp, nBodySize - 4);
			if(bBigBody)
			{
				strTmp.Format("[LJP]nBigBodySize : %d, nTempSize :%d", nBodySize, nTempSize);
				OutputDebugString(strTmp);
				SetWriteLog(strTmp);
			}

			//LJP 20120517 Start-->
//			strTmp.Format("[LJP]nTempSize : %d, nBodySize : %d", nTempSize, nBodySize);
//			OutputDebugString(strTmp);
			if(nTempSize != nBodySize)
			{
				strTmp.Format("[LJP]nTempSize : %d, nBodySize : %d", nTempSize, nBodySize);
				OutputDebugString(strTmp);
				SetWriteLog(strTmp);
				if (pbyDecompressTemp != NULL)
					delete[] pbyDecompressTemp;
				m_RequestDataObList.RemoveData(sWINIDSEQNO);
				return FALSE;
			}
			//<--End
			pbyReceiveBody = pbyDecompressTemp;
		}
		CATCH (CMemoryException, e)
		{
			char buff[1024];
			CString strLog;
			memset(buff, 0x00, sizeof(buff));
			e->GetErrorMessage(buff, 1024);
			strLog.Format("CMemoryException Error : %s", buff);
			SetWriteLog(strLog);
		}
		END_CATCH
		
	}

	// 복호화
	if (pCommHeader->cCpFlag & FLAG_ENCRYPT)
	{
		bDataCheck = TRUE;
		nTempSize	= nBodySize + 1024;
		pbyDecryptTemp = new BYTE[nTempSize];	
		nBodySize = Decrypt(pbyReceiveBody, nBodySize, pbyDecryptTemp);
		//LJP 20120517 Start-->
		if(nBodySize <= 0)
		{
			strTmp.Format("[LJP]FLAG_ENCRYPT nTempSize : %d, nBodySize : %d", nTempSize, nBodySize);
			OutputDebugString(strTmp);
			SetWriteLog(strTmp);
			if (pbyDecryptTemp != NULL)
				delete[] pbyDecryptTemp;
			m_RequestDataObList.RemoveData(sWINIDSEQNO);
			return FALSE;
		}
		//<--End
		pbyReceiveBody = pbyDecryptTemp;
	}
	
	// 압축 후 사이즈가 큰 경우(압축 실패)
	// CommonHeader 다음 4바이트가 붙어 있는데 없애야 한다.
	if (pCommHeader->cCpFlag & FLAG_COMPRESS_FAILED)
	{
		nBodySize -= 4;
		pbyReceiveData += 4;
	}

	// ComApi에 보낼 데이타
	nSendDataSize = nBodySize + COMMON_HEADER_SIZE;
	
	pbySendData = new BYTE[nSendDataSize];
	
	COMMONHEADER* pCommHeaderTemp = (COMMONHEADER*)pbySendData;

	// 압축 또는 암호화 된 데이타 인 경우
	if (bDataCheck)
	{
		// Common Header
		memcpy(pbySendData, pCommHeader, COMMON_HEADER_SIZE);
		// Body
		memcpy(pbySendData + COMMON_HEADER_SIZE, pbyReceiveBody, nBodySize);
	//	pCommHeaderTemp->ulPacketLen = htonl(nSendDataSize - SIZE_DEF_PACKET);
	}
	else
		memcpy(pbySendData, pbyReceiveData, nSendDataSize);

	pCommHeaderTemp->ulPacketLen = htonl(nSendDataSize - SIZE_DEF_PACKET);

	pCommHeaderTemp->ulWinHwnd	= pRequestData->m_ulWinHwnd;
	// ComApi에서 생성한 RqId를 넣어준다.(이걸로 ComApi가 map에서 찾는다)
	pCommHeaderTemp->ulRqId		= pRequestData->m_ulRqId;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// 받은 자료를 해당 window 에 전송한다.
	if (::IsWindow((HWND)dwTempWnd))
	{
		int nQueueSize;
		if (m_pTcpSocket != NULL)
			nQueueSize = m_pTcpSocket->GetQueueSize();

		COPYDATASTRUCT    send_data;
		send_data.dwData	= MAKELONG( LOG_RP, nQueueSize);				// RP용 
		send_data.cbData	= nSendDataSize;		// 보낼 사이즈
		send_data.lpData	= (LPBYTE)pbySendData;	// 보낼 버퍼

		int lRet = ::SendMessage((HWND)dwTempWnd, 
								WM_COPYDATA, 
								DATAKIND_RQRP,

								(LPARAM)&send_data);

	//	TRACE("===\n ReleaseSendToCommApiWindow() RQID:%d====\n", pCommHeaderTemp->ulRqId);

	}

	// RP 데이터 Debug에 보냄
	if (m_hCommsDbgWnd && ::IsWindow(m_hCommsDbgWnd))
		SendToDebugWindow(m_hCommsDbgWnd, nSendDataSize, pbySendData, LOG_RP);
	
	if (pbyDecompressTemp != NULL)
		delete[] pbyDecompressTemp;
	if (pbyDecryptTemp != NULL)
		delete[] pbyDecryptTemp;
	if (pbySendData != NULL)
		delete[] pbySendData;

	// IO테이블 삭제한다.
	m_RequestDataObList.RemoveData(sWINIDSEQNO);
	
	return TRUE;
}

//******************************************************************
//  Function Name : RcvPb
//  Function      : 리얼수신 처리를 한다
//  Param         : PVOID lpData, DWORD dwDataLen
//  Return        : void 
//  Create        : 이용준 , 2008/02/25
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 데이타 영역: Common Header + body(record count포함) size[4] + record count[4] + Rec * n
//******************************************************************
void CCommMain::RcvPb(BYTE* lpData, DWORD dwDataLen)
{	
	int nAdditionalSize = 8;	// body size[4] + record count[4]
	BYTE* lpRecvBody;
	int	nRecvDataSize;

	COMMONHEADER* pCommHeader = (COMMONHEADER*)lpData;
	
	int nPacketLen	= ntohl(pCommHeader->ulPacketLen);

	if (nPacketLen <= 0)
		return;

	lpRecvBody		= lpData + COMMON_HEADER_SIZE;
	nRecvDataSize	= dwDataLen - COMMON_HEADER_SIZE;

	if (nRecvDataSize <= 0)
		return;
	
	BYTE* pbyDecompressTemp = NULL;
	// 압축 해제(실시간 데이타는 압축 안한다고 함)
	/*	
	if (pCommHeader->cCpFlag & FLAG_COMPRESS)
	{
		int nTempSize	= dwDataLen + 1024;
		pbyDecompressTemp = new BYTE[nTempSize];
	
		nRecvDataSize	= DecompressLZO(lpRecvBody + 4, pbyDecompressTemp, nRecvDataSize - 4);
		lpRecvBody		= pbyDecompressTemp;
	}
	*/

	/////////////////////////////////////////////////////////////////
	int nSendDataLen;
	int nBodyLen;
	int nRecCount;
	int nRecSize;
	int nOffset = 0;
	CString strRealType;
	CString strTemp;
	BOOL bAbnormalFlag = FALSE;

	memcpy(&nBodyLen,	lpRecvBody, 4);			// body길이(레코드 수를 포함 한다)
	memcpy(&nRecCount,	lpRecvBody + 4, 4);		// 실시간 레코드 갯수
	nBodyLen	= ntohl(nBodyLen) - 4;			// 레코드 갯수 부분(4)을 뺀다.
	nRecCount	= ntohl(nRecCount);

	if (nBodyLen <= 0)
		return;
	// 레코드 갯수가 비정상이면 패킷을 버린다.
	if (nRecCount <= 0)
		return;

	nRecSize	= nBodyLen / nRecCount;			// 레코드의 길이
	nSendDataLen = REAL_TYPE_SIZE + nRecSize;	// ComApi로 보낼 데이타의 길이 = 리얼 타입(4) + 실제 데이타
	
	if (nRecSize <= 0)
		return;

	// 리얼 데이타 구조
	// Common Header + body size[4] + record count[4] + Rec * n
	BYTE* pPBData = new BYTE[nSendDataLen + 1];
	strRealType.Format("%04d", pCommHeader->cCommandId);	// 실시간 타입
	memcpy(pPBData, strRealType, strRealType.GetLength());
	
	nOffset = nAdditionalSize;
	
	while (1)
	{
		// 데이타 길이가 이상한 경우다
		// 레코드의 길이 보다 실제로 받은 데이타가 작거나,
		// 레코드의 길이 보다 실제로 받은 데이타가 길어서 남는 부분은 버린다.
		if (nRecvDataSize - nOffset < nRecSize)
		{
			strTemp.Format("실시간 데이타 길이 비정상 : 타입:%s, 정상길이:%d, 남은길이:%d]",
													strRealType, nRecSize, nRecvDataSize - nOffset);
			CommsDbgLog((LPSTR)(LPCTSTR)strTemp);
			break;
		}

		// 앞의 4바이트는 리얼 타입
		memcpy(pPBData + REAL_TYPE_SIZE, lpRecvBody + nOffset, nRecSize);

		if (!SendRealDataToCommApiWindow(pPBData, nSendDataLen))
			bAbnormalFlag = TRUE;

		nOffset += nRecSize;

		// CommonHeader를 제외한 길이
		if (nOffset >= nRecvDataSize)
			break;
	}

	// 정의되지 않은 패킷의 수를 센다.
	if (bAbnormalFlag)
	{
		g_unAbnormalPacketCount++;
		strTemp.Format("정의되지 않은 패킷 수 : %d[실시간 타입(PID):%s]", g_unAbnormalPacketCount, strRealType);
		CommsDbgLog((LPSTR)(LPCTSTR)strTemp);
#ifdef _DEBUG
		SetWriteLog(strTemp);
//		AfxMessageBox(strTemp);	
#endif
	}

	delete pPBData;

	if (pbyDecompressTemp != NULL)
		delete[] pbyDecompressTemp;
}
//******************************************************************
//  Function Name : MsgSendToCommApiWindow
//  Function      : 트랜 메세지 처리를 한다.
//  Param         : PVOID lpData, DWORD dwDataLen
//  Return        : BOOL 
//  Create        : 이용준 , 2008/02/25
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CCommMain::MsgSendToCommApiWindow(PVOID lpData, DWORD dwDataLen)
{
	int lRet = 0;
	
	COMMONHEADER* pCommHeader = (COMMONHEADER*)lpData;

	CString sWINIDSEQNO;
	ULONG ulRqId;
	// pCommHeader->ulRqId 대신 nWindowId를 사용한다.
	// nPUniqueKey는 서버에서 다른 용도로 사용 하고 있어서
	ulRqId = pCommHeader->ulWinHwnd;
	sWINIDSEQNO.Format("%04d", ulRqId);
	
	CRequestData* pRequestData = m_RequestDataObList.GetData(sWINIDSEQNO);
	if (pRequestData)
	{
		// CommAPi의 핸들을 얻는다.
		HWND dwTempWnd = m_RequestDataObList.GetHwnd(sWINIDSEQNO);
		if (dwTempWnd)
		{	
			// 받은 자료를 해당 window 에 전송한다.
			if (::IsWindow((HWND)dwTempWnd))
			{
				int nQueueSize;
				if (m_pTcpSocket != NULL)
					nQueueSize = m_pTcpSocket->GetQueueSize();

				COPYDATASTRUCT    send_data;
				send_data.dwData	= MAKELONG( DATAKIND_RQRP, nQueueSize);		// RP용 
				send_data.cbData	= dwDataLen;			// 보낼 사이즈
				send_data.lpData	= lpData;				// 보낼 버퍼

				lRet = ::SendMessage((HWND)dwTempWnd,
									WM_COPYDATA,
									DATAKIND_MSG,
									(LPARAM)&send_data);
			}
		}
	}

	return TRUE;
}
// 실시간 데이타를 ComApi에 전송한다.
BOOL CCommMain::SendRealDataToCommApiWindow(BYTE* pPBData, int nDataLen)
{
	// PB 데이터 Debug에 보냄
	if (m_hCommsDbgWnd && ::IsWindow(m_hCommsDbgWnd))
		SendToDebugWindow(m_hCommsDbgWnd, nDataLen, pPBData, LOG_PB);
	
	// ComApi에 보내기........
	HWND hCommAPIWnd = NULL;
	long lRet;
	BOOL bFlag = TRUE;

	for (int nCnt = m_pArrCommApiWnd->GetSize() - 1; nCnt >= 0; nCnt--)
	{
		hCommAPIWnd = (HWND)(*m_pArrCommApiWnd)[nCnt];
		if (::IsWindow(hCommAPIWnd))
		{
			int nQueueSize;
			if (m_pTcpSocket != NULL)
				nQueueSize = m_pTcpSocket->GetQueueSize();

			COPYDATASTRUCT    send_data;
			send_data.dwData	= MAKELONG( LOG_PB, nQueueSize);			// 데이터 구분자 
			send_data.cbData	= (DWORD)nDataLen;	// 데이터 길이 
			send_data.lpData	= pPBData;
					
			lRet = ::SendMessage( hCommAPIWnd, 
								  WM_COPYDATA, 
								  (int)DATAKIND_PB,
								  (LPARAM)&send_data);
			
			// lRet 가 -1 이면는 등록되지 않은 리얼 타입인 경우다.
			if (lRet == -1)
				bFlag = FALSE;
		}
		else
		{
			m_pArrCommApiWnd->RemoveAt(nCnt);
			PostMessage(UM_WND_STATE_CHECK);
		}
	}

	return bFlag;
}

//******************************************************************
//  Function Name : RcvSystemError
//  Function      : 서버 시스템 에러 수신 처리
//  Param         : PVOID lpData, DWORD dwDataLen
//  Return        : BOOL 
//  Create        : 이용준 , 2008/02/25
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CCommMain::RcvSystemError(BYTE* lpData, DWORD dwDataLen)
{
	COMMONHEADER* pCommHeader = (COMMONHEADER*)lpData;

	CString sWINIDSEQNO;
	ULONG ulPUniqueKey;
	// pCommHeader->ulRqId 대신 nWindowId를 사용한다.
	// nPUniqueKey는 서버에서 다른 용도로 사용 하고 있어서
	ulPUniqueKey = pCommHeader->ulWinHwnd;
	sWINIDSEQNO.Format("%04d", ulPUniqueKey);

	CRequestData* pRequestData = m_RequestDataObList.GetData(sWINIDSEQNO);
	if (pRequestData)
	{
		// CommAPi의 핸들을 얻는다.
		HWND dwTempWnd = m_RequestDataObList.GetHwnd(sWINIDSEQNO);
		if( dwTempWnd )
		{
			// 받은 자료를 해당 window 에 전송한다.
			if (::IsWindow((HWND)dwTempWnd))
			{
				COPYDATASTRUCT    send_data;
				send_data.dwData	= DATAKIND_SS_ERROR;		// RP용 
				send_data.cbData	= dwDataLen;			// 보낼 사이즈
				send_data.lpData	= lpData;			// 보낼 버퍼

				int lRet = ::SendMessage( (HWND)dwTempWnd, 
											WM_COPYDATA, 
											DATAKIND_SS_ERROR,
											(LPARAM)&send_data );
			}
		}

		// IO테이블 삭제한다.
		m_RequestDataObList.RemoveData(sWINIDSEQNO);
	}
	return TRUE;
}

// Xecure 에러 시 메세지를 로그인 윈도우에 send 한다.(아직 미정, 임시로 그냥 함수만 만들어 놓았다)
void CCommMain::SendXecureErrorMessage(int nRet, int nMessageType)
{
	HWND hWnd = NULL;

	if (hWnd == NULL)
		return;

	switch (nRet)
	{
		case ERR_CERT_EXPIRED:		// -1011
		case ERR_CA_CERT_EXPIRED:	// -1012
			::SendMessage(hWnd, WMU_NOCONNECT_ACK, 1, nRet);
			break;
		default:
			::SendMessage(hWnd, WMU_NOCONNECT_ACK, nMessageType, nRet);
			break;
	}
}
// 로그인 윈도우에 메세지 전송(어찌 해야 할지 몰라서 일단 만들어 놓은 것 임)
void CCommMain::SendMessageToLoginWindow(int nMessage, int nMessageType, int nMessageValue)
{
	HWND hWnd = NULL;
	if (hWnd == NULL)
		return;

	::SendMessage(hWnd, nMessage, nMessageType, nMessageValue);
}
// 
//******************************************************************
//  Function Name : XecureInit
//  Function      : 소프트포럼의 암호화 핸드세이킹
//  Param         : int nMode
//  Return        : long 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
long CCommMain::XecureInit(int nMode)
{
	// Create New Xecure CTX
	int nCTXState;
	int nRet = 0;
	BYTE cSendBuf[MAX_PACKET_SIZE];
	int nSendSize;

	nCTXState = 2;
	
	m_pCtx = SF_New_Xecure_Ctx();
	nRet = SFSP_Client_Hello(m_pCtx, (char*)cSendBuf, MAX_PACKET_SIZE, &nSendSize);

	if (nRet < 0)
	{		
		SendXecureErrorMessage(nRet, nCTXState);
		return 0;
	}

	// WM_COPYDATA로 SendMessage 한다.
	CPacketMngr PacketMngr;
	PacketMngr.SendCopyData(GetSafeHwnd(), m_ucBccType, cSendBuf, nSendSize);
	return 1;
}

//******************************************************************
//  Function Name : XecureReceive
//  Function      : 
//  Param         : BYTE* lpData, DWORD dwDataLen
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CCommMain::XecureReceive(BYTE* lpData, DWORD dwDataLen)
{
	COMMONHEADER* pCommHeader = (COMMONHEADER*)lpData;
	int nRet = 0;
	// xecure 인증 시 필요한 암호화된 data를 담을 버퍼
	BYTE cSendBuf[MAX_PACKET_SIZE];
	int nSendLen;
	int nCTXState = 0;

	if (pCommHeader->cCommandId == m_ucBccType)
	{
		// 공통헤더 이후 데이타 영역에 대해...
		if ((nRet = SFSP_Client_Hello_Re(m_pCtx, (char*)&lpData[COMMON_HEADER_SIZE], dwDataLen - COMMON_HEADER_SIZE)) < 0)
		{
			SendXecureErrorMessage(nRet, 7);
			return;
		}

		// SFSP_Client_ID 프로토콜로 메시지 생성
		nCTXState = 3;
		nRet = SFSP_Client_ID(m_pCtx, (char*)cSendBuf, MAX_PACKET_SIZE, &nSendLen, "GUEST", strlen("GUEST"));
		if (nRet < 0)
		{
			SendXecureErrorMessage(nRet, nCTXState);
			return;
		}
		// WM_COPYDATA로 SendMessage 한다.
		CPacketMngr PacketMngr;
		PacketMngr.SendCopyData(GetSafeHwnd(), PID_ENCCLIENTID, cSendBuf, nSendLen);
	}
	else
	{		
		switch (pCommHeader->cCommandId)
		{
			case PID_ENCCLIENTID:
			{
				if ((nRet = SFSP_Client_ID_Re(m_pCtx, (char*)&lpData[COMMON_HEADER_SIZE], dwDataLen - COMMON_HEADER_SIZE)) < 0)
				{
					SendXecureErrorMessage(nRet, 8);
					return;
				}

				nCTXState = 4;
				nRet = SFSP_Client_PWD(m_pCtx, (char*)cSendBuf, MAX_PACKET_SIZE, &nSendLen, "GUEST", strlen("GUEST"), 5);
		
				if (nRet < 0)
				{
					SendXecureErrorMessage(nRet, nCTXState);
					return;
				}
				// WM_COPYDATA로 SendMessage 한다.
				CPacketMngr PacketMngr;
				PacketMngr.SendCopyData(GetSafeHwnd(), PID_ENCCLIENTPWD, cSendBuf, nSendLen);
				break;
			}
			case PID_ENCCLIENTPWD:
			{
				if ((nRet = SFSP_Client_PWD_Re(m_pCtx, (char*)&lpData[COMMON_HEADER_SIZE], dwDataLen - COMMON_HEADER_SIZE)) < 0) 
				{
					SendXecureErrorMessage(nRet, 9);
					return;
				}

				// 버전처리 정보 요청
				CPacketMngr PacketMngr;
				PacketMngr.SendCopyData(GetSafeHwnd(), PID_REVERSION, NULL, 0);
				break;
			}
			case PID_ENCXMINIT_SET:
			{
				// New 버전 일때 서버에서 PID_ENCXMINIT_SET를 응답으로 준다.
				if (m_nXMConnect == 0)	// 최초처리
				{
					nRet = XMC2_ClientLib_Init(&m_XMCtx, "test-cert.der");
					if (nRet < 0)
					{
						AfxMessageBox("XMC Lib Init 에러");
						return;
					}

					nRet = XMC2_Encode_KeyInit_Token(&m_XMCtx, cSendBuf, (unsigned short*)&nSendLen, MAX_PACKET_SIZE);
					if (nRet < 0)
					{
						AfxMessageBox("XMC Encode_KeyInit 에러");
						return;
					}

					// WM_COPYDATA로 SendMessage 한다.
					CPacketMngr PacketMngr;
					PacketMngr.SendCopyData(GetSafeHwnd(), PID_ENCXMINIT_SET, cSendBuf, nSendLen);
					m_nXMConnect = 1;
				}
				else	// 실제 응답을 본다.
				{
					nRet = XMC2_Decode_KeyFinal_Token(&m_XMCtx, (unsigned char*)&lpData[COMMON_HEADER_SIZE], (unsigned short)(dwDataLen - COMMON_HEADER_SIZE));

					if (nRet < 0)
					{
						AfxMessageBox("Decode_KeyFinal 에러");

						SendXecureErrorMessage(nRet, 10);

						return;
					}

					// 버전처리 정보 요청
					CPacketMngr PacketMngr;
					PacketMngr.SendCopyData(GetSafeHwnd(), PID_REVERSION, NULL, 0);
					m_nXMConnect = 2;
				}
				break;
			}
			default:
				break;
		}
	}
}

//******************************************************************
//  Function Name : Encrypt
//  Function      : 데이터 암호화
//  Param         : unsigned char *plainbuff, int plainlen, unsigned char *encdata
//					*plainbuff-암호할 데이타, plainlen 길이	
//				    *encdata-암호화된 데이타
//  Return        : int 
//  Create        : 이용준 , 2008/05/09
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int CCommMain::Encrypt(unsigned char* pInData, int nInDataLen, unsigned char* pEncBuf, int nCTXState)
{
	int nEncLen = 0;

	if (m_nXMConnect == 2)
	{
		int nRet = 0;
		nRet = XMC2_Encrypt_Message(&m_XMCtx, pEncBuf, (unsigned short*)&nEncLen, MAX_PACKET_SIZE, pInData, (unsigned short)nInDataLen);
		if (nRet < 0)
		{
			SendMessageToLoginWindow(WMU_NOCONNECT_ACK, 6, nRet);
			return 0;
		}
	}
	else
	{
		int	nRet;
		if ((nRet = SF_Block_Encrypt(m_pCtx, pEncBuf, MAX_PACKET_SIZE, &nEncLen, pInData, nInDataLen)) < 0)
		{
			if (nCTXState > 0)
				SendXecureErrorMessage(nRet, nCTXState);

			return 0;
		}
		
		if (nEncLen > MAX_PACKET_SIZE)
			return 0;
	}

	return nEncLen;
}

//******************************************************************
//  Function Name : Decrypt
//  Function      : 데이타를 복호화
//  Param         : unsigned char *encdbuff, int encdlen, unsigned char *decdata 
//					*encdbuff-암호화된 데이타, encdlen-encdbuff의길이
//                  *decdata-풀린 데이타,
//  Return        : int 
//  Create        : 이용준 , 2008/05/09
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int CCommMain::Decrypt(unsigned char* pEncBuf, int nEncLen, unsigned char* pDecBuf)
{
	int nRet = 0;
	int nDecLen = 0;

	if (m_nXMConnect == 2)
	{
		nRet =  XMC2_Decrypt_Message(&m_XMCtx, pDecBuf, (unsigned short*)&nDecLen, MAX_PACKET_SIZE, pEncBuf, (unsigned short)nEncLen);
	}
	else
	{
		if ((nRet = SF_Block_Decrypt(m_pCtx, pDecBuf, MAX_PACKET_SIZE, &nDecLen, pEncBuf, nEncLen)) < 0) 
		{
			SendXecureErrorMessage(nRet, 10);
		}
	}

	// 복호화 실패 또는 복화화 후 데이터가 최대 버퍼 크기보다 큰 경우
	if (nRet < 0 || nDecLen > MAX_PACKET_SIZE)
		return 0;

	return nDecLen;
}

//******************************************************************
//  Function Name : CommsDbgLog
//  Function      : 사용자 메세지 찍는 기능
//  Param         : LPSTR lpstr, WORD wDataType /*= 0x01 */
//  Return        : BOOL 
//  Create        : 이용준 , 2006/09/07
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CCommMain::CommsDbgLog(LPSTR lpstr, WORD wDataType /*= 0x01 */)
{
	if (!m_hCommsDbgWnd)
		return FALSE;

	int nLogSize = strlen(lpstr);
	
	SendToDebugWindow(m_hCommsDbgWnd, nLogSize, lpstr, wDataType);

	return TRUE;
}

//******************************************************************
//  Function Name : SendToDebugWindow
//  Function      : CommsDbg로 데이터를 넘겨주는 함수
//  Param         : HWND hCommsDbgWnd,  int   nSizeLen, PVOID lpBuf, WORD	wKind /*= 0x00 */
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CCommMain::SendToDebugWindow(HWND hCommsDbgWnd, 
								  int   nSizeLen, 
								  PVOID lpBuf, 
								  WORD	wKind /*= 0x00 */)
{
	if (!::IsWindow(hCommsDbgWnd))
		return FALSE;

	int nTotSendLen;
	int nQueueSize = 0;
	CString strTime;
	strTime = GetTimeString();
	nTotSendLen = nSizeLen + 8 + 4;
	
	BYTE* pbyData = new BYTE[nTotSendLen];
	if (m_pTcpSocket != NULL)
		nQueueSize = m_pTcpSocket->GetQueueSize();
	// 시간
	memcpy(pbyData, strTime, strTime.GetLength());
	// 큐에 있는 데이타 건수
	memcpy(pbyData + 8, &nQueueSize, sizeof(int));
	// 데이타
	memcpy(pbyData + 8 + sizeof(int), lpBuf, nSizeLen);

	COPYDATASTRUCT copyData;
	copyData.dwData = wKind;
	copyData.cbData = nTotSendLen;
	copyData.lpData = pbyData;
	
	::SendMessage(hCommsDbgWnd, WM_COPYDATA, 0, (LPARAM)&copyData);
	delete[] pbyData;

	return TRUE;
}

CString CCommMain::GetTimeString()
{
	CString strTime;
	
	CTime time = CTime::GetCurrentTime();
	strTime = time.Format("%H:%M:%S");
	return strTime;
}

//******************************************************************
//  Function Name : SetWriteConsol
//  Function      : 
//  Param         : char* lpData, BOOL bTitle/* = TRUE*/, BOOL bLine /*= FALSE*/
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CCommMain::SetWriteConsol( char* lpData, 
								BOOL bTitle/* = TRUE*/, 
								BOOL bLine /*= FALSE*/)
{
	if (m_pLogMsg == NULL)
		return;
	m_pLogMsg->SetWriteConsol(lpData, bTitle, bLine);
}

// TRUE:시스템, FALSE:사용자
BOOL CCommMain::SetWriteLog(CString strMsg, BOOL bMode)
{
	if (m_pLogMsg == NULL)
		return FALSE;
	
	return m_pLogMsg->SetLogMsgWriteToFile(strMsg, bMode);
}

BOOL CCommMain::WriteLogMsg(CString strLogMsg, CString& strErrorMsg, int nErrorCode)
{
	if (m_pLogMsg == NULL)
		return FALSE;

	return m_pLogMsg->WriteLogMsg(strLogMsg, strErrorMsg, nErrorCode);
}

long CCommMain::OnSetWriteConsol(WPARAM wParam, LPARAM lParam)
{
	SetWriteConsol((char*)wParam);
	return 0L;
}

long CCommMain::OnCommsDbgLog(WPARAM wParam, LPARAM lParam)
{
	CommsDbgLog((LPSTR)wParam, (WORD)lParam);
	return 0L;
}

long CCommMain::OnDataReceive(WPARAM wParam, LPARAM lParam)
{
	DataReceive((BYTE*)wParam, (BOOL)lParam);

	return 0L;
}
	
//******************************************************************
//  Function Name : SendSocketNotifyToAllCommApi
//  Function      : 통신프로그램에서 통신 nStatus신호를 모든 ComAPI에게 메세지로 전달한다.
//  Param         : int nStatus /*= SOCKET_CLOSING*/ 
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CCommMain::SendSocketNotifyToAllCommApi(int nStatus /*= SOCKET_CLOSING*/ )
{
	//	m_pParentWnd->SendMessage(UM_SEND_SOCKET_NOTIFY_TO_COMMAPI, (WPARAM)nStatus);

	int nCommAPIWndCnt = m_pArrCommApiWnd->GetSize(); 
	int nParam(0);
	
	if (m_hCommsDbgWnd)
		CommsDbgLog((LPSTR)(LPCTSTR)"&&&&& Comms::SendSocketNotifyToAllCommApi...");
	
	CString strMsg, strTemp;
	switch (nStatus)
	{
		case SOCKET_CONNECTING:					// =50,		// 소켓 연결 중 
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_CONNECTING";
			break;
		case SOCKET_CONNECTED:					//,		// 소켓 연결 완료
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_CONNECTED";
			break;
		case SOCKET_CLOSED:						//,			// 소켓 단절 상태
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_CLOSED";
			break;
		case SOCKET_CLOSING:					//,			// 소켓 단절 중
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_CLOSING";
			break;
		case SOCKET_CONNECT_FAIL:				//,	// 소켓 연결 실패
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_CONNECT_FAIL";
			break;
		case SOCKET_RECEIVE_FAIL:				//,	// 데이터 수신 실패
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_RECEIVE_FAIL";
			break;
		case SOCKET_SEND_FAIL:					//,		// 데이터 송신 실패
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_SEND_FAIL";
			break;
		case SOCKET_SEND_SUCCESS:				//,	// 데이터 송신 성공
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_SEND_SUCCESS";
			break;
		case SOCKET_RECONNECT_REQUEST:			//,// 재접속 요청
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_RECONNECT_REQUEST";
			break;
		case LOGIN_COMPLETE:					//,			// 승인처리 완료 
			{
				strMsg = "SendSocketNotifyToAllCommApi::LOGIN_COMPLETE";
				AfxMessageBox(strMsg);
			}
			break;
		case LOGIN_FAIL:						//			// 승인처리 실패 
			{
				strMsg = "SendSocketNotifyToAllCommApi::LOGIN_FAIL";
			//	AfxMessageBox(strMsg);
			}
			break;
		default:
				strMsg = "SendSocketNotifyToAllCommApi::Nothing!!!";
			break;
	}

	CommsDbgLog((LPSTR)(LPCTSTR)strMsg);

	if (nStatus == LOGIN_COMPLETE)
		nParam  = m_nSignOn;

	HWND hWndCommApi;
	if (nCommAPIWndCnt)
	{
		if (nStatus == SOCKET_CLOSING && m_bConnect == FALSE)
			return;
		
		for (int nCnt = nCommAPIWndCnt - 1; nCnt >= 0; nCnt--)
		{
			hWndCommApi = (HWND)(*m_pArrCommApiWnd)[nCnt];
			
			if (::IsWindow(hWndCommApi))
			{
				if (nStatus ==	SOCKET_CONNECTING)
				{
					nParam = m_nRetryCount + 1;
				}
				else if (nStatus == SOCKET_CLOSED || nStatus == SOCKET_CLOSING || nStatus == SOCKET_RECONNECT_REQUEST || nStatus == SOCKET_CONNECT_FAIL)
				{
					nParam = (LPARAM)GetParent();
				}

				::PostMessage(hWndCommApi,
							g_uSocketNotifyMsg, 
							(WPARAM)(int)nStatus, 
							nParam);
			}
			else
			{
				m_pArrCommApiWnd->RemoveAt(nCnt);
				PostMessage(UM_WND_STATE_CHECK);
			}
		}

		if (nStatus == SOCKET_CLOSED)
		{
		//	m_bSocketClosed = TRUE;
		}
	}
}
// 접속 실패 시 재접속 시도 하기
void CCommMain::RetryConnectToServer(int nErrorCode)
{
	CString		strMsg;
	CString		strSocketMsg;

	m_bConnect = FALSE;
	m_nSignOn  = -1;	// 로그인 상태를 초기화 한다.
	
	if (m_pCommsConfig->m_bLogWrite)
	{		
		strMsg = "Comms,OnSocketNotify SOCKET_CONNECT_FAIL ,%d,%s";
		WriteLogMsg(strMsg, strSocketMsg, nErrorCode);					
		CommsDbgLog((LPSTR)(LPCTSTR)strSocketMsg);
	}

// --> [Edit]  강지원 2010/08/25
	// 재 연결을 시도한다(3초에 1번씩 3번).
	if (m_nTotalRetryCount < m_pCommsConfig->m_nMaxRetryCount)
	{
		// "재접속 중" 임을 알린다.
		m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CONNECTING, m_nRetryCount + 1);
		SendSocketNotifyToAllCommApi(SOCKET_CONNECTING);

// --> [Edit]  강지원 2011/04/12 ( 재접속 수정 )
// 		if (m_nRetryConnectTimer)
// 		{
// 			KillTimer(m_nRetryConnectTimer);
// 			m_nRetryConnectTimer = 0;
// 		}

// -->  //KMG 2012.06.19 접속포트변경 : 버젼처리시 8080 사용했으면 먼저실행, 아니면 Main Ip,Port각각 실행후 8080포트시도
		if( m_pCommsConfig->m_bUseSubPort || m_bConnectSubPort ){
			if(m_nTotalRetryCount%2==0) m_pCommsConfig->NextIPPostion();
			m_pTcpSocket->SetHostAddressAndPort(m_pCommsConfig->GetMainIP(), m_pCommsConfig->m_nSubPort );
			m_bConnectSubPort = FALSE;
			m_pCommsConfig->m_bUseSubPort = FALSE;
		}
		else
		{
//<---
			m_nRePortPosition++;
			if ( m_nRePortPosition >= MAINIP_CNT )
			{
				m_nRePortPosition = 0;
				m_pCommsConfig->NextPortPostion();
			}

			m_pCommsConfig->NextIPPostion();
			m_pTcpSocket->SetHostAddressAndPort(m_pCommsConfig->GetMainIP(), m_pCommsConfig->GetMainPort());

			if ( m_pCommsConfig->m_nMessageOpen == 1 )
			{
				CString strMsg = "";
				strMsg.Format("Connect IP = %s, Port = %d", m_pCommsConfig->GetMainIP(), m_pCommsConfig->GetMainPort());
				AfxMessageBox(strMsg);
			}

			m_nRetryCount++;
	//		m_nRetryConnectTimer = SetTimer(UM_RECONNECT_TIMER, m_pCommsConfig->m_nKeyChangeTimeOut * 1000, 0);	
	// <-- [Edit]  강지원 2011/04/12
			if (m_nRetryCount >= (MAINIP_CNT * 2))
			{
				m_nTotalRetryCount++;
				m_nRetryCount = 0;

				//KMG 2012.06.19 접속포트변경 :  Main Ip,Port각각실행후8080포트시도
				m_bConnectSubPort = TRUE; 
			}
		}
	}
	// 더이상 재시도 안하는 경우 접속 실패를 알린다.
	else
	{
		m_nRetryCount = 0;
		m_nTotalRetryCount = 0;
		// 모든 ComAPI에게 소켓 연결실패 메세지를 전송한다.
		SendSocketNotifyToAllCommApi(SOCKET_CONNECT_FAIL);
		m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CONNECT_FAIL);
		m_pTcpSocket->DisConnectTCPSocket();
		m_pParentWnd->PostMessage(WM_COMMS_PROGRAM_CLOSE, 0, 0);
	}
// <-- [Edit]  강지원 2010/08/25


/*
	// sub port 사용으로 설정 되어 있고
	if (m_pCommsConfig->m_bUseSubPort)
	{
		// Main Port로 3회 접속 실패면 sub port로 접속 시도 한다.
		 if (!m_bConnectSubPort && m_nRetryCount >= m_pCommsConfig->m_nMaxRetryCount)
		 {
			m_nRetryCount		= 0;
			m_bConnectSubPort	= TRUE;
			m_pCommsConfig->m_nMainPort = m_pCommsConfig->m_nSubPort;
			m_pTcpSocket->SetHostAddressAndPort(m_pCommsConfig->m_strMainIP, m_pCommsConfig->m_nMainPort);
		 }
	}

	// 재 연결을 시도한다(10초에 1번씩 3번).
	if (m_nRetryCount < m_pCommsConfig->m_nMaxRetryCount)
	{
		// "재접속 중" 임을 알린다.
		m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CONNECTING, m_nRetryCount + 1);
		SendSocketNotifyToAllCommApi(SOCKET_CONNECTING);

		if (m_nRetryConnectTimer)
		{
			KillTimer(m_nRetryConnectTimer);
			m_nRetryConnectTimer = 0;
		}

		m_nRetryCount++;
		m_nRetryConnectTimer = SetTimer(UM_RECONNECT_TIMER, RECONNECT_TIMER_VALUE, 0);	
	}
	// 더이상 재시도 안하는 경우 접속 실패를 알린다.
	else
	{
		m_nRetryCount = 0;	
		// 모든 ComAPI에게 소켓 연결실패 메세지를 전송한다.
		SendSocketNotifyToAllCommApi(SOCKET_CONNECT_FAIL);
		m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CONNECT_FAIL);
		m_pTcpSocket->DisConnectTCPSocket();
		m_pParentWnd->PostMessage(WM_COMMS_PROGRAM_CLOSE, 0, 0);
	}
*/
}
// 등록된 실시간 타입인가 체크
BOOL CCommMain::CheckRealType(BYTE cCommandId)
{

	return TRUE;
}

// 2002.7.15 -hidden-  신업무 체결통보 처리하자.
int CCommMain::ConclusionRealProcessForBP(CString strTrCode, BYTE* pTrData, DWORD dwDataLen, BYTE* pRealData)
{
	CString strTemp = "";
	long nTemp(0);
	int nDataLen(0);

	//-------------------------------------------------------
	//2011.03.11 jhj 메모리 size를 계산해서 memcpy를 한다.
	int nByteSize(0);
	nByteSize = _msize(pTrData);
	TRACE1("\n\n===============>pTrData size is [%d]<================\n\n", nByteSize);
	//-------------------------------------------------------

	if ( strTrCode == TRAN_CN997Q00 )
	{
		S_CHEJAN_REAL_OUTREC*	pData = (S_CHEJAN_REAL_OUTREC*)(pRealData + REAL_TYPE_SIZE);
		memset(pData, 0x00	, sizeof(S_CHEJAN_REAL_OUTREC) );

		CN997Q00_OutRec1		OutData;
		memset(&OutData, 0x00	, sizeof(CN997Q00_OutRec1) );

		//# 2011.03.11 jhj
		if(nByteSize < sizeof(CN997Q00_OutRec1))
			return 0;

		memcpy(&OutData, pTrData, sizeof(CN997Q00_OutRec1));

		CString strFlag	= CString(OutData.market_gb, sizeof(OutData.market_gb));		//	[시장구분]
		CString strGubun = CString(OutData.data_gb, sizeof(OutData.data_gb));			//	[DATA구분]

		if ( strGubun == "5" )
		{
			//	주문 접수일때만 계좌명/시간등의 처리가 달라지기 때문에 구조체를 바꾼다.
			// 2011.03.11 주문접수 체결통보일때 동일한 구조로 데이터가 내려옴..
			// CN997Q00_OutRec2 => CN997Q00_OutRec1 로 다 수정함
			// 2011.03.14 CN997Q00_OutRec2의 구조체를 수정함. 1으로 하면 중간에 데이터가 맞지 않음. 체결과 주문접수일때 내려오는 데이터 길이와 순서가 다름. => 이게 뭔가여...ㅡㅡ;;
			CN997Q00_OutRec2		OutData;
			memset(&OutData, 0x00	, sizeof(CN997Q00_OutRec2) );

			//# 2011.03.11 jhj
			if(nByteSize < sizeof(CN997Q00_OutRec2))
				return 0;

			memcpy(&OutData, pTrData, sizeof(CN997Q00_OutRec2));

			memcpy(pData->market_gb			, OutData.market_gb			, sizeof(OutData.market_gb		) );	//	[시장구분] 6:KOSPI 선물/옵션								
			memcpy(pData->data_gb			, OutData.data_gb			, sizeof(OutData.data_gb		) );	//	[DATA구분] 1:체결, 2:정정, 3:취소, 4:거부, 5:주문접수확인	
			memcpy(pData->data_name			, OutData.data_name			, sizeof(OutData.data_name		) );	//	[DATA명]													
			memcpy(pData->acct_no			, OutData.acct_no			, sizeof(OutData.acct_no		) );	//	[계좌번호]     												
			memcpy(pData->acct_nm			, OutData.acct_nm			, sizeof(OutData.acct_nm		) );	//	[계좌명]     												
			memcpy(pData->order_no			, OutData.order_no			, sizeof(OutData.order_no		) );	//	[주문번호]	 형식 : 003-000001(선물인경우만)			    
			memcpy(pData->org_order_no		, OutData.org_order_no		, sizeof(OutData.org_order_no	) );	//	[원주문번호] 형식 : 003-000001(선물인경우만)				
	//		memcpy(pData->spread_gb			, OutData.spread_gb			, sizeof(OutData.spread_gb		) );	//	[SPREAD구분]												
			memcpy(pData->jmcode			, OutData.jmcode			, sizeof(OutData.jmcode			) );	//	[종목코드]													
			memcpy(pData->jmname			, OutData.jmname			, sizeof(OutData.jmname			) );	//	[종목명]													
			memcpy(pData->meme_gb			, OutData.meme_gb			, sizeof(OutData.meme_gb		) );	//	[매매구분]													
			memcpy(pData->order_gb			, OutData.order_gb			, sizeof(OutData.order_gb		) );	//	[주문구분]													

			strTemp = CString (OutData.order_qty, sizeof(OutData.order_qty));
			pData->order_qty = htonl(atol(strTemp));															//	[주문수량]													

			strTemp = CString (OutData.order_price, sizeof(OutData.order_price));
			pData->order_price = htonl(atol(strTemp));															//	[주문단가]													

			strTemp = CString (OutData.che_qty, sizeof(OutData.che_qty));
			pData->che_qty = htonl(atol(strTemp));																//	[체결수량]													

			strTemp = CString (OutData.che_price, sizeof(OutData.che_price));
			pData->che_price = htonl(atol(strTemp));															//	[체결단가]													

			strTemp = CString (OutData.tot_che_qty, sizeof(OutData.tot_che_qty));
			pData->tot_che_qty = htonl(atol(strTemp));															//	[총체결수량]													

			strTemp = CString (OutData.avg_che_price, sizeof(OutData.avg_che_price));
			pData->avg_che_price = htonl(atol(strTemp));														//	[평균체결단가]													

			strTemp = CString (OutData.miche_qty, sizeof(OutData.miche_qty));
			pData->miche_qty = htonl(atol(strTemp));															//	[미체결수량]													

			memcpy(pData->mod_can_gb		, OutData.mod_can_gb		, sizeof(OutData.mod_can_gb		) );	//	[정정취소구분]												

			strTemp = CString (OutData.qty, sizeof(OutData.qty));
			pData->qty = htonl(atol(strTemp));																	//	[실질수량]													

			strTemp = CString (OutData.buy_avg_prc, sizeof(OutData.buy_avg_prc));
			pData->buy_avg_prc = htonl(atol(strTemp));															//	[매입단가]													

	//		memcpy(pData->migul_avg_amt		, OutData.migul_avg_amt		, sizeof(OutData.migul_avg_amt	) );	//	[미결제약정평균금액]										
			pData->price	= pData->che_price;																	//	[현재가] 체결단가를 현재가에 넣는다.													
			memcpy(pData->che_cond			, OutData.che_cond			, sizeof(OutData.che_cond		) );	//	[체결조건]													
	//		memcpy(pData->non_code			, OutData.non_code			, sizeof(OutData.non_code		) );	//	[부적격코드]												
	//		memcpy(pData->filler			, OutData.filler			, sizeof(OutData.filler			) );	//	[FILLER]													
	//		memcpy(pData->fu_commit_sonik	, OutData.fu_commit_sonik	, sizeof(OutData.fu_commit_sonik) );	//	[선물정산매매손익]											
	//		memcpy(pData->fu_avg_sonik		, OutData.fu_avg_sonik		, sizeof(OutData.fu_avg_sonik	) );	//	[선물평균매매손익]											
	//		memcpy(pData->op_commit_sonik	, OutData.op_commit_sonik	, sizeof(OutData.op_commit_sonik) );	//	[옵션정산매매손익]											
	//		memcpy(pData->op_buy_amt		, OutData.op_buy_amt		, sizeof(OutData.op_buy_amt		) );	//	[옵션매수대금]												
	//		memcpy(pData->op_sell_amt		, OutData.op_sell_amt		, sizeof(OutData.op_sell_amt	) );	//	[옵션매도대금]												
	//		memcpy(pData->fu_buy_amt		, OutData.fu_buy_amt		, sizeof(OutData.fu_buy_amt		) );	//	[선물매수대금]												
	//		memcpy(pData->fu_sell_amt		, OutData.fu_sell_amt		, sizeof(OutData.fu_sell_amt	) );	//	[선물매도대금]												
	//		memcpy(pData->order_tot_amt		, OutData.order_tot_amt		, sizeof(OutData.order_tot_amt	) );	//	[주문가능총액]												
	//		memcpy(pData->order_cash		, OutData.order_cash		, sizeof(OutData.order_cash		) );	//	[주문가능현금]												

			memcpy(pData->order_time		, OutData.order_time		, sizeof(OutData.order_time		) );	//	[주문시간]													

			memcpy(pData->credit_gb			, OutData.credit_gb			, sizeof(OutData.credit_gb		) );	//	[신용거래구분]												
			memcpy(pData->loan_date			, OutData.loan_date			, sizeof(OutData.loan_date		) );	//	[대출일자]													
			memcpy(pData->damboloan_gb		, OutData.damboloan_gb		, sizeof(OutData.damboloan_gb	) );	//	[담보대출구분]												
			memcpy(pData->buy_date			, OutData.buy_date			, sizeof(OutData.buy_date		) );	//	[매수일]													
			memcpy(pData->tax_target_gb		, OutData.tax_target_gb		, sizeof(OutData.tax_target_gb	) );	//	[과세대상구분]												
			memcpy(pData->bond_jan_gb		, OutData.bond_jan_gb		, sizeof(OutData.bond_jan_gb	) );	//	[채권잔고구분]												
			memcpy(pData->credit_gb_text	, OutData.credit_gb_text	, sizeof(OutData.credit_gb_text	) );	//	[신용구분명]												
			memcpy(pData->credit_tot_order	, OutData.credit_tot_order	, sizeof(OutData.credit_tot_order) );	//	[신용통합주문여부]											
			
			nDataLen = sizeof(S_CHEJAN_REAL_OUTREC);
		}
		else
		{
			CN997Q00_OutRec1		OutData;
			memset(&OutData, 0x00	, sizeof(CN997Q00_OutRec1) );

			//# 2011.03.11 jhj
			if(nByteSize < sizeof(CN997Q00_OutRec1))
				return 0;

			memcpy(&OutData, pTrData, sizeof(CN997Q00_OutRec1));

			memcpy(pData->market_gb			, OutData.market_gb			, sizeof(OutData.market_gb		) );	//	[시장구분] 6:KOSPI 선물/옵션								
			memcpy(pData->data_gb			, OutData.data_gb			, sizeof(OutData.data_gb		) );	//	[DATA구분] 1:체결, 2:정정, 3:취소, 4:거부, 5:주문접수확인	
			memcpy(pData->data_name			, OutData.data_name			, sizeof(OutData.data_name		) );	//	[DATA명]													
			memcpy(pData->acct_no			, OutData.acct_no			, sizeof(OutData.acct_no		) );	//	[계좌번호]     												
			memcpy(pData->acct_nm			, OutData.acct_nm			, sizeof(OutData.acct_nm		) );	//	[계좌명]     												
			memcpy(pData->order_no			, OutData.order_no			, sizeof(OutData.order_no		) );	//	[주문번호]	 형식 : 003-000001(선물인경우만)			    
			memcpy(pData->org_order_no		, OutData.org_order_no		, sizeof(OutData.org_order_no	) );	//	[원주문번호] 형식 : 003-000001(선물인경우만)				
	//		memcpy(pData->spread_gb			, OutData.spread_gb			, sizeof(OutData.spread_gb		) );	//	[SPREAD구분]												
			memcpy(pData->jmcode			, OutData.jmcode			, sizeof(OutData.jmcode			) );	//	[종목코드]													
			memcpy(pData->jmname			, OutData.jmname			, sizeof(OutData.jmname			) );	//	[종목명]													
			memcpy(pData->meme_gb			, OutData.meme_gb			, sizeof(OutData.meme_gb		) );	//	[매매구분]													
			memcpy(pData->order_gb			, OutData.order_gb			, sizeof(OutData.order_gb		) );	//	[주문구분]													

			strTemp = CString (OutData.order_qty, sizeof(OutData.order_qty));
			pData->order_qty = htonl(atol(strTemp));															//	[주문수량]													

			strTemp = CString (OutData.order_price, sizeof(OutData.order_price));
			pData->order_price = htonl(atol(strTemp));															//	[주문단가]													

			strTemp = CString (OutData.che_qty, sizeof(OutData.che_qty));
			pData->che_qty = htonl(atol(strTemp));																//	[체결수량]													

			strTemp = CString (OutData.che_price, sizeof(OutData.che_price));
			pData->che_price = htonl(atol(strTemp));															//	[체결단가]													

			strTemp = CString (OutData.tot_che_qty, sizeof(OutData.tot_che_qty));
			pData->tot_che_qty = htonl(atol(strTemp));															//	[총체결수량]													

			strTemp = CString (OutData.avg_che_price, sizeof(OutData.avg_che_price));
			pData->avg_che_price = htonl(atol(strTemp));														//	[평균체결단가]													

			strTemp = CString (OutData.miche_qty, sizeof(OutData.miche_qty));
			pData->miche_qty = htonl(atol(strTemp));															//	[미체결수량]													

			memcpy(pData->mod_can_gb		, OutData.mod_can_gb		, sizeof(OutData.mod_can_gb		) );	//	[정정취소구분]												

			strTemp = CString (OutData.qty, sizeof(OutData.qty));
			pData->qty = htonl(atol(strTemp));																	//	[실질수량]													

			strTemp = CString (OutData.buy_avg_prc, sizeof(OutData.buy_avg_prc));
			pData->buy_avg_prc = htonl(atol(strTemp));															//	[매입단가]													

	//		memcpy(pData->migul_avg_amt		, OutData.migul_avg_amt		, sizeof(OutData.migul_avg_amt	) );	//	[미결제약정평균금액]										
			pData->price	= pData->che_price;																	//	[현재가] 체결단가를 현재가에 넣는다.													
			memcpy(pData->che_cond			, OutData.che_cond			, sizeof(OutData.che_cond		) );	//	[체결조건]													
	//		memcpy(pData->non_code			, OutData.non_code			, sizeof(OutData.non_code		) );	//	[부적격코드]												
	//		memcpy(pData->filler			, OutData.filler			, sizeof(OutData.filler			) );	//	[FILLER]													
	//		memcpy(pData->fu_commit_sonik	, OutData.fu_commit_sonik	, sizeof(OutData.fu_commit_sonik) );	//	[선물정산매매손익]											
	//		memcpy(pData->fu_avg_sonik		, OutData.fu_avg_sonik		, sizeof(OutData.fu_avg_sonik	) );	//	[선물평균매매손익]											
	//		memcpy(pData->op_commit_sonik	, OutData.op_commit_sonik	, sizeof(OutData.op_commit_sonik) );	//	[옵션정산매매손익]											
	//		memcpy(pData->op_buy_amt		, OutData.op_buy_amt		, sizeof(OutData.op_buy_amt		) );	//	[옵션매수대금]												
	//		memcpy(pData->op_sell_amt		, OutData.op_sell_amt		, sizeof(OutData.op_sell_amt	) );	//	[옵션매도대금]												
	//		memcpy(pData->fu_buy_amt		, OutData.fu_buy_amt		, sizeof(OutData.fu_buy_amt		) );	//	[선물매수대금]												
	//		memcpy(pData->fu_sell_amt		, OutData.fu_sell_amt		, sizeof(OutData.fu_sell_amt	) );	//	[선물매도대금]												
	//		memcpy(pData->order_tot_amt		, OutData.order_tot_amt		, sizeof(OutData.order_tot_amt	) );	//	[주문가능총액]												
	//		memcpy(pData->order_cash		, OutData.order_cash		, sizeof(OutData.order_cash		) );	//	[주문가능현금]												

			memcpy(pData->order_time		, OutData.order_time		, sizeof(OutData.order_time		) );	//	[주문시간]													

			memcpy(pData->credit_gb			, OutData.credit_gb			, sizeof(OutData.credit_gb		) );	//	[신용거래구분]												
			memcpy(pData->loan_date			, OutData.loan_date			, sizeof(OutData.loan_date		) );	//	[대출일자]													
			memcpy(pData->damboloan_gb		, OutData.damboloan_gb		, sizeof(OutData.damboloan_gb	) );	//	[담보대출구분]												
			memcpy(pData->buy_date			, OutData.buy_date			, sizeof(OutData.buy_date		) );	//	[매수일]													
			memcpy(pData->tax_target_gb		, OutData.tax_target_gb		, sizeof(OutData.tax_target_gb	) );	//	[과세대상구분]												
			memcpy(pData->bond_jan_gb		, OutData.bond_jan_gb		, sizeof(OutData.bond_jan_gb	) );	//	[채권잔고구분]												
			memcpy(pData->credit_gb_text	, OutData.credit_gb_text	, sizeof(OutData.credit_gb_text	) );	//	[신용구분명]												
			memcpy(pData->credit_tot_order	, OutData.credit_tot_order	, sizeof(OutData.credit_tot_order) );	//	[신용통합주문여부]											
			
			nDataLen = sizeof(S_CHEJAN_REAL_OUTREC);
		}

		
	}
	else if ( strTrCode == TRAN_CN996Q00 )
	{
		CString strDanga = "";
		S_CHEJAN_REAL_OUTREC*	pData = (S_CHEJAN_REAL_OUTREC*)(pRealData + REAL_TYPE_SIZE);;
		memset(pData, 0x00	, sizeof(S_CHEJAN_REAL_OUTREC) );

		CN996Q00_OutRec1		OutData;
		memset(&OutData, 0x00	, sizeof(CN996Q00_OutRec1) );

		//# 2011.03.11 jhj
		if(nByteSize < sizeof(CN996Q00_OutRec1))
			return 0;

		memcpy(&OutData, pTrData, sizeof(CN996Q00_OutRec1));

		CString strFlag	= CString(OutData.market_gb, sizeof(OutData.market_gb));		//	[시장구분]
		CString strGubun = CString(OutData.data_gb, sizeof(OutData.data_gb));			//	[DATA구분]
		CString strSFlag = CString(OutData.spread_gb, sizeof(OutData.spread_gb));		//	[SPREAD구분]

		memcpy(pData->market_gb			, OutData.market_gb			, sizeof(OutData.market_gb		) );	//	[시장구분] 6:KOSPI 선물/옵션								
		memcpy(pData->data_gb			, OutData.data_gb			, sizeof(OutData.data_gb		) );	//	[DATA구분] 1:체결, 2:정정, 3:취소, 4:거부, 5:주문접수확인	
		memcpy(pData->data_name			, OutData.data_name			, sizeof(OutData.data_name		) );	//	[DATA명]													
		memcpy(pData->acct_no			, OutData.acct_no			, sizeof(OutData.acct_no		) );	//	[계좌번호]     												
		memcpy(pData->acct_nm			, OutData.acct_nm			, sizeof(OutData.acct_nm		) );	//	[계좌명]     												
		memcpy(pData->order_no			, OutData.order_no			, sizeof(OutData.order_no		) );	//	[주문번호]	 형식 : 003-000001(선물인경우만)			    
		memcpy(pData->org_order_no		, OutData.org_order_no		, sizeof(OutData.org_order_no	) );	//	[원주문번호] 형식 : 003-000001(선물인경우만)				
		memcpy(pData->spread_gb			, OutData.spread_gb			, sizeof(OutData.spread_gb		) );	//	[SPREAD구분]												
		memcpy(pData->jmcode			, OutData.jmcode			, sizeof(pData->jmcode			) );	//	[종목코드]	TR에서 내려오는 코드가 자릿수가 더 길다.
		memcpy(pData->jmname			, OutData.jmname			, sizeof(OutData.jmname			) );	//	[종목명]													
		memcpy(pData->meme_gb			, OutData.meme_gb			, sizeof(OutData.meme_gb		) );	//	[매매구분]													
		memcpy(pData->order_gb			, OutData.order_gb			, sizeof(OutData.order_gb		) );	//	[주문구분]													

		strTemp = CString (OutData.order_qty, sizeof(OutData.order_qty));
		pData->order_qty = htonl(atol(strTemp));															//	[주문수량]													

		strTemp = CString (OutData.order_price, sizeof(OutData.order_price));
//		strDanga.Format("%0.2f", atof(strTemp)/100);
		pData->order_price = htonl(atol(strTemp));															//	[주문단가]													

		strTemp = CString (OutData.che_qty, sizeof(OutData.che_qty));
		pData->che_qty = htonl(atol(strTemp));																//	[체결수량]													

		strTemp = CString (OutData.che_price, sizeof(OutData.che_price));
		pData->che_price = htonl(atol(strTemp));															//	[체결단가]													

		strTemp = CString (OutData.tot_che_qty, sizeof(OutData.tot_che_qty));
		pData->tot_che_qty = htonl(atol(strTemp));															//	[총체결수량]													

		strTemp = CString (OutData.avg_che_price, sizeof(OutData.avg_che_price));
		pData->avg_che_price = htonl(atol(strTemp));														//	[평균체결단가]													

		strTemp = CString (OutData.miche_qty, sizeof(OutData.miche_qty));
		pData->miche_qty = htonl(atol(strTemp));															//	[미체결수량]													

		memcpy(pData->mod_can_gb		, OutData.mod_can_gb		, sizeof(OutData.mod_can_gb		) );	//	[정정취소구분]												

		strTemp = CString (OutData.last_qty, sizeof(OutData.last_qty));
		pData->qty = htonl(atol(strTemp));																	//	[실질수량]													

		strTemp = CString (OutData.last_price, sizeof(OutData.last_price));
		pData->buy_avg_prc = htonl(atol(strTemp));															//	[매입단가]													

		memcpy(pData->migul_avg_amt		, OutData.last_migul_amt	, sizeof(OutData.last_migul_amt	) );	//	[미결제약정평균금액]										
		pData->price	= pData->che_price;																	//	[현재가] 체결단가를 현재가에 넣는다.													
//		memcpy(pData->che_cond			, OutData.che_cond			, sizeof(OutData.che_cond		) );	//	[체결조건]													
		memcpy(pData->non_code			, OutData.non_code			, sizeof(OutData.non_code		) );	//	[부적격코드]

		//if ( strSFlag == "1" )			//Spread 이면 처리
		//{
		//	memcpy(pData->jmcode			, OutData.next_code			, sizeof(pData->jmcode		) );	//	[종목코드]	TR에서 내려오는 코드가 자릿수가 더 길다.
		//	memcpy(pData->jmname			, OutData.next_name			, sizeof(OutData.next_name	) );	//	[종목명]													
		//	memcpy(pData->meme_gb			, OutData.next_meme			, sizeof(OutData.next_meme	) );	//	[매매구분]													

		//	strTemp = CString (OutData.next_qty, sizeof(OutData.next_qty));
		//	pData->order_qty = htonl(atol(strTemp));															//	[주문수량]													

		//	strTemp = CString (OutData.next_price, sizeof(OutData.next_price));
		//	pData->buy_avg_prc = htonl(atol(strTemp));															//	[매입단가]													

		//	memcpy(pData->migul_avg_amt		, OutData.next_migul_amt	, sizeof(OutData.next_migul_amt	) );	//	[미결제약정평균금액]										
		//}

		memcpy(pData->che_cond			, "  "				, 1 );	//	[체결조건]													

		memcpy(pData->filler			, "     "			, 5 );	//	[FILLER]													
		memcpy(pData->fu_commit_sonik	, "          "		, 10);	//	[선물정산매매손익]											
		memcpy(pData->fu_avg_sonik		, "          "		, 10);	//	[선물평균매매손익]											
		memcpy(pData->op_commit_sonik	, "          "		, 10);	//	[옵션정산매매손익]											
		memcpy(pData->op_buy_amt		, "            "	, 12);	//	[옵션매수대금]												
		memcpy(pData->op_sell_amt		, "            "	, 12);	//	[옵션매도대금]												
		memcpy(pData->fu_buy_amt		, "            "	, 12);	//	[선물매수대금]												
		memcpy(pData->fu_sell_amt		, "            "	, 12);	//	[선물매도대금]												
		memcpy(pData->order_tot_amt		, "          "		, 10);	//	[주문가능총액]												
		memcpy(pData->order_cash		, "          "		, 10);	//	[주문가능현금]												

		memcpy(pData->order_time		, OutData.order_time		, sizeof(OutData.order_time		) );	//	[주문시간]													
//		memcpy(pData->order_time		, "        "		, 8 );	//	[주문시간]													

		memcpy(pData->credit_gb			, " "				, 1 );	//	[신용거래구분]												
		memcpy(pData->loan_date			, "        "		, 8 );	//	[대출일자]													
		memcpy(pData->damboloan_gb		, " "				, 1 );	//	[담보대출구분]												
		memcpy(pData->buy_date			, "        "		, 8 );	//	[매수일]													
		memcpy(pData->tax_target_gb		, " "				, 1 );	//	[과세대상구분]												
		memcpy(pData->bond_jan_gb		, " "				, 1 );	//	[채권잔고구분]												
		memcpy(pData->credit_gb_text	, "          "		, 10 );	//	[신용구분명]												
		memcpy(pData->credit_tot_order	, " "				, 1 );	//	[신용통합주문여부]											

		nDataLen = sizeof(S_CHEJAN_REAL_OUTREC);
	}
	else if(strTrCode == "CN994Q00")	//ljj 20110314 시스템알람 추가
	{
		S_ALARM_REAL_REC*	pData = (S_ALARM_REAL_REC*)(pRealData + REAL_TYPE_SIZE);
		memset(pData, 0x00	, sizeof(S_ALARM_REAL_REC) );

		CN994Q00_OutRec2		OutData;
		memset(&OutData, 0x00	, sizeof(CN994Q00_OutRec2) );

		//# 2011.03.11 jhj
		if(nByteSize < sizeof(CN994Q00_OutRec2))
			return 0;

		memcpy(&OutData, pTrData, sizeof(CN994Q00_OutRec2));

		memcpy(pData->AccountFlag, OutData.AccountFlag , sizeof(OutData.AccountFlag));
		memcpy(pData->InOutFlag, OutData.InOutFlag , sizeof(OutData.InOutFlag));
		memcpy(pData->BuySellFlag, OutData.BuySellFlag , sizeof(OutData.BuySellFlag));

		nDataLen = sizeof(S_ALARM_REAL_REC);
	}

	return nDataLen;
/*
	CString strTrCode(pstrData, QRYCODE_LEN);
	pstrData += 100;										// 헤더 + 메세지
	pstrData += 40;											// 체결통보 헤더 데이타.
	BYTE *pBuf = new BYTE[1024];							// 체결통보 자동갱신 사이즈 166 + 1
	BYTE *SprBuf = NULL;									// 스프레드 일경우 사용한다.
	long lTemp = 314;		//KJI 20070518(신용추가로 변경)
	lTemp = htonl(lTemp);
	memcpy(pBuf, &lTemp, 4);
	lTemp = 1;
	lTemp = htonl(lTemp);
	memcpy(pBuf+4, &lTemp, 4);
	memcpy(pBuf+8, pstrData, 1);
	//if(strTrCode == "CN994Q00")	//LJP 알람신호
	//{
	//	CString strAccountFlag(pstrData,1); 
	//	pstrData++;
	//	CString strInOutFlag(pstrData, 1);
	//	pstrData++;
	//	CString strBuySellFlag(pstrData, 1);
	//	CStringArray* pConclusion = new CStringArray;

	//	pConclusion->Add(strAccountFlag);				
	//	pConclusion->Add(strInOutFlag);	
	//	pConclusion->Add(strBuySellFlag);	
	//	return pConclusion;
	//}
	CString strFlag(pstrData, 1);	pstrData++;				// 6-KOSPI, 7-KOFEX
	memcpy(pBuf+9, pstrData, 1);
	CString strGubun(pstrData, 1);	pstrData++;				// 1-체결, 2-정정확인, 3-취소확인, 4-거부, 5-주문확인

	CStringArray* pConclusion = new CStringArray;
	
	if (strTrCode == "CN997Q00")  //현물 체결통보 
	{
		pConclusion->Add(strFlag);				//시장구분을 넣어둔다.
		pConclusion->Add(strGubun);				//체결구분을 넣어둔다.		//shc 20030930

		memcpy(pBuf+10, pstrData, 16);
		CString strDataName(pstrData, 16);	pstrData += 16;		// 데이타명(16)
		strDataName.TrimLeft();
		strDataName.TrimRight();
		pConclusion->Add(strDataName);

		memcpy(pBuf+26, pstrData, 11);
		CString strAccount(pstrData, 11);	pstrData += 11;		// 계좌번호(11)
		pConclusion->Add(strAccount);

		//memcpy(pBuf+37, pstrData, 16);		pstrData += 16;		// 계좌명(16)

		//ljj 20060607 현물에만 적용 주문시간을 계좌명패킷에 실어서 보낸준단다..(호가레이더 때문에)
		//계좌명(10)+주문시간(6)
		//계좌명은 16바이트이므로 계좌명(10byt+space(6byte))
		//주문시간은 8바이트이므로 주문시간(6byt) + '00'(2byte)
		CString strAccNMData( pstrData, 16);
		CString strAccNM = strAccNMData.Left(10);
		
		CString strJuTime = strAccNMData.Mid(10);
		strAccNM.Format("%16s", strAccNM+"      ");

		//KJI 20070509
		if( strGubun != "5")
		{
			memcpy(pBuf+37, (LPSTR)(LPCTSTR)strAccNM, 16);		pstrData += 18;		//KJI 20070423 계좌명(10)
			memcpy(pBuf+278, (LPSTR)(LPCTSTR)strJuTime, 8);							// 주문시간(8)
		}
		else
		{
			memcpy(pBuf+37, (LPSTR)(LPCTSTR)strAccNM, 16);
			pstrData += 16;
		}
		
		memcpy(pBuf+53, pstrData, 10);
		CString strNum(pstrData, 10);		pstrData += 10;		// 주문번호(10)
		strNum.TrimRight(); 
		strNum.Format("%d", atoi(strNum));

		memcpy(pBuf+63, pstrData, 10);		pstrData += 10;		// 원주문번호(10)

		memcpy(pBuf+73, " ", 1);								// 스프레드구분(1)

		memcpy(pBuf+74, pstrData, 12);		pstrData += 12;		// 종목코드(12)

		memcpy(pBuf+86, pstrData, 20);
		CString strJongmok(pstrData, 20);	pstrData += 20;		// 종목명(20)
		strJongmok.TrimLeft(); 
		strJongmok.TrimRight();
		pConclusion->Add(strJongmok);

		memcpy(pBuf+106, pstrData, 4);
		CString strSaleBuy(pstrData, 4);	pstrData += 4;		// 매매구분(4)
		pConclusion->Add(strSaleBuy);

		CString strQuant(pstrData, 8);
		lTemp = atoi(strQuant);
		strQuant.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+112, &lTemp, 4);		pstrData += 8;		// 주문수량(4)

		CString strDanga(pstrData, 9);
		lTemp = atoi(strDanga);
		strDanga.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+116, &lTemp, 4);		pstrData += 9;		// 주문단가(4)

		CString strCheQuant(pstrData, 8);
		lTemp = atoi(strCheQuant);
		strCheQuant.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+120, &lTemp, 4);		pstrData += 8;		// 체결수량(4)

		CString strCheDanga(pstrData, 9);
		CString strCheDanga1 = strCheDanga;						//ljj 20070129 체결단가를 현재가에 넣음
		lTemp = atoi(strCheDanga);
		strCheDanga.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+124, &lTemp, 4);		pstrData += 9;		// 체결단가(4)

		CString strTemp(pstrData, 8);
		lTemp = atoi(strTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+128, &lTemp, 4);		pstrData += 8;		// 총체결수량(4)

		CString strTemp1(pstrData, 9);
		lTemp = atoi(strTemp1);
		lTemp = htonl(lTemp);
		memcpy(pBuf+132, &lTemp, 4);		pstrData += 9;		// 평균체결단가(4)

		CString strTemp2(pstrData, 8);
		lTemp = atoi(strTemp2);
		lTemp = htonl(lTemp);
		memcpy(pBuf+136, &lTemp, 4);		pstrData += 8;		// 미체결수량(4)
		
		memcpy(pBuf+140, pstrData, 8);		pstrData += 8;		// 정정취소구분(8)

		CString strTemp3(pstrData, 8);							
		lTemp = atoi(strTemp3);
		lTemp = htonl(lTemp);
		memcpy(pBuf+148, &lTemp, 4);		pstrData += 8;		// 실질수량(4)
		
		CString strTemp4(pstrData, 9);							
		lTemp = atoi(strTemp4);
		lTemp = htonl(lTemp);
		memcpy(pBuf+152, &lTemp, 4);		pstrData += 9;		// 매입단가(4)
		
		//KJI 20040219
		memcpy(pBuf+156, "            ", 12);					// 미결제약정금액(12)

		pstrData += 2;	//잔고구분 사용안함
		//KJI 20040219
		memcpy(pBuf+110, pstrData, 2);							//주문구분(2)
		pstrData += 2;	//주문구분 위에서 처리했음

		memcpy(pBuf+172, pstrData, 1);	pstrData += 1;			//체결조건(1)

		//KJI 20070509
		if(	strGubun == "5")	
		{
			strJuTime.Format("%s", pstrData);	pstrData += 8;
			memcpy(pBuf+278, (LPSTR)(LPCTSTR)strJuTime, 8);
		}

		lTemp = atoi(strCheDanga1);								//ljj 20070129 체결단가를 현재가에 넣음
		lTemp = htonl(lTemp);
		memcpy(pBuf+168, &lTemp, 4);							//현재가(4)

		memcpy(pBuf+173, "       ", 7);							//Filler(7)

		for(int nP = 180; nP < 279; nP++)	//데이터 길이를 맞춘다.
			memcpy(pBuf+nP, " ", 1);

		//KJI 20070418 (신용관련 추가)
		memcpy(pBuf+286, (LPSTR)(LPCTSTR)pstrData, 1);	pstrData += 1;
		memcpy(pBuf+287, (LPSTR)(LPCTSTR)pstrData, 8);	pstrData += 8;
		memcpy(pBuf+295, (LPSTR)(LPCTSTR)pstrData, 1);	pstrData += 1;
		memcpy(pBuf+296, (LPSTR)(LPCTSTR)pstrData, 8);	pstrData += 8;
		memcpy(pBuf+304, (LPSTR)(LPCTSTR)pstrData, 1);	pstrData += 1;
		memcpy(pBuf+305, (LPSTR)(LPCTSTR)pstrData, 1);	pstrData += 1;
		memcpy(pBuf+306, (LPSTR)(LPCTSTR)pstrData, 10);	pstrData += 10;
		memcpy(pBuf+316, (LPSTR)(LPCTSTR)pstrData, 1);	pstrData += 1;	//KJI 20070518

		pBuf[317] = NULL;	//KJI 20070518

		::PostMessage(m_pDBMgr->GetWindow(), WMU_REALDATA_POST, (WPARAM)PID_CHEKYOUL, (LPARAM)pBuf);	
		
		if( strGubun == "1")										// 체결일때
			pConclusion->Add(strCheQuant + "주");				// 체결수량(4)		
		else													// 정정,취소,거부일때
			pConclusion->Add(strQuant + "주");					// 주문수량(4)		
		
		if( strGubun == "3")										// 취소일때 - 단가가 필요없다.
			pConclusion->Add(" ");
		else if( strGubun == "1")								// 체결일때
			pConclusion->Add(strCheDanga + "원");				// 체결단가(4)		
		else												
			pConclusion->Add(strDanga + "원");					// 정정,취소,거부일때

		strNum = "<" + strNum + ">";		
		pConclusion->Add(strNum);
	}
	else if (strTrCode == "CN996Q00")  //선물옵션 체결통보 
	{
		pConclusion->Add(strFlag);				//시장구분을 넣어둔다.
		pConclusion->Add(strGubun);				//주문구분을 넣어둔다.		//shc 20030930

		memcpy(pBuf+10, pstrData, 16);
		CString strDataName(pstrData, 16);	pstrData += 16;		// 데이타명(16)
		strDataName.TrimLeft();
		strDataName.TrimRight();
		pConclusion->Add(strDataName);

		memcpy(pBuf+26, pstrData, 11);
		CString strAccount(pstrData, 11);	pstrData += 11;		// 계좌번호(11)
		pConclusion->Add(strAccount);

		memcpy(pBuf+37, pstrData, 16);	pstrData += 16;			//계좌명(16)

		memcpy(pBuf+53, pstrData, 10);
		CString strNum(pstrData, 10);		pstrData += 10;		// 주문번호(10)
		strNum.TrimRight(); 
		strNum.Format("%d", atoi(strNum));

		memcpy(pBuf+63, pstrData, 10);	pstrData += 10;			//원주문번호(10)

		CString strSFlag(pstrData, 1);
		memcpy(pBuf+73, pstrData, 1);	pstrData += 1;			// 스프레드 구분(1)

		memcpy(pBuf+74, pstrData, 12);	pstrData += 15;			//종목코드(12)

		memcpy(pBuf+86, pstrData, 20);
		CString strJongmok(pstrData, 20);	pstrData += 20;		// 종목명(20)
		strJongmok.TrimLeft(); 
		strJongmok.TrimRight();
		pConclusion->Add(strJongmok);

		memcpy(pBuf+106, pstrData, 4);
		CString strSaleBuy(pstrData, 4);	pstrData += 4;		// 매매구분(4)
		pConclusion->Add(strSaleBuy);

		//KJI 20040219
	//	memcpy(pBuf+110, "  ", 2);								//주문구분(2)

		CString strQuant(pstrData, 8);
		lTemp = atoi(strQuant);
		strQuant.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+112, &lTemp, 4);		pstrData += 8;		// 주문수량(4)

		CString strDanga(pstrData, 9);
		lTemp = atoi(strDanga);
		strDanga.Format("%0.2f", atof(strDanga)/100);
		lTemp = htonl(lTemp);
		memcpy(pBuf+116, &lTemp, 4);		pstrData += 9;		// 주문단가(4)

		CString strCheQuant(pstrData, 8);
		lTemp = atoi(strCheQuant);
		strCheQuant.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+120, &lTemp, 4);		pstrData += 8;		// 체결수량(4)

		CString strCheDanga(pstrData, 9);

		CString strCurPrice1;
		strCurPrice1 = strCheDanga;				//ljj 20070103 현재가에 체결단가를 넣기위해서

		lTemp = atoi(strCheDanga);
		strCheDanga.Format("%0.2f", atof(strCheDanga)/100);
		lTemp = htonl(lTemp);
		memcpy(pBuf+124, &lTemp, 4);		pstrData += 9;		// 체결단가(4)

		CString strTemp(pstrData, 8);
		lTemp = atoi(strTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+128, &lTemp, 4);		pstrData += 8;		//총체결수량(4)

		CString strTemp1(pstrData, 9);
		lTemp = atoi(strTemp1);
		lTemp = htonl(lTemp);
		memcpy(pBuf+132, &lTemp, 4);		pstrData += 9;		// 평균체결단가(4)

		CString strTemp2(pstrData, 8);
		lTemp = atoi(strTemp2);
		lTemp = htonl(lTemp);
		memcpy(pBuf+136, &lTemp, 4);		pstrData += 8;		// 미체결수량(4)

		memcpy(pBuf+140, pstrData, 8);		pstrData += 8;		// 정정취소구분(8)

		//KJI 20070810 (부적격사유코드)
		pstrData += 8;
		CString strUnAcceptCode(pstrData, 2);	pstrData += 2;	//KJI 20070810
		pstrData += 39;											//Skip(39)
		
		CString strTemp3(pstrData, 8);							
		lTemp = atoi(strTemp3);
		lTemp = htonl(lTemp);
		memcpy(pBuf+148, &lTemp, 4);		pstrData += 8;		// 실질수량(4)

		CString strTemp4(pstrData, 9);							
		lTemp = atoi(strTemp4);
		lTemp = htonl(lTemp);
		memcpy(pBuf+152, &lTemp, 4);		pstrData += 9;		// 매입단가(4)

		memcpy(pBuf+156, pstrData, 12);		pstrData += 12;		// 미결제약정금액(12)
		
		if(strSFlag == "1")	//Spread 이면 처리
		{
			pstrData += 1;										//Filler(1)

			SprBuf = new BYTE[1024];
			memcpy(SprBuf, pBuf, 313);	//KJI 20070518(신용추가로 변경)

			//--> ljj 20070103 현재가영역에 위에서 구해온 체결단가를 넣음
			lTemp = atoi(strCurPrice1);
			lTemp = htonl(lTemp);
			memcpy(SprBuf+168, &lTemp, 4);	pstrData += 9;	//현재가2
			//<----

			memcpy(SprBuf+74, pstrData, 12);	pstrData += 15;	//종목코드

			memcpy(SprBuf+86, pstrData, 20);	pstrData += 20;	//종목명

			memcpy(SprBuf+106, pstrData, 4);	pstrData += 4;	//매매구분

			CString strTemp6(pstrData, 8);
			lTemp = atoi(strTemp6);
			lTemp = htonl(lTemp);
			memcpy(SprBuf+112, &lTemp, 4);	pstrData += 8;	//주문수량

			CString strTemp7(pstrData, 9);							
			lTemp = atoi(strTemp7);
			lTemp = htonl(lTemp);
			memcpy(SprBuf+152, &lTemp, 4);	pstrData += 9;	// 매입단가(4)

			memcpy(SprBuf+156, pstrData, 12);	pstrData += 12;	// 미결제약정금액(12)

			pstrData += 1;										// Filler(1)

			//KJI 20070417
			CString strJGubun(pstrData, 1);
			memcpy(SprBuf+110, strJGubun, 2);	pstrData += 1;	// 주문구분(1)

			memcpy(SprBuf+172, " ", 1);						//체결구분(1)

			memcpy(SprBuf+173, strUnAcceptCode, 2);	//KJI 20070810
			memcpy(SprBuf+175, "     ", 5);			//KJI 20070810 (Filler 7->5)

			for(int nP = 180; nP < 279; nP++)	//데이터 길이를 맞춘다.
				memcpy(SprBuf+nP, " ", 1);

			memcpy(SprBuf+278, "        ", 8);				// 주문시간(8) ljj 20060530

			//KJI 20070418 (신용관련 추가)
			memcpy(SprBuf+286, "  ", 1);		
			memcpy(SprBuf+287, "        ", 8);	
			memcpy(SprBuf+295, " ", 1);			
			memcpy(SprBuf+296, "        ", 8);	
			memcpy(SprBuf+304, " ", 1);			
			memcpy(SprBuf+305, " ", 1);			
			memcpy(SprBuf+306, "           ", 10);
			memcpy(SprBuf+316, " ", 1);	//KJI 20070518

			SprBuf[317] = NULL;	//KJI 20070518

			::PostMessage(m_pDBMgr->GetWindow(), WMU_REALDATA_POST, (WPARAM)PID_CHEKYOUL, (LPARAM)SprBuf);
		}
		else
			pstrData += 79;	//KJI 20051101

		//KJI 20051101 
		CString strJGubun(pstrData, 1);
		memcpy(pBuf+110, strJGubun, 2);	pstrData += 1;

		lTemp = atoi(strCurPrice1);
		lTemp = htonl(lTemp);
		memcpy(pBuf+168, &lTemp, 4);

		//KJI 20040219
		memcpy(pBuf+172, " ", 1);								//체결구분(1)
		memcpy(pBuf+173, strUnAcceptCode, 2);	//KJI 20070810
		memcpy(pBuf+175, "     ", 5);			//KJI 20070810 (Filler 7->5)

		for(int nP = 180; nP < 279; nP++)	//데이터 길이를 맞춘다.
			memcpy(pBuf+nP, " ", 1);

		memcpy(pBuf+278, "        ", 8);						// 주문시간(8) ljj 20060530

		//KJI 20070418 (신용관련 추가)
		memcpy(pBuf+286, "  ", 1);
		memcpy(pBuf+287, "        ", 8);
		memcpy(pBuf+295, " ", 1);		
		memcpy(pBuf+296, "        ", 8);
		memcpy(pBuf+304, " ", 1);		
		memcpy(pBuf+305, " ", 1);		
		memcpy(pBuf+306, "          ", 10);		
		memcpy(pBuf+316, " ", 1);	//KJI 20070518

		pBuf[317] = NULL;	//KJI 20070518
		
		::PostMessage(m_pDBMgr->GetWindow(), WMU_REALDATA_POST, (WPARAM)PID_CHEKYOUL, (LPARAM)pBuf);	

		if( strGubun == "1")										// 체결일때
			pConclusion->Add(strCheQuant + "계약");				// 체결수량(4)		
		else													// 정정,취소,거부일때
			pConclusion->Add(strQuant + "계약");					// 주문수량(4)		
		
		if( strGubun == "3")										// 취소일때 - 단가가 필요없다.
			pConclusion->Add(" ");
		else if( strGubun == "1")								// 체결일때
			pConclusion->Add(strCheDanga + "pt");				// 체결단가(4)		
		else												
			pConclusion->Add(strDanga + "pt");					// 정정,취소,거부일때

		strNum = "<" + strNum + ">";		
		pConclusion->Add(strNum);
	}

	return pConclusion;
*/
}

long CCommMain::OnRemoveCommApiCheck(WPARAM wParam, LPARAM lParam)
{
	if ( m_pArrCommApiWnd->GetSize() == 0 )
	{
//// --> [Edit]  강지원 2010/12/20
////#ifdef	_DEBUG
//		// 임시
//		CString strMsg = "";
//		strMsg.Format("핸들이 없다. 종료하자...");
//		AfxMessageBox(strMsg);
////#endif
//// <-- [Edit]  강지원 2010/12/20

		//ASSERT(m_pTcpSocket);
		//if (m_pTcpSocket)
		//	m_pTcpSocket->DisConnectTCPSocket();

		HostDisconnect();

		m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CLOSED);
		SendSocketNotifyToAllCommApi(SOCKET_CLOSED);
		m_pParentWnd->PostMessage(WM_COMMS_PROGRAM_CLOSE, 0, 0);

		KillTimer(m_nWndCheckTimer);
		m_nWndCheckTimer = 0;
	}	

	return 0L;
}
