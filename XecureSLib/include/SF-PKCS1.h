#ifndef _SF_PKS1_H
#define _SF_PKS1_H

#include "SF-X509.h"
#include "SF-ASNtypes.h"
#include "SF-BigNum.h"

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


/************************************************
    PKCS1RSAPublicKey
************************************************/
typedef struct _PKCS1RSAPublicKey {
    ASN_INTEGER *modulus;
    ASN_INTEGER *publicExponent;
} PKCS1RSAPublicKey;

PKCS1RSAPublicKey * WINAPI SF_Read_BIN_To_PKCS1RSAPublicKey(BIN *bin);

PKCS1RSAPublicKey * WINAPI SF_Read_PEM_To_PKCS1RSAPublicKey(char *pem);

PKCS1RSAPublicKey * WINAPI SF_Read_X509Certificate_To_PKCS1RSAPublicKey(X509Certificate *x509Certificate);

void WINAPI SF_Free_PKCS1RSAPublicKey(PKCS1RSAPublicKey *pkcs1RSAPublicKey);

BIN * WINAPI SF_DER_Encode_PKCS1RSAPublicKey(PKCS1RSAPublicKey *pkcs1RSAPublicKey);

void WINAPI	SF_Print_PKCS1RSAPublicKey(PKCS1RSAPublicKey *pkcs1RSAPublicKey);

int WINAPI SF_PKCS1RSAPublicKey_To_RSAPublicKey(PKCS1RSAPublicKey *pkcs1RSAPublicKey, RSAPublicKey *rsa);

PKCS1RSAPublicKey * WINAPI SF_RSAPublicKey_To_PKCS1RSAPublicKey(RSAPublicKey *rsa);


/************************************************
    PKCS1RSAPrivateKey
************************************************/
typedef struct _PKCS1RSAPrivateKey {
    ASN_INTEGER *version;
    ASN_INTEGER *modulus;
    ASN_INTEGER *publicExponent;
    ASN_INTEGER *privateExponent;
    ASN_INTEGER *prime1;
    ASN_INTEGER *prime2;
    ASN_INTEGER *exponent1;
    ASN_INTEGER *exponent2;
    ASN_INTEGER *coefficient;
} PKCS1RSAPrivateKey;

PKCS1RSAPrivateKey * WINAPI SF_Read_BIN_To_PKCS1RSAPrivateKey(BIN *bin);

PKCS1RSAPrivateKey * WINAPI	SF_Read_PEM_To_PKCS1RSAPrivateKey(char *pem);

void WINAPI SF_Free_PKCS1RSAPrivateKey(PKCS1RSAPrivateKey *pkcs1RSAPrivateKey);

BIN * WINAPI SF_DER_Encode_PKCS1RSAPrivateKey(PKCS1RSAPrivateKey *pkcs1RSAPrivateKey);

void WINAPI SF_Print_PKCS1RSAPrivateKey(PKCS1RSAPrivateKey *pkcs1RSAPrivateKey);

int WINAPI SF_PKCS1RSAPrivateKey_To_RSAPrivateKey(PKCS1RSAPrivateKey *pkcs1RSAPrivateKey, RSAPrivateKey *rsa);

PKCS1RSAPrivateKey * WINAPI SF_RSAPrivateKey_To_PKCS1RSAPrivateKey(RSAPrivateKey *rsa);



#ifdef  __cplusplus
}
#endif

#endif /* _SF_PKS1_H */





