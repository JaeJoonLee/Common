#ifndef _SF_HAS_H
#define _SF_HAS_H

#include "SF-Types.h"

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

#define HAS_BLKSIZE  64
#define HAS_DIGEST_LENGTH 20

/*
// defined in SF-Types.h
// typedef unsigned long int DWORD;
// typedef unsigned char BYTE;
*/

typedef struct{
    DWORD state[5];
    DWORD count[2];
    BYTE  buffer[64];
} HAS_CTX;

#ifdef  __cplusplus
extern "C" {
#endif

XECURE_API unsigned char * WINAPI SF_HAS(unsigned char *d, unsigned long n, unsigned char m[HAS_DIGEST_LENGTH]);


#ifdef  __cplusplus
}
#endif

#endif /* _SF_HAS_H */





