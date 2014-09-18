								 
#if !defined(AFX_KWTREEDEFINE_H__84B331CC_704B_4109_8D6B_C3C5CEFE61B3__INCLUDED_)
#define AFX_KWTREEDEFINE_H__84B331CC_704B_4109_8D6B_C3C5CEFE61B3__INCLUDED_

#include <map>
using namespace std;

#define TREE_GROUP_NAME_LEN			30
#define TREE_GROUP_KEY_LEN			9
#define TREE_GROUP_TYPE_LEN			2
#define TREE_GROUP_CODE_LEN			4


// Ʈ�� ����� ���� ����
#define TREE_MASTER_TYPE_KWANSIM				"KG"	// [���ɱ׷�] ������ �׷��� ���δ�.
#define TREE_MASTER_TYPE_KWANSIM_ROOT			"KR"	// ���ɱ׷��� ��Ʈ�� ���δ�.
#define TREE_MASTER_TYPE_KW_ROOT_ALL			"KA"	// ���ɱ׷��� ��Ʈ��, ���� Ʈ���� ���δ�.
#define TREE_MASTER_TYPE_JONGMOK				"MJ"	// ������ ���Ͽ��� ������ �����´�.
#define TREE_MASTER_TYPE_GROUP					"MG"	// ������ ���Ͽ��� �׷��� �����´�.
#define TREE_MASTER_TYPE_GROUP_ROOT				"MR"	// ������ ���Ͽ��� �׷��� �����´�.(�����Ϳ��� ������ �׷츸 ���δ�.)
#define	TREE_MASTER_TYPE_COMM_GROUP				"CG"	// ������� �׷��� �����´�.
#define	TREE_MASTER_TYPE_COMM_CODE				"CC"	// ������� ������ �����´�.
#define	TREE_MASTER_TYPE_COMM_CODE_HW			"HC"	// ������� ������ �����´�.(�ؿ�)
#define TREE_MASTER_TYPE_FUNCTION_GROUP			"FG"	// �Լ�ȣ��� �׷��� �����´�.
#define TREE_MASTER_TYPE_FUNCTION_CODE			"FC"	// �Լ�ȣ��� ������ �����´�.
#define TREE_MASTER_TYPE_FUNCTION_GROUP_ROOT	"FR"	// �Լ�ȣ��� �׷��� �����´�.(�����Ϳ��� ������ �׷츸 ���δ�.)
#define	TREE_MASTER_TYPE_DRFN_GROUP				"DG"	// DRFN ����� ���� �׷��� �����´�.
#define	TREE_MASTER_TYPE_DRFN_CODE				"DC"	// DRFN ����� ���� ������ �����´�.

#define TREE_MASTER_FUNCTION_SEARCH				"SECH"	// ���ǰ˻� ����
#define TREE_MASTER_FUNCTION_HOLD				"HOLD"	// ��������
#define TREE_MASTER_FUNCTION_JMCOMBO_HISTROY	"HIST"	// �ֱ���ȸ(�����޺� histroy)
#define TREE_MASTER_DRFN						"DRFN"	// DRFN �׷�

#define TREE_MASTER_FUNCTION_GNFT				"GNFT"	// �ؿܼ��� ��ü
#define TREE_MASTER_FUNCTION_GNFU				"GNFU"	// �ؿܼ��� ������
#define TREE_MASTER_FUNCTION_GNFC				"GNFC"	// �ؿܼ��� �ŷ��Һ�

/////////////////////////////////////////////////////////////////
/////////////// ����Ʈ������ ��� �ϴ� �׷� ���� ////////////////
/////////////////////////////////////////////////////////////////
#define TREE_GROUP_KEY_KWANSIM_ROOT		101000000	// ���ɱ׷� ��Ʈ
#define TREE_GROUP_KEY_ALL				102000000	// ��ü

#define TREE_GROUP_KEY_SEARCH			901000000	// ���ǰ˻� �׷� Ű
#define TREE_GROUP_KEY_BACKUP			902000000	// ��� �׷�
#define TREE_GROUP_KEY_SAVED			903000000	// ��������� ���� �ߴ� �׷� Ű

#define TREE_GROUP_KEY_KRX				201000000	// KRX �׷�

#define TREE_GROUP_KEY_ETF				202000000	// ETF
#define TREE_GROUP_KEY_KOSPI			203000000	// KOSPI
#define TREE_GROUP_KEY_KOSDAQ			204000000	// KOSDAQ

#define TREE_GROUP_KEY_K200_ETC			205000000	// �ڽ���200/��Ÿ
#define TREE_GROUP_KEY_K200_Q100		205001000	// �ڽ���200/��Ÿ | K200/Q100
#define TREE_GROUP_KEY_KOSPI_UPJONG		205002000	// �ڽ���200/��Ÿ | �ڽ��Ǿ�����
#define TREE_GROUP_KEY_KOSDAQ_UPJONG	205003000	// �ڽ���200/��Ÿ | �ڽ��ھ�����

#define TREE_GROUP_KEY_KOSPI200			207004000	// �ڽ���200

#define TREE_GROUP_KEY_HEW_ALL			208001000	// �ؿ���ü (2011/01/17 Yunchang �߰�)

#define TREE_GROUP_KEY_ELWASSET			209000000	// ELW�����ڻ꺰
#define TREE_GROUP_KEY_ELWISSUE			210000000	// ELW����ȸ�纰

#define TREE_GROUP_KEY_HISTORY			215000000	// �ֱ�����
#define TREE_GROUP_KEY_HOLD				216000000	// �����׷�
#define TREE_GROUP_KEY_THEMA			217000000	// �׸�����
#define TREE_GROUP_KEY_COMPANY			218000000	// �׷�纰

#define TREE_GROUP_KEY_FUTURES			211000000	// ����

#define TREE_GROUP_KEY_DRFN_SEARCH		301000000	// DRFN ����˻� �׷�
#define TREE_GROUP_KEY_DRFN_USER		302000000	// DRFN ��������� �׷�

#define TREE_GROUP_KEY_ETC				205005000	// ��Ÿ�׷�


/////////////////////////// Ʈ�� ���� ��ȣ ///////////////////////////
enum
{
	TREE_STYLE_KW_1 = 0,			// 0=����Ʈ��("���ɱ׷�" ��Ʈ�� �ִ�.)
	TREE_STYLE_KW_2,				// 1=����Ʈ��("���ɱ׷�" ��Ʈ�� ����.)
	TREE_STYLE_SEARCH,				// 2=����˻�Ʈ��
	TREE_STYLE_COMBO,				// 3=�޺�Ʈ��
	TREE_STYLE_ROTATOR,				// 4=��������
	TREE_STYLE_JMCOMBO,				// 5=�����޺�Ʈ��
	TREE_STYLE_JMCOMBO_EXCEPT_ELW,	// 6=�����޺�Ʈ��(Elw����)
	TREE_STYLE_KR_JISU,				// 7=��������
	TREE_STYLE_HW_JISU,				// 8=�ؿ�����
	TREE_STYLE_KW_MAP,				// 9=�ʿ���������Ʈ��
	TREE_STYLE_BOND,				// 10=�峻ä��Ʈ��
	TREE_STYLE_RBOND,				// 11=�Ҹ�ä��Ʈ��
	TREE_STYLE_NEWS,				// 12=���մ���Ʈ��
	TREE_STYLE_ONLY_KW_MAP,			// 13=���ɸ�(Map�������)
	TREE_STYLE_HW_NEWS,				// 14=�ؿ����Ǵ���Ʈ��
	TREE_STYLE_HW_KW_1,				// 15=�ؿܰ���Ʈ��("���ɱ׷�" ��Ʈ�� �ִ�.)
	TREE_STYLE_HW_KW_2,				// 16=�ؿܰ���Ʈ��("���ɱ׷�" ��Ʈ�� ����.)
	TREE_STYLE_HW_FUTURE,			// 17=�ؿܼ���Ʈ��
	TREE_STYLE_KW_PANNEL,			// 18=������
	TREE_STYLE_HW_JISU_FX,			// 19=�ؿ�����(FX)
	TREE_STYLE_KR_JISU_FX,			// 20=��������(FX)
	TREE_STYLE_HW_FUTURE_TICKER,	// 21=�ؿܼ���Ʈ��(ƼĿ)
	TREE_STYLE_HW_KW_FUTURE_1,		// 22=�ؿܼ�������Ʈ��("���ɱ׷�" ��Ʈ�� �ִ�.)
	TREE_STYLE_HW_KW_FUTURE_2,		// 23=�ؿܼ�������Ʈ��("���ɱ׷�" ��Ʈ�� ����.)
	TREE_STYLE_FX_NEW,				// 24=���մ���Ʈ��(FX)
	TREE_STYLE_ROTATOR_ELW			// 25=��������(ELW)
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


// drfn���� �ʿ��� ����
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
typedef map<int, CWnd*>	COMM_MAP;		// ������ ������� �����;� �ϴ� ��� ���

#pragma pack(pop)

#endif // !defined(AFX_KWTREEDEFINE_H__84B331CC_704B_4109_8D6B_C3C5CEFE61B3__INCLUDED_)