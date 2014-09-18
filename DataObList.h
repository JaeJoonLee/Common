// DataObList.h

#ifndef _DATAOBLIST_H
#define _DATAOBLIST_H

#if !defined(_WIN32_WCE)
#include <afxmt.h>
#include <process.h>
#else
#include <wceimpl.h>
#include <Afxmt.h>
#endif


#define	n_WINHWND	8
#define	n_WINDOWID	1


// Request, Reply 데이타의 클래스정의
class CRequestData : public CObject
{
public:
	ULONG	m_ulWinHwnd;					// 윈도우 핸들인데 다른 용도로 사용할 것을 감안하여 ULONG로 잡았음.
	ULONG	m_ulRqId;						// SEQNO(MinorID)
    HWND    m_hCommAPIWnd;                  // CommApi window handle
    WORD    m_wOriginTimeOut;				// Origin TimeOut
    WORD    m_wLeftTimeOut;                 // 남은 TimeOut
	CString	m_strCurFileName;				// 다운로드할 파일명(표시용)
	BYTE	m_ucTrCode[TRCODE_SIZE + 1];	// 서비스명(TR Code)
	int		m_nSize;						// Buf Size
	BYTE*	m_lpData;						// Data Receive Buf
	BOOL	m_bFirstPacket;					// 연속 데이타인경우 첫번째 패킷인지 체크용
};

// Request, Reply 리스트의 클래스 정의
class CRequestDataObList// : public CObList
{
private:
	char m_nWINHWND[n_WINHWND+n_WINDOWID+1];
	CMapStringToOb		m_MapStringTableID;		// Request ID 관리.
	CCriticalSection	m_sect;					// Lock unlock처리
public:
	HWND	m_hCommsDbg;
	CRequestDataObList();
	virtual ~CRequestDataObList();

	int GetTblCount(){return m_MapStringTableID.GetCount();}

	HWND GetHwnd(CString sWINIDSEQNO);
	int AddData(CString sWINIDSEQNO, CRequestData* pRequestData);
	int AddData(CString sWINIDSEQNO, BYTE *lpData,int RealLen);
	BYTE* GetByteData(CString sWINIDSEQNO);
	int GetSize(CString sWINIDSEQNO);
	CRequestData* GetData(CString sWINIDSEQNO);
	BOOL RemoveData(CString sWINIDSEQNO);
	BOOL RemoveRpData(CString sWINIDSEQNO);
	void RemoveAllData();
	BOOL DecreaseTimer(HWND hWnd, BOOL bSendToCommAPI=FALSE);
	CString GetFileName(CString sWINIDSEQNO);
	BOOL ByteOrderRevLong(LPSTR ptr);	
};

#endif
