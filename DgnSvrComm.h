/*************************************************************************************/
/*  1. ���α׷�ID : 0201                                                             */
/*  2. ���α׷��� :                                                                  */
/*  3. ���񽺸�   : 0201                                                             */
/*  4. ������̺� :                                                                  */
/*  5. �ۼ���     :                                                                  */
/*  6. �Է��׸�   :                                                                  */
/*  7. ����׸�   :                                                                  */
/*************************************************************************************/
#ifndef __DGNSVRCOMM_H__
#define __DGNSVRCOMM_H__

#pragma pack(push, 1)

/*************************************************************************************/
/* include file                                                                      */
/*************************************************************************************/

/*************************************************************************************/
/* define constant                                                                   */
/*************************************************************************************/
// ������� ���� ��� ���� 
#include "CommDefineLenInfo.h"

typedef struct tagDGN_RPDATA
{
	long			lRecvLen;							// ������ ������(Ʈ���� ��� ���������� ����ó���� �ϴ� ��� ������ �ʿ���)	
	char*			pRecvData;
} DGN_RPDATA, *LPDGN_RPDATA;


typedef struct	tagLOG_ON
{
	bool	is_manager;									// ����������
	bool	fid_manager;								// FID����������
	bool	menu_manager;								// Menu����������
	bool	dict_manager;								// DD����������
} LOG_ON;


typedef struct  tagUSER_INFO_Redefine
{
	char	user_id[UD_USER_ID_LEN+1];					// user_id
	char	language[2+1];								// language
} USER_INFO_Redefine;

// --> [Edit]  ������ 2006/05/09 Class�� �浹�� �ٽ� ����
// 
// typedef struct  tagUSER_INFO
// {
// 	char	user_id[UD_USER_ID_LEN+1];					// user_id
// 	char	language[2+1];								// language
// } USER_INFO;
// <-- [Edit]  ������ 2006/05/09

typedef struct	tagBUSEO
{
	short	buseo_id;									// buseo_id
	char	buseo_name[30+1];							// �μ���
	short	ordering;									// ����
} BUSEO;

typedef struct	tagUSER
{
	char	user_id[UD_USER_ID_LEN+1];					// user_id
	char	user_name[UD_NAME_LEN+1];					// ����ڸ�
	char	password[8+1];								// ��й�ȣ
	short	buseo_id;									// �μ�ID
	char	phone_no[20+1];								// ��ȭ��ȣ
	short	is_manager;									// ����������
	short	fid_manager;								// FID����������
	short	menu_manager;								// Menu����������
	short	dict_manager;								// DD����������
} USER;

typedef struct	tagSCREEN_SEARCH
{
	char	search_id[25+1];							// search_id
	char	search_info[255];							// ����
} SCREEN_SEARCH;

typedef struct  tagANNOUNCE
    {
	int		announce_id;
	char	input_date[8+1];
	char	user_id[UD_USER_ID_LEN+1];
	char	title[50+1];
	char	description[4000+1];
} ANNOUNCE;

typedef struct  tagANNOUNCE_LIST
    {
	int		announce_id;
	char	input_date[8+1];
	char	user_id[UD_USER_ID_LEN+1];
	char	user_name[UD_NAME_LEN+1];
	char	title[50+1];
	char	description[4000+1];
} ANNOUNCE_LIST;

typedef struct  tagANNOUNCE_WHERE
    {
	char	user_id[UD_USER_ID_LEN+1];
	char	start_date[8+1];
	char	end_date[8+1];
} ANNOUNCE_WHERE;


//<math.h>���ϰ� DOMAIN �浹 
typedef struct	tagDOMAIN
{
	char    domain_id[UD_DOMAIN_ID_LEN+1];				// domain_id
	char    domain_name[UD_NAME_LEN+1];					// domain_name
	short	ordering;
} FN_DOMAIN;

typedef struct	tagEDIT_DOMAIN
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	char    domain_id[UD_DOMAIN_ID_LEN+1];				// domain_id
	char    domain_name[UD_NAME_LEN+1];					// domain_name
	short	ordering;
} EDIT_DOMAIN;

typedef struct	tagSYSTEM
{
	char    sys_id[3+1];								// system_id
	char    sys_name[30+1];								// system_name
	short	parent_order;
	short	ordering;
} SYSTEM;

typedef struct	tagEDIT_SYSTEMS
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	char    sys_id[3+1];								// system_id
	char    sys_name[30+1];								// system_name
	short	parent_order;
	short	ordering;
} EDIT_SYSTEMS;

typedef struct	tagUSER_SYSTEM
{
	char	user_id[UD_USER_ID_LEN+1];					// user_id
	char    sys_id[3+1];								// system_id
	char    sys_name[30+1];								// system_name
	short	ordering;
	short	is_editable;								// �������ɿ���
} USER_SYSTEM;

typedef struct  tagSCREEN_CTRL
{
    char	screen_id[UD_SCREEN_ID_LEN+1];				// screen_id
    short	ordering;
    char	ctrl_name[UD_CTRL_NAME_LEN+1];
    char	parent_name[UD_CTRL_NAME_LEN+1];
    short	ctrl_type;
    short	current_tab;
    short	ctrl_left;
    short	ctrl_top;
    short	ctrl_width;
    short	ctrl_height;
    int		fid_list_len;
    unsigned char __RPC_FAR *fid_list;
    int ctrl_property_len;
    unsigned char __RPC_FAR *ctrl_property;
    int event_script_len;
    unsigned char __RPC_FAR *event_script;
}	SCREEN_CTRL;

typedef struct  tagSCREEN_LAYOUT
{
	char    screen_id[UD_SCREEN_ID_LEN+1];				// screen_id
	short	current_id;
	short	parent_id;
	short	ordering;
	short	view_type;
	short	view_width;
    short	view_height;
    short	row_num;
    short	col_num;
    short	first_tab;
    char	view_scr_id[UD_SCREEN_ID_LEN+1];
    char	view_scr_name[UD_SCREEN_NAME_LEN+1];
    int		tab_info_len;
    unsigned char __RPC_FAR *tab_info;
}	SCREEN_LAYOUT;


typedef struct  tagSCREEN
{
	char	screen_id[UD_SCREEN_ID_LEN + 1];				// screen_id
	char	screen_name[UD_SCREEN_NAME_LEN + 1];
	short	major_version;
	short	minor_version;
	short	screen_type;
	char	domain_id[UD_DOMAIN_ID_LEN + 1];
	short	screen_width;
	short	screen_height;
	int		tab_order_len;
	unsigned char __RPC_FAR *tab_order;
	int comm_info_len;
	unsigned char __RPC_FAR *comm_info;
	int trcomm_info_len;
	unsigned char __RPC_FAR *trcomm_info;
	int tranmem_info_len;
	unsigned char __RPC_FAR *tranmem_info;
	int tran_codes_len;
	unsigned char __RPC_FAR *tran_codes;
	short	init_focus;
	char	msg_display;
	char	split_fix;
	int		first_layout_type;
	char	title_button[11+1];									// 9->11 [2010/11/04 ������] ����ȭ�� Ÿ��Ʋ��ư ��������
	char	layout_type[40+1];
	char	description[100+1];
	int lsp_variable_len;
	unsigned char __RPC_FAR *lsp_variable;
	int lsp_script_len;
	unsigned char __RPC_FAR *lsp_script;
// --> [Edit]  �� �� �� 2006/06/20
	int rq_relation_len;
	unsigned char __RPC_FAR *rq_relation;
	int fidmem_info_len;
	unsigned char __RPC_FAR *fidmem_info;
	int realmem_info_len;
	unsigned char __RPC_FAR *realmem_info;
// <-- [Edit]  �� �� �� 2006/06/20
	int nextprev_info_len;
	unsigned char __RPC_FAR *nextprev_info;
// --> [Edit]  �ӹμ� 2010/05/14
	char modified_user[UD_USER_ID_LEN + 1];	//����������
	char admin[UD_USER_ID_LEN + 1];			//ȭ�������
// <-- [Edit]  �ӹμ� 2010/05/14
} SCREEN;

typedef struct	tagSCREEN_LIST
{
	char    screen_id[UD_SCREEN_ID_LEN+1];				// screen_id
	char    screen_name[UD_SCREEN_NAME_LEN+1];			// ȭ���
	char    domain_id[UD_DOMAIN_ID_LEN+1];				// domain_id
	char    checked_user[UD_USER_ID_LEN+1];				// üũ�����
	char    modified_date[UD_DATETIME_LEN+1];			// ��������
	short	progress;									// progress
//	char    download_flag[100];							// description
} SCREEN_LIST;

// --> [Edit]  ������ 2009/03/09
//	����� ������� �˻�
class CUserSearchInfo
{
public:
	CUserSearchInfo()
	{
		screen_id		= "";
		screen_name		= "";
		domain_id		= "";
		checked_user	= "";
		tran_codes		= "";
		trcomm_info		= "";
		progress		= 0;
		modified_date	= "";
	};
	virtual ~CUserSearchInfo() {}

public:
	CString screen_id;
	CString screen_name;
	CString domain_id;
	CString checked_user;
	CString tran_codes;
	CString trcomm_info;
	short	progress;
	CString modified_date;

};
typedef CArray < CUserSearchInfo*, CUserSearchInfo* >			CUserSearchInfoArray;
// <-- [Edit]  ������ 2009/03/09

// --> [Edit]  ����â 2011/01/28
//	����� ������� �˻�
class CHistoryLogInfo
{
public:
	CHistoryLogInfo()
	{
		user_id		= "";
		history_date	= "";
		object_name		= "";
		description		= "";
	};
	virtual ~CHistoryLogInfo() {}

public:
	CString user_id;
	CString history_date;
	CString object_name;
	CString description;
};
typedef CArray < CHistoryLogInfo*, CHistoryLogInfo* >			CHistoryLogInfoArray;
// <-- [Edit]  ����â 2011/01/28

typedef struct	tagSCREEN_INFO
{
	char    screen_id[UD_SCREEN_ID_LEN+1];				// screen_id
	char    screen_name[UD_SCREEN_NAME_LEN+1];			// ȭ���
	short	major_version;								// Major Version
	short	minor_version;								// Minor Version
	short	screen_type;								// screen type
	char    domain_id[UD_DOMAIN_ID_LEN+1];				// domain_id
	short	screen_width;								// Screen Width
	short	screen_height;								// Screen Height
	char    created_user[UD_USER_ID_LEN+1];				// ������
	char    created_date[UD_DATETIME_LEN+1];			// ��������
	char    modified_user[UD_USER_ID_LEN+1];			// ������
	char    modified_date[UD_DATETIME_LEN+1];			// ��������
	char    checked_user[UD_USER_ID_LEN+1];				// üũ��
	char    checked_date[UD_DATETIME_LEN+1];			// üũ����
	char	descript[100+1];							// description
	short	progress;									// progress
//	char    download_flag[100];							// description
	// --> [Edit]  �ӹμ� 2010/05/18
	char	administrator[UD_USER_ID_LEN+1];			// ȭ�������
	// <-- [Edit]  �ӹμ� 2010/05/18
} SCREEN_INFO;

typedef struct	tagMOVE_SCREEN
{
	char    screen_id[UD_SCREEN_ID_LEN+1];				// screen_id
	char    domain_id[UD_DOMAIN_ID_LEN+1];				// domain_id
} MOVE_SCREEN;

typedef struct	tagRENAME_SCREEN
{
	char    old_screen_id[UD_SCREEN_ID_LEN+1];			// Old screen_id
	char    new_screen_id[UD_SCREEN_ID_LEN+1];			// New screen_id
} RENAME_SCREEN;


// --> [Edit]  �� �� �� 2006/08/03
typedef struct  tagSCREEN_EXT
{
	char	screen_id[UD_SCREEN_ID_LEN + 1];				// screen_id
	int comm_info_len;
	char*	comm_info;
	int	trcomm_info_len;
	char*	trcomm_info;
	int tranmem_info_len;
	char*	tranmem_info;
	int tran_codes_len;
	char*	tran_codes;
	int		rq_relation_len;
	char*	rq_relation;
	int		fidmem_info_len;
	char*	fidmem_info;
	int		realmem_info_len;
	char*	realmem_info;
	int		nextprev_info_len;
	char*	nextprev_info;
} SCREEN_EXT;
// <-- [Edit]  �� �� �� 2006/08/03


// --> [Edit]  �� �� �� 2006/08/03
typedef struct  tagSCREENVER_LIST
{
	char	screen_id[UD_SCREEN_ID_LEN + 1];				// screen_id
	int		nOrdering;
	int		nMajorVer;
	int		nMinorVer;
	char    created_user[UD_USER_ID_LEN+1];				// ������
	char    created_date[UD_DATETIME_LEN+1];			// ��������
	char	descript[2000+1];							// description
} SCREENVER_LIST;
// <-- [Edit]  �� �� �� 2006/08/03



typedef struct	tagTRAN
{
	char	tran_code[UD_TRAN_CODE_LEN + 1];
	char	tran_name[UD_TRAN_NAME_LEN + 1];
	char	domain_id[UD_DOMAIN_ID_LEN + 1];
	short	major_ver;
	short	minor_ver;
	short	tran_type;
	BYTE	target_server;
//	short	target_server;
	short	is_encrypt;
	short	is_compress;
	short	is_use_cert;
	char	description[UD_DESCRIPTION_LEN + 1];
	char	created_user[UD_NAME_LEN + 1];
	char	created_date[UD_DATETIME_LEN + 1];
	char	modified_user[UD_NAME_LEN + 1];
	char	modified_date[UD_DATETIME_LEN + 1];
	char	checked_user[UD_NAME_LEN + 1];
	char	checked_date[UD_DATETIME_LEN + 1];
	short	record_cnt;
	short	item_cnt;
	int		tran_info_len;
	char*	tran_info;

// --> [Edit]  �̿��� 2008/02/18
	short	is_dataheader;
	char	data_trcode[UD_DATAHEADER_TR_LEN + 1];		// �νõ� 
	char	data_jobchk[1+1];								// �۾�����
// <-- [Edit]  �̿��� 2008/02/18

} TRAN;

typedef struct tagTRAN_RECORD
{
	char	tran_code[UD_TRAN_CODE_LEN + 1];
	char	record_name[UD_NAME_LEN + 1];
	short	ordering;
	short	io_type;		// IN:0 OUT:1 [�鵿�� 4/19/2006]
/*	short	is_array;
	short	array_cnt;
	short	is_binary;
// --> [Edit]  �� �� �� 2006/06/08
	short	data_cnt_pos;							// ������ ���� ������ ���� �÷��� ��ġ
// <-- [Edit]  �� �� �� 2006/06/08
*/
	short	is_binary;								
	short	array_type;								// 0:����, 1:���ڱ⺻, 2:���ڱ⺻, 3:Item����,      4:����
	char	array_info[60+1];						// "",      char(4),   long,	   recordName.Item,  10
// --> [Edit]  �� �� �� 2006/06/08
// <-- [Edit]  �� �� �� 2006/06/08
	char	description[UD_DESCRIPTION_LEN + 1];
} TRAN_RECORD;

typedef struct tagTRAN_ITEM
{
	char	tran_code[UD_TRAN_CODE_LEN + 1];
	char	record_name[UD_NAME_LEN + 1];
	short	ordering;
	short	is_attribute;
	char	dd_name[UD_DD_NAME_LEN+1];
	short	dd_type;
	short	fid;
	short	data_type_id;
	short	data_len;
	short	decimal_point;
// --> [Edit]  �� �� �� 2006/07/19
	short	db_data_type_id;
	short	db_data_len;
	short	db_decimal_point;
// <-- [Edit]  �� �� �� 2006/07/19
	char	kor_caption[UD_KORCAPTION_LEN + 1];
	char	eng_caption[UD_ENGCAPTION_LEN + 1];
	short	ctrl_type;
// --> [Edit]  �� �� �� 2006/06/19
	char	description[UD_DESCRIPTION_LEN + 1];		// ����
// <-- [Edit]  �� �� �� 2006/06/19
} TRAN_ITEM;

/*typedef struct tagTranVer 
{
	char	tranCode[UD_TRAN_CODE_LEN + 1];
	short	majorVer;
	short	minorVer;
	char	contants[UD_NAME_LEN + 1];
} TRANVERSION;
*/

typedef struct	tagDD_GROUP
{
	char	group_code[10+1];							// group code
	char	group_name[30+1];							// group name
	short	ordering;									// ����
} DD_GROUP;

typedef struct tagDataDictionary
{
	char	dd_name[UD_DD_NAME_LEN + 1];
	char	group_code[10 + 1];
	short	dd_type;									// DD Type(1:�Ϲ�DD, 2:����DD, 3:���DD, 4:�ü�DD)
	char	is_domain;									// Domain����('Y':Domain, 'N':Domain�ƴ�)
	short	data_type_id;								// ������ Ÿ��
	short	data_len;									// ������ ����
	short	decimal_point;								// ������ �Ҽ��� ��ġ
	short	db_data_type_id;							// DB�� ������ Ÿ��
	short	db_data_len;								// DB�� ������ ����
	short	db_decimal_point;							// DB�� ������ �Ҽ��� ��ġ
	char	kor_caption[UD_KORCAPTION_LEN + 1];			// �ѱ� Caption
	char	eng_caption[UD_ENGCAPTION_LEN + 1];			// ���� Caption
	short	ctrl_type;									// ��Ʈ�� Ÿ��
	short	fid;										// FID ��ȣ
	short	mask_info;									// Mask ����
	char	biz_sys_id[3 + 1];							// ��û��������
	char	ref_dd_name1[UD_DD_NAME_LEN + 1];			// ���� DD
	char	ref_dd_name2[UD_DD_NAME_LEN + 1];			// ���� DD
	char	ref_dd_name3[UD_DD_NAME_LEN + 1];			// ���� DD
	char	request_emplno[16 + 1];						// ��û���
	char	request_date[UD_DATETIME_LEN + 1];			// ��û����
	char	regist_emplno[16 + 1];						// ��ϻ��
	char	regist_date[UD_DATETIME_LEN + 1];			// �������
	char	description[UD_DESCRIPTION_LEN + 1];		// ����
} DATADICTIONARY;

typedef struct	tagFID
{
	char	proc_flag;
	short	fid;									// fid
	char	kor_caption[UD_KORCAPTION_LEN+1];		
	char	eng_caption[UD_ENGCAPTION_LEN+1];		
	short	max_disp_len;							// ȭ�鿡 �����ϴ� ��Ʈ���� ũ�⸦ ���ϱ� ���� �ʿ�
	char	dd_list[200+1];							// dd list
	char	description[UD_DESCRIPTION_LEN + 1];
} FID;

// Group Fid
typedef struct	tagGID
{
	short	gid;									// gid
	char	gid_name[30+1];							// gid name
	short	ordering;								// ����
	short	is_array;								// �迭�ΰ�?
} GID;

typedef struct	tagGID_FID
{
	char	proc_flag;
	short	gid;									// gid
	short	fid;									// fid
	short	ordering;								// ����
} GID_FID;

// �ǽð� ��� Ÿ��
typedef struct  tagREAL_TYPE
{
	char	proc_flag;
	short	realtype_id;
	char	realtype_name[UD_NAME_LEN+1];		// 20�ڸ� 
//	char	realtype_name[UD_DD_NAME_LEN+1];	// 30�ڸ� 
	short	ordering;
	short	rtype_dd_cnt;
}REAL_TYPE;

// �ǽð� ��� Ÿ�Ժ� DD ����
typedef struct  tagREAL_TYPE_DD
{
	short	realtype_id;
// --> [Edit]  �� �� �� 2006/06/07
	short	is_in_rec;								// 1:Input, 2:Output
// <-- [Edit]  �� �� �� 2006/06/07
	short	ordering;
	char	dd_name[UD_DD_NAME_LEN+1];
	char	kor_caption[UD_KORCAPTION_LEN+1];		
	char	eng_caption[UD_ENGCAPTION_LEN+1];		
	short	fid;
	short	data_type_id;								// ������ Ÿ��
	short	data_len;									// ������ ����
	short	decimal_point;								// ������ �Ҽ��� ��ġ
	short	is_key_use;									// Key ��뿩��
}REAL_TYPE_DD;


// --> [Edit]  �̿��� 2008/02/22
// �ǽð� ��� Ÿ��
typedef struct  tagFID_TYPE
{
	char	proc_flag;
	char	fidtype_id[UD_NAME_LEN+1];
	char	fidtype_name[UD_NAME_LEN+1];		// 20�ڸ� 
	short	ordering;
	short	rtype_dd_cnt;
}FID_TYPE;

// �ǽð� ��� Ÿ�Ժ� DD ����
typedef struct  tagFID_TYPE_DD
{
	char	fidtype_id[UD_DD_NAME_LEN+1];
	short	is_in_rec;								// 1:Input, 2:Output
	short	ordering;
	char	dd_name[UD_DD_NAME_LEN+1];
	char	kor_caption[UD_KORCAPTION_LEN+1];		
	char	eng_caption[UD_ENGCAPTION_LEN+1];		
	short	fid;
	short	data_type_id;								// ������ Ÿ��
	short	data_len;									// ������ ����
	short	decimal_point;								// ������ �Ҽ��� ��ġ
	short	is_key_use;									// Key ��뿩��
}FID_TYPE_DD;

// <-- [Edit]  �̿��� 2008/02/22


typedef struct	tagSEARCH_FID_IN
{
	int		search_type;							// Type (1:Fid ����, 2:�˻���)
	short	start_fid;								// Start Fid
	short	end_fid;								// End Fid
	char	caption[UD_KORCAPTION_LEN+1];			// �˻���
} SEARCH_FID_IN;

typedef struct	tagSEARCH_DD_IN
{
	int		search_type;							// Type (1:DD Type, 2:FID, 3:SystemID, 4:��û���)
	char	caption[UD_KORCAPTION_LEN+1];			// �˻���
	short	start_fid;								// Start Fid
	short	end_fid;								// End Fid
} SEARCH_DD_IN;

// --> [Edit]  ��â�� 2006/09/08
// CommsDbg���� Ʈ�������� ���̳ʸ� �������� �ޱ����� ����ü ����

#define		DEF_DGN_TRBIN_TRAN_HEADER_LEN	sizeof(DGN_TRBIN_TRAN_HEADER)
#define		DEF_DGN_TRBIN_TRAN_INFO_LEN		sizeof(DGN_TRBIN_TRAN_INFO)
#define		DEF_DGN_TRBIN_RECORD_INFO_LEN	sizeof(DGN_TRBIN_RECORD_INFO)
#define		DEF_DGN_TRBIN_ITEM_INFO_LEN		sizeof(DGN_TRBIN_ITEM_INFO)

// ���̳ʸ� Ʈ�� ������ ���� 
typedef struct _DGN_TRBIN_TRAN_HEADER
{
	short nTrTotalLength;						// TR�� �ѱ���
	short nRecordCount;							// TR���� ������ �� ���ڵ� ��
	short nItemCount;							// ���ڵ尡 ������ �������� �� ��
} DGN_TRBIN_TRAN_HEADER;


// ���̳ʸ� Ʈ���� ������ ���ڵ� ���� ������ ���� ���� ������ ������. 
typedef struct _DGN_TRBIN_TRAN_INFO
{
	char	tran_code[UD_TRAN_CODE_LEN+1];		// TR�� Ʈ���ڵ� (11�ڸ�)
	char	tran_name[UD_TRAN_NAME_LEN + 1];
	short	tran_type;							// 0: Ʈ�� ,1:FID 
	short	record_cnt;							// ���ڵ� ����(�ִ�:16��)
	BYTE	target_server;						// ������ ���� 

	short	is_encrypt;
	short	is_compress;
	short	is_use_cert;
}DGN_TRBIN_TRAN_INFO;

// ���̳ʸ� Ʈ�� ���ڵ� ���� 
typedef struct _DGN_TRBIN_RECORD_INFO  
{
	char	szRecordName[UD_NAME_LEN+1];		// ���ڵ� �� 
	char	description[UD_NAME_LEN + 1];		// ���ڵ� Ÿ��Ʋ�� 	

	BYTE	bInOut;								// 0: �Է�, 1 : ���  
	BYTE	nArrayType;							// 0:����, 1:���ڱ⺻, 2:���ڱ⺻, 3:Item����, 4:����, 5:������ ������� ���(����,�迭�� ������ ����), 6 : �������ڵ� 
	BYTE	bBinaryType;						// 1:���̳ʸ�����   

	short	nItemCount;							// ������ ī��Ʈ(���ڵ忡 ���ԵȾ����۰���) 
	short	nTotItemDataLen;					// ������ �� ������ ���� 
	short	nItemOffset;						// �������� ������ġ 

	short	nArrayInfo1;						// ArrayType:2�̸� ���ڵ� ��ȣ, ArrayType:4 �̸� �������� 
	short	nArrayInfo2;						// ArrayType 2�̸� ������ ��ġ( ArrayType 2�� ��츸 ��ȿ)
}DGN_TRBIN_RECORD_INFO;

// ���̳ʸ� Ʈ�� ������ ���� 
typedef struct _DGN_TRBIN_ITEM_INFO
{
	char	szItemName[UD_DD_NAME_LEN+1];		// Ʈ�� ������ ������ DD ��� ���� char	dd_name[UD_DD_NAME_LEN+1];
	char	kor_caption[UD_KORCAPTION_LEN + 1];	// Ʈ�� ������ ��
	short	bAttriUse;							// 1:Attribute���   
	short	data_type_id;						// ������ Ÿ��(�ִ�15) 
	short	decimal_point;						// �Ҽ��� ���� �ڸ���(�ִ�31)
	short	nDataLen;							// ������ ���� 
	short	nOffsetLen;							// offset����( ���ΰ��) 
}DGN_TRBIN_ITEM_INFO;


// ���̳ʸ� Ʈ�� ��ü ���� 
typedef struct _DGN_TRBIN_TRAN_TOTAL_INFO
{
	DGN_TRBIN_TRAN_HEADER	trHeader;			// Ʈ�����  
	DGN_TRBIN_TRAN_INFO		trInfo;				// Ʈ������ 
	DGN_TRBIN_RECORD_INFO	*pTrRecord;			// ���ڵ����� 
	DGN_TRBIN_ITEM_INFO		*pTrItem;			// ���������� 
}DGN_TRBIN_TRAN_TOTAL_INFO;  

typedef struct _DGN_TRBIN_COMM_TRAN_INFO		// ��ſ����� �ʿ��� ���� 
{
	DGN_TRBIN_TRAN_INFO   trInfo; 
	DGN_TRBIN_RECORD_INFO *pTrRecord; 
	DGN_TRBIN_ITEM_INFO	  *pTrItem; 
}DGN_TRBIN_COMM_TRAN_INFO;  

// �ڵ����ſ� 
#define		DEF_DGN_REALTRBIN_GROUP_INFO_LEN    sizeof(DGN_REALTRBIN_GROUP_INFO)
#define		DEF_DGN_REALTRBIN_POS_INFO_LEN		sizeof(DGN_REALTRBIN_POS_INFO)
#define		DEF_DGN_REALTRBIN_TRAN_HEADER_LEN	sizeof(DGN_REALTRBIN_TRAN_HEADER)

#define		DEF_DGN_REALTRBIN_TRAN_INFO_LEN		sizeof(DGN_REALTRBIN_TRAN_INFO)
#define		DEF_DGN_REALTRBIN_RECORD_INFO_LEN	sizeof(DGN_REALTRBIN_RECORD_INFO)
#define		DEF_DGN_REALTRBIN_ITEM_INFO_LEN		sizeof(DGN_REALTRBIN_ITEM_INFO)


// ���̳ʸ� Ʈ�� ���Ͽ� ���Ե� Ʈ���� �� ��  
typedef struct _DGN_REALTRBIN_GROUP_INFO
{
	UINT 	nTranVerMajor;						// ������ �������� (DEF_REAL_TRAN_VER_MAJOR)	
	UINT	nTranVerMinor;						// ���̳� �������� (DEF_REAL_TRAN_VER_MINOR)
	UINT	nTrCount;							// TR �� 
} DGN_REALTRBIN_GROUP_INFO;


typedef struct _DGN_REALTRBIN_POS_INFO
{
//	char szTrCode[UD_AUTOTRAN_CODE_LEN+1];		// Ʈ���ڵ�  
	int  nRealCode;								// �ڵ�����Ÿ�� 
	int  nStartPos;								// �ڵ������� ���ϳ������� ���� ��ġ 	
	int	 nEndPos;								// �ڵ������� ���ϳ������� �� ��ġ 	
} DGN_REALTRBIN_POS_INFO;

// ���̳ʸ� Ʈ�� ������ ���� 
typedef struct _DGN_REALTRBIN_TRAN_HEADER
{
	UINT nTrTotalLength;						// �ڵ����� TR�� �ѱ���
	UINT nRecordCount;							// �ڵ����� TR���� ������ �� ���ڵ� ��
	UINT nItemCount;							// �ڵ����� ���ڵ尡 ������ �������� �� ��
} DGN_REALTRBIN_TRAN_HEADER;


struct	DGN_REALTRANBITFLAG
{
	BYTE	nRecordCount:4;						// ���ڵ� ����(�ִ�:16��)
	BYTE	nDumy		:4;						// ���� 
};									

// ���̳ʸ� Ʈ���� ������ ���ڵ� ���� ������ ���� ���� ������ ������. 
typedef struct _DGN_REALTRBIN_TRAN_INFO
{
	char			realtype_name[UD_NAME_LEN+1];   // �ڵ����� �̸� 
	int             nRealCode;						// �ڵ�����Ÿ��
	short			nPosConcProp;					// ü�Ἲ�� ��ġ����  (ü�ᷮ�� �� ���� ���)  
	short			nPDayCf;						// ���ϴ�� ��ġ����
	short			nCurPrice;						// ���簡��ġ���� 
													// ���������� ���ϱ� ���ؼ�(���ϴ��, ���簡��ġ���)
	short			nBasePrice;						// ���ذ���ġ����(ȣ������ �� ����)
	DGN_REALTRANBITFLAG tranBits;						// REALTRANBITFLAG���� 
}DGN_REALTRBIN_TRAN_INFO;

// ���̳ʸ� Ʈ�� ���ڵ� ���� 
typedef struct _DGN_REALTRBIN_RECORD_INFO  
{
	short			nItemCount;					// ������ ī��Ʈ(���ڵ忡 ���ԵȾ����۰���) 
	short			nTotItemDataLen;			// ������ �� ������ ���� 
	short			nItemOffset;				// �������� ������ġ 

	short			nKeyIndex;					// �ڵ����ſ��� ����� KeyIndex���� ItemIndex��ġ.
}DGN_REALTRBIN_RECORD_INFO;

// ���̳ʸ� Ʈ�� ������ ����
struct	DGN_REALITEMBITFLAG
{
	unsigned long	nDataType	:4;				// ������ Ÿ��(�ִ�15) 
	unsigned long	nPointLen	:5;				// �Ҽ��� ���� �ڸ���(�ִ�31)
	unsigned long   nDumy		:23;			// ���� 
};
 
typedef struct _DGN_REALTRBIN_ITEM_INFO
{
	char			kor_ItemCaption[UD_KORCAPTION_LEN + 1];	// Ʈ�� ������ ��
	char			szItemName[UD_DD_NAME_LEN+1];// Ʈ�� ������ ������ DD ��� ���� 
//	char			szFID[UD_FID_CODE_LEN+1];	 // ������ITEM�� �Ҵ�Ǿ��� FID��..
	short			nFidNum;					 // ���� ������ ����(�˻��� ���ؼ� ) 
	DGN_REALITEMBITFLAG	tranItemBits;			 // REALITEMBITFLAG���� 

	short			nDataLen;					 // ������ ���� 
	short			nOffsetLen;					 // offset���� 
}DGN_REALTRBIN_ITEM_INFO;


// ���̳ʸ� ������ ���� �� ���Ǵ� ����ü 
// ���̳ʸ� Ʈ�� ��ü ���� 
typedef struct _DGN_REALTRBIN_TRAN_TOTAL_INFO
{
	DGN_REALTRBIN_TRAN_HEADER trHeader; 
	DGN_REALTRBIN_TRAN_INFO   trInfo; 
	DGN_REALTRBIN_RECORD_INFO *pTrRecord; 
	DGN_REALTRBIN_ITEM_INFO	  *pTrItem; 
}DGN_REALTRBIN_TRAN_TOTAL_INFO;  
									

typedef struct _DGN_REALTRBIN_COMM_TRAN_INFO					// ��ſ����� �ʿ��� ���� 
{
	DGN_REALTRBIN_TRAN_INFO   trInfo; 
	DGN_REALTRBIN_RECORD_INFO *pTrRecord; 
	DGN_REALTRBIN_ITEM_INFO	  *pTrItem; 
}DGN_REALTRBIN_COMM_TRAN_INFO;  

// <-- [Edit]  ��â�� 2006/09/08



//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif		// __DGNSVRCOMM_H__

