#ifndef _OGDESIGNGATE_H_
#define _OGDESIGNGATE_H_

#include "OgDesignDefine.h"

#ifdef MULTI_CAPTION_USE		// �ٱ��� ���ɼ� 
#include "GxCaptionStyle.h"	// GxCaptionArray
#endif

// �׸��� ���� ������ 
//#ifndef GRID_CELL_STYLE_USE		
//#include "GxGridCellStyle.h"	
//#endif


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma pack(push, 1)
/***************************************************/
// Designer �⵿���� OCX�� ������ �Ѱ��ر� ���� ����ü.
/***************************************************/
typedef struct tagInitInfo
{
	long    hOCXWnd;
	char	szFileName[MAX_PATH];
	char    szCaption[MAX_PATH];
	char    szTran[MAX_PATH];
	char    szFeed[MAX_PATH];

} INITINFO, *LPINITINFO;

/***************************************************/
// Base Bit Info
// nToolTip		 : ToolTip Array�� �ε����� ��Ÿ�� (1���� �ε��� ����.)
// bFormula		 : Formula ����ϴ� ���� ��Ÿ��.
// bDspMemo		 : ���� �޸� ���� ��Ÿ���� �� �ǹ�.
/***************************************************/
typedef struct tagBASEBITS
{
	unsigned long nToolTip		: 8;
	unsigned long bFormula		: 1;
	unsigned long nOpCalc		: 6;			// Calculation Cell(5->6Bit)
	unsigned long bRefFormula	: 1;			// Formula������.
	unsigned long nColHideInfo	: 2;			// �÷� �����.
	unsigned long bInputMaskUse	: 1;			// InPutMask��� 
	unsigned long bReplaceText	: 1;			// ReplaceText USe ��� 
	unsigned long bCaptionText	: 1;			// Captiontext ��� 
#ifdef _BIGTEXT_USE
	unsigned long bBigTextUse	: 1;			// ���� Ȯ��.
	unsigned long nBigTextLen	: 3;			// ���� Ȯ���(�ִ�7) 
	unsigned long nTextShowLen	: 4;			// 4Bit : 0 : show, 1 : hide, 1~3bit : TextLen
	unsigned long Dummy			: 6;
#else
	unsigned long Dummy			: 11;
#endif
	// 32 Bits
} BASEBITS; // 4 Byte


/***************************************************/
// Item Bit Info
/***************************************************/
typedef struct tagITEMBITS
{
	unsigned long nItemFlag			: 2;		// ItemFlag
	unsigned long bIsKeyItem		: 1;		// Main Key Item			  : ���¹�ȣ. 
	unsigned long bIsSubKeyItem		: 1;		// Sub Key Item				  : ü���ȣ.  	
	unsigned long bIsThirdKeyItem	: 1;		// Third Key Item			  : �ֹ���ȣ.
	unsigned long bSignBitInfo		: 1;		// ��ȣ�� �������(FID��ȸ) +, ���� 
	unsigned long bReferOwner		: 1;		// ���� ��ü�� �Ǵ� ��.(�����ϸ� ���߿� ����)
	unsigned long bReferSlave		: 1;		// ������ ���ϴ� ��(�����ϸ� ���߿� ����)
	unsigned long bIgnoreReal		: 1;		// �ǽð� ������Ʈ�� ���� �ʴ� ������ �ǹ�(ex:�����, �����ڵ��..)
	unsigned long nLinkTag			: 6;		// LinkTag
	unsigned long bCodeLink			: 1;		// ���񿬵�.
	unsigned long bOrderLink		: 1;		// �ֹ�����.
//	unsigned long bRealItemChange	: 1;		// �ǽð��ÿ� �����۸��� �ٲ����� ����.
	unsigned long bDataHide			: 1;		// �����ͼ� ǥ�� ���ϱ�. 
	unsigned long bMOverCell		: 1;		// �ʷ��� ȿ���� �ִ� ��( Mouse Over�ÿ�  )
	unsigned long bRealCell			: 1;		// ������ ���� �ǽð� ����ǥ�� 
	unsigned long bMemo				: 1;		// ���� ������
	unsigned long bCodeNameColor	: 1;		// ����� ���ڻ� ���
	unsigned long bNewsSign			: 1;		// ������ȣ   

	unsigned long bOneCellDataShow  : 1;		// One Cell Data
	unsigned long bMainTreeDataShow	: 1;		// ����Ʈ�� ������ ǥ�� ���� ��. 
	unsigned long bMainTreeCellHide	: 1;		// ����Ʈ�� �� ����� ��.
	unsigned long bChildTreeCellHide: 1;		// ����Ʈ�� �� ����� ��. 
	unsigned long bAutoPriceMask	: 1;		// �������� �ڵ� ����ŷ
	unsigned long Dummy				: 4;
	// 32 Bits
} ITEMBITS; // 4 Byte


/***************************************************/
// Grid Bit Info
/***************************************************/
typedef struct tagGRIDBITS
{
	unsigned long bCellTip			: 1;		// CellTip ��� ����.
	unsigned long bHideLine			: 1;		// �׸��� ���� �����.
	unsigned long bDontSort			: 1;		// Sort ���� �÷���.
	unsigned long bDragCol			: 1;		// �巡���� �÷�( ex : �����ڵ�)
	unsigned long bNumberCol		: 1;		// No ǥ���� �÷�.
	unsigned long bNoUseBlockColor	: 1;		// No Use of Block Color 
	unsigned long bDragNameCol		: 1;		// �巡���� �̸� �÷�( ex : �����)
	unsigned long bSumCol			: 1;		// �հ��� �÷�(�����ŷ���)(�ð��뺰 �׸��忡�� �հ��÷�)
	unsigned long bDSortCol			: 1;		// Z~A - Sort Col
	unsigned long bNoBlockCount		: 1;		// Block Count ������. 
	unsigned long bASortCol			: 1;		// A~Z - Sort Col
	unsigned long Dummy				: 21;
	// 32 Bits
} GRIDBITS; // 4 Byte

/***************************************************/
// Table Bit Info
/***************************************************/
typedef struct tagTABLEBITS
{
	unsigned long bMOverCell		: 1;			// �ʷ��� ȿ���� �ִ� ��( Mouse Over�ÿ�  )
	unsigned long nHogaGraph		: 2;			// ȣ�� ���� �׷���(0:None, 1:Owner, 2:Slave)
	unsigned long bHogaPrice		: 1;			// ȣ�� ���� ��.
	unsigned long bMouseOver		: 1;			// Runtime�ÿ� ���(�ʷ��� �޴� ǥ�ý�)
	unsigned long bCurPrc			: 1;			// ȣ�� ( ���簡 ��)
	unsigned long bStandardPrc		: 1;			// ȣ�� ( ���ذ�(��������) ��)
	unsigned long bSaleTotAmount	: 2;			// Runtime�ÿ� ���(�ܷ� Progress�� ��Ÿ���� ���� �ŵ� ���ܷ���)
	unsigned long bHogaEmphasis		: 1;			// ȣ�� ������. 
	unsigned long nHogaOrder		: 2;			// �ֹ� ��(0:None, 1:Sale, 2:Buy)
	unsigned long nHogaStop			: 2;			// STOP ��(0:None, 1:Sale, 2:Buy)
	unsigned long nLinkRow			: 6;			// Link Cell Row( �ִ� :60)
	unsigned long nLinkCol			: 6;			// Link Cell Col( �ִ� :60)
	unsigned long bHogaOrderInfo	: 1;			// ȣ����������ǥ�ü�(�ֹ���: �ܰ�,��ü��,���ݼ��ü�)
	unsigned long bHogaRateCell		: 1;			// ȣ������� �÷� 
	unsigned long bXRayHogaCell		: 1;			// ȣ���м���ǥ�� (X-RAY)
	unsigned long bHogapriceInfo	: 1;			// ȣ����������ǥ�ü�(
	unsigned long Dummy				: 2;
	// 32 Bits
} TABLEBITS; // 4 Byte


/***************************************************/
// Tran Bit Info (������ : LG���� Tran�� ������ ���ÿ� ����Ҽ� �־ �ǹ̰� ������ ���ܵд� )
/***************************************************/
typedef struct tagTRANBITS
{
	unsigned long nItemIndex	: 8;
	unsigned long nItemOffset	: 14;
	unsigned long nItemLen		: 10;
	// 32 Bits
} TRANBITS; // 4 Byte


/***************************************************/
// Header, Body, Cell�� ���������� ������ Ư��.
/***************************************************/
typedef struct tagOgBaseItem
{
	short		nBkCrIndex;
	short		nTxCrIndex;
	short		nFontIndex;
	short		nHAlign;
	short		nVAlign;
	int			nCtrlID;
	BASEBITS	BaseBits;				// 4Byte
	short		nWrapText;				// SetWrapText()��� 
	short		nBaseItemDummy;			// ����.
} OGBASEITEM, *LPOGBASEITEM;

/***************************************************/
// Mask ����.
/***************************************************/
typedef struct tagMaskInfo
{
	short		nFormat;				// Format Index
	short		nPlaces;				// �Ҽ��� ���� �ڸ���.
	DWORD		dwBitInfo;				// Bit�� ���� ������� ���.
										// 0x00000001	// �޸����.										
										// 0x00000002	// 0ǥ�þ���.										
										// 0x00000004	// ��ȣ ǥ�� ����.										
										// 0x00000008	// ��ȣ (-) �� ǥ��.										
										// 0x00000010	// ��ȣ (-, +) �׻� ǥ��.										
										// 0x00000020	// Prefix ���.										
										// 0x00000040	// Postfix ���.										
										// 0x00000080	// �տ� 0����.										
										// 0x00000100	// ������
										// 0x00000200	// ������
										// 0x00000400	// ������
										// 0x00000800	// �Ҽ������� �ڸ��� ó���� �����ÿ� ������Ÿ�� �Ҽ����� ������ ��å.
										// 				// (ex) �Ҽ������� �ڸ��� 2�ΰ�� �Է� ����Ÿ�� 116�϶�.
										// 				// True : 116.00, False : 1.16
										// 0x00001000	// �ݿø�.
										// 0x00002000	// ��ȣ ���.
										// 0x00004000	// MBS_ZERO_TRIMLEFT�� ���� ����찡 0�϶� ������ 0�� ���濩��.
										// 0x00008000	// .���� �� ǥ�� ���ϱ�
										// 0x00010000	// ������ ���������� ��ȯ 
										// 0x00020000	// ǥ�ÿ��� ������ �ڵ� 1000���� �����  K ���ڿ� �����̱� 

	char		szFix[MAX_FIX_LEN+1];	// Prefix / Postfix�� ���ڿ� �ִ� ���� 4(ex : %, $, ����).
	long		lMaskInfoUnit;
	
	tagMaskInfo()
	{
		nFormat       = 0;
		nPlaces       = 0;
		dwBitInfo     = 0;
		lMaskInfoUnit = 0L;
		memset( szFix, 0x00, sizeof(szFix) );
	}
} MASKINFO, *LPMASKINFO;



/***************************************************/
// Grid�� Header����. 
/***************************************************/
// Grid�� ���� Header����.
typedef struct tagGridHeader
{
	short		nRow;
	short		nCol;
	short		nOrgRow;				// ����Row��ġ (�÷��̵��� ��� ) 
	short		nOrgCol;				// ����Col��ġ (�÷��̵��� ��� )  
	char		szCaption[CAPTION_LEN+1];
	OGBASEITEM	bsItem;
	MASKINFO	mask;					// �Ｚ���� ����ŷ���� �߰� 
	long		lDummy;
} GRIDHEADER, *LPGRIDHEADER;

// Grid�� ��ü Header����. 
typedef struct tagGridHeaderInfo
{
	DWORD		dwLength;
	short		nCount;
    
	GRIDHEADER** pRec;

} GRIDHEADERINFO, *LPGRIDHEADERINFO;

/***************************************************/
// Grid�� Body����. 
/***************************************************/
// Grid�� ���� Body����. 
typedef struct tagGridBody
{
	short		nPos;
	short		nOrgPos;								// ���� Pos��ġ (�÷��̵��� ��� ) 
	short		nSubIndex;
    short		nKeyIndex;
	short		nRBkCrIndex;
	short		nRTxCrIndex;

	char		szItem[ITEM_LEN+1];
#ifdef FIXLEN_USE
	char		szRecName[RECORD_LEN+1];
#endif
	BYTE		bySignFormat;
	BYTE		cDataType;

	OGBASEITEM	bsItem;
	ITEMBITS	ItemBits;
	GRIDBITS	GridBits;
	MASKINFO	mask;
#ifdef FIXLEN_USE
	TRANBITS	TrBits;
#endif

	short		nFID;		// 
// --> [Edit]  �Ȱ�ȯ 2008/03/26
//	short		wDummy;
	short		nAttrFid;		// FID ���� ���� ATTRIBUTE
// <-- [Edit]  �Ȱ�ȯ 2008/03/26
	char		szRealItem[REAL_ITEM_LEN+1]; // Real Item��

} GRIDBODY,*LPGRIDBODY;

// Grid�� ��ü Body����. 
typedef struct tagGridBodyInfo
{
	DWORD		dwLength;
	short		nSubItemCount;	// ���� �׸��� : Sub Row Count, ���� �׸��� : Sub Cloumn Count, 
	short		nItemCount;		// ���� �׸��� : ����Ÿ ������ Column Count, ���� �׸��� : ����Ÿ ������ Row Count. 
    GRIDBODY*** pRec;

} GRIDBODYINFO,*LPGRIDBODYINFO;


/***************************************************/
// Table�� Cell����. 
/***************************************************/
// Table�� ���� Cell����. 
typedef struct tagTableCell
{
	short		nRow;
	short		nCol;
	short		nOrgRow;				// ����Row��ġ (�÷��̵��� ��� ) 
	short		nOrgCol;				// ����Col��ġ (�÷��̵��� ��� )  
	short		nKeyIndex;
	short		nRBkCrIndex;
	short		nRTxCrIndex;
	short		n3DEffect;

	char		szCaption[CAPTION_LEN+1];
	char		szItem[ITEM_LEN+1];
#ifdef FIXLEN_USE
	char		szRecName[RECORD_LEN+1];
#endif
	BYTE		bySignFormat;	
	BYTE		cDataType;

	OGBASEITEM	bsItem;
	ITEMBITS	ItemBits;
	TABLEBITS	tblBits;
	MASKINFO	mask;
#ifdef FIXLEN_USE
	TRANBITS	TrBits;
#endif

	short		nFID;		// 
// --> [Edit]  �Ȱ�ȯ 2008/03/26
//	short		wDummy;
	short		nAttrFid;		// FID ���� ���� ATTRIBUTE
// <-- [Edit]  �Ȱ�ȯ 2008/03/26
	char		szRealItem[REAL_ITEM_LEN+1]; // Real Item��
	
} TABLECELL, *LPTABLECELL;

// Table�� ��ü Cell����. 
typedef struct tagTableCellInfo
{
	DWORD dwLength;
	short nCount;

    TABLECELL** pRec;

} TABLECELLINFO, *LPTABLECELLINFO;

// --> [Edit]  ��â�� 2005/11/29
// ����� �� ����
//Table Cell Edit
typedef struct tagUserCell
{
	short		nIndex;
	short		nOrgRow;
	short		nOrgCol;
	short		nMoveIndex;		// �̵���ġ
	
	short		nRow;
	short		nCol;

	short		nOrgLinkRow;
	short		nOrgLinkCol;
} USERCELL, *LPUSERCELL;

// Cell Edit info�� ��ü Cell����. 
typedef struct tagUserCellInfo
{
	DWORD dwLength;
	short nCount;
	int   nRowCount;
	int   nColCount;

    USERCELL** pUserRec;
} USERCELLINFO, *LPUSERCELLINFO;
// <-- [Edit]  ��â�� 2005/11/29


/***************************************************/
// Table�� Cell Link����. 
/***************************************************/
// Table�� ���� Cell Link����. 
typedef struct tagCellLink
{
	BYTE  byIsCaption;
	short nRow;
	short nCol;
	short nLinkRow;
	short nLinkCol;
	long  lDummy;

} CELLLINK, *LPCELLLINK;

// Table�� ��ü Cell Link ����. 
typedef struct tagCellLinkInfo
{
	DWORD dwLength;
	short nCount;

    CELLLINK** pRec;

} CELLLINKINFO, *LPCELLLINKINFO;

/***************************************************/
// Size ����. 
/***************************************************/
// Grid & Table�� �� Item�� ������ ����.
typedef struct tagItemSize
{
	short nSize;
	BYTE  bySysHidden;
	long  lDummy;

} ITEMSIZE,*LPITEMSIZE;

// Table�� ��ü Cell����. 
typedef struct tagItemSizeInfo
{
	DWORD dwLength;
	short nCount;

    ITEMSIZE** pRec;

} ITEMSIZEINFO, *LPITEMSIZEINFO;


/***************************************************/
// ���� ����.
/***************************************************/
typedef struct tagReferInfo
{
	short		nBasisKeyIdx;			// ���� ��ü�� Key Index
	char		szBasisItem[ITEM_LEN+1];// ���� ��ü�� Item

	short		nReferCnt;				// ���� ������ �޴� Item�� ����.
	LPSTR*		plpszItem;				// ���� ������ �޴� Item��.
	long		lDummy;					// ����.
							
} REFERINFO, *LPREFERINFO;

typedef struct tagCellRange
{
	short nRow;
	short nCol;
	short nToRow;
	short nToCol;

} CELLRANGE, *LPCELLRANGE;


/***************************************************/
// Grid Line ����.(���α׸���� column�� �����ʿ�, ���α׸���� row�� �Ʒ��ʼ��� �����Ѵ�.)
// 2003.09.03 �׸����� ���������� ������� �ʴ´�.
/***************************************************/
#if FALSE
typedef struct tagGridLine
{
	short nPos;
	BYTE  byUseLine;
	short nCrIndex;
	short nWidth;

} GRIDLINE, *LPGRIDLINE;
#endif

/***************************************************/
// Table Border����.
/***************************************************/
typedef struct tagBorderInfo
{
	short  nStyle;
	short  nCrIndex;
	short  nWidth;
} BORDERINFO, *LPBORDERINFO;

typedef struct tagTblBorder
{
	short nRow;
	short nCol;
	BYTE  byUseLRTB;
	CPtrArray* pBorderArray;

} TBLBORDER, *LPTBLBORDER;

/***************************************************/
// Cell�� ��Ʈ�Ѻ� ����. 
/***************************************************/
// Combo Control
typedef struct 
{
	short nRow;
	short nCol;
	CString strItemList;
	long  lDummy;

} CELLCOMBO, *LPCELLCOMBO;

typedef struct 
{
	short	nRow;
	short	nCol;
	short   nMaxLen;				// ��������°� 
	BYTE	byValueShow;			// 00=00 ������  
	CString strChoiceList;			// �����Է��� ����� ����Ʈ 
	CString strFileName;			// Ini ���ϸ� 
	CString strSectionName;			// [Ini]���Ǹ� 
	long  lDummy;
} CELLCOMBOEX, *LPCELLCOMBOEX;

// Check Control
typedef struct 
{
	short nRow;
	short nCol;
	short nCheckVal;
	short nUnCheckVal;
	CString strText;
	long  lDummy;

} CELLCHECK, *LPCELLCHECK;

// Spin Control
typedef struct 
{
	short nRow;
	short nCol;
	double dbMinVal;
	double dbMaxVal;
	double dbStep;
	double dbInitVal;
	long  lDummy;

} CELLSPIN, *LPCELLSPIN;

// Push Button Control
typedef struct 
{
	short nRow;
	short nCol;
	short nBtCrIndex;
	CString strText;
	long  lDummy;

} CELLPUSHBTN, *LPCELLPUSHBTN;

// Bitmap Button Control
typedef struct 
{
	short nRow;
	short nCol;
	BYTE  byStretch;
	CString strTitle;
	CString strNormalName;
	CString strDownName;
	long  lDummy;

} CELLBMPBTN, *LPCELLBMPBTN;

// Code Input Control
typedef struct 
{
	short nRow;
	short nCol;
	BYTE  byCatalog;
	long  lDummy;

} CELLCODECTRL, *LPCELLCODECTRL;

// Edit Or Password Edit Control
typedef struct 
{
	short nRow;
	short nCol;
	short nMaxLen;
	long  lDummy;

} CELLEDIT, *LPCELLEDIT;

// Progress Control
typedef struct 
{
	short nRow;
	short nCol;
	long  lMinVal;
	long  lMaxVal;
	short nStartPos;		 // 0 : Right, 1:left
	short nCaptionShow;      // 0 : ǥ�þ���, 1 : ǥ��. 
//	long  lDummy;

} CELLPRGRS, *LPCELLPRGRS;

#ifdef GRADIENT_USE 
typedef struct 
{
	short nRow;
	short nCol;
	long  lStartClr;
	long  lEndClr;
	short nMode;			 
	long  lDummy;
} CELLGRADIENTS, *LPCELLGRADIENTS;
#endif

/***************************************************/
// Cell�� Tooltip ����.
/***************************************************/
typedef struct 
{
	short			nFmtCnt;				//����ϴ� ���� ���ڿ��ǰ���. ex) "%s�� �ŷ����� %s�Դϴ�."         --> 2
											//������ 0�� ���� �ܼ��� strText�� �������� �����ش�.
	CStringArray*	pItemArray;				//���� ���ڿ��� ��ġ�� Item�� array
	CString			strText;				//Format String ex) "%s�� �ŷ����� %s�Դϴ�."
	long			lDummy;

} TTINFO, *LPTTINFO;

/***************************************************/
// Cell�� Text ����. 
/***************************************************/
typedef struct 
{
	short nRow;
	short nCol;
	CString strText;

} CELLTEXT, *LPCELLTEXT, CELLFORMULA, *LPCELLFORMULA, CELLFIXKEY, *LPCELLFIXKEY, CELLRECORDNAME, *LPCELLRECORDNAME, CELLINPUTMASK, *LPCELLINPUTMASK,CELLREPLACETEXT, *LPCELLREPLACETEXT,CELLCAPTIONTEXT, *LPCELLCAPTIONTEXT;

/***************************************************/
// �ǽð� ���� �׸�
/***************************************************/
typedef struct tagREALCONBITS
{
	unsigned long nOperator		: 4;	// ���� ��(=, !=, ...)
	unsigned long nTrueAction	: 4;	// ���� �����϶� ��� ���� ���۷��̼�(insert,update,delete,...)
	unsigned long nFalseAction	: 4;	// ���� �����϶� ��� ���� ���۷��̼�(insert,update,delete,...)
	unsigned long nTrueIndex	: 5;	// ���� �����϶� ���� ���� �ε���.
	unsigned long nFalseIndex	: 5;	// ���� �����϶� ���� ���� �ε���.
	unsigned long lDummy		: 10;	// ����.
	// 32 Bits
} REALCONBITS; // 4 Byte

typedef struct tagRealConItem
{
	BYTE		byRec;					// Real Record
	char		szItem[ITEM_LEN+1];		// ���� ������.
	char		szValue[RC_VALUE_MAX+1];// �񱳰�.
	REALCONBITS RConBits;				// ���� ����.
	long		lDummy;					// ����.

} REALCONITEM, *LPREALCONITEM;

typedef struct tagRECTYPEBITS
{
	unsigned long bKeyUse		: 1;	// Key�� ã��.
	unsigned long bSubKeyUse	: 1;	// SubKey�� ã��.
	unsigned long bThirdKeyUse	: 1;	// ThirdKey�� ã��.
	unsigned long lDummy		: 29;	// ����.
	// 32 Bits
} RECTYPEBITS; // 4 Byte

typedef struct tagRecType
{
	BYTE		byRec;					// Real Record
	BYTE		byDefAction;			// Ű�� �ش��ϴ� �ο�/�÷��� ���������� ���۷��̼�.
	BYTE		nConIndex;				// ���� �ε���.
	//long		lDummy;					// ����.
	RECTYPEBITS RTBits;			

} REALRECTYPE, *LPREALRECTYPE;

typedef struct tagRealConInfo
{
	DWORD		dwLength;
	BYTE		nRecCount;				// Real Record ���� ī��Ʈ.
	BYTE		nConCount;				// ���� ������ ī��Ʈ.
	REALRECTYPE** ppRecType;			// Real Record Type�� ����.
 	REALCONITEM** ppCondition;			// ���� ���ǵ�.

} REALCONINFO, *LPREALCONINFO;


/***************************************************/
// New ���� �׸�
/***************************************************/
typedef struct tagNewReferBits
{
	unsigned long nCmpType		: 2;	// �� ����(0:��� ��, 1:�������� ����, 2:���ں� 2:Target Item�� ���� ����(��ü���ڴ� �ش� �ȵ�))
	unsigned long nOperator		: 3;	// ���� ��(>,<,=,>=,<=,!=).
	unsigned long bUseSymbol	: 1;	// ��ü���� ��� ����.
	unsigned long bUseBackCr	: 1;	// Back Color ��� ����.
	unsigned long bUseTextCr	: 1;	// Text Color ��� ����.
	unsigned long nBackCrIndex	: 9;	// Back Color �÷� �ε���(max : 511).
	unsigned long nTextCrIndex	: 9;	// Text Color �÷� �ε���(max : 511).
	unsigned long lDummy		: 6;	// ����.
	// 32 Bits
} NEWREFERBITS; // 4 Byte

typedef struct tagNewReferCon
{
	NEWREFERBITS NRBits;				// New ���� ������.

	char		szTgtItem[ITEM_LEN+1];	// �� ������.
	double		dTgtConstant;			// �� �����.
	char		szSymbol[NR_SYMBOL_MAX+1];// ��ü����.
	long		lTgtCharValue;			 // ���ں�(1BYTE).

} NEWREFERCON, *LPNEWREFERCON;

typedef struct tagNewReferType
{
	char		szItem[ITEM_LEN+1];		// ���� ������.
	BYTE		nKeyIndex;				// ���� Key Index.
	BYTE		nCount;					// ���� ī��Ʈ.
	NEWREFERCON** ppNRCon;				// ���� ����.
	short		nTop;					// Top��ġ 	
	short		nLeft;					// Left��ġ 
	short		nBottom;				// Bottom��ġ 	
	short		nRight;					// Right��ġ 
//	long		lDummy;					// ����.
} NEWREFERTYPE, *LPNEWREFERTYPE;

typedef struct tagNewReferInfo
{
	BYTE		nCount;					// ���� Ÿ�� ī��Ʈ.
	NEWREFERTYPE** ppNRType;			// ���� Ÿ�Ժ� ����.

} NEWREFERINFO, *LPNEWREFERINFO;

// �ǽð��ÿ� �ش� ���� Ÿ�Կ� ����. 
// �����۸��� �������� �ٲ� ��쿡 ���.
typedef struct tagREALCHGITEC
{
	BYTE	byRec;			// �ǽð� ���ڵ� ����(0x10, 0x34)
	BYTE	byUpdate;		// 1: Update, 0: Insert
	char	szItem[ITEM_LEN+1];
	char	szChgItem[ITEM_LEN+1];
}REALCHGITEC;


/***************************************************/
// ȣ�� �ֹ� ����ü.
/***************************************************/
typedef struct 
{
	char	szOrderNo[ORDER_NO_LEN+1];		//�ֹ���ȣ.
	long	lAmount;						//����.

} HOGAORDER, *LPHOGAORDER;

typedef struct 
{
	BYTE	byOption;						//0x01 : �ֹ�, 0x02: STOP
	BYTE	byIsAll;						//�ϰ� ����/����ΰ��.
	BYTE	byOrderType;					//�ŵ�/�ż�����.
	char	szOrderPrice[20];				//�ֹ�����.

} ORDERSRC, *LPORDERSRC;


// 
typedef struct 
{
	char szHogaPrice[20];	// ȣ������(ȣ�����̺� ���εǴ� ����)
	char szOrderPrice[30];	// ���ü�ᰡ, ��ü�ᰡ, ���ð���, ���ð���
	long lQty;				// ����
	long byPriceState;		// ���ݻ���
							// 0x00000000 : 
							// 0x00000001 : ���ð���
							// 0x00000002 : ���ð���
							// 0x00000004 : �ܰ�
							// 0x00000008 : ��ü��

	char szOrderNo[20];		// �ֹ���ȣ(��ü���)
	BYTE byMemagb;			// �Ÿű���

} HO_TABLE_ORDERDATA, *LPHO_TABLE_ORDERDATA;

/***************************************************/
// ü������ Attribute.
/***************************************************/
typedef struct
{	
	BYTE	byAttr;			// ü������ Attribute(Rp)
	BYTE	byAttr1;		// Real
	BYTE	byAttr2;		// Real
	BYTE    byAttr3;		// Real
	BYTE	byAttr4;		// Real
	BYTE	byAttr5;		// Real
	BYTE	byAttr6;		// Real
	BYTE	byAttr7;		// Real
	BYTE	byAttr8;		// Real
	BYTE	byAttr9;		// Real
	BYTE	byAttr10;		// Real
	BYTE	byAttr11;		// Real
	BYTE	byAttr12;		// Real
	BYTE    byAttr13;		// Real
	BYTE	byAttr14;		// Real
	BYTE	byAttr15;		// Real
	short	nLastPos;		// Position

} TREND_ATTR, *LPTREND_ATTR;


typedef struct 
{
	char	szCode[20];			// �����ڵ�
	short	nKeyIndex;			// Key Index

	long	lVolData1;			// �̰��� ���� (����)
	long	lVolData2;			// �̰��� ���� (����)
	long	lVolData3;			// �̰��� ������(����)

} GRAPH_CELL_DATA, *LPGRAPH_CELL_DATA;

/***************************************************/
// ȣ�����̺� ���� ���� ����
/***************************************************/
typedef struct 
{
	long lConfigBit;			// ȣ�����̺� ���� ���� 
								// 0x00000000 ������
								// 0x00000001 ������
								// 0x00000002 ������
								// 0x00000004 ������
								// 0x00000008 ������
								// 0x00000010 �ü��޸�(�������� ǥ�ü� )
								// 0x00000020 �ִ��ܷ� Bold

	long lClrUseBit;			// �����뿩��
								// 0x00000000 ������
								// 0x00000001 ���Ͻð���	
								// 0x00000002 ���ϰ���	
								// 0x00000004 ����������	
								// 0x00000008 ����������	
								// 0x00000010 PIVOT 2������ 
								// 0x00000020 PIVOT 1������ 
								// 0x00000040 PIVOT ���ؼ�  
								// 0x00000080 PIVOT 1������ 
								// 0x00000100 PIVOT 2������ 
								
	long lOrderBit;				// �ֹ��� ���̺�
								// 0x00000000 ������
								// 0x00000001 �ֹ����� "��"���õ�����
								// 0x00000002 �ֹ����� "��" ������
								// 0x00000004 �ֹ����� "��" �ܰ�
								// 0x00000008 �ֹ����� "��"��ü��

	char szOpen     [10];		// ���Ͻð�
	char szHigh     [10];		// ���ϰ�
	char szLow      [10];		// ��������
	char szPrice    [10];		// �������簡
	char szPreClose [10];		// ��������
	
	char szResist2	[10];		// �Ǻ�2������
	char szResist1	[10];		// �Ǻ�1������
	char szPivot	[10];		// �Ǻ�
	char szSupport1 [10];		// �Ǻ�1������
	char szSupport2	[10];		// �Ǻ�2������

	COLORREF clrOpen;			// ���Ͻð���	 
	COLORREF clrHigh;			// ���ϰ���	 
 	COLORREF clrLow;			// ����������	 
	COLORREF clrPreClose;		// ����������	 
	COLORREF clrResist2;		// PIVOT 2������ 
	COLORREF clrResist1;		// PIVOT 1������ 
	COLORREF clrPivot;			// PIVOT ���ؼ�  
	COLORREF clrSupport1;		// PIVOT 1������ 
	COLORREF clrSupport2;		// PIVOT 2������ 
	COLORREF clrDuplicate;		// �ߺ��׸� ����

	

} HOGA_BASE_PRICE_INFO, *LPHOGA_BASE_PRICE_INFO;

/***************************************************/
// ����ȣ�� ����
/***************************************************/
//typedef struct 
//{
//	long lUseBit;				// ���� ����
//	short nDispBitCount;        // ǥ���� �����׸񰳼�
//	BOOL bIsMaxRemQty;			// �ִ��ܷ�����
//
//} HOGA_INFO, *LPHOGA_INFO;


/***************************************************/
// �����ڵ�����ũ�� �ؿܼ��� ���� ǥ�ø� ���� ���� ����ü
/***************************************************/
typedef struct
{	
	BYTE	byFmt;				// ����ũŸ��
	BYTE	byMarket;			// ���屸��
	BYTE	bySpot;				// ������ ǥ�ÿ���
	BYTE	byLog;				// ����
	BYTE    byLogDispSize;		// ����ǥ�� ����( ������ ǥ���ΰ� �������� )
	BYTE	byPrecision;		// �Ҽ��� ����
	BYTE	byItemPrecision;	// ������ ���� �Ҽ��� ����
	char	szTickSize[16];		// �ؿܼ��� TickSize
	char	szTickValue[16];	// �ؿܼ��� TickValue
	char	szPriceInfo[2];		// �ŷ��Ұ���ǥ������
	BYTE	byIsSpread;			// �������� �����ΰ��
	DWORD	dwBitInfo;			// ����ũ �ΰ�����(MASKINFO ����)
} ITEM_PRICE_FORMAT, *LPITEM_PRICE_FORMAT ;


#pragma pack(pop)


class CGridInfo;
/***************************************************/
// Grid  Header ����� Class
/***************************************************/
class CGridHeader : public GRIDHEADERINFO, public CObject
{
public:
	DECLARE_SERIAL(CGridHeader)
	
	CGridHeader();
	CGridHeader(const CGridHeader *r );

	~CGridHeader();

	void		SetGridInfo(CGridInfo* pGrid){m_pGrid = pGrid;}
	void		Initialize();
	void		Clear(BOOL bInitCnt = TRUE);
	void		SetVersion(DWORD dwBaseVer){m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);
// --> [Edit]  ��â�� 2005/11/29
	// �����Cell���� 
	void		SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
// <-- [Edit]  ��â�� 2005/11/29

	// Moving Colums or Rows
	void		Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol = TRUE);
	// Insert Columns Or Rows
	void		Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol = TRUE);
	// Remove Columns Or Rows
	void		Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol = TRUE);
	// Copy Columns Or Rows
	void		Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol = TRUE);
	
	const CGridHeader& operator=(const CGridHeader& other);

private:
	DWORD		m_dwVersion;
	CGridInfo*	m_pGrid;
};

/***************************************************/
// Grid  Body ����� Class
/***************************************************/
class CGridBody : public GRIDBODYINFO, public CObject
{
public:
	DECLARE_SERIAL(CGridBody)
	
	CGridBody ();
	CGridBody (const CGridBody *r );

	~CGridBody();

	void		SetGridInfo(CGridInfo* pGrid){m_pGrid = pGrid;}
	void		Initialize();
	void		Clear(BOOL bInitCnt = TRUE);
	void		SetVersion(DWORD dwBaseVer){m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);
// --> [Edit]  ��â�� 2005/11/29
	// �����Cell���� 
	void		SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
// <-- [Edit]  ��â�� 2005/11/29

	short		GetKeyIndexCount();
	LPCTSTR		GetKeyItem(short nKeyIndex = 0);
	LPCTSTR		GetSubKeyItem(short nKeyIndex = 0);
	LPCTSTR		GetThirdKeyItem(short nKeyIndex = 0);
	BOOL		GetKeyIndexMinMaxPos(unsigned short nKeyIndex, unsigned short& nMinPos, unsigned short& nMaxPos);
	LPGRIDBODY	GetBodyRecordInfo ( short nKeyIndex, LPCTSTR lpszItem );
	
	int			GetFlushItemListArray ( );
	
	// �޸�,CodeDrag,���� ������ ����ϴ� Cell�� �����ϴ� ���� üũ�Ѵ�.
	long		GetBaseBoolBitCheck ( long dwBaseboolBit );
	
	// Move Columns Or Rows
	void		Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol = TRUE);
	// Insert Columns Or Rows
	void		Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol = TRUE);
	// Remove Columns Or Rows
	void		Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol = TRUE);
	// Copy Columns Or Rows
	void		Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol = TRUE);

	const CGridBody& operator=(const CGridBody& other);

public:
	CUIntArray	m_ItemArray;

private:
	DWORD		m_dwVersion;
	CGridInfo*	m_pGrid;
	//int			m_nRowCnt, m_nColCnt, m_nHRows, m_nHCols;
};


class CTableInfo;
/***************************************************/
// Table  Cell ����� Class
/***************************************************/
class CTableCell : public TABLECELLINFO, public CObject
{
public:
	DECLARE_SERIAL(CTableCell)
	
	CTableCell();
	CTableCell (const CTableCell *r );

	~CTableCell();

	void		SetTableInfo(CTableInfo* pTable){m_pTable = pTable;}
	void		Initialize();

	void		Clear( BOOL bInitCnt = TRUE );
	void		Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol = TRUE);

	void		SetVersion(DWORD dwBaseVer){m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);
// --> [Edit]  ��â�� 2005/11/29
	// �����Cell���� 
	void		SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
// <-- [Edit]  ��â�� 2005/11/29

	short		GetKeyIndexCount();
	LPCTSTR		GetKeyItem(short nKeyIndex = 0);
	LPCTSTR		GetSubKeyItem(short nKeyIndex = 0);
	LPCTSTR		GetThirdKeyItem(short nKeyIndex = 0);
	TABLECELL*	GetRowColCell(int nColCnt, int nRow, int nCol);
	int			GetFlushItemListArray ();

	// �޸�,CodeDrag,���� ������ ����ϴ� Cell�� �����ϴ� ���� üũ�Ѵ�.
	long		GetBaseBoolBitCheck ( long dwBaseboolBit );

	const CTableCell& operator=(const CTableCell& other);
	void		CopyTableCell     ( LPTABLECELL pScr, LPTABLECELL pDest , int nOption = 0 );

public:
	CUIntArray	m_ItemArray;

private:
	DWORD		m_dwVersion;
	CTableInfo*	m_pTable;
};

/***************************************************/
// Table Link ����� Class
/***************************************************/
class CTableLink : public CELLLINKINFO, public CObject
{
public:
	DECLARE_SERIAL(CTableLink)
	
	CTableLink();
	~CTableLink();

	void		Initialize();
	void		Clear();
	void		SetVersion(DWORD dwBaseVer){m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);

	const CTableLink& operator=(const CTableLink& other);
	
private:
	DWORD		m_dwVersion;
};

/***************************************************/
// Size ����� Class
/***************************************************/
class CItemSize : public ITEMSIZEINFO, public CObject
{
public:
	DECLARE_SERIAL(CItemSize)
	
	CItemSize();
	~CItemSize();

	void		Initialize(int nDefCount, int nDefSize);
	void		SetResize( int nNewCount, int nDefSize );

	void		Clear();
	ITEMSIZE*	GetAt(int nIndex);
	BOOL		SetAt(int nIndex, short nSize = -1, BYTE  bySysHidden = 2);
	void		SetVersion(DWORD dwBaseVer){m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);
	
	// Move
	void		Move(DWORD nFrom, DWORD nDest);
	// Insert
	void		Insert(DWORD nAddIndex, DWORD nAddCount, int nDefSize);
	// Remove
	void		Remove(DWORD nDelIndex, DWORD nDelCount);
	// Copy
	void		Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo);
	
	const CItemSize& operator=(const CItemSize& other);

private:
	DWORD		m_dwVersion;
};

/***************************************************/
// Real Condition ���� Class
/***************************************************/
class CRealCondition : public REALCONINFO, public CObject
{
public:
	DECLARE_SERIAL(CRealCondition)
	
	CRealCondition();
	~CRealCondition();

	void		SetGridInfo(CGridInfo* pGrid){m_pGrid = pGrid;}
	void		Clear();
	void		SetVersion(DWORD dwBaseVer){m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);

	const CRealCondition& operator=(const CRealCondition& other);

public:
	REALRECTYPE* GetRealRecType(BYTE byRec);
	REALCONITEM* GetRealCondition(short nIndex = 0);
private:
	DWORD		m_dwVersion;
	CGridInfo*	m_pGrid;
};

/***************************************************/
// New ���� ���� Class
/***************************************************/
class CNewRefer : public NEWREFERINFO, public CObject
{
public:
	DECLARE_SERIAL(CNewRefer)
	
	CNewRefer();
	~CNewRefer();

	void		Clear();
	void		SetVersion(DWORD dwBaseVer){m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);

	const CNewRefer& operator=(const CNewRefer& other);

public:
	NEWREFERTYPE*	GetNewReferType(LPCTSTR lpszItem, BYTE nKeyIndex = 0);
	
	BOOL		SetPropList(LPSTR lpBuf );
	BOOL		GetPropList(CString& strList);
	
	NEWREFERTYPE* GetNewReferTypePtr( LPSTR lpTypeBuf );
	CString		GetNewReferTypeString(NEWREFERTYPE* pNRType);
private:
	DWORD		m_dwVersion;
};

/***************************************************/
// Cell Covered ����� Class
/***************************************************/
class CCellCovered : public CPtrArray
{
public:
	DECLARE_SERIAL(CCellCovered)
	
	CCellCovered();
	~CCellCovered();

	void		Clear();
	void		SetVersion(DWORD dwBaseVer){m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);
	CELLRANGE*	GetCoveredRange(short nRow, short nCol);

	// Moving Colums or Rows
	void		Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol = TRUE);
	// Insert Columns Or Rows
	void		Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol = TRUE);
	// Remove Columns Or Rows
	void		Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol = TRUE);
	// Copy Columns Or Rows
	void		Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol = TRUE);

	const CCellCovered& operator=(const CCellCovered& other);
public:
	DWORD		m_dwLength;

private:
	DWORD		m_dwVersion;
	
	void		MoveRowColIndex(short& nRowCol, short& nToRowCol, DWORD nFrom, DWORD nDest, BOOL bToRight);
	void		InsertRowColIndex(short& nRowCol, short& nToRowCol, DWORD nAddIndex, DWORD nAddCount);
	BOOL		RemoveRowColIndex(short& nRowCol, short& nToRowCol, DWORD nDelIndex, DWORD nDelCount);
};

/***************************************************/
// Line(Border) ����� Class
/***************************************************/
class CLineBorder : public CObject
{
public:
	DECLARE_SERIAL(CLineBorder)
	
	CLineBorder(BOOL bIsGrid = TRUE);
	~CLineBorder();

	void		Clear();
	void		SetVersion(DWORD dwBaseVer){m_dwVersion = dwBaseVer;}

	void		SetGridState(BOOL bIsGrid){m_bIsGrid = bIsGrid;}
	BOOL		GetGridState(){return m_bIsGrid;}
	void		Serialize(CArchive &ar);

// --> [Edit]  ��â�� 2005/11/29
	// �����Cell���� 
	void		SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
// <-- [Edit]  ��â�� 2005/11/29
	
	BOOL		SetPropList(LPSTR lpBuf );
	BOOL		GetPropList(CString& strList);
	
	// Moving Colums or Rows
	void		Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol = TRUE);
	// Insert Columns Or Rows
	void		Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol = TRUE);
	// Remove Columns Or Rows
	void		Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol = TRUE);
	// Copy Columns Or Rows
	void		Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol = TRUE);

	const CLineBorder& operator=(const CLineBorder& other);

public:
	// �׸����� Line�� ������� ������ ���� ó�������� ���ܵ�(2003.09.03)
//	CPtrArray*	m_pLine;
	CPtrArray*	m_pBorder;

private:
	DWORD		m_dwVersion;
	BOOL		m_bIsGrid;

	void		MoveRowColIndex(short& nRowCol, DWORD nFrom, DWORD nDest, BOOL bToRight);
	void		InsertRowColIndex(short& nRowCol, DWORD nAddIndex, DWORD nAddCount);
	BOOL		RemoveRowColIndex(short& nRowCol, DWORD nDelIndex, DWORD nDelCount);

};

/***************************************************/
// Cell Control ����� Class
/***************************************************/
class CCellCtrl : public CObject
{
public:
	DECLARE_SERIAL(CCellCtrl)
	
	CCellCtrl();
	~CCellCtrl();

	void		Clear();
	void		ClearCtrl(int nCtrlID);
	void		SetVersion(DWORD dwBaseVer){m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);
	
	BOOL		SetCtrlPropList(int nCtrlID, LPSTR lpBuf );
	BOOL		GetCtrlPropList(int nCtrlID, CString& strList);
	
	BOOL		GetAllCtrlPropList ( CString& strList);
	BOOL		SetAllCtrlPropList ( CString& strList);

	void*		GetCtrlInfo(int nCtrlID, short nRow, short nCol, BOOL bNewAlloc = FALSE);
	
	// Moving Colums or Rows
	void		Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol = TRUE);
	// Insert Columns Or Rows
	void		Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol = TRUE);
	// Remove Columns Or Rows
	void		Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol = TRUE);
	// Copy Columns Or Rows
	void		Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol = TRUE);

	const CCellCtrl& operator=(const CCellCtrl& other);

public:
	CPtrArray*	m_pComboArray;
	CPtrArray*	m_pCheckArray;
	CPtrArray*	m_pSpinArray;
	CPtrArray*	m_pPushBtnArray;
	CPtrArray*	m_pBMPBtnArray;
	CPtrArray*	m_pCodeCtrlArray;
	CPtrArray*	m_pPWEditArray;
	CPtrArray*	m_pEditArray;
	CPtrArray*	m_pPrgrsArray;
	CPtrArray*	m_pComboExArray;

#ifdef GRADIENT_USE 
	CPtrArray*	m_pGradientArray;
#endif

private:
	DWORD		m_dwVersion;

	void		MoveRowColIndex(short& nRowCol, DWORD nFrom, DWORD nDest, BOOL bToRight);
	void		InsertRowColIndex(short& nRowCol, DWORD nAddIndex, DWORD nAddCount);
	BOOL		RemoveRowColIndex(short& nRowCol, DWORD nDelIndex, DWORD nDelCount);

};

/***************************************************/
// Tooltip ����� Class
/***************************************************/
class CTTipArray : public CPtrArray
{
public:
	DECLARE_SERIAL(CTTipArray)
	
	CTTipArray();
	~CTTipArray();

	void		Clear();
	void		SetVersion(DWORD dwBaseVer){ m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);
	
	BOOL		SetPropList(LPSTR lpBuf );
	BOOL		GetPropList(CString& strList);

	
	LPTTINFO	GetTTipInfo(int nTipIndex, BOOL bNewAlloc = FALSE);

	const CTTipArray& operator=(const CTTipArray& other);

private:
	DWORD		m_dwVersion;
	
};

/***************************************************/
// ���� ����� Class
/***************************************************/
class CReferArray : public CPtrArray
{
public:
	DECLARE_SERIAL(CReferArray)
	
	CReferArray();
	~CReferArray();

	void		Clear();
	void		SetVersion(DWORD dwBaseVer){ m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);
	
	BOOL		SetPropList(LPSTR lpBuf );
	BOOL		GetPropList(CString& strList);

	LPREFERINFO GetReferInfoFromOwner(short nKeyIndex, LPCTSTR lpszItem);
	LPREFERINFO GetReferInfoFromSlave(short nKeyIndex, LPCTSTR lpszItem);

	const CReferArray& operator=(const CReferArray& other);

private:
	DWORD		m_dwVersion;
	
};

/***************************************************/
// Cell�� text�� �����ϴ� Class
/***************************************************/
class CCellTextArray : public CPtrArray
{
public:
	DECLARE_SERIAL(CCellTextArray)
	
	CCellTextArray();
	~CCellTextArray();

	// Array Type
	enum DXArrType
	{
		ATFormula,
		ATFixKey,
		ATUserLinkTag,
		ATRecordName,
		ATInputMask,
		ATReplaceText,
		ATCaptionText,
	};

	void		Clear();
	void		SetVersion(DWORD dwBaseVer){ m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);
	
	BOOL		SetPropList( LPSTR lpBuf      );
	BOOL		GetPropList( CString& strList );
	BOOL		GetRowColText(short nRow, short nCol, CString& strText);
	// [���߾�����] �ش���ġ�� �����۸��� ����Ѵ�.
	BOOL		GetRowColItemInfo( DWORD nRow, DWORD nCol, CString& strItem );
	BOOL		GetRowColItemCmp( DWORD nRow,  DWORD nCol, CString  strItem );
	int			GetRowColMultiRecordPos( CString  strItemInfo );

	BOOL		SetRowColText(short nRow, short nCol, CString strText , BOOL bOverWrite = TRUE);

	// FixKey�� ��츸 ���.
	LPCTSTR		GetKeyCode(short nKeyIndex);
	BOOL		SetKeyCode(short nKeyIndex, LPCTSTR lpszKeyCode);
	short		GetKeyIndex(LPCTSTR lpszCode);
	
	// Moving Colums or Rows
	void		Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol = TRUE, DXArrType arrType = ATFixKey);
	// Insert Columns Or Rows
	void		Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol = TRUE, DXArrType arrType = ATFixKey);
	// Remove Columns Or Rows
	void		Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol = TRUE, DXArrType arrType = ATFixKey);
	// Copy Columns Or Rows
	void		Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol = TRUE, DXArrType arrType = ATFixKey);

	const CCellTextArray& operator=(const CCellTextArray& other);

private:
	DWORD		m_dwVersion;
	void		MoveRowColIndex(short& nRowCol, DWORD nFrom, DWORD nDest, BOOL bToRight);
	void		InsertRowColIndex(short& nRowCol, DWORD nAddIndex, DWORD nAddCount);
	BOOL		RemoveRowColIndex(short& nRowCol, DWORD nDelIndex, DWORD nDelCount);
};

/***************************************************/
// Memo ����� Class
/***************************************************/
class CPosFlagArray : public CDWordArray
{
public:
	DECLARE_SERIAL(CPosFlagArray )
	
	CPosFlagArray();
	~CPosFlagArray();

	void		Clear();
	void		SetVersion(DWORD dwBaseVer){ m_dwVersion = dwBaseVer;}
	void		Serialize(CArchive &ar);
	
	BOOL		SetPropList(LPSTR lpBuf );
	BOOL		GetPropList(CString& strList);

	const CPosFlagArray& operator=(const CPosFlagArray& other);
	
private:
	DWORD		m_dwVersion;
	
};


class CMapRecordInfo: public CMapStringToOb
{
public:
	DECLARE_SERIAL(CMapRecordInfo)
	
	CMapRecordInfo();
	~CMapRecordInfo();

	void		Clear();
	void		SetVersion	( DWORD dwBaseVer){ m_dwVersion = dwBaseVer;}
	void		Serialize	( CArchive &ar);

	BOOL		SetPropList ( LPSTR lpBuf      );
	BOOL		GetPropList ( CString& strList );
	
	const CMapRecordInfo& operator=(const CMapRecordInfo& other);
	
private:
	DWORD		m_dwVersion;
};


////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------//
////////////////////////////////////////////////////////////////////
/***************************************************/
// Grid�� Table�� ���� Property Class
/***************************************************/
typedef CCellTextArray		CCaptionTextArray;
typedef CCellTextArray		CRelpaceTextArray;
typedef CCellTextArray		CRecordNameArray;
typedef CCellTextArray		CInputMaskArray;
typedef CCellTextArray		CFormulaArray;
typedef CCellTextArray		CFixKeyArray;
typedef CCellTextArray		CUserLinkTagArray;
class COgBase : public CObject
{
	
// Construction
public:
	DECLARE_SERIAL(COgBase)
	COgBase();
	virtual ~COgBase();

	virtual void  Serialize(CArchive &ar);
	virtual void  SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
	
	virtual void    SerializeCommonApply(CArchive &ar);
	virtual BOOL    SerializeCommonPropertyWrite( CString  strPropertyData );
	virtual CString SerializeCommonPropertyRead( );


	virtual const COgBase& operator=(const COgBase& other);
	virtual void  CopyVariable( const COgBase& other );
	
	BOOL	 GetMemNameFormatList ( LPCTSTR lpImportName, CString& strMemNameList );

	BOOL	 SetCellSizeDataBlobDataChange( CString  strPropertyData );
	CString  GetCellSizeBlobDataFromDataInfo ( );

	BOOL     SetCellCoveredBlobDataChange ( CString  strPropertyData );
	CString  GetCellCoveredBlobDataFromDataInfo( );

//	BOOL     SetBlobCopy(HGLOBAL* phBlobDest, HGLOBAL hBlobScr );

	void     SetBaseBoolBit(const long lBoolBit);
	const    long  GetBaseBoolBit();

//	int		 GetRecordTotalLen ( LPCTSTR lpszRecordName );
//	int      SetRecordTotalLen ( LPCTSTR lpszRecordName, long dwTotalLen );

public:
	BYTE			m_byUseForDll;			// DLL���� ������� �ǹ�.
	BOOL			m_bSkip;				// Skip ��� ����.
	DWORD			m_dwBaseVer;			// Base Version
	CSize			m_CtrlSize;				// Control Size
	int				m_nRowCnt,				// Grid Row Count
					m_nColCnt,				// Grid Column Count
					m_nFrozenRowCnt,		// Frozen Row Count
					m_nFrozenColCnt,		// Frozen Colunm Count
					m_nHiddenRowCnt,		// Row Index 0���� Hidden�� Row�� ��
					m_nHiddenColCnt,		// Column Index 0���� Hidden�� Column�� ��
					m_nDefColWidth,			// Default Column Count
					m_nDefRowHeight,		// Default Row Height
					m_nLineColorIndex,		// Grid Line Color Index( ���̺��� ���� ������� �� ���λ� ����.
											//						  �׸����� ���� �ٵ�κ��� VLine�� ����. ������ ���λ��� GGridInfo�� ������Ƽ�� ���� 	)
					m_nBackGndColorIndex,	// Grid �޿��� Color Index
					m_nSelectionMode,		// Grid Selection Mode(0:Table, 1:Single List Mode, 2: Multi List Mode, 3:One Cell 4: None)
					m_nLineStyle,			// Grid Line Style(0:Solid, 1:Dash, 2:Dot, 3:DashDot, 4:DashDotDot )
					m_nScrollMode,			// Scroll Mode(0:Auto, 1:Not Use, 2:Only Horizental, 3:Only Vertical, 4:Always )
					m_nResizeHeader,		// Header�� Resizing ���(0:Not Use, 1:Only Row, 2:Only Column, 3:Both, 4:Table Resize)
					m_nItemFlag,			// ItemFlag
					m_nLineMode;			// Grid Line Mode(0:Both, 1:Only Horizental, 2:Only Vertical, 3:Not Use)
	BOOL			m_bUseFormula;			// Formula �������.
	WORD			m_wScriptEvent;			// Script Event Kinds
	WORD			m_wFireLinkInfo;		// ���� ���� �߻� �������.
	WORD			m_nSpecialContent;		// �׸��� Ư����� ����.
	BYTE			m_byTailUse;			// Tail Grid Mode
	BYTE			m_byMultiTranUse;		// ����Ʈ�����
	BYTE			m_byMultiMarketUse;		// ���߽�����
	BYTE			m_byNextDataHeaderCheck;// ���������� üũ�� ������ 
	BYTE			m_byFixedRowCheck;		// ������ ó���� Row,Col���� ���� 
	
	int				m_nResize,				// Control Resizing(0:Resize, 1:Move)
					m_nBorderStyle,			// Control Border Style(0:None, 1:Border, 2:3D)
					m_nKeyIndexCnt;			// Key Count

	WORD			m_nDnDMode;				// Drag & Drop�� ���.
	WORD			m_nDragIndex;			// Drag�� Row/Col�� Index
	
	WORD			m_nPopupMenuMode;		// �޴� ǥ�� ���.
	WORD			m_nRealHighlight;		// Real����Ÿ ǥ�� ���.
	BYTE			m_byUseSelectColor;		// ����Ʈ �� �� ǥ�ù��(0: Invert Color, 1:������ Color)
	int				m_nSelectColorIndex;	// ����Ʈ �� ���� ��� Color Index
	
	
	BYTE			m_bySpecialHoga;		// ȣ�� ���̺� Ư���� �׸��� ó���� �ִ� ��� true.
	BYTE			m_byNeedMouseOverCheck;	// ���̺��� ��� Mouse OverCell���� true.

	BYTE			m_byUseAmountGraph;		// ȣ�� ���̺��� �ܷ� �׷����� ����ϴ����� ����.
	int				m_nBorderColorIndex;	// ��Ʈ�� ���� �÷� �ε���.

	CString			m_strRPImportRecord;	// RP Import Nmae
	CString			m_strRealImportRecord;	// Real Import Nmae
	CString			m_strRQExportRecord;	// RP Export Nmae

//	CString			m_strCommTrName;		// RQName
	CString			m_strOptionQueryInfo;	
	CString			m_strPrevCtrlName;		// Prev Button Control Name
	CString			m_strNextCtrlName;		// Next Button Control Name
	int				m_nDataType;			// ����Ÿ Ÿ�� (0:TopInsert, 1:TopUpdate, ...)

//	BYTE			m_byUseDelayTimer;		// �ǽð� Delay Timer ��� �÷���.
// m_byUseDelayTimer �������� m_byMultiItemUse ���� �����Ѵ�.
	BYTE			m_byMultiItemUse;		// ����Ʈ�����(����Row����)

	CItemSize*		m_pRowSize;				// Row Size Info
	CItemSize*		m_pColSize;				// Column Size Info
	CCellCovered*	m_pCovered;				// Covered Info
	CCellCtrl*		m_pCellCtrl;			// Cell Control Info
	CTTipArray*		m_pTTip;				// ToolTip Info	
	CFormulaArray*  m_pFormula;				// Formula Info
	CFixKeyArray*	m_pFixKey;				// Fixed Key Info
	CNewRefer*		m_pNewRefer;			// ���� ����.
	CUserLinkTagArray* m_pUserLinkArray;	// ����� �������� �ױ� ���.

// --> [Edit]  ��â�� 2006/06/16
// Version 3 m_pmapRecordInfo���� ����:
	CMapRecordInfo*  m_pmapRecordInfo;			// Record�� �������� .
	CRecordNameArray* m_pRecordNameArray;		// Record���̸� ����
	CInputMaskArray*  m_pInputMaskArray;		// �Է¸���ũ ���� 	
	CRelpaceTextArray*  m_pReplaceTextArray;	// ��ü���� ���� 	
	CCaptionTextArray*  m_pCaptionTextArray;	// ĸ�ǹ��� ���� ���� 	
// <-- [Edit]  ��â�� 2006/06/16

	CLineBorder*	m_pBorderInfo;			// Border Info
public:
	// Moving Colums or Rows
	virtual BOOL   Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol = TRUE);
	// Insert Columns Or Rows
	virtual BOOL   Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol = TRUE);
	// Remove Columns Or Rows
	virtual BOOL   Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol = TRUE);
	// Copy Columns Or Rows
	virtual BOOL   Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol = TRUE);

};

/***************************************************/
// Grid�� ��� ���� ����� Class
/***************************************************/
class CGridInfo : public COgBase
{
// Construction
public:
	DECLARE_SERIAL(CGridInfo)
	CGridInfo();
	~CGridInfo();

	void Serialize(CArchive &ar);
	void SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );

	const CGridInfo& operator=(const CGridInfo& other);
	void  CopyVariable( const CGridInfo& other );

	// ���̾�α׿��� ����ϱ� ���ؼ� �߰�.
	void SetDefault(int nRowCnt, int nColCnt, int nHRowCnt, int nHColCnt, int nSubCnt);
	CString	GetDumpText									( int nOption = 0 );

	CString  GetGridBodyPropertyDataFromBlobData		( int nControlMode = dxHGrid );
	CString  GetGridHeaderPropertyDataFromBlobData		( int nControlMode = dxHGrid );
	CString  GetRealConditionPropertyDataFromBlobData	( );

	BOOL  SetGridBodyDataBlobDataChange			( CString  strPropertyData );
	BOOL  SetGridHeaderDataBlobDataChange		( CString  strPropertyData );
	BOOL  SetRealConditionDataBlobDataChange	( CString  strPropertyData );

	void  SetBoolBit(const long lBoolBit);
	const long  GetBoolBit();

//	BOOL  SetCellSizeDataBlobDataChange		( HGLOBAL* phBlob );

	int   GetPosFromItemValue				( short nKeyIndex, 
											   LPCTSTR lpItem, 
											   short nItemFlag = -1,
											   int nControlMode = dxHGrid );

	int   SetItemValueChange					( short nKeyIndex, 
											   LPCTSTR lpOldItem, 
											   LPCTSTR lpNewItem, 
											   int& nRecRow,
											   int& nRecCol,
											   int nControlMode = dxHGrid );
public:

	short			m_nGridMode;			// ����/���� �׸��� ����.
	int				m_nVirtualMode;			// Virtual Grid Mode ( 0 : ������, 1 : ��Ÿ�� �и� )
				
	int				m_nSortMode,			// Sort (0:������, 1:Normal, 2:Looping)
					m_nHeaderRowCnt,		// Grid Header Row Count
					m_nHeaderColCnt,		// Grid Header Column Count
					m_nSubItemCnt,			// Sub Item Count (Sub Row Count)
					m_nBlockCount,			// Block Count(�����п�)
					m_nOddColorIndex,		// Ȧ�� ����� Color Index
					m_nEvenColorIndex,		// ¦�� ����� Color Index
					m_nMaxDataCnt,			// ����Ÿ ��û �ִ� ī��Ʈ.
					m_nScrollAction;		// ��Ʈ�ѽ��� ��� ���(0:������, 1:����ȸ )
					
	BOOL			m_bUseBlockColor;		// Block Count����� Block Color�� ���������� ����.
	BOOL			m_bUse3DButtonHeader;	// ����� 3D Button ��� ����.
	WORD			m_nAllowSameKey;		// Key�� �ߺ� ��� ��� ����.
	WORD			m_nAllowSameSubKey;		// SubKey�� �ߺ� ��� ��� ����.
	WORD			m_nAllowSameThirdKey;	// ThirdKey�� �ߺ� ��� ��� ����.
	BYTE			m_byHeaderMove;			// Header Move ��� ����.
	WORD			m_nFixedHeaderMoveCnt;	// ��� �̵��� ���� ���� �÷���.

	int				m_nBHLineColorIndex,	// Grid Body HLine Color Index
					m_nHVLineColorIndex,	// Grid Header VLine Color Index
					m_nHHLineColorIndex;	// Grid Header HLine Color Index
	BYTE			m_bySaveColSize;		// Grid �÷� �������� ���� ����.

	CGridHeader*	m_pGridHeader;			// Grid Header Info Array
	CGridBody*		m_pGridBody;			// Grid Body Info Array
	CRealCondition* m_pRealCon;				// �ǽð� ����. 

#ifdef MULTI_CAPTION_USE					// �ٱ��� ���ɼ� 
	CGXCaptionData*	m_pGridMultiHeader;
	CGXCaptionData*	m_pGridMultiBody;
#endif

public:
	virtual BOOL   CanMove(BOOL bMoveCol = TRUE);
	virtual BOOL   CanInsert(DWORD& nAddIndex, DWORD& nAddCount, BOOL bInsertCol = TRUE);
	virtual BOOL   CanRemove(DWORD& nDelIndex, DWORD& nDelCount, BOOL bRemoveCol = TRUE);
	virtual BOOL   CanCopy(DWORD& nSrcFrom, DWORD& nSrcTo, DWORD& nDestFrom, DWORD& nDestTo, BOOL bCopyCol = TRUE);
	
	// Moving Colums or Rows	
	virtual BOOL   Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol = TRUE);
	// Insert Columns Or Rows
	virtual BOOL   Insert(DWORD nAddIndex, DWORD nAddCount, BOOL bInsertCol = TRUE);
	// Remove Columns Or Rows
	virtual BOOL   Remove(DWORD nDelIndex, DWORD nDelCount, BOOL bRemoveCol = TRUE);
	// Copy Columns Or Rows
	virtual BOOL   Copy(DWORD nSrcFrom, DWORD nSrcTo, DWORD nDestFrom, DWORD nDestTo, BOOL bCopyCol = TRUE);
};


/***************************************************/
// Table�� ��� ���� ����� Class
/***************************************************/
class CTableInfo : public COgBase
{
// Construction
public:
	DECLARE_SERIAL(CTableInfo)
	CTableInfo();
	~CTableInfo();

	void Serialize(CArchive &ar);
// --> [Edit]  ��â�� 2005/11/29
	// �����Cell���� 
	void SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
// <-- [Edit]  ��â�� 2005/11/29

	const CTableInfo& operator=(const CTableInfo& other);

	// ���̾�α׿��� ����ϱ� ���ؼ� �߰�.
	void SetDefault(int nRowCnt, int nColCnt);

	BOOL  SetTableCellInfoBlobDataChange	( CString  strPropertyData );
	BOOL  SetTableCellLinkBlobDataChange	( CString  strPropertyData );

	CString  GetTableCellInfoBlobDataFromDataInfo( );
	CString  GetTableCellLinkBlobDataFromDataInfo( );
	
	virtual BOOL   Move(DWORD nFrom, DWORD nDest, BOOL bMoveCol = TRUE);

	// Tail Grid Serialize ->Start
	void			SetAllClear();
	void			SerializeEx ( CArchive& ar, CString& strProperty );
	BOOL			SetTailGridDataChange ( CString  strPropertyData );  // property String->Binary
	CString			GetTailGridDataChange ( );					         // Binary->property String
	// Tail Grid Serialize ->End
	CString			GetDumpText			  ( int nOption = 0 );
public:
	CTableCell*		m_pTableCell;		// Table Cell Info Array
	CTableLink*		m_pTableLink;		// Table Link Info Array
//	CLineBorder*	m_pTableBorder;		// Table Border Info

#ifdef MULTI_CAPTION_USE				// �ٱ��� ���ɼ� 
	CGXCaptionData*	m_pTableMultiCell;	// Multi lang Array Info(Caption, Item, Record, tooltip,choicelist)
#endif
};

#endif//_OGDESIGNGATE_H_
