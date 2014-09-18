#include "stdafx.h"
#include "StringParser.h"

CStringParser::CStringParser()
{
}

CStringParser::~CStringParser()
{
}

CStringParser::CStringParser(TCHAR *szText, TCHAR *cDelimeter)
{
	CString sText = szText;
	CStringParser(sText, cDelimeter);
}

CStringParser::CStringParser(CString &sText, TCHAR *cDelimeter)
{
	ParseString(sText, cDelimeter);
}

int CStringParser::ParseString(TCHAR *szText, TCHAR *cDelimeter)
{
	CString sText = szText;
	return ParseString(sText, cDelimeter);
}

int CStringParser::ParseString(CString &sText, TCHAR *cDelimeter)
{
	CString sDelimeter = cDelimeter;
	CString sToken;
	int i, nLength = sText.GetLength();
	TCHAR cChar;

	m_saToken.RemoveAll();

	for (i = 0; i < nLength; ++i)
	{
		cChar = sText.GetAt(i);
		if (sDelimeter.Find(cChar) != -1)
		{
			m_saToken.Add(sToken);
			sToken.Empty();
		}
		else
		{
			sToken += cChar;
		}
	}

	if (sToken.GetLength() > 0)
		m_saToken.Add(sToken);

	return m_saToken.GetCount();
}

CString CStringParser::GetAt(int i)
{
	int nCount = m_saToken.GetCount();

	if (0 <= i && i <= nCount-1)
		return m_saToken.GetAt(i);
	else
		return "";
}

int CStringParser::GetAtInt(int i)
{
	int nCount = m_saToken.GetCount();

	if (0 <= i && i <= nCount-1)
		return atoi(m_saToken.GetAt(i));
	else
		return 0xFFFFFFFF;
}

int CStringParser::GetCount()
{
	return m_saToken.GetCount(); 
}

