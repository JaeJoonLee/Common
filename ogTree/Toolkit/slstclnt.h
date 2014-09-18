///////////////////////////////////////////////////////////////////////////////
// slsclnt.h
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
//  Authors:		Dean Hallman and Justin Rudd

#ifdef WIN32

#ifndef __SLSTCLNT_H__
#define __SLSTCLNT_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include "..\StingrayExportDefs.h"

//
// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL

/*
	Normally a class like this would be a set of pure virtual functions, but for some reason VC 4.x won't let me use,
	 a pure virtual interface as a default template parameter.  So these are just stubs that do nothing...
*/

class SECListClient
{
public:
	inline virtual HWND GetHwnd() const
		{ return NULL; }
	inline virtual BOOL IsWordWrapEnabled() const
		{ return FALSE; }
	inline virtual BOOL ProcessAndDestroyEditLabel( BOOL )
		{ return FALSE; }
	inline virtual int  GetSubItemHit( int ) const
		{ return -1; }
	inline virtual BOOL GetOrigin( LPPOINT ) const
		{ return FALSE; }
	inline virtual void GetInsideRect( LPRECT ) const
		{}
	inline virtual BOOL GetItemRect( int, int, LPRECT, UINT ) const
		{ return FALSE; }
	inline virtual CString GetItemText( int, int ) const
		{ return _T(""); }
	inline virtual void Client2Screen( LPRECT )
		{}
	inline virtual CWnd* Capture( BOOL )
		{ return NULL; }
	inline virtual BOOL IsSelected( int ) const
		{ return FALSE; }
	inline virtual COLORREF GetSelTextColor() const
		{ return 0; }
	inline virtual COLORREF GetSelTextBkColor() const
		{ return 0; }
	inline virtual COLORREF GetToolTipTextColor() const
		{ return 0; }
	inline virtual COLORREF GetToolTipBkColor() const
		{ return 0; }
	inline virtual CFont* GetLabelFont() const 
		{ return NULL; }
	inline virtual UINT GetStateFromItemIndex(int, UINT) const
		{ return 0; }
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //__SLSTCLNT_H__

#endif //WIN32
