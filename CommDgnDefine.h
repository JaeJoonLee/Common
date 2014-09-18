/******************************************************************************/
/**************************TRCode ���� ���************************************/
/******************************************************************************/
//	TRCode�� �� 4����Ʈ�� �����Ǿ� ������ ��(1)��(1)��(2)������ �����Ѵ�.
//	��з��δ� �Ʒ��� ���� �з��Ѵ�.
//	'M' : ������ ���
//	'U' : �Ϲ� ���� ���
//	'C' : ä�ÿ� ���� ���
//	'S' : �ܸ��� �ǽð� �ñ׳� ���
//	�ߺз��� �Һз��� �� ����ڰ� �����ϴ� ������ �Ѵ�.
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

#pragma pack(push, 1)

#define MAX_BUFFER_SIZE		1024

#define HEAD_LANGUAGE		1		// ���� 'E' : ����, 'K' : �ѱ���, 'J' : �Ͼ�
#define HEAD_TRCODE			4		// Transaction Code
#define HEAD_USERID			8		// �α��ν� ���� ����
#define HEAD_DUMMY			8		// ���� 

typedef struct tag_DATA_HEADER
{	
	int		nLength		;					// 4	��ű��� 
	BYTE  	chDataType	;					// 1    ������ Ÿ��(��ȸ,����, �ǽð�...)
	char	szLang		[HEAD_LANGUAGE];	// 1	�� 
	char	szTrCode	[HEAD_TRCODE];		// 4	Ʈ���ڵ� 
	char	szUserID	[HEAD_USERID];		// 8	����ھ��̵�
	short	nRQId		;					// 2	��ȸ���̵� 
	long	hWnd		;					// 4	�������ڵ� 
	int     nErrorCode	;					// 4	�����ڵ� 
	char	szDummy		[HEAD_DUMMY];		// 10	���� 	
	long	lDataLen	;					// 4	���� ������ ����
}DATA_HEADER, *LPDATA_HEADER;

#define DATA_HEAD_LEN		sizeof(DATA_HEADER)
#define HEAD_RCV_LENGTH 	sizeof(int)		// Packet�� ����(�ڽ��� ���̸� ������ ��ü ����)

#define RQDT_RQ			'R'			// ���ŵ����� 
#define RQDT_SD			'S'			// �۽ŵ����� 
#define RQDT_MESSAGE	'M'			// �޼��� 
#define RQDT_ERROR		'E'


#define DGN_LOG_DEBUG		0	// ����� ���� ������.
#define DGN_LOG_UM			1	// ����� �޼���.
#define DGN_LOG_STATUS		2	// ���� �޼���.
#define DGN_LOG_RQ			3	// ��ȸ.
#define DGN_LOG_RP			4	// ����.
#define DGN_LOG_SB			5	// ���� ���(�������� �ȿö�).
#define DGN_LOG_SBC			6	// ���� ����(�������� �ȿö�).
#define DGN_LOG_PB			7	// ����.


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
