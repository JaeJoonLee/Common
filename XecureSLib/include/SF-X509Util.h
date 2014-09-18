/********************************************************************
    SF-X509Util.h -- X.509 cert utility functions
                programmed by Jusung Baek
                1999/06/15
                Copyright (c) 1999 SoftForum, All rights reserved.
********************************************************************/

#ifndef __SF_X509UTIL_H__
#define __SF_X509UTIL_H__

#ifdef WIN32
#ifndef  WINAPI	
#define WINAPI __stdcall
#ifdef __XECURELIB__
#define XECURE_API __declspec(dllexport)
#else
#define XECURE_API __declspec(dllimport)
#endif
#endif
#else
#define WINAPI
#define XECURE_API 
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#define SF_CERT_VALID_FROM	1
#define SF_CERT_VALID_TO	2

/*
entry_code :
        C       :  국가 코드
        ST      :  지역 ( 예, 캘리포니아 - CA )
        L       :  주소
        O       :  기관 혹은 회사명
        OU      :  부서명
        CN      :  이름
        Email   :  전자우편주소
        ID      :  아이디
*/
XECURE_API char* WINAPI SF_Get_Certificate_Subject_Entry( X509Certificate *x509Certificate, char *entry_code );


XECURE_API char* WINAPI SF_Get_Certificate_Issuer_Entry ( X509Certificate *x509Certificate, char *entry_code );


XECURE_API long WINAPI SF_Get_Certificate_Serial_Number_Long ( X509Certificate *x509 );


/* 인증서 유효기간의 날짜 정보를 리턴한다.
   which : 1 : 유효기간 시작 날짜
           2 : 유효기간 만료 날짜
   format : strftime 함수에서 사용하는 포맷을 그대로 사용한다.
*/
int  WINAPI SF_Get_Certificate_Valid_Time ( X509Certificate *x509, int which, char *time_buf, int max_size, char *format );



#ifdef  __cplusplus
}
#endif

#endif  /* __SF_X509UTIL_H__ */





