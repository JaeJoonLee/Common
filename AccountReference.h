/*
	������ 2010. 6. 29
	�ش� ���ǻ翡 �����ϴ� ���ºз��� ��� �޸𸮿� ������ ����
	������ �� �ֵ����ϴ� Ŭ����.
*/
#ifndef _ACCOUNT_REFERENCE_H_
#define _ACCOUNT_REFERENCE_H_

#pragma once

#include "CKSMTokenizer.h"

#define MAX_PRODUCT				20		//�ִ� ��ǰ ��
#define MAX_DEFAULT_ITEM		20		//�⺻�׸� �ִ� ��
#define MAX_STOCK_LOAN			20		//�ִ� ��Ź�� ��ü ��

//�ش� ���ǻ翡 �����ϴ� ��� ������ �з������� ������ ���´�.
typedef struct _ACC_TYPE
{
	char szAccTypeName[128];			//���� �з���
	long nTypeNum;						//���� �з���ȣ
	long nArrPresentNum[MAX_PRODUCT];	//���� ��ǰ��ȣ

} ACC_TYPE;

//�ش� ���ǻ翡 �����ϴ� ��� ������ �з��� �� ��Ÿ ������ ������ ���´�.
typedef struct _ALL_ACC_REFERENCE
{
	int nAccTypeCnt;
	ACC_TYPE* pArrAccType;							//���� �з�
	char szArrDefaultItemName[MAX_DEFAULT_ITEM][128];	//���� �⺻�׸��
	char szArrStockLoanName[MAX_STOCK_LOAN][128];		//���� ��Ź�� ��ü��
	
} ALL_ACC_REFERENCE;

class CAccountReference : public CObject
{
public:
	CAccountReference();
	virtual ~CAccountReference();

protected:
	ALL_ACC_REFERENCE	m_arrAccReference;			//���ںз� ���۷���
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