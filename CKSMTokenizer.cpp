// AccountReference.cpp : 구현 파일입니다.
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
/*! Function      : 문자열 파싱을 시작한다. (파싱 사용이 끝나면 EndParsing을 호출해야한다.)
/*! Param         : char* szInText (파싱될 원문 문자열)
/*                  int nInTextLen (파싱될 원문 문자열 길이)
/*                  const char cSP (파싱 구분자)
/*! Return        : 양수(파싱된 건수), 음수(에러)
/*! Create        : 변윤식, 2010/06/29
/*! Comment       : 
//******************************************************************/
int CKSMTokenizer::StartParsing(char* szInText, int nInTextLen, char cSP)
{
	//입력값 오류
	if(!szInText || nInTextLen < 1) return -1;

	//기존에 이미 파싱된 결과 있다.
	if(m_szArrOutText || m_szPlainText)
	{
		//EndParsing을 호출하여 기존 파싱된 결과 값을 클리어하고 새로운 파싱을 해야만한다.
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

	//파싱할 구분자가 없다.
	if(nSPCount < 1)
	{
		delete m_szPlainText;
		m_szPlainText = NULL;

		return 0;
	}

	//파싱된 결과가 저장될 2차원 배열 할당
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
/*! Function      : 파싱된 값들 사용이 끝났거나, 다른 문자열을 파싱할 경우 EndParsing을 호출해야한다.
/*! Param         : 
/*! Return        : 없음.
/*! Create        : 변윤식, 2010/06/29
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
/*! Function      : 파싱된 건수
/*! Param         : 
/*! Return        : 파싱된 건수를 구한다.
/*! Create        : 변윤식, 2010/06/29
/*! Comment       : 
//******************************************************************/
int CKSMTokenizer::GetSize()
{
	return m_nParsingOutCount;
}

//*******************************************************************/
/*! Function Name : GetAt
/*! Function      : 이미 파싱된 값들은 2차원 배열에 들어 있고 이것의 인덱스를 넣어 빼온다.
/*! Param         : 
/*! Return        : 해당 인덱스에 저장되어 있는 파싱된 아이템의 포인터 리턴
/*! Create        : 변윤식, 2010/06/29
/*! Comment       : 
//******************************************************************/
const char* CKSMTokenizer::GetAt(int nIndex)
{
	if(nIndex < 0 || nIndex > m_nParsingOutCount) return NULL;
	return m_szArrOutText[nIndex];
}
