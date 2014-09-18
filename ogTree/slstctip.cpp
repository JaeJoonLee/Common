//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : slstctip.cpp
//  Function      : 
//  System Name   : KSBuilder
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
///////////////////////////////////////////////////////////////////////////////
// slstctip.cpp
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
//  Author:		Jan

#define _OT_EXPORT_IMPL

#include "stdafx.h"

#pragma warning(disable: 4505)

#ifdef WIN32

#ifdef _SECDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif //_SECDLL

#ifndef __SLSTCTL_H__
#include "toolkit\slstclnt.h"
#endif

#ifndef __SLSTCTIP_H__
#include "toolkit\slstctip.h"
#endif

//#ifndef __SLSTCORE_H__
//#include "TreeCtrl\toolkit\slstcore.h"
//#endif

#ifdef _SECDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif //_SECDLL

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const int iLeftPadding = 1;
static const int iRightPadding = 3;

#ifdef UNDER_CE
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif //UNDER_CE

/////////////////////////////////////////////////////////////////////////////
// SECListTip

//******************************************************************
//  Function Name : SECListTip
//  Function      : 생성자
//  Param         : SECListClient* pLC 
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECListTip::SECListTip( SECListClient* pLC )
{
	m_nHitItem = -1;
	m_nHitSubItem = -1;
	m_pLC = pLC;
}

//******************************************************************
//  Function Name : ~SECListTip
//  Function      : 소멸자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECListTip::~SECListTip()
{
}

BEGIN_MESSAGE_MAP( SECListTip, CWnd )
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SECListTip message handlers

static
void EnsureRectInView(CRect *pRect )
{
	int rightScreen=GetSystemMetrics(SM_CXSCREEN);
	int iShift;
	
	if( pRect->right > rightScreen )
		iShift = rightScreen - pRect->right;    //-ve
	else if( pRect->left < 0 )
		iShift = -pRect->left;                  //+ve
	else
		iShift=0;

	pRect->left   +=  iShift;
	pRect->right  +=  iShift;
}

//******************************************************************
//  Function Name : HookMouseMove
//  Function      : 
//  Param         : UINT iHitFlags,  int nHitItem, int nHitCol, CPoint ptDev 
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECListTip::HookMouseMove(UINT iHitFlags,  int nHitItem, int nHitCol, CPoint ptDev )
{

	CRect rectSubItem;
	CRect rectText;
	POINT ptOrigin;
	CPoint ptLog;
	int nHitSubItem;

	if(!GetSafeHwnd() )
	{
#ifndef UNDER_CE
		VERIFY(CreateEx(0,
				AfxRegisterWndClass( CS_OWNDC | CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, 
 				AfxGetApp()->LoadStandardCursor(IDC_ARROW) ),
		        NULL, WS_POPUP|WS_BORDER,
				0,0,0,0, m_pLC->GetHwnd(),
				NULL));
#else
		VERIFY(CreateEx(0,
		        AfxRegisterWndClass( CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, 
				AfxGetApp()->LoadStandardCursor(IDC_ARROW) ),
		        NULL, WS_POPUP|WS_BORDER,
				0,0,0,0, m_pLC->GetHwnd(),
				NULL));
#endif //UNDER_CE
	}

	if (nHitCol != -1)
	{
		nHitSubItem = m_pLC->GetSubItemHit(nHitCol);
	}
	else
		nHitSubItem = -1;

	VERIFY(m_pLC->GetOrigin(&ptOrigin));

	ptLog.x = ptDev.x + ptOrigin.x;
	ptLog.y = ptDev.y + ptOrigin.y;

	CRect rcInside;
	m_pLC->GetInsideRect(rcInside);
	if(	(iHitFlags & LVHT_ONITEMLABEL || (iHitFlags&0x2000 && nHitSubItem > 0))
		&& ( nHitItem != -1 && nHitCol != -1 )
		&& GetActiveWindow() )
	{
		////
		// get text rect of hit item
		if( !m_pLC->GetItemRect( nHitItem, nHitCol, &rectSubItem, LVIR_BOUNDS ) )
		{
			ASSERT(FALSE);
			return(FALSE);
		}
		
		// our actual drawing limit
		rectSubItem.right -= SEC_RIGHT_OFFSET;

		if( !m_pLC->GetItemRect( nHitItem, nHitCol, &rectText, LVIR_LABEL) )
		{
			ASSERT(FALSE);
			return(FALSE);
		}
		
		// decision to show the tooltip or not.
		if ( ( rectText.right > min(rectSubItem.right, rcInside.Width())) ||
			(rectText.left < rcInside.left && rectText.right > rcInside.left) )
		{

			if (nHitItem != m_nHitItem || nHitSubItem != m_nHitSubItem)
			{
				Hide();

				rectText.InflateRect(2, 0, 2, 2);
				m_nHitItem = nHitItem;
				m_nHitSubItem = nHitSubItem;
				m_rectItem = rectSubItem;

				CString str = m_pLC->GetItemText( nHitItem, nHitSubItem );
				if ( str.IsEmpty() )
					return FALSE;				
				SetWindowText( str );

				m_pLC->Client2Screen(rectText);
				// To be consistent with CTreeCtrl.
//				EnsureRectInView(&rectText);
				
				SetWindowPos(NULL, rectText.left - iLeftPadding, rectText.top, rectText.Width() + iRightPadding,
					rectSubItem.Height(), SWP_NOACTIVATE);

				ShowWindow( SW_SHOWNOACTIVATE );
				SetTimer( TOOLTIP_TIMER, 500, NULL);

				// QA: 31895 - Ensure that mouse messages work in ActiveX.
				m_pLC->Capture(TRUE);

				Invalidate(FALSE);
				UpdateWindow();
			}
			return TRUE;
		}
	}

	Hide();

	return FALSE;
}

//******************************************************************
//  Function Name : PreTranslateMessage
//  Function      : 
//  Param         : MSG* pMsg 
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECListTip::PreTranslateMessage( MSG* pMsg )
{
	// Dispatch mouse button messages to the list/tree control
#ifndef UNDER_CE
	if( (pMsg->message >= WM_LBUTTONDOWN && pMsg->message <= WM_MBUTTONDBLCLK) ||
		(pMsg->message >= WM_NCLBUTTONDOWN && pMsg->message <= WM_NCMBUTTONDBLCLK) ||
		(pMsg->message == WM_MOUSEMOVE))
#else
	if( (pMsg->message >= WM_LBUTTONDOWN && pMsg->message <= WM_MBUTTONDBLCLK) )
#endif
	{
		CPoint pt = CPoint( GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam) );
#ifndef UNDER_CE
		// Convert the WM_NCXBUTTONX msg to a suitable WM_XBUTTONX message
		if( pMsg->message >= WM_NCLBUTTONDOWN && pMsg->message <= WM_NCMBUTTONDBLCLK )
			MAKE_NCMOUSEXTOMOUSEX(pMsg)
		else
#endif //UNDER_CE
			FromHandle(pMsg->hwnd)->ClientToScreen(&pt);

		HWND hWndList = m_pLC->GetHwnd();
		::ScreenToClient(hWndList, &pt);
		pMsg->lParam = MAKELPARAM(pt.x, pt.y);
		pMsg->hwnd = hWndList;
		::DispatchMessage(pMsg);

		return TRUE;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

//******************************************************************
//  Function Name : Hide
//  Function      : 
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECListTip::Hide()
{
	HWND hwndList = m_pLC->GetHwnd();
	if(GetSafeHwnd() && IsWindowVisible())
	{
		ShowWindow( SW_HIDE );

		// redraw the uncovered area immediately
		if ( hwndList != NULL )
		{
#ifndef UNDER_CE
			::RedrawWindow( hwndList, &m_rectItem, NULL, 
				RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW );
#else
			CWnd* pWndTemp = CWnd::FromHandle(hwndList);
			pWndTemp->RedrawWindow(&m_rectItem);
#endif
		}
		KillTimer(TOOLTIP_TIMER);
	}

	m_nHitItem = -1;
	m_nHitSubItem = -1;
	m_rectItem.SetRect(0,0,0,0);	

	// QA: 31895 - Ensure that mouse messages work with ActiveX.
	CWnd* pWndCapture = GetCapture();
	if(pWndCapture && (pWndCapture->GetSafeHwnd() == hwndList))
	{
		ReleaseCapture();
	}
}

//******************************************************************
//  Function Name : Refresh
//  Function      : 
//  Param         : void
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECListTip::Refresh(void)
{
	if( GetSafeHwnd() && IsWindowVisible() )
	{
		Invalidate();
		UpdateWindow();
	}
}

//******************************************************************
//  Function Name : SetWindowText
//  Function      : 
//  Param         : const CString &str 
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECListTip::SetWindowText(  const CString &str )
{
	m_strText=str;
}

//******************************************************************
//  Function Name : OnPaint
//  Function      : 
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECListTip::OnPaint() 
{

	CPaintDC dc(this); // device context for painting

	if ( m_nHitItem == -1 )
		return;

	if( m_pLC->IsSelected(m_nHitItem) )
	{
		dc.SetTextColor( m_pLC->GetSelTextColor  () );
		dc.SetBkColor  ( m_pLC->GetSelTextBkColor() );
	}
	else
	{
		dc.SetTextColor( m_pLC->GetToolTipTextColor()   );
		dc.SetBkColor  ( m_pLC->GetToolTipBkColor() );
	}

	CRect rectClient;
	GetClientRect(rectClient);
	dc.FillSolidRect( rectClient, dc.GetBkColor() );
	
	// GetLabelFont may fail on NT 3.51. Cope gracefully
	CFont *pPrevFont = NULL;
	CFont *pFontBold = NULL;
	CFont *pFont = m_pLC->GetLabelFont();

	if(pFont) 
	{
		ASSERT_VALID(pFont);
		//If item state is set to TVIS_BOLD, then use bold fonts for the tooltip
		UINT nState = m_pLC->GetStateFromItemIndex(m_nHitItem,TVIF_STATE|TVIF_HANDLE);
		if(nState & TVIS_BOLD)
		{
			LOGFONT lf;
			memset(&lf,0,sizeof(lf));
			pFont->GetLogFont(&lf);
			lf.lfWeight = FW_BOLD;
			pFontBold = new CFont;
			pFontBold->CreateFontIndirect(&lf);			
			pFont = pFontBold;
		}

		pPrevFont = (CFont *)dc.SelectObject( pFont );
	}

	rectClient.left += 2;
	
	//	Make the text-drawing behavior consistent with that of CTreeCtrl.
	int charNum;
	charNum = m_strText.Find('\n');
	if (charNum == -1) {
		charNum = min(MAX_DISPLAY_CHAR_NUM, m_strText.GetLength());
	} else {
		charNum = min(MAX_DISPLAY_CHAR_NUM, charNum);
	}

	dc.DrawText( m_strText, 
//					   -1,
					   charNum,
					   rectClient,
					   DT_VCENTER | DT_SINGLELINE | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX);

	if(pPrevFont)
		dc.SelectObject( pPrevFont );

	if(pFontBold)
		delete pFontBold;
	
	// Do not call CWnd::OnPaint() for painting messages
}

//******************************************************************
//  Function Name : OnTimer
//  Function      : 
//  Param         : SEC_UINT nIDEvent
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECListTip::OnTimer(SEC_UINT nIDEvent)
{
	if(nIDEvent == TOOLTIP_TIMER)
	{
		HWND hWnd = m_pLC->GetHwnd();
		CRect rcClient;
		::GetClientRect(hWnd, &rcClient);
		CPoint pt;
		GetCursorPos(&pt);
		::ScreenToClient(hWnd, &pt);
		if( !rcClient.PtInRect(pt) )
			Hide();
	}
}


//******************************************************************
//  Function Name : OnDestroy
//  Function      : 
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECListTip::OnDestroy() 
{
	CWnd::OnDestroy();	
	m_nHitItem = -1;
}

#endif // WIN32
