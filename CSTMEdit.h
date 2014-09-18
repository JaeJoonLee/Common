//******************************************************************/
//******************************************************************/
// All Rights Reserved. Copyright(c)   2005 (주)한국소리마치        /
//******************************************************************/
/*! File Name     : CSTMEdit.h
/*! Function      :	
/*! System Name   : CodeDlg
/*! Create        : 안경환 , 2005/07/29
/*! Update        : 
/*! Comment       : 
//******************************************************************/
#if !defined(AFX_CSTMEDIT_H__0FB44D23_94CB_4C8A_A668_704A1B8CC42D__INCLUDED_)
#define AFX_CSTMEDIT_H__0FB44D23_94CB_4C8A_A668_704A1B8CC42D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSTMEdit.h : header file
//

#include "..\Controls\GDIMgr\ImageEdit.h"
#include "..\Controls\GDIMgr\GdiManager.h"
#include "..\Controls\GDIMgr\ColorMap.h"

//#include "CodeDlgDef.h"

/////////////////////////////////////////////////////////////////////////////
// CCSTMEdit window
#define WM_NOTIFY_SEDIT_ON_CHAR	WM_USER + 301
class CCSTMEdit : public CEdit
{
// Construction
public:
	CCSTMEdit();
	DECLARE_DYNCREATE( CCSTMEdit )
private:
   CCSTMEdit( const CCSTMEdit& ); 

   // Attribute
protected:
	

private:
    UINT m_MenuResourceID;

public:
	BOOL		m_bDrawFlat;
	BOOL		m_bDrawOutline;
	BOOL		m_bReadOnly;

	CFont*		m_pfontText;



	CBrush		m_brBkGround;
    COLORREF	m_clrBackColor;
    COLORREF	m_clrTextColor;
	COLORREF	m_clrOutLineColor;
	COLORREF	m_clr3DHilight;
	COLORREF	m_clr3DLight;
	COLORREF	m_clr3DDkShadow;
	COLORREF	m_clr3DShadow;
	COLORREF	m_clr3DFace;


	short		m_nFontIndex;
	short		m_nBackCrIdx;
	short		m_nForeCrIdx;
	short		m_nBorderCrIdx;

	float		m_fXRate, 
				m_fYRate;
	
	CGdiManager*	m_pGDIMng;


	// Operation
private:

protected:
	virtual void DrawBorder();
	virtual BOOL CreateBrushType();

public:
	void SetPopupMenu( UINT uResourceID = 0 ) { m_MenuResourceID = uResourceID; }


public:
    void	SetFlat(BOOL bFlag = TRUE);
	void	SetOutlineColor( COLORREF color );
	void	SetOutlineColor( short nIndex );
	void	SetDrawOutline( BOOL bFlag = TRUE );
	
	//Font Operation
	BOOL SetFontRotation( int nAngle );
	BOOL SetFontBold(BOOL bBold = TRUE);
	BOOL SetFontItalic( BOOL bItalic = TRUE);
	BOOL SetFontHeight( int nHeight );
	BOOL SetFontFaceName( const CString& sFaceName );
	BOOL GetTextFont( LOGFONT* plgfnt);
	BOOL SetTextFont( LONG nHeight, BOOL bBold, BOOL bItalic, const CString& sFaceName );
	BOOL SetTextFont( const LOGFONT& lgfnt );


	//Color Operation
	COLORREF SetBackColor( COLORREF color );
	COLORREF SetBackColor( short nIndex );
	
    COLORREF SetTextColor(COLORREF	color);
	COLORREF SetTextColor( short nIndex );

    COLORREF GetBackColor()		const { return m_clrBackColor; }
    COLORREF GetTextColor()		const { return m_clrTextColor; }

	CString	GetText();
	void	SetText(CString szText);
	
	virtual BOOL SetReadOnly(BOOL bReadOnly = TRUE);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSTMEdit)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCSTMEdit();
	// Generated message map functions
protected:
	//{{AFX_MSG(CCSTMEdit)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysColorChange();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTMEDIT_H__0FB44D23_94CB_4C8A_A668_704A1B8CC42D__INCLUDED_)
