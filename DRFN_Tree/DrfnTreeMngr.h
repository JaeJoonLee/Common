#pragma once
#include "afxwin.h"

#include "inc/ITreeListMng.h"
#include "inc/PcTrMngHelper.h"
#include "../KwTreeDefine.h"

class CDrfnTreeMngr : public CTreeCtrl
{
public:
	CDrfnTreeMngr(void);
	~CDrfnTreeMngr(void);
public:
	BOOL	m_bLoadFlag;	// 트리를 로드 했는지
	HWND	m_hWndTree;
	long	m_lTreeKey;
	CPCTrMngHelper		m_ctrHelper;
	ITreeListManager2*	m_pTreeListMng;
public:
	BOOL	Init();
	long	LoadDrfnTree(TREETYPE_MAP TreeTypeMap, CString strSection, CString strNodeName,
								UINT nGroupKey);

	long	LoadDrfnTree(CTreeCtrl* pTree);
	void	UnloadDrfnTreeList();
	BOOL	RequestData(DRFN_TREE_INFO DrfnTreeInfo, HWND hWnd, ITLMCallback* pTLMCallback);

	void	SetNodeInfo(CTreeTypeInfo* pTreeInfoMap, HTREEITEM hItem, int nDepth,
						int nNodeKey, UINT nRootKey, UINT nParentKey);
};
