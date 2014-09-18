#ifndef _GXCAPTIONSTLE_H_
#define _GXCAPTIONSTLE_H_

#ifdef MULTI_CAPTION_USE		// 다국어 사용옵션 

enum DxCaptionDataType	//
{
	dxDataType_Value				= 0,// Caption Value
	dxDataType_MultiCaption,			// Multi Caption
	dxDataType_MultiTooltip,			// MultiTooltip
	dxDataType_MultiChoiceList,			// MultiChoiceList
	dxDataType_ItemName,				// Item Name
	dxDataType_RecordName,				// Record Name
};


typedef DWORD           ROWCOL;
#define US				(BYTE)0x1F		// Unit Separator


// Caption style
class CGXCaptionStyle : public CObject
{
	DECLARE_SERIAL(CGXCaptionStyle)	
public:
	// operations
	CGXCaptionStyle();
	CGXCaptionStyle(const CGXCaptionStyle& p);

	virtual ~CGXCaptionStyle();

	virtual CGXCaptionStyle* Clone() const;// create a new style with "new CGXCaptionStyle(*this);"

	virtual const CGXCaptionStyle& operator=(const CGXCaptionStyle& p);

	virtual CGXCaptionStyle& SetDefault();

	virtual void Serialize(CArchive& ar);
	virtual void ChangeStyle(const CGXCaptionStyle& p );

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
	
	CGXCaptionStyle& SetMultiLangDataValue( short nDataType ,CString strValue);

	// Caption
	BOOL GetIncludeCaptionValue() const;
	CGXCaptionStyle& SetIncludeCaptionValue(BOOL b);
	LPCTSTR GetCaptionValueBuf() const;
	
	CGXCaptionStyle& SetCaptionValue(LPCTSTR s, short nLen = -1);
	CGXCaptionStyle& SetCaptionValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetValue will convert ansi characters
	// to wide characters.
	CGXCaptionStyle& SetCaptionValue(const char* s);
#endif
	
	// MultiCaption
	BOOL GetIncludeMultiCaptionValue() const;
	CGXCaptionStyle& SetIncludeMultiCaptionValue(BOOL b);
	const CString& GetMultiCaptionValue() const;
	const CString& GetMultiCaptionValueRef() const;

	CGXCaptionStyle& SetMultiCaptionValue(LPCTSTR s);
	CGXCaptionStyle& SetMultiCaptionValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXCaptionStyle& SetMultiCaptionValue(const char* s);
#endif
	
	// MultiChoice list: each choice is separated with a new newline
	BOOL GetIncludeMultiChoiceListValue() const;
	CGXCaptionStyle& SetIncludeMultiChoiceListValue(BOOL b);
	const CString& GetMultiChoiceListValue() const;
	const CString& GetMultiChoiceListValueRef() const;
	CGXCaptionStyle& SetMultiChoiceListValue(LPCTSTR s);
	CGXCaptionStyle& SetMultiChoiceListValue(const CString& s);

#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXCaptionStyle& SetMultiChoiceListValue(const char* s);
#endif

	// Item Name
	BOOL GetIncludeItemNameValue() const;
	CGXCaptionStyle& SetIncludeItemNameValue(BOOL b);
	const CString& GetItemNameValue() const;
	const CString& GetItemNameValueRef() const;
	CGXCaptionStyle& SetItemNameValue(LPCTSTR s);
	CGXCaptionStyle& SetItemNameValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXCaptionStyle& SetItemNameValue(const char* s);
#endif

	// Record Name
	BOOL GetIncludeRecordNameValue() const;
	CGXCaptionStyle& SetIncludeRecordNameValue(BOOL b);
	const CString& GetRecordNameValue() const;
	const CString& GetRecordNameValueRef() const;
	CGXCaptionStyle& SetRecordNameValue(LPCTSTR s);
	CGXCaptionStyle& SetRecordNameValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXCaptionStyle& SetRecordNameValue(const char* s);
#endif

	// Tooltip Caption
	BOOL GetIncludeMultiTooltipValue() const;
	CGXCaptionStyle& SetIncludeMultiTooltipValue(BOOL b);
	const CString& GetMultiTooltipValue() const;
	const CString& GetMultiTooltipValueRef() const;
	CGXCaptionStyle& SetMultiTooltipValue(LPCTSTR s);
	CGXCaptionStyle& SetMultiTooltipValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXCaptionStyle& SetMultiTooltipValue(const char* s);
#endif
	

public:
// Implementation
	DWORD GetStyleBits() const;

};


class CGXCaptionStylePtrArray: public CPtrArray
{
	DECLARE_DYNAMIC(CGXCaptionStylePtrArray)

public:
	// Construcion/Destruction
	CGXCaptionStylePtrArray();
	CGXCaptionStylePtrArray(const CGXCaptionStylePtrArray& other);
	virtual ~CGXCaptionStylePtrArray();
		// destructor automatically deletes all referenced objects

	const CGXCaptionStylePtrArray& operator=(const CGXCaptionStylePtrArray& other);

	void DeleteAll(); // delete all referenced objects
	void DeleteAt(int nIndex, int nCount = 1);
	void Move(int nIndex, int nCount, int nDest);

	virtual void Serialize(CArchive& ar);

public:
	// Accessing elements
	CGXCaptionStyle* GetAt(int nIndex) const;
	void SetAt(int nIndex, CGXCaptionStyle* newElement);

	// Potentially growing the array
	void SetAtGrow(int nIndex, CGXCaptionStyle* newElement);
	int Add(CGXCaptionStyle* newElement);

	// overloaded operator helpers
	CGXCaptionStyle* operator[](int nIndex) const;
	CGXCaptionStyle*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, CGXCaptionStyle* newElement, int nCount = 1);
	void InsertAt(int nStartIndex, CGXCaptionStylePtrArray* pNewArray);
};

// type-safe CPtrArray for array with CGXCaptionStylePtrArray objects

class CGXCaptionStylePtrArrayPtrArray: public CPtrArray
{
	DECLARE_DYNAMIC(CGXCaptionStylePtrArrayPtrArray)

public:
	// Construcion/Destruction
	CGXCaptionStylePtrArrayPtrArray();
	CGXCaptionStylePtrArrayPtrArray(const CGXCaptionStylePtrArrayPtrArray& other);
	virtual ~CGXCaptionStylePtrArrayPtrArray();
		// destructor automatically deletes all referenced objects

	const CGXCaptionStylePtrArrayPtrArray& operator=(const CGXCaptionStylePtrArrayPtrArray& other);

	void DeleteAll(); // delete all referenced objects
	void DeleteAt(int nIndex, int nCount = 1);
	void Move(int nIndex, int nCount, int nDest);

	virtual void Serialize(CArchive& ar);

public:
	// Accessing elements
	CGXCaptionStylePtrArray* GetAt(int nIndex) const;
	void SetAt(int nIndex, CGXCaptionStylePtrArray* newElement);

	// Potentially growing the array
	void SetAtGrow(int nIndex, CGXCaptionStylePtrArray* newElement);
	int Add(CGXCaptionStylePtrArray* newElement);

	// overloaded operator helpers
	CGXCaptionStylePtrArray* operator[](int nIndex) const;
	CGXCaptionStylePtrArray*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, CGXCaptionStylePtrArray* newElement, int nCount = 1);
	void InsertAt(int nStartIndex, CGXCaptionStylePtrArrayPtrArray* pNewArray);
};

class CGXCaptionData: public CObject
{
	DECLARE_SERIAL(CGXCaptionData)

public:
	// operations
	CGXCaptionData();
	virtual ~CGXCaptionData();
	virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);
	

	virtual const CGXCaptionData& operator=(const CGXCaptionData& p);
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

	CGXCaptionStylePtrArrayPtrArray m_apapCellStyle; // spans the cell matrix,
												// CGXCaptionStylePtrArray elements are rows
												// which CGXCaptionStyle elements are styles
	CGXCaptionStyle* m_pDefCaptionStyle;

public:
	static CString m_strValueCache;	// Value to be used for converting into a string in GetValue
// Access member functions
	const CString& GetMultiLangData ( CString strValue , BOOL& bRet , WORD wLangCode , TCHAR chSep ) const;

	BOOL  SetSingleMultiLangData ( CString strValue , short nType, WORD wCurLangCode );
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
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXCaptionStyle* pStyle );
	BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXCaptionStyle& style );
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXCaptionStyle& style );
	virtual CGXCaptionStyle* GetCaptionStyleRef( ROWCOL nRow, ROWCOL nCol ); 

	// Get Data
	virtual BOOL GetDataType ( ROWCOL nRow, ROWCOL nCol, CString& strValue, short nType );
	virtual BOOL GetLangData ( ROWCOL nRow, ROWCOL nCol, CString& strValue, short nType , WORD wLangCode = LANG_ENGLISH , TCHAR chSep = US );
	virtual BOOL GetSingleDataType ( CString& strValue, short nType );
	virtual void SetSingleDataType ( CString& strValue, short nType );
	virtual BOOL SetSingleDataChange ( CString  strValue,  short nType,  TCHAR chSep1, TCHAR chSep2 );
	virtual BOOL GetSingleDataChange ( CString&  strValue, short nType,  TCHAR chSep1, TCHAR chSep2 );

	virtual BOOL GetSingleLangData ( CString& strValue, short nType , WORD wLangCode = LANG_ENGLISH , TCHAR chSep = US );

	BOOL    SetDefaultCaptionChange ( WORD wLangCode = LANG_ENGLISH, TCHAR chSep = US );
};


/////////////////////////////////////////////////////////////////////////////
// Inline function declarations
#ifdef _GX_ENABLE_INLINES
#include "gxcaptionstyle.inl"
#endif

#endif

#endif //_GXCAPTIONSTLE_H_
