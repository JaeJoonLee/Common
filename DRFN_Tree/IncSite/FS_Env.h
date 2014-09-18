#if !defined(AFX_FOR_SITE_ENVIRONMENT_HEADER__8C9176A965AA__INCLUDED_)
#define AFX_FOR_SITE_ENVIRONMENT_HEADER__8C9176A965AA__INCLUDED_

// -----------------------------------------------------------------
//���⿡ ���ǵ� ������ ����Ʈ�� �°� ������ �κ��Դϴ�.
// -----------------------------------------------------------------
// #include "FS_Env.h"

#include "./DefineForSite.h"

#define		gRootStep		0
// -----------------------------------------------------------------
//		Directory����.
// -----------------------------------------------------------------
inline void GetDir_GetModuleFileName(CString& rString)
{
	char szBuf[255];
	::GetModuleFileName(NULL, szBuf, 255);
	rString = szBuf;
}

// DRFN���忡�� Root Directory
inline void GetDir_DrfnRoot(CString& rString)
{
	CString	_strRoot_;
	GetDir_GetModuleFileName(_strRoot_);

	int _loc_ = _strRoot_.ReverseFind('\\');
	if( _loc_ > 0)
		_strRoot_ = _strRoot_.Left(_loc_);
	if(gRootStep==1)
	{
		_loc_ = _strRoot_.ReverseFind('\\');
		if( _loc_ > 0)
			_strRoot_ = _strRoot_.Left(_loc_);
	}
	rString = _strRoot_;
}

// DRFN���忡�� HTS������ Directory
inline void GetDir_DrfnMainExe(CString& rString)
{
	GetDir_DrfnRoot(rString);

	//@NH-100208 rString += "\\Exe";
}

// Chart���� DRFN���� bin Directory��Ȱ�� �ϴ� ���丮
inline void GetDir_DrfnBin(CString& rString)
{
	GetDir_DrfnRoot(rString);

	//rString += "\\Dev";
	rString += gDrfnBin2;	//@NH-100208
}

// Chart���� DRFN���� Data Directory��Ȱ�� �ϴ� ���丮
inline void GetDir_DrfnData(CString& rString)
{
	GetDir_DrfnRoot(rString);
	
	rString += gDrfnData2;
}

// Chart���� DRFN���� Data Directory��Ȱ�� �ϴ� ���丮
inline void GetDir_DrfnImage(CString& rString)
{
	GetDir_DrfnRoot(rString);

	rString += gDrfnData2;
	rString += "\\Image";
}

#endif // AFX_FOR_SITE_ENVIRONMENT_HEADER__8C9176A965AA__INCLUDED_

