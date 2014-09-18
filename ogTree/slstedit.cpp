//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : slstedit.cpp
//  Function      : 
//  System Name   : KSBuilder
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
///////////////////////////////////////////////////////////////////////////////
// slstedit.cpp
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

#ifndef __SLSTCLNT_H__
#include "toolkit\slstclnt.h"
#endif

#ifndef __SLSTCTIP_H__
#include "toolkit\slstedit.h"
#endif


#ifdef _SECDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif //_SECDLL

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


////////////////////////////////////////////////////////////////////////////////
// SECListCtrlEdit implementation


//******************************************************************
//  Function Name : SECListEdit
//  Function      : 생성자
//  Param         : SECListClient* pLC ) : m_pLC(pLC
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECListEdit::SECListEdit( SECListClient* pLC ) : m_pLC(pLC)
{

}

BEGIN_MESSAGE_MAP( SECListEdit, CEdit )
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

//******************************************************************
//  Function Name : OnGetDlgCode
//  Function      : 
//  Param         : 없음
//  Return        : UINT 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
UINT SECListEdit::OnGetDlgCode()
{
	// Use this to allow VK_ESCAPE and VK_RETURN handlers
	return DLGC_WANTALLKEYS;
}


//******************************************************************
//  Function Name : OnKeyDown
//  Function      : 
//  Param         : UINT nChar, UINT nRepCnt, UINT nFlags
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECListEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	ASSERT_VALID(this);
	
	//ASSERT -> You must have a valid list control and it must have a non-null HWND
	ASSERT( m_pLC && m_pLC->GetHwnd() );

	if (nChar == VK_RETURN)
	{
		// If word wrap is enabled, operate as traditional MLE. 
		// If not, signal end of single-line edit.
		if(m_pLC->IsWordWrapEnabled())
		    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		else 
			m_pLC->ProcessAndDestroyEditLabel(TRUE);
	}
	else if (nChar == VK_ESCAPE)
	{
		m_pLC->ProcessAndDestroyEditLabel(FALSE);
	}
	else
	{
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

#endif //WIN32
