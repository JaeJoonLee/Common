#ifndef _SF_ERROR_H
#define _SF_ERROR_H

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



#define ERR_BUFFER_TOO_SMALL	-1000
#define ERR_PROTOCOL_SYNTAX		-1001
#define	ERR_INVALID_SIGN_PWD	-1002
#define ERR_INVALID_CONTEXT		-1003
#define ERR_FILE_OPEN_FAILED	-1004
#define ERR_RSA_KEY_GEN			-1005
#define ERR_CERT_INVALID		-1006
#define ERR_INVALID_PWD			-1007
#define ERR_INVALID_RSA_KEY		-1008
#define ERR_INVALID_SIGNED_MSG	-1009
#define ERR_INVALID_SIGNATURE	-1010
#define ERR_CERT_EXPIRED		-1011
#define ERR_CA_CERT_EXPIRED		-1012
#define	ERR_INVALID_CA_CERT_SIGN	-1013
#define	ERR_INVALID_CA_SIGN		-1014
#define	ERR_INVALID_CERTIFICATE	-1015
#define ERR_CA_CERT_NOT_INSTALLED	-1016
#define	ERR_INVALID_CA_CERT		-1017

/* by cha 1999-08-10 for SEED {{ */
#define ERR_DATA_BROKEN			-1018

#define ERR_SELF_SIGNED_CERT	-1020
/* }} */

#define ERR_UNKNOWN_CIPHER		-1100
#define ERR_INVALID_CIPHER		-1101

#define ERR_SOCKET_OPEN			-1200
#define ERR_SOCKET_CONNECT		-1201
#define ERR_SOCKET_WRITE		-1202
#define ERR_SOCKET_READ			-1203
#define ERR_CRL_FILE			-1204

#define ERR_CA_MESSAGE			-1210
#define ERR_CA_REQUEST_FAILED	-1211
#define ERR_CA_REVOKE_FAILED	-1212
#define ERR_CA_RENEWAL_FAILED	-1213
#define ERR_CA_GET_FAILED		-1214
#define ERR_CA_ERROR			-1215

#define ERR_RA_KEY_INVALID		-1300
#define ERR_RA_KEY_NOT_INSTALLED	-1301
#define ERR_RA_CERT_INVALID		-1302
#define ERR_RA_CERT_NOT_INSTALLED	-1303

#define ERR_HTS_NO_CERT			-1400
#define ERR_HTS_INVALID_CERT		-1401

#define ERR_KEY_DB_CREATE_FAILED	-1501
#define ERR_KEY_DB_OPEN_FAILED		-1502
#define ERR_KEY_DB_WRITE_FAILED		-1503


#define ERR_NOT_DEF_ENV_VARIABLE    -2999
#define ERR_INVALID_INPUT			-3000
#define ERR_CERT_FILE_OPEN			-3001
#define ERR_PRIVATEKEY_FILE_OPEN	-3002
#define ERR_LIBRARY_NOT_INITIALIZED -3003
#define ERR_INVALID_PROTOCOLTYPE	-3004
/* 차정호 1999. 3. 9. 추가 */
#define ERR_PWD_NOT_SAVED			-3005

/* added for SFSP Cert Handling : hanvit extent */ 
/* by cha 1999-08-10 {{ */
#define ERR_CA_CERT_FILE_OPEN		-3006
#define ERR_CERT_FILE_TOO_BIG		-3007
#define ERR_PRIVATE_FILE_TOO_BIG	-3008
#define ERR_CA_CERT_FILE_TOO_BIG	-3009
#define ERR_NO_USE_PEER_AUETH		-3010
/* }} */

/* by cha 1999-08-10 for Message Check Sum {{ */
#define ERR_UNKNOWN_ALGORITHM		-3020
#define ERR_INVALID_PROTOCOL_STATE	-3021
/* }} */

/* by cha 1999-12-08  {{ */
#define ERR_INPUT_PEM_TOO_BIG		-3030
/* }} */

/* by dhlee 1999-12-17  {{ */
#define ERR_OUT_OF_MEMORY			-3040
/* }} */

#ifdef  __cplusplus
extern "C" {
#endif

void BNerr(int code);
void RSAerr(int code);
char * WINAPI SF_Error_Message(int err_code, char *pOutBuff);
void WINAPI SF_Debug_Log(char *lpszFmt, ...);

#ifdef  __cplusplus
}
#endif


#endif /* _SF_ERROR_H */






