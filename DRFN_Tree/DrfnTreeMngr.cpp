#include "StdAfx.h"
#include "DrfnTreeMngr.h"
#include "inc/ITreeListMng.h"
#include <math.h>
#include <stdio.h>


extern HINSTANCE	g_hInstance;

CDrfnTreeMngr::CDrfnTreeMngr()
{
	m_bLoadFlag = FALSE;
	m_hWndTree	= NULL;
	m_lTreeKey	= 0;
	m_pTreeListMng = NULL;
//	Init();
//	m_pTreeListMng = NULL;
//	m_lTreeKey     = NULL;
}

CDrfnTreeMngr::~CDrfnTreeMngr(void)
{
	if (m_hWndTree != NULL)
		::DestroyWindow(m_hWndTree);

//	UnloadDrfnTreeList(m_lTreeKey);
}

BOOL CDrfnTreeMngr::Init()
{
//	if (!Create(WS_OVERLAPPEDWINDOW, CRect(0, 0, 0, 0), NULL, 1212))
//		return FALSE;
/*
	// �������� Ʈ�� �Ѱ� ���� DRFN�� �����´�.
	m_hWndTree = CreateWindow("SysTreeView32",		// name of window class 
				NULL,					// title-bar string 
				WS_OVERLAPPEDWINDOW,	// top-level window 
				0,						// default horizontal position 
				0,						// default vertical position 
				0,						// default width 
				0,						// default height 
				(HWND)NULL,				// no owner window 
				(HMENU)NULL,			// use class menu 
				g_hInstance,			// handle to application instance 
				(LPVOID)NULL);			// no window-creation data 

*/

	return TRUE;
}

void CDrfnTreeMngr::UnloadDrfnTreeList()
{	
	if (m_pTreeListMng != NULL && m_lTreeKey > 0)
		m_pTreeListMng->UnLoadTreeList(m_lTreeKey);

	m_lTreeKey = 0;
}
//*//
long CDrfnTreeMngr::LoadDrfnTree(TREETYPE_MAP TreeTypeMap, CString strSection,
								 CString strNodeName, UINT nGroupKey)
{
	CInputCodeListEx inData;
	
	inData.m_pTreeCtrl	= this;
	inData.m_szSection	= strSection;

	/////////////////////// Ʈ���� �⺻ ��� �߰� ///////////////////////
	
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hItem;
	
	if (m_pTreeListMng == NULL)
		m_pTreeListMng = (ITreeListManager2*)m_ctrHelper.GetInferface(UUID_ITreeListManager2, 0);

	if (m_pTreeListMng == NULL)
		return 0;

	UnloadDrfnTreeList();
	DeleteAllItems();
	
	tvinsert.hParent			= NULL;
	tvinsert.hInsertAfter		= TVI_LAST;
	tvinsert.item.mask			= TVIF_TEXT;
	tvinsert.item.state			= 0;
	tvinsert.item.stateMask		= 0;
	tvinsert.item.cchTextMax	= 60;
	tvinsert.item.cChildren		= 0;
	tvinsert.item.pszText		= (LPTSTR)(LPCTSTR)strNodeName;

	hItem = InsertItem(&tvinsert);
	SetItemData(hItem, nGroupKey);
	
	m_lTreeKey = m_pTreeListMng->LoadTreeList(&inData, strNodeName);

	if (m_lTreeKey == 0)
		return 0;

	/////////////////////// Ʈ�� ���� ���� //////////////////////
	int nDepth;
	CTreeTypeInfo*	pTreeInfoMap;
	TREETYPE_MAP::iterator iter;
	TREEINFO_MAP::iterator iterMap;
	TREEINFO_MAP::iterator iterTemp;
	TREEINFO_MAP::iterator iterDelete;
	
	CTreeTypeInfo TreeInfoMapTemp;
	CDWordArray arrDelete;

	//////////////////// �ϴ� TEMP�� ���� /////////////////
	nDepth = 1;
	SetNodeInfo(&TreeInfoMapTemp, hItem, nDepth, nGroupKey, nGroupKey, 0);

	for (iter = TreeTypeMap.begin(); iter != TreeTypeMap.end(); iter++)
	{
		pTreeInfoMap = iter->second;
		// DRFN ��尡 �ִ��� Ȯ�� �Ѵ�.
		iterMap = pTreeInfoMap->m_TreeInfoMap.find(nGroupKey);
		if (iterMap == pTreeInfoMap->m_TreeInfoMap.end())
			continue;
		// ���� ������ DRFN �׸��� ������ ���� �Ѵ�.
		// ���� ����� ã�´�.
		for (iterTemp = pTreeInfoMap->m_TreeInfoMap.begin(); iterTemp != pTreeInfoMap->m_TreeInfoMap.end(); iterTemp++)
		{
			UINT nKey = iterTemp->first;

			// ��Ʈ�� �������� �ʴ´�.
			if (nKey == nGroupKey)
				continue;
			
			if (nKey / 1000000 == nGroupKey / 1000000)
				arrDelete.Add(nKey);
				
		}
		// �����Ѵ�.
		for (int i = 0; i < arrDelete.GetSize(); i++)
		{
			DWORD dwDelete = arrDelete.GetAt(i);

			iterDelete = pTreeInfoMap->m_TreeInfoMap.find(dwDelete);
			pTreeInfoMap->m_TreeInfoMap.erase(iterDelete);
		}

		for (iterTemp = TreeInfoMapTemp.m_TreeInfoMap.begin(); iterTemp != TreeInfoMapTemp.m_TreeInfoMap.end(); iterTemp++)
		{
			TREE_INFO* pTreeInfoTemp = iterTemp->second;
			TREE_INFO* pTreeInfo = new TREE_INFO;
		
			pTreeInfo->m_nKey			= pTreeInfoTemp->m_nKey;
			pTreeInfo->m_strName		= pTreeInfoTemp->m_strName;
			pTreeInfo->m_strMasterType	= pTreeInfoTemp->m_strMasterType;
			pTreeInfo->m_strMasterCode	= pTreeInfoTemp->m_strMasterCode;
			pTreeInfo->m_DrfnInfo.m_pITrComm		= pTreeInfoTemp->m_DrfnInfo.m_pITrComm;
			pTreeInfo->m_DrfnInfo.m_pITrcommSite	= pTreeInfoTemp->m_DrfnInfo.m_pITrcommSite;
			pTreeInfo->m_DrfnInfo.m_szOCPath		= pTreeInfoTemp->m_DrfnInfo.m_szOCPath;
	
			pTreeInfoMap->m_TreeInfoMap[pTreeInfo->m_nKey] = pTreeInfo;	
		}		
	}

	// TEMP �޸� ����
	for (iterTemp = TreeInfoMapTemp.m_TreeInfoMap.begin(); iterTemp != TreeInfoMapTemp.m_TreeInfoMap.end(); iterTemp++)
	{
		TREE_INFO* pTreeInfoTemp = iterTemp->second;
		delete pTreeInfoTemp;
	}	

	return m_lTreeKey;
}

void CDrfnTreeMngr::SetNodeInfo(CTreeTypeInfo* pTreeInfoMap, HTREEITEM hItem, int nDepth,
								int nNodeKey, UINT nRootKey, UINT nParentKey)
{
	int nDepthTemp = nDepth;
	int nNodeKeyTemp;
	DWORD dwNodeKeyNew;
	CString strTemp;

	if (hItem)
	{
		// ��Ʈ ���� ����
		if (nNodeKey != nRootKey)
		{
			// �ʿ� ���� ����
			CItemOneClickData* pInfo = (CItemOneClickData*)GetItemData(hItem);
			// ����� Ű�� ���� �����ؾ� �Ѵ�.
			dwNodeKeyNew = (DWORD)(nParentKey + nNodeKey * pow(1000.0, 3 - nDepth));
	
	//		strTemp = GetItemText(hParentItem) + "|" + GetItemText(hItem);
	//		TRACE("[���� : %s, hItem = %x, Depth = %d, NodeKey = %d, dwNodeKeyNew = %d]\n",
	//				strTemp, hItem, nDepth, nNodeKey, dwNodeKeyNew);
	
			TREE_INFO* pTreeInfo = new TREE_INFO;
		
			pTreeInfo->m_nKey		= dwNodeKeyNew;
			pTreeInfo->m_strName	= GetItemText(hItem);
			// �ڽ� ��尡 ������
			if (ItemHasChildren(hItem))
				pTreeInfo->m_strMasterType	= TREE_MASTER_TYPE_DRFN_GROUP;
			else
				pTreeInfo->m_strMasterType	= TREE_MASTER_TYPE_DRFN_CODE;
			pTreeInfo->m_strMasterCode	= TREE_MASTER_DRFN;
					
			if (pInfo != NULL)
			{
				pTreeInfo->m_DrfnInfo.m_pITrComm		= pInfo->m_pITrComm;
				pTreeInfo->m_DrfnInfo.m_pITrcommSite	= pInfo->m_pITrcommSite;
				pTreeInfo->m_DrfnInfo.m_szOCPath		= pInfo->m_szOCPath;
			}

			pTreeInfoMap->m_TreeInfoMap[pTreeInfo->m_nKey] = pTreeInfo;	
		}
		else
			dwNodeKeyNew = nNodeKey;

		//////////////////////////////////////////////// 
		HTREEITEM hChild = GetChildItem(hItem);

		nDepthTemp++;
		nNodeKeyTemp = 1;
		while (hChild)
		{
			SetNodeInfo(pTreeInfoMap, hChild, nDepthTemp, nNodeKeyTemp, nRootKey, dwNodeKeyNew);
			hChild = GetNextItem(hChild, TVGN_NEXT);
			nNodeKeyTemp++;
		}
	}
}
/*/
/*/
long CDrfnTreeMngr::LoadDrfnTree(CTreeCtrl* pTree)
{
	CInputCodeListEx inData;
	long lTreeKey = 0;
	inData.m_pTreeCtrl	= pTree;
	inData.m_szSection	= "ONECLICK";

	CPCTrMngHelper pctrHelper;
	m_pTreeListMng = (ITreeListManager2*)pctrHelper.GetInferface(UUID_ITreeListManager2, 0);
	if (m_pTreeListMng != NULL)
		lTreeKey = m_pTreeListMng->LoadTreeList(&inData, "����˻�");

	return lTreeKey;
}
//*/

BOOL CDrfnTreeMngr::RequestData(DRFN_TREE_INFO DrfnTreeInfo, HWND hWnd, ITLMCallback* pTLMCallback)
{	
	CItemOneClickData ItemData;
	ItemData.m_nType		= 1;
	ItemData.m_pITrComm		= DrfnTreeInfo.m_pITrComm;
	ItemData.m_pITrcommSite	= DrfnTreeInfo.m_pITrcommSite;
	ItemData.m_szOCPath		= DrfnTreeInfo.m_szOCPath;

	if (m_pTreeListMng)
	{
		m_pTreeListMng->RequestData(&ItemData, pTLMCallback, 'A', '1', (long)hWnd);
		return TRUE;
	}

	return FALSE;
}
