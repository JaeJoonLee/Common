#pragma once


// �����Ͱ� ��� ������, �������� ������.
#define WM_DEVICE_DATA				WM_USER + 649
// PORT
#define WM_BANKBOOK_WRITER_PORT		1
#define WM_CARDREADER_PORT			2

// �ֺ���ġ��
enum { DEVICE_NONE = 0,
		DEVICE_BANKBOOK_WRITER = 1,	// ���� �μ��
		DEVICE_CARD_READER,			// ī�� �νı�
		DEVICE_PINPAD,				// ���е�
		DEVICE_SCANNER,				// ��ĳ��
		DEVICE_CARD_ISSUER,			// ī�� �߱ޱ�
		DEVICE_CHECK_READER			// ��ǥ �νı�
		 };

/********************************************************************************/
/* ����																			*/
/********************************************************************************/
#define SNULL			_T("")
#define MAX_STRINGS     128
#define MAX_MSR_DATA    80

// ����
#define ERROR_NOTSELECT_DEVICE			11

#define INI_PATH						"\\DeviceCtrl\\"
#define TEMP_PATH						"\\Temp\\"
#define SCANNER_PATH					"Scanner\\"
#define LOG_PATH						"Log\\"

#define SEALFILE_NAME_GIF				"Seal.Gif"
#define SEALFILE_NAME_BMP				"Seal.Bmp"
#define SIGNFILE_NAME_GIF				"Sign.Gif"
#define SIGNFILE_NAME_BMP				"Sign.Bmp"
#define INIFILE_NAME					"KBCCard.ini"
#define LOGOFILE_NAME					""


// error�� 
#define ERROR_INIT_COMPORT				1
#define ERROR_READ_COMPORT_STATE		2
#define ERROR_WRITE_COMPORT_STATE		3
#define ERROR_OPEN_COMPORT				4
#define ERROR_POWER_ON					5
#define ERROR_EMPRY_PAPTER				6
#define ERROR_OPEN_COVER				7
#define ERROR_HANG_PAPER				8
#define ERROR_ABNORMAL					9

#define MESSAGE_BOTH					0
#define MESSAGE_ONLY					1
#define MESSAGE_LOG						2


/********************************************************************************/
/*	���� �μ��																	*/
/********************************************************************************/
// ���� MSR data ����
typedef struct {
    char szOldAccountNo[11+1];			// �������ȣ
    char szAccountNo[8+1];				// �����ȣ
    char szIssueCount[2+1];				// �߱�ȸ��
    char szIssueDate[8+1];				// �߱޳�¥
} BANKBOOK_MSR_DATA;

// �̺�Ʈ
#define USER_EVENT_MSR_ERROR			1
#define USER_EVENT_MSR_OK				2
#define USER_EVENT_INSERT_PAPER			3
#define USER_EVENT_EJECT_PAPER			4

// ����
#define PROCESS_NONE					0	// ó�� �����̴�.
#define PROCESS_INIT_COMPORT			1	// COM PORT�� �� �غ� �P���Ƶ�.
#define PROCESS_POWER_ON				2	// ������ ���� �ִ��� ������.
#define PROCESS_INSERT_PRINTING			3	// ������ ���ԵǾ� ���������غ� ������.

// ���� �μ�� ���� ����
#define ERROR_MSR_OK					0		// ����ó��
#define ERROR_MSR_NORMAL				-1      // �Ϲ����� ó������
#define ERROR_MSR_INVALID				-2      // Data ����
#define ERROR_MSR_MSRREAD				-3      // MSR Read ����
#define ERROR_MSR_MSRCHECK				-4      // MSR Write�� Check ����
#define ERROR_MSR_NOTOPEN				-5      // COM1 Port�� Open���� �ʾ���
#define ERROR_MSR_CANCEL				-6      // ����ڿ� ���� �۾����
#define ERROR_MSR_PARAMS				-7      // �Լ��� �Ķ��Ÿ ����

// ���� �μ�⿡ ������ ��ɰ���
#define BB_COMMAND						VK_ESCAPE	// ESC(0x1b)
#define BB_CMD_INSERT_PAPPER			'('		// '('
#define BB_CMD_GET_STATUS				'S'		// ���� ������ ���¸� ��´�.
#define BB_CMD_WRITE					't'		// �����Ϳ� ����.
#define BB_CMD_WRITE_ENDING				0x1d	// ������
#define BB_STS_EJECT_PAPER2				0x06	// eject paper
#define BB_CMD_GET_POWER				'Y'		// �������¸� ��´�.
#define BB_CMD_LINE_CURRENT				'I'		// ������
#define BB_CMD_EJECT_PAPER				'E'		// ������ �����Ѵ�.
#define BB_CMD_RESET_ERROR				'l'		// �������� ������ ���¸� Reset��
#define BB_CMD_CPI_10					'W'		// CPI 10
#define BB_CMD_CPI_12					'w'		// CPI 12
#define BB_CMD_LPI						'C'		// LPI 1
#define BB_CMD_LINE_SKIP1				0x0d	// Line skip
#define BB_CMD_LINE_SKIP2				0x0a	// Line skip
#define BB_CMD_LINE_BACKSKIP			'7'		// Line back skip
#define BB_CMD_WIDTH_DOUBLE				'D'		// ���� 2�� ����
#define BB_CMD_WIDTH_CANCEL				'd'		// ���� 2�� ���� ���
#define BB_CMD_INSERT_MSR				']'		// MSR�� ������ �ֵ��� ������ �� ���� �����Ѵ�.

// ���� �μ�Ⱑ �ִ� ���ϰ���
#define BB_STS_HOLD_PAPER				'P'		// ������ ���� �ִ� ����
#define BB_STS_AFTER_INSERTPAPER		'D'		// InsertPaper ȣ����
#define BB_STS_INSERT_PAPER				'%'		// ������ �����ִ� ���¿��� 0x1b(ESC), 0x28('(') ���۽� �߻�
#define BB_STS_EMPTY					'A'		// ��������
#define BB_STS_OPEN_COVER				'B'		// ���������� Ŀ������
#define BB_STS_HANG_PAPER				'F'		// ���������� �����ɸ�
#define BB_STS_ERROR1					'E'		// �߸𸣴� error
#define BB_STS_ERROR2					'J'		// �߸𸣴� error
#define BB_STS_POWER_ON					'W'		// �Ŀ� ����
#define BB_STS_MSR_ENDING				0x1c	// MSR DATA�� ������ �÷���
#define BB_STS_MSR_SCRATCH				0x7f	// MSR�� ��ó�� ���ų�


// ���ؽ� �̸�
#define BB_PRN_MUTEX  "BankBookPrinter_Mutex"


// �⺻ ������
#define RETRY_COUNT						3		// ������ ������ ��õ� Ƚ��
#define TIME_READ_MSR					10000	// Read Timeout 10��


/********************************************************************************/
/*	PINPAD																		*/
/********************************************************************************/
#define WM_KEYRESPONSE    WM_USER+646

// �̺�Ʈ
#define USER_EVENT_GET_PASSWORD			1

// PINPAD ���� ����
#define ERROR_PINPAD_OK					0		// ����ó��
#define ERROR_PINPAD_NOTFOUND_DLL		1		// DLL�� ����.
#define ERROR_PINPAD_FAIL_LOADING		2		// DLL�� ����.
#define ERROR_PINPAD_OPEN_COMPORT		3		// ��Ʈ�� ��������.
#define ERROR_PINPAD_INIT_COMPORT		4		// ��Ʈ�� �ʱ�ȭ�ϴµ� �����ߴ�.
#define ERROR_PINPAD_CLOSE_COMPORT		5		// ��Ʈ�� �ݴµ� �����ߴ�.
#define ERROR_PINPAD_READY_PASSWORD		6		// �н����带 �о���µ� �����ߴ�.
#define ERROR_PINPAD_NOTFOUND_PARAM		7		// ���� ��Ʈ���� �������� �ʾҽ��ϴ�.
/********************************************************************************/
/*	��ĳ��																		*/
/********************************************************************************/
#define SCAN_ALL							0
#define SCAN_SEAL							1
#define SCAN_SIGN							2

// Scanner ���� ����
#define ERROR_SCANNER_OK					1000		// �ΰ� ���� �̹��� ����.
#define ERROR_SCANNER_USER_CANCEL			1001		// ����ڰ� �����.
#define ERROR_SCANNER_NOT_CONNECT			1002		// ��ĳ�ʿ� ������� �ʾ���.
#define ERROR_SCANNER_FAILED_LOAD_DLL		1003		// DLL �δ��� ������.
#define ERROR_SCANNER_NOTFOUND_SEAL_SIGN	1009		// �ΰ� ���� �̹��� ���� ����
#define ERROR_SCANNER_SAVE_SEAL				1100		// �ΰ� �̹��� ���� 
#define ERROR_SCANNER_SAVE_SIGN				1200		// ���� �̹��� ����
#define ERROR_SCANNER_NOTFOUND_IMAGEFILE	1300		// �ΰ�, �������� ��ΰ� �����ϴ�.
#define ERROR_SCANNER_FAILED_BMP			1400		// BMP�� �� ����� �ΰ�, ���������� ǥ���ϴµ� �����߽��ϴ�.
#define ERROR_SCANNER_FAILED_BMP			1400		// BMP�� �� ����� �ΰ�, ���������� ǥ���ϴµ� �����߽��ϴ�.

#define ERROR_SCANNER_NOT_SET_IMAGEDEVICE	1		// BMP�� �� ����� �ΰ�, ���������� ǥ���ϴµ� �����߽��ϴ�.

// 
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D


#define BARCODE_LENGTH 9            
#define MAXBLOCK 1024

/********************************************************************************/
/*	ī��߱ޱ�																		*/
/********************************************************************************/

// ī��߱ޱ� ���� ����
#define ERROR_CARDISSUER_OK						0		// ����ó��
#define ERROR_CARDISSUER_NOTFOUND_DLL			1		// NectarCard.DLL�� ����.
#define ERROR_CARDISSUER_NOTFOUND_IMAGEFILE		2		// �ΰ��̳� ���������� ����.
#define ERROR_CARDISSUER_ERROR_DEVICE			-1		// �߱ޱ� ����, ����̹�, �����Ϳ���
#define ERROR_CARDISSUER_FAILED_FEEDING			-2		// ī���ǵ�����
#define ERROR_CARDISSUER_ERROR_MSR_DATA			-3		// MS ����(�߱ޱ� read/write ���� )
#define ERROR_CARDISSUER_ERROR_SYSTEM			-4 		// �ý��ۿ���
#define ERROR_CARDISSUER_ERROR_BRENCH_NUMBER	-5		// MS �������� (������ȣ)
#define ERROR_CARDISSUER_ERROR_TYPE				-6		// MS �������� (Type)

/********************************************************************************/
/*	��ǥ�νı�																	*/
/********************************************************************************/
#define ERROR_CHECKREADER_NOTFOUND_PARAM		1		// ��ǥ��ȣ�� ǥ���� ���� ��Ʈ���� �������� �ʾҽ��ϴ�.
#define ERROR_CHECKREADER_FAILED_CREATETHREAD	2		// ���� ���� - �����带 ����µ� �����߽��ϴ�.

#define CHECKDATA_LENGTH						38
#define WM_CHECK_DATA							WM_USER+648

typedef struct {
    char szCheckNo[8+1];				// ��ǥ��ȣ
    char szBankCode[2+1];				// �����ڵ�(����)
    char szBankBrenchCode[4+1];         // �����ڵ�
    char szBankNo[6+1];					// �����ȣ
    char szCheckCode[4+1];				// ��ǥ�ڵ�(����)
    char szCheckAmount[10+1];			// �ݾ�
} CHECK_DATA;

/********************************************************************************/
/*	ī�帮����																	*/
/********************************************************************************/
#define WM_CARDREADER_DATA    WM_USER+647

#define ERROR_CARDREADER_FAILED_OPEN			1		// ��Ʈ�� ���µ� �����߽��ϴ�.
#define ERROR_CARDREADER_FAILED_CREATE_THREAD	2		// ���� ���� - �����带 ����µ� �����߽��ϴ�.

typedef struct {
    char szCardType[1+1];            // ī�屸��
    char szCheckSum[2+1];            // ��ī�忡 ���� checksum
    char szUserType[2+1];            // ����ڱ���
    char szCardNo[8+1];              // ī���ȣ
    char szOldAccountNo[11+1];       // �����¹�ȣ
    char szIssuedCount[2+1];		 // �߱�ȸ��
} CARD_MSR_DATA;


/********************************************************************************/
