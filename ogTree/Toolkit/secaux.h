///////////////////////////////////////////////////////////////////////////////
// secaux.h
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


#ifndef __SECAUX_H__
#define __SECAUX_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include "..\StingrayExportDefs.h"

#define CX_BORDER       1
#define CY_BORDER       1

#pragma warning(disable: 4005)

/////////////////////////////////////////////////////////////////////////////
// OT Auxiliary System/Screen metrics
// SEC_AUX_DATA definitions have been moved to RWUXTheme.


/////////////////////////////////////////////////////////////////////////////
// OT General purpose 

// Useful for parsing changed style bits to feed to ModifyStyle functions
#define SEC_BITS_ADDED(oldVal,newVal) ((oldVal|newVal)^oldVal)
#define SEC_BITS_REMOVED(oldVal,newVal) ((oldVal^newVal)&oldVal)

// determine number of elements in an array (not bytes) for MBCS & Unicode
#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif //_countof

// SEC_TRACE_WINDOW(p,w,s)
//   calls TRACE("%s%s%s", p, x, s) where x = a description of window w.
//   w may be a CWnd* or an HWND.  If null, p defaults to "".  If null, s defaults to "\n".
#if !defined _DEBUG
#define SEC_TRACE_WINDOW(prefix, window, suffix)
#else // #if !defined _DEBUG
#define SEC_TRACE_WINDOW(prefix, window, suffix) __secTraceWindow(0, prefix, window, suffix)
extern TOOLKIT_API void __secTraceWindow ( FILE * pFile, TCHAR * pszPrefix, CWnd * pwndTrace, TCHAR * pszSuffix = 0 );
extern TOOLKIT_API void __secTraceWindow ( FILE * pFile, TCHAR * pszPrefix, HWND hwndTrace, TCHAR * pszSuffix = 0 );
#endif // #else for #if !defined _DEBUG



/////////////////////////////////////////////////////////////////////////////
// Registered Message helpers

// REGISTERED_MSGID_VAR(m)
// -----------------------
//   expands to the name of the standard variable to use for registered message m.
//
//   For example, 
//        #define WM_TESTREGMSG ::RegisterWindowMessage(_T("TEST REG MSG"))
//
//        const UINT REGISTERED_MSGID_VAR(WM_TESTREGMSG) = WM_TESTREGMSG;
//
// DEFINE_REGISTERED_MSGID_VAR(m)
// ------------------------------
//   expands generically to the line above beginning with "const UINT":
//
//        const UINT REGISTERED_MSGID_VAR(m) = m;
//
// The purpose of these macros is to define a consistent way for naming global variables
// that must be used with the message map entry ON_REGISTERED_MESSAGE()
//
#define REGISTERED_MSGID_VAR(msg) __g_ui##msg##MsgID
#define DEFINE_REGISTERED_MSGID_VAR(msg) const UINT __g_ui##msg##MsgID = msg;
// implementation note:  The implementation of DEFINE_REGISTERED_MSGID_VAR repeats the
//                       name of the identifier constructed in REGISTERED_MSGID_VAR rather
//                       than use the REGISTERED_MSGID_VAR macro directly.  The reason is 
//                       that an unexpected compiler error resulted.  Depending on the 
//                       tweaks to try and make it compile, the compiler ended in an internal
//                       compiler error and call MS message.  The solution above avoids this problem.

/////////////////////////////////////////////////////////////////////////////
// Pragma Message helpers - Thanks to Jeffery Richter

// _SECSTR(x)
// ----------
//   expands x to a string
//
// _SECSTREX(x)
// ------------
//   expands x to a string using _SECSTR
//
// SECMSG(desc)
// ------------
//   takes a string (desc) and outputs to the debug window using pragma message.  Includes File Name and Line number
//		for easy double clicking on the message to jump right to the line.
//      Works in both debug and release builds.
//
// _SECSTREX is an extra layer of indirection that normally isn't needed.  But in order to convert __LINE__ to a string
//  it is needed because the preprocessor knows what __LINE__ is.  So the first time through expands __LINE__ to the line number 
//  and that line number gets passed on to _SECSTR which converts it to the string
//
// USE
// ---
// #pragma SECMSG(_T("Add Error Checking Here"))
//
#define _SECSTR(x)		#x
#define _SECSTREX(x)	_SECSTR(x)
#define SECMSG(desc)    message(__FILE__ "(" _SECSTREX(__LINE__) "):" desc)

/////////////////////////////////////////////////////////////////////////////
// otmax and otmin.

// otmax(a,b)
// ----------
//   returns the max of "a" and "b".  Assumes "a" and "b" have a valid operator >
//
// otmin(a,b)
// ----------
//   returns the min of "a" and "b".  Assumes "a" and "b" have a valid operator <

#ifndef otmax
	#define otmax(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef otmin
	#define otmin(a,b) (((a) < (b)) ? (a) : (b))
#endif

// USE
// ---
// int i = 10;
// int j = 100;
// int max = otmax(i,j);
// _ASSERTE( max == 100 );
// int min = otmin(i,j);
// _ASSERTE( min == 10 );

// Implementation note...these are here because STL defines min and max as templated functions and windows defines these as macros
//  in the new list control we use the macro versions, but depending on the STL that is being used, it will give an ambiguous error
//  so I implemented our own min and max macros that are the exact same as the normal macros but with different names...

#endif // __SECAUX_H__
