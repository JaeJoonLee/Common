/*
	������ 2010. 6. 29 
	���ڿ��� �ڵ����� �Ľ��ϰ�
	�޸𸮸� �ڵ� ���� �� �����ϴ� Ŭ����.
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