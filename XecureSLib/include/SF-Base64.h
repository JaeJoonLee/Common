#ifndef _SF_BASE64_H
#define _SF_BASE64_H

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

#define ULONG unsigned long
#define UCHAR unsigned char


#ifdef  __cplusplus
extern "C" {
#endif

XECURE_API int WINAPI SF_Base64_Encode(UCHAR *t, UCHAR *f, int dlen);
XECURE_API int WINAPI SF_Base64_Decode(UCHAR *t, UCHAR *f, int n);
XECURE_API int WINAPI SF_Hex_Encode(UCHAR *out, UCHAR *in, int n);
XECURE_API int WINAPI SF_Hex_Decode(UCHAR *out, UCHAR *in, int n);


#ifdef  __cplusplus
}
#endif

#endif /* _SF_BASE64_H */





