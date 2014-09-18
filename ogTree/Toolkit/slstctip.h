///////////////////////////////////////////////////////////////////////////////
// slstctip.h
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
//  Author:		Jan


#ifdef WIN32

#ifndef __SLSTCTIP_H__
#define __SLSTCTIP_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

// "windowsx.h" is not needed in this header file. 
//#ifndef _INC_WINDOWSX
//#include <windowsx.h>
//#endif

#include"..\StingrayExportDefs.h"

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

#define TOOLTIP_TIMER			(0xf001)

//	To be consistent with CTreeCtrl: only show a portion of large texts.
#define MAX_DISPLAY_CHAR_NUM	259

// Macro for converting non-client mouse button messages to regular mouse message
#define MAKE_NCMOUSEXTOMOUSEX(X)							\
		  { X->wParam = (X->message == WM_NCLBUTTONDOWN)?MK_LBUTTON:MK_RBUTTON;	\
			X->message = X->message + 0x0160; }

// Forward declarations
class SECListClient;

class SECListTip : public CWnd
{
// Construction
public:
	TOOLKIT_API SECListTip( SECListClient* );

// Attributes
protected:
	int m_nHitItem;
	int m_nHitSubItem;
	SECListClient *m_pLC;
	CString       m_strText;
	CRect         m_rectItem;

	TOOLKIT_API void SetWindowText( const CString &str);

// Operations
public:
	TOOLKIT_API void Refresh(void);

// Overrides
        TOOLKIT_API virtual void Hide();
        TOOLKIT_API virtual BOOL HookMouseMove(UINT iHitFlags, int nHitItem, int nHitCol, CPoint pt);
        TOOLKIT_API virtual BOOL PreTranslateMessage( MSG* pMsg );

// Implementation
public:
	TOOLKIT_API virtual ~SECListTip();

	// Generated message map functions
protected:
	TOOLKIT_API afx_msg void OnPaint();
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnTimer(SEC_UINT nIDEvent);

	TOOLKIT_DECLARE_MESSAGE_MAP()
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __SLSTCTIP_H__

#endif // WIN32
