//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : DataObList.cpp
//  Function      : Rq/Rp의 테이블을 관리한다.
//					  1. TimeOut 관리
//					  2. CommApi handle관리
//                    3. 수신 데이터 합치기(FML)
//                    4. 다운로드 파일의 Target Path 관리
//  System Name   : HwComms
//  Create        : 2003년7월16일   유 광식 (주) 한국 소리마치
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************

#include "stdafx.h"
#include "DataObList.h"
#include "CommsDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////
// CRequestDataObList
//******************************************************************
//  Function Name : CRequestDataObList
//  Function      : 생성자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CRequestDataObList::CRequestDataObList()
{
	m_hCommsDbg	= NULL;
	m_MapStringTableID.RemoveAll();

//	m_pctlLogMsg = NULL;
}

//******************************************************************
//  Function Name : ~CRequestDataObList
//  Function      : 소멸자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CRequestDataObList::~CRequestDataObList()
{
	RemoveAllData();
}


//******************************************************************
//  Function Name : RemoveAllData
//  Function      : Rq/Rp Table을 모두 삭제한다.
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CRequestDataObList::RemoveAllData()
{
	int nCount = m_MapStringTableID.GetCount();
	TRACE("\r\n [CRequestDataObList 최종 갯수] %d", nCount);
	if (nCount == 0)
		return;

	// 모든 데이타의 소멸
	CRequestData* pRequestData = NULL;

	POSITION pos;
	CString key;
    for( pos = m_MapStringTableID.GetStartPosition(); pos != NULL; )
	{
		m_MapStringTableID.GetNextAssoc( pos, key, (CObject*&)pRequestData );

		if(pRequestData->m_lpData != NULL)
		{
			// 2011/03/20 이도영(new / delete, malloc / free 정확히 쓰자)
			free(pRequestData->m_lpData);
			pRequestData->m_lpData = NULL;
		}
//		m_MapStringTableID.RemoveKey(key);
		delete pRequestData;
		pRequestData = NULL;
	}
	m_MapStringTableID.RemoveAll();

}



//******************************************************************
//  Function Name : 
//  Function      : 데이타 리스트 중 nMajorMinorID키항목의 핸들을 찾아 리턴한다.
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
HWND CRequestDataObList::GetHwnd(CString sWINIDSEQNO)
{
	if (m_MapStringTableID.GetCount() == 0)
		return FALSE;

	CRequestData* pRequestTable = NULL;

	BOOL bFound = m_MapStringTableID.Lookup(sWINIDSEQNO, (CObject*&)pRequestTable);
	if(bFound)
		return pRequestTable->m_hCommAPIWnd;
	else
		return NULL;
}

//******************************************************************
//  Function Name : AddData
//  Function      : 데이터(TimeOut정보, CommApi핸들 등)를 리스트에 추가한다.
//  Param         : CString sWINIDSEQNO, CRequestData* pRequestData
//  Return        : int 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int CRequestDataObList::AddData(CString sWINIDSEQNO, CRequestData* pRequestData)
{
	CRequestData* pOldRequestData = NULL; 
	BOOL bFound = m_MapStringTableID.Lookup(sWINIDSEQNO, (CObject*&)pOldRequestData);

	if(!bFound)	// 기존 데이터가 없는 경우에 새로 추가 한다.
	{
		m_MapStringTableID.SetAt(sWINIDSEQNO, (CObject*&)pRequestData);
	}
	else
	{
		return 0;
	}

//
//	HANDLE handle = (HANDLE)pRequestData->m_ulWinHwnd;
//
//	CString m_sWndSeqID;
//	m_sWndSeqID.Format("%08x%c", (long)handle, pRequestData->m_ulRqId);
//	
//	BOOL bFound = m_MapStringTableID.Lookup(m_sWndSeqID, (CObject*&)pOldRequestData);
//
//	if(!bFound)	// 기존 데이터가 없는 경우에 새로 추가 한다.
//	{
//		m_MapStringTableID.SetAt(m_sWndSeqID, (CObject*&)pRequestData);
//	}
//	else
//	{
//		return 0;
//	}


	return 1;
}

//******************************************************************
//  Function Name : AddData
//  Function      : 서버에서 받은 데이터를 FML처리를 한다.
//  Param         : CString sWINIDSEQNO, BYTE* lpData, int nRealLen
//					wParam : Data , lParam : Length
//  Return        : int 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int CRequestDataObList::AddData(CString sWINIDSEQNO, BYTE* lpData, int nRealLen)
{
	CRequestData* pRequestData = NULL; 
	COMMONHEADER* pCommonHeader = (COMMONHEADER*)lpData;
	// 찾아봐서 있으면
	BOOL bFound = m_MapStringTableID.Lookup(sWINIDSEQNO, (CObject*&)pRequestData);
	if (bFound)
	{
		int OldSize = pRequestData->m_nSize;
		if (OldSize == 0)	// 새로운 lpData네.. 
		{
			// 처음
			if (pCommonHeader->cCpFlag & FLAG_PACKET_BEGIN)
				pRequestData->m_bFirstPacket = TRUE;
			// 마지막
			else if (pCommonHeader->cCpFlag & FLAG_PACKET_END)
				pRequestData->m_bFirstPacket = FALSE;
			// 이상한 경우다(디버깅 해보자)
			else
			{
				pRequestData->m_bFirstPacket = FALSE;
			//	AfxMessageBox("Comms:CRequestDataObList::AddData -- 처음 Add 하는데 FLAG_PACKET_CONTINUE 가 온 경우");
			//	return 0;
			}

			pRequestData->m_nSize = nRealLen;
			pRequestData->m_lpData = (BYTE*)malloc(nRealLen);
			
			if (!pRequestData->m_lpData && nRealLen)
			{
				CString strErr;
				strErr.Format("Comms:CRequestDataObList::AddData -- PC Memory lack, Length : %d", nRealLen);
				AfxMessageBox(strErr);
				return 0;
			}
			
			memcpy(pRequestData->m_lpData, lpData, nRealLen);
			pRequestData->m_wLeftTimeOut = pRequestData->m_wOriginTimeOut;	// 타임아웃 다시 셋팅

			return pRequestData->m_nSize;
		}
		// add 가 처음이 아닌 경우
		else
		{
			int nNewSize;
			// 공통 헤더는 빼고 더한다.
			nNewSize = nRealLen - COMMON_HEADER_SIZE;
			
			// 마지막
			if (pCommonHeader->cCpFlag & FLAG_PACKET_END)
			{
			}
			// 중간
			else if (pCommonHeader->cCpFlag & FLAG_PACKET_CONTINUE)
			{
			}
			// 이상한 경우다.(디버깅 해보자)
			else
			{
				AfxMessageBox("Comms:CRequestDataObList::AddData -- 처음 Add 하는게 아닌데 FLAG_PACKET_BEGIN 가 온 경우");
				return 0;
			}

			pRequestData->m_nSize = OldSize + nNewSize;
			pRequestData->m_lpData = (BYTE*)realloc(pRequestData->m_lpData, pRequestData->m_nSize);
			if (!pRequestData->m_lpData && pRequestData->m_nSize)
			{
				CString strErr;
				strErr.Format("Comms:CRequestDataObList::AddData -- PC Memory lack, Length : %d", OldSize + nNewSize);
				AfxMessageBox(strErr);
				return 0;
			}

			// 공통헤더를 제외 하고 add 한다.
			memcpy(pRequestData->m_lpData + OldSize, lpData + COMMON_HEADER_SIZE, nNewSize);

			if (pCommonHeader->cCpFlag & FLAG_PACKET_END)
				pRequestData->m_bFirstPacket = FALSE;
			
			pRequestData->m_wLeftTimeOut = pRequestData->m_wOriginTimeOut;	// 타임아웃 다시 셋팅

			return pRequestData->m_nSize;
		}
	}

	return 0;
}

//******************************************************************
//  Function Name : ByteOrderRevLong
//  Function      : 서버의 데이터(long Type의 4Byte)를 Byte 정렬을 한다
//  Param         : LPSTR ptr
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 현재 사용 안함.	
//******************************************************************
BOOL CRequestDataObList::ByteOrderRevLong(LPSTR ptr)
{
     BYTE    ch;

     ch = *(ptr+3);
     *(ptr+3) = *ptr;
     *ptr = ch;
     ch = *(ptr+2);
     *(ptr+2) = *(ptr+1);
     *(ptr+1) = ch;
     return TRUE;
}

//******************************************************************
//  Function Name : GetByteData
//  Function      : 데이타 리스트 중 nWINIDSEQNO의 키항목의 데이터를 리턴한다 
//  Param         : (CString sWINIDSEQNO
//  Return        : BYTE
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BYTE* CRequestDataObList::GetByteData(CString sWINIDSEQNO)
{
	CRequestData* pRequestData = NULL;

	BOOL bFound = m_MapStringTableID.Lookup(sWINIDSEQNO, (CObject*&)pRequestData);
	if(bFound)
		return pRequestData->m_lpData;			// 데이터
	else
		return NULL;
}


//******************************************************************
//  Function Name : GetSize
//  Function      : 리스트 중 nMajorMinorID의 키항목의 데이터 크기를 얻는다.
//  Param         : CString sWINIDSEQNO
//  Return        : int 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int CRequestDataObList::GetSize(CString sWINIDSEQNO)
{
	CRequestData* pRequestData = NULL;

	BOOL bFound = m_MapStringTableID.Lookup(sWINIDSEQNO, (CObject*&)pRequestData);
	if(bFound)
		return pRequestData->m_nSize;			// 데이타 크기. 
	else
		return 0;
}

//******************************************************************
//  Function Name : GetData
//  Function      : nMajorMinorID키의  Rq테이블 정보를 읽는다.	
//  Param         : CString sWINIDSEQNO
//  Return        : CRequestData*
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 사용안함	
//******************************************************************
CRequestData* CRequestDataObList::GetData(CString sWINIDSEQNO)
{
	CRequestData* pRequestData = NULL;

	BOOL bFound = m_MapStringTableID.Lookup(sWINIDSEQNO, (CObject*&)pRequestData);
	return pRequestData; // 없으면 Null이겠져.. 
}

//******************************************************************
//  Function Name : RemoveData
//  Function      : nMajorMinorID키의  Rq테이블 정보를 제거한다.	
//  Param         : CString sWINIDSEQNO
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CRequestDataObList::RemoveData(CString sWINIDSEQNO)
{
	if (m_MapStringTableID.GetCount() == 0)
		return FALSE;

	CRequestData* pRequestData = NULL;

	BOOL bFound = m_MapStringTableID.Lookup(sWINIDSEQNO, (CObject*&)pRequestData);
	if(bFound)
	{
		m_MapStringTableID.RemoveKey(sWINIDSEQNO);

		if(pRequestData->m_lpData != NULL)
		{
			// 2011/03/20 이도영(new / delete, malloc / free 정확히 쓰자)
			free(pRequestData->m_lpData);
			pRequestData->m_lpData = NULL;
		}

		delete pRequestData;
		pRequestData = NULL;

		

		////////////////////////////////////////////////
		/*
		CString sLog;
		sLog.Format("remove WINIDSEQNO = %s", sWINIDSEQNO);
		int nLogSize = strlen( sLog );
		BYTE* lpLog = new BYTE[nLogSize+1];
		if( !lpLog )
		{
			CString strErr;
			strErr.Format("Comms:CommsDbgLog -- PC Memory lack, Length : %d", nLogSize+1);
			return FALSE;
		}

		memset(lpLog, 0x0, nLogSize+1 );
		memcpy(lpLog, sLog, nLogSize );
		
		COPYDATASTRUCT copyData;
		copyData.dwData = 0x01;
		copyData.cbData = nLogSize;
		copyData.lpData = lpLog;

		if (::IsWindow(m_hCommsDbg))
		{
			::SendMessage(m_hCommsDbg, WM_COPYDATA, nLogSize, (LPARAM)&copyData);
		}

		delete[] lpLog;
		*/
		///////////////////////////////////////

		return TRUE;
	}
	return FALSE;
}

//******************************************************************
//  Function Name : RemoveRpData
//  Function      : nMajorMinorID키의  데이터를 지운다.	
//  Param         : CString sWINIDSEQNO
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CRequestDataObList::RemoveRpData(CString sWINIDSEQNO)
{
	if (m_MapStringTableID.GetCount() == 0)
		return FALSE;

	CRequestData* pRequestData = NULL;

	BOOL bFound = m_MapStringTableID.Lookup(sWINIDSEQNO, (CObject*&)pRequestData);
	if(bFound)
	{
		if(pRequestData->m_lpData != NULL)
		{
			// 2011/03/20 이도영(new / delete, malloc / free 정확히 쓰자)
			free(pRequestData->m_lpData);
			pRequestData->m_lpData = NULL;
		}

		pRequestData->m_nSize = 0;
		pRequestData->m_wLeftTimeOut = 100;

		return TRUE;
	}
	return FALSE;
}
//******************************************************************
//  Function Name : DecreaseTimer
//  Function      : 타임아웃을 알린다.
//					RQ타임아웃을 위해 1초마다 RQ의 타임아웃값을 하나씩 줄인다.	 */ 
//  Param         : HWND hWnd, BOOL bSendToCommAPI
//					bSendToCommAPI이 TRUE이면 모든 RQ리스트가 전부 타임아웃처리됨
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 호 출 함 수 : CMainFrame::OnTimer()	
//******************************************************************
BOOL CRequestDataObList::DecreaseTimer(HWND hWnd, BOOL bSendToCommAPI)
{
	BOOL bIsExistTimeOut = FALSE;

	if (m_MapStringTableID.GetCount() == 0)
		return FALSE;

	CString strTemp;

	POSITION pos;
	CString sKey;

    for (pos = m_MapStringTableID.GetStartPosition(); pos != NULL;)
	{
		// 모든 데이타의 소멸
		CRequestData* pRequestData = NULL;
		m_MapStringTableID.GetNextAssoc(pos, sKey, (CObject*&)pRequestData);
		if (pRequestData == NULL)
			continue;
	
		pRequestData->m_wLeftTimeOut--;

		///////////////////////////////////////////////////////
		// Timeout처리를 한다.
		if (pRequestData->m_wLeftTimeOut <= 0 || bSendToCommAPI)
		{
			m_sect.Lock();

			bIsExistTimeOut = TRUE;
			if (IsWindow(pRequestData->m_hCommAPIWnd)) 	// 윈도우일 때만 값을 보낸다..
			{
				if (pRequestData->m_hCommAPIWnd == hWnd)
				{
					// 서버 접속 끊김.
					int lRet = ::SendMessage((HWND)pRequestData->m_hCommAPIWnd, UM_DISCONNECT, 0, (LPARAM)0);
				}
				else
				{
					if (pRequestData->m_lpData != NULL)
					{
						// 2011/03/20 이도영(new / delete, malloc / free 정확히 쓰자)
						free(pRequestData->m_lpData);
						pRequestData->m_lpData = NULL;
					}
					
					// Timeout임을 알린다.
					CString		strTimeout;
					strTimeout = "TimeOut입니다.";
					
					int nSendLen = HEADER_SIZE + MSG_SIZE;
					BYTE* lpData = new BYTE[nSendLen];
					memset(lpData, ' ', nSendLen);
					//////////////////// Common Header ////////////////////
					// 서버에서 pCommonHeader->ulRqId 값을 다른 용도로 사용하고 있어서
					// pCommonHeader->ulWinHwnd에 pRequestData->m_ulRqId를 넣는다.
					COMMONHEADER CommonHeader;
					CommonHeader.ulPacketLen	= htonl(nSendLen - SIZE_DEF_PACKET);
					CommonHeader.ulRqId			= pRequestData->m_ulRqId;
					CommonHeader.cCpFlag		= 0x03;
					CommonHeader.cCommandId		= PID_TRDATA;
					CommonHeader.cErrComm		= '1';
					CommonHeader.cServerType	= '0';
					CommonHeader.ulWinHwnd		= pRequestData->m_ulRqId;
					memcpy(lpData, &CommonHeader, COMMON_HEADER_SIZE);
					// Tr Header
					TRHEADER TrHeader;
					memcpy(TrHeader.cTRCode, pRequestData->m_ucTrCode, TRCODE_SIZE);
					TrHeader.cBenefit			= 'N';
					TrHeader.cNextPrev			= '0';
					TrHeader.cTrErrorFlag		= '3';	// 3으로 해야 에러 메세지가 있는 유형이다.
					memcpy(TrHeader.cErrCode, "00000", ERRCODE_SIZE);
					TrHeader.ulTrBodySize		= 0;
					memcpy(lpData + COMMON_HEADER_SIZE, &TrHeader, TR_HEADER_SIZE);
					// 메세지(80 byte)
					memcpy(lpData + HEADER_SIZE, strTimeout, strTimeout.GetLength());
					// 받은 자료를 해당 window 에 전송한다.
					COPYDATASTRUCT    send_data;
					send_data.dwData	= DATAKIND_RQRP;	// RP용 
					send_data.cbData	= nSendLen;			// 보낼 사이즈
					send_data.lpData	= lpData;			// 보낼 버퍼

					::SendMessage((HWND)pRequestData->m_hCommAPIWnd, 
								WM_COPYDATA, 
								DATAKIND_RQRP,
								(LPARAM)&send_data);

					delete[] lpData;
				}
				// 데이터를 보내고 테이블에서 지운다.
				RemoveData(sKey);

			}
			m_sect.Unlock();
		}
	}

	return bIsExistTimeOut;
}

//******************************************************************
//  Function Name : GetFileName
//  Function      : nMajorMinorID키의 다운로드 파일을 찾아 리턴한다.
//  Param         : CString sWINIDSEQNO
//  Return        : CString 
//  Create        : 
//  Update        : 김정문, 2009/09/24 VS 2008 Upgrade를 위한 작업
//  Comment       : 다운로드 파일의 Target Path를 얻는데 사용한다.		
//******************************************************************
CString CRequestDataObList::GetFileName(CString sWINIDSEQNO)
{
	if (m_MapStringTableID.GetCount() == 0)
		return _T("");

	CRequestData* pRequestTable = NULL;

	BOOL bFound = m_MapStringTableID.Lookup(sWINIDSEQNO, (CObject*&)pRequestTable);
	if(bFound)
		return pRequestTable->m_strCurFileName;
	else
		return _T("");
}
