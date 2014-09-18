// gxCaptiondata.cpp : implementation of the CGXCaptionData class
//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (ÁÖ)ÇÑ±¹¼Ò¸®¸¶Ä¡        
//******************************************************************
//  File Name     : GxCaptionData.cpp
//  Function      : 
//  System Name   : RunAccountCombo
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
#include "stdafx.h"

#ifdef MULTI_CAPTION_USE		// ´Ù±¹¾î »ç¿ë¿É¼Ç 

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifndef _GXCAPTIONSTYLE_H_
#include "gxcaptionstyle.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCAPTIONDATA")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CGXCaptionData, CObject, 0 /* schema number*/ )
IMPLEMENT_DYNAMIC(CGXCaptionStylePtrArray, CPtrArray)
IMPLEMENT_DYNAMIC(CGXCaptionStylePtrArrayPtrArray, CPtrArray)

// Convert
BYTE*		StringToBinaryEx( CString strOrg);
CString		BinaryToStringEx( BYTE* pData, int nDataLen);

#define new DEBUG_NEW

//******************************************************************
//  Function Name : m_strValueCache
//  Function      : »ý¼ºÀÚ
//  Param         : 
//  Return        : ¾øÀ½ 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CString CGXCaptionData::m_strValueCache;

/////////////////////////////////////////////////////////////////////////////
// class CGXCaptionStylePtrArray
//******************************************************************
//  Function Name : ~CGXCaptionStylePtrArray
//  Function      : ¼Ò¸êÀÚ
//  Param         : ¾øÀ½
//  Return        : ¾øÀ½ 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CGXCaptionStylePtrArray::~CGXCaptionStylePtrArray()
{
	DeleteAll();
}

//******************************************************************
//  Function Name : DeleteAll
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStylePtrArray::DeleteAll()
{
	for (int index = 0; index <= GetUpperBound(); index++)
		delete GetAt(index);

	RemoveAll();
}

//******************************************************************
//  Function Name : DeleteAt
//  Function      : 
//  Param         : int nIndex, int nCount
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStylePtrArray::DeleteAt(int nIndex, int nCount)
{
	int nUpper = min(GetUpperBound(), nIndex+nCount-1);
	if (nUpper >= nIndex)
	{
		for (int index = nIndex; index <= nUpper; index++)
			delete GetAt(index);

		RemoveAt(nIndex, nUpper-nIndex+1);
	}
}

//******************************************************************
//  Function Name : Move
//  Function      : 
//  Param         : int nIndex, int nCount, int nDest
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStylePtrArray::Move(int nIndex, int nCount, int nDest)
{
	if (nDest == nIndex || nCount == 0
		|| GetUpperBound() < nIndex && GetUpperBound() < nDest)
		return;
	else if (nDest < nIndex)
		nIndex += nCount;
	else if (nDest > nIndex)
		nDest += nCount;

	InsertAt(nDest, NULL, nCount);
	for (int n = 0; nIndex+n <= GetUpperBound() && n < nCount; n++)
	{
		if (GetAt(nIndex+n))
			SetAt(nDest+n, GetAt(nIndex+n));
	}

	if (nIndex <= GetUpperBound())
		RemoveAt(nIndex, min(nCount, GetUpperBound()-nIndex+1));
}

//******************************************************************
//  Function Name : operator
//  Function      : 
//  Param         : const CGXCaptionStylePtrArray& other
//  Return        : const 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
const CGXCaptionStylePtrArray& CGXCaptionStylePtrArray::operator=(const CGXCaptionStylePtrArray& other)
{
	if (&other == this)
		return *this;

	DeleteAll();

	SetSize(other.GetSize());
	for (int index = 0; index <= other.GetUpperBound(); index++)
	{
		CGXCaptionStyle* pStyle = other.GetAt(index);
		if (pStyle)
			SetAt(index, pStyle->Clone());
	}

	return *this;
}

//******************************************************************
//  Function Name : Serialize
//  Function      : 
//  Param         : CArchive& ar
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStylePtrArray::Serialize(CArchive& ar)
{
	// Serializes only existing elements,
	// e.g.  1 xxx 2 xxx 3 xxx 7 xxx 22 xxx DWORD_MAX,
	// where xxx is a CGXStyle object and DWORD_MAX identifies the end of serialization
	static const WORD wVersion = 1;
	WORD wActualVersion = wVersion;

	ASSERT_VALID(this);

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion != wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXCaptionStylePtrArray" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXCaptionStylePtrArray object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	const DWORD dwTerm = 0xFFFFFFFF;
	if (ar.IsStoring())
	{
		// storing
		DWORD dwSize = (DWORD) GetSize();
		ar << dwSize;
		for (int index = 0; index <= GetUpperBound(); index++)
		{
			CGXCaptionStyle* pStyle = GetAt(index);
			if (pStyle)
			{
				ar << (DWORD) index;
				pStyle->Serialize ( ar );
//				ar << pStyle;
			}
		}
		ar << dwTerm;
	}
	else
	{
		DeleteAll();

		DWORD dwSize;
		ar >> dwSize;

		SetSize((int) dwSize);

		DWORD dwIndex;
		ar >> dwIndex;

		while (dwIndex != dwTerm)
		{
//			CGXCaptionStyle* pStyle;
//			pStyle = NULL;
//			ar >> pStyle;

			CGXCaptionStyle* pStyle = new CGXCaptionStyle;
			pStyle->Serialize ( ar );

			SetAt((int) dwIndex, pStyle);

			// Next id
			ar >> dwIndex;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// class CGXCaptionStylePtrArrayPtrArray

//******************************************************************
//  Function Name : ~CGXCaptionStylePtrArrayPtrArray
//  Function      : ¼Ò¸êÀÚ
//  Param         : ¾øÀ½
//  Return        : ¾øÀ½ 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CGXCaptionStylePtrArrayPtrArray::~CGXCaptionStylePtrArrayPtrArray()
{
	DeleteAll();
}

//******************************************************************
//  Function Name : DeleteAt
//  Function      : 
//  Param         : int nIndex, int nCount
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStylePtrArrayPtrArray::DeleteAt(int nIndex, int nCount)
{
	int nUpper = min(GetUpperBound(), nIndex+nCount-1);
	if (nUpper >= nIndex)
	{
		for (int index = nIndex; index <= nUpper; index++)
			delete GetAt(index);

		RemoveAt(nIndex, nUpper-nIndex+1);
	}
}

//******************************************************************
//  Function Name : DeleteAll
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStylePtrArrayPtrArray::DeleteAll()
{
	for (int index = 0; index <= GetUpperBound(); index++)
		delete GetAt(index);

	RemoveAll();
}

//******************************************************************
//  Function Name : Move
//  Function      : 
//  Param         : int nIndex, int nCount, int nDest
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStylePtrArrayPtrArray::Move(int nIndex, int nCount, int nDest)
{
	if (nDest == nIndex || nCount == 0
		|| GetUpperBound() < nIndex && GetUpperBound() < nDest)
		return;
	else if (nDest < nIndex)
		nIndex += nCount;
	else if (nDest > nIndex)
		nDest += nCount;

	InsertAt(nDest, NULL, nCount);
	for (int n = 0; nIndex+n <= GetUpperBound() && n < nCount; n++)
	{
		if (GetAt(nIndex+n))
			SetAt(nDest+n, GetAt(nIndex+n));
	}

	if (nIndex <= GetUpperBound())
		RemoveAt(nIndex, min(nCount, GetUpperBound()-nIndex+1));
}

//******************************************************************
//  Function Name : operator
//  Function      : 
//  Param         : const CGXCaptionStylePtrArrayPtrArray& other
//  Return        : const 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
const CGXCaptionStylePtrArrayPtrArray& CGXCaptionStylePtrArrayPtrArray::operator=(const CGXCaptionStylePtrArrayPtrArray& other)
{
	if (&other == this)
		return *this;

	DeleteAll();

	SetSize(other.GetSize());
	for (int index = 0; index <= other.GetUpperBound(); index++)
	{
		if (other.GetAt(index))
			SetAt(index, new CGXCaptionStylePtrArray(*other.GetAt(index)));
	}

	return *this;
}

//******************************************************************
//  Function Name : Serialize
//  Function      : 
//  Param         : CArchive& ar
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStylePtrArrayPtrArray::Serialize(CArchive& ar)
{
	// Serializes only existing elements,
	// e.g.  1 xxx 2 xxx 3 xxx 7 xxx 22 xxx DWORD_MAX,
	// where xxx is a CGXCaptionStylePtrArray object and DWORD_MAX identifies the end of serialization

	static const WORD wVersion = 1;
	WORD wActualVersion = wVersion;

	ASSERT_VALID(this);

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion != wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXCaptionStylePtrArrayPtrArray " );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXCaptionStylePtrArrayPtrArray object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	const DWORD dwTerm = 0xFFFFFFFF;

	if (ar.IsStoring())
	{
		// storing

		DWORD dwSize = (DWORD)GetSize();
		ar << dwSize;
		for (int index = 0; index <= GetUpperBound(); index++)
		{
			CGXCaptionStylePtrArray* pStylePtrArray = GetAt(index);
			if (pStylePtrArray)
			{
				ar << (DWORD) index;
				pStylePtrArray->Serialize(ar);
			}
		}
		ar << dwTerm;
	}
	else
	{
		// loading

		DeleteAll();

		DWORD dwSize;
		ar >> dwSize;

		SetSize((int) dwSize);

		DWORD dwIndex;
		ar >> dwIndex;

		while (dwIndex != dwTerm)
		{
			CGXCaptionStylePtrArray* pStylePtrArray = new CGXCaptionStylePtrArray;
			pStylePtrArray->Serialize(ar);

			SetAt((int) dwIndex, pStylePtrArray);

			// Next id
			ar >> dwIndex;
		}
	}

}



/////////////////////////////////////////////////////////////////////////////
// class CGXCaptionData

//******************************************************************
//  Function Name : CGXCaptionData
//  Function      : »ý¼ºÀÚ
//  Param         : ¾øÀ½
//  Return        : ¾øÀ½ 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CGXCaptionData::CGXCaptionData()
{
	m_nRows = 0;
	m_nCols = 0;

	m_pDefCaptionStyle = NULL;		// Single style
	m_bSingleMode      = FALSE;
}

//******************************************************************
//  Function Name : SetSingleMode
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionData::SetSingleMode( )
{
	m_bSingleMode = TRUE;

	m_pDefCaptionStyle = new CGXCaptionStyle();
}

//******************************************************************
//  Function Name : ~CGXCaptionData
//  Function      : ¼Ò¸êÀÚ
//  Param         : ¾øÀ½
//  Return        : ¾øÀ½ 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CGXCaptionData::~CGXCaptionData()
{
	DeleteContents();

	if ( m_bSingleMode && m_pDefCaptionStyle )
		delete m_pDefCaptionStyle;
}

//******************************************************************
//  Function Name : DeleteContents
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionData::DeleteContents()
{
	if ( m_bSingleMode && m_pDefCaptionStyle )
	{
		m_pDefCaptionStyle->Free();
	}
	m_apapCellStyle.DeleteAll();
}

//******************************************************************
//  Function Name : operator
//  Function      : 
//  Param         : const CGXCaptionData& p
//  Return        : const 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
const CGXCaptionData& CGXCaptionData::operator=(const CGXCaptionData& p)
{
	if (&p == this)
		return *this;

	m_apapCellStyle = p.m_apapCellStyle;
	m_nRows = p.m_nRows;
	m_nCols = p.m_nCols;

	m_bSingleMode   = p.m_bSingleMode;
	m_apapCellStyle = p.m_apapCellStyle;

	return *this;
}

// Property Data-> Object Data Change
//******************************************************************
//  Function Name : SetMultiCaptionBlobDataChange 
//  Function      : 
//  Param         : CString  strPropertyData 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::SetMultiCaptionBlobDataChange ( CString  strPropertyData )
{
	DeleteContents();
	if ( strPropertyData.IsEmpty() )
	{
		return FALSE;
	}

	BYTE*	pvData = NULL;
	pvData = StringToBinaryEx( strPropertyData );
	ASSERT( pvData != NULL );
    if( pvData != NULL )
	{
		DWORD	dwDataLen;
		dwDataLen = *(long*)pvData;
		
		CMemFile memFile;
		memFile.Attach ( (BYTE*)pvData+sizeof(DWORD), dwDataLen - sizeof(DWORD) );
		
		CArchive arMem(&memFile, CArchive::load );
		Serialize ( arMem );

		free ( pvData );
		return TRUE;
	}
	return FALSE;
}

//******************************************************************
//  Function Name : GetMultiCaptionBlobDataChange 
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : CString 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CString CGXCaptionData::GetMultiCaptionBlobDataChange ( )
{
	CString strProperty;

	ASSERT_VALID(this);

//	if ( !m_bSingleMode )
//		DeleteContents();

	CMemFile  memFile;
	CArchive arMem(&memFile, CArchive::store );
	Serialize ( arMem );
	arMem.Flush();

	DWORD dwDataLen = memFile.GetLength();
	if ( dwDataLen > 0 )
	{
		BYTE *pTemp = new BYTE [dwDataLen+1];
		memFile.Seek(0, CFile::begin);
		memFile.Read(pTemp, dwDataLen );

		DWORD dwTotLen = 	dwDataLen + sizeof(DWORD);
		BYTE *pvData = new BYTE[dwTotLen];
		*(DWORD*)pvData = dwTotLen;
		memcpy ( pvData + sizeof(DWORD), pTemp, dwDataLen );
		if ( pTemp )
			delete[] pTemp;

		// Property Save CString
		strProperty = BinaryToStringEx ( pvData, dwTotLen );
		if ( pvData )
			delete[] pvData;
	}	

	return strProperty;
}

/////////////////////////////////////////////////////////////////////////////
// serialization
//******************************************************************
//  Function Name : SerializeEx
//  Function      : 
//  Param         : CArchive& ar, CString& strProperty 
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionData::SerializeEx(CArchive& ar, CString& strProperty )
{
	ASSERT_VALID(this);
	DWORD dwDataLen;
	if (ar.IsStoring())		// Write
	{
		CMemFile  memFile;
		CArchive  arMem(&memFile, CArchive::store );
		Serialize ( arMem );
		arMem.Flush();

		dwDataLen = memFile.GetLength();
		if ( dwDataLen > 0 )
		{
			BYTE *pTemp = new BYTE [dwDataLen+1];
			memFile.Seek(0, CFile::begin);
			memFile.Read(pTemp, dwDataLen );
		
			ar.Write(&dwDataLen, sizeof(DWORD));
			ar.Write(pTemp, dwDataLen);

			// Property Save CString
			strProperty = BinaryToStringEx ( pTemp, dwDataLen );

			if ( pTemp )
				delete []pTemp;
		}
	}
	else					// Read
	{
		ar >> dwDataLen;
		if ( dwDataLen > 0 )
		{
			BYTE *pTemp = new BYTE[dwDataLen+1];
			ar.Read(pTemp, dwDataLen );
			
			CMemFile memFile;
			memFile.Attach ( (BYTE*)pTemp, dwDataLen );

			CArchive arMem(&memFile, CArchive::load );
			Serialize ( arMem );

			// Property Save CString
			DWORD dwTotLen = 	dwDataLen + sizeof(DWORD);
			BYTE *pvData = new BYTE[dwTotLen];
			*(DWORD*)pvData = dwTotLen;
			memcpy ( pvData + sizeof(DWORD), pTemp, dwDataLen );
			
			if ( pTemp )
				delete[] pTemp;

			strProperty = BinaryToStringEx ( pvData, dwTotLen );
			if ( pvData )
				delete[] pvData;
		}
	}
}

//******************************************************************
//  Function Name : Serialize
//  Function      : 
//  Param         : CArchive& ar
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionData::Serialize(CArchive& ar)
{
	static const WORD wVersion = 1;
	WORD wActualVersion = wVersion;

	ASSERT_VALID(this);

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion != wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXCaptionData" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXData object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	if (ar.IsStoring())
	{
		if ( m_bSingleMode && m_pDefCaptionStyle )
		{
			m_pDefCaptionStyle->Serialize ( ar );
//			ar << m_pDefCaptionStyle;
			return;
		}
		ar << m_nRows,
		ar << m_nCols;
	}
	else
	{
		// loading
		if ( m_bSingleMode && m_pDefCaptionStyle )
		{
			m_pDefCaptionStyle->Serialize ( ar );
//			ar >> m_pDefCaptionStyle;
			return;
		}
		ar >> m_nRows,
		ar >> m_nCols;
	}

	m_apapCellStyle.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// Number of Rows and Colums

//******************************************************************
//  Function Name : GetRowCount
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : ROWCOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
ROWCOL CGXCaptionData::GetRowCount()
{
	return (ROWCOL) m_nRows;
}

//******************************************************************
//  Function Name : GetColCount
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : ROWCOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
ROWCOL CGXCaptionData::GetColCount()
{
	return (ROWCOL) m_nCols;
}

//******************************************************************
//  Function Name : SetRowCount
//  Function      : 
//  Param         : ROWCOL nRows 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::SetRowCount(ROWCOL nRows )
{
	TRACE("CGXCaptionData : BEGIN SetRowCount(%u)\n", nRows);

	ROWCOL nOldRows = GetRowCount();
	if (nRows < nOldRows)
		return StoreRemoveRows(nRows+1, nOldRows );
	else if (nRows > nOldRows)
		return StoreInsertRows(nOldRows+1, nRows-nOldRows );
	return TRUE;

}

//******************************************************************
//  Function Name : SetColCount
//  Function      : 
//  Param         : ROWCOL nCols 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::SetColCount(ROWCOL nCols )
{
	ROWCOL nOldCols = GetColCount();
	if (nCols < nOldCols)
		return StoreRemoveCols(nCols+1, nOldCols );
	else if (nCols > nOldCols)
		return StoreInsertCols(nOldCols+1, nCols-nOldCols );
	return TRUE;

}

//******************************************************************
//  Function Name : StoreRowCount
//  Function      : 
//  Param         : ROWCOL nRows
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreRowCount(ROWCOL nRows)
{
	if (nRows < m_nRows)
		StoreRemoveRows(nRows+1, m_nRows);
	else if (nRows > m_nRows)
		StoreInsertRows(m_nRows+1, nRows-m_nRows);
	return TRUE;
}

//******************************************************************
//  Function Name : StoreColCount
//  Function      : 
//  Param         : ROWCOL nCols
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreColCount(ROWCOL nCols)
{
	if (nCols < m_nCols)
		StoreRemoveCols(nCols+1, m_nCols);
	else if (nCols > m_nCols)
		StoreInsertCols(m_nCols+1, nCols-m_nCols);
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// Insert, Remove and Move Cells

//******************************************************************
//  Function Name : StoreInsertRows
//  Function      : 
//  Param         : ROWCOL nRow, ROWCOL nCount
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreInsertRows(ROWCOL nRow, ROWCOL nCount)
{
	ASSERT(nRow <= INT_MAX && nCount <= INT_MAX);

	int row = (int) nRow;
	int count = (int) nCount;

	m_apapCellStyle.InsertAt(row, NULL, count);
	
	m_nRows += nCount;

	return TRUE;
}

//******************************************************************
//  Function Name : StoreInsertCols
//  Function      : 
//  Param         : ROWCOL nCol, ROWCOL nCount
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreInsertCols(ROWCOL nCol, ROWCOL nCount)
{
	ASSERT(nCol <= INT_MAX && nCount <= INT_MAX);

	int col = (int) nCol;
	int count = (int) nCount;

	// insert columns for each row
	int nDataCount = m_apapCellStyle.GetUpperBound();
	for (int row = 0; row <= nDataCount; row++)
	{
		if (m_apapCellStyle.GetAt(row))
			m_apapCellStyle.GetAt(row)->InsertAt(col, NULL, count);
	}
	m_nCols += nCount;

	return TRUE;
}


//******************************************************************
//  Function Name : StoreRemoveRows
//  Function      : 
//  Param         : ROWCOL nFromRow, ROWCOL nToRow
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow)
{
	ASSERT(nFromRow <= INT_MAX && nToRow <= INT_MAX);

	if (nFromRow > m_nRows)
		return TRUE;

	int row = (int) nFromRow;
	int count = (int) (nToRow-nFromRow+1);

	m_apapCellStyle.DeleteAt(row, count);

	m_nRows -= min(nToRow-nFromRow+1, m_nRows);

	return TRUE;
}


//******************************************************************
//  Function Name : StoreRemoveCols
//  Function      : 
//  Param         : ROWCOL nFromCol, ROWCOL nToCol
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol)
{
	ASSERT(nFromCol <= INT_MAX && nToCol <= INT_MAX);

	if (nFromCol > m_nCols)
		return TRUE;

	int col = (int) nFromCol;
	int count = (int) (nToCol-nFromCol+1);

	// delete columns for each row
	int nDataCount = m_apapCellStyle.GetUpperBound();
	for (int row = 0; row <= nDataCount; row++)
	{
		if (m_apapCellStyle.GetAt(row))
			m_apapCellStyle.GetAt(row)->DeleteAt(col, count);
	}

	m_nCols -= min(nToCol-nFromCol+1, m_nCols);

	return TRUE;
}

//******************************************************************
//  Function Name : StoreMoveRows
//  Function      : 
//  Param         : ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow)
{
	ASSERT(nFromRow <= INT_MAX && nToRow <= INT_MAX && nDestRow <= INT_MAX);

	int row = (int) nFromRow;
	int count = (int) (nToRow-nFromRow+1);
	int dest = (int) nDestRow;

	m_apapCellStyle.Move(row, count, dest);

	return TRUE;
}

//******************************************************************
//  Function Name : StoreMoveCols
//  Function      : 
//  Param         : ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol)
{
	ASSERT(nFromCol <= INT_MAX && nToCol <= INT_MAX && nDestCol <= INT_MAX);

	int col = (int) nFromCol;
	int count = (int) (nToCol-nFromCol+1);
	int dest = (int) nDestCol;

	// move columns for each row
	for (int row = 0; row <= m_apapCellStyle.GetUpperBound(); row++)
	{
		if (m_apapCellStyle.GetAt(row))
			m_apapCellStyle.GetAt(row)->Move(col, count, dest);
	}

	return TRUE;
}

//******************************************************************
//  Function Name : StoreCopyCells
//  Function      : 
//  Param         : ROWCOL top,ROWCOL left,ROWCOL bottom,ROWCOL right, ROWCOL nRow, ROWCOL nCol
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreCopyCells(ROWCOL top,ROWCOL left,ROWCOL bottom,ROWCOL right, ROWCOL nRow, ROWCOL nCol)
{

	return FALSE;
}

//******************************************************************
//  Function Name : StoreMoveCells
//  Function      : 
//  Param         : ROWCOL top,ROWCOL left,ROWCOL bottom,ROWCOL right, ROWCOL nRow, ROWCOL nCol
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreMoveCells(ROWCOL top,ROWCOL left,ROWCOL bottom,ROWCOL right, ROWCOL nRow, ROWCOL nCol)
{

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Cell Style

//******************************************************************
//  Function Name : StoreStyleRowCol
//  Function      : 
//  Param         : ROWCOL nRow, ROWCOL nCol, const CGXCaptionStyle* pStyle 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXCaptionStyle* pStyle )
{
	m_nRows = max(nRow, m_nRows);
	m_nCols = max(nCol, m_nCols);

	int row = (int) nRow;
	int col = (int) nCol;

	ASSERT_VALID(pStyle); ASSERT(pStyle->IsKindOf(RUNTIME_CLASS(CGXCaptionStyle)));
	// ASSERTION-> style is invalid ->END
	
	CGXCaptionStyle *pCellStyle = NULL;
	if (pStyle == NULL)
	{
		// remove cell
		if (row <= m_apapCellStyle.GetUpperBound())
		{
			CGXCaptionStylePtrArray* paCells = m_apapCellStyle.GetAt(row);
			if (paCells && col <= paCells->GetUpperBound())
			{
				delete paCells->GetAt(col);
				paCells->SetAt(col, NULL);
			}
		}
	}
	else
	{
		// store style

		// get cell-array for row
		CGXCaptionStylePtrArray* paCells = NULL;
		if (row <= m_apapCellStyle.GetUpperBound())
			paCells = m_apapCellStyle.GetAt(row);
		else
			// increase array size
			m_apapCellStyle.SetSize((int) m_nRows+1);

		// check if row must be created
		if (paCells == NULL)
		{
			paCells = new CGXCaptionStylePtrArray;
			m_apapCellStyle.SetAtGrow(row, paCells);
		}

		if (paCells && col <= paCells->GetUpperBound())
			pCellStyle = paCells->GetAt(col);
		else
			paCells->SetSize((int) m_nCols+1);

		if (pCellStyle)
		{
			pCellStyle->ChangeStyle(*pStyle );
		}
		else 
		{
			CGXCaptionStyle* pNewStyle;
			pNewStyle = pStyle->Clone();
			paCells->SetAtGrow(col, pNewStyle);
		}
	}


	return TRUE;
}

//******************************************************************
//  Function Name : SetDefaultCaptionChange 
//  Function      : 
//  Param         : WORD wLangCode /*= LANG_ENGLISH */, TCHAR chSep /*= US*/ 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::SetDefaultCaptionChange ( WORD wLangCode /*= LANG_ENGLISH */, TCHAR chSep /*= US*/ )
{
	BOOL bRet;
	CString strValue,
		    strCaption;

	if ( m_bSingleMode )
	{
		if ( m_pDefCaptionStyle && m_pDefCaptionStyle->GetDataValue ( dxDataType_MultiCaption, strValue ) )
		{
			strCaption =  GetMultiLangData ( strValue, bRet, wLangCode , chSep );
			m_pDefCaptionStyle->SetCaptionValue ( strCaption );
			return TRUE;
		}
		return FALSE;
	}

	if ( m_nRows <= 0 || m_nCols <= 0 )
		return FALSE;
	
	int   row,
		  col;
	for ( row = 1;  row <= (int)m_nRows; row ++ )
	{
		for ( col = 1;  col <= (int)m_nCols; col++ )
		{
			CGXCaptionStyle* pCellStyle = NULL;

			// get cell-array for row
			CGXCaptionStylePtrArray* paCells = NULL;
			if (row <= m_apapCellStyle.GetUpperBound())
				paCells = m_apapCellStyle.GetAt(row);

			// check if column is there
			if (paCells && col <= paCells->GetUpperBound())
				pCellStyle = paCells->GetAt(col);

			if ( pCellStyle && pCellStyle->GetDataValue ( dxDataType_MultiCaption, strValue ) )
			{
				strCaption =  GetMultiLangData ( strValue, bRet, wLangCode , chSep );
				pCellStyle->SetCaptionValue ( strCaption );
			}
		}
	}
	return bRet;
}

//******************************************************************
//  Function Name : GetSingleDataChange 
//  Function      : 
//  Param         : CString&  strValue, short nType,  TCHAR chSep1, TCHAR chSep2 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::GetSingleDataChange ( CString&  strValue, short nType,  TCHAR chSep1, TCHAR chSep2 )
{
	ASSERT ( m_bSingleMode );
	BOOL bRet  = FALSE;
	if ( m_bSingleMode && m_pDefCaptionStyle )
	{
		bRet = m_pDefCaptionStyle->GetDataValue ( nType, strValue );

		LPTSTR  lpBuf;
		int nLen = strValue.GetLength();
		if ( nLen > 0 )
		{
			lpBuf = strValue.GetBuffer(0);
			for ( int nIndex = 0 ; nIndex < nLen; nIndex ++ )
			{
				if ( lpBuf[nIndex] == chSep1 )
				{
					lpBuf[nIndex] = chSep2;
				}
			}
		}
	}
	return bRet;
}

//******************************************************************
//  Function Name : SetSingleDataChange 
//  Function      : 
//  Param         : CString  strValue, short nType,  TCHAR chSep1, TCHAR chSep2 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::SetSingleDataChange ( CString  strValue, short nType,  TCHAR chSep1, TCHAR chSep2 )
{
	ASSERT ( m_bSingleMode );
	if ( m_bSingleMode && m_pDefCaptionStyle )
	{
		LPTSTR  lpBuf;
		int nLen = strValue.GetLength();
		if ( nLen > 0 )
		{
			lpBuf = strValue.GetBuffer(0);
			char* pDest = strchr ( lpBuf, chSep1 );
			if ( pDest )
			{
				for ( int nIndex = 0 ; nIndex < nLen; nIndex ++ )
				{
					if ( lpBuf[nIndex] == chSep1 )
					{
						lpBuf[nIndex] = chSep2;
					}
				}
				m_pDefCaptionStyle->SetMultiLangDataValue( nType, strValue );
				return TRUE;
			}
		}
		else
		{
			m_pDefCaptionStyle->SetMultiLangDataValue( nType, strValue );
			return TRUE;
		}
	}
	return FALSE;	
}

//******************************************************************
//  Function Name : SetSingleDataType 
//  Function      : 
//  Param         : CString& strValue, short nType 
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionData::SetSingleDataType ( CString& strValue, short nType )
{
	ASSERT ( m_bSingleMode );
	if ( m_bSingleMode && m_pDefCaptionStyle )
	{
		m_pDefCaptionStyle->SetMultiLangDataValue( nType, strValue );
	}
}

//******************************************************************
//  Function Name : GetSingleDataType 
//  Function      : 
//  Param         : CString& strValue, short nType 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::GetSingleDataType ( CString& strValue, short nType )
{
	ASSERT ( m_bSingleMode );
	if ( m_bSingleMode && m_pDefCaptionStyle )
	{
		return m_pDefCaptionStyle->GetDataValue ( nType, strValue );
	}
	return FALSE;
}

// lang Data
//******************************************************************
//  Function Name : GetSingleLangData 
//  Function      : 
//  Param         : CString& strValue, short nType , WORD wLangCode /*= LANG_ENGLISH*/ , TCHAR chSep /*= US */
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::GetSingleLangData ( CString& strValue, short nType , WORD wLangCode /*= LANG_ENGLISH*/ , TCHAR chSep /*= US */)
{
	ASSERT ( m_bSingleMode );
	BOOL bRet = FALSE;
	if ( m_bSingleMode && m_pDefCaptionStyle &&  m_pDefCaptionStyle->GetDataValue ( nType, strValue ) )
	{
		strValue =  GetMultiLangData ( strValue, bRet, wLangCode , chSep );
		return bRet;
	}
	strValue = _T("");
	return bRet;
}

	// Get Data
//******************************************************************
//  Function Name : GetDataType 
//  Function      : 
//  Param         : ROWCOL nRow, ROWCOL nCol, CString& strValue, short nType 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::GetDataType ( ROWCOL nRow, ROWCOL nCol, CString& strValue, short nType )
{
	if (nRow > m_nRows || nCol > m_nCols)
		return FALSE;

	int row = (int) nRow;
	int col = (int) nCol;
	
	CGXCaptionStyle* pCellStyle = NULL;

	// get cell-array for row
	CGXCaptionStylePtrArray* paCells = NULL;
	if (row <= m_apapCellStyle.GetUpperBound())
		paCells = m_apapCellStyle.GetAt(row);

	// check if column is there
	if (paCells && col <= paCells->GetUpperBound())
		pCellStyle = paCells->GetAt(col);

	if ( pCellStyle )
	{
		return pCellStyle->GetDataValue ( nType, strValue );
	}

	return FALSE;
}

//******************************************************************
//  Function Name : SetSingleMultiLangData
//  Function      : 
//  Param         : CString strValue , short nType, WORD wCurLangCode 
//  Return        : BOOL  
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL  CGXCaptionData::SetSingleMultiLangData( CString strValue , short nType, WORD wCurLangCode )
{
	ASSERT ( m_bSingleMode );
	BOOL bRet  = FALSE;
	if ( m_bSingleMode && m_pDefCaptionStyle )
	{
		CString strData,
				strMultiData;
		bRet = m_pDefCaptionStyle->GetDataValue ( nType, strData );
		if ( bRet )
		{
			BOOL bExist;
			CString strEn,
				    strKo,
					strJa;

			strEn = GetMultiLangData ( strData, bExist, LANG_ENGLISH,  US );
			strKo = GetMultiLangData ( strData, bExist, LANG_KOREAN,   US );
			strJa = GetMultiLangData ( strData, bExist, LANG_JAPANESE, US );
			switch ( wCurLangCode )
			{
			default:
			case LANG_ENGLISH:
				strMultiData.Format ( "%s%c%s%c%s%c", strValue, US, strKo, US, strJa, US );
				break;
			case LANG_KOREAN:
				strMultiData.Format ( "%s%c%s%c%s%c", strEn, US, strValue, US, strJa, US );
				break;
			case LANG_JAPANESE:
				strMultiData.Format ( "%s%c%s%c%s%c", strEn, US, strKo, US, strValue, US );
				break;
			}

			m_pDefCaptionStyle->SetMultiLangDataValue( nType, strMultiData );
			return TRUE;
		}
		else
		{
			switch ( wCurLangCode )
			{
			default:
			case LANG_ENGLISH:
				strMultiData.Format ( "%s%c%c%c", strValue, US, US, US );
				break;
			case LANG_KOREAN:
				strMultiData.Format ( "%c%s%c%c", US, strValue, US, US );
				break;
			case LANG_JAPANESE:
				strMultiData.Format ( "%c%c%s%c", US, US, strValue, US );
				break;
			}
			m_pDefCaptionStyle->SetMultiLangDataValue( nType, strMultiData );
			return TRUE;
		}
	}
	return bRet;
			
}

//******************************************************************
//  Function Name : GetMultiLangData 
//  Function      : 
//  Param         : CString strValue , BOOL& bRet, WORD wLangCode , TCHAR chSep 
//  Return        : const 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
const CString& CGXCaptionData::GetMultiLangData ( CString strValue , BOOL& bRet, WORD wLangCode , TCHAR chSep ) const
{
	bRet = TRUE;
	
	LPTSTR p,
		   lpBuf;
	int    nFind(0);

	lpBuf = strValue.GetBuffer(0);
	char* pDest = strchr ( lpBuf, chSep );
	if ( pDest == NULL )
	{
		m_strValueCache = strValue;
		return m_strValueCache;
	}

	nFind  = pDest - lpBuf;
	switch ( wLangCode )
	{
		case LANG_ENGLISH:
			{
				if ( nFind > 0 )
				{
					p = m_strValueCache.GetBuffer(nFind+1);
					memcpy( p, lpBuf, nFind );
					p[nFind] = 0;
					m_strValueCache.ReleaseBuffer();
					bRet = TRUE;
					return m_strValueCache;
				}
			}
			break;
		case LANG_KOREAN:
			{
				nFind ++;
				lpBuf = lpBuf + nFind;
				pDest = strchr ( lpBuf, chSep );
				if ( pDest )
				{
					nFind = pDest - lpBuf;
					if ( nFind > 0 )
					{
						p = m_strValueCache.GetBuffer(nFind+1);
						memcpy( p, lpBuf, nFind );
						p[nFind] = 0;
						m_strValueCache.ReleaseBuffer();
						return m_strValueCache;
					}
				}
			}
			break;
		case LANG_JAPANESE:
			{
				nFind ++;
				lpBuf = lpBuf + nFind;
				pDest = strchr ( lpBuf, chSep );
				if ( pDest )
				{
					nFind = pDest - lpBuf;
					nFind++;
					lpBuf = lpBuf + nFind;
					if ( lpBuf != NULL )
					{
						pDest = strchr ( lpBuf, chSep );
						if ( pDest )
						{
							nFind = pDest - lpBuf;
							if ( nFind > 0 )
							{
								p = m_strValueCache.GetBuffer(nFind+1);
								memcpy( p, lpBuf, nFind );
								p[nFind] = 0;
								m_strValueCache.ReleaseBuffer();
								return m_strValueCache;
							}
						}
						else 
						{
							nFind = strlen ( lpBuf );
							p = m_strValueCache.GetBuffer(nFind+1);
							memcpy( p, lpBuf, nFind );
							p[nFind] = 0;
							m_strValueCache.ReleaseBuffer();
							return m_strValueCache;
						}
					}
				}
			}
			break;
		default:
			break;
	}

	bRet = FALSE;
	m_strValueCache.Empty();
	return m_strValueCache;		
}


//******************************************************************
//  Function Name : GetLangData 
//  Function      : 
//  Param         : ROWCOL nRow, ROWCOL nCol, CString& strValue, short nType , WORD wLangCode /*= LANG_ENGLISH */, TCHAR chSep /*= US*/ 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::GetLangData ( ROWCOL nRow, ROWCOL nCol, CString& strValue, short nType , WORD wLangCode /*= LANG_ENGLISH */, TCHAR chSep /*= US*/ )
{
	BOOL bRet = FALSE;
	if (nRow > m_nRows || nCol > m_nCols)
		return bRet;

	int row = (int) nRow;
	int col = (int) nCol;
	CGXCaptionStyle* pCellStyle = NULL;

	// get cell-array for row
	CGXCaptionStylePtrArray* paCells = NULL;
	if (row <= m_apapCellStyle.GetUpperBound())
		paCells = m_apapCellStyle.GetAt(row);

	// check if column is there
	if (paCells && col <= paCells->GetUpperBound())
		pCellStyle = paCells->GetAt(col);

	if ( pCellStyle && pCellStyle->GetDataValue ( nType, strValue ) )
	{
		strValue =  GetMultiLangData ( strValue, bRet, wLangCode ,chSep );
		return bRet;
	}
	return bRet;
}

//******************************************************************
//  Function Name : GetCaptionStyleRef
//  Function      : 
//  Param         : ROWCOL nRow, ROWCOL nCol 
//  Return        : CGXCaptionStyle
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CGXCaptionStyle* CGXCaptionData::GetCaptionStyleRef( ROWCOL nRow, ROWCOL nCol )
{
	if (nRow > m_nRows || nCol > m_nCols)
		return FALSE;

	int row = (int) nRow;
	int col = (int) nCol;

	CGXCaptionStyle* pCellCaptionStyle = NULL;

	// get cell-array for row
	CGXCaptionStylePtrArray* paCells = NULL;
	if (row <= m_apapCellStyle.GetUpperBound())
		paCells = m_apapCellStyle.GetAt(row);

	// check if column is there
	if (paCells && col <= paCells->GetUpperBound())
		pCellCaptionStyle = paCells->GetAt(col);
	
	if ( pCellCaptionStyle )
	{
		return pCellCaptionStyle;
	}

	return NULL;
}

//******************************************************************
//  Function Name : GetStyleRowCol
//  Function      : 
//  Param         : ROWCOL nRow, ROWCOL nCol, CGXCaptionStyle& style 
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CGXCaptionData::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXCaptionStyle& style )
{
	if (nRow > m_nRows || nCol > m_nCols)
		return FALSE;

	int row = (int) nRow;
	int col = (int) nCol;

	ASSERT(style.IsKindOf(RUNTIME_CLASS(CGXCaptionStyle)));
	ASSERT_VALID(&style);

	CGXCaptionStyle* pCellStyle = NULL;

	// get cell-array for row
	CGXCaptionStylePtrArray* paCells = NULL;
	if (row <= m_apapCellStyle.GetUpperBound())
		paCells = m_apapCellStyle.GetAt(row);

	// check if column is there
	if (paCells && col <= paCells->GetUpperBound())
		pCellStyle = paCells->GetAt(col);

	if ( pCellStyle )
	{
		style.ChangeStyle(*pCellStyle );
		return TRUE;
	}

	// ... no style found
	return FALSE;
}

//******************************************************************
//  Function Name : Grid
//  Function      : 
//  Param         : 
//  Return        : CGXGridCore*
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
//CGXGridCore* CGXCaptionData::Grid() const
//{
//	return GXGetAppData()->GetFirstGrid((void*) this);
//}

//******************************************************************
//  Function Name : StringToBinaryEx
//  Function      : 
//  Param         : CString strOrg
//  Return        : BYTE*  
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BYTE* StringToBinaryEx(CString strOrg)
{
	BYTE* pData = NULL;
	int nLength = strOrg.GetLength();
	
	pData = (BYTE*)malloc(nLength/2);

	if( pData == NULL )
		return pData;
	memset(pData, 0x0, nLength/2);

	for (int i = 0; i < nLength; i+=2)
	{
		if (strOrg[i] <= '9')
			pData[i/2] = (strOrg[i] - '0') * 16; 
		else
			pData[i/2] = (strOrg[i] - 'A' + 10) * 16; 

		if (strOrg[i+1] <= '9')
			pData[i/2] += (strOrg[i+1] - '0'); 
		else
			pData[i/2] += (strOrg[i+1] - 'A' + 10); 
	}

	return pData;
}
//******************************************************************
//  Function Name : BinaryToStringEx
//  Function      : 
//  Param         : BYTE* pData, int nDataLen
//  Return        : CString 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CString	BinaryToStringEx(BYTE* pData, int nDataLen)
{
	CString strReturn;//, strTemp;
	char szTemp[3] = { 0 };
	if( pData )
	{
		int nTotLen = nDataLen*2+1;
		char *pBuf = new char[nTotLen];
		memset ( pBuf, 0x00, nTotLen );

		for (int i = 0; i < nDataLen; i++)
		{
			sprintf(szTemp, "%02X", (BYTE)pData[i] );
			memcpy ( (char*)&pBuf[i*2], (char*)&szTemp[0], 2 );
		}
		
		strReturn = pBuf;	
		int nLen = strReturn.GetLength();
		if ( nLen != nTotLen -1 )
		{
			TRACE("BinaryToString..Error!!![%d]=[%d]\n", nLen, nTotLen);
		}
		if ( pBuf )
			delete[] pBuf;

//		for (int i = 0; i < nDataLen; i++)
//		{
//			strTemp.Format("%02X", (BYTE)pData[i]);
//			strReturn += strTemp;
//		}
	}

	return strReturn;
}

#endif
