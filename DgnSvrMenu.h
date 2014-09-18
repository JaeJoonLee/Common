#ifndef __DGNSVRMENU_H__
#define __DGNSVRMENU_H__

#pragma pack(push, 1)

/*************************************************************************************/
/* define constant                                                                   */
/*************************************************************************************/
// ������� ���� ��� ���� 
#include "CommDefineLenInfo.h"

//#define		UD_TRCODE_LEN			6
#define		UD_MENU_NAME_LEN		40
#define		UD_SHORT_NAME_LEN		9
#define		UD_TAB_NAME_LEN			20
#define		UD_TAB_NAME_LEN30		30
#define		UD_VIPGRADE_LEN			2


#define		UD_AUTHORITY_LEN		128


///////////////////////////////////////////////
// ��ü���� ����ü ���� (1:����, 2:������)
///////////////////////////////////////////////
typedef struct	tagMEDIA
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// ��ü����
	char    media_name[UD_NAME_LEN+1];					// ��ü��
	short	ordering;									// ����
} MEDIA;

///////////////////////////////////////////////
// �����׷� ����ü ����
///////////////////////////////////////////////
typedef struct	tagDUTY_GROUP
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// ��ü����
	short	duty_grp_id;								// �����׷�
	char	duty_grp_name[UD_NAME_LEN+1];				// �����׷��
	char	file_name[UD_NAME_LEN+1];					// �������ϸ�
} DUTY_GROUP;

///////////////////////////////////////////////
// ���� ����ü ����
///////////////////////////////////////////////
typedef struct	tagDUTY
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// ��ü����
	short	duty_id;									// ����
	char	duty_name[UD_NAME_LEN+1];					// ������
	short	ordering;									// ����
} DUTY;

///////////////////////////////////////////////
// ���� ����ü ����
///////////////////////////////////////////////
typedef struct	tagDUTY_GRP_DUTY
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// ��ü����
	short	duty_grp_id;								// �����׷�
	short	duty_id;									// ����
	char	duty_name[UD_NAME_LEN+1];					// ������
	short	ordering;									// ����
} DUTY_GRP_DUTY;

typedef struct	tagGRP_DUTY_IN
{
	short	media_id;									// ��ü����
	short	duty_grp_id;								// �����׷�
} GRP_DUTY_IN;


///////////////////////////////////////////////
// ���Ѽ��� ����ü ����
///////////////////////////////////////////////
typedef struct	tagMENU_AUTH
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// ��ü����
	short	duty_grp_id;								// �����׷�
	short	menu_id;									// Menu ID
	short	menu_item_id;								// Menu Item ID
	char	authority[UD_AUTHORITY_LEN+1];				// �޴�����
} MENU_AUTH;

typedef struct	tagMENUITEM_AUTH
{
//	short	media_id;									// ��ü����
//	short	duty_grp_id;								// �����׷�
	short	menu_id;									// Menu ID
	short	menu_item_id;								// Menu Item ID
	short	menu_gubun;
	short	screen_type;
	char	screen_id[UD_SCREEN_ID_LEN+1];				// Screen ID
	char	menu_name[UD_MENU_NAME_LEN+1];				// Menu��
	char	authority[UD_AUTHORITY_LEN+1];				// �޴�����
} MENUITEM_AUTH;

typedef struct	tagMENU_AUTH_IN
{
	short	media_id;									// ��ü����
	short	duty_grp_id;								// �����׷�
	short	menu_id;									// Menu ID
} MENU_AUTH_IN;


///////////////////////////////////////////////
// �޴� ����ü ����
///////////////////////////////////////////////
typedef struct	tagMENU
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// ��ü����
	short	menu_id;									// Menu ID
	char	menu_name[UD_MENU_NAME_LEN+1];				// Menu��
	short	ordering;									// ����
	short	last_index;									// �޴�Item�� ������ ���� ��ȣ
	char    created_user[UD_USER_ID_LEN+1];				// ������
	char    created_date[UD_DATETIME_LEN+1];			// ��������
	char    modified_user[UD_USER_ID_LEN+1];			// ������
	char    modified_date[UD_DATETIME_LEN+1];			// ��������
	char    checked_user[UD_USER_ID_LEN+1];				// üũ��
	char    checked_date[UD_DATETIME_LEN+1];			// üũ����
} MENU;

///////////////////////////////////////////////
// �޴�Item ����ü ����
///////////////////////////////////////////////
typedef struct	tagMENU_ITEM_IN
{
	short	media_id;									// ��ü����
	short	menu_id;									// Menu ID
} MENU_ITEM_IN;

typedef struct	tagMENU_ITEM
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// ��ü����
	short	menu_id;									// Menu ID
	short	menu_item_id;								// Menu Item ID
	short	ordering;									// ����
	short	parent_menu_id;								// Parent Menu Item ID
	short	menu_gubun;
	short	screen_type;
//	char	tr_code[UD_TRCODE_LEN+1];					// TR Code
	char	screen_id[UD_SCREEN_ID_LEN+1];				// Screen ID
	char	menu_name[UD_MENU_NAME_LEN+1];				// Menu��
	char	short_name[UD_SHORT_NAME_LEN+1];			// Short Name
	char	tab_name[UD_TAB_NAME_LEN30+1];				// Tab Name
	char	file_name[UD_NAME_LEN+1];					// Screen File Name
	char	szvipgrade[UD_VIPGRADE_LEN+1];					// Screen File Name
//	short	disp_mode;
	short	nsingleonly;		// �ߺ� ��뿩�� üũ��(0:�ߺ�����, 1: �ϳ��� ����)	
	short	nmjmenudisp;		// ������ �޴�ǥ�ÿ���(A:��ü, 1: ����)
	short	nnewmenudisp;		// �ű�ȭ�鿩��	1:�ű�
	short	ngoodmenudisp;		// ��õȭ�鿩�� 1:�߰�
	short	nstcertifidisp;		// s/t �������� 1:����, 0:������
	short	ncommogubun;		// ��ǰ���� (1:�ֽ�,2:����,3:�ɼ�,4:elw,5:�ݻ�,6:ä��)
	short	nfunctiongubun;		// ��ɱ��� (1:��������,2:�ֹ�,3:��������,4:��Ÿ)
	short	ninfogubun;			// �������� (1:��������,2:������ü,3:��������,4:���ɱ׷�)

} MENU_ITEM;


//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif		// __DGNSVRMENU_H__

