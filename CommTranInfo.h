#ifndef _COMMTRANINFO_H_
#define _COMMTRANINFO_H_

// ������� ���� ��� ���� 
#include "CommDefineLenInfo.h"


#define		DEF_TRBIN_GROUP_INFO_LEN    sizeof(TRBIN_GROUP_INFO)
#define		DEF_TRBIN_POS_INFO_LEN		sizeof(TRBIN_POS_INFO)
#define		DEF_TRBIN_TRAN_HEADER_LEN	sizeof(TRBIN_TRAN_HEADER)

#define		DEF_TRBIN_TRAN_INFO_LEN		sizeof(TRBIN_TRAN_INFO)
#define		DEF_TRBIN_RECORD_INFO_LEN	sizeof(TRBIN_RECORD_INFO)
#define		DEF_TRBIN_ITEM_INFO_LEN		sizeof(TRBIN_ITEM_INFO)


#pragma pack(push, 1)

// ���̳ʸ� Ʈ�� ���Ͽ� ���Ե� Ʈ���� �� ��  
typedef struct _TRBIN_GROUP_INFO
{
	UINT 	nTranVerMajor;						// ������ �������� 	
	UINT	nTranVerMinor;						// ���̳� �������� 
	UINT	nTrCount;							// TR �� 
} TRBIN_GROUP_INFO;

// ���̳ʸ� Ʈ�� ���Ͽ� ���Ե� �� Ʈ���� ���ϳ������� ��ġ ����  
typedef struct _TRBIN_POS_INFO
{
	char szTrCode[UD_TRAN_CODE_LEN+1];			// Ʈ���ڵ�  
	int  nStartPos;								// Ʈ���� ���ϳ������� ���� ��ġ 	
	int	 nEndPos;								// Ʈ���� ���ϳ������� �� ��ġ 	
} TRBIN_POS_INFO;

// ���̳ʸ� Ʈ�� ������ ���� 
typedef struct _TRBIN_TRAN_HEADER
{
	UINT nTrTotalLength;						// TR�� �ѱ���
	UINT nRecordCount;							// TR���� ������ �� ���ڵ� ��
	UINT nItemCount;							// ���ڵ尡 ������ �������� �� ��
} TRBIN_TRAN_HEADER;


struct	TRANBITFLAG
{
	BYTE	nTranType	:2;						// 0: Ʈ�� ,1:FID 
	BYTE	nRecordCount:4;						// ���ڵ� ����(�ִ�:16��)
	BYTE	nDumy		:2;						// ���� 
};									

// ���̳ʸ� Ʈ���� ������ ���ڵ� ���� ������ ���� ���� ������ ������. 
typedef struct _TRBIN_TRAN_INFO
{
	char		szTrCode[UD_TRAN_CODE_LEN+1];	// TR�� Ʈ���ڵ� (11�ڸ�)
	TRANBITFLAG tranBits;						// TRANBITFLAG���� 
}TRBIN_TRAN_INFO;

struct	RECORDBITFLAG
{
	BYTE	nArrayType	:4;						// 0:����, 1:���ڱ⺻, 2:���ڱ⺻, 3:Item����, 4:����, 5:������ ������� ���(����,�迭�� ������ ����), 6 : �������ڵ� 
	BYTE	bBinaryType	:1;						// 1:���̳ʸ�����   
	BYTE	bInOut		:1;						// 0: �Է�, 1 : ���  
	BYTE	nDumy		:2;						// ���� 
};

// ���̳ʸ� Ʈ�� ���ڵ� ���� 
typedef struct _TRBIN_RECORD_INFO  
{
	char			szRecordName[UD_NAME_LEN+1];// ���ڵ� �� 
	RECORDBITFLAG   recordBits;					// RECORDBITFLAG���� 
	short			nItemCount;					// ������ ī��Ʈ(���ڵ忡 ���ԵȾ����۰���) 
	short			nTotItemDataLen;			// ������ �� ������ ���� 
	short			nItemOffset;				// �������� ������ġ 

	short			nArrayInfo1;				// ArrayType:2�̸� ���ڵ� ��ȣ, ArrayType:4 �̸� �������� 
	short			nArrayInfo2;                // ArrayType 2�̸� ������ ��ġ( ArrayType 2�� ��츸 ��ȿ)
}TRBIN_RECORD_INFO;


struct	ITEMBITFLAG
{
	unsigned long	nDataType	:4;				// ������ Ÿ��(�ִ�15) 
	// 2007/03/07 by gds �⺻���� -1�� ����ǵ��� ����(unsigned long -> long)
	long			bAttriUse	:16;				// Attribute��� ����  
	// 2007/03/07 by gds �⺻���� -1�� ����ǵ��� ����(unsigned long -> long)
	unsigned long	nPointLen	:5;				// �Ҽ��� ���� �ڸ���(�ִ�31)
	unsigned long   nDumy		:7;			// ���� 
};

// ���̳ʸ� Ʈ�� ������ ���� 
typedef struct _TRBIN_ITEM_INFO
{
	char			szItemName[UD_DD_NAME_LEN+1];// Ʈ�� ������ ������ DD ��� ���� 
	ITEMBITFLAG		tranItemBits;				// ITEMBITFLAG���� 
	short			nDataLen;					// ������ ���� 
	short			nOffsetLen;					// offset���� 
}TRBIN_ITEM_INFO;


// ���̳ʸ� ������ ���� �� ���Ǵ� ����ü 
// ���̳ʸ� Ʈ�� ��ü ���� 
typedef struct _TRBIN_TRAN_TOTAL_INFO
{
	TRBIN_TRAN_HEADER trHeader; 
	TRBIN_TRAN_INFO   trInfo; 
	TRBIN_RECORD_INFO *pTrRecord; 
	TRBIN_ITEM_INFO	  *pTrItem; 
}TRBIN_TRAN_TOTAL_INFO;  
									
typedef struct _TRBIN_COMM_TRAN_INFO					// ��ſ����� �ʿ��� ���� 
{
	TRBIN_TRAN_INFO   trInfo; 
	TRBIN_RECORD_INFO *pTrRecord; 
	TRBIN_ITEM_INFO	  *pTrItem; 
}TRBIN_COMM_TRAN_INFO;  



//-------------------------------------------------------------------------------------------
//  [6/11/2006]  �ڵ����� ���� Binaryȭ�Ϸ� �����ϴ� Format�� �����Ѵ�.

#define		DEF_AUTOTRBIN_GROUP_INFO_LEN    sizeof(AUTOTRBIN_GROUP_INFO)
#define		DEF_AUTOTRBIN_POS_INFO_LEN		sizeof(AUTOTRBIN_POS_INFO)
#define		DEF_AUTOTRBIN_TRAN_HEADER_LEN	sizeof(AUTOTRBIN_TRAN_HEADER)

#define		DEF_AUTOTRBIN_TRAN_INFO_LEN		sizeof(AUTOTRBIN_TRAN_INFO)
#define		DEF_AUTOTRBIN_RECORD_INFO_LEN	sizeof(AUTOTRBIN_RECORD_INFO)
#define		DEF_AUTOTRBIN_ITEM_INFO_LEN		sizeof(AUTOTRBIN_ITEM_INFO)

#define     UD_AUTOTRAN_CODE_LEN	5
#define     UD_FID_CODE_LEN			5

// ���̳ʸ� Ʈ�� ���Ͽ� ���Ե� Ʈ���� �� ��  
typedef struct _AUTOTRBIN_GROUP_INFO
{
	UINT 	nTranVerMajor;						// ������ �������� 	
	UINT	nTranVerMinor;						// ���̳� �������� 
	UINT	nTrCount;							// TR �� 
} AUTOTRBIN_GROUP_INFO;

// ���̳ʸ� Ʈ�� ���Ͽ� ���Ե� �� Ʈ���� ���ϳ������� ��ġ ����  
typedef struct _AUTOTRBIN_POS_INFO
{
	char szTrCode[UD_AUTOTRAN_CODE_LEN+1];			// Ʈ���ڵ�  
	int  nStartPos;								// Ʈ���� ���ϳ������� ���� ��ġ 	
	int	 nEndPos;								// Ʈ���� ���ϳ������� �� ��ġ 	
} AUTOTRBIN_POS_INFO;

// ���̳ʸ� Ʈ�� ������ ���� 
typedef struct _AUTOTRBIN_TRAN_HEADER
{
	UINT nTrTotalLength;						// TR�� �ѱ���
	UINT nRecordCount;							// TR���� ������ �� ���ڵ� ��
	UINT nItemCount;							// ���ڵ尡 ������ �������� �� ��
} AUTOTRBIN_TRAN_HEADER;


		

// ���̳ʸ� Ʈ���� ������ ���ڵ� ���� ������ ���� ���� ������ ������. 
typedef struct _AUTOTRBIN_TRAN_INFO
{
	char		szAutoTrCode[5];				// �ڵ����� TR Code �� PBID������ 1Byte�� �����Ѵ�.
	TRANBITFLAG tranBits;						// TRANBITFLAG���� 
}AUTOTRBIN_TRAN_INFO;


// ���̳ʸ� Ʈ�� ���ڵ� ���� 
typedef struct _AUTOTRBIN_RECORD_INFO  
{
	char			szRecordName[UD_NAME_LEN+1];// ���ڵ� �� 
	RECORDBITFLAG   recordBits;					// RECORDBITFLAG���� 
	short			nItemCount;					// ������ ī��Ʈ(���ڵ忡 ���ԵȾ����۰���) 
	short			nTotItemDataLen;			// ������ �� ������ ���� 
	short			nItemOffset;				// �������� ������ġ 
	short			nKeyIndex;					// �ڵ����ſ��� ����� KeyIndex���� ItemIndex��ġ.
}AUTOTRBIN_RECORD_INFO;

// ���̳ʸ� Ʈ�� ������ ���� 
typedef struct _AUTOTRBIN_ITEM_INFO
{
	char			szItemName[UD_DD_NAME_LEN+1];// Ʈ�� ������ ������ DD ��� ���� 
	char			szFID[UD_FID_CODE_LEN+1];	 // ������ITEM�� �Ҵ�Ǿ��� FID��..
	short			nFidNum;					 // ���� ������ ����(�˻��� ���ؼ� ) 
	ITEMBITFLAG		tranItemBits;				 // ITEMBITFLAG���� 
	short			nDataLen;					 // ������ ���� 
	short			nOffsetLen;					 // offset���� 
}AUTOTRBIN_ITEM_INFO;


// ���̳ʸ� ������ ���� �� ���Ǵ� ����ü 
// ���̳ʸ� Ʈ�� ��ü ���� 
typedef struct _AUTOTRBIN_TRAN_TOTAL_INFO
{
	AUTOTRBIN_TRAN_HEADER trHeader; 
	AUTOTRBIN_TRAN_INFO   trInfo; 
	AUTOTRBIN_RECORD_INFO *pTrRecord; 
	AUTOTRBIN_ITEM_INFO	  *pTrItem; 
}AUTOTRBIN_TRAN_TOTAL_INFO;  
									
typedef struct _AUTOTRBIN_COMM_TRAN_INFO					// ��ſ����� �ʿ��� ���� 
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

// ���̳ʸ� Ʈ�� ���Ͽ� ���Ե� Ʈ���� �� ��  
typedef struct _REALTRBIN_GROUP_INFO
{
	UINT 	nTranVerMajor;						// ������ �������� (DEF_REAL_TRAN_VER_MAJOR)	
	UINT	nTranVerMinor;						// ���̳� �������� (DEF_REAL_TRAN_VER_MINOR)
	UINT	nTrCount;							// TR �� 
} REALTRBIN_GROUP_INFO;

// ���̳ʸ� Ʈ�� ���Ͽ� ���Ե� �� Ʈ���� ���ϳ������� ��ġ ����  
typedef struct _REALTRBIN_POS_INFO
{
//	char szTrCode[UD_AUTOTRAN_CODE_LEN+1];		// Ʈ���ڵ�  
	int  nRealCode;								// �ڵ�����Ÿ�� 
// --> [Edit]  �̿��� 2007/03/07
	char			szRealName[UD_TRCODE_LEN+1];		// �ڵ����� ������Ʈ��
// <-- [Edit]  �̿��� 2007/03/07
	int  nStartPos;								// �ڵ������� ���ϳ������� ���� ��ġ 	
	int	 nEndPos;								// �ڵ������� ���ϳ������� �� ��ġ 	
} REALTRBIN_POS_INFO;

// ���̳ʸ� Ʈ�� ������ ���� 
typedef struct _REALTRBIN_TRAN_HEADER
{
	UINT nTrTotalLength;						// �ڵ����� TR�� �ѱ���
	UINT nRecordCount;							// �ڵ����� TR���� ������ �� ���ڵ� ��
	UINT nItemCount;							// �ڵ����� ���ڵ尡 ������ �������� �� ��
} REALTRBIN_TRAN_HEADER;


struct	REALTRANBITFLAG
{
	BYTE	nRecordCount  :4;					   // ���ڵ� ����(�ִ�:16��)
	BYTE	nSiseShareUse :1;					   // �����ü� ���Կ��� 
	BYTE	nDumy		  :3;					   // ���� 
};									

// ���̳ʸ� Ʈ���� ������ ���ڵ� ���� ������ ���� ���� ������ ������. 
typedef struct _REALTRBIN_TRAN_INFO
{
//	char		    szREALTrCode[5];				// �ڵ����� TR Code �� PBID������ 1Byte�� �����Ѵ�.
	int             nRealCode;						// �ڵ�����Ÿ��
	short			nPosConcProp;					// ü�Ἲ�� ��ġ����  (ü�ᷮ�� �� ���� ���)  
	short			nPDayCf;						// ���ϴ�� ��ġ����
	short			nCurPrice;						// ���簡��ġ���� 
													// ���������� ���ϱ� ���ؼ�(���ϴ��, ���簡��ġ���)
	short			nBasePrice;						// ���ذ���ġ����(ȣ������ �� ����)
	REALTRANBITFLAG tranBits;						// REALTRANBITFLAG���� 
}REALTRBIN_TRAN_INFO;

// ���̳ʸ� Ʈ�� ���ڵ� ���� 
typedef struct _REALTRBIN_RECORD_INFO  
{
// --> [Edit]  �̿��� 2007/03/07
	int				nRealGubun;					// �ڵ�������
	char			szRealName[UD_TRCODE_LEN+1];		// �ڵ����� ������Ʈ��
// <-- [Edit]  �̿��� 2007/03/07
//	char			szRecordName[UD_NAME_LEN+1];// ���ڵ� �� 
//	RECORDBITFLAG   recordBits;					// RECORDBITFLAG���� 
	short			nItemCount;					// ������ ī��Ʈ(���ڵ忡 ���ԵȾ����۰���) 
	short			nTotItemDataLen;			// ������ �� ������ ���� 
	short			nItemOffset;				// �������� ������ġ 

	short			nKeyIndex;					// �ڵ����ſ��� ����� KeyIndex���� ItemIndex��ġ.
}REALTRBIN_RECORD_INFO;

// ���̳ʸ� Ʈ�� ������ ����
struct	REALITEMBITFLAG
{
	unsigned long	nDataType	:4;				// ������ Ÿ��(�ִ�15) 
	unsigned long	nPointLen	:5;				// �Ҽ��� ���� �ڸ���(�ִ�31)
	unsigned long   nDumy		:23;			// ���� 
};
 
typedef struct _REALTRBIN_ITEM_INFO
{
	char			szItemName[UD_DD_NAME_LEN+1];// Ʈ�� ������ ������ DD ��� ���� 
	char			szFID[UD_FID_CODE_LEN+1];	 // ������ITEM�� �Ҵ�Ǿ��� FID��..
	short			nFidNum;					 // ���� ������ ����(�˻��� ���ؼ� ) 
	REALITEMBITFLAG	tranItemBits;				 // REALITEMBITFLAG���� 

	short			nDataLen;					 // ������ ���� 
	short			nOffsetLen;					 // offset���� 
}REALTRBIN_ITEM_INFO;


// ���̳ʸ� ������ ���� �� ���Ǵ� ����ü 
// ���̳ʸ� Ʈ�� ��ü ���� 
typedef struct _REALTRBIN_TRAN_TOTAL_INFO
{
	REALTRBIN_TRAN_HEADER trHeader; 
	REALTRBIN_TRAN_INFO   trInfo; 
	REALTRBIN_RECORD_INFO *pTrRecord; 
	REALTRBIN_ITEM_INFO	  *pTrItem; 
}REALTRBIN_TRAN_TOTAL_INFO;  
									
typedef struct _REALTRBIN_COMM_TRAN_INFO					// ��ſ����� �ʿ��� ���� 
{
	REALTRBIN_TRAN_INFO   trInfo; 
	REALTRBIN_RECORD_INFO *pTrRecord; 
	REALTRBIN_ITEM_INFO	  *pTrItem; 
}REALTRBIN_COMM_TRAN_INFO;  


#pragma pack(pop)

#endif//_COMMTRANINFO_H_
