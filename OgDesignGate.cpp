// OgDesignGate.cpp : implementation file
//
//#define _OG_EXPORT_IMPL

#include "stdafx.h"
#include "OgDesignGate.h"
#include "KSCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////// Global Functions //////////////////////////
// 자료형에 따른 실제의 테이타 길이를 구한다.
unsigned short GetRealDataLen(BYTE  byDataType, short nDataLen);

// Convert
BYTE*		StringToBinary( CString strOrg);
CString		BinaryToString( BYTE* pData, int nDataLen);

// Initialize
void		InitITEMBITS(ITEMBITS& ItemBits);
void		InitGRIDBITS(GRIDBITS& GridBits);
void		InitTABLEBITS(TABLEBITS& tblBits);

#ifdef FIXLEN_USE
void		InitTRANBITS(TRANBITS& TrBits);
#endif

void		InitOGBASEITEM(OGBASEITEM& bsItem, BOOL bHeader);
void		InitMASKINFO(MASKINFO& mask);
// Serialize
void		SerializeITEMBITS(CArchive &ar, ITEMBITS& ItemBits);
void		SerializeGRIDBITS(CArchive &ar, GRIDBITS& GridBits);
void		SerializeTABLEBITS(CArchive &ar, TABLEBITS& tblBits);

#ifdef FIXLEN_USE
void		SerializeTRANBITS(CArchive &ar, TRANBITS& TrBits);
#endif

void		SerializeOGBASEITEM(CArchive &ar, OGBASEITEM& bsItem);
void		SerializeREALCONBITS(CArchive &ar, REALCONBITS& RConBits);
void		SerializeRECTYPEBITS(CArchive &ar, RECTYPEBITS& RTBits);
void		SerializeNEWREFERBITS(CArchive &ar, NEWREFERBITS& NRBits);
void		SerializeMASKINFO(CArchive &ar, MASKINFO& mask);


//*******************************************************************
//  FUNCTION:	- GetRealDataLen
//  RETURNS:	- Data Type에 따른 실제의 데이타 길이를 구한다. .
//  PARAMETERS:	- 
//  COMMENTS:	-
//  AUTHOR:		-2004.05.17 Hong~~
//*******************************************************************
unsigned short GetRealDataLen(BYTE  byDataType, short nDataLen)
{
	unsigned short nRealLen(0);
	
	switch(byDataType)
	{
		case DT_CHAR:
		case DT_BYTE:
			{
				if( nDataLen > sizeof(BYTE) )
				{
					// NH에서 사용하는 유형.. BYTE나 CHAR를 String 처럼 처리하기 위함..
					nRealLen = nDataLen;
				}
				else
				{
					nRealLen = sizeof(BYTE);
				}
			}
			break;
		case DT_SHORT:
			nRealLen = sizeof(short);
			break;
		case DT_WORD:
			nRealLen = sizeof(WORD);
			break;
		case DT_LONG:
			nRealLen = sizeof(long);
			break;
		case DT_DWORD:
			nRealLen = sizeof(DWORD);
			break;
		case DT_FLOAT:
			nRealLen = sizeof(float);
			break;
		case DT_DOUBLE:
			nRealLen = sizeof(double);
			break;
		case DT_INT64:
			nRealLen = sizeof(__int64);
			break;
		case DT_DATE:
			nRealLen = sizeof(__int64);
			break;
		case DT_STRING:
		case DT_STRINGNUM:
			nRealLen = nDataLen;
			break;
		case DT_INT:		
			nRealLen = sizeof(int);
			break;
		default:	
			ASSERT(FALSE);
	}

	return nRealLen; 
}

BYTE* StringToBinary(CString strOrg)
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

CString	BinaryToString(BYTE* pData, int nDataLen)
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

void InitITEMBITS(ITEMBITS& ItemBits)
{
	memset(&ItemBits, 0, LEN_ITEMBITS);
//	ItemBits.nItemFlag	= dxItemOut;
	ItemBits.nItemFlag	= dxItemNotUse;
}

void InitGRIDBITS(GRIDBITS& GridBits)
{
	memset(&GridBits, 0, LEN_GRIDBITS);
}

void InitTABLEBITS(TABLEBITS& tblBits)
{
	memset(&tblBits, 0, LEN_TABLEBITS);
}

#ifdef FIXLEN_USE
void InitTRANBITS(TRANBITS& TrBits)
{
	memset(&TrBits, 0, LEN_TRANBITS);
}
#endif

void InitOGBASEITEM(OGBASEITEM& bsItem, BOOL bHeader)
{
	bsItem.nBkCrIndex	= bHeader ? HEADER_BKCR_INDEX : DEF_BKCR_INDEX;
	bsItem.nTxCrIndex	= bHeader ? HEADER_TXCR_INDEX : DEF_TXCR_INDEX;
	bsItem.nFontIndex	= bHeader ? HEADER_FONT_INDEX : DEF_FONT_INDEX;
	bsItem.nHAlign		= bHeader ? HEADER_HALIGN     : DEF_HALIGN;
	bsItem.nVAlign		= DEF_VALIGN;
	bsItem.nCtrlID		= bHeader ? dxCtrlHeader      : dxCtrlStatic;
	memset(&bsItem.BaseBits,	0, LEN_BASEBITS		);
// --> [Edit]  김창하 2006/10/12
	bsItem.nWrapText		= 0;
	bsItem.nBaseItemDummy	= 0;
// <-- [Edit]  김창하 2006/10/12
//	bsItem.lDummy		= 0L;
}

void InitMASKINFO(MASKINFO& mask)
{
	mask.nFormat		= dxFmt_Default;
	mask.nPlaces		= DEF_MASK_PLACES;
	mask.dwBitInfo		= 0;
	mask.szFix[0]		= 0x00;
	mask.lMaskInfoUnit	= 0;
}

void SerializeITEMBITS(CArchive &ar, ITEMBITS& ItemBits)
{
	unsigned long  lLongBits;
	if( ar.IsStoring() )							// Write
	{
		memcpy(&lLongBits, &ItemBits, LEN_ITEMBITS);
		ar << lLongBits;
	}
	else
	{
		ar >> lLongBits;
		memcpy(&ItemBits, &lLongBits, LEN_ITEMBITS);
	}
}

void SerializeGRIDBITS(CArchive &ar, GRIDBITS& GridBits)
{
	unsigned long  lLongBits;
	if( ar.IsStoring() )							// Write
	{
		memcpy(&lLongBits, &GridBits, LEN_GRIDBITS);
		ar << lLongBits;
	}
	else
	{
		ar >> lLongBits;
		memcpy(&GridBits, &lLongBits, LEN_GRIDBITS);
	}
}

void SerializeTABLEBITS(CArchive &ar, TABLEBITS& tblBits)
{
	unsigned long  lLongBits;
	if( ar.IsStoring() )							// Write
	{
		memcpy(&lLongBits, &tblBits, LEN_TABLEBITS);
		ar << lLongBits;
	}
	else
	{
		ar >> lLongBits;
		memcpy(&tblBits, &lLongBits, LEN_TABLEBITS);
	}
}

#ifdef FIXLEN_USE
void SerializeTRANBITS(CArchive &ar, TRANBITS& TrBits)
{
	unsigned long  lLongBits;
	if( ar.IsStoring() )							// Write
	{
		memcpy(&lLongBits, &TrBits, LEN_TRANBITS);
		ar << lLongBits;
	}
	else
	{
		ar >> lLongBits;
		memcpy(&TrBits, &lLongBits, LEN_TRANBITS);
	}
}
#endif

void SerializeOGBASEITEM(CArchive &ar, OGBASEITEM& bsItem)
{
	unsigned long  lLongBits;
	if( ar.IsStoring() )							// Write
	{
		ar << bsItem.nBkCrIndex;
		ar << bsItem.nTxCrIndex;
		ar << bsItem.nFontIndex;
		ar << bsItem.nHAlign;
		ar << bsItem.nVAlign;
		ar << bsItem.nCtrlID;
		memcpy(&lLongBits, &bsItem.BaseBits, LEN_BASEBITS);
		ar << lLongBits;
		// Dummy for OGBASEITEM
// --> [Edit]  김창하 2006/10/12
		ar << bsItem.nWrapText;
		ar << bsItem.nBaseItemDummy;
//		ar << bsItem.lDummy;
// <-- [Edit]  김창하 2006/10/12

	}
	else
	{
		ar >> bsItem.nBkCrIndex;
		ar >> bsItem.nTxCrIndex;
		ar >> bsItem.nFontIndex;
		ar >> bsItem.nHAlign;
		ar >> bsItem.nVAlign;
		ar >> bsItem.nCtrlID;
		ar >> lLongBits;
		memcpy(&bsItem.BaseBits, &lLongBits, LEN_BASEBITS );
// --> [Edit]  김창하 2006/10/12
		ar >> bsItem.nWrapText;
		ar >> bsItem.nBaseItemDummy;
		// Dummy for OGBASEITEM
//		ar >> bsItem.lDummy;
// <-- [Edit]  김창하 2006/10/12
	}
}

void SerializeREALCONBITS(CArchive &ar, REALCONBITS& RConBits)
{
	unsigned long  lLongBits;
	if( ar.IsStoring() )							// Write
	{
		memcpy(&lLongBits, &RConBits, LEN_REALCONBITS);
		ar << lLongBits;
	}
	else
	{
		ar >> lLongBits;
		memcpy(&RConBits, &lLongBits, LEN_REALCONBITS);
	}
}

void SerializeRECTYPEBITS(CArchive &ar, RECTYPEBITS& RTBits)
{
	unsigned long  lLongBits;
	if( ar.IsStoring() )							// Write
	{
		memcpy(&lLongBits, &RTBits, LEN_RECTYPEBITS);
		ar << lLongBits;
	}
	else
	{
		ar >> lLongBits;
		memcpy(&RTBits, &lLongBits, LEN_RECTYPEBITS);
	}
}

void SerializeNEWREFERBITS(CArchive &ar, NEWREFERBITS& NRBits)
{
	unsigned long  lLongBits;
	if( ar.IsStoring() )							// Write
	{
		memcpy(&lLongBits, &NRBits, LEN_NEWREFERBITS);
		ar << lLongBits;
	}
	else
	{
		ar >> lLongBits;
		memcpy(&NRBits, &lLongBits, LEN_NEWREFERBITS);
	}
}

void SerializeMASKINFO(CArchive &ar, MASKINFO& mask)
{
	BYTE byReadLen;
	if( ar.IsStoring() )							// Write
	{
		ar << mask.nFormat;
		ar << mask.nPlaces;
		ar << mask.dwBitInfo;
		ar << (BYTE) lstrlen(mask.szFix);
		ar.WriteString((LPCTSTR) mask.szFix);
		ar << mask.lMaskInfoUnit;
	}
	else
	{
		ar >> mask.nFormat;
		ar >> mask.nPlaces;
		ar >> mask.dwBitInfo;
		ar >> byReadLen;
		ar.ReadString( mask.szFix, byReadLen);
		ar >> mask.lMaskInfoUnit;
	}
}

////////////// Global Functions //////////////////////////

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CGridHeader, CObject, 1)

CGridHeader::CGridHeader() 
{ 
	dwLength	= 0;
	nCount		= 0;
	pRec		= NULL;
	m_dwVersion = DEF_VERSION;
	m_pGrid		= NULL;
};

//*******************************************************************/
/*! Function Name : CGridHeader
/*! Function      : 
/*! Param         : const CGridHeader*r
/*! Return        : 
/*! Create        : 김창하 , 2006/02/04
/*! Comment       : 
//******************************************************************/
CGridHeader::CGridHeader(const CGridHeader*r )
{
// --> [Edit]  김창하 2006/04/10
	m_dwVersion		= DEF_VERSION;
	m_pGrid			= NULL;
	pRec			= NULL;

#if FALSE
	if (r)
	{
		*this = *r;
	}
#endif

	dwLength		= r->dwLength;
	nCount			= r->nCount;
	m_dwVersion		= r->m_dwVersion;
	
	if(nCount > 0)
	{
		pRec = new GRIDHEADER*[nCount];
		
		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRec[nIndex] = new GRIDHEADER;
			
			if ( pRec[nIndex] )
			{
				memcpy(pRec[nIndex], r->pRec[nIndex], LEN_GRIDHEADER);
			}
		}
	}
// <-- [Edit]  김창하 2006/04/10

}

CGridHeader::~CGridHeader() 
{

};

void CGridHeader::Initialize()
{
	if(m_pGrid == NULL)
		return;

	short nRow, nCol, nRowIndex, nColIndex(0), nRowStep(1), nColStep(1);
	nRowIndex = m_pGrid->m_nHeaderRowCnt;
	int nRowMax = m_pGrid->m_nHeaderRowCnt * m_pGrid->m_nColCnt;
	int nColMax = m_pGrid->m_nHeaderColCnt * ( m_pGrid->m_nRowCnt - m_pGrid->m_nHeaderRowCnt );

	nCount			= nRowMax + nColMax;
	dwLength		= LEN_GRIDHEADERINFO( nCount );
	m_dwVersion		= DEF_VERSION;

	pRec = new GRIDHEADER*[nCount];
	
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRec[nIndex] = new GRIDHEADER;
		
		if ( pRec[nIndex] )
		{
			if( nIndex < nRowMax )
			{
				if( nColIndex  == m_pGrid->m_nColCnt)
				{
					nRowStep++;
					nColIndex = 0;
				}

				nColIndex++;

				nRow = nRowStep;
				nCol = nColIndex;

			}
			else if(nIndex >= nRowMax)
			{
				if( nRowIndex == m_pGrid->m_nRowCnt)
				{
					nColStep++;
					nRowIndex = m_pGrid->m_nHeaderRowCnt;
				}

				nRowIndex++;

				nRow = nRowIndex;
				nCol = nColStep;
			}
			
			pRec[nIndex]->nRow				= nRow;
			pRec[nIndex]->nCol				= nCol;
			pRec[nIndex]->nOrgRow           = nRow;
			pRec[nIndex]->nOrgCol           = nCol;
			pRec[nIndex]->szCaption[0]		= 0x00;
			
			// base info
			InitOGBASEITEM(pRec[nIndex]->bsItem, TRUE);
			// MaskInfo
			InitMASKINFO(pRec[nIndex]->mask);

			pRec[nIndex]->lDummy			= 0L;
		
		}
	}

}

const CGridHeader& CGridHeader::operator=(const CGridHeader& other)
{
	if ( &other == this)
		return *this;

	Clear();

	dwLength		= other.dwLength;
	nCount			= other.nCount;
	m_dwVersion		= other.m_dwVersion;
	
	if(nCount > 0)
	{
		pRec = new GRIDHEADER*[nCount];
		
		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRec[nIndex] = new GRIDHEADER;
			
			if ( pRec[nIndex] )
			{
				memcpy(pRec[nIndex], other.pRec[nIndex], LEN_GRIDHEADER);
			}
		}
	}

	return *this;
}

void CGridHeader::Clear( BOOL bInitCnt /*= TRUE*/ )
{
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if(pRec[nIndex])
		{
#ifdef _DEBUG
			if( pRec[nIndex]->lDummy )
			{
				ASSERT(FALSE);
			}
#endif
			delete  pRec[nIndex];
		}
	}

	if(pRec)
	{
		delete[] pRec;
		pRec = NULL;
	}

	if(bInitCnt)
	{
		nCount = 0;
	}
}

//*******************************************************************/
/*! Function Name : SerializeUserData
/*! Function      : 
/*! Param         : CArchive &ar, LPBYTE lpData, DWORD dwLen
/*! Return        : void 
/*! Create        : 김창하 , 2005/11/30
/*! Comment       : 
//******************************************************************/
void CGridHeader::SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen )
{
	if( !ar.IsStoring() )							// Read
	{
		Clear();
		DWORD dwReadVersion;
		
		ar >> dwLength;
		ar >> nCount;
		ar >> dwReadVersion;

		LPUSERCELLINFO puserCellInfo;
		LPUSERCELL    pUserCell = NULL;

		puserCellInfo = (USERCELLINFO*)lpData;
		
		LPBYTE lpCellData;
		lpCellData  = lpData + LEN_USERCELL_POS;

		LPGRIDHEADER pRecCell = new GRIDHEADER;
		int nIndex,
			nRecIndex;
		BYTE byReadLen;
		pRec = new GRIDHEADER*[nCount];
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			pRec[nIndex] = new GRIDHEADER;

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			if ( pRecCell )
			{
				// Grid Header Info
				ar >> pRecCell->nRow;
				ar >> pRecCell->nCol;

				ar >> pRecCell->nOrgRow;
				ar >> pRecCell->nOrgCol;

				nRecIndex = pRecCell->nCol-1;

				ar >> byReadLen;
				ar.Read( pRecCell, byReadLen);
				pRecCell->szCaption[byReadLen] = 0x00;

				// Base Info
				SerializeOGBASEITEM(ar, pRecCell->bsItem);
				// MaskInfo
				SerializeMASKINFO(ar, pRecCell->mask);

				// Dummy for GRIDHEADER
				ar >> pRecCell->lDummy;

				pUserCell = (USERCELL*)(lpCellData + (nRecIndex*LEN_USERCELL) ); 

//				pRecCell->nRow     = pRecCell->nRow;
				pRecCell->nCol     = pUserCell->nCol;
//				pRecCell->nOrgRow  = pRecCell->nRow;
				pRecCell->nOrgCol  = pUserCell->nOrgCol;

				int nPos = (pRecCell->nRow-1)*puserCellInfo->nColCount + (pRecCell->nCol-1);
				memcpy ( pRec[nPos], pRecCell,  LEN_GRIDHEADER  );
			}
		}

		delete pRecCell;
	}
}

void CGridHeader::Serialize(CArchive &ar)
{
	if( ar.IsStoring() )							// Write
	{

		ar << dwLength;
		ar << nCount;
		ar << m_dwVersion;

		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			if ( pRec[nIndex] )
			{
				// Grid Header Info
				ar << pRec[nIndex]->nRow;
				ar << pRec[nIndex]->nCol;
				ar << pRec[nIndex]->nOrgRow;
				ar << pRec[nIndex]->nOrgCol;

				ar << (BYTE) lstrlen(pRec[nIndex]->szCaption);
				ar.WriteString((LPCTSTR) pRec[nIndex]->szCaption);
				// Base Info
				SerializeOGBASEITEM(ar, pRec[nIndex]->bsItem);
				// MaskInfo
				SerializeMASKINFO(ar, pRec[nIndex]->mask);
				// Dummy for GRIDHEADER
				ar << pRec[nIndex]->lDummy;
#ifdef _DEBUG
				if( pRec[nIndex]->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}


	}
	else
	{
		Clear();
		DWORD dwReadVersion;
		
		ar >> dwLength;
		ar >> nCount;
		ar >> dwReadVersion;

		BYTE byReadLen;
		pRec = new GRIDHEADER*[nCount];
	
		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRec[nIndex] = new GRIDHEADER;

			if ( pRec[nIndex] )
			{
				// Grid Header Info
				ar >> pRec[nIndex]->nRow;
				ar >> pRec[nIndex]->nCol;
				ar >> pRec[nIndex]->nOrgRow;
				ar >> pRec[nIndex]->nOrgCol;

				ar >> byReadLen;
				ar.Read( pRec[nIndex]->szCaption, byReadLen);
				pRec[nIndex]->szCaption[byReadLen] = 0x00;
				// Base Info
				SerializeOGBASEITEM(ar, pRec[nIndex]->bsItem);
				// MaskInfo
				SerializeMASKINFO(ar, pRec[nIndex]->mask);
				// Dummy
				ar >> pRec[nIndex]->lDummy;
			}
		}
	}
}

void CGridHeader::Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol /*= TRUE*/)
{
	if( nCount <= 0 )
		return;

	if( m_pGrid == NULL )
		return;

	// 전체를 돌면서 바꾼다.
	DWORD nCnt = 1;
	DWORD nIndex, nNewIndex;
	GRIDHEADER** pNewRec = NULL;

	pNewRec = new GRIDHEADER*[nCount];
	
	if(pNewRec)
	{
		DWORD nCmp, 
			  nStepFrom;
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pNewRec[nIndex] = new GRIDHEADER;

			if ( pNewRec[nIndex] == NULL )
				continue;

			if(bMoveCol)
			{
				if(nIndex >= m_pGrid->m_nColCnt)
				{
					nStepFrom = ( (nIndex / m_pGrid->m_nColCnt) * m_pGrid->m_nColCnt ) + nFrom;
				}
				else
				{
					nStepFrom = nFrom;
				}

				nCmp = pRec[nIndex]->nCol;
			}
			else
			{
				if(nIndex >= m_pGrid->m_nRowCnt)
				{
					nStepFrom = ( (nIndex / m_pGrid->m_nRowCnt) * m_pGrid->m_nRowCnt ) + nFrom;
				}
				else
				{
					nStepFrom = nFrom;
				}
				
				nCmp = pRec[nIndex]->nRow;
			}

			if(nFrom < nDest)
			{
				if(nCmp >= nFrom && nCmp < nDest)
					nNewIndex = nIndex + nCnt;
				else if(nCmp == nDest)
					nNewIndex = nStepFrom - 1;
				else
					nNewIndex = nIndex;
			}
			else
			{
				if(nCmp > nDest && nCmp <= nFrom)
					nNewIndex = nIndex - nCnt;
				else if(nCmp == nDest)
					nNewIndex = nStepFrom - 1;
				else
					nNewIndex = nIndex;
			}

			memcpy(pNewRec[nIndex], pRec[nNewIndex], LEN_GRIDHEADER );
			
			if(bMoveCol)
				pNewRec[nIndex]->nCol = (short)nCmp;
			else
				pNewRec[nIndex]->nRow = (short)nCmp;

		}

		Clear(FALSE);
		pRec = pNewRec;
	}
}

// Insert Columns Or Rows
void CGridHeader::Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol /*= TRUE*/)
{
	if( nAddCount <= 0 )
		return;
	if( m_pGrid == NULL )
		return;
	
	GRIDHEADER** pNewRec = NULL;
	int nIndex, nOldIndex;
	int nCurRowCnt, nCurColCnt, nCurHRows, nCurHCols, nCurRowMax, nCurColMax, nCurTotalCount, nNewTotalCount;
	nCurRowCnt		= m_pGrid->m_nRowCnt;
	nCurColCnt		= m_pGrid->m_nColCnt;
	nCurHRows		= m_pGrid->m_nHeaderRowCnt;
	nCurHCols		= m_pGrid->m_nHeaderColCnt;
	nCurRowMax		= nCurHRows * nCurColCnt;
	nCurColMax		= nCurHCols * ( nCurRowCnt - nCurHRows );
	nCurTotalCount	= nCurRowMax + nCurColMax;

	// Column Insert
	if(bInsertCol)
	{
		nNewTotalCount	= nCurTotalCount + (nCurHRows*nAddCount);
//		this->dwLength	= LEN_GRIDHEADERINFO(nNewTotalCount);
//		this->nCount	= nNewTotalCount;

		pNewRec = new GRIDHEADER*[nNewTotalCount];
		ASSERT(pNewRec);

		int nNewRowMax, nNewColCnt;
		nNewColCnt = nCurColCnt + nAddCount;
		nNewRowMax = nCurHRows * nNewColCnt;
	
		nIndex = 0;
		nOldIndex = 0;
		if ( nNewRowMax > 0 )
		{
			for ( int nRow = 0; nRow < nCurHRows; nRow ++ )
			{
				for ( int nCol = 0; nCol < nNewColCnt; nCol ++ )
				{
					pNewRec[nIndex] = new GRIDHEADER;
					if ( pNewRec[nIndex] == NULL )
						continue;
					
					// Insert Point보다 이전인 경우.
					if( nCol +1 < nAddIndex )
					{
						memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_GRIDHEADER);
						nOldIndex++;
					}
					else if( nCol +1 >= nAddIndex && nCol +1 < nAddIndex + nAddCount )
					{
						pNewRec[nIndex]->nRow			= nRow+1;
						pNewRec[nIndex]->nCol			= nCol+1;
						pNewRec[nIndex]->nOrgRow		= nRow+1;
						pNewRec[nIndex]->nOrgCol		= nCol+1;

						pNewRec[nIndex]->szCaption[0]	= 0x00;
						// base info
						InitOGBASEITEM(pNewRec[nIndex]->bsItem, TRUE);
						// MaskInfo
						InitMASKINFO(pNewRec[nIndex]->mask);
						pNewRec[nIndex]->lDummy			= 0L;

					}
					else if( nCol +1 >= nAddIndex + nAddCount )
					{
						memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_GRIDHEADER);
						pNewRec[nIndex]->nCol			= nCol+1;
						nOldIndex++;
					}
					else
					{
						ASSERT(FALSE);
					}
					
					nIndex ++;
				}
			}
		}

		if( nCurColMax )
		{
			pNewRec[nIndex] = new GRIDHEADER[nCurColMax];
			memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_GRIDHEADER*nCurColMax);
		}

		Clear();
		this->dwLength	= LEN_GRIDHEADERINFO(nNewTotalCount);
		this->nCount	= nNewTotalCount;
		pRec = pNewRec;
	}
	else
	{
		nNewTotalCount	= nCurTotalCount + (nCurHCols*nAddCount);
//		this->dwLength	= LEN_GRIDHEADERINFO(nNewTotalCount);
//		this->nCount	= nNewTotalCount;

		pNewRec = new GRIDHEADER*[nNewTotalCount];
		ASSERT(pNewRec);
	
		int nNewColMax, nNewRowCnt;
		nNewRowCnt = nCurRowCnt + nAddCount;
		nNewColMax = nCurHCols * (nNewRowCnt - nCurHRows);
	
		nIndex = 0;
		nOldIndex = 0;
		
		if( nCurRowMax )
		{
			pNewRec[nIndex] = new GRIDHEADER[nCurRowMax];
			memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_GRIDHEADER*nCurRowMax);
			nIndex = nCurRowMax;
			nOldIndex = nCurRowMax;
		}
	
		if ( nNewColMax > 0 )
		{
			for ( int nCol = 0; nCol < nCurHCols; nCol ++ )
			{
				for ( int nRow = nCurHRows; nRow < nNewRowCnt; nRow ++ )
				{
					pNewRec[nIndex] = new GRIDHEADER;
					if ( pNewRec[nIndex] == NULL )
						continue;
					
					// Insert Point보다 이전인 경우.
					if( nRow +1 < nAddIndex )
					{
						memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_GRIDHEADER);
						nOldIndex++;
					}
					else if( nRow +1 >= nAddIndex && nRow +1 < nAddIndex + nAddCount )
					{
						pNewRec[nIndex]->nRow			= nRow+1;
						pNewRec[nIndex]->nCol			= nCol+1;
						pNewRec[nIndex]->nOrgRow		= nRow+1;
						pNewRec[nIndex]->nOrgCol		= nCol+1;

						pNewRec[nIndex]->szCaption[0]	= 0x00;
						// base info
						InitOGBASEITEM(pNewRec[nIndex]->bsItem, TRUE);
						// MaskInfo
						InitMASKINFO(pNewRec[nIndex]->mask);

						pNewRec[nIndex]->lDummy			= 0L;
					}
					else if( nRow +1 >= nAddIndex + nAddCount )
					{
						memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_GRIDHEADER);
						pNewRec[nIndex]->nRow			= nRow+1;
						nOldIndex++;
					}
					else
					{
						ASSERT(FALSE);
					}
					
					nIndex ++;
				}

			}
		}
		
		Clear();
		this->dwLength	= LEN_GRIDHEADERINFO(nNewTotalCount);
		this->nCount	= nNewTotalCount;
		pRec = pNewRec;
	}
}

// Remove Columns Or Rows
void CGridHeader::Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol /*= TRUE*/)
{
	if( nDelCount <= 0 )
		return;
	if( m_pGrid == NULL )
		return;
	
	GRIDHEADER** pNewRec = NULL;
	int nIndex, nOldIndex;
	int nCurRowCnt, nCurColCnt, nCurHRows, nCurHCols, nCurRowMax, nCurColMax, nCurTotalCount, nNewTotalCount;
	nCurRowCnt		= m_pGrid->m_nRowCnt;
	nCurColCnt		= m_pGrid->m_nColCnt;
	nCurHRows		= m_pGrid->m_nHeaderRowCnt;
	nCurHCols		= m_pGrid->m_nHeaderColCnt;
	nCurRowMax		= nCurHRows * nCurColCnt;
	nCurColMax		= nCurHCols * ( nCurRowCnt - nCurHRows );
	nCurTotalCount	= nCurRowMax + nCurColMax;

	// Column Remove
	if(bRemoveCol)
	{
		nNewTotalCount	= nCurTotalCount - (nCurHRows*nDelCount);
//		this->dwLength	= LEN_GRIDHEADERINFO(nNewTotalCount);
//		this->nCount	= nNewTotalCount;

		pNewRec = new GRIDHEADER*[nNewTotalCount];
		ASSERT(pNewRec);

		int nNewRowMax, nNewColCnt;
		nNewColCnt = nCurColCnt - nDelCount;
		nNewRowMax = nCurHRows * nNewColCnt;
	
		nIndex = 0;
		nOldIndex = 0;
		if ( nNewRowMax > 0 )
		{
			for ( int nRow = 0; nRow < nCurHRows; nRow ++ )
			{
				for ( int nCol = 0; nCol < nNewColCnt; nCol ++ )
				{
					pNewRec[nIndex] = new GRIDHEADER;
					if ( pNewRec[nIndex] == NULL )
						continue;
					
					// Delete Point보다 이전인 경우.
					if( nCol +1 < nDelIndex )
					{
						memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_GRIDHEADER);
						nOldIndex++;
					}
					else
					{
						memcpy(pNewRec[nIndex], pRec[nOldIndex+nDelCount], LEN_GRIDHEADER);
						pNewRec[nIndex]->nCol	= nCol+1;
						pNewRec[nIndex]->nOrgCol= nCol+1;

						nOldIndex ++;
					}
					
					nIndex ++;
				}

				nOldIndex += nDelCount;
			}
		}

		if( nCurColMax )
		{
			pNewRec[nIndex] = new GRIDHEADER[nCurColMax];
			memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_GRIDHEADER*nCurColMax);
		}

		Clear();
		this->dwLength	= LEN_GRIDHEADERINFO(nNewTotalCount);
		this->nCount	= nNewTotalCount;
		pRec = pNewRec;
	}
	else
	{
		nNewTotalCount	= nCurTotalCount - (nCurHCols*nDelCount);
//		this->dwLength	= LEN_GRIDHEADERINFO(nNewTotalCount);
//		this->nCount	= nNewTotalCount;

		pNewRec = new GRIDHEADER*[nNewTotalCount];
		ASSERT(pNewRec);
	
		int nNewColMax, nNewRowCnt;
		nNewRowCnt = nCurRowCnt - nDelCount;
		nNewColMax = nCurHCols * (nNewRowCnt - nCurHRows);
	
		nIndex = 0;
		nOldIndex = 0;
		
		if( nCurRowMax )
		{
			pNewRec[nIndex] = new GRIDHEADER[nCurRowMax];
			memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_GRIDHEADER*nCurRowMax);
			nIndex = nCurRowMax;
			nOldIndex = nCurRowMax;
		}
	
		if ( nNewColMax > 0 )
		{
			for ( int nCol = 0; nCol < nCurHCols; nCol ++ )
			{
				for ( int nRow = nCurHRows; nRow < nNewRowCnt; nRow ++ )
				{
					pNewRec[nIndex] = new GRIDHEADER;
					if ( pNewRec[nIndex] == NULL )
						continue;
					
					// Delete Point보다 이전인 경우.
					if( nRow +1 < nDelIndex )
					{
						memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_GRIDHEADER);
						nOldIndex++;
					}
					else
					{
						memcpy(pNewRec[nIndex], pRec[nOldIndex+nDelCount], LEN_GRIDHEADER);
						pNewRec[nIndex]->nRow	= nRow+1;
						pNewRec[nIndex]->nOrgRow= nRow+1;

						nOldIndex ++;
					}

					nIndex ++;
				}

				nOldIndex += nDelCount;
			}
		}
		
		Clear();
		this->dwLength	= LEN_GRIDHEADERINFO(nNewTotalCount);
		this->nCount	= nNewTotalCount;
		pRec = pNewRec;
	}
}

// Copy Columns Or Rows
void CGridHeader::Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol /*= TRUE*/)
{
	if( nCount <= 0 )
		return;

	if( m_pGrid == NULL )
		return;

	int nIndex, nGap, nRowCnt, nColCnt, nHRows, nHCols, nRowMax, nColMax;
	nRowCnt		= m_pGrid->m_nRowCnt;
	nColCnt		= m_pGrid->m_nColCnt;
	nHRows		= m_pGrid->m_nHeaderRowCnt;
	nHCols		= m_pGrid->m_nHeaderColCnt;
	nRowMax		= nHRows * nColCnt;
	nColMax		= nHCols * ( nRowCnt - nHRows );
	nGap		= nDestFrom-nSrcFrom;
	
	if(bCopyCol)
	{
		if( nRowMax > 0 )
		{
			nIndex = 0;
			for ( int nRow = 0; nRow < nHRows; nRow ++ )
			{
				for ( int nCol = 0; nCol < nColCnt; nCol ++ )
				{
					if( nCol + 1 >= nSrcFrom && nCol + 1 <= nSrcTo )
					{
						memcpy(pRec[nIndex+nGap], pRec[nIndex], LEN_GRIDHEADER);
						pRec[nIndex+nGap]->nCol	    = nCol+nGap+1;
						pRec[nIndex+nGap]->nOrgCol	= nCol+nGap+1;
					}
					nIndex ++;
				}
			}
		}
	}
	else
	{
		if ( nColMax > 0 )
		{
			nIndex = nHRows * nColCnt;
			for ( int nCol = 0; nCol < nHCols; nCol ++ )
			{
				for ( int nRow = nHRows; nRow < nRowCnt; nRow ++ )
				{
					if( nRow + 1 >= nSrcFrom && nRow + 1 <= nSrcTo )
					{
						memcpy(pRec[nIndex+nGap], pRec[nIndex], LEN_GRIDHEADER);

						pRec[nIndex+nGap]->nRow	   = nRow+nGap+1;
						pRec[nIndex+nGap]->nOrgRow = nRow+nGap+1;
					}

					nIndex ++;
				}
			}
		}
	}

}
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CGridBody, CObject, 1)
CGridBody::CGridBody() 
{ 
	dwLength		=	0;
	nSubItemCount	=	0;
	nItemCount		=	0;
	pRec			= NULL;
	m_dwVersion		= DEF_VERSION;
	m_pGrid			= NULL;
	
};

//*******************************************************************/
/*! Function Name : CGridBody
/*! Function      : 
/*! Param         : const CGridBody *r
/*! Return        : 
/*! Create        : 김창하 , 2006/02/04
/*! Comment       : 
//******************************************************************/
CGridBody::CGridBody(const CGridBody *r )
{
// --> [Edit]  김창하 2006/04/10

	m_dwVersion		= DEF_VERSION;
	m_pGrid			= NULL;
	pRec			= NULL;

#if FALSE
	if (r)
	{
		*this = *r;
	}
#endif

	dwLength		= r->dwLength;
	nSubItemCount	= r->nSubItemCount;
	nItemCount		= r->nItemCount;
	m_dwVersion		= r->m_dwVersion;

	if( nItemCount > 0)
	{
		pRec = new GRIDBODY**[nSubItemCount];

		for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			pRec[nRow] = new GRIDBODY*[nItemCount];
			
			for ( int nCol = 0 ; nCol < nItemCount; nCol ++ )
			{
				pRec[nRow][nCol] = new GRIDBODY;

				if ( pRec[nRow][nCol] )
				{
					memcpy(pRec[nRow][nCol], r->pRec[nRow][nCol], LEN_GRIDBODY);
				}
			}
		}
	}
	// Member Variable
	m_ItemArray.Copy(r->m_ItemArray);
// <-- [Edit]  김창하 2006/04/10
}

CGridBody::~CGridBody() 
{
	m_ItemArray.RemoveAll();
};

void CGridBody::Initialize()
{
	if(m_pGrid == NULL)
		return;

	short nPos;
	nSubItemCount	= m_pGrid->m_nSubItemCnt;
	nItemCount		= m_pGrid->m_nGridMode == dxHGrid ? m_pGrid->m_nColCnt - m_pGrid->m_nHeaderColCnt :m_pGrid->m_nRowCnt - m_pGrid->m_nHeaderRowCnt;
	dwLength		= LEN_GRIDBODYINFO( nSubItemCount, nItemCount );
	m_dwVersion		= DEF_VERSION;
	
	pRec = new GRIDBODY**[nSubItemCount];

	for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
	{
		nPos = (m_pGrid->m_nGridMode == dxHGrid ? m_pGrid->m_nHeaderColCnt :m_pGrid->m_nHeaderRowCnt) + 1;
		
		pRec[nRow] = new GRIDBODY*[nItemCount];
		
		for ( int nCol = 0 ; nCol < nItemCount; nCol ++ )
		{
			pRec[nRow][nCol] = new GRIDBODY;

			if ( pRec[nRow][nCol] )
			{
				// body info
				pRec[nRow][nCol]->nPos			= nPos + nCol;
				pRec[nRow][nCol]->nOrgPos		= nPos + nCol;			// 원래위치 
				pRec[nRow][nCol]->nSubIndex		= nRow;				

				pRec[nRow][nCol]->nKeyIndex		= DEF_KEY_INDEX;
				pRec[nRow][nCol]->nRBkCrIndex	= DEF_REAL_BKCR_INDEX;
				pRec[nRow][nCol]->nRTxCrIndex	= DEF_REAL_TXCR_INDEX;
				pRec[nRow][nCol]->szItem[0]		= 0x00;
// --> [Edit]  김창하 2006/06/09
				pRec[nRow][nCol]->nFID			= -1;
// <-- [Edit]  김창하 2006/06/09

// --> [Edit]  안경환 2007/03/22
				pRec[nRow][nCol]->szRealItem[0]	= 0x00;
// <-- [Edit]  안경환 2007/03/22


#ifdef FIXLEN_USE
				pRec[nRow][nCol]->szRecName[0]	= 0x00;
#endif
				pRec[nRow][nCol]->bySignFormat	= (BYTE) 0;
				// DataType
				pRec[nRow][nCol]->cDataType		= DEF_CELL_DATATYPE;
				// Attribute Index
//				pRec[nRow][nCol]->nAttrOffset	= DEF_CELL_ATTROFFSET;

				// base info
				InitOGBASEITEM(pRec[nRow][nCol]->bsItem, FALSE);
				// ItemBits
				InitITEMBITS(pRec[nRow][nCol]->ItemBits);
				// GridBits
				InitGRIDBITS(pRec[nRow][nCol]->GridBits);
				// MaskInfo
				InitMASKINFO(pRec[nRow][nCol]->mask);
#ifdef FIXLEN_USE
				// TranBits
				InitTRANBITS(pRec[nRow][nCol]->TrBits);
#endif


// --> [Edit]  안경환 2008/03/26
				pRec[nRow][nCol]->nAttrFid		= -1;
// <-- [Edit]  안경환 2008/03/26


			}
		}
	}
}

const CGridBody& CGridBody::operator=(const CGridBody& other)
{
	if ( &other == this)
		return *this;

	Clear();

	dwLength		= other.dwLength;
	nSubItemCount	= other.nSubItemCount;
	nItemCount		= other.nItemCount;
	m_dwVersion		= other.m_dwVersion;
	

	if(nItemCount > 0)
	{
		pRec = new GRIDBODY**[nSubItemCount];

		for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			pRec[nRow] = new GRIDBODY*[nItemCount];
			
			for ( int nCol = 0 ; nCol < nItemCount; nCol ++ )
			{
				pRec[nRow][nCol] = new GRIDBODY;

				if ( pRec[nRow][nCol] )
				{
					memcpy(pRec[nRow][nCol], other.pRec[nRow][nCol], LEN_GRIDBODY);
				}
			}
		}
	}
	// Member Variable
	m_ItemArray.Copy(other.m_ItemArray);

	return *this;
}


void CGridBody::Clear( BOOL bInitCnt /*= TRUE*/ )
{
	for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
	{
		for ( int nCol = 0 ; nCol < nItemCount; nCol ++ )
		{
			if( pRec[nRow][nCol] )
			{
				delete  pRec[nRow][nCol];
			}
		}

		if(pRec[nRow])
			delete[] pRec[nRow];
	}


	if(pRec)
	{
		delete[] pRec;
		pRec = NULL;
	}

	if( bInitCnt )
	{
		nSubItemCount = 0;
		nItemCount = 0;
	}

	//m_ItemArray.RemoveAll();
}

//*******************************************************************/
/*! Function Name : SerializeUserData
/*! Function      : 
/*! Param         : CArchive &ar, LPBYTE lpData, DWORD dwLen
/*! Return        : void 
/*! Create        : 김창하 , 2005/11/30
/*! Comment       : 
//******************************************************************/
void CGridBody::SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen )
{
	if( !ar.IsStoring() )
	{
		LPUSERCELLINFO puserCellInfo;
		LPUSERCELL    pUserCell = NULL;

		puserCellInfo = (USERCELLINFO*)lpData;
		
		LPBYTE lpCellData;
		lpCellData  = lpData + LEN_USERCELL_POS;

		Clear();
		m_ItemArray.RemoveAll();

		DWORD dwReadVersion;
		int  nIndex = 0,
			 nRow,
			 nCol;

		CMapWordToOb mapIndex;
		BYTE byReadLen;

		ar >> dwLength;
		ar >> nSubItemCount;
		ar >> nItemCount;
		ar >> dwReadVersion;
		
		pRec = new GRIDBODY**[nSubItemCount];

		LPGRIDBODY pRecCell = new GRIDBODY;
		for ( nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			pRec[nRow] = new GRIDBODY*[nItemCount];
			for ( nCol = 0 ; nCol < nItemCount; nCol ++ )
			{
				pRec[nRow][nCol] = new GRIDBODY;
				if ( nRow == 0  )
				{
					pUserCell = (USERCELL*)(lpCellData + (nCol*LEN_USERCELL) ); 
					mapIndex.SetAt ( pUserCell->nOrgCol, (CObject*) nCol );
				}
			}
		}

		for ( nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			for ( nCol = 0 ; nCol < nItemCount; nCol ++ )
			{
				if ( pRecCell )
				{
					// body info
					ar >> pRecCell->nPos;
					ar >> pRecCell->nOrgPos;

					ar >> pRecCell->nSubIndex;
					ar >> pRecCell->nKeyIndex;
					ar >> pRecCell->nRBkCrIndex;
					ar >> pRecCell->nRTxCrIndex;
					ar >> byReadLen;
					ar.ReadString( pRecCell->szItem, byReadLen);
					pRecCell->szItem[byReadLen] = 0x00;
#ifdef FIXLEN_USE
					ar >> byReadLen;
					ar.ReadString( pRecCell->szRecName, byReadLen);
					pRecCell->szRecName[byReadLen] = 0x00;
#endif
					ar >> pRecCell->bySignFormat;
					// DataType
					ar >> pRecCell->cDataType;
					// Attribute Index
//					ar >> pRecCell->nAttrOffset;
					
					// BaseItem
					SerializeOGBASEITEM(ar, pRecCell->bsItem);
					// ItemBits
					SerializeITEMBITS(ar, pRecCell->ItemBits);
					// GridBits
					SerializeGRIDBITS(ar, pRecCell->GridBits);
					// MaskInfo
					SerializeMASKINFO(ar, pRecCell->mask);
#ifdef FIXLEN_USE
					// TranInfo
					SerializeTRANBITS(ar, pRecCell->TrBits);
#endif
// --> [Edit]  김창하 2006/06/09
					ar >> pRecCell->nFID;
					ar >> pRecCell->nAttrFid;
// <-- [Edit]  김창하 2006/06/09

	// --> [Edit]  안경환 2007/03/22
					if( LOWORD(dwReadVersion) >= 12 && HIWORD(dwReadVersion) == 1 )
					{
						ar >> byReadLen;
						ar.ReadString( pRecCell->szRealItem, byReadLen);
						pRecCell->szRealItem[byReadLen] = 0x00;
					}
	// <-- [Edit]  안경환 2007/03/22

				}

				/////////////////////////////////////////////////////////////
				int nColPos(0);
				if ( !mapIndex.Lookup ( pRecCell->nOrgPos, (CObject*&)nColPos ) )
				{
					ASSERT ( FALSE );
					nColPos = 0;
				}
				pUserCell = (USERCELL*)(lpCellData + (nColPos*LEN_USERCELL) ); 

				nColPos           = pUserCell->nIndex;
				pRecCell->nPos    = pUserCell->nCol;
				memcpy ( pRec[nRow][nColPos], pRecCell, LEN_GRIDBODY );

				if( *pRecCell->szItem != 0x00 )
				{
					if ( pRecCell->ItemBits.nItemFlag == dxItemOut || pRecCell->ItemBits.nItemFlag == dxItemInOut )
						m_ItemArray.Add( nIndex );
				}

				nIndex ++;
			}
		}
		delete pRecCell;
	}
}

void CGridBody::Serialize(CArchive &ar)
{
	if( ar.IsStoring() )							// Write
	{
		ar << dwLength;
		ar << nSubItemCount;
		ar << nItemCount;
		ar << m_dwVersion;
		
		for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			for ( int nCol = 0 ; nCol < nItemCount; nCol ++ )
			{
				if ( pRec[nRow][nCol] )
				{
					// body info
					ar << pRec[nRow][nCol]->nPos;
					ar << pRec[nRow][nCol]->nOrgPos;

					ar << pRec[nRow][nCol]->nSubIndex;
					ar << pRec[nRow][nCol]->nKeyIndex;
					ar << pRec[nRow][nCol]->nRBkCrIndex;
					ar << pRec[nRow][nCol]->nRTxCrIndex;
					ar << (BYTE) lstrlen(pRec[nRow][nCol]->szItem);
					ar.WriteString((LPCTSTR) pRec[nRow][nCol]->szItem);

#ifdef FIXLEN_USE
					ar << (BYTE) lstrlen(pRec[nRow][nCol]->szRecName );
					ar.WriteString((LPCTSTR) pRec[nRow][nCol]->szRecName );
#endif
					ar << pRec[nRow][nCol]->bySignFormat;
					// DataType
					ar << pRec[nRow][nCol]->cDataType;
					// Attribute Index
//					ar << pRec[nRow][nCol]->nAttrOffset;
					// BaseItem
					SerializeOGBASEITEM(ar, pRec[nRow][nCol]->bsItem);
					// ItemBits
					SerializeITEMBITS(ar, pRec[nRow][nCol]->ItemBits);
					// GridBits
					SerializeGRIDBITS(ar, pRec[nRow][nCol]->GridBits);
					// MaskInfo
					SerializeMASKINFO(ar, pRec[nRow][nCol]->mask);
#ifdef FIXLEN_USE
					// TranInfo
					SerializeTRANBITS(ar, pRec[nRow][nCol]->TrBits);
#endif
// --> [Edit]  김창하 2006/06/09
					// FidNum
					ar << (short)( pRec[nRow][nCol]->szItem[0] == 0x0 ? -1 : pRec[nRow][nCol]->nFID     );
					// Fid Attribute fid
					ar << (short)( pRec[nRow][nCol]->szItem[0] == 0x0 ? -1 : pRec[nRow][nCol]->nAttrFid );

	// --> [Edit]  안경환 2007/03/22
					// RealItem name
					ar << (BYTE) lstrlen(pRec[nRow][nCol]->szRealItem);
					ar.WriteString((LPCTSTR) pRec[nRow][nCol]->szRealItem);
	// <-- [Edit]  안경환 2007/03/22


// <-- [Edit]  김창하 2006/06/09
				}
			}
		}
	}
	else														// Read
	{
		Clear();
		m_ItemArray.RemoveAll();
		DWORD dwReadVersion;
		int  nIndex = 0;
		BYTE byReadLen;
		ar >> dwLength;
		ar >> nSubItemCount;
		ar >> nItemCount;
		ar >> dwReadVersion;
		
		pRec = new GRIDBODY**[nSubItemCount];

		for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			pRec[nRow] = new GRIDBODY*[nItemCount];

			for ( int nCol = 0 ; nCol < nItemCount; nCol ++ )
			{
				pRec[nRow][nCol] = new GRIDBODY;

				if ( pRec[nRow][nCol] )
				{
					// body info
					ar >> pRec[nRow][nCol]->nPos;
					ar >> pRec[nRow][nCol]->nOrgPos;

					ar >> pRec[nRow][nCol]->nSubIndex;
					ar >> pRec[nRow][nCol]->nKeyIndex;
					ar >> pRec[nRow][nCol]->nRBkCrIndex;
					ar >> pRec[nRow][nCol]->nRTxCrIndex;

					ar >> byReadLen;
					ar.ReadString( pRec[nRow][nCol]->szItem, byReadLen);
					pRec[nRow][nCol]->szItem[byReadLen] = 0x00;

#ifdef FIXLEN_USE
					ar >> byReadLen;
					ar.ReadString( pRec[nRow][nCol]->szRecName, byReadLen);
					pRec[nRow][nCol]->szRecName[byReadLen] = 0x00;
#endif
					ar >> pRec[nRow][nCol]->bySignFormat;
					// DataType
					ar >> pRec[nRow][nCol]->cDataType;
					// Attribute Index
//					ar >> pRec[nRow][nCol]->nAttrOffset;

					// BaseItem
					SerializeOGBASEITEM(ar, pRec[nRow][nCol]->bsItem);
					// ItemBits
					SerializeITEMBITS(ar, pRec[nRow][nCol]->ItemBits);
					// GridBits
					SerializeGRIDBITS(ar, pRec[nRow][nCol]->GridBits);
					// MaskInfo
					SerializeMASKINFO(ar, pRec[nRow][nCol]->mask);
#ifdef FIXLEN_USE
					// TranInfo
					SerializeTRANBITS(ar, pRec[nRow][nCol]->TrBits);
#endif
// --> [Edit]  김창하 2006/06/09
					// nFID
					ar >> pRec[nRow][nCol]->nFID;
					// fid attribute fid
					ar >> pRec[nRow][nCol]->nAttrFid;


	// --> [Edit]  안경환 2007/03/22
					if( LOWORD(dwReadVersion) >= 12 && HIWORD(dwReadVersion) == 1 )
					{
						ar >> byReadLen;
						ar.ReadString( pRec[nRow][nCol]->szRealItem, byReadLen);
						pRec[nRow][nCol]->szRealItem[byReadLen] = 0x00;
					}
	// <-- [Edit]  안경환 2007/03/22

// <-- [Edit]  김창하 2006/06/09
					
					if( *pRec[nRow][nCol]->szItem != 0x00 )
					{
						if ( pRec[nRow][nCol]->ItemBits.nItemFlag == dxItemOut || pRec[nRow][nCol]->ItemBits.nItemFlag == dxItemInOut )
							m_ItemArray.Add( nIndex );
					}

					nIndex ++;
				}
			}
		}

	}
}


//*****************************************************************************
// 루    틴    명  :  GetFlushItemListArray
// 기          능  :  
// 입          력  :  없음
// 출          력  :  없음
// 작    성    자  :  2003년8월28일    김  창하 (주) 한국 소리마치
// 수  정  이  력  :  
//*****************************************************************************
int CGridBody::GetFlushItemListArray()
{
	int nIndex    = 0;
	
	m_ItemArray.RemoveAll();

	for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
	{
		for ( int nCol = 0 ; nCol < nItemCount; nCol ++ )
		{
			if ( pRec[nRow][nCol]->szItem[0] != 0x00 )
			{
				if ( pRec[nRow][nCol]->ItemBits.nItemFlag == dxItemOut || pRec[nRow][nCol]->ItemBits.nItemFlag == dxItemInOut )
					m_ItemArray.Add( nIndex );
			}
			nIndex++;
		}
	}
	return m_ItemArray.GetSize();
}

//*****************************************************************************
// 루    틴    명  :  GetBaseBoolBitCheck 
// 기          능  :  메모,CodeDrag,참조 정보를 사용하는 Cell이 존재하는 가를 체크한다.
//*****************************************************************************
long CGridBody::GetBaseBoolBitCheck ( long dwBaseboolBit )
{
	ITEMBITS ItemBits;
	BOOL	bKeyUse		= FALSE,
			bSubKeyUse	= FALSE,
			bThirdKeyUse= FALSE,
			bMemoUse	= FALSE,
		    bCodeDrag	= FALSE,
			bCellRef	= FALSE,
			bSignalUse	= FALSE,
			bTooltip	= FALSE,
			bCelltip	= FALSE,
			bSumCol		= FALSE,
			bCodeLink	= FALSE,
			bOrderLink	= FALSE,
			bAutoMaskUse= FALSE;


	// 실시간 조건을 사용하는가?
//	if ( m_pGrid->m_pRealCon != NULL )
//	{
//		if ( m_pGrid->m_pRealCon->nRecCount > 1 && m_pGrid->m_pRealCon->nConCount > 1 )
//		{
//			dwBaseboolBit |= BASE_BBIT_USE_REALCONDITION;
//		}
//	}
	
	// 참조정보를 사용하는가?
	if ( m_pGrid->m_pNewRefer != NULL )
	{
		if ( m_pGrid->m_pNewRefer->nCount > 0 )
		{
			dwBaseboolBit |= BASE_BBIT_USE_CELLREF;
		}
	}

	for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
	{
		for ( int nCol = 0 ; nCol < nItemCount; nCol ++ )
		{
//			if ( pRec[nRow][nCol]->GridBits.bNumberCol )					// SEQNumber 사용. 
//			{
//				dwBaseboolBit |= BASE_BBIT_USE_NUMBERCOL;
//			}

			if ( pRec[nRow][nCol]->bsItem.nCtrlID  == dxCtrlHBongChart )	// 가로봉. 
			{
				dwBaseboolBit |= BASE_BBIT_USE_HCHARTBONG;
			}

			if ( pRec[nRow][nCol]->bsItem.nCtrlID  == dxCtrlVBongChart )	// 세로봉. 
			{
				dwBaseboolBit |= BASE_BBIT_USE_VCHARTBONG;
			}

			if ( pRec[nRow][nCol]->bsItem.nCtrlID  == dxCtrlBMPBtn )		// Bitmap Button
			{
				dwBaseboolBit |= BASE_BBIT_USE_IMAGEBTN;
			}
			
			ItemBits = pRec[nRow][nCol]->ItemBits;

#if FALSE
			// 각 셀에 참조사용 유무룰 마크한다.
			ItemBits.bReferOwner = FALSE;
			if ( dwBaseboolBit & BASE_BBIT_USE_CELLREF )
			{
				if ( pRec[nRow][nCol]->szItem[0] != 0x00 )
				{
					NEWREFERTYPE* lpNewRefType;
					lpNewRefType = m_pGrid->m_pNewRefer->GetNewReferType ( pRec[nRow][nCol]->szItem, pRec[nRow][nCol]->nKeyIndex );
					if ( lpNewRefType != NULL )
					{
						pRec[nRow][nCol]->ItemBits.bReferOwner = TRUE;
					}
				}
			}
#endif
			// Key 사용유무. 
			if ( !bKeyUse && ItemBits.bIsKeyItem )
			{
				bKeyUse = TRUE;
				dwBaseboolBit |= BASE_BBIT_USE_KEY;
			}
			// SubKey 사용유무. 
			if ( !bSubKeyUse && ItemBits.bIsSubKeyItem )
			{
				bSubKeyUse = TRUE;
				dwBaseboolBit |= BASE_BBIT_USE_SUBKEY;
			}
			// ThirdKey 사용유무. 
			if ( !bThirdKeyUse && ItemBits.bIsThirdKeyItem )
			{
				bThirdKeyUse = TRUE;
				dwBaseboolBit |= BASE_BBIT_USE_THIRDKEY;
			}
			// Code Drag사용유무 .
			if ( !bCodeDrag && pRec[nRow][nCol]->GridBits.bDragCol ||  pRec[nRow][nCol]->GridBits.bDragNameCol)
			{
				bCodeDrag = TRUE;
				dwBaseboolBit |= BASE_BBIT_USE_CODEDRAG;
			}
			// 메모 사용유무. 
			if ( !bMemoUse && ItemBits.bMemo  )
			{
				bMemoUse = TRUE;
				dwBaseboolBit |= BASE_BBIT_USE_MEMO;
			}
// --> [Edit]  안경환 2010/11/20 // 자동가격마스크추가
			// 자동마스킹 컬럼 사용유무
			if ( !bAutoMaskUse && ItemBits.bAutoPriceMask )
			{
				bAutoMaskUse = TRUE;
				dwBaseboolBit |= BASE_BBIT_USE_AUTOPRICE;
			}
//			// 해외용 마스크가 지정된경우 자동마스킹을 설정한다.
//			if(pRec[nRow][nCol]->mask.nFormat == dxFmt_DecimalToString
//				|| pRec[nRow][nCol]->mask.nFormat == dxFmt_LogToString
//				|| pRec[nRow][nCol]->mask.nFormat == dxFmt_GLToSpotString )
//			{
//				dwBaseboolBit |= BASE_BBIT_USE_AUTOPRICE;
//			}
// <-- [Edit]  안경환 2010/11/20

			// 참조 셀 사용유무 .
//			if ( !bCellRef && ItemBits.bReferOwner )
//			{
//				bCellRef = TRUE;
//				dwBaseboolBit |= BASE_BBIT_USE_CELLREF;
//			}

			// Tooltip사용 유무. 
			if (!bTooltip && (pRec[nRow][nCol]->bsItem.BaseBits.nToolTip > 0 ) )
			{
				bTooltip = TRUE;
				dwBaseboolBit |= BASE_BBIT_USE_TOOLTIP;
			}
			// CellTip사용 유무. 
			if (!bCelltip && pRec[nRow][nCol]->GridBits.bCellTip )
			{
				bCelltip = TRUE;
				dwBaseboolBit |= BASE_BBIT_USE_CELLTIP;
			}
			// 종목연계.
			if ( !bCodeLink && ItemBits.bCodeLink )
			{
				bCellRef = TRUE;
				dwBaseboolBit |= BASE_BBIT_USE_CODELINK;
			}
			// 주문연계.
			if ( !bOrderLink && ItemBits.bOrderLink )
			{
				bCellRef = TRUE;
				dwBaseboolBit |= BASE_BBIT_USE_ORDERLINK;
			}
		}
	}

	return dwBaseboolBit;
}

//*****************************************************************************
// 루    틴    명  :  GetKeyIndexCount
// 기          능  :  Key Index 갯수를 구한다.
//*****************************************************************************
short CGridBody::GetKeyIndexCount( )
{
	CMapWordToPtr mapKeyCnt;
	mapKeyCnt.RemoveAll();

	for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
	{
		for ( int nCol = 0 ; nCol < nItemCount; nCol ++ )
		{
			if( pRec[nRow][nCol] ) 
				mapKeyCnt.SetAt(pRec[nRow][nCol]->nKeyIndex, (void*) NULL);
		}
	}

	return mapKeyCnt.GetCount();
}

LPCTSTR	CGridBody::GetKeyItem(short nKeyIndex /*= 0*/)
{
	for ( short nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
	{
		for ( short nCol = 0 ; nCol < nItemCount; nCol ++ )
		{
			if( pRec[nRow][nCol]->ItemBits.bIsKeyItem )
			{
				if( pRec[nRow][nCol]->nKeyIndex == nKeyIndex )
					return pRec[nRow][nCol]->szItem;
			}
		}
	}
	return NULL;
}

LPCTSTR	CGridBody::GetSubKeyItem(short nKeyIndex /*= 0*/)
{
	for ( short nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
	{
		for ( short nCol = 0 ; nCol < nItemCount; nCol ++ )
		{
			if( pRec[nRow][nCol]->ItemBits.bIsSubKeyItem )
			{
				if( pRec[nRow][nCol]->nKeyIndex == nKeyIndex )
					return pRec[nRow][nCol]->szItem;
			}
		}
	}
	return NULL;
}

LPCTSTR	CGridBody::GetThirdKeyItem(short nKeyIndex /*= 0*/)
{
	for ( short nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
	{
		for ( short nCol = 0 ; nCol < nItemCount; nCol ++ )
		{
			if( pRec[nRow][nCol]->ItemBits.bIsThirdKeyItem )
			{
				if( pRec[nRow][nCol]->nKeyIndex == nKeyIndex )
					return pRec[nRow][nCol]->szItem;
			}
		}
	}
	return NULL;
}

LPGRIDBODY	CGridBody::GetBodyRecordInfo( short nKeyIndex, LPCTSTR lpszItem )
{
	for ( short nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
	{
		for ( short nCol = 0 ; nCol < nItemCount; nCol ++ )
		{
			if( pRec[nRow][nCol]->szItem[0] != 0x00 )
			{
				if( pRec[nRow][nCol]->nKeyIndex == nKeyIndex && strcmp( pRec[nRow][nCol]->szItem,  lpszItem ) == 0 )
						return pRec[nRow][nCol];
			}
		}
	}
	return NULL;
}
//*****************************************************************************
// 루    틴    명  :  GetKeyIndexMinMaxPos
// 기          능  :  Key Index 갯수를 구한다.
//*****************************************************************************
BOOL CGridBody::GetKeyIndexMinMaxPos(unsigned short nKeyIndex, unsigned short& nMinPos, unsigned short& nMaxPos)
{
	if(m_pGrid)
	{
		nMinPos = USHRT_MAX;
		nMaxPos = 0;

		for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			for ( int nCol = 0 ; nCol < nItemCount; nCol ++ )
			{
				if( pRec[nRow][nCol] && nKeyIndex == pRec[nRow][nCol]->nKeyIndex)
				{
					if( nMinPos > nCol )
						nMinPos = nCol;
					
					if( nMaxPos < nCol )
						nMaxPos = nCol;
				}
			}
		}

		// Key인덱스를 못찾은경우.
		if(nMinPos == USHRT_MAX && 	nMaxPos == 0)
			return FALSE;

		nMinPos += (m_pGrid->m_nGridMode == dxHGrid ? m_pGrid->m_nHeaderColCnt : m_pGrid->m_nHeaderRowCnt) +1;
		nMaxPos += (m_pGrid->m_nGridMode == dxHGrid ? m_pGrid->m_nHeaderColCnt : m_pGrid->m_nHeaderRowCnt) +1;
		return TRUE;
	}

	return FALSE;
}

void CGridBody::Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol /*= TRUE*/)
{
	if( nSubItemCount <= 0 || nItemCount <= 0 )
		return;

	if(m_pGrid == NULL)
		return;

	// 전체를 돌면서 바꾼다.
	DWORD nCnt = 1;
	DWORD nRow(0), 
		  nCol(0), 
		  nNewCol(0), 
		  nStartCol(0);
#if 0
	LPGRIDBODY pRecCell = new GRIDBODY;
	LPGRIDBODY pFromRec,
		       pToRec;
	
	for ( nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
	{
		if( nFrom < nDest )					// left->Right
		{
			nCnt = nDest - nFrom;
		}
		else
		{
			nCnt = nFrom - nDest;
		}

		if ( nCnt == 1 )
		{
			pFromRec = pRec[nRow][nFrom-1];
			pFromRec->nPos = nDest;
				
			pToRec   = pRec[nRow][nDest-1];
			memcpy( pRecCell, pRec[nRow][nDest-1], LEN_GRIDBODY );
			pRecCell->nPos = nFrom;

			memcpy( pToRec,   pFromRec, LEN_GRIDBODY );
			memcpy( pFromRec, pRecCell, LEN_GRIDBODY );
		}
		else
		{
			if( nFrom < nDest )					// left->Right
			{
				
			}
			else								// right->left
			{
				for ( nCol = nFrom; nCol > nDest; nCol--  )
				{
					pFromRec = pRec[nRow][nCol-1];
					pFromRec->nPos   = nCol-1;	// Move
					
					pToRec   = pRec[nRow][nCol-2];

					memcpy( pRecCell, pRec[nRow][nCol-2], LEN_GRIDBODY );
					pRecCell->nPos   = nCol;

					memcpy( pToRec,   pFromRec, LEN_GRIDBODY );
					memcpy( pFromRec, pRecCell, LEN_GRIDBODY );
				}
			}
		}
	}

	if ( pRecCell )
		delete pRecCell;
#else

	GRIDBODY*** pNewRec = NULL;
	pNewRec = new GRIDBODY**[nSubItemCount];

	nStartCol = ( bMoveCol ? m_pGrid->m_nHeaderColCnt : m_pGrid->m_nHeaderRowCnt ) + 1;
	if(pNewRec)
	{
		for ( nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			pNewRec[nRow] = new GRIDBODY*[nItemCount];
			
			for ( nCol = nStartCol; nCol < nItemCount + nStartCol; nCol ++ )
			{
				pNewRec[nRow][nCol-nStartCol] = new GRIDBODY;

				if ( pNewRec[nRow][nCol-nStartCol] == NULL )
					continue;

				if(nFrom < nDest)
				{
					if( nCol >= nFrom && nCol < nDest )
						nNewCol = nCol - nStartCol + nCnt;
					else if( nCol == nDest )
						nNewCol = nFrom - nStartCol;
					else
						nNewCol = nCol - nStartCol;
				}
				else
				{
					if( nCol > nDest && nCol <= nFrom)
						nNewCol = nCol - nStartCol - nCnt;
					else if( nCol == nDest)
						nNewCol = nFrom - nStartCol;
					else
						nNewCol = nCol - nStartCol;
				}
				memcpy(pNewRec[nRow][nCol-nStartCol], pRec[nRow][nNewCol], LEN_GRIDBODY);
				pNewRec[nRow][nCol-nStartCol]->nPos    = (short)nCol;

//				pNewRec[nRow][nCol-nStartCol]->nOrgPos = nCol;
//				pNewRec[nRow][nCol-nStartCol]->lDummy  = 0L;

			}
		}
		Clear(FALSE);
		//nSubItemCount = DEF_SUBITEM_COUNT;
		//nItemCount = nCol - 1;
		pRec = pNewRec;
	}
#endif
}

// Insert Columns Or Rows
void CGridBody::Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol /*= TRUE*/)
{
	if( nSubItemCount <= 0 || nItemCount <= 0 )
		return;

	if(m_pGrid == NULL)
		return;

	int nCurRowCnt, nCurColCnt, nCurHRows, nCurHCols, nSubItemCount, nItemCount, nStart;
	nCurRowCnt		= m_pGrid->m_nRowCnt;
	nCurColCnt		= m_pGrid->m_nColCnt;
	nCurHRows		= m_pGrid->m_nHeaderRowCnt;
	nCurHCols		= m_pGrid->m_nHeaderColCnt;
	nSubItemCount	= m_pGrid->m_nSubItemCnt;
	
	GRIDBODY*** pNewRec = NULL;
	// Column Insert
	if(bInsertCol)
	{
		nItemCount = nCurColCnt - nCurHCols + nAddCount;
//		this->dwLength		= LEN_GRIDBODYINFO( nSubItemCount, nItemCount );
//		this->nSubItemCount = nSubItemCount;
//		this->nItemCount	= nItemCount;

		pNewRec = new GRIDBODY**[nSubItemCount];

		nStart = nCurHCols + 1;
		for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			pNewRec[nRow] = new GRIDBODY*[nItemCount];

			int nOldCol = 0;
			for ( int nCol = 0; nCol < nItemCount; nCol ++ )
			{
				pNewRec[nRow][nCol] = new GRIDBODY;

				if ( pNewRec[nRow][nCol] == NULL )
				{
					ASSERT(FALSE);
					continue;
				}

				// Insert Point보다 이전인 경우.
				if( nCol + nStart < nAddIndex )
				{
					memcpy(pNewRec[nRow][nCol], pRec[nRow][nOldCol], LEN_GRIDBODY);
					//pNewRec[nRow][nCol]->nPos = nCol + nStart;
					nOldCol++;
				}
				else if( nCol + nStart >= nAddIndex && nCol + nStart < nAddIndex + nAddCount )
				{
					// body info
					pNewRec[nRow][nCol]->nPos			= nCol + nStart;
					pNewRec[nRow][nCol]->nOrgPos		= nCol + nStart;

					pNewRec[nRow][nCol]->nSubIndex		= nRow;
					pNewRec[nRow][nCol]->nKeyIndex		= DEF_KEY_INDEX;
					pNewRec[nRow][nCol]->nRBkCrIndex	= DEF_REAL_BKCR_INDEX;
					pNewRec[nRow][nCol]->nRTxCrIndex	= DEF_REAL_TXCR_INDEX;
					pNewRec[nRow][nCol]->szItem[0]		= 0x00;
// --> [Edit]  김창하 2006/06/09
					pNewRec[nRow][nCol]->nFID			= -1;
// <-- [Edit]  김창하 2006/06/09

// --> [Edit]  안경환 2007/03/22
					pNewRec[nRow][nCol]->szRealItem[0]	= 0x00;
// <-- [Edit]  안경환 2007/03/22

#ifdef FIXLEN_USE
					pNewRec[nRow][nCol]->szRecName[0]	= 0x00;
#endif
					pNewRec[nRow][nCol]->bySignFormat	= (BYTE) 0;
					// DataType
					pNewRec[nRow][nCol]->cDataType		= DEF_CELL_DATATYPE;
					// Attribute Index
//					pNewRec[nRow][nCol]->nAttrOffset	= DEF_CELL_ATTROFFSET;

					// base info
					InitOGBASEITEM(pNewRec[nRow][nCol]->bsItem, FALSE);
					// ItemBits
					InitITEMBITS(pNewRec[nRow][nCol]->ItemBits);
					// GridBits
					InitGRIDBITS(pNewRec[nRow][nCol]->GridBits);
					// MaskInfo
					InitMASKINFO(pNewRec[nRow][nCol]->mask);
#ifdef FIXLEN_USE
					// TranBits
					InitTRANBITS(pNewRec[nRow][nCol]->TrBits);
#endif

// --> [Edit]  김창하 2006/06/09
					// Dummy
					pNewRec[nRow][nCol]->nAttrFid		= -1;
// <-- [Edit]  김창하 2006/06/09
				}
				else if( nCol + nStart >= nAddIndex + nAddCount )
				{
					memcpy(pNewRec[nRow][nCol], pRec[nRow][nOldCol], LEN_GRIDBODY);
					pNewRec[nRow][nCol]->nPos   = nCol + nStart;
					
//					pNewRec[nRow][nCol]->nOrgPos = nCol + nStart;
//					pNewRec[nRow][nCol]->lDummy  = 0L;
					nOldCol++;
				}
				else
				{
					ASSERT(FALSE);
				}
			}
		}

		Clear();
		this->dwLength		= LEN_GRIDBODYINFO( nSubItemCount, nItemCount );
		this->nSubItemCount = nSubItemCount;
		this->nItemCount	= nItemCount;
		pRec = pNewRec;
	}
	else
	{
		nItemCount = nCurRowCnt - nCurHRows + nAddCount;
//		this->dwLength		= LEN_GRIDBODYINFO( nSubItemCount, nItemCount );
//		this->nSubItemCount = nSubItemCount;
//		this->nItemCount	= nItemCount;

		pNewRec = new GRIDBODY**[nSubItemCount];

		nStart = nCurHRows + 1;
		for ( int nCol = 0 ; nCol < nSubItemCount ; nCol ++ )
		{
			pNewRec[nCol] = new GRIDBODY*[nItemCount];

			int nOldRow = 0;
			for ( int nRow = 0; nRow < nItemCount; nRow ++ )
			{
				pNewRec[nCol][nRow] = new GRIDBODY;

				if ( pNewRec[nCol][nRow] == NULL )
				{
					ASSERT(FALSE);
					continue;
				}

				// Insert Point보다 이전인 경우.
				if( nRow + nStart < nAddIndex )
				{
					memcpy(pNewRec[nCol][nRow], pRec[nCol][nOldRow], LEN_GRIDBODY);
					//pNewRec[nRow][nCol]->nPos = nCol + nStart;
					nOldRow++;
				}
				else if( nRow + nStart >= nAddIndex && nRow + nStart < nAddIndex + nAddCount )
				{
					// body info
					pNewRec[nCol][nRow]->nPos			= nRow + nStart;
					pNewRec[nRow][nCol]->nOrgPos		= nRow + nStart;

					pNewRec[nCol][nRow]->nSubIndex		= nCol;
					pNewRec[nCol][nRow]->nKeyIndex		= DEF_KEY_INDEX;
					pNewRec[nCol][nRow]->nRBkCrIndex	= DEF_REAL_BKCR_INDEX;
					pNewRec[nCol][nRow]->nRTxCrIndex	= DEF_REAL_TXCR_INDEX;
					pNewRec[nCol][nRow]->szItem[0]		= 0x00;
// --> [Edit]  김창하 2006/06/09
					pNewRec[nCol][nRow]->nFID			= -1;
// <-- [Edit]  김창하 2006/06/09

// --> [Edit]  안경환 2007/03/22
					pNewRec[nCol][nRow]->szRealItem[0]	= 0x00;
// <-- [Edit]  안경환 2007/03/22


#ifdef FIXLEN_USE
					pNewRec[nCol][nRow]->szRecName[0]	= 0x00;
#endif
					pNewRec[nCol][nRow]->bySignFormat	= (BYTE) 0;
					// DataType
					pNewRec[nRow][nCol]->cDataType		= DEF_CELL_DATATYPE;
					// Attribute Index
//					pNewRec[nRow][nCol]->nAttrOffset	= DEF_CELL_ATTROFFSET;
					// base info
					InitOGBASEITEM(pNewRec[nCol][nRow]->bsItem, FALSE);
					// ItemBits
					InitITEMBITS(pNewRec[nCol][nRow]->ItemBits);
					// GridBits
					InitGRIDBITS(pNewRec[nCol][nRow]->GridBits);
					// MaskInfo
					InitMASKINFO(pNewRec[nCol][nRow]->mask);
#ifdef FIXLEN_USE
					// TranBits
					InitTRANBITS(pNewRec[nCol][nRow]->TrBits);
#endif
// --> [Edit]  김창하 2006/06/09
					// Dummy
					pNewRec[nCol][nRow]->nAttrFid		= -1;
// <-- [Edit]  김창하 2006/06/09
					
				}
				else if( nRow + nStart >= nAddIndex + nAddCount )
				{
					memcpy(pNewRec[nCol][nRow], pRec[nRow][nOldRow], LEN_GRIDBODY);
					pNewRec[nCol][nRow]->nPos    = nRow + nStart;
					
	//				pNewRec[nCol][nRow]->nOrgPos = nRow + nStart;
	//				pNewRec[nCol][nRow]->lDummy  = 0L;

					nOldRow++;
				}
				else
				{
					ASSERT(FALSE);
				}
			}
		}

		Clear();
		this->dwLength		= LEN_GRIDBODYINFO( nSubItemCount, nItemCount );
		this->nSubItemCount = nSubItemCount;
		this->nItemCount	= nItemCount;
		pRec = pNewRec;
	}
}

// Remove Columns Or Rows
void CGridBody::Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol /*= TRUE*/)
{
	if( nSubItemCount <= 0 || nItemCount <= 0 )
		return;

	if(m_pGrid == NULL)
		return;

	int nCurRowCnt, nCurColCnt, nCurHRows, nCurHCols, nSubItemCount, nItemCount, nStart;
	nCurRowCnt		= m_pGrid->m_nRowCnt;
	nCurColCnt		= m_pGrid->m_nColCnt;
	nCurHRows		= m_pGrid->m_nHeaderRowCnt;
	nCurHCols		= m_pGrid->m_nHeaderColCnt;
	nSubItemCount	= m_pGrid->m_nSubItemCnt;
	
	GRIDBODY*** pNewRec = NULL;
	// Column Insert
	if(bRemoveCol)
	{
		nItemCount = nCurColCnt - nCurHCols - nDelCount;
//		this->dwLength		= LEN_GRIDBODYINFO( nSubItemCount, nItemCount );
//		this->nSubItemCount = nSubItemCount;
//		this->nItemCount	= nItemCount;

		pNewRec = new GRIDBODY**[nSubItemCount];

		nStart = nCurHCols + 1;
		for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			pNewRec[nRow] = new GRIDBODY*[nItemCount];

			int nOldCol = 0;
			for ( int nCol = 0; nCol < nItemCount; nCol ++ )
			{
				pNewRec[nRow][nCol] = new GRIDBODY;

				if ( pNewRec[nRow][nCol] == NULL )
				{
					ASSERT(FALSE);
					continue;
				}

				// Delete Point보다 이전인 경우.
				if( nCol + nStart < nDelIndex )
				{
					memcpy(pNewRec[nRow][nCol], pRec[nRow][nOldCol], LEN_GRIDBODY);
					//pNewRec[nRow][nCol]->nPos = nCol + nStart;
					nOldCol++;
				}
				else
				{
					memcpy(pNewRec[nRow][nCol], pRec[nRow][nOldCol+nDelCount], LEN_GRIDBODY);
					pNewRec[nRow][nCol]->nPos    = nCol + nStart;
					
//					pNewRec[nRow][nCol]->nOrgPos = nCol + nStart;
//					pNewRec[nRow][nCol]->lDummy  = 0L;

					nOldCol++;
				}
			}

			nOldCol += nDelCount;
		}

		Clear();
		this->dwLength		= LEN_GRIDBODYINFO( nSubItemCount, nItemCount );
		this->nSubItemCount = nSubItemCount;
		this->nItemCount	= nItemCount;
		pRec = pNewRec;
	}
	else
	{
		nItemCount = nCurRowCnt - nCurHRows - nDelCount;
//		this->dwLength		= LEN_GRIDBODYINFO( nSubItemCount, nItemCount );
//		this->nSubItemCount = nSubItemCount;
//		this->nItemCount	= nItemCount;

		pNewRec = new GRIDBODY**[nSubItemCount];

		nStart = nCurHRows + 1;
		for ( int nCol = 0 ; nCol < nSubItemCount ; nCol ++ )
		{
			pNewRec[nCol] = new GRIDBODY*[nItemCount];

			int nOldRow = 0;
			for ( int nRow = 0; nRow < nItemCount; nRow ++ )
			{
				pNewRec[nCol][nRow] = new GRIDBODY;

				if ( pNewRec[nCol][nRow] == NULL )
				{
					ASSERT(FALSE);
					continue;
				}

				// Delete Point보다 이전인 경우.
				if( nRow + nStart < nDelIndex )
				{
					memcpy(pNewRec[nCol][nRow], pRec[nCol][nOldRow], LEN_GRIDBODY);
					//pNewRec[nRow][nCol]->nPos = nRow + nStart;
					nOldRow++;
				}
				else
				{
					memcpy(pNewRec[nCol][nRow], pRec[nCol][nOldRow+nDelCount], LEN_GRIDBODY);
					pNewRec[nCol][nRow]->nPos    = nRow + nStart;

//					pNewRec[nCol][nRow]->nOrgPos = nRow + nStart;
//					pNewRec[nCol][nRow]->lDummy  = 0L;

					nOldRow++;
				}
			}
			
			nOldRow += nDelCount;
		}

		Clear();
		this->dwLength		= LEN_GRIDBODYINFO( nSubItemCount, nItemCount );
		this->nSubItemCount = nSubItemCount;
		this->nItemCount	= nItemCount;
		pRec = pNewRec;
	}
}

// Copy Columns Or Rows
void CGridBody::Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol /*= TRUE*/)
{
	if( nSubItemCount <= 0 || nItemCount <= 0 )
		return;

	if(m_pGrid == NULL)
		return;

	int nGap, nHRows, nHCols, nStart;
	nHRows			= m_pGrid->m_nHeaderRowCnt;
	nHCols			= m_pGrid->m_nHeaderColCnt;
	nGap			= nDestFrom-nSrcFrom;
	
	if(bCopyCol)
	{
		nStart = nHCols + 1;
		for ( int nRow = 0 ; nRow < nSubItemCount ; nRow ++ )
		{
			for ( int nCol = 0; nCol < nItemCount; nCol ++ )
			{
				if( nCol + nStart >= nSrcFrom && nCol + nStart <= nSrcTo )
				{
					memcpy(pRec[nRow][nCol+nGap], pRec[nRow][nCol], LEN_GRIDBODY);
					pRec[nRow][nCol+nGap]->nPos    = nCol + nStart + nGap;

//					pRec[nRow][nCol+nGap]->nOrgPos = nCol + nStart + nGap;
//					pRec[nRow][nCol+nGap]->lDummy  = 0;
				}

			}
		}
	}
	else
	{
		nStart = nHRows + 1;
		for ( int nCol = 0 ; nCol < nSubItemCount ; nCol ++ )
		{
			for ( int nRow = 0; nRow < nItemCount; nRow ++ )
			{
				if( nRow + nStart >= nSrcFrom && nRow + nStart <= nSrcTo )
				{
					memcpy(pRec[nCol][nRow+nGap], pRec[nCol][nRow], LEN_GRIDBODY);
					pRec[nCol][nRow+nGap]->nPos = nRow + nStart + nGap;
					
//					pRec[nCol][nRow+nGap]->nOrgPos = nRow + nStart + nGap;
//					pRec[nCol][nRow+nGap]->lDummy  = 0;
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CTableCell, CObject, 1)
CTableCell::CTableCell() 
{ 
	dwLength	= 0;
	nCount		= 0;
	pRec		= NULL;
	m_dwVersion = DEF_VERSION;
	m_pTable	= NULL;
};

//*******************************************************************/
/*! Function Name : CTableCell
/*! Function      : 
/*! Param         : const CTableCell*r
/*! Return        : 
/*! Create        : 김창하 , 2006/02/04
/*! Comment       : [합계행처리]
//******************************************************************/
CTableCell::CTableCell(const CTableCell* r )
{
	m_dwVersion		= DEF_VERSION;
	m_pTable		= NULL;
	pRec			= NULL;


	dwLength		= r->dwLength;
	nCount			= r->nCount;
	m_dwVersion		= r->m_dwVersion;

	if(nCount > 0)
	{
		pRec = new TABLECELL*[nCount];
		
		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRec[nIndex] = new TABLECELL;
			
			if ( pRec[nIndex] )
			{
				memcpy(pRec[nIndex], r->pRec[nIndex], LEN_TABLECELL);
			}
		}
	}
	// Member Variable
	//m_ItemArray.Copy(other.m_ItemArray);
}

CTableCell::~CTableCell() 
{
	m_ItemArray.RemoveAll();
};

void CTableCell::Initialize()
{
	if(m_pTable == NULL)
		return;

	//dwLength		= LEN_TABLECELLINFO(DEF_ROW_COUNT * DEF_COLUMN_COUNT);
	//nCount			= DEF_ROW_COUNT * DEF_COLUMN_COUNT;
	dwLength		= LEN_TABLECELLINFO(m_pTable->m_nRowCnt * m_pTable->m_nColCnt);
	nCount			= m_pTable->m_nRowCnt * m_pTable->m_nColCnt;
	m_dwVersion		= DEF_VERSION;

	
	int nRow(1), 
		nCol(1);
	
	pRec = new TABLECELL*[nCount];
	
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRec[nIndex] = new TABLECELL;
		
		if(nCol > m_pTable->m_nColCnt)
		{
			nRow++;
			nCol = 1;
		}

		if( pRec[nIndex] )
		{
			// cell info
			pRec[nIndex]->nRow				= nRow;
			pRec[nIndex]->nCol				= nCol;
			pRec[nIndex]->nOrgRow			= nRow;
			pRec[nIndex]->nOrgCol			= nCol;

			pRec[nIndex]->nKeyIndex			= DEF_KEY_INDEX;
			pRec[nIndex]->nRBkCrIndex		= DEF_REAL_BKCR_INDEX;
			pRec[nIndex]->nRTxCrIndex		= DEF_REAL_TXCR_INDEX;
			pRec[nIndex]->n3DEffect			= dx3DNormal;
			pRec[nIndex]->szCaption[0]		= 0x00;
			pRec[nIndex]->szItem[0]			= 0x00;
// --> [Edit]  김창하 2006/06/09
			pRec[nIndex]->nFID				= -1;
// <-- [Edit]  김창하 2006/06/09

// --> [Edit]  안경환 2007/03/22
			pRec[nIndex]->szRealItem[0]		= 0x00;
// <-- [Edit]  안경환 2007/03/22

#ifdef FIXLEN_USE
			pRec[nIndex]->szRecName[0]		= 0x00;
#endif
			pRec[nIndex]->bySignFormat		= (BYTE) 0;
			// DataType
			pRec[nIndex]->cDataType			= DEF_CELL_DATATYPE;   // DT_STRING
			// Attribute Index
//			pRec[nIndex]->nAttrOffset		= DEF_CELL_ATTROFFSET;
			// base info
			InitOGBASEITEM(pRec[nIndex]->bsItem, FALSE);
			// ItemBits
			InitITEMBITS(pRec[nIndex]->ItemBits);
			// TableBits
			InitTABLEBITS(pRec[nIndex]->tblBits);
			// MaskInfo
			InitMASKINFO(pRec[nIndex]->mask);
#ifdef FIXLEN_USE
			// TranBits
			InitTRANBITS(pRec[nIndex]->TrBits);
#endif
// --> [Edit]  김창하 2006/06/09
			pRec[nIndex]->nAttrFid			= -1;
// <-- [Edit]  김창하 2006/06/09

		}

		nCol++;
	}
}

void CTableCell::CopyTableCell( LPTABLECELL pScr, LPTABLECELL pDest , int nOption )
{
	short		nRow     = pDest->nRow;
	short		nCol     = pDest->nCol;
	if ( nOption == 0 )
	{
		memcpy( pDest, pScr, LEN_TABLECELL);
	}
	else
	{
		short		nOrgRow = pDest->nOrgRow,
					nOrgCol = pDest->nOrgCol,
					nLinkRow = pDest->tblBits.nLinkRow,
					nLinkCol = pDest->tblBits.nLinkCol;

		memcpy( pDest, pScr, LEN_TABLECELL);
		
		pDest->nOrgRow = nOrgRow;
		pDest->nOrgCol = nOrgCol;

		pDest->tblBits.nLinkRow = nLinkRow;
		pDest->tblBits.nLinkCol = nLinkCol;
	}

	pDest->nRow = nRow;
	pDest->nCol = nCol;
}

const CTableCell& CTableCell::operator=(const CTableCell& other)
{
	if ( &other == this)
		return *this;

	Clear();

	dwLength		= other.dwLength;
	nCount			= other.nCount;
	m_dwVersion		= other.m_dwVersion;

	
	if(nCount > 0)
	{
		pRec = new TABLECELL*[nCount];
		
		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRec[nIndex] = new TABLECELL;
			
			if ( pRec[nIndex] )
			{
				memcpy(pRec[nIndex], other.pRec[nIndex], LEN_TABLECELL);
			}
		}
	}

	// Member Variable
	m_ItemArray.Copy(other.m_ItemArray);

	return *this;
}

void CTableCell::Clear(  BOOL bInitCnt /*= TRUE*/ )
{
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if( pRec[nIndex] )
		{
			delete  pRec[nIndex];
		}
	}


	if(pRec)
	{
		delete[] pRec;
		pRec = NULL;
	}

	if(bInitCnt)
	{
		nCount = 0;
	}

}

void CTableCell::Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol /*= TRUE*/)
{
	if( nCount <= 0 )
		return;

	if( m_pTable == NULL )
		return;

	// 전체를 돌면서 바꾼다.
	DWORD nCnt = 1;
	DWORD nIndex, nNewIndex;
	TABLECELL** pNewRec = NULL;

	pNewRec = new TABLECELL*[nCount];
	if(pNewRec)
	{
		DWORD nCmp, 
			  nStepFrom;

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pNewRec[nIndex] = new TABLECELL;

			if ( pNewRec[nIndex] == NULL )
				continue;

			if(bMoveCol)
			{
				if(nIndex >= m_pTable->m_nColCnt)
				{
					nStepFrom = ( (nIndex / m_pTable->m_nColCnt) * m_pTable->m_nColCnt ) + nFrom;
				}
				else
				{
					nStepFrom = nFrom;
				}

				nCmp = pRec[nIndex]->nCol;
			}
			else
			{
				if(nIndex >= m_pTable->m_nRowCnt)
				{
					nStepFrom = ( (nIndex / m_pTable->m_nRowCnt) * m_pTable->m_nRowCnt ) + nFrom;
				}
				else
				{
					nStepFrom = nFrom;
				}
				
				nCmp = pRec[nIndex]->nRow;
			}

			if(nFrom < nDest)
			{
				if(nCmp >= nFrom && nCmp < nDest)
					nNewIndex = nIndex + nCnt;
				else if(nCmp == nDest)
					nNewIndex = nStepFrom - 1;
				else
					nNewIndex = nIndex;
			}
			else
			{
				if(nCmp > nDest && nCmp <= nFrom)
					nNewIndex = nIndex - nCnt;
				else if(nCmp == nDest)
					nNewIndex = nStepFrom - 1;
				else
					nNewIndex = nIndex;
			}

			memcpy(pNewRec[nIndex], pRec[nNewIndex], LEN_TABLECELL );
			
			if(bMoveCol)
				pNewRec[nIndex]->nCol = (short)nCmp;
			else
				pNewRec[nIndex]->nRow = (short)nCmp;

		}

		Clear(FALSE);
		pRec = pNewRec;
	}
}


//*******************************************************************/
/*! Function Name : SerializeUserData
/*! Function      : 
/*! Param         : CArchive &ar, LPBYTE lpData, DWORD dwLen
/*! Return        : void 
/*! Create        : 김창하 , 2005/11/29
/*! Comment       : 
//******************************************************************/
void CTableCell::SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen )
{
	if( !ar.IsStoring() )							// Read
	{
		Clear();

		m_ItemArray.RemoveAll();
		DWORD dwReadVersion;
		BYTE byReadLen;

		LPUSERCELLINFO puserCellInfo;
		LPUSERCELL    pUserCell = NULL;

		puserCellInfo = (USERCELLINFO*)lpData;
		
		LPBYTE lpCellData;
		lpCellData  = lpData + LEN_USERCELL_POS;

		ar >> dwLength;
		ar >> nCount;
		ar >> dwReadVersion;
		
		int nIndex(0);

		pRec = new TABLECELL*[nCount];
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			pRec[nIndex] = new TABLECELL;
		
		LPTABLECELL pRecCell = new TABLECELL;

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			// cell info
			ar >> pRecCell->nRow;
			ar >> pRecCell->nCol;
			ar >> pRecCell->nOrgRow;
			ar >> pRecCell->nOrgCol;
			ar >> pRecCell->nKeyIndex;
			ar >> pRecCell->nRBkCrIndex;
			ar >> pRecCell->nRTxCrIndex;
			ar >> pRecCell->n3DEffect;

			ar >> byReadLen;
			ar.Read( pRecCell->szCaption, byReadLen);
			pRecCell->szCaption[byReadLen] = 0x00;
			
			ar >> byReadLen;
			ar.ReadString( pRecCell->szItem, byReadLen);
			pRecCell->szItem[byReadLen] = 0x00;
			
#ifdef FIXLEN_USE
			ar >> byReadLen;
			ar.ReadString( pRecCell->szRecName, byReadLen);
			pRecCell->szRecName[byReadLen] = 0x00;
#endif
			ar >> pRecCell->bySignFormat;
			// DataType
			ar >> pRecCell->cDataType;
			// Attribute Index
//			ar >> pRecCell->nAttrOffset;
			// BaseItem
			SerializeOGBASEITEM(ar, pRecCell->bsItem);
			// ItemBits
			SerializeITEMBITS(ar, pRecCell->ItemBits);
			// TableBits
			SerializeTABLEBITS(ar, pRecCell->tblBits);
			// MaskInfo
			SerializeMASKINFO(ar, pRecCell->mask);
#ifdef FIXLEN_USE
			// TranInfo
			SerializeTRANBITS(ar, pRecCell->TrBits);
#endif
// --> [Edit]  김창하 2006/06/09
			
			ar >> pRecCell->nFID;
			ar >> pRecCell->nAttrFid;

// <-- [Edit]  김창하 2006/06/09

	// --> [Edit]  안경환 2007/03/22
			if( LOWORD(dwReadVersion) >= 12 && HIWORD(dwReadVersion) == 1 )
			{
				ar >> byReadLen;
				ar.ReadString( pRecCell->szRealItem, byReadLen);
				pRecCell->szRealItem[byReadLen] = 0x00;
			}
	// <-- [Edit]  안경환 2007/03/22

			
			if( *pRecCell->szItem != 0x00 )
			{
				if ( pRecCell->ItemBits.nItemFlag == dxItemOut || pRecCell->ItemBits.nItemFlag == dxItemInOut )
					m_ItemArray.Add( nIndex );
			}

			pUserCell = (USERCELL*)(lpCellData + (nIndex*LEN_USERCELL) ); 

			pRecCell->tblBits.nLinkRow = pUserCell->nOrgLinkRow;
			pRecCell->tblBits.nLinkCol = pUserCell->nOrgLinkCol;
			
			memcpy ( pRec[pUserCell->nMoveIndex], pRecCell, LEN_TABLECELL );
		}
		delete pRecCell;
	}
}

void CTableCell::Serialize(CArchive &ar)
{
	if( ar.IsStoring() )							// Write
	{

		ar << dwLength;
		ar << nCount;
		ar << m_dwVersion;

		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			if ( pRec[nIndex] )
			{
				// cell info
				ar << pRec[nIndex]->nRow;
				ar << pRec[nIndex]->nCol;
				ar << pRec[nIndex]->nOrgRow;
				ar << pRec[nIndex]->nOrgCol;

				ar << pRec[nIndex]->nKeyIndex;
				ar << pRec[nIndex]->nRBkCrIndex;
				ar << pRec[nIndex]->nRTxCrIndex;
				ar << pRec[nIndex]->n3DEffect;

				ar << (BYTE) lstrlen(pRec[nIndex]->szCaption);
				ar.WriteString((LPCTSTR) pRec[nIndex]->szCaption);
				ar << (BYTE) lstrlen(pRec[nIndex]->szItem);
				ar.WriteString((LPCTSTR) pRec[nIndex]->szItem);
#ifdef FIXLEN_USE
				ar << (BYTE) lstrlen(pRec[nIndex]->szRecName);
				ar.WriteString((LPCTSTR) pRec[nIndex]->szRecName);
#endif
				ar << pRec[nIndex]->bySignFormat;
				// DataType
				ar << pRec[nIndex]->cDataType;
				// Attribute Index
//				ar << pRec[nIndex]->nAttrOffset;

				// BaseItem
				SerializeOGBASEITEM(ar, pRec[nIndex]->bsItem);
				// ItemBits
				SerializeITEMBITS(ar, pRec[nIndex]->ItemBits);
				// TableBits
				SerializeTABLEBITS(ar, pRec[nIndex]->tblBits);
				// MaskInfo
				SerializeMASKINFO(ar, pRec[nIndex]->mask);
#ifdef FIXLEN_USE
				// TranInfo
				SerializeTRANBITS(ar, pRec[nIndex]->TrBits);
#endif
// --> [Edit]  김창하 2006/06/09
				ar << (short)( pRec[nIndex]->szItem[0] == 0x0 ?  -1 : pRec[nIndex]->nFID     );
				ar << (short)( pRec[nIndex]->szItem[0] == 0x0 ?  -1 : pRec[nIndex]->nAttrFid );

	// --> [Edit]  안경환 2007/03/22
				ar << (BYTE) lstrlen(pRec[nIndex]->szRealItem);
				ar.WriteString((LPCTSTR) pRec[nIndex]->szRealItem);
	// <-- [Edit]  안경환 2007/03/22

			
// <-- [Edit]  김창하 2006/06/09
			}
		}
	}
	else
	{
		Clear();
		m_ItemArray.RemoveAll();
		DWORD dwReadVersion;
		BYTE byReadLen;

		ar >> dwLength;
		ar >> nCount;
		ar >> dwReadVersion;

		pRec = new TABLECELL*[nCount];

		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRec[nIndex] = new TABLECELL;

			if ( pRec[nIndex] )
			{
				// cell info
				ar >> pRec[nIndex]->nRow;
				ar >> pRec[nIndex]->nCol;
				ar >> pRec[nIndex]->nOrgRow;
				ar >> pRec[nIndex]->nOrgCol;

				ar >> pRec[nIndex]->nKeyIndex;
				ar >> pRec[nIndex]->nRBkCrIndex;
				ar >> pRec[nIndex]->nRTxCrIndex;
				ar >> pRec[nIndex]->n3DEffect;

				ar >> byReadLen;
				ar.Read( pRec[nIndex]->szCaption, byReadLen);
				pRec[nIndex]->szCaption[byReadLen] = 0x00;
				
				ar >> byReadLen;
				ar.ReadString( pRec[nIndex]->szItem, byReadLen);
				pRec[nIndex]->szItem[byReadLen] = 0x00;
				
#ifdef FIXLEN_USE
				ar >> byReadLen;
				ar.ReadString( pRec[nIndex]->szRecName, byReadLen);
				pRec[nIndex]->szRecName[byReadLen] = 0x00;
#endif
				ar >> pRec[nIndex]->bySignFormat;
				// DataType
				ar >> pRec[nIndex]->cDataType;
				// Attribute Index
//				ar >> pRec[nIndex]->nAttrOffset;

				// BaseItem
				SerializeOGBASEITEM(ar, pRec[nIndex]->bsItem);
				// ItemBits
				SerializeITEMBITS(ar, pRec[nIndex]->ItemBits);
				// TableBits
				SerializeTABLEBITS(ar, pRec[nIndex]->tblBits);
				// MaskInfo
				SerializeMASKINFO(ar, pRec[nIndex]->mask);
#ifdef FIXLEN_USE
				// TranInfo
				SerializeTRANBITS(ar, pRec[nIndex]->TrBits);
#endif
// --> [Edit]  김창하 2006/06/09

				ar >> pRec[nIndex]->nFID;
				ar >> pRec[nIndex]->nAttrFid;

// <-- [Edit]  김창하 2006/06/09
				
	// --> [Edit]  안경환 2007/03/22
				if( LOWORD(dwReadVersion) >= 12 && HIWORD(dwReadVersion) == 1 )
				{
					ar >> byReadLen;
					ar.ReadString( pRec[nIndex]->szRealItem, byReadLen);
					pRec[nIndex]->szRealItem[byReadLen] = 0x00;
				}
	// <-- [Edit]  안경환 2007/03/22

				if( *pRec[nIndex]->szItem != 0x00 )
				{
					if ( pRec[nIndex]->ItemBits.nItemFlag == dxItemOut || pRec[nIndex]->ItemBits.nItemFlag == dxItemInOut )
						m_ItemArray.Add( nIndex );
				}
			}
		}
	
	}
}

int CTableCell::GetFlushItemListArray ( )
{
	m_ItemArray.RemoveAll();
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if ( pRec[nIndex]->szItem[0] != 0x00 )
		{
			if ( pRec[nIndex]->ItemBits.nItemFlag == dxItemOut || pRec[nIndex]->ItemBits.nItemFlag == dxItemInOut )
				m_ItemArray.Add( nIndex );
		}
	}

	return m_ItemArray.GetSize();
}

//*****************************************************************************
// 루    틴    명  :  GetBaseBoolBitCheck 
// 기          능  :  메모,CodeDrag,참조 정보를 사용하는 Cell이 존재하는 가를 체크한다.
//*****************************************************************************
long CTableCell::GetBaseBoolBitCheck ( long dwBaseboolBit )
{
	ITEMBITS ItemBits;
	BOOL	bMemoUse	= FALSE,
		    bCodeDrag	= FALSE,
			bCellRef	= FALSE,
			bTooltip	= FALSE,
			bCodeLink	= FALSE,
			bOrderLink	= FALSE,
			bAutoMaskUse= FALSE;

	// 참조정보를 사용하는가?.
	if ( m_pTable->m_pNewRefer != NULL )
	{
		if ( m_pTable->m_pNewRefer->nCount > 0 )
		{
			dwBaseboolBit |= BASE_BBIT_USE_CELLREF;
		}
	}

	for ( int nCellIndex = 0 ; nCellIndex < nCount; nCellIndex++ )
	{
		if ( pRec[nCellIndex]->bsItem.nCtrlID  == dxCtrlHBongChart )	// 가로봉. 
		{
			dwBaseboolBit |= BASE_BBIT_USE_HCHARTBONG;
		}

		if ( pRec[nCellIndex]->bsItem.nCtrlID  == dxCtrlVBongChart )	// 세로봉. 
		{
			dwBaseboolBit |= BASE_BBIT_USE_VCHARTBONG;
		}

		if ( pRec[nCellIndex]->bsItem.nCtrlID  == dxCtrlBMPBtn )		// Bitmap Button
		{
			dwBaseboolBit |= BASE_BBIT_USE_IMAGEBTN;
		}

		ItemBits = pRec[nCellIndex]->ItemBits;
//		if ( !bMemoUse && ItemBits.bMemo )
//		{
//			bMemoUse = TRUE;
//			dwBaseboolBit |= BASE_BBIT_USE_MENO;
//		}

//		if ( !bCellRef && ItemBits.bReferOwner )
//		{
//			bCellRef = TRUE;
//			dwBaseboolBit |= BASE_BBIT_USE_CELLREF;
//		}

#if FALSE
		// 각 셀에 참조사용 유무룰 마크한다.
		ItemBits.bReferOwner = FALSE;
		if ( dwBaseboolBit & BASE_BBIT_USE_CELLREF )
		{
			if ( pRec[nCellIndex]->szItem[0] != 0x00 )
			{
				NEWREFERTYPE* lpNewRefType;
				lpNewRefType = m_pTable->m_pNewRefer->GetNewReferType ( pRec[nCellIndex]->szItem, pRec[nCellIndex]->nKeyIndex );
				if ( lpNewRefType != NULL )
				{
					pRec[nCellIndex]->ItemBits.bReferOwner = TRUE;
//					ItemBits.bReferOwner = TRUE;
				}
			}
		}
#endif

		// Tooltip사용 유무. 
		if (!bTooltip && (pRec[nCellIndex]->bsItem.BaseBits.nToolTip > 0 ) )
		{
			bTooltip = TRUE;
			dwBaseboolBit |= BASE_BBIT_USE_TOOLTIP;
		}
		// 종목연계.
		if ( !bCodeLink && ItemBits.bCodeLink )
		{
			bCellRef = TRUE;
			dwBaseboolBit |= BASE_BBIT_USE_CODELINK;
		}
		// 주문연계.
		if ( !bOrderLink && ItemBits.bOrderLink )
		{
			bCellRef = TRUE;
			dwBaseboolBit |= BASE_BBIT_USE_ORDERLINK;
		}

		// 강조셀 설정유무.
		if ( !(dwBaseboolBit & BASE_BBIT_MMOVE_EPSCHECK) && pRec[nCellIndex]->tblBits.bHogaEmphasis )
		{
			dwBaseboolBit |= BASE_BBIT_MMOVE_EPSCHECK;
		}
// --> [Edit]  안경환 2010/11/20 // 자동가격마스크추가
		// 자동마스킹 컬럼 사용유무
		if ( !bAutoMaskUse && ItemBits.bAutoPriceMask )
		{
			bAutoMaskUse = TRUE;
			dwBaseboolBit |= BASE_BBIT_USE_AUTOPRICE;
		}
//		// 해외용 마스크가 지정된경우 자동마스킹을 설정한다.
//		if(pRec[nRow][nCol]->mask.nFormat == dxFmt_DecimalToString
//			|| pRec[nRow][nCol]->mask.nFormat == dxFmt_LogToString
//			|| pRec[nRow][nCol]->mask.nFormat == dxFmt_GLToSpotString )
//		{
//			dwBaseboolBit |= BASE_BBIT_USE_AUTOPRICE;
//		}
// <-- [Edit]  안경환 2010/11/20
	}
	
	return dwBaseboolBit;
}

//*****************************************************************************
// 루    틴    명  :  GetKeyIndexCount
// 기          능  :  Key Index 갯수를 구한다.
//*****************************************************************************
short CTableCell::GetKeyIndexCount( )
{
	CMapWordToPtr mapKeyCnt;
	mapKeyCnt.RemoveAll();

	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if( pRec[nIndex] ) 
			mapKeyCnt.SetAt(pRec[nIndex]->nKeyIndex, (void*) NULL);
	}

	return mapKeyCnt.GetCount();
}

LPCTSTR	CTableCell::GetKeyItem(short nKeyIndex /*= 0*/)
{
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if( pRec[nIndex] ) 
		{
			if( pRec[nIndex]->ItemBits.bIsKeyItem )
			{
				if( pRec[nIndex]->nKeyIndex == nKeyIndex )
					return pRec[nIndex]->szItem;
			}
		}
			
	}
	return NULL;
}

LPCTSTR	CTableCell::GetSubKeyItem(short nKeyIndex /*= 0*/)
{
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if( pRec[nIndex] ) 
		{
			if( pRec[nIndex]->ItemBits.bIsSubKeyItem )
			{
				if( pRec[nIndex]->nKeyIndex == nKeyIndex )
					return pRec[nIndex]->szItem;
			}
		}
			
	}
	return NULL;
}

LPCTSTR	CTableCell::GetThirdKeyItem(short nKeyIndex /*= 0*/)
{
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if( pRec[nIndex] ) 
		{
			if( pRec[nIndex]->ItemBits.bIsThirdKeyItem )
			{
				if( pRec[nIndex]->nKeyIndex == nKeyIndex )
					return pRec[nIndex]->szItem;
			}
		}
			
	}
	return NULL;
}

//*****************************************************************************
// 루    틴    명  :  GetRowColCell
// 기          능  :  Table의 Row,Col에 해당하는 셀 정보를 구한다.
//*****************************************************************************
TABLECELL* CTableCell::GetRowColCell(int nColCnt, int nRow, int nCol)
{
	// 0위치는 인덱스 셀의 위치.
	if(nRow < 1 || nCol < 1)
		return NULL;

	int nIndex = ( (nRow - 1) * nColCnt) + (nCol - 1);

	if( nIndex < nCount && pRec[nIndex])
	{
		if( pRec[nIndex]->nRow == nRow && pRec[nIndex]->nCol == nCol )
			return pRec[nIndex];
	}

	ASSERT(FALSE);
	return NULL;

}

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CTableLink, CObject, 1)
CTableLink::CTableLink() 
{ 
	dwLength	= 0;
	nCount		= 0;
	pRec		= NULL;

	m_dwVersion = DEF_VERSION;
};

CTableLink::~CTableLink() 
{

};

void CTableLink::Initialize()
{
	dwLength		= LEN_CELLLINKINFO( DEF_ROW_COUNT * DEF_COLUMN_COUNT );
	nCount			= DEF_ROW_COUNT * DEF_COLUMN_COUNT;
	m_dwVersion		= DEF_VERSION;

	int nRow(1), nCol(1);

	pRec = new CELLLINK*[nCount];
	
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRec[nIndex] = new CELLLINK;
		memset(pRec[nIndex], 0x00, LEN_CELLLINK);

		if(nCol > DEF_COLUMN_COUNT)
		{
			nRow++;
			nCol = 1;
		}
			
		if ( pRec[nIndex] )
		{
			pRec[nIndex]->byIsCaption = FALSE;
			pRec[nIndex]->nRow = nRow;
			pRec[nIndex]->nCol = nCol;

			pRec[nIndex]->nLinkRow = DEF_LINKROW;
			pRec[nIndex]->nLinkCol = DEF_LINKCOL;
			pRec[nIndex]->lDummy = 0L;
		}

		nCol++;
	}
}

const CTableLink& CTableLink::operator=(const CTableLink& other)
{
	if ( &other == this)
		return *this;

	Clear();

	dwLength		= other.dwLength;
	nCount			= other.nCount;
	m_dwVersion		= other.m_dwVersion;

	if(nCount > 0)	
	{
		pRec = new CELLLINK*[nCount];
		
		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRec[nIndex] = new CELLLINK;
			
			if ( pRec[nIndex] )
			{
				memcpy(pRec[nIndex], other.pRec[nIndex], LEN_CELLLINK);
			}
		}
	}

	return *this;
}


void CTableLink::Clear( )
{
	
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if(pRec[nIndex])
		{
#ifdef _DEBUG
			if( pRec[nIndex]->lDummy )
			{
				ASSERT(FALSE);
			}
#endif
			delete  pRec[nIndex];
		}
	}

	nCount = 0;

	if(pRec)
	{
		delete[] pRec;
		pRec = NULL;
	}
	
}

void CTableLink::Serialize(CArchive &ar)
{
	if( ar.IsStoring() )							// Write
	{

		ar << dwLength;
		ar << nCount;
		ar << m_dwVersion;

		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			if ( pRec[nIndex] )
			{
				ar << pRec[nIndex]->byIsCaption;
				ar << pRec[nIndex]->nRow;
				ar << pRec[nIndex]->nCol;
				ar << pRec[nIndex]->nLinkRow;
				ar << pRec[nIndex]->nLinkCol;
				ar << pRec[nIndex]->lDummy;
#ifdef _DEBUG
				if( pRec[nIndex]->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
	}
	else
	{
		Clear();
		DWORD dwReadVersion;

		ar >> dwLength;
		ar >> nCount;
		ar >> dwReadVersion;

		pRec = new CELLLINK*[nCount];

		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRec[nIndex] = new CELLLINK;
			memset(pRec[nIndex], 0x00, LEN_CELLLINK);

			if ( pRec[nIndex] )
			{
				ar >> pRec[nIndex]->byIsCaption;
				ar >> pRec[nIndex]->nRow;
				ar >> pRec[nIndex]->nCol;
				ar >> pRec[nIndex]->nLinkRow;
				ar >> pRec[nIndex]->nLinkCol;
				ar >> pRec[nIndex]->lDummy;
#ifdef _DEBUG				
				if( pRec[nIndex]->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CItemSize, CObject, 1)
CItemSize::CItemSize() 
{ 
	dwLength	= 0;
	nCount		= 0;
	pRec		= NULL;
	m_dwVersion = DEF_VERSION;
};

CItemSize::~CItemSize() 
{

};

void CItemSize::Initialize(int nDefCount, int nDefSize)
{
	// + 1 : Indexing Row OR Column
	dwLength		= LEN_ITEMSIZEINFO(nDefCount + 1);
	nCount			= nDefCount + 1;
	m_dwVersion		= DEF_VERSION;

	pRec = new ITEMSIZE*[nCount];
	
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRec[nIndex] = new ITEMSIZE;
		
		if ( pRec[nIndex] )
		{
			pRec[nIndex]->nSize = nDefSize;
			pRec[nIndex]->bySysHidden = (nIndex ==  0 ? TRUE : FALSE);
			pRec[nIndex]->lDummy = 0L;
		}
	}
}

const CItemSize& CItemSize::operator=(const CItemSize& other)
{
	if ( &other == this)
		return *this;

	Clear();

	dwLength		= other.dwLength;
	nCount			= other.nCount;
	m_dwVersion		= other.m_dwVersion;

	if(nCount > 0)
	{
		pRec = new ITEMSIZE*[nCount];
		
		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRec[nIndex] = new ITEMSIZE;
			
			if ( pRec[nIndex] )
			{
				memcpy(pRec[nIndex], other.pRec[nIndex], LEN_ITEMSIZE);
			}
		}
	}

	return *this;
}

void CItemSize::SetResize ( int nNewCount, int nDefSize  )
{
#if FALSE
// 미처리.
	ASSERT ( pRec != NULL );

	int nOldCount = nCount;
	int nNewSize;
	if ( nNewCount > nOldCount )
	{
		nNewSize      = nNewCount - nOldCount;
		

		for ( int nIndex = nOldCount ; nIndex < nNewCount; nIndex ++ )
		{
			pRec[nIndex] = new ITEMSIZE;
			
			if ( pRec[nIndex] )
			{
				pRec[nIndex]->nSize			= nDefSize;
				pRec[nIndex]->bySysHidden	= FALSE;
			}
		}
		nCount = nNewCount;
	}
	else if ( nNewCount < nOldCount )
	{
		for ( int nIndex = nNewCount ; nIndex < nCount; nIndex ++ )
		{
			if(pRec[nIndex])
				delete pRec[nIndex];
		}
		nCount = nNewCount;
	}

#endif

}

void CItemSize::Clear()
{
	
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if(pRec && pRec[nIndex])
		{
#ifdef _DEBUG
			if( pRec[nIndex]->lDummy )
			{
				ASSERT(FALSE);
			}
#endif
			delete  pRec[nIndex];
		}
	}

	nCount = 0;

	if(pRec)
	{
		delete[] pRec;
		pRec = NULL;
	}
	
}

ITEMSIZE* CItemSize::GetAt(int nIndex)
{
	if(nIndex < nCount)
	{
		return pRec[nIndex]; 
	}

	return NULL;
}

BOOL CItemSize::SetAt(int nIndex, short nSize /*= -1*/, BYTE  bySysHidden /*= 2*/)
{
	ITEMSIZE* pRec = GetAt(nIndex);
	
	if(pRec)
	{
		if(nSize != -1)
		{
			pRec->nSize = nSize;
			
		}

		if(bySysHidden != 2)
		{
			pRec->bySysHidden = bySysHidden;
		}

		return TRUE;
	}

	return FALSE;
}

void CItemSize::Serialize(CArchive &ar)
{

	if( ar.IsStoring() )							// Write
	{

		ar << dwLength;
		ar << nCount;
		ar << m_dwVersion;

		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			if ( pRec[nIndex] )
			{
				ar << pRec[nIndex]->nSize;
				ar << pRec[nIndex]->bySysHidden;
				ar << pRec[nIndex]->lDummy;
#ifdef _DEBUG
				if( pRec[nIndex]->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
	}
	else
	{
		Clear();
		DWORD dwReadVersion;

		ar >> dwLength;
		ar >> nCount;
		ar >> dwReadVersion;

		pRec = new ITEMSIZE*[nCount];

		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRec[nIndex] = new ITEMSIZE;

			if ( pRec[nIndex] )
			{
				ar >> pRec[nIndex]->nSize;
				ar >> pRec[nIndex]->bySysHidden;
				ar >> pRec[nIndex]->lDummy;
#ifdef _DEBUG
				if( pRec[nIndex]->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
	}
}

void CItemSize::Move(DWORD nFrom, DWORD nDest)
{
	if( nCount <= 0 )
		return;

	// 전체를 돌면서 바꾼다.
	DWORD nCnt = 1;
	DWORD nIndex, nNewIndex;
	ITEMSIZE** pNewRec = NULL;

	pNewRec = new ITEMSIZE*[nCount];
	
	if(pNewRec)
	{
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pNewRec[nIndex] = new ITEMSIZE;

			if ( pNewRec[nIndex] == NULL )
				continue;

			if(nFrom < nDest)
			{
				if(nIndex >= nFrom && nIndex < nDest)
					nNewIndex = nIndex + nCnt;
				else if(nIndex == nDest)
					nNewIndex = nFrom;
				else
					nNewIndex = nIndex;
			}
			else
			{
				if(nIndex > nDest && nIndex <= nFrom)
					nNewIndex = nIndex - nCnt;
				else if(nIndex == nDest)
					nNewIndex = nFrom;
				else
					nNewIndex = nIndex;
			}

			memcpy(pNewRec[nIndex], pRec[nNewIndex], LEN_ITEMSIZE);
		}

		Clear();
		nCount = (short)nIndex;
		pRec = pNewRec;
	}
}

// Insert
void CItemSize::Insert(DWORD nAddIndex, DWORD nAddCount, int nDefSize)
{
	int nNewCount = nCount + nAddCount;
	ITEMSIZE** pNewRec = NULL;
	pNewRec = new ITEMSIZE*[nNewCount];

	if(pNewRec)
	{
		int nOldIndex = 0;
		for ( int nIndex = 0 ; nIndex < nNewCount; nIndex ++ )
		{
			pNewRec[nIndex] = new ITEMSIZE;

			if ( pNewRec[nIndex] == NULL )
				continue;

			// Insert Point보다 이전인 경우.
			if( nIndex /*+ 1*/ < nAddIndex )
			{
				memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_ITEMSIZE);
				nOldIndex++;
			}
			else if( nIndex /*+ 1*/ >= nAddIndex && nIndex /*+ 1*/ < nAddIndex + nAddCount )
			{
				pNewRec[nIndex]->nSize = nDefSize;
				pNewRec[nIndex]->bySysHidden = FALSE;
				pNewRec[nIndex]->lDummy = 0L;
				
			}
			else if( nIndex /*+ 1*/ >= nAddIndex + nAddCount )
			{
				memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_ITEMSIZE);
				nOldIndex++;
			}
			else
			{
				ASSERT(FALSE);
			}
		}

		Clear();
		nCount = nNewCount;
		pRec = pNewRec;
	}
}

// Remove
void CItemSize::Remove(DWORD nDelIndex, DWORD nDelCount)
{
	int nNewCount = nCount - nDelCount;
	ITEMSIZE** pNewRec = NULL;
	pNewRec = new ITEMSIZE*[nNewCount];

	if(pNewRec)
	{
		int nOldIndex = 0;
		for ( int nIndex = 0 ; nIndex < nNewCount; nIndex ++ )
		{
			pNewRec[nIndex] = new ITEMSIZE;

			if ( pNewRec[nIndex] == NULL )
				continue;
			
			// Delete Point보다 이전인 경우.
			if( nIndex /*+ 1*/ < nDelIndex )
			{
				memcpy(pNewRec[nIndex], pRec[nOldIndex], LEN_ITEMSIZE);
				nOldIndex++;
			}
			else
			{
				memcpy(pNewRec[nIndex], pRec[nOldIndex+nDelCount], LEN_ITEMSIZE);
				nOldIndex++;
			}
		}

		Clear();
		nCount = nNewCount;
		pRec = pNewRec;
	}
}

// Copy
void CItemSize::Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo)
{
	if( nCount <= 0 )
		return;

	short nGap, nIndex;
	nGap  = (short)(nDestFrom - nSrcFrom);

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if( nIndex >= nSrcFrom && nIndex <= nSrcTo )
		{
			memcpy(pRec[nIndex+nGap], pRec[nIndex], LEN_ITEMSIZE);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CCellCovered, CObject, 1)
CCellCovered::CCellCovered() 
{ 
	m_dwLength	= 0;
	m_dwVersion = DEF_VERSION;
	
};

CCellCovered::~CCellCovered() 
{
	
};


void CCellCovered::Clear()
{
	m_dwLength	= 0;

	CELLRANGE* pRange = NULL;
	int nCount = GetSize();

	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRange = (CELLRANGE*) GetAt(nIndex);
		
		if ( pRange )
		{
			delete pRange;
		}
	}

	RemoveAll();
}

const CCellCovered& CCellCovered::operator=(const CCellCovered& other)
{
	if ( &other == this)
		return *this;

	Clear();

	m_dwLength		= other.m_dwLength;
	m_dwVersion		= other.m_dwVersion;

	//Copy(other);
	
	int nIndex, nCount;
	CELLRANGE* pRange = NULL;
	nCount = other.GetSize();
	
	SetSize(nCount);
	
	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRange = new CELLRANGE;

		if ( pRange )
		{
			memcpy(pRange, other.GetAt(nIndex), LEN_CELLRANGE);
			SetAt(nIndex, (void*) pRange);
		}
	}

	return *this;
}

void CCellCovered::Serialize(CArchive &ar)
{
	int nCount;
	CELLRANGE* pRange = NULL;

	if( ar.IsStoring() )							// Write
	{
		nCount = GetSize();
		
		ar << m_dwLength;
		ar << nCount;
		ar << m_dwVersion;

		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRange = (CELLRANGE*) GetAt(nIndex);
			
			if ( pRange )
			{
				ar << pRange->nRow;
				ar << pRange->nCol;
				ar << pRange->nToRow;
				ar << pRange->nToCol;
			}
		}
	}
	else
	{
		Clear();
		
		DWORD dwReadVersion;

		ar >> m_dwLength;
		ar >> nCount;
		ar >> dwReadVersion;

		SetSize(nCount);
	
		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRange = new CELLRANGE;
		
			if ( pRange )
			{
				ar >> pRange->nRow;
				ar >> pRange->nCol;
				ar >> pRange->nToRow;
				ar >> pRange->nToCol;

				SetAt(nIndex, (void*) pRange);
			}
		}
	}
}

CELLRANGE* CCellCovered::GetCoveredRange(short nRow, short nCol)
{
	CELLRANGE* pRange = NULL;
	int nIndex, nCount;
	nCount = GetSize();

	for( nIndex = 0; nIndex < nCount; nIndex++ )
	{
		pRange = (CELLRANGE*) GetAt(nIndex);

		if ( pRange )
		{
			if(pRange->nRow == nRow && pRange->nCol == nCol)
				return pRange;
		}
	}

	return NULL;
}

void CCellCovered::Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol /*= TRUE*/)
{
	int nIndex, nCount;
	BOOL bToRight = (nFrom < nDest);

	CELLRANGE* pRange = NULL;
	nCount = GetSize();

	for( nIndex = 0; nIndex < nCount; nIndex++ )
	{
		pRange = (CELLRANGE*) GetAt(nIndex);

		if ( pRange )
		{
			if( bMoveCol )
			{
				MoveRowColIndex(pRange->nCol, pRange->nToCol, nFrom, nDest, bToRight);
			}
			else
			{
				MoveRowColIndex(pRange->nRow, pRange->nToRow, nFrom, nDest, bToRight);
			}
		}
	}
}

void CCellCovered::MoveRowColIndex(short& nRowCol, short& nToRowCol, DWORD nFrom, DWORD nDest, BOOL bToRight)
{

	DWORD nCnt = 1;
	short nGap = nToRowCol - nRowCol;

	if(bToRight)
	{
		if(nRowCol == nFrom)
		{
			nRowCol = (short)nDest;
			
		}
		else if(nRowCol > nFrom && nRowCol <= nDest)
		{
			nRowCol -= (short)nCnt;
		}
	}
	else
	{
		if(nRowCol == nFrom)
		{
			nRowCol = (short)nDest;
		}
		else if(nRowCol >= nDest && nRowCol < nFrom)
		{
			nRowCol += (short)nCnt;
		}
	}

	nToRowCol = nRowCol + nGap;

}

// Insert Columns Or Rows
void CCellCovered::Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol /*= TRUE*/)
{
	CELLRANGE* pRange = NULL;
	int nCount = GetSize();
	
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRange = (CELLRANGE*) GetAt(nIndex);
		
		if ( pRange == NULL )
			continue;
			
		// Column Insert
		if( bInsertCol )
		{
			InsertRowColIndex(pRange->nCol, pRange->nToCol, nAddIndex, nAddCount);
		}
		else
		{
			InsertRowColIndex(pRange->nRow, pRange->nToRow, nAddIndex, nAddCount);
		}
	}
}

void CCellCovered::InsertRowColIndex(short& nRowCol, short& nToRowCol, DWORD nAddIndex, DWORD nAddCount)
{
	if( nToRowCol <= nAddIndex )
	{
		// Insert Point보다 이전인 경우.
		;
	}
	else if(nRowCol > nAddIndex )
	{
		// Insert Point와 갯수보다 이후인 경우.
		nRowCol		+= (short)nAddCount;
		nToRowCol	+= (short)nAddCount;
	}
	else
	{
		// Insert Point와 갯수 사이에 위치하는 경우
		nToRowCol	+= (short)nAddCount;
	}
}

// Remove Columns Or Rows
void CCellCovered::Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol /*= TRUE*/)
{
	CELLRANGE* pRange = NULL;
	int nCount = GetSize();
	BOOL bRemove = FALSE;
	
	for ( int nIndex = nCount-1; nIndex >= 0; nIndex -- )
	{
		pRange = (CELLRANGE*) GetAt(nIndex);
		
		if ( pRange == NULL )
			continue;
			
		// Column Remove
		if( bRemoveCol )
		{
			bRemove = RemoveRowColIndex(pRange->nCol, pRange->nToCol, nDelIndex, nDelCount);
		}
		else
		{
			bRemove = RemoveRowColIndex(pRange->nRow, pRange->nToRow, nDelIndex, nDelCount);
		}

		if( bRemove )
		{
			delete pRange;
			RemoveAt(nIndex);
		}
	}
}

BOOL CCellCovered::RemoveRowColIndex(short& nRowCol, short& nToRowCol, DWORD nDelIndex, DWORD nDelCount)
{
	BOOL bRemove = FALSE;
	if( nToRowCol <= nDelIndex )
	{
		// Delete Point보다 이전인 경우.
		;
	}
	else if(nRowCol > nDelIndex + nDelCount )
	{
		// Delete Point와 갯수보다 이후인 경우.
		nRowCol		-= (short)nDelCount;
		nToRowCol	-= (short)nDelCount;
	}
	else if( nRowCol == nDelIndex + 1 )
	{
		// Cover 주최를 지우는 경우.
		bRemove = TRUE;
	}
	else if( nRowCol > nDelIndex && nRowCol <= nDelIndex + nDelCount )
	{
		// Cover 주최를 지우는 경우.
		bRemove = TRUE;
	}
	else if( nRowCol <= nDelIndex )
	{
		// Delete Point와 갯수 사이에 위치하는 경우.
		nToRowCol	= (short)max(nRowCol, nToRowCol - nDelCount);
	}

	return bRemove;
}

// Copy Columns Or Rows
void CCellCovered::Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol /*= TRUE*/)
{
	short nGap, nIndex, nCount;
	nGap  = (short)(nDestFrom-nSrcFrom);

	CELLRANGE* pRange = NULL;
	CELLRANGE* pNewRange = NULL;
	nCount = GetSize();

	for( nIndex = 0; nIndex < nCount; nIndex++ )
	{
		pRange = (CELLRANGE*) GetAt(nIndex);

		if ( pRange )
		{
			if( bCopyCol )
			{
				// Cover 주최가 카피되는 경우.
				if( pRange->nCol >= nSrcFrom && pRange->nCol <= nSrcTo )
				{
					// 카피되는 영역에 cover정보가 다 있지 않고 넘어가는 경우는 무시한다.
					if( pRange->nToCol > nSrcTo )
						break;

					pNewRange = new CELLRANGE;
					ASSERT(pNewRange);

					memcpy(pNewRange, pRange, LEN_CELLRANGE);
					pNewRange->nCol		+= nGap;
					pNewRange->nToCol	+= nGap;

					Add( (void*) pNewRange);
				}
			}
			else
			{
				// Cover 주최가 카피되는 경우.
				if( pRange->nRow >= nSrcFrom && pRange->nRow <= nSrcTo )
				{
					// 카피되는 영역에 cover정보가 다 있지 않고 넘어가는 경우는 무시한다.
					if( pRange->nToRow > nSrcTo )
						break;

					pNewRange = new CELLRANGE;
					ASSERT(pNewRange);

					memcpy(pNewRange, pRange, LEN_CELLRANGE);
					pNewRange->nRow		+= nGap;
					pNewRange->nToRow	+= nGap;
					
					Add( (void*) pNewRange);
				}
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CLineBorder, CObject, 1)
CLineBorder::CLineBorder(BOOL bIsGrid /*= TRUE*/) 
{ 
	m_dwVersion		=	DEF_VERSION;
	m_bIsGrid		=	bIsGrid;

	m_pBorder		=	NULL;
};

CLineBorder::~CLineBorder() 
{
};


void CLineBorder::Clear()
{
	int nCount, nIndex, nSubCnt, nSubIndex;

	if(m_pBorder)
	{
		TBLBORDER* pBorder = NULL;
		BORDERINFO* pBdrInfo = NULL;
		nCount = m_pBorder->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pBorder = (TBLBORDER*) m_pBorder->GetAt(nIndex); 

			if(pBorder)
			{
				if(pBorder->pBorderArray)
				{
					nSubCnt = pBorder->pBorderArray->GetSize();

					for(nSubIndex =0; nSubIndex < nSubCnt; nSubIndex++)
					{
						pBdrInfo = (BORDERINFO*) pBorder->pBorderArray->GetAt(nSubIndex); 
						
						if(pBdrInfo)
						{
							delete pBdrInfo;
						}
					}

					pBorder->pBorderArray->RemoveAll();
					delete pBorder->pBorderArray;
					pBorder->pBorderArray = NULL;
				}

				delete pBorder;
			}

		}
		
		delete m_pBorder;
		m_pBorder = NULL;
	}

}

void CLineBorder::Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol /*= TRUE*/)
{
	int nIndex, nCount;
	BOOL bToRight = (nFrom < nDest);

	TBLBORDER* pBorder = NULL;
	BORDERINFO* pBdrInfo = NULL;

	if( m_pBorder )						
	{
		nCount = m_pBorder->GetSize();
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pBorder = (TBLBORDER*) m_pBorder->GetAt(nIndex); 
			if(pBorder)
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pBorder->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pBorder->nRow, nFrom, nDest, bToRight);
				}
			}
		}
	}

}

void CLineBorder::MoveRowColIndex(short& nRowCol, DWORD nFrom, DWORD nDest, BOOL bToRight)
{
	DWORD nCnt = 1;

	if(bToRight)
	{
		if(nRowCol == nFrom)
			nRowCol = (short)nDest;
		else if(nRowCol > nFrom && nRowCol <= nDest)
			nRowCol -= (short)nCnt;
	}
	else
	{
		if(nRowCol == nFrom)
			nRowCol = (short)nDest;
		else if(nRowCol >= nDest && nRowCol < nFrom)
			nRowCol += (short)nCnt;

		/*
		if(nRowCol == nDest)
			nRowCol = nFrom;
		else if(nRowCol > nDest && nRowCol <= nFrom)
			nRowCol -= nCnt;
		*/
	}

}

// Insert Columns Or Rows
void CLineBorder::Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol /*= TRUE*/)
{
	int nIndex, nCount;

	if( m_pBorder )
	{
		nCount = m_pBorder->GetSize();
	
		for( nIndex = 0; nIndex < nCount; nIndex++ )
		{

		}
	}
}

void CLineBorder::InsertRowColIndex(short& nRowCol, DWORD nAddIndex, DWORD nAddCount)
{
	if( nRowCol <= nAddIndex )
	{
		// Insert Point보다 이전인 경우.
		;
	}
	else if(nRowCol > nAddIndex )
	{
		// Insert Point와 갯수보다 이후인 경우.
		nRowCol		+= (short)nAddCount;
	}
}


// Remove Columns Or Rows
void CLineBorder::Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol /*= TRUE*/)
{
	int nIndex, nCount;
	BOOL bRemove = FALSE;

	if( m_pBorder )
	{
		nCount = m_pBorder->GetSize();
		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
				
		}
	}
}

BOOL CLineBorder::RemoveRowColIndex(short& nRowCol, DWORD nDelIndex, DWORD nDelCount)
{
	BOOL bRemove = FALSE;
	if( nRowCol <= nDelIndex )
	{
		// Delete Point보다 이전인 경우.
		;
	}
	else if(nRowCol > nDelIndex + nDelCount )
	{
		// Delete Point와 갯수보다 이후인 경우.
		nRowCol		-= (short)nDelCount;
	}
	else if( nRowCol == nDelIndex + 1 )
	{
		// 주최를 지우는 경우.
		bRemove = TRUE;
	}
	else if( nRowCol > nDelIndex && nRowCol <= nDelIndex + nDelCount )
	{
		// Cover 주최를 지우는 경우.
		bRemove = TRUE;
	}

	return bRemove;
}

// Copy Columns Or Rows
void CLineBorder::Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol /*= TRUE*/)
{
	short nGap, nIndex, nCount;
	nGap  = (short)(nDestFrom-nSrcFrom);

	if( m_pBorder )
	{
		nCount = m_pBorder->GetSize();
		for( nIndex = 0; nIndex < nCount; nIndex++ )
		{

		}
	}
}

const CLineBorder& CLineBorder::operator=(const CLineBorder& other)
{
	if ( &other == this)
		return *this;

	Clear();

	m_dwVersion		= other.m_dwVersion;
	m_bIsGrid		= other.m_bIsGrid;

	int nIndex, 
		nCount;
	
	if(other.m_pBorder)
	{
		m_pBorder = new CPtrArray;
		//m_pBorder->Copy(*other.m_pBorder);
		
		TBLBORDER* pBorder = NULL;
		TBLBORDER* pOtherBorder = NULL;
		BORDERINFO* pBdrInfo = NULL;
		int nSubIndex, 
			nSubCount;
		
		nCount = other.m_pBorder->GetSize();
		m_pBorder->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pBorder = new TBLBORDER;

			if ( pBorder )
			{
				pOtherBorder = (TBLBORDER*) other.m_pBorder->GetAt(nIndex);
				memcpy(pBorder, pOtherBorder, LEN_TBLBORDER);
				
				if(pOtherBorder->pBorderArray)
				{
					pBorder->pBorderArray = new CPtrArray;
					nSubCount = pOtherBorder->pBorderArray->GetSize();
					pBorder->pBorderArray->SetSize(nSubCount);

					for ( nSubIndex = 0 ; nSubIndex < nSubCount; nSubIndex ++ )
					{
						pBdrInfo = new BORDERINFO;
						memcpy(pBdrInfo, pOtherBorder->pBorderArray->GetAt(nSubIndex), LEN_BORDERINFO);

						pBorder->pBorderArray->SetAt(nSubIndex, (void*)pBdrInfo);
					}
				}
				
				m_pBorder->SetAt(nIndex, (void*) pBorder);
			}
		}
	}

	return *this;
}

//*******************************************************************/
/*! Function Name : SerializeUserData
/*! Function      : 
/*! Param         : CArchive &ar, LPBYTE lpData, DWORD dwLen
/*! Return        : void 
/*! Create        : 김창하 , 2005/11/29
/*! Comment       : 
//******************************************************************/
void CLineBorder::SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen )
{
	if( !ar.IsStoring() )							// Read
	{
		Serialize ( ar );
	}

}
void CLineBorder::Serialize(CArchive &ar)
{
	int nIndex, nCount, nSubCnt, nSubIndex;
//	GRIDLINE* pLine		= NULL;
	TBLBORDER* pBorder	= NULL;

	if( ar.IsStoring() )							// Write
	{
		BORDERINFO* pBdrInfo = NULL;
		nCount = ( m_pBorder ? m_pBorder->GetSize() : 0);
		
		ar << nCount;
		ar << m_dwVersion;
		ar << m_bIsGrid;

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pBorder = (TBLBORDER*) m_pBorder->GetAt(nIndex);
			
			if ( pBorder )
			{
				ar << pBorder->nRow;
				ar << pBorder->nCol;
				ar << pBorder->byUseLRTB;
				
				nSubCnt = pBorder->pBorderArray->GetSize();
				ar << nSubCnt;

				for ( nSubIndex = 0 ; nSubIndex < nSubCnt; nSubIndex ++ )
				{
					pBdrInfo = (BORDERINFO*) pBorder->pBorderArray->GetAt(nSubIndex);
					
					if(pBdrInfo)
					{
						ar << pBdrInfo->nStyle;
						ar << pBdrInfo->nCrIndex;
						ar << pBdrInfo->nWidth;
					}
				}
		
			}
		}
	}
	else
	{
		Clear();
		DWORD dwReadVersion;

		ar >> nCount;
		ar >> dwReadVersion;
		ar >> m_bIsGrid;

		if( nCount > 0)
		{
			BORDERINFO* pBdrInfo = NULL;

			if(m_pBorder == NULL)
				m_pBorder = new CPtrArray;

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pBorder = new TBLBORDER;
				memset(pBorder, 0x00, LEN_TBLBORDER);
	
				if ( pBorder )
				{
					ar >> pBorder->nRow;
					ar >> pBorder->nCol;
					ar >> pBorder->byUseLRTB;
					ar >> nSubCnt;
					
					if(pBorder->pBorderArray == NULL)
						pBorder->pBorderArray = new CPtrArray;
					
					pBorder->pBorderArray->SetSize(nSubCnt);
					
					for ( nSubIndex = 0 ; nSubIndex < nSubCnt; nSubIndex ++ )
					{
						pBdrInfo = new BORDERINFO;
						memset(pBdrInfo, 0x00, LEN_BORDERINFO);
						
						ar >> pBdrInfo->nStyle;
						ar >> pBdrInfo->nCrIndex;
						ar >> pBdrInfo->nWidth;

						pBorder->pBorderArray->SetAt(nSubIndex, (void*)pBdrInfo);
					}

					m_pBorder->Add((void*) pBorder);
				}
			}
		}
	}
}


BOOL CLineBorder::SetPropList(LPSTR lpBuf )
{
	if(!lpBuf || *lpBuf == 0x00)
		return FALSE;

//	LPSTR		lpStr;
	Clear();

	m_bIsGrid = strtol(lpBuf, &lpBuf, 10);

	if (lpBuf && *lpBuf)
		lpBuf++;

	// Format
	// IsGrid<US>Row<US>Col<US>UseLRTB<US>Count<US>Style1<FS>CrIndex1<FS>Width1<FS>.....Style4<FS>CrIndex4<FS>Width4<FS>......
	//			 Row<US>Col<US>UseLRTB<US>Count<US>Style1<FS>CrIndex1<FS>Width1<FS>.....Style4<FS>CrIndex4<FS>Width4<FS>

	if(m_pBorder == NULL)
		m_pBorder = new CPtrArray;

	TBLBORDER* pBorder = NULL;
	BORDERINFO* pBdrInfo = NULL;
	int nSubCnt, nSubIndex;
	while ( *lpBuf != 0 )
	{
		pBorder = new TBLBORDER;
		memset(pBorder, 0x00, LEN_TBLBORDER);

		if ( pBorder )
		{
			pBorder->nRow = (short)strtol(lpBuf, &lpBuf, 10);
			if (lpBuf && *lpBuf)
				lpBuf++;

			pBorder->nCol = (short)strtol(lpBuf, &lpBuf, 10);
			if (lpBuf && *lpBuf)
				lpBuf++;

			pBorder->byUseLRTB = (BYTE) strtol(lpBuf, &lpBuf, 10);
			if (lpBuf && *lpBuf)
				lpBuf++;
			
			nSubCnt = strtol(lpBuf, &lpBuf, 10);
			if (lpBuf && *lpBuf)
				lpBuf++;
			
			if(nSubCnt)
			{
				if(pBorder->pBorderArray == NULL)
					pBorder->pBorderArray = new CPtrArray;

				pBorder->pBorderArray->SetSize(nSubCnt);

				for(nSubIndex =0; nSubIndex < nSubCnt; nSubIndex++)
				{
					pBdrInfo = new BORDERINFO;
					memset(pBdrInfo, 0x00, LEN_BORDERINFO);

					if(pBdrInfo)
					{
						pBdrInfo->nStyle = (short)strtol(lpBuf, &lpBuf, 10);
						if (lpBuf && *lpBuf)
							lpBuf++;

						pBdrInfo->nCrIndex = (short)strtol(lpBuf, &lpBuf, 10);
						if (lpBuf && *lpBuf)
							lpBuf++;
						
						pBdrInfo->nWidth = (short)strtol(lpBuf, &lpBuf, 10);
						if (lpBuf && *lpBuf)
							lpBuf++;

						pBorder->pBorderArray->SetAt(nSubIndex, (void*) pBdrInfo);

					}
				}
			}
			m_pBorder->Add((void*) pBorder);
		}
	}

	
	return FALSE;
}

BOOL CLineBorder::GetPropList(CString& strList)
{
	strList = _T("");

	//CString strTemp;
	char szTemp[256];
	
	int nIndex, nCount;
	
	// Format
	// IsGrid<US>Row<US>Col<US>UseLRTB<US>Count<US>Style1<FS>CrIndex1<FS>Width1<FS>.....Style4<FS>CrIndex4<FS>Width4<FS>......
	//			 Row<US>Col<US>UseLRTB<US>Count<US>Style1<FS>CrIndex1<FS>Width1<FS>.....Style4<FS>CrIndex4<FS>Width4<FS>
	if(m_pBorder == NULL)
		return FALSE;

	TBLBORDER* pBorder = NULL;
	BORDERINFO* pBdrInfo = NULL;
	
	//CString strBuf;
	char szBuf[256];
	int nSubCnt, nSubIndex;
	nCount = m_pBorder->GetSize();

	if(!nCount)
		return FALSE;

	strList.Format("%d%c", m_bIsGrid, _G_TCH_US);

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pBorder = (TBLBORDER*) m_pBorder->GetAt(nIndex);
		
		if ( pBorder )
		{
			nSubCnt = pBorder->pBorderArray->GetSize();
			
			wsprintf(szTemp,_T("%d%c%d%c%d%c%d%c"), 
							pBorder->nRow,		_G_TCH_US,
							pBorder->nCol,		_G_TCH_US,
							pBorder->byUseLRTB,	_G_TCH_US,
							nSubCnt,			_G_TCH_US); 

			strList += szTemp;
			
			if( nSubCnt > 0 )
			{
				for ( nSubIndex = 0 ; nSubIndex < nSubCnt; nSubIndex++ )
				{
					pBdrInfo = (BORDERINFO*) pBorder->pBorderArray->GetAt(nSubIndex);
					
					wsprintf(szBuf, _T("%d%c%d%c%d%c"), 
							pBdrInfo->nStyle,		_G_TCH_FS,
							pBdrInfo->nCrIndex,		_G_TCH_FS,
							pBdrInfo->nWidth,		_G_TCH_FS);

					strList += szBuf;
				}
				
			}
	
		}
	}

	return (!strList.IsEmpty());
}

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CCellCtrl, CObject, 1)
CCellCtrl::CCellCtrl() 
{ 
	m_dwVersion			=	DEF_VERSION;
	m_pComboArray		=	NULL;
	m_pCheckArray		=	NULL;
	m_pSpinArray		=	NULL;
	m_pPushBtnArray		=	NULL;
	m_pBMPBtnArray		=	NULL;
	m_pCodeCtrlArray	=	NULL;
	m_pPWEditArray		=	NULL;
	m_pEditArray		=	NULL;
	m_pPrgrsArray		=	NULL;
	m_pComboExArray		=	NULL;

#ifdef GRADIENT_USE 
	m_pGradientArray    =	NULL;	// Gradient
#endif
};

CCellCtrl::~CCellCtrl() 
{
};


void CCellCtrl::Clear()
{
	if(m_pComboArray)
	{
		ClearCtrl(dxCtrlCombo);
		delete m_pComboArray;
		m_pComboArray = NULL;
	}

	if(m_pComboExArray)
	{
		ClearCtrl(dxCtrlComboBoxEx);
		delete m_pComboExArray;
		m_pComboExArray = NULL;
	}
	

	if(m_pCheckArray)
	{
		ClearCtrl(dxCtrlCheck);
		delete m_pCheckArray;
		m_pCheckArray = NULL;
	}

	if(m_pSpinArray)
	{
		ClearCtrl(dxCtrlSpin);
		delete m_pSpinArray;
		m_pSpinArray = NULL;
	}

	if(m_pPushBtnArray)
	{
		ClearCtrl(dxCtrlPushBtn);
		delete m_pPushBtnArray;
		m_pPushBtnArray = NULL;
	}

	if(m_pBMPBtnArray)
	{
		ClearCtrl(dxCtrlBMPBtn);
		delete m_pBMPBtnArray;
		m_pBMPBtnArray = NULL;
	}

	if(m_pCodeCtrlArray)
	{
		ClearCtrl(dxCtrlCodeInput);
		delete m_pCodeCtrlArray;
		m_pCodeCtrlArray = NULL;
	}

	if(m_pPWEditArray)
	{
		ClearCtrl(dxCtrlPWEdit);
		delete m_pPWEditArray;
		m_pPWEditArray = NULL;
	}

	if(m_pEditArray)
	{
		ClearCtrl(dxCtrlEdit);
		delete m_pEditArray;
		m_pEditArray = NULL;
	}

	if(m_pPrgrsArray)
	{
		ClearCtrl(dxCtrlProgress);
		delete m_pPrgrsArray;
		m_pPrgrsArray = NULL;
	}
#ifdef GRADIENT_USE 
	// Gradient
	if ( m_pGradientArray )
	{
		ClearCtrl( dxCtrlGradient );
		delete m_pGradientArray;
		m_pGradientArray = NULL;
	}
#endif
}

void CCellCtrl::ClearCtrl(int nCtrlID)
{
	int nCount;
	switch(nCtrlID)
	{
	case dxCtrlComboBoxEx:
		{
			if(m_pComboExArray)
			{
				CELLCOMBOEX* pCombo = NULL;
				nCount = m_pComboExArray->GetSize();
			
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pCombo = (CELLCOMBOEX*) m_pComboExArray->GetAt(nIndex);
					
					if ( pCombo )
					{
#ifdef _DEBUG
						if( pCombo->lDummy )
						{
							ASSERT(FALSE);
						}
#endif
						delete pCombo;
					}
				}

				m_pComboExArray->RemoveAll();
			}
		}
		break;
	case 52527:
	case dxCtrlCombo:
		{
			if(m_pComboArray)
			{
				CELLCOMBO* pCombo = NULL;
				nCount = m_pComboArray->GetSize();
			
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pCombo = (CELLCOMBO*) m_pComboArray->GetAt(nIndex);
					
					if ( pCombo )
					{
#ifdef _DEBUG
						if( pCombo->lDummy )
						{
							ASSERT(FALSE);
						}
#endif
						delete pCombo;
					}
				}

				m_pComboArray->RemoveAll();
			}
		}
		break;
	case dxCtrlCheck:
		{
			if(m_pCheckArray)
			{
				CELLCHECK* pCheck = NULL;
			
				nCount = m_pCheckArray->GetSize();
			
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pCheck = (CELLCHECK*) m_pCheckArray->GetAt(nIndex);
					
					if ( pCheck )
					{
#ifdef _DEBUG
						if( pCheck->lDummy )
						{
							ASSERT(FALSE);
						}
#endif
						delete pCheck;
					}
				}

				m_pCheckArray->RemoveAll();
			}

		}
		break;
	case dxCtrlSpin:
		{
			if(m_pSpinArray)
			{
				CELLSPIN* pSpin = NULL;
			
				nCount = m_pSpinArray->GetSize();
			
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pSpin = (CELLSPIN*) m_pSpinArray->GetAt(nIndex);
					
					if ( pSpin )
					{
#ifdef _DEBUG
						if( pSpin->lDummy )
						{
							ASSERT(FALSE);
						}
#endif
						delete pSpin;
					}
				}

				m_pSpinArray->RemoveAll();
			}
		}
		break;
	case dxCtrlPushBtn:
		{
			if(m_pPushBtnArray)
			{
				CELLPUSHBTN* pPushBtn = NULL;
			
				nCount = m_pPushBtnArray->GetSize();
			
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pPushBtn = (CELLPUSHBTN*) m_pPushBtnArray->GetAt(nIndex);
					
					if ( pPushBtn )
					{
#ifdef _DEBUG
						if( pPushBtn->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						delete pPushBtn;
					}
				}

				m_pPushBtnArray->RemoveAll();
			}

		}
		break;
	case dxCtrlBMPBtn:
		{
			if(m_pBMPBtnArray)
			{
				CELLBMPBTN* pBMPBtn = NULL;
			
				nCount = m_pBMPBtnArray->GetSize();
			
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pBMPBtn = (CELLBMPBTN*) m_pBMPBtnArray->GetAt(nIndex);
					
					if ( pBMPBtn )
					{
#ifdef _DEBUG
						if( pBMPBtn->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						delete pBMPBtn;
					}
				}

				m_pBMPBtnArray->RemoveAll();
			}

		}
		break;
	case dxCtrlCodeInput:
		{
			if(m_pCodeCtrlArray)
			{
				CELLCODECTRL* pCodeCtrl = NULL;
			
				nCount = m_pCodeCtrlArray->GetSize();
			
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pCodeCtrl = (CELLCODECTRL*) m_pCodeCtrlArray->GetAt(nIndex);
					
					if ( pCodeCtrl )
					{
#ifdef _DEBUG
						if( pCodeCtrl->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						delete pCodeCtrl;
					}
				}

				m_pCodeCtrlArray->RemoveAll();
			}

		}
		break;
	case dxCtrlPWEdit:
		{
			if(m_pPWEditArray)
			{
				CELLEDIT* pPWEdit = NULL;
			
				nCount = m_pPWEditArray->GetSize();
			
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pPWEdit = (CELLEDIT*) m_pPWEditArray->GetAt(nIndex);
					
					if ( pPWEdit )
					{
#ifdef _DEBUG
						if( pPWEdit->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						delete pPWEdit;
					}
				}

				m_pPWEditArray->RemoveAll();
			}

		}
		break;
	case dxCtrlEdit:
		{
			if(m_pEditArray)
			{
				CELLEDIT* pEdit = NULL;
			
				nCount = m_pEditArray->GetSize();
			
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pEdit = (CELLEDIT*) m_pEditArray->GetAt(nIndex);
					
					if ( pEdit )
					{
#ifdef _DEBUG
						if( pEdit->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						delete pEdit;
					}
				}

				m_pEditArray->RemoveAll();
			}

		}
		break;
	case dxCtrlProgress:
		{
			if(m_pPrgrsArray)
			{
				CELLPRGRS* pPrgrs = NULL;
			
				nCount = m_pPrgrsArray->GetSize();
			
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pPrgrs = (CELLPRGRS*) m_pPrgrsArray->GetAt(nIndex);
					
					if ( pPrgrs )
					{
						delete pPrgrs;
					}
				}

				m_pPrgrsArray->RemoveAll();
			}
		}
		break;
#ifdef GRADIENT_USE 
	case dxCtrlGradient:	// Gradient
		{
			if( m_pGradientArray )
			{
				CELLGRADIENTS* pGradients= NULL;
			
				nCount = m_pGradientArray->GetSize();
				for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
				{
					pGradients = (CELLGRADIENTS*) m_pGradientArray->GetAt(nIndex);
					if ( pGradients )
					{
						delete pGradients;
					}
				}
				m_pGradientArray->RemoveAll();
			}
		}
		break;
#endif
	}
}

const CCellCtrl& CCellCtrl::operator=(const CCellCtrl& other)
{
	if ( &other == this)
		return *this;

	Clear();

	m_dwVersion		= other.m_dwVersion;


	int nIndex, nCount;

	if(other.m_pComboArray)
	{
		m_pComboArray = new CPtrArray;

		CELLCOMBO* pCombo = NULL;
		CELLCOMBO* pOtherCombo = NULL;
		nCount = other.m_pComboArray->GetSize();
		
		m_pComboArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCombo = new CELLCOMBO;

			if ( pCombo )
			{
				pOtherCombo = (CELLCOMBO*) other.m_pComboArray->GetAt(nIndex);
				
				pCombo->nRow		= pOtherCombo->nRow;
				pCombo->nCol		= pOtherCombo->nCol;
				pCombo->strItemList	= pOtherCombo->strItemList;
				pCombo->lDummy		= pOtherCombo->lDummy;
				
				m_pComboArray->SetAt(nIndex, (void*) pCombo);
			}
		}
	}

	if(other.m_pComboExArray)
	{
		m_pComboExArray = new CPtrArray;

		CELLCOMBOEX* pCombo = NULL;
		CELLCOMBOEX* pOtherCombo = NULL;
		nCount = other.m_pComboExArray->GetSize();
		
		m_pComboExArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCombo = new CELLCOMBOEX;

			if ( pCombo )
			{
				pOtherCombo = (CELLCOMBOEX*) other.m_pComboExArray->GetAt(nIndex);
				
				pCombo->nRow		= pOtherCombo->nRow;
				pCombo->nCol		= pOtherCombo->nCol;

				pCombo->nMaxLen       = pOtherCombo->nMaxLen;				// 데이터출력값 
				pCombo->byValueShow    = pOtherCombo->byValueShow;			// 00=00 데이터  
				pCombo->strChoiceList = pOtherCombo->strChoiceList;
				pCombo->strFileName   = pOtherCombo->strFileName;			// Ini 파일명 
				pCombo->strSectionName= pOtherCombo->strSectionName;		// [Ini]섹션명 
				pCombo->lDummy		  = pOtherCombo->lDummy;
				m_pComboExArray->SetAt(nIndex, (void*) pCombo);
			}
		}
	}

	if(other.m_pCheckArray)
	{
		m_pCheckArray = new CPtrArray;

		CELLCHECK*	pCheck = NULL;
		CELLCHECK*	pOtherCheck = NULL;
		nCount = other.m_pCheckArray->GetSize();
		
		m_pCheckArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCheck = new CELLCHECK;

			if ( pCheck )
			{
				pOtherCheck = (CELLCHECK*) other.m_pCheckArray->GetAt(nIndex);
				
				pCheck->nRow		= pOtherCheck->nRow;
				pCheck->nCol		= pOtherCheck->nCol;
				pCheck->nCheckVal	= pOtherCheck->nCheckVal;
				pCheck->nUnCheckVal	= pOtherCheck->nUnCheckVal;
				pCheck->strText		= pOtherCheck->strText;
				pCheck->lDummy		= pOtherCheck->lDummy;
				
				m_pCheckArray->SetAt(nIndex, (void*) pCheck);
			}
		}

	}

	if(other.m_pSpinArray)
	{
		m_pSpinArray = new CPtrArray;

		CELLSPIN*	pSpin = NULL;
		CELLSPIN*	pOtherSpin = NULL;
		nCount = other.m_pSpinArray->GetSize();
		
		m_pSpinArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pSpin = new CELLSPIN;

			if ( pSpin )
			{
				pOtherSpin = (CELLSPIN*) other.m_pSpinArray->GetAt(nIndex);
				
				memcpy(pSpin, pOtherSpin, sizeof(CELLSPIN));
				
				m_pSpinArray->SetAt(nIndex, (void*) pSpin);
			}
		}

	}

	if(other.m_pPushBtnArray)
	{
		m_pPushBtnArray = new CPtrArray;

		CELLPUSHBTN*	pPushBtn = NULL;
		CELLPUSHBTN*	pOtherPushBtn = NULL;
		nCount = other.m_pPushBtnArray->GetSize();
		
		m_pPushBtnArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPushBtn = new CELLPUSHBTN;

			if ( pPushBtn )
			{
				pOtherPushBtn = (CELLPUSHBTN*) other.m_pPushBtnArray->GetAt(nIndex);
				
				pPushBtn->nRow			= pOtherPushBtn->nRow;
				pPushBtn->nCol			= pOtherPushBtn->nCol;
				pPushBtn->nBtCrIndex	= pOtherPushBtn->nBtCrIndex;
				pPushBtn->strText		= pOtherPushBtn->strText;
				pPushBtn->lDummy		= pOtherPushBtn->lDummy;
				
				m_pPushBtnArray->SetAt(nIndex, (void*) pPushBtn);
			}
		}

	}
	
	if(other.m_pBMPBtnArray)
	{
		m_pBMPBtnArray = new CPtrArray;

		CELLBMPBTN*	pBMPBtn = NULL;
		CELLBMPBTN*	pOtherBMPBtn = NULL;
		nCount = other.m_pBMPBtnArray->GetSize();
		
		m_pBMPBtnArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pBMPBtn = new CELLBMPBTN;

			if ( pBMPBtn )
			{
				pOtherBMPBtn = (CELLBMPBTN*) other.m_pBMPBtnArray->GetAt(nIndex);
				
				pBMPBtn->nRow			= pOtherBMPBtn->nRow;
				pBMPBtn->nCol			= pOtherBMPBtn->nCol;
				pBMPBtn->byStretch		= pOtherBMPBtn->byStretch;
				pBMPBtn->strTitle		= pOtherBMPBtn->strTitle;
				pBMPBtn->strNormalName	= pOtherBMPBtn->strNormalName;
				pBMPBtn->strDownName	= pOtherBMPBtn->strDownName;
				pBMPBtn->lDummy			= pOtherBMPBtn->lDummy;
				
				m_pBMPBtnArray->SetAt(nIndex, (void*) pBMPBtn);
			}
		}

	}
	
	if(other.m_pCodeCtrlArray)
	{
		m_pCodeCtrlArray = new CPtrArray;

		CELLCODECTRL*	pCodeCtrl = NULL;
		CELLCODECTRL*	pOtherCodeCtrl = NULL;
		nCount = other.m_pCodeCtrlArray->GetSize();
		
		m_pCodeCtrlArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCodeCtrl = new CELLCODECTRL;

			if ( pCodeCtrl )
			{
				pOtherCodeCtrl = (CELLCODECTRL*) other.m_pCodeCtrlArray->GetAt(nIndex);
				
				memcpy(pCodeCtrl, pOtherCodeCtrl, sizeof(CELLCODECTRL));
				
				m_pCodeCtrlArray->SetAt(nIndex, (void*) pCodeCtrl);
			}
		}

	}
	
	if(other.m_pPWEditArray)
	{
		m_pPWEditArray = new CPtrArray;

		CELLEDIT*	pPWEdit = NULL;
		CELLEDIT*	pOtherPWEdit = NULL;
		nCount = other.m_pPWEditArray->GetSize();
		
		m_pPWEditArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPWEdit = new CELLEDIT;

			if ( pPWEdit )
			{
				pOtherPWEdit = (CELLEDIT*) other.m_pPWEditArray->GetAt(nIndex);
				memcpy(pPWEdit, pOtherPWEdit, sizeof(CELLEDIT));
				
				m_pPWEditArray->SetAt(nIndex, (void*) pPWEdit);
			}
		}

	}

	if(other.m_pEditArray)
	{
		m_pEditArray = new CPtrArray;

		CELLEDIT*	pEdit = NULL;
		CELLEDIT*	pOtherEdit = NULL;
		nCount = other.m_pEditArray->GetSize();
		
		m_pEditArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pEdit = new CELLEDIT;

			if ( pEdit )
			{
				pOtherEdit = (CELLEDIT*) other.m_pEditArray->GetAt(nIndex);
				memcpy(pEdit, pOtherEdit, sizeof(CELLEDIT));
				
				m_pEditArray->SetAt(nIndex, (void*) pEdit);
			}
		}

	}
	
	if(other.m_pPrgrsArray)
	{
		m_pPrgrsArray = new CPtrArray;

		CELLPRGRS*	pPrgrs = NULL;
		CELLPRGRS*	pOtherPrgrs = NULL;
		nCount = other.m_pPrgrsArray->GetSize();
		
		m_pPrgrsArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPrgrs = new CELLPRGRS;

			if ( pPrgrs )
			{
				pOtherPrgrs = (CELLPRGRS*) other.m_pPrgrsArray->GetAt(nIndex);
				memcpy(pPrgrs, pOtherPrgrs, sizeof(CELLPRGRS));
				
				m_pPrgrsArray->SetAt(nIndex, (void*) pPrgrs);
			}
		}
	}
#ifdef GRADIENT_USE 
	// Gradient
	if(other.m_pGradientArray )
	{
		m_pGradientArray = new CPtrArray;

		CELLGRADIENTS*	pGradients = NULL;
		CELLGRADIENTS*	pOtherGradients = NULL;
		nCount = other.m_pGradientArray->GetSize();
		
		m_pGradientArray->SetSize(nCount);
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pGradients = new CELLGRADIENTS;
			if ( pGradients )
			{
				pOtherGradients = (CELLGRADIENTS*) other.m_pGradientArray->GetAt(nIndex);
				memcpy( pGradients, pOtherGradients, sizeof(CELLGRADIENTS));
				
				m_pGradientArray->SetAt(nIndex, (void*) pGradients );
			}
		}
	}
#endif
	return *this;

}

void CCellCtrl::Serialize(CArchive &ar)
{

	int nIndex, nCount, nCmbCnt,nCmbExCnt(0), nCheckCnt, nSpinCnt, 
		nPushBtnCnt, nBMPBtnCnt, nCodeCtrlCnt, nPWEditCnt, nEditCnt, nPrgrsCnt,nGradientCnt(0);
	
	CELLCOMBO* pCombo			= NULL;
	CELLCOMBOEX* pComboEx		= NULL;
	CELLCHECK* pCheck			= NULL;
	CELLSPIN* pSpin				= NULL;
	CELLPUSHBTN* pPushBtn		= NULL;
	CELLBMPBTN* pBMPBtn			= NULL;
	CELLCODECTRL* pCodeCtrl		= NULL;
	CELLEDIT* pPWEdit			= NULL;
	CELLEDIT* pEdit				= NULL;
	CELLPRGRS* pPrgrs			= NULL;
#ifdef GRADIENT_USE 
	CELLGRADIENTS* pGradients   = NULL;		// Gradient
#endif

	nCmbCnt			= (m_pComboArray		? m_pComboArray->GetSize()		: 0);
	nCheckCnt		= (m_pCheckArray		? m_pCheckArray->GetSize()		: 0);
	nSpinCnt		= (m_pSpinArray			? m_pSpinArray->GetSize()		: 0);
	nPushBtnCnt		= (m_pPushBtnArray		? m_pPushBtnArray->GetSize()	: 0);
	nBMPBtnCnt		= (m_pBMPBtnArray		? m_pBMPBtnArray->GetSize()		: 0);
	nCodeCtrlCnt	= (m_pCodeCtrlArray		? m_pCodeCtrlArray->GetSize()	: 0);
	nPWEditCnt		= (m_pPWEditArray		? m_pPWEditArray->GetSize()		: 0);
	nEditCnt		= (m_pEditArray			? m_pEditArray->GetSize()		: 0);
	nPrgrsCnt		= (m_pPrgrsArray		? m_pPrgrsArray->GetSize()		: 0);

	nCmbExCnt		= (m_pComboExArray		? m_pComboExArray->GetSize()	: 0);


#ifdef GRADIENT_USE 
	nGradientCnt    = (m_pGradientArray		? m_pGradientArray->GetSize()	: 0);	// Gradient
#endif

	if( ar.IsStoring() )							// Write
	{
		nCount = nCmbCnt + nCmbExCnt + nCheckCnt + nSpinCnt + nPushBtnCnt + nBMPBtnCnt + nCodeCtrlCnt + nPWEditCnt + nEditCnt + nPrgrsCnt + nGradientCnt;

		ar << nCount;
		ar << m_dwVersion;

		for ( nIndex = 0 ; nIndex < nCmbCnt; nIndex ++ )
		{
			pCombo = (CELLCOMBO*) m_pComboArray->GetAt(nIndex);
			
			if ( pCombo )
			{
				ar << (int) dxCtrlCombo;
				ar << pCombo->nRow;
				ar << pCombo->nCol;
				ar << pCombo->strItemList;
				ar << pCombo->lDummy;

#ifdef _DEBUG
				if( pCombo->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}

		for ( nIndex = 0 ; nIndex < nCheckCnt; nIndex ++ )
		{
			pCheck = (CELLCHECK*) m_pCheckArray->GetAt(nIndex);
			
			if ( pCheck )
			{
				ar << (int) dxCtrlCheck;
				ar << pCheck->nRow;
				ar << pCheck->nCol;
				ar << pCheck->nCheckVal;
				ar << pCheck->nUnCheckVal;
				ar << pCheck->strText;
				ar << pCheck->lDummy;
				
#ifdef _DEBUG
				if( pCheck->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}

		for ( nIndex = 0 ; nIndex < nSpinCnt; nIndex ++ )
		{
			pSpin = (CELLSPIN*) m_pSpinArray->GetAt(nIndex);
			
			if ( pSpin )
			{
				ar << (int) dxCtrlSpin;
				ar << pSpin->nRow;
				ar << pSpin->nCol;
				ar << pSpin->dbMinVal;
				ar << pSpin->dbMaxVal;
				ar << pSpin->dbStep;
				ar << pSpin->dbInitVal;
				ar << pSpin->lDummy;
				
#ifdef _DEBUG
				if( pSpin->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}

		for ( nIndex = 0 ; nIndex < nPushBtnCnt; nIndex ++ )
		{
			pPushBtn = (CELLPUSHBTN*) m_pPushBtnArray->GetAt(nIndex);
			
			if ( pPushBtn )
			{
				ar << (int) dxCtrlPushBtn;
				ar << pPushBtn->nRow;
				ar << pPushBtn->nCol;
				ar << pPushBtn->nBtCrIndex;
				ar << pPushBtn->strText;
				ar << pPushBtn->lDummy;

#ifdef _DEBUG
				if( pPushBtn->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
		
		for ( nIndex = 0 ; nIndex < nBMPBtnCnt; nIndex ++ )
		{
			pBMPBtn = (CELLBMPBTN*) m_pBMPBtnArray->GetAt(nIndex);
			
			if ( pBMPBtn )
			{
				ar << (int) dxCtrlBMPBtn;
				ar << pBMPBtn->nRow;
				ar << pBMPBtn->nCol;
				ar << pBMPBtn->byStretch;
				ar << pBMPBtn->strTitle;
				ar << pBMPBtn->strNormalName;
				ar << pBMPBtn->strDownName;
				ar << pBMPBtn->lDummy;

#ifdef _DEBUG
				if( pBMPBtn->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
		

		for ( nIndex = 0 ; nIndex < nCodeCtrlCnt; nIndex ++ )
		{
			pCodeCtrl = (CELLCODECTRL*) m_pCodeCtrlArray->GetAt(nIndex);
			
			if ( pCodeCtrl )
			{
				ar << (int) dxCtrlCodeInput;
				ar << pCodeCtrl->nRow;
				ar << pCodeCtrl->nCol;
				ar << pCodeCtrl->byCatalog;
				ar << pCodeCtrl->lDummy;

#ifdef _DEBUG
				if( pCodeCtrl->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
		
		for ( nIndex = 0 ; nIndex < nPWEditCnt; nIndex ++ )
		{
			pPWEdit = (CELLEDIT*) m_pPWEditArray->GetAt(nIndex);
			
			if ( pPWEdit )
			{
				ar << (int) dxCtrlPWEdit;
				ar << pPWEdit->nRow;
				ar << pPWEdit->nCol;
				ar << pPWEdit->nMaxLen;
				ar << pPWEdit->lDummy;

#ifdef _DEBUG
				if( pPWEdit->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}

		for ( nIndex = 0 ; nIndex < nEditCnt; nIndex ++ )
		{
			pEdit = (CELLEDIT*) m_pEditArray->GetAt(nIndex);
			
			if ( pEdit )
			{
				ar << (int) dxCtrlEdit;
				ar << pEdit->nRow;
				ar << pEdit->nCol;
				ar << pEdit->nMaxLen;
				ar << pEdit->lDummy;

#ifdef _DEBUG
				if( pEdit->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
		
		for ( nIndex = 0 ; nIndex < nPrgrsCnt; nIndex ++ )
		{
			pPrgrs = (CELLPRGRS*) m_pPrgrsArray->GetAt(nIndex);
			
			if ( pPrgrs )
			{
				ar << (int) dxCtrlProgress;
				ar << pPrgrs->nRow;
				ar << pPrgrs->nCol;
				ar << pPrgrs->lMinVal;
				ar << pPrgrs->lMaxVal;
				ar << pPrgrs->nStartPos;
				ar << pPrgrs->nCaptionShow;
//				ar << pPrgrs->lDummy;
			}
		}

		for ( nIndex = 0 ; nIndex < nCmbExCnt; nIndex ++ )
		{
			pComboEx = (CELLCOMBOEX*) m_pComboExArray->GetAt(nIndex);
			
			if ( pComboEx )
			{
				ar << (int) dxCtrlComboBoxEx;

				ar << pComboEx->nRow;
				ar << pComboEx->nCol;

				ar << pComboEx->nMaxLen;				// 데이터출력값 
				ar << pComboEx->byValueShow;			// 00=00 데이터
				ar << pComboEx->strChoiceList;
				ar << pComboEx->strFileName;			// Ini 파일명 
				ar << pComboEx->strSectionName;			// [Ini]섹션명 
				ar << pComboEx->lDummy;
#ifdef _DEBUG
				if( pComboEx->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}


#ifdef GRADIENT_USE 
		// Gradient
		for ( nIndex = 0 ; nIndex < nGradientCnt; nIndex ++ )
		{
			pGradients = (CELLGRADIENTS*) m_pGradientArray->GetAt(nIndex);
			
			if ( pGradients )
			{
				ar << (int) dxCtrlGradient;
				ar << pGradients->nRow;
				ar << pGradients->nCol;
				ar << pGradients->lStartClr;
				ar << pGradients->lEndClr;
				ar << pGradients->nMode;
				ar << pGradients->lDummy;
#ifdef _DEBUG
				if( pGradients->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
#endif
	}
	else
	{
		Clear();
		int   nCtrlID;
		DWORD dwReadVersion;

		ar >> nCount;
		ar >> dwReadVersion;

		for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			ar >> nCtrlID;

			switch(nCtrlID)
			{
			case dxCtrlCombo:
				{
					if(m_pComboArray == NULL)
						m_pComboArray = new CPtrArray;

					pCombo = new CELLCOMBO;
		
					if ( pCombo )
					{
						ar >> pCombo->nRow;
						ar >> pCombo->nCol;
						ar >> pCombo->strItemList;
						ar >> pCombo->lDummy;
						
#ifdef _DEBUG
						if( pCombo->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						m_pComboArray->Add((void*) pCombo);
					}
				}
				break;

			case dxCtrlComboBoxEx:
				{
					if(m_pComboExArray == NULL)
						m_pComboExArray = new CPtrArray;

					pComboEx = new CELLCOMBOEX;
		
					if ( pComboEx )
					{
						ar >> pComboEx->nRow;
						ar >> pComboEx->nCol;

						ar >> pComboEx->nMaxLen;				// 데이터출력값 
						ar >> pComboEx->byValueShow;			// 00=00 데이터  
						ar >> pComboEx->strChoiceList;
						ar >> pComboEx->strFileName;			// Ini 파일명 
						ar >> pComboEx->strSectionName;			// [Ini]섹션명 
						ar >> pComboEx->lDummy;

#ifdef _DEBUG
						if( pComboEx->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						m_pComboExArray->Add((void*) pComboEx );
					}
				}
				break;
			case dxCtrlCheck:
				{
					if(m_pCheckArray == NULL)
						m_pCheckArray = new CPtrArray;

					pCheck = new CELLCHECK;
		
					if ( pCheck )
					{
						ar >> pCheck->nRow;
						ar >> pCheck->nCol;
						ar >> pCheck->nCheckVal;
						ar >> pCheck->nUnCheckVal;
						ar >> pCheck->strText;
						ar >> pCheck->lDummy;

#ifdef _DEBUG
						if( pCheck->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						m_pCheckArray->Add((void*) pCheck);
					}
				}
				break;
			case dxCtrlSpin:
				{
					if(m_pSpinArray == NULL)
						m_pSpinArray = new CPtrArray;

					pSpin = new CELLSPIN;
		
					if ( pSpin )
					{
						ar >> pSpin->nRow;
						ar >> pSpin->nCol;
						ar >> pSpin->dbMinVal;
						ar >> pSpin->dbMaxVal;
						ar >> pSpin->dbStep;
						ar >> pSpin->dbInitVal;
						ar >> pSpin->lDummy;

#ifdef _DEBUG
						if( pSpin->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						m_pSpinArray->Add((void*) pSpin);
					}
				}
				break;
			case dxCtrlPushBtn:
				{
					if(m_pPushBtnArray == NULL)
						m_pPushBtnArray = new CPtrArray;

					pPushBtn = new CELLPUSHBTN;
		
					if ( pPushBtn )
					{
						ar >> pPushBtn->nRow;
						ar >> pPushBtn->nCol;
						ar >> pPushBtn->nBtCrIndex;
						ar >> pPushBtn->strText;
						ar >> pPushBtn->lDummy;

#ifdef _DEBUG
						if( pPushBtn->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						m_pPushBtnArray->Add((void*) pPushBtn);
					}
				}
				break;
			case dxCtrlBMPBtn:
				{
					if(m_pBMPBtnArray == NULL)
						m_pBMPBtnArray = new CPtrArray;

					pBMPBtn = new CELLBMPBTN;
		
					if ( pBMPBtn )
					{
						ar >> pBMPBtn->nRow;
						ar >> pBMPBtn->nCol;
						ar >> pBMPBtn->byStretch;
						ar >> pBMPBtn->strTitle;
						ar >> pBMPBtn->strNormalName;
						ar >> pBMPBtn->strDownName;
						ar >> pBMPBtn->lDummy;
#ifdef _DEBUG
						if( pBMPBtn->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						m_pBMPBtnArray->Add((void*) pBMPBtn);
					}
				}
				break;
			case dxCtrlCodeInput:
				{
					if(m_pCodeCtrlArray == NULL)
						m_pCodeCtrlArray = new CPtrArray;

					pCodeCtrl = new CELLCODECTRL;
		
					if ( pCodeCtrl )
					{
						ar >> pCodeCtrl->nRow;
						ar >> pCodeCtrl->nCol;
						ar >> pCodeCtrl->byCatalog;
						ar >> pCodeCtrl->lDummy;

#ifdef _DEBUG
						if( pCodeCtrl->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						m_pCodeCtrlArray->Add((void*) pCodeCtrl);
					}
				}
				break;
			case dxCtrlPWEdit:
				{
					if(m_pPWEditArray == NULL)
						m_pPWEditArray = new CPtrArray;

					pPWEdit = new CELLEDIT;
				
					if ( pPWEdit )
					{
						ar >> pPWEdit->nRow;
						ar >> pPWEdit->nCol;
						ar >> pPWEdit->nMaxLen;
						ar >> pPWEdit->lDummy;

#ifdef _DEBUG
						if( pPWEdit->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						m_pPWEditArray->Add((void*) pPWEdit);
					}
				}
				break;
			case dxCtrlEdit:
				{
					if(m_pEditArray == NULL)
						m_pEditArray = new CPtrArray;

					pEdit = new CELLEDIT;
				
					if ( pEdit )
					{
						ar >> pEdit->nRow;
						ar >> pEdit->nCol;
						ar >> pEdit->nMaxLen;
						ar >> pEdit->lDummy;

#ifdef _DEBUG
						if( pEdit->lDummy )
						{
							ASSERT(FALSE);
						}
#endif

						m_pEditArray->Add((void*) pEdit);
					}
				}
				break;
			case dxCtrlProgress:
				{
					if(m_pPrgrsArray == NULL)
						m_pPrgrsArray = new CPtrArray;

					pPrgrs = new CELLPRGRS;
				
					if ( pPrgrs )
					{
						ar >> pPrgrs->nRow;
						ar >> pPrgrs->nCol;
						ar >> pPrgrs->lMinVal;
						ar >> pPrgrs->lMaxVal;
						ar >> pPrgrs->nStartPos;
						ar >> pPrgrs->nCaptionShow;
//						ar >> pPrgrs->lDummy;

						m_pPrgrsArray->Add((void*) pPrgrs);
					}
				}
				break;
#ifdef GRADIENT_USE 
			case dxCtrlGradient:							// Gradient
				{
					if(m_pGradientArray == NULL)
						m_pGradientArray = new CPtrArray;

					pGradients = new CELLGRADIENTS;
					if ( pGradients )
					{
						ar >> pGradients->nRow;
						ar >> pGradients->nCol;
						ar >> pGradients->lStartClr;
						ar >> pGradients->lEndClr;
						ar >> pGradients->nMode;
						ar >> pGradients->lDummy;

						m_pGradientArray->Add((void*) pGradients );
					}
				}
				break;
#endif
			}
		}
	
	}
}


BOOL CCellCtrl::SetCtrlPropList(int nCtrlID, LPSTR lpBuf )
{
	LPSTR		lpStr;
	//CString strIS = _G_TCH_IS;
	CString strIS;
	strIS.Format("%c", _G_TCH_IS );
	switch(nCtrlID)
	{
	case dxCtrlComboBoxEx:
		{
			// Format
			// Row<US>Col<US>MaxLen<US>byValueShow<US>strChoiceList<US>strFileName<US>strSectionName<US>Dummy<US>...
			CELLCOMBOEX*	pComboEx = NULL;

			if(m_pComboExArray == NULL)
				m_pComboExArray = new CPtrArray;

			ClearCtrl(dxCtrlComboBoxEx);

			while ( *lpBuf != 0 )
			{
				pComboEx = new CELLCOMBOEX;
				//memset(pCombo, 0x00, sizeof(CELLCOMBO));
				
				if ( pComboEx )
				{
					pComboEx->lDummy        = 0;
					pComboEx->strChoiceList = _T("");
					pComboEx->strFileName   = _T("");
					pComboEx->strSectionName = _T("");
					
					pComboEx->nRow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pComboEx->nCol = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pComboEx->nMaxLen = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pComboEx->byValueShow = (BYTE)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );									//strChoiceList
					int   nLen(0);
					BYTE* lpData;
					if ( lpStr != NULL )
					{
						nLen = lpStr - lpBuf;
						//ASSERT(nLen > 0 );
						if( nLen > 0 )
						{
							lpData = new BYTE[nLen+1];
							memset ( lpData, 0x0, nLen+1);
							memcpy ( lpData, &lpBuf[0],  nLen );

							pComboEx->strChoiceList = (LPCTSTR)(char*)lpData;
							//IS를 \n으로 바꾼다.
							pComboEx->strChoiceList.Replace(strIS, _T("\r\n"));
							
							if ( lpData )
								delete[] lpData;
						}
						lpBuf = lpStr;
					}
					if (lpBuf && *lpBuf)
						lpBuf++;
																				  // strFileName
					lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );									
					if ( lpStr != NULL )
					{
						nLen = lpStr - lpBuf;
						//ASSERT(nLen > 0 );
						if( nLen > 0 )
						{
							lpData = new BYTE[nLen+1];
							memset ( lpData, 0x0, nLen+1);
							memcpy ( lpData, &lpBuf[0],  nLen );

							pComboEx->strFileName = (LPCTSTR)(char*)lpData;
							
							if ( lpData )
								delete[] lpData;
						}
						lpBuf = lpStr;
					}
					if (lpBuf && *lpBuf)
						lpBuf++;
																				  // strSectionName

					lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );									
					if ( lpStr != NULL )
					{
						nLen = lpStr - lpBuf;
						//ASSERT(nLen > 0 );
						if( nLen > 0 )
						{
							lpData = new BYTE[nLen+1];
							memset ( lpData, 0x0, nLen+1);
							memcpy ( lpData, &lpBuf[0],  nLen );

							pComboEx->strSectionName = (LPCTSTR)(char*)lpData;
							
							if ( lpData )
								delete[] lpData;
						}
						lpBuf = lpStr;
					}
					if (lpBuf && *lpBuf)
						lpBuf++;

					pComboEx->lDummy = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					m_pComboExArray->Add((void*) pComboEx );
				}

			}
			return TRUE;
		}
		break;
	case 52527:
	case dxCtrlCombo:
		{
			// Format
			// Row<US>Col<US>ItemString<US>Dummy<US>......Row<US>Col<US>ItemString<US>Dummy<US>
			CELLCOMBO*	pCombo = NULL;

			if(m_pComboArray == NULL)
				m_pComboArray = new CPtrArray;

			ClearCtrl(dxCtrlCombo);

			while ( *lpBuf != 0 )
			{
				pCombo = new CELLCOMBO;
				//memset(pCombo, 0x00, sizeof(CELLCOMBO));
				
				if ( pCombo )
				{
					pCombo->lDummy = NULL;
					pCombo->strItemList = _T("");

					pCombo->nRow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pCombo->nCol = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );
					if ( lpStr != NULL )
					{
						int   nLen = lpStr - lpBuf;
						//ASSERT(nLen > 0 );
						if( nLen > 0 )
						{
							BYTE* lpData = new BYTE[nLen+1];
							memset ( lpData, 0x0, nLen+1);
							memcpy ( lpData, &lpBuf[0],  nLen );
							pCombo->strItemList = (LPCTSTR)(char*)lpData;
							
							//IS를 \n으로 바꾼다.
							pCombo->strItemList.Replace(strIS, _T("\r\n"));
							
							if ( lpData )
								delete[] lpData;
						}

						lpBuf = lpStr;
					}
					if (lpBuf && *lpBuf)
						lpBuf++;

					pCombo->lDummy = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					m_pComboArray->Add((void*) pCombo);
				}

			}

			return TRUE;
		}
		break;
	case dxCtrlCheck:
		{
			// Format
			// Row<US>Col<US>CheckVal<US>UnCheckVal<US>Text<US>Dummy<US>......Row<US>Col<US>CheckVal<US>UnCheckVal<US>Text<US>Dummy<US>
			CELLCHECK*	pCheck = NULL;

			if(m_pCheckArray == NULL)
				m_pCheckArray = new CPtrArray;

			ClearCtrl(dxCtrlCheck);

			while ( *lpBuf != 0 )
			{
				pCheck = new CELLCHECK;
				//memset(pCheck, 0x00, sizeof(CELLCHECK));

				if ( pCheck )
				{
					pCheck->lDummy = NULL;
					pCheck->strText = _T("");

					pCheck->nRow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pCheck->nCol = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pCheck->nCheckVal = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pCheck->nUnCheckVal = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

// --> [Edit]  김창하 2006/05/03
					if ( pCheck->nCheckVal == 0 && pCheck->nUnCheckVal == 0 )
					{
						pCheck->nCheckVal = 1;	
					}
// <-- [Edit]  김창하 2006/05/03
					lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );
					if ( lpStr != NULL )
					{
						int   nLen = lpStr - lpBuf;
						//ASSERT(nLen > 0 );
						if( nLen > 0 )
						{
							BYTE* lpData = new BYTE[nLen+1];
							memset ( lpData, 0x0, nLen+1);
							memcpy ( lpData, &lpBuf[0],  nLen );
							pCheck->strText = (LPCTSTR)(char*)lpData;
							
							//IS를 \n으로 바꾼다.
							pCheck->strText.Replace(strIS, _T("\r\n"));

							if ( lpData )
								delete[] lpData;
						}

						lpBuf = lpStr;
					}

					if (lpBuf && *lpBuf)
						lpBuf++;

  					pCheck->lDummy = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					m_pCheckArray->Add((void*) pCheck);
				}

			}

			return TRUE;

		}
		break;
	case dxCtrlSpin:
		{
			// Format
			// Row<US>Col<US>dbMinVal<US>dbMaxVal<US>dbStep<US>dbInitVal<US>Dummy<US>......Row<US>Col<US>dbMinVal<US>dbMaxVal<US>dbStep<US>dbInitVal<US>Dummy<US>
			CELLSPIN*	pSpin = NULL;

			if(m_pSpinArray == NULL)
				m_pSpinArray = new CPtrArray;

			ClearCtrl(dxCtrlSpin);
			
			while ( *lpBuf != 0 )
			{
				pSpin = new CELLSPIN;
				//memset(pSpin, 0x00, sizeof(CELLSPIN));

				if ( pSpin )
				{
					pSpin->lDummy = NULL;

					pSpin->nRow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pSpin->nCol = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pSpin->dbMinVal = strtod(lpBuf, &lpBuf);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pSpin->dbMaxVal = strtod(lpBuf, &lpBuf);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pSpin->dbStep = strtod(lpBuf, &lpBuf);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pSpin->dbInitVal = strtod(lpBuf, &lpBuf);
					if (lpBuf && *lpBuf)
						lpBuf++;

  					pSpin->lDummy = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					m_pSpinArray->Add((void*) pSpin);
				}

			}

			return TRUE;
		}
		break;
	case dxCtrlPushBtn:
		{
			// Format
			// Row<US>Col<US>ButtonColorIndex<US>Text<US>Dummy<US>......Row<US>Col<US>ButtonColorIndex<US>Text<US>Dummy<US>
			CELLPUSHBTN*	pPushBtn = NULL;

			if(m_pPushBtnArray == NULL)
				m_pPushBtnArray = new CPtrArray;

			ClearCtrl(dxCtrlPushBtn);

			while ( *lpBuf != 0 )
			{
				pPushBtn = new CELLPUSHBTN;
				//memset(pPushBtn, 0x00, sizeof(CELLPUSHBTN));

				if ( pPushBtn )
				{
					pPushBtn->lDummy = NULL;
					pPushBtn->strText = _T("");

					pPushBtn->nRow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pPushBtn->nCol = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pPushBtn->nBtCrIndex = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );
					if ( lpStr != NULL )
					{
						int   nLen = lpStr - lpBuf;
						//ASSERT(nLen > 0 );
						if( nLen > 0 )
						{
							BYTE* lpData = new BYTE[nLen+1];
							memset ( lpData, 0x0, nLen+1);
							memcpy ( lpData, &lpBuf[0],  nLen );
							pPushBtn->strText = (LPCTSTR)(char*)lpData;

							//IS를 \n으로 바꾼다.
							pPushBtn->strText.Replace(strIS, _T("\r\n"));

							if ( lpData )
								delete[] lpData;
						}

						lpBuf = lpStr;
					}

					if (lpBuf && *lpBuf)
						lpBuf++;

  					pPushBtn->lDummy = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					m_pPushBtnArray->Add((void*) pPushBtn);
				}

			}

			return TRUE;

		}
		break;
	case dxCtrlBMPBtn:
		{
			// Format
			// Row<US>Col<US>stretch<US>Title<US>normal<US>down<US>Dummy<US>......Row<US>Col<US>stretch<US>Title<US>normal<US>down<US>Dummy<US>
			CELLBMPBTN*	pBMPBtn = NULL;

			if(m_pBMPBtnArray == NULL)
				m_pBMPBtnArray = new CPtrArray;

			ClearCtrl(dxCtrlBMPBtn);

			while ( *lpBuf != 0 )
			{
				pBMPBtn = new CELLBMPBTN;
				//memset(pBMPBtn, 0x00, sizeof(CELLBMPBTN));

				if ( pBMPBtn )
				{
					pBMPBtn->strTitle = _T("");
					pBMPBtn->strNormalName = _T("");
					pBMPBtn->strDownName = _T("");

					pBMPBtn->nRow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pBMPBtn->nCol = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pBMPBtn->byStretch = (BYTE) strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );
					if ( lpStr != NULL )
					{
						int   nLen = lpStr - lpBuf;
						
						if( nLen > 0 )
						{
							BYTE* lpData = new BYTE[nLen+1];
							memset ( lpData, 0x0, nLen+1);
							memcpy ( lpData, &lpBuf[0],  nLen );
							pBMPBtn->strTitle = (LPCTSTR)(char*)lpData;

							if ( lpData )
								delete[] lpData;
						}

						lpBuf = lpStr;
					}

					if (lpBuf && *lpBuf)
						lpBuf++;

					lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );
					if ( lpStr != NULL )
					{
						int   nLen = lpStr - lpBuf;
						
						if( nLen > 0 )
						{
							BYTE* lpData = new BYTE[nLen+1];
							memset ( lpData, 0x0, nLen+1);
							memcpy ( lpData, &lpBuf[0],  nLen );
							pBMPBtn->strNormalName = (LPCTSTR)(char*)lpData;

							if ( lpData )
								delete[] lpData;
						}

						lpBuf = lpStr;
					}

					if (lpBuf && *lpBuf)
						lpBuf++;

					lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );
					if ( lpStr != NULL )
					{
						int   nLen = lpStr - lpBuf;
						
						if( nLen > 0 )
						{
							BYTE* lpData = new BYTE[nLen+1];
							memset ( lpData, 0x0, nLen+1);
							memcpy ( lpData, &lpBuf[0],  nLen );
							pBMPBtn->strDownName = (LPCTSTR)(char*)lpData;

							if ( lpData )
								delete[] lpData;
						}

						lpBuf = lpStr;
					}

					if (lpBuf && *lpBuf)
						lpBuf++;
					
					pBMPBtn->lDummy = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					m_pBMPBtnArray->Add((void*) pBMPBtn);
				}

			}

			return TRUE;

		}
		break;
	case dxCtrlCodeInput:
		{
			// Format
			// Row<US>Col<US>Catalog<US>Dummy<US>......Row<US>Col<US>Catalog<US>Dummy<US>
			CELLCODECTRL*	pCodeCtrl = NULL;

			if(m_pCodeCtrlArray == NULL)
				m_pCodeCtrlArray = new CPtrArray;

			ClearCtrl(dxCtrlCodeInput);

			while ( *lpBuf != 0 )
			{
				pCodeCtrl = new CELLCODECTRL;
	
				if ( pCodeCtrl )
				{
					pCodeCtrl->lDummy = NULL;
					
					pCodeCtrl->nRow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pCodeCtrl->nCol = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pCodeCtrl->byCatalog = (BYTE)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pCodeCtrl->lDummy = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					m_pCodeCtrlArray->Add((void*) pCodeCtrl);
				}

			}

			return TRUE;

		}
		break;
	case dxCtrlPWEdit:
		{
			// Format
			// Row<US>Col<US>MaxLen<US> Dummy<US>......Row<US>Col<US>MaxLen<US> Dummy<US>
			CELLEDIT*	pPWEdit = NULL;

			if(m_pPWEditArray == NULL)
				m_pPWEditArray = new CPtrArray;

			ClearCtrl(dxCtrlPWEdit);

			while ( *lpBuf != 0 )
			{
				pPWEdit = new CELLEDIT;
	
				if ( pPWEdit )
				{
					pPWEdit->lDummy = NULL;
					
					pPWEdit->nRow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pPWEdit->nCol = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pPWEdit->nMaxLen = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pPWEdit->lDummy = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					m_pPWEditArray->Add((void*) pPWEdit);
				}

			}

			return TRUE;

		}
		break;
	case dxCtrlEdit:
		{
			// Format
			// Row<US>Col<US>MaxLen<US> Dummy<US>......Row<US>Col<US>MaxLen<US> Dummy<US>
			CELLEDIT*	pEdit = NULL;

			if(m_pEditArray == NULL)
				m_pEditArray = new CPtrArray;

			ClearCtrl(dxCtrlEdit);

			while ( *lpBuf != 0 )
			{
				pEdit = new CELLEDIT;
	
				if ( pEdit )
				{
					pEdit->lDummy = NULL;
					
					pEdit->nRow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pEdit->nCol = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pEdit->nMaxLen = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pEdit->lDummy = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					m_pEditArray->Add((void*) pEdit);
				}

			}

			return TRUE;

		}
		break;
	case dxCtrlProgress:
		{
			// Format
			// Row<US>Col<US>MinVal<US>MaxVal<US> Dummy<US>......Row<US>Col<US>MinVal<US>MaxVal<US> Dummy<US>
			// 2004년11월29일 변경. 
			// Row<US>Col<US>MinVal<US>MaxVal<US>nStartPos<US>nCaptionShow<US>......Row<US>Col<US>MinVal<US>MaxVal<US>nStartPos<US>nCaptionShow<US>

			CELLPRGRS*	pPrgrs = NULL;

			if(m_pPrgrsArray == NULL)
				m_pPrgrsArray = new CPtrArray;

			ClearCtrl(dxCtrlProgress);

			while ( *lpBuf != 0 )
			{
				pPrgrs = new CELLPRGRS;
	
				if ( pPrgrs )
				{
//					pPrgrs->lDummy = NULL;
					
					pPrgrs->nRow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pPrgrs->nCol = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pPrgrs->lMinVal = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pPrgrs->lMaxVal = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pPrgrs->nStartPos = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pPrgrs->nCaptionShow = (short)strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

//					pPrgrs->lDummy = strtol(lpBuf, &lpBuf, 10);
//					if (lpBuf && *lpBuf)
//						lpBuf++;

					m_pPrgrsArray->Add((void*) pPrgrs);
				}

			}
			return TRUE;
		}
		break;
#ifdef GRADIENT_USE 
	case dxCtrlGradient:			// Gradient
		{
			// Format
			// Row<US>Col<US>lStartClr<US>lEndClr<US>nMode<US>Dummy<US>......

			CELLGRADIENTS*	pGradients = NULL;

			if(m_pGradientArray == NULL)
				m_pGradientArray = new CPtrArray;

			ClearCtrl( dxCtrlGradient );

			while ( *lpBuf != 0 )
			{
				pGradients = new CELLGRADIENTS;
	
				if ( pGradients  )
				{
					pGradients->nRow	= strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pGradients->nCol	= strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pGradients->lStartClr = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pGradients->lEndClr = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pGradients->nMode  = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					pGradients->lDummy = strtol(lpBuf, &lpBuf, 10);
					if (lpBuf && *lpBuf)
						lpBuf++;

					m_pGradientArray->Add((void*) pGradients );
				}
			}
			return TRUE;
		}
		break;
#endif
	}

	return FALSE;
}

BOOL CCellCtrl::GetCtrlPropList(int nCtrlID, CString& strList)
{
	strList = _T("");
	char szTemp[1024];
	
	int nIndex, nCount;
	switch(nCtrlID)
	{
	case dxCtrlComboBoxEx:
		{
			// Format			
			// Row<US>Col<US>MaxLen<US>byValueShow<US>strChoiceList<US>strFileName<US>strSectionName<US>Dummy<US>...
			if(m_pComboExArray == NULL)
				return FALSE;

			CELLCOMBOEX*	pComboEx = NULL;
			nCount = m_pComboExArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pComboEx = (CELLCOMBOEX*) m_pComboExArray->GetAt(nIndex);
				
				if ( pComboEx )
				{
					wsprintf(szTemp, _T("%d%c%d%c%d%c%d%c%s%c%s%c%s%c%d%c"), 
									pComboEx->nRow,_G_TCH_US,
									pComboEx->nCol,_G_TCH_US,
									pComboEx->nMaxLen,_G_TCH_US,				// 데이터출력값 
									pComboEx->byValueShow,_G_TCH_US,			// 00=00 데이터
									pComboEx->strChoiceList,_G_TCH_US,			// 입력리스트문자열  
									pComboEx->strFileName,_G_TCH_US,			// Ini 파일명 
									pComboEx->strSectionName,_G_TCH_US,		// [Ini]섹션명 
									pComboEx->lDummy,_G_TCH_US);
					strList += szTemp;
				}
			}
		}
		break;
	case 52527:
	case dxCtrlCombo:
		{
			// Format
			// Row<US>Col<US>ItemString<US>Dummy<US>......Row<US>Col<US>ItemString<US>Dummy<US>
			if(m_pComboArray == NULL)
				return FALSE;

			CELLCOMBO*	pCombo = NULL;
			nCount = m_pComboArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pCombo = (CELLCOMBO*) m_pComboArray->GetAt(nIndex);
				
				if ( pCombo )
				{
			
					wsprintf(szTemp, _T("%d%c%d%c%s%c%d%c"), 
									pCombo->nRow,_G_TCH_US,
									pCombo->nCol,_G_TCH_US,
									pCombo->strItemList,_G_TCH_US,
									pCombo->lDummy,_G_TCH_US);


					strList += szTemp;
				}
			}

			//\n를 ' '으로 바꾼다.
			//strList.Replace(_T("\r\n"), strIS);
		}
		break;
	case dxCtrlCheck:
		{
			// Format
			// Row<US>Col<US>CheckVal<US>UnCheckVal<US>Text<US>Dummy<US>......Row<US>Col<US>CheckVal<US>UnCheckVal<US>Text<US>Dummy<US>
			if(m_pCheckArray == NULL)
				return FALSE;

			CELLCHECK*	pCheck = NULL;
			nCount = m_pCheckArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pCheck = (CELLCHECK*) m_pCheckArray->GetAt(nIndex);
// --> [Edit]  김창하 2006/05/03
				if ( pCheck->nCheckVal == 0 && pCheck->nUnCheckVal == 0 )
					pCheck->nCheckVal = 1;
// <-- [Edit]  김창하 2006/05/03

				if ( pCheck )
				{
					wsprintf(szTemp, _T("%d%c%d%c%d%c%d%c%s%c%d%c"), 
									pCheck->nRow,_G_TCH_US,
									pCheck->nCol,_G_TCH_US,
									pCheck->nCheckVal,_G_TCH_US,
									pCheck->nUnCheckVal,_G_TCH_US,
									pCheck->strText,_G_TCH_US,
									pCheck->lDummy,_G_TCH_US );

					strList += szTemp;

				}
			}

			//\n를 ' '으로 바꾼다.
			//strList.Replace(_T("\r\n"), strIS);
		}
		break;
	case dxCtrlSpin:
		{
			// Format
			// Row<US>Col<US>dbMinVal<US>dbMaxVal<US>dbStep<US>dbInitVal<US>Dummy<US>......Row<US>Col<US>dbMinVal<US>dbMaxVal<US>dbStep<US>dbInitVal<US>Dummy<US>
			if(m_pSpinArray == NULL)
				return FALSE;

			CELLSPIN*	pSpin = NULL;
			nCount = m_pSpinArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pSpin = (CELLSPIN*) m_pSpinArray->GetAt(nIndex);
				
				if ( pSpin )
				{
					sprintf(szTemp, _T("%d%c%d%c%g%c%g%c%g%c%g%c%d%c"), 
									pSpin->nRow,_G_TCH_US,
									pSpin->nCol,_G_TCH_US,
									pSpin->dbMinVal,_G_TCH_US,
									pSpin->dbMaxVal,_G_TCH_US,
									pSpin->dbStep,_G_TCH_US,
									pSpin->dbInitVal,_G_TCH_US,
									pSpin->lDummy,_G_TCH_US);

					strList += szTemp;

				}
			}

		}
		break;
	case dxCtrlPushBtn:
		{
			// Format
			// Row<US>Col<US>ButtonColorIndex<US>Text<US>Dummy<US>......Row<US>Col<US>ButtonColorIndex<US>Text<US>Dummy<US>
			if(m_pPushBtnArray == NULL)
				return FALSE;

			CELLPUSHBTN*	pPushBtn = NULL;
			nCount = m_pPushBtnArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pPushBtn = (CELLPUSHBTN*) m_pPushBtnArray->GetAt(nIndex);
				
				if ( pPushBtn )
				{
					wsprintf(szTemp, _T("%d%c%d%c%d%c%s%c%d%c"),
									pPushBtn->nRow,_G_TCH_US,
									pPushBtn->nCol,_G_TCH_US,
									pPushBtn->nBtCrIndex,_G_TCH_US,
									pPushBtn->strText,_G_TCH_US,
									pPushBtn->lDummy,_G_TCH_US );

					strList += szTemp;

				}
			}

			//\n를 ' '으로 바꾼다.
			//strList.Replace(_T("\r\n"), strIS);
		}
		break;
	case dxCtrlBMPBtn:
		{
			// Format
			// Row<US>Col<US>stretch<US>Title<US>normal<US>down<US>Dummy<US>......Row<US>Col<US>stretch<US>Title<US>normal<US>down<US>Dummy<US>
			if(m_pBMPBtnArray == NULL)
				return FALSE;

			CELLBMPBTN*	pBMPBtn = NULL;
			nCount = m_pBMPBtnArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pBMPBtn = (CELLBMPBTN*) m_pBMPBtnArray->GetAt(nIndex);
				
				if ( pBMPBtn )
				{
					wsprintf(szTemp, _T("%d%c%d%c%d%c%s%c%s%c%s%c%d%c"),
									pBMPBtn->nRow,_G_TCH_US,
									pBMPBtn->nCol,_G_TCH_US,
									pBMPBtn->byStretch,_G_TCH_US,
									pBMPBtn->strTitle,_G_TCH_US,
									pBMPBtn->strNormalName,_G_TCH_US,
									pBMPBtn->strDownName,_G_TCH_US,
									pBMPBtn->lDummy,_G_TCH_US );

					strList += szTemp;

				}
			}

			//\n를 ' '으로 바꾼다.
			//strList.Replace(_T("\r\n"), strIS);
		}
		break;
	case dxCtrlCodeInput:
		{
			// Format
			// Row<US>Col<US>Catalog<US>Dummy<US>......Row<US>Col<US>Catalog<US>Dummy<US>
			if( m_pCodeCtrlArray == NULL)
				return FALSE;

			CELLCODECTRL*	pCodeCtrl = NULL;
			nCount = m_pCodeCtrlArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pCodeCtrl = (CELLCODECTRL*) m_pCodeCtrlArray->GetAt(nIndex);
				
				if ( pCodeCtrl )
				{
					wsprintf(szTemp, _T("%d%c%d%c%d%c%d%c"),
									pCodeCtrl->nRow,_G_TCH_US,
									pCodeCtrl->nCol,_G_TCH_US,
									pCodeCtrl->byCatalog,_G_TCH_US,
									pCodeCtrl->lDummy,_G_TCH_US);

					strList += szTemp;

				}
			}
		}
		break;
	case dxCtrlPWEdit:
		{
			// Format
			// Row<US>Col<US>MaxLen<US>Dummy<US>......Row<US>Col<US>MaxLen<US>Dummy<US>
			if( m_pPWEditArray == NULL)
				return FALSE;

			CELLEDIT*	pPWEdit = NULL;
			nCount = m_pPWEditArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pPWEdit = (CELLEDIT*) m_pPWEditArray->GetAt(nIndex);
				
				if ( pPWEdit )
				{
					wsprintf(szTemp, _T("%d%c%d%c%d%c%d%c"),
									pPWEdit->nRow,_G_TCH_US,
									pPWEdit->nCol,_G_TCH_US,
									pPWEdit->nMaxLen,_G_TCH_US,
									pPWEdit->lDummy,_G_TCH_US);

					strList += szTemp;

				}
			}
		}
		break;
	case dxCtrlEdit:
		{
			// Format
			// Row<US>Col<US>MaxLen<US>Dummy<US>......Row<US>Col<US>MaxLen<US>Dummy<US>
			if( m_pEditArray == NULL)
				return FALSE;

			CELLEDIT*	pEdit = NULL;
			nCount = m_pEditArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pEdit = (CELLEDIT*) m_pEditArray->GetAt(nIndex);
				
				if ( pEdit )
				{
					wsprintf(szTemp, _T("%d%c%d%c%d%c%d%c"),
									pEdit->nRow,_G_TCH_US,
									pEdit->nCol,_G_TCH_US,
									pEdit->nMaxLen,_G_TCH_US,
									pEdit->lDummy,_G_TCH_US);

					strList += szTemp;

				}
			}
		}
		break;
	case dxCtrlProgress:
		{
			// Format
			// Row<US>Col<US>MinVal<US>MaxVal<US> Dummy<US>......Row<US>Col<US>MinVal<US>MaxVal<US> Dummy<US>
			// 2004년11월29일 변경 
			// Row<US>Col<US>MinVal<US>MaxVal<US>nStartPos<US>nCaptionShow<US>......Row<US>Col<US>MinVal<US>MaxVal<US>nStartPos<US>nCaptionShow<US>
			if( m_pPrgrsArray == NULL)
				return FALSE;

			CELLPRGRS*	pPrgrs = NULL;
			nCount = m_pPrgrsArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pPrgrs = (CELLPRGRS*) m_pPrgrsArray->GetAt(nIndex);
				
				if ( pPrgrs )
				{
					wsprintf(szTemp, _T("%d%c%d%c%d%c%d%c%d%c%d%c"),
									pPrgrs->nRow,_G_TCH_US,
									pPrgrs->nCol,_G_TCH_US,
									pPrgrs->lMinVal,_G_TCH_US,
									pPrgrs->lMaxVal,_G_TCH_US,
									pPrgrs->nStartPos,_G_TCH_US,
									pPrgrs->nCaptionShow,_G_TCH_US);

					strList += szTemp;

				}
			}
		}
		break;
#ifdef GRADIENT_USE 
	case dxCtrlGradient:			// Gradient
		{
			// Format
			// Row<US>Col<US>lStartClr<US>lEndClr<US>nMode<US>Dummy<US>...
			if( m_pGradientArray == NULL)
				return FALSE;

			CELLGRADIENTS*	pGradients = NULL;
			nCount = m_pGradientArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pGradients = (CELLGRADIENTS*) m_pGradientArray->GetAt(nIndex);
				
				if ( pGradients )
				{
					wsprintf(szTemp, _T("%d%c%d%c%d%c%d%c%d%c%d%c"),
									pGradients->nRow,_G_TCH_US,
									pGradients->nCol,_G_TCH_US,
									pGradients->lStartClr,_G_TCH_US,
									pGradients->lEndClr,_G_TCH_US,
									pGradients->nMode,_G_TCH_US,
									pGradients->lDummy,_G_TCH_US);

					strList += szTemp;

				}
			}
		}
		break;
#endif
	}

	return (!strList.IsEmpty());
}


BOOL CCellCtrl::GetAllCtrlPropList ( CString& strList)
{
	strList = _T("");
	CString strBuf,  strTemp;
	int nCount = sizeof(ControlID) / sizeof(ControlID[0]);
	
	for ( int nIndex = /*BASIC_CTRLCNT*/ 0; nIndex < nCount ; nIndex ++ )
	{
		if ( GetCtrlPropList ( ControlID[nIndex], strBuf  ) )
		{
			// CtlID<US>XXX<GS>
			strTemp.Format("%d%c%s%c", ControlID[nIndex], _G_TCH_US, strBuf, _G_TCH_GS );
			strList += strTemp;
		}
	}

	return (BOOL)strList.GetLength();
}

BOOL CCellCtrl::SetAllCtrlPropList ( CString& strList)
{
	BOOL bRet = TRUE;
	
	LPSTR		lpBuf;
	LPSTR		lpStr;
	
	lpBuf = (LPSTR)strList.GetBuffer(0);
	int    nLen;

	while ( *lpBuf != 0 )
	{
		int nCtlID = strtol( lpBuf, &lpBuf, 10);
		if (lpBuf && *lpBuf)
			lpBuf++;
		
		lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_GS );
		if ( lpStr != NULL )
		{
			nLen = lpStr - lpBuf + 1;
			if ( nLen > 1 )
			{
				char* lpData = new char[nLen+1];
				memcpy (lpData, lpBuf, nLen );
				if ( lpData[nLen-1] == _G_TCH_GS )
					lpData[nLen-1] = 0x00;

				SetCtrlPropList ( nCtlID, lpData );	
				if ( lpData )
					delete[] lpData;

				lpBuf = lpStr;
				if (lpBuf && *lpBuf)
					lpBuf++;

			}
		}
	}

	return bRet;
}

void* CCellCtrl::GetCtrlInfo(int nCtrlID, short nRow, short nCol, BOOL bNewAlloc /*= FALSE*/)
{
	int nIndex, nCount;
	switch(nCtrlID)
	{
	case dxCtrlComboBoxEx:
		{
			if( m_pComboExArray == NULL )
				return NULL;

			CELLCOMBOEX*	pComboEx = NULL;
			nCount = m_pComboExArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pComboEx = (CELLCOMBOEX*) m_pComboExArray->GetAt(nIndex);
				
				if ( pComboEx )
				{
					if( pComboEx->nRow == nRow && pComboEx->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pComboEx;
						}
						else
						{
							CELLCOMBOEX*	pNewCtrlEx = new CELLCOMBOEX;
							ASSERT(pNewCtrlEx);

							pNewCtrlEx->nRow		= pComboEx->nRow;
							pNewCtrlEx->nCol		= pComboEx->nCol;
							pNewCtrlEx->nMaxLen     = pComboEx->nMaxLen;				// 데이터출력값 
							pNewCtrlEx->byValueShow = pComboEx->byValueShow;			// 00=00 데이터
							pNewCtrlEx->strChoiceList  = pComboEx->strChoiceList;
							pNewCtrlEx->strFileName	   = pComboEx->strFileName;			// Ini 파일명 
							pNewCtrlEx->strSectionName = pComboEx->strSectionName;			// [Ini]섹션명 
							pNewCtrlEx->lDummy		   = pComboEx->lDummy;
							return (void*) pNewCtrlEx;
						}
					}
				}
			}
			return NULL;
		}
		break;
	case 52527:
	case dxCtrlCombo:
		{
			if( m_pComboArray == NULL )
				return NULL;

			CELLCOMBO*	pCombo = NULL;
			nCount = m_pComboArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pCombo = (CELLCOMBO*) m_pComboArray->GetAt(nIndex);
				
				if ( pCombo )
				{
					if( pCombo->nRow == nRow && pCombo->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pCombo;
						}
						else
						{
							CELLCOMBO*	pNewCtrl = new CELLCOMBO;
							ASSERT(pNewCtrl);
							pNewCtrl->nRow			= pCombo->nRow;
							pNewCtrl->nCol			= pCombo->nCol;
							pNewCtrl->strItemList	= pCombo->strItemList;
							pNewCtrl->lDummy		= pCombo->lDummy;
							return (void*) pNewCtrl;
						}
					}
				}
			}

			return NULL;
		}
		break;
	case dxCtrlCheck:
		{
			if(m_pCheckArray == NULL)
				return FALSE;

			CELLCHECK*	pCheck = NULL;
			nCount = m_pCheckArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pCheck = (CELLCHECK*) m_pCheckArray->GetAt(nIndex);
				
				if ( pCheck )
				{
					if( pCheck->nRow == nRow && pCheck->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pCheck;
						}
						else
						{
							CELLCHECK*	pNewCtrl = new CELLCHECK;
							ASSERT(pNewCtrl);
							pNewCtrl->nRow			= pCheck->nRow;
							pNewCtrl->nCol			= pCheck->nCol;
							pNewCtrl->nCheckVal		= pCheck->nCheckVal;
							pNewCtrl->nUnCheckVal	= pCheck->nUnCheckVal;
							pNewCtrl->strText		= pCheck->strText;
							pNewCtrl->lDummy		= pCheck->lDummy;
							return (void*) pNewCtrl;

						}
					}
				}
			}

			return NULL;

		}
		break;
	case dxCtrlSpin:
		{
			if(m_pSpinArray == NULL)
				return NULL;

			CELLSPIN*	pSpin = NULL;
			nCount = m_pSpinArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pSpin = (CELLSPIN*) m_pSpinArray->GetAt(nIndex);
				
				if ( pSpin )
				{
					if( pSpin->nRow == nRow && pSpin->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pSpin;
						}
						else
						{
							CELLSPIN*	pNewCtrl = new CELLSPIN;
							ASSERT(pNewCtrl);
							memcpy(pNewCtrl, pSpin, sizeof(CELLSPIN));
							return (void*) pNewCtrl;

						}
					}
						
				}
			}

			return NULL;
		}
		break;
	case dxCtrlPushBtn:
		{
			if(m_pPushBtnArray == NULL)
				return FALSE;

			CELLPUSHBTN*	pPushBtn = NULL;
			nCount = m_pPushBtnArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pPushBtn = (CELLPUSHBTN*) m_pPushBtnArray->GetAt(nIndex);
				
				if ( pPushBtn )
				{
					if( pPushBtn->nRow == nRow && pPushBtn->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pPushBtn;
						}
						else
						{
							CELLPUSHBTN*	pNewCtrl = new CELLPUSHBTN;
							ASSERT(pNewCtrl);
							pNewCtrl->nRow			= pPushBtn->nRow;
							pNewCtrl->nCol			= pPushBtn->nCol;
							pNewCtrl->nBtCrIndex	= pPushBtn->nBtCrIndex;
							pNewCtrl->strText		= pPushBtn->strText;
							pNewCtrl->lDummy		= pPushBtn->lDummy;
							return (void*) pNewCtrl;
						}
					}
						
				}
			}

			return NULL;

		}
		break;
	case dxCtrlBMPBtn:
		{
			if(m_pBMPBtnArray == NULL)
				return FALSE;

			CELLBMPBTN*	pBMPBtn = NULL;
			nCount = m_pBMPBtnArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pBMPBtn = (CELLBMPBTN*) m_pBMPBtnArray->GetAt(nIndex);
				
				if ( pBMPBtn )
				{
					if( pBMPBtn->nRow == nRow && pBMPBtn->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pBMPBtn;
						}
						else
						{
							CELLBMPBTN*	pNewCtrl = new CELLBMPBTN;
							ASSERT(pNewCtrl);
							pNewCtrl->nRow			= pBMPBtn->nRow;
							pNewCtrl->nCol			= pBMPBtn->nCol;
							pNewCtrl->byStretch		= pBMPBtn->byStretch;
							pNewCtrl->strTitle		= pBMPBtn->strTitle;
							pNewCtrl->strNormalName	= pBMPBtn->strNormalName;
							pNewCtrl->strDownName	= pBMPBtn->strDownName;
							pNewCtrl->lDummy		= pBMPBtn->lDummy;
							return (void*) pNewCtrl;
						}
					}
				}
			}

			return NULL;

		}
		break;
	case dxCtrlCodeInput:
		{
			if(m_pCodeCtrlArray == NULL)
				return FALSE;

			CELLCODECTRL*	pCodeCtrl = NULL;
			nCount = m_pCodeCtrlArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pCodeCtrl = (CELLCODECTRL*) m_pCodeCtrlArray->GetAt(nIndex);
				
				if ( pCodeCtrl )
				{
					if( pCodeCtrl->nRow == nRow && pCodeCtrl->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pCodeCtrl;
						}
						else
						{
							CELLCODECTRL*	pNewCtrl = new CELLCODECTRL;
							ASSERT(pNewCtrl);
							memcpy(pNewCtrl, pCodeCtrl, sizeof(CELLCODECTRL));
							return (void*) pNewCtrl;
						}
					}
						
				}
			}

			return NULL;

		}
		break;
	case dxCtrlPWEdit:
		{
			if(m_pPWEditArray == NULL)
				return FALSE;

			CELLEDIT*	pPWEdit = NULL;
			nCount = m_pPWEditArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pPWEdit = (CELLEDIT*) m_pPWEditArray->GetAt(nIndex);
				
				if ( pPWEdit )
				{
					if( pPWEdit->nRow == nRow && pPWEdit->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pPWEdit;
						}
						else
						{
							CELLEDIT*	pNewCtrl = new CELLEDIT;
							ASSERT(pNewCtrl);
							memcpy(pNewCtrl, pPWEdit, sizeof(CELLEDIT));
							return (void*) pNewCtrl;
						}
					}
						
				}
			}

			return NULL;

		}
		break;
	case dxCtrlEdit:
		{
			if(m_pEditArray == NULL)
				return FALSE;

			CELLEDIT*	pEdit = NULL;
			nCount = m_pEditArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pEdit = (CELLEDIT*) m_pEditArray->GetAt(nIndex);
				
				if ( pEdit )
				{
					if( pEdit->nRow == nRow && pEdit->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pEdit;
						}
						else
						{
							CELLEDIT*	pNewCtrl = new CELLEDIT;
							ASSERT(pNewCtrl);
							memcpy(pNewCtrl, pEdit, sizeof(CELLEDIT));
							return (void*) pNewCtrl;
						}
					}
						
				}
			}

			return NULL;

		}
		break;
	case dxCtrlProgress:
		{
			if(m_pPrgrsArray == NULL)
				return FALSE;

			CELLPRGRS*	pPrgrs = NULL;
			nCount = m_pPrgrsArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pPrgrs = (CELLPRGRS*) m_pPrgrsArray->GetAt(nIndex);
				
				if ( pPrgrs )
				{
					if( pPrgrs->nRow == nRow && pPrgrs->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pPrgrs;
						}
						else
						{
							CELLPRGRS*	pNewCtrl = new CELLPRGRS;
							ASSERT(pNewCtrl);
							memcpy(pNewCtrl, pPrgrs, sizeof(CELLPRGRS));
							return (void*) pNewCtrl;
						}
					}
						
				}
			}

			return NULL;

		}
		break;
#ifdef GRADIENT_USE 
	case dxCtrlGradient:					// Gradient
		{
			if(m_pGradientArray == NULL)
				return FALSE;

			CELLGRADIENTS*	pGradients = NULL;
			nCount   = m_pGradientArray->GetSize();

			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pGradients = (CELLGRADIENTS*) m_pGradientArray->GetAt(nIndex);
				
				if ( pGradients )
				{
					if( pGradients->nRow == nRow && pGradients->nCol == nCol )
					{
						if( !bNewAlloc )
						{
							return (void*) pGradients;
						}
						else
						{
							CELLGRADIENTS*	pNewCtrl = new CELLGRADIENTS;
							ASSERT(pNewCtrl);
							memcpy(pNewCtrl, pGradients, sizeof(CELLGRADIENTS));
							return (void*) pNewCtrl;
						}
					}
				}
			}
			return NULL;
		}
		break;
#endif
	}

	return NULL;
}

void CCellCtrl::Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol /*= TRUE*/)
{
	int nIndex, nCount;
	BOOL bToRight = (nFrom < nDest);

	if( m_pComboArray )
	{
		CELLCOMBO*	pCombo = NULL;
		nCount = m_pComboArray->GetSize();
		
		for( nIndex = 0; nIndex < nCount; nIndex++ )
		{
			pCombo = (CELLCOMBO*) m_pComboArray->GetAt(nIndex);
				
			if ( pCombo )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pCombo->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pCombo->nRow, nFrom, nDest, bToRight);
				}
			}
		}
	}

	if( m_pComboExArray )
	{
		CELLCOMBOEX*	pCombo = NULL;
		nCount = m_pComboExArray->GetSize();
		
		for( nIndex = 0; nIndex < nCount; nIndex++ )
		{
			pCombo = (CELLCOMBOEX*) m_pComboExArray->GetAt(nIndex);
				
			if ( pCombo )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pCombo->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pCombo->nRow, nFrom, nDest, bToRight);
				}
			}
		}
	}

	if( m_pCheckArray )
	{
		CELLCHECK*	pCheck = NULL;
		nCount = m_pCheckArray->GetSize();
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCheck = (CELLCHECK*) m_pCheckArray->GetAt(nIndex);
			
			if ( pCheck )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pCheck->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pCheck->nRow, nFrom, nDest, bToRight);
				}
			}
		}
	}

	if( m_pSpinArray )
	{
		CELLSPIN*	pSpin = NULL;
		nCount = m_pSpinArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pSpin = (CELLSPIN*) m_pSpinArray->GetAt(nIndex);
			
			if ( pSpin )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pSpin->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pSpin->nRow, nFrom, nDest, bToRight);
				}
			}

		}
	}

	if( m_pPushBtnArray )
	{
		CELLPUSHBTN*	pPushBtn = NULL;
		nCount = m_pPushBtnArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPushBtn = (CELLPUSHBTN*) m_pPushBtnArray->GetAt(nIndex);
			
			if ( pPushBtn )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pPushBtn->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pPushBtn->nRow, nFrom, nDest, bToRight);
				}
			}

		}
	}

	if( m_pBMPBtnArray )
	{
		CELLBMPBTN*	pBMPBtn = NULL;
		nCount = m_pBMPBtnArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pBMPBtn = (CELLBMPBTN*) m_pBMPBtnArray->GetAt(nIndex);
			
			if ( pBMPBtn )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pBMPBtn->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pBMPBtn->nRow, nFrom, nDest, bToRight);
				}
			}

		}
	}
	
	if( m_pCodeCtrlArray )
	{
		CELLCODECTRL*	pCodeCtrl = NULL;
		nCount = m_pCodeCtrlArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCodeCtrl = (CELLCODECTRL*) m_pCodeCtrlArray->GetAt(nIndex);
			
			if ( pCodeCtrl )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pCodeCtrl->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pCodeCtrl->nRow, nFrom, nDest, bToRight);
				}
			}
		}
	}

	if( m_pPWEditArray )
	{
		CELLEDIT*	pPWEdit = NULL;
		nCount = m_pPWEditArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPWEdit = (CELLEDIT*) m_pPWEditArray->GetAt(nIndex);
			
			if ( pPWEdit )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pPWEdit->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pPWEdit->nRow, nFrom, nDest, bToRight);
				}
			}
		}
	}
	
	if( m_pEditArray )
	{
		CELLEDIT*	pEdit = NULL;
		nCount = m_pEditArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pEdit = (CELLEDIT*) m_pEditArray->GetAt(nIndex);
			
			if ( pEdit )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pEdit->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pEdit->nRow, nFrom, nDest, bToRight);
				}
			}
		}
	}

	if( m_pPrgrsArray )
	{
		CELLPRGRS*	pPrgrs = NULL;
		nCount = m_pPrgrsArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPrgrs = (CELLPRGRS*) m_pPrgrsArray->GetAt(nIndex);
			
			if ( pPrgrs )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pPrgrs->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pPrgrs->nRow, nFrom, nDest, bToRight);
				}
			}
		}
	}
#ifdef GRADIENT_USE 
	if( m_pGradientArray )						// Gradient
	{
		CELLGRADIENTS*	pGradients = NULL;
		nCount = m_pGradientArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pGradients = (CELLGRADIENTS*) m_pGradientArray->GetAt(nIndex);
			
			if ( pGradients )
			{
				if( bMoveCol )
				{
					MoveRowColIndex(pGradients->nCol, nFrom, nDest, bToRight);
				}
				else
				{
					MoveRowColIndex(pGradients->nRow, nFrom, nDest, bToRight);
				}
			}
		}
	}
#endif
}

void CCellCtrl::MoveRowColIndex(short& nRowCol, DWORD nFrom, DWORD nDest, BOOL bToRight)
{
	DWORD nCnt = 1;

	if(bToRight)
	{
		if(nRowCol == nFrom)
			nRowCol = (short)nDest;
		else if(nRowCol > nFrom && nRowCol <= nDest)
			nRowCol -= (short)nCnt;
	}
	else
	{
		if(nRowCol == nFrom)
			nRowCol = (short)nDest;
		else if(nRowCol >= nDest && nRowCol < nFrom)
			nRowCol += (short)nCnt;

		/*
		if(nRowCol == nDest)
			nRowCol = nFrom;
		else if(nRowCol > nDest && nRowCol <= nFrom)
			nRowCol -= nCnt;
		*/
	}

}

// Insert Columns Or Rows
void CCellCtrl::Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol /*= TRUE*/)
{
	int nIndex, nCount;

	if( m_pComboArray )
	{
		CELLCOMBO*	pCombo = NULL;
		nCount = m_pComboArray->GetSize();
		
		for( nIndex = 0; nIndex < nCount; nIndex++ )
		{
			pCombo = (CELLCOMBO*) m_pComboArray->GetAt(nIndex);
				
			if ( pCombo )
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pCombo->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pCombo->nRow, nAddIndex, nAddCount);
				}
			}
		}
	}

	if( m_pComboExArray )
	{
		CELLCOMBOEX*	pComboEx = NULL;
		nCount = m_pComboExArray->GetSize();
		
		for( nIndex = 0; nIndex < nCount; nIndex++ )
		{
			pComboEx = (CELLCOMBOEX*) m_pComboExArray->GetAt(nIndex);
				
			if ( pComboEx)
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pComboEx->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pComboEx->nRow, nAddIndex, nAddCount);
				}
			}
		}
	}

	if( m_pCheckArray )
	{
		CELLCHECK*	pCheck = NULL;
		nCount = m_pCheckArray->GetSize();
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCheck = (CELLCHECK*) m_pCheckArray->GetAt(nIndex);
			
			if ( pCheck )
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pCheck->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pCheck->nRow, nAddIndex, nAddCount);
				}
			}
		}
	}

	if( m_pSpinArray )
	{
		CELLSPIN*	pSpin = NULL;
		nCount = m_pSpinArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pSpin = (CELLSPIN*) m_pSpinArray->GetAt(nIndex);
			
			if ( pSpin )
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pSpin->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pSpin->nRow, nAddIndex, nAddCount);
				}
			}

		}
	}

	if( m_pPushBtnArray )
	{
		CELLPUSHBTN*	pPushBtn = NULL;
		nCount = m_pPushBtnArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPushBtn = (CELLPUSHBTN*) m_pPushBtnArray->GetAt(nIndex);
			
			if ( pPushBtn )
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pPushBtn->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pPushBtn->nRow, nAddIndex, nAddCount);
				}
			}

		}
	}

	if( m_pBMPBtnArray )
	{
		CELLBMPBTN*	pBMPBtn = NULL;
		nCount = m_pBMPBtnArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pBMPBtn = (CELLBMPBTN*) m_pBMPBtnArray->GetAt(nIndex);
			
			if ( pBMPBtn )
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pBMPBtn->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pBMPBtn->nRow, nAddIndex, nAddCount);
				}
			}

		}
	}
	
	if( m_pCodeCtrlArray )
	{
		CELLCODECTRL*	pCodeCtrl = NULL;
		nCount = m_pCodeCtrlArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCodeCtrl = (CELLCODECTRL*) m_pCodeCtrlArray->GetAt(nIndex);
			
			if ( pCodeCtrl )
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pCodeCtrl->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pCodeCtrl->nRow, nAddIndex, nAddCount);
				}
			}
		}
	}

	if( m_pPWEditArray )
	{
		CELLEDIT*	pPWEdit = NULL;
		nCount = m_pPWEditArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPWEdit = (CELLEDIT*) m_pPWEditArray->GetAt(nIndex);
			
			if ( pPWEdit )
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pPWEdit->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pPWEdit->nRow, nAddIndex, nAddCount);
				}
			}
		}
	}

	if( m_pEditArray )
	{
		CELLEDIT*	pEdit = NULL;
		nCount = m_pEditArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pEdit = (CELLEDIT*) m_pEditArray->GetAt(nIndex);
			
			if ( pEdit )
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pEdit->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pEdit->nRow, nAddIndex, nAddCount);
				}
			}
		}
	}

	if( m_pPrgrsArray )
	{
		CELLPRGRS*	pPrgrs = NULL;
		nCount = m_pPrgrsArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPrgrs = (CELLPRGRS*) m_pPrgrsArray->GetAt(nIndex);
			
			if ( pPrgrs )
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pPrgrs->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pPrgrs->nRow, nAddIndex, nAddCount);
				}
			}
		}
	}
#ifdef GRADIENT_USE 
	if( m_pGradientArray )						// Gradient
	{
		CELLGRADIENTS*	pGradients = NULL;
		nCount = m_pGradientArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pGradients = (CELLGRADIENTS*) m_pGradientArray->GetAt(nIndex);
			
			if ( pGradients )
			{
				// Column Insert
				if( bInsertCol )
				{
					InsertRowColIndex(pGradients->nCol, nAddIndex, nAddCount);
				}
				else
				{
					InsertRowColIndex(pGradients->nRow, nAddIndex, nAddCount);
				}
			}
		}
	}
#endif
}

void CCellCtrl::InsertRowColIndex(short& nRowCol, DWORD nAddIndex, DWORD nAddCount)
{
	if( nRowCol <= nAddIndex )
	{
		// Insert Point보다 이전인 경우.
		;
	}
	else if(nRowCol > nAddIndex )
	{
		// Insert Point와 갯수보다 이후인 경우.
		nRowCol	+= (short)nAddCount;
	}
}


// Remove Columns Or Rows
void CCellCtrl::Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol /*= TRUE*/)
{
	int nIndex, nCount;
	BOOL bRemove = FALSE;

	if( m_pComboArray )
	{
		CELLCOMBO*	pCombo = NULL;
		nCount = m_pComboArray->GetSize();
		
		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pCombo = (CELLCOMBO*) m_pComboArray->GetAt(nIndex);
				
			if ( pCombo )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pCombo->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pCombo->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pCombo;
					m_pComboArray->RemoveAt(nIndex);
				}
			}
		}
	}

	if( m_pComboExArray )
	{
		CELLCOMBOEX*	pComboEx = NULL;
		nCount = m_pComboExArray->GetSize();
		
		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pComboEx = (CELLCOMBOEX*) m_pComboExArray->GetAt(nIndex);
				
			if ( pComboEx )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pComboEx->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pComboEx->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pComboEx;
					m_pComboExArray->RemoveAt(nIndex);
				}
			}
		}
	}

	if( m_pCheckArray )
	{
		CELLCHECK*	pCheck = NULL;
		nCount = m_pCheckArray->GetSize();
		
		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pCheck = (CELLCHECK*) m_pCheckArray->GetAt(nIndex);
			
			if ( pCheck )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pCheck->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pCheck->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pCheck;
					m_pCheckArray->RemoveAt(nIndex);
				}
			}
		}
	}

	if( m_pSpinArray )
	{
		CELLSPIN*	pSpin = NULL;
		nCount = m_pSpinArray->GetSize();

		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pSpin = (CELLSPIN*) m_pSpinArray->GetAt(nIndex);
			
			if ( pSpin )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pSpin->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pSpin->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pSpin;
					m_pSpinArray->RemoveAt(nIndex);
				}
			}
		}
	}

	if( m_pPushBtnArray )
	{
		CELLPUSHBTN*	pPushBtn = NULL;
		nCount = m_pPushBtnArray->GetSize();

		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pPushBtn = (CELLPUSHBTN*) m_pPushBtnArray->GetAt(nIndex);
			
			if ( pPushBtn )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pPushBtn->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pPushBtn->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pPushBtn;
					m_pPushBtnArray->RemoveAt(nIndex);
				}
			}
		}
	}

	if( m_pBMPBtnArray )
	{
		CELLBMPBTN*	pBMPBtn = NULL;
		nCount = m_pBMPBtnArray->GetSize();

		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pBMPBtn = (CELLBMPBTN*) m_pBMPBtnArray->GetAt(nIndex);
			
			if ( pBMPBtn )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pBMPBtn->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pBMPBtn->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pBMPBtn;
					m_pBMPBtnArray->RemoveAt(nIndex);
				}
			}
		}
	}
	
	if( m_pCodeCtrlArray )
	{
		CELLCODECTRL*	pCodeCtrl = NULL;
		nCount = m_pCodeCtrlArray->GetSize();

		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pCodeCtrl = (CELLCODECTRL*) m_pCodeCtrlArray->GetAt(nIndex);
			
			if ( pCodeCtrl )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pCodeCtrl->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pCodeCtrl->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pCodeCtrl;
					m_pCodeCtrlArray->RemoveAt(nIndex);
				}
			}
		}
	}

	if( m_pPWEditArray )
	{
		CELLEDIT*	pPWEdit = NULL;
		nCount = m_pPWEditArray->GetSize();

		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pPWEdit = (CELLEDIT*) m_pPWEditArray->GetAt(nIndex);
			
			if ( pPWEdit )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pPWEdit->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pPWEdit->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pPWEdit;
					m_pPWEditArray->RemoveAt(nIndex);
				}
			}
		}
	}

	if( m_pEditArray )
	{
		CELLEDIT*	pEdit = NULL;
		nCount = m_pEditArray->GetSize();

		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pEdit = (CELLEDIT*) m_pEditArray->GetAt(nIndex);
			
			if ( pEdit )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pEdit->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pEdit->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pEdit;
					m_pEditArray->RemoveAt(nIndex);
				}
			}
		}
	}

	if( m_pPrgrsArray )
	{
		CELLPRGRS*	pPrgrs = NULL;
		nCount = m_pPrgrsArray->GetSize();

		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pPrgrs = (CELLPRGRS*) m_pPrgrsArray->GetAt(nIndex);
			
			if ( pPrgrs )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pPrgrs->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pPrgrs->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pPrgrs;
					m_pPrgrsArray->RemoveAt(nIndex);
				}
			}
		}
	}
#ifdef GRADIENT_USE 
	if( m_pGradientArray )							// Gradient
	{
		CELLGRADIENTS*	pGradients = NULL;
		nCount = m_pGradientArray->GetSize();

		for( nIndex = nCount-1; nIndex >= 0; nIndex-- )
		{
			pGradients = (CELLGRADIENTS*) m_pGradientArray->GetAt(nIndex);
			
			if ( pGradients )
			{
				// Column Remove
				if( bRemoveCol )
				{
					bRemove = RemoveRowColIndex(pGradients->nCol, nDelIndex, nDelCount);
				}
				else
				{
					bRemove = RemoveRowColIndex(pGradients->nRow, nDelIndex, nDelCount);
				}

				if( bRemove )
				{
					delete pGradients;
					m_pGradientArray->RemoveAt(nIndex);
				}
			}
		}
	}
#endif
}

BOOL CCellCtrl::RemoveRowColIndex(short& nRowCol, DWORD nDelIndex, DWORD nDelCount)
{
	BOOL bRemove = FALSE;
	if( nRowCol <= nDelIndex )
	{
		// Delete Point보다 이전인 경우.
		;
	}
	else if(nRowCol > nDelIndex + nDelCount )
	{
		// Delete Point와 갯수보다 이후인 경우.
		nRowCol	-= (short)nDelCount;
	}
	else if( nRowCol == nDelIndex + 1 )
	{
		// 주최를 지우는 경우.
		bRemove = TRUE;
	}
	else if( nRowCol > nDelIndex && nRowCol <= nDelIndex + nDelCount )
	{
		// Cover 주최를 지우는 경우.
		bRemove = TRUE;
	}

	return bRemove;
}

// Copy Columns Or Rows
void CCellCtrl::Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol /*= TRUE*/)
{
	short nGap, nIndex, nCount;
	nGap  = (short)(nDestFrom - nSrcFrom);

	if( m_pComboArray )
	{
		CELLCOMBO*	pCombo = NULL;
		CELLCOMBO*	pNewCombo = NULL;
		nCount = m_pComboArray->GetSize();
		
		for( nIndex = 0; nIndex < nCount; nIndex++ )
		{
			pCombo = (CELLCOMBO*) m_pComboArray->GetAt(nIndex);
				
			if ( pCombo )
			{
				if( bCopyCol )
				{
					if( pCombo->nCol >= nSrcFrom && pCombo->nCol <= nSrcTo )
					{
						pNewCombo = new CELLCOMBO;
						ASSERT(pNewCombo);
						
						pNewCombo->nRow			= pCombo->nRow;
						pNewCombo->nCol			= pCombo->nCol + nGap;
						pNewCombo->strItemList	= pCombo->strItemList;
						pNewCombo->lDummy		= pCombo->lDummy;
						
						m_pComboArray->Add( (void*) pNewCombo);
					}
				}
				else
				{
					if( pCombo->nRow >= nSrcFrom && pCombo->nRow <= nSrcTo )
					{
						pNewCombo = new CELLCOMBO;
						ASSERT(pNewCombo);

						pNewCombo->nRow			= pCombo->nRow + nGap;
						pNewCombo->nCol			= pCombo->nCol;
						pNewCombo->strItemList	= pCombo->strItemList;
						pNewCombo->lDummy		= pCombo->lDummy;

						m_pComboArray->Add( (void*) pNewCombo);
					}
				}
			}
		}
	}

	if( m_pComboExArray )
	{
		CELLCOMBOEX*	pComboEx = NULL;
		CELLCOMBOEX*	pNewComboEx = NULL;
		nCount = m_pComboExArray->GetSize();
		
		for( nIndex = 0; nIndex < nCount; nIndex++ )
		{
			pComboEx = (CELLCOMBOEX*) m_pComboExArray->GetAt(nIndex);
				
			if ( pComboEx )
			{
				if( bCopyCol )
				{
					if( pComboEx->nCol >= nSrcFrom && pComboEx->nCol <= nSrcTo )
					{
						pNewComboEx = new CELLCOMBOEX;
						ASSERT(pNewComboEx);
						
						pNewComboEx->nRow			= pComboEx->nRow;
						pNewComboEx->nCol			= pComboEx->nCol + nGap;

						pNewComboEx->nMaxLen		= pComboEx->nMaxLen;	// 데이터출력값 
						pNewComboEx->byValueShow	= pComboEx->byValueShow;// 00=00 데이터  
						pNewComboEx->strChoiceList  = pComboEx->strChoiceList;
						pNewComboEx->strFileName	= pComboEx->strFileName;// Ini 파일명 
						pNewComboEx->strSectionName	= pComboEx->strSectionName;	// [Ini]섹션명 
						pNewComboEx->lDummy			= pComboEx->lDummy;

						m_pComboExArray->Add( (void*) pNewComboEx);
					}
				}
				else
				{
					if( pComboEx->nRow >= nSrcFrom && pComboEx->nRow <= nSrcTo )
					{
						pNewComboEx = new CELLCOMBOEX;
						ASSERT(pNewComboEx);

						pNewComboEx->nRow			= pComboEx->nRow + nGap;
						pNewComboEx->nCol			= pComboEx->nCol;

						pNewComboEx->nMaxLen		= pComboEx->nMaxLen;	// 데이터출력값 
						pNewComboEx->byValueShow	= pComboEx->byValueShow;// 00=00 데이터  
						pNewComboEx->strChoiceList  = pComboEx->strChoiceList;
						pNewComboEx->strFileName	= pComboEx->strFileName;// Ini 파일명 
						pNewComboEx->strSectionName	= pComboEx->strSectionName;	// [Ini]섹션명 
						pNewComboEx->lDummy			= pComboEx->lDummy;

						m_pComboExArray->Add( (void*) pNewComboEx );
					}
				}
			}
		}
	}

	if( m_pCheckArray )
	{
		CELLCHECK*	pCheck = NULL;
		CELLCHECK*	pNewCheck = NULL;
		nCount = m_pCheckArray->GetSize();
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCheck = (CELLCHECK*) m_pCheckArray->GetAt(nIndex);
			
			if ( pCheck )
			{
				if( bCopyCol )
				{
					if( pCheck->nCol >= nSrcFrom && pCheck->nCol <= nSrcTo )
					{
						pNewCheck = new CELLCHECK;
						ASSERT(pNewCheck);

						pNewCheck->nRow			= pCheck->nRow;
						pNewCheck->nCol			= pCheck->nCol + nGap;
						pNewCheck->nCheckVal	= pCheck->nCheckVal;
						pNewCheck->nUnCheckVal	= pCheck->nUnCheckVal;
						pNewCheck->strText		= pCheck->strText;
						pNewCheck->lDummy		= pCheck->lDummy;

						m_pCheckArray->Add( (void*) pNewCheck);
					}
				}
				else
				{
					if( pCheck->nRow >= nSrcFrom && pCheck->nRow <= nSrcTo )
					{
						pNewCheck = new CELLCHECK;
						ASSERT(pNewCheck);

						pNewCheck->nRow			= pCheck->nRow + nGap;
						pNewCheck->nCol			= pCheck->nCol;
						pNewCheck->nCheckVal	= pCheck->nCheckVal;
						pNewCheck->nUnCheckVal	= pCheck->nUnCheckVal;
						pNewCheck->strText		= pCheck->strText;
						pNewCheck->lDummy		= pCheck->lDummy;

						m_pCheckArray->Add( (void*) pNewCheck);
					}
				}
			}
		}
	}

	if( m_pSpinArray )
	{
		CELLSPIN*	pSpin = NULL;
		CELLSPIN*	pNewSpin = NULL;
		nCount = m_pSpinArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pSpin = (CELLSPIN*) m_pSpinArray->GetAt(nIndex);
			
			if ( pSpin )
			{
				if( bCopyCol )
				{
					if( pSpin->nCol >= nSrcFrom && pSpin->nCol <= nSrcTo )
					{
						pNewSpin = new CELLSPIN;
						ASSERT(pNewSpin);

						memcpy(pNewSpin, pSpin, sizeof(CELLSPIN));
						pNewSpin->nCol		+= nGap;

						m_pSpinArray->Add( (void*) pNewSpin);
					}
				}
				else
				{
					if( pSpin->nRow >= nSrcFrom && pSpin->nRow <= nSrcTo )
					{
						pNewSpin = new CELLSPIN;
						ASSERT(pNewSpin);

						memcpy(pNewSpin, pSpin, sizeof(CELLSPIN));
						pNewSpin->nRow		+= nGap;

						m_pSpinArray->Add( (void*) pNewSpin);
					}
				}
			}

		}
	}

	if( m_pPushBtnArray )
	{
		CELLPUSHBTN*	pPushBtn = NULL;
		CELLPUSHBTN*	pNewPushBtn = NULL;
		nCount = m_pPushBtnArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPushBtn = (CELLPUSHBTN*) m_pPushBtnArray->GetAt(nIndex);
			
			if ( pPushBtn )
			{
				if( bCopyCol )
				{
					if( pPushBtn->nCol >= nSrcFrom && pPushBtn->nCol <= nSrcTo )
					{
						pNewPushBtn = new CELLPUSHBTN;
						ASSERT(pNewPushBtn);

						pNewPushBtn->nRow		= pPushBtn->nRow;
						pNewPushBtn->nCol		= pPushBtn->nCol + nGap;
						pNewPushBtn->nBtCrIndex	= pPushBtn->nBtCrIndex;
						pNewPushBtn->strText	= pPushBtn->strText;
						pNewPushBtn->lDummy		= pPushBtn->lDummy;

						m_pPushBtnArray->Add( (void*) pNewPushBtn);
					}
				}
				else
				{
					if( pPushBtn->nRow >= nSrcFrom && pPushBtn->nRow <= nSrcTo )
					{
						pNewPushBtn = new CELLPUSHBTN;
						ASSERT(pNewPushBtn);

						pNewPushBtn->nRow		= pPushBtn->nRow + nGap;
						pNewPushBtn->nCol		= pPushBtn->nCol;
						pNewPushBtn->nBtCrIndex	= pPushBtn->nBtCrIndex;
						pNewPushBtn->strText	= pPushBtn->strText;
						pNewPushBtn->lDummy		= pPushBtn->lDummy;

						m_pPushBtnArray->Add( (void*) pNewPushBtn);
					}
				}
			}
		}
	}

	if( m_pBMPBtnArray )
	{
		CELLBMPBTN*	pBMPBtn = NULL;
		CELLBMPBTN*	pNewBMPBtn = NULL;
		nCount = m_pBMPBtnArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pBMPBtn = (CELLBMPBTN*) m_pBMPBtnArray->GetAt(nIndex);
			
			if ( pBMPBtn )
			{
				if( bCopyCol )
				{
					if( pBMPBtn->nCol >= nSrcFrom && pBMPBtn->nCol <= nSrcTo )
					{
						pNewBMPBtn = new CELLBMPBTN;
						ASSERT(pNewBMPBtn);

						pNewBMPBtn->nRow			= pBMPBtn->nRow;
						pNewBMPBtn->nCol			= pBMPBtn->nCol + nGap;
						pNewBMPBtn->byStretch		= pBMPBtn->byStretch;
						pNewBMPBtn->strTitle		= pBMPBtn->strTitle;
						pNewBMPBtn->strNormalName	= pBMPBtn->strNormalName;
						pNewBMPBtn->strDownName		= pBMPBtn->strDownName;
						pNewBMPBtn->lDummy			= pBMPBtn->lDummy;

						m_pBMPBtnArray->Add( (void*) pNewBMPBtn);
					}
				}
				else
				{
					if( pBMPBtn->nRow >= nSrcFrom && pBMPBtn->nRow <= nSrcTo )
					{
						pNewBMPBtn = new CELLBMPBTN;
						ASSERT(pNewBMPBtn);

						pNewBMPBtn->nRow			= pBMPBtn->nRow + nGap;
						pNewBMPBtn->nCol			= pBMPBtn->nCol;
						pNewBMPBtn->byStretch		= pBMPBtn->byStretch;
						pNewBMPBtn->strTitle		= pBMPBtn->strTitle;
						pNewBMPBtn->strNormalName	= pBMPBtn->strNormalName;
						pNewBMPBtn->strDownName		= pBMPBtn->strDownName;
						pNewBMPBtn->lDummy			= pBMPBtn->lDummy;
						
						m_pBMPBtnArray->Add( (void*) pNewBMPBtn);
					}
				}
			}

		}
	}
	
	if( m_pCodeCtrlArray )
	{
		CELLCODECTRL*	pCodeCtrl = NULL;
		CELLCODECTRL*	pNewCodeCtrl = NULL;
		nCount = m_pCodeCtrlArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCodeCtrl = (CELLCODECTRL*) m_pCodeCtrlArray->GetAt(nIndex);
			
			if ( pCodeCtrl )
			{
				if( bCopyCol )
				{
					if( pCodeCtrl->nCol >= nSrcFrom && pCodeCtrl->nCol <= nSrcTo )
					{
						pNewCodeCtrl = new CELLCODECTRL;
						ASSERT(pNewCodeCtrl);

						memcpy(pNewCodeCtrl, pCodeCtrl, sizeof(CELLCODECTRL));
						pNewCodeCtrl->nCol		+= nGap;

						m_pCodeCtrlArray->Add( (void*) pNewCodeCtrl);
					}
				}
				else
				{
					if( pCodeCtrl->nRow >= nSrcFrom && pCodeCtrl->nRow <= nSrcTo )
					{
						pNewCodeCtrl = new CELLCODECTRL;
						ASSERT(pNewCodeCtrl);

						memcpy(pNewCodeCtrl, pCodeCtrl, sizeof(CELLCODECTRL));
						pNewCodeCtrl->nRow		+= nGap;

						m_pCodeCtrlArray->Add( (void*) pNewCodeCtrl);
					}
				}
			}
		}
	}

	if( m_pPWEditArray )
	{
		CELLEDIT*	pPWEdit = NULL;
		CELLEDIT*	pNewPWEdit = NULL;
		nCount = m_pPWEditArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPWEdit = (CELLEDIT*) m_pPWEditArray->GetAt(nIndex);
			
			if ( pPWEdit )
			{
				if( bCopyCol )
				{
					if( pPWEdit->nCol >= nSrcFrom && pPWEdit->nCol <= nSrcTo )
					{
						pNewPWEdit = new CELLEDIT;
						ASSERT(pNewPWEdit);

						memcpy(pNewPWEdit, pPWEdit, sizeof(CELLEDIT));
						pNewPWEdit->nCol		+= nGap;

						m_pPWEditArray->Add( (void*) pNewPWEdit);
					}
				}
				else
				{
					if( pPWEdit->nRow >= nSrcFrom && pPWEdit->nRow <= nSrcTo )
					{
						pNewPWEdit = new CELLEDIT;
						ASSERT(pNewPWEdit);

						memcpy(pNewPWEdit, pPWEdit, sizeof(CELLEDIT));
						pNewPWEdit->nRow		+= nGap;

						m_pPWEditArray->Add( (void*) pNewPWEdit);
					}
				}
			}
		}
	}

	if( m_pEditArray )
	{
		CELLEDIT*	pEdit = NULL;
		CELLEDIT*	pNewEdit = NULL;
		nCount = m_pEditArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pEdit = (CELLEDIT*) m_pEditArray->GetAt(nIndex);
			
			if ( pEdit )
			{
				if( bCopyCol )
				{
					if( pEdit->nCol >= nSrcFrom && pEdit->nCol <= nSrcTo )
					{
						pNewEdit = new CELLEDIT;
						ASSERT(pNewEdit);

						memcpy(pNewEdit, pEdit, sizeof(CELLEDIT));
						pNewEdit->nCol		+= nGap;

						m_pEditArray->Add( (void*) pNewEdit);
					}
				}
				else
				{
					if( pEdit->nRow >= nSrcFrom && pEdit->nRow <= nSrcTo )
					{
						pNewEdit = new CELLEDIT;
						ASSERT(pNewEdit);

						memcpy(pNewEdit, pEdit, sizeof(CELLEDIT));
						pNewEdit->nRow		+= nGap;

						m_pEditArray->Add( (void*) pNewEdit);
					}
				}
			}
		}
	}

	if( m_pPrgrsArray )
	{
		CELLPRGRS*	pPrgrs = NULL;
		CELLPRGRS*	pNewPrgrs = NULL;
		nCount = m_pPrgrsArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pPrgrs = (CELLPRGRS*) m_pPrgrsArray->GetAt(nIndex);
			
			if ( pPrgrs )
			{
				if( bCopyCol )
				{
					if( pPrgrs->nCol >= nSrcFrom && pPrgrs->nCol <= nSrcTo )
					{
						pNewPrgrs = new CELLPRGRS;
						ASSERT(pNewPrgrs);

						memcpy(pNewPrgrs, pPrgrs, sizeof(CELLPRGRS));
						pNewPrgrs->nCol	+= nGap;

						m_pPrgrsArray->Add( (void*) pNewPrgrs);
					}
				}
				else
				{
					if( pPrgrs->nRow >= nSrcFrom && pPrgrs->nRow <= nSrcTo )
					{
						pNewPrgrs = new CELLPRGRS;
						ASSERT(pNewPrgrs);

						memcpy(pNewPrgrs, pPrgrs, sizeof(CELLPRGRS));
						pNewPrgrs->nRow		+= nGap;

						m_pPrgrsArray->Add( (void*) pNewPrgrs);
					}
				}
			}
		}
	}
#ifdef GRADIENT_USE 	
	if( m_pGradientArray )						// Gradient
	{
		CELLGRADIENTS*	pGradients = NULL;
		CELLGRADIENTS*	pNewGradients = NULL;
		nCount = m_pGradientArray->GetSize();

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pGradients = (CELLGRADIENTS*) m_pGradientArray->GetAt(nIndex);
			
			if ( pGradients )
			{
				if( bCopyCol )
				{
					if( pGradients->nCol >= nSrcFrom && pGradients->nCol <= nSrcTo )
					{
						pNewGradients = new CELLGRADIENTS;
						ASSERT(pNewGradients);

						memcpy(pNewGradients, pGradients, sizeof(CELLGRADIENTS));
						pNewGradients->nCol	+= nGap;

						m_pGradientArray->Add( (void*) pNewGradients );
					}
				}
				else
				{
					if( pGradients->nRow >= nSrcFrom && pGradients->nRow <= nSrcTo )
					{
						pNewGradients = new CELLGRADIENTS;
						ASSERT(pNewGradients);

						memcpy(pNewGradients, pGradients, sizeof(CELLGRADIENTS));
						pNewGradients->nRow		+= nGap;

						m_pGradientArray->Add( (void*) pNewGradients );
					}
				}
			}
		}
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CTTipArray, CObject, 1)
CTTipArray::CTTipArray() 
{ 
	m_dwVersion		=	DEF_VERSION;
};

CTTipArray::~CTTipArray() 
{
};

void CTTipArray::Clear()
{

	TTINFO* pTip = NULL;
	int nCount, nIndex;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pTip = (TTINFO*) GetAt(nIndex);
		
		if( pTip )
		{
			if( pTip->nFmtCnt > 0 )
			{
				if( pTip->pItemArray )
				{
					pTip->pItemArray->RemoveAll();
					delete pTip->pItemArray;
					pTip->pItemArray = NULL;
				}
			}

#ifdef _DEBUG
			if( pTip->lDummy )
			{
				ASSERT(FALSE);
			}
#endif
			
			delete pTip;
		}
	}

	RemoveAll();
}

const CTTipArray& CTTipArray::operator=(const CTTipArray& other)
{
	if ( &other == this)
		return *this;

	Clear();

	m_dwVersion		= other.m_dwVersion;

	//Copy(other);

	int nIndex, nCount;
	int nSubIndex, nSubCount;
	TTINFO* pTip = NULL;
	TTINFO* pOtherTip = NULL;
	nCount = other.GetSize();
	
	SetSize(nCount);
	
	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pTip = new TTINFO;

		if ( pTip )
		{
			pOtherTip = (TTINFO*) other.GetAt(nIndex);

			pTip->nFmtCnt = pOtherTip->nFmtCnt;
			pTip->strText = pOtherTip->strText;
			pTip->pItemArray = NULL;

			if(pOtherTip->pItemArray)
			{
				pTip->pItemArray  = new CStringArray;
				nSubCount = pOtherTip->pItemArray->GetSize();
				pTip->pItemArray->SetSize(nSubCount);
				
				for ( nSubIndex = 0 ; nSubIndex < nSubCount; nSubIndex ++ )
				{
					pTip->pItemArray->SetAt(nSubIndex, pOtherTip->pItemArray->GetAt(nSubIndex) );
				}
			}
			
			pTip->lDummy = pOtherTip->lDummy;
			SetAt(nIndex, (void*) pTip);
		}
	}


	return *this;

}

void CTTipArray::Serialize(CArchive &ar)
{
	int nCount, nIndex, nFmtIndex;
	TTINFO* pTip = NULL;

	if( ar.IsStoring() )							// Write
	{
		nCount = GetSize();

		ar << nCount;
		ar << m_dwVersion;

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pTip =  (TTINFO*) GetAt(nIndex);

			if( pTip )
			{
				ar << pTip->nFmtCnt;

				if( pTip->nFmtCnt > 0 )
				{
					if( pTip->pItemArray )
					for ( nFmtIndex = 0 ; nFmtIndex < pTip->nFmtCnt; nFmtIndex ++ )
					{
						ar << pTip->pItemArray->GetAt( nFmtIndex );
					}
				}

				ar << pTip->strText;
				ar << pTip->lDummy;

#ifdef _DEBUG
				if(pTip->lDummy)
				{
					ASSERT(FALSE);
				}
#endif
			}
			
		}

	}
	else
	{
		Clear();
		
		CString strItem;
		DWORD dwReadVersion;

		ar >> nCount;
		ar >> dwReadVersion;

		SetSize(nCount);

		if( nCount > 0)
		{
			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pTip = new TTINFO;
				pTip->pItemArray = NULL;

				if( pTip )
				{
					ar >> pTip->nFmtCnt;

					if( pTip->nFmtCnt > 0 )
					{
						pTip->pItemArray  = new CStringArray;
						
						if( pTip->pItemArray )
						{
							pTip->pItemArray->SetSize(pTip->nFmtCnt);
							
							for ( nFmtIndex = 0 ; nFmtIndex < pTip->nFmtCnt; nFmtIndex ++ )
							{
								ar >> strItem;
								pTip->pItemArray->SetAt( nFmtIndex, strItem );
							}
						}
					}

					ar >> pTip->strText;
					ar >> pTip->lDummy;

#ifdef _DEBUG
					if(pTip->lDummy)
					{
						ASSERT(FALSE);
					}
#endif
				}
				
				SetAt(nIndex, (void*) pTip);
			}
		}
	}
}


BOOL CTTipArray::SetPropList(LPSTR lpBuf )
{
	if(!lpBuf || *lpBuf == 0x00)
		return FALSE;

	// Format
	// FmtCnt<US>Item1<FS>Item2<FS>...Item5<FS>FormatText<US>Dummy<US>......FmtCnt<US>Item1<FS>Item2<FS>...Item5<FS>FormatText<US>Dummy<US>
	LPSTR		lpStr;
	TTINFO* pTip = NULL;
	int nIndex, nLen;
	BYTE* lpData = NULL;

	Clear();

	while ( *lpBuf != 0 )
	{
		pTip = new TTINFO;
		pTip->pItemArray = NULL;
		pTip->strText = _T("");
	
		if ( pTip )
		{
			pTip->nFmtCnt = (short)strtol(lpBuf, &lpBuf, 10);
			
			if (lpBuf && *lpBuf)
				lpBuf++;

			for( nIndex = 0; nIndex < pTip->nFmtCnt; nIndex++ )
			{
				lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_FS );
				
				if ( lpStr != NULL )
				{
					if( pTip->pItemArray == NULL )
						pTip->pItemArray = new CStringArray;

					if(pTip->pItemArray)
					{
						nLen = lpStr - lpBuf;
						//ASSERT(nLen > 0 );

						if( nLen > 0 )
						{
							lpData = new BYTE[nLen+1];
							memset ( lpData, 0x00, nLen+1);
							memcpy ( lpData, &lpBuf[0],  nLen );
							pTip->pItemArray->Add( (LPCTSTR)(char*)lpData );
							
							if ( lpData )
							{
								delete[] lpData;
								lpData = NULL;
							}
						}
						else
						{
							pTip->pItemArray->Add( _T("Error!") );
						}

						lpBuf = lpStr;

						if (lpBuf && *lpBuf)
							lpBuf++;
					}
				}
			}

			lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );
			
			if ( lpStr != NULL )
			{
				nLen = lpStr - lpBuf;
				//ASSERT(nLen > 0 );
				if( nLen > 0 )
				{
					lpData = new BYTE[nLen+1];
					memset ( lpData, 0x0, nLen+1);
					memcpy ( lpData, &lpBuf[0],  nLen );
					pTip->strText = (LPCTSTR)(char*)lpData;
					
					if ( lpData )
						delete[] lpData;
				}

				lpBuf = lpStr;
			}

			if (lpBuf && *lpBuf)
				lpBuf++;

			pTip->lDummy = strtol(lpBuf, &lpBuf, 10);
			
			if (lpBuf && *lpBuf)
				lpBuf++;

			Add((void*) pTip);
		}

	}

	return TRUE;

}

BOOL CTTipArray::GetPropList(CString& strList)
{
	strList = _T("");
	
	// Format
	// FmtCnt<US>Item1<FS>Item2<FS>...Item5<FS>FormatText<US>Dummy<US>......FmtCnt<US>Item1<FS>Item2<FS>...Item5<FS>FormatText<US>Dummy<US>
	CString strTemp, strItemText;
	int nCount, nIndex, nFmtIndex;
	TTINFO* pTip = NULL;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pTip =  (TTINFO*) GetAt(nIndex);

		if( pTip )
		{
			if( pTip->nFmtCnt > 0 )
			{
				strItemText = _T("");

				if( pTip->pItemArray )
				for ( nFmtIndex = 0 ; nFmtIndex < pTip->nFmtCnt; nFmtIndex ++ )
				{
					strItemText += pTip->pItemArray->GetAt( nFmtIndex );
					strItemText += _G_TCH_FS;
				}

				strTemp.Format("%d%c%s%s%c%d%c", pTip->nFmtCnt, _G_TCH_US, strItemText, pTip->strText, _G_TCH_US, pTip->lDummy, _G_TCH_US );
			}
			else
			{
				strTemp.Format("%d%c%s%c%d%c", pTip->nFmtCnt, _G_TCH_US, pTip->strText, _G_TCH_US, pTip->lDummy, _G_TCH_US );
			}

			strList += strTemp;	
			
		}
	}
	
	return (!strList.IsEmpty());
}

LPTTINFO CTTipArray::GetTTipInfo(int nTipIndex, BOOL bNewAlloc /*= FALSE*/)
{
	int nCount;
	TTINFO* pTip = NULL;
	nCount = GetSize();

	if(nTipIndex >= nCount)
		return NULL;

	pTip =  (TTINFO*) GetAt(nTipIndex);

	if( pTip )
	{
		if( !bNewAlloc )
		{
			return pTip;
		}
		else
		{
			TTINFO* pNewTip = new TTINFO;
			ASSERT(pNewTip);
			
			pNewTip->nFmtCnt	= pTip->nFmtCnt;
			
			if( pTip->pItemArray )
			{
				pNewTip->pItemArray	= new CStringArray;
				pNewTip->pItemArray->Copy(*pTip->pItemArray);
			}
			else
			{
				pNewTip->pItemArray	= NULL;
			}
			
			pNewTip->strText	= pTip->strText;
			pNewTip->lDummy		= pTip->lDummy;
			return pNewTip;

		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CReferArray, CObject, 1)
CReferArray::CReferArray() 
{ 
	m_dwVersion		=	DEF_VERSION;
};

CReferArray::~CReferArray() 
{
};

void CReferArray::Clear()
{
	REFERINFO* pRefer = NULL;
	int nCount, nIndex, nItemIndex;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRefer = (REFERINFO*) GetAt(nIndex);
		
		if( pRefer )
		{
			if( pRefer->nReferCnt > 0 && pRefer->plpszItem )
			{
				for( nItemIndex = 0; nItemIndex < pRefer->nReferCnt; nItemIndex++)
				{
					if( pRefer->plpszItem[nItemIndex] )
						delete pRefer->plpszItem[nItemIndex];
				}
				
				delete[] pRefer->plpszItem;
			}
			
			delete pRefer;
		}
	}

	RemoveAll();
}

const CReferArray& CReferArray::operator=(const CReferArray& other)
{
	if ( &other == this)
		return *this;

	Clear();

	m_dwVersion		= other.m_dwVersion;

	//Copy(other);
	int nIndex, nCount;
	int nItemIndex;
	REFERINFO* pRefer = NULL;
	REFERINFO* pOtherRefer = NULL;
	nCount = other.GetSize();
	
	SetSize(nCount);
	
	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRefer = new REFERINFO;

		if ( pRefer )
		{
			pOtherRefer = (REFERINFO*) other.GetAt(nIndex);
			memcpy(pRefer, pOtherRefer, LEN_REFERINFO);
			
			if(pOtherRefer->plpszItem)
			{
				pRefer->plpszItem = new LPSTR[pRefer->nReferCnt];

				for( nItemIndex = 0; nItemIndex < pRefer->nReferCnt; nItemIndex++)
				{
					pRefer->plpszItem[nItemIndex] = new char[ITEM_LEN+1];

					if( pRefer->plpszItem[nItemIndex] )
					{
						strcpy( pRefer->plpszItem[nItemIndex], pOtherRefer->plpszItem[nItemIndex]);
					}
				}
			}
			
			SetAt(nIndex, (void*) pRefer);
		}
	}

	return *this;

}

void CReferArray::Serialize(CArchive &ar)
{

	int nCount, nIndex, nItemIndex;
	REFERINFO* pRefer = NULL;

	if( ar.IsStoring() )							// Write
	{
		nCount = GetSize();

		ar << nCount;
		ar << m_dwVersion;

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pRefer =  (REFERINFO*) GetAt(nIndex);

			if( pRefer )
			{
				ar << pRefer->nBasisKeyIdx;
				ar << (BYTE) lstrlen(pRefer->szBasisItem);
				ar.WriteString((LPCTSTR) pRefer->szBasisItem);
				ar << pRefer->nReferCnt;
			
				if( pRefer->nReferCnt > 0 && pRefer->plpszItem)
				{
					for ( nItemIndex = 0 ; nItemIndex < pRefer->nReferCnt; nItemIndex ++ )
					{
						if( pRefer->plpszItem[nItemIndex] )
						{
							ar << (BYTE) lstrlen( pRefer->plpszItem[nItemIndex] );
							ar.WriteString( (LPCTSTR) pRefer->plpszItem[nItemIndex] );
						}
						else
						{
							LPCTSTR lpErr = _T("Error");
							ar << (BYTE) lstrlen( lpErr );
							ar.WriteString( (LPCTSTR) lpErr );
						}
					}
				}

				ar << pRefer->lDummy;
			}
			
		}

	}
	else
	{
		Clear();
		
//		CString strItem;
		DWORD dwReadVersion;

		ar >> nCount;
		ar >> dwReadVersion;

		if( nCount > 0)
		{
			SetSize(nCount);
			BYTE byReadLen;
			
			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pRefer = new REFERINFO;
				pRefer->plpszItem = NULL;
			
				if( pRefer )
				{
					ar >> pRefer->nBasisKeyIdx;
					ar >> byReadLen;
					ar.ReadString( pRefer->szBasisItem, byReadLen);
					ar >> pRefer->nReferCnt;

					if( pRefer->nReferCnt > 0 )
					{
						pRefer->plpszItem = new LPSTR[pRefer->nReferCnt];

						for(nItemIndex = 0; nItemIndex < pRefer->nReferCnt; nItemIndex++)
						{
							pRefer->plpszItem[nItemIndex] = new char[ITEM_LEN+1];

							if( pRefer->plpszItem[nItemIndex] )
							{
								ar >> byReadLen;
								ar.ReadString( pRefer->plpszItem[nItemIndex], byReadLen);
							}
							else
							{
								ASSERT(FALSE);
							}
						}
						
					}

					ar >> pRefer->lDummy;
				}
				
				SetAt(nIndex, (void*) pRefer);
			}
		}
	}

}


BOOL CReferArray::SetPropList(LPSTR lpBuf )
{
	if(!lpBuf || *lpBuf == 0x00)
		return FALSE;

	// Format
	// BKeyIndex<US>BItem<US>ReferCnt<US>Item1<FS>Item2<FS>...Item5<FS>Dummy<US>...BKeyIndex<US>BItem<US>ReferCnt<US>Item1<FS>Item2<FS>...Item5<FS>Dummy<US>
	LPSTR		lpStr;
	REFERINFO* pRefer = NULL;
	int nIndex, nLen;
	BYTE* lpData = NULL;

	Clear();

	while ( *lpBuf != 0 )
	{
		pRefer = new REFERINFO;
		pRefer->plpszItem = NULL;
	
		if ( pRefer )
		{
			pRefer->nBasisKeyIdx = (short)strtol(lpBuf, &lpBuf, 10);
			
			if (lpBuf && *lpBuf)
				lpBuf++;

			lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );
			nLen = lpStr - lpBuf;

			if( nLen > 0 )
			{
				lpData = new BYTE[nLen+1];
				memset ( lpData, 0x00, nLen+1);
				memcpy ( lpData, &lpBuf[0],  nLen );
				strcpy(pRefer->szBasisItem, (LPCTSTR)(char*)lpData );
				
				if ( lpData )
				{
					delete[] lpData;
					lpData = NULL;
				}
			}
			
			lpBuf = lpStr;

			if (lpBuf && *lpBuf)
				lpBuf++;

			pRefer->nReferCnt = (short)strtol(lpBuf, &lpBuf, 10);

			if (lpBuf && *lpBuf)
				lpBuf++;

			if( pRefer->nReferCnt > 0 )
			{
				pRefer->plpszItem = new LPSTR[pRefer->nReferCnt];
				
				for( nIndex = 0; nIndex < pRefer->nReferCnt; nIndex++ )
				{
					lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_FS );
					
					if ( lpStr != NULL )
					{
						pRefer->plpszItem[nIndex] = new char[ITEM_LEN+1];

						if( pRefer->plpszItem[nIndex] )
						{
							nLen = lpStr - lpBuf;
							//ASSERT(nLen > 0 );

							if( nLen > 0 )
							{
								lpData = new BYTE[nLen+1];
								memset ( lpData, 0x00, nLen+1);
								memcpy ( lpData, &lpBuf[0],  nLen );
								strcpy(pRefer->plpszItem[nIndex], (LPCTSTR)(char*)lpData);
								
								if ( lpData )
								{
									delete[] lpData;
									lpData = NULL;
								}
							}
							else
							{
								*pRefer->plpszItem[nIndex] = 0x00;
							}

							lpBuf = lpStr;

							if (lpBuf && *lpBuf)
								lpBuf++;
						}
					}
				}			
			}

			pRefer->lDummy = strtol(lpBuf, &lpBuf, 10);

			if (lpBuf && *lpBuf)
				lpBuf++;

			Add((void*) pRefer);
		}

	}
	
	return TRUE;
}

BOOL CReferArray::GetPropList(CString& strList)
{

	strList = _T("");
	
	// Format
	// BKeyIndex<US>BItem<US>ReferCnt<US>Item1<FS>Item2<FS>...Item5<FS>Dummy<US>...BKeyIndex<US>BItem<US>ReferCnt<US>Item1<FS>Item2<FS>...Item5<FS>Dummy<US>
	CString strTemp, strItemText;
	int nCount, nIndex, nReferIndex;
	REFERINFO* pRefer = NULL;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRefer =  (REFERINFO*) GetAt(nIndex);

		if( pRefer )
		{
			if( pRefer->nReferCnt > 0 )
			{
				strItemText = _T("");

				if( pRefer->plpszItem )
				for ( nReferIndex = 0 ; nReferIndex < pRefer->nReferCnt; nReferIndex++ )
				{
					strItemText += (LPCTSTR) pRefer->plpszItem[nReferIndex];
					strItemText += _G_TCH_FS;
				}

				strTemp.Format("%d%c%s%c%d%c%s%d%c",	pRefer->nBasisKeyIdx,	_G_TCH_US, 
														pRefer->szBasisItem,	_G_TCH_US, 
														pRefer->nReferCnt,		_G_TCH_US,
														strItemText,
														pRefer->lDummy,			_G_TCH_US);
			}
			else
			{
				strTemp.Format("%d%c%s%c%d%c%d%c",		pRefer->nBasisKeyIdx,	_G_TCH_US, 
														pRefer->szBasisItem,	_G_TCH_US, 
														pRefer->nReferCnt,		_G_TCH_US,
														pRefer->lDummy,			_G_TCH_US);
														
			}

			strList += strTemp;	
			
		}
	}
	
	return (!strList.IsEmpty());
}

LPREFERINFO CReferArray::GetReferInfoFromOwner(short nKeyIndex, LPCTSTR lpszItem)
{
	LPREFERINFO pRefer = NULL;
	int nCount, nIndex;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRefer = (LPREFERINFO) GetAt(nIndex);
		
		if( pRefer && (pRefer->nBasisKeyIdx ==  nKeyIndex) )
		{
			if( pRefer->szBasisItem && lpszItem && strcmp(pRefer->szBasisItem, lpszItem) == 0 )
			{
				return pRefer;
			}
		}
	}

	return NULL;
}

LPREFERINFO CReferArray::GetReferInfoFromSlave(short nKeyIndex, LPCTSTR lpszItem)
{
	LPREFERINFO pRefer = NULL;
	int nCount, nIndex, nItemIndex;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pRefer = (LPREFERINFO) GetAt(nIndex);
		
		if( pRefer && (pRefer->nBasisKeyIdx ==  nKeyIndex) )
		{
			if( pRefer->nReferCnt > 0 && pRefer->plpszItem && lpszItem)
			{
				for ( nItemIndex = 0 ; nItemIndex < pRefer->nReferCnt; nItemIndex++ )
				{
					if(pRefer->plpszItem[nItemIndex])
					{
						if(strcmp(pRefer->plpszItem[nItemIndex], lpszItem) == 0)
							return pRefer;
					}
				}
			}
		}
	}

	return NULL;
}
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CCellTextArray, CObject, 1)
CCellTextArray::CCellTextArray() 
{ 
	m_dwVersion		=	DEF_VERSION;
};

CCellTextArray::~CCellTextArray() 
{
};

void CCellTextArray::Clear()
{

	CELLTEXT* pCellText = NULL;
	int nCount, nIndex;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText = (CELLTEXT*) GetAt(nIndex);
		
		if( pCellText )
		{
			delete pCellText;
		}
	}

	RemoveAll();
}

const CCellTextArray& CCellTextArray::operator=(const CCellTextArray& other)
{
	if ( &other == this)
		return *this;

	Clear();

	m_dwVersion		= other.m_dwVersion;

	//Copy(other);
	int nIndex, nCount;
	CELLTEXT* pCellText = NULL;
	CELLTEXT* pOtherCellText = NULL;
	nCount = other.GetSize();
	
	SetSize(nCount);
	
	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText = new CELLTEXT;

		if ( pCellText )
		{
			pOtherCellText = (CELLTEXT*) other.GetAt(nIndex);

			pCellText->nRow		=	pOtherCellText->nRow;
			pCellText->nCol		=	pOtherCellText->nCol;
			pCellText->strText	=	pOtherCellText->strText;

			
			SetAt(nIndex, (void*) pCellText);
		}
	}


	return *this;

}

void CCellTextArray::Serialize(CArchive &ar)
{
	int nCount, nIndex;
	CELLTEXT* pCellText = NULL;

	if( ar.IsStoring() )							// Write
	{
		nCount = GetSize();

		ar << nCount;
		ar << m_dwVersion;

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			pCellText = (CELLTEXT*) GetAt(nIndex);

			if( pCellText )
			{
				ar << pCellText->nRow;
				ar << pCellText->nCol;
				ar << pCellText->strText;
			}
			
		}
	}
	else
	{
		Clear();
		DWORD dwReadVersion;
		ar >> nCount;
		ar >> dwReadVersion;

		SetSize(nCount);

		if( nCount > 0)
		{
			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pCellText = new CELLTEXT;
			
				if( pCellText )
				{
					ar >> pCellText->nRow;
					ar >> pCellText->nCol;
					ar >> pCellText->strText;
				
				}
			
				SetAt(nIndex, (void*) pCellText);
			}
		}
	}
}


BOOL CCellTextArray::SetPropList(LPSTR lpBuf )
{
	if(!lpBuf || *lpBuf == 0x00)
		return FALSE;

	// Format
	// Row<US>Col<US>Text<US>......Row<US>Col<US>Text<US>
	LPSTR lpStr;
	CELLTEXT* pCellText = NULL;
	int  nLen;
	BYTE* lpData = NULL;

	Clear();

	while ( *lpBuf != 0 )
	{
		pCellText = new CELLTEXT;
		pCellText->strText = _T("");
	
		if ( pCellText )
		{
			pCellText->nRow = (short)strtol(lpBuf, &lpBuf, 10);
			
			if (lpBuf && *lpBuf)
				lpBuf++;

			pCellText->nCol = (short)strtol(lpBuf, &lpBuf, 10);
			
			if (lpBuf && *lpBuf)
				lpBuf++;


			lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );
			
			if ( lpStr != NULL )
			{
				nLen = lpStr - lpBuf;
				//ASSERT(nLen > 0 );

				if( nLen > 0 )
				{
					lpData = new BYTE[nLen+1];
					memset ( lpData, 0x0, nLen+1);
					memcpy ( lpData, &lpBuf[0],  nLen );
					pCellText->strText = (LPCTSTR)(char*)lpData;
					
					if ( lpData )
						delete[] lpData;
				}

				lpBuf = lpStr;
			}

			if (lpBuf && *lpBuf)
				lpBuf++;

			Add((void*) pCellText);
		}

	}

	return TRUE;

}

BOOL CCellTextArray::GetPropList(CString& strList)
{
	strList = _T("");
	
	// Format
	// Row<US>Col<US>Text<US>......Row<US>Col<US>Text<US>
	
	//CString strTemp;
	char szTemp[256];
	int nCount, nIndex;
	CELLTEXT* pCellText = NULL;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText =  (CELLTEXT*) GetAt(nIndex);

		if( pCellText )
		{
			/*
			strTemp.Format("%d%c%d%c%s%c", 
								pCellText->nRow, US,
								pCellText->nCol, US,
								pCellText->strText, US );
	
			strList += strTemp;	
			*/

			wsprintf(szTemp, _T("%d%c%d%c%s%c"), 
							pCellText->nRow, _G_TCH_US,
							pCellText->nCol, _G_TCH_US,
							pCellText->strText, _G_TCH_US );
			
			strList += szTemp;	
		}
	}
	
	return (!strList.IsEmpty());
}

//*******************************************************************/
/*! Function Name : SetRowColText
/*! Function      : 
/*! Param         : short	nRow
/*!					short	nCol
/*!					CString strText
/*!					BOOL bOverWrite
/*! Return        : int 
/*! Create        : 김창하 , 2006/06/20
/*! Comment       : 
//******************************************************************/
BOOL CCellTextArray::SetRowColText(short nRow, short nCol, CString strText, BOOL bOverWrite )
{
	int nCount, nIndex;
	CELLTEXT* pCellText = NULL;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText =  (CELLTEXT*) GetAt(nIndex);

		if( pCellText )
		{
			if(pCellText->nRow == nRow && pCellText->nCol == nCol)
			{
				if ( bOverWrite )
					pCellText->strText = strText;

				return TRUE;
			}
		}
	}

	pCellText = new CELLTEXT;
	pCellText->nRow    = nRow;
	pCellText->nCol    = nCol;
	pCellText->strText = strText;

	Add( (void*)pCellText );

	return TRUE;
}

// [다중아이템] 서비스.레코드명의 위치를 취득하는 함수
int CCellTextArray::GetRowColMultiRecordPos( CString  strItemInfo )
{
	int nCount, nIndex,nFind;
	CELLTEXT* pCellText = NULL;
	nCount = GetSize();
	CString strData,strItem;
	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText =  (CELLTEXT*) GetAt(nIndex);
		if( pCellText )
		{
			// [서비스명.레코드명`아이템명] 
			strData = pCellText->strText;
			nFind = strData.Find( _T('`') );
			if ( nFind > 0 )
			{
				strItem = strData.Left(nFind) ;
				if ( strItemInfo.Compare ( strItem ) == 0 )
					return (int)pCellText->nRow; 
			}
		}
	}
	return 0;
}

// [다중아이템] 해당위치의 아이템명을 취득한다.
BOOL CCellTextArray::GetRowColItemInfo( DWORD nRow, DWORD nCol, CString& strItem )
{
	int nCount, nIndex,nFind;
	CELLTEXT* pCellText = NULL;
	nCount = GetSize();
	CString strData;
	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText =  (CELLTEXT*) GetAt(nIndex);

		if( pCellText )
		{
			if(pCellText->nRow == (short)nRow && pCellText->nCol == (short)nCol)
			{
				// [서비스명.레코드명`아이템명] 
				strData = pCellText->strText;
				nFind = strData.Find( _T('`') );
				if ( nFind > 0 )
				{
					strItem = strData.Mid(nFind+1);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

// [다중아이템] 해당위치의 아이템명이 존재하는가를 비교한다.
BOOL CCellTextArray::GetRowColItemCmp( DWORD nRow,  DWORD nCol, CString  strItem )
{
	int nCount, nIndex;
	CELLTEXT* pCellText = NULL;
	nCount = GetSize();
	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText =  (CELLTEXT*) GetAt(nIndex);

		if( pCellText )
		{
			if(pCellText->nRow == (short)nRow && pCellText->nCol == (short)nCol)
			{
				if ( strItem.Compare( pCellText->strText) == 0 )
					return TRUE;
			}
		}
	}
	return FALSE;	
}

BOOL CCellTextArray::GetRowColText(short nRow, short nCol, CString& strText)
{
	strText = _T("");
	int nCount, nIndex;
	CELLTEXT* pCellText = NULL;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText =  (CELLTEXT*) GetAt(nIndex);

		if( pCellText )
		{
			if(pCellText->nRow == nRow && pCellText->nCol == nCol)
			{
				strText = pCellText->strText;
				break;
			}
		}
	}
	
	return (!strText.IsEmpty());
}

LPCTSTR	CCellTextArray::GetKeyCode(short nKeyIndex)
{
	int nCount, nIndex;
	CELLTEXT* pCellText = NULL;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText =  (CELLTEXT*) GetAt(nIndex);

		if( pCellText )
		{
			//pCellText->nRow가 KeyIndex임 .
			if(pCellText->nRow == nKeyIndex )
			{
				return (LPCTSTR) pCellText->strText;
			}
		}
	}

	return NULL;
}

BOOL CCellTextArray::SetKeyCode(short nKeyIndex, LPCTSTR lpszKeyCode)
{
	if(!lpszKeyCode || *lpszKeyCode == 0x00)
		return FALSE;

	int nCount, nIndex;
	CELLTEXT* pCellText = NULL;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText =  (CELLTEXT*) GetAt(nIndex);

		if( pCellText )
		{
			//pCellText->nRow가 KeyIndex임. 
			if(pCellText->nRow == nKeyIndex )
			{
				pCellText->strText = lpszKeyCode;
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

short CCellTextArray::GetKeyIndex(LPCTSTR lpszCode)
{
	if(!lpszCode || *lpszCode == 0x00)
	{
		ASSERT(FALSE);
		return 0;
	}

	int nCount, nIndex;
	CELLTEXT* pCellText = NULL;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText =  (CELLTEXT*) GetAt(nIndex);

		if( pCellText )
		{
			//pCellText->nRow가 KeyIndex임 .
			if(strcmp(pCellText->strText, lpszCode) == 0 )
			{
				return pCellText->nRow;
			}
		}
	}

	return 0;
}

void CCellTextArray::Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol /*= TRUE*/, DXArrType arrType /*= ATFixKey*/)
{
	// Formula Array인 경우는 Move안함.
	if(arrType == ATFormula)
		return;

	int nIndex, nCount;
	BOOL bToRight = (nFrom < nDest);

	CELLTEXT* pCellText = NULL;
	nCount = GetSize();

/*
		if(nCount)
		{
			TRACE("Old  Text Arr:");
			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pCellText = (CELLTEXT*) GetAt(nIndex);
				
				if( pCellText )
					TRACE("C[%d],N[%s]... ", pCellText->nRow, pCellText->strText);
			}

		}
*/
	
	for( nIndex = 0; nIndex < nCount; nIndex++ )
	{
		pCellText = (CELLTEXT*) GetAt(nIndex);

		// nRow만을 KeyIndex로 사용하는 경우 이므로 Move가 필요없다.
		// COGLDoc::UpdateFixedKeyCode 참고.
		if( arrType == ATFixKey && pCellText->nCol == -1)
			return;
					
		if ( pCellText )
		{
			if( bMoveCol )
			{
				MoveRowColIndex(pCellText->nCol, nFrom, nDest, bToRight);
			}
			else
			{
				MoveRowColIndex(pCellText->nRow, nFrom, nDest, bToRight);
			}
		}
	}

/*
		if(nCount)
		{
			TRACE("\nMove Text Arr:");
			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				pCellText = (CELLTEXT*) GetAt(nIndex);
				
				if( pCellText )
					TRACE("C[%d],N[%s]... ", pCellText->nCol, pCellText->strText);
			}
			TRACE("\n");
		}
*/

}

void CCellTextArray::MoveRowColIndex(short& nRowCol, DWORD nFrom, DWORD nDest, BOOL bToRight)
{
	DWORD nCnt = 1;

	if(bToRight)
	{
		if(nRowCol == nFrom)
			nRowCol = (short)nDest;
		else if(nRowCol > nFrom && nRowCol <= nDest)
			nRowCol -= (short)nCnt;
	}
	else
	{
		if(nRowCol == nFrom)
			nRowCol = (short)nDest;
		else if(nRowCol >= nDest && nRowCol < nFrom)
			nRowCol += (short)nCnt;

		/*
		if(nRowCol == nDest)
			nRowCol = nFrom;
		else if(nRowCol > nDest && nRowCol <= nFrom)
			nRowCol -= nCnt;
		*/
	}

}

// Insert Columns Or Rows
void CCellTextArray::Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol /*= TRUE*/, DXArrType arrType /*= ATFixKey*/)
{
	// Formula Array인 경우는 Insert안함.
	if(arrType == ATFormula)
		return;
	
	CELLTEXT* pCellText = NULL;
	int nCount = GetSize();
	
	for ( int nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		pCellText = (CELLTEXT*) GetAt(nIndex);
		
		if ( pCellText == NULL )
			continue;
			
		// nRow만을 KeyIndex로 사용하는 경우 이므로 Insert가 필요없다.
		// COGLDoc::UpdateFixedKeyCode 참고.
		if( arrType == ATFixKey && pCellText->nCol == -1)
			return;

		// Column Insert
		if( bInsertCol )
		{
			InsertRowColIndex(pCellText->nCol, nAddIndex, nAddCount);
		}
		else
		{
			InsertRowColIndex(pCellText->nRow, nAddIndex, nAddCount);
		}
	}
}

void CCellTextArray::InsertRowColIndex(short& nRowCol, DWORD nAddIndex, DWORD nAddCount)
{
	if( nRowCol <= nAddIndex )
	{
		// Insert Point보다 이전인 경우.
		;
	}
	else if(nRowCol > nAddIndex )
	{
		// Insert Point와 갯수보다 이후인 경우.
		nRowCol	+= (short)nAddCount;
	}
}

// Remove Columns Or Rows
void CCellTextArray::Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol /*= TRUE*/, DXArrType arrType /*= ATFixKey*/)
{
	// Formula Array인 경우는 Remove안함.
	if(arrType == ATFormula)
		return;
	
	CELLTEXT* pCellText = NULL;
	int nCount = GetSize();
	BOOL bRemove = FALSE;
	
	for ( int nIndex = nCount-1; nIndex >= 0; nIndex -- )
	{
		pCellText = (CELLTEXT*) GetAt(nIndex);
		
		if ( pCellText == NULL )
			continue;
			
		// nRow만을 KeyIndex로 사용하는 경우 이므로 Remove가 필요없다.
		// COGLDoc::UpdateFixedKeyCode 참고.
		if( arrType == ATFixKey && pCellText->nCol == -1)
			return;

		// Remove Insert
		if( bRemoveCol )
		{
			bRemove = RemoveRowColIndex(pCellText->nCol, nDelIndex, nDelCount);
		}
		else
		{
			bRemove = RemoveRowColIndex(pCellText->nRow, nDelIndex, nDelCount);
		}

		if( bRemove )
		{
			delete pCellText;
			RemoveAt(nIndex);
		}
	}
}

BOOL CCellTextArray::RemoveRowColIndex(short& nRowCol, DWORD nDelIndex, DWORD nDelCount)
{
	BOOL bRemove = FALSE;
	if( nRowCol <= nDelIndex )
	{
		// Delete Point보다 이전인 경우.
		;
	}
	else if(nRowCol > nDelIndex + nDelCount )
	{
		// Delete Point와 갯수보다 이후인 경우.
		nRowCol	-= (short)nDelCount;
	}
	else if( nRowCol == nDelIndex + 1 )
	{
		// 주최를 지우는 경우.
		bRemove = TRUE;
	}
	else if( nRowCol > nDelIndex && nRowCol <= nDelIndex + nDelCount )
	{
		// Cover 주최를 지우는 경우.
		bRemove = TRUE;
	}

	return bRemove;
}

// Copy Columns Or Rows
void CCellTextArray::Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol /*= TRUE*/, DXArrType arrType /*= ATFixKey*/)
{
	// Formula Array인 경우는 Copy안함.
	if(arrType == ATFormula)
		return;

	int nGap, nIndex, nCount;
	nGap  = nDestFrom-nSrcFrom;

	CELLTEXT* pCellText = NULL;
	CELLTEXT* pNewCellText = NULL;
	nCount = GetSize();

	for( nIndex = 0; nIndex < nCount; nIndex++ )
	{
		pCellText = (CELLTEXT*) GetAt(nIndex);

		// nRow만을 KeyIndex로 사용하는 경우 이므로 Copy못한다.
		// COGLDoc::UpdateFixedKeyCode 참고.
		if( arrType == ATFixKey && pCellText->nCol == -1)
			return;
					
		if ( pCellText )
		{
			if( bCopyCol )
			{
				if( pCellText->nCol >= nSrcFrom && pCellText->nCol <= nSrcTo )
				{
					pNewCellText = new CELLTEXT;
					ASSERT(pNewCellText);

					pNewCellText->nRow		=	pCellText->nRow;
					pNewCellText->nCol		=	pCellText->nCol + nGap;
					pNewCellText->strText	=	pCellText->strText;

					Add( (void*) pNewCellText);
				}
			}
			else
			{
				if( pCellText->nRow >= nSrcFrom && pCellText->nRow <= nSrcTo )
				{
					pNewCellText = new CELLTEXT;
					ASSERT(pNewCellText);

					pNewCellText->nRow		=	pCellText->nRow + nGap;
					pNewCellText->nCol		=	pCellText->nCol;
					pNewCellText->strText	=	pCellText->strText;

					Add( (void*) pNewCellText);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CPosFlagArray, CDWordArray, 1)
CPosFlagArray::CPosFlagArray() 
{ 
	m_dwVersion		=	DEF_VERSION;
};

CPosFlagArray::~CPosFlagArray() 
{
};

void CPosFlagArray::Clear()
{
	RemoveAll();
}

const CPosFlagArray& CPosFlagArray::operator=(const CPosFlagArray& other)
{
	if ( &other == this)
		return *this;

	Clear();

	m_dwVersion		= other.m_dwVersion;

	//Copy(other);

	int nIndex, nCount;
	DWORD dwPos;
	nCount = other.GetSize();
	
	SetSize(nCount);
	
	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		dwPos = other.GetAt(nIndex);

		SetAt(nIndex, dwPos);
	}

	return *this;

}

void CPosFlagArray::Serialize(CArchive &ar)
{
	int nCount, nIndex;
	DWORD dwPos;

	if( ar.IsStoring() )							// Write
	{
		nCount = GetSize();

		ar << nCount;
		ar << m_dwVersion;

		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			dwPos =  GetAt(nIndex);
			ar << dwPos;
		}

	}
	else
	{
		Clear();
		
		DWORD dwReadVersion;

		ar >> nCount;
		ar >> dwReadVersion;

		SetSize(nCount);

		if( nCount > 0)
		{
			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				ar >> dwPos;
				
				SetAt(nIndex, dwPos);
			}
		}
	}
}


BOOL CPosFlagArray::SetPropList(LPSTR lpBuf )
{
	if(!lpBuf || *lpBuf == 0x00)
		return FALSE;

	// Format
	// CellPos<US>CellPos<US>......CellPos<US>
	DWORD dwPos;
	Clear();
		
	while ( *lpBuf != 0 )
	{
		dwPos = strtol(lpBuf, &lpBuf, 10);
		Add(dwPos);

		if (lpBuf && *lpBuf)
			lpBuf++;

	}

	return TRUE;
}

BOOL CPosFlagArray::GetPropList(CString& strList)
{
	strList = _T("");
		
	// Format
	// CellPos<US>CellPos<US>......CellPos<US>
	//CString strTemp;
	char szTemp[20];
	DWORD dwPos;
	int nIndex, nCount;
	nCount = GetSize();

	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		dwPos = GetAt(nIndex);
		
		/*
		strTemp.Format("%d%c", dwPos, US );
		strList += strTemp;
		*/

		wsprintf(szTemp, _T("%d%c"), dwPos, _G_TCH_US );
		strList += szTemp;

	}

	return (!strList.IsEmpty());
}

/////////////////////////////////////////////////////////////////////////////
// --> [Edit]  김창하 2006/06/16
//CMapRecordInfo
// Version 3 m_pmapRecordInfo삭제:
// <-- [Edit]  김창하 2006/06/16
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CMapRecordInfo, CObject, 1)
CMapRecordInfo::CMapRecordInfo() 
{ 
	m_dwVersion		=	DEF_VERSION;
};

CMapRecordInfo::~CMapRecordInfo() 
{

};

void CMapRecordInfo::Clear()
{
	RemoveAll();
}

const CMapRecordInfo& CMapRecordInfo::operator=(const CMapRecordInfo& other)
{
	if ( &other == this)
		return *this;

	return *this;
}

void CMapRecordInfo::Serialize(CArchive &ar)
{
	int nCount;
	CString strKey;
	long    dwDataLen;
	POSITION pos;
	if( ar.IsStoring() )							// Write
	{
		nCount = GetCount();
		ar << nCount;
		ar << m_dwVersion;
		if( nCount <= 0 )
		{
			return;
		}

		pos = GetStartPosition();
		while ( pos )
		{
			GetNextAssoc( pos, strKey, (CObject*&) dwDataLen );
			ar << strKey;
			ar << dwDataLen;
		}
		//CMapStringToOb::Serialize( ar );
	}
	else
	{
		Clear();

		DWORD dwReadVersion;
		ar >> nCount;
		ar >> dwReadVersion;

		if( nCount > 0)
		{
			while ( nCount-- )
			{
				ar >> strKey;
				ar >> dwDataLen;
				SetAt( strKey, (CObject*)dwDataLen );
			}
			//CMapStringToOb::Serialize( ar );
		}
	}
}


BOOL CMapRecordInfo::SetPropList(LPSTR lpBuf )
{
	if(!lpBuf || *lpBuf == 0x00)
		return FALSE;

	// Format
	//RecCnt<FS>RecKey<US>DataLen<US>...RecKey<US>DataLen<US>

	Clear();
	
	int  nRecCnt,
		 nLen;

	long dwDataLen(0);
	CString szKey;
	LPSTR lpStr;
	BYTE* lpData = NULL;
	
	// Record Count
	nRecCnt = strtol( lpBuf, &lpBuf, 10);
	if (lpBuf && *lpBuf)		// <FX>
		lpBuf++;

	while ( *lpBuf != 0 )
	{
		// Record Key
		lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_US );
		nLen  = lpStr - lpBuf;
		if( nLen > 0 )
		{
			lpData = new BYTE[nLen+1];
			memset ( lpData, 0x00, nLen+1);
			memcpy ( lpData, &lpBuf[0],  nLen );
			szKey = lpData;
//			strcpy(  szKey, (LPCTSTR)(char*)lpData );
			if ( lpData )
			{
				delete[] lpData;
				lpData = NULL;
			}
		}

		lpBuf = lpStr;				// <US>
		if (lpBuf && *lpBuf)
			lpBuf++;

		// Data
		dwDataLen = strtol(lpBuf, &lpBuf, 10);
		if (lpBuf && *lpBuf)
			lpBuf++;

		SetAt((LPCTSTR) szKey, (CObject*)dwDataLen );
	}
	return TRUE;
}

BOOL CMapRecordInfo::GetPropList(CString& strList)
{
	strList = _T("");
	
	// Format
	//RecCnt<FS>RecKey<US>DataLen<US>...RecKey<US>DataLen<US>

	CString		strKey,
				strRecBuf;
	long		dwDataLen;
	int			nRecCnt;
	POSITION	pos;

	nRecCnt = GetCount();

	if( nRecCnt <= 0 )
		return FALSE;

	// Record Count
	strList.Format(_T("%d%c"), nRecCnt, _G_TCH_FS );	
	
	pos = GetStartPosition();
	while ( pos )
	{
		GetNextAssoc( pos, strKey, (CObject*&) dwDataLen );
		strRecBuf.Format(_T("%s%c%d%c"), strKey, _G_TCH_US, dwDataLen, _G_TCH_US );

		strList += strRecBuf;
	}
	return (!strList.IsEmpty());
}

///////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(COgBase, CObject, 1)

COgBase::COgBase()
{
	m_bSkip					=	FALSE;
	
	m_dwBaseVer				=	DEF_VERSION;
	m_CtrlSize				=	DEF_CTRL_SIZE;
	m_nRowCnt				=	DEF_ROW_COUNT;
	m_nColCnt				=	DEF_COLUMN_COUNT;
	m_nFrozenRowCnt			=	DEF_FROZEN_ROW_COUNT;
	m_nFrozenColCnt			=	DEF_FROZEN_COLUMN_COUNT;
	m_nHiddenRowCnt			=	DEF_HIDDEN_ROW_COUNT;
	m_nHiddenColCnt			=	DEF_HIDDEN_COLUMN_COUNT;
	m_nDefColWidth			=	DEF_COLUMN_WIDHT;
	m_nDefRowHeight			=	DEF_ROW_HEIGHT;
	m_nLineColorIndex		=	DEF_LINE_COLORINDEX;
	m_nBackGndColorIndex	=	DEF_BACKGND_COLORINDEX;
	m_nSelectionMode		=	(int)dxSelTable;
	m_nLineStyle			=	dxLSSolid;
	m_nScrollMode			=	(int)dxScrollOnlyV;
	m_nResizeHeader			=	(int)dxRszHdrNotUse;
	m_nItemFlag				=   (int)dxItemOut;
	m_nSpecialContent		=   dxSCNotUse;

	m_nLineMode				=	(int)dxLineOnlyV;
	m_bUseFormula			=	FALSE;
	m_wScriptEvent			=	0;
	m_wFireLinkInfo			=	0;
	m_nResize				=	(int)dxRszBoth;
	m_nBorderStyle			=	(int)dxCBdrBorder;
	m_nKeyIndexCnt			=	1;
	m_nDnDMode				=	dxDnDNone;
	m_nDragIndex			=	DEF_HEADER_ROW_COUNT;

	m_nPopupMenuMode		= 	PM_CTRL_DEF;
	m_nRealHighlight		=	dxRealHLCell;
	m_nSelectColorIndex		=	DEF_SELCR_INDEX;
	m_nBorderColorIndex		=	DEF_CTRLBORDER_COLORINDEX;
	
	m_strRPImportRecord		=	_T("");
	m_strRealImportRecord	=	_T("");
	m_strRQExportRecord		=	_T("");

//	m_strCommTrName			=	_T("");				// RQName
	m_strOptionQueryInfo	=	_T("");				// RQName
	m_strPrevCtrlName		=	_T("");				// Prev Button Control Name
	m_strNextCtrlName		=	_T("");				// Next Button Control Name
	m_nDataType				=	dxGDTTopInsert;

	m_byUseSelectColor		=	(BYTE) TRUE;
	m_bySpecialHoga			=	(BYTE) FALSE;
	m_byNeedMouseOverCheck	=	(BYTE) FALSE;
	m_byUseAmountGraph		=	(BYTE) FALSE;
	m_byUseForDll			=	(BYTE) FALSE;
	m_byMultiItemUse		=	(BYTE) FALSE;
	// Tail Use
	m_byTailUse				=   TG_NOTUSE;			// 합계행 
	m_byMultiTranUse		=	(BYTE) FALSE;
	m_byMultiMarketUse		=	(BYTE) FALSE;
	m_byNextDataHeaderCheck =	(BYTE) TRUE;
	m_byFixedRowCheck		=	(BYTE) FALSE;


	m_pRowSize				=	NULL;
	m_pColSize				=	NULL;
	m_pCovered				=	NULL;
	m_pCellCtrl				=	NULL;
	m_pTTip					=	NULL;
	m_pFormula				=	NULL;
	m_pFixKey				=	NULL;

	m_pNewRefer				=   NULL;
	m_pUserLinkArray		=	NULL;
	
	m_pBorderInfo			=	NULL;

	m_pRowSize	= new CItemSize;
	if(m_pRowSize)
		m_pRowSize->Initialize(m_nRowCnt, DEF_ROW_HEIGHT);

	m_pColSize = new CItemSize;
	if(m_pColSize)
		m_pColSize->Initialize(m_nColCnt, DEF_COLUMN_WIDHT);

	m_pCovered			= new CCellCovered;
	m_pCellCtrl			= new CCellCtrl;
	m_pTTip				= new CTTipArray;
	m_pFormula			= new CFormulaArray;
	m_pFixKey			= new CFixKeyArray;
	m_pNewRefer			= new CNewRefer;
	m_pUserLinkArray	= new CUserLinkTagArray;
	m_pBorderInfo		= new CLineBorder;

// --> [Edit]  김창하 2006/06/16
// Version 3 m_pmapRecordInfo삭제:
	m_pmapRecordInfo =	NULL;		// Record Total Len Info
	m_pmapRecordInfo    = new CMapRecordInfo;
// <-- [Edit]  김창하 2006/06/16

// --> [Edit]  김창하 2006/06/16
//	m_pRecordNameArray추가 
	m_pRecordNameArray = NULL;
	m_pRecordNameArray    = new CRecordNameArray;

	m_pInputMaskArray  = NULL;
	m_pInputMaskArray   = new CInputMaskArray;
// 대체문자 정보 	
	m_pReplaceTextArray = NULL;
	m_pReplaceTextArray   = new CRelpaceTextArray;

// --> [Edit]  김창하 2006/09/11
	// Caption Static text 
	m_pCaptionTextArray = NULL;
	m_pCaptionTextArray = new CCaptionTextArray;	// 캡션문자 문자 정보 	
// <-- [Edit]  김창하 2006/09/11

// <-- [Edit]  김창하 2006/06/16
};

COgBase::~COgBase()
{
	if(m_pRowSize)
	{
		m_pRowSize->Clear();
		delete m_pRowSize;
		m_pRowSize = NULL;
	}

	if(m_pColSize)
	{
		m_pColSize->Clear();
		delete m_pColSize;
		m_pColSize = NULL;
	}

	if(m_pCovered)
	{
		m_pCovered->Clear();
		delete m_pCovered;
		m_pCovered = NULL;
	}

	if(m_pCellCtrl)
	{
		m_pCellCtrl->Clear();
		delete m_pCellCtrl;
		m_pCellCtrl = NULL;
	}

	if(m_pTTip)
	{
		m_pTTip->Clear();
		delete m_pTTip;
		m_pTTip = NULL;
	}

	if(m_pFormula)
	{
		m_pFormula->Clear();
		delete m_pFormula;
		m_pFormula = NULL;
	}
// --> [Edit]  김창하 2006/06/16
// m_pRecordNameArray 추가 
	if ( m_pRecordNameArray )
	{
		m_pRecordNameArray->Clear();
		delete m_pRecordNameArray;
		m_pRecordNameArray = NULL;
	}

	if ( m_pInputMaskArray )
	{
		m_pInputMaskArray->Clear();
		delete m_pInputMaskArray;
		m_pInputMaskArray = NULL;
	}

// 대체문자 정보 	
	if ( m_pReplaceTextArray )
	{
		m_pReplaceTextArray->Clear();
		delete m_pReplaceTextArray;

		m_pReplaceTextArray = NULL;
	}
// <-- [Edit]  김창하 2006/06/16

// --> [Edit]  김창하 2006/09/11
	// Caption Static text 
	if ( m_pCaptionTextArray )
	{
		m_pCaptionTextArray->Clear();
		delete m_pCaptionTextArray;

		m_pCaptionTextArray = NULL;
	}
// <-- [Edit]  김창하 2006/09/11

	if(m_pFixKey)
	{
		m_pFixKey->Clear();
		delete m_pFixKey;
		m_pFixKey = NULL;
	}

	if(m_pNewRefer)
	{
		m_pNewRefer->Clear();
		delete m_pNewRefer;
		m_pNewRefer = NULL;
	}
	
	if(m_pUserLinkArray)
	{
		m_pUserLinkArray->Clear();
		delete m_pUserLinkArray;
		m_pUserLinkArray = NULL;
	}
// --> [Edit]  김창하 2006/06/16
// Version 3 m_pmapRecordInfo삭제:
	if ( m_pmapRecordInfo )
	{
		m_pmapRecordInfo->Clear();
		delete m_pmapRecordInfo;
		m_pmapRecordInfo = NULL;
	}
// <-- [Edit]  김창하 2006/06/16
	if ( m_pBorderInfo	)
	{
		m_pBorderInfo->Clear();
		delete m_pBorderInfo;
		m_pBorderInfo = NULL;
	}
};

#if FALSE
//*****************************************************************************
// 루    틴    명  :  GetRecordTotalLen
// 기          능  :  Record별 총 데이터 길이를 취득하는 기능. 
// 입          력  :  LPCTSTR lpszRecordName 레코드명.
// 출          력  :  길이 .
// 작    성    자  :  2005년7월2일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  실행모드에서 호출 . 
//*****************************************************************************
int COgBase::GetRecordTotalLen ( LPCTSTR lpszRecordName )
{
	ASSERT ( m_pmapRecordInfo );
	long dwDataLen(0);
	if( m_pmapRecordInfo && m_pmapRecordInfo->Lookup( lpszRecordName, (CObject*&)dwDataLen ) )
	{
		return dwDataLen;
	}
	return dwDataLen;
}
#endif
#if FALSE
//*****************************************************************************
// 루    틴    명  :  GetRecordTotalLen
// 기          능  :  Record별 총 데이터 길이를 설정하는 기능. 
// 입          력  :  LPCTSTR lpszRecordName		레코드명. 
//					  long    dwTotalLen			총길이 .
// 출          력  :  길이 .
// 작    성    자  :  2005년7월2일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  디자인 시점 .
//*****************************************************************************
int COgBase::SetRecordTotalLen ( LPCTSTR lpszRecordName, long dwTotalLen )
{
	ASSERT ( m_pmapRecordInfo );
	if ( m_pmapRecordInfo )
	{
		m_pmapRecordInfo->SetAt ( lpszRecordName, (CObject*)dwTotalLen );
		return m_pmapRecordInfo->GetCount();
	}

	return 0;
}
#endif
//*****************************************************************************
// 루    틴    명  :  GetMemNameFormatList
// 기          능  :  
// 입          력  :  없음.
// 출          력  :  없음.
// 작    성    자  :  2004년7월7일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
BOOL  COgBase::GetMemNameFormatList ( LPCTSTR lpImportName , CString& strMemNameList)
{

	if (lpImportName == NULL || *lpImportName == NULL )
		return FALSE;

	const char _WCH_SEP	=	0x0019;				// 컬럼정보 문자열의 구분자.

	LPCTSTR lpszTmpMemory = lpImportName;
	
	LPSTR lpszPeriod, lpszComma;
	char szMemBuf[MAX_PATH];
	char szRecBuf[MAX_PATH];
	int nMemLen;
	int nRecLen;
	CString strTemp;

	while (TRUE)
	{
		///// memeory와 record명 사이의 '.'와 memory와 memory사이의 ','를 찾는다.
	//	lpszPeriod = strchr(lpszTmpMemory, _TCH_PERIOD);
		lpszPeriod = (LPTSTR)_tcschr(lpszTmpMemory, COMM_SEPERATOR_SUB);
		lpszComma  = (LPTSTR)_tcschr(lpszTmpMemory, _TCH_COMMA);
		if (lpszPeriod == NULL || lpszPeriod + 1 == NULL)
		{
			return FALSE;
		}

		///// memory명과 찾을 memory명을 비교한다.
		nMemLen = lpszPeriod - lpszTmpMemory;
		memcpy(szMemBuf, lpszTmpMemory, nMemLen);
		szMemBuf[nMemLen] = 0x00;

		lpszPeriod++;
		///// 같은경우.
		if (lpszComma == NULL)
			nRecLen = strlen(lpszPeriod);
		else
			nRecLen = lpszComma - lpszPeriod;

		// Record Name 을 찾는다.
		memcpy( szRecBuf, lpszPeriod, nRecLen );
		szRecBuf[nRecLen] = 0x00;
		
		if( strMemNameList.Find(szMemBuf,0) == -1 )
		{
			strTemp.Format("%s%c", szMemBuf, _WCH_SEP );
			strMemNameList += strTemp;
		}

		if (lpszComma == NULL || (lpszComma + 1) == NULL)
		{
			return TRUE;
		}

		lpszTmpMemory = lpszComma + 1;
	}
	
	return FALSE;
	
}

//*****************************************************************************
// 루    틴    명  :  SetCellCoveredBlobDataChange
// 기          능  :  Covered프로퍼티 데이터를 변환하는 함수 .
// 입          력  :  CString  strPropertyData
// 출          력  :  BOOL
// 작    성    자  :  2003년9월22일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
BOOL  COgBase::SetCellCoveredBlobDataChange ( CString  strPropertyData )
{
	if ( strPropertyData.IsEmpty() )
		return FALSE;

	BYTE*	pvData = NULL;
	pvData = StringToBinary( strPropertyData );
	
	ASSERT( pvData != NULL );
    if( pvData != NULL )
	{
		DWORD	dwTotalLength;
		int		nTotalCount;
		int		nOffset = 0;

		m_pCovered->Clear ( );

		dwTotalLength = *(DWORD*)pvData;
		nOffset		+= sizeof(DWORD);

		nTotalCount = *(short*)(pvData + nOffset);
		nOffset += sizeof(short);
			
		m_pCovered->m_dwLength = dwTotalLength;
			
		m_pCovered->SetSize ( nTotalCount );

		for ( int nCount = 0 ; nCount < nTotalCount; nCount ++ )
		{
			CELLRANGE* pRange = new CELLRANGE;

			memcpy( pRange, pvData + nOffset, LEN_CELLRANGE );
			m_pCovered->SetAt( nCount, (void*)pRange );

			nOffset += LEN_CELLRANGE;
		}

		free ( pvData );
		return TRUE;
	}

	return FALSE;
}

//*****************************************************************************
// 루    틴    명  :  GetCellCoveredBlobDataFromDataInfo
// 기          능  :  
// 입          력  :  없음.
// 출          력  :  CString
// 작    성    자  :  2003년7월15일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
CString  COgBase::GetCellCoveredBlobDataFromDataInfo( )
{
	CString  strPropertyData;
	
	int nOffset			= 0;
	int nTotalnCount	= m_pCovered->GetSize();

	DWORD dwTotalLength = LEN_CELLRANGEINFO( nTotalnCount );

	BYTE* pvData = (BYTE*)malloc( dwTotalLength );
	if ( pvData != NULL )
	{
		memset( pvData, 0x0, dwTotalLength );

		*(DWORD*)pvData = dwTotalLength;
		nOffset += sizeof(DWORD);

		*(short*)(pvData + nOffset ) = nTotalnCount;
		nOffset += sizeof(short);

		CELLRANGE* pRange = NULL;
		
		for ( int nCount = 0 ; nCount < nTotalnCount; nCount ++ )
		{
			pRange = (CELLRANGE*)m_pCovered->GetAt( nCount );
			memcpy ( pvData + nOffset, (void*)pRange, LEN_CELLRANGE );
			nOffset += LEN_CELLRANGE;
		}
		strPropertyData = BinaryToString( pvData, dwTotalLength );
		free(pvData);
	}
	return strPropertyData;
}

//*****************************************************************************
// 루    틴    명  :  SetCellSizeDataBlobDataChange
// 기          능  :  CellSize프로퍼티 데이터를 변환하는 함수 .
// 입          력  :  CString  strPropertyData
// 출          력  :  없음.
// 작    성    자  :  2003년7월15일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
BOOL  COgBase::SetCellSizeDataBlobDataChange( CString  strPropertyData )
{
	if ( strPropertyData.IsEmpty() )
		return FALSE;

	BYTE*	pvData = NULL;
	pvData = StringToBinary( strPropertyData );
	
	ASSERT( pvData != NULL );
    if( pvData != NULL )
	{
		DWORD	dwTotalLength;
		short   nTotalCount;
	
		int		nOffset = 0;

		DWORD	dwRecLen = sizeof(ITEMSIZE);
		int     nRowCount = m_nRowCnt + 1;

		m_pRowSize->Clear();
		m_pColSize->Clear();

		dwTotalLength = *(DWORD*)pvData;
		nOffset += sizeof(DWORD);

		nTotalCount = *(short*)(pvData + nOffset);
		nOffset += sizeof(short);
			
		if ( m_pRowSize == NULL )
			m_pRowSize = new CItemSize;

		m_pRowSize->dwLength	= sizeof(DWORD)+sizeof(short) + (  nRowCount * dwRecLen );
			
		// Row 개수를 취득한다(RowCount)
		m_pRowSize->nCount		= nRowCount;

		m_pRowSize->pRec		= new ITEMSIZE*[nRowCount];
		for ( int nRow = 0 ; nRow < nRowCount; nRow ++ )
		{
			m_pRowSize->pRec[nRow] = new ITEMSIZE;
			memset ( m_pRowSize->pRec[nRow], 0x0, sizeof(ITEMSIZE));

			memcpy( m_pRowSize->pRec[nRow], pvData + nOffset, sizeof(ITEMSIZE) );
			nOffset += sizeof(ITEMSIZE);
		}
			
		int     nColCount = nTotalCount - nRowCount;
//		m_pColSize->SetResize ( nColCount, DEF_COLUMN_WIDHT);
		if ( m_pColSize == NULL )
			m_pColSize = new CItemSize;

		m_pColSize->dwLength		= sizeof(DWORD)+sizeof(short) + (  nColCount * dwRecLen );

		// Col 개수를 취득한다(전체 수 - RowCount )
		m_pColSize->nCount		= nColCount;

		m_pColSize->pRec		= new ITEMSIZE*[nColCount];
//		nOffset += nRowCount * dwRecLen;

		for ( int nCol = 0 ; nCol < nColCount; nCol ++ )
		{
			m_pColSize->pRec[nCol] = new ITEMSIZE;
			memset ( m_pColSize->pRec[nCol], 0x0, sizeof(ITEMSIZE));

			memcpy( m_pColSize->pRec[nCol], pvData + nOffset, sizeof(ITEMSIZE) );
			nOffset += sizeof(ITEMSIZE);
		}
		free ( pvData );
		return TRUE;
	}

	return FALSE;
}

//*****************************************************************************
// 루    틴    명  :  GetCellSizeBlobDataFromDataInfo
// 기          능  :  
// 입          력  :  없음.
// 출          력  :  CString
// 작    성    자  :  2003년7월15일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
CString  COgBase::GetCellSizeBlobDataFromDataInfo( )
{
	CString  strPropertyData;
	
	int nOffset = 0;
	short nCount	= m_pRowSize->nCount + m_pColSize->nCount;

	DWORD dwRecLen		= sizeof(ITEMSIZE);
	DWORD dwTotalLength = sizeof(DWORD)+sizeof(short) + (  nCount * dwRecLen );

	BYTE* pvData = (BYTE*)malloc( dwTotalLength );
	if ( pvData != NULL )
	{
		memset( pvData, 0x0, dwTotalLength );

		*(DWORD*)pvData = dwTotalLength;
		nOffset += sizeof(DWORD);

		*(short*)(pvData + nOffset ) = nCount;
		nOffset += sizeof(short);
			
		for ( int nRow = 0 ; nRow < m_pRowSize->nCount; nRow ++ )
		{
			memcpy ( pvData + nOffset, m_pRowSize->pRec[nRow], LEN_ITEMSIZE );
			nOffset += LEN_ITEMSIZE;
		}

		for ( int nCol = 0 ; nCol < m_pColSize->nCount; nCol ++ )
		{
			memcpy ( pvData + nOffset , m_pColSize->pRec[nCol], LEN_ITEMSIZE );
			nOffset += LEN_ITEMSIZE;
		}
		
		strPropertyData = BinaryToString( pvData, dwTotalLength );
		free(pvData);
	}
	return strPropertyData;
}

void COgBase::SerializeCommonApply(CArchive &ar)
{
    if(ar.IsStoring())							// Write
    {
		ar << m_dwBaseVer;						// Version

		ar << m_byUseSelectColor;
		ar << m_bySpecialHoga;
		ar << m_byMultiItemUse;
		ar << m_byTailUse;						// Tail Use
		ar << m_byMultiTranUse;
		ar << m_byMultiMarketUse;
		ar << m_byNextDataHeaderCheck;
		ar << m_byFixedRowCheck;
	//	ar << m_byUseForDll;
	}
	else
	{
		ar >> m_dwBaseVer;						// Version

		ar >> m_byUseSelectColor;
		ar >> m_bySpecialHoga;
		ar >> m_byMultiItemUse;
		ar >> m_byTailUse;						// Tail Use

		if ( LOWORD(m_dwBaseVer) >= 5 )			// Ver5
			ar >> m_byMultiTranUse;

		if ( LOWORD(m_dwBaseVer) >= 7 )			// Ver7
			ar >> m_byMultiMarketUse;

		if ( LOWORD(m_dwBaseVer) >= 8 )			// Ver8
			ar >> m_byNextDataHeaderCheck;

		if ( LOWORD(m_dwBaseVer) >= 9 )			// Ver9
			ar >> m_byFixedRowCheck;
	//	ar << m_byUseForDll;
	}
}

BOOL   COgBase::SerializeCommonPropertyWrite( CString  strPropertyData )
{
	if ( strPropertyData.IsEmpty() )
	{
		return FALSE;
	}

	BYTE*	pvData = NULL;
	pvData = StringToBinary ( strPropertyData );
	ASSERT( pvData != NULL );
    if( pvData != NULL )
	{
		DWORD	dwDataLen;
		dwDataLen = *(long*)pvData;
		
		CMemFile memFile;
		memFile.Attach ( (BYTE*)pvData+sizeof(DWORD), dwDataLen - sizeof(DWORD) );
		
		CArchive arMem(&memFile, CArchive::load );
		SerializeCommonApply ( arMem );

		free ( pvData );
		return TRUE;
	}
	return FALSE;
	
}

CString COgBase::SerializeCommonPropertyRead( )
{
	CString strProperty;

	ASSERT_VALID(this);

	CMemFile  memFile;
	CArchive arMem(&memFile, CArchive::store );
	SerializeCommonApply ( arMem );
	arMem.Flush();

	DWORD dwDataLen = (DWORD)memFile.GetLength();
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
		strProperty = BinaryToString ( pvData, dwTotLen );
		if ( pvData )
			delete[] pvData;
	}	
	return strProperty;
}

//*******************************************************************/
/*! Function Name : SerializeUserData
/*! Function      : 
/*! Param         : CArchive &ar, LPBYTE lpData, DWORD dwLen
/*! Return        : void 
/*! Create        : 김창하 , 2005/11/29
/*! Comment       : 
//******************************************************************/
void COgBase::SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen )
{
    CObject::Serialize(ar);

	ASSERT_VALID(this);

    if( !ar.IsStoring())							// READ
	{
		
	}
}

void COgBase::Serialize(CArchive &ar)
{
    CObject::Serialize(ar);

	ASSERT_VALID(this);

    if(ar.IsStoring())							// Write
    {
		ar << m_dwBaseVer;						// Version
		ar << m_CtrlSize;
		
		if(!m_bSkip)
		{
			ar << m_nRowCnt;
			ar << m_nColCnt;
			ar << m_nFrozenRowCnt;
			ar << m_nFrozenColCnt;
			ar << m_nHiddenRowCnt;
			ar << m_nHiddenColCnt;
			ar << m_nDefColWidth;
			ar << m_nDefRowHeight;
			ar << m_nLineColorIndex;
			ar << m_nBackGndColorIndex;
			ar << m_nSelectionMode;
			ar << m_nLineStyle;
			ar << m_nScrollMode;
			ar << m_nResizeHeader;
			ar << m_bUseFormula;
			ar << m_wScriptEvent;
			ar << m_wFireLinkInfo;
			ar << m_nResize;
			ar << m_nBorderStyle;
			ar << m_nKeyIndexCnt;
			ar << m_nItemFlag;
			ar << m_nSpecialContent;
			ar << m_nLineMode;
			ar << m_nDnDMode;
			ar << m_nDragIndex;
			ar << m_nPopupMenuMode;
			ar << m_nRealHighlight;
			ar << m_nSelectColorIndex;

			ar << m_byNeedMouseOverCheck;
			ar << m_byUseAmountGraph;

			ar << m_nBorderColorIndex;
			ar << m_strRPImportRecord;
			ar << m_strRealImportRecord;
			ar << m_strRQExportRecord;
			
//			ar << m_strCommTrName;
			ar << m_strOptionQueryInfo;

			ar << m_strPrevCtrlName;
			ar << m_strNextCtrlName;
			ar << m_nDataType;
		}
		ar << m_byUseSelectColor;
		ar << m_bySpecialHoga;
		ar << m_byMultiItemUse;
		ar << m_byTailUse;			// Tail Use
		ar << m_byMultiTranUse;
		ar << m_byMultiMarketUse;
		ar << m_byNextDataHeaderCheck;
		ar << m_byFixedRowCheck;
	//	ar << m_byUseForDll;


		if(m_pRowSize /*&& !m_bSkip*/ )
		{
			m_pRowSize->SetVersion(m_dwBaseVer);
			m_pRowSize->Serialize(ar);
		}

		if(m_pColSize /*&& !m_bSkip*/ )
		{
			m_pColSize->SetVersion(m_dwBaseVer);
			m_pColSize->Serialize(ar);
		}

		if(m_pCovered)
		{
			m_pCovered->SetVersion(m_dwBaseVer);
			m_pCovered->Serialize(ar);
			
		}
	
		if(m_pCellCtrl)
		{
			m_pCellCtrl->SetVersion(m_dwBaseVer);
			m_pCellCtrl->Serialize(ar);
		}

		if ( m_pBorderInfo )
		{
			m_pBorderInfo->SetVersion(m_dwBaseVer);
			m_pBorderInfo->Serialize(ar);
		}

		if(m_pTTip)
		{
			m_pTTip->SetVersion(m_dwBaseVer);
			m_pTTip->Serialize(ar);
		}

		if(!m_bSkip)
		{
			if(m_pFormula)
			{
				m_pFormula->SetVersion(m_dwBaseVer);
				m_pFormula->Serialize(ar);
			}
		}

		if(m_pFixKey)
		{
			m_pFixKey->SetVersion(m_dwBaseVer);
			m_pFixKey->Serialize(ar);
		}

		if(m_pNewRefer)
		{
			m_pNewRefer->SetVersion(m_dwBaseVer);
			m_pNewRefer->Serialize(ar);
		}
		
		if(m_pUserLinkArray)
		{
			m_pUserLinkArray->SetVersion(m_dwBaseVer);
			m_pUserLinkArray->Serialize(ar);
		}

// --> [Edit]  김창하 2006/06/16
// m_pInputMaskArray 추가 
		if ( m_pInputMaskArray )
		{
			m_pInputMaskArray->SetVersion(m_dwBaseVer);
			m_pInputMaskArray->Serialize(ar);
		}

		if ( m_pRecordNameArray )
		{
			m_pRecordNameArray->SetVersion(m_dwBaseVer);
			m_pRecordNameArray->Serialize(ar);
		}

		if ( m_pReplaceTextArray )
		{
			m_pReplaceTextArray->SetVersion(m_dwBaseVer);
			m_pReplaceTextArray->Serialize(ar);
		}

// --> [Edit]  김창하 2006/09/11
		// Caption Static text 
		if ( m_pCaptionTextArray )
		{
			m_pCaptionTextArray->SetVersion(m_dwBaseVer);
			m_pCaptionTextArray->Serialize(ar);
		}
// <-- [Edit]  김창하 2006/09/11

// <-- [Edit]  김창하 2006/06/16

// --> [Edit]  김창하 2006/06/16
// Version 3 m_pmapRecordInfo삭제:
#if FALSE
		if ( m_pmapRecordInfo )					// Record Total len
		{
			m_pmapRecordInfo->SetVersion(m_dwBaseVer);
			m_pmapRecordInfo->Serialize(ar);
		}
#endif
// <-- [Edit]  김창하 2006/06/16
	}
    else										// Read
    {
		// Check for version first
		ar >> m_dwBaseVer;
		ar >> m_CtrlSize;
		if(!m_bSkip)
		{
			ar >> m_nRowCnt;
			ar >> m_nColCnt;
			ar >> m_nFrozenRowCnt;
			ar >> m_nFrozenColCnt;
			ar >> m_nHiddenRowCnt;
			ar >> m_nHiddenColCnt;
			ar >> m_nDefColWidth;
			ar >> m_nDefRowHeight;
			ar >> m_nLineColorIndex;
			ar >> m_nBackGndColorIndex;
			ar >> m_nSelectionMode;
			ar >> m_nLineStyle;
			ar >> m_nScrollMode;
			ar >> m_nResizeHeader;
			ar >> m_bUseFormula;
			ar >> m_wScriptEvent;
			ar >> m_wFireLinkInfo;
			ar >> m_nResize;
			ar >> m_nBorderStyle;
			ar >> m_nKeyIndexCnt;
			ar >> m_nItemFlag;
			ar >> m_nSpecialContent;
			ar >> m_nLineMode;
			ar >> m_nDnDMode;
			ar >> m_nDragIndex;
			ar >> m_nPopupMenuMode;
			ar >> m_nRealHighlight;
			ar >> m_nSelectColorIndex;

			ar >> m_byNeedMouseOverCheck;
			ar >> m_byUseAmountGraph;

			ar >> m_nBorderColorIndex;
			ar >> m_strRPImportRecord;
			ar >> m_strRealImportRecord;
			ar >> m_strRQExportRecord;
//			ar >> m_strCommTrName;
			ar >> m_strOptionQueryInfo;

			ar >> m_strPrevCtrlName;
			ar >> m_strNextCtrlName;
			ar >> m_nDataType;
		}
		ar >> m_byUseSelectColor;
		ar >> m_bySpecialHoga;
		ar >> m_byMultiItemUse;
		ar >> m_byTailUse;

		if ( LOWORD(m_dwBaseVer) >= 5 )				// Ver5
			ar >> m_byMultiTranUse;

		if ( LOWORD(m_dwBaseVer) >= 7 )				// Ver7
			ar >> m_byMultiMarketUse;

		if ( LOWORD(m_dwBaseVer) >= 8 )				// Ver8
			ar >> m_byNextDataHeaderCheck;

		if ( LOWORD(m_dwBaseVer) >= 9 )				// Ver9
			ar >> m_byFixedRowCheck;

//		ar >> m_byUseForDll;
	
		if( m_pRowSize /*&& !m_bSkip*/ )
		{
			m_pRowSize->Serialize(ar);
		}

		if(m_pColSize /*&& !m_bSkip*/ )
		{
			m_pColSize->Serialize(ar);
		}

		if(m_pCovered)
		{
			m_pCovered->Serialize(ar);
		}

		if(m_pCellCtrl)
		{
			m_pCellCtrl->Serialize(ar);
		}

		if ( m_pBorderInfo )
		{
			m_pBorderInfo->Serialize(ar);
		}

		if(m_pTTip)
		{
			m_pTTip->Serialize(ar);
		}

		if(!m_bSkip)
		{
			if(m_pFormula)
			{
				m_pFormula->Serialize(ar);
			}
		}
		
		if(m_pFixKey)
		{
			m_pFixKey->Serialize(ar);
		}
		
		if ( m_pNewRefer )
			m_pNewRefer->Serialize(ar);
		
		if(m_pUserLinkArray)
		{
			m_pUserLinkArray->Serialize(ar);
		}
// --> [Edit]  김창하 2006/06/16
// Version 3 m_pmapRecordInfo삭제:
		if ( LOWORD(m_dwBaseVer) <= 2 )
		{
			if ( m_pmapRecordInfo )
			{
				m_pmapRecordInfo->Serialize(ar);
			}
		}

// --> [Edit]  김창하 2006/06/16
// m_pInputMaskArray 추가 
		if ( LOWORD(m_dwBaseVer) >= 3 )
		{
			if ( m_pInputMaskArray )
			{
				m_pInputMaskArray->Serialize(ar);
			}

			if ( m_pRecordNameArray )
			{
				m_pRecordNameArray->Serialize(ar);
			}

			if ( m_pReplaceTextArray )
			{
				m_pReplaceTextArray->Serialize(ar);
			}
		}

		if ( LOWORD(m_dwBaseVer) >= 9 )
		{
			// Caption Static text 
			if ( m_pCaptionTextArray )
			{
				m_pCaptionTextArray->Serialize(ar);
			}
		}
// <-- [Edit]  김창하 2006/06/16

// <-- [Edit]  김창하 2006/06/16
    }

};

void COgBase::CopyVariable( const COgBase& other )
{
	m_bSkip					=	other.m_bSkip;
	m_dwBaseVer				=	other.m_dwBaseVer;
	m_CtrlSize				=	other.m_CtrlSize;
	m_nRowCnt				=	other.m_nRowCnt;
	m_nColCnt				=	other.m_nColCnt;
	m_nFrozenRowCnt			=	other.m_nFrozenRowCnt;
	m_nFrozenColCnt			=	other.m_nFrozenColCnt;
	m_nHiddenRowCnt			=	other.m_nHiddenRowCnt;
	m_nHiddenColCnt			=	other.m_nHiddenColCnt;
	m_nDefColWidth			=	other.m_nDefColWidth;
	m_nDefRowHeight			=	other.m_nDefRowHeight;
	m_nLineColorIndex		=	other.m_nLineColorIndex;
	m_nBackGndColorIndex	=	other.m_nBackGndColorIndex;
	m_nSelectionMode		=	other.m_nSelectionMode;
	m_nLineStyle			=	other.m_nLineStyle;
	m_nScrollMode			=	other.m_nScrollMode;
	m_nResizeHeader			=	other.m_nResizeHeader;
	m_nItemFlag				=	other.m_nItemFlag;
	m_nSpecialContent		=	other.m_nSpecialContent;

	m_nLineMode				=	other.m_nLineMode;
	m_bUseFormula			=	other.m_bUseFormula;
	m_wScriptEvent			=	other.m_wScriptEvent;
	m_wFireLinkInfo			=	other.m_wFireLinkInfo;
	m_nResize				=	other.m_nResize;
	m_nBorderStyle			=	other.m_nBorderStyle;
	m_nKeyIndexCnt			=	other.m_nKeyIndexCnt;
	m_nDnDMode				=	other.m_nDnDMode;
	m_nDragIndex			=	other.m_nDragIndex;
	m_nPopupMenuMode		=	other.m_nPopupMenuMode;
	m_nRealHighlight		=	other.m_nRealHighlight;
	m_byUseSelectColor		=	other.m_byUseSelectColor;
	m_nSelectColorIndex		=	other.m_nSelectColorIndex;

	m_bySpecialHoga			=	other.m_bySpecialHoga;
	m_byNeedMouseOverCheck	=	other.m_byNeedMouseOverCheck;
	m_byUseAmountGraph		=	other.m_byUseAmountGraph;
	m_byUseForDll			=	other.m_byUseForDll;
	m_byMultiItemUse		=	other.m_byMultiItemUse;
	m_byTailUse				=	other.m_byTailUse;						//Tail Use
	m_byMultiTranUse		=	other.m_byMultiTranUse;					//다중트랜 사용
	m_byMultiMarketUse		=	other.m_byMultiMarketUse;	
	m_byNextDataHeaderCheck =	other.m_byNextDataHeaderCheck;	
	m_byFixedRowCheck		=	other.m_byFixedRowCheck;	

	m_nBorderColorIndex		=	other.m_nBorderColorIndex;
	
	m_strRPImportRecord		=	other.m_strRPImportRecord;
	m_strRealImportRecord	=	other.m_strRealImportRecord;
	m_strRQExportRecord		=	other.m_strRQExportRecord;

//	m_strCommTrName			= 	other.m_strCommTrName;
	m_strOptionQueryInfo			= 	other.m_strOptionQueryInfo;

	m_strPrevCtrlName		= 	other.m_strPrevCtrlName;
	m_strNextCtrlName		= 	other.m_strNextCtrlName;
	m_nDataType				= 	other.m_nDataType;
	
//	m_strTRMemInfo			=	other.m_strTRMemInfo;

}

const COgBase& COgBase::operator=(const COgBase& other)
{
	if (&other == this)
		return *this;

	if(other.m_pRowSize)
		*m_pRowSize			=	*other.m_pRowSize;
	
	if(other.m_pColSize)
		*m_pColSize			=	*other.m_pColSize;
	
	if(other.m_pCovered)
		*m_pCovered			=	*other.m_pCovered;
	
	if(other.m_pCellCtrl)
		*m_pCellCtrl		=	*other.m_pCellCtrl;
	
	if(other.m_pBorderInfo)
		*m_pBorderInfo		=	*other.m_pBorderInfo;

	if(other.m_pTTip)
		*m_pTTip			=	*other.m_pTTip;
	
	if(other.m_pFormula)
		*m_pFormula			=	*other.m_pFormula;

// --> [Edit]  김창하 2006/06/16
// m_pRecordNameArray 추가 
	if(other.m_pRecordNameArray)
		*m_pRecordNameArray	=	*other.m_pRecordNameArray;

// m_pInputMaskArray 추가 
	if(other.m_pInputMaskArray )
		*m_pInputMaskArray	=	*other.m_pInputMaskArray;

	if(other.m_pReplaceTextArray)
		*m_pReplaceTextArray=	*other.m_pReplaceTextArray;

	if(other.m_pCaptionTextArray)
		*m_pCaptionTextArray=	*other.m_pCaptionTextArray;

// <-- [Edit]  김창하 2006/06/16

	if(other.m_pFixKey)
		*m_pFixKey			=	*other.m_pFixKey;
	
	if(other.m_pNewRefer)
		*m_pNewRefer		=	*other.m_pNewRefer;
	
	if(other.m_pUserLinkArray)
		*m_pUserLinkArray	=	*other.m_pUserLinkArray;

#if FALSE
// --> [Edit]  김창하 2006/06/16
// Version 3 m_pmapRecordInfo삭제:
	if(other.m_pmapRecordInfo )
		*m_pmapRecordInfo    =  *other.m_pmapRecordInfo;
// <-- [Edit]  김창하 2006/06/16
#endif

	return *this;
}

//*****************************************************************************
// 루    틴    명  :  SetBaseBoolBit
// 기          능  :  BoolBit의 정보를 실제의 변수에 적용한다..
// 입          력  :  long lBoolBit : Bit Info 
//*****************************************************************************
void COgBase::SetBaseBoolBit(const long lBoolBit)
{
	if( lBoolBit & BASE_BBIT_USE_FORMULA )
		m_bUseFormula = TRUE;
	else
		m_bUseFormula = FALSE;

	if( lBoolBit & BASE_BBIT_USE_CELL_DATACNVT )
		m_nRealHighlight = dxRealHLCell;
	else if( lBoolBit & BASE_BBIT_USE_COL_DATACNVT )
		m_nRealHighlight = dxRealHLCol;
	else if ( lBoolBit & BASE_BBIT_USE_REG_DATACNVT )
		m_nRealHighlight = dxRealHLRegCell;
	else
		m_nRealHighlight = dxRealHLNone;


//	if( lBoolBit & BASE_BBIT_USE_SELECTCOLOR )
//		m_byUseSelectColor = (BYTE) TRUE;
//	else
//		m_byUseSelectColor = (BYTE) FALSE;

//	if( lBoolBit & BASE_BBIT_USE_DELAYTIMER )
//		m_byMultiItemUse = (BYTE) TRUE;
//	else
//		m_byMultiItemUse = (BYTE) FALSE;

//	if( lBoolBit & BASE_BBIT_USE_BOTTOM_TAIL )		// 하단 합계행 
//		m_byTailUse |= TG_BOTTOM;
//	if( lBoolBit & BASE_BBIT_USE_TOP_TAIL )			// 상단 합계행 
//		m_byTailUse |= TG_TOP;

//	if( lBoolBit & BASE_BBIT_IS_SPECIALHOGA )
//		m_bySpecialHoga = (BYTE) TRUE;
//	else
//		m_bySpecialHoga = (BYTE) FALSE;

	if( lBoolBit & BASE_BBIT_MMOVE_OVERCHECK )
		m_byNeedMouseOverCheck = (BYTE) TRUE;
	else
		m_byNeedMouseOverCheck = (BYTE) FALSE;

	if( lBoolBit & BASE_BBIT_USE_AMOUNTGRAPH )
		m_byUseAmountGraph = (BYTE) TRUE;
	else
		m_byUseAmountGraph = (BYTE) FALSE;
}

//*****************************************************************************
// 루    틴    명  :  GetBaseBoolBit
// 기          능  :  변수의 값에 따른 BoolBit를 조합하여 구함.
// 리          턴  :  조합된 BoolBit 
//*****************************************************************************
const long COgBase::GetBaseBoolBit()
{
	long lBoolBit(0);

	if( m_bUseFormula )
		lBoolBit |= BASE_BBIT_USE_FORMULA;

	switch(m_nRealHighlight)
	{
	case dxRealHLCell:
		lBoolBit |= BASE_BBIT_USE_CELL_DATACNVT;
		break;
	case dxRealHLCol:
		lBoolBit |= BASE_BBIT_USE_COL_DATACNVT;
		break;
	case dxRealHLRegCell:
		lBoolBit |= BASE_BBIT_USE_REG_DATACNVT;
		break;
	case dxRealHLNone:
		//lBoolBit |= BASE_BBIT_USE_SELECTCOLOR;
		break;
	}

//	if( m_byUseSelectColor )
//		lBoolBit |= BASE_BBIT_USE_SELECTCOLOR;

//	if( m_byMultiItemUse )
//		lBoolBit |= BASE_BBIT_USE_DELAYTIMER;

//Tail USE
//	if( m_byTailUse & TG_BOTTOM )					// 하단 합계행 
//		lBoolBit |= BASE_BBIT_USE_BOTTOM_TAIL;

//	if( m_byTailUse & TG_TOP )						// 상단 합계행 
//		lBoolBit |= BASE_BBIT_USE_TOP_TAIL;

//	if( m_bySpecialHoga )		
//		lBoolBit |= BASE_BBIT_IS_SPECIALHOGA;

	if( m_byNeedMouseOverCheck )
		lBoolBit |= BASE_BBIT_MMOVE_OVERCHECK;

	if( m_byUseAmountGraph )
		lBoolBit |= BASE_BBIT_USE_AMOUNTGRAPH;

	return lBoolBit;
}

// Moving Colums or Rows
BOOL COgBase::Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol /*= TRUE*/)
{
#if FALSE
	if(bMoveCol)
	{
		if( m_pColSize )
			m_pColSize->Move( nFrom, nDest);

	}
	else
	{
		if( m_pRowSize )
			m_pRowSize->Move( nFrom, nDest);
	}
#endif

	if( m_pCovered )
		m_pCovered->Move( nFrom, nDest, bMoveCol );
	
	if( m_pCellCtrl )
		m_pCellCtrl->Move( nFrom, nDest, bMoveCol );

	
	if( m_pBorderInfo)
		m_pBorderInfo->Move( nFrom, nDest, bMoveCol );

	//m_pTTip
	if( m_pFixKey )
		m_pFixKey->Move( nFrom, nDest, bMoveCol, CCellTextArray::DXArrType::ATFixKey );
	
	if( m_pUserLinkArray )
		m_pUserLinkArray->Move( nFrom, nDest, bMoveCol, CCellTextArray::DXArrType::ATUserLinkTag );

// --> [Edit]  김창하 2006/06/16
// m_pInputMaskArray 추가 
	if ( m_pInputMaskArray )
		m_pInputMaskArray->Move( nFrom, nDest, bMoveCol, CCellTextArray::DXArrType::ATInputMask );

// 대체문자 	
	if ( m_pReplaceTextArray )
		m_pReplaceTextArray->Move( nFrom, nDest, bMoveCol, CCellTextArray::DXArrType::ATReplaceText );

	// Caption Static text 
	if ( m_pCaptionTextArray )
	{
		m_pCaptionTextArray->Move( nFrom, nDest, bMoveCol, CCellTextArray::DXArrType::ATCaptionText );
	}

// m_pRecordNameArray 추가
	if ( m_pRecordNameArray )
		m_pRecordNameArray->Move( nFrom, nDest, bMoveCol, CCellTextArray::DXArrType::ATRecordName );
// <-- [Edit]  김창하 2006/06/16

	//m_pReferArray
	//m_pNewRefer
	//m_pRPImMemArray;
	//m_pRealImMemArray;
	//m_pRQExMemArray;
	//m_pRecItemMap;

	return TRUE;

}

// Insert Columns Or Rows
BOOL COgBase::Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol /*= TRUE*/)
{
	if(bInsertCol)
	{
		if( m_pColSize )
			m_pColSize->Insert(nAddIndex, nAddCount, m_nDefColWidth);

	}
	else
	{
		if( m_pRowSize )
			m_pRowSize->Insert(nAddIndex, nAddCount, m_nDefRowHeight);
	}

	if( m_pCovered )
		m_pCovered->Insert(nAddIndex, nAddCount, bInsertCol );
	
	if( m_pCellCtrl )
		m_pCellCtrl->Insert(nAddIndex, nAddCount, bInsertCol );

	if( m_pBorderInfo )
		m_pBorderInfo->Insert(nAddIndex, nAddCount, bInsertCol );
	

	//m_pTTip
	if( m_pFixKey )
		m_pFixKey->Insert(nAddIndex, nAddCount, CCellTextArray::DXArrType::ATFixKey );

	if( m_pUserLinkArray )
		m_pUserLinkArray->Insert(nAddIndex, nAddCount, CCellTextArray::DXArrType::ATUserLinkTag );

// --> [Edit]  김창하 2006/06/16
// m_pInputMaskArray 추가 
	if ( m_pInputMaskArray )
		m_pInputMaskArray->Insert(nAddIndex, nAddCount, CCellTextArray::DXArrType::ATInputMask );

// 대체문자 	
	if ( m_pReplaceTextArray )
		m_pReplaceTextArray->Insert(nAddIndex, nAddCount, CCellTextArray::DXArrType::ATReplaceText );

	// Caption Static text 
	if ( m_pCaptionTextArray )
	{
		m_pCaptionTextArray->Insert(nAddIndex, nAddCount, CCellTextArray::DXArrType::ATCaptionText  );
	}

// m_pRecordNameArray 추가
	if ( m_pRecordNameArray )
		m_pRecordNameArray->Insert(nAddIndex, nAddCount, CCellTextArray::DXArrType::ATRecordName );
// <-- [Edit]  김창하 2006/06/16

	//m_pReferArray
	//m_pNewRefer
	//m_pRPImMemArray;
	//m_pRealImMemArray;
	//m_pRQExMemArray;
	//m_pRecItemMap;

	return TRUE;

}

// Insert Columns Or Rows
BOOL COgBase::Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol /*= TRUE*/)
{
	if(bRemoveCol)
	{
		if( m_pColSize )
			m_pColSize->Remove(nDelIndex, nDelCount);

	}
	else
	{
		if( m_pRowSize )
			m_pRowSize->Remove(nDelIndex, nDelCount);
	}

	if( m_pCovered )
		m_pCovered->Remove(nDelIndex, nDelCount, bRemoveCol );
	
	if( m_pCellCtrl )
		m_pCellCtrl->Remove(nDelIndex, nDelCount, bRemoveCol );

	if( m_pBorderInfo)
		m_pBorderInfo->Remove(nDelIndex, nDelCount, bRemoveCol );

	//m_pTTip
	if( m_pFixKey )
		m_pFixKey->Remove(nDelIndex, nDelCount, bRemoveCol, CCellTextArray::DXArrType::ATFixKey );
	
	if( m_pUserLinkArray )
		m_pUserLinkArray->Remove(nDelIndex, nDelCount, bRemoveCol, CCellTextArray::DXArrType::ATUserLinkTag );

// --> [Edit]  김창하 2006/06/16
// m_pInputMaskArray 추가 
	if ( m_pInputMaskArray )
		m_pInputMaskArray->Remove(nDelIndex, nDelCount, bRemoveCol, CCellTextArray::DXArrType::ATInputMask );

// 대체문자 	
	if ( m_pReplaceTextArray )
		m_pReplaceTextArray->Remove(nDelIndex, nDelCount, bRemoveCol, CCellTextArray::DXArrType::ATReplaceText );

	// Caption Static text 
	if ( m_pCaptionTextArray )
	{
		m_pCaptionTextArray->Remove(nDelIndex, nDelCount, bRemoveCol, CCellTextArray::DXArrType::ATCaptionText  );
	}

// m_pRecordNameArray 추가
	if ( m_pRecordNameArray )
		m_pRecordNameArray->Remove(nDelIndex, nDelCount, bRemoveCol, CCellTextArray::DXArrType::ATRecordName );
// <-- [Edit]  김창하 2006/06/16

	//m_pReferArray
	//m_pNewRefer
	//m_pRPImMemArray;
	//m_pRealImMemArray;
	//m_pRQExMemArray;
	//m_pRecItemMap;

	return TRUE;

}

// Copy Columns Or Rows
BOOL COgBase::Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol /*= TRUE*/)
{
	if(bCopyCol)
	{
		if( m_pColSize )
			m_pColSize->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo );

	}
	else
	{
		if( m_pRowSize )
			m_pRowSize->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo);
	}

	if( m_pCovered )
		m_pCovered->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol );
	
	if( m_pCellCtrl )
		m_pCellCtrl->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol );

	if( m_pBorderInfo)
		m_pBorderInfo->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol );

	if( m_pFixKey )
		m_pFixKey->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol, CCellTextArray::DXArrType::ATFixKey );

	if( m_pUserLinkArray )
		m_pUserLinkArray->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol, CCellTextArray::DXArrType::ATUserLinkTag );

// --> [Edit]  김창하 2006/06/16
// m_pInputMaskArray 추가 
	if ( m_pInputMaskArray )
		m_pInputMaskArray->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol, CCellTextArray::DXArrType::ATInputMask );

// 대체문자 	
	if ( m_pReplaceTextArray )
		m_pReplaceTextArray->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol, CCellTextArray::DXArrType::ATReplaceText );

	// Caption Static text 
	if ( m_pCaptionTextArray )
	{
		m_pCaptionTextArray->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol, CCellTextArray::DXArrType::ATCaptionText );
	}

// m_pRecordNameArray 추가
	if ( m_pRecordNameArray )
		m_pRecordNameArray ->Copy( nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol, CCellTextArray::DXArrType::ATRecordName );
// <-- [Edit]  김창하 2006/06/16

	//m_pReferArray
	//m_pNewRefer
	//m_pRPImMemArray;
	//m_pRealImMemArray;
	//m_pRQExMemArray;
	//m_pRecItemMap;

	return TRUE;

}

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CGridInfo, CObject, 1)
CGridInfo::CGridInfo()
{
	m_nGridMode				=	dxHGrid;
	m_nVirtualMode			=	dxVMNone;
	m_nSortMode				=	dxSortNotUse;	
	m_nHeaderRowCnt			=	DEF_HEADER_ROW_COUNT;
	m_nHeaderColCnt			=	DEF_HEADER_COLUMN_COUNT;
	m_nSubItemCnt			=	DEF_SUBITEM_COUNT;
	m_nBlockCount			=	/*DEF_BLOCK_COUNT*/1;
	m_nOddColorIndex		=	DEF_ODD_COLORINDEX;
	m_nEvenColorIndex		=	DEF_EVEN_COLORINDEX;
	m_nMaxDataCnt			=	DEF_MAX_DATACOUNT;
	m_nScrollAction			=   dxSActDefault;
	m_bUseBlockColor		=	TRUE;
	m_bUse3DButtonHeader	=	dxHNormal;
	m_nAllowSameKey			=	0;
	m_nAllowSameSubKey		=	0;
	m_nAllowSameThirdKey	=	0;
	m_byHeaderMove			=	FALSE;
	m_nFixedHeaderMoveCnt	=	0;
	m_nBHLineColorIndex		=	DEF_LINE_COLORINDEX;
	m_nHVLineColorIndex		=	DEF_LINE_COLORINDEX;
	m_nHHLineColorIndex		=	DEF_LINE_COLORINDEX;
	m_bySaveColSize			=	FALSE;

	m_pGridHeader			=	NULL;
	m_pGridBody				=	NULL;
	//m_pGridLine				=	NULL;
	m_pRealCon				=	NULL;

	m_pGridHeader = new CGridHeader;
	if(m_pGridHeader)
	{
		m_pGridHeader->SetGridInfo(this);
		m_pGridHeader->Initialize();
	}
	
	m_pGridBody = new CGridBody;
	if(m_pGridBody)
	{
		m_pGridBody->SetGridInfo(this);
		m_pGridBody->Initialize();
	}

	//m_pGridLine = new CLineBorder(TRUE);

	m_pRealCon = new CRealCondition;
	if(m_pRealCon)
	{
		m_pRealCon->SetGridInfo(this);
	}

#ifdef MULTI_CAPTION_USE		// 다국어 사용옵션 
	m_pGridMultiHeader = new CGXCaptionData;
	m_pGridMultiBody   = new CGXCaptionData;
#endif

};

CGridInfo::~CGridInfo()
{
	//COgBase::~COgBase();

	if(m_pGridHeader)
	{
		m_pGridHeader->Clear();
		delete m_pGridHeader;
		m_pGridHeader = NULL;
	}

	if(m_pGridBody)
	{
		m_pGridBody->Clear();
		delete m_pGridBody;
		m_pGridBody = NULL;
	}

#ifdef MULTI_CAPTION_USE		// 다국어 사용옵션 
	if ( m_pGridMultiHeader )
		delete m_pGridMultiHeader;
	if ( m_pGridMultiBody )
		delete m_pGridMultiBody;
#endif

	/*
	if(m_pGridLine)
	{
		m_pGridLine->Clear();
		delete m_pGridLine;
		m_pGridLine = NULL;
	}
	*/
	
	if(m_pRealCon)
	{
		m_pRealCon->Clear();
		delete m_pRealCon;
		m_pRealCon = NULL;
	}

};

// 다이얼로그에서 사용하기 위해서 추가.
void CGridInfo::SetDefault(int nRowCnt, int nColCnt, int nHRowCnt, int nHColCnt, int nSubCnt)
{
	// Base Info
	//m_CtrlSize			=	DEF_CTRL_SIZE;
	m_nRowCnt				=	nRowCnt;
	m_nColCnt				=	nColCnt;
	m_nFrozenRowCnt			=	nHRowCnt;
	m_nFrozenColCnt			=	nHColCnt;
	//m_nSelectionMode		=	(int)dxSelTable;
	//m_nScrollMode			=	(int)dxScrollOnlyV;
	//m_nResizeHeader			=	(int)dxRszHdrNotUse;
	//m_nLineMode				=	(int)dxLineOnlyV;
	//m_nDragIndex			=	DEF_HEADER_ROW_COUNT;

	if(m_pRowSize)
	{
		m_pRowSize->Clear();
		m_pRowSize->Initialize(m_nRowCnt, DEF_ROW_HEIGHT);
	}

	if(m_pColSize)
	{
		m_pColSize->Clear();
		m_pColSize->Initialize(m_nColCnt, DEF_COLUMN_WIDHT);
	}

	// Grid Info
	m_nHeaderRowCnt			=	nHRowCnt;
	m_nHeaderColCnt			=	nHColCnt;
	//m_nBlockCount			=	/*DEF_BLOCK_COUNT*/1;
	//m_bUseBlockColor		=	TRUE;
	//m_bUse3DButtonHeader		=	TRUE;
	//m_byHeaderMove			=	FALSE;
	//m_nFixedHeaderMoveCnt = 1;
	
	if(m_pGridHeader)
	{
		m_pGridHeader->Clear();
		m_pGridHeader->Initialize();
	}
	
	if(m_pGridBody)
	{
		m_pGridBody->Clear();
		m_pGridBody->Initialize();
	}

	if(m_pRealCon)
	{
		m_pRealCon->Clear();
	}
	
}

//*******************************************************************/
/*! Function Name : GetGridBodyPropertyDataFromBlobData
/*! Function      : 그리드 셀 정보를 빌더에 저장하기 위해서 텍스트롤 변환하는 함수 
/*! Param         : int nControlMode /*= dxHGrid*/
/*! Return        : CString  
/*! Create        : 김창하 , 2006/06/09
/*! Comment       : 
//******************************************************************/
CString  CGridInfo::GetGridBodyPropertyDataFromBlobData( int nControlMode /*= dxHGrid*/ )
{
	CString  strPropertyData;
	
	int nLenBaseItem	= sizeof( OGBASEITEM );
	int nLenBodyRec		= sizeof( GRIDBODY   );
		
	int nLenBody		= sizeof(DWORD)+(sizeof(short)*2);

	short nSubItemCount = m_nSubItemCnt;	// 가로 그리드 : Sub Row Count, 세로 그리드 : Sub Cloumn Count, 
		
	short nItemCount;						// 가로 그리드 : Column Count, 세로 그리드 : Row Count, 
	if ( nControlMode == dxHGrid )			// 가로 그리드 : Column Count
	{
		nItemCount = m_nColCnt - m_nHeaderColCnt;
		// 헤더만 존재하는 경우 ...
		
		if ( !(m_wScriptEvent & FE_BODYROW_ZERO) &&  m_nRowCnt-m_nHeaderRowCnt == 0 )
		{
			return _T("");
		}
	}
	else if ( nControlMode == dxVGrid )		// 세로 그리드 : Row Count
	{
		nItemCount = m_nRowCnt - m_nHeaderRowCnt;
	}

	DWORD dwTotalLength = nLenBody + ((nSubItemCount* nItemCount)* nLenBodyRec) ;
    if ( nSubItemCount == 0 )
		return _T("");

	ASSERT ( m_pGridBody->dwLength == dwTotalLength );

	BYTE* pvData = (BYTE*)malloc( dwTotalLength );
	if ( pvData != NULL )
	{
		memset( pvData, 0x0, dwTotalLength );
			
		int nOffset = 0;
		*(DWORD*)pvData = dwTotalLength;
//		memcpy(pvData, (DWORD*)&dwLength, sizeof(DWORD));
		nOffset += sizeof(DWORD);
				
		*(short*)(pvData + nOffset ) = nSubItemCount;
		nOffset += sizeof(short);

		*(short*)(pvData + nOffset ) = nItemCount;
		nOffset += sizeof(short);

		int nMaxRow = nSubItemCount;
		int nMaxCol = nItemCount;
		//int nLen;

		for ( int nRow = 0 ; nRow < nMaxRow; nRow ++ )
		{
			for ( int nCol = 0 ; nCol < nMaxCol ; nCol ++ )
			{
				GRIDBODY* pBodyInfo = NULL;
				pBodyInfo = (GRIDBODY*)m_pGridBody->pRec[nRow][nCol];
				ASSERT ( pBodyInfo != NULL );

				memcpy ( pvData + nOffset , pBodyInfo, LEN_GRIDBODY );
				TRACE(" Item>>> nPos=[%d], Item=[%s] \n", pBodyInfo->nPos, pBodyInfo->szItem );

				nOffset += LEN_GRIDBODY;
			}
		}

		strPropertyData = BinaryToString( pvData, dwTotalLength );
		free(pvData);
	}
	return strPropertyData;
}


//*******************************************************************/
/*! Function Name : GetGridHeaderPropertyDataFromBlobData
/*! Function      : 그리드 셀(헤더) 정보를 빌더에 저장하기 위해서 텍스트롤 변환하는 함수 
/*! Param         : int nControlMode /*= dxHGrid */
/*! Return        : CString  
/*! Create        : 김창하 , 2006/06/09
/*! Comment       : 
//******************************************************************/
CString  CGridInfo::GetGridHeaderPropertyDataFromBlobData( int nControlMode /*= dxHGrid */)
{
	
	CString  strPropertyData;
	int nLenGridHeader	   = sizeof(GRIDHEADER);

	ROWCOL  nRowHeaderCount = m_nHeaderRowCnt,  //GetHeaderRows(),
			nColHeaderCount = m_nHeaderColCnt;  //GetHeaderCols();

	ROWCOL nRowCount, nRowMax,
			nColCount, nColMax;
			
	nRowCount = m_nRowCnt;						// GetRowCount();
	nColCount = m_nColCnt;						// GetColCount();
	// RowHeaderCount * Column Count

	nRowMax = nRowHeaderCount * nColCount;
	nColMax = nColHeaderCount * ( nRowCount - nRowHeaderCount );

	int nTotalCount  = nRowMax + nColMax;
	
	if ( nTotalCount <= 0 )
	{
		return strPropertyData;
	}
	DWORD dwTotalLength   = sizeof(DWORD)+ sizeof(short) + ( nTotalCount * nLenGridHeader );
    
	ASSERT ( m_pGridHeader->dwLength == dwTotalLength );
	ASSERT ( m_pGridHeader->nCount   == nTotalCount );
	int nOffset = 0;
	

	BYTE* pvData = (BYTE*)malloc( dwTotalLength );
	if ( pvData != NULL )
	{
		memset( pvData, 0x0, dwTotalLength );

		*(DWORD*)pvData = dwTotalLength;
		nOffset += sizeof(DWORD);

		*(short*)(pvData + nOffset ) = m_pGridHeader->nCount;
		nOffset += sizeof(short);

		GRIDHEADER* pHeaderRec = NULL;
		int nIndex = 0;

		if ( nRowMax > 0 )
		{
			for ( int nRow = 1 ; nRow <= nRowHeaderCount; nRow ++ )
			{
				for ( int nCol = 1 ; nCol <= nColCount; nCol ++ )
				{
					pHeaderRec = m_pGridHeader->pRec[nIndex];
					ASSERT( pHeaderRec != NULL );

					memcpy ( pvData + nOffset, pHeaderRec, LEN_GRIDHEADER );
					nOffset += LEN_GRIDHEADER;
					TRACE("Header Caption>>> nRow=[%d], Col=[%d], Caption=[%s]\n", 
									pHeaderRec->nRow, pHeaderRec->nCol, pHeaderRec->szCaption );
					nIndex++;

				}
			}
		}

		if ( nColMax > 0 )													// Column 
		{
//			nIndex = 0;
			for ( int nCol = 1 ; nCol <= nColHeaderCount; nCol ++ )
			{
				for ( int nRow = nRowHeaderCount+1 ; nRow <= nRowCount; nRow ++ )
				{
					pHeaderRec = m_pGridHeader->pRec[nIndex];
					ASSERT( pHeaderRec != NULL );

					memcpy ( pvData + nOffset, pHeaderRec, LEN_GRIDHEADER );
					nOffset += LEN_GRIDHEADER;
					TRACE("Header Caption>>> nRow=[%d], Col=[%d], Caption=[%s]\n", 
									pHeaderRec->nRow, pHeaderRec->nCol, pHeaderRec->szCaption );
					nIndex++;
				}
			}
		}
			
		strPropertyData = BinaryToString( pvData, dwTotalLength );
		free(pvData);
	}
	return strPropertyData;
}

//*****************************************************************************
// 루    틴    명  :  GetRealConditionPropertyDataFromBlobData
// 기          능  :  그리드 실시간조건 정보를 프로퍼티 스트링으로 변한하는 함수. 
// 입          력  :  
// 출          력  :  CString  
// 작    성    자  :  2004년10월120일    홍 인기 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
CString  CGridInfo::GetRealConditionPropertyDataFromBlobData()
{
	CString  strPropertyData;
	
	int nOffset = 0;
	DWORD dwTotalLength = LEN_REALCONINFO(m_pRealCon->nRecCount, m_pRealCon->nConCount);

	BYTE* pvData = (BYTE*)malloc( dwTotalLength );
	BYTE nIndex;
	if ( pvData != NULL )
	{
		memset( pvData, 0x0, dwTotalLength );

		*(DWORD*)pvData = dwTotalLength;
		nOffset += sizeof(DWORD);

		*(BYTE*)(pvData + nOffset ) = m_pRealCon->nRecCount;
		nOffset += sizeof(BYTE);

		*(BYTE*)(pvData + nOffset ) = m_pRealCon->nConCount;
		nOffset += sizeof(BYTE);
	
		for ( nIndex = 0 ; nIndex < m_pRealCon->nRecCount; nIndex++ )
		{
			memcpy ( pvData + nOffset, m_pRealCon->ppRecType[nIndex], LEN_REALRECTYPE);
			nOffset += LEN_REALRECTYPE;
		}


		for ( /*BYTE*/ nIndex = 0 ; nIndex < m_pRealCon->nConCount; nIndex++ )
		{
			memcpy ( pvData + nOffset, m_pRealCon->ppCondition[nIndex], LEN_REALCONITEM);
			nOffset += LEN_REALCONITEM;
		}

		
		strPropertyData = BinaryToString( pvData, dwTotalLength );
		free(pvData);
	}
	return strPropertyData;
}



//*******************************************************************/
/*! Function Name : SetGridBodyDataBlobDataChange
/*! Function      : 그리드 셀 정보를 Text에서 바이너리로 변환하는 함수 
/*! Param         : CString  strPropertyData
/*! Return        : BOOL  
/*! Create        : 김창하 , 2006/06/09
/*! Comment       : 디자인 정보에서 Run정보로 변환 
//******************************************************************/
BOOL  CGridInfo::SetGridBodyDataBlobDataChange( CString  strPropertyData )
{
	if ( strPropertyData.IsEmpty() )
		return FALSE;

// --> [Edit]  김창하 2006/04/28
	int nBaseVer = LOWORD(m_dwBaseVer);
	int nAddLen(0);  
	if ( nBaseVer <= 1 )
	{
		nAddLen = 10;							//ITEM_LEN길이값이 20자리에서 30자리로 변경 
	}
// <-- [Edit]  김창하 2006/04/28

	BYTE*	pvData = NULL;
	pvData = StringToBinary( strPropertyData );
	
	ASSERT( pvData != NULL );
    if( pvData != NULL )
	{
		DWORD	dwLength;
		int		nOffset = 0;

		m_pGridBody->Clear();

		dwLength = *(long*)pvData;
		nOffset += sizeof(DWORD);

		m_pGridBody->dwLength = dwLength;

		m_pGridBody->nSubItemCount = *(short*)(pvData + nOffset);
		nOffset += sizeof(short);
				
		m_pGridBody->nItemCount	 = *(short*)(pvData + nOffset);
		nOffset += sizeof(short);
	
		DWORD dwTotalLen	   = sizeof(DWORD)+ (sizeof(short) * 2) + ( m_pGridBody->nSubItemCount *  m_pGridBody->nItemCount * LEN_GRIDBODY );
// --> [Edit]  김창하 2006/04/28
		if ( dwTotalLen != m_pGridBody->dwLength )
		{
			if ( nBaseVer <= 1 )
			{
				m_pGridBody->dwLength = dwTotalLen;
			}
			else
			{
				ASSERT ( FALSE );
			}
		}
// <-- [Edit]  김창하 2006/04/28


		int nMaxRow = m_pGridBody->nSubItemCount;
		int nMaxCol = m_pGridBody->nItemCount;

		m_pGridBody->pRec = new GRIDBODY**[ nMaxRow ];
		for ( int nRow = 0 ; nRow < nMaxRow ; nRow ++ )
		{
			m_pGridBody->pRec[nRow] = new GRIDBODY*[ nMaxCol ];
			for ( int nCol = 0 ; nCol < nMaxCol; nCol ++ )
			{
				m_pGridBody->pRec[nRow][nCol] = new GRIDBODY;
				memset ( m_pGridBody->pRec[nRow][nCol], 0x0, LEN_GRIDBODY );
// --> [Edit]  김창하 2006/04/28
				if ( nBaseVer <= 1 )						//   
				{
					int nLen = sizeof(short)*6;									// nPos->nRTxCrIndex
					memcpy ( m_pGridBody->pRec[nRow][nCol], pvData + nOffset, nLen );
					nOffset += nLen;
																				// char		szItem[ITEM_LEN+1];
					nLen = ITEM_LEN-nAddLen;
					memcpy ( &m_pGridBody->pRec[nRow][nCol]->szItem, pvData + nOffset, nLen );
					nOffset += nLen+1;
					
					nLen = sizeof(BYTE)*2+ sizeof(long) + LEN_OGBASEITEM + LEN_ITEMBITS + LEN_GRIDBITS + LEN_MASKINFO;
					memcpy ( &m_pGridBody->pRec[nRow][nCol]->bySignFormat, pvData + nOffset, nLen );
					nOffset += nLen;					
//					OGBASEITEM	bsItem;
//					ITEMBITS	ItemBits;
//					GRIDBITS	GridBits;
//					MASKINFO	mask;
				}
				else
				{
					memcpy ( m_pGridBody->pRec[nRow][nCol], pvData + nOffset, LEN_GRIDBODY );
					if ( nBaseVer <= 9 )
					{
						if ( m_pGridBody->pRec[nRow][nCol]->bsItem.nCtrlID == 52527 )
						{
							m_pGridBody->pRec[nRow][nCol]->bsItem.nCtrlID = dxCtrlCombo;
						}

						nOffset += ( LEN_GRIDBODY - ( REAL_ITEM_LEN + 1 ) ) ;
					}
					else if( nBaseVer <= 11 )
					{
						nOffset += ( LEN_GRIDBODY - ( REAL_ITEM_LEN + 1 ) ) ;
					}
					else
					{
						nOffset += LEN_GRIDBODY;
					}
					
				}
// <-- [Edit]  김창하 2006/04/28
			}
		}

		free ( pvData );
		return TRUE;
	}
	return FALSE;
}

//*****************************************************************************
// 루    틴    명  :  SetGridHeaderDataBlobDataChange
// 기          능  :  그리드 헤더 BLOB데이터정보를 구조체로 변한하는 함수. 
// 입          력  :  CString  strPropertyData
// 출          력  :  BOOL
// 작    성    자  :  2003년7월15일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
BOOL  CGridInfo::SetGridHeaderDataBlobDataChange( CString  strPropertyData )
{
	if ( strPropertyData.IsEmpty() )
		return FALSE;

	int nBaseVer = LOWORD(m_dwBaseVer);

	BYTE*	pvData = NULL; 
	pvData = StringToBinary( strPropertyData );
	
	ASSERT( pvData != NULL );
    if( pvData != NULL )
	{
		m_pGridHeader->Clear();

		int nTotalCount;
		int nLenGridHeader	   = sizeof(GRIDHEADER);

		DWORD cb;
		int nOffset = 0;

		ROWCOL  nRowHeaderCount = m_nHeaderRowCnt,  //GetHeaderRows(),
				nColHeaderCount = m_nHeaderColCnt;  //GetHeaderCols();

		ROWCOL nRowCount, nRowMax,
				nColCount, nColMax;
			
		nRowCount = m_nRowCnt;						// GetRowCount();
		nColCount = m_nColCnt;						// GetColCount();
		// RowHeaderCount * Column Count

		nRowMax = nRowHeaderCount * nColCount;
		nColMax = nColHeaderCount * ( nRowCount - nRowHeaderCount );

		nTotalCount		   = nRowMax + nColMax;
		ASSERT ( nTotalCount > 0 );
			
		if ( nTotalCount <= 0 )
		{
			free ( pvData );
			return FALSE;
		}
		
		DWORD dwTotalLen	   = sizeof(DWORD)+ sizeof(short) + ( nTotalCount * nLenGridHeader );

		cb = *(DWORD*)pvData;
		nOffset += sizeof(DWORD);
		ASSERT( dwTotalLen == cb);
		if ( dwTotalLen != cb )
		{
			if ( pvData )
				free ( pvData );
			return FALSE;

		}
		m_pGridHeader->dwLength = cb;

		m_pGridHeader->nCount = *(short*)(pvData + nOffset);
		nOffset += sizeof(short);

		m_pGridHeader->pRec = new GRIDHEADER*[ nTotalCount ];
		int nIndex = 0;	
		if ( nRowMax > 0 )
		{
			for ( int nRow = 1 ; nRow <= nRowHeaderCount; nRow ++ )
			{
				for ( int nCol = 1 ; nCol <= nColCount; nCol ++ )
				{
					m_pGridHeader->pRec[nIndex] = new GRIDHEADER;
					memset ( m_pGridHeader->pRec[nIndex], 0x0,				LEN_GRIDHEADER );
					memcpy ( m_pGridHeader->pRec[nIndex], pvData + nOffset, LEN_GRIDHEADER );
					if ( nBaseVer <= 9 )
					{
						if ( m_pGridHeader->pRec[nIndex]->bsItem.nCtrlID == 52527 )
						{
							m_pGridHeader->pRec[nIndex]->bsItem.nCtrlID = dxCtrlCombo;
						}
					}

					nOffset += LEN_GRIDHEADER;

					TRACE("<<<Row:Header Row=[%d],Col=[%d], Caption=[%s]\n", m_pGridHeader->pRec[nIndex]->nRow, m_pGridHeader->pRec[nIndex]->nCol, m_pGridHeader->pRec[nIndex]->szCaption );
					nIndex ++;
				}
			}
		}
		if ( nColMax > 0 )
		{
			for ( int nCol = 1 ; nCol <= nColHeaderCount; nCol ++ )
			{
				for ( int nRow = nRowHeaderCount+1 ; nRow <= nRowCount; nRow ++ )
				{
					m_pGridHeader->pRec[nIndex] = new GRIDHEADER;
						
					memset ( m_pGridHeader->pRec[nIndex], 0x0,				LEN_GRIDHEADER );
					memcpy ( m_pGridHeader->pRec[nIndex], pvData + nOffset, LEN_GRIDHEADER );
					if ( nBaseVer <= 9 )
					{
						if ( m_pGridHeader->pRec[nIndex]->bsItem.nCtrlID == 52527 )
						{
							m_pGridHeader->pRec[nIndex]->bsItem.nCtrlID = dxCtrlCombo;
						}
					}

					nOffset += LEN_GRIDHEADER;
					TRACE("<<<Col:Header Row=[%d],Col=[%d], Caption=[%s]\n", m_pGridHeader->pRec[nIndex]->nRow, m_pGridHeader->pRec[nIndex]->nCol, m_pGridHeader->pRec[nIndex]->szCaption );

					nIndex ++;
				}
			}
		}
		free ( pvData );
		return TRUE;
	}

	return FALSE;
}

//*****************************************************************************
// 루    틴    명  :  SetRealConditionDataBlobDataChange
// 기          능  :  그리드 실시간조건 BLOB데이터정보를 구조체로 변한하는 함수. 
// 입          력  :  CString  strPropertyData
// 출          력  :  BOOL
// 작    성    자  :  2004년10월120일    홍 인기 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
BOOL  CGridInfo::SetRealConditionDataBlobDataChange( CString  strPropertyData )
{
	if ( strPropertyData.IsEmpty() )
		return FALSE;

	BYTE*	pvData = NULL;
	pvData = StringToBinary( strPropertyData );
	
	ASSERT( pvData != NULL );
    if( pvData != NULL )
	{
		int		nOffset = 0;

		m_pRealCon->Clear( );

		m_pRealCon->dwLength = *(DWORD*)pvData;
		nOffset		+= sizeof(DWORD);

		m_pRealCon->nRecCount	= *(BYTE*)(pvData + nOffset);
		nOffset += sizeof(BYTE);

		m_pRealCon->nConCount	= *(BYTE*)(pvData + nOffset);
		nOffset += sizeof(BYTE);
		

		m_pRealCon->ppRecType = new REALRECTYPE*[ m_pRealCon->nRecCount ];
		BYTE nIndex;
		for ( nIndex = 0 ; nIndex < m_pRealCon->nRecCount; nIndex++ )
		{
			m_pRealCon->ppRecType[nIndex] = new REALRECTYPE;
			memset ( m_pRealCon->ppRecType[nIndex], 0x0,	LEN_REALRECTYPE );

			memcpy( m_pRealCon->ppRecType[nIndex], pvData + nOffset, LEN_REALRECTYPE);
			nOffset += LEN_REALRECTYPE;
		}
		
		m_pRealCon->ppCondition = new REALCONITEM*[ m_pRealCon->nConCount ];

		for ( /*BYTE*/ nIndex = 0 ; nIndex < m_pRealCon->nConCount; nIndex++ )
		{
			m_pRealCon->ppCondition[nIndex] = new REALCONITEM;
			memset ( m_pRealCon->ppCondition[nIndex], 0x0,	LEN_REALCONITEM );

			memcpy( m_pRealCon->ppCondition[nIndex], pvData + nOffset, LEN_REALCONITEM);
			nOffset += LEN_REALCONITEM;
		}

		free ( pvData );
		return TRUE;
	}

	return FALSE;
}

//*******************************************************************/
/*! Function Name : SerializeUserData
/*! Function      : 
/*! Param         : CArchive &ar, LPBYTE lpData, DWORD dwLen
/*! Return        : void  
/*! Create        : 김창하 , 2005/11/30
/*! Comment       : 
//******************************************************************/
void  CGridInfo::SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen )
{
    COgBase::Serialize(ar);

	ASSERT_VALID(this);
    if( !ar.IsStoring() )							// Read
	{
		if( m_pGridHeader )
		{
			m_pGridHeader->SerializeUserData(ar, lpData, dwLen );
		}
		
		if( m_pGridBody)
		{
			m_pGridBody->SerializeUserData(ar, lpData, dwLen );
		}

		if( m_pRealCon )
		{
			m_pRealCon->Serialize(ar);
		}
	}
	
}

void CGridInfo::Serialize(CArchive &ar)
{
    COgBase::Serialize(ar);

	ASSERT_VALID(this);

    if(ar.IsStoring())							// Write
    {
		if(!m_bSkip)
		{
			ar << m_nVirtualMode;
			ar << m_nSortMode;
			ar << m_nHeaderRowCnt;
			ar << m_nHeaderColCnt;
			ar << m_nSubItemCnt;
			ar << m_nBlockCount;
			ar << m_nOddColorIndex;
			ar << m_nEvenColorIndex;
			ar << m_nMaxDataCnt;
			ar << m_bUseBlockColor;
			ar << m_bUse3DButtonHeader;
			ar << m_nAllowSameKey;
			ar << m_nAllowSameSubKey;
			ar << m_nAllowSameThirdKey;
			ar << m_byHeaderMove;
			ar << m_nFixedHeaderMoveCnt;
			ar << m_nBHLineColorIndex;
			ar << m_nHVLineColorIndex;
			ar << m_nHHLineColorIndex;
			ar << m_nScrollAction;
			ar << m_bySaveColSize;
		}

		if(m_pGridHeader)
		{
			m_pGridHeader->SetVersion(m_dwBaseVer);
			m_pGridHeader->Serialize(ar);
		}
		
		if(m_pGridBody)
		{
			m_pGridBody->SetVersion(m_dwBaseVer);
			m_pGridBody->Serialize(ar);
		}
		/*
		if(m_pGridLine)
		{
			m_pGridLine->SetVersion(m_dwBaseVer);
			m_pGridLine->Serialize(ar);
		}
		*/
		if(m_pRealCon)
		{
			m_pRealCon->SetVersion(m_dwBaseVer);
			m_pRealCon->Serialize(ar);
		}
		
	}
    else										// Read
    {
		if(!m_bSkip)
		{
			ar >> m_nVirtualMode;
			ar >> m_nSortMode;
			ar >> m_nHeaderRowCnt;
			ar >> m_nHeaderColCnt;
			ar >> m_nSubItemCnt;
			ar >> m_nBlockCount;
			ar >> m_nOddColorIndex;
			ar >> m_nEvenColorIndex;
			ar >> m_nMaxDataCnt;
			ar >> m_bUseBlockColor;
			ar >> m_bUse3DButtonHeader;
			ar >> m_nAllowSameKey;
			ar >> m_nAllowSameSubKey;
			ar >> m_nAllowSameThirdKey;
			ar >> m_byHeaderMove;
			ar >> m_nFixedHeaderMoveCnt;
			ar >> m_nBHLineColorIndex;
			ar >> m_nHVLineColorIndex;
			ar >> m_nHHLineColorIndex;
			ar >> m_nScrollAction;
			ar >> m_bySaveColSize;
		}
		
		if(m_pGridHeader)
		{
			m_pGridHeader->Serialize(ar);
		}
		
		if(m_pGridBody)
		{
			m_pGridBody->Serialize(ar);
		}

		/*
		if(m_pGridLine)
		{
			//m_pGridLine->SetVersion(m_dwBaseVer);
			m_pGridLine->Serialize(ar);
		}
		*/

		if(m_pRealCon)
		{
			m_pRealCon->Serialize(ar);
		}
    }
};

void CGridInfo::CopyVariable( const CGridInfo& other )
{
	COgBase::CopyVariable( other );

	m_nVirtualMode			=	other.m_nVirtualMode;
	m_nSortMode				=	other.m_nSortMode;
	m_nHeaderRowCnt			=	other.m_nHeaderRowCnt;
	m_nHeaderColCnt			=	other.m_nHeaderColCnt;
	m_nSubItemCnt			=	other.m_nSubItemCnt;
	m_nBlockCount			=	other.m_nBlockCount;
	m_nOddColorIndex		=	other.m_nOddColorIndex;
	m_nEvenColorIndex		=	other.m_nEvenColorIndex;
	m_nMaxDataCnt			=	other.m_nMaxDataCnt;
	m_nScrollAction			=   other.m_nScrollAction;

	m_bUseBlockColor		=	other.m_bUseBlockColor;
	m_bUse3DButtonHeader	=	other.m_bUse3DButtonHeader;
	m_nAllowSameKey			=	other.m_nAllowSameKey;
	m_nAllowSameSubKey		=	other.m_nAllowSameSubKey;
	m_nAllowSameThirdKey	=	other.m_nAllowSameThirdKey;
	m_byHeaderMove			=	other.m_byHeaderMove;
	m_nFixedHeaderMoveCnt	=	other.m_nFixedHeaderMoveCnt;
	m_nBHLineColorIndex		=	other.m_nBHLineColorIndex;
	m_nHVLineColorIndex		=	other.m_nHVLineColorIndex;
	m_nHHLineColorIndex		=	other.m_nHHLineColorIndex;
	m_bySaveColSize			=	other.m_bySaveColSize;

}

const CGridInfo& CGridInfo::operator=(const CGridInfo& other)
{
	if (&other == this)
		return *this;

	COgBase::operator=(other);

	if(other.m_pGridHeader)
		*m_pGridHeader		=	*other.m_pGridHeader;
	
	if(other.m_pGridBody)
		*m_pGridBody		=	*other.m_pGridBody;

	//m_pGridLine			=	other.m_pGridLine;

	if(other.m_pRealCon)
		*m_pRealCon			=	*other.m_pRealCon;
	
	return *this;
}

void CGridInfo::SetBoolBit(const long lBoolBit)
{
	if( lBoolBit & BBIT_USE_SCLDWRQST  )
		m_nScrollAction = TRUE;
	else
		m_nScrollAction = FALSE;

	if( lBoolBit & BBIT_USE_BLOCKCOLOR )
		m_bUseBlockColor = TRUE;
	else
		m_bUseBlockColor = FALSE;

	if( lBoolBit & BBIT_USE_VIRTUAL_STEP1 )
		m_nVirtualMode = dxVMStep1;
	else if( lBoolBit & BBIT_USE_VIRTUAL_STEP2 )
		m_nVirtualMode = dxVMStep2;
	else
		m_nVirtualMode = dxVMNone;

	if( lBoolBit & BBIT_USE_3DHEADER  )
		m_bUse3DButtonHeader = dxH3DStyle;			// 3d Header
	else if ( lBoolBit & BBIT_USE_ROUNDHEADER  )
		m_bUse3DButtonHeader = dxHRoundStyle;		// Round Header
	else
		m_bUse3DButtonHeader = dxHNormal;			// Normal
	
	if( lBoolBit & BBIT_USE_SAMEKEY  )
		m_nAllowSameKey = TRUE;
	else
		m_nAllowSameKey = FALSE;

	if( lBoolBit & BBIT_USE_SAMESUBKEY  )
		m_nAllowSameSubKey = TRUE;
	else
		m_nAllowSameSubKey = FALSE;

	if( lBoolBit & BBIT_USE_SAMETHIRDKEY  )
		m_nAllowSameThirdKey = TRUE;
	else
		m_nAllowSameThirdKey = FALSE;
	
	if( lBoolBit & BBIT_USE_HEADERMOVE  )
		m_byHeaderMove = TRUE;
	else
		m_byHeaderMove = FALSE;

	if( lBoolBit & BBIT_USE_SAVE_COLSIZE )
		m_bySaveColSize = TRUE;
	else
		m_bySaveColSize = FALSE;

	
}

const long CGridInfo::GetBoolBit()
{
	long lBoolBit(0);

	if( m_nScrollAction )
		lBoolBit |= BBIT_USE_SCLDWRQST;

	if( m_bUseBlockColor )
		lBoolBit |= BBIT_USE_BLOCKCOLOR;
	
	if( m_nVirtualMode == dxVMStep1 )
		lBoolBit |= BBIT_USE_VIRTUAL_STEP1;
	else if( m_nVirtualMode == dxVMStep2 )
		lBoolBit |= BBIT_USE_VIRTUAL_STEP2;
	
	// Header Style
	if( m_bUse3DButtonHeader == dxH3DStyle )
		lBoolBit |= BBIT_USE_3DHEADER;
	else if ( m_bUse3DButtonHeader == dxHRoundStyle )
		lBoolBit |= BBIT_USE_ROUNDHEADER;
	
	if( m_nAllowSameKey )
		lBoolBit |= BBIT_USE_SAMEKEY;

	if( m_nAllowSameSubKey )
		lBoolBit |= BBIT_USE_SAMESUBKEY;

	if( m_nAllowSameThirdKey )
		lBoolBit |= BBIT_USE_SAMETHIRDKEY;
	

	if( m_byHeaderMove )
		lBoolBit |= BBIT_USE_HEADERMOVE;

	if( m_bySaveColSize )
		lBoolBit |= BBIT_USE_SAVE_COLSIZE;

	return lBoolBit;
}


//*******************************************************************/
/*! Function Name : GetDumpText
/*! Function      : 셀 정보 내용을 표시하는 함수 
/*! Param         : int nOption
/*! Return        : 
/*! Create        : 김창하 , 2006/05/10
/*! Comment       : 
//******************************************************************/
CString	CGridInfo::GetDumpText( int nOption  )
{
	CString strText,
			strBuf;
	
	GRIDBODY*	pRec	  = NULL;
	int nItemCount	  = m_pGridBody->nItemCount,
		nSubItemCount = m_pGridBody->nSubItemCount;

	for ( int nInfoRow = 0 ; nInfoRow < nSubItemCount ; nInfoRow ++ )
	{
		for ( int nInfoCol = 0 ; nInfoCol < nItemCount; nInfoCol ++ )
		{
			pRec = m_pGridBody->pRec[nInfoRow][nInfoCol];
			strBuf.Format ( "Pos=[%d],	OrgPos=[%d],    Item=[%s]\r\n", pRec->nPos,	pRec->nOrgPos, pRec->szItem );
			strText +=  strBuf;	
		}
	}
	return strText;
}

//*****************************************************************************
// 루    틴    명  :  SetItemValueChange
// 기          능  :  
// 입          력  :  없음
// 출          력  :  없음
// 작    성    자  :  2003년9월20일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
int   CGridInfo::SetItemValueChange( short nKeyIndex, 
								   LPCTSTR lpOldItem, 
								   LPCTSTR lpNewItem, 
								   int&		nRecRow,
								   int&		nRecCol,
								   int nControlMode /*= dxHGrid */)
{
	GRIDBODY*	pRec	  = NULL;
	int nItemCount	  = m_pGridBody->nItemCount,
		nSubItemCount = m_pGridBody->nSubItemCount;

	for ( int nInfoRow = 0 ; nInfoRow < nSubItemCount ; nInfoRow ++ )
	{
		for ( int nInfoCol = 0 ; nInfoCol < nItemCount; nInfoCol ++ )
		{
			pRec = m_pGridBody->pRec[nInfoRow][nInfoCol];
			if ( pRec->szItem[0] != 0x00 &&
				_stricmp( pRec->szItem, lpOldItem ) == 0 && 
				pRec->nKeyIndex == nKeyIndex )
			{
				sprintf ( pRec->szItem, lpNewItem );
				nRecRow = nInfoRow;
				nRecCol = nInfoCol;
				
				if ( pRec->ItemBits.nItemFlag == dxItemNotUse ||
					pRec->ItemBits.nItemFlag == dxItemIn )
					return -1;

				return pRec->nPos;													// Col Pos
			}
		}
	}

#if FALSE
	if ( nControlMode == dxHGrid )													// 가로 그리드 : Column Count
	{
		for ( int nCol = 0 ; nCol < m_pGridBody->nItemCount; nCol ++ )				// Column Count
		{
			for ( int nRow = 0 ; nRow < m_pGridBody->nSubItemCount; nRow ++ )		// SubRow Count
			{
				if ( m_pGridBody->pRec[nRow][nCol]->szItem[0] != 0x00 &&
					_stricmp( m_pGridBody->pRec[nRow][nCol]->szItem, lpOldItem ) == 0 && 
					m_pGridBody->pRec[nRow][nCol]->nKeyIndex == nKeyIndex )
				{
					sprintf ( m_pGridBody->pRec[nRow][nCol]->szItem, lpNewItem );
					nRecRow = nRow;
					nRecCol = nCol;
					
					if ( m_pGridBody->pRec[nRow][nCol]->ItemBits.nItemFlag == dxItemNotUse ||
						m_pGridBody->pRec[nRow][nCol]->ItemBits.nItemFlag == dxItemIn )
						return -1;

					return m_pGridBody->pRec[nRow][nCol]->nPos;						// Col Pos
				}
				
			}
		}
	} 
	else if ( nControlMode == dxVGrid )												// 세로 그리드. 
	{
		for ( int nRow = 0 ; nRow < m_pGridBody->nItemCount; nRow ++ )				// Row Count
		{
			for ( int nCol = 0 ; nCol < m_pGridBody->nSubItemCount; nCol ++ )		// SubColumCount
			{
				if ( m_pGridBody->pRec[nCol][nRow]->szItem[0] != 0x00 &&
					_stricmp( m_pGridBody->pRec[nCol][nRow]->szItem, lpOldItem ) == 0 && 
					m_pGridBody->pRec[nCol][nRow]->nKeyIndex == nKeyIndex )
				{
					sprintf ( m_pGridBody->pRec[nCol][nRow]->szItem, lpNewItem );
					nRecRow = nRow;
					nRecCol = nCol;

					if ( m_pGridBody->pRec[nCol][nRow]->ItemBits.nItemFlag == dxItemNotUse ||
						m_pGridBody->pRec[nCol][nRow]->ItemBits.nItemFlag == dxItemIn )
						return -1;

					return m_pGridBody->pRec[nCol][nRow]->nPos;					// Row Pos
				}
			}
		}
	}
#endif
	return -1;
}


//*****************************************************************************
// 루    틴    명  :  GetPosFromItemValue
// 기          능  :  
// 입          력  :  없음.
// 출          력  :  없음.
// 작    성    자  :  2003년8월28일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
int CGridInfo::GetPosFromItemValue(short nKeyIndex, 
								   LPCTSTR lpItem,
								   short nItemFlag /*= -1*/,
								   int nControlMode /*= dxHGrid*/ )
{
	GRIDBODY*	pRec	  = NULL;
	int nItemCount	  = m_pGridBody->nItemCount,
		nSubItemCount = m_pGridBody->nSubItemCount;

	for ( int nInfoRow = 0 ; nInfoRow < nSubItemCount ; nInfoRow ++ )
	{
		for ( int nInfoCol = 0 ; nInfoCol < nItemCount; nInfoCol ++ )
		{
			pRec = m_pGridBody->pRec[nInfoRow][nInfoCol];
			if ( pRec->szItem[0] != 0x00 &&
				_stricmp( pRec->szItem, lpItem ) == 0 && 
				pRec->nKeyIndex == nKeyIndex )
			{
				if ( nItemFlag != -1 && pRec->ItemBits.nItemFlag != nItemFlag )
				{
					pRec->ItemBits.nItemFlag = nItemFlag;
				}
				return pRec->nPos;													// Col Pos
			}
		}
	}

#if FALSE
	if ( nControlMode == dxHGrid )													// 가로 그리드 : Column Count
	{
		for ( int nCol = 0 ; nCol < m_pGridBody->nItemCount; nCol ++ )				// Column Count
		{
			for ( int nRow = 0 ; nRow < m_pGridBody->nSubItemCount; nRow ++ )		// SubRow Count
			{
				if ( m_pGridBody->pRec[nRow][nCol]->szItem[0] != 0x00 &&
					_stricmp( m_pGridBody->pRec[nRow][nCol]->szItem, lpItem ) == 0 && 
					m_pGridBody->pRec[nRow][nCol]->nKeyIndex == nKeyIndex )
				{
					if ( nItemFlag != -1 && m_pGridBody->pRec[nRow][nCol]->ItemBits.nItemFlag != nItemFlag )
					{
						m_pGridBody->pRec[nRow][nCol]->ItemBits.nItemFlag = nItemFlag;
					}

					return m_pGridBody->pRec[nRow][nCol]->nPos;					// Col Pos
				}
				
			}
		}
	} 
	else if ( nControlMode == dxVGrid )												// 세로 그리드. 
	{
		for ( int nRow = 0 ; nRow < m_pGridBody->nItemCount; nRow ++ )				// Row Count
		{
			for ( int nCol = 0 ; nCol < m_pGridBody->nSubItemCount; nCol ++ )		// SubColumCount
			{
				if ( m_pGridBody->pRec[nCol][nRow]->szItem[0] != 0x00 &&
					_stricmp( m_pGridBody->pRec[nCol][nRow]->szItem, lpItem ) == 0 && 
					m_pGridBody->pRec[nCol][nRow]->nKeyIndex == nKeyIndex )
				{
					if ( nItemFlag != -1 && m_pGridBody->pRec[nCol][nRow]->ItemBits.nItemFlag != nItemFlag )
					{
						m_pGridBody->pRec[nCol][nRow]->ItemBits.nItemFlag = nItemFlag;
					}

					return m_pGridBody->pRec[nCol][nRow]->nPos;					// Row Pos
				}
			}
		}
	}
#endif
	return -1;
}

BOOL CGridInfo::CanMove(BOOL bMoveCol /*= TRUE*/)
{
//	if( m_byHeaderMove == FALSE )
//		return FALSE;
//	if( m_pGridBody->GetKeyIndexCount() > 1 )
//		return FALSE;

	switch(m_nGridMode)
	{
	case dxHGrid:
		if( bMoveCol )
		{
			if( m_bUseFormula )
			{
				TRACE("Formular 사용중이므로 컬럼이동 지원하지 않습니다. \n");
				return FALSE;
			}
		}
		else
		{
			TRACE("컬럼이동 불가한 컬럼입니다. \n");
			return FALSE;
		}
		break;
	case dxVGrid:
		if( !bMoveCol )
		{
			if( m_bUseFormula )
			{
				TRACE("Formular 사용중이므로 컬럼이동 지원하지 않습니다. \n");
				return FALSE;
			}
		}
		else
		{
			TRACE("컬럼이동 불가한 컬럼입니다. \n");
			return FALSE;
		}
		break;
	}

	return TRUE;
}

BOOL CGridInfo::CanInsert(DWORD& nAddIndex, DWORD& nAddCount, BOOL bInsertCol /*= TRUE*/)
{
	switch(m_nGridMode)
	{
	case dxHGrid:
		if( bInsertCol )
		{
			if( m_bUseFormula )
				return FALSE;
			
			if( nAddIndex <= m_nHeaderColCnt )
				nAddIndex = m_nHeaderColCnt+1;

			if( nAddIndex < 0 || nAddIndex > m_nColCnt )
				nAddIndex = m_nColCnt+1;

			if( nAddCount <= 0 )
				nAddCount = 1;
		}
		else
		{
			return FALSE;
		}
		break;
	case dxVGrid:
		if( !bInsertCol )
		{
			if( m_bUseFormula )
				return FALSE;

			if( nAddIndex <= m_nHeaderRowCnt )
				nAddIndex = m_nHeaderRowCnt+1;

			if( nAddIndex < 0 || nAddIndex > m_nRowCnt )
				nAddIndex = m_nRowCnt+1;
			
			if( nAddCount <= 0 )
				nAddCount = 1;
		}
		else
		{
			return FALSE;
		}
		break;
	}
	
	return TRUE;
}

BOOL CGridInfo::CanRemove(DWORD& nDelIndex, DWORD& nDelCount, BOOL bRemoveCol /*= TRUE*/)
{
	switch(m_nGridMode)
	{
	case dxHGrid:
		if( bRemoveCol )
		{
			if( m_bUseFormula )
				return FALSE;
			
			if( nDelIndex <= m_nHeaderColCnt )
				nDelIndex = m_nHeaderColCnt+1;

			if( nDelIndex < 0  )
				nDelIndex = 1;
			
			if( nDelIndex > m_nColCnt )
				nDelIndex = m_nColCnt;

			if( nDelIndex + nDelCount > m_nColCnt )
				nDelCount = m_nColCnt - nDelIndex +1;
		}
		else
		{
			return FALSE;
		}
		break;
	case dxVGrid:
		if( !bRemoveCol )
		{
			if( m_bUseFormula )
				return FALSE;
			
			if( nDelIndex <= m_nHeaderRowCnt )
				nDelIndex = m_nHeaderRowCnt+1;

			if( nDelIndex < 0  )
				nDelIndex = 1;
			
			if( nDelIndex > m_nRowCnt )
				nDelIndex = m_nRowCnt;

			if( nDelIndex + nDelCount > m_nRowCnt )
				nDelCount = m_nRowCnt - nDelIndex+1;
		}
		else
		{
			return FALSE;
		}
		break;
	}

	return TRUE;
}

BOOL CGridInfo::CanCopy(DWORD& nSrcFrom, DWORD& nSrcTo, DWORD& nDestFrom, DWORD& nDestTo, BOOL bCopyCol /*= TRUE*/)
{
	switch(m_nGridMode)
	{
	case dxHGrid:
		if( bCopyCol )
		{
			if( m_bUseFormula )
				return FALSE;

			if( nSrcFrom > nSrcTo || nDestFrom > nDestTo /*|| nSrcFrom > nDestFrom || nSrcTo >= nDestFrom*/ )
				return FALSE;

			if( nSrcFrom <= m_nHeaderColCnt )
				nSrcFrom = m_nHeaderColCnt+1;

			if( nDestFrom > m_nColCnt )
				nDestFrom = m_nColCnt;

			if( (nSrcTo - nSrcFrom) != (nDestTo - nDestFrom) )
				return FALSE;
		}
		else
		{
			return FALSE;
		}
		break;
	case dxVGrid:
		if( !bCopyCol )
		{
			if( m_bUseFormula )
				return FALSE;

			if( nSrcFrom > nSrcTo || nDestFrom > nDestTo /*|| nSrcFrom > nDestFrom || nSrcTo >= nDestFrom*/ )
				return FALSE;

			if( nSrcFrom <= m_nHeaderRowCnt )
				nSrcFrom = m_nHeaderRowCnt+1;

			if( nDestFrom > m_nRowCnt )
				nDestFrom = m_nRowCnt;

			if( (nSrcTo - nSrcFrom) != (nDestTo - nDestFrom) )
				return FALSE;
		}
		else
		{
			return FALSE;
		}
		break;
	}

	return TRUE;
}

// Moving Colums or Rows
BOOL CGridInfo::Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol /*= TRUE*/)
{
	//----------예외 처리--------------//
	if( !CanMove(bMoveCol) )
		return FALSE;

	if( nFrom <= 0 || nDest <= 0 || nFrom == nDest)
		return FALSE;

	if( bMoveCol )
	{
		if(nFrom > m_nColCnt || nDest > m_nColCnt )
			return FALSE;
	}
	else
	{
		if(nFrom > m_nRowCnt || nDest > m_nRowCnt )
			return FALSE;
	}
	//----------예외 처리--------------//

	// Base Info Move
	COgBase::Move(nFrom, nDest, bMoveCol);
	
	// Grid Info Move
	if( m_pGridHeader )
	{
		//m_pGridHeader->SetGridCntInfo(m_nRowCnt, m_nColCnt, m_nHeaderRowCnt, m_nHeaderColCnt);
		m_pGridHeader->Move( nFrom, nDest, bMoveCol );
	}

	if( m_pGridBody )
	{
		//m_pGridBody->SetGridCntInfo(m_nRowCnt, m_nColCnt, m_nHeaderRowCnt, m_nHeaderColCnt);
		m_pGridBody->Move( nFrom, nDest, bMoveCol );
	}

	return TRUE;

}

// Insert Columns Or Rows
BOOL CGridInfo::Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol /*= TRUE*/)
{
	//----------예외 처리--------------//
//	if( !CanInsert(nAddIndex, nAddCount, bInsertCol) )
//		return FALSE;
	//----------예외 처리--------------//

	// Base Info Insert
	COgBase::Insert(nAddIndex, nAddCount, bInsertCol);
	
	// Grid Info Insert
	if( m_pGridHeader )
	{
		m_pGridHeader->Insert(nAddIndex, nAddCount, bInsertCol);
	}

	if( m_pGridBody )
	{
		m_pGridBody->Insert(nAddIndex, nAddCount, bInsertCol);
	}

	// Update Grid Info
	if( bInsertCol )
	{
		m_nColCnt += nAddCount;
	}
	else
	{
		m_nRowCnt += nAddCount;
	}

	return TRUE;
}

// Remove Columns Or Rows
BOOL CGridInfo::Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol /*= TRUE*/)
{
	//----------예외 처리--------------//
//	if( !CanRemove(nDelIndex, nDelCount, bRemoveCol) )
//		return FALSE;
	//----------예외 처리--------------//

	// Base Info Remove
	COgBase::Remove(nDelIndex, nDelCount, bRemoveCol);
	
	// Grid Info Remove
	if( m_pGridHeader )
	{
		m_pGridHeader->Remove(nDelIndex, nDelCount, bRemoveCol);
	}

	if( m_pGridBody )
	{
		m_pGridBody->Remove(nDelIndex, nDelCount, bRemoveCol);
	}

	// Update Grid Info
	if( bRemoveCol )
	{
		m_nColCnt -= nDelCount;
		m_nFrozenColCnt  = min(m_nFrozenColCnt, m_nColCnt);
		m_nHiddenColCnt  = min(m_nHiddenColCnt, m_nColCnt);
	}
	else
	{
		m_nRowCnt -= nDelCount;
		m_nFrozenRowCnt  = min(m_nFrozenRowCnt, m_nRowCnt);
		m_nHiddenRowCnt  = min(m_nHiddenRowCnt, m_nColCnt);
	}

	return TRUE;
}

// Copy Columns Or Rows
BOOL CGridInfo::Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol /*= TRUE*/)
{
	//----------예외 처리--------------//
//	if( !CanCopy(nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol) )
//		return FALSE;
	//----------예외 처리--------------//

	// Base Info Insert
	COgBase::Copy(nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol);
	
	// Grid Info Insert
	if( m_pGridHeader )
	{
		m_pGridHeader->Copy(nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol);
	}

	if( m_pGridBody )
	{
		m_pGridBody->Copy(nSrcFrom, nSrcTo, nDestFrom, nDestTo, bCopyCol);
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// 실시간 조건 클래스 구현부.
IMPLEMENT_SERIAL(CRealCondition, CObject, 1)

CRealCondition::CRealCondition() 
{ 
	dwLength	= 0;
	nRecCount	= 0;
	nConCount	= 0;
	ppRecType	= NULL;
	ppCondition	= NULL;
	m_dwVersion = DEF_VERSION;
	m_pGrid		= NULL;
};

CRealCondition::~CRealCondition() 
{

};

const CRealCondition& CRealCondition::operator=(const CRealCondition& other)
{
	if ( &other == this)
		return *this;

	Clear();

	dwLength		= other.dwLength;
	nRecCount		= other.nRecCount;
	nConCount		= other.nConCount;
	m_dwVersion		= other.m_dwVersion;
    BYTE nIndex;
	if(nRecCount > 0)
	{
		ppRecType = new REALRECTYPE*[nRecCount];
		
		for ( nIndex = 0 ; nIndex < nRecCount; nIndex ++ )
		{
			ppRecType[nIndex] = new REALRECTYPE;
			
			if ( ppRecType[nIndex] )
			{
				memcpy(ppRecType[nIndex], other.ppRecType[nIndex], LEN_REALRECTYPE);
			}
		}
	}

	if(nConCount > 0)
	{
		ppCondition = new REALCONITEM*[nConCount];
		
		for ( nIndex = 0 ; nIndex < nConCount; nIndex ++ )
		{
			ppCondition[nIndex] = new REALCONITEM;
			
			if ( ppCondition[nIndex] )
			{
				memcpy(ppCondition[nIndex], other.ppCondition[nIndex], LEN_REALCONITEM);
			}
		}
	}

	return *this;
}

void CRealCondition::Clear()
{
	BYTE nIndex;
	for ( nIndex = 0 ; nIndex < nRecCount; nIndex ++ )
	{
		if(ppRecType[nIndex])
		{
			delete  ppRecType[nIndex];
		}
	}

	if(ppRecType)
	{
		delete[] ppRecType;
		ppRecType = NULL;
	}

	nRecCount = 0;

	for ( /*BYTE*/ nIndex = 0 ; nIndex < nConCount; nIndex ++ )
	{
		if( ppCondition[nIndex])
		{
#ifdef _DEBUG
			if( ppCondition[nIndex]->lDummy )
			{
				ASSERT(FALSE);
			}
#endif

			delete  ppCondition[nIndex];
		}
	}

	if(ppCondition)
	{
		delete[] ppCondition;
		ppCondition = NULL;
	}

	nConCount = 0;
}

void CRealCondition::Serialize(CArchive &ar)
{
	BYTE nIndex;
	if( ar.IsStoring() )							// Write
	{
		ar << dwLength;
		ar << nRecCount;
		ar << nConCount;
		ar << m_dwVersion;

		for ( nIndex = 0 ; nIndex < nRecCount; nIndex ++ )
		{
			if ( ppRecType[nIndex] )
			{
				ar << ppRecType[nIndex]->byRec;
				ar << ppRecType[nIndex]->byDefAction;
				ar << ppRecType[nIndex]->nConIndex;
				// Dummy for REALRECTYPE
				//ar << ppRecType[nIndex]->lDummy;
				SerializeRECTYPEBITS(ar, ppRecType[nIndex]->RTBits);
			}
		}

		for ( /*BYTE*/ nIndex = 0 ; nIndex < nConCount; nIndex ++ )
		{
			if ( ppCondition[nIndex] )
			{
				ar << ppCondition[nIndex]->byRec;
				ar << (BYTE) lstrlen(ppCondition[nIndex]->szItem);
				ar.WriteString((LPCTSTR) ppCondition[nIndex]->szItem);
				ar << (BYTE) lstrlen(ppCondition[nIndex]->szValue);
				ar.WriteString((LPCTSTR) ppCondition[nIndex]->szValue);
				SerializeREALCONBITS(ar, ppCondition[nIndex]->RConBits);	
				// Dummy for REALCONITEM
				ar << ppCondition[nIndex]->lDummy;
#ifdef _DEBUG
				if( ppCondition[nIndex]->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
	}
	else
	{
		Clear();
		DWORD dwReadVersion;
		
		ar >> dwLength;
		ar >> nRecCount;
		ar >> nConCount;
		ar >> dwReadVersion;

		ppRecType = new REALRECTYPE*[nRecCount];
		for ( nIndex = 0 ; nIndex < nRecCount; nIndex ++ )
		{
			ppRecType[nIndex] = new REALRECTYPE;

			if ( ppRecType[nIndex] )
			{
				ar >> ppRecType[nIndex]->byRec;
				ar >> ppRecType[nIndex]->byDefAction;
				ar >> ppRecType[nIndex]->nConIndex;
				// Dummy for REALRECTYPE
				//ar >> ppRecType[nIndex]->lDummy;
				SerializeRECTYPEBITS(ar, ppRecType[nIndex]->RTBits);

			}
		}


		BYTE byReadLen;
		ppCondition = new REALCONITEM*[nConCount];
		for ( /*BYTE*/ nIndex = 0 ; nIndex < nConCount; nIndex ++ )
		{
			ppCondition[nIndex] = new REALCONITEM;

			if ( ppCondition[nIndex] )
			{
				ar >> ppCondition[nIndex]->byRec;
				ar >> byReadLen;
				ar.Read( ppCondition[nIndex]->szItem, byReadLen);
				ppCondition[nIndex]->szItem[byReadLen] = 0x00;
				ar >> byReadLen;
				ar.Read( ppCondition[nIndex]->szValue, byReadLen);
				ppCondition[nIndex]->szValue[byReadLen] = 0x00;
				SerializeREALCONBITS(ar, ppCondition[nIndex]->RConBits);
				// Dummy for REALCONITEM
				ar >> ppCondition[nIndex]->lDummy;
#ifdef _DEBUG
				if( ppCondition[nIndex]->lDummy )
				{
					ASSERT(FALSE);
				}
#endif
			}
		}
	}
}

//*******************************************************************
//  FUNCTION:   - GetRealRecType
//  RETURNS:    - REALRECTYPE 의 포인터 ( 하나의 실시간 레코드별 정보)
//  PARAMETERS: - byRec  : 실시간 레코드 구분자.
//  COMMENTS:   - 하나의 실시간 레코드별 정보를 구한다.
//*******************************************************************
REALRECTYPE* CRealCondition::GetRealRecType(BYTE byRec)
{
	BYTE nIndex;
	for ( nIndex = 0 ; nIndex < nRecCount; nIndex ++ )
	{
		if ( ppRecType[nIndex] )
		{
			if( ppRecType[nIndex]->byRec == byRec)
				return ppRecType[nIndex];
		}
	}

	// 못찻은 경우.
//	ASSERT(FALSE);
	return NULL;
}

//*******************************************************************
//  FUNCTION:   - GetRealCondition
//  RETURNS:    - REALCONITEM 의 포인터 ( 하나의 컨디션 정보)
//  PARAMETERS: - nIndex : 인덱스.
//  COMMENTS:   - 하나의 실시간 조건을 구한다.
//*******************************************************************
REALCONITEM* CRealCondition::GetRealCondition(short nIndex /*= 0*/)
{
	if( nIndex < 0 || nIndex >= nConCount )
	{
		ASSERT(FALSE);
		return NULL;
	}
	
	return ppCondition[nIndex];
}


//////////////////////////////////////////////////////////////////////////
// New 참조 클래스 구현부.
IMPLEMENT_SERIAL(CNewRefer, CObject, 1)

CNewRefer::CNewRefer() 
{ 
	nCount		= 0;
	ppNRType	= NULL;
	m_dwVersion = DEF_VERSION;
};

CNewRefer::~CNewRefer() 
{

};

const CNewRefer& CNewRefer::operator=(const CNewRefer& other)
{
	if ( &other == this)
		return *this;

	Clear();

	nCount			= other.nCount;
	m_dwVersion		= other.m_dwVersion;
	BYTE nIndex,
		 nSubIndex;
	if(nCount > 0)
	{
		ppNRType = new NEWREFERTYPE*[nCount];
		
		for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			ppNRType[nIndex] = new NEWREFERTYPE;
			
			if ( ppNRType[nIndex] )
			{
				strcpy(ppNRType[nIndex]->szItem, other.ppNRType[nIndex]->szItem);
				ppNRType[nIndex]->nKeyIndex	= other.ppNRType[nIndex]->nKeyIndex;
				ppNRType[nIndex]->nCount	= other.ppNRType[nIndex]->nCount;
				ppNRType[nIndex]->ppNRCon	= NULL;
				
				if(ppNRType[nIndex]->nCount > 0) 
				{
					ppNRType[nIndex]->ppNRCon = new NEWREFERCON*[ppNRType[nIndex]->nCount];
					
					for( nSubIndex = 0; nSubIndex < ppNRType[nIndex]->nCount; nSubIndex++)
					{
						ppNRType[nIndex]->ppNRCon[nSubIndex] = new NEWREFERCON;

						if(ppNRType[nIndex]->ppNRCon[nSubIndex])
						{
							memcpy(ppNRType[nIndex]->ppNRCon[nSubIndex], other.ppNRType[nIndex]->ppNRCon[nSubIndex], LEN_NEWREFERCON);
						}
					}

				}

// --> [Edit]  김창하 2006/06/30
				ppNRType[nIndex]->nTop	   = other.ppNRType[nIndex]->nTop;
				ppNRType[nIndex]->nLeft	   = other.ppNRType[nIndex]->nLeft;
				ppNRType[nIndex]->nBottom  = other.ppNRType[nIndex]->nBottom;
				ppNRType[nIndex]->nRight   = other.ppNRType[nIndex]->nRight;
/*
				ppNRType[nIndex]->lDummy = other.ppNRType[nIndex]->lDummy;
				if(ppNRType[nIndex]->lDummy)
				{
					ASSERT(FALSE);
				}
*/
// <-- [Edit]  김창하 2006/06/30
				
			}
		}
	}

	return *this;
}

void CNewRefer::Clear()
{
	BYTE nIndex,
		 nSubIndex;
	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if ( ppNRType[nIndex] )
		{
			for( nSubIndex = 0; nSubIndex < ppNRType[nIndex]->nCount; nSubIndex++)
			{
				if(ppNRType[nIndex]->ppNRCon[nSubIndex])
				{
//					if( ppNRType[nIndex]->ppNRCon[nSubIndex]->lTgtCharValue )
//					{
//						ASSERT(FALSE);
//					}
					delete ppNRType[nIndex]->ppNRCon[nSubIndex];
					ppNRType[nIndex]->ppNRCon[nSubIndex] = NULL;
				}
			}

			if(ppNRType[nIndex]->ppNRCon)
			{
				delete[] ppNRType[nIndex]->ppNRCon;
				ppNRType[nIndex]->ppNRCon = NULL;
			}

// --> [Edit]  김창하 2006/06/30
//#ifdef _DEBUG
//			if( ppNRType[nIndex]->lDummy )
//			{
//				ASSERT(FALSE);
//			}
//#endif
// <-- [Edit]  김창하 2006/06/30
			delete  ppNRType[nIndex];
			ppNRType[nIndex] = NULL;
		}
	}

	if(ppNRType)
	{
		delete[] ppNRType;
		ppNRType = NULL;
	}

	nCount = 0;
}

void CNewRefer::Serialize(CArchive &ar)
{
	BYTE nIndex,
		 nSubIndex;
	if( ar.IsStoring() )							// Write
	{
		ar << nCount;
		ar << m_dwVersion;

		for (  nIndex = 0 ; nIndex < nCount; nIndex ++ )
		{
			if ( ppNRType[nIndex] )
			{
				ar << (BYTE) strlen( ppNRType[nIndex]->szItem );
				ar.WriteString( ppNRType[nIndex]->szItem );
				ar << ppNRType[nIndex]->nKeyIndex;
				ar << ppNRType[nIndex]->nCount;
				
				for( nSubIndex = 0; nSubIndex < ppNRType[nIndex]->nCount; nSubIndex++)
				{
					if(ppNRType[nIndex]->ppNRCon[nSubIndex])
					{
						SerializeNEWREFERBITS(ar, ppNRType[nIndex]->ppNRCon[nSubIndex]->NRBits);
						ar << (BYTE) strlen( ppNRType[nIndex]->ppNRCon[nSubIndex]->szTgtItem);
						ar.WriteString( ppNRType[nIndex]->ppNRCon[nSubIndex]->szTgtItem );
						ar << ppNRType[nIndex]->ppNRCon[nSubIndex]->dTgtConstant;
						ar << (BYTE) strlen( ppNRType[nIndex]->ppNRCon[nSubIndex]->szSymbol);
						ar.WriteString( ppNRType[nIndex]->ppNRCon[nSubIndex]->szSymbol );
						ar << ppNRType[nIndex]->ppNRCon[nSubIndex]->lTgtCharValue;
//#ifdef _DEBUG
//						if( ppNRType[nIndex]->ppNRCon[nSubIndex]->lTgtCharValue )
//						{
//							ASSERT(FALSE);
//						}
//#endif
					}

				}
// --> [Edit]  김창하 2006/06/30
				ar << ppNRType[nIndex]->nTop;
				ar << ppNRType[nIndex]->nLeft;
				ar << ppNRType[nIndex]->nBottom;
				ar << ppNRType[nIndex]->nRight;
//				ar << ppNRType[nIndex]->lDummy;
//				if( ppNRType[nIndex]->lDummy )
//				{
//					ASSERT(FALSE);
//				}
// <-- [Edit]  김창하 2006/06/30
			}
		}

	}
	else
	{
		Clear();
		DWORD dwReadVersion;
		BYTE	byReadLen;
		
		ar >> nCount;
		ar >> dwReadVersion;

		if( nCount > 0 )
		{
			ppNRType = new NEWREFERTYPE*[nCount];
			
			for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
			{
				ppNRType[nIndex] = new NEWREFERTYPE;
				
				if ( ppNRType[nIndex] )
				{
					ar >> byReadLen;
					ar.Read( ppNRType[nIndex]->szItem, byReadLen);
					ppNRType[nIndex]->szItem[byReadLen] = 0x00;
					ar >> ppNRType[nIndex]->nKeyIndex;
					ar >> ppNRType[nIndex]->nCount;
					
					if( ppNRType[nIndex]->nCount > 0) 
					{
						ppNRType[nIndex]->ppNRCon = new NEWREFERCON*[ppNRType[nIndex]->nCount];

						for( nSubIndex = 0; nSubIndex < ppNRType[nIndex]->nCount; nSubIndex++)
						{
							ppNRType[nIndex]->ppNRCon[nSubIndex] = new NEWREFERCON;

							if(ppNRType[nIndex]->ppNRCon[nSubIndex])
							{
								SerializeNEWREFERBITS(ar, ppNRType[nIndex]->ppNRCon[nSubIndex]->NRBits);
								ar >> byReadLen;
								ar.Read( ppNRType[nIndex]->ppNRCon[nSubIndex]->szTgtItem, byReadLen);
								ppNRType[nIndex]->ppNRCon[nSubIndex]->szTgtItem[byReadLen] = 0x00;
								ar >> ppNRType[nIndex]->ppNRCon[nSubIndex]->dTgtConstant;
								ar >> byReadLen;
								ar.Read( ppNRType[nIndex]->ppNRCon[nSubIndex]->szSymbol, byReadLen);
								ppNRType[nIndex]->ppNRCon[nSubIndex]->szSymbol[byReadLen] = 0x00;

								ar >> ppNRType[nIndex]->ppNRCon[nSubIndex]->lTgtCharValue;
							}
						}

					}

// --> [Edit]  김창하 2006/06/30
					ar >> ppNRType[nIndex]->nTop;
					ar >> ppNRType[nIndex]->nLeft;
					ar >> ppNRType[nIndex]->nBottom;
					ar >> ppNRType[nIndex]->nRight;

//					ar >> ppNRType[nIndex]->lDummy;
//	#ifdef _DEBUG
//					if(ppNRType[nIndex]->lDummy)
//					{
//						ASSERT(FALSE);
//					}
//	#endif
// <-- [Edit]  김창하 2006/06/30
				}
			}
		}
	}
}

//*******************************************************************
//  FUNCTION:   - GetNewReferType
//  RETURNS:    - NEWREFERTYPE 의 포인터 ( 기준 Item별 참조 정보 )
//  PARAMETERS: - lpszItem  : 기준 Item
//				  nKeyIndex : 기준 Key Index
//  COMMENTS:   - 기준 Item별 참조 정보  정보를 구한다.
//*******************************************************************
NEWREFERTYPE* CNewRefer::GetNewReferType(LPCTSTR lpszItem, BYTE nKeyIndex /*= 0*/)
{
	if(!lpszItem || *lpszItem == 0x00)
	{
		return NULL;
	}
	BYTE nIndex;
		
	for ( nIndex = 0 ; nIndex < nCount; nIndex ++ )
	{
		if ( ppNRType[nIndex] )
		{
			if( ppNRType[nIndex]->nKeyIndex == nKeyIndex  && strcmp(ppNRType[nIndex]->szItem, lpszItem) == 0 )
				return ppNRType[nIndex];
		}
	}

	// 못찻은 경우.
//	ASSERT(FALSE);
	return NULL;
}

BOOL CNewRefer::SetPropList(LPSTR lpBuf )
{
	if(!lpBuf || *lpBuf == 0x00)
		return FALSE;

	// Format
	// nCount<RS>GetNewReferTypeString<RS>GetNewReferTypeString2<RS>

	Clear();

	LPSTR lpStr;
	int  nLen;
	LPSTR lpTypeBuf = NULL;

	while ( *lpBuf != 0 )
	{
		// nCount
		lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_RS );
		if ( lpStr != NULL )
		{
			nLen = lpStr - lpBuf;
			if( nLen > 0 )
			{
				lpTypeBuf = new char[nLen+1];
				memcpy ( lpTypeBuf, lpBuf,  nLen );
				lpTypeBuf[nLen] = 0x00;

				nCount = (BYTE) atoi(lpTypeBuf);
				
				if ( lpTypeBuf )
					delete[] lpTypeBuf;
			}

			lpBuf = lpStr;
		}
		// RS
		if (lpBuf && *lpBuf)
			lpBuf++;
		BYTE nIndex;
		if( nCount > 0 )
		{
			ppNRType = new NEWREFERTYPE*[nCount];

			for( nIndex = 0; nIndex < nCount; nIndex++)
			{
				// ppNRType
				lpStr = (LPTSTR)_tcschr(lpBuf, _G_TCH_RS );
				if ( lpStr != NULL )
				{
					nLen = lpStr - lpBuf;
					if( nLen > 0 )
					{
						lpTypeBuf = new char[nLen+1];
						memcpy ( lpTypeBuf, lpBuf,  nLen );
						lpTypeBuf[nLen] = 0x00;

						ppNRType[nIndex] = GetNewReferTypePtr( lpTypeBuf );

#ifdef _DEBUG
						if(ppNRType[nIndex] == NULL)
						{
							ASSERT(FALSE);
						}
#endif
						
						if ( lpTypeBuf )
							delete[] lpTypeBuf;
					}

					lpBuf = lpStr;
				}
				// RS
				if (lpBuf && *lpBuf)
					lpBuf++;


			}
		}
	}

	return nCount > 0;
}

BOOL CNewRefer::GetPropList(CString& strList)
{
	// Format
	// nCount<RS>GetNewReferTypeString<RS>GetNewReferTypeString2<RS>
	strList = _T("");
	BYTE nIndex;
	if( nCount > 0 && ppNRType)
	{
		strList.Format(_T("%d%c"), nCount, _G_TCH_RS);
		
		CString strRefer;
		NEWREFERTYPE* pNRType = NULL;

		for( nIndex = 0; nIndex < nCount; nIndex++)
		{
			if(ppNRType[nIndex])
			{
				strRefer = GetNewReferTypeString(ppNRType[nIndex]);

				if(strRefer.IsEmpty())
				{
					ASSERT(FALSE);
					continue;
				}

				strList += strRefer;
			}
		}
	}
	
	return (!strList.IsEmpty());
}

//*******************************************************************
//  FUNCTION:   - GetNewReferTypePtr
//  RETURNS:    - new된 참조 타입의 스트럭쳐 정보.
//  PARAMETERS: - lpTypeBuf : 하나의 조건을 가지는 New Refer Type 스트링.
//  COMMENTS:   - 참조 타입에 해당하는 스트링 문자열을 파싱하여 참조 타입의 스트럭쳐 정보를 구한다.
//*******************************************************************
NEWREFERTYPE* CNewRefer::GetNewReferTypePtr( LPSTR lpTypeBuf )
{
	if( !lpTypeBuf || *lpTypeBuf == 0x00)
	{
		return NULL;
	}

	// Format
	// szItem<US>nKeyIndex<US>nCount<US>Top<US>Left<US>Bottom<US>Right<US>NRBits<FS>szTgtItem<FS>dTgtConstant<FS>szSymbol<FS>lDummy<FS>.......NRBits<FS>szTgtItem<FS>dTgtConstant<FS>szSymbol<FS>lDummy
	LPSTR	lpStr;
	int nLen;
	unsigned long  lLongBits;
	
//	Clear();
	
	NEWREFERTYPE* pNRType = NULL;
	pNRType = new NEWREFERTYPE;
	ASSERT(pNRType);

	// szItem
	lpStr = (LPTSTR)_tcschr(lpTypeBuf, _G_TCH_US );
	
	if ( lpStr != NULL )
	{
		nLen = lpStr - lpTypeBuf;
		if( nLen > 0 )
		{
			memcpy(pNRType->szItem, lpTypeBuf, nLen);
			pNRType->szItem[nLen] = 0x00;
		}
		else
		{
			ASSERT(FALSE);
			*pNRType->szItem = 0x00;
		}

		lpTypeBuf = lpStr;
	}
	// <US>
	if (lpTypeBuf && *lpTypeBuf)
		lpTypeBuf++;

	// nKeyIndex
	pNRType->nKeyIndex = (BYTE) strtol(lpTypeBuf, &lpTypeBuf, 10);
	// <US>
	if (lpTypeBuf && *lpTypeBuf)
		lpTypeBuf++;

	// nCount
	pNRType->nCount = (BYTE) strtol(lpTypeBuf, &lpTypeBuf, 10);
	// <US>
	if (lpTypeBuf && *lpTypeBuf)
		lpTypeBuf++;
	
	// lDummy
// --> [Edit]  김창하 2006/06/30
//	pNRType->lDummy = (long) strtol(lpTypeBuf, &lpTypeBuf, 10);
	// Top위치 
	pNRType->nTop = (short)strtol(lpTypeBuf, &lpTypeBuf, 10);
	// <US>
	if (lpTypeBuf && *lpTypeBuf)
		lpTypeBuf++;
		
	// left위치  
	pNRType->nLeft = (short)strtol(lpTypeBuf, &lpTypeBuf, 10);
	// <US>
	if (lpTypeBuf && *lpTypeBuf)
		lpTypeBuf++;

	// Bottom위치
	pNRType->nBottom = (short)strtol(lpTypeBuf, &lpTypeBuf, 10);
	// <US>
	if (lpTypeBuf && *lpTypeBuf)
		lpTypeBuf++;

	// Right위치  
	pNRType->nRight = (short)strtol(lpTypeBuf, &lpTypeBuf, 10);
	// <US>
	if (lpTypeBuf && *lpTypeBuf)
		lpTypeBuf++;
// <-- [Edit]  김창하 2006/06/30

	// ppNRCon
	pNRType->ppNRCon = NULL;
	BYTE nIndex;
	if(pNRType->nCount > 0)
	{
		pNRType->ppNRCon = new NEWREFERCON*[pNRType->nCount];
		for(  nIndex = 0; nIndex < pNRType->nCount; nIndex++)
		{
			pNRType->ppNRCon[nIndex] = new NEWREFERCON;
			memset(pNRType->ppNRCon[nIndex], 0x00, LEN_NEWREFERCON);

			// NRBits
			lLongBits = (unsigned long) strtol(lpTypeBuf, &lpTypeBuf, 10);
			memcpy(&pNRType->ppNRCon[nIndex]->NRBits, &lLongBits, LEN_NEWREFERBITS);
			// <FS>
			if (lpTypeBuf && *lpTypeBuf)
				lpTypeBuf++;
			
			// szTgtItem
			lpStr = (LPTSTR)_tcschr(lpTypeBuf, _G_TCH_FS);
			
			if ( lpStr != NULL )
			{
				nLen = lpStr - lpTypeBuf;
				if( nLen > 0 )
				{
					memcpy(pNRType->ppNRCon[nIndex]->szTgtItem, lpTypeBuf, nLen);
					pNRType->ppNRCon[nIndex]->szTgtItem[nLen] = 0x00;
				}

				lpTypeBuf = lpStr;
			}
			// <FS>
			if (lpTypeBuf && *lpTypeBuf)
				lpTypeBuf++;

			// dTgtConstant
			pNRType->ppNRCon[nIndex]->dTgtConstant = (double) strtod(lpTypeBuf, &lpTypeBuf);
			// <FS>
			if (lpTypeBuf && *lpTypeBuf)
				lpTypeBuf++;

			// szSymbol
			lpStr = (LPTSTR)_tcschr(lpTypeBuf, _G_TCH_FS);
			
			if ( lpStr != NULL )
			{
				nLen = lpStr - lpTypeBuf;
				if( nLen > 0 )
				{
					memcpy(pNRType->ppNRCon[nIndex]->szSymbol, lpTypeBuf, nLen);
					pNRType->ppNRCon[nIndex]->szSymbol[nLen] = 0x00;
				}

				lpTypeBuf = lpStr;
			}
			// <FS>
			if (lpTypeBuf && *lpTypeBuf)
				lpTypeBuf++;

			// lDummy
			pNRType->ppNRCon[nIndex]->lTgtCharValue = (long) strtol(lpTypeBuf, &lpTypeBuf, 10);
			// <FS>
			if (lpTypeBuf && *lpTypeBuf)
				lpTypeBuf++;

		}
	}

	return pNRType;
}

//*******************************************************************
//  FUNCTION:   - GetNewReferTypeString
//  RETURNS:    - 참조 타입의 스트럭쳐의 스트링 문자.
//  PARAMETERS: - pNRType : 하나의 조건을 가지는 New Refer Type
//  COMMENTS:   - 참조 타입의 스트럭쳐의 스트링 문자열을 구한다.
//*******************************************************************
CString CNewRefer::GetNewReferTypeString(NEWREFERTYPE* pNRType)
{
	if(pNRType == NULL)
	{
		return _T("");
	}

	if( !pNRType->nCount || !pNRType->ppNRCon)
	{
		ASSERT(FALSE);
		return _T("");
	}

	CString strList = _T("");

	// Format
	// szItem<US>nKeyIndex<US>nCount<US>Top<US>Left<US>Bottom<US>Right<US>NRBits<FS>szTgtItem<FS>dTgtConstant<FS>szSymbol<FS>lDummy<FS>.......NRBits<FS>szTgtItem<FS>dTgtConstant<FS>szSymbol<FS>lDummy
	
// --> [Edit]  김창하 2006/06/30
//	strList.Format("%s%c%d%c%d%c%d%c",	
//						pNRType->szItem,	US, 
//						pNRType->nKeyIndex, US, 
//						pNRType->nCount,	US, 
//						pNRType->lDummy,	US);
// <-- [Edit]  김창하 2006/06/30

	strList.Format("%s%c%d%c%d%c%d%c%d%c%d%c%d%c",	
						pNRType->szItem,	_G_TCH_US, 
						pNRType->nKeyIndex, _G_TCH_US, 
						pNRType->nCount,	_G_TCH_US, 
						pNRType->nTop,		_G_TCH_US, 
						pNRType->nLeft,		_G_TCH_US, 
						pNRType->nBottom,	_G_TCH_US, 
						pNRType->nRight,	_G_TCH_US);

	char szBuf[256];
	unsigned long  lLongBits;
	int nLen;
	BYTE nIndex;
	for(  nIndex = 0; nIndex < pNRType->nCount; nIndex++)
	{
		if(pNRType->ppNRCon[nIndex])
		{
			memcpy(&lLongBits, &pNRType->ppNRCon[nIndex]->NRBits, LEN_NEWREFERBITS);

			sprintf(szBuf,_T("%d%c%s%c%g%c%s%c%d%c"), 
							lLongBits,								_G_TCH_FS,
							pNRType->ppNRCon[nIndex]->szTgtItem,	_G_TCH_FS,
							pNRType->ppNRCon[nIndex]->dTgtConstant,	_G_TCH_FS,
							pNRType->ppNRCon[nIndex]->szSymbol,		_G_TCH_FS,
							pNRType->ppNRCon[nIndex]->lTgtCharValue,_G_TCH_FS); 

			if(nIndex + 1 == pNRType->nCount)
			{
				nLen = strlen(szBuf);
				szBuf[nLen]   = _G_TCH_RS;
				szBuf[nLen+1] = 0x00;
				// 마지막에<RS>추가. 
			}
			strList += szBuf;
		}
	}
	return  strList;
}
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CTableInfo, CObject, 1)
CTableInfo::CTableInfo()
{
	m_pTableCell	=	NULL;
	m_pTableLink	=	NULL;
//	m_pTableBorder	=	NULL;
	// 테이블인 경우 기본 선색을 정의한다.
	m_nLineColorIndex	=	DEF_TABLE_LINE_COLORINDEX;

	m_pTableCell = new CTableCell;
	if(m_pTableCell)
	{
		m_pTableCell->SetTableInfo(this);
		m_pTableCell->Initialize();
	}

// --> [Edit]  김창하 2005/11/25
	m_pTableLink = new CTableLink;
// <-- [Edit]  김창하 2005/11/25

	if(m_pTableLink)
		m_pTableLink->Initialize();
	
//	m_pTableBorder = new CLineBorder(FALSE);

#ifdef MULTI_CAPTION_USE		// 다국어 사용옵션 
	m_pTableMultiCell = NULL;
	m_pTableMultiCell = new CGXCaptionData;
#endif

};

CTableInfo::~CTableInfo()
{
	//COgBase::~COgBase();

	if(m_pTableCell)
	{
		m_pTableCell->Clear();
		delete m_pTableCell;
		m_pTableCell = NULL;
	}
	
	if(m_pTableLink)
	{
		m_pTableLink->Clear();
		delete m_pTableLink;
		m_pTableLink = NULL;
	}

//	if(m_pTableBorder)
//	{
//		m_pTableBorder->Clear();
//		delete m_pTableBorder;
//		m_pTableBorder = NULL;
//	}

#ifdef MULTI_CAPTION_USE		// 다국어 사용옵션 
	if ( m_pTableMultiCell )
		delete m_pTableMultiCell;
	m_pTableMultiCell = NULL;
#endif
};


// 다이얼로그에서 사용하기 위해서 추가.
void CTableInfo::SetDefault(int nRowCnt, int nColCnt)
{
	// Base Info
	//m_CtrlSize			=	DEF_CTRL_SIZE;
	m_nRowCnt				=	nRowCnt;
	m_nColCnt				=	nColCnt;
	m_nFrozenRowCnt			=	nRowCnt;
	m_nFrozenColCnt			=	nColCnt;
	m_nSelectionMode		=	(int)dxSelNone;
	m_nScrollMode			=	(int)dxScrollNotUse;
	m_nLineMode				=	(int)dxLineBoth;
	//m_nDragIndex			=	DEF_HEADER_ROW_COUNT;
	m_nBorderStyle			=	(int)dxCBdrNone;
	m_nRealHighlight		=	dxRealHLNone;
	m_byUseForDll			=	(BYTE) FALSE;
	m_byMultiItemUse		=	(BYTE) FALSE;

	if(m_pRowSize)
	{
		m_pRowSize->Clear();
		m_pRowSize->Initialize(m_nRowCnt, DEF_ROW_HEIGHT);
	}

	if(m_pColSize)
	{
		m_pColSize->Clear();
		m_pColSize->Initialize(m_nColCnt, DEF_COLUMN_WIDHT);
	}

	// Table Info
	if(m_pTableCell)
	{
		m_pTableCell->Clear();
		m_pTableCell->Initialize();
	}
}

BOOL CTableInfo::Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol /*= TRUE*/)
{
	if( nFrom <= 0 || nDest <= 0 || nFrom == nDest)
		return FALSE;

	if( bMoveCol )
	{
		if(nFrom > m_nColCnt || nDest > m_nColCnt )
			return FALSE;
	}
	else
	{
		if(nFrom > m_nRowCnt || nDest > m_nRowCnt )
			return FALSE;
	}


	// Base Info Move
	COgBase::Move(nFrom, nDest, bMoveCol);
	
	// Grid Info Move
	if( m_pTableCell )
	{
		m_pTableCell->Move( nFrom, nDest, bMoveCol );
	}

	//if( m_pTableLink )
	//{
	//	m_pTableLink->Move( nFrom, nDest, bMoveCol );
	//}
	return TRUE;
}

//*****************************************************************************
// 루    틴    명  :  SetTableCellInfoBlobDataChange
// 기          능  :  테이블 셀 BLOB데이터정보를 구조체로 변한하는 함수. 
// 입          력  :  CString  strPropertyData
// 출          력  :  BOOL
// 작    성    자  :  2003년7월15일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
BOOL  CTableInfo::SetTableCellInfoBlobDataChange( CString  strPropertyData )
{
	if ( strPropertyData.IsEmpty() )
		return FALSE;

	BYTE* pvData = NULL;
	pvData = StringToBinary( strPropertyData );
	
	ASSERT( pvData != NULL );
    if( pvData != NULL )
	{
		m_pTableCell->Clear();

		int		nTotalCount;
		int		nOffset = 0;

		ROWCOL nRowCount,
				nColCount;
			
		nRowCount = m_nRowCnt;						// GetRowCount();
		nColCount = m_nColCnt;						// GetColCount();

		nTotalCount		   = nRowCount * nColCount;
		ASSERT ( nTotalCount > 0 );

		if ( nTotalCount <= 0 )
		{
			free ( pvData );
			return FALSE;
		}
	// --> [Edit]  김창하 2006/04/28
		int nBaseVer = LOWORD(m_dwBaseVer);
		int nAddLen(0);  
		if ( nBaseVer <= 1 )
		{
			nAddLen = 10; //ITEM_LEN길이값이 20자리에서 30자리로 변경 
		}
	// <-- [Edit]  김창하 2006/04/28

		DWORD dwTotalLen	   = sizeof(DWORD)+ sizeof(short) + ( nTotalCount * LEN_TABLECELL );

		m_pTableCell->dwLength = *(DWORD*)pvData;
		nOffset += sizeof(DWORD);

// --> [Edit]  김창하 2006/04/28
		if ( dwTotalLen != m_pTableCell->dwLength )
		{
			if ( nBaseVer <= 1 )
			{
				m_pTableCell->dwLength = dwTotalLen;
			}
			else
			{
				ASSERT ( FALSE );
			}
		}
// <-- [Edit]  김창하 2006/04/28
		

		m_pTableCell->nCount = *(short*)(pvData + nOffset);
		nOffset += sizeof(short);
			
		ASSERT( m_pTableCell->nCount == nTotalCount );

		m_pTableCell->pRec = new TABLECELL*[ nTotalCount ];
		
		int nIndex = 0;	
		for ( ; nIndex < nTotalCount; nIndex ++ )
		{
			m_pTableCell->pRec[nIndex] = new TABLECELL;
			memset ( m_pTableCell->pRec[nIndex] ,0x0,	  LEN_TABLECELL );
// --> [Edit]  김창하 2006/04/28
			if ( nBaseVer <= 1 )						// 1차 버전 변경분 처리 
			{
//				short		nRow;
//				short		nCol;
//				short		nOrgRow;				// 원래Row위치 (컬럼이동시 사용 ) 
//				short		nOrgCol;				// 원래Col위치 (컬럼이동시 사용 )  
//				short		nKeyIndex;
//				short		nRBkCrIndex;
//				short		nRTxCrIndex;
//				short		n3DEffect;
//				char		szCaption[CAPTION_LEN+1];
//				char		szItem[ITEM_LEN+1];
//				BYTE		bySignFormat;	
//				BYTE		cDataType;
//				OGBASEITEM	bsItem;
//				ITEMBITS	ItemBits;
//				TABLEBITS	tblBits;
//				MASKINFO	mask;
//				long		lDummy;
//
				int nLen = sizeof(short)*8 + CAPTION_LEN+1;		// nPos->n3DEffect
				memcpy ( m_pTableCell->pRec[nIndex], pvData + nOffset, nLen );
				nOffset += nLen;

																// char		szItem[ITEM_LEN+1];
				nLen = ITEM_LEN-nAddLen;
				memcpy ( &m_pTableCell->pRec[nIndex]->szItem, pvData + nOffset, nLen );
				nOffset += nLen+1;
				
				nLen = (sizeof(BYTE)*2)+ sizeof(long) + LEN_OGBASEITEM + LEN_ITEMBITS + LEN_TABLEBITS + LEN_MASKINFO;
				memcpy ( &m_pTableCell->pRec[nIndex]->bySignFormat, pvData + nOffset, nLen );
				nOffset += nLen;					
			}
			else
			{
				memcpy ( m_pTableCell->pRec[nIndex], pvData + nOffset, LEN_TABLECELL );
				if ( nBaseVer <= 9 )
				{
					if ( m_pTableCell->pRec[nIndex]->bsItem.nCtrlID == 52527 )
					{
						m_pTableCell->pRec[nIndex]->bsItem.nCtrlID = dxCtrlCombo;
					}

					nOffset += ( LEN_TABLECELL - ( REAL_ITEM_LEN + 1 ) ) ;

				}
				else if( nBaseVer <= 11 )
				{
					nOffset += ( LEN_TABLECELL - ( REAL_ITEM_LEN + 1 ) ) ;
				}
				else
				{
					nOffset += LEN_TABLECELL;
				}

//				nOffset += LEN_TABLECELL;
			}
// <-- [Edit]  김창하 2006/04/28
		}
		free ( pvData );
		return TRUE;
	}

	return FALSE;
}

//*******************************************************************/
/*! Function Name : GetDumpText
/*! Function      : 셀 정보 내용을 표시하는 함수 
/*! Param         : int nOption
/*! Return        : 
/*! Create        : 김창하 , 2006/05/10
/*! Comment       : 
//******************************************************************/
CString	CTableInfo::GetDumpText( int nOption  )
{
	CString strText,
			strBuf;
	
	TABLECELL * pRec = NULL;
	for ( int nIndex = 0 ; nIndex < m_pTableCell->nCount; nIndex ++ )
	{
		pRec  = m_pTableCell->pRec[nIndex];
		strBuf.Format ( "Row=[%d],Col=[%d], OrgRow=[%d],OrgCol=[%d] \r\n", pRec->nRow,	
														pRec->nCol,
														pRec->nOrgRow,
														pRec->nOrgCol);
		strText +=  strBuf;	
	}

	return strText;
}

//*****************************************************************************
// 루    틴    명  :  SetTableCellLinkBlobDataChange
// 기          능  :  테이블 셀 Link BLOB데이터정보를 구조체로 변한하는 함수 .
// 입          력  :  CString  strPropertyData
// 출          력  :  BOOL
// 작    성    자  :  2003년7월15일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  .
//*****************************************************************************
BOOL  CTableInfo::SetTableCellLinkBlobDataChange	( CString  strPropertyData )
{
	if ( strPropertyData.IsEmpty() )
		return FALSE;

	BYTE* pvData = NULL;
	pvData = StringToBinary( strPropertyData );
	
	ASSERT( pvData != NULL );
    if( pvData != NULL )
	{
		m_pTableLink->Clear();

		int nTotalCount;
		int nOffset = 0;

		ROWCOL nRowCount,
				nColCount;
			
		nRowCount = m_nRowCnt;						// GetRowCount();
		nColCount = m_nColCnt;						// GetColCount();

		nTotalCount		   = nRowCount * nColCount;
		ASSERT ( nTotalCount > 0 );

		if ( nTotalCount <= 0 )
		{
			free ( pvData );
			return FALSE;
		}
	
		DWORD dwTotalLen	   = LEN_CELLLINKINFO ( nTotalCount );

		m_pTableLink->dwLength = *(DWORD*)pvData;
		nOffset += sizeof(DWORD);

		ASSERT( dwTotalLen == m_pTableLink->dwLength  );

		m_pTableLink->nCount = *(short*)(pvData + nOffset);
		nOffset += sizeof(short);
			
		ASSERT( m_pTableLink->nCount == nTotalCount );

		m_pTableLink->pRec = new CELLLINK*[ nTotalCount ];
		
		int nIndex = 0;	
		for ( ; nIndex < nTotalCount; nIndex ++ )
		{
			m_pTableLink->pRec[nIndex] = new CELLLINK;
			memset ( m_pTableLink->pRec[nIndex], 0x0, LEN_CELLLINK );

			memcpy ( m_pTableLink->pRec[nIndex], pvData + nOffset, LEN_CELLLINK );
			nOffset += LEN_CELLLINK;
		}
		free ( pvData );
		return TRUE;
	}

	return FALSE;
}


//*****************************************************************************
// 루    틴    명  :  GetTableCellInfoBlobDataFromDataInfo
// 기          능  :  TableCell정보를 BlobData데이터로 변환하는 함수. 
// 입          력  :  HGLOBAL* phBlob
// 출          력  :  BOOL
// 작    성    자  :  2003년7월15일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
CString  CTableInfo::GetTableCellInfoBlobDataFromDataInfo( )
{
	CString  strPropertyData;
	
	int nOffset = 0;

	int nTotalCount;
	ROWCOL nRowCount,
			nColCount;
			
	nRowCount = m_nRowCnt;							// GetRowCount();
	nColCount = m_nColCnt;							// GetColCount();

	nTotalCount	= nRowCount * nColCount;

	ASSERT ( m_pTableCell->nCount == nTotalCount );

	ASSERT ( nTotalCount > 0 );

	if ( nTotalCount <= 0 )
		return strPropertyData;

	DWORD dwTotalLen   = sizeof(DWORD)+ sizeof(short) + ( nTotalCount * LEN_TABLECELL );
	ASSERT ( m_pTableCell->dwLength == dwTotalLen );


	BYTE* pvData = (BYTE*)malloc( dwTotalLen );
	if ( pvData != NULL )
	{
		memset( pvData, 0x0, dwTotalLen );

		*(DWORD*)pvData				= m_pTableCell->dwLength;
		nOffset += sizeof(DWORD);

		*(short*)(pvData + nOffset ) = m_pTableCell->nCount;
		nOffset += sizeof(short);
			
		TABLECELL * pTableCell = NULL;
	    for ( int nIndex = 0 ; nIndex < m_pTableCell->nCount; nIndex ++ )
		{
			pTableCell = m_pTableCell->pRec[ nIndex ];
			ASSERT ( pTableCell != NULL );
			
			memcpy ( pvData + nOffset, pTableCell, LEN_TABLECELL );
			nOffset += LEN_TABLECELL;

		}
		strPropertyData = BinaryToString( pvData, dwTotalLen );
		free(pvData);
	}
	return strPropertyData;

}

//*****************************************************************************
// 루    틴    명  :  GetTableCellLinkBlobDataFromDataInfo
// 기          능  :  TableCell Link정보를 BlobData데이터로 변환하는 함수 .
// 입          력  :  
// 출          력  :  CString 
// 작    성    자  :  2003년7월15일    김  창하 (주) 한국 소리마치.
// 수  정  이  력  :  
//*****************************************************************************
CString  CTableInfo::GetTableCellLinkBlobDataFromDataInfo( )
{
	CString  strPropertyData;
	
	int nOffset = 0;

	int nTotalCount;
	ROWCOL nRowCount,
			nColCount;
			
	nRowCount = m_nRowCnt;						// GetRowCount();
	nColCount = m_nColCnt;						// GetColCount();

	nTotalCount	= nRowCount * nColCount;


	if ( nTotalCount <= 0 || m_pTableLink->nCount <= 0 )
		return strPropertyData;

	ASSERT ( m_pTableLink->nCount == nTotalCount );
	DWORD dwTotalLen   = LEN_CELLLINKINFO(  nTotalCount  );
	
	ASSERT ( m_pTableLink->dwLength == dwTotalLen );
	BYTE* pvData = (BYTE*)malloc( dwTotalLen );

	if ( pvData != NULL )
	{
		memset( pvData, 0x0, dwTotalLen );

		*(DWORD*)pvData				= m_pTableLink->dwLength;
		nOffset += sizeof(DWORD);

		*(short*)(pvData + nOffset ) = m_pTableLink->nCount;
		nOffset += sizeof(short);
			
		CELLLINK* pRec = NULL; 
		for ( int nIndex = 0 ; nIndex < m_pTableLink->nCount; nIndex ++ )
		{
			pRec = m_pTableLink->pRec[ nIndex ];
			ASSERT ( pRec != NULL );
				
			memcpy ( pvData + nOffset, pRec , LEN_CELLLINK );
			nOffset += LEN_CELLLINK;
		}

		strPropertyData = BinaryToString( pvData, dwTotalLen );
		free(pvData);
	}
	return strPropertyData;
}

//*******************************************************************/
/*! Function Name : SerializeUserData
/*! Function      : 
/*! Param         : CArchive &ar, LPBYTE lpData, DWORD dwLen
/*! Return        : void 
/*! Create        : 김창하 , 2005/11/29
/*! Comment       : 
//******************************************************************/
void CTableInfo::SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen )
{
    COgBase::Serialize(ar);
	ASSERT_VALID(this);

    if(!ar.IsStoring())							// Read
    {
		if( m_pTableCell )
		{
			m_pTableCell->SerializeUserData(ar, lpData, dwLen );
		}

		if(m_pTableLink)
		{
			m_pTableLink->Serialize(ar);
		}

//		if( m_pTableBorder)
//		{
//			m_pTableBorder->SerializeUserData(ar, lpData, dwLen );
//		}
    }
}

void CTableInfo::Serialize(CArchive &ar)
{
    COgBase::Serialize(ar);

	ASSERT_VALID(this);

    if(ar.IsStoring())							// Write
    {

		if(m_pTableCell)
		{
			m_pTableCell->SetVersion(m_dwBaseVer);
			m_pTableCell->Serialize(ar);
		}

		if(m_pTableLink)
		{
			m_pTableLink->SetVersion(m_dwBaseVer);
			m_pTableLink->Serialize(ar);
		}

//		if(m_pTableBorder)
//		{
//			m_pTableBorder->SetVersion(m_dwBaseVer);
//			m_pTableBorder->Serialize(ar);
//		}
	}
    else										// Read
    {
		if(m_pTableCell)
		{
			m_pTableCell->Serialize(ar);
		}
		
		if(m_pTableLink)
		{
			m_pTableLink->Serialize(ar);
		}
//		if(m_pTableBorder)
//		{
//			m_pTableBorder->Serialize(ar);
//		}
    }
};


const CTableInfo& CTableInfo::operator=(const CTableInfo& other)
{
	if (&other == this)
		return *this;

	COgBase::operator=(other);

	if(other.m_pTableCell)
		*m_pTableCell		=	*other.m_pTableCell;
	
	if(other.m_pTableLink)
		*m_pTableLink		=	*other.m_pTableLink;

//	if(other.m_pTableBorder)
//		*m_pTableBorder		=	*other.m_pTableBorder;

	return *this;
}

// Tail Grid Serialize
void CTableInfo::SerializeEx ( CArchive& ar, CString& strProperty )
{
	ASSERT_VALID(this);
	DWORD dwDataLen;

	if (ar.IsStoring())		// Write
	{
		CMemFile  memFile;
		CArchive  arMem(&memFile, CArchive::store );
		Serialize( arMem );
		arMem.Flush();

		dwDataLen = (DWORD)memFile.GetLength();
		if ( dwDataLen > 0 )
		{
			BYTE *pTemp = new BYTE [dwDataLen+1];
			memFile.Seek(0, CFile::begin);
			memFile.Read(pTemp, dwDataLen );
		
			ar.Write(&dwDataLen, sizeof(DWORD));
			ar.Write(pTemp, dwDataLen);

			// Property Save CString
			strProperty = BinaryToString ( pTemp, dwDataLen );

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
			Serialize( arMem );

			// Property Save CString
			DWORD dwTotLen = 	dwDataLen + sizeof(DWORD);
			BYTE *pvData = new BYTE[dwTotLen];
			*(DWORD*)pvData = dwTotLen;
			memcpy ( pvData + sizeof(DWORD), pTemp, dwDataLen );
			
			if ( pTemp )
				delete[] pTemp;

			strProperty = BinaryToString ( pvData, dwTotLen );
			if ( pvData )
				delete[] pvData;
		}
	}
}

BOOL CTableInfo::SetTailGridDataChange ( CString  strPropertyData )  // property String->Binary
{
	SetAllClear();

	if ( strPropertyData.IsEmpty() )
	{
		return FALSE;
	}

	BYTE*	pvData = NULL;
	pvData = StringToBinary ( strPropertyData );
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

CString CTableInfo::GetTailGridDataChange ( )					 // Binary->property String
{
	CString strProperty;

	ASSERT_VALID(this);

	CMemFile  memFile;
	CArchive arMem(&memFile, CArchive::store );
	Serialize ( arMem );
	arMem.Flush();

	DWORD dwDataLen = (DWORD)memFile.GetLength();
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
		strProperty = BinaryToString ( pvData, dwTotLen );
		if ( pvData )
			delete[] pvData;
	}	
	return strProperty;
}

void CTableInfo::SetAllClear()
{
	if(m_pTableCell)
	{
		m_pTableCell->Clear();
	}
	
	if(m_pTableLink)
	{
		m_pTableLink->Clear();
	}
#ifdef MULTI_CAPTION_USE		// 다국어 사용옵션 
	if ( m_pTableMultiCell )
		m_pTableMultiCell->DeleteContents();
#endif
}

