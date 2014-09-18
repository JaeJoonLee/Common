#ifndef _SF_PKS7_H
#define _SF_PKS7_H

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


#include "SF-ASNtypes.h"

#ifdef  __cplusplus
extern "C" {
#endif


typedef OBJECT_IDENTIFIER	ContentType;


/************************************************
    PKCS7Message
************************************************/
typedef struct _PKCS7ContentInfo {
    ContentType	*contentType;
    void		*content;
} PKCS7ContentInfo;

/************************************************
    PKCS7Data
************************************************/
typedef BIT_STRING	PKCS7Data;

/************************************************
    DigestAlgorithmIdentifier
************************************************/
typedef AlgorithmIdentifier	DigestAlgorithmIdentifier;

/************************************************
    DigestAlgorithmIdentifiers
************************************************/
typedef struct _DigestAlgorithmIdentifiers {
	DigestAlgorithmIdentifier			*digestAlgorithmIdentifier;
	struct _DigestAlgorithmIdentifiers	*next;
} DigestAlgorithmIdentifiers;

/************************************************
    ExtendedCertificateOrCertificate
************************************************/
typedef struct _ExtendedCertificateOrCertificate {
	X509Certificate			*x509Certificate;
/*	ExtendedCertificate		*extendedCertificate; */
} ExtendedCertificateOrCertificate;

/************************************************
    ExtendedCertificateAndCertificates
************************************************/
typedef struct _ExtendedCertificateAndCertificates {
	ExtendedCertificateOrCertificate			*extendedCertificateOrCertificate;
	struct _ExtendedCertificateAndCertificates	*next;
} ExtendedCertificateAndCertificates;

/************************************************
    CertificateRevocationList
typedef struct _CertificateRevocationList {
	Version								*version;
} CertificateRevocationList;
************************************************/
typedef BIT_STRING	CertificateRevocationList;

/************************************************
    CertificateRevocationLists
************************************************/
typedef struct _CertificateRevocationLists {
	CertificateRevocationList			*crl;
	struct _CertificateRevocationLists	*next;
} CertificateRevocationLists;

/************************************************
    IssuerAndSerialNumber
************************************************/
typedef struct _IssuerAndSerialNumber {
	Name					*issuer;
	CertificateSerialNumber	*serialNumber;
} IssuerAndSerialNumber;

/************************************************
    DigestEncryptionAlgorithmIdentifier
************************************************/
typedef AlgorithmIdentifier	DigestEncryptionAlgorithmIdentifier;

/************************************************
    EncryptedDigest
************************************************/
typedef BIT_STRING	EncryptedDigest;

/************************************************
    SignerInfo
************************************************/
typedef struct _SignerInfo {
	Version								*version;
	IssuerAndSerialNumber				*issuerAndSerialNumber;
	DigestAlgorithmIdentifier			*digestAlgorithm;
	Attributes							*authenticatedAttributes;
	DigestEncryptionAlgorithmIdentifier	*digestEncryptionAlgorithm;
	EncryptedDigest						*encryptedDigest;
	Attributes							*unauthenticatedAttributes;
} SignerInfo;

/************************************************
    SignerInfos
************************************************/
typedef struct _SignerInfos {
	SignerInfo			*signerInfo;
	struct _SignerInfos	*next;
} SignerInfos;

/************************************************
    PKCS7SignedData
************************************************/
typedef struct _PKCS7SignedData {
	Version								*version;
	DigestAlgorithmIdentifiers			*digestAlgorithms;
    PKCS7ContentInfo					*contentInfo;
	ExtendedCertificateAndCertificates	*certificates;
	CertificateRevocationLists			*crls;
    SignerInfos							*signerInfos;
} PKCS7SignedData;



#ifdef  __cplusplus
}
#endif

#endif /* __SF_PKS7_H */





