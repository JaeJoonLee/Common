#ifndef _TRBUILDER_COMM_H_
#define _TRBUILDER_COMM_H_


#include "DgnSvrComm.h"		// ����Ʈ�� ����    
#include "../Builder/DgnDBConnect/DBConnExport.h"
#include <afxtempl.h>
// �����Լ�

//--------------------------------------------------------------------//
// --> [Edit]  ������ 2006/05/15
// ������ �� ��Ʈ�� ���ڿ� ����Ʈ �ʱ�ȭ 
void InitEnumValList(); 

// ���ڶ��� --> ��ū ����Ʈ 
int GetTrLineData( CString sLine, CStringArray* pArray );

// ���ڿ� ����Ʈ���� ���ڿ��� ��ġ�ϴ� �ε��� ���� 
int GetIndexInArray(CStringArray &arrItem, CString strItem); 

// �ε����� �����ϴ� ���ڿ� 
CString GetItemInArray(CStringArray &arrItem, int nIndex); 
CString GetDBDataTypeString(CStringArray &arrItem, int nType, int nLen, int nDecimal);
// <-- [Edit]  ������ 2006/05/15
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
// --> [Edit]  ������ 2006/05/16
// ���� ��Ʈ�� ����Ʈ���� ���ڿ��� ��ġ�ϴ� �ε��� ���� 
int GetControlIndexInArray(CString strItem); 

// ���� ��Ʈ�� ����Ʈ���� �ε����� ��ġ�ϴ� ���ڿ� ���� 
CString GetControlItemInArray(int nIndex); 

// ���� ��Ʈ�� ����Ʈ���� �Է� ���� ��°�� �����ϴ� ��Ʈ�� �ε��� ���� 
int GetControlIndexByOrder(int nOrder);  

// ���� ��Ʈ�� ����Ʈ���� �Է� ���� ��°�� �����ϴ� ��Ʈ�� ���ڿ� ���� 
CString GetControlItemByOrder(int nOrder);  

// ��� ���� ��Ʈ�� ����Ʈ ���ڿ� ���� 
int GetControlItemArray(CStringArray *pArr);  
// <-- [Edit]  ������ 2006/05/16
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
// --> [Edit]  ������ 2006/05/17
// ���� ��Ʈ�� ����Ʈ���� �ε����� ��ġ�ϴ� �ѱ۹��ڿ� ���� 
CString GetKorControlItemInArray(int nIndex); 

// ���� ��Ʈ�� ����Ʈ���� �ѱ۹��ڿ��� ��ġ�ϴ� �ε��� ���� 
int GetKorControlIndexInArray(CString strKorItem); 
// <-- [Edit]  ������ 2006/05/17
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
// --> [Edit]  ������ 2006/05/18
// ���� ��Ʈ�� ����Ʈ���� �ѱ� �Է� ���� ��°�� �����ϴ� ��Ʈ�� ���ڿ� ���� 
CString GetKorControlItemByOrder(int nOrder);   
// ��� ���� ��Ʈ�� ����Ʈ �ѱ۹��ڿ� ���� 
int GetKorControlItemArray(CStringArray *pArr);  
 
// ���ڿ��� �������� �ε��� ����  
int GetDataTypeIndexInArray(CString strDataType); 
// �������� �ε����� �������� ���ڿ� ����  
CString GetDataTypeItemInArray(int nIndex); 

// 2���� ������ ���� ������ ������ ���ڸ� ���ڿ��� ���� 
CString GetDataLengthByNumbers(short data_len, short decimal_point);   
// ������ ���� ������ ������ ���ڿ��� 2���� ���ڷ� ����  
void GetTwoDataLengthNumbers(CString strDataLen, short *data_len, short *deciaml_point); 

//������ ���ڿ� ���� 
CString GetAttributeStringByVal(short iAttribute); 
//������ �� ����  
short GetAttributeValByString(CString strAttribute); 
//������ ���ڿ� ����Ʈ ���� 
void GetKorAttributeItemArray(CStringArray *pArr); 
// <-- [Edit]  ������ 2006/05/18 
//--------------------------------------------------------------------//


//--------------------------------------------------------------------//
// Ʈ�� �ڵ带 ������ ���� ������ ���ڿ� ����Ʈ�� ���� 
// Ʈ���ڵ� --> 'Ʈ�� ������', '��������', '�Է��ڵ�'   
// ��) 'MBCAOA001A01' --> 'MBCA', 'OA', '001A01' 
BOOL GetTranCodeElements(CString strTrCode, CString &strDomain, CString &strService, CString &strCode); 

// Ʈ���ڵ� ��ҵ���� Ʈ���ڵ�� �����Ͽ� ����  
CString GetTranCodeByElements(CString strDomain, CString strService, CString strCode); 
 
// Ʈ�� ��Ʈ�� ����â Ȱ��ȭ �� ���� �� �޺� ��Ʈ�ѿ� ���Ǵ� ���ڿ� ����Ʈ  
extern CStringArray g_arrDataVal;		//������ �� 
// --> [Edit]  �� �� �� 2006/09/19
extern CStringArray g_arrDBDataVal;	//DB������ �� 
// <-- [Edit]  �� �� �� 2006/09/19
extern CStringArray g_arrInOut;		//����� 
extern CStringArray g_arrArray;		//�迭 
 

// --> [Edit]  ������ 2006/05/16
// FN �Žý��ۿ��� ������ ��Ʈ�Ѱ� ������ �������� ������ ���� ����ü 
typedef struct tagFN_CONTROL_INDEX
{
	int		index; 
	char	szControl[255]; 
	char	szKorControl[255]; 
}FN_CONTROL_INDEX; 

// ��Ʈ�� �ε��� ������ ����Ʈ 
typedef CArray<FN_CONTROL_INDEX, FN_CONTROL_INDEX> FN_CONTROL_INDEX_ARRAY; 

// �۷ι� ��Ʈ�� �ε��� ����Ʈ 
extern FN_CONTROL_INDEX_ARRAY g_arrFnControlIndex; 
// <-- [Edit]  ������ 2006/05/16

// --> [Edit]  ������ 2006/06/16
// Ʈ�� ���� Ÿ�� 
extern CStringArray		g_arrTranServerType; 
extern CString			g_strDefTranServerType; 
// <-- [Edit]  ������ 2006/06/16


#endif 