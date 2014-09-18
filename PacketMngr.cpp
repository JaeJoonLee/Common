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

	//KJI 20110302 (�Ҹ���ġ ����)
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
	
	// CN �� ��� TrHeader�� Output ����Ÿ ���̿� �޼����� ���� �Ѵ�.(80 byte)
	// cTrErrorFlag ['0':����, '1':���� ==> �޼���code�� pc���� ���
	//				 '2':����, '3':���� ==> Data �κп� 80 Byte�� �޼��� ���[MSG(80 Byte) + Data]
	if (m_pCommonHeader->cServerType == '6' || m_pTrHeader->cTrErrorFlag == '2' || m_pTrHeader->cTrErrorFlag == '3')
	{
		//KJI 20110304 (��������)
		if(	nTrBodySize >= MSG_SIZE)
		{
			pBodyData = (BYTE*)lParam + HEADER_SIZE + MSG_SIZE;
			m_strMsg = CString((char*)lParam + HEADER_SIZE, MSG_SIZE);
		}
		else
			m_strMsg = "";
	}
	// �������� �޼��� ���ִ� ��� �Լ� ȣ���ؼ� ã��.
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

	// ����(1, 3)
	if (m_pTrHeader->cTrErrorFlag == '1' || m_pTrHeader->cTrErrorFlag == '3')
	{
		// 80 ����Ʈ �޼��� �ִ� ���
		if (m_pCommonHeader->cServerType == '6' || m_pTrHeader->cTrErrorFlag == '3')
			nTrBodySize -= MSG_SIZE;

		// CN Ʈ���ΰ�� 99999 �ڷᰡ �����ϴ� ������ �� 5����Ʈ(0x00 00 00 00 01)�� �ñ� CH�� ���µ�
		if (m_pCommonHeader->cServerType == '6')
		{
			if (nTrBodySize <= 5)
				nTrBodySize = 0;
		}

		m_bErr = TRUE;
	}
	// ����(0, 2)
	else
	{
		// 80 ����Ʈ �޼��� �ִ� ���
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


// ������ ���� �ϱ� ���� WM_COPYDATA �� send �Ѵ�.
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
	RqCommInfo.TrHeader.ucEncrypt	= '0';		// ��ȣȭ ����.
	RqCommInfo.TrHeader.ucPublic	= '0';		// ����Ű ��������.
	RqCommInfo.TrHeader.ucCompress	= '0';		// ���࿩��...
	RqCommInfo.TrHeader.nTimeOut	= 30;		// Ÿ�Ӿƿ�
	RqCommInfo.TrHeader.nRqID		= 0;
	RqCommInfo.cMsgId				= DM_INFO_ID;
	RqCommInfo.cFIDCommGB			= '0';		// FID ��ű���		('0':TR���,1:FID���)
	RqCommInfo.cCommandId			= cCommandId;
	RqCommInfo.hRQRPWnd				= hWnd;
	RqCommInfo.cJobChk[0]			= '0';
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	memcpy(pSendBuf, &RqCommInfo, RQ_COMMINFO_SIZE);
	if (nDataLen > 0)
		memcpy(pSendBuf + RQ_COMMINFO_SIZE, pData, nDataLen);

	COPYDATASTRUCT cds;
	cds.dwData = (DWORD)hWnd;
	cds.cbData = nSendBufSize;	// �۽� ������ ����
	cds.lpData = pSendBuf;		// �۽� ���� ������ 
	
	::SendMessage(hWnd, WM_COPYDATA,					// �޼���
			  (WPARAM)MAKELONG(0, 0),			// �۽ſ� ������(0: Rq 1:����׿�), ������ ������
			  (LPARAM)(PCOPYDATASTRUCT)&cds);	// COPYDATASTRUCT

	delete[] pSendBuf;
}
///////////////////////////////////// �ǽð� ///////////////////////////////////
int CRealPacketMngr::ParseCommData(WPARAM wParam, LPARAM lParam)
{
	CString strRealType;
	strRealType = CString((char*)lParam, REAL_TYPE_SIZE);
	m_nRealType = atoi(strRealType);

	m_pData		= (char*)lParam + REAL_TYPE_SIZE;
	m_nBodyLen	= (int)wParam - REAL_TYPE_SIZE;

	return m_nBodyLen;
}