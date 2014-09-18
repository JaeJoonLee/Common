#ifndef _INTERFACEDLL_H
#define _INTERFACEDLL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Designer에 I/O 정보 전달 */

/*-----------------------------------------------------------------
■ 기능 : 하나의 DSI(Blick I/O정보)를 전달
	Parameters
		- pDsi		: ReportShop에서 인식할 수 있는 DSI(Block I/O정보)
		- nDsiSize	: pDsi Buffer Size
	Return Values
		- 성공:1, 실패:0
-----------------------------------------------------------------*/
__declspec(dllimport) int rskSendDSI(char* pDsi, int nDsiSize);


/*-----------------------------------------------------------------
■ 기능 : 서비스의 I/O정보 (복수개의 DSI )를 전달
	Parameters
		- pDsi		:ReportShop에서 인식할 수 있는 여러 개의 DSI(Block I/O정보)
					 Block개수(5)|DSI 길이(5)|DSI|DSI 길이(5)|DSI …
		- nDsiSize	: pDsi Buffer Size
	Return Values
		- 성공:1, 실패:0
-----------------------------------------------------------------*/
__declspec(dllimport) int rskSendMultiDSI(char* pDsi, int nDsiSize);


/* 보고서 출력 */

/*-----------------------------------------------------------------
■ 기능 : 복수개의 Block Data를 가진 File(하나의 서비스 데이터)을 Block별로 나누어 각각 파일에 저장
	Parameters
		- pFormFile		: 폼파일(.rps) 이름(FullPath)
		- pDataFileName	: 복수의 Block의 Data를 가진 File명 (FullPath)
		- nBlock		: Block 개수
		- pDataSetName	: DataSet(Block) 이름 목록을 ","로 구분한 문자열을 DataFile에 저장된 순서대로 나열
							예) "DataSet1,DataSet2,DataSet3"
		- pDataSetFile	: 분리한 각 Block Data를 저장할 File명
							예) "DataSet1.dat,DataSet2.dat,DataSet3.dat"
	Return Values
		- 성공:1, 실패:0
	Remarks
		- pDataSetFile의 값이 NULL이면 폼파일에 저장되어 있는 datafile명 사용
-----------------------------------------------------------------*/
__declspec(dllimport) int rskSplitData(char* pFormFile, char *pUsrGroup, char* pDataFileName, int nBlock, char* pDataSetName, char* pDataSetFile);


/*-----------------------------------------------------------------
■ 기능 : Designer 또는 User Program에서 보고서 파일 생성 요청
	Parameters
		- pFormName		: 폼파일(.rps) 이름(FullPath)
		- pDataFileName	: DataFile명 list (DataSet명과 DataFile명이 연결된 정보의 list)
							예) "[DataSet이름1]=파일이름1,[DataSet이름2]=파일이름2,[DataSet이름3]=파일이름3"
		- pUserData		: 외부입력 Data
							Designer 또는 User Program가 직접 넘기는 Data (사용자 ID, 사용자 이름 등)
							예) UserData="MyID",UserPw="1234"
		- nPrintOpt		: 출력 Driver 선택
							1:PC Printer, 2:LP Printer, 3:Preview,
							4:Fax, 5:Mail, 6:Sool저장, 7:대화상자없이 PC Printer로 인쇄
		- pReportName	: 보고서 File명 (*.rpt)
	Return Values
		- 성공:1, 실패:0
-----------------------------------------------------------------*/
__declspec(dllimport) int rskPrintReport(char* pFormName, char* pDataFileName, char* pUserData, int nPrintOpt, char* pReportName);


/*-----------------------------------------------------------------
■ 기능 : Designer 또는 User Program에서 보고서 파일(.rpt) 출력 요청
	Parameters
		- pReportName	: 보고서 파일(.rpt) 이름
		- nFullPath		: 보고서 파일명의 FullPath여부
							0:상대경로(\Temp\*.rpt), 1:FullPath로 인식
		- nPrintOpt		: 출력Driver
							1:PC Printer, 2:LP Printer, 3:Preview,
							4:Fax, 5:Mail, 6:Sool저장, 7:대화상자없이 PC Printer로 인쇄
	Return Values
		- 성공:1, 실패:0	
-----------------------------------------------------------------*/
__declspec(dllimport) int rskPrintOut(char* pReportName, int nFullPath/*=0*/, int nPrintOpt/*=RPS_NONE*/);



/*-----------------------------------------------------------------
■ 기능 : Designer 또는 User Program에서 보고서 파일 생성 및 출력 요청
	Parameters
		- pFormName		: 폼파일(.rps) 이름(FullPath)
		- pDataFileName	: DataFile명
							예) "ReportData.txt"
		- pUserData		: 외부입력 Data
							Designer 또는 User Program가 직접 넘기는 Data (사용자 ID, 사용자 이름 등)
							예) UserData="MyID",UserPw="1234"
		- nPrintOpt		: 출력 Driver 선택
							1:PC Printer, 2:LP Printer, 3:Preview,
							4:Fax, 5:Mail, 6:Sool저장, 7:대화상자없이 PC Printer로 인쇄
		- pReportName	: 보고서 File명 (*.rpt)
		- nBlock		: DataFile에 포함된 Block 개수
		- pDataSetName	: DataSet(Block) 이름 목록을 ","로 구분한 문자열을 DataFile에 저장된 순서대로 나열
							예) "DataSet1,DataSet2,DataSet3"
	Return Values
		- 성공:1, 실패:0
-----------------------------------------------------------------*/
__declspec(dllimport) int rskPrintReportEx(char* pFormName, char *pUsrGroup, char* pDataFileName, char* pUserData, int nPrintOpt, char* pReportName, int nBlock, char* pDataSetName);

#ifdef __cplusplus
}
#endif


typedef int	(*FN_RSKSENDDSI) (char *, int );
typedef int	(*FN_RSKSENDMULTIDSI) (char *, int );
typedef int	(*FN_RSKSPLITDATA)(char* pFormFile, char *pUsrGroup,char* pDataFileName, int nBlock, char* pDataSetName, char* pDataSetFile);
typedef int	(*FN_RSKPRINTREPORT)(char* pFormName, char *pUsrGroup, char* pDataFileName, char* pUserData, int nPrintOpt, char* pReportName);
typedef int	(*FN_RSKPRINTOUT)(char* pReportName, int nFullPath, int nPrintOpt);
typedef int	(*FN_RSKPRINTREPORTEX)(char* pFormName, char *pUsrGroup, char* pDataFileName, char* pUserData, int nPrintOpt, char* pReportName, int nBlock, char* pDataSetName);
typedef int	(*FN_RSKCNVTDATASA)(char* pFormName, char *pUsrGroup, char* pDataSetName, SAFEARRAY* pData, char* pDataFile);


enum {
    RPS_NONE = 0,
    RPS_PC_PRINT,
    RPS_LP_PRINT,
    RPS_PC_PREVIEW,
    RPS_FAX,
    RPS_MAIL,
    RPS_SPOOL,
    RPS_LGF_FAX,
};


#endif /* _INTERFACEDLL_H */
