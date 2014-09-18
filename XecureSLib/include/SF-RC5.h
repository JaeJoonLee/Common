#ifndef _SF_RC5_H
#define _SF_RC5_H

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

#define ULONG unsigned long
#define UCHAR unsigned char

XECURE_API int WINAPI SF_RC5_Encode(UCHAR *out, UCHAR *in, int n, UCHAR *key, int keylen);
XECURE_API int WINAPI SF_RC5_Decode(UCHAR *out, UCHAR *in, int n, UCHAR *key, int keylen);

#ifdef  __cplusplus
}
#endif

#endif /* _SF_RC5_H */





