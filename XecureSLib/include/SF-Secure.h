#ifndef _SF_SECURE_H
#define _SF_SECURE_H


#ifdef WIN32
#ifndef  WINAPI
#define WINAPI __stdcall
#endif
#ifdef __XECURELIB__
#define XECURE_API __declspec(dllexport)
#else
#define XECURE_API __declspec(dllimport)
#endif
#else
#define WINAPI
#define XECURE_API 
#endif


#include "SFSP.h"
#include "SF-RC4.h"
#include "SF-RC5.h"
#include "SF-SHA.h"
#include "SF-HAS.h"
#include "SF-MD5.h"
#include "SF-Error.h"


#define ALGORITHM_MD5 101
#define ALGORITHM_HAS 102
#define	ALGORITHM_SHA 103


#ifdef  __cplusplus
extern "C" {
#endif

XECURE_API int WINAPI SF_Block_Encrypt(XECURE_CTX *ctx, unsigned char *out, int outsize, int *outlen, unsigned char *str, int len);

XECURE_API int WINAPI SF_Block_Decrypt(XECURE_CTX *ctx, unsigned char *out, int outsize, int *outlen, unsigned char *str, int len);

XECURE_API int WINAPI SF_BlockDec(CIPHER_SPEC *spec, unsigned char *out, unsigned char *in, int inlen);

XECURE_API unsigned char * WINAPI SF_Hash(CIPHER_SPEC *spec, unsigned char *str, int len, unsigned char b64dHash[64]);

XECURE_API int WINAPI SF_Sign_Data(unsigned char *out, 
						int outsize, /* 128 */ 
						int *outlen, 
						unsigned char *org_in, 
						int org_insize);

XECURE_API int WINAPI SF_Verify_SignedData(const char *signer_pem, 
								unsigned char *sgnd_in, 
								int sgnd_insize, /* 128 */
								unsigned char *org_in, 
								int org_insize);

XECURE_API int WINAPI SF_Get_Certificate_Local_Pem(char *pPem,  unsigned *outlen, unsigned inlen);
XECURE_API int WINAPI SF_Get_Certificate_Remote_Pem(XECURE_CTX* ctx, char *pPem,  unsigned *outlen, unsigned inlen);


XECURE_API void WINAPI SF_Get_Pem_Certificate_Valid_Before(const char* pPem, 
										   int *nYear, 
										   int *nMonth, 
										   int *nDay, 
										   int *nHour, 
										   int *nMin,
										   int *nSec);
XECURE_API void WINAPI SF_Get_Pem_Certificate_Valid_After(const char* pPem, 
										   int *nYear, 
										   int *nMonth, 
										   int *nDay, 
										   int *nHour, 
										   int *nMin,
										   int *nSec);

/* -------------------------------------------------------------------------
 �Լ��̸� : SF_Get_Pem_Certificate_Common_Name
 ����     : pem ���� �������κ��� �����̸�(���� �ĺ� �̸�)�� �д´�. 
 ���� ��  : 0  - �Լ� ȣ�� ����  
			-1 - pem ������ �������� �ƴ� 
			-2 - ���������� �����̸�(���� �ĺ� �̸�)�� ã�� �� ���� 
			-? - ������ ���� �ĺ��̸���  �ʹ� ŭ 
			     (���밪 - �����̸��� ���� ���ִ� ������ ũ��)
 �Է�     : char out[40] - ���� �ĺ� �̸��� ���� ����
 �Է�     : char *pem - pem ������ ���� ������ 
------------------------------------------------------------------------- */
XECURE_API int WINAPI SF_Get_Pem_Certificate_Common_Name(char out[40], const char *pem);



typedef struct ChkSum
{
	int HashAlgorithm;
	int size;
	unsigned char HashResult[HAS_DIGEST_LENGTH];
} ChkSum;

int SF_Get_Message_ChkSum(unsigned char *out, int outsize, int *outlen, unsigned char *in, int inlen, int algorithm);
int SF_Make_Message_ChkSum(unsigned char *out, int outsize, int *outlen, unsigned char *in, int inlen, int algorithm);
int SF_Strip_SFSPMessage_ChkSum(unsigned char *out, int outsize, int *outlen, ChkSum *pChkSum,  unsigned char *SFSPMessagem, int inlen);
#ifdef  __cplusplus
}
#endif

#endif /* _SF_SECURE_H */




