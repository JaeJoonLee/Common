///////////////////////////////////////////////////////////////////////////////
// TreeNode.h
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
//  Author:		Jan

#ifdef WIN32

#ifndef __TREENODE_H__
#define __TREENODE_H__

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif

#include "..\StingrayExportDefs.h"

// The function names collide with macro names
// from windowsx.h
#undef GetNextSibling
#undef GetPrevSibling
#undef GetFirstChild
#undef GetFirstSibling
#undef GetLastSibling

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

class SECTreeNode 
{
  friend class SECTreeNodeX;

  private:	
	SECTreeNode *m_pParent;
	SECTreeNode *m_pNextSibling;
	SECTreeNode *m_pPrevSibling;
	SECTreeNode *m_pFirstChild;

  public:
	TOOLKIT_API void DeleteChildren(void);
	inline SECTreeNode() { m_pParent=m_pNextSibling=m_pPrevSibling=m_pFirstChild=NULL; }
	inline virtual ~SECTreeNode() { DeleteChildren(); }
	
	//Getting nodes
	inline virtual SECTreeNode *GetParent(void) const { return m_pParent;      }
	inline virtual SECTreeNode *GetNextSibling(void) const { return m_pNextSibling; }
	inline virtual SECTreeNode *GetPrevSibling(void) const { return m_pPrevSibling; }
	inline virtual SECTreeNode *GetFirstChild(void) const { return m_pFirstChild;  }

	TOOLKIT_API SECTreeNode *GetLastChild(void) const;
    TOOLKIT_API SECTreeNode *GetFirstSibling(void) const;
	TOOLKIT_API SECTreeNode *GetLastSibling(void) const;
	TOOLKIT_API SECTreeNode *GetBottomLeftChild(void) const;
	TOOLKIT_API SECTreeNode *GetBottomRightChild(void) const;
    TOOLKIT_API SECTreeNode *GetRoot(void) const;
	TOOLKIT_API SECTreeNode *GetAt(int nIndex) const;

	//setting nodes	// BW: Added for quicksort. 
	inline virtual void SetParent(SECTreeNode *pNode) { m_pParent = pNode; }
	inline virtual void SetNextSibling(SECTreeNode *pNode) { m_pNextSibling = pNode; }
	inline virtual void SetPrevSibling(SECTreeNode *pNode) { m_pPrevSibling = pNode; }
	inline virtual void SetFirstChild(SECTreeNode *pNode) { m_pFirstChild = pNode; }

	//search for a node
	TOOLKIT_API SECTreeNode *GetNextInDisplayOrder(void) const;
	TOOLKIT_API SECTreeNode *GetPrevInDisplayOrder(void) const;
	TOOLKIT_API SECTreeNode *Search( WORD idSearch ) const;
	TOOLKIT_API virtual BOOL OnNextSearchNode( WORD idSearch, SECTreeNode *pNode ) const;

	//setting nodes
	TOOLKIT_API BOOL AddChild( SECTreeNode *ptnNewChild, SECTreeNode *ptnInsertAfter);

	//major setting nodes
	TOOLKIT_API void DetachFromTree(void);
	TOOLKIT_API void DeleteAllChildren(void);

	//questions
	TOOLKIT_API BOOL HasChildren(void) const { return m_pFirstChild!=NULL; }
	TOOLKIT_API BOOL IsDescendant( SECTreeNode *pNode ) const;
    TOOLKIT_API BOOL IsAncestor( SECTreeNode *pNodePossibleAncestor ) const;
    TOOLKIT_API BOOL IsSibling(    SECTreeNode *pNode ) const;
	TOOLKIT_API WORD GetDistanceFromRoot(void) const;
	TOOLKIT_API virtual BOOL IsExpanded() const;
	TOOLKIT_API virtual void Expand(BOOL bExpand = TRUE);
	TOOLKIT_API void Collapse() { Expand(FALSE); };
	TOOLKIT_API void SwapPrev();

	TOOLKIT_API UINT GetNumDescendents(void) const;
	TOOLKIT_API UINT GetNumChildren(void) const;
};

#define TREENODE_FIRST     (SECTreeNode *)NULL
#define TREENODE_LAST      (SECTreeNode *)1
#define TREENODE_SORT      (SECTreeNode *)2

// Exportedt through base class. 
class SECTreeNodeX : public SECTreeNode
{
  private:
    WORD m_root_wFilterLevel; //only valid in root node

  public:  
    inline SECTreeNodeX() { m_root_wFilterLevel=0; }
    inline virtual ~SECTreeNodeX() { m_root_wFilterLevel=0; }
    
    TOOLKIT_API BOOL SetFilterLevel(WORD wLevel);
    TOOLKIT_API WORD GetFilterLevel(void) const;
    TOOLKIT_API WORD GetUnfilteredDistanceFromRoot(void) const;
   
    //override of SECTreeNode virtuals
    TOOLKIT_API SECTreeNode *GetParent(void) const;
    TOOLKIT_API SECTreeNode *GetNextSibling(void) const;
    TOOLKIT_API SECTreeNode *GetPrevSibling(void) const;
    TOOLKIT_API SECTreeNode *GetFirstChild(void) const;
};

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // __TREENODE_H__

#endif // WIN32
