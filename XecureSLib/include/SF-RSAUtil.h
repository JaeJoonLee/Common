#ifndef _SF_RSAUTIL_H
#define _SF_RSAUTIL_H

#include "SF-RSA.h"
#include "SF-Base64.h"
#include "SF-TagFile.h"
#include "SF-BigNum.h"


#ifdef	__cplusplus
extern "C" {
#endif


RSAPrivateKey * WINAPI  SF_NewRSAPrivateKey();

RSAPublicKey * WINAPI SF_NewRSAPublicKey(RSAPrivateKey *key);

void WINAPI SF_FreeRSAPrivateKey(RSAPrivateKey *rsa);

void WINAPI SF_FreeRSAPublicKey(RSAPublicKey *rsa);

RSAPrivateKey * WINAPI SF_GenRSAKey(int bits);

int WINAPI SF_Verify_Sign(TAG_NODE *root);


#ifdef	__cplusplus
}
#endif

#endif /* _SF_RSAUTIL_H */




