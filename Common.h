#pragma once


// 데이터가 들어 왔을때, 메인으로 보낸다.
#define WM_DEVICE_DATA				WM_USER + 649
// PORT
#define WM_BANKBOOK_WRITER_PORT		1
#define WM_CARDREADER_PORT			2

// 주변장치들
enum { DEVICE_NONE = 0,
		DEVICE_BANKBOOK_WRITER = 1,	// 통장 인쇄기
		DEVICE_CARD_READER,			// 카드 인식기
		DEVICE_PINPAD,				// 핀패드
		DEVICE_SCANNER,				// 스캐너
		DEVICE_CARD_ISSUER,			// 카드 발급기
		DEVICE_CHECK_READER			// 수표 인식기
		 };

/********************************************************************************/
/* 공통																			*/
/********************************************************************************/
#define SNULL			_T("")
#define MAX_STRINGS     128
#define MAX_MSR_DATA    80

// 공통
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


// error들 
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
/*	통장 인쇄기																	*/
/********************************************************************************/
// 통장 MSR data 형식
typedef struct {
    char szOldAccountNo[11+1];			// 구통장번호
    char szAccountNo[8+1];				// 통장번호
    char szIssueCount[2+1];				// 발급회차
    char szIssueDate[8+1];				// 발급날짜
} BANKBOOK_MSR_DATA;

// 이벤트
#define USER_EVENT_MSR_ERROR			1
#define USER_EVENT_MSR_OK				2
#define USER_EVENT_INSERT_PAPER			3
#define USER_EVENT_EJECT_PAPER			4

// 순서
#define PROCESS_NONE					0	// 처음 상태이다.
#define PROCESS_INIT_COMPORT			1	// COM PORT를 쓸 준비를 긑마쳤따.
#define PROCESS_POWER_ON				2	// 전원이 켜져 있는지 점검함.
#define PROCESS_INSERT_PRINTING			3	// 용지가 삽입되어 프린팅할준비가 끝났다.

// 통장 인쇄기 오류 종류
#define ERROR_MSR_OK					0		// 정상처리
#define ERROR_MSR_NORMAL				-1      // 일반적인 처리오류
#define ERROR_MSR_INVALID				-2      // Data 오류
#define ERROR_MSR_MSRREAD				-3      // MSR Read 오류
#define ERROR_MSR_MSRCHECK				-4      // MSR Write후 Check 오류
#define ERROR_MSR_NOTOPEN				-5      // COM1 Port가 Open되지 않았음
#define ERROR_MSR_CANCEL				-6      // 사용자에 의한 작업취소
#define ERROR_MSR_PARAMS				-7      // 함수의 파라메타 오류

// 통장 인쇄기에 던지는 명령값들
#define BB_COMMAND						VK_ESCAPE	// ESC(0x1b)
#define BB_CMD_INSERT_PAPPER			'('		// '('
#define BB_CMD_GET_STATUS				'S'		// 현재 프린터 상태를 얻는다.
#define BB_CMD_WRITE					't'		// 프린터에 쓴다.
#define BB_CMD_WRITE_ENDING				0x1d	// 마지막
#define BB_STS_EJECT_PAPER2				0x06	// eject paper
#define BB_CMD_GET_POWER				'Y'		// 전원상태를 얻는다.
#define BB_CMD_LINE_CURRENT				'I'		// 현재줄
#define BB_CMD_EJECT_PAPER				'E'		// 용지를 배출한다.
#define BB_CMD_RESET_ERROR				'l'		// 프린터의 비정상 상태를 Reset함
#define BB_CMD_CPI_10					'W'		// CPI 10
#define BB_CMD_CPI_12					'w'		// CPI 12
#define BB_CMD_LPI						'C'		// LPI 1
#define BB_CMD_LINE_SKIP1				0x0d	// Line skip
#define BB_CMD_LINE_SKIP2				0x0a	// Line skip
#define BB_CMD_LINE_BACKSKIP			'7'		// Line back skip
#define BB_CMD_WIDTH_DOUBLE				'D'		// 넓이 2배 지정
#define BB_CMD_WIDTH_CANCEL				'd'		// 넓이 2배 지정 취소
#define BB_CMD_INSERT_MSR				']'		// MSR을 읽을수 있도록 통장을 더 깊이 삽입한다.

// 통장 인쇄기가 주는 리턴값들
#define BB_STS_HOLD_PAPER				'P'		// 용지를 물고 있는 상태
#define BB_STS_AFTER_INSERTPAPER		'D'		// InsertPaper 호출후
#define BB_STS_INSERT_PAPER				'%'		// 용지가 물려있는 상태에서 0x1b(ESC), 0x28('(') 전송시 발생
#define BB_STS_EMPTY					'A'		// 용지없음
#define BB_STS_OPEN_COVER				'B'		// 통장프린터 커버열림
#define BB_STS_HANG_PAPER				'F'		// 통장프린터 용지걸림
#define BB_STS_ERROR1					'E'		// 잘모르는 error
#define BB_STS_ERROR2					'J'		// 잘모르는 error
#define BB_STS_POWER_ON					'W'		// 파워 켜짐
#define BB_STS_MSR_ENDING				0x1c	// MSR DATA의 마지막 플래그
#define BB_STS_MSR_SCRATCH				0x7f	// MSR에 상처가 났거나


// 뮤텍스 이름
#define BB_PRN_MUTEX  "BankBookPrinter_Mutex"


// 기본 설정값
#define RETRY_COUNT						3		// 오류가 났을때 재시도 횟수
#define TIME_READ_MSR					10000	// Read Timeout 10초


/********************************************************************************/
/*	PINPAD																		*/
/********************************************************************************/
#define WM_KEYRESPONSE    WM_USER+646

// 이벤트
#define USER_EVENT_GET_PASSWORD			1

// PINPAD 오류 종류
#define ERROR_PINPAD_OK					0		// 정상처리
#define ERROR_PINPAD_NOTFOUND_DLL		1		// DLL이 없다.
#define ERROR_PINPAD_FAIL_LOADING		2		// DLL이 없다.
#define ERROR_PINPAD_OPEN_COMPORT		3		// 포트를 못열엇다.
#define ERROR_PINPAD_INIT_COMPORT		4		// 포트를 초기화하는데 실패했다.
#define ERROR_PINPAD_CLOSE_COMPORT		5		// 포트를 닫는데 실패했다.
#define ERROR_PINPAD_READY_PASSWORD		6		// 패스워드를 읽어오는데 실패했다.
#define ERROR_PINPAD_NOTFOUND_PARAM		7		// 연결 컨트롤을 설정하지 않았습니다.
/********************************************************************************/
/*	스캐너																		*/
/********************************************************************************/
#define SCAN_ALL							0
#define SCAN_SEAL							1
#define SCAN_SIGN							2

// Scanner 오류 종류
#define ERROR_SCANNER_OK					1000		// 인감 서명 이미지 저장.
#define ERROR_SCANNER_USER_CANCEL			1001		// 사용자가 취소함.
#define ERROR_SCANNER_NOT_CONNECT			1002		// 스캐너와 연결되지 않았음.
#define ERROR_SCANNER_FAILED_LOAD_DLL		1003		// DLL 로더에 실패함.
#define ERROR_SCANNER_NOTFOUND_SEAL_SIGN	1009		// 인감 서명 이미지 저장 없음
#define ERROR_SCANNER_SAVE_SEAL				1100		// 인감 이미지 저장 
#define ERROR_SCANNER_SAVE_SIGN				1200		// 서명 이미지 저장
#define ERROR_SCANNER_NOTFOUND_IMAGEFILE	1300		// 인감, 서명파일 경로가 없습니다.
#define ERROR_SCANNER_FAILED_BMP			1400		// BMP로 못 만들어 인감, 서명파일을 표시하는데 실패했습니다.
#define ERROR_SCANNER_FAILED_BMP			1400		// BMP로 못 만들어 인감, 서명파일을 표시하는데 실패했습니다.

#define ERROR_SCANNER_NOT_SET_IMAGEDEVICE	1		// BMP로 못 만들어 인감, 서명파일을 표시하는데 실패했습니다.

// 
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D


#define BARCODE_LENGTH 9            
#define MAXBLOCK 1024

/********************************************************************************/
/*	카드발급기																		*/
/********************************************************************************/

// 카드발급기 오류 종류
#define ERROR_CARDISSUER_OK						0		// 정상처리
#define ERROR_CARDISSUER_NOTFOUND_DLL			1		// NectarCard.DLL이 없다.
#define ERROR_CARDISSUER_NOTFOUND_IMAGEFILE		2		// 인감이나 서명파일이 없다.
#define ERROR_CARDISSUER_ERROR_DEVICE			-1		// 발급기 상태, 드라이버, 데이터오류
#define ERROR_CARDISSUER_FAILED_FEEDING			-2		// 카드피딩오류
#define ERROR_CARDISSUER_ERROR_MSR_DATA			-3		// MS 오류(발급기 read/write 오류 )
#define ERROR_CARDISSUER_ERROR_SYSTEM			-4 		// 시스템오류
#define ERROR_CARDISSUER_ERROR_BRENCH_NUMBER	-5		// MS 검증오류 (지점번호)
#define ERROR_CARDISSUER_ERROR_TYPE				-6		// MS 검증오류 (Type)

/********************************************************************************/
/*	수표인식기																	*/
/********************************************************************************/
#define ERROR_CHECKREADER_NOTFOUND_PARAM		1		// 수표번호를 표시할 연결 컨트롤을 설정하지 않았습니다.
#define ERROR_CHECKREADER_FAILED_CREATETHREAD	2		// 내부 오류 - 쓰레드를 만드는데 실패했습니다.

#define CHECKDATA_LENGTH						38
#define WM_CHECK_DATA							WM_USER+648

typedef struct {
    char szCheckNo[8+1];				// 수표번호
    char szBankCode[2+1];				// 은행코드(권종)
    char szBankBrenchCode[4+1];         // 지점코드
    char szBankNo[6+1];					// 은행번호
    char szCheckCode[4+1];				// 수표코드(권종)
    char szCheckAmount[10+1];			// 금액
} CHECK_DATA;

/********************************************************************************/
/*	카드리더기																	*/
/********************************************************************************/
#define WM_CARDREADER_DATA    WM_USER+647

#define ERROR_CARDREADER_FAILED_OPEN			1		// 포트를 여는데 실패했습니다.
#define ERROR_CARDREADER_FAILED_CREATE_THREAD	2		// 내부 오류 - 쓰레드를 만드는데 실패했습니다.

typedef struct {
    char szCardType[1+1];            // 카드구분
    char szCheckSum[2+1];            // 신카드에 대한 checksum
    char szUserType[2+1];            // 사용자구분
    char szCardNo[8+1];              // 카드번호
    char szOldAccountNo[11+1];       // 구계좌번호
    char szIssuedCount[2+1];		 // 발급회차
} CARD_MSR_DATA;


/********************************************************************************/
