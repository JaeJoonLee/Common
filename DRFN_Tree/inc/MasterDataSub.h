// #include "./inc/MasterDataSub.h"
//
#if !defined(AFX_MASTERDATASUB_BY_JUNOK_LEE__INCLUDED_)
#define AFX_MASTERDATASUB_BY_JUNOK_LEE__INCLUDED_


// ��Ƽ��Ʈ������ ���ǳ���. MULTICHART\StdAfx.h
class CMasterTypeInfo
{
public:
	//MultiChart�� StaAfx.h�� ���ǵ� �Ͱ� �����ϰ�.
	enum {
		NONE_CHART= 0xFF,
		STOCK_CHART=0,		//KOSPI,KOSDAQ
		UPJONG_CHART=1,		//UP
		FUTOPT_CHART,		//����/�ɼ�
		STOCKFUTOPT_CHART,	//�ֽļ���/�ֽĿɼ�
		FOREIGN_CHART,		//�ؿ�
		ELW_CHART,			//ELW
		FUOPT_JIPYO_CHART,	//�����ɼ���ǥ
		COMMODITY_CHART,	//��ǰ����
		MARKET_CHART,		//������ǥ
	};
};

class CDRCodeTypeInfo
{
public:
	//MultiChart�� StaAfx.h�� ���ǵ� �Ͱ� �����ϰ�.
	//NH100210 ��ġ�� �̸��� �־ DR_ -> DRCODETYPE_ ���� ������.
	enum { 
		DRCODETYPE_UNKNOWN = 0xFF,
		DRCODETYPE_KOSPI_STOCK=0,
		DRCODETYPE_KOSDAQ_STOCK,
		DRCODETYPE_ELW,
		DRCODETYPE_KOSPI_UPJONG,
		DRCODETYPE_KOSDAQ_UPJONG,
		DRCODETYPE_KFUTURE,
		DRCODETYPE_KOPTION,
		DRCODETYPE_FUTURE_SPREAD,
		DRCODETYPE_STOCKFUT,
		DRCODETYPE_STOCKOPT,
		DRCODETYPE_US_ITEM,
		DRCODETYPE_FUOPT_JIPYO,
		DRCODETYPE_FUOPT_COMMODITY,
		DRCODETYPE_KRXUP,
	};
};

//
//	kind of codeMaster
//
#define	drCode_kospi		100
#define	drCode_future		101
#define	drCode_option		102
#define	drCode_foption		103
#define	drCode_index		104
#define	drCode_bond			105
#define	drCode_kofex		106
#define	drCode_kospi2		107
#define	drCode_koption		108
#define	drCode_sinju		109			// type 0: all, 1: ��������(���ϸ��ݵ�), 2: ELW, 
										//	3: �����μ���, 4: �������� + �����μ���
#define	drCode_third		110
#define	drCode_getfuture	111			// FUTURE code
#define	drCode_getcall		112			// ATM CALL option
#define	drCode_getput		113			// ATM PUT option
#define	drCode_ecn			114			// ECN code
#define drCode_faoption		115			// future + option + kospi option
#define drCode_all2			116			// kospi + option
#define	drCode_us			117			// overseas code
#define	drCode_spread		118			// Spread
#define	drCode_kk			119			// kospi + kosdaq
#define	drCode_elw			120			// elwCode
#define	drCode_kkelw		121			// kospi + kosdaq + elw (except etf)
#define	drCode_sf			122			// only stock future
#define	drCode_smbond		123			// �Ҹ�ä�� code
#define drCode_reits		124			// Reits Code
#define drCode_etf			125			// etf
#define	drCode_fd			126			// fund
#define	drCode_cfuture		127			// ��ǰ����
#define	drCode_coption		128			// ��ǰ�ɼ� 
#define	drCode_K200FO		129			// ��������, �ɼ� (spread, ��Ÿ ����)
#define	drCode_foindex		130			// FOindex
#define	drCode_linkF		131			// ���ἱ��
#define	drCode_basic		132			// �����ڻ� �ڵ� ����
#define	drCode_getstar		133			// STAR code
#define	drCode_gfuture		140			// �ؿܼ���
#define	drCode_gfx			141			// FX



//	Winix ��ǰ���� ���� ���� ����(Code Type)
// 	#define THREE_BONDS		900
// 	#define FIVE_BONDS		901
// 	#define TEN_BONDS		902
// 	#define CD_INTEREST		903
// 	#define MSR_FUTURE		904
// 	#define USD_FUTURE		905
// 	#define USD_OPTION		906
// 	#define JPY_FUTURE		907
// 	#define EUR_FUTURE		908
// 	#define GOLD_FUTURE		909
// 	#define PIG_FUTURE		910 
//-------------------------------------------

#define DEF_CONTINUE_FUT_CODE					"00000000" //"10199999"	//���ἱ��.
#define SZDEF_CONTINUE_FUT_CODE					"���ἱ��"

//���ǵ� Master�̸���.
#define		DRFNMASTER_UMASTER					"UMaster"
#define		DRFNMASTER_KUMASTER					"kUMASTER"
#define		DRFNMASTER_TMMASTER					"TMMASTER"
#define		DRFNMASTER_KRXUMASTER				"KRXUMaster"
#define		DRFNMASTER_K200UMASTER				"K200UMaster"
#define		DRFNMASTER_K100UMASTER				"K100UMaster"
#define		DRFNMASTER_GRPMASTER				"GRPMASTER"
#define		DRFNMASTER_JFMASTER					"JFMASTER"
#define		DRFNMASTER_JPMASTER					"JPMASTER"
#define		DRFNMASTER_ELWINDEXMASTER			"ELWINDEXMASTER"
#define		DRFNMASTER_ELWISSUEMASTER			"ELWISSUEMASTER"
#define		DRFNMASTER_OLDFUTUREMASTER			"OLDFUTUREMASTER"


typedef struct 
{
//	CString m_szCode;
	CString	m_szCodeNme;
	int		m_nCodeType;
	int		m_nMasterType;
} stDrCodeItemInfo;
typedef CList<stDrCodeItemInfo*, stDrCodeItemInfo*> List_stDrCodeItemInfo;
#define stDrCodeItemInfoCopy(pSrc, pTar)  \
	pTar->m_szCodeNme= pSrc->m_szCodeNme; \
	pTar->m_nCodeType = pSrc->m_nCodeType; \
	pTar->m_nMasterType = pSrc->m_nMasterType; 
// pTar->m_szCode=pSrc->m_szCode;

typedef struct
{
	CStringList* pArrList;
	int nArrListCnt;
	
	CString szMasterKey;
	CString szInputKey[2];
} stQueryMasterInfo;

#endif //AFX_MASTERDATASUB_BY_JUNOK_LEE__INCLUDED_
