#ifndef _NEW_DLLCONTENTS_PLATFORM_CODE_DEF_HEADER____
#define _NEW_DLLCONTENTS_PLATFORM_CODE_DEF_HEADER____

// #include "../../_Include/MasterDefine.h"
#include <AFXTEMPL.H>

//#include "../_Platform/CodeDef.h"

// #include "./LocalUtil.h"
// 2005.11.25(��)
// �÷������� ����ϴ� "LoaclUtil.h", "LoaclUtil.cpp" ������ ������
//
// ReadData �Լ��κ��� �����ϴ� cpp������ "LoaclUtil.cpp"��
// ���Խ��Ѿ� �ϱ⶧���� ��������� return FALSE; �ϴ� ��ƾ���� ó����Ŵ.
// ���� ������ Code.ocx�����ϸ� ������ ���� �����̱� ������ �̷����ص� ����...

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
// 		CString m_szUnder;		// 1  ����/��������
// 		CString m_szWarn;		// 1  �������� ����
// 		CString m_szName;		// 18 �����
// 		CString m_szCode;		// 6  �����ڵ�
// 		CString m_szSymbol;		// 7  �ɹ�
// 		CString m_szGubun;		// 1  ��������
// 		CString m_szUpCode;		// 3  �����ڵ�
// 		CString m_szS;			// 1  �α���
// 	//	CString m_szC;			// 1  ���߼�
// 		CString m_szG;			// 3  �׷��ڵ�
// 		CString m_manuf;		// 1  "1" ������
// 	};
// 
// 	// �ڼ��� 2002.09.15
// 	// JMaster �� �׷�� ��� �߰�.(������ JMaster �� ����)
// 	// �ڼ��� 2002.09.18 => SK KMaster.dat ������ �غ� �ȵ�
// 	#define	ONESIZE_KMASTER	(1+1+18+6+7+1+3+1+3+3+1+1+1+3)
// 	class CKMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szUnder;		// 1  ����/��������
// 		CString m_szWarn;		// 1  �������� ����
// 		CString m_szName;		// 18 �����
// 		CString m_szCode;		// 6  �����ڵ�
// 		CString m_szGubun;		// 1  ����
// 		CString	m_szUpCode;		// 3  �����ڵ�
// 	//	CString m_szS;			// 1  �α���
// 		CString m_szUpCodem;	// 3  �����ڵ�(�ߺз� 020 ~ 049)
// 		CString m_szUpCodel;	// 3  �����ڵ�(��з� 002 ~ 019)
// 		CString	m_szCapsize;	// 1  �ð��Ѿ� '1':�� '2':�� '3':�� */
// 										/* '1':KOSDAQ100 '2':KOSDAQMID300 '3':KOSDAQSMALL */
// 		CString m_szVen;		// 1  ��ó����
// 	//	CString m_stargb;		// 1  ��Ÿ����'1'
// 	//    CString m_szg;			// 3     /* �ڽ��� �׷��ڵ��߰�(20051107)*/
// 	};

#define	ONESIZE_UMASTER	(18+1+3)
class CUMaster : public CMasterBase
{
public:
	virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }

	CString m_szName;		// 18 ������
	CString m_szGubun;		// 1 ����
	CString m_szCode;		// 3  �����ڵ�
};
 
#define	ONESIZE_KUMASTER	(18+1+3)
class CKUMaster : public CMasterBase
{
public:
	virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }

	CString m_szName;		// 18 ������
	CString m_szGubun;		// 1 ����
	CString m_szCode;		// 2  �����ڵ�
};

// 	#define ONESIZE_UPMASTER (18+1+3)
// 	class CUPMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 20 ������
// 		CString m_szGubun;		// 1 ����
// 		CString m_szCode;		// 3  �����ڵ�
// 	};
// 
// 	#define ONESIZE_UDMASTER (18+1+3)
// 	class CUDMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 18 ������
// 		CString m_szGubun;		// 1  ��������
// 		CString m_szCode;		// 3  �����ڵ�
// 	};
// 
// 	// ��3����
// 	#define	ONESIZE_TMASTER	(40+6)
// 	class CTMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 40 �����
// 		CString m_szCode;		//   �����ڵ�
// 	};
// 
// 	#define	ONESIZE_GMASTER	(40+3)
// 	class CGMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 40 �׷��
// 		CString	m_szGubun;		// 0  ����
// 		CString m_szCode;		// 3  �׷��ڵ�
// 	};
// 
// 	// ����
// 	// #define	ONESIZE_FMASTER	(20+5)
// 	#define	ONESIZE_FMASTER	(NAMELEN_F+CODELEN_F)
// 	class CFMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 30 �׷��
// 		CString m_szCode;		// 8  �׷��ڵ�
// 	};
// 
// 	// �ɼ�
// 	#define	ONESIZE_PMASTER	(14+8)
// 	class CPMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 14 �׷��
// 		CString m_szCode;		// 8  �׷��ڵ�
// 	};
// 
// 	// �׸�
// 	#define	ONESIZE_THMASTER	(50+4)
// 	class CTHMaster : public CMasterBase
// 	{
// 	public:
//  		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
//  
//  		CString m_szName;		// 50 �׷��
// 		CString	m_szGubun;		// 1 ����
//  		CString m_szCode;		// 4  �׸��ڵ�
// 	};
// 
// 	// * ������
// 	#define		ONESIZE_DMaster			(6+11)
// 	class CDMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
//  		CString m_szCode;		// 6  �������ڵ�
//  		CString m_szName;		// 11 �ڵ��
// 	//	CString m_szDate;		// 7 ������
// 	};
// 
// 	// �ڼ��� 2002.06.27
// 	// ����, ���ܸ� �����ϱ� ���ؼ�
// 	// * �ŷ����ڵ�
// 	#define		ONESIZE_SMaster		(20 + 3 + 1)
// 	class CSMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 20 ���ǻ��
// 		CString	m_szCode;		//  3 �ڵ�
// 		CString m_szGubun;		//  1 ����(0), �ܱ�(1)
// 	};
// 
// 	//  * ä��
// 	#define		ONESIZE_CMaster			(45+9)
// 	class CCMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 		
// 		CString m_szName,		// 45 ä�Ǹ�
// 				m_szCode;		//  9 �ڵ�
// 	};
// 
// 	// * �ڽ��ڼ���
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
// 	// * �ڽ��ڼ����ռ�
// 	#define		ONESIZE_KFTSMASTER	(15)
// 	class CKFTSMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 		CString m_szCode;
// 		CString m_szName;
// 	};
// 
// 	/* ��������,�����μ���  Master Layout */
// 	class CBMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 		CString m_szCode;		// (20)�����
// 		CString m_szName;		// (9)�����ڵ�
// 	} ;
// 	#define		ONESIZE_BMASTER	 sizeof(20+9)
// 
// 	/* ��������,�����μ���  Master Layout */
// 	class CBEMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 		CString m_szCode;		// (20)�����
// 		CString m_szName;		// (9)�����ڵ�
// 	} ;
// 	#define		ONESIZE_BEMASTER	 sizeof(20+9)
// 
// 	#define		ONESIZE_BCMASTER	 sizeof(20+9)
// 	/* �����μ�������  Master Layout */
// 	class CBCMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 		CString m_szCode;		// (20)�����
// 		CString m_szName;		// (9)�����ڵ�
// 	} ;
// 
// 	class CSTKOPT	: public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCTSTR _szStr) { return FALSE; }
// 		CString m_szName;		// �����(20)
// 		CString m_szCode;		// �ڵ�(2)
// 		CString m_szATM;		// ATM ����(10)
// 		CString m_szBaseCode;	// �����ڻ� �ڵ�(6)
// 		CString m_szATMPoint;	//2005.09.26 ATM �Ҽ����ڸ�(21)
// 	};
// 	#define		ONESIZE_STKOPT		59
// 
// 	// �ֽĿɼ� ������
// 	#define	ONESIZE_STKDMASTER	6
// 	class CSTKDMASTER : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szDate;		// 7 ������
// 	};
// 
// 	// �ڼ��� 2002.10.09
// 	//* ETF(���������ݵ�)
// 	#define		ONESIZE_ETFMASTER		(20+6+1)
// 	class CETFMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 20 �ڵ��
// 		CString	m_szCode;		//  6 �ڵ�
// 		CString m_szGubun;		//  1 �ŷ���1, �ڽ���2
// 	};
// 	//006 2006.01.13
// 	#define	ONESIZE_ELWMASTER	(20+6)
// 	class CELWMaster : public CMasterBase
// 	{
// 	public:
// 		virtual BOOL ReadData(LPCSTR _szStr)  { return FALSE; }
// 
// 		CString m_szName;		// 20 ������
// 		CString m_szCode;		// 6  �����ڵ�
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
	int		m_nType;		// 0:�ֽ�����, 1:�ڽ�������
	CString m_szUnder;		// 1  ����/��������
	CString m_szWarn;		// 1  �������� ����
	CString m_szName;		// 18 �����
	CString m_szCode;		// 6  �����ڵ�

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
