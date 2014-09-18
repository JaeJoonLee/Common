#ifndef _SF_TYPES_H_
#define _SF_TYPES_H_

#ifdef  __cplusplus
extern "C" {
#endif

/********************* Type Definitions **********************/

#ifndef TYPE_DEFINITION
#define TYPE_DEFINITION
#if defined(__alpha)
typedef unsigned int        DWORD;
typedef unsigned short      WORD;
#else
typedef unsigned long int   DWORD;
typedef unsigned short int  WORD;
#endif
typedef unsigned char           BYTE;
#endif

#ifdef  __cplusplus
}
#endif

#endif







