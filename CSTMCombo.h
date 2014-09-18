//******************************************************************/
//******************************************************************/
// All Rights Reserved. Copyright(c)   2005 (주)한국소리마치        /
//******************************************************************/
/*! File Name     : CSTMCombo.h
/*! Function      :	
/*! System Name   : CodeDlg
/*! Create        : 안경환 , 2005/07/29
/*! Update        : 
/*! Comment       : 
//******************************************************************/
#if !defined(AFX_CSTMCOMBO_H__249FCF16_B739_444D_8867_C24568558793__INCLUDED_)
#define AFX_CSTMCOMBO_H__249FCF16_B739_444D_8867_C24568558793__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSTMCombo.h : header file
//

#include "..\controls\GDIMgr\ImageEdit.h"
#include "..\controls\GDIMgr\GdiManager.h"
#include "..\controls\GDIMgr\ColorMap.h"

/////////////////////////////////////////////////////////////////////////////
// CCSTMCombo window

class CCSTMCombo : public CComboBox 
{
// Construction
public:
	CCSTMCombo();

// Attributes
private:

protected:

public:

	BOOL		m_bDrawFlat;
	BOOL		m_bDrawOutline;

	CBrush		m_brBkGround;
    
	COLORREF	m_clrBackColor;
    COLORREF	m_clrTextColor;
	COLORREF	m_clrOutLineColor;

	COLORREF	m_clr3DHilight;
	COLORREF	m_clr3DLight;
	COLORREF	m_clr3DDkShadow;
	COLORREF	m_clr3DShadow;
	COLORREF	m_clr3DFace;


	CRect		m_rcButton;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hBitmapSel;


	CImageEdit*		m_Imageload;				// 버튼이미지
	int				m_nBitMapX;
	int				m_nBitMapY;
	CGdiManager*	m_pGDIMng;

	BOOL		    m_bAutoTrim;


// Operations
private:
	virtual BOOL CreateBrushType( );

public:
	void Initialize( BOOL bImageBtn = TRUE );
	void RelocateCtrl( );

	void DrawBitmap( CDC* pDC,CRect rect,BOOL bPressed );
	void DrawTransParentBitmap( CDC* pDC, CRect rect, HBITMAP hBitmap, long crTrans );
	void SetBitmap( HBITMAP hBitmap, HBITMAP hBitmapSel );


	//Color Operation
	COLORREF SetBackColor( COLORREF color );
    COLORREF SetTextColor( COLORREF	color );

    COLORREF GetBackColor()		const { return m_clrBackColor;   }   
    COLORREF GetTextColor()		const { return m_clrTextColor; }

	void	SetFlat(BOOL bFlag = TRUE)           {	m_bDrawFlat = bFlag;	    }
	void	SetOutlineColor(COLORREF color)	     { m_clrOutLineColor = color;	}
	void	SetDrawOutline(BOOL bFlag = TRUE)    { m_bDrawOutline = bFlag;		}
	void	SetAutoTrim( BOOL bTrim = FALSE )    { m_bAutoTrim = bTrim ;        }

protected:


public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSTMCombo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	virtual void DrawBorder(CDC* pDC);
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );

// Implementation
public:
	virtual ~CCSTMCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCSTMCombo)
	afx_msg void OnPaint();
	afx_msg void OnSysColorChange();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelEndCancel();
	//}}AFX_MSG
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTMCOMBO_H__249FCF16_B739_444D_8867_C24568558793__INCLUDED_)
