								 
#if !defined(AFX_KWTREEDEFINE_H__84B331CC_704B_4109_8D6B_C3C5CEFE61B3__INCLUDED_)
#define AFX_KWTREEDEFINE_H__84B331CC_704B_4109_8D6B_C3C5CEFE61B3__INCLUDED_

#include <map>
using namespace std;

#define TREE_GROUP_NAME_LEN			30
#define TREE_GROUP_KEY_LEN			9
#define TREE_GROUP_TYPE_LEN			2
#define TREE_GROUP_CODE_LEN			4


// 트리 노드의 유형 정의
#define TREE_MASTER_TYPE_KWANSIM				"KG"	// [관심그룹] 하위로 그룹을 보인다.
#define TREE_MASTER_TYPE_KWANSIM_ROOT			"KR"	// 관심그룹을 루트에 보인다.
#define TREE_MASTER_TYPE_KW_ROOT_ALL			"KA"	// 관심그룹을 루트에, 종목도 트리에 보인다.
#define TREE_MASTER_TYPE_JONGMOK				"MJ"	// 마스터 파일에서 종목을 가져온다.
#define TREE_MASTER_TYPE_GROUP					"MG"	// 마스터 파일에서 그룹을 가져온다.
#define TREE_MASTER_TYPE_GROUP_ROOT				"MR"	// 마스터 파일에서 그룹을 가져온다.(마스터에서 가져온 그룹만 보인다.)
#define	TREE_MASTER_TYPE_COMM_GROUP				"CG"	// 통신으로 그룹을 가져온다.
#define	TREE_MASTER_TYPE_COMM_CODE				"CC"	// 통신으로 종목을 가져온다.
#define	TREE_MASTER_TYPE_COMM_CODE_HW			"HC"	// 통신으로 종목을 가져온다.(해외)
#define TREE_MASTER_TYPE_FUNCTION_GROUP			"FG"	// 함수호출로 그룹을 가져온다.
#define TREE_MASTER_TYPE_FUNCTION_CODE			"FC"	// 함수호출로 종목을 가져온다.
#define TREE_MASTER_TYPE_FUNCTION_GROUP_ROOT	"FR"	// 함수호출로 그룹을 가져온다.(마스터에서 가져온 그룹만 보인다.)
#define	TREE_MASTER_TYPE_DRFN_GROUP				"DG"	// DRFN 모듈을 통해 그룹을 가져온다.
#define	TREE_MASTER_TYPE_DRFN_CODE				"DC"	// DRFN 모듈을 통해 종목을 가져온다.

#define TREE_MASTER_FUNCTION_SEARCH				"SECH"	// 조건검색 종목
#define TREE_MASTER_FUNCTION_HOLD				"HOLD"	// 보유종목
#define TREE_MASTER_FUNCTION_JMCOMBO_HISTROY	"HIST"	// 최근조회(종목콤보 histroy)
#define TREE_MASTER_DRFN						"DRFN"	// DRFN 그룹

#define TREE_MASTER_FUNCTION_GNFT				"GNFT"	// 해외선물 전체
#define TREE_MASTER_FUNCTION_GNFU				"GNFU"	// 해외선물 업종별
#define TREE_MASTER_FUNCTION_GNFC				"GNFC"	// 해외선물 거래소별

/////////////////////////////////////////////////////////////////
/////////////// 관심트리에서 사용 하는 그룹 정의 ////////////////
/////////////////////////////////////////////////////////////////
#define TREE_GROUP_KEY_KWANSIM_ROOT		101000000	// 관심그룹 루트
#define TREE_GROUP_KEY_ALL				102000000	// 전체

#define TREE_GROUP_KEY_SEARCH			901000000	// 조건검색 그룹 키
#define TREE_GROUP_KEY_BACKUP			902000000	// 백업 그룹
#define TREE_GROUP_KEY_SAVED			903000000	// 내보내기로 저장 했던 그룹 키

#define TREE_GROUP_KEY_KRX				201000000	// KRX 그룹

#define TREE_GROUP_KEY_ETF				202000000	// ETF
#define TREE_GROUP_KEY_KOSPI			203000000	// KOSPI
#define TREE_GROUP_KEY_KOSDAQ			204000000	// KOSDAQ

#define TREE_GROUP_KEY_K200_ETC			205000000	// 코스피200/기타
#define TREE_GROUP_KEY_K200_Q100		205001000	// 코스피200/기타 | K200/Q100
#define TREE_GROUP_KEY_KOSPI_UPJONG		205002000	// 코스피200/기타 | 코스피업종순
#define TREE_GROUP_KEY_KOSDAQ_UPJONG	205003000	// 코스피200/기타 | 코스닥업종순

#define TREE_GROUP_KEY_KOSPI200			207004000	// 코스피200

#define TREE_GROUP_KEY_HEW_ALL			208001000	// 해외전체 (2011/01/17 Yunchang 추가)

#define TREE_GROUP_KEY_ELWASSET			209000000	// ELW기초자산별
#define TREE_GROUP_KEY_ELWISSUE			210000000	// ELW발행회사별

#define TREE_GROUP_KEY_HISTORY			215000000	// 최근종목
#define TREE_GROUP_KEY_HOLD				216000000	// 보유그룹
#define TREE_GROUP_KEY_THEMA			217000000	// 테마종목
#define TREE_GROUP_KEY_COMPANY			218000000	// 그룹사별

#define TREE_GROUP_KEY_FUTURES			211000000	// 선물

#define TREE_GROUP_KEY_DRFN_SEARCH		301000000	// DRFN 종목검색 그룹
#define TREE_GROUP_KEY_DRFN_USER		302000000	// DRFN 사용자조건 그룹

#define TREE_GROUP_KEY_ETC				205005000	// 기타그룹


/////////////////////////// 트리 유형 번호 ///////////////////////////
enum
{
	TREE_STYLE_KW_1 = 0,			// 0=관심트리("관심그룹" 루트가 있다.)
	TREE_STYLE_KW_2,				// 1=관심트리("관심그룹" 루트가 없다.)
	TREE_STYLE_SEARCH,				// 2=종목검색트리
	TREE_STYLE_COMBO,				// 3=콤보트리
	TREE_STYLE_ROTATOR,				// 4=돌려보기
	TREE_STYLE_JMCOMBO,				// 5=종목콤보트리
	TREE_STYLE_JMCOMBO_EXCEPT_ELW,	// 6=종목콤보트리(Elw제외)
	TREE_STYLE_KR_JISU,				// 7=국내지수
	TREE_STYLE_HW_JISU,				// 8=해외지수
	TREE_STYLE_KW_MAP,				// 9=맵에서사용관심트리
	TREE_STYLE_BOND,				// 10=장내채권트리
	TREE_STYLE_RBOND,				// 11=소매채권트리
	TREE_STYLE_NEWS,				// 12=종합뉴스트리
	TREE_STYLE_ONLY_KW_MAP,			// 13=관심만(Map에서사용)
	TREE_STYLE_HW_NEWS,				// 14=해외증권뉴스트리
	TREE_STYLE_HW_KW_1,				// 15=해외관심트리("관심그룹" 루트가 있다.)
	TREE_STYLE_HW_KW_2,				// 16=해외관심트리("관심그룹" 루트가 없다.)
	TREE_STYLE_HW_FUTURE,			// 17=해외선물트리
	TREE_STYLE_KW_PANNEL,			// 18=전광판
	TREE_STYLE_HW_JISU_FX,			// 19=해외지수(FX)
	TREE_STYLE_KR_JISU_FX,			// 20=국내지수(FX)
	TREE_STYLE_HW_FUTURE_TICKER,	// 21=해외선물트리(티커)
	TREE_STYLE_HW_KW_FUTURE_1,		// 22=해외선물관심트리("관심그룹" 루트가 있다.)
	TREE_STYLE_HW_KW_FUTURE_2,		// 23=해외선물관심트리("관심그룹" 루트가 없다.)
	TREE_STYLE_FX_NEW,				// 24=종합뉴스트리(FX)
	TREE_STYLE_ROTATOR_ELW			// 25=돌려보기(ELW)
};
//////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

struct INRECFIELD_INFO
{
	CString m_strFieldName;
	CString m_strValue;
	int		m_nLength;
};

struct FID_OUTREC_INFO
{
	int		m_nSeq;
	CString m_strFidString;
};

struct REQUEST_INFO
{
	CString			m_strService;
	CPtrArray		m_arrInRec;
	CPtrArray		m_arrOutRec;
};


// drfn에서 필요한 정보
struct DRFN_TREE_INFO
{
	CString m_szOCPath;	// OneClick Path
	long	m_pITrComm;
	long	m_pITrcommSite;
};

struct TREE_INFO
{
	UINT			m_nKey;
	CString			m_strName;
	CString			m_strMasterType;
	CString			m_strMasterCode;
	CString			m_strRqString;
	DRFN_TREE_INFO	m_DrfnInfo;
};

typedef map<UINT, TREE_INFO*> TREEINFO_MAP;
//typedef CMap<UINT, UINT, TREE_INFO*, TREE_INFO*> TREEINFO_MAP;
class CTreeTypeInfo: public CObject
{
public:
	CTreeTypeInfo() {}
	virtual ~CTreeTypeInfo() {}

public:
	CString m_strTreeTypeName;
	
	TREEINFO_MAP m_TreeInfoMap;	
};
typedef map<int, CTreeTypeInfo*>	TREETYPE_MAP;
//typedef CMap<int, int, CTreeTypeInfo*, CTreeTypeInfo*>	TREETYPE_MAP;

// <RQID, CWnd*>
typedef map<int, CWnd*>	COMM_MAP;		// 종목을 통신으로 가져와야 하는 경우 사용

#pragma pack(pop)

#endif // !defined(AFX_KWTREEDEFINE_H__84B331CC_704B_4109_8D6B_C3C5CEFE61B3__INCLUDED_)