#include "stdafx.h"
#include "PacketMngr.h"

CPacketMngr::CPacketMngr(void)
{
	m_bFid				= FALSE;
	m_nRqId				= 0;
	m_cCommandId		= '0';
	m_bErr				= FALSE;
	m_pCommonHeader		= NULL;
	m_pTrHeader			= NULL;
	m_pDll_GetErrorCode = NULL;
}

CPacketMngr::~CPacketMngr(void)
{
	Clear();
}

void CPacketMngr::Clear()
{
	m_bErr = FALSE;
	m_strMsg.Empty();
	m_strErrCode.Empty();

	for (int i = 0; i < m_arrOutRecInfo.GetSize(); i++)
	{
		OutRecInfo* pOutRecInfo = (OutRecInfo*)m_arrOutRecInfo.GetAt(i);
		
		if (pOutRecInfo->m_pData != NULL)
			delete[] pOutRecInfo->m_pData;
		
		if (pOutRecInfo != NULL)
			delete pOutRecInfo;
	}
	m_arrOutRecInfo.RemoveAll();
}

int CPacketMngr::ParseCommData(WPARAM wParam, LPARAM lParam)
{
	int nPacketSize;
	int nTrBodySize;
	int nRowLen = 0;
	int nRecLen	= 0;
	
	BYTE *pBodyData;
	
	Clear();
	
	m_pCommonHeader		= (COMMONHEADER*)lParam;
	m_pTrHeader			= (TRHEADER*)((BYTE*)lParam + COMMON_HEADER_SIZE);
	nPacketSize			= ntohl(m_pCommonHeader->ulPacketLen);

	if( nPacketSize < (COMMON_HEADER_SIZE + TR_HEADER_SIZE - SIZE_DEF_PACKET))
		return 0;

	m_nRqId				= m_pCommonHeader->ulRqId;
	m_cCommandId		= m_pCommonHeader->cCommandId;
	m_strTrCode			= CString((char*)m_pTrHeader->cTRCode, sizeof(m_pTrHeader->cTRCode));
	m_strTrCode.TrimRight();
	m_cServerType		= m_pCommonHeader->cServerType;
	m_strErrCode		= CString((char*)m_pTrHeader->cErrCode, sizeof(m_pTrHeader->cErrCode));
	m_strErrCode.TrimRight();
	nTrBodySize			= ntohl(m_pTrHeader->ulTrBodySize);

	//KJI 20110302 (소리마치 수정)
	if(	nPacketSize < nTrBodySize)
	{
		CString strIniFile;
		char lpszModulePath[MAX_PATH];

		char szPath[MAX_PATH]= { 0 };
		GetModuleFileName(AfxGetInstanceHandle(),szPath ,MAX_PATH);

		DWORD dwLen = GetLongPathName ( szPath, lpszModulePath, MAX_PATH);
		*strrchr(lpszModulePath,'\\') = '\0';

		strIniFile.Format("%s\\User\\LastDumpLog.ini", lpszModulePath);
		WritePrivateProfileString("CommError", "TRCode", m_strTrCode, strIniFile);
		return 0;
	}
	
	// CN 인 경우 TrHeader와 Output 데이타 사이에 메세지가 존재 한다.(80 byte)
	// cTrErrorFlag ['0':정상, '1':에러 ==> 메세지code로 pc에서 출력
	//				 '2':정상, '3':에러 ==> Data 부분에 80 Byte의 메세지 출력[MSG(80 Byte) + Data]
	if (m_pCommonHeader->cServerType == '6' || m_pTrHeader->cTrErrorFlag == '2' || m_pTrHeader->cTrErrorFlag == '3')
	{
		//KJI 20110304 (오류수정)
		if(	nTrBodySize >= MSG_SIZE)
		{
			pBodyData = (BYTE*)lParam + HEADER_SIZE + MSG_SIZE;
			m_strMsg = CString((char*)lParam + HEADER_SIZE, MSG_SIZE);
		}
		else
			m_strMsg = "";
	}
	// 서버에서 메세지 안주는 경우 함수 호출해서 찾자.
	else
	{
		pBodyData = (BYTE*)lParam + HEADER_SIZE;

		if (m_pDll_GetErrorCode)
        {
            if (m_strErrCode.GetLength() == 0)
				m_strErrCode = "0";
            m_strMsg = m_pDll_GetErrorCode(m_strErrCode);
        }
	}

	m_strMsg.Trim();

	// 에러(1, 3)
	if (m_pTrHeader->cTrErrorFlag == '1' || m_pTrHeader->cTrErrorFlag == '3')
	{
		// 80 바이트 메세지 있는 경우
		if (m_pCommonHeader->cServerType == '6' || m_pTrHeader->cTrErrorFlag == '3')
			nTrBodySize -= MSG_SIZE;

		// CN 트랜인경우 99999 자료가 없습니다 에러에 왜 5바이트(0x00 00 00 00 01)이 올까 CH는 없는데
		if (m_pCommonHeader->cServerType == '6')
		{
			if (nTrBodySize <= 5)
				nTrBodySize = 0;
		}

		m_bErr = TRUE;
	}
	// 정상(0, 2)
	else
	{
		// 80 바이트 메세지 있는 경우
		if (m_pCommonHeader->cServerType == '6' || m_pTrHeader->cTrErrorFlag == '2')
			nTrBodySize -= MSG_SIZE;
	}

	if (nTrBodySize > 0)
	{
		OUTREC_INFO* pOutRecInfo = new OUTREC_INFO;
		
		pOutRecInfo->m_pData		= new char[nTrBodySize];
		memcpy(pOutRecInfo->m_pData, (char*)pBodyData, nTrBodySize);
		pOutRecInfo->m_nRowLen		= nTrBodySize;
		pOutRecInfo->m_nRowCount	= 1;
		m_arrOutRecInfo.Add(pOutRecInfo);
	}
	
	return nTrBodySize;
}

OutRecInfo* CPacketMngr::GetOutRecInfo(int nIndex)
{
	if (nIndex >= m_arrOutRecInfo.GetSize() || m_arrOutRecInfo.GetSize() <= 0)
		return NULL;

	OutRecInfo* pOutRecInfo = (OutRecInfo*)m_arrOutRecInfo.GetAt(nIndex);
	return pOutRecInfo;
}

char* CPacketMngr::GetOutRecData(int nIndex)
{
	if (nIndex >= m_arrOutRecInfo.GetSize() || m_arrOutRecInfo.GetSize() <= 0)
		return NULL;

	OutRecInfo* pOutRecInfo = (OutRecInfo*)m_arrOutRecInfo.GetAt(nIndex);
	return pOutRecInfo->m_pData;
}

int CPacketMngr::GetPacketUniqueID(WPARAM wParam, LPARAM lParam)
{
	int nPacketUniqueID;
	COMMONHEADER* pCommonHeader = (COMMONHEADER*)lParam;
	nPacketUniqueID			= pCommonHeader->ulRqId;

	return nPacketUniqueID;
}


// 서버에 전송 하기 위해 WM_COPYDATA 를 send 한다.
void CPacketMngr::SendCopyData(HWND hWnd, BYTE cCommandId, BYTE* pData, int nDataLen)
{
	BYTE* pSendBuf;
	int nSendBufSize;

	nSendBufSize = RQ_COMMINFO_SIZE;
	if (nDataLen > 0)
		nSendBufSize += nDataLen;

	pSendBuf = new BYTE[nSendBufSize];
	
	REQUEST_COMMINFO RqCommInfo;
	memset(&RqCommInfo, 0x0, RQ_COMMINFO_SIZE);
	RqCommInfo.TrHeader.ucEncrypt	= '0';		// 암호화 여부.
	RqCommInfo.TrHeader.ucPublic	= '0';		// 공개키 인증여부.
	RqCommInfo.TrHeader.ucCompress	= '0';		// 압축여부...
	RqCommInfo.TrHeader.nTimeOut	= 30;		// 타임아웃
	RqCommInfo.TrHeader.nRqID		= 0;
	RqCommInfo.cMsgId				= DM_INFO_ID;
	RqCommInfo.cFIDCommGB			= '0';		// FID 통신구분		('0':TR통신,1:FID통신)
	RqCommInfo.cCommandId			= cCommandId;
	RqCommInfo.hRQRPWnd				= hWnd;
	RqCommInfo.cJobChk[0]			= '0';
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	memcpy(pSendBuf, &RqCommInfo, RQ_COMMINFO_SIZE);
	if (nDataLen > 0)
		memcpy(pSendBuf + RQ_COMMINFO_SIZE, pData, nDataLen);

	COPYDATASTRUCT cds;
	cds.dwData = (DWORD)hWnd;
	cds.cbData = nSendBufSize;	// 송신 데이터 길이
	cds.lpData = pSendBuf;		// 송신 실제 데이터 
	
	::SendMessage(hWnd, WM_COPYDATA,					// 메세지
			  (WPARAM)MAKELONG(0, 0),			// 송신용 구분자(0: Rq 1:디버그용), 데이터 구분자
			  (LPARAM)(PCOPYDATASTRUCT)&cds);	// COPYDATASTRUCT

	delete[] pSendBuf;
}
///////////////////////////////////// 실시간 ///////////////////////////////////
int CRealPacketMngr::ParseCommData(WPARAM wParam, LPARAM lParam)
{
	CString strRealType;
	strRealType = CString((char*)lParam, REAL_TYPE_SIZE);
	m_nRealType = atoi(strRealType);

	m_pData		= (char*)lParam + REAL_TYPE_SIZE;
	m_nBodyLen	= (int)wParam - REAL_TYPE_SIZE;

	return m_nBodyLen;
}