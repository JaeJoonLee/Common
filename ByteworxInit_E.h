
#pragma once

extern "C"
{
	int	__declspec(dllexport) BwxMakePrjmgr( LPCSTR szProjectPath, LPCSTR szProjectName );
	int BwxMakeText( CString szCurrentPath );
}