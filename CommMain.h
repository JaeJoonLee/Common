#pragma once

#include "DataObList.h"
#include "TcpSocket.h"
#include "CommsDef.h"
#include "LogMsg.h"

// xecure
#include "XecureSLib/include/SF-Crypto.h"
#include "XecureCLib/include/xmclient.h"

// ����Ʈ������ ��ȣȭ ����
#define SESSION_START		1
#define SESSION_END			2

// CCommMain

class CCommMain : public CWnd
{
	DECLARE_DYNAMIC(CCommMain)

public:
	CCommMain(CWnd* pParentWnd,
				COMMS_CONFIG* pCommsConfig,
				CDWordArray* pArrCommApiWnd,
				CLogMsg* pLogMsg = NULL);
	virtual ~CCommMain();

// Attributes	
public:
	CWnd*				m_pParentWnd;
	HWND				m_hCommsDbgWnd;
	COMMS_CONFIG*		m_pCommsConfig;
	CLogMsg*			m_pLogMsg;
	CDWordArray*		m_pArrCommApiWnd;		// CommApi DLL�ڵ��� �迭

	UINT				m_nRetryConnectTimer;   // �翬�� Ÿ�̸� ���̵�
	UINT				m_nKeyChangeTimer;
	UINT				m_nOneSecondTimer;		// 1�� Ÿ�̸� (RQ/RP Ÿ�Ӿƿ�üũ)
	int					m_nRetryCount;			// �� ���� �õ� Ƚ��
	BOOL				m_bConnectSubPort;		// sub port�� �����ΰ�
//	int					m_nInitConnect;			// �ʱ� �������(�ؿܼ����� Ʈ����û�� �����ϱ⶧���� �÷��� �ʿ�)

	HWND				m_hCommsWnd;
	HWND				m_hLoginCommApiWnd;
	
	int					m_nPollTime;			// ���� üũ��
	BOOL				m_bConnect;				// �������
	int					m_nSignOn;				// �α׿� ���� (0:�� �α׿�,1: �α׿� �Ϸ�)

	BYTE*				m_pSendPacket;
	BYTE*				m_pReceivePacket;
	// ����
	CTcpSocket*			m_pTcpSocket;
//	BOOL				m_bSiseSocketClosed;		// ���� ����
	CRequestDataObList	m_RequestDataObList;	// Request, Reply ���̺�..
	BOOL				m_bColsolCreate;
	// ���� ������ ����û ����
//	int					m_nReConnect;			// ������ ��û ����
	// ������ ���� ó��
	HANDLE				m_hRecvEndThread;
	BOOL				m_bRecvStop;
	CWinThread*			m_pRecvTickThread;
	BOOL				m_bReadSizeDsp;			// CommsDbg�� ���� ���Ż����� ǥ�ÿ���

	BOOL				m_bUseCompress;			// ���� ��� ����
	//��ȣȭ ���� ���� �Լ� 	
	int					m_nXMConnect;
	XECURE_CTX*			m_pCtx;
	XM_CLIENT_CTX		m_XMCtx;
	BYTE				m_ucBccType;

	BOOL				m_bToBPServer;			// BP ������ ���� �ΰ�?

// --> [Edit]  ������ 2010/08/24
	// IP�� 2���� �������� ������ IP�� �����Ѵ�.
	int					m_nRePortPosition;
	//	��ü ������ �õ� Ƚ��
	int					m_nTotalRetryCount;
// <-- [Edit]  ������ 2010/08/24

	UINT				m_nWndCheckTimer;


#ifdef _SPEED_CHECK_
	// �ӵ� �׽�Ʈ��
	int					m_nSpeedCount;
	LARGE_INTEGER		m_ltimefeq, m_lstart, m_lend;
	CString				m_strSTTime;
	CString				m_strEDTime;
	int					m_nSTTick;
	int					m_nEDTick;
	int					m_nReceiveCount;
#endif

// Operations
public:
//	void	GetCommsConfigInfoRead();
	void	SetCommsDbgWndHandle(HWND hCommsDbgWnd);
	// Thread
	void	SetThreadInit( BOOL bCreate = TRUE);
	BOOL	MakeReceiveThread();
	void	ReceiveThreadStop(int nType = 0);

	BOOL	HostConnect(BOOL bInitThread = TRUE);
	void	HostDisconnect();
	void	RetryConnectToServer(int nErrorCode);
//	void	ReConnect();
	// ����
	BOOL	fnSend(BYTE* lpPacket, int nSendCount, BYTE cMsgId);
	long	SendDataToServer(BYTE* lpData, int nSendLen, BYTE cMsgId, int nSendDbg = 0);
	// ����
	void	DataReceive(BYTE* lpData, BOOL bFirst);
	void	RcvRp(BYTE* lpData, DWORD dwDataLen);
	void	RcvPb(BYTE* lpData, DWORD dwDataLen);
	BOOL	RcvSystemError(BYTE* lpData, DWORD dwDataLen);
	// ComApiWnd�� ����
	BOOL	MsgSendToCommApiWindow(PVOID lpData, DWORD dwDataLen);
	BOOL	ReleaseSendToCommApiWindow(ULONG nUniqueKey);
	BOOL	SendRealDataToCommApiWindow(BYTE* pPBData, int nDataLen);
	void	SendSocketNotifyToAllCommApi(int nStatus); // SOCKET_CLOSING
	// �α�
//	void	SetWriteLog(LPSTR szFormat, ...);
	BOOL	SendToDebugWindow(HWND, int, PVOID, WORD wKind = 0x00);
	BOOL	CommsDbgLog(LPSTR lpstr, WORD wDataType = 0x01);
	void	SetWriteConsol( char* lpData, BOOL bTitle = TRUE, BOOL bLine = FALSE);
	
	BOOL	WriteLogMsg(CString strLogMsg, CString& strMsg, int nErrorCode =-1);
	BOOL	SetWriteLog(CString strMsg, BOOL bMode = FALSE);
//  BOOL	SetLogMsgWriteToFile(CString strMsg ,BOOL bMode = TRUE);

	long	XecureInit(int nMode);
	void	XecureReceive(BYTE* lpData, DWORD dwDataLen);

	int		Encrypt(unsigned char* pInData, int nInDataLen, unsigned char* pEncBuf, int nCTXState = 0);
	int		Decrypt(unsigned char* pEncBuf, int nEncLen, unsigned char* pDecBuf);
	
	void	SendXecureErrorMessage(int nRet, int nMessageType);
	void	SendMessageToLoginWindow(int nMessage, int nMessageType, int nMessageValue);

	CString	GetTimeString();
	BOOL	CheckRealType(BYTE cCommandId);

	int		ConclusionRealProcessForBP(CString strTrCode, BYTE* pTrData, DWORD dwDataLen, BYTE* pRealData);

protected:
	afx_msg long OnSocketNotify(WPARAM wParam, LPARAM lParam);
	afx_msg long OnCopyData(UINT wParam, long lParam);

	
	afx_msg long OnSetWriteConsol(WPARAM wParam, LPARAM lParam);
	afx_msg long OnCommsDbgLog(WPARAM wParam, LPARAM lParam);
	afx_msg long OnDataReceive(WPARAM wParam, LPARAM lParam);
	afx_msg long OnRemoveCommApiCheck(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


