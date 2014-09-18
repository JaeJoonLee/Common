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

// ��뿹�� �� ������ ���� �ϴ� �κ��� �ڸ�Ʈ�� ����.
//
//
/* -------------------------------------------------------------------------
���� : Ʈ�������� ����Ʈ������
���ù��� : ����_Ʈ������Ʈ.doc
������  : ���ؿ� 2006.01.06(��)
History : 2006.01.06 �������̽� ����
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
	// nRtnState 0 : ����
	//           0 �ƴѰ��� �����ڵ�. (-)��������, (+)PC����
	STDMETHOD_(void, ReceiveData)(int nRtnState, char aDataType, long dwReserved, long nLength, void* pData) PURE;

	// nID : ������ ���̵�
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
	// pInData : CFG���ϸ�
	// szSection : GetPrivateProfileString �Լ��� ù��°���ڰ�.
	STDMETHOD_(LONG, LoadTreeList)(CInputCodeListEx *pInData, LPCSTR szSection="TREELIST") PURE;
	STDMETHOD_(void, UnLoadTreeList)(LONG dwKey) PURE;
//	STDMETHOD_(BOOL, LoadFile)(CInputCodeListEx *pInData, LPCSTR szSection="LIST") PURE;

	// pILData : CTreeCtrl���� GetItemData���� ����� ��.
	// pCallback : �ݹ��Լ�
	// cDataType : ���Ϲ��� ������ Ÿ��. 'A':�����ڵ�/�����
	//                                   'B':�����ڵ�/�����/���簡/�ŷ���
	// cSort : '0':������� ��û������� '1':�ڵ��, '2':�̸���, 
	// dwReserved : Callback�� �� �������� ��.
	STDMETHOD_(void, RequestData)(CItemLongData* pILData, ITLMCallback* pCallback, char cDataType, char cSort, long dwReserved=0) PURE;

	// Config������ �����ϰ��� �Ҷ� 
	// Default�� $DATA/CodeItem.cfg
	STDMETHOD_(void, ChangeConfigFile)(LPCSTR szFileName) PURE;

	STDMETHOD_(void*, GetITrComm)(LONG dwKey) PURE;

	// pITrComm : ITrComm* ����Ʈ
	STDMETHOD_(void, RequestCodeData)(void* pITrComm, LIST_TR_CODEINFO* pCodeList, ITLMCallback* pCallback, char cDataType, char cSort, long dwReserved=0) PURE;

	// ���ɱ׷� Ʈ���� �ٽ� �ε��ϵ��� ��û.
	STDMETHOD_(void, ReloadGwansimGroup)(LONG dwKey, CTreeCtrl* pTreeCtrl) PURE;

	// ���ɱ׷��� ������ TREE�� HITEM
	STDMETHOD_(HTREEITEM, GetGwansimItem)(CTreeCtrl* pTreeCtrl) PURE;

	// Ʈ������ hTreeRoot�ؿ��� ������ �̸��� ���´�. ����������.
	// ���� ���ɱ׷�, �ӽñ׷��..
	// hTreeRoot�̸� �������� �˻�, 
	// ������������ �˻��� ���� ������. ���� ���������� ã�´�.
	STDMETHOD_(HTREEITEM, GetTreeItem)(CTreeCtrl* pTreeCtrl, LPCSTR szFolder, HTREEITEM hTreeRoot=NULL) PURE;

	// Ʈ���� ���ɰ��� ������ �Ѵ�.
	// ������ ���ɿ��� IMainExInfoManager�������̽��� ���ؼ�. IMainExInfoManager_Gwansim���� Key�� ����ϴ� �κ��� 
	// (����ȿ����) Ʈ���������̽����� �߰��� ����.
	// ���� 1.���ɱ׷��� �����ϱ� ���� �� �����͸� �����ϴ� ���ɿ����� ���������͸� ���������.
	//      2.���� ������ �� �� �����͵� ���������.
	STDMETHOD_(void, GwansimRegist)(long dwData) PURE;

	// Ʈ���� �ӽñ׷쿡 ����ϴ� ���. �������� ����� ���� �����.
	//  szSubKey�� ������� �����Ƿ� NULL, ���� �ӽñ׷� �׿� �׷���� �� ���� ��� ���.
	STDMETHOD_(int, ImsiRegist)(LPCSTR szSubKey, long dwData) PURE;

	// Ʈ���� �ӽñ׷��� ������ ����� �Լ�
	//  szSubKey�� ������� �����Ƿ� NULL, ���� �ӽñ׷� �׿� �׷���� �� ���� ��� ���.
	STDMETHOD_(int, ImsiDelete)(LPCSTR szSubKey) PURE;

	// Ʈ���� �ӽñ׷쿡 �߰��ϴ� �Լ�
	//  szSubKey�� ������� �����Ƿ� NULL, ���� �ӽñ׷� �׿� �׷���� �� ���� ��� ���.
	// ���� �ӽñ׷��� �����͸� �������ʰ� �߰��ϴ� ���
	// STDMETHOD_(int, ImsiAppend)(LPCSTR szSubKey, long dwData) PURE;

};

DECLARE_INTERFACE_(ITreeListManager2, ITreeListManager)
{
	STDMETHOD_(void, SetBaseData) (LPCSTR szKey, LPCSTR  szValue) PURE;
	STDMETHOD_(void, GetBaseData) (LPCSTR szKey, CString &rValue) PURE;

//->@Solomon���� �ش�.
	STDMETHOD_(void, SetSendKey) (HWND hWinix, HWND hDrfnWrap) PURE;
	STDMETHOD_(void, SetGwanInterface) (long pInterface) PURE;
//<--@Solomon���� �ش�.
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
CTreeCtrl���� DataPtr�� ���õ� ��.
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
		//01=������,SUB_NO,MASTER,Master_J_K,A1000B000
		//04=�ŷ���,SUB_YES,MASTER,UMaster,A1100B000
		//09=Ư������,SUB_YES,CFG,NONE,A2100B000
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
//	char     m_cGb			;       /* '1':�ֽ�, '2':�ڽ��� , '3':��������(��3����)   */
//	CString  m_szcode		;    	/* �����ڵ�         */
//	CString  m_szhname		;   	/* �����(�ѱ�)M    */
	CString  m_szcode		;    	/* �����ڵ�         */
	CString  m_szhname		;   	/* �����(�ѱ�)M    */

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
		// Virtual���� �����ؾ� ��...
		Convert2(strData);
		//m_cGb = CheckeNameType((LPSTR)(LPCSTR)m_szhname);
	}

	static int CheckeNameType(char* strData)
	{
		CString szKey;
		szKey.Format("%2.2s", strData);

		if (szKey == "��")	
		{
			return codeType_KOSDAQ;
		}
		else if(szKey == "��")
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
//	CString  m_szcode       ;		/* �����ڵ�			*/
//	CString  m_szhname      ;		/* �����(�ѱ�)M	*/
    CString  m_sztime       ;		/* �ð�(HH:MM:SS)	*/
    CString  m_szsign       ;		/* �����ȣ			*/
    CString  m_szchange     ;		/* �����			*/
    CString  m_szprice      ;		/* ���簡			*/
    CString  m_szchrate     ;		/* �����			*/
	CString  m_szvolume     ;		/* �����ŷ���       */

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


// ��û�ϴ� Ÿ�� 'A' or 'B'
// �ڵ��Ʈ Ÿ�� '0':�ڵ��, '1':�ڵ���
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
	else if(aDataType=='B')		//�ڵ嵵�򸻿����� 'A'Ÿ�Ը� �ٷ��.
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
