#if !defined(AFX_INTERFACE_OF_MASTERDATAMANAGER_BY_JUNOK_LEE__INCLUDED_)
#define AFX_INTERFACE_OF_MASTERDATAMANAGER_BY_JUNOK_LEE__INCLUDED_

// #include "../../_include/IMasterDataMng.h"
// 

#include "IBaseDefine.h"
#include "./MasterDefine.h"
#include "./MasterDataSub.h"

//#define		UUID_IMasterDataManager				5
//#define		UUID_IMasterDataManager0712			UUID_IMasterDataManager
//#define		UUID_IMasterDataManager080331		UUID_IMasterDataManager
//#define		UUID_IMasterDataManager099999		UUID_IMasterDataManager
//#define		UUID_IMasterDataManager080902		UUID_IMasterDataManager
#define		IMasterDataManagerLast				IMasterDataManager080902
/* -------------------------------------------------------------------------
���� : ������������ �ڵ鸵
���ù��� : ����_����������.doc
������  : ���ؿ� 2005.11.25(��)
History : 2005.11.25 �������̽� ����
----------------------------------------------------------------------------
- IMasterDataManager�������̽��� ����� �����ϱ� ���ؼ���
  ���ο��� CodeOcx�� IMainExInfoManager�� ���� ��������� �Ѵ�.

int nID = 5;
IMasterDataManager* pManager = (IMasterDataManager*)AfxGetMainWnd()->SendMessage(RMSG_INTERFACE, nID, 0);
IMasterDataManager* pManager = (IMasterDataManager*)AfxGetPctrInterface(nID);

ex1>
	CList<CJMaster, CJMaster>* list = 
		(CList<CJMaster, CJMaster>*)pManager->GetCodePointer("JMASTER"); 

ex2>
	int nID = 5;
	IMasterDataManager* pManager = (IMasterDataManager*)AfxGetPctrInterface(nID);
	if(pManager==NULL)
	{
		AfxMessageBox("IMasterDataManager Not Loaded");
		return;
	}
	int nTotal = pManager->LoadMASTER_J_K();
	CMaster_J_K* pData = pManager->J_K_GetMaster();
	for(int i=0; i<nTotal && i<3; i++)
	{
		CString s;
		s.Format("Code[%s], Name[%s]\n", pData[i].m_szCode, pData[i].m_szName);
		AfxMessageBox(s);
	}
	pManager->UnLoadMASTER_J_K();

ex3>
	...���⿡..

----------------------------------------------------------------------------
������������ $DATA/Master���丮�� ��ġ��.
����(205.11.25��)�� GetCodeList()�Լ��� ������.
// {{ Code.ocx �� // }} Code.ocx ���� �����ִ� �κ��� ������ code.ocx������ 
�״�� ���ϴ� �κ����� �Ķ���ͳ� ��ɿ� ���ؼ��� code.ocx�����ڿ��� ���ǹٶ�.
------------------------------------------------------------------------- */

DECLARE_INTERFACE(IMasterDataManagerBase)
{
	STDMETHOD_(void, SetKeyData)(LPCSTR szKey, LPCSTR szData) PURE;
	STDMETHOD_(void, SetKeyData)(LPCSTR szKey, long   dwData) PURE;
};

DECLARE_INTERFACE_(IMasterDataManager, IMasterDataManagerBase)
{
	STDMETHOD_(BOOL, GetMasterData)(LPCSTR szMasterKey, CStringArray& arrCode, CStringArray& arrName) PURE;
	STDMETHOD_(BOOL, GetMasterDataEx)(stQueryMasterInfo* pInfo) PURE;

	STDMETHOD_(BOOL, GetOptionJongMst)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, 
		CStringArray *&pastrJongEngName, CStringArray *&pastrEventPrice, 
		CStringArray *&pastrFinalYM, CStringArray *&pastrValueGubun )	PURE;

	// Koscom ���������͵����� ���ϱ�
	STDMETHOD_(BOOL, GetFutureJongMst)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;

	// Koscom �ڽ��Ǿ��������͵����� ���ϱ�
	STDMETHOD_(BOOL, GetKSPUpMst)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName, int nOption=0) PURE;

	// Koscom �ڽ��ھ��������͸����͵����� ���ϱ�
	STDMETHOD_(BOOL, GetKSQUpMst)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName, int nOption=0) PURE;

	// �ؿ����� �����͵����� ���ϱ�
	STDMETHOD_(BOOL, GetFRMst)(CStringArray *&pastrCode, CStringArray *&pastrName) PURE;

	// �ؿܱ��� �����͵����� ���ϱ�
	STDMETHOD_(BOOL, GetFRNationMst)(CStringArray *&pastrCode, CStringArray *&pastrName) PURE;

	// ELW �����͵����� ���ϱ�
	STDMETHOD_(BOOL, GetELWMst)(CStringArray *&pastrCode, CStringArray *&pastrName) PURE;

	// �׷�� �����͵����� ���ϱ�
	STDMETHOD_(BOOL, GetGroupMst)(CStringArray *&pastrCode, CStringArray *&pastrName, int nOption=0) PURE;
	STDMETHOD_(BOOL, GetKRXUpMst)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName, int nOption=0) PURE;
	STDMETHOD_(CString, GetStockDetailInfo)(CString strCode, int nType) PURE;
	STDMETHOD_(CString, GetLastCode)(CString strMarketCode) PURE;

	// Koscom �ڽ��Ǿ��������͵����� ���ϱ�
	STDMETHOD_(BOOL, GetK200UpMst)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
	STDMETHOD_(BOOL, GetK100UpMst)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
	STDMETHOD_(BOOL, GetKSTRUpMst)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
	STDMETHOD_(BOOL, GetFREEUpMst)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName, int nOption=0) PURE;

	// �ؿ�
	STDMETHOD_(BOOL, GetForeignMst)(int nKind, CString strCode, CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetUSUPMaster)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetDow30Master)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetNasdaq100Master)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetSP500Master)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetCMEFutMaster)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetETCFutMaster)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetMoneyRateMaster)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetLiborRateMaster)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetADRMaster)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetGDRMaster)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetGovMaster)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetSemiMaster)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;
// 	STDMETHOD_(BOOL, GetChangeRateMaster)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName) PURE;

	// ����
	STDMETHOD_(int, GetGroupItemList)(LPCSTR szGroupName, CStringArray &arrCode, CStringArray &arrName) PURE;
};


//DECLARE_INTERFACE_(IMasterDataManager0712, IMasterDataManager)
DECLARE_INTERFACE_(IMasterDataManager080902, IMasterDataManager)
{
	enum
	{
		IMaster_Future=10,
		IMaster_Option,
	};

	// ����,�ɼ� �����ڵ� ����������� ��� Ȯ���� ���ؼ� ...
	// ����� ������ FALSE�̰� rszCode�� ���� �ֱٿ��� ����.
	// ������� ���������� TRUE�����ϰ� rszCode�� szCode�� �״�� �Ѱ���.
	STDMETHOD_(BOOL, GetRecentCode)(CString szCode, CString& rszCode, int nCodeType) PURE;

	STDMETHOD_(BOOL, GetMasterDataInUpDetails)(CString szType, CStringArray &arrCode, CStringArray &arrBuf, CString strUp) PURE;
	STDMETHOD_(BYTE, GetMarketTypeFromCode)(LPCSTR strCode) PURE;
	STDMETHOD_(BOOL, GetRecentCodeNameArray)(int nMarketType, CStringArray &arrCode, CStringArray &arrName) PURE;
	STDMETHOD_(BOOL, GetAllStock)(CStringArray &arrCode, CStringArray &arrName) PURE ;
	STDMETHOD_(BOOL, GetELWIndexMaster)(CStringArray &arrCode, CStringArray &arrName) PURE ;
	STDMETHOD_(BOOL, GetELWIssueMaster)(CStringArray &arrCode, CStringArray &arrName) PURE ;
	STDMETHOD_(BOOL, GetJFMaster)(CStringArray &arrCode, CStringArray &arrName) PURE;
	STDMETHOD_(BOOL, GetJPMaster)(CStringArray &arrCode, CStringArray &arrName) PURE;
	STDMETHOD_(BOOL, GetELWIndexCode)(CString strELWCode, CString& strIndexCode, CString& strIndexName) PURE;
	STDMETHOD_(CString, GetCodeName)(LPCTSTR lpszItemCode) PURE;
	STDMETHOD_(CString, GetItemExpCode)(LPCTSTR lpszCode) PURE;
	STDMETHOD_(BOOL, GetThemeGroup)(CStringArray& arCode, CStringArray& arName) PURE;
	STDMETHOD_(BOOL, GetThemeItemList)(LPCTSTR szThemeCode, CStringArray &arrCode, CStringArray &arrName) PURE;

	STDMETHOD_(BOOL, GetSiteUpKode)(LPCSTR szCode, CString& rCode);

 	STDMETHOD_(BOOL, GetStockCodeWithType)(int nType, CStringArray &arrCode, CStringArray &arrName) PURE ;			// 2008.11.11 -hidden	

	STDMETHOD_(BYTE, GetCodeTypeFromCode)(LPCSTR strCode)PURE;
	STDMETHOD_(BOOL, ADDCodeToDRList)(LPCSTR szCode, LPCSTR szCodeName, LONG reserved=0)PURE;

	// ex. usrMasterCondition
	STDMETHOD_(int , SetUserMaster)(LPCSTR szKey, int Count, CStringArray *pArrCode, CStringArray *pArrName) PURE;
	STDMETHOD_(int , GetUserMaster)(LPCSTR szKey, CStringArray &arrCode, CStringArray &arrName) PURE;

	// kospi200/etc
	STDMETHOD_(BOOL, GetKOSPI200ETC)(CStringArray *&pastrJongCode, CStringArray *&pastrJongName, CStringArray *&pastrJongEngName, int nOption=0) PURE;
};

// DECLARE_INTERFACE_(IMasterDataManager100330, IMasterDataManager080902)
// {
// 	STDMETHOD_(BOOL, GetChartTRCode)(LPCSTR szCode, CString &rString) PURE;
// 	STDMETHOD_(BOOL, GetChartTRCode)(int nMarketType, LPCSTR szExtraInfo, CString &rString) PURE;
// };

#define	USERINFOMNG_USERID			0
#define	USERINFOMNG_USERENCID		1
#define	USERINFOMNG_ROOTDIR			10
#define	USERINFOMNG_DATADIR			12
#define	USERINFOMNG_IMAGEDIR		13
#define	USERINFOMNG_USERDIR			14
#define	USERINFOMNG_REALUSERDIR		17

// --> UserMaster����
#define		usrMasterCondition		"SearchTemp"
#define		usrPowerThema		"PowerThemaTemp"
// <-- UserMaster����

#endif //AFX_INTERFACE_OF_MASTERDATAMANAGER_BY_JUNOK_LEE__INCLUDED_
