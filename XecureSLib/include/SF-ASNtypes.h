/************************************
  REVISION LOG ENTRY
  Revision By: 차정호
  Revised on 98-11-25 오후 3:29:14
  Comments: 
 ************************************/

/********************************************************************
    SF-ASNtypes.h -- ASN PRIMITIVE data type definition
                 programmed by Jae-Hak Jung
                 1998/06/25
                 Copyright (c) 1998 SoftForum, All rights reserved.
********************************************************************/

#ifndef _SF_ASNTYPES_H
#define _SF_ASNTYPES_H

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

#include <stdio.h>
#include "SF-Base64.h"
#include "ThreadSafe.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define UCHAR unsigned char 

/************************************************
    BIN typedefinition 
************************************************/
typedef struct _BIN {
    int     length;
    UCHAR   *value;
} BIN;

BIN * WINAPI SF_New_BIN(int len, UCHAR *data);

BIN * WINAPI SF_Read_BIN_To_BIN(BIN *bin);

BIN * WINAPI SF_Read_PEM_To_BIN(char *pem);

void WINAPI	SF_Free_BIN(BIN * bin);

BIN * WINAPI SF_DER_Encode_BIN(char tag, BIN *block);

BIN * WINAPI SF_Merge_BIN(BIN *bin1, BIN *bin2);

void WINAPI SF_Print_BIN(BIN *bin);

int WINAPI SF_Write_BIN_To_PEM_File(char *header, BIN *bin, FILE *fp);

int WINAPI SF_Write_BIN_To_PEM_String(char *header, BIN *bin, char *str);


/************************************************
    BIT_STRING
************************************************/
typedef BIN BIT_STRING;

BIT_STRING * WINAPI SF_Read_BIN_To_BIT_STRING(BIN *bin);

void WINAPI	SF_Free_BIT_STRING(BIT_STRING *bit_STRING);

BIN * WINAPI SF_DER_Encode_BIT_STRING(BIT_STRING *bit_STRING);

char * WINAPI SF_Read_BIN_To_String(BIN *bin, char	out[4096]);


/************************************************
    ASN_ASN_INTEGER
************************************************/
/* typedef BIN ASN_INTEGER;

ASN_INTEGER * WINAPI SF_Read_BIN_To_ASN_INTEGER(BIN *bin);

void WINAPI SF_Free_ASN_INTEGER(ASN_INTEGER *integer);

BIN * WINAPI SF_DER_Encode_ASN_INTEGER(ASN_INTEGER *integer);
*/

/************************************************
    ASN_INTEGER
************************************************/
typedef BIN ASN_INTEGER;

ASN_INTEGER * WINAPI SF_Read_BIN_To_ASN_INTEGER(BIN *bin);

void WINAPI SF_Free_ASN_INTEGER(ASN_INTEGER *integer);

BIN * WINAPI SF_DER_Encode_ASN_INTEGER(ASN_INTEGER *integer);

/************************************************
    OBJECT_IDENTIFIER   // temporary...
************************************************/
typedef BIN OBJECT_IDENTIFIER;

OBJECT_IDENTIFIER * WINAPI SF_Read_BIN_To_OBJECT_IDENTIFIER(BIN *bin);

void WINAPI SF_Free_OBJECT_IDENTIFIER(OBJECT_IDENTIFIER *object_IDENTIFIER);

BIN * WINAPI SF_DER_Encode_OBJECT_IDENTIFIER(OBJECT_IDENTIFIER *object_IDENTIFIER);


/************************************************
    ASN_ANY             // temporary...
************************************************/
typedef BIN ASN_ANY;

ASN_ANY * WINAPI SF_Read_BIN_To_ASN_ANY(BIN *bin);

void WINAPI SF_Free_ASN_ANY(ASN_ANY *asn_ANY);

BIN * WINAPI SF_DER_Encode_ASN_ANY(ASN_ANY *asn_ANY);


/************************************************
    ASN_TIME                // temporary...
************************************************/
typedef BIN ASN_TIME;

ASN_TIME * WINAPI SF_Read_BIN_To_ASN_TIME(BIN *bin);

void WINAPI SF_Free_ASN_TIME(ASN_TIME *time);

BIN * WINAPI SF_DER_Encode_ASN_TIME(ASN_TIME *time);


/************************************************
    AlgorithmIdentifier
************************************************/
typedef struct _AlgorithmIdentifier {
    OBJECT_IDENTIFIER   *algorithm;
    ASN_ANY             *parameters;
} AlgorithmIdentifier;

AlgorithmIdentifier * WINAPI SF_Read_BIN_To_AlgorithmIdentifier(BIN *bin);

void WINAPI	SF_Free_AlgorithmIdentifier(AlgorithmIdentifier *algorithmIdentifier);

BIN * WINAPI SF_DER_Encode_AlgorithmIdentifier(AlgorithmIdentifier *algorithmIdentifier);



/************************************************
    Attributes          // temporary...
************************************************/
typedef BIN	Attributes;

Attributes * WINAPI SF_Read_BIN_To_Attributes(BIN *bin);

void WINAPI	SF_Free_Attributes(Attributes *attributes);

BIN * WINAPI SF_DER_Encode_Attributes(Attributes *attributes);




/************************************************
    AttributeType
************************************************/
typedef OBJECT_IDENTIFIER	AttributeType;

AttributeType * WINAPI
SF_Read_BIN_To_AttributeType(BIN *bin);

void WINAPI
SF_Free_AttributeType(AttributeType *attributeType);

BIN * WINAPI
SF_DER_Encode_AttributeType(AttributeType *attributeType);


/************************************************
    AttributeValue
************************************************/
typedef ASN_ANY				AttributeValue;

AttributeValue * WINAPI
SF_Read_BIN_To_AttributeValue(BIN *bin);

void WINAPI
SF_Free_AttributeValue(AttributeValue *attributeValue);

BIN * WINAPI
SF_DER_Encode_AttributeValue(AttributeValue *attributeValue);

/************************************************
    AttributeTypeAndValue
************************************************/
typedef struct _AttributeTypeAndValue {
	AttributeType	*type;
	AttributeValue	*value;
} AttributeTypeAndValue;

AttributeTypeAndValue * WINAPI
SF_Read_BIN_To_AttributeTypeAndValue(BIN *bin);

void WINAPI
SF_Free_AttributeTypeAndValue(AttributeTypeAndValue *attributeTypeAndValue);

BIN * WINAPI
SF_DER_Encode_AttributeTypeAndValue(AttributeTypeAndValue *attributeTypeAndValue);



/************************************************
    RelativeDistinguishedName
************************************************/
typedef struct _RelativeDistinguishedName {
	AttributeTypeAndValue	*attributeTypeAndValue;
} RelativeDistinguishedName;

RelativeDistinguishedName * WINAPI
SF_Read_BIN_To_RelativeDistinguishedName(BIN *bin);

void WINAPI
SF_Free_RelativeDistinguishedName(RelativeDistinguishedName *relativeDistinguishedName);

BIN * WINAPI
SF_DER_Encode_RelativeDistinguishedName(RelativeDistinguishedName *relativeDistinguishedName);


/************************************************
    RDNSequence
************************************************/
typedef struct _RDNSequence {
	RelativeDistinguishedName	*rdn;
	struct _RDNSequence         *next;
} RDNSequence;

RDNSequence * WINAPI
SF_Read_BIN_To_RDNSequence(BIN *bin);

void WINAPI
SF_Free_RDNSequence(RDNSequence *rdnSequence);

BIN * WINAPI
SF_DER_Encode_RDNSequence(RDNSequence *rdnSequence);



/************************************************
    Name
************************************************/
typedef struct _Name {
	BIN			*bin;
	RDNSequence *rdnSequence;
} Name;
	
Name * WINAPI
SF_Read_BIN_To_Name(BIN *bin);

void WINAPI
SF_Free_Name(Name *name);

BIN * WINAPI
SF_DER_Encode_Name(Name *name);


/************************************************
    SubjectPublicKeyInfo
************************************************/
typedef struct _SubjectPublicKeyInfo {
	BIN					*bin;
    AlgorithmIdentifier *algorithm;
    BIT_STRING          *subjectPublicKey;
} SubjectPublicKeyInfo;

SubjectPublicKeyInfo * WINAPI
SF_Read_BIN_To_SubjectPublicKeyInfo(BIN *bin);

void WINAPI
SF_Free_SubjectPublicKeyInfo(SubjectPublicKeyInfo *subjectPublicKeyInfo);

BIN * WINAPI
SF_DER_Encode_SubjectPublicKeyInfo(SubjectPublicKeyInfo *SubjectPublicKeyInfo);


/************************************************
    UniqueIdentifier
************************************************/
typedef BIT_STRING  UniqueIdentifier;

UniqueIdentifier * WINAPI
SF_Read_BIN_To_UniqueIdentifier(BIN *bin);

void WINAPI
SF_Free_UniqueIdentifier(UniqueIdentifier *uniqueIdentifier);

BIN * WINAPI
SF_DER_Encode_UniqueIdentifier(UniqueIdentifier *uniqueIdentifier);


/************************************************
    Extensions          // temporary...
************************************************/
typedef BIN	Extensions;

Extensions * WINAPI
SF_Read_BIN_To_Extensions(BIN *bin);

void WINAPI
SF_Free_Extensions(Extensions *extensions);

BIN * WINAPI
SF_DER_Encode_Extensions(Extensions *extensions);

#ifdef  __cplusplus
}
#endif

#endif /* _SF_ASNTYPES_H */






