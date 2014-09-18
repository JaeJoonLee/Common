#ifndef _SFSP_CLIENT_H
#define _SFSP_CLIENT_H

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


#include "SF-PKCS1.h"
#include "SFSP.h"
#include "SF-Cert.h"
#include "SF-RSAUtil.h"
#include "SF-Secure.h"
#include "ThreadSafe.h"
#include "debug.h"


#ifdef  __cplusplus
extern "C" {
#endif

XECURE_API int WINAPI SFSP_Client_Hello(XECURE_CTX *ctx, char *out, int outsize, int *outlen);
XECURE_API int WINAPI SFSP_Client_Hello_Re(XECURE_CTX *ctx, char *in, int inlen);
XECURE_API int WINAPI SFSP_Client_ID(XECURE_CTX *ctx, char *out, int outsize, int *outlen, char *id, int idlen);
XECURE_API int WINAPI SFSP_Client_ID_Re(XECURE_CTX *ctx, char *in, int inlen);
XECURE_API int WINAPI SFSP_Client_PWD(XECURE_CTX *ctx, char *out, int outsize, int *outlen, char *pwd, int pwdlen, int algorithm);
XECURE_API int WINAPI SFSP_Client_PWD_Re(XECURE_CTX *ctx, char *in, int inlen);
XECURE_API int WINAPI SFSP_Client_SIGN_Res(XECURE_CTX *ctx, char *out, int outsize, int *outlen, char *in, int inlen);


#ifdef  __cplusplus
}
#endif

#endif /* _SFSP_CLIENT_H */




