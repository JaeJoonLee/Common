// --> [Edit]  김정원 2006/04/04
#ifndef COMMON_DGN_MSG_H
#define COMMON_DGN_MSG_H
// <-- [Edit]  김정원 2006/04/04

#pragma pack(push, 1)

typedef struct tagDGNREPLYDATA
{
	int				nRpKind;						// REQUEST_KIND
	int             nMsgLen;
	char*           lpMsg;

	long			nDataSize;						// 데이터 사이즈(트랜인 경우 가변적으로 예외처리를 하는 경우 사이즈 필요함)	
	char*			pData;
} DGNREPLYDATA_st, *LPDGNREPLYDATA;


enum  DGN_REQUEST_KIND {
						DGN_REQUEST_LOGIN			,		// login
						DGN_REQUEST_LOGOUT			 ,		// logout 
						DGN_REQUEST_RQDATA			 ,		// 시세데이터등록 . 
						DGN_REQUEST_RPDATA			 ,		// 시세데이터등록 . 
						DGN_REQUEST_PBDATA			 ,		// Real   Data
						DGN_REQUEST_ERRDATA			 ,		// Error  Data 
						DGN_REQUEST_MESSAGE			,		// Msg Data
						DGN_REQUEST_COMPETE			,		// Msg Data
						DGN_REQUEST_TIMEOUT			 ,		// TIMEOUT Data
						};

//////////////////////////////////////////////////////////////////
// RegisterWindowMessage로 등록된 메세지에 대한 WPARAM값을 정의한 값 .
//////////////////////////////////////////////////////////////////
//   HANDLE_CONTROL_MSG							//
// CommsDbg.exe <-> Comms.exe <-> CommAPI.dll
enum  DGN_HANDLE_CONTROL_MSG { 
						DGN_COOMS_WINDOW_HANDLE =1,	// Comms의 윈도우 핸들.
						DGN_COMAPI_WINDOW_HANDLE,	// ComAPI의 윈도우 핸들 .
						DGN_COMMSDBG_WINDOW_HANDLE,	// ComsDBG의 윈도우 핸들.
						DGN_STARTER_WINDOW_HANDLE	// Starter의 윈도우 핸들.
						};

//	SOCKET_NOTIFY_MSG(소켓통지관련)
// Comms.exe->CommAPI.dll
enum  DGN_SOCKET_STATUS_MSG { 
						DGN_SOCKET_CONNECTING =50,		// 소켓 연결 중. 
						DGN_SOCKET_CONNECTED,		// 소켓 연결 완료.
						DGN_SOCKET_CLOSED,			// 소켓 단절 상태.
						DGN_SOCKET_CLOSING,			// 소켓 단절 중.
						DGN_SOCKET_CONNECT_FAIL,	// 소켓 연결 실패.
						DGN_SOCKET_RECEIVE_FAIL,	// 데이터 수신 실패.
						DGN_SOCKET_SEND_FAIL,		// 데이터 송신 실패.
						DGN_SOCKET_SEND_SUCCESS,	// 데이터 송신 성공.
						DGN_SOCKET_RECONNECT_REQUEST,// 재접속 요청.
						DGN_LOGIN_COMPLETE,			// 승인처리 완료. 
						DGN_LOGIN_FAIL,				// 승인처리 실패 .
						DGN_SOCKET_ICON_CLOSED,
						};

// COMMS_PROCCESS_MSG(통신프로그램 기동, 프로그램 종료및 데이터설정및 취득 관련)
// CommAPI.dll -> Comms.exe
//////////////////////////////////////////////////////////////////
enum  DGN_COMMS_PROCCESS_MSG { 
						DGN_COMMS_CONNECT_START = 1,	// TCP 연결시작.
						DGN_COMMS_RECONNECT_START,		// TCP 재연결 .
						DGN_COMMS_TERMINATE,			// 프로그램 종료.
						DGN_GET_CONNECT_STATE,
						DGN_GET_SIGNON_DATA,			// 사이온 상태취득.
						DGN_SET_SIGNON_DATA,			// 사이온 상태설정.
						DGN_COMMS_CONFIG_CHANGE,		// 통신환경 변경. 
						DGN_GET_REALKEY_DISPLPAY,		// Real키 리스트요구(디버그용) .
						DGN_GET_EXCELDDE_ITEMLIST,		// Excel DDE링크정보(디버그용) .
						DGN_SET_CONSOLAPP_CREATE,		// Consol 프로그램 기동 .
						DGN_GET_USERINFO_DATA,			// 사용자 정보 요구 .
						DGN_GET_USERINFO_DISPLPAY,		// 사용자 정보리스트 표시(디버그용) .
						DGN_COMMS_LANG_CHANGE,			// 언어변경 통지.
						DGN_COMMS_RECONNECT_REQUEST,  	// TCP 재연결 요청  .
						DGN_COMMS_RQ_ID,
						DGN_COMMS_SIGNON_DATA_REQUEST,
						DGN_COMMS_CODE_DATA_REQUEST,
						};


// 쿼리컨트롤 또는 메인에서 조회요청에 대한 조회응답 메세지 정보를 정의한 값.
// (수신초과, 모든 템플릿 조회응답 수신완료(조회완료내용)표시  .
// CommAPI.dll -> 각 화면 .
//////////////////////////////////////////////////////////////////
enum  DGN_REPLY_MESSAGE_INFO{ 
						RP_DGN_SUCCESS		= (WORD)0x00,	// 조회정상		정보.
						RP_DGN_ERROR		= (WORD)0x02,	// 조회에러		정보.
						RP_DGN_TIMEOUT		= (WORD)0x04	// 수신시간초과 정보.
						};



//////////////////////////////////////////////////////////////////
// ComApi에서 화면(쿼리,메인, 템플릿)으로 데이터를 전달하기위한.
// 사용자 메세지 정의값 .
//////////////////////////////////////////////////////////////////
// 화면에게 조회응답데이터(RP) 처리를 하도록하는 메세지 .
#define WM_DGN_GET_DATA				WM_USER + 1600
/*
함수형식 : long XXX::OnGetData(WPARAM wParam, LPARAM lParam )
								wParam : 데이터 구분자.
								lParam : LPREPLAYDATA 구조체  .
										lpRpData = (LPREPLAYDATA)lParam;
*/
// 화면에게 실시간데이터(PB)처리를 하도록하는 메세지. 
#define WM_DGN_GET_BROD				WM_USER + 1601
/*
함수형식 : long XXX::OnGetBroa(WPARAM wParam, LPARAM lParam )
								wParam : 데이터길이 .
								lParam : 실제 데이터내용.
*/

#pragma pack(pop)

// --> [Edit]  김정원 2006/04/04
#endif 
// <-- [Edit]  김정원 2006/04/04
