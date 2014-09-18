#ifndef _COMMONDEFINELENINFO__H_
#define _COMMONDEFINELENINFO__H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ʈ������ ������ ���� ���� ���� ���� 

// Ʈ������ ���� 
// Version
/*****************************************************/
// Version 1 : �ʱ����  
/*****************************************************/
#define		DEF_TRAN_VER_MAJOR		0		
#define		DEF_TRAN_VER_MINOR		1

#define		UD_DATACNT_LEN			4
#define		UD_NAME_LEN				20
#define		UD_DD_NAME_LEN			30		// Ʈ�� �����۱��� 
#define		UD_TRAN_NAME_LEN		30		// Tran�� ���� 

#define		UD_DOMAIN_ID_LEN		6
#define		UD_USER_ID_LEN			10
// --> [Edit]  �� �� �� 2006/06/09
#define		UD_SCREEN_ID_LEN		6
// <-- [Edit]  �� �� �� 2006/06/09
#define		UD_SCREEN_NAME_LEN		30
#define		UD_CTRL_NAME_LEN		30
#define		UD_DATETIME_LEN			20

// --> [Edit]  �̿��� 2007/02/27
//#define		UD_TRAN_CODE_LEN		15
#define		UD_TRAN_CODE_LEN		32
// <-- [Edit]  �̿��� 2007/02/27

#define		UD_DATA_LEN				10
#define		UD_KORCAPTION_LEN		30
#define		UD_ENGCAPTION_LEN		30
#define		UD_FORMULA_LEN			30
#define		UD_DESCRIPTION_LEN		255

// --> [Edit]  �̿��� 2007/08/22
#define		UD_TRCODE_LEN			32		// ���Ʈ�� �ڵ� ����
// <-- [Edit]  �̿��� 2007/08/22

// --> [Edit]  �̿��� 2008/02/18
#define		UD_DATAHEADER_TR_LEN	10
// <-- [Edit]  �̿��� 2008/02/18

#define		UD_USE_AUTHORITY_LEN	32

#endif//COMMONDEFINELENINFO__H_
