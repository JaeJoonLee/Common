#if !defined(_COMMSDEF_H_)
#define _COMMSDEF_H_

//WM_USER_SOCKET_NOTIFY lParam 의 하위 Flag값 정의 
enum 
{
	TCP_SOCKET_READ					= 1000,	// Socket으로 부터  Read Signal발생.
	TCP_SOCKET_WRITE			,	//1001 Socket으로 부터  Read Signal발생.
	TCP_SOCKET_OOB				,	//1002
	TCP_SOCKET_ACCEPT			,	//1003
	TCP_SOCKET_CONNECT			,	//1004
	TCP_SOCKET_CLOSE			,	//1005
	TCP_SOCKET_CLOSING			,	//1006
	TCP_SOCKET_CONNECT_SUCCESS	,	//1007
	TCP_SOCKET_CONNECT_FAIL		,	//1008
	TCP_SOCKET_CONNECTING		,	//1009		// 연결을 시도한다.
	TCP_SOCKET_ADDR_IP_NOTFOUND	,	//1010		// IP를 얻지 못했다.
	TCP_SOCKET_CREATE_ERR		,	//1011
	COMAPI_CONNECTING			,	//1012
	TCP_SOCKET_SERVER_POLL		,
	COMAPI_CONNECTING2			,	// 두번째 Session을 연결한다.
	TCP_SOCKET_CONNECTING2		,   // 두번째 Session으로 접속이 되었다.			
	TCP_SOCKET_CONNECT_SUCCESS2	,	// 두번째 접속 성공.
	TCP_SOCKET_CREATE_ERR2		,   // 두번째 Socket 을 생성하다 실패.
	TCP_SOCKET_CONNECT_FAIL2	,	// 두번재 Socket 접속 실패.
	TCP_SOCKET_CONNECT2			,   // 두번째
	TCP_SOCKET_PROXY_CONNECTING	,	// Proxy 서버에 접속이 되었다.
	TCP_SOCKET_PROXY_CONNECTING2	,	// Proxy 서버에 접속이 되었다.

};


#define WM_COMMS_PROGRAM_CLOSE			WM_USER + 201
#define WM_USER_SOCKET_NOTIFY				WM_USER + 202
#define WM_SISE_SOCKET_NOTIFY				WM_USER + 203
#define UM_RECONNECT_TIMER					WM_USER + 301	// 소켓연결 실패시 재 접속 타이머 정의.
#define UM_ONESECONDTIMER					WM_USER + 302	// 1초마다 한번씩 RQ테이블의 RQ TimeOut을 체크한다.
#define UM_HEARTBEATTIMER					WM_USER + 303	// 1분마다 CommAPI가 존재하는를 체크한다.
#define UM_DISCONNECT						WM_USER + 304
#define UM_LOG_CONSOL						WM_USER + 305	// consol에 로그 기록 하기 위해
#define UM_LOG_COMS_DBG						WM_USER + 306	// ComsDbg에 로그를 기록 하기 위해
#define UM_DATA_RECEIVE						WM_USER + 307	// 수신 완료 패킷 처리를 위해
#define UM_SET_TRAYICON_STATUS				WM_USER + 308	// TrayIcon 상태 변경 처리
#define UM_SEND_SOCKET_NOTIFY_TO_COMMAPI	WM_USER + 309	// 
#define	UM_WND_STATE_CHECK					WM_USER + 310	// CommApi 체크후 남아있는 CommApi가 없을경우 종료하는 메시지

//#define RECONNECT_TIMER_VALUE		10000			// 10초

#define FD_CONNECT_SUCCESS			0x40
#define FD_CONNECT_FAIL				0x42

const UINT g_AnyTrayPopupMenuID		= WM_APP + 1;

/*
 * Define flags to be used with the WSAAsyncSelect() call.
*/

//const UINT KunIconIDs[] = { IDI_ICON0, IDI_ICON1, IDI_ICON2, IDI_ICON3, 0};


#define	 ARRAYCOUNT( array )		(sizeof(array) /sizeof(array[0]))

// 통신 종류
#define PROTOCOL_TCPIP		0							// TCP/IP


// 정보파일명 정의
#define COMMS_INI_FILE		"\\system\\Comms.ini"		// 통신정보 파일명
#define COMMS_USERINI_FILE	"\\System\\CommsU.ini"		// 통신정보 파일명

#define	IDS_COMMS_NAME		_T("HwComms1.0")
#define	IDS_COMMS_CLASS		_T("_HwComms")
#define	IDS_COMMSDBG_NAME	_T("_HwCommsDbgClass")
#define	IDS_COMMAPI_NAME	_T("Hw_COMMAPI")


#endif // !defined(_COMMSDEF_H_)
