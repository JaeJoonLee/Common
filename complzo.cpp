//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : complzo.cpp
//  Function      : 
//  System Name   : HwComms
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
#include "stdafx.h"
#include "minilzo/minilzo.h"

#if defined(__LZO_STRICT_16BIT)
#define IN_LEN      (8*1024)
#else
#define IN_LEN      (128*1024L)
#endif
#define OUT_LEN     (IN_LEN + IN_LEN / 64 + 16 + 3)

//static lzo_byte in  [ IN_LEN ];

/* Work-memory needed for compression. Allocate memory in units
 * of `lzo_align_t' (instead of `char') to make sure it is properly aligned.
  */

#define HEAP_ALLOC(var,size) \
  lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

//static HEAP_ALLOC(wrkmem,LZO1X_1_MEM_COMPRESS);

//******************************************************************
//  Function Name : InitialLZO
//  Function      : 
//  Param         : 없음
//  Return        : int 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int InitialLZO()
{
	if (lzo_init() != LZO_E_OK)
	{
		//("lzo_init() failed !!!\n");
		return 0;
	}
	return 1;
}

//******************************************************************
//  Function Name : CompressLZO
//  Function      : 
//  Param         : unsigned char *src, unsigned char *tar, int slen
//  Return        : int 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int CompressLZO(unsigned char *src, unsigned char *tar, int slen)
{
	lzo_uint new_len;
	HEAP_ALLOC(wrkmem,LZO1X_1_MEM_COMPRESS);
	int	err;

    err = lzo1x_1_compress((lzo_byte *)src,slen,(lzo_byte *)tar,&new_len,wrkmem);
    if (err == LZO_E_OK)
	{
        return new_len;
	}
	return 0;
}
    
//******************************************************************
//  Function Name : DecompressLZO
//  Function      : 
//  Param         : unsigned char *src, unsigned char *tar, int slen
//  Return        : int 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int DecompressLZO(unsigned char *src, unsigned char *tar, int slen)
{
	lzo_uint new_len;
	int	err;
	
	err = lzo1x_decompress((lzo_byte *)src, slen, (lzo_byte *)tar, &new_len, NULL);
    if(err == LZO_E_OK)
    {
        return (int)new_len;
    }
	return 0;
}
