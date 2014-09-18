#if !defined (_HEADERFILE_DEFINE_OF_CODE_H)
#define _HEADERFILE_DEFINE_OF_CODE_H


// #include "../../_include/DefineCode.h"


typedef struct
{
    char gb             ;       /* '1':주식, '2':코스닥    */
								//상장 종목 							= "1";
								//코스닥 종목 						= "2";
								//프리보드 							= "3";
								//선물, 스프레드 						= "4";
								//옵션 								= "5";
								//채권 								= "8";
								//수익증권 							= "9";
								//ETF코드 							= "A";
								//KOSPI 200 업종, KOSPI 100 업종, 장내업종, KRX, KRX업종 = "B";
								//코스닥 업종, 코스닥 50 				= "C";
								//개별주식옵션  						= "G";
								//프리보드업종 						= "L";
								//스타선물 							= "M";
								//주식워런트 ELW 						= "N";
	char code       [ 10];      /* 종목코드                */
} TR_CODEINFO;
#define  TR_CODEINFO_SIZE sizeof(TR_CODEINFO)

typedef struct : public TR_CODEINFO
{
    char codeName       [40+1];	/* 종목명                */
} TR_CODEINFOEX;

typedef CList<TR_CODEINFOEX, TR_CODEINFOEX>		LIST_TR_CODEINFO;
//typedef CList<TR_CODEINFO, TR_CODEINFO>		LIST_TR_CODEINFO; //유진에서 변경.


#endif // _HEADERFILE_DEFINE_OF_CODE_H
