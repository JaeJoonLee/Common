#ifndef _GXGRIDCELLSTYLE_H_
#define _GXGRIDCELLSTYLE_H_

enum DxGridCellDataType	//
{
	dxGridDataType_Value				= 0,// Caption Value
	dxGridDataType_MultiCaption,			// Multi Caption
	dxGridDataType_MultiTooltip,			// MultiTooltip
	dxGridDataType_MultiChoiceList,			// MultiChoiceList
	dxGridDataType_ItemName,				// Item Name
	dxGridDataType_RecordName,				// Record Name
};


typedef DWORD           ROWCOL;

// GridCellstyle
class CGXGridCellStyle : public CObject
{
	DECLARE_SERIAL(CGXGridCellStyle)	
public:
	// operations
	CGXGridCellStyle();
	CGXGridCellStyle(const CGXGridCellStyle& p);

	virtual ~CGXGridCellStyle();

	virtual CGXGridCellStyle* Clone() const;// create a new style with "new CGXGridCellStyle(*this);"

	virtual const CGXGridCellStyle& operator=(const CGXGridCellStyle& p);

	virtual CGXGridCellStyle& SetDefault();

	virtual void Serialize(CArchive& ar);
	virtual void ChangeStyle(const CGXGridCellStyle& p );

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual void Free();

protected:
	void ConstructStyle();

// Attributes
	struct STYLEBITS
	{
		unsigned value:			1;
		unsigned multicaption:	1;
		unsigned tooltip:		1;
		unsigned choicelist:	1;
		unsigned item:			1;
		unsigned recordname:	1;
		//6 Bits

		DWORD GetPortable() const;
		void SetPortable(DWORD dw);
		STYLEBITS(DWORD dw = 0);

		DWORD GetNoPortableBits() const;
        void SetNoPortableBits(DWORD dw);
        BOOL NoPortableIsEmptyBits() const;
	};
public:
	STYLEBITS	stylebits;

	// CString m_sValue;
	LPSTR       m_lpszValue;
	CString		m_strMultiCaption,
		        m_strMultiTooltip,
				m_strMultiChoiceList,
				m_strItemName,
				m_strRecordName;
	// 4 byte
	
// Access member functions
public:
	// Get Data
	BOOL GetDataValue( short nDataType ,CString& strValue  ) const;
	
	CGXGridCellStyle& SetMultiLangDataValue( short nDataType ,CString strValue);

	// Caption
	BOOL GetIncludeCaptionValue() const;
	CGXGridCellStyle& SetIncludeCaptionValue(BOOL b);
	LPCTSTR GetCaptionValueBuf() const;
	
	CGXGridCellStyle& SetCaptionValue(LPCTSTR s, short nLen = -1);
	CGXGridCellStyle& SetCaptionValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetValue will convert ansi characters
	// to wide characters.
	CGXGridCellStyle& SetCaptionValue(const char* s);
#endif
	
	// MultiCaption
	BOOL GetIncludeMultiCaptionValue() const;
	CGXGridCellStyle& SetIncludeMultiCaptionValue(BOOL b);
	const CString& GetMultiCaptionValue() const;
	const CString& GetMultiCaptionValueRef() const;

	CGXGridCellStyle& SetMultiCaptionValue(LPCTSTR s);
	CGXGridCellStyle& SetMultiCaptionValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXGridCellStyle& SetMultiCaptionValue(const char* s);
#endif
	
	// MultiChoice list: each choice is separated with a new newline
	BOOL GetIncludeMultiChoiceListValue() const;
	CGXGridCellStyle& SetIncludeMultiChoiceListValue(BOOL b);
	const CString& GetMultiChoiceListValue() const;
	const CString& GetMultiChoiceListValueRef() const;
	CGXGridCellStyle& SetMultiChoiceListValue(LPCTSTR s);
	CGXGridCellStyle& SetMultiChoiceListValue(const CString& s);

#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXGridCellStyle& SetMultiChoiceListValue(const char* s);
#endif

	// Item Name
	BOOL GetIncludeItemNameValue() const;
	CGXGridCellStyle& SetIncludeItemNameValue(BOOL b);
	const CString& GetItemNameValue() const;
	const CString& GetItemNameValueRef() const;
	CGXGridCellStyle& SetItemNameValue(LPCTSTR s);
	CGXGridCellStyle& SetItemNameValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXGridCellStyle& SetItemNameValue(const char* s);
#endif

	// Record Name
	BOOL GetIncludeRecordNameValue() const;
	CGXGridCellStyle& SetIncludeRecordNameValue(BOOL b);
	const CString& GetRecordNameValue() const;
	const CString& GetRecordNameValueRef() const;
	CGXGridCellStyle& SetRecordNameValue(LPCTSTR s);
	CGXGridCellStyle& SetRecordNameValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXGridCellStyle& SetRecordNameValue(const char* s);
#endif

	// Tooltip Caption
	BOOL GetIncludeMultiTooltipValue() const;
	CGXGridCellStyle& SetIncludeMultiTooltipValue(BOOL b);
	const CString& GetMultiTooltipValue() const;
	const CString& GetMultiTooltipValueRef() const;
	CGXGridCellStyle& SetMultiTooltipValue(LPCTSTR s);
	CGXGridCellStyle& SetMultiTooltipValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXGridCellStyle& SetMultiTooltipValue(const char* s);
#endif
	

public:
// Implementation
	DWORD GetStyleBits() const;

};


class CGXGridCellStylePtrArray: public CPtrArray
{
	DECLARE_DYNAMIC(CGXGridCellStylePtrArray)

public:
	// Construcion/Destruction
	CGXGridCellStylePtrArray();
	CGXGridCellStylePtrArray(const CGXGridCellStylePtrArray& other);
	virtual ~CGXGridCellStylePtrArray();
		// destructor automatically deletes all referenced objects

	const CGXGridCellStylePtrArray& operator=(const CGXGridCellStylePtrArray& other);

	void DeleteAll(); // delete all referenced objects
	void DeleteAt(int nIndex, int nCount = 1);
	void Move(int nIndex, int nCount, int nDest);

	virtual void Serialize(CArchive& ar);

public:
	// Accessing elements
	CGXGridCellStyle* GetAt(int nIndex) const;
	void SetAt(int nIndex, CGXGridCellStyle* newElement);

	// Potentially growing the array
	void SetAtGrow(int nIndex, CGXGridCellStyle* newElement);
	int Add(CGXGridCellStyle* newElement);

	// overloaded operator helpers
	CGXGridCellStyle* operator[](int nIndex) const;
	CGXGridCellStyle*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, CGXGridCellStyle* newElement, int nCount = 1);
	void InsertAt(int nStartIndex, CGXGridCellStylePtrArray* pNewArray);
};

// type-safe CPtrArray for array with CGXGridCellStylePtrArray objects

class CGXGridCellStylePtrArrayPtrArray: public CPtrArray
{
	DECLARE_DYNAMIC(CGXGridCellStylePtrArrayPtrArray)

public:
	// Construcion/Destruction
	CGXGridCellStylePtrArrayPtrArray();
	CGXGridCellStylePtrArrayPtrArray(const CGXGridCellStylePtrArrayPtrArray& other);
	virtual ~CGXGridCellStylePtrArrayPtrArray();
		// destructor automatically deletes all referenced objects

	const CGXGridCellStylePtrArrayPtrArray& operator=(const CGXGridCellStylePtrArrayPtrArray& other);

	void DeleteAll(); // delete all referenced objects
	void DeleteAt(int nIndex, int nCount = 1);
	void Move(int nIndex, int nCount, int nDest);

	virtual void Serialize(CArchive& ar);

public:
	// Accessing elements
	CGXGridCellStylePtrArray* GetAt(int nIndex) const;
	void SetAt(int nIndex, CGXGridCellStylePtrArray* newElement);

	// Potentially growing the array
	void SetAtGrow(int nIndex, CGXGridCellStylePtrArray* newElement);
	int Add(CGXGridCellStylePtrArray* newElement);

	// overloaded operator helpers
	CGXGridCellStylePtrArray* operator[](int nIndex) const;
	CGXGridCellStylePtrArray*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, CGXGridCellStylePtrArray* newElement, int nCount = 1);
	void InsertAt(int nStartIndex, CGXGridCellStylePtrArrayPtrArray* pNewArray);
};

class CGXGridCellData: public CObject
{
	DECLARE_SERIAL(CGXGridCellData)

public:
	// operations
	CGXGridCellData();
	virtual ~CGXGridCellData();
	virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);
	

	virtual const CGXGridCellData& operator=(const CGXGridCellData& p);
	void		  SerializeEx(CArchive& ar, CString& strPropertyData );

	BOOL		  SetMultiCaptionBlobDataChange ( CString  strPropertyData );
	CString       GetMultiCaptionBlobDataChange ( );

	void		  SetSingleMode					( );

	DWORD		  GetStyleBitsInfo				( ) {  ASSERT ( m_pDefCaptionStyle ); return m_pDefCaptionStyle->GetStyleBits(); }

protected:
	// attributes
	ROWCOL	m_nRows, // row count
			m_nCols; // column count

	unsigned m_bSingleMode : 1;        

	CGXGridCellStylePtrArrayPtrArray m_apapCellStyle; // spans the cell matrix,
													  // CGXGridCellStylePtrArray elements are rows
													  // which CGXGridCellStyle elements are styles
	CGXGridCellStyle* m_pDefCaptionStyle;

public:

// Access member functions
public:
	// Number of Rows and Colums
	virtual ROWCOL GetRowCount();
	virtual ROWCOL GetColCount();

	BOOL SetRowCount(ROWCOL nRows );
	BOOL SetColCount(ROWCOL nCols );

	virtual BOOL StoreRowCount(ROWCOL wRows);
	virtual BOOL StoreColCount(ROWCOL wCols);

// Operations
public:
	// Inserting Colums or Rows
	virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount);
	virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount);

	// Removing Colums or Rows
	virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow);
	virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol);

	// Moving Colums or Rows
	virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);

	// copy/move ranges in one step
	virtual BOOL StoreCopyCells(ROWCOL top,ROWCOL left,ROWCOL bottom,ROWCOL right , ROWCOL nRow, ROWCOL nCol);
	virtual BOOL StoreMoveCells(ROWCOL top,ROWCOL left,ROWCOL bottom,ROWCOL right, ROWCOL nRow, ROWCOL nCol);

	// Cell data
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXGridCellStyle* pStyle );
	BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXGridCellStyle& style );

	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXGridCellStyle& style );
	virtual CGXGridCellStyle* GetCaptionStyleRef( ROWCOL nRow, ROWCOL nCol ); 

	// Get Data
	virtual BOOL GetDataType ( ROWCOL nRow, ROWCOL nCol, CString& strValue, short nType );

	virtual BOOL GetSingleDataType ( CString& strValue, short nType );
	virtual void SetSingleDataType ( CString& strValue, short nType );
	virtual BOOL SetSingleDataChange ( CString  strValue,  short nType,  TCHAR chSep1, TCHAR chSep2 );
	virtual BOOL GetSingleDataChange ( CString&  strValue, short nType,  TCHAR chSep1, TCHAR chSep2 );
};


/////////////////////////////////////////////////////////////////////////////
// Inline function declarations
#ifdef _GX_ENABLE_INLINES
#include "gxGridCellStyle.inl"
#endif

#endif //_GXGRIDCELLSTYLE_H_
