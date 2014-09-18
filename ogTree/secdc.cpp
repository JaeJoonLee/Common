//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : secdc.cpp
//  Function      : 
//  System Name   : KSBuilder
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
///////////////////////////////////////////////////////////////////////////////
// secdc.pp
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

#define _SFL_EXPORT_IMPL

#include "stdafx.h"

#ifdef _SFL_MFC_SUPPORT

#ifdef WIN32

#ifdef _SFLDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif //_SFLDLL

#include "Foundation\Graphics\MFC\secdc.h"

#ifdef _SFLDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif //_SFLDLL

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace stingray {
namespace foundation {

IMPLEMENT_DYNAMIC(SECMemDC, CDC)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//******************************************************************
//  Function Name : SECMemDC
//  Function      : 생성자
//  Param         : CDC& dcSrc, CRect rcSrc, BOOL bInit /*= TRUE*/, BOOL bUpdateCoords /*= TRUE*/ )
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECMemDC::SECMemDC( CDC& dcSrc, CRect rcSrc, BOOL bInit /*= TRUE*/, BOOL bUpdateCoords /*= TRUE*/ ) 
	: CDC(),
	  m_pSrcDC(&dcSrc), 
	  m_rcSrc(rcSrc),
	  m_bUpdateCoords(bUpdateCoords)
{
	if( m_pSrcDC == NULL ) 
		AfxThrowResourceException();

	if(bInit)
	{
		InitDC();
	}
}

//******************************************************************
//  Function Name : SECMemDC
//  Function      : 생성자
//  Param         : CDC* pdcSrc, CRect rcSrc, BOOL bInit /*= TRUE*/, BOOL bUpdateCoords /*= TRUE*/ 
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECMemDC::SECMemDC( CDC* pdcSrc, CRect rcSrc, BOOL bInit /*= TRUE*/, BOOL bUpdateCoords /*= TRUE*/ )
	: CDC(),
	  m_pSrcDC(pdcSrc),
	  m_rcSrc(rcSrc),
	  m_bUpdateCoords(bUpdateCoords)
{
	if( m_pSrcDC == NULL )
		AfxThrowResourceException();

	if(bInit)
	{
		InitDC();
	}
}

//******************************************************************
//  Function Name : ~SECMemDC
//  Function      : 소멸자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECMemDC::~SECMemDC()
{
	// QA: 32569
	if(m_bUpdateCoords)
	{
		SetViewportOrg(m_ptVp);
		SetWindowOrg(m_ptWnd);
		SetViewportExt(m_szVp);
		SetWindowExt(m_szWnd);
	}

	m_pSrcDC->BitBlt(m_rcSrc.left, m_rcSrc.top, m_rcSrc.Width(), m_rcSrc.Height(), this, m_rcSrc.left, m_rcSrc.top, SRCCOPY );
	this->SelectObject(m_pOldBitmap);
}

// 
//******************************************************************
//  Function Name : DoCreateCompatibleDC
//  Function      : QA: 32569
//  Param         : 없음
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECMemDC::DoCreateCompatibleDC()
{
	return this->CreateCompatibleDC(m_pSrcDC);
}

// 
//******************************************************************
//  Function Name : DoCreateCompatibleBitmap
//  Function      : QA: 32569
//  Param         : 없음
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECMemDC::DoCreateCompatibleBitmap()
{
	return m_bmp.CreateCompatibleBitmap(m_pSrcDC, m_rcSrc.Width(), m_rcSrc.Height());
}

// 
//******************************************************************
//  Function Name : DoSelectBitmap
//  Function      : QA: 32569
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECMemDC::DoSelectBitmap()
{
	m_pOldBitmap = (CBitmap*)this->SelectObject(&m_bmp);
}

//******************************************************************
//  Function Name : InitDC
//  Function      : 
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECMemDC::InitDC()
{
	ASSERT_VALID(m_pSrcDC);

	// QA: 32569
	if(m_bUpdateCoords)
	{
		m_ptVp = m_pSrcDC->GetViewportOrg();
		m_ptWnd = m_pSrcDC->GetWindowOrg();
		m_szVp = m_pSrcDC->GetViewportExt();
		m_szWnd = m_pSrcDC->GetWindowExt();
	}

	if(DoCreateCompatibleDC() == FALSE )
		AfxThrowResourceException();

	// QA: 32569
	if(!m_bUpdateCoords)
	{
		m_pSrcDC->LPtoDP(&m_rcSrc);
	}

	if( DoCreateCompatibleBitmap() == FALSE )
		AfxThrowResourceException();

	DoSelectBitmap();

	// QA: 32569
	if(m_bUpdateCoords)
	{
		SetViewportOrg(m_ptVp);
		SetWindowOrg(m_ptWnd);
		SetViewportExt(m_szVp);
		SetWindowExt(m_szWnd);
	}else
	{
		SetMapMode(m_pSrcDC->GetMapMode());
		SetWindowExt(m_pSrcDC->GetWindowExt());
		SetViewportExt(m_pSrcDC->GetViewportExt());
		m_pSrcDC->DPtoLP(&m_rcSrc);
		SetWindowOrg(m_rcSrc.left, m_rcSrc.top);
	}
}

};  // namespace stingray::foundation
};  // namespace stingray

#endif // WIN32

#endif  // ifdef _SFL_MFC_SUPPORT
