//******************************************************************/
// All Rights Reserved. Copyright(c)   2005 (주)한국소리마치        /
//******************************************************************/
/*! File Name     : CommDef.h
/*! Function      :	공통헤더 정의파일 
/*! System Name   : TrBuilder
/*! Create        : 김창하 , 2006/03/15
/*! Update        : 
/*! Comment       : 
//******************************************************************/

#ifndef _COMMDEF_H_
#define _COMMDEF_H_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
  
// --> [Edit]  김정원 2006/05/04
/*
	기존의 파일에서 공통적으로 사용되는 부분만 남겨두고 
	TrBuilder에서만 사용되는 부분을 '../Builder/TrBuidler/TrBuilderDef.h'
	파일로 이동 시킴.   
*/
// <-- [Edit]  김정원 2006/05/04

//====================================================================
// Tran Info Read/Write  
// By miru 2006.03.20 

#define SNULL		_T("")		// NULL 스트링

#define BEGIN_FUNCTION_MAP		_T("BEGIN_FUNCTION_MAP")	// TR 시작
#define END_FUNCTION_MAP		_T("END_FUNCTION_MAP")		// TR 끝

#define BEGIN_DATA_MAP			_T("BEGIN_DATA_MAP")	// TR DATA 시작
#define END_DATA_MAP			_T("END_DATA_MAP")		// TR DATA 끝

#define BEGIN					_T("begin")				// TR 아이템 시작
#define END						_T("end")				// TR 아이템 끝


// Tran Info 데이터 인덱스
enum TR_INDEX{ 
	TR_CODE=0,		// 1. 트랜코드 
	TR_NAME,		// 2. 트랜명
	TR_SERVER,		// 3. 서버목적지 구분 
	TR_TYPE,		// 4. 데이터 타입 
	TR_ENCODE,		// 5. 암호화 
	TR_COMPRESS,	// 6. 압축 
	TR_CERTIFICATE,	// 7. 공인인증  
	TR_DESC,		// 8. 설명문 
	TR_DBTYPE,		// 9. DB데이터 타입 
}; 

// --> [Edit]  김정원 2006/06/16
// 서버 타입 리스트를 파일 'TranConfig.ini'에서 로드
/*
// Tran 서버 타입 인덱스 
enum TR_SERVER_TYPE{
	LOCAL_SERVER=0,		//1. Local 서버('1')
	TRAN_SERVER,		//2. Tr 서버('2')
	MASTER_SERVER,		//3. Master 서버('3')
	SYSTEM_SERVER,		//4. Tr 서버('4')
};

// Tran 서버 타입 문자열  
#define SZ_LOCAL_SERVER		_T("local")
#define SZ_TRAN_SERVER		_T("tran")
#define SZ_MASTER_SERVER	_T("master")
#define SZ_SYSTEM_SERVER	_T("system")
*/
// <-- [Edit]  김정원 2006/06/16

// Tran 데이터 타입 인덱스 
enum TR_DATA_TYPE{
	STRUCTURED_DATA=0,		//1. Structured Data 
	STRING_FID,				//2. String FID
}; 

// Tran 데이터 타입 문자열 
// --> [Edit]  이용준 2008/03/05
//#define SZ_STRUCTURED_DATA	_T("structured data")
//#define SZ_STRING_FID		_T("string fid")
#define SZ_STRUCTURED_DATA	_T("TR ")
#define SZ_STRING_FID		_T("FID")
// <-- [Edit]  이용준 2008/03/05

// Tran 암호화 타입 인덱스 
enum TR_ENCODE_TYPE{
	ENCODE_NO=0,	//1. 암호화 사용 안함 
	ENCODE_YES,		//2. 암호화 사용 	
}; 
	
// Tran 암호화 타입 문자열 
#define SZ_ENCODE_YES		_T("encode_yes")
#define SZ_ENCODE_NO		_T("encode_no")

// Tran 압축 타입 인덱스 
enum TR_COMPRESS_TYPE{
	COMPRESS_NO=0,	//1. 압축 사용 안함 
	COMPRESS_YES,	//2. 압축 사용  
}; 
	
// Tran 압축 타입 문자열 
#define SZ_COMPRESS_YES		_T("compress_yes")
#define SZ_COMPRESS_NO		_T("compress_no")

// Tran 공인인증 타입 인덱스 
enum TR_CERTIFICATE_TYPE{
	CERTIFICATE_NO=0,	//1. 공인인증 사용 안함 
	CERTIFICATE_YES		//2. 공인인증 사용 	
}; 
	
// Tran 공인인증 타입 문자열 
#define SZ_CERTIFICATE_YES		_T("certificate_yes")
#define SZ_CERTIFICATE_NO		_T("certificate_no")

// Tran 레코드 데이터 인덱스
enum TR_RECORD_INDEX{ 
	TR_RECORD_NAME=0,		// 1. 레코드 명 
	TR_RECORD_DESC,			// 2. 레코드 설명문 
	TR_RECORD_IO,			// 3. 입출력 
	TR_RECORD_ARRAY,		// 4. 배열  
	// --> [Edit]  김정원 2006/06/12
	TR_RECORD_ARRAY_INFO,	// 5. 배열 정보  
	// <-- [Edit]  김정원 2006/06/12
	TR_RECORD_BINARY		// 6. 레코드 데이터 형식 
};

// Tran 레코드 입출력 타입 인덱스  
enum RECORD_IO_TYPE{
	IN_RECORD=0,		//1. 입력 
	OUT_RECORD			//2. 출력 
}; 

// Tran 레코드 입출력 타입 문자열 
#define SZ_IN_RECORD		_T("input") 
#define SZ_OUT_RECORD		_T("output") 

// Tran 레코드 입출력 타입 문자열(한글) 
#define SZ_KOR_IN_RECORD		_T("입력") 
#define SZ_KOR_OUT_RECORD		_T("출력") 


// Tran 레코드 배열 타입 인덱스 
enum TR_ARRAY_TYPE{
	SINGLE_RECORD   =0,	//1. 'Single'	 = 0x00
	ARRAY_TYPE_CHAR =1,	//1:문자기본
	ARRAY_TYPE_LONG =2,	//2:숫자기본 
	ARRAY_TYPE_ITEM =3,	//3:Item지정, 
	ARRAY_TYPE_FIXED=4,	//4:고정
}; 

// Tran 레코드 배열 타입 문자열 
#define SZ_SINGLE_RECORD		_T("single") 
#define SZ_ARRAY_RECORD			_T("array") 

// Tran 레코드 배열 타입 문자열(한글)  
#define SZ_KOR_SINGLE_RECORD	_T("단일") 
#define SZ_KOR_ARRAY_RECORD		_T("배열") 
  
// --> [Edit]  김정원 2006/05/18
// Tran 레코드 데이터 방식 
enum TR_RECORD_COMM_TYPE
{
	CHARACTER_BASE_RECORD = 0, // Charecter-base
	BINARY_BASE_RECORD		   // Binary-base 
};

// Tran 레코드 데이터 방식 문자열 
#define SZ_CHARACTER_BASE_RECORD	_T("character-base")
#define SZ_BINARY_BASE_RECORD		_T("binary-base")

// <-- [Edit]  김정원 2006/05/18
 

// --> [Edit]  김정원 2006/05/18
// Tran 아이템 데이터 인덱스
enum TR_ITEM_INDEX{ 	
	ITEM_TITLE=0,		// 1. 타이틀 
	ITEM_NAME,			// 2. Tran 아이템 명 
	ITEM_ENGTITLE,		// 3. 영문타이틀  
	ITEM_FID,			// 4. FID 	
	ITEM_DATATYPE,		// 5. 데이터 형   
	ITEM_DATALEN,		// 6. 데이터 길이 
	ITEM_DECIAMLPOINT,	// 7. 데이터 형(소수점 이하)  	
	ITEM_CONTROL,		// 8. 컨트롤 
	ITEM_ATTRIBUTE,		// 9. 색정보 
	ITEM_DESC,			//10. 설명문 	
// --> [Edit]  박 경 규 2006/07/19
	ITEM_DBDATATYPE,	//11. DB데이터 형   
	ITEM_DBDATALEN,		//12. DB데이터 길이 
	ITEM_DBDECIAMLPOINT//13. DB데이터 형(소수점 이하)  	
// <-- [Edit]  박 경 규 2006/07/19
};
// <-- [Edit]  김정원 2006/05/18


// Tran 아이템 데이터 형 인덱스 
enum TR_ITEM_DATA_TYPE{	
	FT_BYTE=0,			// unsigned char(8bit)
	FT_SHORT,			// int16
	FT_USHORT,			// unsigned int16 
	FT_LONG,			// int32
	FT_ULONG,			// unsigned int32 
	FT_FLOAT,			// float  (4 bytes)
	FT_DOUBLE,			// double (8 bytes) 
	FT_LONGLONG,		// int64  (8 bytes)   
	FT_STRING,			// 일반 텍스트 
	FT_STRINGNUM,		// 숫자형 문자열
	FT_DATE,			// 날자형 
	FT_DAY,				// 일자형 
	FT_TIME				// 시간형 
}; 

// Tran 아이템 데이터 형 문자열  
#define SZ_BYTE			_T("byte")			// unsigned char(8bit)
#define SZ_SHORT		_T("short")			// int16
#define SZ_USHORT		_T("ushort")		// unsigned int16
#define SZ_LONG			_T("long")			// int32
#define SZ_ULONG		_T("ulong")			// unsigned int32 
#define SZ_FLOAT		_T("float")			// float  (4 bytes)
#define SZ_DOUBLE		_T("double")		// double (8 bytes) 
#define SZ_LONGLONG		_T("longlong")		// int64  (8 bytes)   
#define SZ_STRING		_T("string")		// 일반 텍스트 
#define SZ_STRINGNUM	_T("string num")	// 일반 텍스트 -> 부호있는  string num
#define SZ_DATE			_T("string nsnum")	// 날짜형 -> 부호없는  string num
#define SZ_DAY			_T("day")			// 일자형 
#define SZ_TIME			_T("time")			// 시간형 
 

// --> [Edit]  김정원 2006/05/11
// Tran 아이템 컨트롤 형 상수 
// '../SrShare/sd_global.h'에 컨트롤 정의 상수 사용  

// Tran 아이템 컨트롤 형 문자열 
#define SZ_CT_NULL		_T("nouse")
#define SZ_KOR_CT_NULL	_T("사용안함")
/*
// '../SrShare/sd_global.h'에 컨트롤 문자열 사용  
// --> 문자열 리스트는 m_GControlName에 정의 됨 
*/  	
// <-- [Edit]  김정원 2006/05/11


// Tran 아이템 색정보 
enum TR_ITEM_ATTRIBUTE_TYPE
{
	ATTRIBUTE_NO = 0,	// 색정보 없음 
	ATTRIBUTE_YES		// 색정보 있음 
}; 

// Tran 아이템 색정보 문자열  
#define SZ_ATTRIBUTE_NO		_T("no")
#define SZ_ATTRIBUTE_YES	_T("yes")

// Tran 아이템 색정보 한글 문자열 
#define SZ_KOR_ATTRIBUTE_NO		_T("없음")
#define SZ_KOR_ATTRIBUTE_YES	_T("있음")  

// --> [Edit]  김정원 2006/03/23   
// DD 아이템 드래그 앤 드랍 
#define DDITEM_DRAG_DROP _T("DDItem_DragDrop")
// <-- [Edit]  김정원 2006/03/23



// --> [Edit]  김정원 2006/03/30
// Tran 데이터 드래깅 
#define TRANINFO_DRAG_DROP _T("Tran_DragDrop")  

// Tran 데이터 드래깅 종류 
enum TRANINFO_DRAG_TYPE{
						TRAN_DRAG_UNKNOWN = 0,	//데이터 없음
						TRAN_DRAG_QUERY,
						TRAN_DRAG_TRANINFO,		//Tran 전체정보 
						TRAN_DRAG_TRANRECORD,	//Tran 레코드 
						TRAN_DRAG_TRANITEM,		//Tran 아이템  
						TRAN_DRAG_MULTIITEM,	//Tran 복수 아이템  
						TRAN_DRAG_DB_TRANINFO,	//Tran 정보(레코드 및 아이템 리스트 데이터 없음)
						FID_DRAG_QUERY,
						FID_DRAG_INOUTBLOCK,
						FID_DRAG_GID,
						FID_DRAG_FID,
						REAL_DRAG_QUERY,
						REAL_DRAG_TRANINFO,		//Tran 전체정보 
						REAL_DRAG_TRANRECORD,	//Tran 레코드 
						REAL_DRAG_TRANITEM		//Tran 아이템 
						}; 
// <-- [Edit]  김정원 2006/03/30


// --> [Edit]  김정원 2006/04/14
// 체크 아웃/인 문자열  
#define SZ_CHECK_IN		_T("CheckIn")
#define SZ_CHECK_OUT	_T("CheckOut")
// <-- [Edit]  김정원 2006/04/14

// 체크 아웃/인 문자열  
#define SZ_KOR_CHECK_IN		_T("체크인(&I)")
#define SZ_KOR_CHECK_OUT	_T("체크아웃(&O)")

// --> [Edit]  김정원 2006/04/21
// 디자인 로컬 트랜 폴더 경로 
#define SZ_DGN_TRAN_FOLDER _T("\\dgn\\tran")
// <-- [Edit]  김정원 2006/04/21

// --> [Edit]  김정원 2006/04/25
#define UD_TRAN_DRAG_FILE_POS 512
// <-- [Edit]  김정원 2006/04/25
 

// --> [Edit]  김정원 2006/05/04


// --> [Edit]  김정원 2006/05/26
//=================================================================== 
// FID 아이템 데이터 드래깅 
#define FIDINFO_DRAG_DROP	_T("{{FID_DragDrop}}")  
  
// FID 드래깅 타입 
enum FID_DRAG_TYPE
{
	FIDINFO_DRAG_UNKNOWN = 0,		// Unknown FID 아이템 드래깅  
	FIDINFO_DRAG_TABLE,			// 자동갱신 테이블 	 
	FIDINFO_DRAG_ITEM,				// 자동갱신 아이템 

	FID_DRAG_UNKNOWN = 0,		// Unknown FID 아이템 드래깅  
	FID_DRAG_GIDFID_ITEM,		// GID의 FID 아이템 드래깅
	FID_DRAG_FID_ITEM,			// FID 아이템 드래깅
	FID_DRAG_DD_ITEM			// DD 아이템 드래깅


};
// <-- [Edit]  김정원 2006/05/26


//=================================================================== 
// Tran 클립보드 데이터 종류 식별자 
#define SZ_TRAN_CLIPBRD_MULTI_ITEM _T("{{FN_TranClipboard_MultiItem}}") 

#define SZ_TRAN_CLIPBRD_TRAN_CODE  _T("{{TranCode}}") 


//=================================================================== 
// 자동갱신 테이블 드래깅 
#define REALINFO_DRAG_DROP	_T("{{RealTable_DragDrop}}")  

// 자동갱신 테이블 타입 
enum REALINFO_DRAG_TYPE
{
	REALINFO_DRAG_UNKNOWN = 0,		// Unknown FID 아이템 드래깅  
	REALINFO_DRAG_TABLE,			// 자동갱신 테이블 	 
	REALINFO_DRAG_ITEM,				// 자동갱신 아이템 
};

//=================================================================== 
// 트랜빌더 환경 파일 
#define SZ_TRAN_CONFIG_FILE		_T("\\dgn\\TranConfig.ini")


#endif//_COMMDEF_H_
