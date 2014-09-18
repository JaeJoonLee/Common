#if !defined(_COMMSDEF_H_)
#define _COMMSDEF_H_

//WM_USER_SOCKET_NOTIFY lParam �� ���� Flag�� ���� 
enum 
{
	TCP_SOCKET_READ					= 1000,	// Socket���� ����  Read Signal�߻�.
	TCP_SOCKET_WRITE			,	//1001 Socket���� ����  Read Signal�߻�.
	TCP_SOCKET_OOB				,	//1002
	TCP_SOCKET_ACCEPT			,	//1003
	TCP_SOCKET_CONNECT			,	//1004
	TCP_SOCKET_CLOSE			,	//1005
	TCP_SOCKET_CLOSING			,	//1006
	TCP_SOCKET_CONNECT_SUCCESS	,	//1007
	TCP_SOCKET_CONNECT_FAIL		,	//1008
	TCP_SOCKET_CONNECTING		,	//1009		// ������ �õ��Ѵ�.
	TCP_SOCKET_ADDR_IP_NOTFOUND	,	//1010		// IP�� ���� ���ߴ�.
	TCP_SOCKET_CREATE_ERR		,	//1011
	COMAPI_CONNECTING			,	//1012
	TCP_SOCKET_SERVER_POLL		,
	COMAPI_CONNECTING2			,	// �ι�° Session�� �����Ѵ�.
	TCP_SOCKET_CONNECTING2		,   // �ι�° Session���� ������ �Ǿ���.			
	TCP_SOCKET_CONNECT_SUCCESS2	,	// �ι�° ���� ����.
	TCP_SOCKET_CREATE_ERR2		,   // �ι�° Socket �� �����ϴ� ����.
	TCP_SOCKET_CONNECT_FAIL2	,	// �ι��� Socket ���� ����.
	TCP_SOCKET_CONNECT2			,   // �ι�°
	TCP_SOCKET_PROXY_CONNECTING	,	// Proxy ������ ������ �Ǿ���.
	TCP_SOCKET_PROXY_CONNECTING2	,	// Proxy ������ ������ �Ǿ���.

};


#define WM_COMMS_PROGRAM_CLOSE			WM_USER + 201
#define WM_USER_SOCKET_NOTIFY				WM_USER + 202
#define WM_SISE_SOCKET_NOTIFY				WM_USER + 203
#define UM_RECONNECT_TIMER					WM_USER + 301	// ���Ͽ��� ���н� �� ���� Ÿ�̸� ����.
#define UM_ONESECONDTIMER					WM_USER + 302	// 1�ʸ��� �ѹ��� RQ���̺��� RQ TimeOut�� üũ�Ѵ�.
#define UM_HEARTBEATTIMER					WM_USER + 303	// 1�и��� CommAPI�� �����ϴ¸� üũ�Ѵ�.
#define UM_DISCONNECT						WM_USER + 304
#define UM_LOG_CONSOL						WM_USER + 305	// consol�� �α� ��� �ϱ� ����
#define UM_LOG_COMS_DBG						WM_USER + 306	// ComsDbg�� �α׸� ��� �ϱ� ����
#define UM_DATA_RECEIVE						WM_USER + 307	// ���� �Ϸ� ��Ŷ ó���� ����
#define UM_SET_TRAYICON_STATUS				WM_USER + 308	// TrayIcon ���� ���� ó��
#define UM_SEND_SOCKET_NOTIFY_TO_COMMAPI	WM_USER + 309	// 
#define	UM_WND_STATE_CHECK					WM_USER + 310	// CommApi üũ�� �����ִ� CommApi�� ������� �����ϴ� �޽���

//#define RECONNECT_TIMER_VALUE		10000			// 10��

#define FD_CONNECT_SUCCESS			0x40
#define FD_CONNECT_FAIL				0x42

const UINT g_AnyTrayPopupMenuID		= WM_APP + 1;

/*
 * Define flags to be used with the WSAAsyncSelect() call.
*/

//const UINT KunIconIDs[] = { IDI_ICON0, IDI_ICON1, IDI_ICON2, IDI_ICON3, 0};


#define	 ARRAYCOUNT( array )		(sizeof(array) /sizeof(array[0]))

// ��� ����
#define PROTOCOL_TCPIP		0							// TCP/IP


// �������ϸ� ����
#define COMMS_INI_FILE		"\\system\\Comms.ini"		// ������� ���ϸ�
#define COMMS_USERINI_FILE	"\\System\\CommsU.ini"		// ������� ���ϸ�

#define	IDS_COMMS_NAME		_T("HwComms1.0")
#define	IDS_COMMS_CLASS		_T("_HwComms")
#define	IDS_COMMSDBG_NAME	_T("_HwCommsDbgClass")
#define	IDS_COMMAPI_NAME	_T("Hw_COMMAPI")


#endif // !defined(_COMMSDEF_H_)
