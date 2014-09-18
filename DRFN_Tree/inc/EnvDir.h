#if !defined(AFX_ENVIRONMENT_OF_DIR_H__DEAC0189__8C9176A965AA__INCLUDED_)
#define AFX_ENVIRONMENT_OF_DIR_H__DEAC0189__8C9176A965AA__INCLUDED_

// #include "../../../include/EnvDir.h"

// 디렉토리를 구할 때 PCTRMng를 이용할 수 도 있고, 
// 지금 보고 있는 이 헤더파일을 이용할 수 도 있다.
// PCTRMng에서 내부적으로 이 헤더파일을 이용하고 있다.
//
// 사용법
// 예)	CString	strDataDir;
//		GET_DATA_DIR(strDataDir);		//※반드시 단항으로 사용할것.
//		CString	strDataFile = strDataDir + "\\test.dat";
//
//
// 만든이  : 이준옥 2005.11.02(수)
// History : 2005.11.02 인터페이스 정의
//

// 실행파일이 있는 디렉토리 : MainDirectory
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

// 메인, DLL등이 위치하고 있는 bin/binD 디렉토리.
// exe모듈이 있는 디렉토리임.
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

