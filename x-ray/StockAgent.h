#if !defined(AFX_STOCKAGENT_H__ABE2770E_4A30_4F1D_B5E0_E256AA03E998__INCLUDED_)
#define AFX_STOCKAGENT_H__ABE2770E_4A30_4F1D_B5E0_E256AA03E998__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StockAgent.h : header file
//
#include "XRayDLL.h"		//KJI 20060328
/////////////////////////////////////////////////////////////////////////////
// CStockAgent window
//#include "../CommonLib/ServerMsg.h"
//#include "RealUpdate.h"

class CStockAgent : public CWnd
{
// Construction
public:
	CStockAgent();

// Attributes
public:

// Operations
public:
	BOOL	LoadDll();	//KJI 20060511
	void	UnLoadDll();
	//BOOL	IsLoad();
	//void	SetOfferUint(int nPos, int nUnit);
	//int		ConvertCode(CString strCode, int nJongType);
	//CString	DeConvertCode(CString strCode, int* pnJongType);	//KJI 20060508

	//BOOL	CheckQuery(CString strQuery, int* pQryType);
	//BOOL	IsAnalCode(CString strCode, int nJongType);
	//BOOL	CreateIO(CString strCode, int nJongType, int nPower, HWND hWnd);
	//BOOL	DeleteIO(CString strCode, int nJongType, int nPower, HWND hWnd);

	//KJI 20060517
//	BOOL	GetChekyulXRayData(CString strAcc, CString strCode, CString strOrderNo, CString strOrderOrgNo, CString strJState, CRealData* pData);
//	BOOL	SetCheyulRealData(CString& strAcc, CString& strCode, CString& strOrderNo, CString& strOrderOrgNo, CString& strJState, int nJongType, CRealData* pData);
//	BOOL	GetRealData(WORD wRealType, CString strCodeKey, int nJongType, int nPower, int nRange, HWND hWnd, CRealData* pData);
//	BOOL	SetRealData(WORD wRealType, CString strCodeKey, int nJongType, CRealData* pData);
//	BOOL	GetAnalData(CString strQryCode, CString strCode, int nJongType, int nPower, int nRange, HWND hWnd, CDWordArray* pCurPrice, CServerMsg* pMsg);
//	BOOL	SetAnalData(CString strQryCode, CString strCode, int nJongType, int nPower, HWND hWnd, CServerMsg* pMsg);
//	void	DelAnalData(CString	strCode, int nJongType);

//	BOOL	SetAccountMicheInfo(BYTE* pBuf, long lSize, CString& strAcc, CString& strPwd, CString& strNextKey);	//KJI 20060612
//
//	CString	GetPriceAccInfo(CString strCode, int nJongType, long lPrice);
//	int		GetMaxFilter(CString strCode, int nJongType, int nShowNum);	//KJI 20060420
//
//	//KJI 20060422
//	void	ClearMicheOrderNo();
////	BOOL	GetMicheXRayData(CString strAcc, CServerMsg* pMsg);
//	BOOL	GetMicheInfo(CString strAcc, CString strOrderNo, 
//						int* pVol, int* pQty, int* pPrice, XRAY_POWER* pDetail);	//KJI 20060422
//	void	DeleteMicheInfo(CString strAcc);	//KJI 20060424
//
//	//KJI 20060503
//	BOOL	CheckFocusData(CString strName, CRealData* pData, CString strKey);
//	void	ChangeFocusData(CString strName, CRealData* pData);	
//	void	LoadFocusData(CString strFilePath);
//
//	//ynkim 20060906 ELW 포착
//	BOOL	CheckFocusData_ELW(CString strName, CRealData* pData, CString strKey);
//	void	LoadFocusData_ELW(CString strFilePath);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockAgent)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStockAgent();

public:
//	HWND					m_hDataMgr;
	HMODULE					m_hMod;
	XRCreate				fXRayCreate;
	XRDelete				fXRayDelete;
	XRCreateH				fXRayCreateH;
	XRDeleteH				fXRayDeleteH;
	XRGetStdData			fXRayGetStdData;
	XRGetPowerData			fXRayGetPowerData;
	XRGetPriceData			fXRayGetPriceData;
	XRCreateIO				fXRayCreateIO;
	XRDeleteIO				fXRayDeleteIO;
	XRGetIOData				fXRayGetIOData;
	XRGetIOPriceData		fXRayGetIOPriceData;
	XRGetOffer				fXRGetOfferData;
	XRSetSiseData			fXRaySetSiseData;
	XRSetHogaData			fXRaySetHogaData;
	XRCodeConv				fXRayCodeConv;
	XRIsExist				fXRayIsExist;
	XRIsExistH				fXRayIsExistH;
	XRSetMiche				fXRaySetMiche;
	XRSetReal				fXRaySetReal;
	XRGetPriceToOrderVol	fXRayPriceToOrderVol;	//KJI 20060410
	XRGetRemainOrderVol		fXRayRemainOrderVol;
	XRGetOrderNoToOrderVol	fXRayOrderNoToOrderVol;
	XRGetPriceByOrderNo		fXRayPriceByOrderNo;
	XRGetMaxFilter			fXRayGetMaxFilter;			//KJI 20060420
	XRGetPowerRangeRatio	fXRayGetPowerRangeRatio;	//KJI 20060615
	XRGetIOPowerRatio		fXRayGetIOPowerRatio;
	XRGetChPowerRatio		fXRayGetChPowerRatio;
	XRClearMicheInfo		fXRayClearMicheInfo;
	XRDataLogMode			fXRayDataLogMode;			//KJI 20060628(분석 데이터 확인시 사용)
	XRGetHandleList			fXRayGetHandleList;

	CMapWordToPtr			m_mapHwndList;
	//void					fXRayCreateH(int nXRayCode, HWND hRecvWnd);
	//void					fXRayDeleteH(int nXRayCode, HWND hRecvWnd);
	//int						fXRayGetHandleList(int nXRayCode, int* nHwndList);
	void					fXRayGetPowerPercent(int nXRayCode, int nXRayFilter, int nPricePos, SHA_POWER* ShaPower);


	//CDWordArray			m_aCurPrice;
	//int					m_nOfferUnit[10];	//10단계지만
	//SHA_MICHE_INFO*		m_pInfo;
	//int					m_nMicheCnt;
	//int					m_nAccInfoCnt;	
	//CStringArray		m_aOrderNo;		//KJI 20060422 (미체결시 주문번호)
	//CStringArray		m_aOrderOrgNo;		//KJI 20060517 (미체결시 원주문번호)
	//CStringArray		m_aCode;		//KJI 20060517

	////KJI 20060503 (포착관련)
	//CString			m_strFileName;	//ynkim 20060912
	//CString			m_strMainDir;
	//int				m_nMarketType;
	//int				m_nIntrPos;
	//int				m_nCodeUse;
	//CStringArray	m_saFCode;
	//CStringArray	m_saFExecption;
	//int				m_nPUse;
	//int				m_nPriceMin;
	//int				m_nPriceMax;
	//int				m_nVUse;
	//int				m_nVolMin;
	//int				m_nVolMax;
	//int				m_nUDUse;
	//double			m_dUDMin;
	//double			m_dUDMax;
	//int				m_nFNBuySel;
	//int				m_nFNRange;
	//int				m_nFNVol;
	//int				m_nFNAmt;
	//int				m_nFCBuySel;
	//int				m_nFCVol;
	//int				m_nFCAmt;
	///////////////////////////////

	////ynkim 20060906 ELW 포착
	////KJI 20060503 (포착관련)
	//CString			m_strFileName_ELW;
	//CString			m_strMainDir_ELW;
	//int				m_nMarketType_ELW;
	//int				m_nIntrPos_ELW;
	//int				m_nCodeUse_ELW;
	//CStringArray	m_saFCode_ELW;
	//int				m_nPUse_ELW;
	//int				m_nPriceMin_ELW;
	//int				m_nPriceMax_ELW;
	//int				m_nVUse_ELW;
	//int				m_nVolMin_ELW;
	//int				m_nVolMax_ELW;
	//int				m_nUDUse_ELW;
	//double			m_dUDMin_ELW;
	//double			m_dUDMax_ELW;
	//int				m_nFNBuySel_ELW;
	//int				m_nFNRange_ELW;
	//int				m_nFNVol_ELW;
	//int				m_nFNAmt_ELW;
	//int				m_nFCBuySel_ELW;
	//int				m_nFCVol_ELW;
	//int				m_nFCAmt_ELW;
	////////////////////////////////

	//int		GetMaxPowerNum(SHA_POWER* pPowerData);	//KJI 20060530
	//int		GetMaxOfferNum(int nCnt, SHA_DISTRIBUTION *pOfferData);	//KJI 20060420
	//double	CalcRatio(int nUnitVol, int nVol);	//KJI 20060530
	//void	ConvHogaIndex(int nIndex, int* pPowerPos);
	//void	GetPowerData(CString strCode, int nJongType, int nPower, int nRange, HWND hWnd, CDWordArray* pCurPrice, CServerMsg* pMsg);
	//void	GetIOData(CString strCode, int nJongType, int nPower, int nRange, HWND hWnd, CDWordArray* pCurPrice, CServerMsg* pMsg);
	//void	GetOfferData(CString strCode, int nJongType, int nPower, CServerMsg* pMsg);
	//void	GetFocusData(CString strQryCode, CServerMsg* pMsg);	//KJI 20060504

//	void	GetPowerRealData(CString strCode, int nJongType, int nPower, int nRange, HWND hWnd, CRealData* pData);
//	void	GetIORealData(CString strCode, int nJongType, int nPower, int nRange, HWND hWnd, CRealData* pData);
//	void	GetOfferRealData(CString strCode, int nJongType, int nPower, int nRange, CRealData* pData);
//
//	void	SetSiseRealData(CString strCode, int nJongType, CRealData* pData);
//	void	SetHogaRealData(CString strCode, int nJongType, CRealData* pData);
//
////	BOOL	GetMicheData(CString strAcc, CString strCode, CString strOrderOrgNo, CString strOrderNo, CServerMsg* pMsg);	//KJI 20060517
//
//	void	WriteDataLog(CString strCode, int nPower);	//KJI 20060629

	short	ByteReverseShort(short *a);
	int		ByteReverseInt(int *a);
	void	ByteReverseDetail(SHA_DETAIL *tmp);
	void	ByteReverseShaPrice(SHA_PRICE *tmp);
	void	ByteReverseHoga(KOS_HOGA_DATA *tmp);
	void	ByteReverseKosPacket(KOS_PACKET *tmp);
	void	ByteReverseShaData(SHA_DATA *tmp);

	////KJI 20060503
	//BOOL	CF_MarketValid(CRealData* pData);
	//BOOL	CF_CodeValid(CRealData* pData);
	//BOOL	CF_ExceptionValid(CRealData* pData);
	//BOOL	CF_ConditionValid(CRealData* pData);
	//BOOL	CF_FocusValid(CRealData* pData);
	//BOOL	CheckIntrCodeList(int nIndex, CString strCode);

	////ynkim 20060906
	//BOOL	CF_MarketValid_ELW(CRealData* pData);
	//BOOL	CF_CodeValid_ELW(CRealData* pData);
	//BOOL	CF_ConditionValid_ELW(CRealData* pData);
	//BOOL	CF_FocusValid_ELW(CRealData* pData);

	// Generated message map functions
protected:
	//{{AFX_MSG(CStockAgent)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKAGENT_H__ABE2770E_4A30_4F1D_B5E0_E256AA03E998__INCLUDED_)
