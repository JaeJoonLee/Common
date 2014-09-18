#ifndef _SF_X509_H
#define _SF_X509_H

#include "SF-ASNtypes.h"
#include "SF-RSA.h"

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
    Version
************************************************/
typedef ASN_INTEGER Version;

Version * WINAPI SF_Read_BIN_To_Version(BIN *bin);

void WINAPI	SF_Free_Version(Version *version);

BIN * WINAPI SF_DER_Encode_Version(Version *version);


/************************************************
    CertificateSerialNumber
************************************************/
typedef ASN_INTEGER CertificateSerialNumber;

CertificateSerialNumber * WINAPI
SF_Read_BIN_To_CertificateSerialNumber(BIN *bin);

void WINAPI	SF_Free_CertificateSerialNumber(CertificateSerialNumber *certificateSerialNumber);

BIN * WINAPI SF_DER_Encode_CertificateSerialNumber(CertificateSerialNumber *certificateSerialNumber);


/************************************************
    Validity
************************************************/
typedef struct _Validity {
    ASN_TIME    *notBefore;
    ASN_TIME    *notAfter;
} Validity;

Validity * WINAPI SF_Read_BIN_To_Validity(BIN *bin);

void WINAPI SF_Free_Validity(Validity *validity);

BIN * WINAPI SF_DER_Encode_Validity(Validity *validity);


AttributeTypeAndValue * WINAPI SF_Read_BIN_To_AttributeTypeAndValue(BIN *bin);

void WINAPI SF_Free_AttributeTypeAndValue(AttributeTypeAndValue *attributeTypeAndValue);

BIN * WINAPI SF_DER_Encode_AttributeTypeAndValue(AttributeTypeAndValue *attributeTypeAndValue);


/************************************************
    RelativeDistinguishedName
************************************************/
/* typedef struct _RelativeDistinguishedName {
	AttributeTypeAndValue	*attributeTypeAndValue;
} RelativeDistinguishedName;
*/
RelativeDistinguishedName * WINAPI SF_Read_BIN_To_RelativeDistinguishedName(BIN *bin);

void WINAPI SF_Free_RelativeDistinguishedName(RelativeDistinguishedName *relativeDistinguishedName);

BIN * WINAPI SF_DER_Encode_RelativeDistinguishedName(RelativeDistinguishedName *relativeDistinguishedName);


/************************************************
    RDNSequence
************************************************/
/* typedef struct _RDNSequence {
	RelativeDistinguishedName	*rdn;
	struct _RDNSequence         *next;
} RDNSequence;
*/
RDNSequence * WINAPI SF_Read_BIN_To_RDNSequence(BIN *bin);

void WINAPI SF_Free_RDNSequence(RDNSequence *rdnSequence);

BIN * WINAPI SF_DER_Encode_RDNSequence(RDNSequence *rdnSequence);


/************************************************
    Name
************************************************/
/* typedef struct _Name {
	RDNSequence *rdnSequence;
} Name;
	
*/Name * WINAPI SF_Read_BIN_To_Name(BIN *bin);

void WINAPI	SF_Free_Name(Name *name);

BIN * WINAPI SF_DER_Encode_Name(Name *name);


/************************************************
    SubjectPublicKeyInfo
************************************************/
/* typedef struct _SubjectPublicKeyInfo {
    AlgorithmIdentifier *algorithm;
    BIT_STRING          *subjectPublicKey;
} SubjectPublicKeyInfo;
*/
SubjectPublicKeyInfo * WINAPI
SF_Read_BIN_To_SubjectPublicKeyInfo(BIN *bin);

void WINAPI	SF_Free_SubjectPublicKeyInfo(SubjectPublicKeyInfo *subjectPublicKeyInfo);

BIN * WINAPI SF_DER_Encode_SubjectPublicKeyInfo(SubjectPublicKeyInfo *SubjectPublicKeyInfo);


/************************************************
    TBSCertificate
************************************************/
typedef struct _TBSCertificate {
    Version					*version;
    CertificateSerialNumber *serialNumber;
    AlgorithmIdentifier     *signature;
    Name                    *issuer;
    Validity                *validity;
    Name                    *subject;
    SubjectPublicKeyInfo    *subjectPublicKeyInfo;
    UniqueIdentifier        *issuerUniqueID;     /* optional, v2 or v3 */
    UniqueIdentifier        *subjectUniqueID;    /* optional, v2 or v3 */
    Extensions              *extensions;         /* optional, v3 */
} TBSCertificate;

TBSCertificate * WINAPI SF_Read_BIN_To_TBSCertificate(BIN *bin);

void WINAPI SF_Free_TBSCertificate(TBSCertificate *tbsCertificate);

BIN * WINAPI SF_DER_Encode_TBSCertificate(TBSCertificate *tbsCertificate);


 
/***********************************************
    CertificationRequestInfo
**********************************************/
typedef struct _CertificationRequestInfo {
    Version					*version;
    Name                    *subject;
    SubjectPublicKeyInfo    *subjectPublicKeyInfo;
    Attributes				*attributes;
} CertificationRequestInfo;

CertificationRequestInfo * WINAPI SF_Read_BIN_To_CertificationRequestInfo(BIN *bin);

void WINAPI SF_Free_CertificationRequestInfo(CertificationRequestInfo *certificationRequestInfo);

BIN * WINAPI SF_DER_Encode_CertificationRequestInfo(CertificationRequestInfo *certificationRequestInfo);

/***********************************************
    PKCS10CertificateRequest
***********************************************/
typedef struct _PKCS10CertificationRequest {
    CertificationRequestInfo	*certificationRequestInfo;
    AlgorithmIdentifier			*signatureAlgorithm;
    BIT_STRING					*signature;
} PKCS10CertificationRequest;

PKCS10CertificationRequest * WINAPI SF_Read_BIN_To_PKCS10CertificationRequest(BIN *bin);

void WINAPI SF_Free_PKCS10CertificationRequest(PKCS10CertificationRequest *pkcs10CertificationRequest);

BIN * WINAPI SF_DER_Encode_PKCS10CertificationRequest(PKCS10CertificationRequest *pkcs10CertificationRequest);

BIN * WINAPI SFRA_New_DER_Encoded_PKCS10CertificationRequest(RSAPrivateKey *rsa,
												char *pem, 
												char *nation, 
												char *state, 
												char *addr,
												char *organ,
												char *ounit,
												char *name, 
												char *email,
												char *id
												);



/************************************************
    X509Certificate
************************************************/       
typedef struct _X509Certificate {
    TBSCertificate      *tbsCertificate;
    AlgorithmIdentifier *signatureAlgorithm;
    BIT_STRING          *signature;
	BIN					*binFingerPrint;
} X509Certificate;

X509Certificate * WINAPI SF_Read_BIN_To_X509Certificate(BIN *bin);

X509Certificate * WINAPI SF_Read_PEM_To_X509Certificate(char *pem);

void WINAPI SF_Free_X509Certificate(X509Certificate *x509Certificate);

BIN * WINAPI SF_DER_Encode_X509Certificate(X509Certificate *x509Certificate);

void WINAPI	SF_Print_X509Certificate(X509Certificate *x509Certificate, int tab_width);

char * WINAPI SF_Get_Certificate_Serial_Number(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Subject(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Subject_Email(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Subject_ID(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Subject_Name(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Issuer(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Issuer_Name(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Valid_From(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Valid_To(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Validity(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Finger_Print(X509Certificate *x509Certificate);

char * WINAPI SF_Get_Certificate_Extension(X509Certificate *x509Certificate);

int WINAPI SF_Check_Expired(X509Certificate *x509Certificate);

int WINAPI SF_Check_Sign(X509Certificate *x509Certificate, RSAPublicKey *rsa);

#ifdef  __cplusplus
}
#endif

#endif /* _SF_X509_H */





