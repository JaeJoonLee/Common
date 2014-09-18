#if !defined(AFX_ZLIBMNGR_H__B6DA075C_AB3C_46E8_9EE4_C495518111C4__INCLUDED_)
#define AFX_ZLIBMNGR_H__B6DA075C_AB3C_46E8_9EE4_C495518111C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZLIBMNGR.h : header file
//

//#include "ProgressbarDlg.h"
#include "ZipFile.h"	// zip���� Ǯ��

/////////////////////////////////////////////////////////////////////////////
// CZLibMngr window
class CProgressbarDlg;
class CZLibMngr : public CWnd
{
// Construction
public:
	CZLibMngr();

// Attributes
public:
	BOOL		m_bContinueStatus;
	CString		m_strContKey;
private:
    // ����� ���� ������ ����
//	CProgressbarDlg* m_pDlgSaveToServer;
	
// Operations
public:
	// ����� ���� ������ ����
	BOOL	SaveUsersDataToServer(int nOrder=0, BOOL bSendGubun = TRUE);
	BOOL	GetUsersDataFromServer(CString strUnZipFile = "");			// ����� ������ �������� �޾Ƽ� Ǭ��.

	BOOL	CompressDirctory(CZipFile* pZipFile, zip_fileinfo* pZipInfo,
							long* lTotalZipSize, CString sNewZipFilePath,
							CString sDirectory);
	CString Compress(CString UserId, int nGubun = 0);	// zip���� ����
	BOOL	Extract(CString UserId, CString strUnZipFile = _T(""));		// zip���� Ǯ��
	CString	GetZipDirectory( CString sFullPath, CString sNewZipFilePath );
	BOOL	MakeExtractDirectory( CString sFullPath  );
	BOOL	CompressFile( CString strZipFileFullName, CString strZipFileName );	//LJP 20110323 ���� �ϳ��� ����

//	BOOL	CreateProgressBar(BOOL bTrick=0);
//	BOOL	DestroyProgressBar();

//================================================================================================
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZLibMngr)
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CZLibMngr();

	// Generated message map functions
protected:
	//{{AFX_MSG(CZLibMngr)
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg void	OnDestroy();
	//}}AFX_MSG
	afx_msg long OnSendToServer(WPARAM wParam, LPARAM lParam);
//	afx_msg long OnDestroyProgressBar(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZLIBMNGR_H__B6DA075C_AB3C_46E8_9EE4_C495518111C4__INCLUDED_)
