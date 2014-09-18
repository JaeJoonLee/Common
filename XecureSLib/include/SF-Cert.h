#ifndef _SF_CERT_H
#define _SF_CERT_H


#include "SF-X509.h"
#include "SF-PKCS1.h"
#include "SF-RSAUtil.h"
#include "SF-Error.h"


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

typedef struct {
	long	serial;
	char	*subject_nation;
	char	*subject_state;
	char	*subject_locality;
	char	*subject_organ;
	char	*subject_unit;
	char	*subject_name;
	char	*subject_email;
	char	*subject_id;		/* id@server */
	char	*issuer_nation;
	char	*issuer_state;
	char	*issuer_locality;
	char	*issuer_organ;
	char	*issuer_unit;
	char	*issuer_name;
	char	*issuer_email;
	char	*valid_from;		/* YYYY-MM-DD hh:mm:ss */
	char	*valid_to;
} CERTINFO;

XECURE_API int WINAPI SF_Verify_Certificate(const char *cert, int certlen);

#ifdef  __cplusplus
}
#endif

#endif /* _SF_CERT_H */




