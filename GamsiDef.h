#if !defined(AFX_GAMSIDEF_H__F8F250A3_2616_4407_A9C3_5DE6DBF244A6__INCLUDED_)
#define AFX_GAMSIDEF_H__F8F250A3_2616_4407_A9C3_5DE6DBF244A6__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#pragma pack(push, 1)

//==========================================================
// 16���� ���ǰ� ����
#define STOPLOSS	0x00000001	// ����ν�				0x10
#define SISEGAMSI	0x00000002	// �ü�����             0x20
#define CHART		0x00000004	// ������Ʈ				0x30
#define ST_CHART	0x00000008	//		����(�ý��� Ʈ���̵�)
#define ST_JUMUN	0x00000010  // ��ž�ֹ�				0x50
#define GONGSI		0x00000020  // ����					0x60
#define NEWS		0x00000040  // ����					0x70
#define RESERCH		0x00000080  // ����ġ				0x80
#define RESERVE2	0x00000100  //		����			0x90
#define CONDITION	0x00000200  // ���ǰ˻�				0xa0
#define SINGAL		0x00000400  // Ư�̽�ȣ				0xb0
#define CHEGYEL		0x00000800  //		����(ü������)	0xc0
#define JANGO		0x00001000  //		����(�ܰ���)	0xd0
#define SPE_GONGJI  0x00002000  //		����(Ư������)	0xe0
#define RESERVE3	0x00004000  //		����			0xf0

#define MACRO_JUMUN	0x00008000  // ��ũ�� �ֹ�

// ī�װ���Ʈ��
#define CATE_STOPLOSS		0x10	// ����ν�				
#define CATE_SISEGAMSI		0x20	// �ü�����
#define CATE_CHART			0x30	// ������Ʈ				
#define CATE_ST_CHART		0x40	//		����(�ý�����Ʈ			
#define CATE_ST_JUMUN		0x50	// ��ž�ֹ�				
#define CATE_GONGSI			0x60	// ����					
#define CATE_NEWS			0x70	// ����					
#define CATE_RESERCH		0x80	// ����ġ				
#define CATE_RESERVE2		0x90	//		����					
#define CATE_CONDITION		0xa0	// ���ǰ˻�				
#define CATE_SINGAL			0xb0	// Ư�̽�ȣ				
#define CATE_CHEGYEL		0xc0	//		����(ü������				
#define CATE_JANGO			0xd0	//		����(�ܰ���				
#define CATE_SPE_GONGJI 	0xe0	//		����(Ư������				
#define CATE_RESERVE3		0xf0	//		����					



#define		UM_CONCHANGE		WM_USER+900

// �ֹ����� ����ü
typedef struct	tagJUMUN_ITEM
{
	short	nJumunCheck;		// �ֹ����� ��� ���� 
	short	nAutoJumun;			// �����ڵ� ����(0:����, 1:�ڵ�)
	short	nSMS;				// SMS�˸�
	int		nMemeGB;			// �Ÿ�����(0:���尡, 1: ����, 2: ���Ǻ�)
	int		nMemeCombo;			// �Ÿ����� ���Ǻ� �޺��ε���
	
	int		nValRadio;			// ���� ��� ����(0: �޺��� �ε���, 1:�ݾ�)
	int		nVal;				// �Է��� ����

	int		nSuRadio;			// ���� ��� ����(0:û��ݾ׺���, 1: ���������Է�, 2:�ݾ����� ���� ��� )
	int 	nSuRyang;			// �Է��� ����
	int 	nSuCheck;			// �ż��� �̼� ���� üũ��

	// �ֹ� ��� ����Ÿ ǥ�ÿ�
	char	szJumunNo[6];		// �ֹ� ��ȣ
	int		nJumunSu;			// �ֹ� ����
	int		nJumunVal;			// �ֹ� ����
	char	reserve[16];		// ����
} JUMUN_ITEM;

// �ü����� ����ü
typedef struct	tagSISEGAMSI_ITEM
{
	short	nAndOr;		// 
	short	nItem;		// �׸� �ε���
	short	nCon;		// ����
	double	dVal;		// ���ǰ�
	short	nUse;		// �������
} SISEGAMSI_ITEM;

typedef struct tagSISEGAMSI
{
	char	szKey[11+6+1];		// ���¹�ȣ+�����ڵ�
	char	szGyeja[11+1];		// ���¹�ȣ	
	char	szCode[6+1];		// �����ڵ�	
	short	nGamsiState;		// ���û��� üũ��(0 ���þ���, 1:������)

	short	nGamsiFlag;			// ���ðɸ��� ��� ���õǴ� ������ �������� �÷���

	short	nMedosu;			// �ŵ��� ���� ����(1:�ŵ�, 2:�ż�)
	char	reserve[16];		// ����

	SISEGAMSI_ITEM	item[5];
	JUMUN_ITEM		jumun;
} SISE_GAMSI;

// ��ž�ֹ�
typedef struct	tagSTOPJUMUN
{
	char	szKey[11+6+1];		// ���¹�ȣ+�����ڵ�
	char	szGyeja[11+1];		// ���¹�ȣ	
	char	szCode[6+1];		// �����ڵ�	
	short	nGamsiState;		// ���û��� üũ��(0 ���þ���, 1:������)

	short	nMedosu;			// �ŵ��� ���� ����(1:�ŵ�, 2:�ż�)
	short	nItem;				// �񱳰��ݼ���
	short	nCon;				// ����
	int		nVal;				// ���ذ���
	char	reserve[16];		// ����
	JUMUN_ITEM		jumun;
}STOP_JUMUN;


// ��ž�ν� 
typedef struct	tagSTOP_LOSS_CON
{
	short	nSiseGB;			// �ü�����
	short	nDangaGB;			// �ܰ�����
	int		nDangaVal;			// ���شܰ� �Է°�

	short	nLossCheck;			// �ս����� üũ
	int		nLossVal;			// �ս� ��
	int		nLossCombo;			// �ս� �޺�

	short	nProfitCheck;		// ����üũ
	int		nProfitVal;			// ���ͱݾ�
	int		nProfitCombo;		// �����޺�

	short	nTSCheck;			// ���ͺ�����
	int		nTSVal;				// ���� ���� ��
	int		nTSCombo;			// ���� ���� �޺�

	int		nSonValue;			// �ս� �񱳰�
	int		nIkValue;			// ���� �񱳰�
	int		nTsValue;			// ���ͺ����� �񱳰�
	int		nHighVal;			// ���ͺ����� �� �����
	int		nIkUpdate;			// ���ͽ��� ���� üũ��	
	char	reserve[16];		// ����
}STOP_LOSS_CON;

// ��ž�ν� �ܰ� ���Խ� ����
typedef struct	tagSTOPLOSS_INPUT
{
	short			nCheck;				// �ܰ� ���Խ� �ݿ�����
	char	reserve[16];		// ����
	STOP_LOSS_CON	con;
	JUMUN_ITEM		jumun;
}STOPLOSS_INPUT;

// ��ž�ν� 
typedef struct	tagSTOP_LOSS
{
	char	szKey[11+6+1];		// ���¹�ȣ+�����ڵ�
	char	szGyeja[11+1];		// ���¹�ȣ	
	char	szCode[6+1];		// �����ڵ�	
	short	nGamsiState;		// ���û��� üũ��(0 ���þ���, 1:������)
	char	reserve[16];		// ����

	STOP_LOSS_CON	con;
	JUMUN_ITEM		jumun;
}STOP_LOSS;


// �ֹ�â ���� ����ü
typedef struct	tagJUMUN_WND_INFO
{
	HWND	hParentWnd;
	short	nGubun;				// 0:�ü����øż�, 1:�ü����� �ŵ� 2:��ž�ν�, 3:��ž�ֹ�, 4:��ũ�� �ֹ�
	char	szGyeja[11+1];		// ���¹�ȣ	
	char	szCode[6+1];		// �����ڵ�	

	// ��ũ�� �ֹ� ���� �߰�����
	char	szPasswd[8+1];		// ���º��	
	short	nMacroIndex;		// ��ũ�� �ֹ� �ε���

	char	szJumunMsg[80];		// �ֹ���� �޼���
	JUMUN_ITEM		jumun;
} JUMUN_WND_INFO;


//====================================================================
// ���� �ɼ� ��ž�ν� ���� ����ü ����
//====================================================================


// ���� �ֹ����� ����ü
typedef struct	tagFU_JUMUN_ITEM
{
	short	nJumunCheck;		// �ֹ����� ��� ���� 
	short	nAutoJumun;			// �����ڵ� ����(0:����, 1:�ڵ�)
	short	nSMS;				// SMS�˸�
	int		nMemeGB;			// �Ÿ�����(0:���尡, 1: ����, 2: ���Ǻ�)
	
	int		nValRadio;			// ���� ��� ����(0: �޺��� �ε���, 1:�ݾ�)
	float	fVal;				// �Է��� ����

	int		nSuRadio;			// ���� ��� ����(0:û��ݾ׺���, 1: ���������Է�, 2:�ݾ����� ���� ��� )
	int 	nSuRyang;			// �Է��� ����
	// �ֹ� ��� ����Ÿ ǥ�ÿ�
	char	szJumunNo[7];		// �ֹ� ��ȣ
	int		nJumunSu;			// �ֹ� ����
	int		nJumunVal;			// �ֹ� ����
	char	reserve[16];		// ����

} FU_JUMUN_ITEM;

// ���� ��ž�ν� 
typedef struct	tagFU_STOP_LOSS_CON
{
	short	nSiseGB;			// �ü�����
	short	nDangaGB;			// �ܰ�����
	float	fDangaVal;			// ���شܰ� �Է°�

	short	nLossCheck;			// �ս����� üũ
	float	fLossVal;			// �ս� ��
	int		nLossCombo;			// �ս� �޺�

	short	nProfitCheck;		// ����üũ
	float	fProfitVal;			// ���ͱݾ�
	int		nProfitCombo;		// �����޺�

	short	nTSCheck;			// ���ͺ�����
	float	fTSVal;				// ���� ���� ��
	int		nTSCombo;			// ���� ���� �޺�

	float	fSonValue;			// �ս� �񱳰�
	float	fIkValue;			// ���� �񱳰�
	float	fTsValue;			// ���ͺ����� �񱳰�
	float	fHighVal;			// ���ͺ����� �� �����
	int		nIkUpdate;			// ���ͽ��� ���� üũ��	

	char	reserve[16];		// ����
}FU_STOP_LOSS_CON;
//====================================================================
// ���� ��ž�ν� 
//====================================================================
typedef struct	tagFU_STOP_LOSS
{
	char	szKey[11+8+1];		// ���¹�ȣ+�����ڵ�
	char	szGyeja[11+1];		// ���¹�ȣ	
	char	szCode[8+1];		// �����ڵ�	
	short	nGamsiState;		// ���û��� üũ��(0 ���þ���, 1:������)
	char	reserve[16];		// ����

	FU_STOP_LOSS_CON	con;
	FU_JUMUN_ITEM		jumun;
}FU_STOP_LOSS;

// ��ž�ν� �ܰ� ���Խ� ����
typedef struct	tagFU_STOPLOSS_INPUT
{
	short			nCheck;				// �ܰ� ���Խ� �ݿ�����
	char	reserve[16];		// ����
	FU_STOP_LOSS_CON	con;
	FU_JUMUN_ITEM		jumun;
}FU_STOPLOSS_INPUT;
//====================================================================
// ��ž�ֹ�
//====================================================================
typedef struct	tagFU_STOPJUMUN
{
	char	szKey[11+8+1];		// ���¹�ȣ+�����ڵ�
	char	szGyeja[11+1];		// ���¹�ȣ	
	char	szCode[8+1];		// �����ڵ�	
	short	nGamsiState;		// ���û��� üũ��(0 ���þ���, 1:������)

	short	nMedosu;			// �ŵ��� ���� ����(1:�ŵ�, 2:�ż�)
	short	nItem;				// �񱳰��ݼ���
	short	nCon;				// ����
	float	fVal;				// ���ذ���
	
	char	reserve[16];		// ����

	FU_JUMUN_ITEM	jumun;
}FU_STOP_JUMUN;

//====================================================================
// �ֹ�â ���� ����ü
typedef struct	tagFU_JUMUN_WND_INFO
{
	HWND	hParentWnd;
	short	nGubun;				// 0:�ż�, 1:�ŵ�
	char	szGyeja[11+1];		// ���¹�ȣ	
	char	szCode[8+1];		// �����ڵ�	

	// ��ũ�� �ֹ� ���� �߰�����
	char	szPasswd[8+1];		// ���º��	
	short	nMacroIndex;		// ��ũ�� �ֹ� �ε���

	char	szJumunMsg[80];		// �ֹ���� �޼���
	FU_JUMUN_ITEM	jumun;
} FU_JUMUN_WND_INFO;
//====================================================================


// ��ȣ�ֹ� ���� ����ü
typedef struct	tagSIGN_JUMUN_ITEM
{
	int		nMemeCombo;			// �Ÿ����� �޺��ε���
	int		nVal;				// �Է��� ����
	int 	nSuRyang;			// �Է��� ����
	int 	nSuCheck;			// �ż��� �̼� ���� üũ��
	char	reserve[16];		// ����
} SIGN_JUMUN_ITEM;

typedef struct	tagSIGN_JUMUN
{
	SIGN_JUMUN_ITEM	medo;
	SIGN_JUMUN_ITEM	mesu;
} SIGN_JUMUN;


#pragma pack(pop)

#endif // !defined(AFX_GAMSIDEF_H__F8F250A3_2616_4407_A9C3_5DE6DBF244A6__INCLUDED_)
