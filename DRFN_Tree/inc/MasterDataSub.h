// #include "./inc/MasterDataSub.h"
//
#if !defined(AFX_MASTERDATASUB_BY_JUNOK_LEE__INCLUDED_)
#define AFX_MASTERDATASUB_BY_JUNOK_LEE__INCLUDED_


// 멀티차트에서의 정의내용. MULTICHART\StdAfx.h
class CMasterTypeInfo
{
public:
	//MultiChart의 StaAfx.h에 정의된 것과 동일하게.
	enum {
		NONE_CHART= 0xFF,
		STOCK_CHART=0,		//KOSPI,KOSDAQ
		UPJONG_CHART=1,		//UP
		FUTOPT_CHART,		//선물/옵션
		STOCKFUTOPT_CHART,	//주식선물/주식옵션
		FOREIGN_CHART,		//해외
		ELW_CHART,			//ELW
		FUOPT_JIPYO_CHART,	//선물옵션지표
		COMMODITY_CHART,	//상품선물
		MARKET_CHART,		//시장지표
	};
};

class CDRCodeTypeInfo
{
public:
	//MultiChart의 StaAfx.h에 정의된 것과 동일하게.
	//NH100210 겹치는 이름이 있어서 DR_ -> DRCODETYPE_ 으로 변경함.
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
#define	drCode_sinju		109			// type 0: all, 1: 수익증권(하일리펀드), 2: ELW, 
										//	3: 신주인수권, 4: 수익증권 + 신주인수권
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
#define	drCode_smbond		123			// 소매채권 code
#define drCode_reits		124			// Reits Code
#define drCode_etf			125			// etf
#define	drCode_fd			126			// fund
#define	drCode_cfuture		127			// 상품선물
#define	drCode_coption		128			// 상품옵션 
#define	drCode_K200FO		129			// 지수선물, 옵션 (spread, 스타 제외)
#define	drCode_foindex		130			// FOindex
#define	drCode_linkF		131			// 연결선물
#define	drCode_basic		132			// 기초자산 코드 리턴
#define	drCode_getstar		133			// STAR code
#define	drCode_gfuture		140			// 해외선물
#define	drCode_gfx			141			// FX



//	Winix 상품선물 관련 종목 구분(Code Type)
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

#define DEF_CONTINUE_FUT_CODE					"00000000" //"10199999"	//연결선물.
#define SZDEF_CONTINUE_FUT_CODE					"연결선물"

//정의된 Master이름들.
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
