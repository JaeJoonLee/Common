#if !defined(AFX_HANARO_INTERFACE_H__320E_1464_BY_JUNOK_LEE_98B1A__INCLUDED_)
#define AFX_HANARO_INTERFACE_H__320E_1464_BY_JUNOK_LEE_98B1A__INCLUDED_

#include <afxtempl.h>

// #include "../../_Include/IBaseDefine.h"
// 만든이  : 이준옥 2005.11.02(수)
// History : 2005.11.02 인터페이스 및 메시지 정의
//
//---------------------------------------------------------
// VARIANT사용법은 아래에 설명함.
//_________________________________________________________

// 인터페이스 UUID_ 정의
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

#define		UUID_IKSLibManager					50	// 한국소리마치(KS) 라이브러리 인터페이스
#define		UUID_IPacketConvertManager			51

#define		MAX_INTERFACE						71
#define		MAX_IMainExInfoManager				41

//	HTS Mode
#define		HTSMODE_HTS						0
#define		HTSMODE_FOPRO					1

typedef struct
{
	int  nID;			// 데이터 고유ID
	CString szData;		// 데이터값
} STPCTR_SETDATA;


typedef struct 
{
	int  nID;			// 데이터 고유ID
	char sTR[5];		// TR번호
	long dwKey;			// 사용자키값. 리턴받을 때 그대로 넘겨줌.
	int  nInputSize;	// TR InputData size
	char aInputData[1];	// TR InputData
} STPCTR_GETDATAEX;
#define	SZ_STPCTR_GETDATAEX 		sizeof(STPCTR_GETDATAEX)

#define ZERO_STPCTR_GETDATAEX(st)	memset(&st, 0, SZ_STPCTR_GETDATAEX);


// STPCTR_SETEXDATA 이 구조체는 임의변경 말것. 플랫폼(DLL)에서 사용
typedef struct
{
	int  nID;					// 데이터 고유ID
	COleVariant varData;		// 데이터값
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
	// szKey로 주어진 데이터 값을 구한다.
	// I-PARAM : dwKey(키값)
	//           vData(리턴받을 VARIANT타입)
	// O-PARAM : 해당키값에 해당하는 데이터 포인터
	STDMETHOD_(COleVariant*, GetData)(LPCSTR szKey) PURE;

	// szKey로 주어진 데이터 값을 구한다.
	// I-PARAM : dwKey(키), dwData(새로운 값)
	// O-PARAM : 성공여부. TRUE(성공)/FALSE
	STDMETHOD_(BOOL, SetData)(LPCSTR szKey, const COleVariant* pvData) PURE;

	// dwKey로 주어진 데이터 값을 구한다.
	// I-PARAM : dwKey(키값)
	//           vData(리턴받을 VARIANT타입)
	// O-PARAM : 해당키값에 해당하는 데이터 포인터
	STDMETHOD_(COleVariant*, GetData)(int dwKey) PURE;

	// dwKey로 주어진 데이터 값을 구한다.
	// I-PARAM : dwKey(키), dwData(새로운 값)
	// O-PARAM : 성공여부. TRUE(성공)/FALSE
	STDMETHOD_(BOOL, SetData)(int dwKey, const COleVariant* pvData) PURE;
};


// vData->vt = VT_BSTR
// VARIANT var;		AfxVariantInit(&var);
// vData->bstrVal = szTmp.AllocSysString();

DECLARE_INTERFACE(IBaseDataString)
{
	// dwKey로 주어진 데이터 값을 구한다.
	// I-PARAM : szKey(키값)
	// O-PARAM : 해당키값에 해당하는 데이터
	STDMETHOD_(LPCSTR, GetDataString)(int nKey) PURE;

	// dwKey로 주어진 데이터 값을 구한다.
	// I-PARAM : szKey(키), szData(새로운 값)
	// O-PARAM : 예전데이타
	//           (인터페이스마다 예전데이터가 아닐 수도 있으므로 인터페이스 헤더 꼭 참조)
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

// 인터페이스 포인트 구하기
/* -----------------------------------------------------------
	WPARAM wp;  //STMSG_INTERFACE* 구조체
	LPARAM lp;  //사용안함.
	Return-Value : //현재는 의미없음
 
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

/* AfxGetMainWnd()의 잘못된 값 리턴을 대비해 AfxGetMainWnd()를 사용하지 않음
   아래 같은 이름의 함수로 구현되어있음 ojtaso - 2006/2/14
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

// AfxGetMainWnd()가 제대로 값을 리턴못할 경우를 위해서.....

#define		HANARO_CLIPKEY_MAINFRAME		"HANAROMAINFRAME"		//사이트독립적이므로 사이트별로 수정마세요.
#define		HANARO_CLIPKEY_GATEMANAGER		"HANAROIGATEMANAGER"	//사이트독립적이므로 사이트별로 수정마세요.
#define		HANARO_CLIPKEY_PCTRMAIN			"HANAROPCTRMAIN"		//사이트독립적이므로 사이트별로 수정마세요.
#define		HANARO_PCTRMNG					"PcTrMng.dll"

// GetModuleName(..)을 적용한 이유 : 각 사이트마다 다르게 적용가능하고,
// 같은 사이트에서도 로드된 모듈마다 다르게 적용 가능하도록 위해서...
// 주의사항A : 2006.06.30금
// 기본에는 MainFrame의 핸들을 얻고, 메시지를 보내는 형태이었으나, 
// 이제는 PCTRMainWnd라는 별도의 윈도우를 통해서 동작하도록 수정했다.
// 코딩상으로 HANARO_CLIPKEY_MAINFRAME -> AHANARO_CLIPKEY_PCTRMAIN 이렇게 수정.
// ~주의사항
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


// 메인의 핸들을 넘겨준다.
static HWND AFXAPI AfxGetPctrMainHandle()
{
	HWND hMain=NULL;
	AfxGetHanaroMainWnd(hMain);
	
	return hMain;
}

// AfxGetMainWnd() 대신에 사용..
static CWnd* AFXAPI AfxGetPctrMainWnd()
{
	HWND hMain = AfxGetPctrMainHandle();
	return CWnd::FromHandle(hMain);
}

// AfxGetMainWnd()의 잘못된 값 리턴을 대비해 AfxGetHanaroMainWnd를 사용하여 함수로 구현 ojtaso - 2006/2/14
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

// AfxGetMainWnd()의 잘못된 값 리턴을 대비해 AfxGetHanaroMainWnd를 사용하여 함수로 구현 ojtaso - 2006/2/14
// #define AfxGetPctrData(xID) -> LRESULT AFXAPI AfxGetPctrData(int nID)
static LRESULT AFXAPI AfxGetPctrData(int nID)
{
	HWND hMainWnd;
	AfxGetHanaroMainWnd(hMainWnd);

	return ::SendMessage(hMainWnd, RMSG_GETPCTRDATA, (WPARAM)'A', (LPARAM)nID);
}

// AfxGetMainWnd()의 잘못된 값 리턴을 대비해 AfxGetHanaroMainWnd를 사용하여 함수로 구현 ojtaso - 2006/2/14
// #define AfxGetPctrDataEx(xID) -> LRESULT AFXAPI AfxGetPctrDataEx(int nID)
static LRESULT AFXAPI AfxGetPctrDataEx(int nID)
{
	HWND hMainWnd;
	AfxGetHanaroMainWnd(hMainWnd);

	return ::SendMessage(hMainWnd, RMSG_GETPCTRDATA, (WPARAM)'E', (LPARAM)nID);
}

// AfxGetMainWnd()의 잘못된 값 리턴을 대비해 AfxGetHanaroMainWnd를 사용하여 함수로 구현 ojtaso - 2006/2/14
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

// AfxGetMainWnd()의 잘못된 값 리턴을 대비해 AfxGetHanaroMainWnd를 사용하여 함수로 구현 ojtaso - 2006/2/14
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

