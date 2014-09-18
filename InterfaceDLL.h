#ifndef _INTERFACEDLL_H
#define _INTERFACEDLL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Designer�� I/O ���� ���� */

/*-----------------------------------------------------------------
�� ��� : �ϳ��� DSI(Blick I/O����)�� ����
	Parameters
		- pDsi		: ReportShop���� �ν��� �� �ִ� DSI(Block I/O����)
		- nDsiSize	: pDsi Buffer Size
	Return Values
		- ����:1, ����:0
-----------------------------------------------------------------*/
__declspec(dllimport) int rskSendDSI(char* pDsi, int nDsiSize);


/*-----------------------------------------------------------------
�� ��� : ������ I/O���� (�������� DSI )�� ����
	Parameters
		- pDsi		:ReportShop���� �ν��� �� �ִ� ���� ���� DSI(Block I/O����)
					 Block����(5)|DSI ����(5)|DSI|DSI ����(5)|DSI ��
		- nDsiSize	: pDsi Buffer Size
	Return Values
		- ����:1, ����:0
-----------------------------------------------------------------*/
__declspec(dllimport) int rskSendMultiDSI(char* pDsi, int nDsiSize);


/* ���� ��� */

/*-----------------------------------------------------------------
�� ��� : �������� Block Data�� ���� File(�ϳ��� ���� ������)�� Block���� ������ ���� ���Ͽ� ����
	Parameters
		- pFormFile		: ������(.rps) �̸�(FullPath)
		- pDataFileName	: ������ Block�� Data�� ���� File�� (FullPath)
		- nBlock		: Block ����
		- pDataSetName	: DataSet(Block) �̸� ����� ","�� ������ ���ڿ��� DataFile�� ����� ������� ����
							��) "DataSet1,DataSet2,DataSet3"
		- pDataSetFile	: �и��� �� Block Data�� ������ File��
							��) "DataSet1.dat,DataSet2.dat,DataSet3.dat"
	Return Values
		- ����:1, ����:0
	Remarks
		- pDataSetFile�� ���� NULL�̸� �����Ͽ� ����Ǿ� �ִ� datafile�� ���
-----------------------------------------------------------------*/
__declspec(dllimport) int rskSplitData(char* pFormFile, char *pUsrGroup, char* pDataFileName, int nBlock, char* pDataSetName, char* pDataSetFile);


/*-----------------------------------------------------------------
�� ��� : Designer �Ǵ� User Program���� ���� ���� ���� ��û
	Parameters
		- pFormName		: ������(.rps) �̸�(FullPath)
		- pDataFileName	: DataFile�� list (DataSet��� DataFile���� ����� ������ list)
							��) "[DataSet�̸�1]=�����̸�1,[DataSet�̸�2]=�����̸�2,[DataSet�̸�3]=�����̸�3"
		- pUserData		: �ܺ��Է� Data
							Designer �Ǵ� User Program�� ���� �ѱ�� Data (����� ID, ����� �̸� ��)
							��) UserData="MyID",UserPw="1234"
		- nPrintOpt		: ��� Driver ����
							1:PC Printer, 2:LP Printer, 3:Preview,
							4:Fax, 5:Mail, 6:Sool����, 7:��ȭ���ھ��� PC Printer�� �μ�
		- pReportName	: ���� File�� (*.rpt)
	Return Values
		- ����:1, ����:0
-----------------------------------------------------------------*/
__declspec(dllimport) int rskPrintReport(char* pFormName, char* pDataFileName, char* pUserData, int nPrintOpt, char* pReportName);


/*-----------------------------------------------------------------
�� ��� : Designer �Ǵ� User Program���� ���� ����(.rpt) ��� ��û
	Parameters
		- pReportName	: ���� ����(.rpt) �̸�
		- nFullPath		: ���� ���ϸ��� FullPath����
							0:�����(\Temp\*.rpt), 1:FullPath�� �ν�
		- nPrintOpt		: ���Driver
							1:PC Printer, 2:LP Printer, 3:Preview,
							4:Fax, 5:Mail, 6:Sool����, 7:��ȭ���ھ��� PC Printer�� �μ�
	Return Values
		- ����:1, ����:0	
-----------------------------------------------------------------*/
__declspec(dllimport) int rskPrintOut(char* pReportName, int nFullPath/*=0*/, int nPrintOpt/*=RPS_NONE*/);



/*-----------------------------------------------------------------
�� ��� : Designer �Ǵ� User Program���� ���� ���� ���� �� ��� ��û
	Parameters
		- pFormName		: ������(.rps) �̸�(FullPath)
		- pDataFileName	: DataFile��
							��) "ReportData.txt"
		- pUserData		: �ܺ��Է� Data
							Designer �Ǵ� User Program�� ���� �ѱ�� Data (����� ID, ����� �̸� ��)
							��) UserData="MyID",UserPw="1234"
		- nPrintOpt		: ��� Driver ����
							1:PC Printer, 2:LP Printer, 3:Preview,
							4:Fax, 5:Mail, 6:Sool����, 7:��ȭ���ھ��� PC Printer�� �μ�
		- pReportName	: ���� File�� (*.rpt)
		- nBlock		: DataFile�� ���Ե� Block ����
		- pDataSetName	: DataSet(Block) �̸� ����� ","�� ������ ���ڿ��� DataFile�� ����� ������� ����
							��) "DataSet1,DataSet2,DataSet3"
	Return Values
		- ����:1, ����:0
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
