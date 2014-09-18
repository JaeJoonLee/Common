#ifndef _SFSP_SERVER_H
#define _SFSP_SERVER_H

#include "SF-PKCS1.h"
#include "SFSP.h"
#include "SF-MD5.h"
#include "SF-Secure.h"
#include "SF-Error.h"

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

XECURE_API int WINAPI SFSP_Server_Hello(XECURE_CTX *ctx, char *out, int outsize, int *outlen, char *in, int inlen);
XECURE_API int WINAPI SFSP_Server_ID(XECURE_CTX *ctx, char *out, int outsize, int *outlen, char *in, int inlen);
XECURE_API int WINAPI SFSP_Get_Client_UserID(XECURE_CTX *ctx, char *out, int outsize, int *outlen);
XECURE_API int WINAPI SFSP_Server_ProtocolType(XECURE_CTX *ctx, char *out, int outsize, int *outlen, int ProtocolType);
XECURE_API int WINAPI SFSP_Server_Auth(XECURE_CTX *ctx, char *out, int outsize, int *outlen, char *in, int inlen, int algorithm);
XECURE_API int WINAPI SFSP_Get_Client_UserPWD(XECURE_CTX *ctx, char *out, int outsize, int *outlen);
XECURE_API int WINAPI	SFSP_Server_Auth_ProtocolType(XECURE_CTX *ctx, char *out, int outsize, int *outlen, int ProtocolType, int fOK);
XECURE_API int WINAPI SFSP_Server_SIGN_Res(XECURE_CTX *ctx, char *in, int inlen);





#ifdef  __cplusplus
}
#endif

#endif /* _SFSP_SERVER_H */




