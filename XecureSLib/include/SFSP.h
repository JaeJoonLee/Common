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

/* {{ by ����ȣ 1998.11.24 */
#define SFSP_PWD_PROTOCOL			1
#define SFSP_CLIENT_SIGN_PROTOCOL	2
/* }} */

/* {{ by ����ȣ 1999-08-10 */
#define RC4_128_MD5		1
#define RC4_128_SHA		2
#define RC5_128_MD5		3
#define RC5_128_SHA		4
#define SEED_128_HAS	5
/* }} by ����ȣ 1999-08-10 */

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

/* {{ by ����ȣ 1999-11-10 */
#define CTX_TAG_RESERVERD  ("XCR_CTX")
/* }} by ����ȣ 1999-11-10 */

typedef struct {
	char tag[8];
	int					nAuth;
	char				bIC;
/* {{ by ����ȣ 1999-11-10 : �뵵 ���� */	
	/* char				*sStatus; */
	int				sStatus;
/* }} by ����ȣ 1999-11-10 */
	char				*sSID;
	char				*sUID;
	char				*sPwd;
	CIPHER_SPEC			*spec;
	RSAPrivateKey		*rsa;
	X509Certificate		*cert;
	char				*pem;
} XECURE_CTX;


/* -------------------------------------------------------------------------
   �Լ��̸�	: SFSP_FilePath_Set
   ����	    : SFSP_Lib_Initialize()  �Լ� ȣ������ 
			  ȯ�溯���� �ʿ��� ������ ��ġ�� �����Ѵ�. 
			  ���� ȯ�溯���� �̹� �����Ǿ� �ִٸ� ȣ���� �ʿ䰡 ����. 
   ���ϰ�	: int WINAPI 
   �Է�		: char *cert - ���� ������ ������ �н� 
   �Է�		: char *pri - ����Ű ������ �н� 
   �Է�		: char *pcacert - CA ������ ������ �н� 
			  (��Ģ) NULL : �ش� ������ ��� ���� ���� 
					 �׿� -  ������ �н�
------------------------------------------------------------------------- */
XECURE_API int WINAPI SFSP_FilePath_Set(const char *cert, const char *pri, const char *pcacert);

/* -------------------------------------------------------------------------
   �Լ��̸�	: SFSP_Lib_Initialize
   ����	    : Xecure Library�� �ʱ�ȭ �Ѵ�. 
			 �� �Լ��� ���� �����忡�� ���ο� ������ ���� �������� ȣ���ϸ� 
			 ���̺귯���� �ʱ�ȭ�� �̷������ �Լ� ȣ�� �� ������ �����忡�� 
			 ���̺귯�� �ʱ�ȭ ������ �ݿ��ȴ�.    
   �Է�		: 
		XECURE_USE_NO_CERT 
			- XecureNet R Client ȣȯ ��� �ʱ�ȭ 
				�̰�� �� �Լ��� ȣ������ �ʾƵ� �� 
		XECURE_USE_CERT_PRIVATE	
			- ����Ű, ������, CA ������ ��� ���� �ʱ�ȭ 
		XECURE_USE_ONLY_CACAERT	
			- CA ���������� ����ϴ� ���� �ʱ�ȭ 
				���� ������ �߰� ���� ��� (XecureNet S���� �߰�) 	
  ���ϰ�	: int  
				ERR_CA_CERT_FILE_OPEN - CA ������ ���� �б� ���� 
				ERR_CERT_FILE_OPEN - ���� ������ ���� �б� ���� 
				ERR_PRIVATEKEY_FILE_OPEN - ����Ű ���� �б� ���� 
				ERR_CA_CERT_FILE_TOO_BIG - CA ������ ���� ũ�Ⱑ 4k ���� ŭ  
				ERR_CERT_FILE_TOO_BIG - ���� ������ ���� ũ�Ⱑ 4k ���� ŭ  
				ERR_PRIVATE_FILE_TOO_BIG - ����Ű ���� ũ�Ⱑ 4k ���� ŭ  
				ERR_NOT_DEF_ENV_VARIABLE - ȯ�溯���� �����Ǿ� ���� ���� 
					����)
						"SFSP_PRIVATE_FILEPATH"
						"SFSP_CERT_FILEPATH"
						"SFSP_CA_CERT_FILEPATH"
------------------------------------------------------------------------- */
XECURE_API int WINAPI SFSP_Lib_Initialize(int UseOption);

/* -------------------------------------------------------------------------
   �Լ��̸�	: SFSP_Lib_Initialize_With_Data
   ����	    : Xecure Library�� �ʱ�ȭ �Ѵ�. 
			 �� �Լ��� ��������� ����Ű ������ �޸𸮿� ������ ���� �� ȣ���ϴ� �Լ� 
			 ���� �����忡�� ���ο� ������ ���� �������� ȣ���ϸ� 
			 ���̺귯���� �ʱ�ȭ�� �̷������ �Լ� ȣ�� �� ������ �����忡�� 
			 ���̺귯�� �ʱ�ȭ ������ �ݿ��ȴ�.    
   �Է�		: cert - ���������� pem �������� ������ 
   �Է�		: pri - ����Ű pem �������� ������ 
   �Է�		: pcacert - CA ������ pem �������� ������ 
			(����) �� �Է¿� NULL ���� ������ ������ ������ �ʴ� �����ͷ� ���� 
		
		XECURE_USE_NO_CERT 
			- XecureNet R Client ȣȯ ��� �ʱ�ȭ 
				�̰�� �� �Լ��� ȣ������ �ʾƵ� �� 
		XECURE_USE_CERT_PRIVATE	
			- ����Ű, ������, CA ������ ��� ���� �ʱ�ȭ 
			--> �� �Է� pem �����͸� ��� �Է��ؾ� ���� ��  
		XECURE_USE_ONLY_CACAERT	
			- CA ���������� ����ϴ� ���� �ʱ�ȭ 
				���� ������ �߰� ���� ��� (XecureNet S���� �߰�) 	
			--> cert, pri �� NULL �Է� , pcacert�� CA �������� pem ������ ������ �Է�  
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



