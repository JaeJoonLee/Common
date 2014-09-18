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


// Request, Reply ����Ÿ�� Ŭ��������
class CRequestData : public CObject
{
public:
	ULONG	m_ulWinHwnd;					// ������ �ڵ��ε� �ٸ� �뵵�� ����� ���� �����Ͽ� ULONG�� �����.
	ULONG	m_ulRqId;						// SEQNO(MinorID)
    HWND    m_hCommAPIWnd;                  // CommApi window handle
    WORD    m_wOriginTimeOut;				// Origin TimeOut
    WORD    m_wLeftTimeOut;                 // ���� TimeOut
	CString	m_strCurFileName;				// �ٿ�ε��� ���ϸ�(ǥ�ÿ�)
	BYTE	m_ucTrCode[TRCODE_SIZE + 1];	// ���񽺸�(TR Code)
	int		m_nSize;						// Buf Size
	BYTE*	m_lpData;						// Data Receive Buf
	BOOL	m_bFirstPacket;					// ���� ����Ÿ�ΰ�� ù��° ��Ŷ���� üũ��
};

// Request, Reply ����Ʈ�� Ŭ���� ����
class CRequestDataObList// : public CObList
{
private:
	char m_nWINHWND[n_WINHWND+n_WINDOWID+1];
	CMapStringToOb		m_MapStringTableID;		// Request ID ����.
	CCriticalSection	m_sect;					// Lock unlockó��
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
