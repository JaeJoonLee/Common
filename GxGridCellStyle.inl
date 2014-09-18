#ifdef GX_INLINE

class CGXGridCellStyle;
class CGXGridCellStylePtrArray;
class CGXGridCellStylePtrArrayPtrArray;
class CGXGridCellData;


GX_INLINE CGXGridCellStyle::CGXGridCellStyle()
	{ ConstructStyle(); }

GX_INLINE CGXGridCellStyle::STYLEBITS::STYLEBITS(DWORD dw)
	{ SetPortable(dw); }

GX_INLINE DWORD CGXGridCellStyle::STYLEBITS::GetNoPortableBits() const
	{ return *((DWORD*) this); } 

GX_INLINE void CGXGridCellStyle::STYLEBITS::SetNoPortableBits(DWORD dw) 
	{ *((DWORD*) this) = dw; }

GX_INLINE BOOL CGXGridCellStyle::STYLEBITS::NoPortableIsEmptyBits() const 
	{ return GetNoPortableBits() == 0; }

GX_INLINE BOOL CGXGridCellStyle::GetDataValue( short nDataType ,CString& strValue ) const
{
	switch ( nDataType )
	{
		case dxGridDataType_Value:					// Caption Value
			if ( stylebits.value && m_lpszValue )
			{
				strValue = m_lpszValue;
				return TRUE;
			}
			break;
		case dxGridDataType_MultiCaption:			// Multi Caption
			if ( stylebits.multicaption )
			{
				strValue = m_strMultiCaption;
				return TRUE;
			}
			break;
		case dxGridDataType_MultiTooltip:			// MultiTooltip
			if ( stylebits.tooltip )
			{
				strValue = m_strMultiTooltip;
				return TRUE;
			}
			break;
		case dxGridDataType_MultiChoiceList:		// MultiChoiceList
			if ( stylebits.choicelist )
			{
				strValue = m_strMultiChoiceList;
				return TRUE;
			}
			break;
		case dxGridDataType_ItemName:				// Item Name
			if ( stylebits.item )
			{
				strValue = m_strItemName;
				return TRUE;
			}
			break;
		case dxGridDataType_RecordName:				// Record Name
			if ( stylebits.recordname )
			{
				strValue = m_strRecordName;
				return TRUE;
			}
			break;
		default:
			break;
	}
	return FALSE;	
}



// Caption Value
GX_INLINE BOOL CGXGridCellStyle::GetIncludeCaptionValue() const
	{ return stylebits.value; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetIncludeCaptionValue(BOOL b)
	{ 
		stylebits.value = (unsigned) b; 
		if (!b) 
		{
			//m_sValue.Empty();
			if(m_lpszValue)
				*m_lpszValue = 0x00;
		}
		return *this; 
	}

GX_INLINE LPCTSTR CGXGridCellStyle::GetCaptionValueBuf() const
	{   return m_lpszValue; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetCaptionValue(LPCTSTR s, short nLen /*= -1*/)
	{ 
		ASSERT(s);
		if(m_lpszValue)
		{
			delete m_lpszValue;
			m_lpszValue = NULL;
		}

		if( nLen == -1)
			nLen = lstrlen(s);
		
		if ( nLen > 0 )
		{
			m_lpszValue = new char[nLen+1];
			memcpy(m_lpszValue, s, nLen);
			m_lpszValue[nLen] = 0x00;
			return CGXGridCellStyle::SetIncludeCaptionValue(TRUE); 
		}

		return CGXGridCellStyle::SetIncludeCaptionValue(FALSE); 
	}

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetCaptionValue(const CString& s)
	{ 
		ASSERT(s);
		if(m_lpszValue)
		{
			delete m_lpszValue;
			m_lpszValue = NULL;
		}
		
		short nLen = s.GetLength();
		if ( nLen > 0 )
		{
			m_lpszValue = new char[nLen+1];
			memcpy(m_lpszValue, (LPCTSTR)s, nLen);
			m_lpszValue[nLen] = 0x00;
			return CGXGridCellStyle::SetIncludeCaptionValue(TRUE); 
		}
		return CGXGridCellStyle::SetIncludeCaptionValue(FALSE); 
	}

//      I have already tried to use a pointer instead of CString
//      { delete m_pszValue; m_pszValue = new char [strlen(s)+1]; _tcscpy(m_pszValue, s); return CGXGridCellStyle::SetIncludeValue(TRUE); }
//      But, this is not much faster, so I continued to use CString for the value

#ifdef _UNICODE
// special UNICODE version of SetValue will convert ansi characters
// to wide characters.
GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetCaptionValue(const char* s)
	{
		ASSERT(s);
		if(m_lpszValue)
		{
			delete m_lpszValue;
			m_lpszValue = NULL;
		}

		if( nLen == -1)
			nLen = lstrlen(s);
		if ( nLen > 0 )
		{
			m_lpszValue = new char[nLen+1];
			memcpy(m_lpszValue, s, nLen);
			m_lpszValue[nLen] = 0x00;
			return CGXGridCellStyle::SetIncludeCaptionValue(TRUE); 
		}
		return CGXGridCellStyle::SetIncludeCaptionValue(FALSE); 
	}
#endif

// MultiCaption
GX_INLINE BOOL CGXGridCellStyle::GetIncludeMultiCaptionValue() const
	{ return stylebits.multicaption; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetIncludeMultiCaptionValue(BOOL b)
	{ stylebits.multicaption = (unsigned) b; return *this; }

GX_INLINE const CString& CGXGridCellStyle::GetMultiCaptionValue() const
	{   ASSERT(GetIncludeMultiCaptionValue());
		// ASSERTION-> 
		return m_strMultiCaption; }

GX_INLINE const CString& CGXGridCellStyle::GetMultiCaptionValueRef() const
	{   ASSERT(GetIncludeMultiCaptionValue());
		// ASSERTION-> 
		return m_strMultiCaption; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetMultiCaptionValue(LPCTSTR s)
	{ m_strMultiCaption = s; return CGXGridCellStyle::SetIncludeMultiCaptionValue(TRUE); }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetMultiCaptionValue(const CString& s)
	{ m_strMultiCaption = s; return CGXGridCellStyle::SetIncludeMultiCaptionValue(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetMultiCaptionValue(const char* s)
	{ m_strMultiCaption = s; return CGXGridCellStyle::SetIncludeMultiCaptionValue(TRUE); }

#endif


// Item Name
GX_INLINE BOOL CGXGridCellStyle::GetIncludeItemNameValue() const
	{ return stylebits.item; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetIncludeItemNameValue(BOOL b)
	{ stylebits.item = (unsigned) b; return *this; }

GX_INLINE const CString& CGXGridCellStyle::GetItemNameValue() const
	{   ASSERT(GetIncludeItemNameValue());
		// ASSERTION-> 
		return m_strItemName; }

GX_INLINE const CString& CGXGridCellStyle::GetItemNameValueRef() const
	{   ASSERT(GetIncludeItemNameValue());
		// ASSERTION-> 
		return m_strItemName; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetItemNameValue(LPCTSTR s)
	{ m_strItemName = s; return CGXGridCellStyle::SetIncludeItemNameValue(TRUE); }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetItemNameValue(const CString& s)
	{ m_strItemName = s; return CGXGridCellStyle::SetIncludeItemNameValue(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetItemNameValue(const char* s)
	{ m_strItemName = s; return CGXGridCellStyle::SetIncludeItemNameValue(TRUE); }

#endif



// Record Name
GX_INLINE BOOL CGXGridCellStyle::GetIncludeRecordNameValue() const
	{ return stylebits.recordname; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetIncludeRecordNameValue(BOOL b)
	{ stylebits.recordname = (unsigned) b; return *this; }

GX_INLINE const CString& CGXGridCellStyle::GetRecordNameValue() const
	{   ASSERT(GetIncludeRecordNameValue());
		// ASSERTION-> 
		return m_strRecordName; }

GX_INLINE const CString& CGXGridCellStyle::GetRecordNameValueRef() const
	{   ASSERT(GetIncludeRecordNameValue());
		// ASSERTION-> 
		return m_strRecordName; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetRecordNameValue(LPCTSTR s)
	{ m_strRecordName = s; return CGXGridCellStyle::SetIncludeRecordNameValue(TRUE); }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetRecordNameValue(const CString& s)
	{ m_strRecordName = s; return CGXGridCellStyle::SetIncludeRecordNameValue(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetRecordNameValue(const char* s)
	{ m_strRecordName = s; return CGXGridCellStyle::SetIncludeRecordNameValue(TRUE); }

#endif


// Tooltip Caption
GX_INLINE BOOL CGXGridCellStyle::GetIncludeMultiTooltipValue() const
	{ return stylebits.tooltip; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetIncludeMultiTooltipValue(BOOL b)
	{ stylebits.tooltip = (unsigned) b; return *this; }

GX_INLINE const CString& CGXGridCellStyle::GetMultiTooltipValue() const
	{   ASSERT(GetIncludeMultiTooltipValue());
		// ASSERTION-> 
		return m_strMultiTooltip; }

GX_INLINE const CString& CGXGridCellStyle::GetMultiTooltipValueRef() const
	{   ASSERT(GetIncludeMultiTooltipValue());
		// ASSERTION-> 
		return m_strMultiTooltip; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetMultiTooltipValue(LPCTSTR s)
	{ m_strMultiTooltip = s; return CGXGridCellStyle::SetIncludeMultiTooltipValue(TRUE); }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetMultiTooltipValue(const CString& s)
	{ m_strMultiTooltip = s; return CGXGridCellStyle::SetIncludeMultiTooltipValue(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetMultiTooltipValue(const char* s)
	{ m_strMultiTooltip = s; return CGXGridCellStyle::SetIncludeMultiTooltipValue(TRUE); }

#endif


// Choice list: each choice is separated with a new newline
GX_INLINE BOOL CGXGridCellStyle::GetIncludeMultiChoiceListValue() const
	{ return stylebits.choicelist; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetIncludeMultiChoiceListValue(BOOL b)
	{ stylebits.choicelist = (unsigned) b; return *this; }

GX_INLINE const CString& CGXGridCellStyle::GetMultiChoiceListValue() const
	{   ASSERT(GetIncludeMultiChoiceListValue());
		// ASSERTION-> // Did you check CGXGridCellStyle::GetInclude...? ->END
		return m_strMultiChoiceList; }

GX_INLINE const CString& CGXGridCellStyle::GetMultiChoiceListValueRef() const
	{   ASSERT(GetIncludeMultiChoiceListValue());
		// ASSERTION-> // Did you check CGXGridCellStyle::GetInclude...? ->END
		return m_strMultiChoiceList; }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetMultiChoiceListValue(LPCTSTR s)
	{ m_strMultiChoiceList = s; return CGXGridCellStyle::SetIncludeMultiChoiceListValue(TRUE); }

GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetMultiChoiceListValue(const CString& s)
	{ m_strMultiChoiceList = s; return CGXGridCellStyle::SetIncludeMultiChoiceListValue(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXGridCellStyle& CGXGridCellStyle::SetMultiChoiceListValue(const char* s)
	{ m_strMultiChoiceList = s; return CGXGridCellStyle::SetIncludeMultiChoiceListValue(TRUE); }

#endif



// StyleBit
GX_INLINE DWORD CGXGridCellStyle::GetStyleBits() const
	{ return stylebits.GetPortable(); }


/////////////////////////////////////////////////////////////////////////////
// class CGXGridCellStylePtrArray

GX_INLINE CGXGridCellStylePtrArray::CGXGridCellStylePtrArray()
	{ };

GX_INLINE CGXGridCellStylePtrArray::CGXGridCellStylePtrArray(const CGXGridCellStylePtrArray& other)
	{ operator=(other); };

GX_INLINE CGXGridCellStyle* CGXGridCellStylePtrArray::GetAt(int nIndex) const
	{ return (CGXGridCellStyle*) CPtrArray::GetAt(nIndex); }

GX_INLINE void CGXGridCellStylePtrArray::SetAt(int nIndex, CGXGridCellStyle* newElement)
	{ CPtrArray::SetAt(nIndex, newElement); }

	// Potentially growing the array
GX_INLINE void CGXGridCellStylePtrArray::SetAtGrow(int nIndex, CGXGridCellStyle* newElement)
	{ CPtrArray::SetAtGrow(nIndex, newElement); }

GX_INLINE int CGXGridCellStylePtrArray::Add(CGXGridCellStyle* newElement)
	{ return (int)CPtrArray::Add(newElement); }

	// overloaded operator helpers
GX_INLINE CGXGridCellStyle* CGXGridCellStylePtrArray::operator[](int nIndex) const
	{ return (CGXGridCellStyle*) CPtrArray::operator[](nIndex); }

GX_INLINE CGXGridCellStyle*& CGXGridCellStylePtrArray::operator[](int nIndex)
	{ return (CGXGridCellStyle*&) CPtrArray::operator[](nIndex); }

	// Operations that move elements around
GX_INLINE void CGXGridCellStylePtrArray::InsertAt(int nIndex, CGXGridCellStyle* newElement, int nCount)
	{ CPtrArray::InsertAt(nIndex, newElement, nCount); }

GX_INLINE void CGXGridCellStylePtrArray::InsertAt(int nStartIndex, CGXGridCellStylePtrArray* pNewArray)
	{ CPtrArray::InsertAt(nStartIndex, pNewArray); }

/////////////////////////////////////////////////////////////////////////////
// class CGXGridCellStylePtrArrayPtrArray

GX_INLINE CGXGridCellStylePtrArrayPtrArray::CGXGridCellStylePtrArrayPtrArray()
	{ };

GX_INLINE CGXGridCellStylePtrArrayPtrArray::CGXGridCellStylePtrArrayPtrArray(const CGXGridCellStylePtrArrayPtrArray& other)
	{ operator=(other); };

GX_INLINE CGXGridCellStylePtrArray* CGXGridCellStylePtrArrayPtrArray::GetAt(int nIndex) const
	{ return (CGXGridCellStylePtrArray*) CPtrArray::GetAt(nIndex); }

GX_INLINE void CGXGridCellStylePtrArrayPtrArray::SetAt(int nIndex, CGXGridCellStylePtrArray* newElement)
	{ CPtrArray::SetAt(nIndex, newElement); }

	// Potentially growing the array
GX_INLINE void CGXGridCellStylePtrArrayPtrArray::SetAtGrow(int nIndex, CGXGridCellStylePtrArray* newElement)
	{ CPtrArray::SetAtGrow(nIndex, newElement); }

GX_INLINE int CGXGridCellStylePtrArrayPtrArray::Add(CGXGridCellStylePtrArray* newElement)
	{ return (int)CPtrArray::Add(newElement); }

	// overloaded operator helpers
GX_INLINE CGXGridCellStylePtrArray* CGXGridCellStylePtrArrayPtrArray::operator[](int nIndex) const
	{ return (CGXGridCellStylePtrArray*) CPtrArray::operator[](nIndex); }

GX_INLINE CGXGridCellStylePtrArray*& CGXGridCellStylePtrArrayPtrArray::operator[](int nIndex)
	{ return (CGXGridCellStylePtrArray*&) CPtrArray::operator[](nIndex); }

	// Operations that move elements around
GX_INLINE void CGXGridCellStylePtrArrayPtrArray::InsertAt(int nIndex, CGXGridCellStylePtrArray* newElement, int nCount)
	{ CPtrArray::InsertAt(nIndex, newElement, nCount); }

GX_INLINE void CGXGridCellStylePtrArrayPtrArray::InsertAt(int nStartIndex, CGXGridCellStylePtrArrayPtrArray* pNewArray)
	{ CPtrArray::InsertAt(nStartIndex, pNewArray); }

/////////////////////////////////////////////////////////////////////////////
// class CGXGridCellData
GX_INLINE BOOL CGXGridCellData::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXGridCellStyle& style )
{
	return StoreStyleRowCol(nRow, nCol, &style );
}

#endif // GX_INLINE

