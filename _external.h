
//-> 2012.04.25 jhj ������������ ���� ��������,�Լ�����.

class _external
{
public:
	static BOOL			g_bTreadF;				// ü������ ����,������ Flag
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
