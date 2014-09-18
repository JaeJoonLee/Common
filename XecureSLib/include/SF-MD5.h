#ifndef _SF_MD5_H
#define _SF_MD5_H

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

#define MD5_CBLOCK			64
#define MD5_LBLOCK			16
#define MD5_BLOCK			16
#define MD5_LAST_BLOCK		56
#define MD5_LENGTH_BLOCK	8
#define MD5_DIGEST_LENGTH	16

typedef struct {
	unsigned long A,B,C,D;
	unsigned long Nl,Nh;
	unsigned long data[MD5_LBLOCK];
	int num;
} MD5_CTX;

#ifdef  __cplusplus
extern "C" {
#endif

void MD5_Init(MD5_CTX *c);
void MD5_Update(MD5_CTX *c, unsigned char *data, unsigned long len);
void MD5_Final(unsigned char *md, MD5_CTX *c);
/* unsigned char * WINAPI SF_MD5(unsigned char *d, unsigned long n);*/
unsigned char * WINAPI SF_MD5(unsigned char *d, unsigned long n,unsigned char m[MD5_DIGEST_LENGTH]);

#ifdef  __cplusplus
}
#endif

#endif /* _SF_MD5_H */






