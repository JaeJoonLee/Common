#ifndef _SFSP_H
#define _SFSP_H

#include "SF-RSAUtil.h"
#include "SF-X509.h"
#include "SF-Cert.h"
#include "debug.h"

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

#define XECURE_USE_NO_CERT					0
#define XECURE_USE_CERT_PRIVATE				1
#define XECURE_USE_ONLY_CACAERT				2
#define XECURE_USE_FULL_CERTS				3


#define SFSP_PRIVATE_FILEPATH	"SFSP_PRIVATE_FILEPATH"
#define SFSP_CERT_FILEPATH		"SFSP_CERT_FILEPATH"
#define SFSP_CA_CERT_FILEPATH	"SFSP_CA_CERT_FILEPATH"

#define SFSP_TYPE_PWD 1

/* {{ by 차정호 1998.11.24 */
#define SFSP_PWD_PROTOCOL			1
#define SFSP_CLIENT_SIGN_PROTOCOL	2
/* }} */

/* {{ by 차정호 1999-08-10 */
#define RC4_128_MD5		1
#define RC4_128_SHA		2
#define RC5_128_MD5		3
#define RC5_128_SHA		4
#define SEED_128_HAS	5
/* }} by 차정호 1999-08-10 */

#define CLIENT_HELLO_STATE					10 
#define	CLIENT_HELLO_RE_STATE				11
#define	CLIENT_ID_STATE						12 
#define CLIENT_ID_RE_STATE					13	 
#define CLIENT_PWD_STATE					14           
#define CLIENT_PWD_RE_STATE					15        
#define CLIENT_SIGN_RES_STATE				16      
#define SERVER_HELLO_STATE					21 
#define	SERVER_ID_STATE						22
#define	SERVER_PROTOCOL_TYPE_STATE			23 
#define	SERVER_AUTH_STATE					24 
#define	SERVER_AUTH_PROTOCOL_TYPE_STATE		25           
#define	SERVER_SIGN_RES_STATE				26        
#define SECURE_COMM_STATE					100

typedef struct {
	int	spec_enum;
	int	key_len;
	unsigned char key[64];
} CIPHER_SPEC;

/* {{ by 차정호 1999-11-10 */
#define CTX_TAG_RESERVERD  ("XCR_CTX")
/* }} by 차정호 1999-11-10 */

typedef struct {
	char tag[8];
	int					nAuth;
	char				bIC;
/* {{ by 차정호 1999-11-10 : 용도 수정 */	
	/* char				*sStatus; */
	int				sStatus;
/* }} by 차정호 1999-11-10 */
	char				*sSID;
	char				*sUID;
	char				*sPwd;
	CIPHER_SPEC			*spec;
	RSAPrivateKey		*rsa;
	X509Certificate		*cert;
	char				*pem;
} XECURE_CTX;


/* -------------------------------------------------------------------------
   함수이름	: SFSP_FilePath_Set
   설명	    : SFSP_Lib_Initialize()  함수 호출전에 
			  환경변수에 필요한 파일의 위치를 지정한다. 
			  만먁 환경변수가 이미 설정되어 있다면 호출할 필요가 없다. 
   리턴값	: int WINAPI 
   입력		: char *cert - 개인 인증서 파일의 패스 
   입력		: char *pri - 개인키 파일의 패스 
   입력		: char *pcacert - CA 인증서 파일의 패스 
			  (규칙) NULL : 해당 파일을 사용 하지 않음 
					 그외 -  파일의 패스
------------------------------------------------------------------------- */
XECURE_API int WINAPI SFSP_FilePath_Set(const char *cert, const char *pri, const char *pcacert);

/* -------------------------------------------------------------------------
   함수이름	: SFSP_Lib_Initialize
   설명	    : Xecure Library를 초기화 한다. 
			 이 함수는 메인 스레드에서 새로운 스레드 등이 생성전에 호출하면 
			 라이브러리의 초기화가 이루어지고 함수 호출 후 생성된 스레드에도 
			 라이브러리 초기화 설정이 반영된다.    
   입력		: 
		XECURE_USE_NO_CERT 
			- XecureNet R Client 호환 모드 초기화 
				이경우 이 함수를 호출하지 않아도 됨 
		XECURE_USE_CERT_PRIVATE	
			- 개인키, 인증서, CA 인증서 사용 모드로 초기화 
		XECURE_USE_ONLY_CACAERT	
			- CA 인증서만을 사용하는 모드로 초기화 
				서버 인증서 추가 검증 모드 (XecureNet S에서 추가) 	
  리턴값	: int  
				ERR_CA_CERT_FILE_OPEN - CA 인증서 파일 읽기 오류 
				ERR_CERT_FILE_OPEN - 개인 인증서 파일 읽기 오류 
				ERR_PRIVATEKEY_FILE_OPEN - 개인키 파일 읽기 오류 
				ERR_CA_CERT_FILE_TOO_BIG - CA 인증서 파일 크기가 4k 보다 큼  
				ERR_CERT_FILE_TOO_BIG - 개인 인증서 파일 크기가 4k 보다 큼  
				ERR_PRIVATE_FILE_TOO_BIG - 개인키 파일 크기가 4k 보다 큼  
				ERR_NOT_DEF_ENV_VARIABLE - 환경변수가 설덩되어 있지 않음 
					참조)
						"SFSP_PRIVATE_FILEPATH"
						"SFSP_CERT_FILEPATH"
						"SFSP_CA_CERT_FILEPATH"
------------------------------------------------------------------------- */
XECURE_API int WINAPI SFSP_Lib_Initialize(int UseOption);

/* -------------------------------------------------------------------------
   함수이름	: SFSP_Lib_Initialize_With_Data
   설명	    : Xecure Library를 초기화 한다. 
			 이 함수는 인증서들과 개인키 내용을 메모리에 가지고 있을 때 호출하는 함수 
			 메인 스레드에서 새로운 스레드 등이 생성전에 호출하면 
			 라이브러리의 초기화가 이루어지고 함수 호출 후 생성된 스레드에도 
			 라이브러리 초기화 설정이 반영된다.    
   입력		: cert - 개인인증서 pem 데이터의 포인터 
   입력		: pri - 개인키 pem 데이터의 포인터 
   입력		: pcacert - CA 인증서 pem 데이터의 포인터 
			(참고) 각 입력에 NULL 값을 넣으면 설정을 위하지 않는 데이터로 간주 
		
		XECURE_USE_NO_CERT 
			- XecureNet R Client 호환 모드 초기화 
				이경우 이 함수를 호출하지 않아도 됨 
		XECURE_USE_CERT_PRIVATE	
			- 개인키, 인증서, CA 인증서 사용 모드로 초기화 
			--> 세 입력 pem 포인터를 모두 입력해야 설정 됨  
		XECURE_USE_ONLY_CACAERT	
			- CA 인증서만을 사용하는 모드로 초기화 
				서버 인증서 추가 검증 모드 (XecureNet S에서 추가) 	
			--> cert, pri 는 NULL 입력 , pcacert는 CA 인증서의 pem 데이터 포인터 입력  
  ----------------------------------------------------------------------- */
XECURE_API int WINAPI SFSP_Lib_Initialize_With_Data(int UseOption, const char *cert, const char *pri, const char *pcacert);

XECURE_API  XECURE_CTX * WINAPI SF_New_Xecure_Ctx();
XECURE_API  void WINAPI SF_Free_Xecure_Ctx(XECURE_CTX *ctx);
/* XECURE_API  CERTINFO * WINAPI SF_Read_CERTINFO(char *cert); */
int GetDataLength(unsigned char *pDataLen);

#ifdef  __cplusplus
}
#endif


#endif /* _SFSP_H */



