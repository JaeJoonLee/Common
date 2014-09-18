#ifndef _COMMTRANINFO_H_
#define _COMMTRANINFO_H_

// 공통길이 정보 헤더 파일 
#include "CommDefineLenInfo.h"


#define		DEF_TRBIN_GROUP_INFO_LEN    sizeof(TRBIN_GROUP_INFO)
#define		DEF_TRBIN_POS_INFO_LEN		sizeof(TRBIN_POS_INFO)
#define		DEF_TRBIN_TRAN_HEADER_LEN	sizeof(TRBIN_TRAN_HEADER)

#define		DEF_TRBIN_TRAN_INFO_LEN		sizeof(TRBIN_TRAN_INFO)
#define		DEF_TRBIN_RECORD_INFO_LEN	sizeof(TRBIN_RECORD_INFO)
#define		DEF_TRBIN_ITEM_INFO_LEN		sizeof(TRBIN_ITEM_INFO)


#pragma pack(push, 1)

// 바이너리 트랜 파일에 포함된 트랜의 총 수  
typedef struct _TRBIN_GROUP_INFO
{
	UINT 	nTranVerMajor;						// 메이저 버전정보 	
	UINT	nTranVerMinor;						// 마이너 버전정보 
	UINT	nTrCount;							// TR 수 
} TRBIN_GROUP_INFO;

// 바이너리 트랜 파일에 포함된 각 트랜의 파일내에서의 위치 정보  
typedef struct _TRBIN_POS_INFO
{
	char szTrCode[UD_TRAN_CODE_LEN+1];			// 트랜코드  
	int  nStartPos;								// 트랜의 파일내에서의 시작 위치 	
	int	 nEndPos;								// 트랜의 파일내에서의 끝 위치 	
} TRBIN_POS_INFO;

// 바이너리 트랜 데이터 정보 
typedef struct _TRBIN_TRAN_HEADER
{
	UINT nTrTotalLength;						// TR의 총길이
	UINT nRecordCount;							// TR내에 포함한 총 레코드 수
	UINT nItemCount;							// 레코드가 포함한 아이템의 총 수
} TRBIN_TRAN_HEADER;


struct	TRANBITFLAG
{
	BYTE	nTranType	:2;						// 0: 트랜 ,1:FID 
	BYTE	nRecordCount:4;						// 레코드 개수(최대:16개)
	BYTE	nDumy		:2;						// 여분 
};									

// 바이너리 트랜의 정보로 레코드 수와 아이템 수에 대한 정보를 가진다. 
typedef struct _TRBIN_TRAN_INFO
{
	char		szTrCode[UD_TRAN_CODE_LEN+1];	// TR의 트랜코드 (11자리)
	TRANBITFLAG tranBits;						// TRANBITFLAG정보 
}TRBIN_TRAN_INFO;

struct	RECORDBITFLAG
{
	BYTE	nArrayType	:4;						// 0:단일, 1:문자기본, 2:숫자기본, 3:Item지정, 4:고정, 5:데이터 사이즈로 계산(단일,배열인 구조만 적용), 6 : 가변레코드 
	BYTE	bBinaryType	:1;						// 1:바이너리파일   
	BYTE	bInOut		:1;						// 0: 입력, 1 : 출력  
	BYTE	nDumy		:2;						// 여분 
};

// 바이너리 트랜 레코드 정보 
typedef struct _TRBIN_RECORD_INFO  
{
	char			szRecordName[UD_NAME_LEN+1];// 레코드 명 
	RECORDBITFLAG   recordBits;					// RECORDBITFLAG정보 
	short			nItemCount;					// 아이템 카운트(레코드에 포함된아이템개수) 
	short			nTotItemDataLen;			// 아이템 총 데이터 길이 
	short			nItemOffset;				// 아이템의 시작위치 

	short			nArrayInfo1;				// ArrayType:2이면 레코드 번호, ArrayType:4 이면 고정개수 
	short			nArrayInfo2;                // ArrayType 2이면 아이템 위치( ArrayType 2인 경우만 유효)
}TRBIN_RECORD_INFO;


struct	ITEMBITFLAG
{
	unsigned long	nDataType	:4;				// 데이터 타입(최대15) 
	// 2007/03/07 by gds 기본값인 -1이 적용되도록 수정(unsigned long -> long)
	long			bAttriUse	:16;				// Attribute사용 유무  
	// 2007/03/07 by gds 기본값인 -1이 적용되도록 수정(unsigned long -> long)
	unsigned long	nPointLen	:5;				// 소수점 이하 자리수(최대31)
	unsigned long   nDumy		:7;			// 여분 
};

// 바이너리 트랜 아이템 정보 
typedef struct _TRBIN_ITEM_INFO
{
	char			szItemName[UD_DD_NAME_LEN+1];// 트랜 아이템 명으로 DD 명과 동일 
	ITEMBITFLAG		tranItemBits;				// ITEMBITFLAG정보 
	short			nDataLen;					// 데이터 길이 
	short			nOffsetLen;					// offset정보 
}TRBIN_ITEM_INFO;


// 바이너리 파일을 읽을 때 사용되는 구조체 
// 바이너리 트랜 전체 정보 
typedef struct _TRBIN_TRAN_TOTAL_INFO
{
	TRBIN_TRAN_HEADER trHeader; 
	TRBIN_TRAN_INFO   trInfo; 
	TRBIN_RECORD_INFO *pTrRecord; 
	TRBIN_ITEM_INFO	  *pTrItem; 
}TRBIN_TRAN_TOTAL_INFO;  
									
typedef struct _TRBIN_COMM_TRAN_INFO					// 통신에서만 필요한 정보 
{
	TRBIN_TRAN_INFO   trInfo; 
	TRBIN_RECORD_INFO *pTrRecord; 
	TRBIN_ITEM_INFO	  *pTrItem; 
}TRBIN_COMM_TRAN_INFO;  



//-------------------------------------------------------------------------------------------
//  [6/11/2006]  자동갱신 관련 Binary화일로 저장하는 Format을 정의한다.

#define		DEF_AUTOTRBIN_GROUP_INFO_LEN    sizeof(AUTOTRBIN_GROUP_INFO)
#define		DEF_AUTOTRBIN_POS_INFO_LEN		sizeof(AUTOTRBIN_POS_INFO)
#define		DEF_AUTOTRBIN_TRAN_HEADER_LEN	sizeof(AUTOTRBIN_TRAN_HEADER)

#define		DEF_AUTOTRBIN_TRAN_INFO_LEN		sizeof(AUTOTRBIN_TRAN_INFO)
#define		DEF_AUTOTRBIN_RECORD_INFO_LEN	sizeof(AUTOTRBIN_RECORD_INFO)
#define		DEF_AUTOTRBIN_ITEM_INFO_LEN		sizeof(AUTOTRBIN_ITEM_INFO)

#define     UD_AUTOTRAN_CODE_LEN	5
#define     UD_FID_CODE_LEN			5

// 바이너리 트랜 파일에 포함된 트랜의 총 수  
typedef struct _AUTOTRBIN_GROUP_INFO
{
	UINT 	nTranVerMajor;						// 메이저 버전정보 	
	UINT	nTranVerMinor;						// 마이너 버전정보 
	UINT	nTrCount;							// TR 수 
} AUTOTRBIN_GROUP_INFO;

// 바이너리 트랜 파일에 포함된 각 트랜의 파일내에서의 위치 정보  
typedef struct _AUTOTRBIN_POS_INFO
{
	char szTrCode[UD_AUTOTRAN_CODE_LEN+1];			// 트랜코드  
	int  nStartPos;								// 트랜의 파일내에서의 시작 위치 	
	int	 nEndPos;								// 트랜의 파일내에서의 끝 위치 	
} AUTOTRBIN_POS_INFO;

// 바이너리 트랜 데이터 정보 
typedef struct _AUTOTRBIN_TRAN_HEADER
{
	UINT nTrTotalLength;						// TR의 총길이
	UINT nRecordCount;							// TR내에 포함한 총 레코드 수
	UINT nItemCount;							// 레코드가 포함한 아이템의 총 수
} AUTOTRBIN_TRAN_HEADER;


		

// 바이너리 트랜의 정보로 레코드 수와 아이템 수에 대한 정보를 가진다. 
typedef struct _AUTOTRBIN_TRAN_INFO
{
	char		szAutoTrCode[5];				// 자동갱신 TR Code 즉 PBID값으로 1Byte로 정의한다.
	TRANBITFLAG tranBits;						// TRANBITFLAG정보 
}AUTOTRBIN_TRAN_INFO;


// 바이너리 트랜 레코드 정보 
typedef struct _AUTOTRBIN_RECORD_INFO  
{
	char			szRecordName[UD_NAME_LEN+1];// 레코드 명 
	RECORDBITFLAG   recordBits;					// RECORDBITFLAG정보 
	short			nItemCount;					// 아이템 카운트(레코드에 포함된아이템개수) 
	short			nTotItemDataLen;			// 아이템 총 데이터 길이 
	short			nItemOffset;				// 아이템의 시작위치 
	short			nKeyIndex;					// 자동갱신에서 사용할 KeyIndex값의 ItemIndex위치.
}AUTOTRBIN_RECORD_INFO;

// 바이너리 트랜 아이템 정보 
typedef struct _AUTOTRBIN_ITEM_INFO
{
	char			szItemName[UD_DD_NAME_LEN+1];// 트랜 아이템 명으로 DD 명과 동일 
	char			szFID[UD_FID_CODE_LEN+1];	 // 각각의ITEM에 할당되어진 FID값..
	short			nFidNum;					 // 숫자 아이템 정보(검색을 위해서 ) 
	ITEMBITFLAG		tranItemBits;				 // ITEMBITFLAG정보 
	short			nDataLen;					 // 데이터 길이 
	short			nOffsetLen;					 // offset정보 
}AUTOTRBIN_ITEM_INFO;


// 바이너리 파일을 읽을 때 사용되는 구조체 
// 바이너리 트랜 전체 정보 
typedef struct _AUTOTRBIN_TRAN_TOTAL_INFO
{
	AUTOTRBIN_TRAN_HEADER trHeader; 
	AUTOTRBIN_TRAN_INFO   trInfo; 
	AUTOTRBIN_RECORD_INFO *pTrRecord; 
	AUTOTRBIN_ITEM_INFO	  *pTrItem; 
}AUTOTRBIN_TRAN_TOTAL_INFO;  
									
typedef struct _AUTOTRBIN_COMM_TRAN_INFO					// 통신에서만 필요한 정보 
{
	AUTOTRBIN_TRAN_INFO   trInfo; 
	AUTOTRBIN_RECORD_INFO *pTrRecord; 
	AUTOTRBIN_ITEM_INFO	  *pTrItem; 
}AUTOTRBIN_COMM_TRAN_INFO;  

////////////////////////////////////////////////////////

#define		DEF_REALTRBIN_GROUP_INFO_LEN    sizeof(REALTRBIN_GROUP_INFO)
#define		DEF_REALTRBIN_POS_INFO_LEN		sizeof(REALTRBIN_POS_INFO)
#define		DEF_REALTRBIN_TRAN_HEADER_LEN	sizeof(REALTRBIN_TRAN_HEADER)

#define		DEF_REALTRBIN_TRAN_INFO_LEN		sizeof(REALTRBIN_TRAN_INFO)
#define		DEF_REALTRBIN_RECORD_INFO_LEN	sizeof(REALTRBIN_RECORD_INFO)
#define		DEF_REALTRBIN_ITEM_INFO_LEN		sizeof(REALTRBIN_ITEM_INFO)

//#define     UD_REALTRAN_CODE_LEN	5
//#define     UD_FID_CODE_LEN			5

#define		DEF_REAL_TRAN_VER_MAJOR		0		
#define		DEF_REAL_TRAN_VER_MINOR		1

// 바이너리 트랜 파일에 포함된 트랜의 총 수  
typedef struct _REALTRBIN_GROUP_INFO
{
	UINT 	nTranVerMajor;						// 메이저 버전정보 (DEF_REAL_TRAN_VER_MAJOR)	
	UINT	nTranVerMinor;						// 마이너 버전정보 (DEF_REAL_TRAN_VER_MINOR)
	UINT	nTrCount;							// TR 수 
} REALTRBIN_GROUP_INFO;

// 바이너리 트랜 파일에 포함된 각 트랜의 파일내에서의 위치 정보  
typedef struct _REALTRBIN_POS_INFO
{
//	char szTrCode[UD_AUTOTRAN_CODE_LEN+1];		// 트랜코드  
	int  nRealCode;								// 자동갱신타입 
// --> [Edit]  이용준 2007/03/07
	char			szRealName[UD_TRCODE_LEN+1];		// 자동구분 서브젝트명
// <-- [Edit]  이용준 2007/03/07
	int  nStartPos;								// 자동갱신의 파일내에서의 시작 위치 	
	int	 nEndPos;								// 자동갱신의 파일내에서의 끝 위치 	
} REALTRBIN_POS_INFO;

// 바이너리 트랜 데이터 정보 
typedef struct _REALTRBIN_TRAN_HEADER
{
	UINT nTrTotalLength;						// 자동갱신 TR의 총길이
	UINT nRecordCount;							// 자동갱신 TR내에 포함한 총 레코드 수
	UINT nItemCount;							// 자동갱신 레코드가 포함한 아이템의 총 수
} REALTRBIN_TRAN_HEADER;


struct	REALTRANBITFLAG
{
	BYTE	nRecordCount  :4;					   // 레코드 개수(최대:16개)
	BYTE	nSiseShareUse :1;					   // 공유시세 포함여부 
	BYTE	nDumy		  :3;					   // 여분 
};									

// 바이너리 트랜의 정보로 레코드 수와 아이템 수에 대한 정보를 가진다. 
typedef struct _REALTRBIN_TRAN_INFO
{
//	char		    szREALTrCode[5];				// 자동갱신 TR Code 즉 PBID값으로 1Byte로 정의한다.
	int             nRealCode;						// 자동갱신타입
	short			nPosConcProp;					// 체결성향 위치정보  (체결량의 색 정보 사용)  
	short			nPDayCf;						// 전일대비 위치정보
	short			nCurPrice;						// 현재가위치정보 
													// 전일종가를 구하기 위해서(전일대비, 현재가위치사용)
	short			nBasePrice;						// 기준가위치정보(호가가격 색 정보)
	REALTRANBITFLAG tranBits;						// REALTRANBITFLAG정보 
}REALTRBIN_TRAN_INFO;

// 바이너리 트랜 레코드 정보 
typedef struct _REALTRBIN_RECORD_INFO  
{
// --> [Edit]  이용준 2007/03/07
	int				nRealGubun;					// 자동구분자
	char			szRealName[UD_TRCODE_LEN+1];		// 자동구분 서브젝트명
// <-- [Edit]  이용준 2007/03/07
//	char			szRecordName[UD_NAME_LEN+1];// 레코드 명 
//	RECORDBITFLAG   recordBits;					// RECORDBITFLAG정보 
	short			nItemCount;					// 아이템 카운트(레코드에 포함된아이템개수) 
	short			nTotItemDataLen;			// 아이템 총 데이터 길이 
	short			nItemOffset;				// 아이템의 시작위치 

	short			nKeyIndex;					// 자동갱신에서 사용할 KeyIndex값의 ItemIndex위치.
}REALTRBIN_RECORD_INFO;

// 바이너리 트랜 아이템 정보
struct	REALITEMBITFLAG
{
	unsigned long	nDataType	:4;				// 데이터 타입(최대15) 
	unsigned long	nPointLen	:5;				// 소수점 이하 자리수(최대31)
	unsigned long   nDumy		:23;			// 여분 
};
 
typedef struct _REALTRBIN_ITEM_INFO
{
	char			szItemName[UD_DD_NAME_LEN+1];// 트랜 아이템 명으로 DD 명과 동일 
	char			szFID[UD_FID_CODE_LEN+1];	 // 각각의ITEM에 할당되어진 FID값..
	short			nFidNum;					 // 숫자 아이템 정보(검색을 위해서 ) 
	REALITEMBITFLAG	tranItemBits;				 // REALITEMBITFLAG정보 

	short			nDataLen;					 // 데이터 길이 
	short			nOffsetLen;					 // offset정보 
}REALTRBIN_ITEM_INFO;


// 바이너리 파일을 읽을 때 사용되는 구조체 
// 바이너리 트랜 전체 정보 
typedef struct _REALTRBIN_TRAN_TOTAL_INFO
{
	REALTRBIN_TRAN_HEADER trHeader; 
	REALTRBIN_TRAN_INFO   trInfo; 
	REALTRBIN_RECORD_INFO *pTrRecord; 
	REALTRBIN_ITEM_INFO	  *pTrItem; 
}REALTRBIN_TRAN_TOTAL_INFO;  
									
typedef struct _REALTRBIN_COMM_TRAN_INFO					// 통신에서만 필요한 정보 
{
	REALTRBIN_TRAN_INFO   trInfo; 
	REALTRBIN_RECORD_INFO *pTrRecord; 
	REALTRBIN_ITEM_INFO	  *pTrItem; 
}REALTRBIN_COMM_TRAN_INFO;  


#pragma pack(pop)

#endif//_COMMTRANINFO_H_
