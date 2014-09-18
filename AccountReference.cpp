// AccountReference.cpp : 구현 파일입니다.
//
//이재준
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
/*! Create        : 변윤식
/*! Comment       : 계좌 ini파일을 메모리에 읽어 들인다.
//******************************************************************/
void CAccountReference::InitAccReference(CString strPath)
{
	CString strSection, strTemp;
	int nCount, nCount2, i, j;
	DWORD dwLen = 0;
	char szDataBuf[4092] = {0x00};
	CKSMTokenizer tokenizer;
	nCount = GetPrivateProfileInt(_T("계좌번호"), _T("분류갯수"), 0, strPath);
	
	m_arrAccReference.nAccTypeCnt = nCount;
	m_arrAccReference.pArrAccType = new ACC_TYPE[nCount];
	memset(m_arrAccReference.pArrAccType, 0x00, sizeof(ACC_TYPE) * nCount);

    int nParseCnt = 0;
	for(i = 0; i < nCount; i++)
	{
		strSection.Format("계좌분류%d", i+1);

		memset(szDataBuf, 0x00, sizeof(szDataBuf));		
		dwLen = GetPrivateProfileString(strSection, _T("분류명"), _T(""), szDataBuf, sizeof(szDataBuf), strPath);
		memcpy(m_arrAccReference.pArrAccType[i].szAccTypeName, szDataBuf, dwLen);
		
		nCount2 = GetPrivateProfileInt(strSection, _T("분류번호"), 0, strPath);
		m_arrAccReference.pArrAccType[i].nTypeNum = nCount2;

		memset(szDataBuf, 0x00, sizeof(szDataBuf));		
		dwLen = GetPrivateProfileString(strSection, _T("상품번호"), _T(""), szDataBuf, sizeof(szDataBuf), strPath);

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

	//기본항목을 읽어들인다.
	nCount = GetPrivateProfileInt(_T("기본항목"), _T("COUNT"), 0, strPath);
	for(i = 0; i < nCount; i++)
	{
		memset(szDataBuf, 0x00, sizeof(szDataBuf));
		strTemp.Format("%d", i);
		dwLen = GetPrivateProfileString(_T("기본항목"), strTemp, _T(""), szDataBuf, sizeof(szDataBuf), strPath);
		memcpy(m_arrAccReference.szArrDefaultItemName[i], szDataBuf, dwLen);

	}

	//스탁론업체 읽어들인다.
	nCount = GetPrivateProfileInt(_T("스탁론업체"), _T("COUNT"), 0, strPath);
	for(i = 0; i < nCount; i++)
	{
		memset(szDataBuf, 0x00, sizeof(szDataBuf));
		strTemp.Format("%d", i);
		dwLen = GetPrivateProfileString(_T("스탁론업체"), strTemp, _T(""), szDataBuf, sizeof(szDataBuf), strPath);
		memcpy(m_arrAccReference.szArrStockLoanName[i], szDataBuf, dwLen);

	}


	DWORD nReadSize = GetPrivateProfileSection("상품구분명", szDataBuf, sizeof(szDataBuf), strPath);

	if(nReadSize <= 0) return ;

	int nStartPos = 0, nEndPos = 0;
	char szTemp[512] = {0x00};
	CString strKey, strData;
	
    //상품구분명 섹션은 카운트가 없어서 덩어리로 읽어서 파싱해서 넣는다.
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

	//은행연계계좌
	memset(szDataBuf, 0x00, sizeof(szDataBuf));
	dwLen = GetPrivateProfileString(_T("BankAcc"), _T("BankAccType"), _T(""), szDataBuf, sizeof(szDataBuf), strPath);

	m_strBankAccType = szDataBuf;

}

//계좌상품코드로 계좌분류를 찾는다.
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

//계좌상품코드로 상품구분명을 찾는다.
void CAccountReference::FindProductNameList(CString strInput, CString& strOutPut)
{
	strOutPut = "";
	CString strProductCode;
    strProductCode = GetAccProductCode(strInput);

    if(strProductCode == "") return;

	m_mapProductName.Lookup(strProductCode, strOutPut);

    //맵에서 찾아서 없으면 계좌분류 섹션을 다 뒤져서 찾는다.
	if(strOutPut == "")
		FindProductNameAll(strProductCode, strOutPut);
}

//계좌상품코드로 상품구분명을 찾는다.
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

//은행연계계좌 타입
CString CAccountReference::GetBankAccType()
{
	return m_strBankAccType;
}

//계좌분류명을 구한다.
void CAccountReference::GetAccTypeName(CString strInput, CString& strOutput)
{
    strOutput = "";
    int nProductNum;
    nProductNum = atoi(GetAccProductCode(strInput));
    if(!nProductNum) return;

    ACC_TYPE* accType = FindAccTypeByProduct(nProductNum);

    strOutput = accType->szAccTypeName;
}

//계좌분류명 번호를 구한다.
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

//입력 받은 계좌번호에서 상품코드만 봅아낸다.
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