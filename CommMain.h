#pragma once

#include "DataObList.h"
#include "TcpSocket.h"
#include "CommsDef.h"
#include "LogMsg.h"

// xecure
#include "XecureSLib/include/SF-Crypto.h"
#include "XecureCLib/include/xmclient.h"

// 소프트포럼의 암호화 관련
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
	CDWordArray*		m_pArrCommApiWnd;		// CommApi DLL핸들의 배열

	UINT				m_nRetryConnectTimer;   // 재연결 타이머 아이디값
	UINT				m_nKeyChangeTimer;
	UINT				m_nOneSecondTimer;		// 1초 타이머 (RQ/RP 타임아웃체크)
	int					m_nRetryCount;			// 재 접속 시도 횟수
	BOOL				m_bConnectSubPort;		// sub port로 접속인가
//	int					m_nInitConnect;			// 초기 연결상태(해외서버는 트랜요청시 연결하기때문에 플래그 필요)

	HWND				m_hCommsWnd;
	HWND				m_hLoginCommApiWnd;
	
	int					m_nPollTime;			// 폴링 체크용
	BOOL				m_bConnect;				// 연결상태
	int					m_nSignOn;				// 로그온 상태 (0:미 로그온,1: 로그온 완료)

	BYTE*				m_pSendPacket;
	BYTE*				m_pReceivePacket;
	// 소켓
	CTcpSocket*			m_pTcpSocket;
//	BOOL				m_bSiseSocketClosed;		// 소켓 종료
	CRequestDataObList	m_RequestDataObList;	// Request, Reply 테이블..
	BOOL				m_bColsolCreate;
	// 소켓 단절시 제요청 관련
//	int					m_nReConnect;			// 재접속 요청 상태
	// 스레드 관련 처리
	HANDLE				m_hRecvEndThread;
	BOOL				m_bRecvStop;
	CWinThread*			m_pRecvTickThread;
	BOOL				m_bReadSizeDsp;			// CommsDbg에 소켓 수신사이즈 표시여부

	BOOL				m_bUseCompress;			// 압축 사용 유무
	//암호화 관련 변수 함수 	
	int					m_nXMConnect;
	XECURE_CTX*			m_pCtx;
	XM_CLIENT_CTX		m_XMCtx;
	BYTE				m_ucBccType;

	BOOL				m_bToBPServer;			// BP 서버로 접속 인가?

// --> [Edit]  강지원 2010/08/24
	// IP가 2개라 랜덤으로 생성한 IP로 접속한다.
	int					m_nRePortPosition;
	//	전체 재접속 시도 횟수
	int					m_nTotalRetryCount;
// <-- [Edit]  강지원 2010/08/24

	UINT				m_nWndCheckTimer;


#ifdef _SPEED_CHECK_
	// 속도 테스트용
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
	// 전송
	BOOL	fnSend(BYTE* lpPacket, int nSendCount, BYTE cMsgId);
	long	SendDataToServer(BYTE* lpData, int nSendLen, BYTE cMsgId, int nSendDbg = 0);
	// 수신
	void	DataReceive(BYTE* lpData, BOOL bFirst);
	void	RcvRp(BYTE* lpData, DWORD dwDataLen);
	void	RcvPb(BYTE* lpData, DWORD dwDataLen);
	BOOL	RcvSystemError(BYTE* lpData, DWORD dwDataLen);
	// ComApiWnd에 전송
	BOOL	MsgSendToCommApiWindow(PVOID lpData, DWORD dwDataLen);
	BOOL	ReleaseSendToCommApiWindow(ULONG nUniqueKey);
	BOOL	SendRealDataToCommApiWindow(BYTE* pPBData, int nDataLen);
	void	SendSocketNotifyToAllCommApi(int nStatus); // SOCKET_CLOSING
	// 로그
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


