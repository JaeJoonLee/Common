#if !defined(AFX_TCPSOCKET_H__A6343943_00A3_431A_82C2_B49BDAB903EC__INCLUDED_)
#define AFX_TCPSOCKET_H__A6343943_00A3_431A_82C2_B49BDAB903EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TcpSocket.h : header file
//
#include <process.h>
#include <afxmt.h>

//#include "CommUtil.h"

//*****************************************************************************
// Revision By:  �� â�� Revision Day:  2004��12��30��
// Comments: ...
//*****************************************************************************
#pragma warning (disable:4786)
#include <queue>
//*****************************************************************************
typedef std::pair<int, BYTE*>	RecvDataPair;


////////////////////////////////////////
//-> 2012.02.28 jhj ������ ��Ŷ ���� ����Ʈ EzNet Smart �� ���� ������!!
#define ERP_COMM_LENGTH_CHECK_ERROR		'1'
#define ERP_COMM_BCC_CHECK_ERROR		'2'
#define ERP_COMM_BCC_MEMORY_FAILED		'3'
#define ERP_COMM_NOT_FOUND				'4'
#define ERP_COMM_CERT_ERROR				'5'
#define ERP_COMM_QUEUE_FULLED			'6'
#define ERP_COMM_PACKET_RECOVERY_OK		'7'
#define ERP_COMM_PACKET_RECOVERY_FAILED	'8'
#define ERP_COMM_PACKET_CRECOVERY_OK	'9'

#define MAX_ERR_REPORT_TITLE         254
#define MAX_ERR_REPORT_RAW_BUFFER    4096
#define MAX_ERR_REPORT_SZ_LEN        4

typedef struct tagERR_REPORT_BUFFER {
	char szType;
	char filler_1;
	char szTitle[MAX_ERR_REPORT_TITLE];
	char filler_2[2];
	char szLenBuffer[MAX_ERR_REPORT_SZ_LEN];
	char filler_3;
	char szRealLenBuffer[MAX_ERR_REPORT_SZ_LEN];
	char filler_4;
	char pRawDataBuffer[MAX_ERR_REPORT_RAW_BUFFER];
} ERR_REPORT_BUFFER;

#define SZ_ERR_REPORT_BUFFER	sizeof(ERR_REPORT_BUFFER)
#define SZ_HD_ERR_REPORT_BUFFER	(sizeof(ERR_REPORT_BUFFER)-MAX_ERR_REPORT_RAW_BUFFER)

////////////////////////////////////////
#define	HEADLEN_SIZ			4	//��������� ����Ÿ ������
#define	HEADERLEN			12	//winowhandle����� �� ������� ������(4 + 1 + 1 + 1 + 1 + 4)
#define DATASTART_POS		16	//shc 20030506	HEADLEN_SIZ + HEADERLEN
#define	SZ_LG				4
#define QRYCODE_LEN			8
	
#define MEM_PAGE_SIZE       4096
#define MAX_COMP_SENDSIZ	2048
// END ADD NEOFRAME KHY : 20050524
#define SZ_CLIENT_CHAIN_UNIQID      32
#define SZ_CLIENT_CHAIN_FRAME_NO    6
#define SZ_CLIENT_CHAIN_FRAME_SIZE  6
#define SZ_CLIENT_CHAIN_DATA_SIZE   12    
#define MAX_COMP_SENDSIZ            2048


// ADD NEOFRAME KHY : 20050524
#define PC_COMPRESS     0x80    /* ��������BIT */
#define PC_COMP_RE      0x7f    /* ��������BIT REVERSE */
#define PC_CIPHER       0x40    /* ��ȣȭ����BIT */
#define PC_CIPHER_RE    0xbf    /* ��ȣȭ����BIT REVERSE */
#define PC_COMP_CIP_RE  0x3f    /* �����ȣȭ����BIT REVERSE */
#define PC_PACKS        0x08    /* ��Ŷ����BIT */
#define PC_PACKM        0x04    /* ��Ŷ����BIT */
#define PC_PACKE        0x02    /* ��Ŷ��BIT */
#define PC_COMPRESS_FAILED 0x10    /* �����Ϸ��ٰ� ������ ��쿡 �ø��� Bit */
// END ADD NEOFRAME KHY : 20050524
//<-

/////////////////////////////////////////////////////////////////////////////
// CTcpSocket command target
class CTcpSocket : public CObject
{
	DECLARE_DYNAMIC(CTcpSocket);

	enum	{ receives = 0, sends = 1, both = 2 };
// Attributes
private:
	CCriticalSection	m_sect;
	SOCKET				m_hSocket;				// instances which refer to sockets.
	int					m_nSocketErrorCode;

	CString				m_strHostAddress;
	int					m_nHostPort;

	unsigned int		m_nRecvThreadID;
	HANDLE				m_hRecvThread;
	HANDLE				m_hRecvStopEvent;

	CWnd*				m_pParentWnd;
	
	BOOL				m_bReadSizeDsp;
	BOOL				m_bAllSetCompleted;
	long				m_lDataIndex;
	BOOL				m_bFirstDown;

	int					m_nTotalFileCount;		// ��ü ���� ���� ��
	int					m_nReceivedFileCount;	// ���� ���� ��

	BOOL				m_bColsolCreate;
	HWND				m_hCommsDbgWnd;			// CommsDbgWnd
	BOOL				m_bIPShare;				// ������ ��� ����

// Operations
public:
	CTcpSocket( CWnd* pParentWnd = NULL);
	void	SetHostAddressAndPort( CString strHost, int nHostPort);

	CString m_strCommonPath;

	BOOL	CreateTCPSocket();
	BOOL	ConnectTCPSocket( );

	BOOL    DisConnectTCPSocket();

	BOOL	GetSockName(CString& strSocketAddress, UINT& nSocketPort);

	BOOL	IsConnecting()							{ return ( m_hSocket != INVALID_SOCKET );}
	SOCKET	GetSocketFromHandle ()					{ return m_hSocket; }
	int		GetLastError()							{ m_nSocketErrorCode;}
	int		GetSocketErrorCode()					{ return ::WSAGetLastError();}
	void    SetAllRealReset(BOOL bReset )			{ m_bAllSetCompleted = bReset;}
	BOOL	IsValidSocketHandle();

	void	SetTotalReceiveFileCount(int nCount)	{ m_nTotalFileCount = nCount;}
	void	SetReceivedFileCount(int nReceivedFile)	{ m_nReceivedFileCount = nReceivedFile;}

	int		Receive( void* lpBuf, int nBufLen, int nFlags = 0);
	int		Send( const void* lpBuf, int nBufLen, int nFlags = 0);

	int		CheckSendable();
	BOOL    ReceiveStopEvent(BOOL bSignal = TRUE);
	int     GetSocketInfo ( DWORD& wSocketBytes );

	int		GetHostPort(){ return m_nHostPort; } //KMG 2012.03.12

// Implementation
public:
	virtual ~CTcpSocket();
	BOOL	CreateSocketReadThread();
	virtual void    StartReceive();
	static UINT __stdcall RecvTCPSocketThread( void* pParam );

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// ������ ���� ���� data�� Queue�� �����Ѵ�.
	std::queue<RecvDataPair>		m_RecvDataPairQue;
	void							AddSocketData(BYTE* lpData, BOOL bFirst, int nLength);

	//-----------------------------------------------------------------------------
	// MainFrame���� ������ Session���� �Ҵ��� �Ǿ��� Queue���� �о�� ����Ѵ�.
	// MultiSessionó���� MainFrame���� �������� �Ű�����.
	BOOL	m_bRecvStop;
	void	AllRecvDataQueueClear();
	int		GetReadRecvQueueData(  RecvDataPair& DataQue);
	int		SetWriteRecvQueueData( RecvDataPair& DataQue); 
	void	ReceiveTick();
	CString	GetServerIPfromEnpiaDNS(CString strDomainName);
	int		GetQueueSize();
	
	void	SetWriteConsol(char* pBuf);
	BOOL	CommsDbgLog(LPSTR lpstr, WORD wDataType = 0x01);
	void	DataReceive(BYTE* pData, int nFirst);

	//-> 2012.02.28 jhj 
	long				m_nPacketId;			// packet ���� id
	CCriticalSection	m_PacketSendLock;	// ADD NEOFRAME KHY 
	time_t				m_SendErrorReportTime;	// ADD NEOFRAME KHY 
	BYTE				m_ucBccType;
	long				m_lMaxSeq;

	BOOL	RecvDataBlock(char *packetBuf, long nBufSize);
	BOOL	SendErrorReport(BOOL bForce,BYTE chType,LPCTSTR lpszErrorReport=NULL,BYTE *pRawBuffer=NULL,int nRawDataLen=0);
	virtual BOOL SendRawPacket(HWND hWnd, unsigned char chPacketType, char *packetBuf, long nBufSiz,unsigned char chChainFlg=0);
	virtual BOOL SendDataBlock(char *packetBuf, long nBufSiz);

	void    WriteErrorLog(CString sLog);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPSOCKET_H__A6343943_00A3_431A_82C2_B49BDAB903EC__INCLUDED_)
