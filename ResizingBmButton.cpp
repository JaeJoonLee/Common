// ResizingBmButton.cpp : 
//
//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (ÁÖ)ÇÑ±¹¼Ò¸®¸¶Ä¡        
//******************************************************************
//  File Name     : ResizingBmButton.cpp
//  Function      : 
//  System Name   : KHDialog
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/22 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : ºñ½ºÅ¸ UACÃ³¸®
//******************************************************************
#include "stdafx.h"
#include "ResizingBmButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizingBmButton
//******************************************************************
//  Function Name : CResizingBmButton
//  Function      : ÃÊ±â »ý¼ºÀÚ
//  Param         : ¾øÀ½
//  Return        : ¾øÀ½
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/22 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CResizingBmButton::CResizingBmButton()
{
    m_TopHeight	 = 8;
    m_BottomHeight = 8;
    m_LeftWidth = 8;
    m_RightWidth = 17;
    m_State = notInited;
    m_BkColor = RGB(255,0,255);
	m_TextColor   = RGB(0,0,0);

    m_RcId       = 0;       // Resource ID
    m_NumofPics  = 0;  
}
//******************************************************************
//  Function Name : ~CResizingBmButton
//  Function      : ¼Ò¸êÀÚ
//  Param         : ¾øÀ½
//  Return        : ¾øÀ½
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/22 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CResizingBmButton::~CResizingBmButton()
{
    NormalBitmap.DeleteObject();
    SelectBitmap.DeleteObject();
    FocusBitmap.DeleteObject();
    DisableBitmap.DeleteObject();
//    SAFE_DELETE(m_pFnt);
}


BEGIN_MESSAGE_MAP(CResizingBmButton, CButton)
	//{{AFX_MSG_MAP(CResizingBmButton)
    ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//******************************************************************
//  Function Name : DrawItem
//  Function      : 
//  Param         :	LPDRAWITEMSTRUCT lpDrawItemStruct
//  Return        :	void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/22 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CResizingBmButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    CDC xdc;
    xdc.Attach( lpDrawItemStruct->hDC );
    CRect rc;
    GetClientRect(rc);
    CMemDC1 dc(&xdc,rc);
    
    UINT state = lpDrawItemStruct->itemState ;
    bool IsDisable = false;

	if (state & ODS_FOCUS)
    {
		DrawBitmap( &dc, focus );
		if (state & ODS_SELECTED)
        { 
            DrawBitmap( &dc, select );
            rc.left += 5;
		}
	}
	else if (state & ODS_DISABLED)
    {
        IsDisable = true;
    	DrawBitmap( &dc, disable );

    }else{

        DrawBitmap( &dc, normal );
    }

    int imode = dc.SetBkMode(TRANSPARENT);

	CFont *pOldFnt = dc.SelectObject(GetFont());
    COLORREF oldColor;

    if(IsDisable)
      oldColor = dc.SetTextColor( GetSysColor(COLOR_GRAYTEXT) );
    else
      oldColor = dc.SetTextColor( m_TextColor );

    CString txt;
    GetWindowText(txt);
    dc.DrawText(txt,rc,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
      
    dc.SetTextColor( oldColor );
    dc.SelectObject(pOldFnt);
  
	dc.SetBkMode(imode );
	
}


//******************************************************************
//  Function Name : LoadBitmaps
//  Function      : 
//  Param         :	UINT id, int count , int TopHeight, int BottomHeight, int LeftWidth, int RightWidth
//  Return        :	bool 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/22 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
bool CResizingBmButton::LoadBitmaps
(
     UINT id, int count ,    
     int TopHeight, int BottomHeight, int LeftWidth, int RightWidth
)
{
    m_TopHeight = TopHeight;
    m_BottomHeight = BottomHeight;
    m_LeftWidth = LeftWidth;
    m_RightWidth = RightWidth;

    m_RcId       = id;       // Resource ID
    m_NumofPics  = count;  


    CBitmap bmp;
    if( !bmp.LoadBitmap(id) ) return false;

    if( !InitBitmap( bmp, NormalBitmap, 0, count ) ) return false;
    if( !InitBitmap( bmp, SelectBitmap, 1, count ) ) return false;
    if( !InitBitmap( bmp, DisableBitmap,2, count ) ) return false;
    if( !InitBitmap( bmp, FocusBitmap,  3, count ) ) return false;

    bmp.DeleteObject();

    return true;
}

//******************************************************************
//  Function Name : LoadBitmapsFromFile
//  Function      : 
//  Param         :	CString strFileName,  int TopHeight, int BottomHeight, int LeftWidth, int RightWidth
//  Return        :	bool 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/22 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
bool CResizingBmButton::LoadBitmapsFromFile
(
     CString strFileName,  int TopHeight, int BottomHeight, int LeftWidth, int RightWidth
)
{
    m_TopHeight = TopHeight;
    m_BottomHeight = BottomHeight;
    m_LeftWidth = LeftWidth;
    m_RightWidth = RightWidth;

    m_RcId       = 0;       // Resource ID
    m_NumofPics  = 1;  

    CBitmap* bmp;
	HBITMAP hBitmap;
	CString tmpFileName;

	tmpFileName = strFileName + "_f.bmp";
	HINSTANCE hInstance = AfxGetInstanceHandle();
	hBitmap = (HBITMAP)LoadImage(hInstance, tmpFileName, 
									IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE);
	bmp = CBitmap::FromHandle(hBitmap);
    if(!bmp) return FALSE;
    if( !InitBitmap( *bmp, FocusBitmap, 0, 1 ) ) return false;
	::DeleteObject((HBITMAP)hBitmap);

	// UP
	tmpFileName = strFileName + "_u.bmp";
	hBitmap = (HBITMAP)LoadImage(hInstance, tmpFileName, 
									IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE);
	bmp = CBitmap::FromHandle(hBitmap);
    if(!bmp) return FALSE;
    if( !InitBitmap( *bmp, NormalBitmap, 0, 1 ) ) return false;
	::DeleteObject((HBITMAP)hBitmap);

	// Down
	tmpFileName = strFileName + "_d.bmp";
	hBitmap = (HBITMAP)LoadImage(hInstance, tmpFileName, 
									IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE);
	bmp = CBitmap::FromHandle(hBitmap);
    if(!bmp) return FALSE;
    if( !InitBitmap( *bmp, SelectBitmap, 0, 1 ) ) return false;
	::DeleteObject((HBITMAP)hBitmap);

	// Disable
	tmpFileName = strFileName + "_x.bmp";
	hBitmap = (HBITMAP)LoadImage(hInstance, tmpFileName, 
									IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE);
	bmp = CBitmap::FromHandle(hBitmap);
    if(!bmp) return FALSE;
    if( !InitBitmap( *bmp, DisableBitmap, 0, 1 ) ) return false;
	::DeleteObject((HBITMAP)hBitmap);

    return true;
}

//******************************************************************
//  Function Name : InitBitmap
//  Function      : 
//  Param         :	CBitmap & src, CBitmap & dist, int index, int count 
//  Return        :	bool 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/22 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
bool CResizingBmButton::InitBitmap( CBitmap & src, CBitmap & dist, int index, int count )
{
    CDC * pDC = GetDC();

    CDC memDC; 
    memDC.CreateCompatibleDC(pDC);

    CDC srcDC;
    srcDC.CreateCompatibleDC(pDC);

    CBitmap* pOldBitmap1;
    pOldBitmap1 = srcDC.SelectObject(&src);

    BITMAP bmpinfo;
    src.GetBitmap(&bmpinfo);
    int bmpWidth = bmpinfo.bmWidth / count;
    int bmpHeight = bmpinfo.bmHeight;
    int orix = bmpWidth * index;

    CRect rc;
    GetClientRect(rc);

    CBitmap* pOldBitmap2;
    dist.DeleteObject();
    dist.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());
    pOldBitmap2 = memDC.SelectObject(&dist);

    // lefttop,leftbottom,righttop,rightbottom
    if( !memDC.BitBlt(0,0,m_LeftWidth, m_TopHeight, &srcDC,orix,0,SRCCOPY) ) return false;
    

    if( !memDC.BitBlt(0,rc.bottom - m_BottomHeight,m_LeftWidth, m_BottomHeight, 
                &srcDC,orix,bmpHeight - m_BottomHeight,SRCCOPY) ) return false;


    if( !memDC.BitBlt(rc.right - m_RightWidth, 0 ,m_RightWidth, m_TopHeight, 
                 &srcDC,orix + bmpWidth - m_RightWidth,0,SRCCOPY) ) return false;


    if( !memDC.BitBlt(rc.right - m_RightWidth,rc.bottom - m_BottomHeight,m_RightWidth,m_BottomHeight,
                 &srcDC,orix + bmpWidth - m_RightWidth,bmpHeight - m_BottomHeight,SRCCOPY) ) return false;

    // entireimage
    memDC.StretchBlt(m_LeftWidth,
                     m_TopHeight,
                     rc.Width()  - ( m_LeftWidth + m_RightWidth ) ,
                     rc.Height() -  ( m_TopHeight + m_BottomHeight) ,
                     &srcDC,
                     orix + m_LeftWidth,
                     m_TopHeight,
                     bmpWidth - ( m_LeftWidth + m_RightWidth ) ,
                     bmpHeight - ( m_TopHeight + m_BottomHeight ) ,SRCCOPY);

    
    // topbar,bottombar( Stretch )
    memDC.StretchBlt(m_LeftWidth,0, rc.Width() - (m_LeftWidth + m_RightWidth), m_TopHeight,
                     &srcDC,orix + m_LeftWidth, 0, bmpWidth - ( m_LeftWidth + m_RightWidth) , m_TopHeight,SRCCOPY);

    memDC.StretchBlt(m_LeftWidth, rc.bottom - m_BottomHeight, rc.Width() - ( m_LeftWidth + m_RightWidth), m_BottomHeight,
                     &srcDC,orix + m_LeftWidth,bmpHeight - m_BottomHeight,bmpWidth - ( m_LeftWidth + m_RightWidth) , m_BottomHeight,SRCCOPY );


    // sidebar ( STretch? )
    memDC.StretchBlt(0,m_TopHeight,m_LeftWidth,rc.bottom - m_TopHeight - m_BottomHeight ,
                     &srcDC, orix,m_TopHeight, m_LeftWidth, bmpHeight - ( m_TopHeight + m_BottomHeight ) ,SRCCOPY);

    memDC.StretchBlt(rc.right - m_RightWidth ,m_TopHeight,m_RightWidth,rc.bottom - m_TopHeight - m_BottomHeight ,
                     &srcDC, orix +  bmpWidth - m_RightWidth,m_TopHeight, m_RightWidth, bmpHeight - m_TopHeight - m_BottomHeight ,SRCCOPY);

    srcDC.SelectObject(pOldBitmap1);
    memDC.SelectObject(pOldBitmap2);

    ReleaseDC(pDC);
    ReleaseDC(&srcDC);
    ReleaseDC(&memDC);

     m_State = FileLoaded;
    
    return true;

}

//******************************************************************
//  Function Name : DrawBitmap
//  Function      : 
//  Param         :	CDC * pDC, int mode 
//  Return        :	void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/22 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CResizingBmButton::DrawBitmap( CDC * pDC, int mode )
{
    if( m_State < FileLoaded ) return;

    CRect rc;
    GetClientRect(rc);
 
	COLORREF crOldBack = pDC->SetBkColor(RGB(255,255,255));
	COLORREF crOldText = pDC->SetTextColor(RGB(0,0,0));

	CDC		dcImage, dcTrans;		
	// Create two memory dcs for the image and the mask
	dcImage.CreateCompatibleDC(pDC);
	dcTrans.CreateCompatibleDC(pDC);

	// Select the image into the appropriate dc
    CBitmap* pOldBitmapImage;
    BITMAP bmpinfo;
    switch(mode)
    {
		case normal:
		   pOldBitmapImage  = dcImage.SelectObject(&NormalBitmap);
		   NormalBitmap.GetBitmap(&bmpinfo);
		   break;
		case select:
		   pOldBitmapImage  = dcImage.SelectObject(&SelectBitmap);
		   SelectBitmap.GetBitmap(&bmpinfo);
		   break;
		case focus:
		   pOldBitmapImage  = dcImage.SelectObject(&FocusBitmap);
		   FocusBitmap.GetBitmap(&bmpinfo);
		   break;
		case disable:
		   pOldBitmapImage  = dcImage.SelectObject(&DisableBitmap);
		   DisableBitmap.GetBitmap(&bmpinfo);
		   break;
		default:
			return;
    }
    int bmpWidth = bmpinfo.bmWidth;
    int bmpHeight = bmpinfo.bmHeight;
      
	// Create the mask bitmap
	CBitmap bitmapTrans;
	int nWidth = rc.Width();
	int nHeight = rc.Height();

	// create transrate bitmap
	bitmapTrans.CreateBitmap(bmpWidth , bmpHeight, 1, 1, NULL);
	CBitmap* pBmBackupTrans	= (CBitmap*)dcTrans.SelectObject(&bitmapTrans);

	// Build mask based on transparent colour
	COLORREF crBack = dcImage.SetBkColor(m_BkColor);
	dcTrans.BitBlt(0, 0, bmpWidth, bmpHeight, &dcImage, 0, 0, SRCCOPY);

	// Do the work - True Mask method - cool if not actual display
    pDC->StretchBlt(0,0, nWidth, nHeight , &dcImage, 0, 0, bmpWidth, bmpHeight ,SRCINVERT);
    pDC->StretchBlt(0,0, nWidth, nHeight , &dcTrans, 0, 0, bmpWidth, bmpHeight ,SRCAND);
    pDC->StretchBlt(0,0, nWidth, nHeight , &dcImage, 0, 0, bmpWidth, bmpHeight ,SRCINVERT);
	
	// Restore settings
	dcImage.SelectObject(pOldBitmapImage);
	dcTrans.SelectObject(pBmBackupTrans);		
	pDC->SetBkColor(crOldBack);
	pDC->SetTextColor(crOldText);
}

//******************************************************************
//  Function Name : OnEraseBkgnd
//  Function      : 
//  Param         :	CDC* pDC
//  Return        :	BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/22 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CResizingBmButton::OnEraseBkgnd(CDC* pDC) 
{
    return FALSE;
}

//******************************************************************
//  Function Name : SetButtonDef
//  Function      : 
//  Param         :	int TopHeight, int BottomHeight, int LeftWidth, int RightWidth 
//  Return        :	void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/22 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CResizingBmButton::SetButtonDef( int TopHeight, int BottomHeight, int LeftWidth, int RightWidth )
{ 
    m_TopHeight = TopHeight;
    m_BottomHeight = BottomHeight;
    m_LeftWidth = LeftWidth;
    m_RightWidth = RightWidth;

    if( m_RcId != 0 && m_NumofPics != 0 )
    {
       LoadBitmaps(m_RcId,m_NumofPics,TopHeight,BottomHeight,LeftWidth,RightWidth);
    }

}
