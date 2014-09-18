//
//	xmdevice.h
//		standard library for multiple devices
//		definition for device dependent functions
//
#ifndef	__XM_DEVICE_H__
#define __XM_DEVICE_H__

//	Device List
//	WIN32
//	WINCE
//	BREW
//	_DTWM		Intec device
//	PALM
//	HPLJ
//	DOS
//	POS_ARM		T-FINCE device (Hanaro - ARM)
//	MOBICOS		T-FINCE device (Mobicos - Mitsubishi)
//	CYBERNET	T-FINCE device (Cybernet - Hitachi)
//	WITHUS		T-FINCE device (Withus- Toshiba)
//	LINUX

//#define NO_GLOBAL
#define NO_INT64
#define USE_MALLOC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// string
#define		MEMSET		memset
#define		MEMCPY		memcpy
#define		MEMMOVE		memcpy
#define		MEMCMP		memcmp

#define		STRCPY		strcpy
#define		STRCAT		strcat

// memory
#define		MALLOC		malloc
#define		FREE		free
#define ENABLE_FILE

#define far
#if defined (WIN32) | defined (LINUX)
//#define ENABLE_RSA_PRI
#endif


#endif
