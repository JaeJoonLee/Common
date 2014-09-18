#ifndef _SF_SHA_H
#define _SF_SHA_H

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

#define SHA_CBLOCK			64
#define SHA_LBLOCK			16
#define SHA_BLOCK			16
#define SHA_LAST_BLOCK		56
#define SHA_LENGTH_BLOCK	8
#define SHA_DIGEST_LENGTH	20


#ifdef  __cplusplus
extern "C" {
#endif

XECURE_API void WINAPI SF_SHA(unsigned char *d, unsigned long n, unsigned char * pOut);

#ifdef  __cplusplus
}
#endif

#endif /* _SF_SHA_H */



