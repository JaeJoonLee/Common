#ifndef _NEW_DLLCONTENTS_PLATFORM_CODE_DEF_HEADER____
#define _NEW_DLLCONTENTS_PLATFORM_CODE_DEF_HEADER____

// #include "../../_Include/MasterDefine.h"
#include <AFXTEMPL.H>

//#include "../_Platform/CodeDef.h"

// #include "./LocalUtil.h"
// 2005.11.25(금)
// 플랫폼에서 사용하는 "LoaclUtil.h", "LoaclUtil.cpp" 파일을 변경함
//
// ReadData 함수부분을 구현하는 cpp때문에 "LoaclUtil.cpp"을
// 포함시켜야 하기때문에 헤더에서는 return FALSE; 하는 루틴으로 처리시킴.
// 실제 구현은 Code.ocx에서하며 가져가 쓰는 형태이기 때문에 이렇게해도 가능...

class CMasterBase
{
public:
	virtual BOOL ReadData(LPCSTR _szStr) { return FALSE; }
};

// 	//#define	ONESIZE_JMASTER	(1+1+18+6+7+3+1+1+3)
// 	#define	ONESIZE_JMASTER	(1+1+18+6+7+1+3+1+1+1+3+1)
// 	class CJMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szUnder;		// 1  관리/감리구분
// 		CString m_szWarn;		// 1  투자유의 구분
// 		CString m_szName;		// 18 종목명
// 		CString m_szCode;		// 6  종목코드
// 		CString m_szSymbol;		// 7  심벌
// 		CString m_szGubun;		// 1  업종구분
// 		CString m_szUpCode;		// 3  업종코드
// 		CString m_szS;			// 1  부구분
// 	//	CString m_szC;			// 1  대중소
// 		CString m_szG;			// 3  그룹코드
// 		CString m_manuf;		// 1  "1" 제조업
// 	};
// 
// 	// 박성진 2002.09.15
// 	// JMaster 에 그룹사 양식 추가.(파일을 JMaster 와 동일)
// 	// 박성진 2002.09.18 => SK KMaster.dat 파일이 준비가 안됨
// 	#define	ONESIZE_KMASTER	(1+1+18+6+7+1+3+1+3+3+1+1+1+3)
// 	class CKMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szUnder;		// 1  관리/감리구분
// 		CString m_szWarn;		// 1  투자유의 구분
// 		CString m_szName;		// 18 종목명
// 		CString m_szCode;		// 6  종목코드
// 		CString m_szGubun;		// 1  구분
// 		CString	m_szUpCode;		// 3  업종코드
// 	//	CString m_szS;			// 1  부구분
// 		CString m_szUpCodem;	// 3  업종코드(중분류 020 ~ 049)
// 		CString m_szUpCodel;	// 3  업종코드(대분류 002 ~ 019)
// 		CString	m_szCapsize;	// 1  시가총액 '1':대 '2':중 '3':소 */
// 										/* '1':KOSDAQ100 '2':KOSDAQMID300 '3':KOSDAQSMALL */
// 		CString m_szVen;		// 1  벤처구분
// 	//	CString m_stargb;		// 1  스타지수'1'
// 	//    CString m_szg;			// 3     /* 코스닥 그룹코드추가(20051107)*/
// 	};

#define	ONESIZE_UMASTER	(18+1+3)
class CUMaster : public CMasterBase
{
public:
	virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }

	CString m_szName;		// 18 업종명
	CString m_szGubun;		// 1 구분
	CString m_szCode;		// 3  업종코드
};
 
#define	ONESIZE_KUMASTER	(18+1+3)
class CKUMaster : public CMasterBase
{
public:
	virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }

	CString m_szName;		// 18 업종명
	CString m_szGubun;		// 1 구분
	CString m_szCode;		// 2  업종코드
};

// 	#define ONESIZE_UPMASTER (18+1+3)
// 	class CUPMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 20 업종명
// 		CString m_szGubun;		// 1 구분
// 		CString m_szCode;		// 3  업종코드
// 	};
// 
// 	#define ONESIZE_UDMASTER (18+1+3)
// 	class CUDMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 18 업종명
// 		CString m_szGubun;		// 1  업종구분
// 		CString m_szCode;		// 3  업종코드
// 	};
// 
// 	// 제3시장
// 	#define	ONESIZE_TMASTER	(40+6)
// 	class CTMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 40 종목명
// 		CString m_szCode;		//   종목코드
// 	};
// 
// 	#define	ONESIZE_GMASTER	(40+3)
// 	class CGMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 40 그룹명
// 		CString	m_szGubun;		// 0  구분
// 		CString m_szCode;		// 3  그룹코드
// 	};
// 
// 	// 선물
// 	// #define	ONESIZE_FMASTER	(20+5)
// 	#define	ONESIZE_FMASTER	(NAMELEN_F+CODELEN_F)
// 	class CFMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 30 그룹명
// 		CString m_szCode;		// 8  그룹코드
// 	};
// 
// 	// 옵션
// 	#define	ONESIZE_PMASTER	(14+8)
// 	class CPMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 14 그룹명
// 		CString m_szCode;		// 8  그룹코드
// 	};
// 
// 	// 테마
// 	#define	ONESIZE_THMASTER	(50+4)
// 	class CTHMaster : public CMasterBase
// 	{
// 	public:
//  		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
//  
//  		CString m_szName;		// 50 그룹명
// 		CString	m_szGubun;		// 1 구분
//  		CString m_szCode;		// 4  테마코드
// 	};
// 
// 	// * 결재년월
// 	#define		ONESIZE_DMaster			(6+11)
// 	class CDMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
//  		CString m_szCode;		// 6  결재년월코드
//  		CString m_szName;		// 11 코드명
// 	//	CString m_szDate;		// 7 결재년월
// 	};
// 
// 	// 박성진 2002.06.27
// 	// 국내, 국외를 구분하기 위해서
// 	// * 거래원코드
// 	#define		ONESIZE_SMaster		(20 + 3 + 1)
// 	class CSMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 20 증권사명
// 		CString	m_szCode;		//  3 코드
// 		CString m_szGubun;		//  1 국내(0), 외국(1)
// 	};
// 
// 	//  * 채권
// 	#define		ONESIZE_CMaster			(45+9)
// 	class CCMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 		
// 		CString m_szName,		// 45 채권명
// 				m_szCode;		//  9 코드
// 	};
// 
// 	// * 코스닥선물
// 	#define		ONESIZE_KFMASTER	(30 + 11)
// 	class CKFMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;
// 		CString m_szCode;
// 	};
// 
// 	// * 코스닥선물합성
// 	#define		ONESIZE_KFTSMASTER	(15)
// 	class CKFTSMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 		CString m_szCode;
// 		CString m_szName;
// 	};
// 
// 	/* 수익증권,신주인수권  Master Layout */
// 	class CBMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 		CString m_szCode;		// (20)종목명
// 		CString m_szName;		// (9)종목코드
// 	} ;
// 	#define		ONESIZE_BMASTER	 sizeof(20+9)
// 
// 	/* 수익증권,신주인수권  Master Layout */
// 	class CBEMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 		CString m_szCode;		// (20)종목명
// 		CString m_szName;		// (9)종목코드
// 	} ;
// 	#define		ONESIZE_BEMASTER	 sizeof(20+9)
// 
// 	#define		ONESIZE_BCMASTER	 sizeof(20+9)
// 	/* 신주인수권증서  Master Layout */
// 	class CBCMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 		CString m_szCode;		// (20)종목명
// 		CString m_szName;		// (9)종목코드
// 	} ;
// 
// 	class CSTKOPT	: public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCTSTR _szStr) { return FALSE; }
// 		CString m_szName;		// 종목명(20)
// 		CString m_szCode;		// 코드(2)
// 		CString m_szATM;		// ATM 가격(10)
// 		CString m_szBaseCode;	// 기초자산 코드(6)
// 		CString m_szATMPoint;	//2005.09.26 ATM 소수점자리(21)
// 	};
// 	#define		ONESIZE_STKOPT		59
// 
// 	// 주식옵션 결제월
// 	#define	ONESIZE_STKDMASTER	6
// 	class CSTKDMASTER : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szDate;		// 7 결재년월
// 	};
// 
// 	// 박성진 2002.10.09
// 	//* ETF(상장지수펀드)
// 	#define		ONESIZE_ETFMASTER		(20+6+1)
// 	class CETFMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 20 코드명
// 		CString	m_szCode;		//  6 코드
// 		CString m_szGubun;		//  1 거래소1, 코스닥2
// 	};
// 	//006 2006.01.13
// 	#define	ONESIZE_ELWMASTER	(20+6)
// 	class CELWMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 20 업종명
// 		CString m_szCode;		// 6  업종코드
// 	};

/*

typedef CList<CJMaster, CJMaster>		MASTERLIST_JMASTER;
typedef CList<CKMaster, CKMaster>		MASTERLIST_KMASTER;
typedef CList<CUMaster, CUMaster>		MASTERLIST_UMASTER;
typedef CList<CKUMaster, CKUMaster>		MASTERLIST_KUMASTER;
typedef CList<CUPMaster, CUPMaster>		MASTERLIST_UPMASTER;
typedef CList<CUDMaster, CUDMaster>		MASTERLIST_UDMASTER;
typedef CList<CTMaster, CTMaster>		MASTERLIST_TMASTER;
typedef CList<CGMaster, CGMaster>		MASTERLIST_GMASTER;
typedef CList<CFMaster, CFMaster>		MASTERLIST_FMASTER;
typedef CList<CPMaster, CPMaster>		MASTERLIST_PMASTER;
typedef CList<CTHMaster, CTHMaster>		MASTERLIST_THMASTER;
typedef CList<CDMaster, CDMaster>		MASTERLIST_DMASTER;
typedef CList<CSMaster, CSMaster>		MASTERLIST_SMASTER;
typedef CList<CCMaster, CCMaster>		MASTERLIST_CMASTER;
typedef CList<CKFMaster, CKFMaster>		MASTERLIST_KFMASTER;
typedef CList<CKFTSMaster, CKFTSMaster>	MASTERLIST_KFTSMASTER;
typedef CList<CBMaster, CBMaster>		MASTERLIST_BMASTER;
typedef CList<CBEMaster, CBEMaster>		MASTERLIST_BEMASTER;
typedef CList<CBCMaster, CBCMaster>		MASTERLIST_BCMASTER;
typedef CList<CETFMaster, CETFMaster>	MASTERLIST_ETFMASTER;
typedef CList<CSTKOPT, CSTKOPT>			MASTERLIST_SOMASTER;
typedef CList<CSTKDMASTER, CSTKDMASTER>	MASTERLIST_STKDMASTER;	

class CMaster_J_K
{
public:
	int		m_nType;		// 0:주식종목, 1:코스닥종목
	CString m_szUnder;		// 1  관리/감리구분
	CString m_szWarn;		// 1  투자유의 구분
	CString m_szName;		// 18 종목명
	CString m_szCode;		// 6  종목코드

public:
	void  Convert(CJMaster* pMaster)
	{
		m_nType = 0;
		m_szUnder = pMaster->m_szUnder;
		m_szWarn  = pMaster->m_szWarn;
		m_szName  = pMaster->m_szName;
		m_szCode  = pMaster->m_szCode;
	}

	void  Convert(CKMaster* pMaster)
	{
		m_nType = 1;
		m_szUnder = pMaster->m_szUnder;
		m_szWarn  = pMaster->m_szWarn;
		m_szName  = pMaster->m_szName;
		m_szCode  = pMaster->m_szCode;
	}
};

*/
#endif // _NEW_DLLCONTENTS_PLATFORM_CODE_DEF_HEADER____
