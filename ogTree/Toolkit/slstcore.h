///////////////////////////////////////////////////////////////////////////////
// slscore.h
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
//          Supplement Section 227.7202, Government�s use, duplication or
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

#ifndef __SLSTCLNT_H__
#include "slstclnt.h"
#endif

#ifndef __CMNSTRT_H__
#include "cmnstrt.h"
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

// Extended Styles Defined By SEC_LISTCLASS
//		All these styles use the high-order 16 bits...
#define LVXS_FLYBYTOOLTIPS			0x00100000
#define LVXS_OWNERDRAWVARIABLE		0x00200000
#define LVXS_LINESBETWEENITEMS		0x00400000
#define LVXS_LINESBETWEENCOLUMNS	0x00800000
#define LVXS_WORDWRAP				0x01000000
#define LVXS_HILIGHTSUBITEMS		0x02000000
#define LVXS_FITCOLUMNSONSIZE		0x04000000
#define LVXS_NOGROWCOLUMNONDELETE	0x08000000
#define LVXS_BLENDIMAGE				0x10000000					
#define LVXS_STYLES					(LVXS_FLYBYTOOLTIPS			| \
									 LVXS_OWNERDRAWVARIABLE		| \
									 LVXS_LINESBETWEENITEMS		| \
									 LVXS_LINESBETWEENCOLUMNS	| \
									 LVXS_WORDWRAP				| \
									 LVXS_HILIGHTSUBITEMS		| \
									 LVXS_FITCOLUMNSONSIZE		| \
									 LVXS_NOGROWCOLUMNONDELETE  |\
									 LVXS_BLENDIMAGE)

// The LVS_OWNERDATA style is only define for MFC 4.2 and above
#if _MFC_VER >= 0x0420
#define SEC_LVS_OWNERDATA	LVS_OWNERDATA
#else
#define SEC_LVS_OWNERDATA	0
#endif

#define LVS_STYLES					(LVS_TYPEMASK				| \
									 LVS_SINGLESEL				| \
									 LVS_SHOWSELALWAYS			| \
									 LVS_SORTASCENDING			| \
									 LVS_SORTDESCENDING			| \
									 LVS_SHAREIMAGELISTS		| \
									 LVS_NOLABELWRAP			| \
									 LVS_AUTOARRANGE			| \
									 LVS_EDITLABELS				| \
									 SEC_LVS_OWNERDATA			| \
									 LVS_NOCOLUMNHEADER			| \
									 LVS_NOSORTHEADER			| \
									 LVS_NOSCROLL)

// Extra Mask Flags
#define LVIF_EX_STATEEX				0x0001

// Extra State Flags
#define LVIS_EX_DISABLED			0x0100
#define LVIS_EX_HIDDEN				0x0200

// Extra Hit Test Codes
#define LVHT_COLUMNSEP				0x0800
#define LVHT_COLUMNHEADING			0x1000
#define LVHT_INSIDEITEMBOUNDS		0x2000
#define LVHT_ONITEMLEFT				0x4000
#define LVHT_ONITEMRIGHT			0x8000

#define LVXC_INTERNALBUFFERSIZE		2048

//Constants...
#define SEC_LEFT_OFFSET				(6)
#define SEC_RIGHT_OFFSET			(5)
#define ID_EDIT_REFTREE				(1)        //any old ID will do
#define SECLIST_MAX_LOGICAL_WIDTH	(10000)

#define SECLISTCTRL_HDRHEIGHT_CLISTCTRL 	20
#define SECLISTCTRL_HDRHEIGHT_SECTREECTRL 	18

//Flag used for header images
#define LVSIL_HEADER					3

//Forward Declarations
class SECListTip;
class SECListEdit;

// Return On Error Macro
#ifdef _DEBUG
#define RETURN_ON_ERROR(f, r) \
	do \
	{ \
		if (!(f) && AfxAssertFailedLine(THIS_FILE, __LINE__)) \
		{ \
			AfxDebugBreak(); \
			return r; \
		} \
	} while (0)
#else
#define RETURN_ON_ERROR(f, r) \
	((void)(f))
#endif

#define WIDTH_GAP              6

/////////////////////////////
// AutoDuck tag block block for SEC_LISTCLASS

//@doc SEC_LISTCLASS
//@mfunc virtual int | SEC_LISTCLASS | GetSubItemHit | Returns the subitem 
// number for a given column.
//@parm  int | nHitCol | column number to retrieve the subitem for.

//@doc SEC_LISTCLASS
//@mfunc inline CDWordArray*  | SEC_LISTCLASS | GetSelectionArray | Returns a 
// pointer to the array of selected items. Each item in the array is an index.

//@doc SEC_LISTCLASS
//@mfunc virtual BOOL  |  SEC_LISTCLASS | AreSysColorsTracked | Returns the 
// state of system color tracking.
//@xref <mf SEC_LISTCLASS::EnableSysColorTracking>

//@doc SEC_LISTCLASS
//@mfunc virtual void  |  SEC_LISTCLASS | SetHeaderHeight | Resets the header 
// control height. 
//@parmopt  int | nHeight | SECLISTCTRL_HDRHEIGHT_CLISTCTRL | Use 
// SECLISTCTRL_HDRHEIGHT_CLISTCTRL for CListCtrl height, 
// SECLISTCTRL_HDRHEIGHT_SECTREECTRL for backward compatibility.

//@doc SEC_LISTCLASS
//@mfunc virtual void  |  SEC_LISTCLASS | EnableSysColorTracking | Enables or 
// disables the effects of a WM_SYSCOLORCHANGE message. 
//@parm  BOOL | bEnable | TRUE to enable system color tracking, FALSE to disable. 
// Default TRUE.
//@comm   If enabled,  a WM_SYSCOLORCHANGE message will cause all colors to be 
// refreshed from the default system colors. This will overwrite any color 
// settings that were previously set using SetBkColor, SetTextColor, etc. 
// By default, the control will not track system colors.

// adinsert AutoDuck insertion point for SEC_LISTCLASS
//@doc SEC_LISTCLASS
//@class SEC_LISTCLASS | 
// This class is used internally by the Stingray list controls and tree controls.
// It is not meant for external use, and is documented primarily for the 
// inherited funtions that tree control users may need.
//@base public | SEC_LISTBASE
//@base public | SECListClient
class SEC_LISTCLASS : public SEC_LISTBASE, public SECListClient
{
public:

	enum AutoKeySelectionState
	{
		AutoKeySelectionOn  = 0x0001,	// Will be set as soon as the user 
										// starts typing keys and stays on 
										// until he stops typing (for atleast 
										// the m_nAutoKeySelectionTimerInterval time)			
		AutoKeySelecting	= 0x0002,	// Will be set and stays on as long as the user keeps 
										// typing within the AutoKeySelection timer interval			
		AutoKeySelectionIgnore		= 0x0004,	// Will be set when the user enters the first invalid key
												// and stays as long as AutoKeySelectionOn is set
		AutoKeySelectionDisable = 0x0008	// Globally turns off autokeyselection.
	};

public:
	typedef SECListItem			Item;
	typedef SECListSubItem		SubItem;
	typedef SECListColumn		Column;
	typedef SECListDrawAction	DrawAction;
	typedef SECListSelectAction	SelectAction;
	typedef SECListPaintContext	LvPaintContext;

	friend class SECListEdit;

	int m_nAutoKeySelectionTimerInterval;	// In milli-seconds

// Attributes
protected:
	int m_iDeltaAccum;		// mouse wheel deltas
	int m_nStretchingColumn;
	int m_nTopIndex;
	int m_cyHeader;
	int m_nPendingSelect;
	int m_nPendingEdit;
	int m_nActiveColumn;
	int m_nEditItem;
	int m_nSubItemCount;
	int m_nFocusIndex;
	int m_nDropHilite;
	int m_nAnchor;
	int m_nHotHeaderItem;
	
	LRESULT m_lastNotifyResult;

	UINT m_uiCallbackMask;
	UINT m_uiCallbackMaskEx;
	SEC_UINT m_idEditLabelTimer;
	SEC_UINT m_idAutoScrollTimer;	
	SEC_UINT m_idAutoKeySelectTimer;	// Id for the AutoKeySelection timer
	UINT m_uiAutoKeySelectionMode;	// Current AutoKeySelection mode.
	
	DWORD m_dwListStyle;
	DWORD m_dwListStyleEx;
	DWORD m_dwScrollStyle;

	COLORREF m_rgbText;
	COLORREF m_rgbTextBk;
	COLORREF m_rgbSelText;
	COLORREF m_rgbSelTextBk;
	COLORREF m_rgbDisabledText;
	COLORREF m_rgbIconBk;
	COLORREF m_rgbSelIconBk;
	COLORREF m_rgbToolTipBk;
	COLORREF m_rgbToolTipText;
	COLORREF m_rgbBk;

	BOOL m_bColSepHit;
	BOOL m_bAbortPendingSelect;
	BOOL m_bDidProcessAndDestroyEditLabel;
	BOOL m_bRedrawAfterEveryInsert;
	BOOL m_bDragging;
	BOOL m_bHdrDragging;
	BOOL m_bLookForBeginDrag;
	BOOL m_bTrackSystemColors;


	HCURSOR m_hcurSplit;

	LPTSTR m_pszInternalBuffer;

	CFont* m_pLabelFont;
	CFont* m_pHeaderFont;

	CImageList* m_pImageList;
	CImageList* m_pSmallImageList;
	CImageList* m_pStateImageList;
	CImageList* m_pHeaderImageList;
	CImageList* m_pHdrDragImageList;
	
	SECListTip* m_pToolTipWnd;

	CPoint m_ptViewportOrg;
    CPoint m_ptButtonDown;
	
	CString m_strOldEditText;
	CString m_strAutoKeySelectString;	// Current AutoKeySelection String

	CPtrArray m_arrColumns;
	CPtrArray m_arrItems;
	
	CDWordArray m_arrSelItems;

	SECListEdit* m_pEditCtrl;

	CWnd* m_pNotifyWnd;
	
	int m_nBtnHdr;	//Keeps track of the button header
	int m_nColInsert; //Used for tracking header drag-drop index


// Operations
public:
	//@access Operations
	TOOLKIT_API SEC_LISTCLASS();

	TOOLKIT_API virtual ~SEC_LISTCLASS();
	//[kim] Ŀ���� �ܺο��� ����ϴ� ���
	TOOLKIT_API void	SetCursorSplit ( HCURSOR hCur ) { m_hcurSplit = hCur; }

	TOOLKIT_API virtual BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL );
	TOOLKIT_API virtual BOOL Create( DWORD dwStyle, DWORD dwStyleEx, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL );
	
	//This is the CWnd version of Create.  It gets called from CFrameWnd, CSplitterWnd, SECTabWndBase, and SECShortcutBar.
	// I hook into it, so I can get my own custom Create calls to do the work.
	TOOLKIT_API virtual BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	//One of the problems of the earlier List control was all the bit manipulation.  
	// Since one of my Create calls kicks off to CWnd::CreateEx,
	// I've decided to hide it, and do all bit manipulation for intial create calls inside PreCreateWindow.  
	// The downside is, I have to completely copy and paste CWnd::CreateEx 
	// or I will end up calling PreCreateWindow twice.
	// Luckily, CWnd::CreateEx is relatively simple to code :-)  
	// And I made mine virtual where as MFC didn't.

	TOOLKIT_API virtual BOOL CreateEx( DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, 
		                   int x, int y, int cx, int cy, HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam = NULL );
	
	// Creation Members
	TOOLKIT_API virtual BOOL AttachListCtrl( UINT uID, CWnd* pParentWnd );


	inline  virtual HWND GetHwnd() const{ return GetSafeHwnd(); }
	//@cmember
	/* Returns the subitem number for a given column.*/
	inline virtual int GetSubItemHit( int nHitCol ) const{ return GetColumnAt(nHitCol)->iSubItem; }
	inline virtual void Client2Screen( LPRECT rect ){ ClientToScreen(rect); }

	// Visual Attribute Accessors
	//@cmember
	/* Returns the background color of the control.*/
	TOOLKIT_API virtual COLORREF GetBkColor() const;
	//@cmember
	/* Returns the normal text color.*/
	TOOLKIT_API virtual COLORREF GetTextColor() const;
	//@cmember
	/* Returns the current normal text background color.*/
	TOOLKIT_API virtual COLORREF GetTextBkColor() const;
	//@cmember
	/* Returns the selected text color.*/
	TOOLKIT_API virtual COLORREF GetSelTextColor() const;
	//@cmember
	/* Returns the selected text background color.*/
	TOOLKIT_API virtual COLORREF GetSelTextBkColor() const;
	//@cmember
	/* Returns the disabled text color.*/
	TOOLKIT_API virtual COLORREF GetDisabledTextColor() const;
	//@cmember
	/* Returns the icon background color.*/
	TOOLKIT_API virtual COLORREF GetIconBkColor() const;
	//@cmember
	/* Returns the selected icon background color.*/
	TOOLKIT_API virtual COLORREF GetSelIconBkColor() const;
	//@cmember
	/* Returns the tooltip text background color.*/
	TOOLKIT_API virtual COLORREF GetToolTipBkColor() const;
	//@cmember
	/* Returns the tooltip text color.*/
	TOOLKIT_API virtual COLORREF GetToolTipTextColor() const;
	//@cmember
	/* Returns a pointer to the label font.*/
	TOOLKIT_API virtual CFont* GetLabelFont() const;
	//@cmember
	/* Returns a pointer to the header font.*/
	TOOLKIT_API virtual CFont* GetHeaderFont() const;
	//@cmember
	/* Returns a pointer to the window that will receive control notifications.*/
	TOOLKIT_API virtual CWnd*  GetNotifyWnd() const;
	//@cmember
	/* Resets the header control height. Use SECLISTCTRL_HDRHEIGHT_CLISTCTRL for CListCtrl height, SECLISTCTRL_HDRHEIGHT_SECTREECTRL for backward compatibility */
	inline void SetHeaderHeight(int nHeight=SECLISTCTRL_HDRHEIGHT_CLISTCTRL) { m_cyHeader=nHeight; }

	//@cmember
	/* Sets the background color of the control.*/
	TOOLKIT_API virtual BOOL SetBkColor(COLORREF rgbBk);
	//@cmember
	/* Sets the normal text color.*/
	TOOLKIT_API virtual BOOL SetTextColor(COLORREF rgbText);
	//@cmember
	/* Sets the normal text background color.*/
	TOOLKIT_API virtual BOOL SetTextBkColor(COLORREF rgbTextBk);
	//@cmember
	/* Sets the selected text color.*/
	TOOLKIT_API virtual BOOL SetSelTextColor(COLORREF rgbSelText);
	//@cmember
	/* Sets the normal text background color.*/
	TOOLKIT_API virtual BOOL SetSelTextBkColor(COLORREF rgbSelTextBk);
	//@cmember
	/* Sets the disabled text color.*/
	TOOLKIT_API virtual BOOL SetDisabledTextColor(COLORREF rgbDisabledText);
	//@cmember
	/* Sets the normal icon background color.*/
	TOOLKIT_API virtual BOOL SetIconBkColor(COLORREF rgbIconBk);
	//@cmember
	/* Sets the selected icon background color.*/
	TOOLKIT_API virtual BOOL SetSelIconBkColor(COLORREF rgbSelIconBk);
	//@cmember
	/* Sets the tooltip text background color.*/
	TOOLKIT_API virtual BOOL SetToolTipBkColor(COLORREF rgbToolTipBk);
	//@cmember
	/* Sets the tooltip text color.*/
	TOOLKIT_API virtual BOOL SetToolTipTextColor(COLORREF rgbToolTipText);
	//@cmember
	/* Sets the font to be used when drawing label text.*/
	TOOLKIT_API virtual BOOL SetLabelFont(CFont* pFont);
	//@cmember
	/* Sets the font to be used when drawing header text.*/
	TOOLKIT_API virtual BOOL SetHeaderFont(CFont* pFont);
	//@cmember
	/* Sets the window that will receive notifications.*/
	TOOLKIT_API virtual BOOL SetNotifyWnd(CWnd* pNotifyWnd);
	//@cmember
	/* Enables/disables system color tracking.*/
	inline virtual void EnableSysColorTracking( BOOL bEnable = TRUE ){m_bTrackSystemColors = bEnable;}
	//@cmember
	/* Returns whether system colors are being tracked or not.*/
	inline virtual BOOL AreSysColorsTracked(){ return m_bTrackSystemColors; }
	//@cmember
	/* starts automatic scrolling during drag drop operation. */
	TOOLKIT_API virtual void StartAutoScroll(UINT nInterval=300);
	//@cmember
	/* stops automatic scrolling after a drag drop operation. */
	TOOLKIT_API virtual void StopAutoScroll();

	// Drawing Members
	TOOLKIT_API virtual BOOL Update( int nItem, BOOL bLabelOnly = FALSE, BOOL bEraseBkgnd = TRUE, BOOL bUpdateBelow = FALSE, BOOL bUpdateNow = FALSE );
	TOOLKIT_API virtual BOOL RedrawItems( int nFirst, int nLast );

	// Position/Dimension Accessors
	TOOLKIT_API virtual int GetTopIndex() const;
	TOOLKIT_API virtual int ItemsThisPage();
	TOOLKIT_API virtual int ItemsPrevPage();
	TOOLKIT_API virtual int GetFirstItemLastPage() const;
	TOOLKIT_API virtual int GetLastFullyVisibleItem(LvPaintContext* pPC=NULL);
	TOOLKIT_API virtual int GetFirstItemNextPage() const;
	TOOLKIT_API virtual int GetFirstItemPrevPage();
	
	TOOLKIT_API virtual int GetItemAtPoint(const CPoint& pt);
	TOOLKIT_API virtual int GetItemAbovePoint( const CPoint& pt );
	TOOLKIT_API virtual int GetItemBelowPoint( const CPoint& pt );

	//@cmember
	/* Returns the useable client area of the control.*/
	TOOLKIT_API virtual void GetInsideRect(LPRECT lpRect) const;
	TOOLKIT_API virtual BOOL SetItemHeight(int nIndex, UINT cyItemHeight) const;
	TOOLKIT_API virtual BOOL GetOrigin(LPPOINT lpPoint) const;
	TOOLKIT_API virtual int CalcRangeHeight(int nFirst, int nLast, BOOL bInclusive);
	TOOLKIT_API virtual int CalcItemsInRange(int cyRange, int nStartItem, BOOL bDown);
	//@cmember
	/* Marks all items as needing a remeasurement when the next WM_PAINT occurs.*/
	TOOLKIT_API virtual void ReMeasureAllItems(); 
	TOOLKIT_API virtual void ReMeasureItem( int iIndex );

	// Column Management & Accessors
	//@cmember
	/* Deletes a column.*/
   TOOLKIT_API  virtual BOOL DeleteColumn( int nCol  );
	//@cmember
	/* Deletes a column.*/
	TOOLKIT_API virtual BOOL DeleteColumn( const CString& strColumnHeading );
	//@cmember
	/* Deletes all columns.*/
	TOOLKIT_API virtual BOOL DeleteAllColumns();
    
	//@cmember
	/* Adds a column in the list view control.*/
	TOOLKIT_API virtual BOOL AddColumn( Column* pCol );
	//@cmember
	/* Adds a column in the list view control.*/
	TOOLKIT_API virtual BOOL AddColumn( const CString& strHeader, int fmt=LVCFMT_LEFT, int widthCol=-1, int iSubItem = -1, int iImage = -1);
	//@cmember
	/* Adds a column in the list view control.*/
	TOOLKIT_API virtual BOOL AddColumn( const LV_COLUMN* lvc );

	//@cmember
	/* Inserts a column in the list view control.*/
    TOOLKIT_API virtual BOOL InsertColumn( int nCol, Column* pCol, BOOL bUpdate = TRUE);
	//@cmember
	/* Inserts a column in the list view control.*/
	TOOLKIT_API virtual BOOL InsertColumn( int nCol, const CString& strHeader, int nFormat=LVCFMT_LEFT, int wWidth=-1, int iSubItem = -1, int iImage = -1, BOOL bUpdate = TRUE );
	//@cmember
	/* Inserts a column in the list view control.*/
	TOOLKIT_API virtual BOOL InsertColumn( int nCol, const LV_COLUMN* lvc, BOOL bUpdate = TRUE );

	//@cmember
	/* Removes the column at index 'nColIndexOld' and reinserts it at index 'nColIndexNew'.*/
	TOOLKIT_API virtual BOOL RepositionColumn(int nColIndexOld, int nColIndexNew, BOOL bUpdate = TRUE);	

	//@cmember
	/* Retrieves information about a column.*/
	TOOLKIT_API virtual BOOL GetColumn( int nCol, LV_COLUMN* lvc );
	//@cmember
	/* Sets the properties of a column.*/
	TOOLKIT_API virtual BOOL SetColumn( int nCol, const LV_COLUMN* lvc, BOOL bUpdate );

	TOOLKIT_API virtual int GetColumnLeft( int nCol ) const;
	TOOLKIT_API virtual int GetColumnRight( int nCol ) const;
	//@cmember
	/* Sets the width of a column in pixels.*/
	TOOLKIT_API virtual void SetColumnWidth( int nCol, int width );
	//@cmember
	/* Returns the width of a column in pixels.*/
	TOOLKIT_API virtual int GetColumnWidth( int nCol ) const;
	//@cmember
	/* Sets the alignment of a column.*/
	TOOLKIT_API virtual void SetColumnFormat( int nCol, int fmt );
	//@cmember
	/* Returns the alignment of a column.*/
	TOOLKIT_API virtual int GetColumnFormat( int nCol ) const;
	//@cmember
	/* Sets the text of a column header.*/
	TOOLKIT_API virtual void SetColumnHeading( int nCol, const CString& strHeading );
	//@cmember
	/* Returns the text of a column header.*/
	TOOLKIT_API virtual CString GetColumnHeading( int nCol ) const;
	//@cmember
	/* Sets the column header image.*/
	TOOLKIT_API void SetColumnImage( int nCol, int nImage );
	//@cmember
	/* Returns the column header image index.*/
	TOOLKIT_API int GetColumnImage( int nCol ) const;
	//@cmember
	/* Returns whether a column with the given text exists or not.*/
    TOOLKIT_API virtual BOOL ColumnExists( const CString &strColTitle ) const;
	//@cmember
	/* Returns the number of columns.*/
	TOOLKIT_API virtual int GetColumnCount() const;
	//@cmember
	/* Searches for a column by string title.*/
    TOOLKIT_API virtual BOOL FindColumn( const CString &strColumnHeading, int& nCol, int& iSubItem ) const;
	//@cmember
	/* Returns the Column object at a given index.*/
	TOOLKIT_API virtual Column* GetColumnAt(int nCol) const;

	// Items/SubItem Management & Accessors
	TOOLKIT_API virtual LPARAM GetUserParam(Item* pItem) const;
	TOOLKIT_API Item* GetItemAt(int nIndex) const;
	TOOLKIT_API virtual int GetItemCount() const;
	TOOLKIT_API virtual int GetSubItemCount() const;
	TOOLKIT_API virtual BOOL SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem, int nImage, UINT nState, UINT nStateMask, LPARAM lParam);
	TOOLKIT_API virtual BOOL SetItem(const LV_ITEM* pLVI, BOOL bRedraw = TRUE);
	TOOLKIT_API virtual BOOL SetItemEx(LV_ITEM* pLVI, const LV_ITEM_EX* pLVIX);
	TOOLKIT_API virtual BOOL GetItem(LV_ITEM* pLVI, BOOL bCopyText = TRUE, BOOL bGetDispInfo = FALSE) const;
	TOOLKIT_API virtual BOOL GetItemEx(LV_ITEM* pLVI, LV_ITEM_EX* pLVIX, BOOL bGetDispInfo = FALSE) const;
	TOOLKIT_API virtual BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText);
	TOOLKIT_API virtual int GetItemText(int nItem, int nSubItem, LPTSTR lpszText, int nLen) const;
	TOOLKIT_API virtual CString GetItemText(int nItem, int nSubItem) const;
	
	TOOLKIT_API virtual BOOL DeleteItem( int nItem, int cCount = 1 );
	TOOLKIT_API virtual BOOL DeleteItem( Item* pItem );
	TOOLKIT_API virtual BOOL DeleteAllItems();

	//@cmember
	/* Returns the number of selected items.*/
	TOOLKIT_API virtual UINT GetSelectedCount( ) const;
	TOOLKIT_API virtual BOOL GetItemRect( int nItem, LPRECT lpRect, UINT nCode ) const;
	TOOLKIT_API virtual BOOL GetItemRect( int nItem, int nCol, LPRECT lpRect, UINT nCode ) const;
	
	TOOLKIT_API virtual int InsertItem(const LV_ITEM* pItem);
	TOOLKIT_API virtual int InsertItem(int nItem, LPCTSTR lpszItem);
	TOOLKIT_API virtual int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);
	TOOLKIT_API virtual int InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask, int nImage, LPARAM lParam);
	TOOLKIT_API virtual int InsertItem(int nItem, const Item* pItem);
	TOOLKIT_API virtual int InsertItemAfter( Item* pItem, LV_ITEM* pLVI );
	TOOLKIT_API virtual int InsertItemBefore( Item* pItem, LV_ITEM* pLVI );
	
	TOOLKIT_API virtual BOOL IsSelected(int nIndex) const;
	TOOLKIT_API virtual BOOL SelectFocusItem(int nIndex, BOOL bSelected = TRUE);
	TOOLKIT_API virtual BOOL SetFocusItem(int nIndex);
	//@cmember
	/* Clears the selection array.*/
	TOOLKIT_API virtual BOOL DeselectAllItems(int iExclude = -1);
	TOOLKIT_API virtual BOOL SelectItemRange(int nFirst, int nLast, BOOL bSelect = TRUE);
	TOOLKIT_API virtual int GetFocusIndex() const;
	//@cmember
	/* Retrieves the logical size of the list view control.*/
	TOOLKIT_API virtual CSize GetLogicalSize(LvPaintContext* pPC=NULL);
	TOOLKIT_API virtual BOOL SetItemState(int nItem, UINT nState, UINT nMask);
	TOOLKIT_API virtual UINT GetItemState(int nItem, UINT nMask) const;
	TOOLKIT_API virtual BOOL SetItemData(int nItem, SEC_DWORD dwData);
	TOOLKIT_API virtual SEC_DWORD GetItemData(int nItem) const;
	TOOLKIT_API virtual BOOL SelectItem(int nIndex, BOOL bSelect = TRUE);
	TOOLKIT_API virtual UINT GetCallbackMask() const;
	TOOLKIT_API virtual BOOL SetCallbackMask(UINT nMask);
	TOOLKIT_API virtual UINT GetCallbackMaskEx() const;
	TOOLKIT_API virtual BOOL SetCallbackMaskEx(UINT nMaskEx);
	TOOLKIT_API  BOOL IsCallbackItem(int nItem) const;

	// Item Traversal
	//
	// There are two ways to traverse the selected items.  You can use
	// GetNextItem() passing LVNI_SELECTED or you can retrieve the
	// selection array.  GetNextItem() is useful when you want to find
	// items that have more than one state bit set concurrently.  If
	// you are only interested in selected items, GetSelectionArray
	// is faster.

	TOOLKIT_API virtual int GetNextItem(int nItem, int nFlags = LVNI_ALL) const;
	//@cmember
	/* Returns a pointer to the array of selected items.*/
	inline CDWordArray* GetSelectionArray() { return &m_arrSelItems; };

	// Drag and Drop
	TOOLKIT_API virtual BOOL SelectDropTarget(int nIndex);
	TOOLKIT_API virtual int GetDropHilightIndex() const;

	// Image List
	TOOLKIT_API virtual CImageList* GetImageList(UINT nImageList) const;
	TOOLKIT_API virtual CImageList* SetImageList(CImageList* pImageList, int nImageListType);
	TOOLKIT_API virtual void CopyImageList( CImageList* pImlFrom, CImageList*& pImlTo );

	// Hit Testing
	//@cmember
	/* Determines what is under a given point.*/
	TOOLKIT_API virtual int HitTest( CPoint pt, UINT* pFlags, int& nHitCol ) const;

	// Scrolling Members
	TOOLKIT_API virtual void SetFirstVisible(int nIndex);
	TOOLKIT_API virtual void ScrollHorz(int nPixels);
	TOOLKIT_API virtual void ScrollVert(int nScrollItems, BOOL bFromBottom = FALSE);
	TOOLKIT_API virtual BOOL EnsureVisible(int nItem, BOOL bPartialOk = FALSE);
	TOOLKIT_API virtual BOOL EnsureRangeVisible(int nFirst, int nLast, BOOL bPartialOk = FALSE);

	// In-Place Editing Members
	TOOLKIT_API virtual CEdit* EditLabel( int nItem, int nCol = 0 );
	//@cmember
	/* Returns a pointer to the edit control used in EditLabel.*/
	TOOLKIT_API virtual CEdit* GetEditControl();
	TOOLKIT_API virtual BOOL KillEditControl();

	// Style accessors
	TOOLKIT_API virtual BOOL IsStyleSet( DWORD dwStyle ) const;
	TOOLKIT_API virtual BOOL IsExStyleSet( DWORD dwExStyle ) const;
	//@cmember
	/* Returns the list control style and extended style.*/
	TOOLKIT_API virtual BOOL GetListCtrlStyles(DWORD& dwStyle, DWORD& dwStyleEx) const;
	//@cmember
	/* Sets the list control styles and extended styles.*/
	TOOLKIT_API virtual BOOL SetListCtrlStyles(DWORD dwStyle, DWORD dwStyleEx, BOOL bRedraw = TRUE);
	//@cmember
	/* Returns the list control style.*/
	TOOLKIT_API virtual DWORD GetListCtrlStyle() const;
	//@cmember
	/* Returns the list control extended style.*/
	TOOLKIT_API virtual DWORD GetListCtrlStyleEx() const;
	//@cmember
	/* Sets the list control style.*/
	TOOLKIT_API virtual BOOL SetListCtrlStyle(DWORD dwStyle, BOOL bRedraw = TRUE);
	//@cmember
	/* Sets the list control extended style.*/
	TOOLKIT_API virtual BOOL SetListCtrlStyleEx(DWORD dwStyleEx, BOOL bRedraw = TRUE);
	//@cmember
	/* Adds and/or removes list control styles.*/
	TOOLKIT_API virtual BOOL ModifyListCtrlStyle(DWORD dwRemove, DWORD dwAdd, BOOL bRedraw = TRUE);
	//@cmember
	/* Adds and/or removes list control extended styles.*/
	TOOLKIT_API virtual BOOL ModifyListCtrlStyleEx(DWORD dwRemoveEx, DWORD dwAddEx, BOOL bRedraw = TRUE);
	//@cmember
	/* Adds and/or removes list control styles and extended styles.*/
	TOOLKIT_API virtual BOOL ModifyListCtrlStyles(DWORD dwRemove, DWORD dwAdd,
							DWORD dwRemoveEx, DWORD dwAddEx, BOOL bRedraw = TRUE);

	// Feature and Viewing Mode Enable/Disable Members
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
	/* Returns whether word wrap is enabled or not.*/
	TOOLKIT_API virtual BOOL IsWordWrapEnabled() const;
	//@cmember
	/* Returns whether tooltips is enabled or not.*/
	TOOLKIT_API virtual BOOL AreToolTipsEnabled() const;
	//@cmember
	/* Returns whether the column header is enabled or not.*/
	TOOLKIT_API virtual BOOL IsHeaderCtrlEnabled() const;
	//@cmember
	/* Enables/disables the column header.*/
	TOOLKIT_API virtual void EnableHeaderCtrl(BOOL bEnable = TRUE, BOOL bSortHeader = FALSE);
	//@cmember
	/* Returns whether multiple selection is enabled or not.*/
	TOOLKIT_API virtual BOOL IsMultiSelectEnabled() const;
	//@cmember
	/* Enables/disables redrawing after every insert/delete.*/
	TOOLKIT_API virtual void EnableRedrawAfterInsert(BOOL bEnable = TRUE);
	//@cmember
	/* Returns whether redraw after insert/delete is enabled or not.*/
	TOOLKIT_API virtual BOOL IsRedrawAfterInsertEnabled() const;
	//@cmember
	/* determines if the horizontal and/or vertical scroll bars should be shown or not.*/
	TOOLKIT_API virtual void RecalcScrollBars();

	// Queries
	//@cmember
	/* Returns the number of visible items.*/
	TOOLKIT_API UINT GetVisibleCount() const;

	// used by the tooltip class
	inline virtual CWnd* Capture( BOOL b )
	{ 
		if(b)
			return SetCapture();
		else 
			return NULL;
	}

	// Helper functions for AutoKeySelection feature.
	TOOLKIT_API BOOL TryMovingTo(int nFromItem, CString strLike);
	TOOLKIT_API int GetNextMatchingItem(int nFromItem, CString strLike);

// Implementation
protected:
	TOOLKIT_API virtual int GetLogicalWidth(LvPaintContext* pPC=NULL);
	TOOLKIT_API virtual int GetLogicalHeight();
	inline virtual void SECGetClientRect( LPRECT lpRect ) const { GetClientRect(lpRect); }
	TOOLKIT_API virtual CDC* GetActiveDC( BOOL& bDelete );
	TOOLKIT_API virtual void ClearMeasurements();
	TOOLKIT_API void ClearAllCy();

	TOOLKIT_API virtual BOOL AutoSizeColumns();

	// Allocation & Initialization
	TOOLKIT_API virtual BOOL CreateScrollBarCtrl(DWORD dwStyle, UINT nID);
  TOOLKIT_API virtual BOOL AllocateSubItems( Item* pItem ) const;
	TOOLKIT_API virtual BOOL DeallocateSubItems( Item* pItem ) const;
	TOOLKIT_API virtual int InitNewItem(Item* pItem) const;
	TOOLKIT_API virtual Item* CreateNewItem();
	TOOLKIT_API virtual void ShowScrollBarCtrl(int nBar, BOOL bShow = TRUE, LPSCROLLINFO lpScrollInfo = NULL);
	TOOLKIT_API BOOL AddToSelItemsArray(int iItem);
	TOOLKIT_API BOOL RemoveFromSelItemsArray(int iItem);
	TOOLKIT_API BOOL FindInSelItemsArray(int iItem, int& nIndex) const;

	// Color/Font/Pen Pick Members
	TOOLKIT_API virtual void PickItemBkgnd(LvPaintContext* pPC);
	TOOLKIT_API virtual void PickIconBkgnd(LvPaintContext* pPC);
	//@cmember
	/* Sets the text color for list items.*/
	TOOLKIT_API virtual void PickTextColors(LvPaintContext* pPC);
	//@cmember
	/* Sets the text font for list items.*/
	TOOLKIT_API virtual void PickTextFont(LvPaintContext* pPC);
	TOOLKIT_API virtual void PickItemLinePen(CPen*& pPen);
	TOOLKIT_API virtual void PickColumnLinePen(CPen*& pPen);

	// Layout Members
	TOOLKIT_API virtual void MeasureItem(int nItem, LvPaintContext* pPC=NULL);
	TOOLKIT_API virtual void MeasureItem(LvPaintContext* pPC);
	TOOLKIT_API virtual void MeasureSubItem(LvPaintContext* pPC, UINT& cySubItem);
	TOOLKIT_API virtual void MeasureSubItemIcon( LvPaintContext* pPC, CRect& rcIcon );
	TOOLKIT_API virtual void MeasureSubItemText( LvPaintContext* pPC, CRect& rcText );

	TOOLKIT_API virtual void RecalcLayout();
	TOOLKIT_API virtual void ResizeColumnsToFit();
	inline virtual int  GetMargin() const
		{ return 0; }

	// Column Resize Tracking
	TOOLKIT_API virtual int TrackColumnResize(CPoint point, int nCol);

	// Owner Draw Members
	// Note, the draw members below reference the paint context for
	// display info needed for the item rendering.
	TOOLKIT_API virtual void DoPaint(CDC* pDC);
	TOOLKIT_API virtual BOOL LoadPaintContext(LvPaintContext* pPC);
	TOOLKIT_API virtual LvPaintContext* CreatePaintContext(CDC* pDC);
	TOOLKIT_API virtual BOOL CreateMemDC( CDC* pScreenDC, CDC*& pMemDC, const CRect& rectBitmap ) const;

	//Header extended drawing functionality
	TOOLKIT_API virtual void DrawHeader(LvPaintContext* pPC);
	TOOLKIT_API virtual void DrawBtnHeader(int nColHit, BOOL bPush);
	TOOLKIT_API virtual void DrawHeaderImage(CDC* pDC, Column* pCol, CRect& rectText, UINT& nFlags);
	TOOLKIT_API void ColumnFormatHelper(int& nColFmt, UINT& nflags);

	//Header drag-drop helper members
	TOOLKIT_API virtual CImageList* CreateHeaderDragImage(int nColumn );
	TOOLKIT_API virtual void DrawHdrInsertionPoint(CPoint point, int nHitCol);
	TOOLKIT_API void InternalErasePrevInsert(int nInsertTemp);
	inline virtual void InternalUpdateColumnText(int /*nOldSubIndex*/, int /*nNewSubIndex */)	{};

	TOOLKIT_API virtual void DrawInvalidItems(LvPaintContext* pPC);
	TOOLKIT_API virtual void DrawItem(LvPaintContext* pPC);
	TOOLKIT_API virtual void DrawSubItem(LvPaintContext* pPC);
	TOOLKIT_API virtual void DrawSubItemIcon( LvPaintContext* pPC );
	TOOLKIT_API virtual void DrawSubItemText( LvPaintContext* pPC );
	TOOLKIT_API virtual void DrawItemLines(CDC* pDC, int nItem, const CRect& rcRow);
	TOOLKIT_API virtual void DrawColumnLines(CDC* pDC, int nItem, const CRect& rcRow);

	// In-Place Editing Implementation Members
	TOOLKIT_API virtual BOOL ProcessAndDestroyEditLabel(BOOL bSaveLabel=TRUE);

	// Scrolling Implementation Members
	TOOLKIT_API virtual void RecalcVertScrollBar(int cyLog);
	TOOLKIT_API virtual void RecalcHorzScrollBar(int cxLog);

	// Keyboard handlers
	TOOLKIT_API virtual void OnSpaceKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnUpKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnDownKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnF2KeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnReturnKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnHomeKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnEndKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnLeftKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnBackKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnRightKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnMultKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnPgUpKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API virtual void OnPgDnKeyPressed(int nItem, int nSubItem, BOOL bShift, BOOL bCtrl, UINT nRepCnt, UINT nFlags);

	// List Control Notifications (sent to parent)
	TOOLKIT_API virtual void NotifyNMHDR( UINT wNotify );
	TOOLKIT_API virtual void NotifyBeginDrag(int nDragItem, POINT ptDrag);
	TOOLKIT_API virtual BOOL NotifyBeginLabelEdit(int nEditItem, int iSubItem) const;
	TOOLKIT_API virtual void NotifyBeginRDrag(int nDragItem, POINT ptDrag);
	TOOLKIT_API virtual void NotifyDeleteItem(int nDelItem) const;
	TOOLKIT_API virtual BOOL NotifyEndLabelEdit(int nEditItem, int iSubItem, CString& strEdit, BOOL bCommit) const;
	TOOLKIT_API virtual void NotifyEndLabelEditChangeComplete(int nEditItem,int iSubItem) const;
	TOOLKIT_API virtual void NotifySelChanged(int nNewItem, int nOldItem, SelectAction sa) const;
	TOOLKIT_API virtual BOOL NotifySelChanging(int nNewItem, int nOldItem, SelectAction sa) const;
	TOOLKIT_API virtual void NotifyGetDispInfo(LV_ITEM* pLVI) const;
	TOOLKIT_API virtual void NotifySetDispInfo(const LV_ITEM* pLVI);
	TOOLKIT_API virtual void NotifyGetDispInfoEx(LV_ITEM_EX* pLVIX) const;
	TOOLKIT_API virtual void NotifySetDispInfoEx(const LV_ITEM_EX* pLVIX) const;
	TOOLKIT_API virtual void NotifyInsertItem(int nItem) const;
	TOOLKIT_API virtual void NotifyKeyDown(UINT nChar) const;
	TOOLKIT_API virtual void NotifyColumnClick(int nColumnClick) const;

	TOOLKIT_API virtual BOOL ProcessSelectChange(int nHitIndex,UINT iHitFlags,UINT nFlags,SelectAction sa);
	TOOLKIT_API virtual void ExecuteSelectChange(int nItem, SelectAction sa);
	TOOLKIT_API virtual CWnd* NotifyWnd() const;

	//Create Struct Cracker...
	TOOLKIT_API virtual void ParseCreateStruct( CREATESTRUCT& cs );

	// hit testing
	TOOLKIT_API virtual void ListHitTestEx( const CPoint& point, const int nHitIndex, const UINT iHitFlags, BOOL& bLookForBeginDrag, BOOL& bSelChange);

// MFC Overrides
public:
	TOOLKIT_API virtual CScrollBar* GetScrollBarCtrl(int nBar) const;

protected:
	TOOLKIT_API afx_msg void OnPaint();
    TOOLKIT_API afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	TOOLKIT_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnDestroy();
	TOOLKIT_API afx_msg void OnSize(UINT nType, int cx, int cy);
	TOOLKIT_API afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	TOOLKIT_API afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	TOOLKIT_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	TOOLKIT_API afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	TOOLKIT_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnTimer(SEC_UINT nIDEvent);
	TOOLKIT_API afx_msg void EditLabel_OnKillFocus(void);
	TOOLKIT_API afx_msg void EditLabel_OnUpdate(void);
	TOOLKIT_API afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	TOOLKIT_API afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	TOOLKIT_API afx_msg void OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	TOOLKIT_API afx_msg void OnEnable( BOOL bEnable );
	TOOLKIT_API afx_msg UINT OnGetDlgCode();
#ifndef UNDER_CE
	TOOLKIT_API afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	TOOLKIT_API afx_msg void OnRButtonUp( UINT nFlags, CPoint point );
#endif //UNDER_CE
	TOOLKIT_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	TOOLKIT_API afx_msg void OnKillFocus( CWnd *pwndNew );
	TOOLKIT_API afx_msg void OnCancelMode( );
#ifndef UNDER_CE
	TOOLKIT_API afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
#endif
	TOOLKIT_API afx_msg void OnSysColorChange( );

	// QA: 32259
	#if defined NTDDI_VERSION && (NTDDI_VERSION >= NTDDI_WINXP)
		TOOLKIT_API virtual LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);
	#endif

	TOOLKIT_API virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};


// Intellimouse not supported on MFC < 4.21
#if _MFC_VER < 0x0421
	#define ON_WM_MOUSEWHEEL() 
#endif

#ifndef CHAIN_LISTCORE_MESSAGES
#ifndef UNDER_CE
#define CHAIN_LISTCORE_MESSAGES()\
	ON_WM_PAINT()\
    ON_WM_CREATE()\
	ON_WM_ERASEBKGND()\
	ON_WM_SETCURSOR()\
	ON_WM_MOUSEMOVE()\
	ON_WM_CANCELMODE()\
	ON_WM_LBUTTONDOWN()\
	ON_WM_LBUTTONUP()\
	ON_WM_LBUTTONDBLCLK()\
	ON_WM_DESTROY()\
	ON_WM_SIZE()\
	ON_WM_HSCROLL()\
	ON_WM_VSCROLL()\
	ON_WM_TIMER()\
	ON_WM_KEYDOWN()\
	ON_WM_CHAR()\
	ON_WM_SYSKEYDOWN()\
	ON_WM_ENABLE()\
	ON_WM_GETDLGCODE()\
	ON_WM_RBUTTONDOWN()\
	ON_WM_RBUTTONUP()\
	ON_WM_SETFOCUS()\
	ON_WM_KILLFOCUS()\
	ON_WM_MOUSEWHEEL()\
	ON_WM_SYSCOLORCHANGE()\
	ON_CONTROL( EN_KILLFOCUS, ID_EDIT_REFTREE, EditLabel_OnKillFocus )\
	ON_CONTROL( EN_UPDATE, ID_EDIT_REFTREE, EditLabel_OnUpdate )
#else
#define CHAIN_LISTCORE_MESSAGES()\
	ON_WM_PAINT()\
    ON_WM_CREATE()\
	ON_WM_ERASEBKGND()\
	ON_WM_SETCURSOR()\
	ON_WM_MOUSEMOVE()\
	ON_WM_CANCELMODE()\
	ON_WM_LBUTTONDOWN()\
	ON_WM_LBUTTONUP()\
	ON_WM_LBUTTONDBLCLK()\
	ON_WM_DESTROY()\
	ON_WM_SIZE()\
	ON_WM_HSCROLL()\
	ON_WM_VSCROLL()\
	ON_WM_TIMER()\
	ON_WM_KEYDOWN()\
	ON_WM_CHAR()\
	ON_WM_SYSKEYDOWN()\
	ON_WM_ENABLE()\
	ON_WM_GETDLGCODE()\
	ON_WM_SETFOCUS()\
	ON_WM_KILLFOCUS()\
	ON_WM_SYSCOLORCHANGE()\
	ON_CONTROL( EN_KILLFOCUS, ID_EDIT_REFTREE, EditLabel_OnKillFocus )\
	ON_CONTROL( EN_UPDATE, ID_EDIT_REFTREE, EditLabel_OnUpdate )
#endif //UNDER_CE
#endif //CHAIN_LISTCORE_MESSAGES

//
// SEC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // WIN32

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           