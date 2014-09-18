#pragma once

#include "CommHeaderDef.h"
#include "CommstructDef.h"

#if !defined(_WIN32_WCE)
	#pragma pack(push, 1)
#endif

// outrec 정보
typedef struct OUTREC_INFO
{
	OUTREC_INFO()
	{
		m_pData		= NULL;
		m_nRowLen	= 0;
		m_nRowCount = 0;
	}

	char*	m_pData;
	int		m_nRowLen;
	int		m_nRowCount;
} OutRecInfo;

#if !defined(_WIN32_WCE)
	#pragma pack(pop)
#endif


typedef LPCTSTR (*DLL_GETERRORCODE)(LPCTSTR szCode);
class CPacketMngr
{
public:
	CPacketMngr(void);
	~CPacketMngr(void);

public:
	BOOL		m_bFid;
	int			m_nRqId;
	BYTE		m_cCommandId;
	BYTE		m_cServerType;
	CString		m_strTrCode;
		
	BOOL		m_bErr;
	CString		m_strErrCode;
	CString		m_strMsg;
		
	COMMONHEADER*	m_pCommonHeader;
	TRHEADER*		m_pTrHeader;

	CPtrArray		m_arrOutRecInfo;
	DLL_GETERRORCODE	m_pDll_GetErrorCode;
public:
	void		Clear();
	// 서버로 부터 받은 데이터 처리
	int			ParseCommData(WPARAM wParam, LPARAM lParam);

	OutRecInfo*	GetOutRecInfo(int nIndex);
	char*		GetOutRecData(int nIndex);

	int			GetPacketUniqueID(WPARAM wParam, LPARAM lParam);
	
	void		SendCopyData(HWND hWnd, BYTE cCommandId, BYTE* pData, int nDataLen);
};

class CRealPacketMngr
{
public:
	CRealPacketMngr(void);
	~CRealPacketMngr(void);

public:
	int		m_nRealType;
	int		m_nBodyLen;
	char*	m_pData;
public:
	// 서버로 부터 받은 데이터 처리
	int			ParseCommData(WPARAM wParam, LPARAM lParam);
};