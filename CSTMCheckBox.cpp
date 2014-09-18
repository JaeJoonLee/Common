// STMCheckBox.cpp : implementation file
//

#include "stdafx.h"
#include "CSTMCheckBox.h"


extern CGdiManager* GetGDIMng();

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define DEF_FONT_IDX					2		//2:굴림체:9:N
#define DEF_FONT_IDX					14		//14:굴림체:9:B

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//
// Initialisation of static members

bool		CCSTMCheckBox::drawFocus = true;


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//
// CCSTMCheckBox construction/destruction

//-----------------------------------------------------------------------------
// Name:		CCSTMCheckBox
// Description:	Constructor
//
// Entry:		
//				int rcID		- resource ID with state bitmaps
//
//				int dimension	== width == height of a state bitmap
//-----------------------------------------------------------------------------
CCSTMCheckBox::CCSTMCheckBox ()
{	
	m_Imageload	= new CImageEdit;	
	BOX_SIZE	= 12;		// 이미지 한개 크기 BOX_SIZE( dimension )

	// load state bitmaps
	//
	_ASSERTE (m_bSrc != 0);	// * bitmap resource rcID valid ? * //
	
	m_bLeftText = false;
	m_bDisabled = false;
	m_bChecked  = false;
	m_nState    = BOX_OFF;

	inRect    = false;
	spaceDown = false;
	mouseDown = false;
	
	m_brush = NULL;

	hasFocus = false;

	prepare_bitmaps = true;

	for (int i = 0; i < 2; i++)
		m_bitmaps [i] = 0;

	m_nBackColor = RGB(237,241,244);		// 배경색

	m_bSrc = m_Imageload->GetImageEx("main/checkbox_onoff.bmp", 0);

	// 폰트 관련 
	m_nFontIndex	= 2;
	m_pGDIMng		= NULL;
	if(!m_pGDIMng)
		m_pGDIMng = GetGDIMng();
}
  
//-----------------------------------------------------------------------------
// Name:		~CCSTMCheckBox
// Description:	Destructor
//-----------------------------------------------------------------------------
CCSTMCheckBox::~CCSTMCheckBox()
{
	for (int i = 0; i < 2; i++) 
	{   
		if (m_bitmaps [i])
			DeleteObject (m_bitmaps [0]);
	}

	if(m_Imageload != NULL)
	{
		delete m_Imageload;
		m_Imageload = NULL;
	}

//	DeleteObject (m_font);
}


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//
// CCSTMCheckBox overrides

//-----------------------------------------------------------------------------
// Name:		PreSubclassWindow
// Description:	Makes some initialisations before the actuall 
//				subclassing occurs
//-----------------------------------------------------------------------------
void CCSTMCheckBox::PreSubclassWindow() 
{
	// text on left side?
	//
	unsigned style    = GetStyle   ();
	unsigned ex_style = GetExStyle ();

	if ((style	  & BS_LEFTTEXT)    || (style	  & BS_RIGHTBUTTON) || 
		(ex_style & WS_EX_RIGHT) )
		m_bLeftText = true;
	
	GetWindowText (m_text, 64);										// get text
//	m_font = (HFONT) GetParent()->SendMessage (WM_GETFONT, 0, 0);	// get font	

	
	if (!IsWindowEnabled ()) 
	{
		m_bDisabled = true;
		m_nState = BOX_DISABLED_2;
	}
	
	// prevent any drawing by the control itself
	//
	ModifyStyle (0,BS_OWNERDRAW,0);
		
	
	CButton::PreSubclassWindow();
}


//-----------------------------------------------------------------------------
// Name:		DrawItem
// Description:	We have to override this, because CButton::DrawItem
//				only executes an ASSERT
//-----------------------------------------------------------------------------
void CCSTMCheckBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{	
	return;	
}

//-----------------------------------------------------------------------------
// Name:		PreTranslateMessage
// Description:	WM_LBUTTONDBLCLK => WM_LBUTTONDOWN
//					- to ensure proper state repainting of the control
//					- to prevent BN_DBLCLK notifications to the parent 
//					  (BS_OWNERDRAW buttons send them, but CBs don't)
//-----------------------------------------------------------------------------
BOOL CCSTMCheckBox::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_LBUTTONDBLCLK)
		pMsg->message = WM_LBUTTONDOWN;
	
	return CButton::PreTranslateMessage(pMsg);
}



//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//
// CCSTMCheckBox message handlers

BEGIN_MESSAGE_MAP(CCSTMCheckBox, CButton)
	//{{AFX_MSG_MAP(CCSTMCheckBox)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()	
	//}}AFX_MSG_MAP	
	ON_MESSAGE (BM_GETCHECK, OnGetCheck)
	ON_MESSAGE (BM_SETCHECK, OnSetCheck)
END_MESSAGE_MAP()


//-----------------------------------------------------------------------------
// Name:		OnPaint
// Description:	Blits the prepared bitmaps to the screen
//-----------------------------------------------------------------------------
void CCSTMCheckBox::OnPaint() 
{
	DWORD clr1 = ::GetSysColor (COLOR_3DFACE);
//	if (m_clr != clr1)
	{			// sysColor changed ??				
		for (int i = 0; i < 2; i++)
		{	// => prepare bitmaps again
			if (m_bitmaps [i])
				DeleteObject (m_bitmaps [0]);
		}
		m_clr = clr1;

		if (m_brush) 
			DeleteObject (m_brush);
		m_brush = ::CreateSolidBrush (m_nBackColor);

		prepare_bitmaps = true;
	}


	if (hasFocus)
		DrawFocus (true);

	CPaintDC dc (this);

	if (prepare_bitmaps)
	{			// called first time or sysColor changed?
		PrepareBitmaps (dc.m_hDC);	// => prepare bitmaps
		prepare_bitmaps = false;
	}
	BlitToScreen (dc.m_hDC, m_nState);

	if (hasFocus)
		DrawFocus (true);
}


//-----------------------------------------------------------------------------
// Name:		OnEraseBkgnd
// Description:	Prevent any background erasing
//-----------------------------------------------------------------------------
BOOL CCSTMCheckBox::OnEraseBkgnd(CDC* pDC) 
{		
	return true;
}


//-----------------------------------------------------------------------------
// Name:		OnEnable
// Description:	Enable or disable CB
//-----------------------------------------------------------------------------
void CCSTMCheckBox::OnEnable(BOOL bEnable) 
{
	if (bEnable)
	{
		m_bDisabled = false;

		if (m_nState == BOX_DISABLED_1)
			SetState (BOX_ON);
		else
			SetState (BOX_OFF);			
	}
	else
	{
		m_bDisabled = true; 

		if (m_bChecked)
			SetState (BOX_DISABLED_1);
		else
			SetState (BOX_DISABLED_2);
	}

	CButton::OnEnable(bEnable);	
}


//-----------------------------------------------------------------------------
// Name:		OnKeyDown
//-----------------------------------------------------------------------------
void CCSTMCheckBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_SPACE && !spaceDown) 
	{

		spaceDown = true;

		if (!mouseDown)
		{		
			if (m_bChecked)
				SetState (BOX_LDOWN_1);
			else
				SetState (BOX_LDOWN_2);
		}
	}
	else if (nChar != VK_SPACE && spaceDown)
	{	// if any other key pressed
												// while space down
        spaceDown = false;			

		if (!mouseDown)
		{		
			if (m_bChecked)
				SetState (BOX_ON);
			else
				SetState (BOX_OFF);
		}			
	}	
	
	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}


//-----------------------------------------------------------------------------
// Name:		OnKeyUp
//-----------------------------------------------------------------------------
void CCSTMCheckBox::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_SPACE && spaceDown) 
	{
		spaceDown = false;

		if (!mouseDown) 
		{
			m_bChecked = (m_bChecked == true ? false : true);

			if (m_bChecked)
				SetState (BOX_ON);
			else
				SetState (BOX_OFF);				
		}			
	}
	
	CButton::OnKeyUp(nChar, nRepCnt, nFlags);
}


//-----------------------------------------------------------------------------
// Name:		OnLButtonDown
//-----------------------------------------------------------------------------
void CCSTMCheckBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	mouseDown = true;
	inRect = true;		

	if (m_bChecked)
		SetState (BOX_LDOWN_1);
	else
		SetState (BOX_LDOWN_2);

	CButton::OnLButtonDown(nFlags, point);  // also calls "SetCapture" & "SetFocus" 
}


//-----------------------------------------------------------------------------
// Name:		OnMouseMove
//-----------------------------------------------------------------------------
void CCSTMCheckBox::OnMouseMove(UINT nFlags, CPoint pt) 
{
	RECT rc;
	GetClientRect (&rc);

	if (mouseDown)
	{
		if (!PtInRect (&rc, pt)) 
		{			

			if (m_bChecked) 
				SetState (BOX_ON);
			else
				SetState (BOX_OFF);
			
			inRect = false;
		}
		else if (!inRect)  // again over control
		{
			inRect = true;

			if (m_bChecked)
				SetState (BOX_LDOWN_1);
			else
				SetState (BOX_LDOWN_2);
		}
	}
	
	CButton::OnMouseMove(nFlags, pt);
}


//-----------------------------------------------------------------------------
// Name:		OnLButtonUp
//-----------------------------------------------------------------------------
void CCSTMCheckBox::OnLButtonUp(UINT nFlags, CPoint pt) 
{
	mouseDown = false;

	RECT rc;
	GetClientRect (&rc);
					
	if (PtInRect (&rc, pt)) 
	{

		m_bChecked = (m_bChecked == true ? false : true);

		if (!spaceDown) 
		{
			if (m_bChecked)
				SetState (BOX_ON);
			else
				SetState (BOX_OFF);
		}
		else
		{
			if (m_bChecked)
				SetState (BOX_LDOWN_1);
			else
				SetState (BOX_LDOWN_2);				
		}
	}
	else if (spaceDown)  // mouse released outside of control, but "space" still pressed
	{
		if (m_bChecked)
			SetState (BOX_LDOWN_1);
		else
			SetState (BOX_LDOWN_2);
	}
										
	CButton::OnLButtonUp(nFlags, pt);	// also calls "ReleaseCapture"
}


//-----------------------------------------------------------------------------
// Name:		OnSetFocus
//-----------------------------------------------------------------------------
void CCSTMCheckBox::OnSetFocus(CWnd* pOldWnd) 
{	
	hasFocus = drawFocus;
	DrawFocus ();

	CButton::OnSetFocus(pOldWnd);
}


//-----------------------------------------------------------------------------
// Name:		OnKillFocus
//-----------------------------------------------------------------------------
void CCSTMCheckBox::OnKillFocus(CWnd* pNewWnd) 
{
	if (spaceDown)
	{				// mouse pressed in another window, 
		spaceDown = false;			// while spaceDown
		if (m_bChecked)
			SetState (BOX_ON);
		else
			SetState (BOX_OFF);
	}
	hasFocus = false;
	DrawFocus ();

	CButton::OnKillFocus(pNewWnd);
}


//-----------------------------------------------------------------------------
// Name:		OnGetCheck
// Description:	recieved BM_GETCHECK - either directly or through:
//						- CWnd::IsDlgButtonChecked or
//						- CButton::GetCheck wrapper
//-----------------------------------------------------------------------------
LRESULT CCSTMCheckBox::OnGetCheck(WPARAM wParam, LPARAM lParam)
{
	if (m_bChecked)
		return BST_CHECKED;
	else
		return BST_UNCHECKED;
}


//-----------------------------------------------------------------------------
// Name:		OnSetCheck
// Description:	recieved BM_SETCHECK - either directly or through 
//				CButton::SetCheck wrapper
//-----------------------------------------------------------------------------
LRESULT CCSTMCheckBox::OnSetCheck(WPARAM wParam, LPARAM lParam)
{	
	if (wParam == BST_CHECKED) 
	{
		m_bChecked = true;

		if (m_bDisabled)
		{              // the state of a disabled CB
			SetState (BOX_DISABLED_1);  // can also be changed
			return 0;
		}

		if (mouseDown)					// if mouse down => space doesn't matter
		{
			if (inRect)
				SetState (BOX_LDOWN_1);
			else
				SetState (BOX_ON);
		}
		else if (spaceDown)
			SetState (BOX_LDOWN_1);
		else
			SetState (BOX_ON);
	}
	else
	{
		m_bChecked = false;

		if (m_bDisabled) 
		{
			SetState (BOX_DISABLED_2);
			return 0;
		}

		if (mouseDown)
		{
			if (inRect)
				SetState (BOX_LDOWN_2);
			else
				SetState (BOX_OFF);
		}
		else if (spaceDown)
			SetState (BOX_LDOWN_2);
		else
			SetState (BOX_OFF);
	}

	return 0;
}



//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//
// CCSTMCheckBox drawing methods

//-----------------------------------------------------------------------------
// Name:		DrawFocus
// Description:	Draws a focus rectangle
//
// Entry:		
//				bool forceDraw - this parameter can be one of the following:
//					 false : draw focus rect only if "hasFocus" has changed
//					 true  : draw focus rect regardles of previous value 
//							 of "hasFocus" 
//
//					hasFocus - has the following meaning:
//					true  : check box has the keyboard focus at the moment
//					false : check box is not focused at the moment
//-----------------------------------------------------------------------------
void CCSTMCheckBox::DrawFocus (bool forceDraw)
{	
	if (!drawFocus)   // draw focus rectangle?
		return;

	static bool prev = false;
	if (prev != hasFocus || forceDraw) 
	{
		
		prev = hasFocus;

		CDC* pdc = GetDC ();		
		DrawFocusRect (pdc->m_hDC,&rcFocus);
		ReleaseDC (pdc);		
	}
}


//-----------------------------------------------------------------------------
// Name:		SetState
// Description:	Sets the new state and then blits the CB to the screen
//
// Entry:		
//				int nState - specifies the state of the CB and can be: 
//					BOX_ON			== checked state
//					BOX_OFF			== unchecked state
//					BOX_LDOWN_1		== mouse button down in checked state
//					BOX_LDOWN_2		== mouse button down in unchecked state
//					BOX_DISABLED_1	== CB disabled in checked state
//					BOX_DISABLED_2	== CB disabled in unchecked state		
//-----------------------------------------------------------------------------
void CCSTMCheckBox::SetState (int state)
{
	if (state != m_nState) 
	{
		m_nState = state;

		CDC* pdc = GetDC ();
		BlitToScreen(pdc->m_hDC,state);
		ReleaseDC (pdc);

		if (hasFocus)
			DrawFocus (true);
	}
}


//-----------------------------------------------------------------------------
// Name:		BlitToScreen
// Description:	Blits (=draw, copy,..) "m_bitmaps [nState]" to the screen
//
// Entry:		
//				HDC hdc - DC to blit to
//
//				int nState - specifies the state of the CB and can be:
//					BOX_ON
//					BOX_OFF
//					BOX_LDOWN_1
//					BOX_LDOWN_2
//					BOX_DISABLED_1
//					BOX_DISABLED_2
//-----------------------------------------------------------------------------
void CCSTMCheckBox::BlitToScreen (HDC hdc, int nState)
{
	HDC     destDC = ::CreateCompatibleDC (hdc);
	HBITMAP oDest;
	oDest = (HBITMAP) ::SelectObject (destDC,m_bitmaps [nState]);

	RECT rect;
	GetClientRect(&rect);

	int width  = rect.right  - rect.left;
	int height = rect.bottom - rect.top;

	if(height >= mHeight) {
		rect.top    += (height  - mHeight)/2;
		rect.bottom -= (height - mHeight)/2;
		height = rect.bottom - rect.top;
	}

	// Blit pre-prepared bitmap to screen
	//	
	BitBlt(hdc, rect.left, rect.top, width, height, destDC, 0, 0, SRCCOPY);
	

	// Clean up
	//	
	SelectObject(destDC, oDest);
	
	DeleteDC(destDC);	
}


//-----------------------------------------------------------------------------
// Name:		GetMinHeight
// Description:	Calculates minimal height of CB based on m_font
//
// Entry:		
//				HDC hdc - DC into which m_font is selected
//			
//-----------------------------------------------------------------------------
int CCSTMCheckBox::GetMinHeight (HDC hdc)
{
	CDC* pDC = CDC::FromHandle(hdc);
	CFont *pFont, *hOldFont;
	CSize	cs;
	if ( m_pGDIMng )
	{
		pFont = m_pGDIMng->GetFont( m_nFontIndex, 1 );
		hOldFont = pDC->SelectObject(pFont);
		cs = pDC->GetTextExtent("Dummy");
		pDC->SelectObject(hOldFont);
	}
	return cs.cy+1;

//	HFONT oFont = (HFONT) SelectObject (hdc, m_font);
//	SIZE sz;
//	GetTextExtentPoint32 (hdc, "Dummy", 5, &sz);
//	SelectObject (hdc,oFont);
//
//	return sz.cy+1;

}


//-----------------------------------------------------------------------------
// Name:		PrepareBitmaps & PrepareState
// Description:	This methods prepare "m_bitmaps[???]" for all posible states
//
// Entry:		
//				HDC     hdc - DC used to create memory DCs for bitmap preparation
//
//				HBITMAP &bDest - this parameter is one of the following:
//						m_bitmaps [0] : BOX_ON  bitmap
//						m_bitmaps [1] : BOX_OFF bitmap
//						...
//						m_bitmaps [5] : BOX_DISABLED_2 bitmap
//
//				int nState - specifies the state of the CB and can be:
//					BOX_ON
//					BOX_OFF
//					BOX_LDOWN_1
//					BOX_LDOWN_2
//					BOX_DISABLED_1
//					BOX_DISABLED_2
//-----------------------------------------------------------------------------
void CCSTMCheckBox::PrepareBitmaps (HDC hdc)
{
	mHeight = GetMinHeight (hdc);
	if (mHeight < BOX_SIZE)
		mHeight = BOX_SIZE;
	

	PrepareState (hdc, m_bitmaps [0], BOX_ON);
	PrepareState (hdc, m_bitmaps [1], BOX_OFF);
	PrepareState (hdc, m_bitmaps [2], BOX_LDOWN_1);
	PrepareState (hdc, m_bitmaps [3], BOX_LDOWN_2);
	PrepareState (hdc, m_bitmaps [4], BOX_DISABLED_1);
	PrepareState (hdc, m_bitmaps [5], BOX_DISABLED_2);
}

void CCSTMCheckBox::PrepareState (HDC hdc, HBITMAP & bDest, int nState)
{
	RECT rect;
	GetClientRect(&rect);

	int width  = rect.right  - rect.left;
	int height = rect.bottom - rect.top;

	if(height >= mHeight) {
		rect.top    += (height - mHeight)/2;
		rect.bottom -= (height - mHeight)/2;
		height = rect.bottom - rect.top;
	}
	int o = (mHeight - BOX_SIZE) / 2;

	//
	// Create memory DCs and bitmaps to prepare the image
	//
	HDC srcDC  = ::CreateCompatibleDC (hdc);
	HDC maskDC = ::CreateCompatibleDC (hdc);
	HDC destDC = ::CreateCompatibleDC (hdc);


	HBITMAP bMask = ::CreateBitmap (BOX_SIZE,BOX_SIZE,1,1,NULL);
			bDest = ::CreateCompatibleBitmap (hdc,width,mHeight);		  

	HBITMAP oSrc  = (HBITMAP) ::SelectObject (srcDC, m_bSrc);	
	HBITMAP oMask = (HBITMAP) ::SelectObject (maskDC,bMask);
	HBITMAP oDest = (HBITMAP) ::SelectObject (destDC,bDest);	
	

	// Create mask - mask color: RGB(255,0,255)
	//
	COLORREF color = SetBkColor(srcDC, RGB(255,0,255));	


	RECT rc;				// rect = drawing rectangle inside client area of CB
	rc.left	  = rc.top = 0;	// rc   = drawing rectangle inside destDC 
	rc.right  = width;		// right of rc = (width) of rect
	rc.bottom = height;     // bottom of rc = (height) of rect
	

	// copy the display surface where the CheckBox will be to destDC
	//
#if TRANSPARENT_CB
	BitBlt (destDC,0,0,width,height,hdc, rect.left, rect.top, SRCCOPY);
#else
	FillRect (destDC, &rc, m_brush);
#endif

	int l = 0;
	if (m_bLeftText) l = width - BOX_SIZE;		

	int x = BOX_SIZE*nState;  
	BitBlt(maskDC, 0, 0, BOX_SIZE, BOX_SIZE, srcDC, x, 0, SRCCOPY);
	BitBlt(destDC, l, o, BOX_SIZE, BOX_SIZE, srcDC, x, 0, SRCINVERT); 
	BitBlt(destDC, l, o, BOX_SIZE, BOX_SIZE,maskDC, 0, 0, SRCAND); 
	BitBlt(destDC, l, o, BOX_SIZE, BOX_SIZE, srcDC, x, 0, SRCINVERT);


	// Draw control text
	//
	DrawText_ (destDC, rc, nState);
	rcFocus.top    += rect.top;
	rcFocus.bottom += rect.top;
	rcFocus.left  -= 1;
	rcFocus.right += 1;
	
	// Clean up
	//
	SelectObject(srcDC,  oSrc);
	SelectObject(maskDC, oMask);
	SelectObject(destDC, oDest);
	
	DeleteDC(srcDC);
	DeleteDC(maskDC);
	DeleteDC(destDC);

	DeleteObject(bMask);
}


//-----------------------------------------------------------------------------
// Name:		DrawText_
// Description:	Draws text for the CB to destDC
//				(into which one of the "m_bitmaps [???]" is selected)
//
// Entry:		
//				HDC destDC - DC to which text is drawed
//							 ("m_bitmaps [???]" is selected into it)
//
//				RECT rc    - part of client area (of the CB) to which
//							 text is output
//			
//-----------------------------------------------------------------------------
void CCSTMCheckBox::DrawText_ (HDC destDC, RECT rc, int nState)
{	
	// akh 06-07-07 수정
	GetWindowText (m_text, 64);

	int oState = SaveDC (destDC);
	SetBkMode (destDC, TRANSPARENT);

	// 폰트 설정
//	SelectObject (destDC,m_font);
	CDC* pDC = CDC::FromHandle(destDC);
	CFont *pFont, *hOldFont;
	if ( m_pGDIMng )
	{
		pFont = m_pGDIMng->GetFont( m_nFontIndex, 1 );
		hOldFont = pDC->SelectObject(pFont);
	}


	unsigned style = 0;
	if (m_bLeftText) {
		rc.right -= BOX_SIZE+6;  style = DT_RIGHT;
	}
	else {
		rc.left  += BOX_SIZE+5;  style = DT_LEFT;
	}
	rc.bottom -= 1;				// rc   = drawing rectangle inside destDC  
	
	int nTextColor = RGB(21,62,116); 
	if (m_nFontIndex == 2)
		nTextColor = RGB(27,27,27);

	SetTextColor (destDC, nTextColor);
	
	if (nState == BOX_DISABLED_1 || nState == BOX_DISABLED_2) 
	{
//		SetTextColor (destDC, RGB(21,62,116)/*GetSysColor (COLOR_3DHILIGHT)*/);
//		rc.left  += 1;	rc.top   += 1;
//		rc.right += 1;	rc.bottom+= 1;
//		DrawText (destDC, m_text, -1, &rc, DT_SINGLELINE | DT_VCENTER | style);
			
		SetTextColor (destDC, GetSysColor (COLOR_3DSHADOW));
//		rc.left  -= 1;	rc.top   -= 1;
//		rc.right -= 1;	rc.bottom-= 1;
		DrawText (destDC, m_text, -1, &rc, DT_SINGLELINE | DT_VCENTER | style);
	}
	else
		DrawText (destDC, m_text, -1, &rc, DT_SINGLELINE | DT_VCENTER | style);
	
	// calculate rcFocus
	//
	int r_t = rc.right;				// right side of text rectangle

	DrawText (destDC, m_text, -1, &rc, DT_SINGLELINE | DT_VCENTER | style | DT_CALCRECT);

	if (m_bLeftText)
	{
		int d = rc.right - rc.left; // text width
		d = r_t - d;
		rc.left  += d; 
		rc.right += d;
	}
	rcFocus = rc;

	if ( m_pGDIMng )
		pDC->SelectObject(hOldFont);
	RestoreDC (destDC, oState);
}

//*******************************************************************/
/*! Function Name : SetBackColor
/*! Function      : 배경색 변경시 m_clr 값과 m_clr1 값이 같아 처리되지않는부분을 아래와 같이 수정한다.
/*! Param         : int nColor
/*! Return        : void 
/*! Modify        : 남궁중 , 2006/06/05
/*! Comment       : 
//******************************************************************/
void CCSTMCheckBox::SetBackColor(int nColor)			// 배경색 지정
{
	m_clr			= nColor;
	m_nBackColor	= nColor;
}

//*******************************************************************/
/*! Function Name : SetTextFontIndex
/*! Function      : 폰트의 크기를 결정한다.
/*! Param         : short nFontIndex (2:굴림체:9:N, 14:굴림체:9:B)
/*! Return        : void 
/*! Create        : 이용준 , 2006/06/05
/*! Comment       : 볼드체를 사용하려면 nFontIndex = 14를 셋트할것
//******************************************************************/
void CCSTMCheckBox::SetTextFontIndex( short nFontIndex)
{
	m_nFontIndex = nFontIndex;
}
