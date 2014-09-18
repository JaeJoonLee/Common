#if !defined(_COMMSTRUCTDEF_H_)
#define _COMMSTRUCTDEF_H_

#pragma warning (disable:4786)

// ��Ʈ ���̺� ���� 
#include <vector>
#include <algorithm>
#include <functional>
#include "commheaderdef.h"
#include "kscommon.h"

using namespace std;

#if !defined(_WIN32_WCE)
#pragma pack(push, 1)
#endif

// FIDLIST�� ���� ���̺��� �̿��Ѵ�.
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

// Ʈ���� ��� �� ItemSize�� ����Ѵ�.
typedef std::vector<unsigned short> SHORTVECTOR;
typedef std::vector<std::vector<unsigned short> > SHORTVECTOR2;
// ��Ʈ�� �������ڵ鿡 ����Ѵ�. 
typedef std::vector<HWND> HWNDVECTOR;
typedef std::vector<long> LONGVECTOR;

typedef HWNDVECTOR::iterator HWNDVECTORIT;
typedef LONGVECTOR::iterator LONGVECTORIT;

////////////////////////////////////////////////////////////////////
// ��ȸ ���� Ʈ���Է� ����ü ���� 
////////////////////////////////////////////////////////////////////

#define USERID_LEN		8
#define PASSWD_LEN		8
#define IPADDR_LEN		15
#define SYSTIME_LEN		14

////////////////////////////////////////////////////////////////////
// ��ȸ���� �����͸� ��Ʈ��(1���� ���ڵ�)�� �����ϴ� ����ü
// Ʈ���� FID �������� ����Ѵ�.
////////////////////////////////////////////////////////////////////
typedef struct REPLYDATA
{
	int				nRQID;					// ��ȸID
	int				nRpKind;				// REQUEST_KIND
	char			szTrCode[TRCODE_SIZE];	// TRCode
	int             nMsgLen;
	char*           lpMsg;
	long			nDataSize;				// ������ ������(Ʈ���� ��� ���������� ����ó���� �ϴ� ��� ������ �ʿ���)	
	char *			m_pData;

} REPLYDATA_st, *LPREPLYDATA;

typedef struct tagRPDATA
{
	int				nRpKind;					// 0: Ʈ��, 1 : FID
												// Ʈ�� ������ ��� 
	int				nNextFlag;					// (Tran)��� : 0 -> �������� ����, 1-> ��������, 2->��������. 3 ->���� ��������.
	char			szTrCode[TRCODE_SIZE + 1];	// TRCode
	long			pRecordInfo;				// ���ڵ� ����(������ �Ľ��� ���� Ʈ�� ����)
	long			pItemInfo;					// Item ����(������ �Ľ��� ���� Ʈ�� ����)
	int				nDataCount;					// ���Ϸ��ڵ� �̸� 1
	long			nDataLen;					// ������ ������ = �����Ͱ���* ���ڵ� ����  
	char*			pData;						// ���� ������ 
												// Fid ���� 		
	CString			strSaveBuf;					// SaveBuf
	CHARVECTOR2		vvRpValueList;				// ��� �������� DataList
	// íƮ���� ����Ű ó���� ���� RQ�̸����� ��Ƽ� �����Ѵ�.
	CString			strRQName;					// ��� RQ��
} RPDATA_st, *LPRPDATA;

////////////////////////////////////////////////////////////////////
// ������ ��� (�׸��� ��)
// FID�� ��� �ݺ��Ǵ� �����Ϳ��� ��/��¿� �ݵ�� �߰� �ȴ�.
// Ʈ���� ��쿡�� ������� �ʴ´�. 
// ������ ������ ���Եȴ�.
////////////////////////////////////////////////////////////////////
#define n_GRH_ONEBYTE			1
#define n_GRH_NROW				4
#define n_GRH_SAVELEN			3
#define n_GRH_DLEN				8

// FID ����ΰ�� ����Ÿ���� FID��� ������ ���´�.
typedef struct _REQUEST_IO_GRID
{
	char	conti[1];					// 0: ���Ӿ���, 1: ���� ����.
	BYTE	szcontiKey[79];				// ���� / ���� ó���� ���� ���α׷����� ����� ���� ����

//	BYTE	ucGRDC[n_GRH_ONEBYTE];		// �׸������� �˸��� Ư������ '$' ����
//	BYTE	ucDLEN[n_GRH_DLEN];			// ������ ����(Fid����Ʈ,��� ������)
//	BYTE	ucNROW[n_GRH_NROW];			// �䱸 ���ڵ� �� / ��ȿ ���ڵ� �� 
//	BYTE	ucAKEY[n_GRH_ONEBYTE];		// �۽� �߻����� ACTION
//										// '0' : Enter, '1' : ������ȸ, '2' : ������ȸ  
//
//	BYTE	ucSTAT[n_GRH_ONEBYTE];		// ���Žÿ� �ʿ��� FLAG
//										// 0x40 : �׻� SET, 0x01 : ���� Enable, 0x02 : ���� Enable
//	BYTE	ucSAVELen[n_GRH_SAVELEN];	// ���� / ���� ó���� ���� ���α׷����� ����� ���� ����
} REQUEST_IO_GRID_st, *LPREQUEST_IO_GRID_st;
/////////////////////////////////////////////////////////////////////
// WM_GET_MSG
// �޼��� ����ü
#define n_MSGCD_SIZE	5
#define n_MSGLEN_SIZE   2

typedef struct REPLYMSG
{
	BYTE			ucErrFlag;
	char			nexttp;
	BYTE			MsgCd[n_MSGCD_SIZE+1];	// �޼��� �ڵ�
	BYTE*			lpMsg;					// ���� �޼���
} REPLYMSG_st, *LPREPLYMSG;

////////////////////////////////////////////////////////////////////
// ����� ������ ������ vMajorMinorIDList.size�� �� �� �ִ�.
// �ü� �����͸� CLIENT��  ����ϴ� ����ü
// �� ����Ʈ�� ÷���� ���� ��� ���� �׸����� �����Ѵ�.
////////////////////////////////////////////////////////////////////
typedef struct _REAL_CLIENT_REG
{
	CHARVECTOR  vGubunList;				// ������ ����Ʈ 
										// "ABC", "A", "B" �� ���
										// A���Ű��[0], B���Ű��[0], C���Ű��[0] ...�� ����Ѵ�.
	CHARVECTOR  vKeyValueList;			// KeyValue
	CHARVECTOR  vGubunKeyValueList;		// ������ + �ڵ�
	CHARVECTOR2 vvItemList;				// ��� FID LIST
										// ��� Ű�� vFidValueList[0]�� ��� ������
										// vvFidList[0]�� ���� ��.
	CHARVECTOR2 vvAttriList;			// ��� ������ attribute LIST
	SHORTVECTOR	vSequence;				// Insert������ ��ȸ �������� ��ġ�� ������.
} REAL_CLIENT_REG_st, *LP_REAL_CLIENT_REG_st;

////////////////////////////////////////////////////////////////////
// �������͸� ��Ʈ��(1���� ���ڵ�)�� �����ϴ� ����ü
// Ʈ���� FID �������� ����Ѵ�.
////////////////////////////////////////////////////////////////////
#define MAX_KEYVALUESIZE 41	// (���¹�ȣ+�����ڵ�+�Ÿű���)

// �ڵ����� 
typedef struct REALDATA
{
	char		szKeyCode[32];	// �����ڵ�(������)
	BYTE		chRealType;		// �ڵ����� Ÿ�� 
	BYTE		chCount;		// �ڵ����� ���� 
	short       nSize;			// �ڵ����� ����ü ������ 

	char*       pDataBuf;		// ���� ������ 
	long		lRealStruct;	// �ڵ����� ����ü ( ����ü�� ���� Pointer )


	int			nPoolDataUse;						// �����ü�������� 
	int			nQueDataCount;						// ť������ �Ǽ� 
	int			nTotalCount;						// �ڵ����� ��ü���� 
	int			nCurIndex;							// ����ó�� �ε��� 
	int			nSharedReal;						// �����޸� ��� 
	char*       pSharedRealBuf;						// �����޸� ������ 
} REALDATA_st, *LPREALDATA;

// ���� ���/���� ����ü
typedef struct REALREGIN_1
{
	UCHAR		ucAutoFlag;		// 1:���, 2:����
	UCHAR		ucFiller;		
	short		nCodeCnt;	// �����	//LJP 20110527
	//	(REAL_REG_IN_2�� ucCodeCnt ��ŭ �ݺ�)
} REAL_REG_IN_1;

typedef struct REALREGIN_2
{
	UCHAR		ucMarketFlag;	// �屸��	
	// '1':����,					'2':����,				'3':����,						'4':�ɼ�,
	// '5':ä��,					'6':��3����,			'7':��������,					'8':�����μ���,
	// '9':kfx����,					'A':�ؿ�����,			'B':ecn,						'C':�¶������ڻ��,
	// 'D',�ֽĿɼ�,				'E':�����ں�,			'F':��������,					'G':ECN����,
	// 'H':���α׷�������������,	'I':���� ���ű���,	'J':�ð��ܴ��ϰ��ŸŰ�������,	'K':FOCHT,
	// 'L':STAR��������,			'M':��������,		'N':��ǰ����,					'O':��ǰ�ɼ�,
	// 'P':��ǰ����,				'S':����/�����ñ׳�
	UCHAR		ucRealType;		// �屸�п� ���� �ڵ� ���� ���
	// 0x01 : ����ü��
	// 0x02 : 10ȣ��
	// 0x04 : �ü�, ���庣�̽ý�
	// 0x08 : ���纯����, �峻NAV, FOCHT_LIVE_JISU
	// 0x10 : �ü�����, ELW������ǥ, ȣ���м�, FOCHT_JISU
	// 0x20 : �ŷ���, ��������, �����ñ׳�, FOCHT_For000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	// 0x40 : ȣ��, �������, ECN��������, ���ǽ�ȣ(�ý���), FOCHT_OIX
	// 0x80 : ü��, ��������, ���ǽ�ȣ(�����), FOCHT_RATION
	UCHAR		ucFiller[2];
	UCHAR		ucCode[12];		// �����ڵ�
} REAL_REG_IN_2;

// �Ϲݸ޸�(Ű�� �����Ͻ�)
class CGMemoData: public CObject
{
public:
	char* pFmtDate;	// ����ȭ�� �����Ͻ�
	char* pMemo;	// ����
	char* pTitle;	// ����
};

// ����޸�(Ű�� �����ڵ�)
class CMemoData: public CObject
{
public:
	char* pMemo;	// �޸� ������
};

typedef struct _REQUEST_COMMINFO
{
	char		cTrCode[TRCODE_SIZE + 1];
	char        sSCRN[SCRN_LEN + 1];
	TR_HEADER	TrHeader;
	BYTE		cFIDCommGB;			// FID ��ű���		('0':TR���,1:FID���)
	BYTE		cMsgId;				// ��ű���, DM_ID
	BYTE		cCommandId;			// ��� ������.(PID)

	BYTE		cRqId;				// CommApi���� ����Ÿ ��û�� ��Ʈ��.
	HWND		hRQRPWnd;			// ����� ��û�� ������ �ڵ�

	char		cJobChk[1];			// [����:1, ���弭��:2, �����ͼ���:3
									// ������tab:4, �ý���Ʈ���̵�:5, ������string:6)
									// ȣ������:7, �޸�DB:8, ��ž�ν�����:9]

	char		cContChk[1];		// TR��ȸ�� ����/������ ǥ���ϴ°�,
										// SERVER: ����, ���� ��ư enable ����
										// CLIENT: ����, ���� data ��û(data �׸� �ʿ�� �����ڵ带 �ø���)
										// 0:���� Disable, 1:��Enable, 2:��Enable, 3:����Enable
										// �ɼ� data�� ���� ��� : �ɼ� data ������ �´�(���� ���� key data��)
										// �ɼ� data�� ���� ��� : data �κп� �´�.
	char		sRecCnt[RECSIZE + 1];	// ���ڵ�Ǽ�
	char		sSeq[2];			// ����üũ,TR����
	char		sHold[1];			// �����ֹ�	: ���� ��������	(Y:����, N:)
	// �νõ� ��� Ʈ�����п�
	char		cTranGB[1];			// "A �ڵ��ֹ�",	"M �����ֹ�",	"U Update��",	"V ������ȸ"
	char		cBenefit;			// 'Y' : ������������, 'N' : �ƴ�
	char		cExistRequestCheck;	// 'N' : ���񽺿��Է°��� �����ص� ������ ����
}REQUEST_COMMINFO;

// Common Header
typedef struct tagCommonHeader
{
	ULONG		ulPacketLen;	// ��Ŷ�� ��ü Size
	ULONG		ulRqId;			// Packet Unique Key��( Packet Sequence ID )
	
	// bit���� ó��
	// ���� | ��ȣȭ | 0x20 | ����ô�������� | packet���� | packet���� | packet�� | 0x01
	BYTE		cCpFlag;
	BYTE		cCommandId;		// �ܸ��� ���� Process Command
	BYTE		cErrComm;
	BYTE		cServerType;	// 1:default, 2:�ž�������, 3:DB����
	ULONG		ulWinHwnd;		// (�������� Ŭ���̾�Ʈ�� �������� �ڵ� ���� data�� 0)
} COMMONHEADER, *LPCOMMONHEADER;
// Tr Header
typedef struct tagTrHeader
{
	BYTE			cTRCode[TRCODE_SIZE];	// TR��ȣ
	BYTE			cBenefit;				// �������ǿ���(Y:��������, N:�ƴ�)
	BYTE			cNextPrev;				// TR��ȸ�� ����/������ ǥ���ϴ°�,
											// SERVER: ����, ���� ��ư enable ����
											// CLIENT: ����, ���� data ��û(data �׸� �ʿ�� �����ڵ带 �ø���)
											// 0:���� Disable, 1:��Enable, 2:��Enable, 3:����Enable
											// �ɼ� data�� ���� ��� : �ɼ� data ������ �´�(���� ���� key data��)
											// �ɼ� data�� ���� ��� : data �κп� �´�.
	
	BYTE			cTrErrorFlag;			// '0':����, '1':���� ==> �޼���code�� pc���� ���
											// '2':����, '3':���� ==> Data �κп� 80 Byte�� �޼��� ���[MSG(80 Byte) + Data]
	BYTE			cErrCode[ERRCODE_SIZE];	// �����ڵ�
	ULONG			ulTrBodySize;			// C->S(�ɼǱ���:�������� key data�� ���� ��쵵 ����)
											// S->C(�������� ��ü data ����)
} TRHEADER, *LPTRHEADER;

// ���� ���� �� ��� ��
#define CHAIN_TR_HEADER_SIZE		sizeof(TRHEADER) - 3
typedef struct tagCLIENT_CHAIN_PKT
{
	char			TrHeader[CHAIN_TR_HEADER_SIZE];
	char			cFrameNo[6];		//
	char			cFrameSize[6];
	char			cBlockSize[6];		// 2048
	char			cUniqID[32];
	char			cOrgSize[12];		// ������ ũ��
	char			cCompressSize[12];
} CLIENT_CHAIN_PKT;

typedef struct tagTranHeader
{
	COMMONHEADER	commhdr;	// ����	���.
	TRHEADER		trhdr;		// TR	���.
} TRANHEADER, *LPTRANHEADER;
/*
// Packet = Header + Data
typedef struct tagSockPacket
{
	COMMONHEADER	commhdr;
	TRHEADER		trhdr;		// TR	���.

} SOCK_PACKET, *LPSOCK_PACKET;
*/

// --> [Edit]  ������ 2010/08/25
// DownLoad Version Header ( ��ȭ���� ��� )
typedef struct tagVER_DOWNHEADER
{
	char		cSize[6];		// Data Size
	char		cError[4];		// error
	char		cDataID[2];		// 
	char		cNext[1];		// 0:end, 1:continue
	char		cType[2];		// ���� ���� ( ������ �÷��� ���� �״�� �ٽ� �޾Ƽ� ó���Ѵ�. )
	char		cFiller[1];		// filler
} VER_DOWNHEADER, *LPVER_DOWNHEADER;

#define VER_DOWNHEADER_SIZE			sizeof(VER_DOWNHEADER)

typedef struct tagVER_DOWNHEADER_INREC
{
	char   Spcdirnm[512];			/* PC���丮�� 	*/
	char   Ssvrdirnm[512];			/* SVR���丮�� 	*/
	char   Sfilenm[256];			/* ���ϸ� 			*/
	char   Sfiller[4];				/* FILLER 			*/
	short  Wseq_no;
	char   Sfiller2[2];
} VER_DOWNHEADER_INREC, *LPVER_DOWNHEADER_INREC;

#define VER_DOWNHEADER_INREC_SIZE	sizeof(VER_DOWNHEADER_INREC)

typedef struct tagVER_DOWNHEADER_OUTREC
{
	char   Cerrflg;					/* �������� '0':���� '1':���� */
	char   Smsgcode[5];				/* �޼����ڵ� 		*/
	short  Wseq_no;
	char   Spcdirnm[512];			/* PC���丮�� 	*/
	char   Ssvrdirnm[512];			/* SVR���丮�� 	*/
	char   Sfilenm[256];   			/* ���ϸ� 			*/
	int    Ifsize;					/* ����ũ�� 		*/
} VER_DOWNHEADER_OUTREC, *LPVER_DOWNHEADER_OUTREC;

#define VER_DOWNHEADER_OUTREC_SIZE	sizeof(VER_DOWNHEADER_OUTREC)

//	IP�� 2���� �����ϰ� ����ϱ����ؼ� Ŭ������ �����.
//	��ſ��� ����ϴ� ���ȯ�� ���� Ŭ����	( ��ȭ���� ��� )
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

	//	���� Port�� �����Ѵ�.
	int	GetMainPort()
	{
		return m_nMainPort[m_nPortPosition];
	};

	void NextPortPostion()
	{
		m_nPortPosition = (m_nPortPosition + 1) % 2;
	};

public:
	int			m_nMainPort[2];			// ���Ӽ��� Port��ȣ
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
		m_nMessageOpen		= 0;		//	���� IP Ȯ�ο� �÷���
		m_strHTSType		= "����";

		m_nIndexDataPort	= 0;	//KJI 20110725 (�α����� ���� ������ ó����)	
		GetStartIPPostion();
	};
	virtual ~COMMS_CONFIG() {}

	//	���� IP�� �����Ѵ�.
	CString	GetMainIP()
	{
		return m_strMainIP[m_nIPPosition];
	};

	//	���� Port�� �����Ѵ�.
	int	GetMainPort()
	{
		//KJI 20110725 (�α����� ���� ������ ó����)
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
		// 20090910  JJH  ����/������� ������ �����Լ��� ��ü
		srand(GetTickCount());	// Seed �ʱ�ȭ
		int nRandom = rand();
		m_nIPPosition = (nRandom % MAINIP_CNT);
	};

public:
	int			m_nCONNECT_TYPE;		// 0:����, 1:HTS, 2:call center 3:�̴�HTS
	CString		m_strMainIP[MAINIP_CNT];// ���Ӽ��� IP��
	MAIN_PORT	m_csMainPort[2];		// ���Ӽ��� Port��ȣ
	int			m_nSubPort;				// Main Port�� ������ �ȵɶ� ����ϴ� ��Ʈ
	BOOL		m_bUseSubPort;
	BOOL		m_bUseEncrypt;			// ��ȣȭ ����
	int			m_nSpeedCheckCount;
	int			m_nMakeSubDir;			// ��� API�ΰ�� ���� ���丮�� ���� ���ҷ���...
	int			m_nMaxRetryCount;		// �ִ��� ���� �� 
	int			m_nKeyChangeTimeOut;	// Ű ��ȯ Ÿ�Ӿƿ� 
	BOOL		m_bLogWrite;			// �α����� �ۼ�����(1:�ۼ�, �׿�:����)
	BOOL		m_bConsol;				// ConSolȭ������ ������ ǥ�� ����
	BOOL		m_bBccUse;
	BOOL		m_bIPShare;

	int			m_nIndexDataPort;		//KJI 20110725 (�α����� ���� ������ ó����)

	//	IP���� ������
	int			m_nIPPosition;

	//	���� IP Ȯ�ο� �÷���
	int			m_nMessageOpen;

	//	Tray Icon�� ǥ�õ� HTS Ÿ��
	CString		m_strHTSType;
};
/*
// ��ſ��� ����ϴ� ���ȯ�� ���� ����ü
typedef struct COMMS_CONFIG
{
	int			m_nCONNECT_TYPE;		// 0:����, 1:HTS, 2:call center 3:�̴�HTS
	CString		m_strMainIP;			// ���Ӽ��� IP��
	int			m_nMainPort;			// ���Ӽ��� Port��ȣ
	int			m_nSubPort;				// Main Port�� ������ �ȵɶ� ����ϴ� ��Ʈ
	BOOL		m_bUseSubPort;
	BOOL		m_bUseEncrypt;			// ��ȣȭ ����
	int			m_nSpeedCheckCount;
	int			m_nMakeSubDir;			// ��� API�ΰ�� ���� ���丮�� ���� ���ҷ���...
	int			m_nMaxRetryCount;		// �ִ��� ���� �� 
	int			m_nKeyChangeTimeOut;	// Ű ��ȯ Ÿ�Ӿƿ� 
	BOOL		m_bLogWrite;			// �α����� �ۼ�����(1:�ۼ�, �׿�:����)
	BOOL		m_bConsol;				// ConSolȭ������ ������ ǥ�� ����
	BOOL		m_bBccUse;
	BOOL		m_bIPShare;
} COMMS_CONFIG;
*/
// <-- [Edit]  ������ 2010/08/25
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// �α��� �������� ����ϴ� ����ü /////////////////////////////
typedef struct _REVERSION_INFO
{
	char	cFiller[10];
	char	cBackupChangeGb;	// �����ȯ����
	char	cFiller_1;
	char	cServerName[20];	// �����̸�
	long	lPid;
	long	lIdOffset;
	char	cServerDate[8];		// ������¥[8]
	char	cNameSeq[15];
	char 	cExceptMsgCode[5];	// �����ȯ�޼����ڵ�
} REVERSION_INFO;

////////////////////////////////// ��/���� �α��� in/out /////////////////////////////
// LogIn ����
typedef struct _LOGININFO
{
	BYTE	suser_id[12];			// ����� ID 
	BYTE	spasswd[16];				// ��й�ȣ
	BYTE	sucrayer;				// ȸ������('1':�ӽ�ȸ�� '2':HTSȸ��), �ϴ� 2�� �ִ´�.
	BYTE	sip_address[15];		// IP�ּ�
	BYTE	susergubun[3];			// ����ڱ���
	BYTE	ucSiseUse;				// �ü����뿩��
	BYTE	ucProgramType;			// ������α׷�����(������, ǥ��, ������)
	BYTE	sFiller[48];
	BYTE	sServerUse[20 + 8];
	BYTE	sLoginFlag;
	BYTE	sCertFlag;
	BYTE	sPassFlag;
	//[PMI]LJP 20120329 Start-->
	BYTE	sUserDivInfo[60];		// �����ŷ� ���� ��ġ ���� ex) IP, MAC, PHONE ���(�⺻3������)
	//<--End
} LOGIN_IN;

// sign�� ����Ÿ
//BYTE	sSignLen[4];			
//BYTE	sSignData[2048];		

struct USER_INFO
{	
    UCHAR   ucSvrFlag;			// �������� DB:'1'
	UCHAR   ucMultiFlag;		// �������� ��뿩�� ��Y��=��� ��N�� =�Ұ�
    UCHAR   ucStockLoan;		// Stock Loan ������ ��� '1':������
    UCHAR   ucSysFlag;			// �ý���Ʈ���̵� �����̼����� : Y:�̼�, N:���̼�
    UCHAR   ucLogidFlag;		// �α��ι�� : ID:I, ����:G
    UCHAR   ucKwansimFlag;		// ���ɺ��� ��밡���� ���¿��� : Y:���� N:�Ұ�
    UCHAR   ucHtsFlag;			// HTS�ΰ����� ���Կ��� => Y:����, N:�̰���
    UCHAR   ucJnum[13];			// �ֹι�ȣ/����ڹ�ȣ
    UCHAR   ucLogMedia;			// �������Ӹ�ü => 1:HTS, 2:WEB
    UCHAR   ucLogDate[20];		// �������ӽð� => yyyy/mm/dd hh:mi:ss
    UCHAR   ucName[40];			// ID�� �̸�/���θ�

	UCHAR   ucSessionId[8];		// HTS�������� �����ϴ� ������ Unique�� ID => ����Ű������
	UCHAR   ucCertUse_f;		// ��������뿩�� => Y:�������ʼ�, N:������ �̻��
    UCHAR   ucCertReg_f;		// �������߱��ʿ俩��
	// 0:�߱޺��ʿ� 1:�űԹ߱޿� 2:��߱޿� 3: ������� 4:���ſ�
   	UCHAR   ucPubKeyLen[4];     // KJI 20110907 (�������� ��ȭ) ����Ű�� ���� 1024bit => 140 / 2048bit => 270
	UCHAR   ucDn[256];			// ������ DN��( 40 ~ 256 Byte) : Char
//	UCHAR   ucPubKey[140];
    UCHAR   ucPubKey[270];		// KJI 20110907 (�������� ��ȭ, 270����) ����Ű��(Public Key)=>Binary:140byte(����),Char:186byte
    UCHAR   ucLogin_f;			// �α��α��� => 0.1���α��ΰ�� 1.2���α��ΰ��

	UCHAR   ucPubc_yn;			// �������߱޿���
    UCHAR   ucCert_sta;			// ���������� : 0[�������߱ް���:�ſ�Ȯ���� ���]
    UCHAR   ucGame_f;			// �������ڰ��ӿ��� ��Y��: ���ǰ��� ��N��: ���
    UCHAR   ucFiller2[4];
	// ���ڼ��� �������� ���� �߰��� �׸�-����
    UCHAR   ucAutoStock_yn;		// AUTO-STOCK ��뿩�� => 2003.04.14  �߰�
	UCHAR   ucCertErrFlag;		// �������� ��󿩺� Y:���, N:����
	UCHAR   ucFirewall;			// ���ι�ȭ�� ��뿩�� Y:���, N:����
    UCHAR   ucFiller3[32];		// filler 50Byte -> 10Byte�� ��� : name������ 42->35->34        
};

#define ACCOUNT_LEN			12
typedef struct _USER_ACC_INFO
{
    UCHAR   ucFiller1;
    UCHAR   ucSflag;				// ���༱������ ������� ���� Y:����, N:�̰��� 2002.9.10 �߰�
    UCHAR   ucAflag;				// �������� 'Y':�������� 'N':�ƴ�
    UCHAR   ucBflag;				// ��ǥ���� 'Y':��ǥ���� 'N':�ƴ� 'X':Ÿ�θ��ǰ���
    UCHAR   ucCflag;				// ���űݹ�¡�� 'Y':���űݹ�¡�� 'N':�ƴ�
    UCHAR   ucDflag;				// �ڻ��ְ��¿��� '0':�ش���� '1':�Ϲݹ��� '2':���ǻ���ü
    UCHAR   ucEflag;				// �����������忩�� 'Y':�������� 'N':�ƴ�
    UCHAR   ucFflag;				// HTS��Ͽ��� 'Y':��� 'N':�̵��
	 //[PMI]LJP 20120327 Start-->
	UCHAR   ucGflag;                 /* 1:��ȭ����, 2:��ȭ��������*/
  	UCHAR   ucHflag;                 /* Y:���࿬�����, N:������������*/
	UCHAR   ucIflag;                 /* ����Ÿ�� 1:��Ź, 2:����, 3:����, 4:��������, 5:CD, 6:CP, 7:RP, 8:��������, 9:��Ź���� */
  	//<--End
    UCHAR   ucAccNo[ACCOUNT_LEN];	// ���¹�ȣ
} USER_ACC_INFO;

typedef struct _LOGUSERINFO		
{
	BYTE			ucUserID[12];		// ����� ID
	BYTE			ucUserRayer;		// ����ڱ���('0':�������� '1':HTS)
	BYTE			ucUserLevel;		// ����� ���['1':������(ID�� 099�� ����) '2':���λ���� 
										// '3':�������� '4':GUEST '6':��ȸ��(���¹̺���)]
	USER_INFO		UserInfo;			// 530 byte
	BYTE			ucAccNum[4];		// ���°���

	USER_ACC_INFO	AccInfo[100];		// ��������
	BYTE			ucFiller[48];		// ���� ��Ȯ�� �𸥴� ��.

	BYTE			ucServer[20];		// ������
	DWORD			dwPID;				// PID
	DWORD			dwID_OFF;			// ID_OFF
	BYTE			ucDate[8];
	BYTE			ucNameSeq[15];
	BYTE			ucUserIP[16];		// ����� IP
	BYTE			ucUserPasswd[8];	// ����� ��й�ȣ
	BYTE			ucHKTradeUse;		// Filler �ڸ��� ��� ���߹��� ���
} LOGIN_OUT;

// --> [Edit]  �̵��� 2010/09/30
// �̱ۿ� �α��� ����ü
typedef struct _LOGUSER_EAGLE
{
	BYTE			ucUserID[9];		// ����� ID
	BYTE			ucName[20];			// ����ڸ�
	BYTE			ucUserLayer;		// ����ڱ���
	BYTE			ucUserGrade[3];		// �����Grade
	BYTE			ucServerGuBun;		// (��ī������ ���õ�� �߰�)
	BYTE			ucTemp;				// �̰� ���� ���� ����. ���� ��ư �޴� ���ѿ� ���
	BYTE			ucFiller1[2591];	// KJI 20110907 �������� ��ȭ (2561 -> 2691)
//	BYTE			ucFiller1[2561];	// KJI 20110907 �������� ��ȭ (2561 -> 2691)
	BYTE			ucServer[20];		// ������
	DWORD			dwPID;				// PID
	DWORD			dwID_OFF;			// ID_OFF
	BYTE			ucDate[8];
	BYTE			ucNameSeq[15];
	BYTE			ucUserIP[16];		// ����� IP
	BYTE			ucUserPasswd[8];	// ����� ��й�ȣ
	BYTE			ucFiller2[1];		// �̰� ���� ���� ����.
	BYTE			ucHostIP[15];		// HOST IP
}LOGUSER_EAGLE;
// <-- [Edit]  �̵��� 2010/09/30

///////////////////////////// ������ BP �α��� in/out //////////////////////////////

// LogIn ����
typedef struct _LOGININFO_STAFF
{
	BYTE	suser_id[9];			// ����� ID(���)
	BYTE	sip_address[15];		// IP�ּ�('.'�� ����, 3�ڸ��� ��12�ڸ�)
	BYTE	spasswd[16];				// ��й�ȣ
} LOGIN_STAFF_BP_IN;

typedef struct _LOGUSERINFO_STAFF
{
//	BYTE	ucMessage[80];			// ���� �޼���
	BYTE	ucUserID[9];			// ����� ID
	BYTE	ucIPAddr[15];			// ����� IP
	BYTE	ucPassWord[8];			// ��й�ȣ
	BYTE	ucUserNM[20];			// ����� NM
	BYTE	ucTnbCode[3];			// ó����(�Ҽ���)
	BYTE	ucTnbName[20];			// �ʸ�����
	BYTE	ucUserGroup[4];			// ����� �׷�
	BYTE	ucUserLevel[1];			// ����� ����
	BYTE	ucChngDT[8];			// ��¥
	BYTE	ucServerName[20];		// ������
	BYTE	ucServerDay[8];			// ��¥
	BYTE	ucServerTime[6];		// �ð�
	BYTE	ucIsPWGubun[1];			// ��п�������
	BYTE	ucIsChangePW[1];		// ��й�ȣ���濩��
	BYTE	ucMVTradeUse[1];		// �ؿܽü���뿩��
	BYTE	ucHKTradeUse[1];		// ȫ���ֹ���뿩��
	BYTE	ucCHTradeUse[1];		// �߱��ֹ���뿩��
	BYTE	ucFiller[6];			//
} LOGIN_STAFF_BP_OUT;

#define RQ_COMMINFO_SIZE			sizeof(REQUEST_COMMINFO)
#define HEADER_SIZE					sizeof(COMMONHEADER) + sizeof(TRHEADER)
#define COMMON_HEADER_SIZE			sizeof(COMMONHEADER)
#define TR_HEADER_SIZE				sizeof(TRHEADER)

#define	SIZE_DEF_PACKET				4		// packet ��ü ���� �κ�
#define	LOGIN_IN_SIZE				sizeof(LOGIN_IN)
#define LOGIN_OUT_SIZE				sizeof(LOGIN_OUT)
#define LOGIN_OUT_BP_SIZE			sizeof(LOGIN_STAFF_BP_OUT)

#if !defined(_WIN32_WCE)
#pragma pack(pop)
#endif
#endif // !defined(_COMMSTRUCTDEF_H_)
