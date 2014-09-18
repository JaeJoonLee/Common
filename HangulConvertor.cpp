#include "stdafx.h"
#include "HangulConvertor.h"

char *hanTable[]={"��","��","��","��","��","��","��","��","��","��",
					  "��","��","��","��","��","��","��","��","��"}; // 19 �ʼ�
#define LETTER_KIYEOK	0x3131		// ��
#define LETTER_HIEUH	0x314E		// ��
#define WORD_START		0xAC00		// ��

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
	// ã�� �ܾ�� ������� ª���� ����
	if (nLoopCnt > nNameLen)
		return FALSE;
	chTemp[2] = 0x00;
	chFind[2] = 0x00;

	BOOL	bFind = TRUE;
	for (j = 0 ; j < nLoopCnt ; j++)
	{
		// �Է��� ���� �ѱ��� ���
		if (pchFind[j] & 0x80)
		{
			// ����� �����ڸ��� �ѱ�����
			if (pchValue[j] & 0x80)	
			{
				memcpy(chFind, pchFind + j, 2);
				// �����ڵ�� ��ȯ�ϱ⿡ �ռ� ���� �װ��� �����ڵ忡���� ���̸� �˾ƾ� �Ѵ�.
				int nStrLen = MultiByteToWideChar(CP_ACP, 0, chFind, lstrlen(chFind), NULL, NULL);
				// �� ���̸�ŭ �޸𸮸� �Ҵ��Ѵ�.
				bstr = SysAllocStringLen(NULL, nStrLen);
				// ���� ��ȯ�� �����Ѵ�.(��Ƽ����Ʈ���� unicode��)
				MultiByteToWideChar(CP_ACP, 0, chFind, lstrlen(chFind), bstr, nStrLen);
				
				// ã�� ���ڰ� '��' ~ '��' �� �ʼ��� �Է��Ѱ��
				if (bstr[0] >= LETTER_KIYEOK && bstr[0] <= LETTER_HIEUH)
				{
					SysFreeString(bstr);
					// �ѱ��ϰ�� �ѱ��ھ� ���´�
					memcpy(chTemp, pchValue + j, 2);
					// �����ڵ�� ��ȯ�ϱ⿡ �ռ� ���� �װ��� �����ڵ忡���� ���̸� �˾ƾ� �Ѵ�.
					nStrLen = MultiByteToWideChar(CP_ACP, 0, chTemp, lstrlen(chTemp), NULL, NULL);
					// �� ���̸�ŭ �޸𸮸� �Ҵ��Ѵ�.
					bstr = SysAllocStringLen(NULL, nStrLen );
					// ���� ��ȯ�� �����Ѵ�.(��Ƽ����Ʈ���� unicode��)
					MultiByteToWideChar(CP_ACP, 0, chTemp, lstrlen(chTemp), bstr, nStrLen );
					// 		�ʼ�: ������ �ڵ忡�� 44032�� ����, 21*28�� ���� �� 0 ~ 18
					// 		�߼�: ������ �ڵ忡�� 44032�� ����, 21*28�� ���� �������� �ٽ� 28�� ���� �� 0 ~ 20
					//		����: ������ �ڵ忡�� 44032�� ����, 21*28�� ���� �������� �ٽ� 28�� ���� ������ 0 ~ 27 
					
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
				// �ʼ��� �ƴϸ� �׳� ��
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
			// ������� �ѱ��� �ƴ� ���
			else
			{
				j++;
				bFind = FALSE;
				break;
			}
		}
		// �Է°��� �ѱ��� �ƴ� ���
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
