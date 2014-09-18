//******************************************************************/
// All Rights Reserved. Copyright(c)   2005 (주)한국소리마치        /
//******************************************************************/
/*! File Name     : AcctDef.h
/*! Function      :	계좌 공통헤더 정의파일 
/*! System Name   : 
/*! Create        : 남상윤 , 2006/07/25
/*! Update        : 
/*! Comment       : 
//******************************************************************/

#ifndef _ACCTDEF_H_
#define _ACCTDEF_H_



#define ACCOUNT_COMBO_INI		_T("\\Data\\Account.ini")
#define ACCOUNT_COMBO_EMP_INI	_T("\\Data\\AccountEmp.ini")

#define		TRUST_ACCT			_T("01")	//위탁계좌
#define		SAVE_ACCT			_T("02")	//저축계좌
#define		FO_ACCT				_T("03")	//선물옵션
#define		MUTUAL_ACCT			_T("04")	//국내뮤추얼
#define		RANDIO_ACCT			_T("05")	//수시입출금식 RP
#define		FOR_MUT_ACCT		_T("06")	//해외증권/뮤추얼
#define		TUSIN_ACCT			_T("07")	//투신
#define		BANKTRUST_ACCT		_T("08")	//은행위탁계좌
#define		KOSDAQ_FUT_ACCT		_T("09")	//코스닥 선물
#define		TRUST_ONLY01_ACCT	_T("10")	//국내뮤추얼
#define		SAVE_0609_ACCT		_T("11")	//저축 06, 09
#define		SINTAK_ACCT			_T("12")	//신탁


#define		ORDER_ACCT			_T("J")		//주문용 계좌
#define		INQUIRE_ACCT		_T("Q")		//조회횽 계좌

#define 	_TCH_COMMA			0x2C		// 쉼표(,)

#define 	CHK_TRUE			'1'
#define 	CHK_FALSE			'0'

#define		ACC_NAME			0
#define		ACC_PWD				1
#define		ACC_PWD_B_REG		2
#define		ACC_STOP_ACC		3
#define		ACC_ODR_ACC			4

#define		ACTIVE_ACC			_T("1")
#define		DEACTIVE_ACC		_T("0")





#endif//_ACCTDEF_H_
