//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : treeutil.cpp
//  Function      : 
//  System Name   : KSBuilder
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
///////////////////////////////////////////////////////////////////////////////
// treeutil.cpp
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
//  Author:	Brad King

#define _OT_EXPORT_IMPL

#include "stdafx.h"

#ifdef WIN32

#ifdef _SECDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif //_SECDLL

#ifndef __TREEUTIL_H__
#include "toolkit\treeutil.h"
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

//////////////////////////////////////////
// subitem text storage for SECTreeCore.
//******************************************************************
//  Function Name : SECSubItemTextStorage
//  Function      : 생성자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECSubItemTextStorage::SECSubItemTextStorage()
{
}

//******************************************************************
//  Function Name : ~SECSubItemTextStorage
//  Function      : 소멸자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECSubItemTextStorage::~SECSubItemTextStorage()
{
	POSITION pos = m_mapItems.GetStartPosition();
	CStringArray* pArray = 0;
	HTREEITEM hItem;
	while( pos )
	{
		m_mapItems.GetNextAssoc( pos, hItem, pArray );
		if ( pArray )
			delete pArray;
	}

}

//******************************************************************
//  Function Name : DeleteItem
//  Function      : 
//  Param         : HTREEITEM htiDelete
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECSubItemTextStorage::DeleteItem(HTREEITEM htiDelete)
{
	// remove the item from our map
	CStringArray* pArray = 0;
	if ( m_mapItems.Lookup( htiDelete, pArray ) )
	{
		if ( pArray )
			delete pArray;
		m_mapItems.RemoveKey( htiDelete );
	}

}

//******************************************************************
//  Function Name : GetString
//  Function      : 
//  Param         : HTREEITEM hItem,  int iSubItem, LPTSTR pszText, int cchTextMax ) 
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECSubItemTextStorage::GetString( HTREEITEM hItem,  int iSubItem, LPTSTR pszText, int cchTextMax ) const
{

	// the control is asking for the subitem text,
	// lookup the item
	CStringArray* pArray = 0;
	if ( m_mapItems.Lookup( hItem, pArray ) )
	{
		// found the string array, see if the requested element is there
		int nIndex = iSubItem - 1;
		if ( nIndex  < pArray->GetSize() )
		{
			// QA: 31989 - #if Secure Code Cleanup.
			strncpy( pszText, pArray->GetAt(nIndex), cchTextMax);
			return TRUE;
		}
	}
	// not initialized
	// QA: 31989 - #if Secure Code Cleanup.
	strncpy(pszText, _T(""), cchTextMax);
	return FALSE;
}

//******************************************************************
//  Function Name : AddOrModifyString
//  Function      : 
//  Param         : HTREEITEM hItem, int nSubItem, LPCTSTR lpszItem 
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECSubItemTextStorage::AddOrModifyString( HTREEITEM hItem, int nSubItem, LPCTSTR lpszItem )
{
	// lookup the handle to the item
	CStringArray* pArray = 0;
	if ( !m_mapItems.Lookup( hItem, pArray ) )
	{
		// doesn't exist, so add it
		pArray = new CStringArray;
		m_mapItems.SetAt( hItem, pArray);
	}
	

	if (!pArray )
		return FALSE;

	// add the string
#ifndef UNDER_CE
	try
	{
		pArray->SetAtGrow( nSubItem - 1, lpszItem );
	}
	catch( CMemoryException* e )
	{
		e->ReportError();
		e->Delete();
		if ( pArray )
			delete pArray;
		return FALSE;
	}
#else
	pArray->SetAtGrow( nSubItem - 1, lpszItem );
#endif
	return TRUE;
}


//******************************************************************
//  Function Name : ReorderItems
//  Function      : 
//  Param         : HTREEITEM hItem, int nSubItemOld, int nSubItemNew
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECSubItemTextStorage::ReorderItems( HTREEITEM hItem, int nSubItemOld, int nSubItemNew)
{
	CStringArray* pArray = NULL;
	m_mapItems.Lookup( hItem, pArray );

	if(!pArray)
	{
		TRACE( _T("Item does not have subitems associated with it\n") );
		return FALSE;
	}

        if(nSubItemOld - 1 < pArray->GetSize())
        {
                CString strText = pArray->GetAt( nSubItemOld-1 );
    	        pArray->RemoveAt(nSubItemOld-1);
    	        pArray->InsertAt( nSubItemNew-1, LPCTSTR(strText) );
        }
        else if(nSubItemNew - 1 < pArray->GetSize())
        {
                pArray->InsertAt(nSubItemNew - 1, LPCTSTR(NULL));
        }

	return TRUE;
}

//******************************************************************
//  Function Name : InsertItemAll
//  Function      : 
//  Param         : int nSubItemNew
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECSubItemTextStorage::InsertItemAll(int nSubItemNew)
{
	HTREEITEM		hti; 
	CStringArray*	pArray;

	POSITION pos = m_mapItems.GetStartPosition();
	while(pos)
	{
		m_mapItems.GetNextAssoc(pos, hti, pArray);
		if(pArray)
			pArray->InsertAt( nSubItemNew-1, LPCTSTR("") );	
	}
	return TRUE;
}

//******************************************************************
//  Function Name : ReorderItemAll
//  Function      : 
//  Param         : int nSubItemOld, int nSubItemNew
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECSubItemTextStorage::ReorderItemAll(int nSubItemOld, int nSubItemNew)
{
	HTREEITEM		hti; 
	CStringArray*	pArray;

	POSITION pos = m_mapItems.GetStartPosition();
	while(pos)
	{
		m_mapItems.GetNextAssoc(pos, hti, pArray);
		if(!pArray)
		{
			TRACE( _T("Item does not have subitems associated with it\n") );
			return FALSE;
		}

		CString strText = pArray->GetAt( nSubItemOld-1 );
		pArray->RemoveAt(nSubItemOld-1);
		pArray->InsertAt( nSubItemNew-1, LPCTSTR(strText) );	
	}
	return TRUE;
}


#endif // WIN32

