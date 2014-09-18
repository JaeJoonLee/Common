////////////////////////////////////////////////////////////////////////////////////
// ManifestDefs.h
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
////////////////////////////////////////////////////////////////////////////////////

#if !defined(__MANIFESTDEFS__H__)
#define __MANIFESTDEFS__H__

////////////////////////////////////////////////////////////////////////////////////
// NOTE:
// This file is being provided to make it easier to include manifest definitions
// for Windows XP Styles. 
////////////////////////////////////////////////////////////////////////////////////

#if _MSC_VER >= 1400

	// Determine the Processor Architecture:
	#if defined _M_IX86
		#define PROCESSOR_ARCH "x86"
		#define CC_PROCESSOR_ARCH "x86"
	#elif defined _M_X64 
		#if defined _WIN64 
			#define PROCESSOR_ARCH "amd64"
			#define CC_PROCESSOR_ARCH "amd64"
		#else
			#define PROCESSOR_ARCH "x86"
			#define CC_PROCESSOR_ARCH "*"
		#endif
	#endif

	// Common Controls
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='" CC_PROCESSOR_ARCH "' publicKeyToken='6595b64144ccf1df' language='*'\"")

	// QA: 32134 - Removing dependency on CRT/MFC assemblies when linked statically. 
	#if defined _AFXDLL || defined _SFLDLL
		// Defines for __LIBRARIES_ASSEMBLY_NAME_PREFIX, _CRT_ASSEMBLY_VERSION, and _VC_ASSEMBLY_PUBLICKEYTOKEN come from 
		// the Microsoft VS2005 header file crtassem.h and MFCAssem.h
		#include "crtassem.h"
		#include "MFCassem.h"// MFCassem.h will embed appropriate MFC manifest dependencies. 

		#ifdef _DEBUG
			#pragma comment(linker, "/manifestdependency:\"type='win32' name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".DebugCRT' version='" _CRT_ASSEMBLY_VERSION "' processorArchitecture='" CC_PROCESSOR_ARCH "' publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "' language='*'\"")
			// MFC assembly dependencies will get added with the inclusion of mfcassem.h	
		#else
			#pragma comment(linker, "/manifestdependency:\"type='win32' name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".CRT' version='" _CRT_ASSEMBLY_VERSION "' processorArchitecture='" CC_PROCESSOR_ARCH "' publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "' language='*'\"")
			// MFC assembly dependencies will get added with the inclusion of mfcassem.h
		#endif // _DEBUG
		
		#pragma message("CRT Assembly Version: " _CRT_ASSEMBLY_VERSION) 
		#pragma message("MFC Assembly Version: " _MFC_ASSEMBLY_VERSION)
		#pragma message("    To specify/remove dependencies of assembly versions use")
		#pragma message("    a custom manifest. Refer to MSDN mt.exe documentation.")
		#pragma message("----------------------------------------------------")

	//	#ifdef NTDDI_VERSION 
	//		#if (NTDDI_VERSION >= NTDDI_VISTA)
	//			#pragma comment(linker, "/requestedExecutionLevel:\"level='requireAdministrator' uiAccess='false'\"")
	//		#endif
	//	#endif

	#endif // defined _AFXDLL || defined _SFLDLL

#endif // _MSC_VER >= 1400

#endif // __MANIFESTDEFS__H__