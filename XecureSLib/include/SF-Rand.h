#ifndef _SF_RAND_H
#define _SF_RAND_H

#include "SF-MD5.h"

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

#define ULONG	unsigned long
#define UCHAR	unsigned char

#ifdef  __cplusplus
extern "C" {
#endif

void WINAPI SF_RandBytes(UCHAR  *buf, int num);
void SF_RandSeed(UCHAR *buf, int num);

#ifdef  __cplusplus
}
#endif

#endif /* _SF_RAND_H */





