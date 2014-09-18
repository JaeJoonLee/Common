// Monitor.cpp: implementation of the CMonitor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Monitor.h"
#include <afxtempl.h>
//#include <multimon.h>
#include "KHResource.h"
//#include "Winuser.h"
//#include "Windows.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define	COMPILE_MULTIMON_STUBS


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonitor::CMonitor()
{

}

CMonitor::~CMonitor()
{

}


#ifndef VER_NT_WORKSTATION
	#define VER_NT_WORKSTATION			0x00000001
#endif
#ifndef VER_NT_DOMAIN_CONTROLLER
	#define VER_NT_DOMAIN_CONTROLLER	0x00000002
#endif
#ifndef VER_NT_SERVER
	#define VER_NT_SERVER				0x00000003
#endif
#ifndef VER_SUITE_DATACENTER	
	#define	VER_SUITE_DATACENTER		0x00000080
#endif
#ifndef VER_SUITE_ENTERPRISE	
	#define	VER_SUITE_ENTERPRISE		0x00000002
#endif
#ifndef VER_SUITE_PERSONAL	
	#define	VER_SUITE_PERSONAL			0x00000200
#endif
#ifndef VER_SUITE_STORAGE_SERVER
	#define VER_SUITE_STORAGE_SERVER	0x00002000
#endif
#ifndef VER_SUITE_COMPUTE_SERVER
	#define VER_SUITE_COMPUTE_SERVER	0x00004000
#endif
#ifndef VER_SUITE_BLADE
	#define VER_SUITE_BLADE				0x00000400
#endif


#ifndef PRODUCT_BUSINESS
	#define PRODUCT_BUSINESS				0x00000006
#endif
#ifndef PRODUCT_BUSINESS_N
	#define PRODUCT_BUSINESS_N				0x00000010
#endif
#ifndef PRODUCT_CLUSTER_SERVER
	#define PRODUCT_CLUSTER_SERVER			0x00000012
#endif
#ifndef PRODUCT_DATACENTER_SERVER	
	#define	PRODUCT_DATACENTER_SERVER		0x00000008
#endif
#ifndef PRODUCT_DATACENTER_SERVER_CORE	
	#define	PRODUCT_DATACENTER_SERVER_CORE	0x0000000C
#endif
#ifndef PRODUCT_ENTERPRISE	
	#define	PRODUCT_ENTERPRISE				0x00000004
#endif
#ifndef PRODUCT_ENTERPRISE_N
	#define PRODUCT_ENTERPRISE_N			0x0000001B
#endif
#ifndef PRODUCT_ENTERPRISE_SERVER
	#define PRODUCT_ENTERPRISE_SERVER		0x0000000A
#endif
#ifndef PRODUCT_ENTERPRISE_SERVER_CORE
	#define PRODUCT_ENTERPRISE_SERVER_CORE	0x0000000E
#endif
#ifndef PRODUCT_ENTERPRISE_SERVER_IA64	
	#define	PRODUCT_ENTERPRISE_SERVER_IA64	0x0000000F
#endif
#ifndef PRODUCT_HOME_BASIC	
	#define	PRODUCT_HOME_BASIC				0x00000002
#endif
#ifndef PRODUCT_HOME_BASIC_N	
	#define	PRODUCT_HOME_BASIC_N			0x00000005
#endif
#ifndef PRODUCT_HOME_PREMIUM
	#define PRODUCT_HOME_PREMIUM			0x00000003
#endif
#ifndef PRODUCT_HOME_PREMIUM_N
	#define PRODUCT_HOME_PREMIUM_N			0x0000001A
#endif
#ifndef PRODUCT_HOME_SERVER
	#define PRODUCT_HOME_SERVER				0x00000013
#endif
#ifndef PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT	
	#define	PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT	0x0000001E
#endif
#ifndef PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING	
	#define	PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING		0x00000020
#endif
#ifndef PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY	
	#define	PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY		0x0000001F
#endif
#ifndef PRODUCT_SERVER_FOR_SMALLBUSINESS
	#define PRODUCT_SERVER_FOR_SMALLBUSINESS			0x00000018
#endif
#ifndef PRODUCT_SMALLBUSINESS_SERVER
	#define PRODUCT_SMALLBUSINESS_SERVER				0x00000009
#endif
#ifndef PRODUCT_SMALLBUSINESS_SERVER_PREMIUM
	#define PRODUCT_SMALLBUSINESS_SERVER_PREMIUM		0x00000019
#endif
#ifndef PRODUCT_STANDARD_SERVER	
	#define	PRODUCT_STANDARD_SERVER			0x00000007
#endif
#ifndef PRODUCT_STANDARD_SERVER_CORE 	
	#define	PRODUCT_STANDARD_SERVER_CORE 	0x0000000D
#endif
#ifndef PRODUCT_STARTER	
	#define	PRODUCT_STARTER					0x0000000B
#endif
#ifndef PRODUCT_STORAGE_ENTERPRISE_SERVER
	#define PRODUCT_STORAGE_ENTERPRISE_SERVER	0x00000017
#endif
#ifndef PRODUCT_STORAGE_EXPRESS_SERVER
	#define PRODUCT_STORAGE_EXPRESS_SERVER		0x00000014
#endif
#ifndef PRODUCT_STORAGE_STANDARD_SERVER
	#define PRODUCT_STORAGE_STANDARD_SERVER		0x00000015
#endif
#ifndef PRODUCT_STORAGE_WORKGROUP_SERVER	
	#define	PRODUCT_STORAGE_WORKGROUP_SERVER	0x00000016
#endif
#ifndef PRODUCT_UNDEFINED
	#define	PRODUCT_UNDEFINED				0x00000000
#endif
#ifndef PRODUCT_ULTIMATE	
	#define	PRODUCT_ULTIMATE				0x00000001
#endif
#ifndef PRODUCT_ULTIMATE_N
	#define PRODUCT_ULTIMATE_N				0x0000001C
#endif
#ifndef PRODUCT_WEB_SERVER
	#define PRODUCT_WEB_SERVER				0x00000011
#endif
#ifndef PRODUCT_WEB_SERVER
	#define PRODUCT_WEB_SERVER				0x0000001D
#endif

#ifndef PROCESSOR_ARCHITECTURE_AMD64
	#define PROCESSOR_ARCHITECTURE_AMD64		9
#endif
#ifndef PROCESSOR_ARCHITECTURE_IA64
	#define PROCESSOR_ARCHITECTURE_IA64			6
#endif
#ifndef PROCESSOR_ARCHITECTURE_INTEL
	#define PROCESSOR_ARCHITECTURE_INTEL		0
#endif
#ifndef PROCESSOR_ARCHITECTURE_UNKNOWN
	#define PROCESSOR_ARCHITECTURE_UNKNOWN		0xffff
#endif

#ifndef SM_SERVERR2
	#define SM_SERVERR2		89
#endif

/////	OS Version('1' : 95, '2' : 98, '3' : ME, '4' : NT, '5' : 2000, '6' : XP, '7' : Windows Vista, '8' : 기타)
int GetOSVersionInfo(char	*szOSName)
{
/*
#ifndef VER_NT_WORKSTATION
	#define VER_NT_WORKSTATION	0x00000001
#endif
#ifndef VER_NT_DOMAIN_CONTROLLER
	#define VER_NT_DOMAIN_CONTROLLER	0x00000002
#endif
#ifndef VER_NT_SERVER
	#define VER_NT_SERVER	0x00000003
#endif
#ifndef VER_SUITE_DATACENTER	
	#define	VER_SUITE_DATACENTER	0x00000080
#endif
#ifndef VER_SUITE_ENTERPRISE	
	#define	VER_SUITE_ENTERPRISE	0x00000002
#endif
#ifndef VER_SUITE_PERSONAL	
	#define	VER_SUITE_PERSONAL	0x00000200
#endif
*/
	typedef struct _OSVERSIONINFOEX 
	{
		  DWORD dwOSVersionInfoSize;
		  DWORD dwMajorVersion;
		  DWORD dwMinorVersion;
		  DWORD dwBuildNumber;
		  DWORD dwPlatformId;
		  TCHAR szCSDVersion[ 128 ];
		  WORD wServicePackMajor;
		  WORD wServicePackMinor;
		  WORD wSuiteMask;
		  BYTE wProductType;
		  BYTE wReserved;
	} OSVERSIONINFOEX, *POSVERSIONINFOEX, *LPOSVERSIONINFOEX;

	OSVERSIONINFOEX osvi;
	BOOL bIsWindows64Bit;
	BOOL bOsVersionInfoEx;

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	// If that fails, try using the OSVERSIONINFO structure.
	ZeroMemory (&osvi, sizeof (OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);
	if (!(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi))) 
	{
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		if (!GetVersionEx ((OSVERSIONINFO *) &osvi)) return NULL;
	}

	switch ( osvi.dwPlatformId ) 
	{
		case VER_PLATFORM_WIN32_NT:
		{
			int			nVerType = 4;
			// Test for the product.
			if (osvi.dwMajorVersion <= 4)
			{
				strcpy (szOSName, "Microsoft Windows NT ");
			}
			if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
			{
				strcpy (szOSName, "Microsoft Windows 2000 ");
				nVerType = OS_WIN2000;
			}
			if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
			{
				strcpy (szOSName, "Microsoft Windows XP ");
				nVerType = OS_WINXP;
			}
			if (osvi.dwMajorVersion >= 6 )
			{
				strcpy (szOSName, "Microsoft Windows VISTA ");
				nVerType = OS_VISTA;
			}

			// Test for product type.
			if ( bOsVersionInfoEx ) 
			{
				if (osvi.wProductType == VER_NT_WORKSTATION) 
				{
					if (osvi.wSuiteMask & VER_SUITE_PERSONAL)	strcat (szOSName, "Personal ");
					else										strcat (szOSName, "Professional ");
				} 
				else if (osvi.wProductType == VER_NT_SERVER) 
				{
					// Check for .NET Server instead of Windows XP.
					if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)	strcpy (szOSName, "Microsoft Windows .NET ");
					
					// Continue with the type detection.
					if (osvi.wSuiteMask & VER_SUITE_DATACENTER)					strcat (szOSName, "DataCenter Server ");
					else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)			strcat (szOSName, "Advanced Server ");
					else														strcat (szOSName, "Server ");
				}
			} 
			else 
			{
				HKEY hKey;
				char szProductType[80];
				DWORD dwBufLen;

				// Query the registry to retrieve information.
				RegOpenKeyEx (HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\ProductOptions", 0, KEY_QUERY_VALUE, &hKey);
				RegQueryValueEx (hKey, "ProductType", NULL, NULL, (LPBYTE) szProductType, &dwBufLen);
				RegCloseKey (hKey);
				if (lstrcmpi ("WINNT", szProductType) == 0) strcat (szOSName, "Professional ");
				if (lstrcmpi ("LANMANNT", szProductType) == 0)
				{
					// Decide between Windows 2000 Advanced Server and Windows .NET Enterprise Server.
					if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)	strcat (szOSName, "Standard Server ");
					else														strcat (szOSName, "Server ");
				}
				if (lstrcmpi ("SERVERNT", szProductType) == 0)
				{
					// Decide between Windows 2000 Advanced Server and Windows .NET Enterprise Server.
					if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1) 	strcat (szOSName, "Enterprise Server ");
					else														strcat (szOSName, "Advanced Server ");
				}
			}

			// Display version, service pack (if any), and build number.
			if (osvi.dwMajorVersion <= 4) 
			{
				// NB: NT 4.0 and earlier.
				sprintf (szOSName, "%sversion %d.%d %s (Build %d)",
											szOSName,
											osvi.dwMajorVersion,
											osvi.dwMinorVersion,
											osvi.szCSDVersion,
											osvi.dwBuildNumber & 0xFFFF);
			} 
			else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1) 
			{
				// Windows XP and .NET server.
				typedef BOOL (CALLBACK* LPFNPROC) (HANDLE, BOOL *);
				HINSTANCE hKernelDLL; 
				LPFNPROC DLLProc;
				
				// Load the Kernel32 DLL.
				hKernelDLL = LoadLibrary ("kernel32");
				if (hKernelDLL != NULL)  
				{ 
					// Only XP and .NET Server support IsWOW64Process so... Load dynamically!
					DLLProc = (LPFNPROC) GetProcAddress (hKernelDLL, "IsWow64Process"); 
					// If the function address is valid, call the function.
					if (DLLProc != NULL) (DLLProc) (GetCurrentProcess (), &bIsWindows64Bit);
					else				  bIsWindows64Bit = false;
				 
					// Free the DLL module.
					FreeLibrary (hKernelDLL); 
				} 

 				// IsWow64Process ();
				if (bIsWindows64Bit)	strcat (szOSName, "64-Bit ");
				else					strcat (szOSName, "32-Bit ");
			} 
			else 
			{ 
				// Windows 2000 and everything else.
				sprintf (szOSName, "%s%s(Build %d)", szOSName, osvi.szCSDVersion, osvi.dwBuildNumber & 0xFFFF);
			}
			return	nVerType;
		}
		case VER_PLATFORM_WIN32_WINDOWS:
		{
			// Test for the product.
			if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0) 
			{
				strcpy (szOSName, "Microsoft Windows 95 ");
				if (osvi.szCSDVersion[1] == 'C') strcat (szOSName, "OSR 2.5 ");
				else if (osvi.szCSDVersion[1] == 'B') strcat (szOSName, "OSR 2 ");

				return		1;
			} 

			if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10) 
			{
				strcpy (szOSName, "Microsoft Windows 98 ");
				if (osvi.szCSDVersion[1] == 'A' ) strcat (szOSName, "SE ");
				return		2;
			} 

			if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90) 
			{
				strcpy (szOSName, "Microsoft?Windows Me ");
				return		3;
			} 
		}
		case VER_PLATFORM_WIN32s:
		{
			strcpy (szOSName, "Microsoft Win32s ");
			return	8;
		}
		default:
		{
			strcpy (szOSName, "Unknown Windows ");
			return	8;
		}
	}
	return		8;
}

/////	OS Version('1' : 95, '2' : 98, '3' : ME, '4' : NT, '5' : 2000, '6' : XP, '7' : Windows Vista, '8' : 기타, '9':Windows 7)

typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);
int GetOSVersionInfoEx(char	*pszOS)
{
	typedef struct _OSVERSIONINFOEX 
	{
		  DWORD dwOSVersionInfoSize;
		  DWORD dwMajorVersion;
		  DWORD dwMinorVersion;
		  DWORD dwBuildNumber;
		  DWORD dwPlatformId;
		  TCHAR szCSDVersion[ 128 ];
		  WORD wServicePackMajor;
		  WORD wServicePackMinor;
		  WORD wSuiteMask;
		  BYTE wProductType;
		  BYTE wReserved;
	} OSVERSIONINFOEX, *POSVERSIONINFOEX, *LPOSVERSIONINFOEX;

   OSVERSIONINFOEX osvi;
   SYSTEM_INFO si;
   PGNSI pGNSI;
//   PGPI pGPI;
   BOOL bOsVersionInfoEx;
//   DWORD dwType;

   ZeroMemory(&si, sizeof(SYSTEM_INFO));
   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	int	nVerType = 8;

   if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
      return 0;

   // Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.

   pGNSI = (PGNSI) GetProcAddress(
      GetModuleHandle(TEXT("kernel32.dll")), 
      "GetNativeSystemInfo");
   if(NULL != pGNSI)
      pGNSI(&si);
   else GetSystemInfo(&si);

   if ( VER_PLATFORM_WIN32_NT==osvi.dwPlatformId && 
        osvi.dwMajorVersion > 4 )
   {
      strcpy(pszOS, TEXT("Microsoft "));

      // Test for the specific product.

      if ( osvi.dwMajorVersion == 6 )
      {
		  DWORD dwOSMinrVersion = 0;
		  if( osvi.dwMinorVersion == 0 )
		  {
			 if( osvi.wProductType == VER_NT_WORKSTATION )
			 {
				 strcat(pszOS, TEXT("Windows Vista "));
				 nVerType = 7;
			 }
			 else 
			 {
				 strcat(pszOS, TEXT("Windows Server 2008 " ));
				 nVerType = 8;
			 }
		  }
		  else if( osvi.dwMinorVersion == 1 )
		  {
			 dwOSMinrVersion = 1;
			  if( osvi.wProductType == VER_NT_WORKSTATION )
			 {
				 strcat(pszOS, TEXT("Windows 7 "));
				 nVerType = 9;
			 }
/*
			 else 
			 {
				 strcat(pszOS, TEXT("Windows Server 2008 " ));
				 nVerType = 8;
			 }
*/
		  }

/*
         pGPI = (PGPI) GetProcAddress(
            GetModuleHandle(TEXT("kernel32.dll")), 
            "GetProductInfo");

         pGPI( 6, dwOSMinrVersion, 0, 0, &dwType);

         switch( dwType )
         {
            case PRODUCT_ULTIMATE:
               strcat(pszOS, TEXT("Ultimate Edition" ));
               break;
            case PRODUCT_HOME_PREMIUM:
               strcat(pszOS, TEXT("Home Premium Edition" ));
               break;
            case PRODUCT_HOME_BASIC:
               strcat(pszOS, TEXT("Home Basic Edition" ));
               break;
            case PRODUCT_ENTERPRISE:
               strcat(pszOS, TEXT("Enterprise Edition" ));
               break;
            case PRODUCT_BUSINESS:
               strcat(pszOS, TEXT("Business Edition" ));
               break;
            case PRODUCT_STARTER:
               strcat(pszOS, TEXT("Starter Edition" ));
               break;
            case PRODUCT_CLUSTER_SERVER:
               strcat(pszOS, TEXT("Cluster Server Edition" ));
               break;
            case PRODUCT_DATACENTER_SERVER:
               strcat(pszOS, TEXT("Datacenter Edition" ));
               break;
            case PRODUCT_DATACENTER_SERVER_CORE:
               strcat(pszOS, TEXT("Datacenter Edition (core installation)" ));
               break;
            case PRODUCT_ENTERPRISE_SERVER:
               strcat(pszOS, TEXT("Enterprise Edition" ));
               break;
            case PRODUCT_ENTERPRISE_SERVER_CORE:
               strcat(pszOS, TEXT("Enterprise Edition (core installation)" ));
               break;
            case PRODUCT_ENTERPRISE_SERVER_IA64:
               strcat(pszOS, TEXT("Enterprise Edition for Itanium-based Systems" ));
               break;
            case PRODUCT_SMALLBUSINESS_SERVER:
               strcat(pszOS, TEXT("Small Business Server" ));
               break;
            case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
               strcat(pszOS, TEXT("Small Business Server Premium Edition" ));
               break;
            case PRODUCT_STANDARD_SERVER:
               strcat(pszOS, TEXT("Standard Edition" ));
               break;
            case PRODUCT_STANDARD_SERVER_CORE:
               strcat(pszOS, TEXT("Standard Edition (core installation)" ));
               break;
            case PRODUCT_WEB_SERVER:
               strcat(pszOS, TEXT("Web Server Edition" ));
               break;
         }
*/
         if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
            strcat(pszOS, TEXT( ", 64-bit" ));
         else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
            strcat(pszOS, TEXT(", 32-bit"));
      }

      if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
      {
		  nVerType = 8;

         if( GetSystemMetrics(SM_SERVERR2) )
            strcat(pszOS, TEXT( "Windows Server 2003 R2, "));
         else if ( osvi.wSuiteMask==VER_SUITE_STORAGE_SERVER )
            strcat(pszOS, TEXT( "Windows Storage Server 2003"));
         else if( osvi.wProductType == VER_NT_WORKSTATION &&
                  si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
         {
            strcat(pszOS, TEXT( "Windows XP Professional x64 Edition"));
			strcat(pszOS, TEXT( ", 64-bit" ));
			nVerType = 6;
         }
         else strcat(pszOS, TEXT("Windows Server 2003, "));

         // Test for the server type.
         if ( osvi.wProductType != VER_NT_WORKSTATION )
         {
            if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_IA64 )
            {
                if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                   strcat(pszOS, TEXT( "Datacenter Edition for Itanium-based Systems" ));
                else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                   strcat(pszOS, TEXT( "Enterprise Edition for Itanium-based Systems" ));
            }

            else if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
            {
                if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                   strcat(pszOS, TEXT( "Datacenter x64 Edition" ));
                else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                   strcat(pszOS, TEXT( "Enterprise x64 Edition" ));
                else strcat(pszOS, TEXT( "Standard x64 Edition" ));

				strcat(pszOS, TEXT( ", 64-bit" ));
            }

            else
            {
                if ( osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER )
                   strcat(pszOS, TEXT( "Compute Cluster Edition" ));
                else if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                   strcat(pszOS, TEXT( "Datacenter Edition" ));
                else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                   strcat(pszOS, TEXT( "Enterprise Edition" ));
                else if ( osvi.wSuiteMask & VER_SUITE_BLADE )
                   strcat(pszOS, TEXT( "Web Edition" ));
                else strcat(pszOS, TEXT( "Standard Edition" ));
            }
         }
      }

      if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
      {
         nVerType = 6;

		  strcat(pszOS, TEXT("Windows XP "));
         if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
            strcat(pszOS, TEXT( "Home Edition" ));
         else strcat(pszOS, TEXT( "Professional" ));

         if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
            strcat(pszOS, TEXT( ", 64-bit" ));
         else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
            strcat(pszOS, TEXT(", 32-bit"));
      }

      if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
      {
         nVerType = 5;

		  strcat(pszOS, TEXT("Windows 2000 "));

         if ( osvi.wProductType == VER_NT_WORKSTATION )
         {
            strcat(pszOS, TEXT( "Professional" ));
         }
         else 
         {
            if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
               strcat(pszOS, TEXT( "Datacenter Server" ));
            else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
               strcat(pszOS, TEXT( "Advanced Server" ));
            else strcat(pszOS, TEXT( "Server" ));
         }

         if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
            strcat(pszOS, TEXT( ", 64-bit" ));
         else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
            strcat(pszOS, TEXT(", 32-bit"));
      }

       // Include service pack (if any) and build number.

      if( _tcslen(osvi.szCSDVersion) > 0 )
      {
//		  nVerType = 0;

          strcat(pszOS, TEXT(" ") );
          strcat(pszOS, osvi.szCSDVersion);
      }

      TCHAR buf[80];

      sprintf( buf, TEXT(" (build %d)"), osvi.dwBuildNumber);
      strcat(pszOS, buf);
   }

   else
   {  
      printf( "This sample does not support this version of Windows.\n");
   }

	return		nVerType;
}



CRect CMonitor::GetDesktopRect( LPPOINT ppt )
{
	HMONITOR hMon = ::MonitorFromPoint( *ppt, MONITOR_DEFAULTTONEAREST );
	if( hMon != NULL )
	{
		MONITORINFO mi;
		ZeroMemory( &mi, sizeof( mi ) );
		mi.cbSize = sizeof( mi );
		if( ::GetMonitorInfo( hMon, &mi ) )
		{
			return mi.rcWork;
		}
	}

	CRect rcDesktop;
	CWnd::GetDesktopWindow()->GetWindowRect( rcDesktop );
	return rcDesktop;
}

CRect CMonitor::GetDesktopRect( LPRECT prc )
{
	HMONITOR hMon = ::MonitorFromRect( prc, MONITOR_DEFAULTTONEAREST );
	if( hMon != NULL )
	{
		MONITORINFO mi;
		ZeroMemory( &mi, sizeof( mi ) );
		mi.cbSize = sizeof( mi );
		if( ::GetMonitorInfo( hMon, &mi ) )
		{
			return mi.rcWork;
		}
	}

	CRect rcDesktop;
	CWnd::GetDesktopWindow()->GetWindowRect( rcDesktop );
	return rcDesktop;
}


BOOL CALLBACK EnumMonitorProc(HMONITOR hMonitor, HDC hdc, LPRECT prc, LPARAM lParam)
{
    CDWordArray *parrHMonitor = (CDWordArray *)lParam;

	parrHMonitor->Add((DWORD)hMonitor);

    return TRUE;
}

//	좌표를 이용해 모니터 영역을 구함
CRect CMonitor::GetMonitorRect(CPoint& point)
{
	CRect rc(0, 0, 0, 0);
	CRect rcWork;

	HMONITOR	hMonitor;
	CDWordArray arrHMonitor;

	::EnumDisplayMonitors(NULL, NULL, EnumMonitorProc, (LPARAM)&arrHMonitor);
	int nMonitorCount = arrHMonitor.GetSize();

	CArray<CRect, CRect &>	arrRect;
	for(int i = 0; i < nMonitorCount; i++)
	{
		MONITORINFO mi;

		memset(&mi, 0x00, sizeof(MONITORINFO));
		mi.cbSize	= sizeof(MONITORINFO);
		hMonitor	= (HMONITOR)arrHMonitor[i];

		::GetMonitorInfo(hMonitor, &mi);

		rcWork = mi.rcWork;

		if( rcWork.left <= point.x && point.x <= rcWork.right &&
			rcWork.top  <= point.y && point.y <= rcWork.bottom )
		{
			return rcWork;
		}

	}

	return rc;
}

CRect CMonitor::GetMonitorRect(int index)
{
	int			nMonitorCount;
	CRect		rcWork;
	HMONITOR	hMonitor;
	CDWordArray arrHMonitor;

	::EnumDisplayMonitors(NULL, NULL, EnumMonitorProc, (LPARAM)&arrHMonitor);
	nMonitorCount = arrHMonitor.GetSize();

	if( index < 0 || nMonitorCount <= index )
	{
		// 범위에 없는 경우는 무조건 기본 영역
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0);

		return rcWork;
	}

	MONITORINFO mi;

	memset(&mi, 0x00, sizeof(MONITORINFO));
	mi.cbSize	= sizeof(MONITORINFO);
	hMonitor	= (HMONITOR)arrHMonitor[index];

	::GetMonitorInfo(hMonitor, &mi);

	rcWork = mi.rcWork;

	return rcWork;
}

int	CMonitor::GetMonitorCount()
{
	int			nMonitorCount = 1;
	CDWordArray arrHMonitor;

	::EnumDisplayMonitors(NULL, NULL, EnumMonitorProc, (LPARAM)&arrHMonitor);
	nMonitorCount = arrHMonitor.GetSize();

	return nMonitorCount;
}

int CMonitor::GetDualPosition(CPoint point)
{
	CRect rc(0, 0, 0, 0);
	CRect rcWork;

	HMONITOR	hMonitor;
	CDWordArray arrHMonitor;

	::EnumDisplayMonitors(NULL, NULL, EnumMonitorProc, (LPARAM)&arrHMonitor);
	int nMonitorCount = arrHMonitor.GetSize();

	CArray<CRect, CRect &>	arrRect;
	for(int i = 0; i < nMonitorCount; i++)
	{
		MONITORINFO mi;

		memset(&mi, 0x00, sizeof(MONITORINFO));
		mi.cbSize	= sizeof(MONITORINFO);
		hMonitor	= (HMONITOR)arrHMonitor[i];

		::GetMonitorInfo(hMonitor, &mi);

		rcWork = mi.rcWork;

		if( rcWork.left <= point.x && point.x <= rcWork.right &&
			rcWork.top  <= point.y && point.y <= rcWork.bottom )
		{
			return i;
		}
	}

	return -1;
}


int  CMonitor::GetWorkArea(CRect *rc)
{
	int nWinVersion;
	char chOsName[128];

	nWinVersion = GetOSVersionInfo(chOsName);
	
	CPoint pt;
    GetCursorPos(&pt);

	if (nWinVersion == OS_WIN2000 || nWinVersion == OS_WINXP || nWinVersion >= OS_VISTA)
	{
		int nCount = GetMonitorCount();

		if (nCount > 1)//bIsMultiMax)
		{
			CRect			rcMon;

			rc->SetRectEmpty();

			for(int i = 0; i < nCount; i++)
			{
				rcMon = GetMonitorRect(i);
				
				rc->left = __min(rc->left, rcMon.left);
				rc->top = __min(rc->top, rcMon.top);
				rc->right = __max(rc->right, rcMon.right);
				rc->bottom = __min(rc->bottom, rcMon.bottom);
				if(rc->bottom <= 100)
					rc->bottom = __max(rc->bottom, rcMon.bottom);
			}
		}
		else
		{
			MONITORINFO		mtCursor, mtMenu;

			mtCursor.cbSize = sizeof(mtCursor);
			mtMenu.cbSize   = sizeof(mtMenu);

			HMONITOR hmtCursor = ::MonitorFromPoint (pt, MONITOR_DEFAULTTOPRIMARY);

			if (GetMonitorInfo (hmtCursor, &mtCursor))
			{
				*rc = mtCursor.rcWork;
			}
			else
			{
				SystemParametersInfo (SPI_GETWORKAREA, 0, rc, 0);
			}
		}
	}
	else
	{
		SystemParametersInfo (SPI_GETWORKAREA, 0, rc, 0);
	}

	return 1;
}