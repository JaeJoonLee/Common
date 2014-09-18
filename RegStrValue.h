
class	CRegistry
{
public :
	static	void 	SetStrValue(HKEY hMainKey,CString strKey,CString strSubKey,CString strKeyValue);
	static	CString GetStrValue(HKEY Hkey,CString strkey, CString strsubkey,CString strRValue);
};

