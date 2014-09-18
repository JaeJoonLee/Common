/*
	변윤식 2010. 6. 29
	해당 증권사에 존재하는 계좌분류를 모두 메모리에 저장해 놓고
	참조할 수 있도록하는 클래스.
*/
#ifndef _ACCOUNT_REFERENCE_H_
#define _ACCOUNT_REFERENCE_H_

#pragma once

#include "CKSMTokenizer.h"

#define MAX_PRODUCT				20		//최대 상품 수
#define MAX_DEFAULT_ITEM		20		//기본항목 최대 수
#define MAX_STOCK_LOAN			20		//최대 스탁론 업체 수

//해당 증권사에 존재하는 모든 계좌의 분류정보를 저장해 놓는다.
typedef struct _ACC_TYPE
{
	char szAccTypeName[128];			//계자 분류명
	long nTypeNum;						//계좌 분류번호
	long nArrPresentNum[MAX_PRODUCT];	//계좌 상품번호

} ACC_TYPE;

//해당 증권사에 존재하는 모든 계좌의 분류를 및 기타 정보를 저장해 놓는다.
typedef struct _ALL_ACC_REFERENCE
{
	int nAccTypeCnt;
	ACC_TYPE* pArrAccType;							//계좌 분류
	char szArrDefaultItemName[MAX_DEFAULT_ITEM][128];	//계좌 기본항목명
	char szArrStockLoanName[MAX_STOCK_LOAN][128];		//계좌 스탁론 업체명
	
} ALL_ACC_REFERENCE;

class CAccountReference : public CObject
{
public:
	CAccountReference();
	virtual ~CAccountReference();

protected:
	ALL_ACC_REFERENCE	m_arrAccReference;			//계자분류 레퍼런스
	CMapStringToString	m_mapProductName;
	CString				m_strBankAccType;

    CString GetAccProductCode(CString strInput);

public:
	void InitAccReference(CString strPath);
	void ReleaseData();
	ACC_TYPE* FindAccTypeByProduct(int nProductNum);
	void FindProductNameList(CString strInput, CString& strOutPut);
	void FindProductNameAll(CString strInput, CString& strOutPut);
	CString GetBankAccType();

    void GetAccTypeName(CString strInput, CString& strOutput);
    void GetAccTypeNo(CString strInput, CString& strOutput);

};

#endif