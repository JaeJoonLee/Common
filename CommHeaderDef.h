#if !defined(_COMMHEADERDEF_H_)
#define _COMMHEADERDEF_H_

#include "KSCommon.h"

#define		WM_RP_RECEIVED				WM_USER + 1000
//#define		TRAN_H_TRCODE_LEN			32				// TrCode��  ���۱��� ���� 
//#define		TRAN_H_CODE_LEN				8				// Code�� ���۱��� ���� 


// 1 Byte Allignment
#pragma pack(push, 1)

// CommsLogin ��Ž� �޼��� ó��
enum {
	ERR_COMM_OK		= 0,
	ERR_COMM_LOGIN,				// �α��� ����
	ERR_COMM_LOGIN_RCV,			// �α��� ������ �÷��� ������ ����ó��
	ERR_COMM_CERT,
};

// CommAPI�⵿ ���α׷� ���� ���� 
enum  COMMINI_TYPE 
{
	RUN_PROGRAM		= 0,	// Main_Run
	BUILDER_PROGRAM,		// ���� ���α׷� 
	STARTER_PROGRAM,		// ��Ÿ�� ���α׷�
	TRANBUILDER_PROGRAM,	// Ʈ������ 
	STARTER_INDEX_PROGRAM,	//KJI 20110725 (�α��� ���� ���� ������ ó����)
};


//*****************************************************************************
// Revision By:  �� â�� Revision Day:  2003��8��13��
// Comments: �׸���� FORM���� �������
// OnRequestActionChanged �̺�Ʈ�� ���� ������ ���� 
//*****************************************************************************
enum  ACTIONKEY_STATUS
{
	ACTIONKEY_DEFAULT		 = 0,				// �Ϲ� ��ȸ���а�
	ACTIONKEY_PRE_BUTTON,						// ���� ��ư ���ý� ��ȸ���а�
	ACTIONKEY_NEXT_BUTTON,						// ���� ��ư ���ý� ��ȸ���а�
	ACTIONKEY_PAGEDOWN,							// Page Down ���ý� ��ȸ���а�
	ACTIONKEY_PAGEUP,							// Page Up   ���ý� ��ȸ���а�
	ACTIONKEY_FID_CHANGE,						// FID Drag&drop �߻��� ��ȸ���а�
	ACTIONKEY_CODE_CHANGE						// �׸��� ���ο��� �����ڵ� ����� ��ȸ���а�   
};


enum  DATAKIND_STATUS
{
	DATAKIND_RQRP		 = 0,	// ��ȸ��û����
	DATAKIND_PB,      			// �ǽð� ������
	DATAKIND_MSG,				// ��� �޼���
	DATAKIND_RELEASE,			// Ʈ�� ������
	DATAKIND_DOWNLOAD ,			// ���� �ٿ�ε�
	DATAKIND_DOWNLOAD_STATUS,	// ���� �ٿ�ε� ��������
	DATAKIND_COMM_DEBUG,		// CommsDbg������
	DATAKIND_CERT_DATA,			// ������ ������
	DATAKIND_DATAHEADER_DATA,	// ���������
	DATAKIND_DOWNLOAD_ERROR,	// �ٿ�ε� ����
	DATAKIND_CERT_ERROR,		// ��������
	DATAKIND_SS_ERROR,			// ���� �ý��ۿ���
	DATAKIND_SHAREMEM,			// ����������
	DATAKIND_CERT_DATA2,		// ������ ������(���Ǳ��� �Ϲ� ���� ������ ó����)
	DATAKIND_SERVER_PUSH,		// ������ push
	DATAKIND_LOGIN,				// �α���/��������
};

//*****************************************************************************

/*--- message define ---*/
enum    DM_ID           // NEX MESSAGE ID   
{
    DM_RQ_ID,			//  0 Request
    DM_RP_ID,           //  1 Reply
    DM_SB_ID,			//  2 Subscribe
    DM_SBC_ID,			//  3 Subscribe Cancel
    DM_PB_ID,			//  4 Publish
	DM_INFO_ID
};


// ������ �α� ǥ�� Ÿ���� 
#define LOG_DEBUG		0	// ����� ���� ������
#define LOG_UM			1	// ����� �޼���
#define LOG_STATUS		2	// ���� �޼���
#define LOG_RQ			3	// ��ȸ
#define LOG_RP			4	// ����
#define LOG_SB			5	// ���� ���
#define LOG_SBC			6	// ���� ����
#define LOG_PB			7	// ����
#define LOG_DATA		8	
#define LOG_CERT		9	// ��������
#define LOG_ERROR		10
#define LOG_INFO		11
//#define LOG_LOGIN		11
//#define LOG_LOGIN_BP	12
//#define LOG_XECURE	13

#define LOG_TYPE_COMMS					0	// ��ŷα�
#define LOG_TYPE_STARTER				1	// ��Ÿ�� �α��� ���� �α�(starter.log�� ���)
#define LOG_TYPE_REGISTERED_REALKEY		2	// ���� ��ϵ� �ǽð� ���Ű�� ���Ϸ� �ۼ��Ѵ�.(notepad ����)

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// �� ��Ŷ�� ������ ID(��ȭ���ǿ�) /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define	PID_CONNECT_OLD			0x01	// �ʱ� ����(������) KJI 20021203 Not Use
//#define	PID_CONNECT				0x18	// �α��� ���� ���� ���޻�� KJI 20021203 Add
#define	PID_CONNECT				0x35	// �α��� ���� ���� ���޻�� KJI 20021203 Add	[PMI] 0x18 -> 0x35�� ����
#define PID_PLOT_CONNECT		0x29	//KJI 20120206 (�������� ����ó��)
#define	PID_NEWREGISTER			0x02	// �űԵ��
#define	PID_TRDATA				0x05	// �Ϲ� TR
#define	PID_ENDVERSION			0x08	// ����ó�� �Ϸ�			//shc 20011030
#define	PID_REVERSION			0x09	// ���� ���� ��ȣ �䱸
#define	PID_POLLING				0x10	// Alive Check - pc �Ⱦ�
#define	PID_REGCONCERN			0x11	// ���� ���� ���
#define	PID_CRCFILEDN			0x12	// JJH 20071117  CRC ���ϴٿ�ε�

#define	PID_FILEDOWN			0x5f	// FileDownLoad		0x12 -> 0x82 -> 0x82 �� �ٲ�

#define PID_REQ_CONNECT			0xfb	//KJI 20070619	(����ó�� ����)
#define PID_ENCXMINIT_SET		0x7d	//KJI 20070618

#define	PID_ENCCLIENTSET_OLD	0x13	// XECURE INIT
#define	PID_ENCCLIENTSET		0x0A	// XECURE INIT		//shc 20040106	BCC ���set
#define	PID_ENCCLIENTID			0x16	// XECURE ID
#define	PID_ENCCLIENTPWD		0x17	// XECURE PWD
#define	PID_SVRPOLL				0x14	// Alive Check - server
#define	PID_PCCLOSE				0x19	// PC ����
// ADD NEOFRAME KHY 20050827
#define PID_ERROR_REPORT        0x1d	// PC Error Report 
#define	PID_THREAD_TRDATA       0x1d	// THREAD_TRDATA : �Ϲ� TR PC���� ���
#define	PID_THREAD_RELEASECODE  0x1f	// THREAD �ڵ����� �ڵ� ���/����
// END ADD NEOFRAME KHY 20050827

#define	PID_TICKERMSG			0x20	// Ticker Message
#define	PID_POPUPMSG			0x21	// Popup Message
#define	PID_CB					0x22	// CB(Circuit Break)
//#define	PID_BASEPRICE		0x23	// ���ذ� �뺸(�űԻ��������� ����۰� ���Ҿ� ���ذ��� �����Ǵµ� �̸� �뺸
#define	PID_ONLINECONSULT		0x23	// �¶������ڻ�� ��ȣ
#define	PID_CHEKYOUL			0x24	// ü���뺸
#define PID_PLOT_CHEKYOUL		0xC1	//KJI 20120206 (��������)
#define	PID_TICKERNEWS			0x25	// Ticker ����
#define	PID_TICKERSIHWANG		0x26	// Ticker ��Ȳ
#define	PID_SC					0x27	// SideCar
#define	PID_TICKERKONGJI		PID_TICKERMSG	// Ticker ���� ����(�ϴ��� TickerMsg�� ���� ó��),
#define	PID_TICKERJONG			0x29	// Ticker ����

#define	PID_RELEASECODE			0x30	// �ڵ����� �ڵ� ���/����

#define	PID_JISUSISE			0x31	//�����ü�
#define	PID_YEJISUSISE			0x40	//����ü������			//shc 20030212
#define	PID_JONGSISE			0x32	//�ֽ�����ü� 1��		//shc 20011030
#define	PID_JONGHOGA			0x33	//�ֽ�����ȣ�� �ܷ�
#define	PID_JONGMEMBER			0x34	//�ֽ����� �ŷ���
#define	PID_JONGFORIGN			0x35	//�ֽ����� �ܱ���
#define	PID_JISUUPDOWN			0x36	//�������
#define	PID_JONGCHEGYUL			0x3A	//�ֽ�����ü��	20��	//shc 20011030
#define	PID_JONGHOGA_10			0x3B	//�ֽ�����ȣ�� 10�ܰ�	//shc 20011217
#define	PID_JONGSISECYCLE		0x50	//�ֽ�����ü�����		//shc 20011030
#define PID_JONGRANDOM_END		0x0B	//�ֽ���������-����ü��	//shc 20040109
#define PID_JONG_YECHEGYUL		0x3C	//�ֽ����� ����ü��		//ynkim 20061122

//KJI 20060329
#define PID_XRPOWER				0xC8	//���������Ϲ�
#define PID_XRIO				0xC9	//��������
#define PID_XROFFER				0xCA	//�Ź���
#define PID_XRCHEKYOUL			0xCB	//ü�����
#define	PID_XRFOCUS				0x6a	//ȣ������ ��������

#define PID_TIMEOVERJONGSISE	0x63    //�ð��� ü��			//KJI 20050516
#define PID_TIMEOVERJONGHOGA	0x64    //�ð��� ȣ��			//KJI 20050516
//#define PID_TIMEOVERJONGMEMBER	0x65    //�ð��� �ŷ���			//KJI 20050516
//#define	PID_TIMEOVERUPJISU	    0x3E	//�ð��ܾ�������		//KJI 20050516
#define	PID_TIMEOVERJISUUPDOWN	0x3D	//�ð��ܾ������		//KJI 20050516
//#define	PID_TIMEOVERYEJISUSISE	0x3C	//�ð��ܿ�������		//KJI 20050516

#define	PID_NEWGETSISE			0x37	// �����μ�������ü�� + ELW
#define	PID_NEWGETHOGA			0x38	// �����μ�������ȣ�� + ELW
#define	PID_NEWGETMEMBER		0x39	// �����μ�������ŷ��� + ELW
#define	PID_ELWHOGA_10			0x4C	// ELW 10�ܰ� ȣ��	KJI 20051206
#define PID_ELW_IDX				0x4D	// ELW ������ǥ KJI 20051216
#define PID_ELW_ICHANGE			0x4E	// ELW ���纯����	KJI 20051229
#define PID_ELW_YECHE			0x3E	// ELW ����ü�� KJI 20061122

#define	PID_FUTURESISE			0x41	// ����ü��
#define	PID_FUTUREHOGA			0x42	// ����ȣ��
#define	PID_FUTUREMIGYUL		0x48	// ������ü��
#define	PID_FUTUREBASIS			0x88	// �������̽ý�		//shc 20021127
#define	PID_OPTIONSISE			0x43	// �ɼ�ü��
#define	PID_OPTIONHOGA			0x44	// �ɼ�ȣ��
#define	PID_OPTIONINVOLA		0x45	// �ɼ�ȣ�� ���� ������
#define	PID_OPTIONMIGYUL		0x49	// �ɼǹ�ü��
#define	PID_FUTUREOPEN			0x4A	// �����ð�			//shc 20040419
#define	PID_OPTIONOPEN			0x4B	// �ɼǽð�			//shc 20040419

//KJI 20051025
#define	PID_FSTARSISE			0x5A	// ��Ÿ����ü��
#define	PID_FSTARHOGA			0x5B	// ��Ÿ����ȣ��
#define	PID_FSTARMIGYUL			0x5C	// ��Ÿ������ü��
#define	PID_FSTARBASIS			0x5D	// ��Ÿ�������̽ý�
#define	PID_FSTAROPEN			0x5E	// ��Ÿ�����ð�

#define	PID_HIYIELDSISE			0x46	// �������� ����ü��
#define	PID_HIYIELDHOGA			0x47	// �������� ����ȣ��
#define	PID_BONDSISE			0x51	// ä�� ü��
#define	PID_BONDHOGA			0x52	// ä�� ȣ��
#define	PID_QFUTURECHEGYUL		0x53	// KOSDAQ50 ���� ü��
#define	PID_QFUTUREHOGA			0x54	// KOSDAQ50 ���� ȣ��
#define	PID_QFUTURESISE			0x55	// KOSDAQ50 ���� �ü�
#define	PID_QFUTUREMIGYUL		0x56	// KOSDAQ50 ���� �̰�������
#define	PID_EXCHSISE			0x57	// �ƽþ� ȯ�� /�����ü�	   2001.4.24
#define	PID_KOFEXMARKET			0x58	// �ڽ��ڼ��� �� ����	   2001.6.15 -hidden-			

#define	PID_STOPLOSSAUTO		0x59	// StopLoss �ڵ��ֹ� ����
#define	PID_STOPLOSSSEMI		0x60	// StopLoss ���ڵ��ֹ�

#define	PID_OTCBBSISE			0x61	// ��3���� ���� ü��
#define	PID_OTCBBHOGA			0x62	// ��3���� ���� ȣ��

#define PID_QOPTIONCHE			0x69    //KOSDAQ�ɼ� ü��
#define PID_QOPTIONSISE			0x70    //KOSDAQ�ɼ� �ü�
#define PID_QOPTIONHOGA			0x71    //KOSDAQ�ɼ� ȣ�� 
#define PID_QOPTIONNJ			0x72    //KOSDAQ�ɼ� ���纯����
#define PID_QOPTIONMCHE			0x73	//KOSDAQ�ɼ� ��ü��

#define PID_JOPTIONSISE			0x74    //�ֽĿɼ� �ü�			//shc 20020110
#define PID_JOPTIONHOGA			0x75    //�ֽĿɼ� ȣ�� 
#define PID_JOPTIONNJ			0x76    //�ֽĿɼ� ���纯����
#define PID_JOPTIONMCHE			0x77	//�ֽĿɼ� ��ü��
#define PID_SC_JOPTION			0x78	//Ư�� �ֽĿɼ����� SC

//ljj 20080318 add �ֽļ��� 
#define PID_JFUTURESISE			0x79    //�ֽļ��� ü��
#define PID_JFUTUREHOGA			0x7a    //�ֽļ��� ȣ�� 
#define PID_JFUTUREMCHE			0x7b	//�ֽļ��� ��ü��
#define PID_JFUTUREBASIS		0x7c    //�ֽļ��� ���̽ý�

#define PID_TUJASISE			0x80	//������ü�� ���ż� �ڵ�����	//shc 20020404
#define PID_NAVSISE				0x83	//���� ���ڽ�Ź ��������		//shc 20021022	

#define PID_IPDUP				0x81	// �ߺ����� ������ ���� �뺸
#define	PID_OTPSEND				0x97	
#define	PID_SETHWND				0x98	// ��ſ� ���� �����츦 ����
#define	PID_LOGUSERINFO			0x99	// ����� ���� (Ŭ���̾�Ʈ������ ���)
#define PID_BASEPRC				0x9f	// ���ذ� �뺸 20091014 JJH
#define PID_SINGLESIGN_INFO		0xf0	//KJI 20070704
#define	PID_CONNECTERROR		0xa0
#define	PID_LOGUSERINFOAGAIN	0xa1
#define PID_JDEPOS_REAL			0x0e	//KJI 20041019 (���� ���ű� �ǽð� ����)
#define PID_JDEPOS_GROUP_REAL	0x2f	//ljj 20061114(���� ���űݷ��� �ǽð� ����)
#define	PID_TIMEOVER_REAL		0x0f	//KJI 20050516 (�ð��� ���� �ǽð� ����)

// 2002.06.17 -hidden-
#define PID_TRDATA_TOBP			0xa2	// BP�� ��Ŷ�� ����������(PC������ �����)
#define PID_BP_LOGUSERINFO		0xa3	// �ž��� ������� ����� ����
#define PID_BP_ERRLOGUSERINFO	0xa4	// �ž��� ����������� �����϶�
#define	PID_BP_CHEKYOUL			0xa5	// �ž��� ü���뺸(PC������ ���)
#define	PID_BP_POLLING			0xa6	// �ž��� ���� ����
#define	PID_BP_POPUPMSG			0xa7	// �ž��� POPUP �޼��� (PC������ �����)
#define PID_TRDATA_XRAY			0xa8	// ȣ������������ ���
#define PID_SYSALARM			0xa9	// LJP 20070910 �ý��� �˶�

// CJH 20050711
#define PID_SIGNAL_UAS_FID		0x1a	// PC-����ں����ǰ˻� mdb���������߻�FID
#define PID_SIGNAL_SAS_FID		0x1b	// PC-set�� �ɰ��� �Ǵ� �Ŀ� ������ �ʿ�mdb���������߻�FID
// CJH 20050711
#define PID_SIGNAL_NEWS_FID		0x1c	// ADD NEOFRAME KHY 20050721

#define PID_TEMA				0x6e	// �׸��ǽð�
#define NEW_UAS_FID				0x6b	// New User Signal
#define NEW_SAS_FID				0x6c	// New System Signal
#define NEW_CAS_FID				0x6d	// ����ü�ᷮ

// ADD NEOFRAME KHY 20050822
#define PID_FO_PCR_FID			0x2a    // PUT_CALL_Premium_Ratio
#define PID_FO_OIX_FID			0x2b    // Future_Min_OIX
#define PID_FO_FOR_FID			0x2c    // Future_Hoga_FOR
#define PID_FO_OI2_FID			0x2d    // OPTION_JISU
#define PID_FO_KP2_FID			0x2e    // KP200_LIVE_JISU

// ��ǰ����
#define PID_SFUTURESISE			0x8a
#define PID_SFUTUREHOGA			0x8b
#define PID_SFUTUREMCHE			0x8c
#define PID_SFUTUREBASIS		0x8d
#define PID_SFUT_YECHE			0x8e
#define PID_SOPTIONSISE			0x9a
#define PID_SOPTIONHOGA			0x9b
#define PID_SOPTIONNJ			0x9c
#define PID_SOPTIONMCHE			0x9d
#define PID_SOPT_YECHE			0x9e
#define PID_SOBJ_JISU			0x8f

//KJI 20120104 (Buy-In ���� ���� ����)
#define PID_BUYIN_JONGSISE		0x92	//�ֽ�����ü��
#define PID_BUYIN_JONGHOGA		0x93	//�ֽ�����ȣ��
#define	PID_BUYIN_NEWGETSISE	0x94	// �����μ�������ü�� + ELW
#define	PID_BUYIN_NEWGETHOGA	0x95	// �����μ�������ȣ�� + ELW
#define	PID_BUYIN_HIYIELDSISE	0x96	// �������� ����ü��
#define	PID_BUYIN_HIYIELDHOGA	0x97	// �������� ����ȣ��

#define	PID_AUTOORDER			0x28	// �������ڵ��ֹ�
#define	PID_PLOT_AUTOORDER		0xC2	//KJI 20120206 (��������)

#define RECSIZE					3
#define ERRCODE_SIZE			5
#define TRCODE_SIZE				8
#define SCRN_LEN				6
#define POLLING_CHECK_INTERVAL	180		// 3��
#define MSG_SIZE				80		// �������� �ִ� �޼���(���� ����) ũ��

// ������ ������ �Ǵ� body ũ��
#define COMPRESS_STANDARD_SIZE	4096
// ���� �� ������ ���� �� body�� ����
#define COMPRESS_SEND_SIZE		2048

#define MAX_PACKET_SIZE			4096
#define MAX_SEND_SIZE			2048	

#define SZ_BCC_CHECKSUM			4
#define REAL_TYPE_SIZE			4

// Common Header�� cCpFlag ��Ʈ�� ��
#define FLAG_COMPRESS			0x80	// ����
#define FLAG_ENCRYPT			0x40	// ��ȣȭ
#define FLAG_FIDCOMM			0x20	// FID���
#define FLAG_COMPRESS_FAILED	0x10	// ���� �� ����� ū ���(���� ����)
#define FLAG_PACKET_BEGIN		0x08	// packet ����
#define FLAG_PACKET_CONTINUE	0x04	// packet ����
#define FLAG_PACKET_END			0x02	// packet ��

//////////////////////////////////////////////////////////////

// 91 ~ 99�� ����� MinorID
#define MINOR_ENCRYPT		30090	// ��ȣȭ Ű��ȯ��
#define MINOR_CERTIFICATE	30091	// ������ ���� ���
#define MINOR_CERT_VERIFY	30092	// ������ ����
#define MINOR_CERTPASSERR	30093	// ������ ��й�ȣ ����
#define MINOR_CERTISSUE		30094	// ������ �߱�
//#define MINOR_TICKER		95	// ƼĿ ��û
//#define MINOR_REALREG		96	// ������/����
#define MINOR_AS_LOGIN_DATA	30096	// �α��� ���� ���� ���
#define MINOR_SETPUBLIC_KEY	30097	// �������� ���� ���� ���
#define MINOR_LOGOUT		30098	// Logoutó��
#define MINOR_LOGIN			30099	// Loginó��

#define MINOR_CERT_DESTROY	30100	// ���������� ���� (������ 2010. 12. 1)

// --> [Edit]  ������ 2010/07/28	( X-Ray �߰� )
#define MINOR_XRAY			30100	// X-RAY ��û ID
// <-- [Edit]  ������ 2010/07/28

#define RQ_ID_LOGIN			100		// �α����� RQID
#define RQ_ID_CERT			101		// ���������� RQID

// ����Ÿ ��� Ÿ�� ����
#define FID_HEADER				0		// FID ��� 
#define TR_HTS_G_HEADER			1		// HTS �Ϲ�
#define NO_TR_HEADER			2		// TR ����� �ʿ� ���� ���

//�α�������
#define LOGIN_TYPE_STOCKTOT		'1'	//�ֽ�������		ljj 20070208 Modify
#define LOGIN_TYPE_CMA			'2'	//CMA �ڻ������	ljj 20070208 Add
#define LOGIN_TYPE_MINI			'3'	//������
#define LOGIN_TYPE_TRAD			'4'	//Ez-YesTrader
#define LOGIN_TYPE_EAGLE		'5'	//Eagle				//ljj 20040423 �̱�
#define LOGIN_TYPE_VIRTUALFUT	'6'	//�����������ڰ���	//shc 20040720
#define LOGIN_TYPE_FUTOPT		'7'	//�����ɼ���		ljj 20070208 Modify


/*----------------------------------------------------*/

////////////////////////////////////////////////////////////////
/*
// ������ ����� �������
typedef struct _NEXTKEY_IO
{
	char	KeyValue[16];	// Next�� ���� Ű���κ�
	long	KeyNo;			// Ű�� �Ϸù�ȣ
	long	Count;			// �� Read ����
	long	RequestCnt;		// �� Client�� ��û�� ���ϵ� ����
}NEXTKEY_IO;
*/

// ������ ������ ���Ե� ������ ���� 
#define US						(BYTE)0x1F	// ������ ��Ҹ� �и��ϴ� ����(Unit Separator)
#define FS						(BYTE)0x1E	// ��Ʈ�� ������ �����ڷ� ��� (Field Separator)
#define PS						(BYTE)0x0D	// Out �� ����
#define RS						(BYTE)0x0A  // ���ڵ� ����
#define IS						(BYTE)0x7F	// FID�� �Է� ������ ������ �����ڷ� ��� ( ������ )
#define _TCH_US					US
#define _TCH_FS					FS
#define _TCH_PS					PS
#define _TCH_RS					RS
#define _TCH_IS					IS

//// ������ ������ ����
#define	CDID_R_SISED			0x0101		// �ü� DATA
#define	CDID_R_MULTISISED		0x0181		// �ü� DATA(����Ű)

////
#define CDID_DT_RST				0x0201		// DATA ��ȸ
#define CDID_DT_RSP				0x0202		// DATA ���� 
#define CDID_DT_RSET			0x0203		// DATA RESET(ȭ��Close)
#define CDID_CODE_RSET			0x0204		// CODE RESET


#define CDID_TR_RST				0x0211		// TR ��ȸ
#define CDID_TR_RSP				0x0212		// TR ���� 

#define CDID_FILEDOWN_RST		0x0221		// �������ۿ�û
#define CDID_FILEDOWN_START		0x0222		// �������۰���
#define CDID_FILEDOWN_DATA		0x0223		// ���Ϻ���
#define CDID_FILEDOWN_END		0x0224		// ������������

#define CDID_FILERECOVERY_RST	0x0241		// �������ۿ�û
#define CDID_FILERECOVERY_START	0x0242		// �������۰���
#define CDID_FILERECOVERY_DATA	0x0243		// ��������
#define CDID_FILERECOVERY_END	0x0244		// ������������

#define CDID_CONN_CLOSE			0x0433		// ���Ӵ��� ��û 

//
#define CDID_STAT_RQ			0x0701		// ���� �Ƿ�
#define CDID_STAT_RP			0x0702		// ���� ����(Reply Only)
#define CDID_POLLING_DATA		0x0705		// Polling Data

enum  REQUEST_STATUS
{
	REQUEST_SUCCESS					= (BYTE)0x00,	// ����
	REQUEST_ERROR_SOCKET			= (BYTE)0x01,	// ���ϼ۽� ����
	REQUEST_ERROR_NOTCONNECT		= (BYTE)0x02,	// ��� �̿��� ����
	REQUEST_ERROR_ALLOCMEM			= (BYTE)0x03,	// �޸� ����
	REQUEST_ERROR_FORMAT			= (BYTE)0x04,	// ��űԾ� ����
	REQUEST_ERROR_DOWNLOAD			= (BYTE)0x05,	// �ٿ�ε� ����  
	REQUEST_CERT_NOTDEFINE			= (BYTE)0x06,	// ������ ������ 
	REQUEST_LOGIN_NOTUNSERINFO		= (BYTE)0x07,	// �������� ���� 	
	REQUEST_LOGIN_FAIL				= (BYTE)0x08,	// ����ó�� ���� 	
	REQUEST_SENDLEN_OVER			= (BYTE)0x09,	// ������ �������� �ʰ�
	REQUEST_ERROR_NOTCOMPLETE		= (BYTE)0x10,	// ������ ��ȸ��
	REQUEST_CERT_NOTCOMPLETE		= (BYTE)0x11,	// ������ ����
	REQUEST_INVALID_SERVICE			= (BYTE)0x12,	// ���񽺸��� Ʋ��
};


// �ǽð� ��Ϲ� ������ ���� ����  
enum  REALUPDATE_MSG
{
	REALUPDATE_REISTER,			// ������� ���̺� ���
	REALUPDATE_UNREISTER,		// ������� ���̺� ������ ���������۽�
	REALUPDATE_CODE_DELETE		// ������� ���̺� �����ڵ������ ���������۽�
								// (���������������� �ϳ��� Ű���� ����) 
};											


//////////////////////////////////////////////////////////////////
// RegisterWindowMessage�� ��ϵ� �޼����� ���� WPARAM���� 
// ������ �� 
//////////////////////////////////////////////////////////////////
//   HANDLE_CONTROL_MSG							//
// CommsDbg.exe <-> Comms.exe <-> CommAPI.dll
enum  HANDLE_CONTROL_MSG
{ 
	COOMS_WINDOW_HANDLE	= 1,	// Comms�� ������ �ڵ�
	COMAPI_WINDOW_HANDLE,		// ComAPI�� ������ �ڵ� 
	COMMSDBG_WINDOW_HANDLE,		// ComsDBG�� ������ �ڵ�
	STARTER_WINDOW_HANDLE		// Starter�� ������ �ڵ�
};

//	SOCKET_NOTIFY_MSG(������������)
// Comms.exe->CommAPI.dll
enum  SOCKET_STATUS_MSG
{ 
	SOCKET_CONNECTING =50,		// ���� ���� �� 
	SOCKET_CONNECTED,			// ���� ���� �Ϸ�
	SOCKET_CLOSED,				// ���� ���� ����
	SOCKET_CLOSING,				// ���� ���� ��
	SOCKET_CONNECT_FAIL,		// ���� ���� ����
	SOCKET_RECEIVE_FAIL,		// ������ ���� ����
	SOCKET_SEND_FAIL,			// ������ �۽� ����
	SOCKET_SEND_SUCCESS,		// ������ �۽� ����
	SOCKET_RECONNECT_REQUEST,	// ������ ��û
	LOGIN_COMPLETE,				// ����ó�� �Ϸ� 
	LOGIN_FAIL,					// ����ó�� ���� 
	SISE_SOCKET_CONNECTED,		// ���� ���� �Ϸ�
	SISE_SOCKET_CLOSED,			// ���� ���� ����
	REVERSION,					// ����ó�� �϶�� �޼���
	ENDVERSION,					// ����ó�� �Ϸ� �ߴٴ� �޼���
};

// COMMS_PROCCESS_MSG(������α׷� �⵿, ���α׷� ����� �����ͼ����� ��� ����)
// CommAPI.dll -> Comms.exe
//////////////////////////////////////////////////////////////////
enum  COMMS_PROCCESS_MSG
{ 
	COMMS_CONNECT_START = 1,	// TCP �������
	COMMS_RECONNECT_START,		// TCP �翬�� 
	COMMS_TERMINATE,			// ���α׷� ����
	GET_SIGNON_DATA,			// ���̿� �������
	SET_SIGNON_DATA,			// ���̿� ���¼���
	COMMS_CONFIG_CHANGE,		// ���ȯ�� ���� 
	GET_REALKEY_DISPLPAY,		// RealŰ ����Ʈ�䱸(����׿�) 
	GET_EXCELDDE_ITEMLIST,		// Excel DDE��ũ����(����׿�) 
	SET_CONSOLAPP_CREATE,		// Consol ���α׷� �⵿ 
	GET_USERINFO_DATA,			// ����� ���� �䱸 
	GET_USERINFO_DISPLPAY,		// ����� ��������Ʈ ǥ��(����׿�) 
	COMMS_LANG_CHANGE,			// ���� ����
	COMMS_RECONNECT_REQUEST,  	// TCP �翬�� ��û  
	COMMS_COMSTART,  			// ���� ó�� ����� ���� ���� ����
	XECURE_INIT					// xecure init
};


// ������Ʈ�� �Ǵ� ���ο��� ��ȸ��û�� ���� ��ȸ���� �޼��� ������ ������ ��
// (�����ʰ�, ��� ���ø� ��ȸ���� ���ſϷ�(��ȸ�Ϸ᳻��)ǥ��  
// CommAPI.dll -> �� ȭ�� 
//////////////////////////////////////////////////////////////////
enum  REPLY_MESSAGE_INFO
{ 
	RP_SUCCESS		= (WORD)0x00,	// ��ȸ����		����
	RP_ERROR		= (WORD)0x02,	// ��ȸ����		����
	RP_TIMEOUT		= (WORD)0x04	// ���Žð��ʰ� ����
};

// ����,����,CL �����������ΰ�� �ٿ�ε� ���°� 
enum  DOWNLOAD_MSG_INFO
{
	FILE_DOWN_TIMEOUT  = 130,		// ���� �ٿ�ε� ���Žð��ʰ�  
	FILE_DOWN_START,				// ����,�����ٿ�ε�  ����
	FILE_DOWN_DATA,					// ����,�����ٿ�ε�  ���� 
	FILE_DOWN_END,					// ����,�����ٿ�ε�  ����
	FILE_PCMASTER_START,			// ���������� �ٿ�ε�  ����
	FILE_PCMASTER_DATA,				// ���������� �ٿ�ε�  ���� 
	FILE_PCMASTER_END,				// ���������� �ٿ�ε�  ����
	FILE_DOWN_ERROR,				// ������ ���(���� ���� �����ڵ�) 
	FILE_DOWN_SOCKETCLOSED,			// ���� ������ ���� ������ ��� 
	FILE_DOWN_FORMAT_ERROR  = 200,	// ���ϰ��� �������� ������ ���� �ʽ��ϴ� 
	FILE_DOWN_FILESIZE_ERROR,		// �ٿ�ε��� �� ���ϻ���� ��ġ���� �ʽ��ϴ�
	FILE_DOWN_SEQNUMBER_ERROR,		// �ٿ�ε��� �Ϸù�ȣ�� ��ġ���� �ʽ��ϴ�
	FILE_DOWN_LISTFILESIZE_ERROR,	// ��ϸ���Ʈ�� �����κ��� ������ ��ü ���ϻ���� ��ġ���� �ʽ��ϴ�.
	FILE_DOWN_FILEWRITE_ERROR		// ���� �����۾��� �ý��ۿ����� �߻� �߽��ϴ�.
};

// CommAPI�� �޼����� �����ڵ尪 ���� 
enum  COMMAPI_MSG_INFO
{
	COMMAPI_USERDATA_NOTFIND = 210,			// ������ ������ ���Ͽ� �� ������ �����ϴ�(win.ini)
	COMMAPI_COMMSPRO_NOTFIND,				// ��� ���ø����̼��� ���� ���� �ʽ��ϴ�
	COMMAPI_COMMSINIFILE_NOTFIND,			// ���ȯ�� ���������� ���� ���� �ʽ��ϴ�
	COMMAPI_SCREENVERFILE_NOTFIND,			// ȭ���� ���������� ���� ���� �ʽ��ϴ�
	COMMAPI_COMMS_OPENERROR,				// ��� ���α׷��� �⵿�� ������ �߻� �߽��ϴ�
	COMMAPI_SCREEN_MAPINFO_ERROR,			// ȭ�������� �ٿ�ε��� ������ ȭ���� �� ������ �����ϴ�
	COMMAPI_PCMASTERFILE_DOWNLOAD_START,	// ���������� �ٿ�ε� ���Դϴ�.
	COMMAPI_MENUFILE_DOWNLOAD_START			// �޴�����   �ٿ�ε� ���Դϴ�.
};


// CheckStart�� �޼����� �����ڵ尪 ���� 
enum  CHECKSTART_MSG_INFO
{
	CHECKSTART_MACADDRESS_NOTFIND = 250,	// ��ϵ� MacAddress�� �������� �ʽ��ϴ�.call���ͷ� ���ǹٶ��ϴ�.
	CHECKSTART_LOGIN_REQUEST,				// ����ó�� ��û�� �Դϴ�
	CHECKSTART_NOTCOMAPRE_MACADDRESS,		// ������ ��ϵ� MacAddress�� �ܸ���MacAddress��ġ ���� �ʽ��ϴ�. call���ͷ� ���ǹٶ��ϴ�.
	CHECKSTART_NOT_USERPID,					// �� PID�� �����ϴ�.Call���ͷ� ���� �ٶ��ϴ�
	CHECKSTART_LOGIN_COMPLETE,				// ����ó�� �Ϸ�
	CHECKSTART_VERSIONLIST_RECEIVE,			// ��������� �������Դϴ�
	CHECKSTART_VERSIONLIST_COMPARE,			// ��������� ���� �Դϴ�
	CHECKSTART_VERSIONLIST_COMPAREERROR,	// ��������� ���� ���� �߻� �߽��ϴ�
	CHECKSTART_MASTERLIST_COMPARE,			// �����͸���� ���� �Դϴ�
	CHECKSTART_MASTERLIST_COMPAREERROR,		// �����͸���� ���� ���� �߻� �߽��ϴ�
	CHECKSTART_CONTROL_REGISTER,			// ����� ���ó�� ���Դϴ�
	CHECKSTART_CONTROL_REGISTERERROR,		// ����� ��Ͻ� ������ �߻� �߽��ϴ�=File[%s],ErrorCode=[%d]
	CHECKSTART_CALLCENTER_TEL,				// Call���ͷ� ���� �ٶ��ϴ�
	CHECKSTART_NEWFILE_PROCCESS,			// �ֽ����� ����ó��(�ٿ�ε�)�� �Դϴ�
	CHECKSTART_LANGECHANGE_PROCCESS,		// ���ȯ�� ����ó���� �Դϴ�
	CHECKSTART_LANGECHANGE_CONFIRM,			// ���ȯ�� ����Ȯ�� �޼��� 
	CHECKSTART_USERLEVEL_ERROR,				// ����� ������� �����Դϴ�..call���ͷ� ���ǹٶ��ϴ�.
	CHECKSTART_LANGCODE_ERROR,				// ����ڵ� ���� �����Դϴ�..call���ͷ� ���ǹٶ��ϴ�.
	CHECKSTART_MENUFILE_NOTFIND				// ������Ͽ� ��������� ���� �޴������� �����ϴ�..call���ͷ� ���ǹٶ��ϴ�.
};



//////////////////////////////////////////////////////////////////
// ComApi���� ȭ��,�������� �����͸� �����ϱ����� ����� �޼��� ���ǰ� 
//////////////////////////////////////////////////////////////////
#define WM_BEGIN_WAIT_CURSOR		WM_USER + 600	// CommApi���� Form Wnd�� �ִ� BeginWaitCursor�� �⵿�ϰ� �Ѵ�.
#define WM_END_WAIT_CURSOR			WM_USER + 601	// CommApi���� Form Wnd�� �ִ� EndWaitCursor�� �⵿�ϰ� �Ѵ�.
#define WM_GET_DATA					WM_USER + 602	// ȭ�鿡�� ��ȸ���䵥����(RP) ó���� �ϵ����ϴ� �޼��� 
#define WM_GET_MSG					WM_USER + 603	// CommApi���� Form Wnd�� �޼����� ������.
#define WM_GET_RELEASE				WM_USER + 604	// CommApi���� Form Wnd�� Ʈ�����Ḧ ������.
#define WM_GET_BROD					WM_USER + 605	// ȭ�鿡�� �ǽð�������(PB)ó���� �ϵ����ϴ� �޼��� 
#define WM_GET_CONTRACT				WM_USER + 606	// ��Ʈ�ѿ��� ü�ᵥ���͸� �޴´�.
#define WM_RESET_DATA				WM_USER + 620	// ��ȸ��û�� ���� ��ȸ���� �޼��� ������ ó���� �ϵ����ϴ� �޼���
// ���� �ٿ�ε�
#define WM_FILE_DOWNLOAD			WM_USER + 621
#define WM_FILE_DOWNLOAD_CANCEL		WM_USER + 622
#define WM_FILE_DOWNLOAD_COMMAND	WM_USER + 623
#define WM_FILE_DOWNLOAD_REQUEST	WM_USER + 624

#define WM_REPLY_MSGINFO			WM_USER + 625	// ��ȸ��û�� ���� ��ȸ���� �޼��� ������ ó�� �ϵ����ϴ� �޼��� 
#define WM_COMMAND_MSGDATA			WM_USER + 626

#define WM_REALDATA_RECEIVED		WM_USER + 627
#define WM_WATING_TCP_DOWNLOAD		WM_USER + 628
#define WM_USER_ABORT_FLAG			WM_USER + 629

#define WM_SIGNALDATA_RECEIVED		WM_USER + 630
#define WM_MEMODATA_CHANGED			WM_USER + 631
#define WM_WATCHDATA_CHANGED		WM_USER + 633
#define WM_JANGO_RECEIVED_OK		WM_USER + 634
#define WM_GET_FREESTYLE			WM_USER + 635

#define WMU_NOCONNECT_ACK			WM_USER + 636

#define UM_GET_TREE_COMM_DATA		WM_USER + 637	// Ʈ������ ����� ���� ������ �������� ���

// ���� �ٿ�ε�� ������ ������ ���ǰ� 
#define	MAIN_VERSION_FILE		0			// ���ο� �ٿ�ε�(ȣ���� ȭ�鿡�� ������ �ۼ�) 
#define SCREEN_VERSION_FILE		1			// ȭ��� �ٿ�ε�(CommAPI���� �����ۼ�) 
#define MENU_DATA_FILE			2			// ������������ ��û�� �޴� ���� �ٿ�ε�(CommAPI���� �����ۼ�) 
#define COMMAPI_DATA_FILE		3			// ������ COMMAPI����  ������ �����͸� �ۼ��Ѵ�.
#define PCMASTER_DATA_FILE		4			// ������������ ��û�� PC������ ���� �ٿ�ε�  
#define RECOVERY_DATA_FILE		5			// ���������� �ٿ�ε�(ȣ���� ȭ�鿡�� ������ �ۼ�) 

#define	IDS_MENU_FILENAME					_T("menu/menu.dat")


// Little_edian ->Big_edian
inline void ConvertBigEndian ( short& d )
{
	short s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[1];
	pd[1] = ps[0];
}

inline void ConvertBigEndian ( WORD& d )
{
	WORD s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[1];
	pd[1] = ps[0];
}

inline void ConvertBigEndian ( int& d )
{
	int s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[3];
	pd[1] = ps[2];
	pd[2] = ps[1];
	pd[3] = ps[0];
}

inline void ConvertBigEndian ( DWORD& d )
{
	DWORD s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[3];
	pd[1] = ps[2];
	pd[2] = ps[1];
	pd[3] = ps[0];
}

inline void ConvertBigEndian ( long& d )
{
	long s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[3];
	pd[1] = ps[2];
	pd[2] = ps[1];
	pd[3] = ps[0];
}

inline void ConvertBigEndian ( float& d )
{
	float s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[3];
	pd[1] = ps[2];
	pd[2] = ps[1];
	pd[3] = ps[0];
}

inline void ConvertBigEndian ( double& d )
{
	double s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[7];
	pd[1] = ps[6];
	pd[2] = ps[5];
	pd[3] = ps[4];
	pd[4] = ps[3];
	pd[5] = ps[2];
	pd[6] = ps[1];
	pd[7] = ps[0];
}
inline void ConvertBigEndian ( __int64& d )
{
	__int64 s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[0] = ps[7];
	pd[1] = ps[6];
	pd[2] = ps[5];
	pd[3] = ps[4];
	pd[4] = ps[3];
	pd[5] = ps[2];
	pd[6] = ps[1];
	pd[7] = ps[0];
}
inline void ConvertLittleEndian ( float& d )
{
	float s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[3] = ps[0];
	pd[2] = ps[1];
	pd[1] = ps[2];
	pd[0] = ps[3];
}


inline void ConvertLittleEndian ( double& d )
{
	double s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[7] = ps[0];
	pd[6] = ps[1];
	pd[5] = ps[2];
	pd[4] = ps[3];
	pd[3] = ps[4];
	pd[2] = ps[5];
	pd[1] = ps[6];
	pd[0] = ps[7];
}
inline void ConvertLittleEndian ( __int64& d )
{
	__int64 s=d;
	char *ps = (char*)&s;
	char *pd = (char*)&d;

	pd[7] = ps[0];
	pd[6] = ps[1];
	pd[5] = ps[2];
	pd[4] = ps[3];
	pd[3] = ps[4];
	pd[2] = ps[5];
	pd[1] = ps[6];
	pd[0] = ps[7];
}



//--------------------------------------------

inline short ConvertBigEndianRet ( short s )
{
	ConvertBigEndian( s );
	return s; 
}

inline WORD ConvertBigEndianRet ( WORD s )
{
	ConvertBigEndian( s );
	return s; 
}

inline int ConvertBigEndianRet ( int s )
{
	ConvertBigEndian( s );
	return s;
}

inline DWORD ConvertBigEndianRet ( DWORD s )
{
	ConvertBigEndian( s );
	return s;
}

inline long ConvertBigEndianRet ( long s )
{
	ConvertBigEndian( s );
	return s;
}

inline float ConvertBigEndianRet ( float s )
{
	ConvertBigEndian( s );
	return s;
}

inline double ConvertBigEndianRet ( double s )
{
	ConvertBigEndian( s );
	return s;
}

inline __int64 ConvertBigEndianRet ( __int64 s )
{
	ConvertBigEndian( s );
	return s;
}

#pragma pack(pop)

#endif // !defined(_COMMHEADERDEF_H_)
