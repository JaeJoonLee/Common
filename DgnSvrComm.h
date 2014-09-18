/*************************************************************************************/
/*  1. 프로그램ID : 0201                                                             */
/*  2. 프로그램명 :                                                                  */
/*  3. 서비스명   : 0201                                                             */
/*  4. 사용테이블 :                                                                  */
/*  5. 작성자     :                                                                  */
/*  6. 입력항목   :                                                                  */
/*  7. 출력항목   :                                                                  */
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
// 공통길이 정보 헤더 파일 
#include "CommDefineLenInfo.h"

typedef struct tagDGN_RPDATA
{
	long			lRecvLen;							// 데이터 사이즈(트랜인 경우 가변적으로 예외처리를 하는 경우 사이즈 필요함)	
	char*			pRecvData;
} DGN_RPDATA, *LPDGN_RPDATA;


typedef struct	tagLOG_ON
{
	bool	is_manager;									// 관리자유무
	bool	fid_manager;								// FID관리자유무
	bool	menu_manager;								// Menu관리자유무
	bool	dict_manager;								// DD관리자유무
} LOG_ON;


typedef struct  tagUSER_INFO_Redefine
{
	char	user_id[UD_USER_ID_LEN+1];					// user_id
	char	language[2+1];								// language
} USER_INFO_Redefine;

// --> [Edit]  전순모 2006/05/09 Class명 충돌로 다시 정의
// 
// typedef struct  tagUSER_INFO
// {
// 	char	user_id[UD_USER_ID_LEN+1];					// user_id
// 	char	language[2+1];								// language
// } USER_INFO;
// <-- [Edit]  전순모 2006/05/09

typedef struct	tagBUSEO
{
	short	buseo_id;									// buseo_id
	char	buseo_name[30+1];							// 부서명
	short	ordering;									// 순서
} BUSEO;

typedef struct	tagUSER
{
	char	user_id[UD_USER_ID_LEN+1];					// user_id
	char	user_name[UD_NAME_LEN+1];					// 사용자명
	char	password[8+1];								// 비밀번호
	short	buseo_id;									// 부서ID
	char	phone_no[20+1];								// 전화번호
	short	is_manager;									// 관리자유무
	short	fid_manager;								// FID관리자유무
	short	menu_manager;								// Menu관리자유무
	short	dict_manager;								// DD관리자유무
} USER;

typedef struct	tagSCREEN_SEARCH
{
	char	search_id[25+1];							// search_id
	char	search_info[255];							// 설명
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


//<math.h>파일과 DOMAIN 충돌 
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
	short	is_editable;								// 수정가능여부
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
	char	title_button[11+1];									// 9->11 [2010/11/04 박정일] 종합화면 타이틀버튼 갯수수정
	char	layout_type[40+1];
	char	description[100+1];
	int lsp_variable_len;
	unsigned char __RPC_FAR *lsp_variable;
	int lsp_script_len;
	unsigned char __RPC_FAR *lsp_script;
// --> [Edit]  박 경 규 2006/06/20
	int rq_relation_len;
	unsigned char __RPC_FAR *rq_relation;
	int fidmem_info_len;
	unsigned char __RPC_FAR *fidmem_info;
	int realmem_info_len;
	unsigned char __RPC_FAR *realmem_info;
// <-- [Edit]  박 경 규 2006/06/20
	int nextprev_info_len;
	unsigned char __RPC_FAR *nextprev_info;
// --> [Edit]  임민수 2010/05/14
	char modified_user[UD_USER_ID_LEN + 1];	//최종수정자
	char admin[UD_USER_ID_LEN + 1];			//화면관리자
// <-- [Edit]  임민수 2010/05/14
} SCREEN;

typedef struct	tagSCREEN_LIST
{
	char    screen_id[UD_SCREEN_ID_LEN+1];				// screen_id
	char    screen_name[UD_SCREEN_NAME_LEN+1];			// 화면명
	char    domain_id[UD_DOMAIN_ID_LEN+1];				// domain_id
	char    checked_user[UD_USER_ID_LEN+1];				// 체크사용자
	char    modified_date[UD_DATETIME_LEN+1];			// 수정일자
	short	progress;									// progress
//	char    download_flag[100];							// description
} SCREEN_LIST;

// --> [Edit]  강지원 2009/03/09
//	사용자 통신정보 검색
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
// <-- [Edit]  강지원 2009/03/09

// --> [Edit]  양윤창 2011/01/28
//	사용자 통신정보 검색
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
// <-- [Edit]  양윤창 2011/01/28

typedef struct	tagSCREEN_INFO
{
	char    screen_id[UD_SCREEN_ID_LEN+1];				// screen_id
	char    screen_name[UD_SCREEN_NAME_LEN+1];			// 화면명
	short	major_version;								// Major Version
	short	minor_version;								// Minor Version
	short	screen_type;								// screen type
	char    domain_id[UD_DOMAIN_ID_LEN+1];				// domain_id
	short	screen_width;								// Screen Width
	short	screen_height;								// Screen Height
	char    created_user[UD_USER_ID_LEN+1];				// 생성자
	char    created_date[UD_DATETIME_LEN+1];			// 생성일자
	char    modified_user[UD_USER_ID_LEN+1];			// 수정자
	char    modified_date[UD_DATETIME_LEN+1];			// 수정일자
	char    checked_user[UD_USER_ID_LEN+1];				// 체크자
	char    checked_date[UD_DATETIME_LEN+1];			// 체크일자
	char	descript[100+1];							// description
	short	progress;									// progress
//	char    download_flag[100];							// description
	// --> [Edit]  임민수 2010/05/18
	char	administrator[UD_USER_ID_LEN+1];			// 화면관리자
	// <-- [Edit]  임민수 2010/05/18
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


// --> [Edit]  박 경 규 2006/08/03
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
// <-- [Edit]  박 경 규 2006/08/03


// --> [Edit]  박 경 규 2006/08/03
typedef struct  tagSCREENVER_LIST
{
	char	screen_id[UD_SCREEN_ID_LEN + 1];				// screen_id
	int		nOrdering;
	int		nMajorVer;
	int		nMinorVer;
	char    created_user[UD_USER_ID_LEN+1];				// 생성자
	char    created_date[UD_DATETIME_LEN+1];			// 생성일자
	char	descript[2000+1];							// description
} SCREENVER_LIST;
// <-- [Edit]  박 경 규 2006/08/03



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

// --> [Edit]  이용준 2008/02/18
	short	is_dataheader;
	char	data_trcode[UD_DATAHEADER_TR_LEN + 1];		// 턱시도 
	char	data_jobchk[1+1];								// 작업구분
// <-- [Edit]  이용준 2008/02/18

} TRAN;

typedef struct tagTRAN_RECORD
{
	char	tran_code[UD_TRAN_CODE_LEN + 1];
	char	record_name[UD_NAME_LEN + 1];
	short	ordering;
	short	io_type;		// IN:0 OUT:1 [백동주 4/19/2006]
/*	short	is_array;
	short	array_cnt;
	short	is_binary;
// --> [Edit]  박 경 규 2006/06/08
	short	data_cnt_pos;							// 데이터 개수 정보를 가진 컬럼의 위치
// <-- [Edit]  박 경 규 2006/06/08
*/
	short	is_binary;								
	short	array_type;								// 0:단일, 1:문자기본, 2:숫자기본, 3:Item지정,      4:고정
	char	array_info[60+1];						// "",      char(4),   long,	   recordName.Item,  10
// --> [Edit]  박 경 규 2006/06/08
// <-- [Edit]  박 경 규 2006/06/08
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
// --> [Edit]  박 경 규 2006/07/19
	short	db_data_type_id;
	short	db_data_len;
	short	db_decimal_point;
// <-- [Edit]  박 경 규 2006/07/19
	char	kor_caption[UD_KORCAPTION_LEN + 1];
	char	eng_caption[UD_ENGCAPTION_LEN + 1];
	short	ctrl_type;
// --> [Edit]  박 경 규 2006/06/19
	char	description[UD_DESCRIPTION_LEN + 1];		// 설명
// <-- [Edit]  박 경 규 2006/06/19
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
	short	ordering;									// 순서
} DD_GROUP;

typedef struct tagDataDictionary
{
	char	dd_name[UD_DD_NAME_LEN + 1];
	char	group_code[10 + 1];
	short	dd_type;									// DD Type(1:일반DD, 2:조합DD, 3:계산DD, 4:시세DD)
	char	is_domain;									// Domain여부('Y':Domain, 'N':Domain아님)
	short	data_type_id;								// 데이터 타입
	short	data_len;									// 데이터 길이
	short	decimal_point;								// 데이터 소수점 위치
	short	db_data_type_id;							// DB용 데이터 타입
	short	db_data_len;								// DB용 데이터 길이
	short	db_decimal_point;							// DB용 데이터 소수점 위치
	char	kor_caption[UD_KORCAPTION_LEN + 1];			// 한글 Caption
	char	eng_caption[UD_ENGCAPTION_LEN + 1];			// 영문 Caption
	short	ctrl_type;									// 컨트롤 타입
	short	fid;										// FID 번호
	short	mask_info;									// Mask 정보
	char	biz_sys_id[3 + 1];							// 요청업무구분
	char	ref_dd_name1[UD_DD_NAME_LEN + 1];			// 연관 DD
	char	ref_dd_name2[UD_DD_NAME_LEN + 1];			// 연관 DD
	char	ref_dd_name3[UD_DD_NAME_LEN + 1];			// 연관 DD
	char	request_emplno[16 + 1];						// 요청사번
	char	request_date[UD_DATETIME_LEN + 1];			// 요청일자
	char	regist_emplno[16 + 1];						// 등록사번
	char	regist_date[UD_DATETIME_LEN + 1];			// 등록일자
	char	description[UD_DESCRIPTION_LEN + 1];		// 설명
} DATADICTIONARY;

typedef struct	tagFID
{
	char	proc_flag;
	short	fid;									// fid
	char	kor_caption[UD_KORCAPTION_LEN+1];		
	char	eng_caption[UD_ENGCAPTION_LEN+1];		
	short	max_disp_len;							// 화면에 생성하는 컨트롤의 크기를 정하기 위해 필요
	char	dd_list[200+1];							// dd list
	char	description[UD_DESCRIPTION_LEN + 1];
} FID;

// Group Fid
typedef struct	tagGID
{
	short	gid;									// gid
	char	gid_name[30+1];							// gid name
	short	ordering;								// 순서
	short	is_array;								// 배열인가?
} GID;

typedef struct	tagGID_FID
{
	char	proc_flag;
	short	gid;									// gid
	short	fid;									// fid
	short	ordering;								// 순서
} GID_FID;

// 실시간 통신 타입
typedef struct  tagREAL_TYPE
{
	char	proc_flag;
	short	realtype_id;
	char	realtype_name[UD_NAME_LEN+1];		// 20자리 
//	char	realtype_name[UD_DD_NAME_LEN+1];	// 30자리 
	short	ordering;
	short	rtype_dd_cnt;
}REAL_TYPE;

// 실시간 통신 타입별 DD 정보
typedef struct  tagREAL_TYPE_DD
{
	short	realtype_id;
// --> [Edit]  박 경 규 2006/06/07
	short	is_in_rec;								// 1:Input, 2:Output
// <-- [Edit]  박 경 규 2006/06/07
	short	ordering;
	char	dd_name[UD_DD_NAME_LEN+1];
	char	kor_caption[UD_KORCAPTION_LEN+1];		
	char	eng_caption[UD_ENGCAPTION_LEN+1];		
	short	fid;
	short	data_type_id;								// 데이터 타입
	short	data_len;									// 데이터 길이
	short	decimal_point;								// 데이터 소수점 위치
	short	is_key_use;									// Key 사용여부
}REAL_TYPE_DD;


// --> [Edit]  이용준 2008/02/22
// 실시간 통신 타입
typedef struct  tagFID_TYPE
{
	char	proc_flag;
	char	fidtype_id[UD_NAME_LEN+1];
	char	fidtype_name[UD_NAME_LEN+1];		// 20자리 
	short	ordering;
	short	rtype_dd_cnt;
}FID_TYPE;

// 실시간 통신 타입별 DD 정보
typedef struct  tagFID_TYPE_DD
{
	char	fidtype_id[UD_DD_NAME_LEN+1];
	short	is_in_rec;								// 1:Input, 2:Output
	short	ordering;
	char	dd_name[UD_DD_NAME_LEN+1];
	char	kor_caption[UD_KORCAPTION_LEN+1];		
	char	eng_caption[UD_ENGCAPTION_LEN+1];		
	short	fid;
	short	data_type_id;								// 데이터 타입
	short	data_len;									// 데이터 길이
	short	decimal_point;								// 데이터 소수점 위치
	short	is_key_use;									// Key 사용여부
}FID_TYPE_DD;

// <-- [Edit]  이용준 2008/02/22


typedef struct	tagSEARCH_FID_IN
{
	int		search_type;							// Type (1:Fid 구간, 2:검색어)
	short	start_fid;								// Start Fid
	short	end_fid;								// End Fid
	char	caption[UD_KORCAPTION_LEN+1];			// 검색어
} SEARCH_FID_IN;

typedef struct	tagSEARCH_DD_IN
{
	int		search_type;							// Type (1:DD Type, 2:FID, 3:SystemID, 4:요청사번)
	char	caption[UD_KORCAPTION_LEN+1];			// 검색어
	short	start_fid;								// Start Fid
	short	end_fid;								// End Fid
} SEARCH_DD_IN;

// --> [Edit]  김창하 2006/09/08
// CommsDbg에서 트랜정보를 바이너리 형식으로 받기위한 구조체 정의

#define		DEF_DGN_TRBIN_TRAN_HEADER_LEN	sizeof(DGN_TRBIN_TRAN_HEADER)
#define		DEF_DGN_TRBIN_TRAN_INFO_LEN		sizeof(DGN_TRBIN_TRAN_INFO)
#define		DEF_DGN_TRBIN_RECORD_INFO_LEN	sizeof(DGN_TRBIN_RECORD_INFO)
#define		DEF_DGN_TRBIN_ITEM_INFO_LEN		sizeof(DGN_TRBIN_ITEM_INFO)

// 바이너리 트랜 데이터 정보 
typedef struct _DGN_TRBIN_TRAN_HEADER
{
	short nTrTotalLength;						// TR의 총길이
	short nRecordCount;							// TR내에 포함한 총 레코드 수
	short nItemCount;							// 레코드가 포함한 아이템의 총 수
} DGN_TRBIN_TRAN_HEADER;


// 바이너리 트랜의 정보로 레코드 수와 아이템 수에 대한 정보를 가진다. 
typedef struct _DGN_TRBIN_TRAN_INFO
{
	char	tran_code[UD_TRAN_CODE_LEN+1];		// TR의 트랜코드 (11자리)
	char	tran_name[UD_TRAN_NAME_LEN + 1];
	short	tran_type;							// 0: 트랜 ,1:FID 
	short	record_cnt;							// 레코드 개수(최대:16개)
	BYTE	target_server;						// 목적지 서버 

	short	is_encrypt;
	short	is_compress;
	short	is_use_cert;
}DGN_TRBIN_TRAN_INFO;

// 바이너리 트랜 레코드 정보 
typedef struct _DGN_TRBIN_RECORD_INFO  
{
	char	szRecordName[UD_NAME_LEN+1];		// 레코드 명 
	char	description[UD_NAME_LEN + 1];		// 레코드 타이틀명 	

	BYTE	bInOut;								// 0: 입력, 1 : 출력  
	BYTE	nArrayType;							// 0:단일, 1:문자기본, 2:숫자기본, 3:Item지정, 4:고정, 5:데이터 사이즈로 계산(단일,배열인 구조만 적용), 6 : 가변레코드 
	BYTE	bBinaryType;						// 1:바이너리파일   

	short	nItemCount;							// 아이템 카운트(레코드에 포함된아이템개수) 
	short	nTotItemDataLen;					// 아이템 총 데이터 길이 
	short	nItemOffset;						// 아이템의 시작위치 

	short	nArrayInfo1;						// ArrayType:2이면 레코드 번호, ArrayType:4 이면 고정개수 
	short	nArrayInfo2;						// ArrayType 2이면 아이템 위치( ArrayType 2인 경우만 유효)
}DGN_TRBIN_RECORD_INFO;

// 바이너리 트랜 아이템 정보 
typedef struct _DGN_TRBIN_ITEM_INFO
{
	char	szItemName[UD_DD_NAME_LEN+1];		// 트랜 아이템 명으로 DD 명과 동일 char	dd_name[UD_DD_NAME_LEN+1];
	char	kor_caption[UD_KORCAPTION_LEN + 1];	// 트랜 아이템 명
	short	bAttriUse;							// 1:Attribute사용   
	short	data_type_id;						// 데이터 타입(최대15) 
	short	decimal_point;						// 소수점 이하 자리수(최대31)
	short	nDataLen;							// 데이터 길이 
	short	nOffsetLen;							// offset정보( 내부계산) 
}DGN_TRBIN_ITEM_INFO;


// 바이너리 트랜 전체 정보 
typedef struct _DGN_TRBIN_TRAN_TOTAL_INFO
{
	DGN_TRBIN_TRAN_HEADER	trHeader;			// 트랜헤더  
	DGN_TRBIN_TRAN_INFO		trInfo;				// 트랜정보 
	DGN_TRBIN_RECORD_INFO	*pTrRecord;			// 레코드정보 
	DGN_TRBIN_ITEM_INFO		*pTrItem;			// 아이템정보 
}DGN_TRBIN_TRAN_TOTAL_INFO;  

typedef struct _DGN_TRBIN_COMM_TRAN_INFO		// 통신에서만 필요한 정보 
{
	DGN_TRBIN_TRAN_INFO   trInfo; 
	DGN_TRBIN_RECORD_INFO *pTrRecord; 
	DGN_TRBIN_ITEM_INFO	  *pTrItem; 
}DGN_TRBIN_COMM_TRAN_INFO;  

// 자동갱신용 
#define		DEF_DGN_REALTRBIN_GROUP_INFO_LEN    sizeof(DGN_REALTRBIN_GROUP_INFO)
#define		DEF_DGN_REALTRBIN_POS_INFO_LEN		sizeof(DGN_REALTRBIN_POS_INFO)
#define		DEF_DGN_REALTRBIN_TRAN_HEADER_LEN	sizeof(DGN_REALTRBIN_TRAN_HEADER)

#define		DEF_DGN_REALTRBIN_TRAN_INFO_LEN		sizeof(DGN_REALTRBIN_TRAN_INFO)
#define		DEF_DGN_REALTRBIN_RECORD_INFO_LEN	sizeof(DGN_REALTRBIN_RECORD_INFO)
#define		DEF_DGN_REALTRBIN_ITEM_INFO_LEN		sizeof(DGN_REALTRBIN_ITEM_INFO)


// 바이너리 트랜 파일에 포함된 트랜의 총 수  
typedef struct _DGN_REALTRBIN_GROUP_INFO
{
	UINT 	nTranVerMajor;						// 메이저 버전정보 (DEF_REAL_TRAN_VER_MAJOR)	
	UINT	nTranVerMinor;						// 마이너 버전정보 (DEF_REAL_TRAN_VER_MINOR)
	UINT	nTrCount;							// TR 수 
} DGN_REALTRBIN_GROUP_INFO;


typedef struct _DGN_REALTRBIN_POS_INFO
{
//	char szTrCode[UD_AUTOTRAN_CODE_LEN+1];		// 트랜코드  
	int  nRealCode;								// 자동갱신타입 
	int  nStartPos;								// 자동갱신의 파일내에서의 시작 위치 	
	int	 nEndPos;								// 자동갱신의 파일내에서의 끝 위치 	
} DGN_REALTRBIN_POS_INFO;

// 바이너리 트랜 데이터 정보 
typedef struct _DGN_REALTRBIN_TRAN_HEADER
{
	UINT nTrTotalLength;						// 자동갱신 TR의 총길이
	UINT nRecordCount;							// 자동갱신 TR내에 포함한 총 레코드 수
	UINT nItemCount;							// 자동갱신 레코드가 포함한 아이템의 총 수
} DGN_REALTRBIN_TRAN_HEADER;


struct	DGN_REALTRANBITFLAG
{
	BYTE	nRecordCount:4;						// 레코드 개수(최대:16개)
	BYTE	nDumy		:4;						// 여분 
};									

// 바이너리 트랜의 정보로 레코드 수와 아이템 수에 대한 정보를 가진다. 
typedef struct _DGN_REALTRBIN_TRAN_INFO
{
	char			realtype_name[UD_NAME_LEN+1];   // 자동갱신 이름 
	int             nRealCode;						// 자동갱신타입
	short			nPosConcProp;					// 체결성향 위치정보  (체결량의 색 정보 사용)  
	short			nPDayCf;						// 전일대비 위치정보
	short			nCurPrice;						// 현재가위치정보 
													// 전일종가를 구하기 위해서(전일대비, 현재가위치사용)
	short			nBasePrice;						// 기준가위치정보(호가가격 색 정보)
	DGN_REALTRANBITFLAG tranBits;						// REALTRANBITFLAG정보 
}DGN_REALTRBIN_TRAN_INFO;

// 바이너리 트랜 레코드 정보 
typedef struct _DGN_REALTRBIN_RECORD_INFO  
{
	short			nItemCount;					// 아이템 카운트(레코드에 포함된아이템개수) 
	short			nTotItemDataLen;			// 아이템 총 데이터 길이 
	short			nItemOffset;				// 아이템의 시작위치 

	short			nKeyIndex;					// 자동갱신에서 사용할 KeyIndex값의 ItemIndex위치.
}DGN_REALTRBIN_RECORD_INFO;

// 바이너리 트랜 아이템 정보
struct	DGN_REALITEMBITFLAG
{
	unsigned long	nDataType	:4;				// 데이터 타입(최대15) 
	unsigned long	nPointLen	:5;				// 소수점 이하 자리수(최대31)
	unsigned long   nDumy		:23;			// 여분 
};
 
typedef struct _DGN_REALTRBIN_ITEM_INFO
{
	char			kor_ItemCaption[UD_KORCAPTION_LEN + 1];	// 트랜 아이템 명
	char			szItemName[UD_DD_NAME_LEN+1];// 트랜 아이템 명으로 DD 명과 동일 
//	char			szFID[UD_FID_CODE_LEN+1];	 // 각각의ITEM에 할당되어진 FID값..
	short			nFidNum;					 // 숫자 아이템 정보(검색을 위해서 ) 
	DGN_REALITEMBITFLAG	tranItemBits;			 // REALITEMBITFLAG정보 

	short			nDataLen;					 // 데이터 길이 
	short			nOffsetLen;					 // offset정보 
}DGN_REALTRBIN_ITEM_INFO;


// 바이너리 파일을 읽을 때 사용되는 구조체 
// 바이너리 트랜 전체 정보 
typedef struct _DGN_REALTRBIN_TRAN_TOTAL_INFO
{
	DGN_REALTRBIN_TRAN_HEADER trHeader; 
	DGN_REALTRBIN_TRAN_INFO   trInfo; 
	DGN_REALTRBIN_RECORD_INFO *pTrRecord; 
	DGN_REALTRBIN_ITEM_INFO	  *pTrItem; 
}DGN_REALTRBIN_TRAN_TOTAL_INFO;  
									

typedef struct _DGN_REALTRBIN_COMM_TRAN_INFO					// 통신에서만 필요한 정보 
{
	DGN_REALTRBIN_TRAN_INFO   trInfo; 
	DGN_REALTRBIN_RECORD_INFO *pTrRecord; 
	DGN_REALTRBIN_ITEM_INFO	  *pTrItem; 
}DGN_REALTRBIN_COMM_TRAN_INFO;  

// <-- [Edit]  김창하 2006/09/08



//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif		// __DGNSVRCOMM_H__

