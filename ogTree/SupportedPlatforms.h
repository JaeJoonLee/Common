///////////////////////////////////////////////////////////////////////////////
// SupportedPlatforms.h
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
//-------------------------------------------------------------------
// The purpose of this file is to include definitions of supported
// target platforms. Trying to compile libraries under an UNSUPPORTED
// platform will give a compile time error.
//-------------------------------------------------------------------


#if !defined(__SUPPORTEDPLATFORMS__H__)
#define __SUPPORTEDPLATFORMS__H__

#pragma warning(disable: 4005)

#pragma message("----------------------------------------------------")

// Platform Targeting -----------------------------------------------
//
// For more details, refer to 
//      http://msdn2.microsoft.com/en-us/library/aa383745.aspx
/*
// SUPPORTED
Windows Vista, Vista SP1, Server 2008 
	_WIN32_WINNT>=0x0600
	WINVER>=0x0600
 
Windows Server 2003 
	_WIN32_WINNT>=0x0502
	WINVER>=0x0502
 
Windows XP 
	_WIN32_WINNT>=0x0501
	WINVER>=0x0501
 
// UNSUPPORTED 
Windows 2000 
	_WIN32_WINNT>=0x0500
	WINVER>=0x0500
 
Windows NT 4.0 
	_WIN32_WINNT>=0x0400
	WINVER>=0x0400
 
Windows Me 
	_WIN32_WINDOWS=0x0500
	WINVER>=0x0500
 
Windows 98 
	_WIN32_WINDOWS>=0x0410
	WINVER>=0x0410
 
Windows 95 
	_WIN32_WINDOWS>=0x0400
	WINVER>=0x0400

// Internet Explorer versions 
Internet Explorer 7.0				_WIN32_IE>=0x0700 
Internet Explorer 6.0 SP2		_WIN32_IE>=0x0603 
Internet Explorer 6.0 SP1		_WIN32_IE>=0x0601 
Internet Explorer 6.0				_WIN32_IE>=0x0600 
Internet Explorer 5.5 			_WIN32_IE>=0x0550 
Internet Explorer 5.01 			_WIN32_IE>=0x0501 
Internet Explorer 5.0,.0a,.0b	_WIN32_IE>=0x0500 
Internet Explorer 4.01 			_WIN32_IE>=0x0401 
Internet Explorer 4.0 			_WIN32_IE>=0x0400 
Internet Explorer 3.0,.01,.02	_WIN32_IE>=0x0300 

//
// NTDDI version constants (as of Sept 2007) 
// Constant values are from sdkddkver.h in the latest Windows SDK
//
#define NTDDI_WIN2K                         0x05000000
#define NTDDI_WIN2KSP1                      0x05000100
#define NTDDI_WIN2KSP2                      0x05000200
#define NTDDI_WIN2KSP3                      0x05000300
#define NTDDI_WIN2KSP4                      0x05000400

#define NTDDI_WINXP                         0x05010000
#define NTDDI_WINXPSP1                      0x05010100
#define NTDDI_WINXPSP2                      0x05010200
#define NTDDI_WINXPSP3                      0x05010300
#define NTDDI_WINXPSP4                      0x05010400

#define NTDDI_WS03                          0x05020000
#define NTDDI_WS03SP1                       0x05020100
#define NTDDI_WS03SP2                       0x05020200
#define NTDDI_WS03SP3                       0x05020300
#define NTDDI_WS03SP4                       0x05020400

#define NTDDI_WIN6                          0x06000000
#define NTDDI_WIN6SP1                       0x06000100
#define NTDDI_WIN6SP2                       0x06000200
#define NTDDI_WIN6SP3                       0x06000300
#define NTDDI_WIN6SP4                       0x06000400

#define NTDDI_VISTA                         NTDDI_WIN6   
#define NTDDI_VISTASP1                      NTDDI_WIN6SP1
#define NTDDI_VISTASP2                      NTDDI_WIN6SP2
#define NTDDI_VISTASP3                      NTDDI_WIN6SP3
#define NTDDI_VISTASP4                      NTDDI_WIN6SP4
         
#define NTDDI_WS08                          NTDDI_WIN6SP1
#define NTDDI_WS08SP2                       NTDDI_WIN6SP2
#define NTDDI_WS08SP3                       NTDDI_WIN6SP3
#define NTDDI_WS08SP4                       NTDDI_WIN6SP4

#define NTDDI_LONGHORN  NTDDI_VISTA

*/

/////////////////////////////////////////////////////////////////////

// Window 2000
#if !defined NTDDI_WIN2K	
#define NTDDI_WIN2K			0x05000000
#endif

// Windows 2000 with Service Pack 1
#if !defined NTDDI_WIN2KSP1	
#define NTDDI_WIN2KSP1      0x05000100
#endif 

// Windows 2000 with Service Pack 2
#if !defined NTDDI_WIN2KSP2	
#define NTDDI_WIN2KSP2      0x05000200
#endif 

// Windows 2000 with Service Pack 3
#if !defined NTDDI_WIN2KSP3	
#define NTDDI_WIN2KSP3      0x05000300
#endif

// Windows 2000 with Service Pack 4
#if !defined NTDDI_WIN2KSP4	
#define NTDDI_WIN2KSP4      0x05000400
#endif

// Windows XP
#if !defined NTDDI_WINXP	
#define NTDDI_WINXP         0x05010000
#endif

// Windows XP with Service Pack 1
#if !defined NTDDI_WINXPSP1	
#define NTDDI_WINXPSP1      0x05010100
#endif

// Windows XP with Service Pack 2
#if !defined NTDDI_WINXPSP2	
#define NTDDI_WINXPSP2      0x05010200
#endif

// Windows XP with Service Pack 3
#if !defined NTDDI_WINXPSP3	
#define NTDDI_WINXPSP3      0x05010300
#endif

// Windows XP with Service Pack 4
#if !defined NTDDI_WINXPSP4	
#define NTDDI_WINXPSP4      0x05010400
#endif

// Windows Server 2003
#if !defined NTDDI_WS03		
#define NTDDI_WS03          0x05020000
#endif 

// Windows Server 2003 with Service Pack 1
#if !defined NTDDI_WS03SP1	
#define NTDDI_WS03SP1       0x05020100
#endif 

// Windows Server 2003 with Service Pack 2
#if !defined NTDDI_WS03SP2	
#define NTDDI_WS03SP2       0x05020200
#endif

// Windows Server 2003 with Service Pack 3
#if !defined NTDDI_WS03SP3	
#define NTDDI_WS03SP3       0x05020300
#endif

// Windows Server 2003 with Service Pack 4
#if !defined NTDDI_WS03SP4	
#define NTDDI_WS03SP4       0x05020400
#endif

// Windows Longhorn
#if !defined NTDDI_LONGHORN	
#define NTDDI_LONGHORN      0x06000000
#endif

#if !defined NTDDI_WIN6 
#define NTDDI_WIN6          0x06000000
#endif 

#if !defined NTDDI_WIN6SP1
#define NTDDI_WIN6SP1       0x06000100
#endif

#if !defined NTDDI_WIN6SP2
#define NTDDI_WIN6SP2       0x06000200
#endif

#if !defined NTDDI_WIN6SP3
#define NTDDI_WIN6SP3       0x06000300
#endif

#if !defined NTDDI_WIN6SP4
#define NTDDI_WIN6SP4       0x06000400
#endif

// Windows Vista
#if !defined NTDDI_VISTA					
#define NTDDI_VISTA         NTDDI_WIN6 
#endif

// Windows Vista with Service Pack 1
#if !defined NTDDI_VISTASP1	
#define NTDDI_VISTASP1		NTDDI_WIN6SP1
#endif

// Windows Vista with Service Pack 2
#if !defined NTDDI_VISTASP2	
#define NTDDI_VISTASP2		NTDDI_WIN6SP2
#endif

// Windows Vista with Service Pack 3
#if !defined NTDDI_VISTASP3	
#define NTDDI_VISTASP3		NTDDI_WIN6SP3
#endif

// Windows Vista with Service Pack 4
#if !defined NTDDI_VISTASP4	
#define NTDDI_VISTASP4		NTDDI_WIN6SP4
#endif

// Windows Server 2008
#if !defined NTDDI_WS08		
#define NTDDI_WS08			NTDDI_WIN6SP1
#endif

// Windows Server 2008 with Service Pack 2
#if !defined NTDDI_WS08SP2	
#define NTDDI_WS08SP2       NTDDI_WIN6SP2
#endif 

// Windows Server 2008 with Service Pack 3
#if !defined NTDDI_WS08SP3	
#define NTDDI_WS08SP3       NTDDI_WIN6SP3
#endif 

// Windows Server 2008 with Service Pack 4
#if !defined NTDDI_WS08SP4	
#define NTDDI_WS08SP4       NTDDI_WIN6SP4
#endif

// Windows 7
#if !defined NTDDI_WIN7 
#define NTDDI_WIN7          0x07000000
#endif 

// Windows 7 with Service Pack 1
#if !defined NTDDI_WIN7SP1
#define NTDDI_WIN7SP1       0x07000100
#endif

// Windows 7 with Service Pack 2
#if !defined NTDDI_WIN7SP2
#define NTDDI_WIN7SP2       0x07000200
#endif

// Windows 7 with Service Pack 3
#if !defined NTDDI_WIN7SP3
#define NTDDI_WIN7SP3       0x07000300
#endif

// Windows 7 with Service Pack 4
#if !defined NTDDI_WIN7SP4
#define NTDDI_WIN7SP4       0x07000400
#endif

/////////////////////////////////////////////////////////////////////
#ifndef NO_TARGETING
#pragma message ("Operating System:")
	// Default Platform definition
	#if !defined NTDDI_VERSION
		//------------------------------------------------------//
    // Redefine default target platform with one of the     //
		// supported NTDDI_* versions listed above.             //
		//------------------------------------------------------//
		#define NTDDI_VERSION					NTDDI_VISTA
		
		//#if(_MSC_VER >= 1500) // Microsoft Visual Studio 2008 (9.0+) including SP1"
		// Comment/uncomment #define below
		// to disallow/allow binding to current compiler libraries.
		#define _BIND_TO_CURRENT_VCLIBS_VERSION 1
		//#endif // _BIND...
		//------------------------------------------------------//
	#endif // NTDDI_VERSION

	// Windows 7
	#if (NTDDI_VERSION >= NTDDI_WIN7) && (NTDDI_VERSION <= NTDDI_WIN7SP4)
		#pragma message("    Targeting unsupported (WINDOWS 7)* platform")
		#pragma message("          WINVER      >= 0x0601")
		#pragma message("         _WIN32_WINNT == 0x0601")
		#pragma message("         _WIN32_IE    == 0x0800")
		#define WINVER		 		0x0601
		#define _WIN32_WINNT 	0x0601
		#define	_WIN32_IE	 		0x0800
		#pragma message("    Windows 7 is UNSUPPORTED.")
		#pragma message("    ***Please review the support matrix for supported target platforms.***")
	// Windows Server 2008
	#elif (NTDDI_VERSION >= NTDDI_WS08) && (NTDDI_VERSION <= NTDDI_WS08SP4)
		#pragma message("    Targeting supported (WINDOWS SERVER 2008)* platform")
		#pragma message("          WINVER      >= 0x0600")
		#pragma message("         _WIN32_WINNT == 0x0600")
		#pragma message("         _WIN32_IE    == 0x0700")
		#define WINVER		 		0x0600
		#define _WIN32_WINNT 	0x0600
		#define	_WIN32_IE	 		0x0700
		//#error Target platforms where the appropriate NTDDI_VERSION is supported!
	// Windows Vista SP1 - SP4
	#elif (NTDDI_VERSION >= NTDDI_VISTASP1) && (NTDDI_VERSION <= NTDDI_VISTASP4)
			#pragma message("    Targeting supported (WINDOWS VISTA)* platform")
		#pragma message("          WINVER      >= 0x0600")
		#pragma message("         _WIN32_WINNT == 0x0600")
		#pragma message("         _WIN32_IE    == 0x0700")
		#define WINVER		 		0x0600
		#define _WIN32_WINNT 	0x0600
		#define	_WIN32_IE	 		0x0700
	// Windows Vista
	#elif NTDDI_VERSION == NTDDI_VISTA 
		#define WINVER		 		0x0600
		#define _WIN32_WINNT 	0x0600
		#define	_WIN32_IE	 		0x0700
		#pragma message("    Targeting supported (WINDOWS VISTA)* platform")
		#pragma message("          WINVER      >= 0x0600")
		#pragma message("         _WIN32_WINNT == 0x0600")
		#pragma message("         _WIN32_IE    == 0x0700")
	// Windows Server 2003 - Service Pack 4
	#elif (NTDDI_VERSION >= NTDDI_WS03) && (NTDDI_VERSION <= NTDDI_WS03SP4) 
		#define WINVER       	0x0502
		#define _WIN32_WINNT 	0x0502
		#define	_WIN32_IE	 		0x0603
		#pragma message("    Targeting supported (WINDOWS 2003 SERVER)* platform")
		#pragma message("          WINVER      >= 0x0502")
		#pragma message("         _WIN32_WINNT == 0x0502")
		#pragma message("         _WIN32_IE    == 0x0603")
	#elif (NTDDI_VERSION >= NTDDI_WINXPSP3) && (NTDDI_VERSION <= NTDDI_WINXPSP4)  // Windows XP SP3 - SP4
		// These values are based on the Windows Server 2008 PSDK sdkddkver.h
		#define WINVER       	0x0502
		#define _WIN32_WINNT 	0x0501
		#define	_WIN32_IE	 		0x0603
		#pragma message("    Targeting supported (WINDOWS XP SP3)* platform")
		#pragma message("          WINVER      >= 0x0502")
		#pragma message("         _WIN32_WINNT == 0x0501")
		#pragma message("         _WIN32_IE    == 0x0603")
	#elif NTDDI_VERSION == NTDDI_WINXPSP2 // Windows XP SP2
		// NOTE: With some Microsoft Platform SDKs, _WIN32_WINNT may need to be defined at 0x0501.
		#define WINVER       	0x0502
		#define _WIN32_WINNT	0x0502
		#define	_WIN32_IE	 		0x0603
		#pragma message("    Targeting supported (WINDOWS XP SP2)* platform")
		#pragma message("          WINVER      >= 0x0502")
		#pragma message("         _WIN32_WINNT == 0x0502")
		#pragma message("         _WIN32_IE    == 0x0603")
	#elif NTDDI_VERSION == NTDDI_WINXPSP1 // Windows XP SP1
		#pragma message("    Windows XP SP1 is UNSUPPORTED, please upgrade to SP2.")
		#pragma message("    ***Please review the support matrix for supported target platforms.***")
		//#error Windows XP SP1 is UNSUPPORTED, please upgrade to SP2.
	// Windows 2000 - SP4
	#elif (NTDDI_VERSION >= NTDDI_WIN2K) && (NTDDI_VERSION <= NTDDI_WIN2KSP4) 
		#define WINVER       	0x0500
		#define _WIN32_WINNT 	0x0500
		#define	_WIN32_IE	 		0x0500
        #define HRAWINPUT DWORD  // Required to remove specific syntax error: ?L_TYPE_raw>?
		#pragma message("    Windows 2000 (SP0 - SP4) are UNSUPPORTED.")
		#pragma message("    ***Please review the support matrix for supported target platforms.***")
		//#error Windows 2000 (SP0 - SP3) are UNSUPPORTED, please upgrade to SP4.
		#pragma message("          WINVER      >= 0x0500")
		#pragma message("         _WIN32_WINNT == 0x0500")
		#pragma message("         _WIN32_IE    == 0x0500")
	#else // Other platform
		#define WINVER       	0x0502
		#define _WIN32_WINNT 	0x0502
		#define	_WIN32_IE	 		0x0603
		#pragma message("    Targeting UNSUPPORTED platform.")
		#pragma message("    ***Please review the support matrix for supported target platforms.***")
		#pragma message("          WINVER      >= 0x0502")
		#pragma message("         _WIN32_WINNT == 0x0502")
		#pragma message("         _WIN32_IE    == 0x0603")
		//#error Target platforms where the appropriate NTDDI_VERSION is supported!
	#endif // WINVER

	#pragma message("    *Target platform defined in SupportedPlatforms.h")
#endif // NO_TARGETING

// Operating System Bit Version---------------------------------------
#if defined(_WIN64)
	#if defined(_M_AMD64)
		#if(_MSC_VER >= 1400)
			#pragma message("    AMD x64 Processor Family is supported")
		//#else
			//#pragma message("    You must use Microsoft Visual Studio 2005 (8.0) or Higher!")
			//#error You must use Microsoft Visual Studio 2005 (8.0) or Higher!
		#endif
    #elif defined(_M_IA64)
		#pragma message("    Intel Itanium x64 Processor Family is not supported!")
	//#error
	#else
		#pragma message("    Unknown x64 Processor Family is not supported!")
		//#error
    #endif // x64 Processors
#endif // _WIN64

#if defined(_M_IX86) // x86 archictecture
	#if defined(_WIN64) // 64-bit application
		#pragma message("    x86 OS is supported for 32 Bit only. x64 cross-compiler is not supported.")
	#else
		#pragma message("    x86 OS is supported")
	#endif
#endif

#if defined(_M_X64)
	#if (_MSC_VER >= 1400)
		#pragma message("    x64 OS is supported")
	#else
		//#pragma message("    You must use Microsoft Visual Studio 2005 (8.0) or Higher!")
		//#error You must use Microsoft Visual Studio 2005 (8.0) or Higher!
	#endif
#endif

// COMPILERS --------------------------------------------------------
#pragma message("Compiler:")
// Add the compiler info into our object file.
#if(_MSC_VER >= 1600)
	#pragma message("    Microsoft Visual Studio 2010 is unsupported.")
	#pragma message("    ***Please review the support matrix for supported compilers.***")
//#pragma comment(compiler)
#elif(_MSC_VER >= 1500) // Microsoft Visual Studio 2008")
	// This is a supported compiler.
	#pragma message("    Microsoft Visual Studio 2008 (9.0 +) including SP1")
#elif(_MSC_VER >= 1400) // Microsoft Visual Studio 2005 (8.0 +) including SP1
	// This is a supported compiler.
	#pragma message("    Microsoft Visual Studio 2005 (8.0 +) is supported.")
#elif(_MSC_VER == 1310) // Microsoft Visual Studio 2003 .NET (7.1)
	#if WINVER >= 0x0600
		// This is not a supported compiler on Vista.
		#pragma message("    Microsoft Visual Studio 2003 .NET (7.1) is not supported on Vista!")
		#pragma message("    ***Please review the support matrix for supported compilers.***")
		//#error Microsoft Visual Studio 2003 .NET (7.1) is not supported on Vista!
	#else
		// This is a supported compiler.
		#pragma message("    Microsoft Visual Studio 2003 .NET (7.1) is supported.")
	#endif
#elif (_MSC_VER == 1300) // Microsoft Visual Studio 2002 .NET (7.0)
	// This is not a supported compiler.
	#pragma message("    Microsoft Visual Studio 2002 .NET (7.0) is not supported!")
	#pragma message("    ***Please review the support matrix for supported compilers.***")
	//#error Microsoft Visual Studio 2002 .NET (7.0) is not supported!
#elif (_MSC_VER == 1200) // Microsoft Visual Studio 1998 (6.0)
	#if WINVER >= 0x0600
		// This is not a supported compiler on Vista.
		#pragma message("    Microsoft Visual Studio 1998 (6.0) is not supported on Vista!")
		#pragma message("    ***Please review the support matrix for supported compilers.***")
		//#error Microsoft Visual Studio 1998 (6.0) is not supported on Vista!
	#else
		// This is a supported compiler.
		#pragma message("    Microsoft Visual Studio 1998 (6.0) is no longer supported.")
		#pragma message("    ***Please review the support matrix for supported compilers.***")
		//#error Microsoft Visual Studio 1998 (6.0) is no longer supported.
	#endif
#else
	// These are not supported compilers.
	#pragma message("    This compiler is not supported!")
	#pragma message("    ***Please review the support matrix for supported compilers.***")
	//#error This compiler is not supported!
#endif 

// 64 Bit Support:
#if defined(_WIN64)
  #if(_MSC_VER >= 1500)
		#pragma message("    Licensed 64 Bit builds are supported with Microsoft Visual Studio 2008 (9.0)")
	#elif(_MSC_VER >= 1400)
		#pragma message("    Licensed 64 Bit builds are supported with Microsoft Visual Studio 2005 (8.0 +)")
	#else
		#pragma message("    64 Bit libraries require Microsoft Visual Studio 2005 (8.0) or higher!")
		//#error 64 Bit libraries require Microsoft Visual Studio 2005 (8.0) or higher!
	#endif // 1400 == _MSC_VER
#endif // _WIN64

// Build Configurations ---------------------------------------------
//
#pragma message("Build Configuration:")
// Managed /CLR?
#if defined (_MANAGED)
#pragma message ("    (m) Managed")
#else
#pragma message ("    ( ) Unmanaged")
#endif // _MANAGED
// MFC Static or DLL 
#if defined(_AFXDLL)
	#pragma message("    (a) AFX/MFC DLL")
#else
	#pragma message("    ( ) MFC/AFX Static Library")	
#endif // _AFXDLL

// Stingray Static or DLL
#if defined(_SFLDLL) || defined(_SFLEXDLL) || defined(_OBJCHART_DLL) || defined(_OBJCHART_UT_DLL) || defined(_SECEDITDLL) || defined(_GXDLL) || defined(_OGEXDLL) || defined(_SECDLL) || defined(_OVDLL)
	#pragma message("    (s) Stingray DLL")
#else
	#pragma message("    ( ) Stingray Static Library")	
#endif // _PRODUCTDLL

// Unicode
#if defined(_UNICODE)
	#pragma message("    (u) Unicode")
#else
	#pragma message("    ( ) ANSI")	
#endif // _UNICODE

// Debug or Release
#if defined(_DEBUG)
	#pragma message("    (d) Debug")
#elif defined(NDEBUG)
	#pragma message("    ( ) Release")
#endif // _DEBUG

#pragma message("----------------------------------------------------")

#endif // (__SUPPORTEDPLATFORMS__H__)
