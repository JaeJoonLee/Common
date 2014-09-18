
//-> 2012.04.25 jhj 오류개선사항 관련 전역변수,함수모음.

class _external
{
public:
	static BOOL			g_bTreadF;				// 체결추이 적용,비적용 Flag
	static CString		g_sCommUFNM;
	static CString		g_sTreadFNM;

	static void			__getReadFromEnvFile();
	static void			__setTreadFToFile(CString sTrCode,BOOL bTread);
	static BOOL			__isTreadTRCode(CString sTrCode);
	static CString		__getVolumeName(CString sTrCode);
	static int			__getTreadFlag(CString sTrCode);

public:
	_external(void);
	~_external(void);
};
