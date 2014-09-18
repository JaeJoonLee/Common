#ifndef _COMMONDEFINELENINFO__H_
#define _COMMONDEFINELENINFO__H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 트랜관련 데이터 길이 정보 정의 파일 

// 트랜버전 정보 
// Version
/*****************************************************/
// Version 1 : 초기버전  
/*****************************************************/
#define		DEF_TRAN_VER_MAJOR		0		
#define		DEF_TRAN_VER_MINOR		1

#define		UD_DATACNT_LEN			4
#define		UD_NAME_LEN				20
#define		UD_DD_NAME_LEN			30		// 트랜 아이템길이 
#define		UD_TRAN_NAME_LEN		30		// Tran명 길이 

#define		UD_DOMAIN_ID_LEN		6
#define		UD_USER_ID_LEN			10
// --> [Edit]  박 경 규 2006/06/09
#define		UD_SCREEN_ID_LEN		6
// <-- [Edit]  박 경 규 2006/06/09
#define		UD_SCREEN_NAME_LEN		30
#define		UD_CTRL_NAME_LEN		30
#define		UD_DATETIME_LEN			20

// --> [Edit]  이용준 2007/02/27
//#define		UD_TRAN_CODE_LEN		15
#define		UD_TRAN_CODE_LEN		32
// <-- [Edit]  이용준 2007/02/27

#define		UD_DATA_LEN				10
#define		UD_KORCAPTION_LEN		30
#define		UD_ENGCAPTION_LEN		30
#define		UD_FORMULA_LEN			30
#define		UD_DESCRIPTION_LEN		255

// --> [Edit]  이용준 2007/08/22
#define		UD_TRCODE_LEN			32		// 통신트랜 코드 길이
// <-- [Edit]  이용준 2007/08/22

// --> [Edit]  이용준 2008/02/18
#define		UD_DATAHEADER_TR_LEN	10
// <-- [Edit]  이용준 2008/02/18

#define		UD_USE_AUTHORITY_LEN	32

#endif//COMMONDEFINELENINFO__H_
