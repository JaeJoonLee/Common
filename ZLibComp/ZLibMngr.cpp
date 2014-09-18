//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : ZLibMngr.cpp
//  Function      : 
//  System Name   : RegKwansim
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************


// ZLibMngr.cpp : implementation file
//

#include "stdafx.h"
#include "ZLibMngr.h"
#include "..\..\Builder\LinkInfoMng\KSLinkInfoMng.h"
//#include "ProgressbarDlg.h"
#include <afxpriv.h>
#include "UnZipFile.h"	// zip에서 풀기

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_SAVETOSERVER			WM_USER + 1001
#define ZIP_FILE				".Zip"
#define USER_DIR2				"User"

// 파일 서버로 올리기
int g_nSendingCount				= 0;
int g_nTotalCount				= 0;
BOOL g_bCanceledSaveToServer	= FALSE;

/////////////////////////////////////////////////////////////////////////////
// CZLibMngr

//******************************************************************
//  Function Name : CZLibMngr
//  Function      : 생성자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CZLibMngr::CZLibMngr()
{
	// 파일 서버로 저장
//	m_pDlgSaveToServer = NULL;
	m_bContinueStatus = FALSE;
	m_strContKey	= "";	
}

//******************************************************************
//  Function Name : ~CZLibMngr
//  Function      : 소멸자
//  Param         : 없음
//  Return        : 없음
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CZLibMngr::~CZLibMngr()
{
	
}


BEGIN_MESSAGE_MAP(CZLibMngr, CWnd)
	//{{AFX_MSG_MAP(CZLibMngr)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SAVETOSERVER,			OnSendToServer)			// 서버로 사용자 파일을 올린다.
//	ON_MESSAGE(WM_DESTROY_PROGRESSBAR,	OnDestroyProgressBar)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CZLibMngr message handlers

//******************************************************************
//  Function Name : OnCreate
//  Function      : 
//  Param         : LPCREATESTRUCT lpCreateStruct
//  Return        : int 
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int CZLibMngr::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

//******************************************************************
//  Function Name : OnSize
//  Function      : 
//  Param         : UINT nType, int cx, int cy
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CZLibMngr::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
}

//******************************************************************
//  Function Name : OnEraseBkgnd
//  Function      : 
//  Param         : CDC* pDC
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CZLibMngr::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CWnd::OnEraseBkgnd(pDC);
	return TRUE;
}

//******************************************************************
//  Function Name : SaveUsersDataToServer
//  Function      : 관심파일을 서버로 저장
//  Param         : int nOrder, BOOL bSendGubun/* = TRUE*/
//  Return        : BOOL 
//  Create        : 정미란 , 2006/12/19
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CZLibMngr::SaveUsersDataToServer(int nOrder, BOOL bSendGubun/* = TRUE*/)
{
	if (bSendGubun)
		PostMessage( WM_SAVETOSERVER, (long)nOrder, 0L );
	else
		SendMessage( WM_SAVETOSERVER, (long)nOrder, 0L );

	return TRUE;
}

//******************************************************************
//  Function Name : OnSendToServer
//  Function      : 
//  Param         : WPARAM wParam, LPARAM lParam
//  Return        : long 
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
long CZLibMngr::OnSendToServer(WPARAM wParam, LPARAM lParam)
{
	int nOrder = (int)wParam;
	if( nOrder < 0 )
		return 0L;

	g_nSendingCount = 0;
	g_nTotalCount = 0;
	g_bCanceledSaveToServer = FALSE;

	CString sCompressUserId(""), sUserId("");	
	sCompressUserId = KSLink_GetFileHeader();

	if( sCompressUserId.GetLength() <= 0 )
		return FALSE;

	sUserId = KSLink_GetLoginInfo( "USER_ID" );
	if( sUserId.GetLength() <= 0 )
		return FALSE;

	// 관심 종목 저장파일을 점검한다.
	Compress(sCompressUserId, (int)wParam);

//	g_sUserDataZipFile = Compress(sCompressUserId, (int)wParam);

	return 0L;
}

//******************************************************************
//  Function Name : GetUsersDataFromServer
//  Function      : 관심그룹을 서버에서 받아서 관심종목파일로 저장
//  Param         : 없음
//  Return        : BOOL 
//  Create        : 정미란 , 2006/12/19
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CZLibMngr::GetUsersDataFromServer(CString strUnZipFile)
{
	CString sCompressUserId("");
	sCompressUserId = KSLink_GetFileHeader();
	if (sCompressUserId.GetLength() <= 0)
		return FALSE;

	CString sUserId("");	
	sUserId = KSLink_GetLoginInfo( "USER_ID" );
	if( sUserId.GetLength() <= 0 )
		return FALSE;

	// 관심 종목 저장파일을 점검한다.
	CString sUserDataZipFile( _T(""));
	sUserDataZipFile = sCompressUserId + ZIP_FILE;
	if( sUserDataZipFile.GetLength() <= 0 )
		return FALSE;

//	g_sUserDataZipFile = _T("");
//	g_sUserDataZipFile = Extract(sCompressUserId, strUnZipFile);
//	g_sUserDataZipFile.TrimRight();
//	if (g_sUserDataZipFile == _T(""))
//		return FALSE;

	return Extract(sCompressUserId, strUnZipFile);
}
//******************************************************************
//  Function Name : Compress
//  Function      : 
//  Param         : CString sCompressUserId, int nGubun
//  Return        : CString 
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CString CZLibMngr::Compress(CString sCompressUserId, int nGubun)
{
	CString strRunTimePath;
	CString sNewZipFilePath( _T("") ), 
	sNewZipFileName( _T("") ), 
	sUserDirPath( _T("") ), 
	sFilePath( _T("") ),
	sFileName( _T("") );
	long lTotalZipSize = 0;

	strRunTimePath = GetRunTimePath();

	TRY
	{
		sNewZipFilePath.Format( _T("%s\\%s\\%s\\"), strRunTimePath, USER_DIR2, sCompressUserId );

		if (nGubun == 0)
		{
			// [20080528] 암호화 된 파일이 아닌 사용자 ID로 압축파일을 만든다.
			//	sNewZipFileName.Format( _T("%s%sEU_%s.Zip"), g_szRunTimePath, USER_DIR, sCompressUserId );
			sNewZipFileName.Format( _T("%s%s%s.Zip"), strRunTimePath, "\\user\\", KSLink_GetLoginInfo( "USER_ID" ) );
		}
		else
		{
			CString	szDate;
			CTime	t = CTime::GetCurrentTime();
			szDate.Format("%04d%02d%02d", t.GetYear(), t.GetMonth(), t.GetDay());

			//sNewZipFileName.Format( _T("%s%sEU%s%s.Zip"), g_szRunTimePath, USER_DIR, sCompressUserId, szDate );
			sNewZipFileName.Format( _T("%s%sEU%s%s.Zip"), strRunTimePath, "\\user\\", KSLink_GetLoginInfo("USER_ID"), szDate );
		}

		sUserDirPath = sNewZipFilePath +  _T("*.*");
		
		// 압축한다.
		// 새 압축파일 경로를 지정한다.
		CZipFile zipFile( sNewZipFileName, 0 );
		zip_fileinfo zipInfo;  

		CompressDirctory( &zipFile, &zipInfo,&lTotalZipSize, sNewZipFilePath, sUserDirPath );

		zipFile.Close(); 
		
	}
	CATCH(CFileException, pEx)
	{
		pEx->ReportError();
		return _T("");
	}
	AND_CATCH(CMemoryException, pEx)
	{
		AfxAbort();
		return _T("");
	}
	END_CATCH
		
	if( lTotalZipSize <= 0 )
	{
		MessageBox( _T("저장할 사용자 정보 파일의 내용이 없습니다.") );
		return _T("");
	}
///#endif // #ifdef _SERVERSAVEENV_

	return sNewZipFileName;
}
BOOL CZLibMngr::CompressDirctory( CZipFile* pZipFile, 
									zip_fileinfo* pZipInfo, 
									long* lTotalZipSize, 
									CString sNewZipFilePath, 
									CString sDirectory )
{
	TRY
	{
		CString sUserDirPath( _T("") ), 
			sFilePath( _T("") ),
			sFileName( _T("") );

		// 각 파일을 압축한다.
		//int nError = 0, nMaxData = MAX_PACKETSIZE, nReadSize = 0;
		int nError = 0, nMaxData = (1024*10), nReadSize = 0;
		long lTotalReadSize = 0, lFileSize = 0;
		char szBuf[(1024*10)];
		CFile file;

		CFileFind fileFind;
		BOOL bNext = fileFind.FindFile( sDirectory );
		while( bNext )
		{
			bNext = fileFind.FindNextFile();
			
			// 파일이 있는지 살핀다.
			sFilePath = fileFind.GetFilePath();
			if( sFilePath.GetLength() == 0 )
				continue;
			
			if( fileFind.IsDots() ) 
				continue;

			if( fileFind.IsDirectory() ) 
			{
				sUserDirPath = sFilePath +  _T("\\*.*");
				CompressDirctory( pZipFile, pZipInfo, lTotalZipSize, sNewZipFilePath, sUserDirPath );
				continue;
			}
			
			if( !file.Open( sFilePath, CFile::modeRead|CFile::shareDenyNone ) )
				continue;
			
			lTotalReadSize = 0;
			lFileSize = (long)fileFind.GetLength();
			sFileName = fileFind.GetFileName();
			
			// 파일 정보를 zip info로 옮기고 	
			pZipFile->UpdateZipInfo( *pZipInfo, file );
			
			// zip info를 .zip로 옮기고 	
			// USER_DIR/userid변경 폴더 아래 경로+화일명을 쓴다.
			sFileName = GetZipDirectory( sFilePath, sNewZipFilePath );
			if( !sFileName.GetLength() )
				continue;
			pZipFile->OpenNewFileInZip( sFileName, *pZipInfo, Z_BEST_COMPRESSION ); 
			
			//AfxMessageBox( sFilePath );
			// 파일을 열어 데이터를 넣는다.
			memset( szBuf, 0x00, nMaxData );
			do
			{		
				nReadSize = file.Read( szBuf, nMaxData );    
				if( nReadSize )
				{
					pZipFile->WriteInFileInZip( szBuf, nReadSize );//압축 쓰기 	
					int nLength = (int)pZipFile->zi.filezip.GetLength();
				}
				lTotalReadSize += nReadSize;
				
			}while( lTotalReadSize < lFileSize );
			
			*lTotalZipSize += lTotalReadSize;
			
			file.Close();
		}
	}
	CATCH(CFileException, pEx)
	{
		pEx->ReportError();
		return FALSE;
	}
	AND_CATCH(CMemoryException, pEx)
	{
		AfxAbort();
		return FALSE;
	}
	END_CATCH
		
	return TRUE;
}

BOOL CZLibMngr::CompressFile( CString strZipFileFullName, CString strZipFileName )
{
	TRY
	{
		CString sUserDirPath( _T("") ), 
			sFilePath( _T("") ),
			sFileName( _T("") ),
			strZipName(_T("") );

		// 각 파일을 압축한다.
		//int nError = 0, nMaxData = MAX_PACKETSIZE, nReadSize = 0;
		int nError = 0, nMaxData = (1024*10), nReadSize = 0;
		long lTotalReadSize = 0, lFileSize = 0, lTotalZipSize = 0;
		char szBuf[(1024*10)];
		CFile file;
		
		strZipName.Format("%s.gz", strZipFileFullName);
		CZipFile zipFile( strZipName, 0 );
		zip_fileinfo ZipInfo; 

		if( !file.Open( strZipFileFullName, CFile::modeRead|CFile::shareDenyNone ) )
			return FALSE;
		
		lFileSize = file.GetLength();
		// 파일 정보를 zip info로 옮기고 	
		zipFile.UpdateZipInfo( ZipInfo, file );
		
//		sFileName = GetZipDirectory( sNewZipFileName, sNewZipFileName );
//		if( !sFileName.GetLength() )
//			return FALSE;
		zipFile.OpenNewFileInZip( strZipFileName, ZipInfo, Z_BEST_COMPRESSION ); 

		//AfxMessageBox( sFilePath );
		// 파일을 열어 데이터를 넣는다.
		memset( szBuf, 0x00, nMaxData );
		do
		{		
			nReadSize = file.Read( szBuf, nMaxData );    
			if( nReadSize )
			{
				zipFile.WriteInFileInZip( szBuf, nReadSize );//압축 쓰기 	
				int nLength = (int)zipFile.zi.filezip.GetLength();
			}
			lTotalReadSize += nReadSize;

		}while( lTotalReadSize < lFileSize );

//		lTotalZipSize += lTotalReadSize;

		file.Close();
		zipFile.Close(); 
	}
	CATCH(CFileException, pEx)
	{
		pEx->ReportError();
		return FALSE;
	}
	AND_CATCH(CMemoryException, pEx)
	{
		AfxAbort();
		return FALSE;
	}
	END_CATCH

		return TRUE;
}

//******************************************************************
//  Function Name : GetZipDirectory
//  Function      : zip으로 올릴때 user directory  이후 경로를 얻는다.
//  Param         : CString sFullPath, CString sNewZipFilePath 
//  Return        : CString 
//  Create        : 정미란 , 2007/01/23
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
CString CZLibMngr::GetZipDirectory( CString sFullPath, CString sNewZipFilePath )
{
	CString sZipPath(  _T("") );
	
	int nFind = sFullPath.Find( sNewZipFilePath );

	// 디렉토리가 있으면
 	if( nFind == 0 )
		sZipPath = sFullPath.Mid( sNewZipFilePath.GetLength() );
	
	return sZipPath;
}


//******************************************************************
//  Function Name : MakeExtractDirectory
//  Function      : zip을 풀때 user directory 이후 directory를 만든다.
//  Param         : CString sFullPath  
//  Return        : BOOL 
//  Create        : 홍길동 , 2007/01/23 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CZLibMngr::MakeExtractDirectory( CString sFullPath  )
{
	int nFind = sFullPath.ReverseFind( '\\' );

	// 디렉토리가 있으면
 	if( nFind <= 0 )
		return FALSE;

	CString sExtractPath(  _T("") );
	sExtractPath = sFullPath.Left( nFind );

	// user id에 해당하는 dir을 만든다.
	if( !::CreateDirectory( sExtractPath, NULL ) )
	{
		LONG dwErrCode = ::GetLastError();
		if( dwErrCode != ERROR_ALREADY_EXISTS )
			return FALSE;
	}

	return TRUE;
}

///#ifdef _SERVERSAVEENV_

//******************************************************************
//  Function Name : Extract
//  Function      : 
//  Param         : CString sCompressUserId, CString strUnZipFile
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
BOOL CZLibMngr::Extract(CString sCompressUserId, CString strUnZipFile)
{
	CString strRunTimePath;
	CString sUnZipFilePath( _T("") ), 
	sUnZipFileName( _T("") ), 
	sUserDirPath( _T("") ), 
	sFilePath( _T("") ),
	sFileName( _T("") );

	strRunTimePath = GetRunTimePath();
	
	TRY
	{
		sUnZipFilePath.Format( _T("%s%s%s\\"), strRunTimePath, "\\user\\", sCompressUserId );
		// sUnZipFileName.Format( _T("%s%sEUZIP.Zip"), g_szRunTimePath, USER_DIR );

		if (strUnZipFile.IsEmpty())
		{
			// [20080528] 암호화 된 파일이 아닌 사용자 ID로 압축파일을 만든다.
			// sUnZipFileName.Format( _T("%s%sEU_%s.Zip"), g_szRunTimePath, USER_DIR, sCompressUserId );
			sUnZipFileName.Format( _T("%s%s%s.Zip"), strRunTimePath, "\\user\\", KSLink_GetLoginInfo( "USER_ID" ) );
		}
		else
			sUnZipFileName.Format( _T("%s"), strUnZipFile );
		
		sUserDirPath = sUnZipFilePath +  _T("*.*");
		
		// user id에 해당하는 dir을 만든다.
		if( !::CreateDirectory( sUnZipFilePath, NULL ) )
		{
			LONG dwErrCode = ::GetLastError();
			if( dwErrCode != ERROR_ALREADY_EXISTS )
			{
				CString sMessage( _T("") );
				sMessage.Format( _T("디렉토리를 만드는데 실패했습니다.\n Error = %d"), dwErrCode );
				MessageBox( sMessage );
				return FALSE;
			}
		}
		
		// 해제할 파일을 설정한다.
		CUnzipFile unzipFile( sUnZipFileName );
		
		//처음 파일을 받는다.
		unzipFile.GoToFirstFile(); 
		unz_file_info unzipInfo;
		
		// 총갯수를 받는다.
		int nFileCount  = unzipFile.uf.gi.number_entry;
		
		// 압축을 푼다.
		//int nMaxData = MAX_PACKETSIZE;
		int nMaxData = (1024 * 10);
		//char szBuf[MAX_PACKETSIZE];
		char szBuf[(1024 * 10)];
		int nReadSize = 0;
		long lTotalReadSize = 0;
		long lFileSize = 0;
		CFile file;
		do
		{
			// 잠시 파일이름을 담는다.
			memset( szBuf, 0x00, nMaxData );
			
			unzipFile.GetCurrentFileInfo( &unzipInfo );
			unzipFile.GetCurrentFileInfo( NULL, szBuf, unzipInfo.size_filename );
			szBuf[unzipInfo.size_filename] = 0;
			
			sFileName = CString( szBuf );
			lFileSize = unzipFile.uf.byte_before_the_zipfile;
			sFilePath = sUnZipFilePath + sFileName;

			// 이전 파일을 지운다.
			DeleteFile( sFilePath );
			
			// 디렉토리를 점검한다.
			if( !MakeExtractDirectory( sFilePath ) )
				continue;

			if( !file.Open( sFilePath, CFile::modeWrite|CFile::modeCreate|CFile::modeNoTruncate|CFile::shareDenyWrite) )
				continue;
			
			// zip 파일을 연다.
			unzipFile.OpenCurrentFile();
			
			// 파일 사이즈를 가진다.
			lFileSize = unzipInfo.uncompressed_size;
			
			memset( szBuf, 0x00, nMaxData );
			lTotalReadSize = 0;
			do
			{		
				nReadSize = unzipFile.ReadCurrentFile( szBuf, nMaxData );
				if( nReadSize > 0 )
					file.Write( szBuf, nReadSize );
				
				lTotalReadSize += nReadSize;
				
			} while( lTotalReadSize < lFileSize );
			
			unzipFile.UpdateFileStatus( file, unzipInfo );
			//file.Close();
		}
		while( unzipFile.GoToNextFile() );
		
		unzipFile.Close(); 
	}
	CATCH(CFileException, pEx)
	{
		pEx->ReportError();
		return FALSE;
	}
	AND_CATCH(CMemoryException, pEx)
	{
		AfxAbort();
		return FALSE;
	}
	END_CATCH
	return TRUE;
}

///#endif

//******************************************************************
//  Function Name : OnDestroy
//  Function      : 
//  Param         : 없음
//  Return        : void 
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void CZLibMngr::OnDestroy() 
{
	g_bCanceledSaveToServer = TRUE;
	g_nSendingCount = 0;
	g_nTotalCount = 0;

//	DestroyProgressBar();

	CWnd::OnDestroy();
}



//******************************************************************
//  Function Name : CreateProgressBar
//  Function      : 
//  Param         : BOOL bTrick
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
/*
BOOL CZLibMngr::CreateProgressBar(BOOL bTrick)
{
	if( m_pDlgSaveToServer == NULL )
		m_pDlgSaveToServer = new CProgressbarDlg(this);
	m_pDlgSaveToServer->Init( 0, g_nTotalCount, g_nSendingCount );
	if( m_pDlgSaveToServer->GetSafeHwnd() == NULL )
		m_pDlgSaveToServer->Create( IDD_PROGRESSBAR_DLG );

	CWnd* pMain = AfxGetMainWnd();
	if( pMain )
	{
		BOOL bReturn = pMain->IsWindowEnabled();
		if( bReturn )
			bReturn = pMain->EnableWindow(FALSE);
	}
	return TRUE;
}
*/
//******************************************************************
//  Function Name : OnDestroyProgressBar
//  Function      : 
//  Param         : WPARAM wParam, LPARAM lParam
//  Return        : long 
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
/*
long CZLibMngr::OnDestroyProgressBar(WPARAM wParam, LPARAM lParam)
{
	g_bCanceledSaveToServer = TRUE;
	DestroyProgressBar();
	
	MessageBox( _T("파일 서버로 저장이 취소되었습니다" ) );

	return 0L;
}
*/
//******************************************************************
//  Function Name : DestroyProgressBar
//  Function      : 
//  Param         : 없음
//  Return        : BOOL 
//  Create        : 
//  Update        : 김정문, 2009/09/30 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
/*
BOOL CZLibMngr::DestroyProgressBar()
{
	CWnd* pMain = AfxGetMainWnd();
	if( pMain )
	{
		BOOL bReturn = pMain->EnableWindow(TRUE);
//		SetCursor(LoadCursor(NULL, IDC_UPARROW));
	}

	if( m_pDlgSaveToServer  )
	{
		m_pDlgSaveToServer->SetParentWindow( NULL );
		delete m_pDlgSaveToServer;
		m_pDlgSaveToServer = NULL ;
	}

	return TRUE;
}
*/
