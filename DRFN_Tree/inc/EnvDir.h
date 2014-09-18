#if !defined(AFX_ENVIRONMENT_OF_DIR_H__DEAC0189__8C9176A965AA__INCLUDED_)
#define AFX_ENVIRONMENT_OF_DIR_H__DEAC0189__8C9176A965AA__INCLUDED_

// #include "../../../include/EnvDir.h"

// ���丮�� ���� �� PCTRMng�� �̿��� �� �� �ְ�, 
// ���� ���� �ִ� �� ��������� �̿��� �� �� �ִ�.
// PCTRMng���� ���������� �� ��������� �̿��ϰ� �ִ�.
//
// ����
// ��)	CString	strDataDir;
//		GET_DATA_DIR(strDataDir);		//�عݵ�� �������� ����Ұ�.
//		CString	strDataFile = strDataDir + "\\test.dat";
//
//
// ������  : ���ؿ� 2005.11.02(��)
// History : 2005.11.02 �������̽� ����
//

// ���������� �ִ� ���丮 : MainDirectory
#define	GET_ROOT_DIR(strDir)\
{\
	char _szBuf_[255];\
\
	::GetModuleFileName(NULL, _szBuf_, 255);\
	CString	_strRoot_ = _szBuf_;\
	int _loc_ = _strRoot_.ReverseFind('\\');\
	if( _loc_ > 0)\
		_strRoot_ = _strRoot_.Left(_loc_);\
	_loc_ = _strRoot_.ReverseFind('\\');\
	if( _loc_ > 0)\
		_strRoot_ = _strRoot_.Left(_loc_);\
\
	strDir = _strRoot_;\
}

// ����, DLL���� ��ġ�ϰ� �ִ� bin/binD ���丮.
// exe����� �ִ� ���丮��.
#define GET_MAIN_DIR(strDir)\
{\
	char _szBuf_[255];\
\
	::GetModuleFileName(NULL, _szBuf_, 255);\
	CString	_strMain_ = _szBuf_;\
	int _loc_ = _strMain_.ReverseFind('\\');\
	if( _loc_ > 0)\
		_strMain_ = _strMain_.Left(_loc_);\
	strDir = _strMain_;\
}

#define GET_CONFIG_DIR(strDir)\
{\
	CString	_strTmp_;\
	GET_ROOT_DIR(_strTmp_);\
	strDir = _strTmp_ + "\\Config";\
}

#define GET_DATA_DIR(strDir)\
{\
	CString	_strTmp_;\
	GET_ROOT_DIR(_strTmp_);\
	strDir = _strTmp_ + "\\Data";\
}

#define GET_USERS_DIR(strDir)\
{\
	CString	_strTmp_;\
	GET_ROOT_DIR(_strTmp_);\
	strDir = _strTmp_ + "\\User";\
}


#define GET_IMAGE_DIR(strDir)\
{\
	CString	_strTmp_;\
	GET_ROOT_DIR(_strTmp_);\
	strDir = _strTmp_ + "\\Image";\
}

#define GET_MEDIA_DIR(strDir)\
{\
	CString	_strTmp_;\
	GET_ROOT_DIR(_strTmp_);\
	strDir = _strTmp_ + "\\Media";\
}


#define GET_MAP_DIR(strDir)\
{\
	CString	_strTmp_;\
	GET_ROOT_DIR(_strTmp_);\
	strDir = _strTmp_ + "\\Map";\
}

#define GET_TEMP_DIR(strDir)\
{\
	CString	_strTmp_;\
	GET_ROOT_DIR(_strTmp_);\
	strDir = _strTmp_ + "\\Temp";\
}

#define GET_HELP_DIR(strDir)\
{\
	CString	_strTmp_;\
	GET_ROOT_DIR(_strTmp_);\
	strDir = _strTmp_ + "\\Help";\
}

#define GET_LOG_DIR(strDir)\
{\
	CString	_strTmp_;\
	GET_ROOT_DIR(_strTmp_);\
	strDir = _strTmp_ + "\\Log";\
}


#define	GET_MODULE_NAME(strName)\
{\
	char _szBuf_[255];\
	\
	::GetModuleFileName(NULL, _szBuf_, 255);\
	CString	_strRoot_ = _szBuf_;\
	int _loc_ = _strRoot_.ReverseFind('\\');\
	if( _loc_ > 0)\
	_strRoot_ = _strRoot_.Mid(_loc_+1);\
	_loc_ = _strRoot_.Find('.'); \
	if( _loc_ > 0)\
	_strRoot_ = _strRoot_.Left(_loc_);\
	strName = _strRoot_;\
}

#endif // AFX_ENVIRONMENT_OF_DIR_H__DEAC0189__8C9176A965AA__INCLUDED_

