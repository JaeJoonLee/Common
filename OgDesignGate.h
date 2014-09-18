#ifndef _OGDESIGNGATE_H_
#define _OGDESIGNGATE_H_

#include "OgDesignDefine.h"

#ifdef MULTI_CAPTION_USE		// 다국어 사용옵션 
#include "GxCaptionStyle.h"	// GxCaptionArray
#endif

// 그리드 문자 셀정보 
//#ifndef GRID_CELL_STYLE_USE		
//#include "GxGridCellStyle.h"	
//#endif


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma pack(push, 1)
/***************************************************/
// Designer 기동시의 OCX의 정보를 넘겨준기 위한 그조체.
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
// nToolTip		 : ToolTip Array의 인덱스를 나타냄 (1부터 인덱스 시작.)
// bFormula		 : Formula 사용하는 셀을 나타냄.
// bDspMemo		 : 셀에 메모를 직접 나타내는 셀 의미.
/***************************************************/
typedef struct tagBASEBITS
{
	unsigned long nToolTip		: 8;
	unsigned long bFormula		: 1;
	unsigned long nOpCalc		: 6;			// Calculation Cell(5->6Bit)
	unsigned long bRefFormula	: 1;			// Formula참조셀.
	unsigned long nColHideInfo	: 2;			// 컬럼 숨기기.
	unsigned long bInputMaskUse	: 1;			// InPutMask사용 
	unsigned long bReplaceText	: 1;			// ReplaceText USe 사용 
	unsigned long bCaptionText	: 1;			// Captiontext 사용 
#ifdef _BIGTEXT_USE
	unsigned long bBigTextUse	: 1;			// 글자 확대.
	unsigned long nBigTextLen	: 3;			// 글자 확대수(최대7) 
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
	unsigned long bIsKeyItem		: 1;		// Main Key Item			  : 계좌번호. 
	unsigned long bIsSubKeyItem		: 1;		// Sub Key Item				  : 체결번호.  	
	unsigned long bIsThirdKeyItem	: 1;		// Third Key Item			  : 주문번호.
	unsigned long bSignBitInfo		: 1;		// 부호색 사용유무(FID조회) +, 빨강 
	unsigned long bReferOwner		: 1;		// 참조 주체가 되는 셀.(사용안하면 나중에 빼자)
	unsigned long bReferSlave		: 1;		// 참조를 당하는 셀(사용안하면 나중에 빼자)
	unsigned long bIgnoreReal		: 1;		// 실시간 업데이트를 하지 않는 셀임을 의미(ex:종목명, 종목코드등..)
	unsigned long nLinkTag			: 6;		// LinkTag
	unsigned long bCodeLink			: 1;		// 종목연동.
	unsigned long bOrderLink		: 1;		// 주문연동.
//	unsigned long bRealItemChange	: 1;		// 실시간시에 아이템명을 바꿀지의 여부.
	unsigned long bDataHide			: 1;		// 데이터셀 표시 안하기. 
	unsigned long bMOverCell		: 1;		// 뽈록이 효과가 있는 셀( Mouse Over시에  )
	unsigned long bRealCell			: 1;		// 지정한 셀을 실시간 반전표시 
	unsigned long bMemo				: 1;		// 현재 사용안함
	unsigned long bCodeNameColor	: 1;		// 종목명 글자색 사용
	unsigned long bNewsSign			: 1;		// 뉴스신호   

	unsigned long bOneCellDataShow  : 1;		// One Cell Data
	unsigned long bMainTreeDataShow	: 1;		// 메인트리 데이터 표시 유무 셀. 
	unsigned long bMainTreeCellHide	: 1;		// 메인트리 셀 숨기기 셀.
	unsigned long bChildTreeCellHide: 1;		// 서브트리 셀 숨기기 셀. 
	unsigned long bAutoPriceMask	: 1;		// 가격정보 자동 마스킹
	unsigned long Dummy				: 4;
	// 32 Bits
} ITEMBITS; // 4 Byte


/***************************************************/
// Grid Bit Info
/***************************************************/
typedef struct tagGRIDBITS
{
	unsigned long bCellTip			: 1;		// CellTip 사용 유무.
	unsigned long bHideLine			: 1;		// 그리드 라인 지우기.
	unsigned long bDontSort			: 1;		// Sort 안함 플래그.
	unsigned long bDragCol			: 1;		// 드래그할 컬럼( ex : 종목코드)
	unsigned long bNumberCol		: 1;		// No 표시할 컬럼.
	unsigned long bNoUseBlockColor	: 1;		// No Use of Block Color 
	unsigned long bDragNameCol		: 1;		// 드래그할 이름 컬럼( ex : 종목명)
	unsigned long bSumCol			: 1;		// 합계할 컬럼(누적거래량)(시간대별 그리드에서 합계컬럼)
	unsigned long bDSortCol			: 1;		// Z~A - Sort Col
	unsigned long bNoBlockCount		: 1;		// Block Count 사용안함. 
	unsigned long bASortCol			: 1;		// A~Z - Sort Col
	unsigned long Dummy				: 21;
	// 32 Bits
} GRIDBITS; // 4 Byte

/***************************************************/
// Table Bit Info
/***************************************************/
typedef struct tagTABLEBITS
{
	unsigned long bMOverCell		: 1;			// 뽈록이 효과가 있는 셀( Mouse Over시에  )
	unsigned long nHogaGraph		: 2;			// 호가 막대 그래프(0:None, 1:Owner, 2:Slave)
	unsigned long bHogaPrice		: 1;			// 호가 가격 셀.
	unsigned long bMouseOver		: 1;			// Runtime시에 사용(뽈록이 메뉴 표시시)
	unsigned long bCurPrc			: 1;			// 호가 ( 현재가 셀)
	unsigned long bStandardPrc		: 1;			// 호가 ( 기준가(전일종가) 셀)
	unsigned long bSaleTotAmount	: 2;			// Runtime시에 사용(잔량 Progress를 나타내기 위한 매도 총잔량셀)
	unsigned long bHogaEmphasis		: 1;			// 호가 강조셀. 
	unsigned long nHogaOrder		: 2;			// 주문 셀(0:None, 1:Sale, 2:Buy)
	unsigned long nHogaStop			: 2;			// STOP 셀(0:None, 1:Sale, 2:Buy)
	unsigned long nLinkRow			: 6;			// Link Cell Row( 최대 :60)
	unsigned long nLinkCol			: 6;			// Link Cell Col( 최대 :60)
	unsigned long bHogaOrderInfo	: 1;			// 호가가격정보표시셀(주문용: 잔고,미체결,가격선택셀)
	unsigned long bHogaRateCell		: 1;			// 호가등락률 컬럼 
	unsigned long bXRayHogaCell		: 1;			// 호가분석셀표시 (X-RAY)
	unsigned long bHogapriceInfo	: 1;			// 호가가격정보표시셀(
	unsigned long Dummy				: 2;
	// 32 Bits
} TABLEBITS; // 4 Byte


/***************************************************/
// Tran Bit Info (사용안함 : LG에선 Tran을 여러개 동시에 사용할수 있어서 의미가 없지만 남겨둔다 )
/***************************************************/
typedef struct tagTRANBITS
{
	unsigned long nItemIndex	: 8;
	unsigned long nItemOffset	: 14;
	unsigned long nItemLen		: 10;
	// 32 Bits
} TRANBITS; // 4 Byte


/***************************************************/
// Header, Body, Cell의 공통적으로 가지는 특성.
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
	short		nWrapText;				// SetWrapText()기능 
	short		nBaseItemDummy;			// 여분.
} OGBASEITEM, *LPOGBASEITEM;

/***************************************************/
// Mask 정보.
/***************************************************/
typedef struct tagMaskInfo
{
	short		nFormat;				// Format Index
	short		nPlaces;				// 소수점 이하 자리수.
	DWORD		dwBitInfo;				// Bit별 정보 순서대로 사용.
										// 0x00000001	// 콤마사용.										
										// 0x00000002	// 0표시안함.										
										// 0x00000004	// 부호 표시 안함.										
										// 0x00000008	// 부호 (-) 만 표시.										
										// 0x00000010	// 부호 (-, +) 항상 표시.										
										// 0x00000020	// Prefix 사용.										
										// 0x00000040	// Postfix 사용.										
										// 0x00000080	// 앞에 0제거.										
										// 0x00000100	// 사용안함
										// 0x00000200	// 사용안함
										// 0x00000400	// 사용안함
										// 0x00000800	// 소수점이하 자리수 처리가 있을시에 원데이타에 소수점이 없을시 정책.
										// 				// (ex) 소수점이하 자리수 2인경우 입력 데이타가 116일때.
										// 				// True : 116.00, False : 1.16
										// 0x00001000	// 반올림.
										// 0x00002000	// 괄호 사용.
										// 0x00004000	// MBS_ZERO_TRIMLEFT를 사용시 모든경우가 0일때 마지막 0은 남길여부.
										// 0x00008000	// .이하 값 표시 안하기
										// 0x00010000	// 무조건 숫자형으로 변환 
										// 0x00020000	// 표시영역 부족시 자동 1000으로 나누어서  K 문자열 덧붙이기 

	char		szFix[MAX_FIX_LEN+1];	// Prefix / Postfix의 문자열 최대 길이 4(ex : %, $, 만원).
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
// Grid의 Header정보. 
/***************************************************/
// Grid의 세부 Header정보.
typedef struct tagGridHeader
{
	short		nRow;
	short		nCol;
	short		nOrgRow;				// 원래Row위치 (컬럼이동시 사용 ) 
	short		nOrgCol;				// 원래Col위치 (컬럼이동시 사용 )  
	char		szCaption[CAPTION_LEN+1];
	OGBASEITEM	bsItem;
	MASKINFO	mask;					// 삼성증권 마스킹정보 추가 
	long		lDummy;
} GRIDHEADER, *LPGRIDHEADER;

// Grid의 전체 Header정보. 
typedef struct tagGridHeaderInfo
{
	DWORD		dwLength;
	short		nCount;
    
	GRIDHEADER** pRec;

} GRIDHEADERINFO, *LPGRIDHEADERINFO;

/***************************************************/
// Grid의 Body정보. 
/***************************************************/
// Grid의 세부 Body정보. 
typedef struct tagGridBody
{
	short		nPos;
	short		nOrgPos;								// 원래 Pos위치 (컬럼이동시 사용 ) 
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
// --> [Edit]  안경환 2008/03/26
//	short		wDummy;
	short		nAttrFid;		// FID 색상 지정 ATTRIBUTE
// <-- [Edit]  안경환 2008/03/26
	char		szRealItem[REAL_ITEM_LEN+1]; // Real Item명

} GRIDBODY,*LPGRIDBODY;

// Grid의 전체 Body정보. 
typedef struct tagGridBodyInfo
{
	DWORD		dwLength;
	short		nSubItemCount;	// 가로 그리드 : Sub Row Count, 세로 그리드 : Sub Cloumn Count, 
	short		nItemCount;		// 가로 그리드 : 데이타 영역의 Column Count, 세로 그리드 : 데이타 영역의 Row Count. 
    GRIDBODY*** pRec;

} GRIDBODYINFO,*LPGRIDBODYINFO;


/***************************************************/
// Table의 Cell정보. 
/***************************************************/
// Table의 세부 Cell정보. 
typedef struct tagTableCell
{
	short		nRow;
	short		nCol;
	short		nOrgRow;				// 원래Row위치 (컬럼이동시 사용 ) 
	short		nOrgCol;				// 원래Col위치 (컬럼이동시 사용 )  
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
// --> [Edit]  안경환 2008/03/26
//	short		wDummy;
	short		nAttrFid;		// FID 색상 지정 ATTRIBUTE
// <-- [Edit]  안경환 2008/03/26
	char		szRealItem[REAL_ITEM_LEN+1]; // Real Item명
	
} TABLECELL, *LPTABLECELL;

// Table의 전체 Cell정보. 
typedef struct tagTableCellInfo
{
	DWORD dwLength;
	short nCount;

    TABLECELL** pRec;

} TABLECELLINFO, *LPTABLECELLINFO;

// --> [Edit]  김창하 2005/11/29
// 사용자 셀 정보
//Table Cell Edit
typedef struct tagUserCell
{
	short		nIndex;
	short		nOrgRow;
	short		nOrgCol;
	short		nMoveIndex;		// 이동위치
	
	short		nRow;
	short		nCol;

	short		nOrgLinkRow;
	short		nOrgLinkCol;
} USERCELL, *LPUSERCELL;

// Cell Edit info의 전체 Cell정보. 
typedef struct tagUserCellInfo
{
	DWORD dwLength;
	short nCount;
	int   nRowCount;
	int   nColCount;

    USERCELL** pUserRec;
} USERCELLINFO, *LPUSERCELLINFO;
// <-- [Edit]  김창하 2005/11/29


/***************************************************/
// Table의 Cell Link정보. 
/***************************************************/
// Table의 세부 Cell Link정보. 
typedef struct tagCellLink
{
	BYTE  byIsCaption;
	short nRow;
	short nCol;
	short nLinkRow;
	short nLinkCol;
	long  lDummy;

} CELLLINK, *LPCELLLINK;

// Table의 전체 Cell Link 정보. 
typedef struct tagCellLinkInfo
{
	DWORD dwLength;
	short nCount;

    CELLLINK** pRec;

} CELLLINKINFO, *LPCELLLINKINFO;

/***************************************************/
// Size 정보. 
/***************************************************/
// Grid & Table의 각 Item별 사이즈 정보.
typedef struct tagItemSize
{
	short nSize;
	BYTE  bySysHidden;
	long  lDummy;

} ITEMSIZE,*LPITEMSIZE;

// Table의 전체 Cell정보. 
typedef struct tagItemSizeInfo
{
	DWORD dwLength;
	short nCount;

    ITEMSIZE** pRec;

} ITEMSIZEINFO, *LPITEMSIZEINFO;


/***************************************************/
// 참조 정보.
/***************************************************/
typedef struct tagReferInfo
{
	short		nBasisKeyIdx;			// 참조 주체의 Key Index
	char		szBasisItem[ITEM_LEN+1];// 참조 주체의 Item

	short		nReferCnt;				// 참조 영향을 받는 Item의 갯수.
	LPSTR*		plpszItem;				// 참조 영향을 받는 Item들.
	long		lDummy;					// 여분.
							
} REFERINFO, *LPREFERINFO;

typedef struct tagCellRange
{
	short nRow;
	short nCol;
	short nToRow;
	short nToCol;

} CELLRANGE, *LPCELLRANGE;


/***************************************************/
// Grid Line 정보.(가로그리드는 column의 오른쪽에, 세로그리드는 row의 아래쪽선에 적용한다.)
// 2003.09.03 그리드의 라인정보는 사용하지 않는다.
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
// Table Border정보.
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
// Cell의 컨트롤별 정보. 
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
	short   nMaxLen;				// 데이터출력값 
	BYTE	byValueShow;			// 00=00 데이터  
	CString strChoiceList;			// 직접입력한 경우의 리스트 
	CString strFileName;			// Ini 파일명 
	CString strSectionName;			// [Ini]섹션명 
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
	short nCaptionShow;      // 0 : 표시안함, 1 : 표시. 
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
// Cell의 Tooltip 정보.
/***************************************************/
typedef struct 
{
	short			nFmtCnt;				//사용하는 형식 문자열의갯수. ex) "%s의 거래량은 %s입니다."         --> 2
											//갯수가 0인 경우는 단순히 strText을 가공없이 보여준다.
	CStringArray*	pItemArray;				//형식 문자열에 대치될 Item의 array
	CString			strText;				//Format String ex) "%s의 거래량은 %s입니다."
	long			lDummy;

} TTINFO, *LPTTINFO;

/***************************************************/
// Cell의 Text 정보. 
/***************************************************/
typedef struct 
{
	short nRow;
	short nCol;
	CString strText;

} CELLTEXT, *LPCELLTEXT, CELLFORMULA, *LPCELLFORMULA, CELLFIXKEY, *LPCELLFIXKEY, CELLRECORDNAME, *LPCELLRECORDNAME, CELLINPUTMASK, *LPCELLINPUTMASK,CELLREPLACETEXT, *LPCELLREPLACETEXT,CELLCAPTIONTEXT, *LPCELLCAPTIONTEXT;

/***************************************************/
// 실시간 조건 항목
/***************************************************/
typedef struct tagREALCONBITS
{
	unsigned long nOperator		: 4;	// 조건 식(=, !=, ...)
	unsigned long nTrueAction	: 4;	// 조건 성공일때 결과 실행 오퍼레이션(insert,update,delete,...)
	unsigned long nFalseAction	: 4;	// 조건 실패일때 결과 실행 오퍼레이션(insert,update,delete,...)
	unsigned long nTrueIndex	: 5;	// 조건 성공일때 다음 조건 인덱스.
	unsigned long nFalseIndex	: 5;	// 조건 실패일때 다음 조건 인덱스.
	unsigned long lDummy		: 10;	// 여분.
	// 32 Bits
} REALCONBITS; // 4 Byte

typedef struct tagRealConItem
{
	BYTE		byRec;					// Real Record
	char		szItem[ITEM_LEN+1];		// 조건 아이템.
	char		szValue[RC_VALUE_MAX+1];// 비교값.
	REALCONBITS RConBits;				// 조건 정보.
	long		lDummy;					// 여분.

} REALCONITEM, *LPREALCONITEM;

typedef struct tagRECTYPEBITS
{
	unsigned long bKeyUse		: 1;	// Key를 찾음.
	unsigned long bSubKeyUse	: 1;	// SubKey를 찾음.
	unsigned long bThirdKeyUse	: 1;	// ThirdKey를 찾음.
	unsigned long lDummy		: 29;	// 여분.
	// 32 Bits
} RECTYPEBITS; // 4 Byte

typedef struct tagRecType
{
	BYTE		byRec;					// Real Record
	BYTE		byDefAction;			// 키에 해당하는 로우/컬럼을 못찻았을때 오퍼레이션.
	BYTE		nConIndex;				// 시작 인덱스.
	//long		lDummy;					// 여분.
	RECTYPEBITS RTBits;			

} REALRECTYPE, *LPREALRECTYPE;

typedef struct tagRealConInfo
{
	DWORD		dwLength;
	BYTE		nRecCount;				// Real Record 구분 카운트.
	BYTE		nConCount;				// 실제 조건의 카운트.
	REALRECTYPE** ppRecType;			// Real Record Type별 정보.
 	REALCONITEM** ppCondition;			// 실제 조건들.

} REALCONINFO, *LPREALCONINFO;


/***************************************************/
// New 참조 항목
/***************************************************/
typedef struct tagNewReferBits
{
	unsigned long nCmpType		: 2;	// 비교 조건(0:상수 비교, 1:아이템의 값비교, 2:문자비교 2:Target Item의 색상 복사(대체문자는 해당 안됨))
	unsigned long nOperator		: 3;	// 조건 식(>,<,=,>=,<=,!=).
	unsigned long bUseSymbol	: 1;	// 대체문자 사용 여부.
	unsigned long bUseBackCr	: 1;	// Back Color 사용 여부.
	unsigned long bUseTextCr	: 1;	// Text Color 사용 여부.
	unsigned long nBackCrIndex	: 9;	// Back Color 컬러 인덱스(max : 511).
	unsigned long nTextCrIndex	: 9;	// Text Color 컬러 인덱스(max : 511).
	unsigned long lDummy		: 6;	// 여분.
	// 32 Bits
} NEWREFERBITS; // 4 Byte

typedef struct tagNewReferCon
{
	NEWREFERBITS NRBits;				// New 참조 정보들.

	char		szTgtItem[ITEM_LEN+1];	// 비교 아이템.
	double		dTgtConstant;			// 비교 상수값.
	char		szSymbol[NR_SYMBOL_MAX+1];// 대체문자.
	long		lTgtCharValue;			 // 문자비교(1BYTE).

} NEWREFERCON, *LPNEWREFERCON;

typedef struct tagNewReferType
{
	char		szItem[ITEM_LEN+1];		// 기준 아이템.
	BYTE		nKeyIndex;				// 기준 Key Index.
	BYTE		nCount;					// 참조 카운트.
	NEWREFERCON** ppNRCon;				// 참조 정보.
	short		nTop;					// Top위치 	
	short		nLeft;					// Left위치 
	short		nBottom;				// Bottom위치 	
	short		nRight;					// Right위치 
//	long		lDummy;					// 여분.
} NEWREFERTYPE, *LPNEWREFERTYPE;

typedef struct tagNewReferInfo
{
	BYTE		nCount;					// 참조 타입 카운트.
	NEWREFERTYPE** ppNRType;			// 참조 타입별 정보.

} NEWREFERINFO, *LPNEWREFERINFO;

// 실시간시에 해당 리얼 타입에 따라서. 
// 아이템명을 동적으로 바꿀 경우에 사용.
typedef struct tagREALCHGITEC
{
	BYTE	byRec;			// 실시간 레코드 구분(0x10, 0x34)
	BYTE	byUpdate;		// 1: Update, 0: Insert
	char	szItem[ITEM_LEN+1];
	char	szChgItem[ITEM_LEN+1];
}REALCHGITEC;


/***************************************************/
// 호가 주문 구조체.
/***************************************************/
typedef struct 
{
	char	szOrderNo[ORDER_NO_LEN+1];		//주문번호.
	long	lAmount;						//수량.

} HOGAORDER, *LPHOGAORDER;

typedef struct 
{
	BYTE	byOption;						//0x01 : 주문, 0x02: STOP
	BYTE	byIsAll;						//일괄 정정/취소인경우.
	BYTE	byOrderType;					//매도/매수구분.
	char	szOrderPrice[20];				//주문가격.

} ORDERSRC, *LPORDERSRC;


// 
typedef struct 
{
	char szHogaPrice[20];	// 호가가격(호가테이블에 매핑되는 가격)
	char szOrderPrice[30];	// 평균체결가, 미체결가, 선택가격, 감시가격
	long lQty;				// 수량
	long byPriceState;		// 가격상태
							// 0x00000000 : 
							// 0x00000001 : 선택가격
							// 0x00000002 : 감시가격
							// 0x00000004 : 잔고
							// 0x00000008 : 미체결

	char szOrderNo[20];		// 주문번호(미체결시)
	BYTE byMemagb;			// 매매구분

} HO_TABLE_ORDERDATA, *LPHO_TABLE_ORDERDATA;

/***************************************************/
// 체결추이 Attribute.
/***************************************************/
typedef struct
{	
	BYTE	byAttr;			// 체결추이 Attribute(Rp)
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
	char	szCode[20];			// 종목코드
	short	nKeyIndex;			// Key Index

	long	lVolData1;			// 미결제 증감 (감소)
	long	lVolData2;			// 미결제 증감 (증가)
	long	lVolData3;			// 미결제 데이터(당일)

} GRAPH_CELL_DATA, *LPGRAPH_CELL_DATA;

/***************************************************/
// 호가테이블 가격 설정 정보
/***************************************************/
typedef struct 
{
	long lConfigBit;			// 호가테이블 설정 정보 
								// 0x00000000 사용안함
								// 0x00000001 사용안함
								// 0x00000002 사용안함
								// 0x00000004 사용안함
								// 0x00000008 사용안함
								// 0x00000010 시세메모(가격정보 표시셀 )
								// 0x00000020 최대잔량 Bold

	long lClrUseBit;			// 색상사용여부
								// 0x00000000 사용안함
								// 0x00000001 당일시가색	
								// 0x00000002 당일고가색	
								// 0x00000004 당일저가색	
								// 0x00000008 전일종가색	
								// 0x00000010 PIVOT 2차저항 
								// 0x00000020 PIVOT 1차저항 
								// 0x00000040 PIVOT 기준선  
								// 0x00000080 PIVOT 1차지지 
								// 0x00000100 PIVOT 2차지지 
								
	long lOrderBit;				// 주문용 테이블
								// 0x00000000 사용안함
								// 0x00000001 주문에서 "▶"선택된종목
								// 0x00000002 주문에서 "●" 감시중
								// 0x00000004 주문에서 "■" 잔고
								// 0x00000008 주문에서 "◆"미체결

	char szOpen     [10];		// 당일시가
	char szHigh     [10];		// 당일고가
	char szLow      [10];		// 당일저가
	char szPrice    [10];		// 당일현재가
	char szPreClose [10];		// 전일종가
	
	char szResist2	[10];		// 피봇2차저항
	char szResist1	[10];		// 피봇1차저항
	char szPivot	[10];		// 피봇
	char szSupport1 [10];		// 피봇1차지지
	char szSupport2	[10];		// 피봇2차지지

	COLORREF clrOpen;			// 당일시가색	 
	COLORREF clrHigh;			// 당일고가색	 
 	COLORREF clrLow;			// 당일저가색	 
	COLORREF clrPreClose;		// 전일종가색	 
	COLORREF clrResist2;		// PIVOT 2차저항 
	COLORREF clrResist1;		// PIVOT 1차저항 
	COLORREF clrPivot;			// PIVOT 기준선  
	COLORREF clrSupport1;		// PIVOT 1차지지 
	COLORREF clrSupport2;		// PIVOT 2차지지 
	COLORREF clrDuplicate;		// 중복항목 색상

	

} HOGA_BASE_PRICE_INFO, *LPHOGA_BASE_PRICE_INFO;

/***************************************************/
// 개별호가 정보
/***************************************************/
//typedef struct 
//{
//	long lUseBit;				// 설정 정보
//	short nDispBitCount;        // 표시할 정보항목개수
//	BOOL bIsMaxRemQty;			// 최대잔량유무
//
//} HOGA_INFO, *LPHOGA_INFO;


/***************************************************/
// 가격자동마스크및 해외선물 진법 표시를 위한 포멧 구조체
/***************************************************/
typedef struct
{	
	BYTE	byFmt;				// 마스크타입
	BYTE	byMarket;			// 시장구분
	BYTE	bySpot;				// 현물가 표시여부
	BYTE	byLog;				// 진법
	BYTE    byLogDispSize;		// 진법표시 정보( 현물가 표시인경 가격정보 )
	BYTE	byPrecision;		// 소수점 정보
	BYTE	byItemPrecision;	// 현물가 계산시 소수점 정보
	char	szTickSize[16];		// 해외선물 TickSize
	char	szTickValue[16];	// 해외선물 TickValue
	char	szPriceInfo[2];		// 거래소가격표시정보
	BYTE	byIsSpread;			// 스프레드 종목인경우
	DWORD	dwBitInfo;			// 마스크 부가정보(MASKINFO 참조)
} ITEM_PRICE_FORMAT, *LPITEM_PRICE_FORMAT ;


#pragma pack(pop)


class CGridInfo;
/***************************************************/
// Grid  Header 저장용 Class
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
// --> [Edit]  김창하 2005/11/29
	// 사용자Cell정보 
	void		SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
// <-- [Edit]  김창하 2005/11/29

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
// Grid  Body 저장용 Class
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
// --> [Edit]  김창하 2005/11/29
	// 사용자Cell정보 
	void		SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
// <-- [Edit]  김창하 2005/11/29

	short		GetKeyIndexCount();
	LPCTSTR		GetKeyItem(short nKeyIndex = 0);
	LPCTSTR		GetSubKeyItem(short nKeyIndex = 0);
	LPCTSTR		GetThirdKeyItem(short nKeyIndex = 0);
	BOOL		GetKeyIndexMinMaxPos(unsigned short nKeyIndex, unsigned short& nMinPos, unsigned short& nMaxPos);
	LPGRIDBODY	GetBodyRecordInfo ( short nKeyIndex, LPCTSTR lpszItem );
	
	int			GetFlushItemListArray ( );
	
	// 메모,CodeDrag,참조 정보를 사용하는 Cell이 존재하는 가를 체크한다.
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
// Table  Cell 저장용 Class
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
// --> [Edit]  김창하 2005/11/29
	// 사용자Cell정보 
	void		SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
// <-- [Edit]  김창하 2005/11/29

	short		GetKeyIndexCount();
	LPCTSTR		GetKeyItem(short nKeyIndex = 0);
	LPCTSTR		GetSubKeyItem(short nKeyIndex = 0);
	LPCTSTR		GetThirdKeyItem(short nKeyIndex = 0);
	TABLECELL*	GetRowColCell(int nColCnt, int nRow, int nCol);
	int			GetFlushItemListArray ();

	// 메모,CodeDrag,참조 정보를 사용하는 Cell이 존재하는 가를 체크한다.
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
// Table Link 저장용 Class
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
// Size 저장용 Class
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
// Real Condition 저장 Class
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
// New 참조 저장 Class
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
// Cell Covered 저장용 Class
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
// Line(Border) 저장용 Class
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

// --> [Edit]  김창하 2005/11/29
	// 사용자Cell정보 
	void		SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
// <-- [Edit]  김창하 2005/11/29
	
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
	// 그리드의 Line은 사용하지 않지만 버젼 처리때문에 남겨둠(2003.09.03)
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
// Cell Control 저장용 Class
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
// Tooltip 저장용 Class
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
// 참조 저장용 Class
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
// Cell의 text를 저장하는 Class
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
	// [다중아이템] 해당위치의 아이템명을 취득한다.
	BOOL		GetRowColItemInfo( DWORD nRow, DWORD nCol, CString& strItem );
	BOOL		GetRowColItemCmp( DWORD nRow,  DWORD nCol, CString  strItem );
	int			GetRowColMultiRecordPos( CString  strItemInfo );

	BOOL		SetRowColText(short nRow, short nCol, CString strText , BOOL bOverWrite = TRUE);

	// FixKey인 경우만 사용.
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
// Memo 저장용 Class
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
// Grid와 Table의 공통 Property Class
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
	BYTE			m_byUseForDll;			// DLL에서 사용함을 의미.
	BOOL			m_bSkip;				// Skip 방법 지정.
	DWORD			m_dwBaseVer;			// Base Version
	CSize			m_CtrlSize;				// Control Size
	int				m_nRowCnt,				// Grid Row Count
					m_nColCnt,				// Grid Column Count
					m_nFrozenRowCnt,		// Frozen Row Count
					m_nFrozenColCnt,		// Frozen Colunm Count
					m_nHiddenRowCnt,		// Row Index 0부터 Hidden할 Row의 수
					m_nHiddenColCnt,		// Column Index 0부터 Hidden할 Column의 수
					m_nDefColWidth,			// Default Column Count
					m_nDefRowHeight,		// Default Row Height
					m_nLineColorIndex,		// Grid Line Color Index( 테이블인 경우는 원래대로 전 라인색 지정.
											//						  그리드인 경우는 바디부분의 VLine만 지정. 마머지 라인색은 GGridInfo의 프로퍼티로 적용 	)
					m_nBackGndColorIndex,	// Grid 뒷여백 Color Index
					m_nSelectionMode,		// Grid Selection Mode(0:Table, 1:Single List Mode, 2: Multi List Mode, 3:One Cell 4: None)
					m_nLineStyle,			// Grid Line Style(0:Solid, 1:Dash, 2:Dot, 3:DashDot, 4:DashDotDot )
					m_nScrollMode,			// Scroll Mode(0:Auto, 1:Not Use, 2:Only Horizental, 3:Only Vertical, 4:Always )
					m_nResizeHeader,		// Header의 Resizing 방법(0:Not Use, 1:Only Row, 2:Only Column, 3:Both, 4:Table Resize)
					m_nItemFlag,			// ItemFlag
					m_nLineMode;			// Grid Line Mode(0:Both, 1:Only Horizental, 2:Only Vertical, 3:Not Use)
	BOOL			m_bUseFormula;			// Formula 사용유무.
	WORD			m_wScriptEvent;			// Script Event Kinds
	WORD			m_wFireLinkInfo;		// 연결 정보 발생 사용유무.
	WORD			m_nSpecialContent;		// 그리드 특수기능 정의.
	BYTE			m_byTailUse;			// Tail Grid Mode
	BYTE			m_byMultiTranUse;		// 다중트랜사용
	BYTE			m_byMultiMarketUse;		// 다중시장사용
	BYTE			m_byNextDataHeaderCheck;// 다음데이터 체크시 헤더사용 
	BYTE			m_byFixedRowCheck;		// 데이터 처리시 Row,Col개수 고정 
	
	int				m_nResize,				// Control Resizing(0:Resize, 1:Move)
					m_nBorderStyle,			// Control Border Style(0:None, 1:Border, 2:3D)
					m_nKeyIndexCnt;			// Key Count

	WORD			m_nDnDMode;				// Drag & Drop의 모드.
	WORD			m_nDragIndex;			// Drag할 Row/Col의 Index
	
	WORD			m_nPopupMenuMode;		// 메뉴 표시 방법.
	WORD			m_nRealHighlight;		// Real데이타 표시 방법.
	BYTE			m_byUseSelectColor;		// 셀렉트 된 셀 표시방법(0: Invert Color, 1:지정된 Color)
	int				m_nSelectColorIndex;	// 셀렉트 된 셀의 배경 Color Index
	
	
	BYTE			m_bySpecialHoga;		// 호가 테이블에 특별한 그리기 처리가 있는 경우 true.
	BYTE			m_byNeedMouseOverCheck;	// 테이블인 경우 Mouse OverCell사용시 true.

	BYTE			m_byUseAmountGraph;		// 호가 테이블에서 잔량 그래프를 사용하는지의 유무.
	int				m_nBorderColorIndex;	// 컨트롤 보더 컬러 인덱스.

	CString			m_strRPImportRecord;	// RP Import Nmae
	CString			m_strRealImportRecord;	// Real Import Nmae
	CString			m_strRQExportRecord;	// RP Export Nmae

//	CString			m_strCommTrName;		// RQName
	CString			m_strOptionQueryInfo;	
	CString			m_strPrevCtrlName;		// Prev Button Control Name
	CString			m_strNextCtrlName;		// Next Button Control Name
	int				m_nDataType;			// 데이타 타입 (0:TopInsert, 1:TopUpdate, ...)

//	BYTE			m_byUseDelayTimer;		// 실시간 Delay Timer 사용 플래그.
// m_byUseDelayTimer 변수명을 m_byMultiItemUse 으로 변경한다.
	BYTE			m_byMultiItemUse;		// 다중트랜사용(같은Row영역)

	CItemSize*		m_pRowSize;				// Row Size Info
	CItemSize*		m_pColSize;				// Column Size Info
	CCellCovered*	m_pCovered;				// Covered Info
	CCellCtrl*		m_pCellCtrl;			// Cell Control Info
	CTTipArray*		m_pTTip;				// ToolTip Info	
	CFormulaArray*  m_pFormula;				// Formula Info
	CFixKeyArray*	m_pFixKey;				// Fixed Key Info
	CNewRefer*		m_pNewRefer;			// 참조 정보.
	CUserLinkTagArray* m_pUserLinkArray;	// 사용자 연결정보 테그 어레이.

// --> [Edit]  김창하 2006/06/16
// Version 3 m_pmapRecordInfo삭제 예정:
	CMapRecordInfo*  m_pmapRecordInfo;			// Record별 길이정보 .
	CRecordNameArray* m_pRecordNameArray;		// Record별이름 정보
	CInputMaskArray*  m_pInputMaskArray;		// 입력마스크 정보 	
	CRelpaceTextArray*  m_pReplaceTextArray;	// 대체문자 정보 	
	CCaptionTextArray*  m_pCaptionTextArray;	// 캡션문자 문자 정보 	
// <-- [Edit]  김창하 2006/06/16

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
// Grid의 모든 정보 저장용 Class
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

	// 다이어로그에서 사용하기 위해서 추가.
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

	short			m_nGridMode;			// 가로/세로 그리드 구별.
	int				m_nVirtualMode;			// Virtual Grid Mode ( 0 : 사용안함, 1 : 스타일 분리 )
				
	int				m_nSortMode,			// Sort (0:사용안함, 1:Normal, 2:Looping)
					m_nHeaderRowCnt,		// Grid Header Row Count
					m_nHeaderColCnt,		// Grid Header Column Count
					m_nSubItemCnt,			// Sub Item Count (Sub Row Count)
					m_nBlockCount,			// Block Count(색구분용)
					m_nOddColorIndex,		// 홀수 블록의 Color Index
					m_nEvenColorIndex,		// 짝수 블록의 Color Index
					m_nMaxDataCnt,			// 데이타 요청 최대 카운트.
					m_nScrollAction;		// 스트롤시의 통신 사용(0:사용안함, 1:↓조회 )
					
	BOOL			m_bUseBlockColor;		// Block Count적용시 Block Color를 적용할지의 여부.
	BOOL			m_bUse3DButtonHeader;	// 헤더의 3D Button 사용 유무.
	WORD			m_nAllowSameKey;		// Key의 중복 사용 허용 유무.
	WORD			m_nAllowSameSubKey;		// SubKey의 중복 사용 허용 유무.
	WORD			m_nAllowSameThirdKey;	// ThirdKey의 중복 사용 허용 유무.
	BYTE			m_byHeaderMove;			// Header Move 사용 여부.
	WORD			m_nFixedHeaderMoveCnt;	// 헤더 이동을 하지 않을 컬럼수.

	int				m_nBHLineColorIndex,	// Grid Body HLine Color Index
					m_nHVLineColorIndex,	// Grid Header VLine Color Index
					m_nHHLineColorIndex;	// Grid Header HLine Color Index
	BYTE			m_bySaveColSize;		// Grid 컬럼 사이즈의 저장 여부.

	CGridHeader*	m_pGridHeader;			// Grid Header Info Array
	CGridBody*		m_pGridBody;			// Grid Body Info Array
	CRealCondition* m_pRealCon;				// 실시간 조건. 

#ifdef MULTI_CAPTION_USE					// 다국어 사용옵션 
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
// Table의 모든 정보 저장용 Class
/***************************************************/
class CTableInfo : public COgBase
{
// Construction
public:
	DECLARE_SERIAL(CTableInfo)
	CTableInfo();
	~CTableInfo();

	void Serialize(CArchive &ar);
// --> [Edit]  김창하 2005/11/29
	// 사용자Cell정보 
	void SerializeUserData(CArchive &ar, LPBYTE lpData, DWORD dwLen );
// <-- [Edit]  김창하 2005/11/29

	const CTableInfo& operator=(const CTableInfo& other);

	// 다이어로그에서 사용하기 위해서 추가.
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

#ifdef MULTI_CAPTION_USE				// 다국어 사용옵션 
	CGXCaptionData*	m_pTableMultiCell;	// Multi lang Array Info(Caption, Item, Record, tooltip,choicelist)
#endif
};

#endif//_OGDESIGNGATE_H_
