#include "stdafx.h"
#include "HangulConvertor.h"

char *hanTable[]={"ㄱ","ㄲ","ㄴ","ㄷ","ㄸ","ㄹ","ㅁ","ㅂ","ㅃ","ㅅ",
					  "ㅆ","ㅇ","ㅈ","ㅉ","ㅊ","ㅋ","ㅌ","ㅍ","ㅎ"}; // 19 초성
#define LETTER_KIYEOK	0x3131		// ㄱ
#define LETTER_HIEUH	0x314E		// ㅎ
#define WORD_START		0xAC00		// 가

CHangulConvertor::CHangulConvertor(void)
{
}

CHangulConvertor::~CHangulConvertor(void)
{
}

BOOL CHangulConvertor::IsMatchString(CString strSrc, CString strFind)
{
	int j, nNameLen;
	CString strTemp=_T(""), strTemp2=_T("");
	char chTemp[3], chFind[3];
	int nLoopCnt;
	BSTR bstr;
	
	char* pchValue	= strSrc.GetBuffer(0);
	char* pchFind	= strFind.GetBuffer(0);
	nNameLen		= strSrc.GetLength();
	nLoopCnt		= strFind.GetLength();
	// 찾을 단어보다 종목명이 짧으면 제외
	if (nLoopCnt > nNameLen)
		return FALSE;
	chTemp[2] = 0x00;
	chFind[2] = 0x00;

	BOOL	bFind = TRUE;
	for (j = 0 ; j < nLoopCnt ; j++)
	{
		// 입력한 값이 한글인 경우
		if (pchFind[j] & 0x80)
		{
			// 종목명에 같은자리가 한글인지
			if (pchValue[j] & 0x80)	
			{
				memcpy(chFind, pchFind + j, 2);
				// 유니코드로 변환하기에 앞서 먼저 그것의 유니코드에서의 길이를 알아야 한다.
				int nStrLen = MultiByteToWideChar(CP_ACP, 0, chFind, lstrlen(chFind), NULL, NULL);
				// 얻어낸 길이만큼 메모리를 할당한다.
				bstr = SysAllocStringLen(NULL, nStrLen);
				// 이제 변환을 수행한다.(멀티바이트에서 unicode로)
				MultiByteToWideChar(CP_ACP, 0, chFind, lstrlen(chFind), bstr, nStrLen);
				
				// 찾는 글자가 'ㄱ' ~ 'ㅎ' 의 초성을 입력한경우
				if (bstr[0] >= LETTER_KIYEOK && bstr[0] <= LETTER_HIEUH)
				{
					SysFreeString(bstr);
					// 한글일경우 한글자씩 빼온다
					memcpy(chTemp, pchValue + j, 2);
					// 유니코드로 변환하기에 앞서 먼저 그것의 유니코드에서의 길이를 알아야 한다.
					nStrLen = MultiByteToWideChar(CP_ACP, 0, chTemp, lstrlen(chTemp), NULL, NULL);
					// 얻어낸 길이만큼 메모리를 할당한다.
					bstr = SysAllocStringLen(NULL, nStrLen );
					// 이제 변환을 수행한다.(멀티바이트에서 unicode로)
					MultiByteToWideChar(CP_ACP, 0, chTemp, lstrlen(chTemp), bstr, nStrLen );
					// 		초성: 글자의 코드에서 44032를 빼고, 21*28로 나눈 몫 0 ~ 18
					// 		중성: 글자의 코드에서 44032를 빼고, 21*28로 나눈 나머지를 다시 28로 나눈 몫 0 ~ 20
					//		종성: 글자의 코드에서 44032를 빼고, 21*28로 나눈 나머지를 다시 28로 나눈 나머지 0 ~ 27 
					
					int hcode = bstr[0] - WORD_START;
					int cho = hcode / 588;
					strTemp = strFind.Mid(j, 2);
					strTemp2.Format("%s", hanTable[cho]);
					j++;

					SysFreeString(bstr);

					if (strTemp2 != strTemp)
					{
						bFind = FALSE;
						break;
					}
				}
				// 초성이 아니면 그냥 비교
				else
				{
					strTemp		= strFind.Mid(j, 2);
					strTemp2	= strSrc.Mid(j, 2);
					j++;

					if (strTemp2 != strTemp)
					{
						bFind = FALSE;
						break;
					}
				}
			}
			// 종목명이 한글이 아닌 경우
			else
			{
				j++;
				bFind = FALSE;
				break;
			}
		}
		// 입력값이 한글이 아닌 경우
		else
		{
			if (pchFind[j] != pchValue[j])
			{
				bFind = FALSE;
				break;
			}
		}
		//	TRACE("FALSE [%c]\n",pchValue[j]);
	}

	if (!bFind)
		return FALSE;

	return TRUE;
}
