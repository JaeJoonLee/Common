#ifndef __DGNSVRMENU_H__
#define __DGNSVRMENU_H__

#pragma pack(push, 1)

/*************************************************************************************/
/* define constant                                                                   */
/*************************************************************************************/
// 공통길이 정보 헤더 파일 
#include "CommDefineLenInfo.h"

//#define		UD_TRCODE_LEN			6
#define		UD_MENU_NAME_LEN		40
#define		UD_SHORT_NAME_LEN		9
#define		UD_TAB_NAME_LEN			20
#define		UD_TAB_NAME_LEN30		30
#define		UD_VIPGRADE_LEN			2


#define		UD_AUTHORITY_LEN		128


///////////////////////////////////////////////
// 매체구분 구조체 정의 (1:고객용, 2:직원용)
///////////////////////////////////////////////
typedef struct	tagMEDIA
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// 매체구분
	char    media_name[UD_NAME_LEN+1];					// 매체명
	short	ordering;									// 순서
} MEDIA;

///////////////////////////////////////////////
// 직무그룹 구조체 정의
///////////////////////////////////////////////
typedef struct	tagDUTY_GROUP
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// 매체구분
	short	duty_grp_id;								// 직무그룹
	char	duty_grp_name[UD_NAME_LEN+1];				// 직무그룹명
	char	file_name[UD_NAME_LEN+1];					// 생성파일명
} DUTY_GROUP;

///////////////////////////////////////////////
// 직무 구조체 정의
///////////////////////////////////////////////
typedef struct	tagDUTY
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// 매체구분
	short	duty_id;									// 직무
	char	duty_name[UD_NAME_LEN+1];					// 직무명
	short	ordering;									// 순서
} DUTY;

///////////////////////////////////////////////
// 직무 구조체 정의
///////////////////////////////////////////////
typedef struct	tagDUTY_GRP_DUTY
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// 매체구분
	short	duty_grp_id;								// 직무그룹
	short	duty_id;									// 직무
	char	duty_name[UD_NAME_LEN+1];					// 직무명
	short	ordering;									// 순서
} DUTY_GRP_DUTY;

typedef struct	tagGRP_DUTY_IN
{
	short	media_id;									// 매체구분
	short	duty_grp_id;								// 직무그룹
} GRP_DUTY_IN;


///////////////////////////////////////////////
// 권한설정 구조체 정의
///////////////////////////////////////////////
typedef struct	tagMENU_AUTH
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// 매체구분
	short	duty_grp_id;								// 직무그룹
	short	menu_id;									// Menu ID
	short	menu_item_id;								// Menu Item ID
	char	authority[UD_AUTHORITY_LEN+1];				// 메뉴권한
} MENU_AUTH;

typedef struct	tagMENUITEM_AUTH
{
//	short	media_id;									// 매체구분
//	short	duty_grp_id;								// 직무그룹
	short	menu_id;									// Menu ID
	short	menu_item_id;								// Menu Item ID
	short	menu_gubun;
	short	screen_type;
	char	screen_id[UD_SCREEN_ID_LEN+1];				// Screen ID
	char	menu_name[UD_MENU_NAME_LEN+1];				// Menu명
	char	authority[UD_AUTHORITY_LEN+1];				// 메뉴권한
} MENUITEM_AUTH;

typedef struct	tagMENU_AUTH_IN
{
	short	media_id;									// 매체구분
	short	duty_grp_id;								// 직무그룹
	short	menu_id;									// Menu ID
} MENU_AUTH_IN;


///////////////////////////////////////////////
// 메뉴 구조체 정의
///////////////////////////////////////////////
typedef struct	tagMENU
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// 매체구분
	short	menu_id;									// Menu ID
	char	menu_name[UD_MENU_NAME_LEN+1];				// Menu명
	short	ordering;									// 순서
	short	last_index;									// 메뉴Item의 마지막 생성 번호
	char    created_user[UD_USER_ID_LEN+1];				// 생성자
	char    created_date[UD_DATETIME_LEN+1];			// 생성일자
	char    modified_user[UD_USER_ID_LEN+1];			// 수정자
	char    modified_date[UD_DATETIME_LEN+1];			// 수정일자
	char    checked_user[UD_USER_ID_LEN+1];				// 체크자
	char    checked_date[UD_DATETIME_LEN+1];			// 체크일자
} MENU;

///////////////////////////////////////////////
// 메뉴Item 구조체 정의
///////////////////////////////////////////////
typedef struct	tagMENU_ITEM_IN
{
	short	media_id;									// 매체구분
	short	menu_id;									// Menu ID
} MENU_ITEM_IN;

typedef struct	tagMENU_ITEM
{
	char	proc_flag;									// I;Insert, U:Update, D:Delete, N:Normal
	short	media_id;									// 매체구분
	short	menu_id;									// Menu ID
	short	menu_item_id;								// Menu Item ID
	short	ordering;									// 순서
	short	parent_menu_id;								// Parent Menu Item ID
	short	menu_gubun;
	short	screen_type;
//	char	tr_code[UD_TRCODE_LEN+1];					// TR Code
	char	screen_id[UD_SCREEN_ID_LEN+1];				// Screen ID
	char	menu_name[UD_MENU_NAME_LEN+1];				// Menu명
	char	short_name[UD_SHORT_NAME_LEN+1];			// Short Name
	char	tab_name[UD_TAB_NAME_LEN30+1];				// Tab Name
	char	file_name[UD_NAME_LEN+1];					// Screen File Name
	char	szvipgrade[UD_VIPGRADE_LEN+1];					// Screen File Name
//	short	disp_mode;
	short	nsingleonly;		// 중복 허용여부 체크용(0:중복생성, 1: 하나만 생성)	
	short	nmjmenudisp;		// 직원용 메뉴표시여부(A:전체, 1: 직원)
	short	nnewmenudisp;		// 신규화면여부	1:신규
	short	ngoodmenudisp;		// 추천화면여부 1:추가
	short	nstcertifidisp;		// s/t 인증여부 1:인증, 0:미인증
	short	ncommogubun;		// 상품구분 (1:주식,2:선물,3:옵션,4:elw,5:금상,6:채권)
	short	nfunctiongubun;		// 기능구분 (1:시장정보,2:주문,3:계좌정보,4:기타)
	short	ninfogubun;			// 정보범위 (1:개별종목,2:시장전체,3:개별업종,4:관심그룹)

} MENU_ITEM;


//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif		// __DGNSVRMENU_H__

