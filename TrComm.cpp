//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (주)한국소리마치        
//******************************************************************
//  File Name     : TrComm.cpp
//  Function      : 
//  System Name   : KSBuilder
//  Create        : 김정원 , 2006/03/20
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
#include "stdafx.h"   
#include "CommDef.h"		// 공통헤더 정의 
#include "TrComm.h"			// 공통함수 정의 

// --> [Edit]  김정원 2006/05/11
#include "../builder/srshare/sd_global.h"		// 공통 파일 
// <-- [Edit]  김정원 2006/05/11

// 트리 컨트롤 편집창 활성화 시 라디오 및 콤보 컨트롤에 사용되는 문자열 리스트  
CStringArray g_arrDataVal;		//데이터 형 
// --> [Edit]  박 경 규 2006/09/19
CStringArray g_arrDBDataVal;	//DB데이터 형 
// <-- [Edit]  박 경 규 2006/09/19
CStringArray g_arrInOut;		//입출력 
CStringArray g_arrArray;		//배열 
 
// --> [Edit]  김정원 2006/05/16
// 글로벌 컨트롤 인덱스 리스트 
FN_CONTROL_INDEX_ARRAY g_arrFnControlIndex; 
// <-- [Edit]  김정원 2006/05/16

// --> [Edit]  김정원 2006/06/16
// 트랜 서버 타입 
CStringArray		g_arrTranServerType; 
CString			g_strDefTranServerType; 
// <-- [Edit]  김정원 2006/06/16

//******************************************************************
//  Function Name : InitEnumValList
//  Function      : 데이터 문자열, 컨트롤 문자열 리스트 초기화 함수 
//  Param         :	없음
//  Return        :	void
//  Create        : 김정원 , 2006/05/17
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void InitEnumValList()
{
	//데이터 형 
	g_arrDataVal.RemoveAll(); 
	g_arrDataVal.Add(SZ_BYTE);		// FT_BYTE(unsigned char(8bit))
	g_arrDataVal.Add(SZ_SHORT);		// FT_SHORT(int16)
	g_arrDataVal.Add(SZ_USHORT);	// FT_USHORT(unsigned int16)
	g_arrDataVal.Add(SZ_LONG);		// FT_LONG(int32)
	g_arrDataVal.Add(SZ_ULONG);		// FT_ULONG(unsigned int32)
	g_arrDataVal.Add(SZ_FLOAT);		// FT_FLOAT(float  (4 bytes))
	g_arrDataVal.Add(SZ_DOUBLE);	// FT_DOUBLE(double (8 bytes)) 
	g_arrDataVal.Add(SZ_LONGLONG);	// FT_LONGLONG(8 bytes)   
	g_arrDataVal.Add(SZ_STRING);  	// FT_STRING(텍스트)
	g_arrDataVal.Add(SZ_STRINGNUM); // FT_STRINGNUM(텍스트)
	g_arrDataVal.Add(SZ_DATE);		// FT_DATE(날자형)
	g_arrDataVal.Add(SZ_DAY);		// FT_DAY(일자형)
	g_arrDataVal.Add(SZ_TIME);		// FT_TIME(시간형)      
	
// --> [Edit]  박 경 규 2006/09/19
	//DB데이터 형 
	g_arrDBDataVal.RemoveAll(); 
	g_arrDBDataVal.Add("char");  
	g_arrDBDataVal.Add("varchar"); 
	g_arrDBDataVal.Add("numeric");  
	g_arrDBDataVal.Add("int"); 
	g_arrDBDataVal.Add("text"); 
	g_arrDBDataVal.Add("datetime"); 
	g_arrDBDataVal.Add("image"); 
// <-- [Edit]  박 경 규 2006/09/19


	//컨트롤 형 인덱스 리스트  
	/*
		파일 '실행폴더\dgn\system\TranItemCtrl.Ini'에 정의된 컨트롤 리스트를 로드하여 	
		TrBuilder에서 개발자들이 정의된 컨트롤 리스트 범위에서 선택하게 한다. 
	*/ 
	
	// 실행 프로그램 파일 경로 
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
				
				// 데이터 끝 
				if(bNull && ch=='\0')
				{
					break; 
				}

				// 널문자인 경우 지금까지의 데이터를 (키,값) 정보 데이터 함 
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

	//입출력 
	g_arrInOut.RemoveAll(); 
	g_arrInOut.Add(SZ_KOR_IN_RECORD); 
	g_arrInOut.Add(SZ_KOR_OUT_RECORD); 

	//배열 
	g_arrArray.RemoveAll(); 
	g_arrArray.Add(SZ_KOR_SINGLE_RECORD); 
	g_arrArray.Add(SZ_KOR_ARRAY_RECORD); 


	//트랜 서버 타입 리스트 			
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
//  Function      : 유틸리티 함수 - 라인문자열을 파싱
//  Param         :	 CString sLine, CStringArray* pArray
//  Return        :	int
//  Create        : 김정원 , 2006/05/17
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int GetTrLineData( CString sLine, CStringArray* pArray )
{
	// 파일에서 읽어서 ( "\r\n", ",", 등으로 구분 ) 스트링리스트에 넣는다.
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
//  Function      : 문자열 리스트에서 문자열과 일치하는 인덱스 쿼리 
//  Param         :	CStringArray &arrItem, CString strItem
//  Return        :	int
//  Create        : 김정원 , 2006/05/17
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 인덱스에 대응하는 문자열 
//  Param         :	CStringArray &arrItem, int nIndex
//  Return        :	CString
//  Create        : 김정원 , 2006/05/17
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Create        : 박 경 규 , 2006/09/19
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 연동 컨트롤 리스트에서 문자열과 일치하는 인덱스 쿼리 
//  Param         :	CString strItem
//  Return        :	int
//  Create        : 김정원 , 2006/05/17
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 연동 컨트롤 리스트에서 문자열과 일치하는 인덱스 쿼리 
//  Param         :	int nIndex
//  Return        :	CString
//  Create        : 김정원 , 2006/05/17
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 연동 컨트롤 리스트에서 입력 인자 번째에 대응하는 컨트롤 인덱스 쿼리 
//  Param         :	int nOrder
//  Return        :	int
//  Create        : v
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 연동 컨트롤 리스트에서 입력 인자 번째에 대응하는 컨트롤 문자열 쿼리 
//  Param         :	int nOrder
//  Return        :	CString
//  Create        : 김정원 , 2006/05/17
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 모든 연동 컨트롤 리스트 문자열 쿼리 
//  Param         :	CStringArray *pArr음
//  Return        :	int
//  Create        : 김정원 , 2006/05/17
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 연동 컨트롤 리스트에서 인덱스에 일치하는 한글문자열 쿼리 
//  Param         :	int nIndex
//  Return        :	CString
//  Create        : 김정원 , 2006/05/17
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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

	return CString("사용안함");
}

//******************************************************************
//  Function Name : GetKorControlIndexInArray
//  Function      : 연동 컨트롤 리스트에서 한글문자열과 일치하는 인덱스 쿼리 
//  Param         :	CString strKorItem
//  Return        :	int
//  Create        : 김정원 , 2006/05/17
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 연동 컨트롤 리스트에서 입력 인자 번째에 대응하는 
//					컨트롤 한글 문자열 쿼리 
//  Param         :	int nOrder
//  Return        :	CString 
//  Create        : 김정원 , 2006/05/18
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 모든 연동 컨트롤 리스트 한글문자열 쿼리 
//  Param         :	CStringArray *pArr
//  Return        :	int 
//  Create        : 김정원 , 2006/05/18
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 문자열로 데이터형 인덱스 쿼리  
//  Param         :	CString strDataType
//  Return        :	int 
//  Create        : 김정원 , 2006/05/18
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
int GetDataTypeIndexInArray(CString strDataType) 
{ 
	for(int i=0; i<g_arrDataVal.GetSize(); i++)
	{
		CString strFnDataType = g_arrDataVal.GetAt(i);  
		if(strFnDataType == strDataType)
			return i; // TR_ITEM_DATA_TYPE에서 정의 된 값으로 리턴   
	}

	 return FT_BYTE; 
}

//******************************************************************
//  Function Name : GetDataTypeItemInArray
//  Function      : 데이터형 인덱스로 데이터형 문자열 쿼리  
//  Param         :	int nIndex
//  Return        :	CString
//  Create        : 김정원 , 2006/05/18
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 2개의 데이터 길이 정보를 가지는 숫자를 문자열로 리턴 
//  Param         : short data_len, short decimal_point
//  Return        :	CString
//  Create        : 김정원 , 2006/05/18
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 데이터 길이 정보를 가지는 문자열을 2개의 숫자로 리턴  
//  Param         :	CString strDataLen, int *data_len, int *deciaml_point
//  Return        :	void
//  Create        : 김정원 , 2006/05/18
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
// --> [Edit]  김창하 2006/08/28
		CString strTmpDataLen = strDataLen.Left(decimal_pos); 
//		CString strDecimalPoint = strTmpDataLen; 
		CString strDecimalPoint = strDataLen; 
		strDecimalPoint.Delete(0, decimal_pos+1); 

		*data_len = atoi(strTmpDataLen); 
		*deciaml_point = atoi(strDecimalPoint); 
// <-- [Edit]  김창하 2006/08/28
	}
}
 
//******************************************************************
//  Function Name : GetAttributeStringByVal 
//  Function      : 색정보 문자열 리턴 
//  Param         :	short iAttribute
//  Return        :	CString
//  Create        : 김정원 , 2006/05/18
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 색정보 값 리턴  
//  Param         :	CString strAttribute
//  Return        :	short
//  Create        : 김정원 , 2006/05/18
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 색정보 문자열 리스트 리턴 
//  Param         :	CStringArray *pArr
//  Return        :	void
//  Create        : 김정원 , 2006/05/18
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
//  Comment       : 
//******************************************************************
void GetKorAttributeItemArray(CStringArray *pArr)
{
	pArr->Add(SZ_KOR_ATTRIBUTE_NO); 
	pArr->Add(SZ_KOR_ATTRIBUTE_YES); 
}

//******************************************************************
//  Function Name : GetTranCodeElements
//  Function      : 트랜 코드를 다음과 같이 구분한 문자열 리스트로 리턴 
//					트랜코드 --> '트랜 도메인', '서비스종류', '입력코드'   
//					예) 'MBCAOA001A01' --> 'MBCA', 'OA', '001A01' 
//  Param         :	CString strTrCode, CString &strDomain, CString &strService, CString &strCode
//  Return        :	BOOL
//  Create        : 김정원 , 2006/06/09
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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
//  Function      : 트랜코드 요소들들을 트랜코드로 조합하여 리턴  
//  Param         :	CString strDomain, CString strService, CString strCode
//  Return        :	CString
//  Create        : 김정원 , 2006/06/09
//  Update        : 김호겸, 2009/09/25 VS 2008 Upgrade를 위한 작업
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





