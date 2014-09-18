// AccountReference.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CKSMTokenizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CKSMTokenizer::CKSMTokenizer()
{
	m_szArrOutText = NULL;
	m_szPlainText = NULL;
	m_nParsingOutCount = 0;
}

CKSMTokenizer::~CKSMTokenizer()
{
	EndParsing();
}

//*******************************************************************/
/*! Function Name : StartParsing
/*! Function      : ���ڿ� �Ľ��� �����Ѵ�. (�Ľ� ����� ������ EndParsing�� ȣ���ؾ��Ѵ�.)
/*! Param         : char* szInText (�Ľ̵� ���� ���ڿ�)
/*                  int nInTextLen (�Ľ̵� ���� ���ڿ� ����)
/*                  const char cSP (�Ľ� ������)
/*! Return        : ���(�Ľ̵� �Ǽ�), ����(����)
/*! Create        : ������, 2010/06/29
/*! Comment       : 
//******************************************************************/
int CKSMTokenizer::StartParsing(char* szInText, int nInTextLen, char cSP)
{
	//�Է°� ����
	if(!szInText || nInTextLen < 1) return -1;

	//������ �̹� �Ľ̵� ��� �ִ�.
	if(m_szArrOutText || m_szPlainText)
	{
		//EndParsing�� ȣ���Ͽ� ���� �Ľ̵� ��� ���� Ŭ�����ϰ� ���ο� �Ľ��� �ؾ߸��Ѵ�.
		return -2;
	}

	int i = 0;
	int nSPCount = 0;
	char szSP[2] = {0x00};
	char* p = NULL;

	szSP[0] = cSP;

	m_szPlainText = new char[nInTextLen+1];
	memset(m_szPlainText, 0x00, nInTextLen+1);
	memcpy(m_szPlainText, szInText, nInTextLen);

	for(i = 0; i < nInTextLen; i++)
	{
		if(m_szPlainText[i] == szSP[0]) nSPCount++;
	}

	//�Ľ��� �����ڰ� ����.
	if(nSPCount < 1)
	{
		delete m_szPlainText;
		m_szPlainText = NULL;

		return 0;
	}

	//�Ľ̵� ����� ����� 2���� �迭 �Ҵ�
	m_szArrOutText = new char*[nSPCount+1];
	memset(m_szArrOutText, 0x00, sizeof(char*) * (nSPCount+1));

	p = _tcstok(m_szPlainText, szSP);
	m_szArrOutText[0] = p;
	m_nParsingOutCount++;
	for(i=0; i < nSPCount && p != NULL ; i++)
	{
		p = _tcstok(NULL, szSP);
		if(!p) break;
		m_szArrOutText[i+1] = p;
		m_nParsingOutCount++;

	}/* End of for */

	return m_nParsingOutCount;

} /* End of Tokenizer */

//*******************************************************************/
/*! Function Name : EndParsing
/*! Function      : �Ľ̵� ���� ����� �����ų�, �ٸ� ���ڿ��� �Ľ��� ��� EndParsing�� ȣ���ؾ��Ѵ�.
/*! Param         : 
/*! Return        : ����.
/*! Create        : ������, 2010/06/29
/*! Comment       : 
//******************************************************************/
void CKSMTokenizer::EndParsing()
{
	if(m_szPlainText)
	{
		delete m_szPlainText;
		m_szPlainText = NULL;
	}

	if(m_szArrOutText)
	{
		delete m_szArrOutText;
		m_szArrOutText = NULL;
	}

	m_nParsingOutCount = 0;
}

//*******************************************************************/
/*! Function Name : GetSize
/*! Function      : �Ľ̵� �Ǽ�
/*! Param         : 
/*! Return        : �Ľ̵� �Ǽ��� ���Ѵ�.
/*! Create        : ������, 2010/06/29
/*! Comment       : 
//******************************************************************/
int CKSMTokenizer::GetSize()
{
	return m_nParsingOutCount;
}

//*******************************************************************/
/*! Function Name : GetAt
/*! Function      : �̹� �Ľ̵� ������ 2���� �迭�� ��� �ְ� �̰��� �ε����� �־� ���´�.
/*! Param         : 
/*! Return        : �ش� �ε����� ����Ǿ� �ִ� �Ľ̵� �������� ������ ����
/*! Create        : ������, 2010/06/29
/*! Comment       : 
//******************************************************************/
const char* CKSMTokenizer::GetAt(int nIndex)
{
	if(nIndex < 0 || nIndex > m_nParsingOutCount) return NULL;
	return m_szArrOutText[nIndex];
}
