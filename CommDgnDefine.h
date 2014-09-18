/******************************************************************************/
/**************************TRCode 생성 방법************************************/
/******************************************************************************/
//	TRCode는 총 4바이트로 구성되어 있으며 대(1)중(1)소(2)구분을 생성한다.
//	대분류로는 아래와 같이 분류한다.
//	'M' : 관리자 기능
//	'U' : 일반 유저 기능
//	'C' : 채팅에 관한 기능
//	'S' : 단말에 실시간 시그널 기능
//	중분류와 소분류는 각 담당자가 정리하는 것으로 한다.
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

#pragma pack(push, 1)

#define MAX_BUFFER_SIZE		1024

#define HEAD_LANGUAGE		1		// 언어구분 'E' : 영어, 'K' : 한국어, 'J' : 일어
#define HEAD_TRCODE			4		// Transaction Code
#define HEAD_USERID			8		// 로그인시 값을 전송
#define HEAD_DUMMY			8		// 더미 

typedef struct tag_DATA_HEADER
{	
	int		nLength		;					// 4	통신길이 
	BYTE  	chDataType	;					// 1    데이터 타입(조회,응답, 실시간...)
	char	szLang		[HEAD_LANGUAGE];	// 1	언어값 
	char	szTrCode	[HEAD_TRCODE];		// 4	트랜코드 
	char	szUserID	[HEAD_USERID];		// 8	사용자아이디
	short	nRQId		;					// 2	조회아이디 
	long	hWnd		;					// 4	윈도우핸들 
	int     nErrorCode	;					// 4	에러코드 
	char	szDummy		[HEAD_DUMMY];		// 10	더미 	
	long	lDataLen	;					// 4	실제 데이터 길이
}DATA_HEADER, *LPDATA_HEADER;

#define DATA_HEAD_LEN		sizeof(DATA_HEADER)
#define HEAD_RCV_LENGTH 	sizeof(int)		// Packet의 길이(자신의 길이를 제외한 전체 길이)

#define RQDT_RQ			'R'			// 수신데이터 
#define RQDT_SD			'S'			// 송신데이터 
#define RQDT_MESSAGE	'M'			// 메세지 
#define RQDT_ERROR		'E'


#define DGN_LOG_DEBUG		0	// 디버그 전용 데이터.
#define DGN_LOG_UM			1	// 사용자 메세지.
#define DGN_LOG_STATUS		2	// 상태 메세지.
#define DGN_LOG_RQ			3	// 조회.
#define DGN_LOG_RP			4	// 응답.
#define DGN_LOG_SB			5	// 리얼 등록(서버에는 안올라감).
#define DGN_LOG_SBC			6	// 리얼 삭제(서버에는 안올라감).
#define DGN_LOG_PB			7	// 리얼.


// CommAPI<->Comms
typedef struct tagCommInterface
{
	long			hRecvWnd;
	int				nTimeout;	
	int				nRQID;
}DGNCOMMINTERFACE,*LPDGNCOMMINTERFACE;

#define		DGN_COMMINTERFACE_LEN	sizeof(DGNCOMMINTERFACE)


//-------------------------------------
#define		_TOK_GS			0x1D
#define		_TOK_RS			0x1E
#define		_TOK_US			0x1F
//-------------------------------------

#pragma pack(pop)
