#ifndef __CRYPTEX_H_
#define __CRYPTEX_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef WIN32
#include <windows.h>
#endif

// error code
#define GET_BLOCKID_FAIL -1
#define GET_RANDOM_STRING_FAIL -2
#define PEM_TO_DER_FAIL	-3
#define PUBLIC_ENCRYPTION_BY_CERT_FAIL	-4
#define BASE64_ENCODE_FAIL -5
#define FAIL_GET_ALGOID_FROM_LOCAL	-6
#define FAIL_GET_KEYIV_FROM_LOCAL	-7
#define FAIL_BASE64_DECODE	-8
#define BLOCK_ENCRYPTION_FAIL	-9
#define WRONG_ARGUMENT	-10

#ifdef CSTOOLKITFORSAMSECURITY_EXPORTS
#define CSPTK_API __declspec(dllexport)
#else
#define CSPTK_API __declspec(dllimport)
#endif CSTOOLKITFORSAMSECURITY_EXPORTS
#ifdef WIN32

CSPTK_API int WINAPI TN_GenerateEx(char *Algo, char *Cert) ;
CSPTK_API int WINAPI TN_EncipherEx(unsigned char *pData, int nDataLen, char *pEncData) ;
CSPTK_API int WINAPI TN_DecipherEx(char *pEncData, unsigned char * pData, int * nDataLen) ;
CSPTK_API int WINAPI TN_GetKeyIV(char *enckeyiv) ;

#endif // WIN32

#ifdef __cplusplus
}
#endif


#endif // __CRYPTEX_H_