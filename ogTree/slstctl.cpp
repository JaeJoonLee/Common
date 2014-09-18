//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : slstctl.cpp
//  Function      : 
//  System Name   : KSBuilder
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
///////////////////////////////////////////////////////////////////////////////
// slstctl.cpp
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

#ifndef __SLSTCTL_H__
#include "TreeCtrl\toolkit\slstctl.h"
#endif

#ifdef _SECDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif //_SECDLL

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//@doc SECListCtrl
//@mfunc Constructs an SECListCtrl object.
//@comm see the SEC_LISTCLASS class for list control member functions.
//@xref <c SEC_LISTCLASS>
//******************************************************************
//  Function Name : SECListCtrl
//  Function      : 생성자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECListCtrl::SECListCtrl()
{

}

//******************************************************************
//  Function Name : ~SECListCtrl
//  Function      : 소멸자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECListCtrl::~SECListCtrl()
{

}

IMPLEMENT_DYNAMIC( SECListCtrl, CWnd )

BEGIN_MESSAGE_MAP( SECListCtrl, CWnd )
	CHAIN_LISTCORE_MESSAGES()
	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		ON_MESSAGE(WM_THEMECHANGED, OnThemeChanged)
	#endif
END_MESSAGE_MAP()

void DDX_Control
	(
		CDataExchange* pdx,
		int id,
		SECListCtrl& list
	)
{
	if( list.GetSafeHwnd() == NULL )
	{
		ASSERT(!pdx->m_bSaveAndValidate);

		if( list.AttachListCtrl( id, pdx->m_pDlgWnd ) == FALSE )
		{
			ASSERT(FALSE);
			pdx->Fail();
		}
	}
}

// QA: 32259
#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
//******************************************************************
//  Function Name : OnThemeChanged
//  Function      : 
//  Param         : WPARAM wParam, LPARAM lParam
//  Return        : LRESULT 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
LRESULT SECListCtrl::OnThemeChanged(WPARAM wParam, LPARAM lParam)
{
    // Add code to handle theme changes here...
    return 0;
}
#endif

#endif // WIN32
