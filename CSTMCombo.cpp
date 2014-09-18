// CSTMCombo.cpp : implementation file
//

#include "stdafx.h"
#include "CSTMCombo.h"
//#include "..\..\Common\ControlBitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CColorMap*		GetColorMap();

#define COMBO_DOWN					"main/combo_p.bmp"		// Down
#define COMBO_UP					"main/combo_n.bmp"		// Normal

//extern CGdiManager*		GetGDIMng();
/////////////////////////////////////////////////////////////////////////////
// CCSTMCombo

CCSTMCombo::CCSTMCombo()
{
	m_Imageload			= new CImageEdit;
//	m_nBitMapX			= 13;				// 콤보버튼 비트맵 
//	m_nBitMapY			= 16;

//	m_pGDIMng			= NULL;

	m_clrTextColor	= ::GetSysColor( COLOR_WINDOWTEXT );
    m_clrBackColor	= ::GetSysColor( COLOR_WINDOW     );

    CreateBrushType();

	m_clr3DFace		= GetSysColor(COLOR_3DFACE);
	m_clr3DLight	= GetSysColor(COLOR_3DLIGHT);
	m_clr3DHilight	= GetSysColor(COLOR_3DHILIGHT);
	m_clr3DShadow	= GetSysColor(COLOR_3DSHADOW);
	m_clr3DDkShadow = GetSysColor(COLOR_3DDKSHADOW);
	m_clrOutLineColor	= RGB(109,127,149);

	m_bDrawFlat     = TRUE;
	m_bDrawOutline  = TRUE;

	m_hBitmap       = NULL;
	m_hBitmapSel    = NULL;
	
	m_bAutoTrim     = FALSE;

	Initialize();
}

CCSTMCombo::~CCSTMCombo()
{
	if(m_Imageload != NULL)
	{
		delete m_Imageload;
		m_Imageload = NULL;
	}
}


BEGIN_MESSAGE_MAP(CCSTMCombo, CComboBox)
	//{{AFX_MSG_MAP(CCSTMCombo)
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_CONTROL_REFLECT(CBN_SELENDCANCEL, OnSelEndCancel)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSTMCombo message handlers
void CCSTMCombo::DrawBorder(CDC* pDC)
{
	CRect rcItem;
	DWORD dwExStyle = GetExStyle();
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
	{
		colorBoard = m_clrBackColor;

		nBorderWidth  = m_bDrawOutline ? 1 : 2;
	}

	if (m_bDrawFlat == FALSE) 
	{
	
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

	for (int nLoop = 0; nLoop < nBorderWidth; nLoop++) 
	{
		pDC->Draw3dRect(rcItem, colorBoard, colorBoard);
		rcItem.DeflateRect(1, 1);
	}

	//Button Draw
	rcItem.left = rcItem.right - ::GetSystemMetrics( SM_CXHTHUMB );

	m_rcButton = rcItem;
	BOOL bDropped = GetDroppedState();
	DrawBitmap(pDC,m_rcButton,bDropped);
}


void CCSTMCombo::DrawBitmap(CDC* pDC,CRect rect,BOOL bPressed)
{
	BOOL bDCInit = FALSE;
	if(pDC == NULL)
	{
		pDC = GetDC();
		bDCInit = TRUE;
	}
	if(m_hBitmap == NULL)     // required
		return;
	ASSERT(m_hBitmap != NULL);     // required


	HBITMAP hBitmap = m_hBitmap;
	pDC->FillSolidRect(rect,RGB(255,255,255));
	
	if (bPressed && m_hBitmapSel != NULL)
		hBitmap = m_hBitmapSel;

	COLORREF crOldBack = pDC->SetBkColor(RGB(255,255,255));
	DrawTransParentBitmap(pDC, rect, hBitmap, RGB(255,0,255));
	pDC->SetBkColor(crOldBack);

	if(bDCInit)
	{
		ReleaseDC(pDC);
	}


}

//*******************************************************************/
/*! Function Name : DrawTransParentBitmap
/*! Function      : 비트멥 그리기
/*! Param         : CDC* pDC, CRect rect, HBITMAP hBitmap, long crTrans
/*! Return        : void 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
void CCSTMCombo::DrawTransParentBitmap(CDC* pDC, CRect rect, HBITMAP hBitmap, long crTrans)
{
	// Create two memory dcs for the image and the mask
	CDC dcImage, dcTrans;
	dcImage.CreateCompatibleDC(pDC);
	dcTrans.CreateCompatibleDC(pDC);
	// Select the image into the appropriate dc
	CBitmap* pOldBmp = (CBitmap*)dcImage.SelectObject(CBitmap::FromHandle(hBitmap));

	// Create the mask bitmap
	CBitmap bitmapTrans;
	// get the image dimensions
	BITMAP bm = {NULL};
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
	int nWidth	= bm.bmWidth;
	int nHeight = bm.bmHeight;
	bitmapTrans.CreateBitmap(nWidth, nHeight, 1, 1, NULL);

	// Select the mask bitmap into the appropriate dc
	CBitmap* pOldTransBmp = (CBitmap*)dcTrans.SelectObject(&bitmapTrans);

	// Build mask based on transparent colour
	dcImage.SetBkColor(crTrans);
	dcTrans.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCCOPY);

	// Do the work - True Mask method - cool if not actual display
//	pDC->BitBlt(xPos, yPos, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);
//	pDC->BitBlt(xPos, yPos, nWidth, nHeight, &dcTrans, 0, 0, SRCAND);
//	pDC->BitBlt(xPos, yPos, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);
	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dcImage,0,0,nWidth,nHeight,SRCCOPY);
//	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dcImage,0,0,nWidth,nHeight,SRCAND);
//	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dcImage,0,0,nWidth,nHeight,SRCINVERT);

	// Restore settings
	// don't delete this, since it is the bitmap
	dcImage.SelectObject(pOldBmp);
	dcTrans.SelectObject(pOldTransBmp);
	// delete bitmapTrans
	bitmapTrans.DeleteObject();
	// clean up
	dcImage.DeleteDC();
	dcTrans.DeleteDC();
////////////////////////////////////////////////////////////////////////////////////////////
}

//*******************************************************************/
/*! Function Name : SetBitmap
/*! Function      : 비트멥 설정
/*! Param         : HBITMAP hBitmap, HBITMAP hBitmapSel
/*! Return        : void 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
void CCSTMCombo::SetBitmap(HBITMAP hBitmap, HBITMAP hBitmapSel)
{
	m_hBitmap = hBitmap;
	m_hBitmapSel = hBitmapSel;
}



//*******************************************************************/
/*! Function Name : CtlColor
/*! Function      : 컨트롤 색상 변경.
/*! Param         : CDC* pDC, UINT nCtlColor
/*! Return        : HBRUSH 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
HBRUSH CCSTMCombo::CtlColor(CDC* pDC, UINT nCtlColor) 
{
    pDC->SetTextColor( m_clrTextColor );
    pDC->SetBkColor( m_clrBackColor );
    return (HBRUSH)m_brBkGround;
}

//*******************************************************************/
/*! Function Name : OnSysColorChange
/*! Function      : 시스템 컬러 변경 통지 처리.
/*! Param         : 
/*! Return        : void 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
void CCSTMCombo::OnSysColorChange() 
{
	CComboBox::OnSysColorChange();
	
	m_clr3DFace = GetSysColor(COLOR_3DFACE);
	m_clr3DLight = GetSysColor(COLOR_3DLIGHT);
	m_clr3DHilight = GetSysColor(COLOR_3DHILIGHT);
	m_clr3DShadow = GetSysColor(COLOR_3DSHADOW);
	m_clr3DDkShadow = GetSysColor(COLOR_3DDKSHADOW);
	
}

//*******************************************************************/
/*! Function Name : SetBackColor
/*! Function      : 배경색 적용
/*! Param         : COLORREF crColor
/*! Return        : COLORREF 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
COLORREF CCSTMCombo::SetBackColor( COLORREF crColor )
{
    _ASSERT(::IsWindow(m_hWnd)); 

    COLORREF crPrevBkColor = m_clrBackColor;

    m_clrBackColor = crColor;
    
    m_brBkGround.DeleteObject();

    CreateBrushType();

    Invalidate();

    return crPrevBkColor;
}


//*******************************************************************/
/*! Function Name : SetTextColor
/*! Function      : 글자색 적용
/*! Param         : COLORREF crColor
/*! Return        : COLORREF 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
COLORREF CCSTMCombo::SetTextColor( COLORREF crColor )
{
    _ASSERT(::IsWindow(m_hWnd)); 
    
    COLORREF crPrevTextColor = m_clrTextColor;
    m_clrTextColor = crColor;
    Invalidate();
    
    return crPrevTextColor;
}


//*******************************************************************/
/*! Function Name : CreateBrushType
/*! Function      : 배경색 적용을 위한 브러시 생성
/*! Param         : 
/*! Return        : BOOL 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
BOOL CCSTMCombo::CreateBrushType()
{
    return m_brBkGround.CreateSolidBrush(m_clrBackColor );
}

//*******************************************************************/
/*! Function Name : OnPaint
/*! Function      : WM_PAINT 통지 처리
/*! Param         : 
/*! Return        : void 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
void CCSTMCombo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	DefWindowProc( WM_PAINT, (WPARAM)dc.GetSafeHdc(), (LPARAM)0 );
	
	DrawBorder(&dc);
	
}
void CCSTMCombo::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
#if FALSE
	LPCTSTR lpszText = (LPCTSTR) lpDrawItemStruct->itemData;
	ASSERT(lpszText != NULL);
	CDC dc;
	dc.Attach( lpDrawItemStruct->hDC);
	if( m_bAutoTrim )
	{
		CString strText;
		strText.TrimLeft();
		strText.TrimRight();

		 dc.DrawText(
		  strText,
		  strlen(strText),
		  &lpDrawItemStruct->rcItem,
		  DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	}
#endif

}


//*******************************************************************/
/*! Function Name : PreSubclassWindow
/*! Function      : 윈도우 Subclassing 
/*! Param         : 
/*! Return        : void 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
void CCSTMCombo::PreSubclassWindow() 
{
	CComboBox::PreSubclassWindow();
}

//*******************************************************************/
/*! Function Name : OnCtlColor
/*! Function      : 컬러 처리
/*! Param         : CDC* pDC, CWnd* pWnd, UINT nCtlColor
/*! Return        : HBRUSH 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
HBRUSH CCSTMCombo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}



//*******************************************************************/
/*! Function Name : OnCreate
/*! Function      : ON_WM_CREATE  통지 처리
/*! Param         : LPCREATESTRUCT lpCreateStruct
/*! Return        : int 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
int CCSTMCombo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

//*******************************************************************/
/*! Function Name : OnSize
/*! Function      : ON_WM_SIZE 통지 처리
/*! Param         : UINT nType, int cx, int cy
/*! Return        : void 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
void CCSTMCombo::OnSize(UINT nType, int cx, int cy) 
{
	CComboBox::OnSize(nType, cx, cy);
	RelocateCtrl();
}

//*******************************************************************/
/*! Function Name : Initialize
/*! Function      : 콤보 버튼 초기화 처리.
/*! Param         : BOOL bImageBtn/*=TRUE*/
/*! Return        : void 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
void CCSTMCombo::Initialize(BOOL bImageBtn/*=TRUE*/)
{
	if( bImageBtn )	
	{
//		SetBitmap(  m_Imageload->GetControlStyleImage(  COMBO_UP ), m_Imageload->GetControlStyleImage(COMBO_DOWN) );
		SetBitmap(  m_Imageload->GetImageEx(   COMBO_UP , 0 ), m_Imageload->GetImageEx(COMBO_DOWN, 0 ) );
	}
	else			
	{
		SetBitmap(NULL, NULL);
	}

}

//*******************************************************************/
/*! Function Name : RelocateCtrl
/*! Function      : dropdown 스타일일경우 Edit 위치 이동 처리
/*! Param         : 
/*! Return        : void 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
void CCSTMCombo::RelocateCtrl()
{
	CWnd* pChidEdit = (CEdit*)GetDlgItem( 0x03E9 ); // Resource control first id
	if(pChidEdit && pChidEdit->GetSafeHwnd())
	{
		CRect rect;
		pChidEdit->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.top += 1;
		rect.bottom += 1;
		pChidEdit->MoveWindow(rect);
	
	}
}

//*******************************************************************/
/*! Function Name : WindowProc
/*! Function      : 
/*! Param         : UINT message, WPARAM wParam, LPARAM lParam
/*! Return        : LRESULT 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
LRESULT CCSTMCombo::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if( message == WM_COMMAND )
	{
		Invalidate();
	}

	return CComboBox::WindowProc(message, wParam, lParam);
}



//*******************************************************************/
/*! Function Name : PreTranslateMessage
/*! Function      : 
/*! Param         : MSG* pMsg
/*! Return        : BOOL 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
BOOL CCSTMCombo::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_COMMAND)
	{
		Invalidate();
	}
	return CComboBox::PreTranslateMessage(pMsg);
}

//*******************************************************************/
/*! Function Name : OnSelEndCancel
/*! Function      : 
/*! Param         : 
/*! Return        : void 
/*! Create        : 안경환 , 2005/07/29
/*! Comment       : 
//******************************************************************/
void CCSTMCombo::OnSelEndCancel() 
{
	Invalidate();
}
