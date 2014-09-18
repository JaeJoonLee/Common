/*
	변윤식 2010. 6. 29 
	문자열을 자동으로 파싱하고
	메모리를 자동 생성 및 해제하는 클래스.
*/
#ifndef _CKSMTokenizer_H_
#define _CKSMTokenizer_H_

#include <string.h>
#include <stdio.h>

#pragma once

class CKSMTokenizer
{
public:
	CKSMTokenizer();
	virtual ~CKSMTokenizer();

protected:
	char** m_szArrOutText;
	char* m_szPlainText;
	int m_nParsingOutCount;

public:
	int StartParsing(char* szInText, int nInTextLen, char cSP);
	void EndParsing();
	int GetSize();
	const char* GetAt(int nIndex);
};

#endif