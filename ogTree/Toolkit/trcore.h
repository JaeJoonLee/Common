///////////////////////////////////////////////////////////////////////////////
// trcore.h
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

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif
#include <afxtempl.h>
#ifndef __CMNSTRT_H__
#include "treectrl\toolkit\cmnstrt.h"
#endif

#ifndef __TREENODE_H__
#include "treectrl\toolkit\TreeNode.h"
#endif

#include "..\StingrayExportDefs.h"

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


// Extended Styles Defined By SECTreeCtrl
#define TVXS_MULTISEL				0x00100000
#define TVXS_WORDWRAP				0x00200000
#define TVXS_COLUMNHEADER		0x00400000
#define TVXS_FLYBYTOOLTIPS	0x00800000
#define TVXS_ANIMATE				0x01000000
#define TVXS_AUTOEXPAND			0x02000000
#define TVXS_SORTHEADER			0x04000000
#define TVXS_HEADERDRAGDROP	0x08000000	

// Extra GetNextItem Codes
#define TVGN_FIRSTSELECTED		0x0020
#define TVGN_NEXTSELECTED			0x0021
#define TVGN_PREVIOUSSELECTED	0x0022
#define TVGV_FIRSTSELECTED		TVGN_FIRSTSELECTED
#define TVGV_NEXTSELECTED			TVGN_NEXTSELECTED
#define TVGV_PREVIOUSSELECTED	TVGN_PREVIOUSSELECTED

// HitTest Codes
#define TVHT_COLUMNSEP				0x1000
#define TVHT_COLUMNHEADING		0x2000
#define TVHT_INSIDEITEMBOUNDS	0x4000

// Extra Mask Flags
#define TVIF_EX_STATEEX				0x0001

// Extra State Flags
#define TVIS_EX_DISABLED			0x0100
#define TVIS_EX_HIDDEN				0x0200

#define TVI_SORT_DESCENDING   ((HTREEITEM)(SEC_ULONG)0xFFFF0010)

// this style is only defined for commmon controls 4.71 and higher.
// so we'll define it if needed
#ifndef TVS_SINGLEEXPAND
#define TVS_SINGLEEXPAND      0x0400
#endif

#define TVS_STYLES (TVS_HASLINES		|\
									 TVS_LINESATROOT	|\
									 TVS_HASBUTTONS		|\
									 TVS_EDITLABELS		|\
									 TVS_SHOWSELALWAYS	|\
									 TVS_DISABLEDRAGDROP |\
									 TVS_SINGLEEXPAND)

#define TVXS_STYLES	(TVXS_MULTISEL		|\
									 TVXS_WORDWRAP		|\
									 TVXS_COLUMNHEADER	|\
									 TVXS_FLYBYTOOLTIPS |\
									 TVXS_ANIMATE		|\
									 TVXS_AUTOEXPAND)

// macro to retrieve the state image index for an item
#define GET_STATE_IMAGE(state) (((state) & TVIS_STATEIMAGEMASK)>>12)
// macro to retrieve the overlay image index for an item
#define GET_OVERLAY_IMAGE(state) (((state) & TVIS_OVERLAYMASK)>>8)

// Registered message sent by NotifyEndLabelEditChangeComplete
// To receive in your app, you must call 
// RegisterWindowMessage(SEC_TREECTRL_NOTIFYENDLABELEDITCHG_REGMSG) 
// to fetch the appropriate unique message id.
#define SEC_TREECTRL_NOTIFYENDLABELEDITCHG_REGMSG _T("SECTreeCtrlNotifyEndLabelEditRegMsg")

/////////////////////////////
// AutoDuck tag block block for SEC_TREECLASS 
//@doc SEC_TREECLASS
//@mfunc virtual BOOL  | SEC_TREECLASS | IsStoringSubItemText | This will return TRUE if the tree control is storing subitem text,
// instead of using the LV_GETDISPINFO callback. The default is FALSE.

//@doc SEC_TREECLASS
//@mfunc inline BOOL  | SEC_TREECLASS | InvalidateItem | Invalidates the rectangle of the specified item.
//@parm HTREEITEM  | hti | The item to invalidate.

//@doc SEC_TREECLASS
//@mfunc void  | SEC_TREECLASS | SetAutoExpandDelay | sets the hover time required to auto expand a drop target. Must have TVXS_AUTOEXPAND.
//@parm  UINT | nDelay | the hover time in milliseconds

//@doc SEC_TREECLASS
//@mfunc void  | SEC_TREECLASS | SetMaxAnimations | sets the maximum numbret of animations when expanding or collapsing, for TVXS_ANIMATE style
//@parm  int | nMaxAnimations | the maximum number of times to redraw the control


// adinsert AutoDuck insertion point for SEC_TREECLASS
//@doc SEC_TREECLASS 
//@class SEC_TREECLASS | SEC_TREECLASS is the base class for SECTreeCtrl and SECTreeView. All tree functionality
// is implemented in this class ( include\trcore.inl ), and SEC_LISTCLASS ( include\slstcore.inl ).
//@xref <c SEC_LISTCLASS>

// Forward declarations
class SECSubItemTextStorage;

class SEC_TREECLASS : public SEC_TREEBASE
{
public:
	//BEGIN List Core typedefs
	//These should not have to be here, but for some reason the compiler is not
	//   bringing down the public typedefs for SECListCtrl ( really a SECListCore<CWnd> )
	//   so when compiler technology catches up...these will be removed...
	typedef SECListItem			Item;
	typedef SECListSubItem	SubItem;
	typedef SECListColumn		Column;
	typedef SECListDrawAction	DrawAction;
	typedef SECListSelectAction	SelectAction;
	typedef SECListPaintContext	LvPaintContext;
	
	//END List Core typedefs

	typedef SECTreePaintContext	TvPaintContext;
	typedef _Node				Node;

public:
	//@access Construction/Initialization
	//@cmember
	/* Construction*/
	TOOLKIT_API SEC_TREECLASS();

	TOOLKIT_API virtual ~SEC_TREECLASS();

	// Creation Members

	//@access Operations
	//@cmember
	/* retrieve the active Column*/
	inline int GetActiveColumn() {return m_nActiveColumn;};
	//@cmember
	/* Create an SECTreeCtrl*/
	TOOLKIT_API virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//@cmember
	/* Create an SECTreeCtrl*/
	TOOLKIT_API virtual BOOL Create(DWORD dwStyle, DWORD dwStyleEx, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	//Create a SECTreeCtrl on a dialog template. Call this func
	//from OnInitDialog and pass the IDC of MS's tree-ctrl from
	//create in dialog editor.

	//@cmember
	/* Create a SECTreeCtrl on a dialog template. */
	TOOLKIT_API BOOL SubclassTreeCtrlId( UINT idc, CWnd *pWndDlg );

	// Position/Dimension Accessors
	//@cmember
	/* Retrieves the bounding rectangle for an item and determines whether it is visible or not.*/
	TOOLKIT_API BOOL GetItemRect( HTREEITEM hti, LPRECT lpRect, UINT nCode ) const;
	//@cmember
	/* Retrieves the amount, in pixels, that child items are indented relative to their parents.*/
	TOOLKIT_API UINT GetIndent() const;
	//@cmember
	/* Sets the width of indentation for a tree view control and redraws the control to reflect the new width.*/
	TOOLKIT_API void SetIndent(UINT nIndent);
	//@cmember
	/* Sets the height of a single tree item */
	TOOLKIT_API UINT SetItemHeight(HTREEITEM hti, UINT cyItemHeight) const;
	//@cmember
	/* Retrieves the next tree view item.*/
	TOOLKIT_API HTREEITEM GetNextItem(HTREEITEM hItem, UINT nCode) const;
	//@cmember
	/* Retrieves the tree view item that is the child of the item specified.*/
	TOOLKIT_API HTREEITEM GetChildItem(HTREEITEM hItem) const;
	//@cmember
	/* Retrieves the next sibling of the item specified.*/
	TOOLKIT_API HTREEITEM GetNextSiblingItem(HTREEITEM hItem) const;
	//@cmember
	/* Retrieves the previous sibling of the item specified.*/
	TOOLKIT_API HTREEITEM GetPrevSiblingItem(HTREEITEM hItem) const;
	//@cmember
	/* Retrieves the parent of the item specified.*/
	TOOLKIT_API HTREEITEM GetParentItem(HTREEITEM hItem) const;
	//@cmember
	/* Retrieves the first visible item of the tree view control.*/
	TOOLKIT_API HTREEITEM GetFirstVisibleItem() const;
	//@cmember
	/* Retrieves the last visible item of the tree view control.*/
    TOOLKIT_API HTREEITEM GetLastVisibleItem() const;
	//@cmember
	/* Retrieves the next visible item of the item specified.*/
	TOOLKIT_API HTREEITEM GetNextVisibleItem(HTREEITEM hItem) const;
	//@cmember
	/* Retrieves the previous visible item of the item specified.*/
	TOOLKIT_API HTREEITEM GetPrevVisibleItem(HTREEITEM hItem) const;
	//@cmember
	/* Retrieves the first item currently selected in the tree view control.*/
	TOOLKIT_API HTREEITEM GetFirstSelectedItem() const;
	//@cmember
	/* Retrieves the next item currently selected in the tree view control.*/
	TOOLKIT_API HTREEITEM GetNextSelectedItem(HTREEITEM hItem) const;
	//@cmember
	/* Retrieves the previously selected item in the tree view control.*/
	TOOLKIT_API HTREEITEM GetPrevSelectedItem(HTREEITEM hItem) const;
	//@cmember
	/* Retrieves the item that currently has the caret (i.e., keyboard focus).*/
	TOOLKIT_API HTREEITEM GetCaretItem() const;
	//@cmember
	/* Retrieves a currently selected item of the tree view control.*/
	TOOLKIT_API HTREEITEM GetSelectedItem() const;
	//@cmember
	/* Retrieves the item that is the target of a drag-and-drop operation.*/
	TOOLKIT_API HTREEITEM GetDropHilightItem() const;
	//@cmember
	/* Retrieves the root item of the tree view control.*/
	TOOLKIT_API HTREEITEM GetRootItem(HTREEITEM hti = NULL) const;
	//@cmember
	/* Gets the next displayed item.*/
	TOOLKIT_API HTREEITEM GetNextItemInDisplayOrder(HTREEITEM hti) const;
	//@cmember
	/* Gets the previous displayed item.*/
	TOOLKIT_API HTREEITEM GetPrevItemInDisplayOrder(HTREEITEM hti) const;

	//@cmember
	/* Sets the attributes of the specified item.*/
	TOOLKIT_API virtual BOOL SetItem(const LV_ITEM* pLVI, BOOL bRedraw = TRUE);
	//@cmember
	/* Sets the attributes of the specified item.*/
	TOOLKIT_API BOOL SetItem(TV_ITEM* pItem);
	//@cmember
	/* Sets the attributes of the specified item.*/
	TOOLKIT_API BOOL SetItem(HTREEITEM hItem, UINT nMask, LPCTSTR lpszItem, int nImage, int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam);
	//@cmember
	/* Sets the extended attributes of the specified item.*/
	TOOLKIT_API virtual BOOL SetItemEx(TV_ITEM* pTVI, TV_ITEM_EX* pTVIX);
	//@cmember
	/* Sets the extended attributes of the specified item.*/
	TOOLKIT_API virtual BOOL SetItemEx(LV_ITEM* pLVI, const LV_ITEM_EX* pLVIX);
	//@cmember
	/* Sets the index of the item’s image and its selected image within the tree view control’s image list.*/
	TOOLKIT_API BOOL SetItemImage(HTREEITEM hItem, int nImage, int nSelectedImage);
	//@cmember
	/* Sets the state of the item specified.*/
	TOOLKIT_API BOOL SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask);
	//@cmember
	/* Sets the 32-bit application-specific value associated with the item specified.*/
	TOOLKIT_API BOOL SetItemData(HTREEITEM hItem, SEC_DWORD dwData);

	//kim	
	//virtual void	 SetItemColor(HTREEITEM hti, COLORREF clr);
	//virtual COLORREF GetItemColor(HTREEITEM hti );
	//virtual void	 ClearDspInfo ( );
	//virtual HTREEITEM GetTreeItem(LV_ITEM* lvi); 

	//@cmember
	/* Retrieves the attributes of the specified item.*/
	TOOLKIT_API virtual BOOL GetItem(TV_ITEM* pItem, BOOL bCopyText = TRUE, BOOL bGetDispInfo = FALSE) const;
	//@cmember
	/* Retrieves the attributes of the specified item.*/
	TOOLKIT_API virtual BOOL GetItem(LV_ITEM* pLVI, BOOL bCopyText = TRUE, BOOL bGetDispInfo = FALSE) const;
	//@cmember
	/* Retrieves the extended attributes of the specified item.*/
	TOOLKIT_API virtual BOOL GetItemEx(TV_ITEM* pTVI, TV_ITEM_EX* pTVIX, BOOL bGetDispInfoEx = FALSE) const;
	//@cmember
	/* Retrieves the extended attributes of the specified item.*/
	TOOLKIT_API virtual BOOL GetItemEx(LV_ITEM* pLVI, LV_ITEM_EX* pLVIX, BOOL bGetDispInfoEx = FALSE) const;

	//Used by SECListTip for displaying tooltip for items with TVIS_BOLD
	TOOLKIT_API virtual UINT GetStateFromItemIndex(int nItem, UINT nStateMask) const;

	//@cmember
	/* Retrieves the index of the item’s image and its selected image within the tree view control’s image list.*/
	TOOLKIT_API BOOL GetItemImage(HTREEITEM hItem, int& nImage, int& nSelectedImage) const;

	//@cmember
	/* Returns the state of the item specified.*/
	TOOLKIT_API UINT GetItemState(HTREEITEM hItem, UINT nStateMask) const;
	//@cmember
	/* Gets the 32-bit application-specific value associated with the item specified.*/
	TOOLKIT_API SEC_DWORD GetItemData(HTREEITEM hItem) const;

	//@cmember
	/* Gets the stored pointer to a Node from an HTREEITEM.*/
	TOOLKIT_API Node* GetNode( HTREEITEM hti ) const;
	//@cmember
	/* Gets the stored pointer to a node from a list Item pointer.*/
	TOOLKIT_API Node* GetNode( Item* pItem ) const;
	//@cmember
	/* Gets the stored pointer of a node based on an item index.*/
	TOOLKIT_API Node* GetNodeAt( int nIndex ) const;
	//@cmember
	/* Changes the parent of an existing node.*/
	TOOLKIT_API BOOL SetNodeParent( SECTreeNode *pNode, SECTreeNode *pNodeParent, BOOL bInvalidate=TRUE, HTREEITEM hInsertAfter=TVI_LAST );
	TOOLKIT_API BOOL SetNodeParent( HTREEITEM hti, HTREEITEM htiNewParent, BOOL bInvalidate=TRUE, HTREEITEM hInsertAfter=TVI_LAST );

	//@cmember
	/* Gets an HTREEITEM based on a list index.*/
	TOOLKIT_API HTREEITEM GetItemAt(int nIndex) const;
    
	//@cmember
	/* Returns the list index of an HTREEITEM.*/
	TOOLKIT_API int  ItemIndex(HTREEITEM, int nStartFrom = 0) const;
	//@cmember
	/* Returns the list index of a Node.*/
    TOOLKIT_API int  NodeIndex(Node *, int nStartFrom = 0) const;
	
	//@cmember
	/* Determines whether a given item is expanded (i.e., displaying the list of child items, if any, associated with it).*/
	TOOLKIT_API BOOL IsExpanded(HTREEITEM hItem) const;
	//@cmember
	/* Determines whether specified item uses text or image callbacks.*/
	TOOLKIT_API virtual BOOL IsCallbackItem(int nIndex) const;

	//@cmember
	/* Enables or disables sub-item text storage for multi-column trees.*/
	TOOLKIT_API virtual void StoreSubItemText( BOOL bEnable = TRUE );
	//@cmember
	/* Returns the state of sub-item text storage.*/
	inline virtual BOOL IsStoringSubItemText() const { return m_pSubItemTextStorage != NULL; }

	// Text accessors
	// WARNING: Be sure to read the comments associated with these
	//   functions in the implementation file.  These functions have
	//   a somewhat different purpose than you're probably assuming.

	//@cmember
	/* Returns the text of the specified item or sub-item.*/
	TOOLKIT_API CString GetItemText(HTREEITEM hItem, int iSubItem = 0) const;
	//@cmember
	/* Sets the text of the specified item.*/
	TOOLKIT_API virtual BOOL SetItemText(HTREEITEM hItem, LPCTSTR lpszItem);
	//@cmember
	/* Sets the text of the specified item or sub-item.*/
	TOOLKIT_API virtual BOOL SetItemText(HTREEITEM hItem, int nSubItem, LPCTSTR lpszItem);
	//@cmember
	/* Sets the text of the specified item or sub-item.*/
	TOOLKIT_API BOOL SetItemString(HTREEITEM hti, int nSubItem, const CString& strItem);
	//@cmember
	/* Returns the text of the specified item or sub-item.*/
	TOOLKIT_API BOOL GetItemString(HTREEITEM hti, int nSubItem, CString& strItem);

	//@cmember
	/* Insert a group of items under a common parent*/
	TOOLKIT_API BOOL InsertBatch(TV_ITEM** ppItems, HTREEITEM hParent, int cItems, BOOL bInvalidate=TRUE);

	//@cmember
	/* Inserts a new item in a tree view control.*/
	TOOLKIT_API HTREEITEM InsertItem(LPTV_INSERTSTRUCT lpInsertStruct);
	//@cmember
	/* Inserts a new item in a tree view control.*/
	TOOLKIT_API HTREEITEM InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter);
	//@cmember
	/* Inserts a new item in a tree view control.*/
	TOOLKIT_API HTREEITEM InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	//@cmember
	/* Inserts a new item in a tree view control.*/
	TOOLKIT_API HTREEITEM InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);

	//@cmember
	/* Deletes an item from the tree view control.*/
	TOOLKIT_API BOOL DeleteItem(HTREEITEM hItem);
	//@cmember
	/* Deletes all items from the tree view control.*/
	TOOLKIT_API BOOL DeleteAllItems();

	//@cmember
	/* Expands or collapses the list of child items, if any, associated with the given parent item.*/
	TOOLKIT_API virtual BOOL Expand(HTREEITEM hItem, UINT nCode, BOOL bRedraw = TRUE, BOOL bForceExpand = FALSE);
	//@cmember
	/* Recursively expands an item and all of its children.*/
	TOOLKIT_API void ExpandCompletely(HTREEITEM hItem, BOOL bRedraw = TRUE);
	//@cmember
	/* Recursively collapse an item and all of its children */
	TOOLKIT_API void CollapseCompletely(HTREEITEM hItem, BOOL bRedraw = TRUE);
	//@cmember
	/* Selects the given tree view item, scrolls the item into view, or redraws the item in the style used to indicate the target of a drag-and-drop operation.*/
	TOOLKIT_API BOOL Select(HTREEITEM hItem, UINT nCode);
	//@cmember
	/* Selects the given tree view item.*/
	TOOLKIT_API BOOL SelectItem(HTREEITEM hItem);
	//@cmember
	/* Redraws the item in the style used to indicate the target of a drag-and-drop operation.*/
	TOOLKIT_API BOOL SelectDropTarget(HTREEITEM hItem, BOOL bAutoScroll=TRUE);
	//@cmember
	/* Scrolls the tree view vertically so that the given item is the first visible item and gives it the focus and selection.*/
	TOOLKIT_API BOOL SelectSetFirstVisible(HTREEITEM hItem);
	//@cmember
	/* Determines whether a given item is set as the first visible item in the tree view control.*/
	TOOLKIT_API BOOL SetFirstVisible(HTREEITEM hti);

	//@cmember
	/* Determines the location of the specified point relative to the client area of a tree view control.*/
	TOOLKIT_API HTREEITEM HitTest(CPoint pt, UINT* pFlags = NULL);
	//@cmember
	/* Determines the location of the specified point relative to the client area of a tree view control.*/
	TOOLKIT_API HTREEITEM HitTest(TV_HITTESTINFO* pHitTestInfo);

	//@cmember
	/* Creates a dragging bitmap for the given item in a tree view control, creates an image list for the bitmap, and adds the bitmap to the image list.  An application uses the image-list functions to display the image when an item is being dragged.*/
	TOOLKIT_API CImageList* CreateDragImage(HTREEITEM hItem);

	//@cmember
	/* Extends CreateDragImage to create multiple selection images */
	TOOLKIT_API CImageList* CreateDragImageEx(HTREEITEM hItem, CPoint& ptOffset);

	//@cmember
	/* Ensures that a tree view item is visible.  If necessary, expands the parent item or scrolls the tree view control so that the item is visible.*/
	TOOLKIT_API BOOL EnsureVisible(HTREEITEM hItem, BOOL bParentVisible = FALSE);

	//@cmember
	/* Compares the text of two items.*/
	TOOLKIT_API virtual int CompareItem(Node *pNode1, Node *pNode2);
	//@cmember
	/* Sorts the child items of the given parent item in a tree view control.*/
	TOOLKIT_API BOOL SortChildren(HTREEITEM hItem, BOOL bRecursive = TRUE, BOOL bAscending = TRUE);
	//@cmember
	/* Sorts tree view items using an application-defined callback function that compares the items.*/
	TOOLKIT_API BOOL SortChildrenCB(LPTV_SORTCB pSort, BOOL bRecursive = TRUE, BOOL bAscending = TRUE);

	//@cmember
	/* Begins in-place editing of the specified item’s text.*/
	TOOLKIT_API CEdit* EditLabel(HTREEITEM hItem, int nCol = 0);

	//@cmember
	/* Returns the number of children an item has.*/
	TOOLKIT_API UINT GetChildCount(HTREEITEM hti, BOOL bRecursive = TRUE, BOOL bExpandedOnly = FALSE);


	//@cmember
	/* Selects all child nodes visible beneath a parent node.*/
	TOOLKIT_API BOOL SelectAllVisibleChildren(HTREEITEM hti);
	//@cmember
	/* Selects/deselects a range of items.*/
	TOOLKIT_API BOOL SelectItemRange( HTREEITEM htiFirst, HTREEITEM htiLast, BOOL bSelect);
	//@cmember
	/* Indicates whether an item is selected.*/
	TOOLKIT_API BOOL IsSelected(HTREEITEM hti) const;

	//@cmember
	/* Hides/Shows an item.*/
	TOOLKIT_API BOOL      HideItem( HTREEITEM hti, BOOL bHide );
	//@cmember
	/* Indicates whether or not an item is hidden.*/
	TOOLKIT_API BOOL      IsHidden( HTREEITEM hti ) const;
	//@cmember
	/* Gets first hidden item.*/
	TOOLKIT_API HTREEITEM GetFirstHiddenItem(void) const;
	//@cmember
	/* Gets next hidden item.*/
	TOOLKIT_API HTREEITEM GetNextHiddenItem(HTREEITEM) const;
	//@cmember
	/* Makes all hidden items visible.*/
	TOOLKIT_API BOOL      UnHideAllItems(void);

	//@cmember
	/* Disables all items (shown in disabled text color), or enables disabled items.*/
	TOOLKIT_API BOOL      DisableAllItems( BOOL bDisable );
	//@cmember
	/* Disables/enables a particular item.*/
	TOOLKIT_API BOOL      DisableItem( HTREEITEM hti, BOOL bDisable );
	//@cmember
	/* Indicates whether or not an item is disabled.*/
	TOOLKIT_API BOOL      IsDisabled( HTREEITEM ) const;
	//@cmember
	/* Gets first disabled item.*/
	TOOLKIT_API HTREEITEM GetFirstDisabledItem(void) const;
	//@cmember
	/* Gets next disabled item.*/
	TOOLKIT_API HTREEITEM GetNextDisabledItem(HTREEITEM) const;
	//@cmember
	/* Hides items that are disabled.*/
	TOOLKIT_API void	  HideDisabledItems(BOOL bHide);
	//@cmember
	/* Indicates whether or not disabled items are hidden.*/
	TOOLKIT_API BOOL      IsHideDisabledItems(void) const;

	//@cmember
	/* Retrieves a count of the items in a tree view control.*/
	TOOLKIT_API UINT GetCount() const;
	//@cmember
	/* Determines whether the tree item specified has child items on demand.*/
	TOOLKIT_API BOOL ItemHasChildrenOnDemand(HTREEITEM hItem) const;
	//@cmember
	/* Determines whether the tree item specified has child items.*/
	TOOLKIT_API BOOL ItemHasChildren(HTREEITEM hItem) const;
	//@cmember
	/* Indicates whether or not an item exists in the tree view control.*/
	TOOLKIT_API BOOL ItemExists(HTREEITEM hti) const;
	//@cmember
	/* Enables/disables scrolling after an item is expanded, to make the last child visible.*/
	TOOLKIT_API void EnableScrollOnExpand(BOOL bEnable=TRUE);
	//@cmember
	/* Returns a pointer to the requested image list.*/
	TOOLKIT_API virtual CImageList* GetImageList(UINT nImageList) const;
	//@cmember
	/* Sets the normal or state image list.*/
	TOOLKIT_API virtual CImageList* SetImageList(CImageList* pImageList, int nImageListType);

	//@cmember
	/* Enables/disables the column header control.*/
	TOOLKIT_API virtual void EnableHeaderCtrl(BOOL bEnable = TRUE, BOOL bSortHeader = FALSE);

	//@cmember
	/* Enables/disables wrapping of item text.*/
	TOOLKIT_API virtual void EnableWordWrap(BOOL bEnable = TRUE);
	//@cmember
	/* Enables/disables tooltips.*/
	TOOLKIT_API virtual void EnableToolTips(BOOL bEnable = TRUE);
	//@cmember
	/* Enables/disables multiple selection.*/
	TOOLKIT_API virtual void EnableMultiSelect(BOOL bEnable = TRUE);
	//@cmember
	/* Retrieves values for the style and extended style of a tree view control.*/
	TOOLKIT_API virtual BOOL GetTreeCtrlStyles(DWORD& dwStyle, DWORD& dwStyleEx) const;
	//@cmember
	/* Sets values for the style and extended style of a tree view control.*/
	TOOLKIT_API virtual BOOL SetTreeCtrlStyles(DWORD dwStyle, DWORD dwStyleEx, BOOL bRedraw = TRUE);
	//@cmember
	/* Retrieves the style of a tree view control.*/
	TOOLKIT_API virtual DWORD GetTreeCtrlStyle() const;
	//@cmember
	/* Retrieves the extended style of a tree view control.*/
	TOOLKIT_API virtual DWORD GetTreeCtrlStyleEx() const;
	//@cmember
	/* Sets value for the style of a tree view control.*/
	TOOLKIT_API virtual BOOL SetTreeCtrlStyle(DWORD dwStyle, BOOL bRedraw = TRUE);
	//@cmember
	/* Sets value for the extended style of a tree view control.*/
	TOOLKIT_API virtual BOOL SetTreeCtrlStyleEx(DWORD dwStyleEx, BOOL bRedraw = TRUE);
	//@cmember
	/* Modifies a tree view control’s style by removal and addition of specified styles.*/
	TOOLKIT_API virtual BOOL ModifyTreeCtrlStyle(DWORD dwRemove, DWORD dwAdd, BOOL bRedraw = TRUE);
	//@cmember
	/* Modifies a tree view control’s extended style by removal and addition of specified extended styles.*/
	TOOLKIT_API virtual BOOL ModifyTreeCtrlStyleEx(DWORD dwRemoveEx, DWORD dwAddEx, BOOL bRedraw = TRUE);
	//@cmember
	/* Modifies a tree view control’s style ans extended style by removal and addition of specified styles and extended styles.*/
	TOOLKIT_API virtual BOOL ModifyTreeCtrlStyles(DWORD dwRemove, DWORD dwAdd, DWORD dwRemoveEx, DWORD dwAddEx, BOOL bRedraw = TRUE);

	//@cmember
	/* Filters out a complete level of the tree from visibility.*/
	TOOLKIT_API void      SetFilterLevel(WORD wLevel);
	//@cmember
	/* Retrieves level of the tree isolated by the filter set by SetFilterLevel.*/
  TOOLKIT_API WORD      GetFilterLevel(void) const;

	//@cmember
	/* Updates the drawing of an item.*/
	TOOLKIT_API virtual BOOL Update( HTREEITEM hti, BOOL bLabelOnly = FALSE, BOOL bEraseBkgnd = TRUE, BOOL bUpdateBelow = FALSE, BOOL bUpdateNow = FALSE );
	//@cmember
	/* Invalidates an item's rectangle.*/
	inline BOOL InvalidateItem(HTREEITEM hti) { Update(hti); return TRUE; };
	//@cmember
	/* Causes the item's width and height to be measured. The item will then be invalidated.*/
	TOOLKIT_API void ReMeasureItem( HTREEITEM hti );

	//@cmember
	/* sets the hover time required to auto expand a drop target. Must have TVXS_AUTOEXPAND. */
	TOOLKIT_API void SetAutoExpandDelay( UINT nDelay ) { m_nAutoExpandDelay = nDelay; }

	//@cmember
	/* sets the maximum numbret of animations when expanding or collapsing, for TVXS_ANIMATE style */
	inline void SetMaxAnimations( int nMaxAnimations )
	{ 
		ASSERT(nMaxAnimations > 0 );
		m_nMaxAnimations = nMaxAnimations;
	}

	TOOLKIT_API void CreateDragArray(CPtrArray* pArray, HTREEITEM hti, CPoint& ptOffset, CRect& rect);

	// Fix the wrong column insertion/deletion behavior.
	// Column Management & Accessors
	//@cmember
	/* Inserts a column.*/
	TOOLKIT_API virtual BOOL InsertColumn( int nCol, const CString& strHeader, int nFormat=LVCFMT_LEFT, int wWidth=-1, int iSubItem = -1, int iImage = -1, BOOL bUpdate = TRUE );

	//@cmember
	/* Deletes a column.*/
    TOOLKIT_API virtual BOOL DeleteColumn( int nCol  );
	//@cmember
	/* Deletes a column.*/
	TOOLKIT_API virtual BOOL DeleteColumn( const CString& strColumnHeading );
//

protected:
	TOOLKIT_API virtual CImageList* InternalCreateDragImage(HTREEITEM hti);
	TOOLKIT_API virtual LPARAM GetUserParam(Item* pItem) const;

		// Paint Context members
	TOOLKIT_API virtual BOOL LoadPaintContext( LvPaintContext* pPC );
	TOOLKIT_API virtual LvPaintContext* CreatePaintContext(CDC* pDC);
	TOOLKIT_API virtual void PickTextFont(LvPaintContext* pPC);

	TOOLKIT_API virtual void MeasureText(CDC* pDC, Node* pNode, const CString& strText, CRect& rectText) const;
	TOOLKIT_API virtual void DrawHierarchyLines(LvPaintContext* pPC);
	TOOLKIT_API virtual void DrawButton(LvPaintContext* pPC);
	TOOLKIT_API virtual void MeasureItem(LvPaintContext* pPC); // QA 27667 - add this override
	TOOLKIT_API virtual void MeasureSubItem(LvPaintContext* pPC, UINT& cySubItem);
    TOOLKIT_API virtual void DrawSubItem(LvPaintContext* pPC);
	
	TOOLKIT_API virtual void DrawHorzHierarchyLine(CDC* pDC, BOOL bSelected, int x1, int x2, int y);
	TOOLKIT_API virtual void DrawVertHierarchyLine(CDC* pDC, BOOL bSelected, int x, int y1, int y2);

	TOOLKIT_API virtual void OnReturnKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnHomeKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnEndKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnLeftKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnBackKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnRightKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnMultKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);

	TOOLKIT_API virtual void NotifyBeginDrag(int nDragItem, POINT ptDrag);
	TOOLKIT_API virtual BOOL NotifyBeginLabelEdit(int nEditItem, int iSubItem) const;
	TOOLKIT_API virtual void NotifyBeginRDrag(int nDragItem, POINT ptDrag);
	TOOLKIT_API virtual void NotifyDeleteItem(int nDelItem) const;
	TOOLKIT_API virtual BOOL NotifyEndLabelEdit(int nEditItem, int iSubItem, CString& strEdit, BOOL bCommit) const;
	TOOLKIT_API virtual void NotifyEndLabelEditChangeComplete(int nEditItem,int iSubItem) const;
	TOOLKIT_API virtual void NotifyGetDispInfo(TV_ITEM *pTVI) const;
	TOOLKIT_API virtual void NotifyGetDispInfo(LV_ITEM* pLVI) const;
	TOOLKIT_API virtual void NotifyItemExpanded(HTREEITEM hti, UINT nCode) const;
	TOOLKIT_API virtual BOOL NotifyItemExpanding(HTREEITEM hti, UINT nCode) const;
	TOOLKIT_API virtual void NotifySelChanged(int nNewItem, int nOldItem, SelectAction sa) const;
	TOOLKIT_API virtual BOOL NotifySelChanging(int nNewItem, int nOldItem, SelectAction sa) const;
	TOOLKIT_API virtual void NotifySetDispInfo(TV_ITEM* pTVI) const;
	TOOLKIT_API virtual void NotifySetDispInfo(const LV_ITEM* pLVI);
	TOOLKIT_API virtual void NotifyGetDispInfoEx(TV_ITEM_EX* pTVIX) const;
	TOOLKIT_API virtual void NotifySetDispInfoEx(const TV_ITEM_EX* pTVIX) const;
	TOOLKIT_API virtual void NotifyKeyDown(UINT nChar) const;

	//Helper functions for CreateDragImage
	TOOLKIT_API virtual CBitmap* BitmapFromText( CDC* pdc, const CString& rStr );
	TOOLKIT_API virtual CImageList* ImageListForText( CDC* pdc, const CString& rStr );
	TOOLKIT_API virtual CImageList* ImageListForImage( CImageList* pImageFrom, int iImageIndex );
	TOOLKIT_API virtual CImageList* CombineImageLists( CImageList* pImlImage, CImageList* pImlText );

	//Create struct cracker
	TOOLKIT_API virtual void ParseCreateStruct( CREATESTRUCT& cs );

	// Improve the sorting efficiency by replacing the bubble sort code with the quicksort code.
	// A helper function for sorting.
	TOOLKIT_API _Node** loadChildrenIntoArray(Node *pParent, unsigned long *ulArySize);

	// Helper functions for insert/delete a column.
	// bArray changed from a BOOL pointer to a reference to a BOOL
	// pointer as a fix for incident 1102532
	TOOLKIT_API void GetExpandInfo(Node* pParent, int nCol, BOOL*& bArray);
	TOOLKIT_API void SetExpandInfo(Node* pParent, int nCol, BOOL*& bArray);

//Operations
protected:
	TOOLKIT_API Item* CreateItemForNode(Node* pNode);
	TOOLKIT_API void RenderSelectionArray(CDC* pDC, int xOffset, int yOffset);
	TOOLKIT_API BOOL HasImage(TV_ITEM* pTVI) const;
	TOOLKIT_API BOOL BuildTreeNode(TV_ITEM* pTVI, Node* pNode, UINT* pMask = NULL );
	TOOLKIT_API SECTreeNode* DetermineNodePosition(	HTREEITEM hInsertAfter,	Node* pNodeNew,	SECTreeNode* pNodeParent);
	TOOLKIT_API BOOL AddNodeToListBox(   Node *ptcnAdd );
	TOOLKIT_API BOOL DelNodeFromListBox( Node *ptcnDel );
	TOOLKIT_API void InitRootNode(void);
	TOOLKIT_API BOOL DeleteUnChildedItem( HTREEITEM hti, BOOL bDelFromListBox=TRUE );
	TOOLKIT_API virtual	BOOL InternalDeleteItem(HTREEITEM hItem);

	TOOLKIT_API BOOL AddChildNodesToListBox( Node *pNode, BOOL bExpand );
	TOOLKIT_API BOOL NodeInListBox( Node *pNode ) const;

    TOOLKIT_API BOOL GetIndexSelItems( CWordArray *pWa ) const;
    TOOLKIT_API void DelNonSiblingsFromListBox( Node *);
    TOOLKIT_API HTREEITEM ExpandSelectedItem( UINT nCode );
    TOOLKIT_API void CollapseSelectedItemThenSelectParent(void);
    TOOLKIT_API void AddSiblingsToListBox( Node *);
    TOOLKIT_API BOOL FilterListBox();
    TOOLKIT_API void AddChildrenToListCtrl(Node* pParent, int& nIndex);
	TOOLKIT_API void RemoveChildrenFromListCtrl(Node* pParent, int nParent);

	TOOLKIT_API virtual void CalcButtonRect( CRect *pRectButton, int iItem, const CRect &rcItem ) const;

	TOOLKIT_API BOOL SelectCaretItem( HTREEITEM hti );

	TOOLKIT_API BOOL ToolTipManager( CPoint pt );
	TOOLKIT_API BOOL ShouldBeInListBox( HTREEITEM hti ) const;

	TOOLKIT_API virtual void NotifyParent_DeleteItem(HTREEITEM hti);

    TOOLKIT_API virtual Node *NewRefTreeCtrlNode(void) const { return new Node; }

	TOOLKIT_API virtual void InternalUpdateColumnText(int nOldSubIndex, int  nNewSubIndex);
	TOOLKIT_API void RecIterateChildren(HTREEITEM hItem, int nOldSubIndex, int nNewSubIndex);

//Message Map handlers
protected:
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	TOOLKIT_API afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	TOOLKIT_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	TOOLKIT_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    DECLARE_MESSAGE_MAP();
	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		TOOLKIT_API virtual LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam); // QA: 31635
	#endif

protected:
	SECSubItemTextStorage* m_pSubItemTextStorage;		
	Node *m_pNodeRoot; //the root of all node storage
	UINT m_nIndent;
	BOOL m_bHideDisabledItems;
	DWORD m_dwTreeStyle;
	DWORD m_dwTreeStyleEx;
	SEC_UINT m_idAutoExpandTimer;
	UINT m_nAutoExpandDelay;
	int m_nMaxAnimations;
	int m_nAnimateCount;
	BOOL m_bScrollOnExpand;
    HANDLE m_hTheme; // QA: 31635
	mutable int m_nLastNodeIndex;

//kim////////////////////////////////////////////////////////////////////
//	struct Color_Font 	
//	{		
//		COLORREF color;
//		LOGFONT  logfont;
//	};	
//	CMap <void*, void*, Color_Font, Color_Font&> m_mapColorFont;
	//////////////////////////////////////////////////////////////////////Nested Classes are last since there seems to be a problem with VC, templates,
// and nested classes...as soon as it is fixed or we have a better workaround, these will
// be taken out of line.
public:
};

#ifndef CHAIN_TREECORE_MESSAGES
#define CHAIN_TREECORE_MESSAGES()\
	ON_WM_DESTROY()\
	ON_WM_LBUTTONDBLCLK()\
	ON_WM_LBUTTONDOWN()\
	ON_WM_TIMER()\
	ON_WM_CHAR()
#endif


//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif // WIN32
