// gxGridCelldata.cpp : implementation of the CGXGridCellData class
#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifndef _GXGRIDCELLSTYLE_H_
#include "gxgridcellstyle.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXGRIDCELLDATA")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CGXGridCellData, CObject, 0 /* schema number*/ )
IMPLEMENT_DYNAMIC(CGXGridCellStylePtrArray, CPtrArray)
IMPLEMENT_DYNAMIC(CGXGridCellStylePtrArrayPtrArray, CPtrArray)

// Convert
BYTE*		StringToBinaryEx( CString strOrg);
CString		BinaryToStringEx( BYTE* pData, int nDataLen);

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// class CGXGridCellStylePtrArray
CGXGridCellStylePtrArray::~CGXGridCellStylePtrArray()
{
	DeleteAll();
}

void CGXGridCellStylePtrArray::DeleteAll()
{
	for (int index = 0; index <= GetUpperBound(); index++)
		delete GetAt(index);

	RemoveAll();
}

void CGXGridCellStylePtrArray::DeleteAt(int nIndex, int nCount)
{
	int nUpper = min(GetUpperBound(), nIndex+nCount-1);
	if (nUpper >= nIndex)
	{
		for (int index = nIndex; index <= nUpper; index++)
			delete GetAt(index);

		RemoveAt(nIndex, nUpper-nIndex+1);
	}
}

void CGXGridCellStylePtrArray::Move(int nIndex, int nCount, int nDest)
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

const CGXGridCellStylePtrArray& CGXGridCellStylePtrArray::operator=(const CGXGridCellStylePtrArray& other)
{
	if (&other == this)
		return *this;

	DeleteAll();

	SetSize(other.GetSize());
	for (int index = 0; index <= other.GetUpperBound(); index++)
	{
		CGXGridCellStyle* pStyle = other.GetAt(index);
		if (pStyle)
			SetAt(index, pStyle->Clone());
	}

	return *this;
}

void CGXGridCellStylePtrArray::Serialize(CArchive& ar)
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
			TRACE0( "Incompatible format while reading CGXGridCellStylePtrArray" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXGridCellStylePtrArray object ->END
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
			CGXGridCellStyle* pStyle = GetAt(index);
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
//			CGXGridCellStyle* pStyle;
//			pStyle = NULL;
//			ar >> pStyle;

			CGXGridCellStyle* pStyle = new CGXGridCellStyle;
			pStyle->Serialize ( ar );

			SetAt((int) dwIndex, pStyle);

			// Next id
			ar >> dwIndex;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// class CGXGridCellStylePtrArrayPtrArray

CGXGridCellStylePtrArrayPtrArray::~CGXGridCellStylePtrArrayPtrArray()
{
	DeleteAll();
}

void CGXGridCellStylePtrArrayPtrArray::DeleteAt(int nIndex, int nCount)
{
	int nUpper = min(GetUpperBound(), nIndex+nCount-1);
	if (nUpper >= nIndex)
	{
		for (int index = nIndex; index <= nUpper; index++)
			delete GetAt(index);

		RemoveAt(nIndex, nUpper-nIndex+1);
	}
}

void CGXGridCellStylePtrArrayPtrArray::DeleteAll()
{
	for (int index = 0; index <= GetUpperBound(); index++)
		delete GetAt(index);

	RemoveAll();
}

void CGXGridCellStylePtrArrayPtrArray::Move(int nIndex, int nCount, int nDest)
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

const CGXGridCellStylePtrArrayPtrArray& CGXGridCellStylePtrArrayPtrArray::operator=(const CGXGridCellStylePtrArrayPtrArray& other)
{
	if (&other == this)
		return *this;

	DeleteAll();

	SetSize(other.GetSize());
	for (int index = 0; index <= other.GetUpperBound(); index++)
	{
		if (other.GetAt(index))
			SetAt(index, new CGXGridCellStylePtrArray(*other.GetAt(index)));
	}

	return *this;
}

void CGXGridCellStylePtrArrayPtrArray::Serialize(CArchive& ar)
{
	// Serializes only existing elements,
	// e.g.  1 xxx 2 xxx 3 xxx 7 xxx 22 xxx DWORD_MAX,
	// where xxx is a CGXGridCellStylePtrArray object and DWORD_MAX identifies the end of serialization

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
			TRACE0( "Incompatible format while reading CGXGridCellStylePtrArrayPtrArray " );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXGridCellStylePtrArrayPtrArray object ->END
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
			CGXGridCellStylePtrArray* pStylePtrArray = GetAt(index);
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
			CGXGridCellStylePtrArray* pStylePtrArray = new CGXGridCellStylePtrArray;
			pStylePtrArray->Serialize(ar);

			SetAt((int) dwIndex, pStylePtrArray);

			// Next id
			ar >> dwIndex;
		}
	}

}



/////////////////////////////////////////////////////////////////////////////
// class CGXGridCellData
CGXGridCellData::CGXGridCellData()
{
	m_nRows = 0;
	m_nCols = 0;

	m_pDefCaptionStyle = NULL;		// Single style
	m_bSingleMode      = FALSE;
}

void CGXGridCellData::SetSingleMode( )
{
	m_bSingleMode = TRUE;

	m_pDefCaptionStyle = new CGXGridCellStyle();
}

CGXGridCellData::~CGXGridCellData()
{
	DeleteContents();

	if ( m_bSingleMode && m_pDefCaptionStyle )
		delete m_pDefCaptionStyle;
}

void CGXGridCellData::DeleteContents()
{
	if ( m_bSingleMode && m_pDefCaptionStyle )
	{
		m_pDefCaptionStyle->Free();
	}
	m_apapCellStyle.DeleteAll();
}

const CGXGridCellData& CGXGridCellData::operator=(const CGXGridCellData& p)
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
BOOL CGXGridCellData::SetMultiCaptionBlobDataChange ( CString  strPropertyData )
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

CString CGXGridCellData::GetMultiCaptionBlobDataChange ( )
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
void CGXGridCellData::SerializeEx(CArchive& ar, CString& strProperty )
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

void CGXGridCellData::Serialize(CArchive& ar)
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
			TRACE0( "Incompatible format while reading CGXGridCellData" );
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

ROWCOL CGXGridCellData::GetRowCount()
{
	return (ROWCOL) m_nRows;
}

ROWCOL CGXGridCellData::GetColCount()
{
	return (ROWCOL) m_nCols;
}

BOOL CGXGridCellData::SetRowCount(ROWCOL nRows )
{
	TRACE("CGXGridCellData : BEGIN SetRowCount(%u)\n", nRows);

	ROWCOL nOldRows = GetRowCount();
	if (nRows < nOldRows)
		return StoreRemoveRows(nRows+1, nOldRows );
	else if (nRows > nOldRows)
		return StoreInsertRows(nOldRows+1, nRows-nOldRows );
	return TRUE;

}

BOOL CGXGridCellData::SetColCount(ROWCOL nCols )
{
	ROWCOL nOldCols = GetColCount();
	if (nCols < nOldCols)
		return StoreRemoveCols(nCols+1, nOldCols );
	else if (nCols > nOldCols)
		return StoreInsertCols(nOldCols+1, nCols-nOldCols );
	return TRUE;

}

BOOL CGXGridCellData::StoreRowCount(ROWCOL nRows)
{
	if (nRows < m_nRows)
		StoreRemoveRows(nRows+1, m_nRows);
	else if (nRows > m_nRows)
		StoreInsertRows(m_nRows+1, nRows-m_nRows);
	return TRUE;
}

BOOL CGXGridCellData::StoreColCount(ROWCOL nCols)
{
	if (nCols < m_nCols)
		StoreRemoveCols(nCols+1, m_nCols);
	else if (nCols > m_nCols)
		StoreInsertCols(m_nCols+1, nCols-m_nCols);
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// Insert, Remove and Move Cells

BOOL CGXGridCellData::StoreInsertRows(ROWCOL nRow, ROWCOL nCount)
{
	ASSERT(nRow <= INT_MAX && nCount <= INT_MAX);

	int row = (int) nRow;
	int count = (int) nCount;

	m_apapCellStyle.InsertAt(row, NULL, count);
	
	m_nRows += nCount;

	return TRUE;
}

BOOL CGXGridCellData::StoreInsertCols(ROWCOL nCol, ROWCOL nCount)
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


BOOL CGXGridCellData::StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow)
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


BOOL CGXGridCellData::StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol)
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

BOOL CGXGridCellData::StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow)
{
	ASSERT(nFromRow <= INT_MAX && nToRow <= INT_MAX && nDestRow <= INT_MAX);

	int row = (int) nFromRow;
	int count = (int) (nToRow-nFromRow+1);
	int dest = (int) nDestRow;

	m_apapCellStyle.Move(row, count, dest);

	return TRUE;
}

BOOL CGXGridCellData::StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol)
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

BOOL CGXGridCellData::StoreCopyCells(ROWCOL top,ROWCOL left,ROWCOL bottom,ROWCOL right, ROWCOL nRow, ROWCOL nCol)
{

	return FALSE;
}

BOOL CGXGridCellData::StoreMoveCells(ROWCOL top,ROWCOL left,ROWCOL bottom,ROWCOL right, ROWCOL nRow, ROWCOL nCol)
{

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Cell Style

BOOL CGXGridCellData::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXGridCellStyle* pStyle )
{
	m_nRows = max(nRow, m_nRows);
	m_nCols = max(nCol, m_nCols);

	int row = (int) nRow;
	int col = (int) nCol;

	ASSERT_VALID(pStyle); ASSERT(pStyle->IsKindOf(RUNTIME_CLASS(CGXGridCellStyle)));
	// ASSERTION-> style is invalid ->END
	
	CGXGridCellStyle *pCellStyle = NULL;
	if (pStyle == NULL)
	{
		// remove cell
		if (row <= m_apapCellStyle.GetUpperBound())
		{
			CGXGridCellStylePtrArray* paCells = m_apapCellStyle.GetAt(row);
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
		CGXGridCellStylePtrArray* paCells = NULL;
		if (row <= m_apapCellStyle.GetUpperBound())
			paCells = m_apapCellStyle.GetAt(row);
		else
			// increase array size
			m_apapCellStyle.SetSize((int) m_nRows+1);

		// check if row must be created
		if (paCells == NULL)
		{
			paCells = new CGXGridCellStylePtrArray;
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
			CGXGridCellStyle* pNewStyle;
			pNewStyle = pStyle->Clone();
			paCells->SetAtGrow(col, pNewStyle);
		}
	}


	return TRUE;
}


BOOL CGXGridCellData::GetSingleDataChange ( CString&  strValue, short nType,  TCHAR chSep1, TCHAR chSep2 )
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

BOOL CGXGridCellData::SetSingleDataChange ( CString  strValue, short nType,  TCHAR chSep1, TCHAR chSep2 )
{
	ASSERT ( m_bSingleMode );
	if ( m_bSingleMode && m_pDefCaptionStyle )
	{
		LPTSTR  lpBuf;
		int nLen = strValue.GetLength();
		if ( nLen > 0 )
		{
			lpBuf = strValue.GetBuffer(0);
			char* pDest = (LPTSTR)_tcschr ( lpBuf, chSep1 );
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

void CGXGridCellData::SetSingleDataType ( CString& strValue, short nType )
{
	ASSERT ( m_bSingleMode );
	if ( m_bSingleMode && m_pDefCaptionStyle )
	{
		m_pDefCaptionStyle->SetMultiLangDataValue( nType, strValue );
	}
}

BOOL CGXGridCellData::GetSingleDataType ( CString& strValue, short nType )
{
	ASSERT ( m_bSingleMode );
	if ( m_bSingleMode && m_pDefCaptionStyle )
	{
		return m_pDefCaptionStyle->GetDataValue ( nType, strValue );
	}
	return FALSE;
}


// Get Data
BOOL CGXGridCellData::GetDataType ( ROWCOL nRow, ROWCOL nCol, CString& strValue, short nType )
{
	if (nRow > m_nRows || nCol > m_nCols)
		return FALSE;

	int row = (int) nRow;
	int col = (int) nCol;
	
	CGXGridCellStyle* pCellStyle = NULL;

	// get cell-array for row
	CGXGridCellStylePtrArray* paCells = NULL;
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


CGXGridCellStyle* CGXGridCellData::GetCaptionStyleRef( ROWCOL nRow, ROWCOL nCol )
{
	if (nRow > m_nRows || nCol > m_nCols)
		return FALSE;

	int row = (int) nRow;
	int col = (int) nCol;

	CGXGridCellStyle* pCellCaptionStyle = NULL;

	// get cell-array for row
	CGXGridCellStylePtrArray* paCells = NULL;
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

BOOL CGXGridCellData::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXGridCellStyle& style )
{
	if (nRow > m_nRows || nCol > m_nCols)
		return FALSE;

	int row = (int) nRow;
	int col = (int) nCol;

	ASSERT(style.IsKindOf(RUNTIME_CLASS(CGXGridCellStyle)));
	ASSERT_VALID(&style);

	CGXGridCellStyle* pCellStyle = NULL;

	// get cell-array for row
	CGXGridCellStylePtrArray* paCells = NULL;
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

//CGXGridCore* CGXGridCellData::Grid() const
//{
//	return GXGetAppData()->GetFirstGrid((void*) this);
//}


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
