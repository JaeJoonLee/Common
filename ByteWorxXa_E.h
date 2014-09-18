#pragma once

#ifdef __BYTEWORXXA_DLL__
	#ifdef _BUILD
		#define BYTEWORXXA_EXT_API		__declspec(dllexport)
		#define BYTEWORXXA_EXT_CLASS	__declspec(dllexport)
		#define BYTEWORXXA_EXT_DATA		__declspec(dllexport)
	#else // !_BUILD
		#define BYTEWORXXA_EXT_API		__declspec(dllimport)
		#define BYTEWORXXA_EXT_CLASS	__declspec(dllimport)
		#define BYTEWORXXA_EXT_DATA		__declspec(dllimport)
	#endif // !_BUILD
#else // Static Library
	#ifdef _BUILD
		#define BYTEWORXXA_EXT_API
		#define BYTEWORXXA_EXT_CLASS
		#define BYTEWORXXA_EXT_DATA
	#else // !_BUILD
		#define BYTEWORXXA_EXT_API
		#define BYTEWORXXA_EXT_CLASS
		#define BYTEWORXXA_EXT_DATA
	#endif // !_BUILD
#endif // Static Library

extern "C"
{
	int		BYTEWORXXA_EXT_API BwxXaEncode_M2M(/*[in]*/void* pInBuf, /*[in]*/UINT iInSize, /*[out]*/void* pOutBuf, /*[in,out]*/UINT* piOutSize);
	int		BYTEWORXXA_EXT_API BwxXaEncode_M2M_with_Msg(/*[in]*/void* pInBuf, /*[in]*/UINT iInSize, /*[out]*/void* pOutBuf, /*[in,out]*/UINT* piOutSize, HWND hProgWnd, UINT iProgMsgId);
	int		BYTEWORXXA_EXT_API BwxXaEncode_F2F(/*[in]*/int iFlag, /*[in]*/LPCTSTR pSourcePath, /*[in]*/LPCTSTR pTargetPath);
	int		BYTEWORXXA_EXT_API BwxXaDecodedSize_M2M(/*[in]*/void* pInBuf, /*[in]*/UINT iInSize, /*[out]*/UINT* piOutSize);
	int		BYTEWORXXA_EXT_API BwxXaDecode_M2M(/*[in]*/void* pInBuf, /*[in]*/UINT iInSize, /*[out]*/void* pOutBuf, /*[in,out]*/UINT* piOutSize);
	int		BYTEWORXXA_EXT_API BwxXaDecode_F2F(/*[in]*/LPCTSTR pSourcePath, /*[in]*/LPCTSTR pTargetPath);
	BOOL	BYTEWORXXA_EXT_API BwxMd(LPCSTR szPathName);
	BOOL	BYTEWORXXA_EXT_API BwxRd(LPCSTR szPathName);
	int		BYTEWORXXA_EXT_API BwxCalculateCRC32(void* pData, int iLen);
	int		BYTEWORXXA_EXT_API BwxCp(LPCSTR szSource, LPCSTR szTarget);
	int		BYTEWORXXA_EXT_API BwxEds(LPSTR szPath);
}
