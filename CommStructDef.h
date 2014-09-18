#if !defined(_COMMSTRUCTDEF_H_)
#define _COMMSTRUCTDEF_H_

#pragma warning (disable:4786)

// 벡트 테이블 정의 
#include <vector>
#include <algorithm>
#include <functional>
#include "commheaderdef.h"
#include "kscommon.h"

using namespace std;

#if !defined(_WIN32_WCE)
#pragma pack(push, 1)
#endif

// FIDLIST는 벡터 테이블을 이용한다.
#if !defined(_WIN32_WCE)
	typedef std::vector<char*>					CHARVECTOR;
	typedef std::vector<std::vector<char*> >	CHARVECTOR2;
	typedef CHARVECTOR::iterator				CHARVECTORIT;
	typedef CHARVECTOR2::iterator				CHARVECTOR2IT;
#else
	typedef std::vector<TCHAR*>					CHARVECTOR;
	typedef std::vector<std::vector<TCHAR*> >	CHARVECTOR2;
	typedef CHARVECTOR::iterator				CHARVECTORIT;
	typedef CHARVECTOR2::iterator				CHARVECTOR2IT;
#endif

typedef std::vector<string> VTSTRING;
typedef std::vector<std::vector<string> > VTSTRING2;

// 트랜인 경우 각 ItemSize에 사용한다.
typedef std::vector<unsigned short> SHORTVECTOR;
typedef std::vector<std::vector<unsigned short> > SHORTVECTOR2;
// 컨트롤 윈도우핸들에 사용한다. 
typedef std::vector<HWND> HWNDVECTOR;
typedef std::vector<long> LONGVECTOR;

typedef HWNDVECTOR::iterator HWNDVECTORIT;
typedef LONGVECTOR::iterator LONGVECTORIT;

////////////////////////////////////////////////////////////////////
// 조회 정보 트랜입력 구조체 정의 
////////////////////////////////////////////////////////////////////

#define USERID_LEN		8
#define PASSWD_LEN		8
#define IPADDR_LEN		15
#define SYSTIME_LEN		14

////////////////////////////////////////////////////////////////////
// 조회응답 데이터를 컨트롤(1개의 레코드)에 전달하는 구조체
// 트랜과 FID 공용으로 사용한다.
////////////////////////////////////////////////////////////////////
typedef struct REPLYDATA
{
	int				nRQID;					// 조회ID
	int				nRpKind;				// REQUEST_KIND
	char			szTrCode[TRCODE_SIZE];	// TRCode
	int             nMsgLen;
	char*           lpMsg;
	long			nDataSize;				// 데이터 사이즈(트랜인 경우 가변적으로 예외처리를 하는 경우 사이즈 필요함)	
	char *			m_pData;

} REPLYDATA_st, *LPREPLYDATA;

typedef struct tagRPDATA
{
	int				nRpKind;					// 0: 트랜, 1 : FID
												// 트랜 정보만 사용 
	int				nNextFlag;					// (Tran)허용 : 0 -> 이전다음 없음, 1-> 다음있음, 2->이전있음. 3 ->다음 이전있음.
	char			szTrCode[TRCODE_SIZE + 1];	// TRCode
	long			pRecordInfo;				// 레코드 정보(데이터 파싱을 위한 트랜 정보)
	long			pItemInfo;					// Item 정보(데이터 파싱을 위한 트랜 정보)
	int				nDataCount;					// 단일레코드 이면 1
	long			nDataLen;					// 데이터 사이즈 = 데이터개수* 레코드 길이  
	char*			pData;						// 실제 데이터 
												// Fid 정보 		
	CString			strSaveBuf;					// SaveBuf
	CHARVECTOR2		vvRpValueList;				// 출력 데이터의 DataList
	// 챠트에서 이중키 처리를 위해 RQ이름까지 모아서 전달한다.
	CString			strRQName;					// 통신 RQ명
} RPDATA_st, *LPRPDATA;

////////////////////////////////////////////////////////////////////
// 데이터 헤더 (그리드 형)
// FID인 경우 반복되는 데이터에는 입/출력에 반드시 추가 된다.
// 트랜인 경우에는 사용하지 않는다. 
// 데이터 전문에 포함된다.
////////////////////////////////////////////////////////////////////
#define n_GRH_ONEBYTE			1
#define n_GRH_NROW				4
#define n_GRH_SAVELEN			3
#define n_GRH_DLEN				8

// FID 통신인경우 데이타부의 FID헤더 구조를 갖는다.
typedef struct _REQUEST_IO_GRID
{
	char	conti[1];					// 0: 연속없음, 1: 연속 있음.
	BYTE	szcontiKey[79];				// 이전 / 다음 처리시 서버 프로그램에서 사용할 내부 버퍼

//	BYTE	ucGRDC[n_GRH_ONEBYTE];		// 그리드임을 알리는 특수문자 '$' 고정
//	BYTE	ucDLEN[n_GRH_DLEN];			// 데이터 길이(Fid리스트,출력 데이터)
//	BYTE	ucNROW[n_GRH_NROW];			// 요구 레코드 수 / 유효 레코드 수 
//	BYTE	ucAKEY[n_GRH_ONEBYTE];		// 송신 발생시의 ACTION
//										// '0' : Enter, '1' : 이전조회, '2' : 다음조회  
//
//	BYTE	ucSTAT[n_GRH_ONEBYTE];		// 수신시에 필요한 FLAG
//										// 0x40 : 항상 SET, 0x01 : 이전 Enable, 0x02 : 다음 Enable
//	BYTE	ucSAVELen[n_GRH_SAVELEN];	// 이전 / 다음 처리시 서버 프로그램에서 사용할 내부 버퍼
} REQUEST_IO_GRID_st, *LPREQUEST_IO_GRID_st;
/////////////////////////////////////////////////////////////////////
// WM_GET_MSG
// 메세지 구조체
#define n_MSGCD_SIZE	5
#define n_MSGLEN_SIZE   2

typedef struct REPLYMSG
{
	BYTE			ucErrFlag;
	char			nexttp;
	BYTE			MsgCd[n_MSGCD_SIZE+1];	// 메세지 코드
	BYTE*			lpMsg;					// 에러 메세지
} REPLYMSG_st, *LPREPLYMSG;

////////////////////////////////////////////////////////////////////
// 등록할 리얼의 갯수는 vMajorMinorIDList.size로 알 수 있다.
// 시세 데이터를 CLIENT에  등록하는 구조체
// 각 리스트의 첨수가 같은 경우 같은 항목으로 간주한다.
////////////////////////////////////////////////////////////////////
typedef struct _REAL_CLIENT_REG
{
	CHARVECTOR  vGubunList;				// 구분자 리스트 
										// "ABC", "A", "B" 일 경우
										// A등록키값[0], B등록키값[0], C등록키값[0] ...로 등록한다.
	CHARVECTOR  vKeyValueList;			// KeyValue
	CHARVECTOR  vGubunKeyValueList;		// 구분자 + 코드
	CHARVECTOR2 vvItemList;				// 출력 FID LIST
										// 등록 키값 vFidValueList[0]의 출력 포맷은
										// vvFidList[0]에 대응 됨.
	CHARVECTOR2 vvAttriList;			// 출력 아이템 attribute LIST
	SHORTVECTOR	vSequence;				// Insert형에서 조회 데이터의 위치를 지정함.
} REAL_CLIENT_REG_st, *LP_REAL_CLIENT_REG_st;

////////////////////////////////////////////////////////////////////
// 리얼데이터를 컨트롤(1개의 레코드)에 전달하는 구조체
// 트랜과 FID 공용으로 사용한다.
////////////////////////////////////////////////////////////////////
#define MAX_KEYVALUESIZE 41	// (계좌번호+종목코드+매매구분)

// 자동갱신 
typedef struct REALDATA
{
	char		szKeyCode[32];	// 종목코드(모든시장)
	BYTE		chRealType;		// 자동갱신 타입 
	BYTE		chCount;		// 자동갱신 개수 
	short       nSize;			// 자동갱신 구조체 사이즈 

	char*       pDataBuf;		// 실제 데이터 
	long		lRealStruct;	// 자동갱신 구조체 ( 구조체에 대한 Pointer )


	int			nPoolDataUse;						// 공유시세사용유무 
	int			nQueDataCount;						// 큐데이터 건수 
	int			nTotalCount;						// 자동갱신 전체개수 
	int			nCurIndex;							// 현재처리 인덱스 
	int			nSharedReal;						// 공유메모리 사용 
	char*       pSharedRealBuf;						// 공유메모리 데이터 
} REALDATA_st, *LPREALDATA;

// 리얼 등록/해제 구조체
typedef struct REALREGIN_1
{
	UCHAR		ucAutoFlag;		// 1:등록, 2:해제
	UCHAR		ucFiller;		
	short		nCodeCnt;	// 종목수	//LJP 20110527
	//	(REAL_REG_IN_2가 ucCodeCnt 만큼 반복)
} REAL_REG_IN_1;

typedef struct REALREGIN_2
{
	UCHAR		ucMarketFlag;	// 장구분	
	// '1':종목,					'2':업종,				'3':선물,						'4':옵션,
	// '5':채권,					'6':제3시장,			'7':수익증권,					'8':신주인수권,
	// '9':kfx선물,					'A':해외지수,			'B':ecn,						'C':온라인투자상담,
	// 'D',주식옵션,				'E':투자자별,			'F':예상지수,					'G':ECN업종,
	// 'H':프로그램사전공시종목,	'I':종목별 증거금율,	'J':시간외단일가매매가능종목,	'K':FOCHT,
	// 'L':STAR지수선물,			'M':종목별종목군,		'N':상품선물,					'O':상품옵션,
	// 'P':상품현물,				'S':조건/뉴스시그널
	UCHAR		ucRealType;		// 장구분에 따른 자동 갱신 목록
	// 0x01 : 예상체결
	// 0x02 : 10호가
	// 0x04 : 시세, 시장베이시스
	// 0x08 : 내재변동성, 장내NAV, FOCHT_LIVE_JISU
	// 0x10 : 시세변동, ELW투자지표, 호가분석, FOCHT_JISU
	// 0x20 : 거래원, 예상지수, 뉴스시그널, FOCHT_For000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	// 0x40 : 호가, 업종등락, ECN예상지수, 조건신호(시스템), FOCHT_OIX
	// 0x80 : 체결, 업종지수, 조건신호(사용자), FOCHT_RATION
	UCHAR		ucFiller[2];
	UCHAR		ucCode[12];		// 종목코드
} REAL_REG_IN_2;

// 일반메모(키는 수정일시)
class CGMemoData: public CObject
{
public:
	char* pFmtDate;	// 정형화된 수정일시
	char* pMemo;	// 내용
	char* pTitle;	// 제목
};

// 종목메모(키는 종목코드)
class CMemoData: public CObject
{
public:
	char* pMemo;	// 메모 데이터
};

typedef struct _REQUEST_COMMINFO
{
	char		cTrCode[TRCODE_SIZE + 1];
	char        sSCRN[SCRN_LEN + 1];
	TR_HEADER	TrHeader;
	BYTE		cFIDCommGB;			// FID 통신구분		('0':TR통신,1:FID통신)
	BYTE		cMsgId;				// 통신구분, DM_ID
	BYTE		cCommandId;			// 통신 구분자.(PID)

	BYTE		cRqId;				// CommApi에서 데이타 요청시 셋트함.
	HWND		hRQRPWnd;			// 통신을 요청한 윈도우 핸들

	char		cJobChk[1];			// [서버:1, 원장서버:2, 마스터서버:3
									// 업무용tab:4, 시스템트레이딩:5, 업무용string:6)
									// 호가변동:7, 메모리DB:8, 스탑로스서버:9]

	char		cContChk[1];		// TR조회시 이전/다음을 표시하는값,
										// SERVER: 이전, 이후 버튼 enable 여부
										// CLIENT: 이전, 이후 data 요청(data 항목에 필요시 종목코드를 올린다)
										// 0:전후 Disable, 1:전Enable, 2:후Enable, 3:전후Enable
										// 옵션 data가 있을 경우 : 옵션 data 다음에 온다(이전 이후 key data가)
										// 옵션 data가 없을 경우 : data 부분에 온다.
	char		sRecCnt[RECSIZE + 1];	// 레코드건수
	char		sSeq[2];			// 오류체크,TR구분
	char		sHold[1];			// 착오주문	: 직원 보류여부	(Y:보류, N:)
	// 턱시도 헤더 트랜구분용
	char		cTranGB[1];			// "A 자동주문",	"M 수동주문",	"U Update성",	"V 수동조회"
	char		cBenefit;			// 'Y' : 수익증권통장, 'N' : 아님
	char		cExistRequestCheck;	// 'N' : 서비스와입력값이 동일해도 서버로 보냄
}REQUEST_COMMINFO;

// Common Header
typedef struct tagCommonHeader
{
	ULONG		ulPacketLen;	// 패킷의 전체 Size
	ULONG		ulRqId;			// Packet Unique Key값( Packet Sequence ID )
	
	// bit단위 처리
	// 압축 | 암호화 | 0x20 | 압축시더작은경우 | packet시작 | packet연속 | packet끝 | 0x01
	BYTE		cCpFlag;
	BYTE		cCommandId;		// 단말과 서버 Process Command
	BYTE		cErrComm;
	BYTE		cServerType;	// 1:default, 2:신업무서버, 3:DB서버
	ULONG		ulWinHwnd;		// (서버에서 클라이언트로 내려오는 자동 갱신 data는 0)
} COMMONHEADER, *LPCOMMONHEADER;
// Tr Header
typedef struct tagTrHeader
{
	BYTE			cTRCode[TRCODE_SIZE];	// TR번호
	BYTE			cBenefit;				// 수익증권여부(Y:수익증권, N:아님)
	BYTE			cNextPrev;				// TR조회시 이전/다음을 표시하는값,
											// SERVER: 이전, 이후 버튼 enable 여부
											// CLIENT: 이전, 이후 data 요청(data 항목에 필요시 종목코드를 올린다)
											// 0:전후 Disable, 1:전Enable, 2:후Enable, 3:전후Enable
											// 옵션 data가 있을 경우 : 옵션 data 다음에 온다(이전 이후 key data가)
											// 옵션 data가 없을 경우 : data 부분에 온다.
	
	BYTE			cTrErrorFlag;			// '0':정상, '1':에러 ==> 메세지code로 pc에서 출력
											// '2':정상, '3':에러 ==> Data 부분에 80 Byte의 메세지 출력[MSG(80 Byte) + Data]
	BYTE			cErrCode[ERRCODE_SIZE];	// 오류코드
	ULONG			ulTrBodySize;			// C->S(옵션길이:이전이후 key data가 있을 경우도 포함)
											// S->C(압축전의 전체 data 길이)
} TRHEADER, *LPTRHEADER;

// 분할 전송 시 사용 함
#define CHAIN_TR_HEADER_SIZE		sizeof(TRHEADER) - 3
typedef struct tagCLIENT_CHAIN_PKT
{
	char			TrHeader[CHAIN_TR_HEADER_SIZE];
	char			cFrameNo[6];		//
	char			cFrameSize[6];
	char			cBlockSize[6];		// 2048
	char			cUniqID[32];
	char			cOrgSize[12];		// 압축전 크기
	char			cCompressSize[12];
} CLIENT_CHAIN_PKT;

typedef struct tagTranHeader
{
	COMMONHEADER	commhdr;	// 공통	헤더.
	TRHEADER		trhdr;		// TR	헤더.
} TRANHEADER, *LPTRANHEADER;
/*
// Packet = Header + Data
typedef struct tagSockPacket
{
	COMMONHEADER	commhdr;
	TRHEADER		trhdr;		// TR	헤더.

} SOCK_PACKET, *LPSOCK_PACKET;
*/

// --> [Edit]  강지원 2010/08/25
// DownLoad Version Header ( 한화증권 사용 )
typedef struct tagVER_DOWNHEADER
{
	char		cSize[6];		// Data Size
	char		cError[4];		// error
	char		cDataID[2];		// 
	char		cNext[1];		// 0:end, 1:continue
	char		cType[2];		// 파일 구분 ( 서버에 올려준 값을 그대로 다시 받아서 처리한다. )
	char		cFiller[1];		// filler
} VER_DOWNHEADER, *LPVER_DOWNHEADER;

#define VER_DOWNHEADER_SIZE			sizeof(VER_DOWNHEADER)

typedef struct tagVER_DOWNHEADER_INREC
{
	char   Spcdirnm[512];			/* PC디렉토리명 	*/
	char   Ssvrdirnm[512];			/* SVR디렉토리명 	*/
	char   Sfilenm[256];			/* 파일명 			*/
	char   Sfiller[4];				/* FILLER 			*/
	short  Wseq_no;
	char   Sfiller2[2];
} VER_DOWNHEADER_INREC, *LPVER_DOWNHEADER_INREC;

#define VER_DOWNHEADER_INREC_SIZE	sizeof(VER_DOWNHEADER_INREC)

typedef struct tagVER_DOWNHEADER_OUTREC
{
	char   Cerrflg;					/* 정상유무 '0':정상 '1':에러 */
	char   Smsgcode[5];				/* 메세지코드 		*/
	short  Wseq_no;
	char   Spcdirnm[512];			/* PC디렉토리명 	*/
	char   Ssvrdirnm[512];			/* SVR디렉토리명 	*/
	char   Sfilenm[256];   			/* 파일명 			*/
	int    Ifsize;					/* 파일크기 		*/
} VER_DOWNHEADER_OUTREC, *LPVER_DOWNHEADER_OUTREC;

#define VER_DOWNHEADER_OUTREC_SIZE	sizeof(VER_DOWNHEADER_OUTREC)

//	IP를 2개로 랜덤하게 사용하기위해서 클래스로 만든다.
//	통신에서 사용하는 통신환경 정보 클래스	( 한화증권 사용 )
#define		MAINIP_CNT	2
class MAIN_PORT
{
public:
	MAIN_PORT()
	{
		m_nMainPort[0]		= 0;	//8080;		
		m_nMainPort[1]		= 0;	//6789;		

		m_nPortPosition		= 0;
	};
	virtual ~MAIN_PORT() {}

	//	메인 Port를 리턴한다.
	int	GetMainPort()
	{
		return m_nMainPort[m_nPortPosition];
	};

	void NextPortPostion()
	{
		m_nPortPosition = (m_nPortPosition + 1) % 2;
	};

public:
	int			m_nMainPort[2];			// 접속서버 Port번호
	int			m_nPortPosition;
};

class COMMS_CONFIG
{
public:
	COMMS_CONFIG()
	{
		m_nCONNECT_TYPE		= 1;	

		for ( int i = 0 ; i < MAINIP_CNT ; i++ )
			m_strMainIP[i]		= "";		
	
		m_bUseSubPort		= 0;
		m_bUseEncrypt		= 1;		
		m_nSpeedCheckCount	= 20000;
		m_nMakeSubDir		= 1;		
		m_nMaxRetryCount	= 3;	
		m_nKeyChangeTimeOut	= 3;
		m_bLogWrite			= 0;		
		m_bConsol			= 0;			
		m_bBccUse			= 1;
		m_bIPShare			= 0;

		m_nIPPosition		= 0;
		m_nMessageOpen		= 0;		//	접속 IP 확인용 플래그
		m_strHTSType		= "서버";

		m_nIndexDataPort	= 0;	//KJI 20110725 (로그인전 지수 데이터 처리용)	
		GetStartIPPostion();
	};
	virtual ~COMMS_CONFIG() {}

	//	메인 IP를 리턴한다.
	CString	GetMainIP()
	{
		return m_strMainIP[m_nIPPosition];
	};

	//	메인 Port를 리턴한다.
	int	GetMainPort()
	{
		//KJI 20110725 (로그인전 지수 데이터 처리용)
		int nRetPort = 0;

		if(	m_nIndexDataPort == 0)
			nRetPort = m_csMainPort[m_nIPPosition].GetMainPort();
		else
		{
			nRetPort = m_nIndexDataPort;
			m_bBccUse = 0;
		}

		return nRetPort;
	};

	void NextIPPostion()
	{
		m_nIPPosition = (m_nIPPosition + 1) % MAINIP_CNT;
	};

	void NextPortPostion()
	{
		for ( int i = 0 ; i < MAINIP_CNT ; i++ )
			m_csMainPort[i].NextPortPostion();
		
	};

	void GetStartIPPostion()
	{
		// 20090910  JJH  본사/백업센터 구분을 렌덤함수로 교체
		srand(GetTickCount());	// Seed 초기화
		int nRandom = rand();
		m_nIPPosition = (nRandom % MAINIP_CNT);
	};

public:
	int			m_nCONNECT_TYPE;		// 0:지점, 1:HTS, 2:call center 3:미니HTS
	CString		m_strMainIP[MAINIP_CNT];// 접속서버 IP명
	MAIN_PORT	m_csMainPort[2];		// 접속서버 Port번호
	int			m_nSubPort;				// Main Port로 접속이 안될때 사용하는 포트
	BOOL		m_bUseSubPort;
	BOOL		m_bUseEncrypt;			// 암호화 유무
	int			m_nSpeedCheckCount;
	int			m_nMakeSubDir;			// 통신 API인경우 서브 디렉토리를 생성 안할려구...
	int			m_nMaxRetryCount;		// 최대재 접속 수 
	int			m_nKeyChangeTimeOut;	// 키 교환 타임아웃 
	BOOL		m_bLogWrite;			// 로그파일 작성여부(1:작성, 그외:무시)
	BOOL		m_bConsol;				// ConSol화면으로 데이터 표시 여부
	BOOL		m_bBccUse;
	BOOL		m_bIPShare;

	int			m_nIndexDataPort;		//KJI 20110725 (로그인전 지수 데이터 처리용)

	//	IP선택 포지션
	int			m_nIPPosition;

	//	접속 IP 확인용 플래그
	int			m_nMessageOpen;

	//	Tray Icon에 표시될 HTS 타입
	CString		m_strHTSType;
};
/*
// 통신에서 사용하는 통신환경 정보 구조체
typedef struct COMMS_CONFIG
{
	int			m_nCONNECT_TYPE;		// 0:지점, 1:HTS, 2:call center 3:미니HTS
	CString		m_strMainIP;			// 접속서버 IP명
	int			m_nMainPort;			// 접속서버 Port번호
	int			m_nSubPort;				// Main Port로 접속이 안될때 사용하는 포트
	BOOL		m_bUseSubPort;
	BOOL		m_bUseEncrypt;			// 암호화 유무
	int			m_nSpeedCheckCount;
	int			m_nMakeSubDir;			// 통신 API인경우 서브 디렉토리를 생성 안할려구...
	int			m_nMaxRetryCount;		// 최대재 접속 수 
	int			m_nKeyChangeTimeOut;	// 키 교환 타임아웃 
	BOOL		m_bLogWrite;			// 로그파일 작성여부(1:작성, 그외:무시)
	BOOL		m_bConsol;				// ConSol화면으로 데이터 표시 여부
	BOOL		m_bBccUse;
	BOOL		m_bIPShare;
} COMMS_CONFIG;
*/
// <-- [Edit]  강지원 2010/08/25
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// 로그인 과정에서 사용하는 구조체 /////////////////////////////
typedef struct _REVERSION_INFO
{
	char	cFiller[10];
	char	cBackupChangeGb;	// 백업전환구분
	char	cFiller_1;
	char	cServerName[20];	// 서버이름
	long	lPid;
	long	lIdOffset;
	char	cServerDate[8];		// 서버날짜[8]
	char	cNameSeq[15];
	char 	cExceptMsgCode[5];	// 백업전환메세지코드
} REVERSION_INFO;

////////////////////////////////// 고객/지점 로그인 in/out /////////////////////////////
// LogIn 정보
typedef struct _LOGININFO
{
	BYTE	suser_id[12];			// 사용자 ID 
	BYTE	spasswd[16];				// 비밀번호
	BYTE	sucrayer;				// 회원구분('1':임시회원 '2':HTS회원), 일단 2로 넣는다.
	BYTE	sip_address[15];		// IP주소
	BYTE	susergubun[3];			// 사용자구분
	BYTE	ucSiseUse;				// 시세전용여부
	BYTE	ucProgramType;			// 사용프로그램종류(전문가, 표준, 직장인)
	BYTE	sFiller[48];
	BYTE	sServerUse[20 + 8];
	BYTE	sLoginFlag;
	BYTE	sCertFlag;
	BYTE	sPassFlag;
	//[PMI]LJP 20120329 Start-->
	BYTE	sUserDivInfo[60];		// 금융거래 지정 장치 정보 ex) IP, MAC, PHONE 등등(기본3개까지)
	//<--End
} LOGIN_IN;

// sign된 데이타
//BYTE	sSignLen[4];			
//BYTE	sSignData[2048];		

struct USER_INFO
{	
    UCHAR   ucSvrFlag;			// 서버구분 DB:'1'
	UCHAR   ucMultiFlag;		// 다중접속 허용여부 ‘Y’=허용 ‘N’ =불가
    UCHAR   ucStockLoan;		// Stock Loan 관리자 등급 '1':관리자
    UCHAR   ucSysFlag;			// 시스템트래이딩 교육이수여부 : Y:이수, N:미이수
    UCHAR   ucLogidFlag;		// 로그인방법 : ID:I, 계좌:G
    UCHAR   ucKwansimFlag;		// 관심변동 사용가능한 계좌여부 : Y:가능 N:불가
    UCHAR   ucHtsFlag;			// HTS부가서비스 가입여부 => Y:가입, N:미가입
    UCHAR   ucJnum[13];			// 주민번호/사업자번호
    UCHAR   ucLogMedia;			// 최종접속매체 => 1:HTS, 2:WEB
    UCHAR   ucLogDate[20];		// 최종접속시간 => yyyy/mm/dd hh:mi:ss
    UCHAR   ucName[40];			// ID의 이름/법인명

	UCHAR   ucSessionId[8];		// HTS서버에서 관리하는 세션의 Unique한 ID => 공개키관리용
	UCHAR   ucCertUse_f;		// 인증서사용여부 => Y:인증서필수, N:인증서 미사용
    UCHAR   ucCertReg_f;		// 인증서발급필요여부
	// 0:발급불필요 1:신규발급요 2:재발급요 3: 사용정지 4:갱신요
   	UCHAR   ucPubKeyLen[4];     // KJI 20110907 (공인인증 고도화) 공개키값 길이 1024bit => 140 / 2048bit => 270
	UCHAR   ucDn[256];			// 인증서 DN값( 40 ~ 256 Byte) : Char
//	UCHAR   ucPubKey[140];
    UCHAR   ucPubKey[270];		// KJI 20110907 (공인인증 고도화, 270변경) 공개키값(Public Key)=>Binary:140byte(권장),Char:186byte
    UCHAR   ucLogin_f;			// 로그인구분 => 0.1차로그인결과 1.2차로그인결과

	UCHAR   ucPubc_yn;			// 인증서발급여부
    UCHAR   ucCert_sta;			// 인증서상태 : 0[인증서발급가능:신원확인한 경우]
    UCHAR   ucGame_f;			// 모의투자게임여부 ‘Y’: 모의게임 ‘N’: 상용
    UCHAR   ucFiller2[4];
	// 전자서명 적용으로 인해 추가된 항목-종료
    UCHAR   ucAutoStock_yn;		// AUTO-STOCK 사용여부 => 2003.04.14  추가
	UCHAR   ucCertErrFlag;		// 공인인증 비상여부 Y:비상, N:정상
	UCHAR   ucFirewall;			// 개인방화벽 사용여부 Y:비상, N:정상
    UCHAR   ucFiller3[32];		// filler 50Byte -> 10Byte로 축소 : name때문에 42->35->34        
};

#define ACCOUNT_LEN			12
typedef struct _USER_ACC_INFO
{
    UCHAR   ucFiller1;
    UCHAR   ucSflag;				// 은행선물계좌 위험고지 여부 Y:고지, N:미고지 2002.9.10 추가
    UCHAR   ucAflag;				// 금융법인 'Y':금융법인 'N':아님
    UCHAR   ucBflag;				// 대표계좌 'Y':대표계좌 'N':아님 'X':타인명의계좌
    UCHAR   ucCflag;				// 증거금미징수 'Y':증거금미징수 'N':아님
    UCHAR   ucDflag;				// 자사주계좌여부 '0':해당없슴 '1':일반법인 '2':증권사자체
    UCHAR   ucEflag;				// 수익증권통장여부 'Y':금융법인 'N':아님
    UCHAR   ucFflag;				// HTS등록여부 'Y':등록 'N':미등록
	 //[PMI]LJP 20120327 Start-->
	UCHAR   ucGflag;                 /* 1:한화증권, 2:한화투자증권*/
  	UCHAR   ucHflag;                 /* Y:은행연계계좌, N:지점개설계좌*/
	UCHAR   ucIflag;                 /* 계좌타입 1:위탁, 2:저축, 3:선물, 4:수익증권, 5:CD, 6:CP, 7:RP, 8:일임형랩, 9:신탁계좌 */
  	//<--End
    UCHAR   ucAccNo[ACCOUNT_LEN];	// 계좌번호
} USER_ACC_INFO;

typedef struct _LOGUSERINFO		
{
	BYTE			ucUserID[12];		// 사용자 ID
	BYTE			ucUserRayer;		// 사용자구분('0':투자정보 '1':HTS)
	BYTE			ucUserLevel;		// 사용자 등급['1':관리자(ID가 099로 시작) '2':개인사용자 
										// '3':기관사용자 '4':GUEST '6':준회원(계좌미보유)]
	USER_INFO		UserInfo;			// 530 byte
	BYTE			ucAccNum[4];		// 계좌갯수

	USER_ACC_INFO	AccInfo[100];		// 계좌정보
	BYTE			ucFiller[48];		// 뭔지 정확히 모른다 함.

	BYTE			ucServer[20];		// 서버명
	DWORD			dwPID;				// PID
	DWORD			dwID_OFF;			// ID_OFF
	BYTE			ucDate[8];
	BYTE			ucNameSeq[15];
	BYTE			ucUserIP[16];		// 사용자 IP
	BYTE			ucUserPasswd[8];	// 사용자 비밀번호
	BYTE			ucHKTradeUse;		// Filler 자리를 사용 개발범위 축소
} LOGIN_OUT;

// --> [Edit]  이도영 2010/09/30
// 이글용 로그인 구조체
typedef struct _LOGUSER_EAGLE
{
	BYTE			ucUserID[9];		// 사용자 ID
	BYTE			ucName[20];			// 사용자명
	BYTE			ucUserLayer;		// 사용자구분
	BYTE			ucUserGrade[3];		// 사용자Grade
	BYTE			ucServerGuBun;		// (방카스랑스 관련등급 추가)
	BYTE			ucTemp;				// 이건 뭔지 설명도 없다. 젠장 암튼 메뉴 권한에 사용
	BYTE			ucFiller1[2591];	// KJI 20110907 공인인증 고도화 (2561 -> 2691)
//	BYTE			ucFiller1[2561];	// KJI 20110907 공인인증 고도화 (2561 -> 2691)
	BYTE			ucServer[20];		// 서버명
	DWORD			dwPID;				// PID
	DWORD			dwID_OFF;			// ID_OFF
	BYTE			ucDate[8];
	BYTE			ucNameSeq[15];
	BYTE			ucUserIP[16];		// 사용자 IP
	BYTE			ucUserPasswd[8];	// 사용자 비밀번호
	BYTE			ucFiller2[1];		// 이건 뭔지 설명도 없다.
	BYTE			ucHostIP[15];		// HOST IP
}LOGUSER_EAGLE;
// <-- [Edit]  이도영 2010/09/30

///////////////////////////// 지점용 BP 로그인 in/out //////////////////////////////

// LogIn 정보
typedef struct _LOGININFO_STAFF
{
	BYTE	suser_id[9];			// 사용자 ID(사번)
	BYTE	sip_address[15];		// IP주소('.'은 제거, 3자리씩 총12자리)
	BYTE	spasswd[16];				// 비밀번호
} LOGIN_STAFF_BP_IN;

typedef struct _LOGUSERINFO_STAFF
{
//	BYTE	ucMessage[80];			// 에러 메세지
	BYTE	ucUserID[9];			// 사용자 ID
	BYTE	ucIPAddr[15];			// 사용자 IP
	BYTE	ucPassWord[8];			// 비밀번호
	BYTE	ucUserNM[20];			// 사용자 NM
	BYTE	ucTnbCode[3];			// 처리점(소속점)
	BYTE	ucTnbName[20];			// 초리점명
	BYTE	ucUserGroup[4];			// 사용자 그룹
	BYTE	ucUserLevel[1];			// 사용자 권한
	BYTE	ucChngDT[8];			// 날짜
	BYTE	ucServerName[20];		// 서버명
	BYTE	ucServerDay[8];			// 날짜
	BYTE	ucServerTime[6];		// 시간
	BYTE	ucIsPWGubun[1];			// 비밀오류여부
	BYTE	ucIsChangePW[1];		// 비밀번호변경여부
	BYTE	ucMVTradeUse[1];		// 해외시세사용여부
	BYTE	ucHKTradeUse[1];		// 홍콩주문사용여부
	BYTE	ucCHTradeUse[1];		// 중국주문사용여부
	BYTE	ucFiller[6];			//
} LOGIN_STAFF_BP_OUT;

#define RQ_COMMINFO_SIZE			sizeof(REQUEST_COMMINFO)
#define HEADER_SIZE					sizeof(COMMONHEADER) + sizeof(TRHEADER)
#define COMMON_HEADER_SIZE			sizeof(COMMONHEADER)
#define TR_HEADER_SIZE				sizeof(TRHEADER)

#define	SIZE_DEF_PACKET				4		// packet 전체 길이 부분
#define	LOGIN_IN_SIZE				sizeof(LOGIN_IN)
#define LOGIN_OUT_SIZE				sizeof(LOGIN_OUT)
#define LOGIN_OUT_BP_SIZE			sizeof(LOGIN_STAFF_BP_OUT)

#if !defined(_WIN32_WCE)
#pragma pack(pop)
#endif
#endif // !defined(_COMMSTRUCTDEF_H_)
