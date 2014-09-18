
#ifndef	__IniFiles_h
#define	__IniFiles_h

class	CIniFiles
{
public :
	CStringArray	val;

	CIniFiles(CString strFileName, CString strSection="Section")
	{
		m_strFileName = strFileName;
		m_strSection = strSection;
	};
	// key=value 형태로 된 입력을 name 과 value 로 나눠준다.
	static	int	Parse(const char *in, CString *name, CString *value)
	{
		int		n;
		char	szkey[512], szvalue[1024];
		szkey[0] = szvalue[0] = 0x00;
		n = sscanf(in, "%[^=]=%[^\n]", szkey, szvalue);
		*name = szkey;
		*value = szvalue;
		return n;
	};
	// 값에 'key = ' 이라고 쓰지 말것!!! 꼭 "key=" 이라고 쓰도록..
	const CString	Value(const char *key)
	{
		int		i;
		char	szkey[512], szvalue[1024];
		for (i = 0; i < val.GetSize(); i ++)
		{
			int nItem = sscanf(val[i], "%[^=]=%s", szkey, szvalue);
			if (strcmp(key, szkey) == 0)
			{
				if (nItem == 1)
				{
					return CString("");
				}
				else
					return CString(szvalue);
			}
		}
		return CString("");
	};
	const CString	Value(int nIdx)
	{
		char	szkey[512], szvalue[512];
		int		nItem = sscanf(val[nIdx], "%[^=]=%[^\n]", szkey, szvalue);
		if (nItem == 1)
			return CString("");
		return CString(szvalue);
	};

	void	ReadSection(void)
	{
		ReadSection(m_strSection);
	};
	void	ReadSection(CString strSection)
	{
		m_strSection = strSection;

		int		i, nRead;
		char	buf[65535], *ptr;
		ptr = buf;
		// win95/98 에서는 최대 32767 이란다  (32k)
		val.RemoveAll();
		nRead = ::GetPrivateProfileSection(m_strSection, buf, 32767, m_strFileName);
		buf[nRead] = 0x00;

		for (i = 0; i < nRead;)
		{
			val.Add(ptr);
			i += strlen(ptr) + 1;
			ptr += strlen(ptr) + 1;
		}
	};
	// 파일의 내용만 지우고.. 실제값은 지우지 않는다.
	// 값을 지우고 싶은 경우에는 val.RemoveAll() 을 사용한다.
	void	Clear(void)
	{
		int		i;
		for (i = 0; i < val.GetSize(); i ++)
		{
			char	key[512];
			sscanf(val[i], "%[^=]", key);
			::WritePrivateProfileString(m_strSection, key, NULL, m_strFileName);
		}
	};
	void	WriteSection(void)
	{
		int		i, nWrite;
		char	buf[65535], *ptr;
		ptr = buf;
		for (i = 0; i < val.GetSize(); i ++)
		{
			sprintf(ptr, "%s", val[i]);
			ptr += strlen(val[i]) + 1;
		}
		// 끝에 널이 두개면 완죠니 끝..
		*ptr = 0x00;
		*(ptr + 1) = 0x00;
		nWrite = ::WritePrivateProfileSection(m_strSection, buf, m_strFileName);
	};

	void	WriteValue(const char *item, const char *value)
	{
		::WritePrivateProfileString(m_strSection, item, value, m_strFileName);
	};

protected :
	CString		m_strFileName;
	CString		m_strSection;
};

#endif	__IniFiles_h
