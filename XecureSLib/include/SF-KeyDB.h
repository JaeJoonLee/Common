#ifndef _SF_KEYDB_H
#define _SF_KEYDB_H

#include "SF-Error.h"
#include "SF-X509.h"
#include "SFSP.h"

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

char * WINAPI SF_Read_CA_Cert(char *cn);

char * WINAPI SF_Read_User_Cert(char *id);

int WINAPI SF_Delete_CA_Cert(char *id);

int WINAPI SF_Delete_User_Cert(char *id);

int WINAPI SF_Write_Cert(char *cert);

char * WINAPI SF_Read_Key(char *id);

int WINAPI SF_Delete_Key(char *id);

int WINAPI SF_Write_Key(char *id, char *pem);

#ifdef WIN32
int WINAPI SF_Show_Certificate(XECURE_CTX *ctx, int type);
#endif




#ifdef  __cplusplus
}
#endif

#endif /* _SF_KEYDB_H */





