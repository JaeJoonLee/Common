#ifndef _SF_TAGFILE_H
#define _SF_TAGFILE_H


#ifdef __cplusplus
extern "C" {
#endif


typedef struct _tag_node {
    unsigned short	tag;
	unsigned char	flag;
    unsigned short	size;
    char    *value;
    struct _tag_node    *next;
    struct _tag_node    *sub;
} TAG_NODE;

char *get_tag_value(TAG_NODE *tag_node, short tag, short *size);
short get_tag_value_size(TAG_NODE *tag_node, short tag);
TAG_NODE *new_tag(short tag, char *value, short size);
int insert_tag(TAG_NODE *root, short tag, TAG_NODE *node);
int free_tag(TAG_NODE *tag_node);
TAG_NODE *build_tag(char *value, short size);
int print_tag(TAG_NODE *node, int level); 


#define TAG_INVALID             0
#define TAG_CERTIFICATE_REQUEST 1
#define TAG_CERTIFICATE         2
#define TAG_RSA_PRIVATE_KEY     3

#define TAG_PRIVATE_N           11
#define TAG_PRIVATE_E           12
#define TAG_PRIVATE_D           13
#define TAG_PRIVATE_P           14
#define TAG_PRIVATE_Q           15
#define TAG_PRIVATE_DMP1        16
#define TAG_PRIVATE_DMQ1        17
#define TAG_PRIVATE_IQMP        18

#define TAG_DATA                21
#define TAG_VERSION             22
#define TAG_VERSION_CERTIFICATE 23
#define TAG_VERSION_SFCA_KEY    24
#define TAG_SITE_INFO           25
#define TAG_SITE_INFO_ID_STR    26
#define TAG_SITE_INFO_EMAIL     27
#define TAG_VALIDITY            28
#define TAG_VALIDITY_NOT_BEFORE 29
#define TAG_VALIDITY_NOT_AFTER  30
#define TAG_PUBLIC_KEY          31
#define TAG_PUBLIC_KEY_ALGORITHM    32
#define TAG_PUBLIC_KEY_MODULUS  33
#define TAG_PUBLIC_KEY_EXPONENT 34

#define TAG_SIGNATURE           41
#define TAG_SIGNATURE_ALGORITHM 42
#define TAG_SIGNATURE_VALUE     43




#ifdef __cplusplus
}
#endif

#endif /* _SF_TAGFILE_H */






