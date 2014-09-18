// LinkInfoHelper.h: interface for the CLinkInfoHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKINFOHELPER_H__2B9DF3A2_03AC_4D39_812B_AE9356A19829__INCLUDED_)
#define AFX_LINKINFOHELPER_H__2B9DF3A2_03AC_4D39_812B_AE9356A19829__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


typedef  int (*LPKSLINK_COMMONLINKDATA)	( LPTSTR lpszBuffer, int nSize );


class CLinkInfoHelper  
{
public:
	CLinkInfoHelper();
	virtual ~CLinkInfoHelper();

	int				Initialize		( char* szPath );
	int				LoadCommHelper	( char* szPath );
	
	int				KSLink_CommonLinkData ( LPTSTR lpszBuffer, int nSize  );

public :
	LPKSLINK_COMMONLINKDATA		m_lpfnLink_CommonLinkData;

private :
	BOOL			m_bIsInitialized;
	TCHAR			m_szCommonPath[MAX_PATH];

	HINSTANCE		m_hModLib;
};


#endif // !defined(AFX_LINKINFOHELPER_H__2B9DF3A2_03AC_4D39_812B_AE9356A19829__INCLUDED_)
