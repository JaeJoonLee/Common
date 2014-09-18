//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : TrCtlX.cpp
//  Function      : 
//  System Name   : KSBuilder
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
///////////////////////////////////////////////////////////////////////////////
// TrCtlX.cpp
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
//          Supplement Section 227.7202, Government뭩 use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
// 
//  Authors:		Dean Hallman and Justin Rudd

#define _OT_EXPORT_IMPL

#include "stdafx.h"

#ifdef WIN32

#ifdef _SECDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif //_SECDLL

#ifndef __TRCTLX_H__
#include "toolkit\trctlx.h"
#endif

#ifndef __RWUXTHEME_H
#include "RWUXTheme.h"
#endif

#ifdef _SECDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif //_SECDLL

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// SECTreeCtrl Construction/Destruction
//////////////////////////////////////////////////////////////////////

//@doc SECTreeCtrl
//@mfunc Constructor for an SECTreeCtrl.
//@comm see the SECTreeCore class for tree control member functions.
//@xref <c SECTreeCore>
//@xref <c SEC_LISTCLASS>
//******************************************************************
//  Function Name : SECTreeCtrl
//  Function      : 생성자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeCtrl::SECTreeCtrl()
{
	  m_hTreeTheme = NULL; // QA: 32574
}

//******************************************************************
//  Function Name : ~SECTreeCtrl
//  Function      : 소멸자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeCtrl::~SECTreeCtrl()
{
	// QA: 32574
	if(m_hTreeTheme)
	{
#ifndef __RWUXTHEME_H
		RWCloseThemeData(m_hTreeTheme);
#endif
	}
}

IMPLEMENT_DYNAMIC( SECTreeCtrl, SECListCtrl )

BEGIN_MESSAGE_MAP( SECTreeCtrl, SECListCtrl )
	CHAIN_TREECORE_MESSAGES()
	// QA: 32574 - removed call to ON_WM_NCPAINT() for QA: 31209.

	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		ON_MESSAGE(WM_THEMECHANGED, OnThemeChanged)
	#endif
END_MESSAGE_MAP()


//******************************************************************
//  Function Name : DDX_Control
//  Function      : 
//  Param         : CDataExchange* pdx, int idc,SECTreeCtrl& tree
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void DDX_Control(CDataExchange* pdx, int idc,SECTreeCtrl& tree)
{
	if( tree.GetSafeHwnd() == NULL )
	{
		ASSERT(pdx->m_bSaveAndValidate == FALSE);

		if( tree.SubclassTreeCtrlId( idc, pdx->m_pDlgWnd ) == FALSE )
		{
			ASSERT(FALSE);
			pdx->Fail();
		}
	}
}

// 
//******************************************************************
//  Function Name : OnNcPaint
//  Function      : QA: 32574
//  Param         : HRGN hrgnUpdate
//  Return        : LRESULT 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
LRESULT SECTreeCtrl::OnNcPaint(HRGN hrgnUpdate)
{
	if(!m_hTreeTheme)
	{
#ifndef __RWUXTHEME_H
		m_hTreeTheme = RWOpenThemeData(m_hWnd, L"TREEVIEW");
#endif
	}

	if(m_hTreeTheme)
	{
		//---------------------//
		// Draw Themed Border  //
		//---------------------//

		HDC hdc = ::GetWindowDC(m_hWnd);
		RECT rc;
		RECT rcWindow;
		DWORD state = ETS_NORMAL;
		HRGN hrgnClip;

		// State
		if(!::IsWindowEnabled(this->GetSafeHwnd()))
		{
			state = ETS_DISABLED;
		}else if(GetFocus() == this->GetParent())
		{
			state = ETS_HOT;
		}else
		{
			state = ETS_NORMAL;
		}

		// Rect mapping
		::GetWindowRect(m_hWnd, &rcWindow);
		::GetClientRect(m_hWnd, &rc);
		::ClientToScreen(m_hWnd, (POINT *)&rc.left);
		::ClientToScreen(m_hWnd, (POINT *)&rc.right);

		rc.right = rcWindow.right - (rc.left - rcWindow.left);
		rc.bottom = rcWindow.bottom - (rc.top - rcWindow.top);

		// Region
		hrgnClip = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

		if(hrgnUpdate != (HRGN)1)
		CombineRgn(hrgnClip, hrgnClip, hrgnUpdate, RGN_AND);

		OffsetRect(&rc, -rcWindow.left, -rcWindow.top);

		ExcludeClipRect(hdc, rc.left, rc.top, rc.right, rc.bottom);
		OffsetRect(&rcWindow, -rcWindow.left, -rcWindow.top);

		//if (IsThemeBackgroundPartiallyTransparent (m_hTreeTheme, TVP_TREEITEM, state))
		//RWDrawThemeParentBackground(m_hWnd, hdc, &rcWindow);
#ifndef __RWUXTHEME_H
		RWDrawThemeBackground(m_hTreeTheme, hdc,
		TVP_TREEITEM, 
		state,
		&rcWindow, NULL);
#endif
		::ReleaseDC(m_hWnd, hdc);
	}

	return 0; 
}

// 
#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
//******************************************************************
//  Function Name : OnThemeChanged
//  Function      : QA: 32259
//  Param         : WPARAM wParam, LPARAM lParam
//  Return        : LRESULT 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
LRESULT SECTreeCtrl::OnThemeChanged(WPARAM wParam, LPARAM lParam)
{
    // Add specific theme handling code here...
    return 0;
}
#endif

// 
//******************************************************************
//  Function Name : DefWindowProc
//  Function      : QA: 32574
//  Param         : UINT message, WPARAM wParam, LPARAM lParam
//  Return        : LRESULT 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
LRESULT SECTreeCtrl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{				
	// Handle messages ourselves.
	switch(message)
	{
	case WM_NCPAINT:
		 OnNcPaint((HRGN)wParam);
		break;
	default:
		return CWnd::DefWindowProc(message, wParam, lParam);
	}
	return 0;
}

#endif // WIN32
