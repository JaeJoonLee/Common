// --> [Edit]  ������ 2006/04/04
#ifndef COMMON_DGN_MSG_H
#define COMMON_DGN_MSG_H
// <-- [Edit]  ������ 2006/04/04

#pragma pack(push, 1)

typedef struct tagDGNREPLYDATA
{
	int				nRpKind;						// REQUEST_KIND
	int             nMsgLen;
	char*           lpMsg;

	long			nDataSize;						// ������ ������(Ʈ���� ��� ���������� ����ó���� �ϴ� ��� ������ �ʿ���)	
	char*			pData;
} DGNREPLYDATA_st, *LPDGNREPLYDATA;


enum  DGN_REQUEST_KIND {
						DGN_REQUEST_LOGIN			,		// login
						DGN_REQUEST_LOGOUT			 ,		// logout 
						DGN_REQUEST_RQDATA			 ,		// �ü������͵�� . 
						DGN_REQUEST_RPDATA			 ,		// �ü������͵�� . 
						DGN_REQUEST_PBDATA			 ,		// Real   Data
						DGN_REQUEST_ERRDATA			 ,		// Error  Data 
						DGN_REQUEST_MESSAGE			,		// Msg Data
						DGN_REQUEST_COMPETE			,		// Msg Data
						DGN_REQUEST_TIMEOUT			 ,		// TIMEOUT Data
						};

//////////////////////////////////////////////////////////////////
// RegisterWindowMessage�� ��ϵ� �޼����� ���� WPARAM���� ������ �� .
//////////////////////////////////////////////////////////////////
//   HANDLE_CONTROL_MSG							//
// CommsDbg.exe <-> Comms.exe <-> CommAPI.dll
enum  DGN_HANDLE_CONTROL_MSG { 
						DGN_COOMS_WINDOW_HANDLE =1,	// Comms�� ������ �ڵ�.
						DGN_COMAPI_WINDOW_HANDLE,	// ComAPI�� ������ �ڵ� .
						DGN_COMMSDBG_WINDOW_HANDLE,	// ComsDBG�� ������ �ڵ�.
						DGN_STARTER_WINDOW_HANDLE	// Starter�� ������ �ڵ�.
						};

//	SOCKET_NOTIFY_MSG(������������)
// Comms.exe->CommAPI.dll
enum  DGN_SOCKET_STATUS_MSG { 
						DGN_SOCKET_CONNECTING =50,		// ���� ���� ��. 
						DGN_SOCKET_CONNECTED,		// ���� ���� �Ϸ�.
						DGN_SOCKET_CLOSED,			// ���� ���� ����.
						DGN_SOCKET_CLOSING,			// ���� ���� ��.
						DGN_SOCKET_CONNECT_FAIL,	// ���� ���� ����.
						DGN_SOCKET_RECEIVE_FAIL,	// ������ ���� ����.
						DGN_SOCKET_SEND_FAIL,		// ������ �۽� ����.
						DGN_SOCKET_SEND_SUCCESS,	// ������ �۽� ����.
						DGN_SOCKET_RECONNECT_REQUEST,// ������ ��û.
						DGN_LOGIN_COMPLETE,			// ����ó�� �Ϸ�. 
						DGN_LOGIN_FAIL,				// ����ó�� ���� .
						DGN_SOCKET_ICON_CLOSED,
						};

// COMMS_PROCCESS_MSG(������α׷� �⵿, ���α׷� ����� �����ͼ����� ��� ����)
// CommAPI.dll -> Comms.exe
//////////////////////////////////////////////////////////////////
enum  DGN_COMMS_PROCCESS_MSG { 
						DGN_COMMS_CONNECT_START = 1,	// TCP �������.
						DGN_COMMS_RECONNECT_START,		// TCP �翬�� .
						DGN_COMMS_TERMINATE,			// ���α׷� ����.
						DGN_GET_CONNECT_STATE,
						DGN_GET_SIGNON_DATA,			// ���̿� �������.
						DGN_SET_SIGNON_DATA,			// ���̿� ���¼���.
						DGN_COMMS_CONFIG_CHANGE,		// ���ȯ�� ����. 
						DGN_GET_REALKEY_DISPLPAY,		// RealŰ ����Ʈ�䱸(����׿�) .
						DGN_GET_EXCELDDE_ITEMLIST,		// Excel DDE��ũ����(����׿�) .
						DGN_SET_CONSOLAPP_CREATE,		// Consol ���α׷� �⵿ .
						DGN_GET_USERINFO_DATA,			// ����� ���� �䱸 .
						DGN_GET_USERINFO_DISPLPAY,		// ����� ��������Ʈ ǥ��(����׿�) .
						DGN_COMMS_LANG_CHANGE,			// ���� ����.
						DGN_COMMS_RECONNECT_REQUEST,  	// TCP �翬�� ��û  .
						DGN_COMMS_RQ_ID,
						DGN_COMMS_SIGNON_DATA_REQUEST,
						DGN_COMMS_CODE_DATA_REQUEST,
						};


// ������Ʈ�� �Ǵ� ���ο��� ��ȸ��û�� ���� ��ȸ���� �޼��� ������ ������ ��.
// (�����ʰ�, ��� ���ø� ��ȸ���� ���ſϷ�(��ȸ�Ϸ᳻��)ǥ��  .
// CommAPI.dll -> �� ȭ�� .
//////////////////////////////////////////////////////////////////
enum  DGN_REPLY_MESSAGE_INFO{ 
						RP_DGN_SUCCESS		= (WORD)0x00,	// ��ȸ����		����.
						RP_DGN_ERROR		= (WORD)0x02,	// ��ȸ����		����.
						RP_DGN_TIMEOUT		= (WORD)0x04	// ���Žð��ʰ� ����.
						};



//////////////////////////////////////////////////////////////////
// ComApi���� ȭ��(����,����, ���ø�)���� �����͸� �����ϱ�����.
// ����� �޼��� ���ǰ� .
//////////////////////////////////////////////////////////////////
// ȭ�鿡�� ��ȸ���䵥����(RP) ó���� �ϵ����ϴ� �޼��� .
#define WM_DGN_GET_DATA				WM_USER + 1600
/*
�Լ����� : long XXX::OnGetData(WPARAM wParam, LPARAM lParam )
								wParam : ������ ������.
								lParam : LPREPLAYDATA ����ü  .
										lpRpData = (LPREPLAYDATA)lParam;
*/
// ȭ�鿡�� �ǽð�������(PB)ó���� �ϵ����ϴ� �޼���. 
#define WM_DGN_GET_BROD				WM_USER + 1601
/*
�Լ����� : long XXX::OnGetBroa(WPARAM wParam, LPARAM lParam )
								wParam : �����ͱ��� .
								lParam : ���� �����ͳ���.
*/

#pragma pack(pop)

// --> [Edit]  ������ 2006/04/04
#endif 
// <-- [Edit]  ������ 2006/04/04
