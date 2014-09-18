#if !defined(AFX_RESIZINGBMBUTTON_H__518122CF_358F_11D4_8F4F_00402656D980__INCLUDED_)
#define AFX_RESIZINGBMBUTTON_H__518122CF_358F_11D4_8F4F_00402656D980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//class CAutoFont;
//#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }

//////////////////////////////////////////////////
// CResizingBmButton - Window Blinds like button class
//
// Author: Shinya Miyamoto
// Email:  s-miya@ops.dti.ne.jp
// Copyright 2000, Shinya Miyamoto
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// This class implements a Window Blinds like button

class CResizingBmButton : public CButton
{

public:
	CResizingBmButton();

// Methods
public:
    // Bitmap Loding and Initialize
	// from resource
    bool LoadBitmaps
    ( 
         UINT id,          // ResourceID
         int count,        // Num Of Pics
         int TopHeight	 = 0,	// Top Merigin for Resizing
         int BottomHeight= 0,	// Bottom Merigin for Resizing
         int LeftWidth	 = 0,   // Left Merigin for Resizing
         int RightWidth	 = 0	// Right Merigin for Resizing
    );
	// from File 
	bool CResizingBmButton::LoadBitmapsFromFile
	(
		 CString strFileName,
         int TopHeight	 = 0,	// Top Merigin for Resizing
         int BottomHeight= 0,	// Bottom Merigin for Resizing
         int LeftWidth	 = 0,   // Left Merigin for Resizing
         int RightWidth	 = 0	// Right Merigin for Resizing
	);

    // Set Merigins
    void SetButtonDef( int TopHeight, int BottomHeight, int LeftWidth, int RightWidth );

protected:

    enum mode
    {
        normal  = 0,
        select  = 1,
        focus   = 2,
        disable = 3
    };

    enum state
    {
        notInited    = 0,
        FileLoaded   = 1,
        BitmapInited = 2
    };

    int m_State;

    // Bitmaps
    bool InitBitmap( CBitmap & src, CBitmap & dist, int index, int count);
    void DrawBitmap( CDC * pDC, int mode );

    UINT m_RcId;       // Resource ID
    int  m_NumofPics;  

    CBitmap NormalBitmap;
    CBitmap SelectBitmap;
    CBitmap FocusBitmap;
    CBitmap DisableBitmap;

    int m_TopHeight;
    int m_BottomHeight;
    int m_LeftWidth;
    int m_RightWidth;

    int m_dwWidth;
    int m_dwHeight;

// Transpararent BackColor
protected:
    COLORREF m_BkColor;
    COLORREF m_TextColor;
public:
    void	SetBackColor( COLORREF color ) { m_BkColor = color; }
    void	SetTextColor( COLORREF color ) { m_TextColor = color; }
    COLORREF GetBackColor() { return m_BkColor; }
    COLORREF GetTextColor() { return m_TextColor; }

	//{{AFX_VIRTUAL(CResizingBmButton)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

public:
	virtual ~CResizingBmButton();

	
protected:
	//{{AFX_MSG(CResizingBmButton)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#ifndef _MEMDC1_H_
#define _MEMDC1_H_

//////////////////////////////////////////////////
// CMemDC - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// This class implements a memory Device Context

class CMemDC1 : public CDC {
private:
	CBitmap*	m_bitmap;
	CBitmap*	m_oldBitmap;
	CDC*		m_pDC;
	CRect		m_rcBounds;
public:
	CMemDC1(CDC* pDC, const CRect& rcBounds) : CDC()
	{
		CreateCompatibleDC(pDC);
		m_bitmap = new CBitmap;
		m_bitmap->CreateCompatibleBitmap(pDC, rcBounds.Width(), rcBounds.Height());
		m_oldBitmap = SelectObject(m_bitmap);
		m_pDC	= pDC;
		m_rcBounds = rcBounds;
        //For some reason the background color is not correct,
        //so we use the button face color.
        DWORD	color = ::GetSysColor( COLOR_BTNFACE );
        CBrush bkg;
		bkg.CreateSolidBrush(color);
        FillRect(rcBounds, &bkg);
		bkg.DeleteObject();

	}
	~CMemDC1() 
	{
		m_pDC->BitBlt(m_rcBounds.left, m_rcBounds.top, m_rcBounds.Width(), m_rcBounds.Height(), 
					this, m_rcBounds.left, m_rcBounds.top, SRCCOPY);
		SelectObject(m_oldBitmap);
		if (m_bitmap != NULL) delete m_bitmap;
	}
	CMemDC1* operator->() {
		return this;
	}
};

#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++

#endif // !defined(AFX_RESIZINGBMBUTTON_H__518122CF_358F_11D4_8F4F_00402656D980__INCLUDED_)
