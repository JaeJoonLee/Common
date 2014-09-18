// DgnCommApiHelper.h: interface for the DgnCommApiHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DGNCOMMAPIHELPER_H__B687FC4D_A86A_42B1_BA07_7CC99C4559F4__INCLUDED_)
#define AFX_DGNCOMMAPIHELPER_H__B687FC4D_A86A_42B1_BA07_7CC99C4559F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef  int  (*LPDGNCOMMINIT)			( int nInitOption );								
typedef  void (*LPDGNCOMMTERMINATE )	( BOOL bSocketClose );
typedef  int  (*LPDGNCOMMREQUESTDATA)	( HWND hRecvWnd, char* szTrcode, BYTE* lpData, int nDataLen );
typedef  void *(*LPDGNCOMMTCPREQUESTDATA)  ( HWND hRecvWnd, char* szTrcode, BYTE* lpData, int nDataLen);

typedef  int (*LPDGNCOMMRECONNECT)			( int nRetryCount ,HWND hRecvWnd );
typedef  int (*LPDGNCOMMGETCONNECTSTATE)	( int& nConnect );
typedef  int (*LPDGNCOMMCOMMONMSGSEND)	    ( int nMsgID, WPARAM wParam, LPARAM lParam );

typedef  HWND (*LPDGNGETCOMMAPIWNDHANDLE)	( );

class DgnCommApiHelper  
{
public:
	DgnCommApiHelper();
	virtual ~DgnCommApiHelper();

public :
	
	int				DgnCommApiInitialize( int nOption , char* szPath );
	int				DgnLoadCommHelper( char* szPath );


	int				DgnCommInit( int nOption );
	void			DgnCommTerminate( BOOL bSocketClose = TRUE );	
	
	int				DgnCommRequestData  ( HWND hRecvWnd, char* szTrcode, BYTE* lpData, int nDataLen );
	void *          DgnCommTcpRequestData ( HWND hRecvWnd, char* szTrcode, BYTE* lpData, int nDataLen);
	int				DgnCommReConnect    ( int nRetryCount = 3 ,HWND hRecvWnd = NULL );
	int				DgnCommGetConnectState(int& nConnect );
	int				DgnCommCommonMsgSend( int nMsgID, WPARAM wParam, LPARAM lParam  );
	int				DgnCommGetCommsWindowHandle ( HWND& hDgnComApiWnd );

private :
	BOOL			m_bIsInitialized;
	TCHAR			m_szCommonPath[MAX_PATH];

	HINSTANCE		m_hDgnCommAPILib;

	LPDGNCOMMINIT			 m_lpfnDgnCommInit;
	LPDGNCOMMTERMINATE		 m_lpfnDgnCommTerminate;
	LPDGNCOMMREQUESTDATA	 m_lpfnDgnCommRequestData;
	LPDGNCOMMTCPREQUESTDATA	 m_lpfnDgnCommTcpRequestData;
	LPDGNCOMMGETCONNECTSTATE m_lpfnDgnCommGetConnectState;
	LPDGNCOMMRECONNECT		 m_lpfnDgnCommReConnect;
	LPDGNCOMMCOMMONMSGSEND	 m_lpfnDgnCommCommonMsgSend; 
	LPDGNGETCOMMAPIWNDHANDLE m_lpfnDgnGetCommApiWndHandle; 


};

#endif // !defined(AFX_DGNCOMMAPIHELPER_H__B687FC4D_A86A_42B1_BA07_7CC99C4559F4__INCLUDED_)
