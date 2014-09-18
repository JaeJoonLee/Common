///////////////////////////////////////////////////////////////////////////////
// SflCommon.h : SFL macros and utility classes
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
// Author:       Gilberto Araya
// Description:  SFL utility classes
//

#pragma once

#ifndef __SFLCOMMON_H__
#define __SFLCOMMON_H__


#if !defined(_SFL)
#define _SFL
#endif

#ifndef _WIN64
	// _WIN32
	#if !defined(_X86_)
		#define _X86_
	#endif	// !_X86_
#else //!_WIN32 && _WIN64 defined
	#if !defined(_M_AMD64_) // AMD x64 processor			
		#define _AMD64_
//	#endif // !_AMD64_
	#else !defined(_M_IA64_) // Intel x64 processor
		#define _IA64_
	#endif // !_IA64_
#endif // _WIN64

#if defined(_UNICODE) && !defined(UNICODE)
#define UNICODE _UNICODE
#endif
#if !defined(_UNICODE) && defined(UNICODE)
#define _UNICODE UNICODE
#endif

//////////////////////////////////////////////////////////////
// If _AFX defined, assume _SFL_MFC_SUPPORT is desired.

#ifndef _SFL_MFC_SUPPORT
#ifdef _AFX
#define _SFL_MFC_SUPPORT
#endif
#endif

#if defined(_ATL) && !defined(_SFL_NO_ATL)
#define _SFL_ATL_SUPPORT
#endif
#if defined(_SFL_ATL_SUPPORT) && defined(_SFL_NO_ATL)
#undef _SFL_ATL_SUPPORT
#endif

//////////////////////////////////////////////////////////////
// Include version info and autolink pragmas
//#include "OgTree\Foundation\SflVersion.h"

//////////////////////////////////////////////////////////////
// Produce error if trying to compile with old Common and MVC
// headers

#if defined(_CMN_VER)
#if (_CMN_VER != 0x0FFF)
#error SFL cannot be compiled with older versions of the Stingray Common library. Check your include path.
#endif
#endif

#if defined(_MVC_VER)
#if (_MVC_VER != 0x0FFF)
#error SFL cannot be compiled with older versions of the Stingray MVC library. Check your include path.
#endif
#endif

//////////////////////////////////////////////////////////////
// Define sfl abbreviation for stingray::foundation namespace

namespace stingray {
namespace foundation {
};
};

#ifndef _SFL_NO_NAMESPACE_ABBREVIATION
namespace sfl=stingray::foundation;
#endif

#include <stdarg.h>
#include <windef.h>
#if _MSC_VER > 1100
#include <basetsd.h>
#endif
#include <winbase.h>
#include <winuser.h>
#include <shlwapi.h>
#include <CommCtrl.h>

// Debugging support
// Debug macros automatically nooped in release mode
#include <crtdbg.h>

//#if !defined(_AFX) || !defined(_WTL_VER)
//#if defined(_SFL_MFC_SUPPORT)
//#undef _SFL_MFC_SUPPORT
//#endif
//#endif

#ifdef _SFLDLL
#include <Foundation\SflDll.h>
#endif

#include "..\StingrayExportDefs.h"

// ***********************************************************
// *
// *  BuildWizard preliminary includes
// *
// ***********************************************************

#if !defined(__SFL_BWDEFINES_H) && !defined(_SFLBWCONFIG_H_)
//#include "OgTree\foundation\BWDef.h"
#endif //__SFL_BWDEFINES_H


/////////////////////////////////////////////////////////////////////////////
// VC++ version check for SFL XML Support

#if defined(_SFL_MFC_SUPPORT) && defined(SFL_BLD_XMLSERCORE)

// Selecting this option requires VC 6.0 or later
#if (_MFC_VER < 0x0600)
#error The XML Serialization feature requires Visual C++ 6.0 or higher. Stopping Compilation!
#endif	// _MFC_VER

#endif // _SFL_MFC_SUPPORT && SFL_BLD_XMLSERCORE
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// Also defined in:
//        <Stingray Studio root dir>\Include\Foundation\sflcommon.h
//        <Stingray Studio root dir>\Include\Grid\GXVER.h
//        <Stingray Studio root dir>\Include\Toolkit\atl\Otlbase.h
//
// x64 compatibility
#ifndef SEC_X64_TYPES
#define SEC_X64_TYPES

#ifdef _WIN64 // x64 application-specific; x64 processor independent

typedef INT_PTR SEC_INT, *SEC_PINT;
typedef UINT_PTR SEC_UINT, *SEC_PUINT;
typedef ULONG_PTR SEC_ULONG, *SEC_PULONG;
typedef LONG_PTR SEC_LONG, *SEC_PLONG;
typedef DWORD_PTR SEC_DWORD, *SEC_PDWORD;

#else	//WIN32

typedef int SEC_INT, *SEC_PINT;
typedef unsigned int SEC_UINT, *SEC_PUINT;
typedef unsigned long SEC_ULONG, *SEC_PULONG;
typedef long SEC_LONG, *SEC_PLONG;
typedef unsigned long SEC_DWORD, *SEC_PDWORD;

#endif	//_WIN64/WIN32

#endif	//SEC_X64_TYPES

// backward compatibility as of SFL 5.0.2 (SS 10.2; 8/2009)
#ifdef SEC_IA64_TYPES
#undef SEC_IA64_TYPES
#define SEC_IA64_TYPES SEC_X64_TYPES
#endif

#ifdef _WIN64
// STL causes numerous truncation warnings. Ignore these till an updated version of the SDK is available
#pragma warning(disable : 4018 4146 4244)
#endif	//_WIN64

/////////////////////////////////////////////////////////////////////////////
// Custom Messages

#ifndef SFL_WM_USER
#define SFL_WM_USER   (WM_USER+1000)
#endif

#define WM_GETPRINTABLE                (SFL_WM_USER+1)
#define WM_UIUPDATE                    (SFL_WM_USER+2)
#define WM_CLOSE_PRINT_PREVIEW         (SFL_WM_USER+3)

/////////////////////////////////////////////////////////////////////////////
// Macros

#define MESSAGE_HANDLER_DELEGATE(msg, func) \
	if(uMsg == msg) \
	{ \
		lResult = func(uMsg, wParam, lParam, bHandled); \
	}


#if (_WIN32_IE >= 0x0400)
#define ICC_ALL 0x2FFF
#else
#define ICC_ALL 0x4FF
#endif


#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)   ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)   ((int)(short)HIWORD(lp))
#endif


// Define min and max template functions

template<class _Ty> inline
 const _Ty& _SFLMIN(const _Ty& _X, const _Ty& _Y)
{
	return (_Y < _X ? _Y : _X);
}

template<class _Ty> inline
 const _Ty& _SFLMAX(const _Ty& _X, const _Ty& _Y)
{
	return (_X < _Y ? _Y : _X);
}


///////////////////////////////////////////////////////////////////////////////
// Run-time helper structure sizes (QA 32297)
//
#ifndef _SIZEOF_STRUCT
  #define _SIZEOF_STRUCT(structname, member)  (((int)((LPBYTE)(&((structname*)0)->member) - ((LPBYTE)((structname*)0)))) + sizeof(((structname*)0)->member))
#endif

#if (_WIN32_WINNT >= 0x0600) && !defined(REBARBANDINFO_V6_SIZE)
  #define REBARBANDINFO_V6_SIZE   _SIZEOF_STRUCT(REBARBANDINFO, cxHeader)
#endif // (_WIN32_WINNT >= 0x0600) && !defined(REBARBANDINFO_V6_SIZE)

#if defined(NTDDI_VERSION) && (NTDDI_VERSION >= NTDDI_LONGHORN) && !defined(MCHITTESTINFO_V1_SIZE)
  #define MCHITTESTINFO_V1_SIZE   _SIZEOF_STRUCT(MCHITTESTINFO, st)
#endif // defined(NTDDI_VERSION) && (NTDDI_VERSION >= NTDDI_LONGHORN) && !defined(MCHITTESTINFO_V1_SIZE)

#if !defined(_WIN32_WCE) && (WINVER >= 0x0600) && !defined(NONCLIENTMETRICS_V1_SIZE)
  #define NONCLIENTMETRICS_V1_SIZE   _SIZEOF_STRUCT(NONCLIENTMETRICS, lfMessageFont)
#endif // !defined(_WIN32_WCE) && (WINVER >= 0x0600) && !defined(NONCLIENTMETRICS_V1_SIZE)


///////////////////////////////////////////////////////////////////////////////
// Run-time helper Windows version functions (QA 32297)
//

// Helper function to determine COMCTL32.DLL version
// Refer to http://msdn.microsoft.com/en-us/library/bb776404(VS.85).aspx
// for detailed information on GetDllVersion()
//
#define DLLVERSION(major,minor) MAKELONG(minor,major)
inline DWORD GetDllVersion(LPCTSTR lpszDllName)
{
    HINSTANCE hinstDll;
    DWORD dwVersion = 0;

    /* For security purposes, LoadLibrary should be provided with a 
       fully-qualified path to the DLL. The lpszDllName variable should be
       tested to ensure that it is a fully qualified path before it is used. */
    hinstDll = LoadLibrary(lpszDllName);
	
    if(hinstDll)
    {
        DLLGETVERSIONPROC pDllGetVersion;
        pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hinstDll, "DllGetVersion");

        /* 
		   Because some DLLs might not implement this function, you must test for it 
		   explicitly. Depending on the particular DLL, the lack of a DllGetVersion 
		   function can be a useful indicator of the version.
		*/
        if(pDllGetVersion)
        {
            DLLVERSIONINFO dvi;
            HRESULT hr;

            ZeroMemory(&dvi, sizeof(dvi));
            dvi.cbSize = sizeof(dvi);

            hr = (*pDllGetVersion)(&dvi);

            if(SUCCEEDED(hr))
            {
               dwVersion = DLLVERSION(dvi.dwMajorVersion, dvi.dwMinorVersion);
            }
        }

        FreeLibrary(hinstDll);
    }
    return dwVersion;
}

inline BOOL IsComCtrl6()
{
	// Check COMCTL32.dll version
	BOOL bComCtrl6 = GetDllVersion(TEXT("comctl32.dll")) >= DLLVERSION(6,0);
	return bComCtrl6;
}

inline BOOL IsVista()
{
	// Check OS version
    OSVERSIONINFO ovi = { sizeof(OSVERSIONINFO) };
    BOOL bRet = ::GetVersionEx(&ovi);
    return ((bRet != FALSE) && (ovi.dwMajorVersion >= 6));
}

// For more details on NONCLIENTMETRICS structure,
// refer to http://msdn.microsoft.com/en-us/library/ms724506(VS.85).aspx 
//
// Refer to these Objective Toolkit functions 
// for detailed usage of the SEC_NONCLIENTMETRICS structure
//
//      (global) static HFONT CreateMenuFont() in TMenuFrm.cpp  
//		SECBmpMenuPlugIn::CreateDefaultMenuFont() in TBMPMENU.cpp
//		SECBmpMenuPlugIn::CreateMenuFont() in TBMPMENU.cpp
//		SECMDIFrameWnd::CreateCaptionAppFont(CFont& font) in swinmdi.cpp
//		SECMDIFrameWnd::CreateCaptionDocFont(CFont& font) in swinmdi.cpp
//		SECFrameWnd::CreateCaptionAppFont(CFont& font) in swinfrm.cpp
//		SECFrameWnd::CreateCaptionDocFont(CFont& font) in swinfrm.cpp
//		SECAutoHideBarBtn::OnCreate(LPCREATESTRUCT lpCreateStruct) in sbarautohide.cpp
//		SECAutoHideBar::OnCreate(LPCREATESTRUCT lpCreateStruct) in sbarautohide.cpp
//
// Refer to this Objective Grid sample's function 
// for detailed usage of the SEC_NONCLIENTMETRICS structure
//
//     CMultiLineTooltipsPlugin::InitializeCellTip(...) in 
//	    ..\Samples\Grid\General\CellTipDemo\MultilineTooltipsView.cpp
//
// Define SEC_NONCLIENTMETRICS (QA 32297)
struct SEC_NONCLIENTMETRICS : public NONCLIENTMETRICS
{
		// Constructor
    SEC_NONCLIENTMETRICS() 
    {
    	  // Initialize struct size at compile-time
    	  // Could be Vista or non-Vista struct size, who knows?
        cbSize = sizeof(NONCLIENTMETRICS);

        // Target platform compile-time check
        // If VC++ 9.0 or greater and Vista or greater, then
#if (_MSC_VER >= 1500) && (WINVER >= 0x0600)
				// Do a run-time check for non-Vista platforms
        if(!IsVista())
        	  // If non-Vista platform, reset to "old" struct size
            cbSize = NONCLIENTMETRICS_V1_SIZE;
#endif
    } // end Constructor
    
}; // end struct SEC_NONCLIENTMETRICS


// For further details on REBARBANDINFO structure,
// refer to http://msdn.microsoft.com/en-us/library/bb774393(VS.85).aspx
//
// Refer to these SFL and Objective Toolkit functions 
// for detailed usage of the SEC_REBARBANDINFO structure
//
//    InsertBandInfo() in atlcontrols.h
//    SECReBar::CalcFixedLayout() in sbarcore.cpp
//    SECCustomToolBar::FitBandToSize() in tbarcust.cpp
//
// Define SEC_REBARBANDINFO (QA 32297)
struct SEC_REBARBANDINFO : public REBARBANDINFO
{
		// Constructor
    SEC_REBARBANDINFO() 
    {
    	  // Initialize struct size at compile-time
    	  // Could be Vista or non-Vista struct size, who knows?
        cbSize = sizeof(REBARBANDINFO);

        // Target platform compile-time check
        // If VC++ 9.0 or greater and Vista or greater, then
#if (_MSC_VER >= 1500) && (_WIN32_WINNT >= 0x0600)
				// Do a run-time check for non-Vista platforms
        if(!(IsVista() && IsComCtrl6()))
        	  // If non-Vista platform, reset to "old" struct size
            cbSize = REBARBANDINFO_V6_SIZE;
#endif
    } // end Constructor
    
}; // end struct SEC_REBARBANDINFO


// For further details on MCHITTESTINFO structure,
// refer to http://msdn.microsoft.com/en-us/library/bb774393(VS.85).aspx
//
// Refer to these SFL functions
// for detailed usage of the SEC_MCHITTESTINFO structure
//
//    HitTest() in atlcontrols.h does not call MCHITTESTINFO.cbSize
//
// Define SEC_MCHITTESTINFO (QA 32297)
//struct SEC_MCHITTESTINFO : public MCHITTESTINFO
//{
//		// Constructor
//    SEC_MCHITTESTINFO() 
//    {
//    	  // Initialize struct size at compile-time
//    	  // Could be Vista or non-Vista struct size, who knows?
//        cbSize = sizeof(MCHITTESTINFO);
//        
//        // Target platform compile-time check
//        // If VC++ 9.0 or greater and Vista or greater, then
//#if (_MSC_VER >= 1500) && defined(NTDDI_VERSION) && (NTDDI_VERSION >= NTDDI_LONGHORN)
//				// Do a run-time check for non-Vista platforms
//        if(!(IsVista() && IsComCtrl6()))
//        	  // If non-Vista platform, reset to "old" struct size
//            cbSize = MCHITTESTINFO_V1_SIZE;
//#endif
//    } // end Constructor
//
//}; // end struct SEC_MCHITTESTINFO


#endif // __SFLCOMMON_H__