///////////////////////////////////////////////////////////////////////////////
// TrCtlX.h
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
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
// 
//  Authors:		Dean Hallman and Justin Rudd

#ifdef WIN32

#ifndef __TRCTLX_H__
#define __TRCTLX_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __SEC_TREEBASEC_H__
#include "trbaseC.h"
#endif

#include "..\StingrayExportDefs.h"

// QA: 32259
#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
	#include "VC6PlatDefs.h"
#endif

//
// SEC Extension DLL
// Initialize declaration context
//

#ifdef _SECDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SEC_DATAEXT
#endif //_SECDLL


///////////// SECTreeCtrl /////////////
/////////////////////////////
// AutoDuck tag block block for SECTreeCtrl 

// adinsert AutoDuck insertion point for SECTreeCtrl 
//@doc SECTreeCtrl 
//@class SECTreeCtrl | The Stingray enhanced tree control class. The implementation of this class is defined in the SEC_TREECLASS class.
//@base public | SEC_TREECLASS
//@xref <c SEC_TREECLASS> <c SEC_LISTCLASS>
class SECTreeCtrl : public SECTreeBaseC
{
	TOOLKIT_DECLARE_DYNAMIC( SECTreeCtrl )
public:
	//@access Construction/Initialization
	//@cmember
	/* Constructor*/
	TOOLKIT_API SECTreeCtrl();
	TOOLKIT_API virtual ~SECTreeCtrl();

protected:
	TOOLKIT_DECLARE_MESSAGE_MAP()

    // QA: 32574 removed OnNcPaint() from  QA: 31209 and replaced with OnNcPaint(HRGN).
	TOOLKIT_API LRESULT OnNcPaint(HRGN hrgnUpdate);
	TOOLKIT_API LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		TOOLKIT_API virtual LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam); // RWDN
	#endif

	HTHEME m_hTreeTheme;  // QA: 32574
};



////////////////////////////////////////
TOOLKIT_API void DDX_Control
	(
		CDataExchange* pdx,
		int idc,
		SECTreeCtrl& tree
	);

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TRCTLX_H__

#endif // WIN32

