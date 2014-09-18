#ifndef _TRBUILDER_COMM_H_
#define _TRBUILDER_COMM_H_


#include "DgnSvrComm.h"		// 서버트랜 정의    
#include "../Builder/DgnDBConnect/DBConnExport.h"
#include <afxtempl.h>
// 공통함수

//--------------------------------------------------------------------//
// --> [Edit]  김정원 2006/05/15
// 데이터 및 콘트롤 문자열 리스트 초기화 
void InitEnumValList(); 

// 문자라인 --> 토큰 리스트 
int GetTrLineData( CString sLine, CStringArray* pArray );

// 문자열 리스트에서 문자열과 일치하는 인덱스 쿼리 
int GetIndexInArray(CStringArray &arrItem, CString strItem); 

// 인덱스에 대응하는 문자열 
CString GetItemInArray(CStringArray &arrItem, int nIndex); 
CString GetDBDataTypeString(CStringArray &arrItem, int nType, int nLen, int nDecimal);
// <-- [Edit]  김정원 2006/05/15
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
// --> [Edit]  김정원 2006/05/16
// 연동 컨트롤 리스트에서 문자열과 일치하는 인덱스 쿼리 
int GetControlIndexInArray(CString strItem); 

// 연동 컨트롤 리스트에서 인덱스이 일치하는 문자열 쿼리 
CString GetControlItemInArray(int nIndex); 

// 연동 컨트롤 리스트에서 입력 인자 번째에 대응하는 컨트롤 인덱스 쿼리 
int GetControlIndexByOrder(int nOrder);  

// 연동 컨트롤 리스트에서 입력 인자 번째에 대응하는 컨트롤 문자열 쿼리 
CString GetControlItemByOrder(int nOrder);  

// 모든 연동 컨트롤 리스트 문자열 쿼리 
int GetControlItemArray(CStringArray *pArr);  
// <-- [Edit]  김정원 2006/05/16
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
// --> [Edit]  김정원 2006/05/17
// 연동 컨트롤 리스트에서 인덱스에 일치하는 한글문자열 쿼리 
CString GetKorControlItemInArray(int nIndex); 

// 연동 컨트롤 리스트에서 한글문자열과 일치하는 인덱스 쿼리 
int GetKorControlIndexInArray(CString strKorItem); 
// <-- [Edit]  김정원 2006/05/17
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
// --> [Edit]  김정원 2006/05/18
// 연동 컨트롤 리스트에서 한글 입력 인자 번째에 대응하는 컨트롤 문자열 쿼리 
CString GetKorControlItemByOrder(int nOrder);   
// 모든 연동 컨트롤 리스트 한글문자열 쿼리 
int GetKorControlItemArray(CStringArray *pArr);  
 
// 문자열로 데이터형 인덱스 쿼리  
int GetDataTypeIndexInArray(CString strDataType); 
// 데이터형 인덱스로 데이터형 문자열 쿼리  
CString GetDataTypeItemInArray(int nIndex); 

// 2개의 데이터 길이 정보를 가지는 숫자를 문자열로 리턴 
CString GetDataLengthByNumbers(short data_len, short decimal_point);   
// 데이터 길이 정보를 가지는 문자열을 2개의 숫자로 리턴  
void GetTwoDataLengthNumbers(CString strDataLen, short *data_len, short *deciaml_point); 

//색정보 문자열 리턴 
CString GetAttributeStringByVal(short iAttribute); 
//색정보 값 리턴  
short GetAttributeValByString(CString strAttribute); 
//색정보 문자열 리스트 리턴 
void GetKorAttributeItemArray(CStringArray *pArr); 
// <-- [Edit]  김정원 2006/05/18 
//--------------------------------------------------------------------//


//--------------------------------------------------------------------//
// 트랜 코드를 다음과 같이 구분한 문자열 리스트로 리턴 
// 트랜코드 --> '트랜 도메인', '서비스종류', '입력코드'   
// 예) 'MBCAOA001A01' --> 'MBCA', 'OA', '001A01' 
BOOL GetTranCodeElements(CString strTrCode, CString &strDomain, CString &strService, CString &strCode); 

// 트랜코드 요소들들을 트랜코드로 조합하여 리턴  
CString GetTranCodeByElements(CString strDomain, CString strService, CString strCode); 
 
// 트리 컨트롤 편집창 활성화 시 라디오 및 콤보 컨트롤에 사용되는 문자열 리스트  
extern CStringArray g_arrDataVal;		//데이터 형 
// --> [Edit]  박 경 규 2006/09/19
extern CStringArray g_arrDBDataVal;	//DB데이터 형 
// <-- [Edit]  박 경 규 2006/09/19
extern CStringArray g_arrInOut;		//입출력 
extern CStringArray g_arrArray;		//배열 
 

// --> [Edit]  김정원 2006/05/16
// FN 신시스템에서 정의한 컨트롤과 디자인 빌더와의 연동을 위한 구조체 
typedef struct tagFN_CONTROL_INDEX
{
	int		index; 
	char	szControl[255]; 
	char	szKorControl[255]; 
}FN_CONTROL_INDEX; 

// 컨트롤 인덱스 데이터 리스트 
typedef CArray<FN_CONTROL_INDEX, FN_CONTROL_INDEX> FN_CONTROL_INDEX_ARRAY; 

// 글로벌 컨트롤 인덱스 리스트 
extern FN_CONTROL_INDEX_ARRAY g_arrFnControlIndex; 
// <-- [Edit]  김정원 2006/05/16

// --> [Edit]  김정원 2006/06/16
// 트랜 서버 타입 
extern CStringArray		g_arrTranServerType; 
extern CString			g_strDefTranServerType; 
// <-- [Edit]  김정원 2006/06/16


#endif 