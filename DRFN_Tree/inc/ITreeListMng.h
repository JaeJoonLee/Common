#if !defined(AFX_INTERFACE_OF_TREELISTMANAGER_BY_JUNOK_LEE__INCLUDED_)
#define AFX_INTERFACE_OF_TREELISTMANAGER_BY_JUNOK_LEE__INCLUDED_

// #include "../../_include/ITreeListMng.h"
// 

#include "IBaseDefine.h"
// #include "./MasterDefine.h"
#include "./IMasterDataMng.h"
#include <AFXTEMPL.H>
//#include "./LoadTreeListMng.h"

#include "./DefineCode.h"

#define		UUID_ITreeListManager				26
#define		UUID_ITreeListManager2				26

// 사용예는 이 파일의 제일 하단 부분의 코멘트것 참조.
//
//
/* -------------------------------------------------------------------------
설명 : 트리형태의 리스트뷰지원
관련문서 : 정리_트리리스트.doc
만든이  : 이준옥 2006.01.06(금)
History : 2006.01.06 인터페이스 정의
----------------------------------------------------------------------------
int nID = UUID_ITreeListManager;
ITreeListManager* pManager = (ITreeListManager*)AfxGetMainWnd()->SendMessage(RMSG_INTERFACE, nID, 0);
ITreeListManager* pManager = (ITreeListManager*)AfxGetPctrInterface(nID);

------------------------------------------------------------------------- */
class CItemLongData;
class CInputCodeList;
class CInputCodeListEx;

DECLARE_INTERFACE(ITLMCallback)
{
	// nRtnState 0 : 정상
	//           0 아닌값은 에러코드. (-)서버에러, (+)PC에러
	STDMETHOD_(void, ReceiveData)(int nRtnState, char aDataType, long dwReserved, long nLength, void* pData) PURE;

	// nID : 데이터 아이디
//	STDMETHOD_(void, ChangedData)(int nID, long dwData) PURE;
};

DECLARE_INTERFACE(ITreeListManagerBase)
{
	STDMETHOD_(void, SetKeyData)(LPCSTR szKey, LPCSTR szData) PURE;
	STDMETHOD_(void, SetKeyData)(LPCSTR szKey, long   dwData) PURE;
};

DECLARE_INTERFACE_(ITreeListManager, ITreeListManagerBase)
//DECLARE_INTERFACE(ITreeListManager)
{
	// pInData : CFG파일명
	// szSection : GetPrivateProfileString 함수의 첫번째인자값.
	STDMETHOD_(LONG, LoadTreeList)(CInputCodeListEx *pInData, LPCSTR szSection="TREELIST") PURE;
	STDMETHOD_(void, UnLoadTreeList)(LONG dwKey) PURE;
//	STDMETHOD_(BOOL, LoadFile)(CInputCodeListEx *pInData, LPCSTR szSection="LIST") PURE;

	// pILData : CTreeCtrl에서 GetItemData에서 얻어진 값.
	// pCallback : 콜백함수
	// cDataType : 리턴받을 데이터 타입. 'A':종목코드/종목명
	//                                   'B':종목코드/종목명/현재가/거래량
	// cSort : '0':변경없이 요청순서대로 '1':코드순, '2':이름순, 
	// dwReserved : Callback할 때 리턴해줄 값.
	STDMETHOD_(void, RequestData)(CItemLongData* pILData, ITLMCallback* pCallback, char cDataType, char cSort, long dwReserved=0) PURE;

	// Config파일을 변경하고자 할때 
	// Default는 $DATA/CodeItem.cfg
	STDMETHOD_(void, ChangeConfigFile)(LPCSTR szFileName) PURE;

	STDMETHOD_(void*, GetITrComm)(LONG dwKey) PURE;

	// pITrComm : ITrComm* 포인트
	STDMETHOD_(void, RequestCodeData)(void* pITrComm, LIST_TR_CODEINFO* pCodeList, ITLMCallback* pCallback, char cDataType, char cSort, long dwReserved=0) PURE;

	// 관심그룹 트리를 다시 로딩하도록 요청.
	STDMETHOD_(void, ReloadGwansimGroup)(LONG dwKey, CTreeCtrl* pTreeCtrl) PURE;

	// 관심그룹이 설정된 TREE의 HITEM
	STDMETHOD_(HTREEITEM, GetGwansimItem)(CTreeCtrl* pTreeCtrl) PURE;

	// 트리에서 hTreeRoot밑에서 폴더의 이름을 얻어온다. 상위폴더임.
	// 따라서 관심그룹, 임시그룹등..
	// hTreeRoot이면 상위에서 검색, 
	// 하위폴더로의 검색은 하지 않은다. 같은 레벨에서만 찾는다.
	STDMETHOD_(HTREEITEM, GetTreeItem)(CTreeCtrl* pTreeCtrl, LPCSTR szFolder, HTREEITEM hTreeRoot=NULL) PURE;

	// 트리에 관심관련 세팅을 한다.
	// 기존에 관심에서 IMainExInfoManager인터페이스를 통해서. IMainExInfoManager_Gwansim으로 Key로 등록하던 부분을 
	// (같은효과를) 트리인터페이스에도 추가한 것임.
	// 주의 1.관심그룹을 변경하기 전에 이 데이터를 세팅하는 관심에서는 기존데이터를 지워줘야함.
	//      2.관심 내려갈 때 이 포인터도 지워줘야함.
	STDMETHOD_(void, GwansimRegist)(long dwData) PURE;

	// 트리의 임시그룹에 등록하는 기능. 기존것은 지우고 새로 만든다.
	//  szSubKey는 사용하지 않으므로 NULL, 추후 임시그룹 및에 그룹명을 더 넣을 경우 대비.
	STDMETHOD_(int, ImsiRegist)(LPCSTR szSubKey, long dwData) PURE;

	// 트리의 임시그룹의 내용을 지우는 함수
	//  szSubKey는 사용하지 않으므로 NULL, 추후 임시그룹 및에 그룹명을 더 넣을 경우 대비.
	STDMETHOD_(int, ImsiDelete)(LPCSTR szSubKey) PURE;

	// 트리의 임시그룹에 추가하는 함수
	//  szSubKey는 사용하지 않으므로 NULL, 추후 임시그룹 및에 그룹명을 더 넣을 경우 대비.
	// 기존 임시그룹의 데이터를 지우지않고 추가하는 기능
	// STDMETHOD_(int, ImsiAppend)(LPCSTR szSubKey, long dwData) PURE;

};

DECLARE_INTERFACE_(ITreeListManager2, ITreeListManager)
{
	STDMETHOD_(void, SetBaseData) (LPCSTR szKey, LPCSTR  szValue) PURE;
	STDMETHOD_(void, GetBaseData) (LPCSTR szKey, CString &rValue) PURE;

//->@Solomon에만 해당.
	STDMETHOD_(void, SetSendKey) (HWND hWinix, HWND hDrfnWrap) PURE;
	STDMETHOD_(void, SetGwanInterface) (long pInterface) PURE;
//<--@Solomon에만 해당.
};

#include "DefineCode.h"

// -----------------------------------------------------------------------------------------
class CInputCodeList
{
public:
	CTreeCtrl	*m_pTreeCtrl;
	CString		m_szFile;
	CString		m_szSection;

public:
	CInputCodeList()
	{
		m_pTreeCtrl = NULL;
		m_szSection = "TREELIST";
	}
};

class CInputCodeListEx : public CInputCodeList
{
public:
	CListCtrl*	m_pListCtrl;
	int		m_nCtrlType;
	void	SetCtrlType(int nType)
	{
		m_nCtrlType = nType;
	}
	int		GetCtrlType() { return m_nCtrlType;	}

	enum {
		ICLE_CTLTYPE_TREE=0,
		ICLE_CTLTYPE_LIST,
	};

public:
	CInputCodeListEx()
	{
		m_nCtrlType = ICLE_CTLTYPE_TREE;
		m_pListCtrl = NULL;
	}
};

/* =====================================================================
CItemLongData 
CTreeCtrl에서 DataPtr로 세팅될 값.
===================================================================== */
#define		TREELIST_DEFAULT_TR			"NONE"

enum {
	BaseLongData_Item=0,
	BaseLongData_OneClick,
};

class CBaseLongData
{
public:
	CBaseLongData() 
	{
		m_nType=BaseLongData_Item; 
	}

public:
	int		m_nType;
};

typedef CList <CBaseLongData*, CBaseLongData*> LIST_CBaseLongData;


class CItemLongData : public CBaseLongData
{
public:
	CString m_szTitle;
	CString	m_szSub;
	CString	m_szMethod;
	CString m_szSection;
	CString m_szInputData;
	CString m_szTR;
	long	m_lReserved1;
	long	m_lReserved2;
	long	m_pITrComm;

public:
	CItemLongData()
	{
		m_nType = BaseLongData_Item;
		m_szSub = "SUB_NO";
		m_szMethod = "PC";
		m_lReserved1 = 0;
		m_lReserved2 = 0;
		m_pITrComm = NULL;
	}
	
	CItemLongData(LPCSTR szTitle, LPCSTR szSub, LPCSTR szMethod, LPCSTR szSection, LPCSTR szInputData, LPCSTR szTR, long dw1, long dw2, long pITrComm=NULL)
	{
		m_szTitle = szTitle;
		m_szSub = szSub;
		m_szMethod = szMethod;
		m_szSection = szSection;
		m_szInputData = szInputData;
		m_szTR = szTR;
		if(m_szTR.GetLength()==0) m_szTR=TREELIST_DEFAULT_TR;
		m_lReserved1 = dw1;
		m_lReserved2 = dw2;
		m_pITrComm = pITrComm;
	}

	void Convert(char* szString)
	{
		char aTitle[MAX_PATH+1],
			aSub[MAX_PATH+1],
			aMethod[MAX_PATH+1],
			aSection[MAX_PATH+1],
			aInputData[MAX_PATH+1],
			aTr[MAX_PATH+1];
		//01=전종목,SUB_NO,MASTER,Master_J_K,A1000B000
		//04=거래소,SUB_YES,MASTER,UMaster,A1100B000
		//09=특이종목,SUB_YES,CFG,NONE,A2100B000
		sscanf(szString, "%[^,], %[^,],%[^,],%[^,],%[^,],%[^,],", aTitle, aSub, aMethod, aSection, aInputData, aTr);
		// TRACE("[%s][%s][%s][%s][%s]\n", aTitle, aSection, aSub, aMethod, aInputData);
		m_szTR = aTr;
		m_szTitle = aTitle;
		m_szSub = aSub;
		m_szMethod = aMethod;
		m_szSection = aSection;
		m_szInputData = aInputData;
	}

	void SetCopy(CItemLongData *pIn)
	{
		m_szTitle		=	pIn->m_szTitle;
		m_szSub			=	pIn->m_szSub;
		m_szMethod		=	pIn->m_szMethod;
		m_szSection		=	pIn->m_szSection;
		m_szInputData	=	pIn->m_szInputData;
		m_szTR			=   pIn->m_szTR;
		m_lReserved1	=	pIn->m_lReserved1;
		m_lReserved2	=	pIn->m_lReserved2;
		m_pITrComm      =	pIn->m_pITrComm;
	}
};

 typedef CList <CItemLongData*, CItemLongData*> LIST_CItemLongData;

class CItemOneClickData : public CItemLongData
{
public:
	CItemOneClickData()
	{
		m_nType = BaseLongData_OneClick;
		m_lReserved1 = NULL;
		m_lReserved2 = NULL;
		m_pITrComm	 = NULL;
		m_pITrcommSite = NULL;
	}

public:
	CString m_szOCPath;	// OneClick Path
	long	m_lReserved1;
	long	m_lReserved2;
	long	m_pITrComm;
	long	m_pITrcommSite;
};

/*
typedef struct _tr_88888_A
{
	char code       [ 6];
	char hname      [20];
} TR_88888_A;
*/

enum 
{
	codeType_KOSPI=1,
	codeType_KOSDAQ,
	codeType_FREEBOARD,
};
class CCodeTypeBase
{
public: //Variable
//	char     m_cGb			;       /* '1':주식, '2':코스닥 , '3':프리보드(제3시장)   */
//	CString  m_szcode		;    	/* 종목코드         */
//	CString  m_szhname		;   	/* 종목명(한글)M    */
	CString  m_szcode		;    	/* 종목코드         */
	CString  m_szhname		;   	/* 종목명(한글)M    */

	void Copy(CCodeTypeBase *pSrc)
	{
		m_szcode = pSrc->m_szcode;
		m_szhname = pSrc->m_szhname;
		//m_cGb     = pSrc->m_cGb;
	}


	virtual void  Convert(char* pData) 	{}
	virtual void  Convert2(char* pData) 	{}
	
	virtual void ConvertOneClickData(char* strData) 
	{
		// Virtual에서 구현해야 함...
		Convert2(strData);
		//m_cGb = CheckeNameType((LPSTR)(LPCSTR)m_szhname);
	}

	static int CheckeNameType(char* strData)
	{
		CString szKey;
		szKey.Format("%2.2s", strData);

		if (szKey == "ⓚ")	
		{
			return codeType_KOSDAQ;
		}
		else if(szKey == "ⓣ")
		{
			return codeType_FREEBOARD;
		}
		else
		{
			return codeType_KOSPI;
		}
	}
};

class CCodeTypeA : public CCodeTypeBase
{
public:
	CCodeTypeA() {}
	virtual void  Convert(char* pData) 
	{
		int nL;
		char sTmp[20+1];
		//m_cGb = pData[0];   pData=&pData[1];
		nL=16; memcpy(sTmp, pData, nL); sTmp[nL]=0;  pData=&pData[nL]; m_szcode=sTmp;
		nL=20; memcpy(sTmp, pData, nL); sTmp[nL]=0;  m_szhname=sTmp; m_szhname.TrimRight();
	}

	virtual void  Convert2(char* pData) 
	{
		int nL;
		char sTmp[20+1];
		nL=16; memcpy(sTmp, pData, nL); sTmp[nL]=0;  pData=&pData[nL]; m_szcode=sTmp;
		nL=20; memcpy(sTmp, pData, nL); sTmp[nL]=0;  m_szhname=sTmp; m_szhname.TrimRight();
	}

	void Copy(CCodeTypeA* pSrc)
	{
		CCodeTypeBase::Copy(pSrc);
	}

	virtual void ConvertOneClickData(char* strData) 
	{
		CCodeTypeBase::ConvertOneClickData(strData);
	}

//	static int CompBackward(CCodeTypeA* pFirstObj, CCodeTypeA* pSecondObj)
//    {
//        return lstrcmp((LPCTSTR)pFirstObj->m_szhname,(LPCTSTR)pSecondObj->m_szhname);
//    }

};

typedef CList<CCodeTypeA, CCodeTypeA> LIST_CCodeTypeA;
typedef CArray<CCodeTypeA, CCodeTypeA> ARRAY_CCodeTypeA;

/*	
typedef struct _tr_88888_B
{
	char code       [ 6];
	char hname      [20];
    char time       [ 6];
    char sign       [ 1];
    char change     [ 9];
    char price      [ 9];
    char chrate     [ 5];
	char volume     [12]; 
} TR_88888_B;
*/
class CCodeTypeB : public CCodeTypeBase
{
public: //Variable
//	CString  m_szcode       ;		/* 종목코드			*/
//	CString  m_szhname      ;		/* 종목명(한글)M	*/
    CString  m_sztime       ;		/* 시간(HH:MM:SS)	*/
    CString  m_szsign       ;		/* 등락부호			*/
    CString  m_szchange     ;		/* 등락폭			*/
    CString  m_szprice      ;		/* 현재가			*/
    CString  m_szchrate     ;		/* 등락률			*/
	CString  m_szvolume     ;		/* 누적거래량       */

public:
	CCodeTypeB() {}

	virtual void  Convert(char* pData) 
	{
		int nL;
		char sTmp[20+1];
		//m_cGb = pData[0];   pData=&pData[1];
		nL=16; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szcode=sTmp;	m_szcode.TrimRight();
		nL=20; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szhname=sTmp;	m_szhname.TrimRight();
		nL=10; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szprice=sTmp;	m_szprice.TrimRight();
		//nL= 6; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_sztime=sTmp;	m_sztime.TrimRight();
		nL= 1; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szsign=sTmp;	m_szsign.TrimRight();
		nL=10; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szchange=sTmp;	m_szchange.TrimRight();
		nL= 6; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szchrate=sTmp;	m_szchrate.TrimRight();
		nL=12; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szvolume=sTmp;	m_szvolume.TrimRight();
	}

	virtual void  Convert2(char* pData) 
	{
		int nL;
		char sTmp[20+1];
		nL=6;  memcpy(sTmp, pData, nL); sTmp[nL]=0;  pData=&pData[nL]; m_szcode=sTmp;
		nL=20; memcpy(sTmp, pData, nL); sTmp[nL]=0;  pData=&pData[nL]; m_szhname=sTmp; m_szhname.TrimRight();
		nL= 3;	pData=&pData[nL]; 
		nL= 8; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szprice=sTmp;	m_szprice.TrimRight();
		nL= 1; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szsign=sTmp;	m_szsign.TrimRight();
		nL= 8; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szchange=sTmp;	m_szchange.TrimRight();
		nL= 6; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szchrate=sTmp;	m_szchrate.TrimRight();
		nL=9; memcpy(sTmp, pData, nL); sTmp[nL]=0; pData=&pData[nL]; m_szvolume=sTmp;	m_szvolume.TrimRight();

		switch(atoi(m_szsign)) {
		case 1:
			m_szsign = "7";
			break;
		case 2:
			m_szsign = "6";
			break;
		case 3:
			m_szsign = "5";
			break;
		case 4:
			m_szsign = "3";
			break;
		case 5:
			m_szsign = "4";
			break;
		}

		//nL= 6;	pData=&pData[nL]; 		
	}

	virtual void ConvertOneClickData(char* strData) 
	{
		CCodeTypeBase::ConvertOneClickData(strData);
	}
};
typedef CList<CCodeTypeB, CCodeTypeB> LIST_CCodeTypeB;

/*	
typedef struct _tr_88803_C
{
    char under           [ 1];
    char jg_tp           [ 1];
    char jg_code         [15];
    char jg_name         [30];
    char price           [ 9];
    char change          [ 6];
    char change_rate     [ 5];
    char sign            [ 1];
    char volume          [12];
    char offerho         [ 9];
    char bidho           [ 9];
    char ofremain        [12];
    char bidremain       [12];
    char offertot        [12];
    char bidtot          [12];
    char openam          [ 9];
    char high            [ 9];
    char low             [ 9];
    char value           [14];
    char uplmtprice      [ 9];
    char dnlmtprice      [ 9];
    char openyak         [ 9];
    char parvalue        [ 9];
    char presign         [ 1];
    char updnlmtcont_tp  [ 1];
    char updnlmtcont     [ 2];
    char recprice        [ 9];
    char cvolume         [ 9];
    char open_chrate     [ 5];
    char high_chrate     [ 5];
    char low_chrate      [ 5];
    char hightime        [ 6];
    char lowtime         [ 6];
    char expsign         [ 1];
    char expprice        [ 9];
    char expchang        [ 9];
    char expchgrt        [ 9];
    char expvol          [12];
    char color           [ 1];
} TR_88803_C;

  Size 313
*/
class CCodeTypeC : public CCodeTypeBase
{
public: //Variable
	char m_InquiryData[400];

public:
	CCodeTypeC() {}

	virtual void  Convert(char* pData) 
	{
		::memcpy(&m_InquiryData, pData, 313);
	}

	virtual void  Convert2(char* pData) 
	{
//		int nL;
//		char sTmp[20+1];
//		nL=6;  memcpy(sTmp, pData, nL); sTmp[nL]=0;  pData=&pData[nL]; m_szcode=sTmp;
//		nL=20; memcpy(sTmp, pData, nL); sTmp[nL]=0;  m_szhname=sTmp; m_szhname.TrimRight();
	}

	virtual void ConvertOneClickData(char* strData) 
	{
		CCodeTypeBase::ConvertOneClickData(strData);
	}
};
typedef CList<CCodeTypeC, CCodeTypeC> LIST_CCodeTypeC;


class CDataInfo_GwanList
{
public:
	int nIndex;
};

#endif //AFX_INTERFACE_OF_TREELISTMANAGER_BY_JUNOK_LEE__INCLUDED_


/*
void CJMCodeDlg::InitTree()
{
	CInputCodeList inData;
	inData.m_pTreeCtrl = &m_TreeList;
	inData.m_szSection = "TREELIST";

	theApp.m_pTreeListMng->LoadTreeList(&inData);
}

void CJMCodeDlg::OnDestroy() 
{
	theApp.m_pTreeListMng->UnLoadTreeList();

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}


// 요청하는 타입 'A' or 'B'
// 코드소트 타입 '0':코드순, '1':코드명순
void CJMCodeDlg::OnClickTreelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM hItem = m_TreeList.m_hSelTreeItem;
	if(hItem == NULL)
		return;

	CItemLongData* pLData = (CItemLongData*)m_TreeList.GetItemData(hItem);
	if(pLData)
	{
		m_List.DeleteAllItems();
		m_ListCodeTypeA.RemoveAll();

		long dwReserved=0;
		theApp.m_pTreeListMng->RequestData(pLData, &m_xTLMCallback, 'A', '1', dwReserved);
	}
	
	*pResult = 0;
}


void CJMCodeDlg::CTLMCallback::ReceiveData(int nRtnState, char aDataType, long dwReserved, int nLength, void* pData)
{
	METHOD_PROLOGUE(CJMCodeDlg, TLMCallback);
	// pThis->
	if(aDataType=='A')
	{
		LIST_CCodeTypeA *pListType = (LIST_CCodeTypeA*)pData;
		if(pListType)
		{
			for(POSITION pos=pListType->GetHeadPosition(); pos; )
			{
				CCodeTypeA codeData = pListType->GetNext(pos);
				pThis->m_ListCodeTypeA.AddTail(codeData);
			}
			pThis->m_List.SetItemCount(pThis->m_ListCodeTypeA.GetCount());
		}
	}
	else if(aDataType=='B')		//코드도움말에서는 'A'타입만 다룬다.
	{
		LIST_CCodeTypeB *pListType = (LIST_CCodeTypeB*)pData;
		if(pListType)
		{
			for(POSITION pos=pListType->GetHeadPosition(); pos; )
			{
				CCodeTypeB codeData = pListType->GetNext(pos);
				CCodeTypeA	codeDataA;	codeDataA.m_szcode=codeData.m_szcode;
										codeDataA.m_szhname=codeData.m_szhname;
				pThis->m_ListCodeTypeA.AddTail(codeDataA);
			}
			pThis->m_List.SetItemCount(pThis->m_ListCodeTypeA.GetCount());
		}
	}
}

*/
