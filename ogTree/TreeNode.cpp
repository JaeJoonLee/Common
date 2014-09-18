//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : TreeNode.cpp
//  Function      : 
//  System Name   : KSBuilder
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
///////////////////////////////////////////////////////////////////////////////
// TreeNode.cpp : Implementation of SECTreeNode Class
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


#define _OT_EXPORT_IMPL

#include "stdafx.h"

#ifdef WIN32

#ifdef _SECDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif //_SECDLL

#ifndef __TREENODE_H__
#include "TreeCtrl\toolkit\TreeNode.h"
#endif

#ifdef _SECDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif //_SECDLL


/////////////////////////////////////////////////////////////////////////////////
// SECTreeNode
/////////////////////////////////////////////////////////////////////////////////


//******************************************************************
//  Function Name : GetDistanceFromRoot
//  Function      : 
//  Param         : void
//  Return        : WORD 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
WORD SECTreeNode::GetDistanceFromRoot(void) const
{
	WORD w;
	SECTreeNode *pNode=this->GetParent();

	for( w=0 ; pNode ; w++)
		pNode = pNode->GetParent();

	return w;
}

////
//
// This is a question to ask SECTreeNode object!
//
//******************************************************************
//  Function Name : GetRoot
//  Function      : 
//  Param         : void
//  Return        : SECTreeNode *
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNode::GetRoot(void) const
{
	const SECTreeNode *pNode;

	for( pNode=this; pNode->m_pParent ; pNode=pNode->m_pParent )
		; //do nothing (like my weekends)

	return (SECTreeNode*)pNode;
}

////

//******************************************************************
//  Function Name : GetFirstSibling
//  Function      : 
//  Param         : 없음
//  Return        : SECTreeNode *
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNode::GetFirstSibling() const
{
	const SECTreeNode *pNode=this;

	while( TRUE )
	{
		if( !pNode->GetPrevSibling() )
			return (SECTreeNode*)pNode;

		pNode = pNode->GetPrevSibling();
	}

	ASSERT(FALSE);
	return NULL;

}

//******************************************************************
//  Function Name : GetLastSibling
//  Function      : 
//  Param         : 없음 
//  Return        : SECTreeNode *
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNode::GetLastSibling() const
{
	SECTreeNode *pNode = (SECTreeNode*)this;

	while (pNode->GetNextSibling())
		pNode = pNode->GetNextSibling();

	return pNode;
}

//******************************************************************
//  Function Name : GetLastChild
//  Function      : 
//  Param         : void
//  Return        : SECTreeNode *
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNode::GetLastChild(void) const
{
	SECTreeNode *pNode;
	pNode = GetFirstChild();
	if( !pNode )
		return NULL;
	
	return pNode->GetLastSibling();
}

//******************************************************************
//  Function Name : GetBottomLeftChild
//  Function      : 
//  Param         : void
//  Return        : SECTreeNode *
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNode::GetBottomLeftChild(void) const
{
	SECTreeNode *pNode = m_pFirstChild;

	if( pNode )
	{
		while( pNode->GetFirstChild() )
			pNode = pNode->GetFirstChild();
	}

	return pNode;
}

//******************************************************************
//  Function Name : GetBottomRightChild
//  Function      : 
//  Param         : void
//  Return        : SECTreeNode *
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNode::GetBottomRightChild(void) const
{
	SECTreeNode* pNode = GetLastChild();
	if (pNode)
		return pNode->GetBottomRightChild();
	else
		return (SECTreeNode*)this;
}

////

//******************************************************************
//  Function Name : DetachFromTree
//  Function      : 
//  Param         : void
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECTreeNode::DetachFromTree(void)
//
// private
//
{
	//ASSERT( !HasChildren() );

	if( m_pNextSibling )
		m_pNextSibling->m_pPrevSibling = m_pPrevSibling;

	if( m_pPrevSibling )
		m_pPrevSibling->m_pNextSibling = m_pNextSibling;

	if( m_pParent && m_pParent->m_pFirstChild==this )
		m_pParent->m_pFirstChild = m_pNextSibling;

	m_pParent = NULL;
}

////

//******************************************************************
//  Function Name : DeleteChildren
//  Function      : 
//  Param         : void
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECTreeNode::DeleteChildren(void)
{
	//TRACE( "DeleteChildren\n" );
	
	SECTreeNode *pBLC;
		
	while( 	(pBLC = GetBottomLeftChild()) != NULL )
	{
		pBLC->DetachFromTree();
		delete pBLC;
	}
}

////

//******************************************************************
//  Function Name : DeleteAllChildren
//  Function      : 
//  Param         : void
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECTreeNode::DeleteAllChildren(void)
{
	SECTreeNode *pChild;
	
	while( (pChild=GetFirstChild()) != NULL )
	{
		pChild->DetachFromTree();
		delete pChild;
	}
}

////

//******************************************************************
//  Function Name : AddChild
//  Function      : 
//  Param         : SECTreeNode *pNewTreeNode
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECTreeNode::AddChild(SECTreeNode *pNewTreeNode,
                         SECTreeNode *pInsAfter  )
{
	if( pInsAfter==TREENODE_SORT ) //24/05/96
	{
		TRACE( _T("Warning: haven't implemented TREENODE_SORT\n") );
		pInsAfter=TREENODE_LAST;
	}
	
	pNewTreeNode->m_pParent = this;

	if( !m_pFirstChild )
	{
		//node does not have any children
		ASSERT(    pInsAfter==TREENODE_FIRST 
		        || pInsAfter==TREENODE_LAST );

		m_pFirstChild = pNewTreeNode;
		pNewTreeNode->m_pNextSibling=NULL;
		pNewTreeNode->m_pPrevSibling=NULL;
	}
	else
	{
		//node has children
		SECTreeNode *pChild;

		if( pInsAfter==TREENODE_LAST )
		{
			//insert as last child
			pChild = m_pFirstChild; 
			while(  pChild->m_pNextSibling )
				pChild= pChild->m_pNextSibling;
			
			//now pChild is last child
			pChild->m_pNextSibling = pNewTreeNode;
			pNewTreeNode->m_pPrevSibling = pChild;
			pNewTreeNode->m_pNextSibling = NULL;
		}
		else if( pInsAfter==TREENODE_FIRST )
		{
			//insert as first child
			pNewTreeNode->m_pPrevSibling  = NULL;
			pNewTreeNode->m_pNextSibling  = m_pFirstChild;
			m_pFirstChild->m_pPrevSibling = pNewTreeNode;
			m_pFirstChild                 = pNewTreeNode;
		}
		else
		{
			//insert after a specified sibling
			BOOL bFound=FALSE;
			for( pChild = m_pFirstChild; 
			     pChild; 
				 pChild = pChild->m_pNextSibling )
			{
				if( pChild==pInsAfter )
				{
					bFound=TRUE;
					break;
				}
			}

			if( !bFound )
			{
				ASSERT(FALSE);
				return FALSE;
			}

			//put in pNewTreeNode
			pNewTreeNode->m_pNextSibling=pInsAfter->m_pNextSibling;
			pNewTreeNode->m_pPrevSibling=pInsAfter;
			//make a whole to file pNewTreeNode into
			if( pInsAfter->m_pNextSibling )
				pInsAfter->m_pNextSibling->m_pPrevSibling = pNewTreeNode;
			pInsAfter->m_pNextSibling = pNewTreeNode;
		}
	}

	return TRUE;
}

//******************************************************************
//  Function Name : GetAt
//  Function      : 
//  Param         : int nIndex 
//  Return        : SECTreeNode*
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode* SECTreeNode::GetAt(int nIndex) const
{
	SECTreeNode *pNode;
	int nCount;

	for (nCount = 0, pNode = GetFirstSibling();
		pNode && nCount < nIndex;
		pNode = pNode->GetNextSibling(), nCount++);

	return pNode;
}

//******************************************************************
//  Function Name : SwapPrev
//  Function      : 
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECTreeNode::SwapPrev()
{
	SECTreeNode *a, *b, *c, *d;

	// Initial order is  a, b, c, d
	// Order after swap  a, c, b, d
	d = GetNextSibling();
	c = this;
	b = c->GetPrevSibling();
	a = b->GetPrevSibling();

	if (a)
		a->m_pNextSibling = c;
	c->m_pPrevSibling = a;
	c->m_pNextSibling = b;
	b->m_pPrevSibling = c;
	b->m_pNextSibling = d;
	if (d)
		d->m_pPrevSibling = b;
	if (b == GetParent()->m_pFirstChild)
		GetParent()->m_pFirstChild = c;
}

////

//******************************************************************
//  Function Name : OnNextSearchNode
//  Function      : 
//  Param         : WORD idSearch, SECTreeNode *pNode
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECTreeNode::OnNextSearchNode( WORD idSearch, SECTreeNode *pNode ) const
//
// A serach func for subclass to over-ride
//
{ 
	idSearch; // UNUSED
	pNode; // UNUSED
	ASSERT(FALSE); 
	return FALSE;
}

//******************************************************************
//  Function Name : Search
//  Function      : 
//  Param         : WORD idSearch
//  Return        : SECTreeNode *
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNode::Search( WORD idSearch ) const
//
// This search is ordered in a specific manner :-
//   in order of bottom left most branch.
//
{
	SECTreeNode *pNode;
	BOOL       bFound;
	
	pNode=GetBottomLeftChild();

	while( pNode )
	{
		bFound=OnNextSearchNode( idSearch, pNode );
		if( bFound )
			return pNode;
	
		if( pNode->GetNextSibling() )
			pNode=pNode->GetNextSibling();
		else if( pNode->GetParent() && pNode->GetParent()!=this )
			pNode=pNode->GetParent();
		else
			break;
	}

	return NULL;
}

////

//******************************************************************
//  Function Name : GetNextInDisplayOrder
//  Function      : 
//  Param         : void 
//  Return        : SECTreeNode *
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNode::GetNextInDisplayOrder(void) const
{
	if( GetFirstChild() )
		return GetFirstChild();

	if( GetNextSibling() )
		return GetNextSibling();
	
	const SECTreeNode *pNodeAncestor=this;
	while( pNodeAncestor->GetParent() )
	{
		pNodeAncestor=pNodeAncestor->GetParent();
		if( pNodeAncestor->GetNextSibling() )
			return pNodeAncestor->GetNextSibling();
	}

	return NULL;
}

////

//******************************************************************
//  Function Name : GetPrevInDisplayOrder
//  Function      : 
//  Param         : void
//  Return        : SECTreeNode *
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNode::GetPrevInDisplayOrder(void) const
{
	if( GetPrevSibling() )
	{
		SECTreeNode *pBRC=GetPrevSibling()->GetBottomRightChild();
		if( pBRC )
			return pBRC;

		return GetPrevSibling();
	}

	return GetParent();
}

////

//******************************************************************
//  Function Name : IsDescendant
//  Function      : 
//  Param         : SECTreeNode *pNode
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECTreeNode::IsDescendant( SECTreeNode *pNode ) const
{
	if( !pNode	/*|| pNode==this*/ )
	{
		ASSERT(FALSE);
		return FALSE;
	}

	while( pNode->GetParent() )
	{
		pNode=pNode->GetParent();
		if( pNode == this )
			return TRUE;

		if( !AfxIsValidAddress(pNode,sizeof(*pNode) ) )
		{
			ASSERT(FALSE);
			return FALSE;
		}
	}

	return FALSE;
}

////

//******************************************************************
//  Function Name : IsAncestor
//  Function      : 
//  Param         : SECTreeNode *pNodePossibleAncestor
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECTreeNode::IsAncestor( SECTreeNode *pNodePossibleAncestor ) const
//
// kkep looking at parents of this and compare to arg
//
{
    const SECTreeNode *pNode=this;

	for( pNode=GetParent() ; pNode ; pNode=pNode->GetParent() )
	{
		if( pNode == pNodePossibleAncestor )
			return TRUE;
	}

	return FALSE;
}

////

//******************************************************************
//  Function Name : IsSibling
//  Function      : 
//  Param         : SECTreeNode *pNodeTest
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECTreeNode::IsSibling( SECTreeNode *pNodeTest ) const
{
    SECTreeNode *pNode;

    for( pNode=GetFirstSibling(); pNode ; pNode=pNode->GetNextSibling() )
    {
        if( pNodeTest==pNode )
        {
            return(TRUE);
        }
    } 

    return FALSE;
}

/////

//******************************************************************
//  Function Name : GetNumChildren
//  Function      : 
//  Param         : void
//  Return        : UINT 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
UINT SECTreeNode::GetNumChildren(void) const
{
	SECTreeNode *pNode;
	UINT iCount;

	for ( pNode=GetFirstChild(), iCount = 0	; 
	      pNode ; 
		  pNode = pNode->GetNextSibling(), iCount++ );

	return iCount;
}

//******************************************************************
//  Function Name : GetNumDescendents
//  Function      : 
//  Param         : void
//  Return        : UINT 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
UINT SECTreeNode::GetNumDescendents(void) const
//
// iterate and count all descendent nodes below this one
//
{
	UINT iCount=0;

	for ( SECTreeNode *pNode=GetFirstChild()	; 
	      pNode ; 
		  pNode = pNode->GetNextInDisplayOrder() )  // BUG?? GetNextInDisplayOrder??
	{
		iCount++;
	}

	return iCount;


}

//******************************************************************
//  Function Name : IsExpanded
//  Function      : 
//  Param         : 없음
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECTreeNode::IsExpanded() const
{
	return FALSE;
}

//******************************************************************
//  Function Name : Expand
//  Function      : 
//  Param         : BOOL bExpand
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void SECTreeNode::Expand(BOOL bExpand)
{
	bExpand; // UNUSED
}

/////////////////////////////////////////////////////////////////////////////////
// SECTreeNodeX
/////////////////////////////////////////////////////////////////////////////////

//******************************************************************
//  Function Name : GetUnfilteredDistanceFromRoot
//  Function      : 
//  Param         : void
//  Return        : WORD 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
WORD SECTreeNodeX::GetUnfilteredDistanceFromRoot(void) const
//
// private
//
{
	WORD w;
	SECTreeNode *pNode=this->m_pParent;

	for( w=0 ; pNode ; w++)
		pNode = pNode->m_pParent;

	return w;

}

////

//******************************************************************
//  Function Name : SetFilterLevel
//  Function      : 
//  Param         : WORD wFilterLevel
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL SECTreeNodeX::SetFilterLevel(WORD wFilterLevel)
{
    ((SECTreeNodeX *)GetRoot())->m_root_wFilterLevel=wFilterLevel;
    return TRUE;
}

////

//******************************************************************
//  Function Name : GetFilterLevel
//  Function      : 
//  Param         : void
//  Return        : WORD 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
WORD SECTreeNodeX::GetFilterLevel(void) const
{
    return ((SECTreeNodeX *)GetRoot())->m_root_wFilterLevel;
}

////

//******************************************************************
//  Function Name : GetParent
//  Function      : 
//  Param         : void
//  Return        : SECTreeNode *
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNodeX::GetParent(void) const
{
    if( GetFilterLevel()>0 && m_pParent )
    {
        if( GetUnfilteredDistanceFromRoot()==(GetFilterLevel()+1) )
        {
            return m_pParent->m_pParent;
        }
    }

    return m_pParent;
}

////

//******************************************************************
//  Function Name : GetFirstChild
//  Function      : 
//  Param         : void
//  Return        : SECTreeNode 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNodeX::GetFirstChild(void) const
{
    if( m_pFirstChild && GetFilterLevel()>0 )
    {
        if( GetUnfilteredDistanceFromRoot()==(GetFilterLevel()-1) )
        {
            return m_pFirstChild->m_pFirstChild;
        }
    }

    return m_pFirstChild;
}

////

//******************************************************************
//  Function Name : GetNextSibling
//  Function      : 
//  Param         : void
//  Return        : SECTreeNode 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNodeX::GetNextSibling(void) const
{
    if( GetFilterLevel()>0 )
    {
        if( GetUnfilteredDistanceFromRoot()==(GetFilterLevel()+1) )
        {
            if( !m_pNextSibling )
            {
                SECTreeNode *pNode = m_pParent;
                if( !pNode )
                    return NULL;
                
                pNode = pNode->m_pNextSibling;
                if( !pNode )
                    return NULL;

                pNode = pNode->m_pFirstChild;
                return pNode;
            }
        }
    }

    return m_pNextSibling;
}

////

//******************************************************************
//  Function Name : GetPrevSibling
//  Function      : 
//  Param         : void
//  Return        : SECTreeNode 
//  Create        : 
//  Update        : 김정문, 2009/10/09 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
SECTreeNode *SECTreeNodeX::GetPrevSibling(void) const
{
    if( GetFilterLevel()>0 )
    {
        if( GetUnfilteredDistanceFromRoot()==(GetFilterLevel()+1) )
        {
            if( !m_pPrevSibling )
            {
                SECTreeNode *pNode = m_pParent;
                if( !pNode )
                    return NULL;
                
                pNode = pNode->m_pPrevSibling;
                if( !pNode )
                    return NULL;

                pNode = pNode->m_pFirstChild;
                if( !pNode )
                    return NULL;

                while( pNode->m_pNextSibling )
                    pNode=pNode->m_pNextSibling;

                return pNode;
            }
        }
    }

    return m_pPrevSibling;
}

#endif // WIN32

/////////////////////////////////////////////////////////////////////////////////
// End of SECTreeNodeX
/////////////////////////////////////////////////////////////////////////////////
