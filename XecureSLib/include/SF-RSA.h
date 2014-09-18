#ifndef _SF_RSA_H
#define _SF_RSA_H


#include "SF-BigNum.h"
#include "SF-Rand.h"
#include "SF-Base64.h"


#ifdef  __cplusplus
extern "C" {
#endif

#define UINT	unsigned int
#define ULONG	unsigned long
#define UCHAR	unsigned char

typedef struct {
	BIGNUM *n;
	BIGNUM *e;
} RSAPublicKey;

typedef struct {
	BIGNUM *n;
	BIGNUM *e;
	BIGNUM *d;
	BIGNUM *p;
	BIGNUM *q;
	BIGNUM *dmp1;
	BIGNUM *dmq1;
	BIGNUM *iqmp;
} RSAPrivateKey;

int WINAPI SF_RSA_Encrypt(UCHAR *to, UCHAR *from, int flen, RSAPublicKey *rsa);
int WINAPI SF_RSA_Decrypt(UCHAR *to, UCHAR *from, int flen, RSAPrivateKey *rsa);
int WINAPI SF_RSA_Sign(UCHAR *to, UCHAR *from, int flen, RSAPrivateKey *rsa);
int WINAPI SF_RSA_Verify(UCHAR *to, UCHAR *from, int flen, RSAPublicKey *rsa);

int SF_RSA_mod_exp(BIGNUM *r0, BIGNUM *I, RSAPrivateKey *rsa);


#define ERR_R_MALLOC_FAILURE				10
#define ERR_LIB_BN					50
#define RSA_R_BAD_FF_HEADER				102
#define RSA_R_BAD_PAD_BYTE_COUNT			103
#define RSA_R_BLOCK_TYPE_IS_NOT_01			105
#define RSA_R_BLOCK_TYPE_IS_NOT_02			106
#define RSA_R_DATA_NOT_EQ_TO_MOD_LEN			107
#define RSA_R_DATA_TO_LARGE_FOR_KEY_SIZE		108
#define RSA_R_NULL_BEFORE_BLOCK_MISSING			110

#ifdef  __cplusplus
}
#endif

#endif /* _SF_RSA_H */




