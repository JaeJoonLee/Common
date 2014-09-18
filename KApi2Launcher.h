// KDefenseLancher.h: interface for the CKDefenseLancher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KDEFENSELANCHER_H__B0FF70DD_7626_46CD_9B3C_E710D827437C__INCLUDED_)
#define AFX_KDEFENSELANCHER_H__B0FF70DD_7626_46CD_9B3C_E710D827437C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// kdfAddEditCtrl�� ����ϰ� ������ �� �ڸ�Ʈ�� Ȱ��ȭ
#define USE_KDFADDEDITCRTL

//kdfExOption nType
#define KDFINJ_EXTYPE_KDFMOD_OPT		21		// Ư������ ��ȣ (GetMessage���� ��ȣȭ)

#define KDFINJ_EXTYPE_OPTIONEX2			22		// EX2 Ȯ�� �ɼ�
// EX2 Ȯ�� �ɼ�
#define KDFINJ_OPTIONEX2_GENTLEDRIVER		0x00000010	// Ÿ�� Ű���� ���� �浹��, ��ȣ ����
#define KDFINJ_OPTIONEX2_KDFMGR_OPT			0x00000020	// Ư������ ��ȣ2 (ó������ ��ȣȭ����)
#define KDFINJ_OPTIONEX2_GAMESENDINPUT		0x00000040	// ��ǥ�� ��ȯ �ɼ� (���Ӻ�ȣ���α׷����� �浹 ȸ��)
// EX2 Ȯ�� �ɼ�

#define KDFINJ_EXTYPE_SUBCLASSING		23		// Subclassing �߰� ���

#define KDFINJ_EXTYPE_BYPASS_STR		24		// ����Ű - ���� ���ڿ� ����
#define KDFINJ_EXTYPE_CHECK_INKEY		25		// ��ȣ ���/���� ���� �˻� return: 1-�ӽð�, 0-������

#define KDFINJ_EXTYPE_DEFAULTSUBCLASS	27		// ����Ŭ���� ���� ���

#define KDFINJ_EXTYPE_PROTECT_HANNUM	31		// �ѱ۸���� �� ���� �Է� ��ȣ


typedef BOOL	(*kdfAutoStart_t)		(char *pClassList, BOOL bExtend, int nOption);

//--> 2011.09.14 jhj ThreadID �߰�
typedef BOOL	(*kdfAutoStart_h)		(char *pClassList, BOOL bExtend, int nOption, DWORD dwThreadID);
//<--

typedef void	(*kdfAutoStartClean_t)	(void);
typedef DWORD	(*kdfGetVersion_t)		(void);
// Ư���� ��쿡 ��� typedef DWORD	(*kdfGetVersion_t)		(BOOL bApi = TRUE);
typedef void	(*kdfSetImageDir_t)		(char *pImageDir);
typedef DWORD	(*kdfSelfCheckIntegrity_t)(void *pParam1, void *pParam2, void *pParam3);
typedef BOOL	(*kdfProtectModeOn_t)	(void);
typedef BOOL	(*kdfProtectModeCheck_t)(void);

typedef DWORD	(*kdfExOption_t)(int nType, char *pOption1, char *pOption2, char *pOption3);	//NEW060224

#ifdef USE_KDFADDEDITCRTL
typedef BOOL	(*kdfAddEditCtrl_t)(HWND hWnd, HWND hWnd_main);
typedef void	(*kdfDelEditCtrl_t)(HWND hWnd);
typedef int		(*kdfGetPassword_t)(HWND hWnd, char *pRetBuf, int nRetBufSize);
typedef int		(*kdfSetPassword_t)(HWND hWnd, char *pRetBuf, int nRetBufSize);
#endif


class CKApi2Launcher  
{
public:
	CKApi2Launcher();
	virtual		~CKApi2Launcher();

private:
	bool		m_bStart;
	HMODULE		m_hDll;

	kdfAutoStart_t			m_lpkdfAutoStart;
	
	//--> 2011.09.14 jhj ThreadID �߰�
	kdfAutoStart_h			m_lpkdfAutoStart_h;
	//<--

	kdfGetVersion_t			m_lpkdfGetVersion;
	kdfProtectModeOn_t		m_lpkdfProtectModeOn;
	kdfProtectModeCheck_t	m_lpkdfProtectModeCheck;
	kdfSelfCheckIntegrity_t	m_lpkdfSelfCheckIntegrity;

	kdfSetImageDir_t		m_lpkdfSetImageDir;

	
public:
	kdfExOption_t			m_lpkdfExOption;
	kdfAddEditCtrl_t		m_lpkdfAddEditCtrl;
	kdfDelEditCtrl_t		m_lpkdfDelEditCtrl;
	kdfGetPassword_t		m_lpkdfGetPassword;
	kdfSetPassword_t		m_lpkdfSetPassword;

public:
	bool	kdfAutoStart(CString strRoot = _T(""));

	//--> 2011.09.14 jhj ThreadID �߰�
	bool	kdfAutoStartH(CString strRoot = _T(""), DWORD dwThreadID = 0x00);
	//<--

	bool	kdfAutoStartClean();

	int		kdfGetPassword(HWND hWnd, char *pRetBuf, int nRetBufSize);
	void	kdfAddEditCtrl(HWND hWnd, HWND hWnd_main);
	int		kdfExOption(int nType, char *pOption1, char *pOption2, char *pOption3);	// 2011.05 jhj 
	int		kdfSetPassword(HWND hWnd, char *pRetBuf, int nRetBufSize); // 2011.08 jhj

private:
	bool	loadKdfLibrary();
	void	freeKdfLibrary();
};

#endif // !defined(AFX_KDEFENSELANCHER_H__B0FF70DD_7626_46CD_9B3C_E710D827437C__INCLUDED_)
