//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (��)�ѱ��Ҹ���ġ        
//******************************************************************
//  File Name     : TrComm.cpp
//  Function      : 
//  System Name   : KSBuilder
//  Create        : ������ , 2006/03/20
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
#include "stdafx.h"   
#include "CommDef.h"		// ������� ���� 
#include "TrComm.h"			// �����Լ� ���� 

// --> [Edit]  ������ 2006/05/11
#include "../builder/srshare/sd_global.h"		// ���� ���� 
// <-- [Edit]  ������ 2006/05/11

// Ʈ�� ��Ʈ�� ����â Ȱ��ȭ �� ���� �� �޺� ��Ʈ�ѿ� ���Ǵ� ���ڿ� ����Ʈ  
CStringArray g_arrDataVal;		//������ �� 
// --> [Edit]  �� �� �� 2006/09/19
CStringArray g_arrDBDataVal;	//DB������ �� 
// <-- [Edit]  �� �� �� 2006/09/19
CStringArray g_arrInOut;		//����� 
CStringArray g_arrArray;		//�迭 
 
// --> [Edit]  ������ 2006/05/16
// �۷ι� ��Ʈ�� �ε��� ����Ʈ 
FN_CONTROL_INDEX_ARRAY g_arrFnControlIndex; 
// <-- [Edit]  ������ 2006/05/16

// --> [Edit]  ������ 2006/06/16
// Ʈ�� ���� Ÿ�� 
CStringArray		g_arrTranServerType; 
CString			g_strDefTranServerType; 
// <-- [Edit]  ������ 2006/06/16

//******************************************************************
//  Function Name : InitEnumValList
//  Function      : ������ ���ڿ�, ��Ʈ�� ���ڿ� ����Ʈ �ʱ�ȭ �Լ� 
//  Param         :	����
//  Return        :	void
//  Create        : ������ , 2006/05/17
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
void InitEnumValList()
{
	//������ �� 
	g_arrDataVal.RemoveAll(); 
	g_arrDataVal.Add(SZ_BYTE);		// FT_BYTE(unsigned char(8bit))
	g_arrDataVal.Add(SZ_SHORT);		// FT_SHORT(int16)
	g_arrDataVal.Add(SZ_USHORT);	// FT_USHORT(unsigned int16)
	g_arrDataVal.Add(SZ_LONG);		// FT_LONG(int32)
	g_arrDataVal.Add(SZ_ULONG);		// FT_ULONG(unsigned int32)
	g_arrDataVal.Add(SZ_FLOAT);		// FT_FLOAT(float  (4 bytes))
	g_arrDataVal.Add(SZ_DOUBLE);	// FT_DOUBLE(double (8 bytes)) 
	g_arrDataVal.Add(SZ_LONGLONG);	// FT_LONGLONG(8 bytes)   
	g_arrDataVal.Add(SZ_STRING);  	// FT_STRING(�ؽ�Ʈ)
	g_arrDataVal.Add(SZ_STRINGNUM); // FT_STRINGNUM(�ؽ�Ʈ)
	g_arrDataVal.Add(SZ_DATE);		// FT_DATE(������)
	g_arrDataVal.Add(SZ_DAY);		// FT_DAY(������)
	g_arrDataVal.Add(SZ_TIME);		// FT_TIME(�ð���)      
	
// --> [Edit]  �� �� �� 2006/09/19
	//DB������ �� 
	g_arrDBDataVal.RemoveAll(); 
	g_arrDBDataVal.Add("char");  
	g_arrDBDataVal.Add("varchar"); 
	g_arrDBDataVal.Add("numeric");  
	g_arrDBDataVal.Add("int"); 
	g_arrDBDataVal.Add("text"); 
	g_arrDBDataVal.Add("datetime"); 
	g_arrDBDataVal.Add("image"); 
// <-- [Edit]  �� �� �� 2006/09/19


	//��Ʈ�� �� �ε��� ����Ʈ  
	/*
		���� '��������\dgn\system\TranItemCtrl.Ini'�� ���ǵ� ��Ʈ�� ����Ʈ�� �ε��Ͽ� 	
		TrBuilder���� �����ڵ��� ���ǵ� ��Ʈ�� ����Ʈ �������� �����ϰ� �Ѵ�. 
	*/ 
	
	// ���� ���α׷� ���� ��� 
	CString strExePath; 
	::GetModuleFileName(NULL, strExePath.GetBuffer(1024), 1024); 
	strExePath.ReleaseBuffer(); 
	int pos = strExePath.ReverseFind('\\'); 
	if(pos > -1)
	{
		strExePath = strExePath.Left(pos); 
	}

	CString strControlIndexPath = strExePath; 
	strControlIndexPath += "\\dgn\\system\\TranItemCtrl.Ini"; 		
	int control_count = ::GetPrivateProfileInt("Control", "count", 0, strControlIndexPath); 
	if(control_count > 0)
	{
		DWORD dwSize = 255*20; 
		char *pRetString = new char[dwSize];  
		memset(pRetString, 0, dwSize); 
		DWORD dwRet = GetPrivateProfileSection("Control", pRetString, dwSize, strControlIndexPath); 
		if(dwRet > 0)
		{
			CStringArray arrLine; 
			CString strLine;
			BOOL bNull = FALSE; 			
			for(int i=0; i<(int)dwRet; i++)
			{
				char ch = pRetString[i]; 
				
				// ������ �� 
				if(bNull && ch=='\0')
				{
					break; 
				}

				// �ι����� ��� ���ݱ����� �����͸� (Ű,��) ���� ������ �� 
				if(ch == '\0')
				{					
					arrLine.Add(strLine); 
					strLine = "";
					bNull = TRUE; 
				}
				else
				{
					strLine += ch;
					bNull = FALSE; 
				}
			}
			delete pRetString; 

			BOOL bCountLine = FALSE;
			for(int i=0; i<arrLine.GetSize(); i++)
			{
				CString strLine = arrLine.GetAt(i); 
				TRACE("InitEnumValList ==> %s \n", strLine); 

				if(!bCountLine)
				{
					strLine.TrimLeft();  
					
					if(strLine.Find("count", 0) == 0)
					{
						bCountLine = TRUE;
					} 
				}
				else
				{
					CStringArray arrLine; 
					::GetTrLineData(strLine, &arrLine); 
					if(arrLine.GetSize() >= 2)
					{  
						CString strIndex = arrLine.GetAt(0); 
						CString strControl = arrLine.GetAt(1); 
						CString strKorControl = arrLine.GetAt(2); 
						strControl.TrimLeft(); 
						strControl.TrimRight();  
						strKorControl.TrimLeft(); 
						strKorControl.TrimRight();  
						int control_index = atoi(strIndex);  

						FN_CONTROL_INDEX fnControlIndex;
						fnControlIndex.index = control_index; 
						strcpy(fnControlIndex.szControl, strControl); 
						strcpy(fnControlIndex.szKorControl, strKorControl); 
						g_arrFnControlIndex.Add(fnControlIndex);  
					}
				} 
			}
		}
	} 

	//����� 
	g_arrInOut.RemoveAll(); 
	g_arrInOut.Add(SZ_KOR_IN_RECORD); 
	g_arrInOut.Add(SZ_KOR_OUT_RECORD); 

	//�迭 
	g_arrArray.RemoveAll(); 
	g_arrArray.Add(SZ_KOR_SINGLE_RECORD); 
	g_arrArray.Add(SZ_KOR_ARRAY_RECORD); 


	//Ʈ�� ���� Ÿ�� ����Ʈ 			
	CString strConfigPath = strExePath; 
	strConfigPath += SZ_TRAN_CONFIG_FILE; 
	int tr_server_count = GetPrivateProfileInt("TRAN_SERVER", "count", 0, strConfigPath); 	
	::GetPrivateProfileString("TRAN_SERVER", "default", "", g_strDefTranServerType.GetBuffer(1024), 1024, strConfigPath); 
	g_strDefTranServerType.ReleaseBuffer(); 
	for(int i=0; i<tr_server_count; i++)
	{
		CString strIndex; 
		CString strVal; 
		strIndex.Format("%d", i+1); 		
		::GetPrivateProfileString("TRAN_SERVER", strIndex, "", strVal.GetBuffer(1024), 1024, strConfigPath); 
		strVal.ReleaseBuffer(); 
		strVal.TrimLeft(); 
		strVal.TrimRight(); 
		g_arrTranServerType.Add(strVal); 
	} 
}

//******************************************************************
//  Function Name : GetTrLineData
//  Function      : ��ƿ��Ƽ �Լ� - ���ι��ڿ��� �Ľ�
//  Param         :	 CString sLine, CStringArray* pArray
//  Return        :	int
//  Create        : ������ , 2006/05/17
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
int GetTrLineData( CString sLine, CStringArray* pArray )
{
	// ���Ͽ��� �о ( "\r\n", ",", ������ ���� ) ��Ʈ������Ʈ�� �ִ´�.
	char* pszBuffer = (LPSTR)(LPCTSTR)sLine;
	char seps[]   = ",=";
	char* token = NULL;
	char* pNexttoken = NULL;
	CString sWord( SNULL );
	
	token = strtok_s( pszBuffer, seps, &pNexttoken );
	while( token != NULL )
	{
		sWord.Format( _T("%s"), token );
		sWord.TrimLeft( _T(" \t") );
		sWord.TrimRight( _T(" \t") );
		pArray->Add( sWord );
		token = strtok_s( NULL, seps, &pNexttoken );
	}
	
	return pArray->GetSize();
}

//******************************************************************
//  Function Name : GetIndexInArray 
//  Function      : ���ڿ� ����Ʈ���� ���ڿ��� ��ġ�ϴ� �ε��� ���� 
//  Param         :	CStringArray &arrItem, CString strItem
//  Return        :	int
//  Create        : ������ , 2006/05/17
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
int GetIndexInArray(CStringArray &arrItem, CString strItem){
	for(int i=0; i<arrItem.GetSize(); i++){  

		strItem.MakeLower(); 
		CString strIn = arrItem.GetAt(i); 
		strIn.MakeLower(); 
		if(strItem == strIn)
			return i; 
	}
	return -1; 
}

//******************************************************************
//  Function Name : GetItemInArray
//  Function      : �ε����� �����ϴ� ���ڿ� 
//  Param         :	CStringArray &arrItem, int nIndex
//  Return        :	CString
//  Create        : ������ , 2006/05/17
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString GetItemInArray(CStringArray &arrItem, int nIndex){ 	 
	if(nIndex<0 || nIndex>=arrItem.GetSize())
		return ""; 
	else
		return arrItem.GetAt(nIndex); 
}

//******************************************************************
//  Function Name : GetDBDataTypeString
//  Function      : 
//  Param         :	CStringArray &arrItem, int nType, int nLen, int nDecimal
//  Return        :	CString
//  Create        : �� �� �� , 2006/09/19
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString GetDBDataTypeString(CStringArray &arrItem, int nType, int nLen, int nDecimal)
{
	int nIndex = nType -1;
	if (nIndex < 0 || nIndex >= arrItem.GetSize())
		return ""; 

	CString	strRetValue = _T("");
	CString strDataType = arrItem.GetAt(nIndex); 
	if (nIndex == 0 || nIndex == 1)
		strRetValue.Format("%s(%d)", strDataType, nLen);
	else if (nIndex == 2)
		strRetValue.Format("%s(%d,%d)", strDataType, nLen, nDecimal);
	else
		strRetValue	= strDataType;

	return strRetValue;
}

//******************************************************************
//  Function Name : GetControlIndexInArray
//  Function      : ���� ��Ʈ�� ����Ʈ���� ���ڿ��� ��ġ�ϴ� �ε��� ���� 
//  Param         :	CString strItem
//  Return        :	int
//  Create        : ������ , 2006/05/17
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
int GetControlIndexInArray(CString strItem)
{
	strItem.MakeLower(); 
	for(int i=0; i<g_arrFnControlIndex.GetSize(); i++)
	{
		FN_CONTROL_INDEX fnControlIndex = g_arrFnControlIndex.GetAt(i);  
		CString strTmp = fnControlIndex.szControl;
		strTmp.MakeLower(); 
		if(strItem == strTmp)
			return fnControlIndex.index; 
	}  

	return CT_NOCONTROL; 	
} 

//******************************************************************
//  Function Name : GetControlItemInArray
//  Function      : ���� ��Ʈ�� ����Ʈ���� ���ڿ��� ��ġ�ϴ� �ε��� ���� 
//  Param         :	int nIndex
//  Return        :	CString
//  Create        : ������ , 2006/05/17
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString GetControlItemInArray(int nIndex)
{
	for(int i=0; i<g_arrFnControlIndex.GetSize(); i++)
	{
		FN_CONTROL_INDEX fnControlIndex = g_arrFnControlIndex.GetAt(i);  
		if(nIndex == fnControlIndex.index)
			return fnControlIndex.szControl; 
	}  

	return SZ_CT_NULL; 
}

//******************************************************************
//  Function Name : GetControlIndexByOrder
//  Function      : ���� ��Ʈ�� ����Ʈ���� �Է� ���� ��°�� �����ϴ� ��Ʈ�� �ε��� ���� 
//  Param         :	int nOrder
//  Return        :	int
//  Create        : v
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
int GetControlIndexByOrder(int nOrder)
{
	if(nOrder >= 0 && nOrder < g_arrFnControlIndex.GetSize())
	{
		FN_CONTROL_INDEX fnControlIndex = g_arrFnControlIndex.GetAt(nOrder); 
		return fnControlIndex.index; 
	}
	else
	{
		return CT_NOCONTROL;
	}
}

 

//******************************************************************
//  Function Name : GetControlItemByOrder
//  Function      : ���� ��Ʈ�� ����Ʈ���� �Է� ���� ��°�� �����ϴ� ��Ʈ�� ���ڿ� ���� 
//  Param         :	int nOrder
//  Return        :	CString
//  Create        : ������ , 2006/05/17
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString GetControlItemByOrder(int nOrder)
{
	if(nOrder >= 0 && nOrder < g_arrFnControlIndex.GetSize())
	{
		FN_CONTROL_INDEX fnControlIndex = g_arrFnControlIndex.GetAt(nOrder); 
		return fnControlIndex.szControl;  
	}
	else
	{
		return SZ_CT_NULL;
	}
}

//******************************************************************
//  Function Name : GetControlItemArray
//  Function      : ��� ���� ��Ʈ�� ����Ʈ ���ڿ� ���� 
//  Param         :	CStringArray *pArr��
//  Return        :	int
//  Create        : ������ , 2006/05/17
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
int GetControlItemArray(CStringArray *pArr)
{
	for(int i=0; i<g_arrFnControlIndex.GetSize(); i++)
	{
		FN_CONTROL_INDEX fnControlIndex = g_arrFnControlIndex.GetAt(i); 		
		pArr->Add(fnControlIndex.szControl); 
	}

	return g_arrFnControlIndex.GetSize(); 
}
 
//******************************************************************
//  Function Name : GetKorControlItemInArray
//  Function      : ���� ��Ʈ�� ����Ʈ���� �ε����� ��ġ�ϴ� �ѱ۹��ڿ� ���� 
//  Param         :	int nIndex
//  Return        :	CString
//  Create        : ������ , 2006/05/17
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString GetKorControlItemInArray(int nIndex)
{
	for(int i=0; i<g_arrFnControlIndex.GetSize(); i++)
	{
		FN_CONTROL_INDEX fnControlIndex = g_arrFnControlIndex.GetAt(i);  
		if(nIndex == fnControlIndex.index)
			return fnControlIndex.szKorControl; 
	}  

	return CString("������");
}

//******************************************************************
//  Function Name : GetKorControlIndexInArray
//  Function      : ���� ��Ʈ�� ����Ʈ���� �ѱ۹��ڿ��� ��ġ�ϴ� �ε��� ���� 
//  Param         :	CString strKorItem
//  Return        :	int
//  Create        : ������ , 2006/05/17
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
int GetKorControlIndexInArray(CString strKorItem)
{
	strKorItem.MakeLower(); 
	for(int i=0; i<g_arrFnControlIndex.GetSize(); i++)
	{
		FN_CONTROL_INDEX fnControlIndex = g_arrFnControlIndex.GetAt(i);  
		CString strTmp = fnControlIndex.szKorControl; 
		strTmp.MakeLower(); 
		if(strKorItem == strTmp)
			return fnControlIndex.index; 
	}  

	return CT_NOCONTROL; 	
} 

//******************************************************************
//  Function Name : GetKorControlItemByOrder
//  Function      : ���� ��Ʈ�� ����Ʈ���� �Է� ���� ��°�� �����ϴ� 
//					��Ʈ�� �ѱ� ���ڿ� ���� 
//  Param         :	int nOrder
//  Return        :	CString 
//  Create        : ������ , 2006/05/18
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString GetKorControlItemByOrder(int nOrder)
{
	if(nOrder >= 0 && nOrder < g_arrFnControlIndex.GetSize())
	{
		FN_CONTROL_INDEX fnControlIndex = g_arrFnControlIndex.GetAt(nOrder); 
		return fnControlIndex.szKorControl;  
	}
	else
	{
		return SZ_KOR_CT_NULL;
	}	
} 

//******************************************************************
//  Function Name : GetKorControlItemArray
//  Function      : ��� ���� ��Ʈ�� ����Ʈ �ѱ۹��ڿ� ���� 
//  Param         :	CStringArray *pArr
//  Return        :	int 
//  Create        : ������ , 2006/05/18
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************

int GetKorControlItemArray(CStringArray *pArr)
{
	for(int i=0; i<g_arrFnControlIndex.GetSize(); i++)
	{
		FN_CONTROL_INDEX fnControlIndex = g_arrFnControlIndex.GetAt(i); 		
		pArr->Add(fnControlIndex.szKorControl); 
	}

	return g_arrFnControlIndex.GetSize(); 
}

//******************************************************************
//  Function Name : GetDataTypeIndexInArray
//  Function      : ���ڿ��� �������� �ε��� ����  
//  Param         :	CString strDataType
//  Return        :	int 
//  Create        : ������ , 2006/05/18
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
int GetDataTypeIndexInArray(CString strDataType) 
{ 
	for(int i=0; i<g_arrDataVal.GetSize(); i++)
	{
		CString strFnDataType = g_arrDataVal.GetAt(i);  
		if(strFnDataType == strDataType)
			return i; // TR_ITEM_DATA_TYPE���� ���� �� ������ ����   
	}

	 return FT_BYTE; 
}

//******************************************************************
//  Function Name : GetDataTypeItemInArray
//  Function      : �������� �ε����� �������� ���ڿ� ����  
//  Param         :	int nIndex
//  Return        :	CString
//  Create        : ������ , 2006/05/18
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString GetDataTypeItemInArray(int nIndex)
{
	if(nIndex<0 || nIndex>=g_arrDataVal.GetSize())
		return SZ_BYTE; 

	return g_arrDataVal.GetAt(nIndex); 
}
 
//******************************************************************
//  Function Name : GetDataLengthByNumbers
//  Function      : 2���� ������ ���� ������ ������ ���ڸ� ���ڿ��� ���� 
//  Param         : short data_len, short decimal_point
//  Return        :	CString
//  Create        : ������ , 2006/05/18
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString GetDataLengthByNumbers(short data_len, short decimal_point)
{
	CString strDataLen;
	if(decimal_point > 0)
	{
		strDataLen.Format("%d.%d", data_len, decimal_point); 
	}
	else 
	{
		strDataLen.Format("%d", data_len); 
	}

	return strDataLen; 
}

//******************************************************************
//  Function Name : GetTwoDataLengthNumbers
//  Function      : ������ ���� ������ ������ ���ڿ��� 2���� ���ڷ� ����  
//  Param         :	CString strDataLen, int *data_len, int *deciaml_point
//  Return        :	void
//  Create        : ������ , 2006/05/18
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
void GetTwoDataLengthNumbers(CString strDataLen, short *data_len, short *deciaml_point)
{
	int decimal_pos = strDataLen.Find('.', 0); 
	if(decimal_pos == -1)
	{
		*data_len = atoi(strDataLen); 
	}
	else
	{
// --> [Edit]  ��â�� 2006/08/28
		CString strTmpDataLen = strDataLen.Left(decimal_pos); 
//		CString strDecimalPoint = strTmpDataLen; 
		CString strDecimalPoint = strDataLen; 
		strDecimalPoint.Delete(0, decimal_pos+1); 

		*data_len = atoi(strTmpDataLen); 
		*deciaml_point = atoi(strDecimalPoint); 
// <-- [Edit]  ��â�� 2006/08/28
	}
}
 
//******************************************************************
//  Function Name : GetAttributeStringByVal 
//  Function      : ������ ���ڿ� ���� 
//  Param         :	short iAttribute
//  Return        :	CString
//  Create        : ������ , 2006/05/18
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString GetAttributeStringByVal(short iAttribute)
{
	if(iAttribute == ATTRIBUTE_NO)
	{
		return SZ_KOR_ATTRIBUTE_NO; 
	}
	else
	{
		return SZ_KOR_ATTRIBUTE_YES; 
	}
}

//******************************************************************
//  Function Name : GetAttributeValByString
//  Function      : ������ �� ����  
//  Param         :	CString strAttribute
//  Return        :	short
//  Create        : ������ , 2006/05/18
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
short GetAttributeValByString(CString strAttribute)
{
	strAttribute.TrimLeft(); 
	strAttribute.TrimRight(); 
	strAttribute.MakeLower(); 

	if(strAttribute == SZ_KOR_ATTRIBUTE_YES)
		return ATTRIBUTE_YES; 

	return ATTRIBUTE_NO; 	
}

//******************************************************************
//  Function Name : GetKorAttributeItemArray
//  Function      : ������ ���ڿ� ����Ʈ ���� 
//  Param         :	CStringArray *pArr
//  Return        :	void
//  Create        : ������ , 2006/05/18
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
void GetKorAttributeItemArray(CStringArray *pArr)
{
	pArr->Add(SZ_KOR_ATTRIBUTE_NO); 
	pArr->Add(SZ_KOR_ATTRIBUTE_YES); 
}

//******************************************************************
//  Function Name : GetTranCodeElements
//  Function      : Ʈ�� �ڵ带 ������ ���� ������ ���ڿ� ����Ʈ�� ���� 
//					Ʈ���ڵ� --> 'Ʈ�� ������', '��������', '�Է��ڵ�'   
//					��) 'MBCAOA001A01' --> 'MBCA', 'OA', '001A01' 
//  Param         :	CString strTrCode, CString &strDomain, CString &strService, CString &strCode
//  Return        :	BOOL
//  Create        : ������ , 2006/06/09
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
BOOL GetTranCodeElements(CString strTrCode, CString &strDomain, CString &strService, CString &strCode) 
{
	if(strTrCode.GetLength()<12)
	{
		return FALSE; 
	}

	strDomain = strTrCode.Left(4); 
	strService = strTrCode.Mid(4,2); 
	strCode = strTrCode.Mid(6,6); 

	return TRUE; 
}

//******************************************************************
//  Function Name : GetTranCodeByElements
//  Function      : Ʈ���ڵ� ��ҵ���� Ʈ���ڵ�� �����Ͽ� ����  
//  Param         :	CString strDomain, CString strService, CString strCode
//  Return        :	CString
//  Create        : ������ , 2006/06/09
//  Update        : ��ȣ��, 2009/09/25 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString GetTranCodeByElements(CString strDomain, CString strService, CString strCode) 
{  
	if(strDomain.GetLength() < 4)
		return ""; 

	if(strService.GetLength() < 2)
		return ""; 

	if(strCode.GetLength() < 6)
		return ""; 

	CString strTrCode;   
	strTrCode = strDomain.Left(4); 
	strTrCode += strService.Left(2); 
	strTrCode += strCode.Left(6); 

	return strTrCode; 
}





