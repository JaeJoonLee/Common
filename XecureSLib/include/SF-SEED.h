#ifndef _SF_SEED_H
#define _SF_SEED_H


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


#ifdef  __cplusplus
extern "C" {
#endif

#include "SF-Types.h"

/******************* Constant Definitions *********************/

#define NoRounds         16
#define NoRoundKeys      (NoRounds*2)
#define SeedBlockSize    16    /* in bytes */
#define SeedBlockLen     128   /* in bits */


/********************** Common Macros ************************/

#if defined(_MSC_VER)
    #define SEED_ROTL(x, n)     (_lrotl((x), (n)))
    #define SEED_ROTR(x, n)     (_lrotr((x), (n)))
#else
    #define SEED_ROTL(x, n)     (((x) << (n)) | ((x) >> (32-(n))))
    #define SEED_ROTR(x, n)     (((x) >> (n)) | ((x) << (32-(n))))
#endif


/**************** Function Prototype Declarations **************/

#ifndef PROTOTYPES
#define PROTOTYPES  1
#endif

#if PROTOTYPES
#define PROTO_LIST(list)    list
#else
#define PROTO_LIST(list)    ()
#endif

void SeedEncrypt 
    PROTO_LIST((BYTE *pbData, DWORD *pdwRoundKey));
void SeedDecrypt
    PROTO_LIST((BYTE *pbData, DWORD *pdwRoundKey));
void SeedEncRoundKey
    PROTO_LIST((DWORD *pdwRoundKey, BYTE *pbUserKey));
void SeedDecRoundKey
    PROTO_LIST((DWORD *pdwRoundKey, BYTE *pbUserKey));

/************/

XECURE_API int WINAPI SF_SEED_Enc(unsigned char *out, unsigned char *in, int n, unsigned char *key, unsigned char *iv );
XECURE_API int WINAPI SF_SEED_Dec(unsigned char *out, unsigned char *in, int n, unsigned char *key, unsigned char *iv );



#ifdef  __cplusplus
}
#endif

#endif




