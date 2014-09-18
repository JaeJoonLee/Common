#ifdef GX_INLINE

class CGXCaptionStyle;
class CGXCaptionStylePtrArray;
class CGXCaptionStylePtrArrayPtrArray;
class CGXCaptionData;


GX_INLINE CGXCaptionStyle::CGXCaptionStyle()
	{ ConstructStyle(); }

GX_INLINE CGXCaptionStyle::STYLEBITS::STYLEBITS(DWORD dw)
	{ SetPortable(dw); }

GX_INLINE DWORD CGXCaptionStyle::STYLEBITS::GetNoPortableBits() const
	{ return *((DWORD*) this); } 

GX_INLINE void CGXCaptionStyle::STYLEBITS::SetNoPortableBits(DWORD dw) 
	{ *((DWORD*) this) = dw; }

GX_INLINE BOOL CGXCaptionStyle::STYLEBITS::NoPortableIsEmptyBits() const 
	{ return GetNoPortableBits() == 0; }

GX_INLINE BOOL CGXCaptionStyle::GetDataValue( short nDataType ,CString& strValue ) const
{
	switch ( nDataType )
	{
		case dxDataType_Value:				// Caption Value
			if ( stylebits.value && m_lpszValue )
			{
				strValue = m_lpszValue;
				return TRUE;
			}
			break;
		case dxDataType_MultiCaption:			// Multi Caption
			if ( stylebits.multicaption )
			{
				strValue = m_strMultiCaption;
				return TRUE;
			}
			break;
		case dxDataType_MultiTooltip:			// MultiTooltip
			if ( stylebits.tooltip )
			{
				strValue = m_strMultiTooltip;
				return TRUE;
			}
			break;
		case dxDataType_MultiChoiceList:		// MultiChoiceList
			if ( stylebits.choicelist )
			{
				strValue = m_strMultiChoiceList;
				return TRUE;
			}
			break;
		case dxDataType_ItemName:				// Item Name
			if ( stylebits.item )
			{
				strValue = m_strItemName;
				return TRUE;
			}
			break;
		case dxDataType_RecordName:				// Record Name
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
GX_INLINE BOOL CGXCaptionStyle::GetIncludeCaptionValue() const
	{ return stylebits.value; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetIncludeCaptionValue(BOOL b)
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

GX_INLINE LPCTSTR CGXCaptionStyle::GetCaptionValueBuf() const
	{   return m_lpszValue; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetCaptionValue(LPCTSTR s, short nLen /*= -1*/)
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
			return CGXCaptionStyle::SetIncludeCaptionValue(TRUE); 
		}

		return CGXCaptionStyle::SetIncludeCaptionValue(FALSE); 
	}

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetCaptionValue(const CString& s)
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
			return CGXCaptionStyle::SetIncludeCaptionValue(TRUE); 
		}
		return CGXCaptionStyle::SetIncludeCaptionValue(FALSE); 
	}

//      I have already tried to use a pointer instead of CString
//      { delete m_pszValue; m_pszValue = new char [strlen(s)+1]; _tcscpy(m_pszValue, s); return CGXCaptionStyle::SetIncludeValue(TRUE); }
//      But, this is not much faster, so I continued to use CString for the value

#ifdef _UNICODE
// special UNICODE version of SetValue will convert ansi characters
// to wide characters.
GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetCaptionValue(const char* s)
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
			return CGXCaptionStyle::SetIncludeCaptionValue(TRUE); 
		}
		return CGXCaptionStyle::SetIncludeCaptionValue(FALSE); 
	}
#endif

// MultiCaption
GX_INLINE BOOL CGXCaptionStyle::GetIncludeMultiCaptionValue() const
	{ return stylebits.multicaption; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetIncludeMultiCaptionValue(BOOL b)
	{ stylebits.multicaption = (unsigned) b; return *this; }

GX_INLINE const CString& CGXCaptionStyle::GetMultiCaptionValue() const
	{   ASSERT(GetIncludeMultiCaptionValue());
		// ASSERTION-> 
		return m_strMultiCaption; }

GX_INLINE const CString& CGXCaptionStyle::GetMultiCaptionValueRef() const
	{   ASSERT(GetIncludeMultiCaptionValue());
		// ASSERTION-> 
		return m_strMultiCaption; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetMultiCaptionValue(LPCTSTR s)
	{ m_strMultiCaption = s; return CGXCaptionStyle::SetIncludeMultiCaptionValue(TRUE); }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetMultiCaptionValue(const CString& s)
	{ m_strMultiCaption = s; return CGXCaptionStyle::SetIncludeMultiCaptionValue(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetMultiCaptionValue(const char* s)
	{ m_strMultiCaption = s; return CGXCaptionStyle::SetIncludeMultiCaptionValue(TRUE); }

#endif


// Item Name
GX_INLINE BOOL CGXCaptionStyle::GetIncludeItemNameValue() const
	{ return stylebits.item; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetIncludeItemNameValue(BOOL b)
	{ stylebits.item = (unsigned) b; return *this; }

GX_INLINE const CString& CGXCaptionStyle::GetItemNameValue() const
	{   ASSERT(GetIncludeItemNameValue());
		// ASSERTION-> 
		return m_strItemName; }

GX_INLINE const CString& CGXCaptionStyle::GetItemNameValueRef() const
	{   ASSERT(GetIncludeItemNameValue());
		// ASSERTION-> 
		return m_strItemName; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetItemNameValue(LPCTSTR s)
	{ m_strItemName = s; return CGXCaptionStyle::SetIncludeItemNameValue(TRUE); }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetItemNameValue(const CString& s)
	{ m_strItemName = s; return CGXCaptionStyle::SetIncludeItemNameValue(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetItemNameValue(const char* s)
	{ m_strItemName = s; return CGXCaptionStyle::SetIncludeItemNameValue(TRUE); }

#endif



// Record Name
GX_INLINE BOOL CGXCaptionStyle::GetIncludeRecordNameValue() const
	{ return stylebits.recordname; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetIncludeRecordNameValue(BOOL b)
	{ stylebits.recordname = (unsigned) b; return *this; }

GX_INLINE const CString& CGXCaptionStyle::GetRecordNameValue() const
	{   ASSERT(GetIncludeRecordNameValue());
		// ASSERTION-> 
		return m_strRecordName; }

GX_INLINE const CString& CGXCaptionStyle::GetRecordNameValueRef() const
	{   ASSERT(GetIncludeRecordNameValue());
		// ASSERTION-> 
		return m_strRecordName; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetRecordNameValue(LPCTSTR s)
	{ m_strRecordName = s; return CGXCaptionStyle::SetIncludeRecordNameValue(TRUE); }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetRecordNameValue(const CString& s)
	{ m_strRecordName = s; return CGXCaptionStyle::SetIncludeRecordNameValue(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetRecordNameValue(const char* s)
	{ m_strRecordName = s; return CGXCaptionStyle::SetIncludeRecordNameValue(TRUE); }

#endif


// Tooltip Caption
GX_INLINE BOOL CGXCaptionStyle::GetIncludeMultiTooltipValue() const
	{ return stylebits.tooltip; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetIncludeMultiTooltipValue(BOOL b)
	{ stylebits.tooltip = (unsigned) b; return *this; }

GX_INLINE const CString& CGXCaptionStyle::GetMultiTooltipValue() const
	{   ASSERT(GetIncludeMultiTooltipValue());
		// ASSERTION-> 
		return m_strMultiTooltip; }

GX_INLINE const CString& CGXCaptionStyle::GetMultiTooltipValueRef() const
	{   ASSERT(GetIncludeMultiTooltipValue());
		// ASSERTION-> 
		return m_strMultiTooltip; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetMultiTooltipValue(LPCTSTR s)
	{ m_strMultiTooltip = s; return CGXCaptionStyle::SetIncludeMultiTooltipValue(TRUE); }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetMultiTooltipValue(const CString& s)
	{ m_strMultiTooltip = s; return CGXCaptionStyle::SetIncludeMultiTooltipValue(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetMultiTooltipValue(const char* s)
	{ m_strMultiTooltip = s; return CGXCaptionStyle::SetIncludeMultiTooltipValue(TRUE); }

#endif


// Choice list: each choice is separated with a new newline
GX_INLINE BOOL CGXCaptionStyle::GetIncludeMultiChoiceListValue() const
	{ return stylebits.choicelist; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetIncludeMultiChoiceListValue(BOOL b)
	{ stylebits.choicelist = (unsigned) b; return *this; }

GX_INLINE const CString& CGXCaptionStyle::GetMultiChoiceListValue() const
	{   ASSERT(GetIncludeMultiChoiceListValue());
		// ASSERTION-> // Did you check CGXCaptionStyle::GetInclude...? ->END
		return m_strMultiChoiceList; }

GX_INLINE const CString& CGXCaptionStyle::GetMultiChoiceListValueRef() const
	{   ASSERT(GetIncludeMultiChoiceListValue());
		// ASSERTION-> // Did you check CGXCaptionStyle::GetInclude...? ->END
		return m_strMultiChoiceList; }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetMultiChoiceListValue(LPCTSTR s)
	{ m_strMultiChoiceList = s; return CGXCaptionStyle::SetIncludeMultiChoiceListValue(TRUE); }

GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetMultiChoiceListValue(const CString& s)
	{ m_strMultiChoiceList = s; return CGXCaptionStyle::SetIncludeMultiChoiceListValue(TRUE); }

#ifdef _UNICODE

	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
GX_INLINE CGXCaptionStyle& CGXCaptionStyle::SetMultiChoiceListValue(const char* s)
	{ m_strMultiChoiceList = s; return CGXCaptionStyle::SetIncludeMultiChoiceListValue(TRUE); }

#endif



// StyleBit
GX_INLINE DWORD CGXCaptionStyle::GetStyleBits() const
	{ return stylebits.GetPortable(); }


/////////////////////////////////////////////////////////////////////////////
// class CGXCaptionStylePtrArray

GX_INLINE CGXCaptionStylePtrArray::CGXCaptionStylePtrArray()
	{ };

GX_INLINE CGXCaptionStylePtrArray::CGXCaptionStylePtrArray(const CGXCaptionStylePtrArray& other)
	{ operator=(other); };

GX_INLINE CGXCaptionStyle* CGXCaptionStylePtrArray::GetAt(int nIndex) const
	{ return (CGXCaptionStyle*) CPtrArray::GetAt(nIndex); }

GX_INLINE void CGXCaptionStylePtrArray::SetAt(int nIndex, CGXCaptionStyle* newElement)
	{ CPtrArray::SetAt(nIndex, newElement); }

	// Potentially growing the array
GX_INLINE void CGXCaptionStylePtrArray::SetAtGrow(int nIndex, CGXCaptionStyle* newElement)
	{ CPtrArray::SetAtGrow(nIndex, newElement); }

GX_INLINE int CGXCaptionStylePtrArray::Add(CGXCaptionStyle* newElement)
	{ return (int)CPtrArray::Add(newElement); }

	// overloaded operator helpers
GX_INLINE CGXCaptionStyle* CGXCaptionStylePtrArray::operator[](int nIndex) const
	{ return (CGXCaptionStyle*) CPtrArray::operator[](nIndex); }

GX_INLINE CGXCaptionStyle*& CGXCaptionStylePtrArray::operator[](int nIndex)
	{ return (CGXCaptionStyle*&) CPtrArray::operator[](nIndex); }

	// Operations that move elements around
GX_INLINE void CGXCaptionStylePtrArray::InsertAt(int nIndex, CGXCaptionStyle* newElement, int nCount)
	{ CPtrArray::InsertAt(nIndex, newElement, nCount); }

GX_INLINE void CGXCaptionStylePtrArray::InsertAt(int nStartIndex, CGXCaptionStylePtrArray* pNewArray)
	{ CPtrArray::InsertAt(nStartIndex, pNewArray); }

/////////////////////////////////////////////////////////////////////////////
// class CGXCaptionStylePtrArrayPtrArray

GX_INLINE CGXCaptionStylePtrArrayPtrArray::CGXCaptionStylePtrArrayPtrArray()
	{ };

GX_INLINE CGXCaptionStylePtrArrayPtrArray::CGXCaptionStylePtrArrayPtrArray(const CGXCaptionStylePtrArrayPtrArray& other)
	{ operator=(other); };

GX_INLINE CGXCaptionStylePtrArray* CGXCaptionStylePtrArrayPtrArray::GetAt(int nIndex) const
	{ return (CGXCaptionStylePtrArray*) CPtrArray::GetAt(nIndex); }

GX_INLINE void CGXCaptionStylePtrArrayPtrArray::SetAt(int nIndex, CGXCaptionStylePtrArray* newElement)
	{ CPtrArray::SetAt(nIndex, newElement); }

	// Potentially growing the array
GX_INLINE void CGXCaptionStylePtrArrayPtrArray::SetAtGrow(int nIndex, CGXCaptionStylePtrArray* newElement)
	{ CPtrArray::SetAtGrow(nIndex, newElement); }

GX_INLINE int CGXCaptionStylePtrArrayPtrArray::Add(CGXCaptionStylePtrArray* newElement)
	{ return (int)CPtrArray::Add(newElement); }

	// overloaded operator helpers
GX_INLINE CGXCaptionStylePtrArray* CGXCaptionStylePtrArrayPtrArray::operator[](int nIndex) const
	{ return (CGXCaptionStylePtrArray*) CPtrArray::operator[](nIndex); }

GX_INLINE CGXCaptionStylePtrArray*& CGXCaptionStylePtrArrayPtrArray::operator[](int nIndex)
	{ return (CGXCaptionStylePtrArray*&) CPtrArray::operator[](nIndex); }

	// Operations that move elements around
GX_INLINE void CGXCaptionStylePtrArrayPtrArray::InsertAt(int nIndex, CGXCaptionStylePtrArray* newElement, int nCount)
	{ CPtrArray::InsertAt(nIndex, newElement, nCount); }

GX_INLINE void CGXCaptionStylePtrArrayPtrArray::InsertAt(int nStartIndex, CGXCaptionStylePtrArrayPtrArray* pNewArray)
	{ CPtrArray::InsertAt(nStartIndex, pNewArray); }

/////////////////////////////////////////////////////////////////////////////
// class CGXCaptionData
GX_INLINE BOOL CGXCaptionData::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXCaptionStyle& style )
{
	return StoreStyleRowCol(nRow, nCol, &style );
}

#endif // GX_INLINE

