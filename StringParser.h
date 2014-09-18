#ifndef __STRINGPARSER_H__
#define __STRINGPARSER_H__

class CStringParser
{
public:
	CStringParser();
	CStringParser(TCHAR *szText, TCHAR *cDelimeter);
	CStringParser(CString &sText, TCHAR *cDelimeter);
	~CStringParser();

	int ParseString(CString &sText, TCHAR *cDelimeter);
	int ParseString(TCHAR *szText, TCHAR *cDelimeter);

	CString GetAt(int i);
	int GetAtInt(int i);
	int GetCount();

private:
	CStringArray m_saToken;
};

#endif
