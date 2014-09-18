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
        C       :  ���� �ڵ�
        ST      :  ���� ( ��, Ķ�����Ͼ� - CA )
        L       :  �ּ�
        O       :  ��� Ȥ�� ȸ���
        OU      :  �μ���
        CN      :  �̸�
        Email   :  ���ڿ����ּ�
        ID      :  ���̵�
*/
XECURE_API char* WINAPI SF_Get_Certificate_Subject_Entry( X509Certificate *x509Certificate, char *entry_code );


XECURE_API char* WINAPI SF_Get_Certificate_Issuer_Entry ( X509Certificate *x509Certificate, char *entry_code );


XECURE_API long WINAPI SF_Get_Certificate_Serial_Number_Long ( X509Certificate *x509 );


/* ������ ��ȿ�Ⱓ�� ��¥ ������ �����Ѵ�.
   which : 1 : ��ȿ�Ⱓ ���� ��¥
           2 : ��ȿ�Ⱓ ���� ��¥
   format : strftime �Լ����� ����ϴ� ������ �״�� ����Ѵ�.
*/
int  WINAPI SF_Get_Certificate_Valid_Time ( X509Certificate *x509, int which, char *time_buf, int max_size, char *format );



#ifdef  __cplusplus
}
#endif

#endif  /* __SF_X509UTIL_H__ */





