#if !defined(AFX_HANARO_INTERFACE_H__320E_1464_BY_JUNOK_LEE_98B1A__INCLUDED_)
#define AFX_HANARO_INTERFACE_H__320E_1464_BY_JUNOK_LEE_98B1A__INCLUDED_

#include <afxtempl.h>

// #include "../../_Include/IBaseDefine.h"
// ������  : ���ؿ� 2005.11.02(��)
// History : 2005.11.02 �������̽� �� �޽��� ����
//
//---------------------------------------------------------
// VARIANT������ �Ʒ��� ������.
//_________________________________________________________

// �������̽� UUID_ ����
#define		UUID_IGateManager					0
#define		UUID_IPCTRManager					1
#define		UUID_IAUTrCommManager				2
#define		UUID_IAUGDIManager					4
#define		UUID_IMasterDataManager				5
#define		UUID_IAUBGManager					7
#define		UUID_IOrderMonitorManager			8
#define		UUID_IAUGwanManager					9
#define		UUID_ISignalManager					10
#define		UUID_IAUOrderManager				11
#define		UUID_IDebugManager					14
#define		UUID_IAccountManager				15
#define		UUID_IAccountManager2				15
#define		UUID_IRegistryManager				17
#define		UUID_IAUDrdsManager					19
#define		UUID_IMainInfoManager				21
#define		UUID_IMainInfoManager0002           21
#define		UUID_IMainExInfoManager				22
#define		UUID_IMainExInfoManager2			22
#define		UUID_IEncryptionManager				23
#define		UUID_IDataUtilManager				24
#define		UUID_IAUPCOrderManager				25
#define		UUID_IExtCodeWndManager				27
#define		UUID_IAUDataMonitorManager			28
#define		UUID_IClipboardManager				29
#define		UUID_IAUFormOpenDispManager			30
#define		UUID_IAUFormDataDispManager			31
#define		UUID_IAUDeskDispManager				32
#define		UUID_IAUMainDispManager				33
#define		UUID_IAUFrameDispManager			34
#define		UUID_IAUViewDispManager				35
#define		UUID_IAUPrimLibDispManager			36
#define		UUID_IAUPrimScrDispManager			37
#define		UUID_IRunStateManager				38
#define		UUID_IControlPosManager				39
// #define		UUID_INewsSignalManager			45	//

#define		UUID_IKSLibManager					50	// �ѱ��Ҹ���ġ(KS) ���̺귯�� �������̽�
#define		UUID_IPacketConvertManager			51

#define		MAX_INTERFACE						71
#define		MAX_IMainExInfoManager				41

//	HTS Mode
#define		HTSMODE_HTS						0
#define		HTSMODE_FOPRO					1

typedef struct
{
	int  nID;			// ������ ����ID
	CString szData;		// �����Ͱ�
} STPCTR_SETDATA;


typedef struct 
{
	int  nID;			// ������ ����ID
	char sTR[5];		// TR��ȣ
	long dwKey;			// �����Ű��. ���Ϲ��� �� �״�� �Ѱ���.
	int  nInputSize;	// TR InputData size
	char aInputData[1];	// TR InputData
} STPCTR_GETDATAEX;
#define	SZ_STPCTR_GETDATAEX 		sizeof(STPCTR_GETDATAEX)

#define ZERO_STPCTR_GETDATAEX(st)	memset(&st, 0, SZ_STPCTR_GETDATAEX);


// STPCTR_SETEXDATA �� ����ü�� ���Ǻ��� ����. �÷���(DLL)���� ���
typedef struct
{
	int  nID;					// ������ ����ID
	COleVariant varData;		// �����Ͱ�
} STPCTR_SETEXDATA;



#define BEGIN_HANARO_INTERFACE_PART(localClass, baseClass) \
	class X##localClass : public baseClass \
	{ \
	public: 

#define END_HANARO_INTERFACE_PART(localClass) \
	} m_x##localClass; \
	friend class X##localClass; 

DECLARE_INTERFACE(IBaseDataDB)
{
	// szKey�� �־��� ������ ���� ���Ѵ�.
	// I-PARAM : dwKey(Ű��)
	//           vData(���Ϲ��� VARIANTŸ��)
	// O-PARAM : �ش�Ű���� �ش��ϴ� ������ ������
	STDMETHOD_(COleVariant*, GetData)(LPCSTR szKey) PURE;

	// szKey�� �־��� ������ ���� ���Ѵ�.
	// I-PARAM : dwKey(Ű), dwData(���ο� ��)
	// O-PARAM : ��������. TRUE(����)/FALSE
	STDMETHOD_(BOOL, SetData)(LPCSTR szKey, const COleVariant* pvData) PURE;

	// dwKey�� �־��� ������ ���� ���Ѵ�.
	// I-PARAM : dwKey(Ű��)
	//           vData(���Ϲ��� VARIANTŸ��)
	// O-PARAM : �ش�Ű���� �ش��ϴ� ������ ������
	STDMETHOD_(COleVariant*, GetData)(int dwKey) PURE;

	// dwKey�� �־��� ������ ���� ���Ѵ�.
	// I-PARAM : dwKey(Ű), dwData(���ο� ��)
	// O-PARAM : ��������. TRUE(����)/FALSE
	STDMETHOD_(BOOL, SetData)(int dwKey, const COleVariant* pvData) PURE;
};


// vData->vt = VT_BSTR
// VARIANT var;		AfxVariantInit(&var);
// vData->bstrVal = szTmp.AllocSysString();

DECLARE_INTERFACE(IBaseDataString)
{
	// dwKey�� �־��� ������ ���� ���Ѵ�.
	// I-PARAM : szKey(Ű��)
	// O-PARAM : �ش�Ű���� �ش��ϴ� ������
	STDMETHOD_(LPCSTR, GetDataString)(int nKey) PURE;

	// dwKey�� �־��� ������ ���� ���Ѵ�.
	// I-PARAM : szKey(Ű), szData(���ο� ��)
	// O-PARAM : ��������Ÿ
	//           (�������̽����� ���������Ͱ� �ƴ� ���� �����Ƿ� �������̽� ��� �� ����)
	STDMETHOD_(BOOL   , SetDataString)(int nKey, LPCSTR szData) PURE;
};


interface ISumInterface
{
	STDMETHOD_(void*, GetInterface)(int nID) PURE;
	STDMETHOD_(BOOL,  SetInterface)(int nID, void* dwValue) PURE;
};

DECLARE_INTERFACE(IDataCallback)
{
	LONG  m_dwVersion;
	LONG  m_dwKey[2];		// For Future.
	STDMETHOD_(HRESULT, ReceiveData)(long dwKey, LONG pData, long dwDataLen) PURE;
};

// �������̽� ����Ʈ ���ϱ�
/* -----------------------------------------------------------
	WPARAM wp;  //STMSG_INTERFACE* ����ü
	LPARAM lp;  //������.
	Return-Value : //����� �ǹ̾���
 
 	int nID = 22;

	wp = (WPARAM)nID;
 	IMainInfoManager* pMainInfoMng = (IMainInfoManager*)AfxGetMainWnd()->SendMessage(wp, lp);

	if(pMainInfoMng!=NULL)
	{
		// Do-Yourself....
	}
----------------------------------------------------------- */
const UINT RMSG_INTERFACE = ::RegisterWindowMessage("RMSG_INTERFACE");
const UINT RMSG_GETPCTRDATA = ::RegisterWindowMessage("RMSG_GETPCTRDATA");
const UINT RMSG_SETPCTRDATA = ::RegisterWindowMessage("RMSG_SETPCTRDATA");

/* AfxGetMainWnd()�� �߸��� �� ������ ����� AfxGetMainWnd()�� ������� ����
   �Ʒ� ���� �̸��� �Լ��� �����Ǿ����� ojtaso - 2006/2/14
#define AfxGetPctrInterface(xID)	AfxGetMainWnd()->SendMessage(RMSG_INTERFACE, xID, 0)
#define AfxGetPctrData(xID)		AfxGetMainWnd()->SendMessage(RMSG_GETPCTRDATA, (WPARAM)'A', xID)
#define AfxGetPctrDataEx(xID)	AfxGetMainWnd()->SendMessage(RMSG_GETPCTRDATA, (WPARAM)'E', xID)


#define AfxSetPctrData(xID, xData)	{	\
	STPCTR_SETDATA lData; lData.nID=xID; lData.szData=xData;	\
	AfxGetMainWnd()->SendMessage(RMSG_SETPCTRDATA, (WPARAM)'A', (LPARAM)&lData); }
//		AfxGetMainWnd()->SendMessage(RMSG_SETPCTRDATA, (WPARAM)'A', xID, xData)

#define AfxSetPctrDataEx(xID, xData)	 {	\
	STPCTR_SETEXDATA exData;  exData.nID=xID; exData.varData=xData; \
	AfxGetMainWnd()->SendMessage(RMSG_SETPCTRDATA, (WPARAM)'E', (LPARAM)&exData); }
	// AfxGetMainWnd()->SendMessage(RMSG_SETPCTRDATA, (WPARAM)'E', xID, xData)
*/

// AfxGetMainWnd()�� ����� ���� ���ϸ��� ��츦 ���ؼ�.....

#define		HANARO_CLIPKEY_MAINFRAME		"HANAROMAINFRAME"		//����Ʈ�������̹Ƿ� ����Ʈ���� ����������.
#define		HANARO_CLIPKEY_GATEMANAGER		"HANAROIGATEMANAGER"	//����Ʈ�������̹Ƿ� ����Ʈ���� ����������.
#define		HANARO_CLIPKEY_PCTRMAIN			"HANAROPCTRMAIN"		//����Ʈ�������̹Ƿ� ����Ʈ���� ����������.
#define		HANARO_PCTRMNG					"PcTrMng.dll"

// GetModuleName(..)�� ������ ���� : �� ����Ʈ���� �ٸ��� ���밡���ϰ�,
// ���� ����Ʈ������ �ε�� ��⸶�� �ٸ��� ���� �����ϵ��� ���ؼ�...
// ���ǻ���A : 2006.06.30��
// �⺻���� MainFrame�� �ڵ��� ���, �޽����� ������ �����̾�����, 
// ������ PCTRMainWnd��� ������ �����츦 ���ؼ� �����ϵ��� �����ߴ�.
// �ڵ������� HANARO_CLIPKEY_MAINFRAME -> AHANARO_CLIPKEY_PCTRMAIN �̷��� ����.
// ~���ǻ���
#define	AfxGetHanaroMainWnd(hMainHwnd)								\
	{																\
		hMainHwnd=NULL;												\
		char aBufWnd[8+1]={0,};										\
		CString szClipFormat;										\
		szClipFormat.Format("%s%08X", HANARO_CLIPKEY_PCTRMAIN, ::GetModuleHandle(HANARO_PCTRMNG));	\
		::GetEnvironmentVariable(szClipFormat, aBufWnd, 9);			\
		sscanf_s(aBufWnd,"%X", &hMainHwnd);							\
	}
// szClipFormat.Format("%s%08X", HANARO_CLIPKEY_MAINFRAME, ::GetModuleHandle(HANARO_PCTRMNG));

#define	AfxGetIGateManager(pGateMng)								\
	{																\
		pGateMng=NULL;												\
		char aBufWnd[8+1]={0,};										\
		CString szClipFormat;										\
		szClipFormat.Format("%s%08X", HANARO_CLIPKEY_GATEMANAGER, ::GetModuleHandle(HANARO_PCTRMNG));	\
		::GetEnvironmentVariable(szClipFormat, aBufWnd, 9);			\
		sscanf_s(aBufWnd,"%X", &pGateMng);							\
	}


#define		LIST_DELETEALL(xxList,xxClass)  {			\
	for(POSITION pos=xxList.GetHeadPosition(); pos;)	\
	{	xxClass* pItem = xxList.GetNext(pos);			\
		if(pItem) delete pItem;							\
	}	xxList.RemoveAll();		}

#define		LIST_DELETEALL2(xpList,xxClass)  {			\
	for(POSITION pos=xpList->GetHeadPosition(); pos;)	\
	{	xxClass* pItem = xpList->GetNext(pos);			\
		if(pItem) delete pItem;							\
	}	xpList->RemoveAll();	}


// ������ �ڵ��� �Ѱ��ش�.
static HWND AFXAPI AfxGetPctrMainHandle()
{
	HWND hMain=NULL;
	AfxGetHanaroMainWnd(hMain);
	
	return hMain;
}

// AfxGetMainWnd() ��ſ� ���..
static CWnd* AFXAPI AfxGetPctrMainWnd()
{
	HWND hMain = AfxGetPctrMainHandle();
	return CWnd::FromHandle(hMain);
}

// AfxGetMainWnd()�� �߸��� �� ������ ����� AfxGetHanaroMainWnd�� ����Ͽ� �Լ��� ���� ojtaso - 2006/2/14
// #define AfxGetPctrInterface(xID) -> LRESULT AFXAPI AfxGetPctrInterface(int nID)
static LRESULT AFXAPI AfxGetPctrInterface(int nID)
{
	HWND hMainWnd;
	AfxGetHanaroMainWnd(hMainWnd);

	return ::SendMessage(hMainWnd, RMSG_INTERFACE, (WPARAM)nID, 0);
}

static LRESULT AFXAPI AfxGetPctrInterfaceEx(int nID, int nSubID)
{
	HWND hMainWnd;
	AfxGetHanaroMainWnd(hMainWnd);
	
	return ::SendMessage(hMainWnd, RMSG_INTERFACE, (WPARAM)nID, nSubID);
}

// AfxGetMainWnd()�� �߸��� �� ������ ����� AfxGetHanaroMainWnd�� ����Ͽ� �Լ��� ���� ojtaso - 2006/2/14
// #define AfxGetPctrData(xID) -> LRESULT AFXAPI AfxGetPctrData(int nID)
static LRESULT AFXAPI AfxGetPctrData(int nID)
{
	HWND hMainWnd;
	AfxGetHanaroMainWnd(hMainWnd);

	return ::SendMessage(hMainWnd, RMSG_GETPCTRDATA, (WPARAM)'A', (LPARAM)nID);
}

// AfxGetMainWnd()�� �߸��� �� ������ ����� AfxGetHanaroMainWnd�� ����Ͽ� �Լ��� ���� ojtaso - 2006/2/14
// #define AfxGetPctrDataEx(xID) -> LRESULT AFXAPI AfxGetPctrDataEx(int nID)
static LRESULT AFXAPI AfxGetPctrDataEx(int nID)
{
	HWND hMainWnd;
	AfxGetHanaroMainWnd(hMainWnd);

	return ::SendMessage(hMainWnd, RMSG_GETPCTRDATA, (WPARAM)'E', (LPARAM)nID);
}

// AfxGetMainWnd()�� �߸��� �� ������ ����� AfxGetHanaroMainWnd�� ����Ͽ� �Լ��� ���� ojtaso - 2006/2/14
// #define AfxSetPctrData(xID, xData) -> LRESULT AFXAPI AfxSetPctrData(int nID, CString strData)
static LRESULT AFXAPI AfxSetPctrData(int nID, CString strData)
{
	STPCTR_SETDATA lData;
	lData.nID = nID;
	lData.szData = strData;

	HWND hMainWnd;
	AfxGetHanaroMainWnd(hMainWnd);

	return ::SendMessage(hMainWnd, RMSG_SETPCTRDATA, (WPARAM)'A', (LPARAM)&lData);
}

// AfxGetMainWnd()�� �߸��� �� ������ ����� AfxGetHanaroMainWnd�� ����Ͽ� �Լ��� ���� ojtaso - 2006/2/14
// #define AfxSetPctrDataEx(xID, xData) -> LRESULT AFXAPI AfxSetPctrDataEx(int nID, COleVariant varData)
static LRESULT AFXAPI AfxSetPctrDataEx(int nID, COleVariant varData)
{
	STPCTR_SETEXDATA exData;
	exData.nID = nID;
	exData.varData = varData;

	HWND hMainWnd;
	AfxGetHanaroMainWnd(hMainWnd);

	return ::SendMessage(hMainWnd, RMSG_SETPCTRDATA, (WPARAM)'E', (LPARAM)&exData);
}


#define MYMETHOD_PROLOGUE(theClass, localClass) \
	theClass* pThis = \
	((theClass*)((BYTE*)this - offsetof(theClass, m_x##localClass))); \
	pThis;

#define BDMakeValInit(xpVal, xxVal)		xpVal=xxVal;
#define	BDMakeNull(xpVal)	xpVal=NULL;
#define	BDSafeDelete(xpVal)	if(xpVal) delete xpVal; xpVal=NULL;

#define ADT_IF(pUsePoint) if(pUsePoint) {
#define	ADT_ELSE(pUsePoint) } else{
#define	ADT_ELSEIF(pUsePoint) } else if(pUsePoint) {
#define ADT_IFEND() }

#endif //AFX_HANARO_INTERFACE_H__320E_1464_BY_JUNOK_LEE_98B1A__INCLUDED_

