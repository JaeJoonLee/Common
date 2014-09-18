// CSTMEdit.cpp : implementation file
//

#include "stdafx.h"
#include "CSTMEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CColorMap* GetColorMap();
extern CGdiManager* GetGDIMng();
//extern CBrushManager* GetBrush();
//#define CR_IDX_EDIT_BACK				28
//#define CR_IDX_EDIT_FORE				29
//#define CR_IDX_EDIT_LINE				27
#define CR_IDX_EDIT_BACK				6
#define CR_IDX_EDIT_FORE				8
#define CR_IDX_EDIT_LINE				9

#define DEF_FONT_IDX					2
/////////////////////////////////////////////////////////////////////////////
// CCSTMEdit
IMPLEMENT_DYNCREATE( CCSTMEdit, CEdit )

CCSTMEdit::CCSTMEdit()
{
	if( !m_pGDIMng )
		m_pGDIMng = GetGDIMng();

	m_nFontIndex = DEF_FONT_IDX;
	m_nBackCrIdx = CR_IDX_EDIT_BACK;
	m_nForeCrIdx = CR_IDX_EDIT_FORE;
	m_nBorderCrIdx = CR_IDX_EDIT_LINE;

	m_MenuResourceID = 0;

    m_clrTextColor = ::GetSysColor( COLOR_WINDOWTEXT );
    m_clrBackColor   = ::GetSysColor( COLOR_WINDOW     );

    CreateBrushType();


	m_clr3DFace		= GetSysColor(COLOR_3DFACE);
	m_clr3DLight	= GetSysColor(COLOR_3DLIGHT);
	m_clr3DHilight	= GetSysColor(COLOR_3DHILIGHT);
	m_clr3DShadow	= GetSysColor(COLOR_3DSHADOW);
	m_clr3DDkShadow = GetSysColor(COLOR_3DDKSHADOW);

	m_bDrawFlat = TRUE;
	m_bDrawOutline = TRUE;
	m_bReadOnly = FALSE;

	m_pfontText = NULL;

	CColorMap* pColorMap = GetColorMap();
	if( !pColorMap )
	{
		ASSERT(pColorMap);
		return;
	}

	m_clrBackColor	= pColorMap->GetColor( (short)m_nBackCrIdx );
	m_clrTextColor	= pColorMap->GetColor( (short)m_nForeCrIdx );
	m_clrOutLineColor= RGB(109,127,149);


}

CCSTMEdit::~CCSTMEdit()
{
	///// 사용이 끝난 brush를 반환
	m_brBkGround.DeleteObject();
}


BEGIN_MESSAGE_MAP(CCSTMEdit, CEdit)
	//{{AFX_MSG_MAP(CCSTMEdit)
	ON_WM_CONTEXTMENU()
    ON_WM_CHAR()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR_REFLECT()

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSTMEdit message handlers



COLORREF CCSTMEdit::SetBackColor( COLORREF crColor )
{
    _ASSERT(::IsWindow(m_hWnd)); 

    COLORREF crPrevBkColor = m_clrBackColor;

    m_clrBackColor = crColor;
    
	m_brBkGround.DeleteObject();

    CreateBrushType();

    Invalidate();

    return crPrevBkColor;
}
COLORREF CCSTMEdit::SetBackColor( short nIndex  )
{
    _ASSERT(::IsWindow(m_hWnd)); 

    COLORREF crPrevBkColor = m_clrBackColor;
	
	CColorMap* pColorMap = GetColorMap();
	if( !pColorMap )
	{
		ASSERT( pColorMap );
	}
//	m_clrTextColor = pColorMap->GetColor( nIndex );
	m_clrBackColor = pColorMap->GetColor( nIndex );
   
	m_brBkGround.DeleteObject();

    CreateBrushType();

    Invalidate();

    return crPrevBkColor;
}



COLORREF CCSTMEdit::SetTextColor( COLORREF crColor )
{
    _ASSERT(::IsWindow(m_hWnd)); 
    
    COLORREF crPrevTextColor = m_clrTextColor;
    
    m_clrTextColor = crColor;
    
    Invalidate();
    
    return crPrevTextColor;
}
COLORREF CCSTMEdit::SetTextColor( short nIndex )
{
	_ASSERT(::IsWindow(m_hWnd)); 
    
    COLORREF crPrevTextColor = m_clrTextColor;

	CColorMap* pColorMap = GetColorMap();
	if( !pColorMap )
	{
		ASSERT( pColorMap );
	}

	m_clrTextColor = pColorMap->GetColor( nIndex );

	Invalidate();
    
    return crPrevTextColor;
}

/////////////////////////////////////////////////////////////////////////////
// Protected and private interfaces:


BOOL CCSTMEdit::CreateBrushType()
{
	m_brBkGround.CreateSolidBrush ( m_clrBackColor );

	return TRUE;
}

void CCSTMEdit::OnContextMenu(CWnd* pWnd, CPoint point) 
{
    if ( !m_MenuResourceID ) {
         CEdit::OnContextMenu( pWnd, point );
         return;
    }

    CMenu menu;
    
    if ( !menu.LoadMenu( m_MenuResourceID ) ) {
         CEdit::OnContextMenu( pWnd, point);
    }
    else {
         CMenu* pContext = menu.GetSubMenu(0);
         pContext->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, this );
    }
}

void CCSTMEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(!m_bReadOnly)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		GetParent()->SendMessage(WM_NOTIFY_SEDIT_ON_CHAR,nChar,(LPARAM)this);
	}
}

HBRUSH CCSTMEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
    pDC->SetTextColor( m_clrTextColor );
	pDC->SetBkColor( m_clrBackColor );

	return (HBRUSH)m_brBkGround;
}

void CCSTMEdit::SetFlat(BOOL bFlag)
{
	m_bDrawFlat = bFlag;
}

void CCSTMEdit::SetDrawOutline(BOOL bFlag)
{
	m_bDrawOutline	= bFlag;
}

BOOL CCSTMEdit::SetReadOnly(BOOL bReadOnly)
{
	m_bReadOnly = TRUE;
	
	m_clrBackColor = RGB(237,241,244);
	m_clrTextColor = RGB(128, 128, 128);

	m_brBkGround.DeleteObject();

    CreateBrushType();
    
    Invalidate();

//	EnableWindow(FALSE);

	return FALSE;
}

BOOL CCSTMEdit::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN){
		switch(pMsg->wParam){
		case VK_RETURN :
		case VK_ESCAPE :
		case VK_DELETE :
			return TRUE;
		}
	}

	return CEdit::PreTranslateMessage(pMsg);
}

void CCSTMEdit::DrawBorder()
{
	CRect rcItem;
	DWORD dwExStyle = GetExStyle();
	CDC* pDC = GetDC();
	int nBorderWidth = 0;

	GetWindowRect(&rcItem);
	ScreenToClient(&rcItem);

	if (dwExStyle & WS_EX_DLGMODALFRAME)
	{
		nBorderWidth += 3;
	}
	if (dwExStyle & WS_EX_CLIENTEDGE) 
	{
		nBorderWidth += 2;
	}
	if (dwExStyle & WS_EX_STATICEDGE && !(dwExStyle & WS_EX_DLGMODALFRAME)) 
	{
		nBorderWidth ++;
	}
	if(m_bDrawOutline)
	{
		pDC->Draw3dRect(rcItem, m_clrOutLineColor,m_clrOutLineColor );
		rcItem.DeflateRect(1,1);
	}

	COLORREF	colorBoard = m_clr3DFace;
	if(m_bDrawFlat)
		colorBoard = m_clrBackColor;

	for (int nLoop = 0; nLoop < nBorderWidth; nLoop++) {
		pDC->Draw3dRect(rcItem, colorBoard, colorBoard);
		rcItem.DeflateRect(1, 1);
	}


	if (m_bDrawFlat == FALSE) {
	
		rcItem.InflateRect(1, 1);
		if (dwExStyle & WS_EX_CLIENTEDGE) {
			pDC->Draw3dRect(rcItem, m_clr3DDkShadow, m_clr3DLight);
			rcItem.InflateRect(1, 1);
			pDC->Draw3dRect(rcItem, m_clr3DShadow, m_clr3DHilight);
			rcItem.InflateRect(1, 1);
		}

		if (dwExStyle & WS_EX_STATICEDGE && !(dwExStyle & WS_EX_DLGMODALFRAME)) {
			pDC->Draw3dRect(rcItem, m_clr3DShadow, m_clr3DHilight);
			rcItem.InflateRect(1, 1);
		}

		if (dwExStyle & WS_EX_DLGMODALFRAME) {
			pDC->Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);
			rcItem.InflateRect(1, 1);
			pDC->Draw3dRect(rcItem, m_clr3DHilight, m_clr3DShadow);
			rcItem.InflateRect(1, 1);
			pDC->Draw3dRect(rcItem, m_clr3DLight, m_clr3DDkShadow);
		}
	}

/*	DWORD dwStyle = this->GetStyle();
	if(::IsWindowEnabled( GetSafeHwnd() ) == FALSE || (dwStyle & ES_READONLY )  )
	{
		pDC->FillSolidRect( rcItem, GetSysColor(COLOR_BTNFACE) );
//		CString strText = GetText();
//		m_clrTextColor = ::GetSysColor( COLOR_BTNTEXT );
//		pDC->DrawText ( strText  , rcItem, DT_CENTER | DT_CALCRECT );
	}*/	

	ReleaseDC(pDC);
}

void CCSTMEdit::OnSysColorChange() 
{
	CEdit::OnSysColorChange();
	
	m_clr3DFace = GetSysColor(COLOR_3DFACE);
	m_clr3DLight = GetSysColor(COLOR_3DLIGHT);
	m_clr3DHilight = GetSysColor(COLOR_3DHILIGHT);
	m_clr3DShadow = GetSysColor(COLOR_3DSHADOW);
	m_clr3DDkShadow = GetSysColor(COLOR_3DDKSHADOW);
	
}

void CCSTMEdit::OnPaint() 
{	
	Default();

	DrawBorder();
	
}

BOOL CCSTMEdit::SetTextFont( LONG nHeight, BOOL bBold, BOOL bItalic, const CString& sFaceName )
{
	LOGFONT lgfnt;

	lgfnt.lfHeight			= -MulDiv(nHeight, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY), 72);
	lgfnt.lfWidth			= 0;
	lgfnt.lfEscapement		= 0;
	lgfnt.lfOrientation		= 0;
	lgfnt.lfWeight			= bBold?FW_BOLD:FW_DONTCARE;
	lgfnt.lfItalic			= bItalic?TRUE:FALSE;
	lgfnt.lfUnderline		= FALSE;
	lgfnt.lfStrikeOut		= FALSE;
	lgfnt.lfCharSet			= DEFAULT_CHARSET;
	lgfnt.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	lgfnt.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lgfnt.lfQuality			= DEFAULT_QUALITY;
	lgfnt.lfPitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;
	strcpy( lgfnt.lfFaceName, sFaceName );

	return SetTextFont( lgfnt );

}


BOOL CCSTMEdit::SetTextFont( const LOGFONT& lgfnt )
{

//	m_pfontText = CFontMng::GetFont(lgfnt);
	m_pfontText = m_pGDIMng->GetFont( m_nFontIndex, min( m_fXRate, m_fYRate) );
	SetFont(m_pfontText, TRUE);

	return TRUE;
}


BOOL CCSTMEdit::GetTextFont( LOGFONT* plgfnt)
{
	GetFont()->GetObject( sizeof(LOGFONT), (void*)plgfnt);
	return TRUE;
}



BOOL CCSTMEdit::SetFontBold( BOOL bBold )
{
	LOGFONT lgfnt;
	
	GetTextFont( &lgfnt );
	lgfnt.lfWeight	= bBold?FW_BOLD:FW_DONTCARE; 
	
	SetTextFont( lgfnt );
	
	return TRUE;
}


BOOL CCSTMEdit::SetFontItalic( BOOL bItalic )
{
	LOGFONT lgfnt;
	
	GetTextFont( &lgfnt );
	lgfnt.lfItalic	= bItalic ? TRUE : FALSE; 
	
	SetTextFont( lgfnt );
	return TRUE;
}


BOOL CCSTMEdit::SetFontHeight( int nHeight )
{
	LOGFONT lgfnt;
	
	GetTextFont( &lgfnt );
	lgfnt.lfHeight	= -MulDiv(nHeight, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY), 72);    
	lgfnt.lfWidth	= 0; 
	
	SetTextFont( lgfnt );
	return TRUE;
}



BOOL CCSTMEdit::SetFontFaceName( const CString& sFaceName )
{
	LOGFONT lgfnt;
	
	GetTextFont( &lgfnt );
	strcpy( lgfnt.lfFaceName, sFaceName );
	
	SetTextFont( lgfnt );
	return TRUE;
}


BOOL CCSTMEdit::SetFontRotation( int nAngle )
{
	LOGFONT lgfnt;
	
	GetTextFont( &lgfnt );
	lgfnt.lfEscapement	= long(nAngle)*10;
	lgfnt.lfOrientation	= long(nAngle)*10;
	SetTextFont( lgfnt );
	
	return TRUE;
}


CString	CCSTMEdit::GetText()
{
	CString szText;
	GetWindowText(szText);
	return szText;
}
void CCSTMEdit::SetText(CString szText)
{
	SetWindowText(szText);
	return;
}

void CCSTMEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{		
	CEdit::OnLButtonDown(nFlags, point);

}

void CCSTMEdit::SetOutlineColor( COLORREF color )
{
	m_clrOutLineColor = color;
}



void CCSTMEdit::SetOutlineColor( short nIndex )
{
	CColorMap* pColorMap = GetColorMap();

	if( !pColorMap )
	{
		ASSERT( pColorMap );
		return;
	}

	m_clrOutLineColor = pColorMap->GetColor( nIndex );
}

BOOL CCSTMEdit::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	
	return CEdit::OnChildNotify(message, wParam, lParam, pLResult);
}

void CCSTMEdit::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CEdit::OnWindowPosChanged(lpwndpos);
}

