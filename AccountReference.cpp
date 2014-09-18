// AccountReference.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AccountReference.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAccountReference::CAccountReference()
{
	memset(&m_arrAccReference, 0x00, sizeof(ALL_ACC_REFERENCE));
}

CAccountReference::~CAccountReference()
{
	ReleaseData();
}

//*******************************************************************/
/*! Function Name : InitAccReference
/*! Function      : 
/*! Param         : 
/*! Return        : 
/*! Create        : ������
/*! Comment       : ���� ini������ �޸𸮿� �о� ���δ�.
//******************************************************************/
void CAccountReference::InitAccReference(CString strPath)
{
	CString strSection, strTemp;
	int nCount, nCount2, i, j;
	DWORD dwLen = 0;
	char szDataBuf[4092] = {0x00};
	CKSMTokenizer tokenizer;
	nCount = GetPrivateProfileInt(_T("���¹�ȣ"), _T("�з�����"), 0, strPath);
	
	m_arrAccReference.nAccTypeCnt = nCount;
	m_arrAccReference.pArrAccType = new ACC_TYPE[nCount];
	memset(m_arrAccReference.pArrAccType, 0x00, sizeof(ACC_TYPE) * nCount);

    int nParseCnt = 0;
	for(i = 0; i < nCount; i++)
	{
		strSection.Format("���ºз�%d", i+1);

		memset(szDataBuf, 0x00, sizeof(szDataBuf));		
		dwLen = GetPrivateProfileString(strSection, _T("�з���"), _T(""), szDataBuf, sizeof(szDataBuf), strPath);
		memcpy(m_arrAccReference.pArrAccType[i].szAccTypeName, szDataBuf, dwLen);
		
		nCount2 = GetPrivateProfileInt(strSection, _T("�з���ȣ"), 0, strPath);
		m_arrAccReference.pArrAccType[i].nTypeNum = nCount2;

		memset(szDataBuf, 0x00, sizeof(szDataBuf));		
		dwLen = GetPrivateProfileString(strSection, _T("��ǰ��ȣ"), _T(""), szDataBuf, sizeof(szDataBuf), strPath);

		tokenizer.StartParsing(szDataBuf, dwLen, ',');

        nParseCnt = tokenizer.GetSize();

        if(nParseCnt > 0)
        {
		    for(j = 0; j < nParseCnt; j++)
		    {
			    m_arrAccReference.pArrAccType[i].nArrPresentNum[j] = atoi(tokenizer.GetAt(j));
		    }
        }
        else
        {
            m_arrAccReference.pArrAccType[i].nArrPresentNum[0] = atoi(szDataBuf);
        }

		tokenizer.EndParsing();

	}//End of for

	//�⺻�׸��� �о���δ�.
	nCount = GetPrivateProfileInt(_T("�⺻�׸�"), _T("COUNT"), 0, strPath);
	for(i = 0; i < nCount; i++)
	{
		memset(szDataBuf, 0x00, sizeof(szDataBuf));
		strTemp.Format("%d", i);
		dwLen = GetPrivateProfileString(_T("�⺻�׸�"), strTemp, _T(""), szDataBuf, sizeof(szDataBuf), strPath);
		memcpy(m_arrAccReference.szArrDefaultItemName[i], szDataBuf, dwLen);

	}

	//��Ź�о�ü �о���δ�.
	nCount = GetPrivateProfileInt(_T("��Ź�о�ü"), _T("COUNT"), 0, strPath);
	for(i = 0; i < nCount; i++)
	{
		memset(szDataBuf, 0x00, sizeof(szDataBuf));
		strTemp.Format("%d", i);
		dwLen = GetPrivateProfileString(_T("��Ź�о�ü"), strTemp, _T(""), szDataBuf, sizeof(szDataBuf), strPath);
		memcpy(m_arrAccReference.szArrStockLoanName[i], szDataBuf, dwLen);

	}


	DWORD nReadSize = GetPrivateProfileSection("��ǰ���и�", szDataBuf, sizeof(szDataBuf), strPath);

	if(nReadSize <= 0) return ;

	int nStartPos = 0, nEndPos = 0;
	char szTemp[512] = {0x00};
	CString strKey, strData;
	
    //��ǰ���и� ������ ī��Ʈ�� ��� ����� �о �Ľ��ؼ� �ִ´�.
	for(int i = 0; i < nReadSize; i++, nEndPos++)
	{
		if(szDataBuf[i] == 0x00)
		{
			memset(szTemp, 0x00, sizeof(szTemp));
			memcpy(szTemp, szDataBuf+nStartPos, nEndPos-nStartPos);
			nStartPos = nEndPos+1;
			tokenizer.StartParsing(szTemp, strlen(szTemp), '=');

			if(tokenizer.GetSize() > 1)
			{
				strKey = tokenizer.GetAt(0);
				strData = tokenizer.GetAt(1);

				m_mapProductName.SetAt(strKey, strData);
			}

			tokenizer.EndParsing();
		
		}//End of if

	}//End of for

	//���࿬�����
	memset(szDataBuf, 0x00, sizeof(szDataBuf));
	dwLen = GetPrivateProfileString(_T("BankAcc"), _T("BankAccType"), _T(""), szDataBuf, sizeof(szDataBuf), strPath);

	m_strBankAccType = szDataBuf;

}

//���»�ǰ�ڵ�� ���ºз��� ã�´�.
ACC_TYPE* CAccountReference::FindAccTypeByProduct(int nProductNum)
{
	int i, j;

	for(i = 0; i < m_arrAccReference.nAccTypeCnt; i++)
	{
		for(j = 0; j < MAX_PRODUCT; j++)
		{
            if(m_arrAccReference.pArrAccType[i].nArrPresentNum[j] == 0) break;

			if(m_arrAccReference.pArrAccType[i].nArrPresentNum[j] == nProductNum)
				return &m_arrAccReference.pArrAccType[i];

		}//End of for
	
	}//End of for

	return NULL;

}

void CAccountReference::ReleaseData()
{
	if(m_arrAccReference.pArrAccType)
	{
		delete m_arrAccReference.pArrAccType;
		m_arrAccReference.pArrAccType = NULL;
	}

	memset(&m_arrAccReference, 0x00, sizeof(ALL_ACC_REFERENCE));
}

//���»�ǰ�ڵ�� ��ǰ���и��� ã�´�.
void CAccountReference::FindProductNameList(CString strInput, CString& strOutPut)
{
	strOutPut = "";
	CString strProductCode;
    strProductCode = GetAccProductCode(strInput);

    if(strProductCode == "") return;

	m_mapProductName.Lookup(strProductCode, strOutPut);

    //�ʿ��� ã�Ƽ� ������ ���ºз� ������ �� ������ ã�´�.
	if(strOutPut == "")
		FindProductNameAll(strProductCode, strOutPut);
}

//���»�ǰ�ڵ�� ��ǰ���и��� ã�´�.
void CAccountReference::FindProductNameAll(CString strInput, CString& strOutPut)
{
	strOutPut = "";
	CString strProductCode;
	strProductCode = GetAccProductCode(strInput);

    if(strProductCode == "") return;

	int nCount = m_arrAccReference.nAccTypeCnt;
	int i, j, nProductNum;
	nProductNum = atoi(strProductCode);

	for(i = 0; i < nCount; i++)
	{
		for(j = 0; j < MAX_PRODUCT; j++)
		{
			if(m_arrAccReference.pArrAccType[i].nArrPresentNum[j] == nProductNum)
			{
				strOutPut = m_arrAccReference.pArrAccType[i].szAccTypeName;
				return;
			}
		}
	}

}

//���࿬����� Ÿ��
CString CAccountReference::GetBankAccType()
{
	return m_strBankAccType;
}

//���ºз����� ���Ѵ�.
void CAccountReference::GetAccTypeName(CString strInput, CString& strOutput)
{
    strOutput = "";
    int nProductNum;
    nProductNum = atoi(GetAccProductCode(strInput));
    if(!nProductNum) return;

    ACC_TYPE* accType = FindAccTypeByProduct(nProductNum);

    strOutput = accType->szAccTypeName;
}

//���ºз��� ��ȣ�� ���Ѵ�.
void CAccountReference::GetAccTypeNo(CString strInput, CString& strOutput)
{
    strOutput = "";
    int nProductNum;
    nProductNum = atoi(GetAccProductCode(strInput));
    if(!nProductNum) return;

    ACC_TYPE* accType = FindAccTypeByProduct(nProductNum);

    if(accType)
        strOutput.Format("%d", accType->nTypeNum);
}

//�Է� ���� ���¹�ȣ���� ��ǰ�ڵ常 ���Ƴ���.
CString CAccountReference::GetAccProductCode(CString strInput)
{
    CString strProductCode;
    if(strInput.GetLength() == 11)
        strProductCode = strInput.Mid(3, 2);
    else if(strInput.GetLength() == 2)
        strProductCode = strInput;
    else if(strInput.GetLength() == 10)
        strProductCode = strInput.Right(2);
    else
        return "";

    return strProductCode;
}