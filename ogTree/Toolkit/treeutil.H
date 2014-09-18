///////////////////////////////////////////////////////////////////////////////
// treeutil.h
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
//  Author: Brad King

#ifdef WIN32

#ifndef __TREEUTIL_H__
#define __TREEUTIL_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#include <StingrayExportDefs.h>

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


/////////////////////////////////////////////////////////////////
// subitem text mapping
struct _TREEITEM {};	// maps of HTREEITEMS won't work without this, 'cause it's not in the VC headers.

class SECSubItemTextStorage
{
public:
	TOOLKIT_API BOOL ReorderItemAll(int nSubItemOld, int nSubItemNew);
	TOOLKIT_API BOOL InsertItemAll(int nSubItemNew);
	typedef CMap<HTREEITEM, HTREEITEM&, CStringArray*, CStringArray*> mapSubItemText;

	TOOLKIT_API SECSubItemTextStorage();
	TOOLKIT_API virtual ~SECSubItemTextStorage();

	// operations
	TOOLKIT_API BOOL AddOrModifyString( HTREEITEM hItem, int nSubItem, LPCTSTR lpszItem );
	TOOLKIT_API BOOL GetString( HTREEITEM hItem,  int iSubItem, LPTSTR pszText, int cchTextMax ) const;
	TOOLKIT_API void DeleteItem( HTREEITEM hItem );
	TOOLKIT_API BOOL ReorderItems( HTREEITEM hItem, int nSubItemOld, int nSubItemNew);
protected:
	mapSubItemText m_mapItems;

};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TREEUTIL_H__

#endif // WIN32
