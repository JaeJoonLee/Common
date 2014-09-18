// D:\��ȭ����\�ҽ�\src\Common\CommMain.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CommMain.h"
#include "complzo.h"
#include "PacketMngr.h"

#include "../TrDll/CheJanStruct.h"

// �ӵ� �������� �۷ι���...
//BYTE g_pbySendEncrypTemp;		// Encryption Buffer
//BYTE* g_pbySendCompressTemp;	// Compress Buffer

// CommApi���� ��Ż��¸� �˷��ֱ� ���� �޼��� ����
extern UINT g_uSocketNotifyMsg;

UINT		g_unAbnormalPacketCount = 0;

#define		MAX_COMM_SIZE			8192

#define		UM_WNDCHECKTIMER		100
#define		DEF_WINDOW_CHECK_TIME	20000			//	30�� ������ üũ�Ѵ�.
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
	m_pTcpSocket			= NULL;		// ���� �ʱ�ȭ
	m_pCtx					= NULL;

//	m_nReConnect			= 0;		// ������ ��û ����
	m_nPollTime				= 0;		// ���� üũ��
	m_bConnect				= FALSE;	// ������� ��
	m_nRetryCount			= 1;		// �� ���� ��
	m_bConnectSubPort		= FALSE;	// sub port�� ���� �ΰ�
	m_nSignOn				= 0;		// �α׿� ���� (0:�� �α׿�,1: �α׿� �Ϸ�, 2: �����Ϸ�)
	m_nRetryConnectTimer	= 0;		// �� ���� Ÿ�̸� ���̵� 
	m_nOneSecondTimer		= 0;		// 1�� Ÿ�̸� (RQ/RP Ÿ�Ӿƿ�üũ)
	m_bColsolCreate			= FALSE;	// Consol���� ����
	m_bReadSizeDsp			= 0;		// CommsDbg�� ���ŵ����� ������ ǥ�� ����
	m_bUseCompress			= TRUE;
	
	m_bToBPServer			= FALSE;	// BP ���� ��������

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

	ON_MESSAGE(UM_LOG_CONSOL,			OnSetWriteConsol)	// consol�� �α� ��� �ϱ� ����
	ON_MESSAGE(UM_LOG_COMS_DBG,			OnCommsDbgLog)		// ComsDbg�� �α׸� ��� �ϱ� ����
	ON_MESSAGE(UM_DATA_RECEIVE,			OnDataReceive)		// ���� �Ϸ� ��Ŷ ó���� ����
	ON_MESSAGE(UM_WND_STATE_CHECK,		OnRemoveCommApiCheck)// CommApi üũ�� �����ִ� CommApi�� ������� �����ϴ� �޽���

END_MESSAGE_MAP()


void CCommMain::SetCommsDbgWndHandle(HWND hCommsDbgWnd)
{
	m_hCommsDbgWnd = hCommsDbgWnd;
	m_RequestDataObList.m_hCommsDbg = m_hCommsDbgWnd;
}
// CCommMain �޽��� ó�����Դϴ�.


int CCommMain::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
SetWriteLog("====================================");
SetWriteLog("========= (���� ���� ����) =========");
SetWriteLog("====================================");

	// ����Ÿ ���� �޸� �Ҵ� 
	m_pSendPacket		= new BYTE[MAX_PACKET_SIZE];

	// �ڽ��� ������ �ڵ��� �����Ѵ�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void CCommMain::OnTimer(UINT_PTR nIDEvent)
{
	// �� ���� Ÿ�̸��� ��� 
	if (nIDEvent == m_nRetryConnectTimer)
	{
		if (m_nRetryConnectTimer)
		{
			KillTimer(m_nRetryConnectTimer);
			m_nRetryConnectTimer = 0;
		}

		if (m_bConnect)
		{
			// ������ Ƚ��
			m_nRetryCount = 0;
		}
		else
		{
// --> [Edit]  ������ 2011/04/12 ( ������ ���� )
			m_pTcpSocket->DisConnectTCPSocket();
			RetryConnectToServer(0);

			//KJI 20110516
			if (m_nRetryCount != 0 || m_nTotalRetryCount != 0 )
			{
				// ���� �õ� �ϱ�
				HostConnect();
			}	
// <-- [Edit]  ������ 2011/04/12
		}
	}
	// RQ/RP äũ
	else if (nIDEvent == m_nOneSecondTimer)
	{
		////////////////////// Time outó�� ///////////////////
		m_RequestDataObList.DecreaseTimer(m_hCommsWnd, FALSE);
					
		////////////////////// ���� üũ ////////////////////
		m_nPollTime++;
		// 180 = 60 * 3 : 3�е��� ������ �ۼ����� ���ٸ�...
		if (m_nPollTime > POLLING_CHECK_INTERVAL)
		{
			char cCommandId;
			// BP ���� ������ ���
			if (m_bToBPServer)
				cCommandId	= (BYTE)PID_BP_POLLING;
			else
				cCommandId	= (BYTE)PID_POLLING;
			CPacketMngr PacketMngr;
			PacketMngr.SendCopyData(GetSafeHwnd(), cCommandId, NULL, 0);

			m_nPollTime = 0;			// ���� üũ��
		}
	}
	// Ű ��ȯTimeOut�߻� 
	else if (nIDEvent == m_nKeyChangeTimer)
	{
		KillTimer(m_nKeyChangeTimer);
		m_nKeyChangeTimer = 0;
		
		// �� ȭ������ Ÿ�Ӿƿ� �߻��� �����Ѵ�.
		SendSocketNotifyToAllCommApi(LOGIN_FAIL);
	}
// --> [Edit]  ������ 2010/12/19
	// Commapi�� ������ ����Ǿ����� ��Ÿ���� �����Ѵ�.
	else if (nIDEvent == m_nWndCheckTimer)
	{
		// ComApi�� ������........
		HWND hCommAPIWnd = NULL;
		long lRet;
		BOOL bFlag = FALSE;

//// --> [Edit]  ������ 2010/12/20
////#ifdef	_DEBUG
//		// �ӽ�
//		CString strMsg = "";
//		strMsg.Format("�ڵ� ����.. %d", m_pArrCommApiWnd->GetSize());
//		AfxMessageBox(strMsg);
////#endif
//// <-- [Edit]  ������ 2010/12/20

		for (int nCnt = m_pArrCommApiWnd->GetSize() - 1; nCnt >= 0; nCnt--)
		{
			hCommAPIWnd = (HWND)(*m_pArrCommApiWnd)[nCnt];

			if (!::IsWindow(hCommAPIWnd))
			{
//// --> [Edit]  ������ 2010/12/20
////#ifdef	_DEBUG
//				// �ӽ�
//				CString strMsg = "";
//				strMsg.Format("�ڵ� ����... %x", hCommAPIWnd);
//				AfxMessageBox(strMsg);
////#endif
//// <-- [Edit]  ������ 2010/12/20

				m_pArrCommApiWnd->RemoveAt(nCnt);
				PostMessage(UM_WND_STATE_CHECK);
			}
		}
	}
// <-- [Edit]  ������ 2010/12/19

	

	CWnd::OnTimer(nIDEvent);
}

long CCommMain::OnCopyData(UINT wParam, long lParam)
{
	BOOL	bDataDelete	= FALSE;
	int		nKind		= LOWORD(wParam);
	BOOL	bReturn;
	long	lRet;
	lRet = (long)REQUEST_SUCCESS;

	// ������ �����ڸ� ����Ѵ�.
	// CommsDbg�� �����͸� ǥ���Ѵ�.
	PCOPYDATASTRUCT pcds	= (PCOPYDATASTRUCT)lParam;
	HWND hCommApi			= (HWND)pcds->dwData;	// CommApi������ �ڵ�
	long nBufLen			= pcds->cbData;			// ������ ���� = RQ_COMMINFO_SIZE + body
	int nBodyLen;		// body
	int nSendDataSize;	// ��� + body
	int nHeaderSize;

	COMMONHEADER* pCommonHeader;	// �������

	// �α׸� ����� ����.. �����δ� ���� ���� �ʴ´�.
	if (nKind == DATAKIND_COMM_DEBUG)
	{
		WORD	wDataGubun  = HIWORD(wParam);	// ������ ������
		SendToDebugWindow(m_hCommsDbgWnd, nBufLen, pcds->lpData, wDataGubun);
		return REQUEST_SUCCESS;
	}
	
	// ����� ���� �Ǿ� �ִ� �����ΰ�?
	if (!m_bConnect)
		return REQUEST_ERROR_NOTCONNECT;

	REQUEST_COMMINFO* pRqCommInfo;
	BYTE *pData;
	pRqCommInfo	= (REQUEST_COMMINFO*)pcds->lpData;
	pData		= (((BYTE*)pcds->lpData) + RQ_COMMINFO_SIZE);
	nBodyLen	= nBufLen - RQ_COMMINFO_SIZE;
	
	/////////////////////////////////// ������� ����� //////////////////////////////////
	// TR �� ��� TR ����� �߰� �ؾ� �Ѵ�.
	if (pRqCommInfo->cMsgId == DM_RQ_ID && pRqCommInfo->TrHeader.nDataheader != NO_TR_HEADER)
		nHeaderSize = HEADER_SIZE;
	// TR �ƴ� ���
	else
		nHeaderSize = COMMON_HEADER_SIZE;
	
	nSendDataSize = nHeaderSize + nBodyLen;
	// ��ü send �� ������
	BYTE* pSendPacket = new BYTE[nSendDataSize];
	memset(pSendPacket, 0x00, nSendDataSize);
	// ���� ���
	pCommonHeader = (COMMONHEADER*)pSendPacket;
	// body
	memcpy(pSendPacket + nHeaderSize, pData, nBodyLen);

	// Common Header - SIZE_DEF_PACKET(nPacketLen ����) + Tr Header + body
	pCommonHeader->ulPacketLen	= htonl(nHeaderSize - SIZE_DEF_PACKET + nBodyLen);
	// �������� pCommonHeader->ulRqId ���� �ٸ� �뵵�� ����ϰ� �־
	// pCommonHeader->ulWinHwnd�� pRqCommInfo->cRqId�� �ִ´�.
	pCommonHeader->ulRqId		= pRqCommInfo->cRqId;
	pCommonHeader->ulWinHwnd	= pRqCommInfo->cRqId;
	pCommonHeader->cCommandId	= pRqCommInfo->cCommandId;
	
	// bit���� ó��
	// ���� | ��ȣȭ | �̻�� | ���� �� ����� ū ��� | packet���� | packet���� | packet�� | 0x01
	pCommonHeader->cCpFlag = 0x00;
	// �α����� ��ȣȭ�� ����
	if (pCommonHeader->cCommandId != PID_CONNECT &&
		pCommonHeader->cCommandId != PID_PLOT_CONNECT)	//KJI 20120206 (�������� ����ó��)
	{
		// ��ȣȭ ����.
		if (pRqCommInfo->TrHeader.ucEncrypt == '1' && m_pCommsConfig->m_bUseEncrypt)
			pCommonHeader->cCpFlag |= FLAG_ENCRYPT;
	}

	// ���� flag
	pCommonHeader->cErrComm		= '0';
	// ������ ����
	pCommonHeader->cServerType	= pRqCommInfo->cJobChk[0];

	/////////////////////////////////////// TR ��û�� ��� ///////////////////////////////////////
	if (pRqCommInfo->cMsgId == DM_RQ_ID)
	{
		BOOL bAddRequest = TRUE;
	
		// ������ �ʿ� ���� ���....
		if (pRqCommInfo->TrHeader.nRqID == MINOR_AS_LOGIN_DATA ||	// �α������� �뺸 ����
			pRqCommInfo->TrHeader.nRqID == MINOR_SETPUBLIC_KEY)		// �������� �����ΰ��� ������ ������ ����.
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

				return 6L; // �޸� ����
			}
			// HWND, MinorID ��Ʈ
			pRequestData->m_ulWinHwnd		= (long)pRqCommInfo->hRQRPWnd;
			pRequestData->m_ulRqId			= pRqCommInfo->cRqId;				// ComApi���� �ο��� RqId
			pRequestData->m_hCommAPIWnd		= (HWND)hCommApi;					// CommApi window Handle
			pRequestData->m_wOriginTimeOut	= pRqCommInfo->TrHeader.nTimeOut;	// Time Out
			pRequestData->m_wLeftTimeOut	= pRqCommInfo->TrHeader.nTimeOut;	// Time Out
			pRequestData->m_nSize			= 0;								// �ʱ� Receive������ �ʱ�ȭ
			pRequestData->m_lpData			= NULL;								// Receive Buf�ʱ�ȭ
			pRequestData->m_bFirstPacket	= FALSE;
			memcpy(pRequestData->m_ucTrCode, pRqCommInfo->cTrCode, TRCODE_SIZE);

			// ComApi���� ���� ������ RqId
			strWndSeqID.Format("%04d", pRqCommInfo->cRqId);		
			m_RequestDataObList.AddData(strWndSeqID, pRequestData);
		}

		// TR����� �ִ� ���
		if (pRqCommInfo->TrHeader.nDataheader != NO_TR_HEADER)
		{
			// Tr ���
			TRHEADER* pTrHeader	= (TRHEADER*)(pSendPacket + COMMON_HEADER_SIZE);
		
			///////////////////////////////////// TR ��� /////////////////////////////////
			memcpy(pTrHeader->cTRCode, pRqCommInfo->cTrCode, sizeof(pRqCommInfo->cTrCode));
			pTrHeader->cBenefit		= pRqCommInfo->cBenefit;		// �������ǿ���(Y:��������, N:�ƴ�)
			pTrHeader->cNextPrev	= pRqCommInfo->cContChk[0];		// TR��ȸ�� ����/������ ǥ���ϴ°�,
											// SERVER: ����, ���� ��ư enable ����
											// CLIENT: ����, ���� data ��û(data �׸� �ʿ�� �����ڵ带 �ø���)
											// 0:���� Disable, 1:��Enable, 2:��Enable, 3:����Enable
											// �ɼ� data�� ���� ��� : �ɼ� data ������ �´�(���� ���� key data��)
											// �ɼ� data�� ���� ��� : data �κп� �´�.
			
			pTrHeader->cTrErrorFlag = '0';	// '0':����, '1':���� ==> �޼���code�� pc���� ���
											// '2':����, '3':���� ==> Data �κп� 80 Byte�� �޼��� ���[MSG(80 Byte) + Data]
			pTrHeader->ulTrBodySize = htonl(nBodyLen);	// C->S(�ɼǱ���:�������� key data�� ���� ��쵵 ����)
											// S->C(�������� ��ü data ����)

			pTrHeader->cErrCode[0]	= pRqCommInfo->cJobChk[0];	// �����ڵ� ù��°�� ������ ����(���� ����)�� �ִ´�.
			memcpy(pTrHeader->cErrCode + 1, pRqCommInfo->sSCRN, 4);		
		}		
	}
	// ������ ����
	bReturn = fnSend(pSendPacket, nSendDataSize, pRqCommInfo->cMsgId);

	if (pSendPacket != NULL)
		delete[] pSendPacket;

	return lRet;
}

//******************************************************************
//  Function Name : OnSocketNotify
//  Function      : ���Ͽ��� ���ϻ��� ������ ����ؼ� ó���ϴ� �Լ�
//  Param         : WPARAM wParam, LPARAM lParam
//					WPARAM wParam		���Ϲ�ȣ 
//					LPARAM lParam		�ΰ����� 
//  Return        : long 
//  Create        : 
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
long CCommMain::OnSocketNotify(WPARAM wParam, LPARAM lParam)
{
	CString strMsg;
	int nSocket = (int)wParam;
	
	// ���� ���� �ڵ带 ����Ѵ�.
	int nErrorCode = WSAGETSELECTERROR(lParam);
	switch (WSAGETSELECTEVENT(lParam))
	{
		case FD_CONNECT:			// ���Ͽ���
		case FD_CONNECT_SUCCESS:	// ���Ͽ��� ����
		{
			if (nErrorCode == 0)
			{
// --> [Edit]  ������ 2011/04/12 ( ������ ���� )
				if (m_nRetryConnectTimer)
				{
					KillTimer(m_nRetryConnectTimer);
					m_nRetryConnectTimer = 0;
				}
// <-- [Edit]  ������ 2011/04/12

//---->	//KMG 2012.06.19 ������Ʈ���� : ip������ ����ϱ����� ����
				if( m_pTcpSocket->GetHostPort() == m_pCommsConfig->m_nSubPort )
					m_pCommsConfig->m_bUseSubPort = TRUE;
				else	m_pCommsConfig->m_bUseSubPort = FALSE;
//<---

				m_bConnect = TRUE;
				// ���� Read�� Thread�� �ۼ��Ѵ�.
				m_pTcpSocket->CreateSocketReadThread();
			}
			else
			{
				m_bConnect = FALSE;
				m_pTcpSocket->DisConnectTCPSocket();

				//KJI 20110523 (���� �ٷ� ���Ͻ� ó��)
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
					// ���� �õ� �ϱ�
					HostConnect();
				}
//				RetryConnectToServer(nErrorCode);
			}
			break;
		}
		// ���Ͽ��� ���� 
		case FD_CONNECT_FAIL:
		{
			m_bConnect = FALSE;

			//KJI 20110523 (���� �ٷ� ���Ͻ� ó��)
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
				// ���� �õ� �ϱ�
				HostConnect();
			}	
	
			break;
		}
		// ������ �۽� ���� 
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

				// Timeout üũ Ÿ�̸� �⵿
				if (m_nOneSecondTimer)
				{
					KillTimer(m_nOneSecondTimer); // 1�� Ÿ�̸� �����..
					m_nOneSecondTimer = 0;
				}
				m_nOneSecondTimer = SetTimer(UM_ONESECONDTIMER, 1000, NULL); // 1�� Ÿ�̸� �����Ѵ�..
			}

			if (m_hCommsDbgWnd)
				CommsDbgLog((LPSTR)(LPCTSTR)"@@@ [FD_WRITE] Socket Send Ready Ok...");
			
			SendSocketNotifyToAllCommApi(SOCKET_CONNECTED);	// ����� ����Ǿ����� �˸���.
			break;
		}
		// ������������ ������ ���
		case FD_CLOSE:
		{
			m_bConnect = FALSE;

			Sleep(1000);
			m_nSignOn  = -1;	// �α��� ���¸� �ʱ�ȭ �Ѵ�.

			ASSERT(m_pTcpSocket);
			if (m_pTcpSocket)
				m_pTcpSocket->DisConnectTCPSocket();

			m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CLOSED);
			SendSocketNotifyToAllCommApi(SOCKET_CLOSED);
		
			if (m_pCommsConfig->m_bLogWrite)	// �α� �ۼ� 
			{
				CString strSocketMsg;
				strMsg = "Comms,OnSocketNotify SOCKET_CLOSED ,%d,%s";
				WriteLogMsg( strMsg , strSocketMsg, (DWORD)nErrorCode);

				CommsDbgLog((LPSTR)(LPCTSTR)strSocketMsg );
			}

			if (m_hCommsDbgWnd)
			{
				CString strText;
				strText.Format(" @@@ [FD_CLOSE] ����� ���� �Ǿ����ϴ�... ErrorCode=[%d]", nErrorCode );
				CommsDbgLog((LPSTR)(LPCTSTR)strText);
			}

			break;
		}
	}
	return 0L;
}

//*****************************************************************************
// ��    ƾ    ��  :  HostConnect
// ��          ��  :  ���Ӽ����� ���� ������ �����Ѵ�.
// ��          ��  :  ���� 
// ��          ��  :  BOOL
//						TRUE: ���� �Ϸ�, FALSE:���� ����
// ��    ��    ��  :  
// ��  ��  ��  ��  :  
//*****************************************************************************
BOOL CCommMain::HostConnect(BOOL bInitThread)
{	
	ASSERT(m_hCommsWnd);

	// �̹� ���ӵ� �����ΰ��� üũ�Ѵ�.
	if (m_bConnect)
		return TRUE;
	else
// --> [Edit]  ������ 2011/04/12 ( ������ ���� )
		m_nRetryConnectTimer = SetTimer(UM_RECONNECT_TIMER, m_pCommsConfig->m_nKeyChangeTimeOut * 1000, 0);	
// <-- [Edit]  ������ 2011/04/12

	if (m_nOneSecondTimer)
	{
		KillTimer(m_nOneSecondTimer);	// 1�� Ÿ�̸� �����..
		m_nOneSecondTimer = 0;
	}

	if ( m_nWndCheckTimer == 0 )
	{
		m_nWndCheckTimer = SetTimer(UM_WNDCHECKTIMER, DEF_WINDOW_CHECK_TIME, NULL); // 30�� Ÿ�̸Ӹ� �����Ѵ�. ���߿� �ٲ���...
	}
	
	///////////////////////////////////////////////////
	// ������ �̹� ������ ����Ǿ� ������ �����ϰ�,
	// �ٽ� ������ �����Ѵ�.

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
	// ������ �ۼ��Ѵ�
	bRet = m_pTcpSocket->CreateTCPSocket();

	// ������ ������ �õ��Ѵ�.
	if (bRet)
		bRet = m_pTcpSocket->ConnectTCPSocket();
	else
		SetWriteLog((LPSTR)"Comms::CreateTCPSocket�Լ� Error...");
	
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
//  Function      : ���� ������ ������ �����ϴ� �Լ� 
//  Param         : ����
//  Return        : void 
//  Create        : 
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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
//  Function      : �ѹ��� ���� ũ��� ����Ÿ�� ������ ������.
//  Param         : AS_SOCK_PACKET* lpPacket, int nSendLen
//  Return        : BOOL 
//  Create        : �̿��� , 2008/04/08
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
BOOL CCommMain::fnSend(BYTE* lpPacket, int nSendLen, BYTE cMsgId)
{
	int		nSendBodySize		= nSendLen - COMMON_HEADER_SIZE;	// ���� ����Ÿ ����(���� ��� ����)
	BYTE*	lpSendBodyBuffer	=  lpPacket + COMMON_HEADER_SIZE;	// ���� ����Ÿ
	COMMONHEADER* pCommHeader	= (COMMONHEADER*)lpPacket;
	CString strTemp;
	int		nRetLen;
	int		nRet			= 0;
	int		nCTXState		= 0;
	BOOL	bInsertChain	= FALSE;
	
#ifdef _WRITE_LOG_TYPE_STARTER_
	// �α� ���� ���
	CString strLog;
	strLog = CString((char*)lpPacket, nSendLen);
	SetWriteLog(strLog);
#endif

	// ��ȣȭ �� ����Ÿ�� Dbg�� ������.(Polling�� ������ ����)
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
		// �α׿�
		case PID_CONNECT:
		case PID_PLOT_CONNECT:	//KJI 20120206 (�������� ����ó��)
			nCTXState = 5;
			break;				
		default:
			nCTXState = 6;
			break;
	}

	BYTE* pbySendCompressTemp	= NULL;
	BYTE* pbySendEncrypTemp		= NULL;
	
	///////////////////////////////// ���� üũ ///////////////////////////////
	// body�� ���̰� 4k�� ������ ����(��ȣȭ�� ����, Chain ��� �߰�, ���� ����)
	// TR�� ��츸 ���� �Ѵ�.
	if (nSendBodySize > COMPRESS_STANDARD_SIZE)
	{
		ULONG ulBodySize;
		pbySendCompressTemp = new BYTE[nSendBodySize * 2];	// �켱 2�� ũ��� ����......................
		memset(pbySendCompressTemp, 0x00, sizeof(pbySendCompressTemp));	//���� ����
		ulBodySize = htonl(nSendBodySize);
		memcpy(pbySendCompressTemp, &ulBodySize, 4);
		nRetLen = CompressLZO(lpSendBodyBuffer, pbySendCompressTemp + 4, nSendBodySize) + 4;
		if (nRetLen > 0)
		{
			// ���� ũ�Ⱑ ���� ��츸 �����ؼ� ������.
			if (nSendBodySize > nRetLen)
			{
				pCommHeader->cCpFlag |= FLAG_COMPRESS;
				lpSendBodyBuffer	= pbySendCompressTemp;
				nSendBodySize		= nRetLen;
			}
			// ���� �� ����� �� ū ��� ���� ���� ���� ������.
			else
			{
				pCommHeader->cCpFlag &= ~FLAG_COMPRESS;
				pCommHeader->cCpFlag |= FLAG_COMPRESS_FAILED;
			}
		}
		// ������ �ȵ� ���
		else
		{
			pCommHeader->cCpFlag &= ~FLAG_COMPRESS;
			pCommHeader->cCpFlag |= FLAG_COMPRESS_FAILED;
		}
		// ������ ������ ��ȣȭ ���Ѵ�.
		pCommHeader->cCpFlag &= ~FLAG_ENCRYPT;
		bInsertChain = TRUE;
	}
	
	////////////////////// ��ȣȭ üũ(�α����� ������ ��ȣȭ �Ѵ�) /////////////////////
	if (pCommHeader->cCpFlag & FLAG_ENCRYPT || pCommHeader->cCommandId == PID_CONNECT ||
		pCommHeader->cCommandId == PID_PLOT_CONNECT)	//KJI 20120206 (�������� ����ó��)
	{
		pbySendEncrypTemp = new BYTE[nSendBodySize + 1024];
		memset(pbySendEncrypTemp, 0x00, sizeof(pbySendEncrypTemp));
		// ����� ��ȣȭ ���� �ʴ´�.
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
		// ��ȣȭ ���� �� ���� ����.....................................................
		else
		{
			return FALSE;
			pCommHeader->cCpFlag &= ~FLAG_ENCRYPT;
		}
	}

	//////////////////// ���� ���۵� ����Ÿ //////////////////
	CLIENT_CHAIN_PKT Chain;
	int nHeaderSize;
	int nPacketCnt;		// ������ Data�� ȸ�� - 1
	int nRemainData;	// ������ ��Ŷ�� ������ ũ��
	
	// ���� ���
	memcpy(m_pSendPacket, pCommHeader, COMMON_HEADER_SIZE);
	pCommHeader = (COMMONHEADER*)m_pSendPacket;

	// ���� ����(2048 ������ ����)
	if (bInsertChain)
	{
		nPacketCnt	= nSendBodySize / MAX_SEND_SIZE;	// ������ Data�� ȸ�� - 1
		nRemainData	= nSendBodySize % MAX_SEND_SIZE;	// ������ ��Ŷ�� ������ ũ��
		
		if (nRemainData > 0)
			nPacketCnt++;
		nHeaderSize = COMMON_HEADER_SIZE + sizeof(CLIENT_CHAIN_PKT);
		// chain �� ����
		SYSTEMTIME tm;
		GetLocalTime(&tm);

		memset(&Chain, 0x00, sizeof(CLIENT_CHAIN_PKT));
		// Chain TR ���(TR ��� ũ�� - 3)
		memcpy(Chain.TrHeader, lpPacket + COMMON_HEADER_SIZE, CHAIN_TR_HEADER_SIZE);
		
		strTemp.Format("%d", nSendLen - COMMON_HEADER_SIZE);
		memcpy(Chain.cOrgSize, strTemp, strTemp.GetLength());		// ���� �� ũ��
	
		strTemp.Format("%d", nSendBodySize);
		memcpy(Chain.cCompressSize,	strTemp, strTemp.GetLength());	// ���� �� ũ��

		strTemp.Format("%d", MAX_SEND_SIZE);
		memcpy(Chain.cBlockSize, strTemp, strTemp.GetLength());		// send ����(2048)
		sprintf_s(Chain.cUniqID,		"%02d%02d%02d%03d%05d", tm.wHour,tm.wMinute,tm.wSecond,tm.wMilliseconds,rand());
	}
	// �ѹ� ����
	else
	{
		nPacketCnt = 1;
		nRemainData = nSendBodySize;
		nHeaderSize = COMMON_HEADER_SIZE;
	}

	int nSendSize;
	int nPacketIndex;
	int nOffset = 0;
	// ������ ��Ŷ�� ���� �ϰ� ����(chain�� �ִ� ����)
	for (nPacketIndex = 0; nPacketIndex < nPacketCnt - 1; nPacketIndex++) 
	{
//		pCommHeader->cCpFlag = 0x00;	//LJP 20110401 6698���� ����� �����÷��� �� �¾Ƽ� ������.
		// ó�� ��Ŷ
		if (nPacketIndex == 0)
			pCommHeader->cCpFlag |= FLAG_PACKET_BEGIN;
		// �߰� ��Ŷ
		else
		{
			// 2011.05.16 jhj 
			pCommHeader->cCpFlag &= ~FLAG_PACKET_BEGIN;
			pCommHeader->cCpFlag |= FLAG_PACKET_CONTINUE;
		}
		
		// chain �� ä���
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
			// ���� ó���Ұ�
		//	return FALSE;
		}
		
		nOffset += MAX_SEND_SIZE;
	}

	// ������ ��Ŷ ����
	// �������� �� ��Ŷ�� ��� ���࿩�θ� ��Ʈ�� �˻���ϴ� ��찡 �־ FLAG_PACKET_END�� ������ �ȵȴ�.
	// �������ݿ� ���� ���Ǹ��� ����� ������ �𸣰ڸ� ���� �ܸ��� ���̾�
	if (nPacketCnt > 1)
	{
		// 2011.05.16 jhj 
		pCommHeader->cCpFlag &= ~FLAG_PACKET_BEGIN;
		pCommHeader->cCpFlag &= ~FLAG_PACKET_CONTINUE;

		pCommHeader->cCpFlag |= FLAG_PACKET_END;
	}
	
	// ���� ������ �ƴ� ���� nRemainData�� 0�� �� �ִ�.(No body�� ����� ������ ��� ����)
	if ((bInsertChain && nRemainData > 0) || bInsertChain == FALSE)
	{
		// ���� ���� �� chain �� ä���
		if (bInsertChain)
		{
			// 2011.05.16 jhj �ʱ�ȭ �߰� . ��Ŷ������� 1000 ���� ������� Ŭ���� �����༭. 596 �� ��� 5968 �� ���۵Ǵ� ����������.!!!
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
			// ���� ó���Ұ�
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
//  Create        : �̿��� , 2007/05/22
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
long CCommMain::SendDataToServer (BYTE* lpData, int nSendLen, BYTE cMsgId, int nSendDbg)
{
	if (m_bConnect == FALSE || m_pTcpSocket == NULL)
		return FALSE;

	if (nSendDbg)
	{
		// ��ȣȭ �� ����Ÿ�� Dbg�� ������.
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

	m_nPollTime = 0;			// ���� üũ��

	return nRet;
}

//******************************************************************
//  Function Name : DataReceive
//  Function      : ����Ÿ ���� ó��
//  Param         : BYTE* lpData, BOOL bFirst
//  Return        : void 
//  Create        : �̿��� , 2007/09/18
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
void CCommMain::DataReceive(BYTE* lpData, BOOL bFirst)
{
	m_nPollTime = 0;			// ���� üũ��

	int i;
	int nPacketLen;
	DWORD dwDataLen;

	COMMONHEADER* pCommonHeader = (COMMONHEADER*)lpData;
	nPacketLen	= ntohl(pCommonHeader->ulPacketLen);
	dwDataLen	= nPacketLen + SIZE_DEF_PACKET;
	
	if(nPacketLen > MAX_COMM_SIZE || nPacketLen < SIZE_DEF_PACKET)
		return;

	// (BP ���� ó������ �ʵ��� �Ѵ�.)
	if (m_pCommsConfig->m_bBccUse == TRUE)
	{
		// BCCüũ�� �������� 
		BYTE	ucBcc = 0;
		for (i = 0; i < (int)(dwDataLen - SZ_BCC_CHECKSUM); i++)
			ucBcc ^= lpData[i];

		if (ucBcc < 0x20)	// space�� �����ؼ� ���ڷ� �����.
			ucBcc += 0x20;

		if (ucBcc != (BYTE)lpData[dwDataLen - SZ_BCC_CHECKSUM])
		{	// �ǵ��� FF, CR, LF����
#ifdef _DEBUG
			CString strmsg;
			strmsg.Format("BCC CHECK ����[!0x%02X]", ucBcc);
			AfxMessageBox(strmsg);
#endif
			return;
		}
		// bcc ��ŭ�� ���̸� ����. 
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
	//	case AS_SISE_DATA:		//�ü�
	//		RcvPb((UCHAR*)lpData, dwDataLen);
	//		return;
	//	case AS_PUSH_DATA:		//�ֹ�ü��
	//		RcvPb((UCHAR*)lpData, dwDataLen);
	//		return;
		////////////////////// Xecure ��ȣó�� Command /////////////////////
		case PID_ENCCLIENTSET:
		case PID_ENCCLIENTSET_OLD:
		case PID_ENCCLIENTID:
		case PID_ENCCLIENTPWD:
		case PID_ENCXMINIT_SET:
			XecureReceive((UCHAR*)lpData, dwDataLen);
			return;
		// �������� ���� ������ Ŭ���Ʈ�� ������.
		case PID_REVERSION:
		{
			COPYDATASTRUCT    send_data;
			send_data.dwData	= DATAKIND_SERVER_PUSH;	// ������ ������ 
			send_data.cbData	= dwDataLen;			// ������ ���� 
			send_data.lpData	= lpData;
			// �α��� ComApi�� ������.
			if (m_hLoginCommApiWnd != NULL)
			{
				::SendMessage(m_hLoginCommApiWnd,
							  WM_COPYDATA,
							  (int)DATAKIND_SERVER_PUSH,
							  (LPARAM)&send_data);
			}
			return;
		}
		// �α���
		case PID_FILEDOWN:
		case PID_CONNECT:
		case PID_PLOT_CONNECT:	//KJI 20120206 (�������� ����ó��)
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
			strmsg.Format("[warning] ���ǵ��� ���� �޽��� ���� [Command Id = %d]", pCommonHeader->cCommandId);
			AfxMessageBox(strmsg);
			return;
		}
		*/
	}

	// ������ PID�� �� ó�� �ϰ� ������ ��� PID�� �ǽð� ����Ÿ�� ����.
	// ������ �ڵ��� ������ �ڵ��������� ����
	// RcvPb()���� ���ǵ��� ���� PID�� ������.
	if (pCommonHeader->ulWinHwnd == NULL)
		RcvPb((UCHAR*)lpData, dwDataLen);
	// �̰��� �ϴ� �̻��� ��Ŷ���� ����.
	else
		g_unAbnormalPacketCount++;
}



//******************************************************************
//  Function Name : RcvRp
//  Function      : ����Ÿ ���� ó�����Ѵ�.
//  Param         : BYTE* lpData, DWORD dwDataLen
//  Return        : void 
//  Create        : �̿��� , 2008/02/25
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
void CCommMain::RcvRp(BYTE* lpData, DWORD dwDataLen)
{
	COMMONHEADER* pCommHeader = (COMMONHEADER*)lpData;

#ifdef _DEBUG
	if (dwDataLen != ntohl(pCommHeader->ulPacketLen) + SIZE_DEF_PACKET)
	{
		AfxMessageBox("���� ����Ÿ ���̰� �̻���");
		return;
	}
#endif

	CString sWINIDSEQNO;
	ULONG ulRqId;
	// pCommHeader->ulRqId ��� nWindowId�� ����Ѵ�.
	// nPUniqueKey�� �������� �ٸ� �뵵�� ��� �ϰ� �־
	ulRqId = pCommHeader->ulWinHwnd;
	sWINIDSEQNO.Format("%04d", ulRqId);

	if ( ulRqId == 0 )
	{
		//	����ó�� ( �����ε� TRó�� ���� ��� )
		//----BP �������� ���� �ǽð� �����ʹ� ���������� �Ʒ�ó�� ó�� �ؾ� �Ѵ�
		// BP �������� ���� �ǽð� �����ʹ� �պκп� ���񽺸��� �ִ�.
		CString strRealType = "";
		CString strTrCode = CString((char*)lpData + COMMON_HEADER_SIZE, TRCODE_SIZE);
		int nOffSize = 0;

		// ü���뺸 (996Q-����/ 997Q-����)
		if (strTrCode == "CN996Q00" || strTrCode == "CN997Q00")
		{

			//	���� �̱ۿ��� ü���뺸 ���µ� Ÿ���� ���� �� �ʿ䰡 ������? �׳� HTS�� ������ Ÿ������ ������ �ɰ� ������...
//			strRealType.Format("%04d", PID_BP_CHEKYOUL);
			strRealType.Format("%04d", PID_CHEKYOUL);
//			DWORD nSendDataLen = (dwDataLen - HEADER_SIZE) + REAL_TYPE_SIZE;	// ComApi�� ���� ����Ÿ�� ���� = ���� Ÿ��(4) + ���� ����Ÿ

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
			//			DWORD nSendDataLen = (dwDataLen - HEADER_SIZE) + REAL_TYPE_SIZE;	// ComApi�� ���� ����Ÿ�� ���� = ���� Ÿ��(4) + ���� ����Ÿ

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

		// ��Ŷ�� ����, �߰��� �ƴϸ� ������ ��Ŷ���� ���� �Ѵ�.
		// �����ϴٸ��� ������ ���� ����� packet �� �Ѱ�¥�� packet ���� ���
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
//  Function      : Ʈ�� ���� ó���� �Ѵ�.
//  Param         : PVOID lpData, DWORD dwDataLen
//  Return        : BOOL 
//  Create        : �̿��� , 2008/02/25
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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

	// CommAPi�� �ڵ��� ��´�.
	HWND dwTempWnd = m_RequestDataObList.GetHwnd(sWINIDSEQNO);
	if (pRequestData->m_nSize <= 0 || pRequestData->m_lpData == NULL || dwTempWnd == NULL)
	{
		// IO���̺� �����Ѵ�.
		m_RequestDataObList.RemoveData(sWINIDSEQNO);
		return FALSE;
	}

	//////////////////// ���� ����, ��ȣȭ ó�� �Ѵ�. ////////////////////
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
	// ��������
	if (pCommHeader->cCpFlag & FLAG_COMPRESS)
	{
		TRY 
		{
			int nRealBodySize;
			bDataCheck = TRUE;
			// ������ ũ��
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

			// COMMONHEADER �� Body ���̿� 4����Ʈ�� ������ body���̸� ��Ÿ����.
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

	// ��ȣȭ
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
	
	// ���� �� ����� ū ���(���� ����)
	// CommonHeader ���� 4����Ʈ�� �پ� �ִµ� ���־� �Ѵ�.
	if (pCommHeader->cCpFlag & FLAG_COMPRESS_FAILED)
	{
		nBodySize -= 4;
		pbyReceiveData += 4;
	}

	// ComApi�� ���� ����Ÿ
	nSendDataSize = nBodySize + COMMON_HEADER_SIZE;
	
	pbySendData = new BYTE[nSendDataSize];
	
	COMMONHEADER* pCommHeaderTemp = (COMMONHEADER*)pbySendData;

	// ���� �Ǵ� ��ȣȭ �� ����Ÿ �� ���
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
	// ComApi���� ������ RqId�� �־��ش�.(�̰ɷ� ComApi�� map���� ã�´�)
	pCommHeaderTemp->ulRqId		= pRequestData->m_ulRqId;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// ���� �ڷḦ �ش� window �� �����Ѵ�.
	if (::IsWindow((HWND)dwTempWnd))
	{
		int nQueueSize;
		if (m_pTcpSocket != NULL)
			nQueueSize = m_pTcpSocket->GetQueueSize();

		COPYDATASTRUCT    send_data;
		send_data.dwData	= MAKELONG( LOG_RP, nQueueSize);				// RP�� 
		send_data.cbData	= nSendDataSize;		// ���� ������
		send_data.lpData	= (LPBYTE)pbySendData;	// ���� ����

		int lRet = ::SendMessage((HWND)dwTempWnd, 
								WM_COPYDATA, 
								DATAKIND_RQRP,

								(LPARAM)&send_data);

	//	TRACE("===\n ReleaseSendToCommApiWindow() RQID:%d====\n", pCommHeaderTemp->ulRqId);

	}

	// RP ������ Debug�� ����
	if (m_hCommsDbgWnd && ::IsWindow(m_hCommsDbgWnd))
		SendToDebugWindow(m_hCommsDbgWnd, nSendDataSize, pbySendData, LOG_RP);
	
	if (pbyDecompressTemp != NULL)
		delete[] pbyDecompressTemp;
	if (pbyDecryptTemp != NULL)
		delete[] pbyDecryptTemp;
	if (pbySendData != NULL)
		delete[] pbySendData;

	// IO���̺� �����Ѵ�.
	m_RequestDataObList.RemoveData(sWINIDSEQNO);
	
	return TRUE;
}

//******************************************************************
//  Function Name : RcvPb
//  Function      : ������� ó���� �Ѵ�
//  Param         : PVOID lpData, DWORD dwDataLen
//  Return        : void 
//  Create        : �̿��� , 2008/02/25
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : ����Ÿ ����: Common Header + body(record count����) size[4] + record count[4] + Rec * n
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
	// ���� ����(�ǽð� ����Ÿ�� ���� ���Ѵٰ� ��)
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

	memcpy(&nBodyLen,	lpRecvBody, 4);			// body����(���ڵ� ���� ���� �Ѵ�)
	memcpy(&nRecCount,	lpRecvBody + 4, 4);		// �ǽð� ���ڵ� ����
	nBodyLen	= ntohl(nBodyLen) - 4;			// ���ڵ� ���� �κ�(4)�� ����.
	nRecCount	= ntohl(nRecCount);

	if (nBodyLen <= 0)
		return;
	// ���ڵ� ������ �������̸� ��Ŷ�� ������.
	if (nRecCount <= 0)
		return;

	nRecSize	= nBodyLen / nRecCount;			// ���ڵ��� ����
	nSendDataLen = REAL_TYPE_SIZE + nRecSize;	// ComApi�� ���� ����Ÿ�� ���� = ���� Ÿ��(4) + ���� ����Ÿ
	
	if (nRecSize <= 0)
		return;

	// ���� ����Ÿ ����
	// Common Header + body size[4] + record count[4] + Rec * n
	BYTE* pPBData = new BYTE[nSendDataLen + 1];
	strRealType.Format("%04d", pCommHeader->cCommandId);	// �ǽð� Ÿ��
	memcpy(pPBData, strRealType, strRealType.GetLength());
	
	nOffset = nAdditionalSize;
	
	while (1)
	{
		// ����Ÿ ���̰� �̻��� ����
		// ���ڵ��� ���� ���� ������ ���� ����Ÿ�� �۰ų�,
		// ���ڵ��� ���� ���� ������ ���� ����Ÿ�� �� ���� �κ��� ������.
		if (nRecvDataSize - nOffset < nRecSize)
		{
			strTemp.Format("�ǽð� ����Ÿ ���� ������ : Ÿ��:%s, �������:%d, ��������:%d]",
													strRealType, nRecSize, nRecvDataSize - nOffset);
			CommsDbgLog((LPSTR)(LPCTSTR)strTemp);
			break;
		}

		// ���� 4����Ʈ�� ���� Ÿ��
		memcpy(pPBData + REAL_TYPE_SIZE, lpRecvBody + nOffset, nRecSize);

		if (!SendRealDataToCommApiWindow(pPBData, nSendDataLen))
			bAbnormalFlag = TRUE;

		nOffset += nRecSize;

		// CommonHeader�� ������ ����
		if (nOffset >= nRecvDataSize)
			break;
	}

	// ���ǵ��� ���� ��Ŷ�� ���� ����.
	if (bAbnormalFlag)
	{
		g_unAbnormalPacketCount++;
		strTemp.Format("���ǵ��� ���� ��Ŷ �� : %d[�ǽð� Ÿ��(PID):%s]", g_unAbnormalPacketCount, strRealType);
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
//  Function      : Ʈ�� �޼��� ó���� �Ѵ�.
//  Param         : PVOID lpData, DWORD dwDataLen
//  Return        : BOOL 
//  Create        : �̿��� , 2008/02/25
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
BOOL CCommMain::MsgSendToCommApiWindow(PVOID lpData, DWORD dwDataLen)
{
	int lRet = 0;
	
	COMMONHEADER* pCommHeader = (COMMONHEADER*)lpData;

	CString sWINIDSEQNO;
	ULONG ulRqId;
	// pCommHeader->ulRqId ��� nWindowId�� ����Ѵ�.
	// nPUniqueKey�� �������� �ٸ� �뵵�� ��� �ϰ� �־
	ulRqId = pCommHeader->ulWinHwnd;
	sWINIDSEQNO.Format("%04d", ulRqId);
	
	CRequestData* pRequestData = m_RequestDataObList.GetData(sWINIDSEQNO);
	if (pRequestData)
	{
		// CommAPi�� �ڵ��� ��´�.
		HWND dwTempWnd = m_RequestDataObList.GetHwnd(sWINIDSEQNO);
		if (dwTempWnd)
		{	
			// ���� �ڷḦ �ش� window �� �����Ѵ�.
			if (::IsWindow((HWND)dwTempWnd))
			{
				int nQueueSize;
				if (m_pTcpSocket != NULL)
					nQueueSize = m_pTcpSocket->GetQueueSize();

				COPYDATASTRUCT    send_data;
				send_data.dwData	= MAKELONG( DATAKIND_RQRP, nQueueSize);		// RP�� 
				send_data.cbData	= dwDataLen;			// ���� ������
				send_data.lpData	= lpData;				// ���� ����

				lRet = ::SendMessage((HWND)dwTempWnd,
									WM_COPYDATA,
									DATAKIND_MSG,
									(LPARAM)&send_data);
			}
		}
	}

	return TRUE;
}
// �ǽð� ����Ÿ�� ComApi�� �����Ѵ�.
BOOL CCommMain::SendRealDataToCommApiWindow(BYTE* pPBData, int nDataLen)
{
	// PB ������ Debug�� ����
	if (m_hCommsDbgWnd && ::IsWindow(m_hCommsDbgWnd))
		SendToDebugWindow(m_hCommsDbgWnd, nDataLen, pPBData, LOG_PB);
	
	// ComApi�� ������........
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
			send_data.dwData	= MAKELONG( LOG_PB, nQueueSize);			// ������ ������ 
			send_data.cbData	= (DWORD)nDataLen;	// ������ ���� 
			send_data.lpData	= pPBData;
					
			lRet = ::SendMessage( hCommAPIWnd, 
								  WM_COPYDATA, 
								  (int)DATAKIND_PB,
								  (LPARAM)&send_data);
			
			// lRet �� -1 �̸�� ��ϵ��� ���� ���� Ÿ���� ����.
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
//  Function      : ���� �ý��� ���� ���� ó��
//  Param         : PVOID lpData, DWORD dwDataLen
//  Return        : BOOL 
//  Create        : �̿��� , 2008/02/25
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
BOOL CCommMain::RcvSystemError(BYTE* lpData, DWORD dwDataLen)
{
	COMMONHEADER* pCommHeader = (COMMONHEADER*)lpData;

	CString sWINIDSEQNO;
	ULONG ulPUniqueKey;
	// pCommHeader->ulRqId ��� nWindowId�� ����Ѵ�.
	// nPUniqueKey�� �������� �ٸ� �뵵�� ��� �ϰ� �־
	ulPUniqueKey = pCommHeader->ulWinHwnd;
	sWINIDSEQNO.Format("%04d", ulPUniqueKey);

	CRequestData* pRequestData = m_RequestDataObList.GetData(sWINIDSEQNO);
	if (pRequestData)
	{
		// CommAPi�� �ڵ��� ��´�.
		HWND dwTempWnd = m_RequestDataObList.GetHwnd(sWINIDSEQNO);
		if( dwTempWnd )
		{
			// ���� �ڷḦ �ش� window �� �����Ѵ�.
			if (::IsWindow((HWND)dwTempWnd))
			{
				COPYDATASTRUCT    send_data;
				send_data.dwData	= DATAKIND_SS_ERROR;		// RP�� 
				send_data.cbData	= dwDataLen;			// ���� ������
				send_data.lpData	= lpData;			// ���� ����

				int lRet = ::SendMessage( (HWND)dwTempWnd, 
											WM_COPYDATA, 
											DATAKIND_SS_ERROR,
											(LPARAM)&send_data );
			}
		}

		// IO���̺� �����Ѵ�.
		m_RequestDataObList.RemoveData(sWINIDSEQNO);
	}
	return TRUE;
}

// Xecure ���� �� �޼����� �α��� �����쿡 send �Ѵ�.(���� ����, �ӽ÷� �׳� �Լ��� ����� ���Ҵ�)
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
// �α��� �����쿡 �޼��� ����(���� �ؾ� ���� ���� �ϴ� ����� ���� �� ��)
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
//  Function      : ����Ʈ������ ��ȣȭ �ڵ弼��ŷ
//  Param         : int nMode
//  Return        : long 
//  Create        : 
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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

	// WM_COPYDATA�� SendMessage �Ѵ�.
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
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
void CCommMain::XecureReceive(BYTE* lpData, DWORD dwDataLen)
{
	COMMONHEADER* pCommHeader = (COMMONHEADER*)lpData;
	int nRet = 0;
	// xecure ���� �� �ʿ��� ��ȣȭ�� data�� ���� ����
	BYTE cSendBuf[MAX_PACKET_SIZE];
	int nSendLen;
	int nCTXState = 0;

	if (pCommHeader->cCommandId == m_ucBccType)
	{
		// ������� ���� ����Ÿ ������ ����...
		if ((nRet = SFSP_Client_Hello_Re(m_pCtx, (char*)&lpData[COMMON_HEADER_SIZE], dwDataLen - COMMON_HEADER_SIZE)) < 0)
		{
			SendXecureErrorMessage(nRet, 7);
			return;
		}

		// SFSP_Client_ID �������ݷ� �޽��� ����
		nCTXState = 3;
		nRet = SFSP_Client_ID(m_pCtx, (char*)cSendBuf, MAX_PACKET_SIZE, &nSendLen, "GUEST", strlen("GUEST"));
		if (nRet < 0)
		{
			SendXecureErrorMessage(nRet, nCTXState);
			return;
		}
		// WM_COPYDATA�� SendMessage �Ѵ�.
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
				// WM_COPYDATA�� SendMessage �Ѵ�.
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

				// ����ó�� ���� ��û
				CPacketMngr PacketMngr;
				PacketMngr.SendCopyData(GetSafeHwnd(), PID_REVERSION, NULL, 0);
				break;
			}
			case PID_ENCXMINIT_SET:
			{
				// New ���� �϶� �������� PID_ENCXMINIT_SET�� �������� �ش�.
				if (m_nXMConnect == 0)	// ����ó��
				{
					nRet = XMC2_ClientLib_Init(&m_XMCtx, "test-cert.der");
					if (nRet < 0)
					{
						AfxMessageBox("XMC Lib Init ����");
						return;
					}

					nRet = XMC2_Encode_KeyInit_Token(&m_XMCtx, cSendBuf, (unsigned short*)&nSendLen, MAX_PACKET_SIZE);
					if (nRet < 0)
					{
						AfxMessageBox("XMC Encode_KeyInit ����");
						return;
					}

					// WM_COPYDATA�� SendMessage �Ѵ�.
					CPacketMngr PacketMngr;
					PacketMngr.SendCopyData(GetSafeHwnd(), PID_ENCXMINIT_SET, cSendBuf, nSendLen);
					m_nXMConnect = 1;
				}
				else	// ���� ������ ����.
				{
					nRet = XMC2_Decode_KeyFinal_Token(&m_XMCtx, (unsigned char*)&lpData[COMMON_HEADER_SIZE], (unsigned short)(dwDataLen - COMMON_HEADER_SIZE));

					if (nRet < 0)
					{
						AfxMessageBox("Decode_KeyFinal ����");

						SendXecureErrorMessage(nRet, 10);

						return;
					}

					// ����ó�� ���� ��û
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
//  Function      : ������ ��ȣȭ
//  Param         : unsigned char *plainbuff, int plainlen, unsigned char *encdata
//					*plainbuff-��ȣ�� ����Ÿ, plainlen ����	
//				    *encdata-��ȣȭ�� ����Ÿ
//  Return        : int 
//  Create        : �̿��� , 2008/05/09
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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
//  Function      : ����Ÿ�� ��ȣȭ
//  Param         : unsigned char *encdbuff, int encdlen, unsigned char *decdata 
//					*encdbuff-��ȣȭ�� ����Ÿ, encdlen-encdbuff�Ǳ���
//                  *decdata-Ǯ�� ����Ÿ,
//  Return        : int 
//  Create        : �̿��� , 2008/05/09
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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

	// ��ȣȭ ���� �Ǵ� ��ȭȭ �� �����Ͱ� �ִ� ���� ũ�⺸�� ū ���
	if (nRet < 0 || nDecLen > MAX_PACKET_SIZE)
		return 0;

	return nDecLen;
}

//******************************************************************
//  Function Name : CommsDbgLog
//  Function      : ����� �޼��� ��� ���
//  Param         : LPSTR lpstr, WORD wDataType /*= 0x01 */
//  Return        : BOOL 
//  Create        : �̿��� , 2006/09/07
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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
//  Function      : CommsDbg�� �����͸� �Ѱ��ִ� �Լ�
//  Param         : HWND hCommsDbgWnd,  int   nSizeLen, PVOID lpBuf, WORD	wKind /*= 0x00 */
//  Return        : BOOL 
//  Create        : 
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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
	// �ð�
	memcpy(pbyData, strTime, strTime.GetLength());
	// ť�� �ִ� ����Ÿ �Ǽ�
	memcpy(pbyData + 8, &nQueueSize, sizeof(int));
	// ����Ÿ
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
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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

// TRUE:�ý���, FALSE:�����
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
//  Function      : ������α׷����� ��� nStatus��ȣ�� ��� ComAPI���� �޼����� �����Ѵ�.
//  Param         : int nStatus /*= SOCKET_CLOSING*/ 
//  Return        : void 
//  Create        : 
//  Update        : ������, 2009/09/24 VS 2008 Upgrade�� ���� �۾�
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
		case SOCKET_CONNECTING:					// =50,		// ���� ���� �� 
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_CONNECTING";
			break;
		case SOCKET_CONNECTED:					//,		// ���� ���� �Ϸ�
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_CONNECTED";
			break;
		case SOCKET_CLOSED:						//,			// ���� ���� ����
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_CLOSED";
			break;
		case SOCKET_CLOSING:					//,			// ���� ���� ��
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_CLOSING";
			break;
		case SOCKET_CONNECT_FAIL:				//,	// ���� ���� ����
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_CONNECT_FAIL";
			break;
		case SOCKET_RECEIVE_FAIL:				//,	// ������ ���� ����
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_RECEIVE_FAIL";
			break;
		case SOCKET_SEND_FAIL:					//,		// ������ �۽� ����
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_SEND_FAIL";
			break;
		case SOCKET_SEND_SUCCESS:				//,	// ������ �۽� ����
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_SEND_SUCCESS";
			break;
		case SOCKET_RECONNECT_REQUEST:			//,// ������ ��û
				strMsg = "SendSocketNotifyToAllCommApi::SOCKET_RECONNECT_REQUEST";
			break;
		case LOGIN_COMPLETE:					//,			// ����ó�� �Ϸ� 
			{
				strMsg = "SendSocketNotifyToAllCommApi::LOGIN_COMPLETE";
				AfxMessageBox(strMsg);
			}
			break;
		case LOGIN_FAIL:						//			// ����ó�� ���� 
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
// ���� ���� �� ������ �õ� �ϱ�
void CCommMain::RetryConnectToServer(int nErrorCode)
{
	CString		strMsg;
	CString		strSocketMsg;

	m_bConnect = FALSE;
	m_nSignOn  = -1;	// �α��� ���¸� �ʱ�ȭ �Ѵ�.
	
	if (m_pCommsConfig->m_bLogWrite)
	{		
		strMsg = "Comms,OnSocketNotify SOCKET_CONNECT_FAIL ,%d,%s";
		WriteLogMsg(strMsg, strSocketMsg, nErrorCode);					
		CommsDbgLog((LPSTR)(LPCTSTR)strSocketMsg);
	}

// --> [Edit]  ������ 2010/08/25
	// �� ������ �õ��Ѵ�(3�ʿ� 1���� 3��).
	if (m_nTotalRetryCount < m_pCommsConfig->m_nMaxRetryCount)
	{
		// "������ ��" ���� �˸���.
		m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CONNECTING, m_nRetryCount + 1);
		SendSocketNotifyToAllCommApi(SOCKET_CONNECTING);

// --> [Edit]  ������ 2011/04/12 ( ������ ���� )
// 		if (m_nRetryConnectTimer)
// 		{
// 			KillTimer(m_nRetryConnectTimer);
// 			m_nRetryConnectTimer = 0;
// 		}

// -->  //KMG 2012.06.19 ������Ʈ���� : ����ó���� 8080 ��������� ��������, �ƴϸ� Main Ip,Port���� ������ 8080��Ʈ�õ�
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
	// <-- [Edit]  ������ 2011/04/12
			if (m_nRetryCount >= (MAINIP_CNT * 2))
			{
				m_nTotalRetryCount++;
				m_nRetryCount = 0;

				//KMG 2012.06.19 ������Ʈ���� :  Main Ip,Port����������8080��Ʈ�õ�
				m_bConnectSubPort = TRUE; 
			}
		}
	}
	// ���̻� ��õ� ���ϴ� ��� ���� ���и� �˸���.
	else
	{
		m_nRetryCount = 0;
		m_nTotalRetryCount = 0;
		// ��� ComAPI���� ���� ������� �޼����� �����Ѵ�.
		SendSocketNotifyToAllCommApi(SOCKET_CONNECT_FAIL);
		m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CONNECT_FAIL);
		m_pTcpSocket->DisConnectTCPSocket();
		m_pParentWnd->PostMessage(WM_COMMS_PROGRAM_CLOSE, 0, 0);
	}
// <-- [Edit]  ������ 2010/08/25


/*
	// sub port ������� ���� �Ǿ� �ְ�
	if (m_pCommsConfig->m_bUseSubPort)
	{
		// Main Port�� 3ȸ ���� ���и� sub port�� ���� �õ� �Ѵ�.
		 if (!m_bConnectSubPort && m_nRetryCount >= m_pCommsConfig->m_nMaxRetryCount)
		 {
			m_nRetryCount		= 0;
			m_bConnectSubPort	= TRUE;
			m_pCommsConfig->m_nMainPort = m_pCommsConfig->m_nSubPort;
			m_pTcpSocket->SetHostAddressAndPort(m_pCommsConfig->m_strMainIP, m_pCommsConfig->m_nMainPort);
		 }
	}

	// �� ������ �õ��Ѵ�(10�ʿ� 1���� 3��).
	if (m_nRetryCount < m_pCommsConfig->m_nMaxRetryCount)
	{
		// "������ ��" ���� �˸���.
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
	// ���̻� ��õ� ���ϴ� ��� ���� ���и� �˸���.
	else
	{
		m_nRetryCount = 0;	
		// ��� ComAPI���� ���� ������� �޼����� �����Ѵ�.
		SendSocketNotifyToAllCommApi(SOCKET_CONNECT_FAIL);
		m_pParentWnd->SendMessage(UM_SET_TRAYICON_STATUS, SOCKET_CONNECT_FAIL);
		m_pTcpSocket->DisConnectTCPSocket();
		m_pParentWnd->PostMessage(WM_COMMS_PROGRAM_CLOSE, 0, 0);
	}
*/
}
// ��ϵ� �ǽð� Ÿ���ΰ� üũ
BOOL CCommMain::CheckRealType(BYTE cCommandId)
{

	return TRUE;
}

// 2002.7.15 -hidden-  �ž��� ü���뺸 ó������.
int CCommMain::ConclusionRealProcessForBP(CString strTrCode, BYTE* pTrData, DWORD dwDataLen, BYTE* pRealData)
{
	CString strTemp = "";
	long nTemp(0);
	int nDataLen(0);

	//-------------------------------------------------------
	//2011.03.11 jhj �޸� size�� ����ؼ� memcpy�� �Ѵ�.
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

		CString strFlag	= CString(OutData.market_gb, sizeof(OutData.market_gb));		//	[���屸��]
		CString strGubun = CString(OutData.data_gb, sizeof(OutData.data_gb));			//	[DATA����]

		if ( strGubun == "5" )
		{
			//	�ֹ� �����϶��� ���¸�/�ð����� ó���� �޶����� ������ ����ü�� �ٲ۴�.
			// 2011.03.11 �ֹ����� ü���뺸�϶� ������ ������ �����Ͱ� ������..
			// CN997Q00_OutRec2 => CN997Q00_OutRec1 �� �� ������
			// 2011.03.14 CN997Q00_OutRec2�� ����ü�� ������. 1���� �ϸ� �߰��� �����Ͱ� ���� ����. ü��� �ֹ������϶� �������� ������ ���̿� ������ �ٸ�. => �̰� ������...�Ѥ�;;
			CN997Q00_OutRec2		OutData;
			memset(&OutData, 0x00	, sizeof(CN997Q00_OutRec2) );

			//# 2011.03.11 jhj
			if(nByteSize < sizeof(CN997Q00_OutRec2))
				return 0;

			memcpy(&OutData, pTrData, sizeof(CN997Q00_OutRec2));

			memcpy(pData->market_gb			, OutData.market_gb			, sizeof(OutData.market_gb		) );	//	[���屸��] 6:KOSPI ����/�ɼ�								
			memcpy(pData->data_gb			, OutData.data_gb			, sizeof(OutData.data_gb		) );	//	[DATA����] 1:ü��, 2:����, 3:���, 4:�ź�, 5:�ֹ�����Ȯ��	
			memcpy(pData->data_name			, OutData.data_name			, sizeof(OutData.data_name		) );	//	[DATA��]													
			memcpy(pData->acct_no			, OutData.acct_no			, sizeof(OutData.acct_no		) );	//	[���¹�ȣ]     												
			memcpy(pData->acct_nm			, OutData.acct_nm			, sizeof(OutData.acct_nm		) );	//	[���¸�]     												
			memcpy(pData->order_no			, OutData.order_no			, sizeof(OutData.order_no		) );	//	[�ֹ���ȣ]	 ���� : 003-000001(�����ΰ�츸)			    
			memcpy(pData->org_order_no		, OutData.org_order_no		, sizeof(OutData.org_order_no	) );	//	[���ֹ���ȣ] ���� : 003-000001(�����ΰ�츸)				
	//		memcpy(pData->spread_gb			, OutData.spread_gb			, sizeof(OutData.spread_gb		) );	//	[SPREAD����]												
			memcpy(pData->jmcode			, OutData.jmcode			, sizeof(OutData.jmcode			) );	//	[�����ڵ�]													
			memcpy(pData->jmname			, OutData.jmname			, sizeof(OutData.jmname			) );	//	[�����]													
			memcpy(pData->meme_gb			, OutData.meme_gb			, sizeof(OutData.meme_gb		) );	//	[�Ÿű���]													
			memcpy(pData->order_gb			, OutData.order_gb			, sizeof(OutData.order_gb		) );	//	[�ֹ�����]													

			strTemp = CString (OutData.order_qty, sizeof(OutData.order_qty));
			pData->order_qty = htonl(atol(strTemp));															//	[�ֹ�����]													

			strTemp = CString (OutData.order_price, sizeof(OutData.order_price));
			pData->order_price = htonl(atol(strTemp));															//	[�ֹ��ܰ�]													

			strTemp = CString (OutData.che_qty, sizeof(OutData.che_qty));
			pData->che_qty = htonl(atol(strTemp));																//	[ü�����]													

			strTemp = CString (OutData.che_price, sizeof(OutData.che_price));
			pData->che_price = htonl(atol(strTemp));															//	[ü��ܰ�]													

			strTemp = CString (OutData.tot_che_qty, sizeof(OutData.tot_che_qty));
			pData->tot_che_qty = htonl(atol(strTemp));															//	[��ü�����]													

			strTemp = CString (OutData.avg_che_price, sizeof(OutData.avg_che_price));
			pData->avg_che_price = htonl(atol(strTemp));														//	[���ü��ܰ�]													

			strTemp = CString (OutData.miche_qty, sizeof(OutData.miche_qty));
			pData->miche_qty = htonl(atol(strTemp));															//	[��ü�����]													

			memcpy(pData->mod_can_gb		, OutData.mod_can_gb		, sizeof(OutData.mod_can_gb		) );	//	[������ұ���]												

			strTemp = CString (OutData.qty, sizeof(OutData.qty));
			pData->qty = htonl(atol(strTemp));																	//	[��������]													

			strTemp = CString (OutData.buy_avg_prc, sizeof(OutData.buy_avg_prc));
			pData->buy_avg_prc = htonl(atol(strTemp));															//	[���Դܰ�]													

	//		memcpy(pData->migul_avg_amt		, OutData.migul_avg_amt		, sizeof(OutData.migul_avg_amt	) );	//	[�̰���������ձݾ�]										
			pData->price	= pData->che_price;																	//	[���簡] ü��ܰ��� ���簡�� �ִ´�.													
			memcpy(pData->che_cond			, OutData.che_cond			, sizeof(OutData.che_cond		) );	//	[ü������]													
	//		memcpy(pData->non_code			, OutData.non_code			, sizeof(OutData.non_code		) );	//	[�������ڵ�]												
	//		memcpy(pData->filler			, OutData.filler			, sizeof(OutData.filler			) );	//	[FILLER]													
	//		memcpy(pData->fu_commit_sonik	, OutData.fu_commit_sonik	, sizeof(OutData.fu_commit_sonik) );	//	[��������Ÿż���]											
	//		memcpy(pData->fu_avg_sonik		, OutData.fu_avg_sonik		, sizeof(OutData.fu_avg_sonik	) );	//	[������ոŸż���]											
	//		memcpy(pData->op_commit_sonik	, OutData.op_commit_sonik	, sizeof(OutData.op_commit_sonik) );	//	[�ɼ�����Ÿż���]											
	//		memcpy(pData->op_buy_amt		, OutData.op_buy_amt		, sizeof(OutData.op_buy_amt		) );	//	[�ɼǸż����]												
	//		memcpy(pData->op_sell_amt		, OutData.op_sell_amt		, sizeof(OutData.op_sell_amt	) );	//	[�ɼǸŵ����]												
	//		memcpy(pData->fu_buy_amt		, OutData.fu_buy_amt		, sizeof(OutData.fu_buy_amt		) );	//	[�����ż����]												
	//		memcpy(pData->fu_sell_amt		, OutData.fu_sell_amt		, sizeof(OutData.fu_sell_amt	) );	//	[�����ŵ����]												
	//		memcpy(pData->order_tot_amt		, OutData.order_tot_amt		, sizeof(OutData.order_tot_amt	) );	//	[�ֹ������Ѿ�]												
	//		memcpy(pData->order_cash		, OutData.order_cash		, sizeof(OutData.order_cash		) );	//	[�ֹ���������]												

			memcpy(pData->order_time		, OutData.order_time		, sizeof(OutData.order_time		) );	//	[�ֹ��ð�]													

			memcpy(pData->credit_gb			, OutData.credit_gb			, sizeof(OutData.credit_gb		) );	//	[�ſ�ŷ�����]												
			memcpy(pData->loan_date			, OutData.loan_date			, sizeof(OutData.loan_date		) );	//	[��������]													
			memcpy(pData->damboloan_gb		, OutData.damboloan_gb		, sizeof(OutData.damboloan_gb	) );	//	[�㺸���ⱸ��]												
			memcpy(pData->buy_date			, OutData.buy_date			, sizeof(OutData.buy_date		) );	//	[�ż���]													
			memcpy(pData->tax_target_gb		, OutData.tax_target_gb		, sizeof(OutData.tax_target_gb	) );	//	[������󱸺�]												
			memcpy(pData->bond_jan_gb		, OutData.bond_jan_gb		, sizeof(OutData.bond_jan_gb	) );	//	[ä���ܰ���]												
			memcpy(pData->credit_gb_text	, OutData.credit_gb_text	, sizeof(OutData.credit_gb_text	) );	//	[�ſ뱸�и�]												
			memcpy(pData->credit_tot_order	, OutData.credit_tot_order	, sizeof(OutData.credit_tot_order) );	//	[�ſ������ֹ�����]											
			
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

			memcpy(pData->market_gb			, OutData.market_gb			, sizeof(OutData.market_gb		) );	//	[���屸��] 6:KOSPI ����/�ɼ�								
			memcpy(pData->data_gb			, OutData.data_gb			, sizeof(OutData.data_gb		) );	//	[DATA����] 1:ü��, 2:����, 3:���, 4:�ź�, 5:�ֹ�����Ȯ��	
			memcpy(pData->data_name			, OutData.data_name			, sizeof(OutData.data_name		) );	//	[DATA��]													
			memcpy(pData->acct_no			, OutData.acct_no			, sizeof(OutData.acct_no		) );	//	[���¹�ȣ]     												
			memcpy(pData->acct_nm			, OutData.acct_nm			, sizeof(OutData.acct_nm		) );	//	[���¸�]     												
			memcpy(pData->order_no			, OutData.order_no			, sizeof(OutData.order_no		) );	//	[�ֹ���ȣ]	 ���� : 003-000001(�����ΰ�츸)			    
			memcpy(pData->org_order_no		, OutData.org_order_no		, sizeof(OutData.org_order_no	) );	//	[���ֹ���ȣ] ���� : 003-000001(�����ΰ�츸)				
	//		memcpy(pData->spread_gb			, OutData.spread_gb			, sizeof(OutData.spread_gb		) );	//	[SPREAD����]												
			memcpy(pData->jmcode			, OutData.jmcode			, sizeof(OutData.jmcode			) );	//	[�����ڵ�]													
			memcpy(pData->jmname			, OutData.jmname			, sizeof(OutData.jmname			) );	//	[�����]													
			memcpy(pData->meme_gb			, OutData.meme_gb			, sizeof(OutData.meme_gb		) );	//	[�Ÿű���]													
			memcpy(pData->order_gb			, OutData.order_gb			, sizeof(OutData.order_gb		) );	//	[�ֹ�����]													

			strTemp = CString (OutData.order_qty, sizeof(OutData.order_qty));
			pData->order_qty = htonl(atol(strTemp));															//	[�ֹ�����]													

			strTemp = CString (OutData.order_price, sizeof(OutData.order_price));
			pData->order_price = htonl(atol(strTemp));															//	[�ֹ��ܰ�]													

			strTemp = CString (OutData.che_qty, sizeof(OutData.che_qty));
			pData->che_qty = htonl(atol(strTemp));																//	[ü�����]													

			strTemp = CString (OutData.che_price, sizeof(OutData.che_price));
			pData->che_price = htonl(atol(strTemp));															//	[ü��ܰ�]													

			strTemp = CString (OutData.tot_che_qty, sizeof(OutData.tot_che_qty));
			pData->tot_che_qty = htonl(atol(strTemp));															//	[��ü�����]													

			strTemp = CString (OutData.avg_che_price, sizeof(OutData.avg_che_price));
			pData->avg_che_price = htonl(atol(strTemp));														//	[���ü��ܰ�]													

			strTemp = CString (OutData.miche_qty, sizeof(OutData.miche_qty));
			pData->miche_qty = htonl(atol(strTemp));															//	[��ü�����]													

			memcpy(pData->mod_can_gb		, OutData.mod_can_gb		, sizeof(OutData.mod_can_gb		) );	//	[������ұ���]												

			strTemp = CString (OutData.qty, sizeof(OutData.qty));
			pData->qty = htonl(atol(strTemp));																	//	[��������]													

			strTemp = CString (OutData.buy_avg_prc, sizeof(OutData.buy_avg_prc));
			pData->buy_avg_prc = htonl(atol(strTemp));															//	[���Դܰ�]													

	//		memcpy(pData->migul_avg_amt		, OutData.migul_avg_amt		, sizeof(OutData.migul_avg_amt	) );	//	[�̰���������ձݾ�]										
			pData->price	= pData->che_price;																	//	[���簡] ü��ܰ��� ���簡�� �ִ´�.													
			memcpy(pData->che_cond			, OutData.che_cond			, sizeof(OutData.che_cond		) );	//	[ü������]													
	//		memcpy(pData->non_code			, OutData.non_code			, sizeof(OutData.non_code		) );	//	[�������ڵ�]												
	//		memcpy(pData->filler			, OutData.filler			, sizeof(OutData.filler			) );	//	[FILLER]													
	//		memcpy(pData->fu_commit_sonik	, OutData.fu_commit_sonik	, sizeof(OutData.fu_commit_sonik) );	//	[��������Ÿż���]											
	//		memcpy(pData->fu_avg_sonik		, OutData.fu_avg_sonik		, sizeof(OutData.fu_avg_sonik	) );	//	[������ոŸż���]											
	//		memcpy(pData->op_commit_sonik	, OutData.op_commit_sonik	, sizeof(OutData.op_commit_sonik) );	//	[�ɼ�����Ÿż���]											
	//		memcpy(pData->op_buy_amt		, OutData.op_buy_amt		, sizeof(OutData.op_buy_amt		) );	//	[�ɼǸż����]												
	//		memcpy(pData->op_sell_amt		, OutData.op_sell_amt		, sizeof(OutData.op_sell_amt	) );	//	[�ɼǸŵ����]												
	//		memcpy(pData->fu_buy_amt		, OutData.fu_buy_amt		, sizeof(OutData.fu_buy_amt		) );	//	[�����ż����]												
	//		memcpy(pData->fu_sell_amt		, OutData.fu_sell_amt		, sizeof(OutData.fu_sell_amt	) );	//	[�����ŵ����]												
	//		memcpy(pData->order_tot_amt		, OutData.order_tot_amt		, sizeof(OutData.order_tot_amt	) );	//	[�ֹ������Ѿ�]												
	//		memcpy(pData->order_cash		, OutData.order_cash		, sizeof(OutData.order_cash		) );	//	[�ֹ���������]												

			memcpy(pData->order_time		, OutData.order_time		, sizeof(OutData.order_time		) );	//	[�ֹ��ð�]													

			memcpy(pData->credit_gb			, OutData.credit_gb			, sizeof(OutData.credit_gb		) );	//	[�ſ�ŷ�����]												
			memcpy(pData->loan_date			, OutData.loan_date			, sizeof(OutData.loan_date		) );	//	[��������]													
			memcpy(pData->damboloan_gb		, OutData.damboloan_gb		, sizeof(OutData.damboloan_gb	) );	//	[�㺸���ⱸ��]												
			memcpy(pData->buy_date			, OutData.buy_date			, sizeof(OutData.buy_date		) );	//	[�ż���]													
			memcpy(pData->tax_target_gb		, OutData.tax_target_gb		, sizeof(OutData.tax_target_gb	) );	//	[������󱸺�]												
			memcpy(pData->bond_jan_gb		, OutData.bond_jan_gb		, sizeof(OutData.bond_jan_gb	) );	//	[ä���ܰ���]												
			memcpy(pData->credit_gb_text	, OutData.credit_gb_text	, sizeof(OutData.credit_gb_text	) );	//	[�ſ뱸�и�]												
			memcpy(pData->credit_tot_order	, OutData.credit_tot_order	, sizeof(OutData.credit_tot_order) );	//	[�ſ������ֹ�����]											
			
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

		CString strFlag	= CString(OutData.market_gb, sizeof(OutData.market_gb));		//	[���屸��]
		CString strGubun = CString(OutData.data_gb, sizeof(OutData.data_gb));			//	[DATA����]
		CString strSFlag = CString(OutData.spread_gb, sizeof(OutData.spread_gb));		//	[SPREAD����]

		memcpy(pData->market_gb			, OutData.market_gb			, sizeof(OutData.market_gb		) );	//	[���屸��] 6:KOSPI ����/�ɼ�								
		memcpy(pData->data_gb			, OutData.data_gb			, sizeof(OutData.data_gb		) );	//	[DATA����] 1:ü��, 2:����, 3:���, 4:�ź�, 5:�ֹ�����Ȯ��	
		memcpy(pData->data_name			, OutData.data_name			, sizeof(OutData.data_name		) );	//	[DATA��]													
		memcpy(pData->acct_no			, OutData.acct_no			, sizeof(OutData.acct_no		) );	//	[���¹�ȣ]     												
		memcpy(pData->acct_nm			, OutData.acct_nm			, sizeof(OutData.acct_nm		) );	//	[���¸�]     												
		memcpy(pData->order_no			, OutData.order_no			, sizeof(OutData.order_no		) );	//	[�ֹ���ȣ]	 ���� : 003-000001(�����ΰ�츸)			    
		memcpy(pData->org_order_no		, OutData.org_order_no		, sizeof(OutData.org_order_no	) );	//	[���ֹ���ȣ] ���� : 003-000001(�����ΰ�츸)				
		memcpy(pData->spread_gb			, OutData.spread_gb			, sizeof(OutData.spread_gb		) );	//	[SPREAD����]												
		memcpy(pData->jmcode			, OutData.jmcode			, sizeof(pData->jmcode			) );	//	[�����ڵ�]	TR���� �������� �ڵ尡 �ڸ����� �� ���.
		memcpy(pData->jmname			, OutData.jmname			, sizeof(OutData.jmname			) );	//	[�����]													
		memcpy(pData->meme_gb			, OutData.meme_gb			, sizeof(OutData.meme_gb		) );	//	[�Ÿű���]													
		memcpy(pData->order_gb			, OutData.order_gb			, sizeof(OutData.order_gb		) );	//	[�ֹ�����]													

		strTemp = CString (OutData.order_qty, sizeof(OutData.order_qty));
		pData->order_qty = htonl(atol(strTemp));															//	[�ֹ�����]													

		strTemp = CString (OutData.order_price, sizeof(OutData.order_price));
//		strDanga.Format("%0.2f", atof(strTemp)/100);
		pData->order_price = htonl(atol(strTemp));															//	[�ֹ��ܰ�]													

		strTemp = CString (OutData.che_qty, sizeof(OutData.che_qty));
		pData->che_qty = htonl(atol(strTemp));																//	[ü�����]													

		strTemp = CString (OutData.che_price, sizeof(OutData.che_price));
		pData->che_price = htonl(atol(strTemp));															//	[ü��ܰ�]													

		strTemp = CString (OutData.tot_che_qty, sizeof(OutData.tot_che_qty));
		pData->tot_che_qty = htonl(atol(strTemp));															//	[��ü�����]													

		strTemp = CString (OutData.avg_che_price, sizeof(OutData.avg_che_price));
		pData->avg_che_price = htonl(atol(strTemp));														//	[���ü��ܰ�]													

		strTemp = CString (OutData.miche_qty, sizeof(OutData.miche_qty));
		pData->miche_qty = htonl(atol(strTemp));															//	[��ü�����]													

		memcpy(pData->mod_can_gb		, OutData.mod_can_gb		, sizeof(OutData.mod_can_gb		) );	//	[������ұ���]												

		strTemp = CString (OutData.last_qty, sizeof(OutData.last_qty));
		pData->qty = htonl(atol(strTemp));																	//	[��������]													

		strTemp = CString (OutData.last_price, sizeof(OutData.last_price));
		pData->buy_avg_prc = htonl(atol(strTemp));															//	[���Դܰ�]													

		memcpy(pData->migul_avg_amt		, OutData.last_migul_amt	, sizeof(OutData.last_migul_amt	) );	//	[�̰���������ձݾ�]										
		pData->price	= pData->che_price;																	//	[���簡] ü��ܰ��� ���簡�� �ִ´�.													
//		memcpy(pData->che_cond			, OutData.che_cond			, sizeof(OutData.che_cond		) );	//	[ü������]													
		memcpy(pData->non_code			, OutData.non_code			, sizeof(OutData.non_code		) );	//	[�������ڵ�]

		//if ( strSFlag == "1" )			//Spread �̸� ó��
		//{
		//	memcpy(pData->jmcode			, OutData.next_code			, sizeof(pData->jmcode		) );	//	[�����ڵ�]	TR���� �������� �ڵ尡 �ڸ����� �� ���.
		//	memcpy(pData->jmname			, OutData.next_name			, sizeof(OutData.next_name	) );	//	[�����]													
		//	memcpy(pData->meme_gb			, OutData.next_meme			, sizeof(OutData.next_meme	) );	//	[�Ÿű���]													

		//	strTemp = CString (OutData.next_qty, sizeof(OutData.next_qty));
		//	pData->order_qty = htonl(atol(strTemp));															//	[�ֹ�����]													

		//	strTemp = CString (OutData.next_price, sizeof(OutData.next_price));
		//	pData->buy_avg_prc = htonl(atol(strTemp));															//	[���Դܰ�]													

		//	memcpy(pData->migul_avg_amt		, OutData.next_migul_amt	, sizeof(OutData.next_migul_amt	) );	//	[�̰���������ձݾ�]										
		//}

		memcpy(pData->che_cond			, "  "				, 1 );	//	[ü������]													

		memcpy(pData->filler			, "     "			, 5 );	//	[FILLER]													
		memcpy(pData->fu_commit_sonik	, "          "		, 10);	//	[��������Ÿż���]											
		memcpy(pData->fu_avg_sonik		, "          "		, 10);	//	[������ոŸż���]											
		memcpy(pData->op_commit_sonik	, "          "		, 10);	//	[�ɼ�����Ÿż���]											
		memcpy(pData->op_buy_amt		, "            "	, 12);	//	[�ɼǸż����]												
		memcpy(pData->op_sell_amt		, "            "	, 12);	//	[�ɼǸŵ����]												
		memcpy(pData->fu_buy_amt		, "            "	, 12);	//	[�����ż����]												
		memcpy(pData->fu_sell_amt		, "            "	, 12);	//	[�����ŵ����]												
		memcpy(pData->order_tot_amt		, "          "		, 10);	//	[�ֹ������Ѿ�]												
		memcpy(pData->order_cash		, "          "		, 10);	//	[�ֹ���������]												

		memcpy(pData->order_time		, OutData.order_time		, sizeof(OutData.order_time		) );	//	[�ֹ��ð�]													
//		memcpy(pData->order_time		, "        "		, 8 );	//	[�ֹ��ð�]													

		memcpy(pData->credit_gb			, " "				, 1 );	//	[�ſ�ŷ�����]												
		memcpy(pData->loan_date			, "        "		, 8 );	//	[��������]													
		memcpy(pData->damboloan_gb		, " "				, 1 );	//	[�㺸���ⱸ��]												
		memcpy(pData->buy_date			, "        "		, 8 );	//	[�ż���]													
		memcpy(pData->tax_target_gb		, " "				, 1 );	//	[������󱸺�]												
		memcpy(pData->bond_jan_gb		, " "				, 1 );	//	[ä���ܰ���]												
		memcpy(pData->credit_gb_text	, "          "		, 10 );	//	[�ſ뱸�и�]												
		memcpy(pData->credit_tot_order	, " "				, 1 );	//	[�ſ������ֹ�����]											

		nDataLen = sizeof(S_CHEJAN_REAL_OUTREC);
	}
	else if(strTrCode == "CN994Q00")	//ljj 20110314 �ý��۾˶� �߰�
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
	pstrData += 100;										// ��� + �޼���
	pstrData += 40;											// ü���뺸 ��� ����Ÿ.
	BYTE *pBuf = new BYTE[1024];							// ü���뺸 �ڵ����� ������ 166 + 1
	BYTE *SprBuf = NULL;									// �������� �ϰ�� ����Ѵ�.
	long lTemp = 314;		//KJI 20070518(�ſ��߰��� ����)
	lTemp = htonl(lTemp);
	memcpy(pBuf, &lTemp, 4);
	lTemp = 1;
	lTemp = htonl(lTemp);
	memcpy(pBuf+4, &lTemp, 4);
	memcpy(pBuf+8, pstrData, 1);
	//if(strTrCode == "CN994Q00")	//LJP �˶���ȣ
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
	CString strGubun(pstrData, 1);	pstrData++;				// 1-ü��, 2-����Ȯ��, 3-���Ȯ��, 4-�ź�, 5-�ֹ�Ȯ��

	CStringArray* pConclusion = new CStringArray;
	
	if (strTrCode == "CN997Q00")  //���� ü���뺸 
	{
		pConclusion->Add(strFlag);				//���屸���� �־�д�.
		pConclusion->Add(strGubun);				//ü�ᱸ���� �־�д�.		//shc 20030930

		memcpy(pBuf+10, pstrData, 16);
		CString strDataName(pstrData, 16);	pstrData += 16;		// ����Ÿ��(16)
		strDataName.TrimLeft();
		strDataName.TrimRight();
		pConclusion->Add(strDataName);

		memcpy(pBuf+26, pstrData, 11);
		CString strAccount(pstrData, 11);	pstrData += 11;		// ���¹�ȣ(11)
		pConclusion->Add(strAccount);

		//memcpy(pBuf+37, pstrData, 16);		pstrData += 16;		// ���¸�(16)

		//ljj 20060607 �������� ���� �ֹ��ð��� ���¸���Ŷ�� �Ǿ �����شܴ�..(ȣ�����̴� ������)
		//���¸�(10)+�ֹ��ð�(6)
		//���¸��� 16����Ʈ�̹Ƿ� ���¸�(10byt+space(6byte))
		//�ֹ��ð��� 8����Ʈ�̹Ƿ� �ֹ��ð�(6byt) + '00'(2byte)
		CString strAccNMData( pstrData, 16);
		CString strAccNM = strAccNMData.Left(10);
		
		CString strJuTime = strAccNMData.Mid(10);
		strAccNM.Format("%16s", strAccNM+"      ");

		//KJI 20070509
		if( strGubun != "5")
		{
			memcpy(pBuf+37, (LPSTR)(LPCTSTR)strAccNM, 16);		pstrData += 18;		//KJI 20070423 ���¸�(10)
			memcpy(pBuf+278, (LPSTR)(LPCTSTR)strJuTime, 8);							// �ֹ��ð�(8)
		}
		else
		{
			memcpy(pBuf+37, (LPSTR)(LPCTSTR)strAccNM, 16);
			pstrData += 16;
		}
		
		memcpy(pBuf+53, pstrData, 10);
		CString strNum(pstrData, 10);		pstrData += 10;		// �ֹ���ȣ(10)
		strNum.TrimRight(); 
		strNum.Format("%d", atoi(strNum));

		memcpy(pBuf+63, pstrData, 10);		pstrData += 10;		// ���ֹ���ȣ(10)

		memcpy(pBuf+73, " ", 1);								// �������屸��(1)

		memcpy(pBuf+74, pstrData, 12);		pstrData += 12;		// �����ڵ�(12)

		memcpy(pBuf+86, pstrData, 20);
		CString strJongmok(pstrData, 20);	pstrData += 20;		// �����(20)
		strJongmok.TrimLeft(); 
		strJongmok.TrimRight();
		pConclusion->Add(strJongmok);

		memcpy(pBuf+106, pstrData, 4);
		CString strSaleBuy(pstrData, 4);	pstrData += 4;		// �Ÿű���(4)
		pConclusion->Add(strSaleBuy);

		CString strQuant(pstrData, 8);
		lTemp = atoi(strQuant);
		strQuant.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+112, &lTemp, 4);		pstrData += 8;		// �ֹ�����(4)

		CString strDanga(pstrData, 9);
		lTemp = atoi(strDanga);
		strDanga.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+116, &lTemp, 4);		pstrData += 9;		// �ֹ��ܰ�(4)

		CString strCheQuant(pstrData, 8);
		lTemp = atoi(strCheQuant);
		strCheQuant.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+120, &lTemp, 4);		pstrData += 8;		// ü�����(4)

		CString strCheDanga(pstrData, 9);
		CString strCheDanga1 = strCheDanga;						//ljj 20070129 ü��ܰ��� ���簡�� ����
		lTemp = atoi(strCheDanga);
		strCheDanga.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+124, &lTemp, 4);		pstrData += 9;		// ü��ܰ�(4)

		CString strTemp(pstrData, 8);
		lTemp = atoi(strTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+128, &lTemp, 4);		pstrData += 8;		// ��ü�����(4)

		CString strTemp1(pstrData, 9);
		lTemp = atoi(strTemp1);
		lTemp = htonl(lTemp);
		memcpy(pBuf+132, &lTemp, 4);		pstrData += 9;		// ���ü��ܰ�(4)

		CString strTemp2(pstrData, 8);
		lTemp = atoi(strTemp2);
		lTemp = htonl(lTemp);
		memcpy(pBuf+136, &lTemp, 4);		pstrData += 8;		// ��ü�����(4)
		
		memcpy(pBuf+140, pstrData, 8);		pstrData += 8;		// ������ұ���(8)

		CString strTemp3(pstrData, 8);							
		lTemp = atoi(strTemp3);
		lTemp = htonl(lTemp);
		memcpy(pBuf+148, &lTemp, 4);		pstrData += 8;		// ��������(4)
		
		CString strTemp4(pstrData, 9);							
		lTemp = atoi(strTemp4);
		lTemp = htonl(lTemp);
		memcpy(pBuf+152, &lTemp, 4);		pstrData += 9;		// ���Դܰ�(4)
		
		//KJI 20040219
		memcpy(pBuf+156, "            ", 12);					// �̰��������ݾ�(12)

		pstrData += 2;	//�ܰ��� ������
		//KJI 20040219
		memcpy(pBuf+110, pstrData, 2);							//�ֹ�����(2)
		pstrData += 2;	//�ֹ����� ������ ó������

		memcpy(pBuf+172, pstrData, 1);	pstrData += 1;			//ü������(1)

		//KJI 20070509
		if(	strGubun == "5")	
		{
			strJuTime.Format("%s", pstrData);	pstrData += 8;
			memcpy(pBuf+278, (LPSTR)(LPCTSTR)strJuTime, 8);
		}

		lTemp = atoi(strCheDanga1);								//ljj 20070129 ü��ܰ��� ���簡�� ����
		lTemp = htonl(lTemp);
		memcpy(pBuf+168, &lTemp, 4);							//���簡(4)

		memcpy(pBuf+173, "       ", 7);							//Filler(7)

		for(int nP = 180; nP < 279; nP++)	//������ ���̸� �����.
			memcpy(pBuf+nP, " ", 1);

		//KJI 20070418 (�ſ���� �߰�)
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
		
		if( strGubun == "1")										// ü���϶�
			pConclusion->Add(strCheQuant + "��");				// ü�����(4)		
		else													// ����,���,�ź��϶�
			pConclusion->Add(strQuant + "��");					// �ֹ�����(4)		
		
		if( strGubun == "3")										// ����϶� - �ܰ��� �ʿ����.
			pConclusion->Add(" ");
		else if( strGubun == "1")								// ü���϶�
			pConclusion->Add(strCheDanga + "��");				// ü��ܰ�(4)		
		else												
			pConclusion->Add(strDanga + "��");					// ����,���,�ź��϶�

		strNum = "<" + strNum + ">";		
		pConclusion->Add(strNum);
	}
	else if (strTrCode == "CN996Q00")  //�����ɼ� ü���뺸 
	{
		pConclusion->Add(strFlag);				//���屸���� �־�д�.
		pConclusion->Add(strGubun);				//�ֹ������� �־�д�.		//shc 20030930

		memcpy(pBuf+10, pstrData, 16);
		CString strDataName(pstrData, 16);	pstrData += 16;		// ����Ÿ��(16)
		strDataName.TrimLeft();
		strDataName.TrimRight();
		pConclusion->Add(strDataName);

		memcpy(pBuf+26, pstrData, 11);
		CString strAccount(pstrData, 11);	pstrData += 11;		// ���¹�ȣ(11)
		pConclusion->Add(strAccount);

		memcpy(pBuf+37, pstrData, 16);	pstrData += 16;			//���¸�(16)

		memcpy(pBuf+53, pstrData, 10);
		CString strNum(pstrData, 10);		pstrData += 10;		// �ֹ���ȣ(10)
		strNum.TrimRight(); 
		strNum.Format("%d", atoi(strNum));

		memcpy(pBuf+63, pstrData, 10);	pstrData += 10;			//���ֹ���ȣ(10)

		CString strSFlag(pstrData, 1);
		memcpy(pBuf+73, pstrData, 1);	pstrData += 1;			// �������� ����(1)

		memcpy(pBuf+74, pstrData, 12);	pstrData += 15;			//�����ڵ�(12)

		memcpy(pBuf+86, pstrData, 20);
		CString strJongmok(pstrData, 20);	pstrData += 20;		// �����(20)
		strJongmok.TrimLeft(); 
		strJongmok.TrimRight();
		pConclusion->Add(strJongmok);

		memcpy(pBuf+106, pstrData, 4);
		CString strSaleBuy(pstrData, 4);	pstrData += 4;		// �Ÿű���(4)
		pConclusion->Add(strSaleBuy);

		//KJI 20040219
	//	memcpy(pBuf+110, "  ", 2);								//�ֹ�����(2)

		CString strQuant(pstrData, 8);
		lTemp = atoi(strQuant);
		strQuant.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+112, &lTemp, 4);		pstrData += 8;		// �ֹ�����(4)

		CString strDanga(pstrData, 9);
		lTemp = atoi(strDanga);
		strDanga.Format("%0.2f", atof(strDanga)/100);
		lTemp = htonl(lTemp);
		memcpy(pBuf+116, &lTemp, 4);		pstrData += 9;		// �ֹ��ܰ�(4)

		CString strCheQuant(pstrData, 8);
		lTemp = atoi(strCheQuant);
		strCheQuant.Format("%d", lTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+120, &lTemp, 4);		pstrData += 8;		// ü�����(4)

		CString strCheDanga(pstrData, 9);

		CString strCurPrice1;
		strCurPrice1 = strCheDanga;				//ljj 20070103 ���簡�� ü��ܰ��� �ֱ����ؼ�

		lTemp = atoi(strCheDanga);
		strCheDanga.Format("%0.2f", atof(strCheDanga)/100);
		lTemp = htonl(lTemp);
		memcpy(pBuf+124, &lTemp, 4);		pstrData += 9;		// ü��ܰ�(4)

		CString strTemp(pstrData, 8);
		lTemp = atoi(strTemp);
		lTemp = htonl(lTemp);
		memcpy(pBuf+128, &lTemp, 4);		pstrData += 8;		//��ü�����(4)

		CString strTemp1(pstrData, 9);
		lTemp = atoi(strTemp1);
		lTemp = htonl(lTemp);
		memcpy(pBuf+132, &lTemp, 4);		pstrData += 9;		// ���ü��ܰ�(4)

		CString strTemp2(pstrData, 8);
		lTemp = atoi(strTemp2);
		lTemp = htonl(lTemp);
		memcpy(pBuf+136, &lTemp, 4);		pstrData += 8;		// ��ü�����(4)

		memcpy(pBuf+140, pstrData, 8);		pstrData += 8;		// ������ұ���(8)

		//KJI 20070810 (�����ݻ����ڵ�)
		pstrData += 8;
		CString strUnAcceptCode(pstrData, 2);	pstrData += 2;	//KJI 20070810
		pstrData += 39;											//Skip(39)
		
		CString strTemp3(pstrData, 8);							
		lTemp = atoi(strTemp3);
		lTemp = htonl(lTemp);
		memcpy(pBuf+148, &lTemp, 4);		pstrData += 8;		// ��������(4)

		CString strTemp4(pstrData, 9);							
		lTemp = atoi(strTemp4);
		lTemp = htonl(lTemp);
		memcpy(pBuf+152, &lTemp, 4);		pstrData += 9;		// ���Դܰ�(4)

		memcpy(pBuf+156, pstrData, 12);		pstrData += 12;		// �̰��������ݾ�(12)
		
		if(strSFlag == "1")	//Spread �̸� ó��
		{
			pstrData += 1;										//Filler(1)

			SprBuf = new BYTE[1024];
			memcpy(SprBuf, pBuf, 313);	//KJI 20070518(�ſ��߰��� ����)

			//--> ljj 20070103 ���簡������ ������ ���ؿ� ü��ܰ��� ����
			lTemp = atoi(strCurPrice1);
			lTemp = htonl(lTemp);
			memcpy(SprBuf+168, &lTemp, 4);	pstrData += 9;	//���簡2
			//<----

			memcpy(SprBuf+74, pstrData, 12);	pstrData += 15;	//�����ڵ�

			memcpy(SprBuf+86, pstrData, 20);	pstrData += 20;	//�����

			memcpy(SprBuf+106, pstrData, 4);	pstrData += 4;	//�Ÿű���

			CString strTemp6(pstrData, 8);
			lTemp = atoi(strTemp6);
			lTemp = htonl(lTemp);
			memcpy(SprBuf+112, &lTemp, 4);	pstrData += 8;	//�ֹ�����

			CString strTemp7(pstrData, 9);							
			lTemp = atoi(strTemp7);
			lTemp = htonl(lTemp);
			memcpy(SprBuf+152, &lTemp, 4);	pstrData += 9;	// ���Դܰ�(4)

			memcpy(SprBuf+156, pstrData, 12);	pstrData += 12;	// �̰��������ݾ�(12)

			pstrData += 1;										// Filler(1)

			//KJI 20070417
			CString strJGubun(pstrData, 1);
			memcpy(SprBuf+110, strJGubun, 2);	pstrData += 1;	// �ֹ�����(1)

			memcpy(SprBuf+172, " ", 1);						//ü�ᱸ��(1)

			memcpy(SprBuf+173, strUnAcceptCode, 2);	//KJI 20070810
			memcpy(SprBuf+175, "     ", 5);			//KJI 20070810 (Filler 7->5)

			for(int nP = 180; nP < 279; nP++)	//������ ���̸� �����.
				memcpy(SprBuf+nP, " ", 1);

			memcpy(SprBuf+278, "        ", 8);				// �ֹ��ð�(8) ljj 20060530

			//KJI 20070418 (�ſ���� �߰�)
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
		memcpy(pBuf+172, " ", 1);								//ü�ᱸ��(1)
		memcpy(pBuf+173, strUnAcceptCode, 2);	//KJI 20070810
		memcpy(pBuf+175, "     ", 5);			//KJI 20070810 (Filler 7->5)

		for(int nP = 180; nP < 279; nP++)	//������ ���̸� �����.
			memcpy(pBuf+nP, " ", 1);

		memcpy(pBuf+278, "        ", 8);						// �ֹ��ð�(8) ljj 20060530

		//KJI 20070418 (�ſ���� �߰�)
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

		if( strGubun == "1")										// ü���϶�
			pConclusion->Add(strCheQuant + "���");				// ü�����(4)		
		else													// ����,���,�ź��϶�
			pConclusion->Add(strQuant + "���");					// �ֹ�����(4)		
		
		if( strGubun == "3")										// ����϶� - �ܰ��� �ʿ����.
			pConclusion->Add(" ");
		else if( strGubun == "1")								// ü���϶�
			pConclusion->Add(strCheDanga + "pt");				// ü��ܰ�(4)		
		else												
			pConclusion->Add(strDanga + "pt");					// ����,���,�ź��϶�

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
//// --> [Edit]  ������ 2010/12/20
////#ifdef	_DEBUG
//		// �ӽ�
//		CString strMsg = "";
//		strMsg.Format("�ڵ��� ����. ��������...");
//		AfxMessageBox(strMsg);
////#endif
//// <-- [Edit]  ������ 2010/12/20

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
