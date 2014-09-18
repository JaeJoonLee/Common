// StockAgent.cpp : implementation file
//

#include "stdafx.h"
#include "StockAgent.h"

//#include "../include/CommonDef.h"
//#include "../include/EnvDir.h"
//#include "../include/IniFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define QRY_POWER	0
#define	QRY_IO		1
#define	QRY_OFFER	2
#define	QRY_FOCUS	3

#define HOGA_10_RANGE	20
/////////////////////////////////////////////////////////////////////////////
// CStockAgent

CStockAgent::CStockAgent()
{
	m_hMod = NULL;
	//m_pInfo = NULL;
	//m_nMicheCnt = 0;

	////KJI 20060503
	//m_nMarketType = 0;
	//m_nIntrPos = 0;
	//m_nPriceMin = 0;
	//m_nPriceMax = 0;
	//m_nVolMin = 0;
	//m_nVolMax = 0;
	//m_dUDMin = 0.0;
	//m_dUDMax = 0.0;
	//m_nFNBuySel = 0;
	//m_nFNRange = 0;
	//m_nFNVol = 0;
	//m_nFNAmt = 0;
	//m_nFCBuySel = 0;
	//m_nFCVol = 0;
	//m_nFCAmt = 0;
	//m_nCodeUse = 0;
	//m_nPUse = 0;
	//m_nVUse = 0;
	//m_nUDUse = 0;

	////ynkim 20060922
	//m_nMarketType_ELW = 0;
	//m_nIntrPos_ELW = 0;
	//m_nPriceMin_ELW = 0;
	//m_nPriceMax_ELW = 0;
	//m_nVolMin_ELW = 0;
	//m_nVolMax_ELW = 0;
	//m_dUDMin_ELW = 0.0;
	//m_dUDMax_ELW = 0.0;
	//m_nFNBuySel_ELW = 0;
	//m_nFNRange_ELW = 0;
	//m_nFNVol_ELW = 0;
	//m_nFNAmt_ELW = 0;
	//m_nFCBuySel_ELW = 0;
	//m_nFCVol_ELW = 0;
	//m_nFCAmt_ELW = 0;
	//m_nCodeUse_ELW = 0;
	//m_nPUse_ELW = 0;
	//m_nVUse_ELW = 0;
	//m_nUDUse_ELW = 0;

	//GET_MAIN_DIR(m_strMainDir);
}

CStockAgent::~CStockAgent()
{
	if ( m_hMod )
		UnLoadDll();

	WORD	nKey;
	int*	nHwndList;
	POSITION pos = m_mapHwndList.GetStartPosition();
	while (pos)
	{
		m_mapHwndList.GetNextAssoc(pos, nKey, (void*&)nHwndList);
		delete[] nHwndList;
		nHwndList = NULL;
	}
}


BEGIN_MESSAGE_MAP(CStockAgent, CWnd)
	//{{AFX_MSG_MAP(CStockAgent)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStockAgent message handlers
BOOL CStockAgent::LoadDll()
{
//	m_hDataMgr = hDataMgr;	//KJI 20060512

	m_hMod = LoadLibrary("StockXray.dll");
	if(	m_hMod == NULL)
	{
		AfxMessageBox("StockXray.dll을 로드할 수 없습니다.");
		return FALSE;
	}

	fXRayCreate = (XRCreate)GetProcAddress(m_hMod, "_sha_create");
	if(	fXRayCreate == NULL)
	{
		AfxMessageBox("_sha_create 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayDelete = (XRDelete)GetProcAddress(m_hMod, "_sha_delete");
	if(	fXRayDelete == NULL)
	{
		AfxMessageBox("_sha_delete 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayCreateH = (XRCreateH)GetProcAddress(m_hMod, "_sha_create_by_handle");
	if(	fXRayCreateH == NULL)
	{
		AfxMessageBox("_sha_create_by_handle 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayDeleteH = (XRDeleteH)GetProcAddress(m_hMod, "_sha_delete_by_handle");
	if(	fXRayDeleteH == NULL)
	{
		AfxMessageBox("_sha_delete_by_handle 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}
	
	fXRayGetStdData = (XRGetStdData)GetProcAddress(m_hMod, "_sha_get");
	if(	fXRayGetStdData == NULL)
	{
		AfxMessageBox("_sha_get 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayGetPowerData = (XRGetPowerData)GetProcAddress(m_hMod, "_sha_get_power");
	if(	fXRayGetPowerData == NULL)
	{
		AfxMessageBox("_sha_get_power 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayGetPriceData = (XRGetPriceData)GetProcAddress(m_hMod, "_sha_get_price");
	if(	fXRayGetPriceData == NULL)
	{
		AfxMessageBox("_sha_get_price 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayCreateIO = (XRCreateIO)GetProcAddress(m_hMod, "_sha_io_create");
	if(	fXRayCreateIO == NULL)
	{
		AfxMessageBox("_sha_io_create 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayDeleteIO = (XRDeleteIO)GetProcAddress(m_hMod, "_sha_io_delete");
	if(	fXRayDeleteIO == NULL)
	{
		AfxMessageBox("_sha_io_delete 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayGetIOData = (XRGetIOData)GetProcAddress(m_hMod, "_sha_io_get");
	if(	fXRayGetIOData == NULL)
	{
		AfxMessageBox("_sha_io_get 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayGetIOPriceData = (XRGetIOPriceData)GetProcAddress(m_hMod, "_sha_io_get_price");
	if(	fXRayGetIOPriceData == NULL)
	{
		AfxMessageBox("_sha_io_get_price 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRGetOfferData = (XRGetOffer)GetProcAddress(m_hMod, "_sha_get_distribution");
	if(	fXRGetOfferData == NULL)
	{
		AfxMessageBox("_sha_get_distribution 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRaySetSiseData = (XRSetSiseData)GetProcAddress(m_hMod, "_sha_set_sise");
	if(	fXRaySetSiseData == NULL)
	{
		AfxMessageBox("_sha_set_sise 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRaySetHogaData = (XRSetHogaData)GetProcAddress(m_hMod, "_sha_set_hoga");
	if(	fXRaySetHogaData == NULL)
	{
		AfxMessageBox("_sha_set_hoga 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayCodeConv = (XRCodeConv)GetProcAddress(m_hMod, "_sha_code_conv");
	if(	fXRayCodeConv == NULL)
	{
		AfxMessageBox("_sha_code_conv 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	//KJI 20060420
	fXRayGetMaxFilter = (XRGetMaxFilter)GetProcAddress(m_hMod, "_sha_get_max_filter");
	if(	fXRayGetMaxFilter == NULL)
	{
		AfxMessageBox("_sha_get_max_filter 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayIsExist = (XRIsExist)GetProcAddress(m_hMod, "_sha_is_exist");
	if(	fXRayIsExist == NULL)
	{
		AfxMessageBox("_sha_is_exist 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayIsExistH = (XRIsExistH)GetProcAddress(m_hMod, "_sha_is_exist_by_handle");
	if(	fXRayIsExistH == NULL)
	{
		AfxMessageBox("_sha_is_exist_by_handle 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRaySetMiche = (XRSetMiche)GetProcAddress(m_hMod, "_sha_set_miche");
	if(	fXRaySetMiche == NULL)
	{
		AfxMessageBox("_sha_set_miche 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRaySetReal = (XRSetReal)GetProcAddress(m_hMod, "_sha_set_real");
	if(	fXRaySetReal == NULL)
	{
		AfxMessageBox("_sha_set_real 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	//KJI 20060410
	fXRayPriceToOrderVol = (XRGetPriceToOrderVol)GetProcAddress(m_hMod, "_sha_get_remain_order_vol");
	if(	fXRayPriceToOrderVol == NULL)
	{
		AfxMessageBox("_sha_get_remain_order_vol 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayRemainOrderVol = (XRGetRemainOrderVol)GetProcAddress(m_hMod, "_sha_get_remain_order_vol_array");
	if(	fXRayRemainOrderVol == NULL)
	{
		AfxMessageBox("_sha_get_remain_order_vol_array 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayOrderNoToOrderVol = (XRGetOrderNoToOrderVol)GetProcAddress(m_hMod, "_sha_get_remain_order_vol_by_orderno");
	if(	fXRayOrderNoToOrderVol == NULL)
	{
		AfxMessageBox("_sha_get_remain_order_vol_by_orderno 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayPriceByOrderNo = (XRGetPriceByOrderNo)GetProcAddress(m_hMod, "_sha_get_price_by_orderno");
	if(	fXRayPriceByOrderNo == NULL)
	{
		AfxMessageBox("_sha_get_price_by_orderno 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	//KJI 20060615
	fXRayGetPowerRangeRatio = (XRGetPowerRangeRatio)GetProcAddress(m_hMod, "_sha_get_power_range_ratio");
	if(	fXRayGetPowerRangeRatio == NULL)
	{
		AfxMessageBox("_sha_get_power_range_ratio 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayGetIOPowerRatio = (XRGetIOPowerRatio)GetProcAddress(m_hMod, "_sha_get_io_power_ratio");
	if(	fXRayGetIOPowerRatio == NULL)
	{
		AfxMessageBox("_sha_get_io_power_ratio 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayGetChPowerRatio = (XRGetChPowerRatio)GetProcAddress(m_hMod, "_sha_get_ch_power_ratio");
	if(	fXRayGetChPowerRatio == NULL)
	{
		AfxMessageBox("_sha_get_ch_power_ratio 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayClearMicheInfo = (XRClearMicheInfo)GetProcAddress(m_hMod, "_sha_clear_miche");
	if(	fXRayClearMicheInfo == NULL)
	{
		AfxMessageBox("_sha_clear_miche 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	//KJI 20060628
	fXRayDataLogMode = (XRDataLogMode)GetProcAddress(m_hMod, "_sha_set_logging");
	if(	fXRayDataLogMode == NULL)
	{
		AfxMessageBox("_sha_set_logging 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	fXRayGetHandleList = (XRGetHandleList)GetProcAddress(m_hMod, "_sha_get_handle_list");
	if(	fXRayGetHandleList == NULL)
	{
		AfxMessageBox("_sha_get_handle_list 함수를 로드할 수 없습니다.");
		FreeLibrary(m_hMod);
		
		m_hMod = NULL;
		return FALSE;
	}

	return TRUE;
}

void CStockAgent::UnLoadDll()
{
	if(	m_hMod != NULL)
		FreeLibrary(m_hMod);
	m_hMod = NULL;
}


short CStockAgent::ByteReverseShort(short *a)
{
	short b = *a;
    *a = (b & 0xff00) >> 8 | (b & 0x00ff) << 8;
    return *a;
}
	
int	CStockAgent::ByteReverseInt(int *a)
{
	int b = *a;
    *a = (b & 0xff000000) >> 24 | (b & 0x00ff0000) >> 8 | (b & 0x0000ff00) << 8 | (b & 0x000000ff) << 24;
    return *a;
}
	
void CStockAgent::ByteReverseDetail(SHA_DETAIL *tmp)
{
	ByteReverseInt(&tmp->vol);
    ByteReverseInt(&tmp->time);
}
	
void CStockAgent::ByteReverseShaPrice(SHA_PRICE *tmp)
{
	ByteReverseInt(&tmp->price);

	for(int nPos = 0; nPos < MAX_DETAIL; nPos++)
		ByteReverseDetail(&tmp->detail[nPos]);

	ByteReverseInt(&tmp->qty);
	ByteReverseInt(&tmp->vol);
	ByteReverseInt(&tmp->chegyul);
	ByteReverseInt(&tmp->cancel);
	ByteReverseInt(&tmp->add);
	ByteReverseInt(&tmp->gubun);
	ByteReverseInt(&tmp->not_anal_flag);
	ByteReverseInt(&tmp->not_anal_vol);
	ByteReverseShort(&tmp->update_flag);
	ByteReverseShort(&tmp->sb_che_flag);
	ByteReverseInt(&tmp->org_vol);
}
	
void CStockAgent::ByteReverseHoga(KOS_HOGA_DATA *tmp)
{
	ByteReverseInt(&tmp->sell_price);
    ByteReverseInt(&tmp->buy_price);
    ByteReverseInt(&tmp->sell_vol);
    ByteReverseInt(&tmp->buy_vol);
}
	
void CStockAgent::ByteReverseKosPacket(KOS_PACKET *tmp)
{
    ByteReverseInt(&tmp->code);
    ByteReverseShort(&tmp->jang);
    ByteReverseInt(&tmp->time);
    ByteReverseInt(&tmp->cur_price);
    ByteReverseInt(&tmp->volume);

	int nPos = 0;
    for(nPos = 0; nPos < STOCK_HOGA_RANGE; nPos++)
		ByteReverseHoga(&tmp->hoga[nPos]);

    ByteReverseInt(&tmp->count);
    ByteReverseInt(&tmp->seq_no);

    ByteReverseInt(&tmp->hoga_vol);
    ByteReverseInt(&tmp->base_vol);

	for(nPos = 0; nPos < 8; nPos++)
		ByteReverseInt(&tmp->reserved[nPos]);
}
	
void CStockAgent::ByteReverseShaData(SHA_DATA *tmp)
{
	ByteReverseKosPacket(&tmp->kos_packet);
	ByteReverseInt(&tmp->code);

	for(int nPos = 0; nPos < SHA_RANGE; nPos++)
		ByteReverseShaPrice(&tmp->sha_price[nPos]);
}

//void CStockAgent::fXRayCreateH(int nXRayCode, HWND hRecvWnd)
//{
//	int*	hWndList = NULL;
//	if ( m_mapHwndList.Lookup(nXRayCode, (void*&)hWndList) )
//	{
//		BOOL bFull = FALSE;
//		int i = 0;
//		while(hWndList[i])
//		{
//			if ( i >= 100 )
//			{
//				//	100개가 꽉차면 어케할까... 
//				bFull = TRUE;
//				break;
//			}
//			i++;
//		}
//		hWndList[i] = (int)hRecvWnd;
//	}
//	else
//	{
//		hWndList = new int[100];
//		m_mapHwndList.SetAt(nXRayCode, (void*&)hWndList);
//
//		memset(hWndList, 0x00, sizeof(int)*100);
//		hWndList[0] = (int)hRecvWnd;
//	}
//}
//
//void CStockAgent::fXRayDeleteH(int nXRayCode, HWND hRecvWnd)
//{
//	int*	hWndList = NULL;
//	if ( m_mapHwndList.Lookup(nXRayCode, (void*&)hWndList) )
//	{
//		BOOL bClear = TRUE;
//		int i = 0;
//		for ( int i = 0 ; i < 100 ; i++ )
//		{
//			if ( (int)hRecvWnd == hWndList[i] )
//			{
//				hWndList[i] = 0x00;
////				break;
//			}
//
//			if ( hWndList[i] )
//				bClear = FALSE;
//		}
//
//		if ( bClear )
//		{
//			m_mapHwndList.RemoveKey(nXRayCode);
//			delete[] hWndList;
//		}
//
//		
//
//		//while(hWndList[i])
//		//{
//		//	if ( i >= 100 )
//		//	{
//		//		//	100개가 꽉차면 어케할까... 
//		//		bFull = TRUE;
//		//		break;
//		//	}
//
//		//	if ( (int)hRecvWnd == hWndList[i] )
//		//	{
//		//		hWndList[i] = 0x00;
//		//		break;
//		//	}
//		//	i++;
//		//}
//	}
//}
//
//int CStockAgent::fXRayGetHandleList(int nXRayCode, int* nHwndList)
//{
//	int nCnt = 0;
//	int* nList = NULL;
//	if ( m_mapHwndList.Lookup(nXRayCode, (void*&)nList) )
//	{
//		BOOL bFull = FALSE;
//		int i = 0;
//		for ( int i = 0 ; i < 100 ; i++ )
//		{
//			if ( nList[i] )
//				nCnt++;
//		}
//
//		memcpy( nHwndList, nList, sizeof(int)*100 );
//	}
//
//	return nCnt;
//}

void CStockAgent::fXRayGetPowerPercent(int nXRayCode, int nXRayFilter, int nPricePos, SHA_POWER* ShaPower)
{
	if(	m_hMod != NULL)
		fXRayGetPowerData(nXRayCode, nXRayFilter, ShaPower);
}


//BOOL CStockAgent::IsLoad()
//{
//	if(	m_hMod == NULL)
//		return FALSE;
//	else
//		return TRUE;
//}
//
////매물대 기본 수량을 설정한다.
//void CStockAgent::SetOfferUint(int nPos, int nUnit)
//{
//	m_nOfferUnit[nPos] = nUnit;
//}
//
//BOOL CStockAgent::IsAnalCode(CString strCode, int nJongType)
//{
//	if(	IsLoad())
//	{
//		int nXRayJCode = ConvertCode(strCode, nJongType);
//		if(	fXRayIsExist(nXRayJCode) == 1)
//			return TRUE;
//	}
//		
//	return FALSE;
//}
//
//BOOL CStockAgent::CreateIO(CString strCode, int nJongType, int nPower, HWND hWnd)
//{
//	if(	IsLoad())
//	{
//		int nXRayJCode = ConvertCode(strCode, nJongType);
//		if(	fXRayCreateIO(nXRayJCode, nPower, hWnd) == 1)
//			return TRUE;
//	}
//		
//	return FALSE;
//}
//
//BOOL CStockAgent::DeleteIO(CString strCode, int nJongType, int nPower, HWND hWnd)
//{
//	if(	IsLoad())
//	{
//		int nXRayJCode = ConvertCode(strCode, nJongType);
//		fXRayDeleteIO(nXRayJCode, nPower, hWnd);
//			
//		return TRUE;
//	}
//		
//	return FALSE;
//}
//
//int	CStockAgent::ConvertCode(CString strCode, int nJongType)
//{
//	char ucType;
//	if(	nJongType == 1)
//		ucType = '1';
//	else if(nJongType == 2)
//		ucType = '2';
//	else if( nJongType == 27)	//ynkim 20060922
//		ucType = '8';
//	else
//		return 0;
//
//	strCode = "A" + strCode;
//	int nCode = fXRayCodeConv(strCode.GetBuffer(strCode.GetLength()), ucType);
//	strCode.ReleaseBuffer();
//	return nCode;
//}
//
////KJI 20060508
//CString	CStockAgent::DeConvertCode(CString strCode, int* pnJongType)
//{
//	if(	strCode.GetLength() < 8)
//	{
//		*pnJongType = -1;
//		return "";
//	}
//
//	*pnJongType = atoi(strCode.Left(1));
//	return strCode.Mid(1, 6);
//}

//BOOL CStockAgent::CheckQuery(CString strQuery, int* pQryType)
//{
//	if(	strQuery == "XRPOWER0")
//	{
//		*pQryType = QRY_POWER;
//		return TRUE;
//	}
//	else if(strQuery == "XRIO0000")
//	{
//		*pQryType = QRY_IO;
//		return TRUE;
//	}
//	else if(strQuery == "XROFFER0")
//	{
//		*pQryType = QRY_OFFER;
//		return TRUE;
//	}
//	else if(strQuery == "XRFOCUS0")	//KJI 20060504
//	{
//		*pQryType = QRY_FOCUS;
//		return TRUE;
//	}
//	else
//		return FALSE;
//}
//
//void CStockAgent::ConvHogaIndex(int nIndex, int* pPowerPos)
//{
//	if(	nIndex < (HOGA_10_RANGE / 2))
//	{
//		*pPowerPos = 9 - nIndex;
//	}
//	else
//	{
//		*pPowerPos = nIndex;
//	}
//}
//
////분석중인 데이터를 해당 자동갱신 데이터로 얻어온다
//BOOL CStockAgent::GetRealData(WORD wRealType, CString strCodeKey, int nJongType, int nPower, int nRange, HWND hWnd, CRealData* pData)
//{
//	WriteDataLog(strCodeKey, nPower);	//KJI 20060629
//
//	//KJI 20060616
//	if(	nRange < 1 || nRange > 10)
//		nRange = 10;
//
//	switch(wRealType)
//	{
//	case PID_XRPOWER:	GetPowerRealData(strCodeKey, nJongType, nPower, nRange, hWnd, pData);	return TRUE;
//	case PID_XRIO:		GetIORealData(strCodeKey, nJongType, nPower, nRange, hWnd, pData);	return TRUE;
//	case PID_XROFFER:	GetOfferRealData(strCodeKey, nJongType, nPower, nRange, pData);	return TRUE;	//KJI 20060627
//	default: break;
//	}
//
//	return FALSE;
//}

////시세,호가,체결등 자동갱신 데이터를 엔진에 설정한다.
//BOOL CStockAgent::SetRealData(WORD wRealType, CString strCodeKey, int nJongType, CRealData* pData)
//{
//	switch(wRealType)
//	{
//	case PID_JONGCHEGYUL:
//	case PID_JONGSISE:		
//	case PID_NEWGETSISE:	//ynkim 20060824	
//		SetSiseRealData(strCodeKey, nJongType, pData);		return FALSE;
//	case PID_JONGHOGA_10:	
//	case PID_ELWHOGA_10:	//ynkim 20060824
//		SetHogaRealData(strCodeKey, nJongType, pData);		return TRUE;	
//	default: break;
//	}
//	return FALSE;
//}
//
////분석중인 데이터를 해당 조회 데이터로 얻어온다.
//BOOL CStockAgent::GetAnalData(CString strQryCode, CString strCode, int nJongType, int nPower, int nRange, HWND hWnd, CDWordArray* pCurPrice, CServerMsg* pMsg)
//{
//	WriteDataLog(strCode, nPower);	//KJI 20060629
//
//	int nQryType = 0;
//	if(	CheckQuery(strQryCode, &nQryType))
//	{
//		//해당 가상 공통 쿼리 부분을 정의한다.
//		pMsg->AddString(strQryCode, QRYCODE_LEN);
//		pMsg->AddString("N0000000", 8);
//		pMsg->AddLong(0);
//
//		int nLenIndex = pMsg->GetIndex();
//		pMsg->AddString(strCode, JONGCODE_LEN);
//		int nStartDataIndex = pMsg->GetIndex();
//
//		pMsg->AddLong(nPower);
//
//		//KJI 20060616
//		if(	nRange < 1 || nRange > 10)
//			nRange = 10;
//
//		switch(nQryType)
//		{
//		case QRY_POWER:	GetPowerData(strCode, nJongType, nPower, nRange, hWnd, pCurPrice, pMsg);	break;
//		case QRY_IO:	GetIOData(strCode, nJongType, nPower, nRange, hWnd, pCurPrice, pMsg);	break;
//		case QRY_OFFER:	GetOfferData(strCode, nJongType, nPower, pMsg);	break;
//		case QRY_FOCUS:	GetFocusData(strQryCode, pMsg);	return TRUE;	//KJI 20060504
//		default: return FALSE;
//		}
//
//		int nEndDataIndex = pMsg->GetIndex();
//		int dwLength = nEndDataIndex - nStartDataIndex;
//		pMsg->SetLong(16, dwLength);
//	}
//
//	return TRUE;
//}
//
////분석데이터 만들고 설정한다.
//BOOL CStockAgent::SetAnalData(CString strQryCode, CString strCode, int nJongType, int nPower, HWND hWnd, CServerMsg* pMsg)
//{
//	int nQryType = 0;
//	SHA_DATA* pData = (SHA_DATA*)pMsg->GetBuffer();
//
//	ByteReverseShaData(pData);
//
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//
//	if(	fXRayCreate(nXRayJCode, pData) == 0)
//		return FALSE;	
//	
//	if(	fXRayCreateIO(nXRayJCode, nPower, hWnd) == 0)
//		return FALSE;
//
//	return TRUE;
//}
//
////분석중인 데이터를 삭제한다.
//void CStockAgent::DelAnalData(CString strCode, int nJongType)
//{
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//
//	fXRayDelete(nXRayJCode);
//}
//
//void CStockAgent::GetPowerData(CString strCode, int nJongType, int nPower, int nRange, HWND hWnd, CDWordArray* pCurPrice, CServerMsg* pMsg)
//{
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//	
//	SHA_POWER PowerData;
//	SHA_PRICE* pPriceData = NULL;
//
//	memset(&PowerData, 0x00, sizeof(SHA_POWER));
//
//	fXRayGetPowerData(nXRayJCode, nPower, &PowerData);
//	int nMaxVol = GetMaxPowerNum(&PowerData);	//KJI 20060530
//
//	int nPowerHoga = 0;
//	int nStdHoga = 0;
//	BYTE ucSellBuy;
//
//	for(int nPos = 0; nPos < HOGA_10_RANGE; nPos++)
//	{
//		//0:매도, 1:매수
//		nPos < 10 ? ucSellBuy = '0' : ucSellBuy = '1';
//
//		ConvHogaIndex(nPos, &nPowerHoga);
//
//		pPriceData = fXRayGetPriceData(nXRayJCode, pCurPrice->GetAt(nPos));
//		if(	pPriceData != NULL)
//		{
//			//각 호가별 세력 아이템 설정
//			pMsg->AddByte(ucSellBuy);
//			pMsg->AddDouble(CalcRatio(PowerData.power[nPowerHoga].power_vol, nMaxVol));	//KJI 20060530
//			
//			int nModifyPos = pMsg->GetIndex();
//			
//			pMsg->AddLong(pPriceData->qty);
//
//			int nAddCnt = 0;
//			for(int nIndex = 0; nIndex < pPriceData->qty; nIndex++)
//			{
//				if(	pPriceData->detail[nIndex].vol >= nPower)
//				{
//					SHA_MICHE_INFO* pMichInfo = (SHA_MICHE_INFO*)pPriceData->detail[nIndex].order_info;
//					if(	pMichInfo != NULL)	//계좌추적중이면(미분석은 아님)
//					{	
//						if(	pMichInfo->trace != NULL)
//						{
//							if(	pMichInfo->trace->gubun == 1)	//추정
//								pMsg->AddByte('1');
//							else if(pMichInfo->trace->gubun == 2)	//포착
//								pMsg->AddByte('2');
//							else
//								pMsg->AddByte('0');
//						}
//						else
//							pMsg->AddByte('0');
//
//						pMsg->AddLong(pPriceData->detail[nIndex].vol);
//					}
//					else
//					{
//						//만약 미분석 잔량이 있다면
//						if(	pPriceData->not_anal_vol >= nPower && (pPriceData->qty - 1) == nIndex)
//						{
//							pMsg->AddByte('3');
//							pMsg->AddLong(pPriceData->not_anal_vol);
//						}
//						else
//						{
//							pMsg->AddByte('0');
//							pMsg->AddLong(pPriceData->detail[nIndex].vol);
//						}
//					}
//
//					nAddCnt++;	//추가한 데이터를 증가한다.
//				}
//			}
//
//			//나머지는 기본값으로 처리 한다.
//			for(nIndex = nAddCnt; nIndex < MAX_DETAIL; nIndex++)
//			{
//				pMsg->AddByte('0');
//				pMsg->AddLong(0);
//			}
//			
//			pMsg->SetLong(nModifyPos, nAddCnt);
//
//			//각 호가별 건수 설정
//			pMsg->AddLong(nAddCnt);
//
//			//세력합
//			pMsg->AddLong(PowerData.power[nPowerHoga].power_vol);
//
//			//KJI 20060424 미분석잔량합
//			if(	pPriceData->not_anal_vol >= nPower)
//				pMsg->AddLong(pPriceData->not_anal_vol);
//			else
//				pMsg->AddLong(0);
//		}
//		else	//에러도 초기값으로 전달한다. (무조건 자동갱신을 걸어야 함)
//		{
//			pMsg->AddByte(ucSellBuy);
//			pMsg->AddDouble(0.0);
//			pMsg->AddLong(0);
//
//			for(int nIndex = 0; nIndex < MAX_DETAIL; nIndex++)
//			{
//				pMsg->AddByte('0');
//				pMsg->AddLong(0);
//			}
//
//			//각 호가별 건수 설정
//			pMsg->AddLong(0);
//
//			//세력합
//			pMsg->AddLong(0);
//
//			//미분석잔량합
//			pMsg->AddLong(0);
//		}
//	}
//
//	//매도세력합
//	pMsg->AddLong(PowerData.medo_total_power.power_vol);
//
//	//매수세력합
//	pMsg->AddLong(PowerData.mesu_total_power.power_vol);
//
//	//차이
//	pMsg->AddLong(PowerData.mesu_total_power.power_vol - PowerData.medo_total_power.power_vol);
//
//	//세력강도 KJI 20060422
//	int nVal = fXRayGetPowerRangeRatio(nXRayJCode, nPower, nRange);	//KJI 20060615
//	pMsg->AddLong(nVal);
//	
//	//입출강도
//	nVal = fXRayGetIOPowerRatio(nXRayJCode, nPower, NULL);
//	pMsg->AddLong(nVal);
//
//	//체결강도
//	nVal = fXRayGetChPowerRatio(nXRayJCode, nPower, NULL);
//	pMsg->AddLong(nVal);
//}
//	
//void CStockAgent::GetIOData(CString strCode, int nJongType, int nPower, int nRange, HWND hWnd, CDWordArray* pCurPrice, CServerMsg* pMsg)
//{
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//
//	SHA_POWER PowerData;
//	SHA_IO_PRICE* pIOPriceData = NULL;
//
//	memset(&PowerData, 0x00, sizeof(SHA_POWER));
//
//	fXRayGetPowerData(nXRayJCode, nPower, &PowerData);
//
//	int nPowerHoga = 0;
//	int nStdHoga = 0;
//	BYTE ucSellBuy;
//
//	for(int nPos = 0; nPos < HOGA_10_RANGE; nPos++)
//	{
//		//0:매도, 1:매수
//		nPos < 10 ? ucSellBuy = '0' : ucSellBuy = '1';
//
//		ConvHogaIndex(nPos, &nPowerHoga);
//
//		pIOPriceData = fXRayGetIOPriceData(nXRayJCode, nPower, NULL, pCurPrice->GetAt(nPos));
//		if(	pIOPriceData != NULL)
//		{
//			//각 호가별 입출 아이템 설정
//			pMsg->AddByte(ucSellBuy);
//			pMsg->AddDouble(0.0);	//입출은 호가별 강도가 없다.
//		//	pMsg->AddDouble(PowerData.power[nPowerHoga].ratio);
//			pMsg->AddLong(pIOPriceData->cnt);
//
//			for(int nIndex = 0; nIndex < XRAY_IO_NUM; nIndex++)
//			{
//				//KJI 20060425
//				if(	pIOPriceData->cnt > nIndex)
//				{
//					//KJI 20060608
//					if(	pIOPriceData->data[nIndex].gubun == 2 || pIOPriceData->data[nIndex].gubun == 3)
//					{
//						//매도 체결
//						pMsg->AddByte('0');
//						pMsg->AddLong(abs(pIOPriceData->data[nIndex].vol));
//					}
//					else if(pIOPriceData->data[nIndex].gubun == 1)
//					{
//						//매도신규,취소
//						pMsg->AddByte('1');
//						pMsg->AddLong(pIOPriceData->data[nIndex].vol);
//					}
//					else if(pIOPriceData->data[nIndex].gubun == -1)
//					{
//						//매수신규,취소
//						pMsg->AddByte('2');
//						pMsg->AddLong(pIOPriceData->data[nIndex].vol);
//					}
//					else if(pIOPriceData->data[nIndex].gubun == -2 || pIOPriceData->data[nIndex].gubun == -3)
//					{
//						//매수 체결
//						pMsg->AddByte('3');
//						pMsg->AddLong(abs(pIOPriceData->data[nIndex].vol));
//					}
//					else	
//					{	
//						pMsg->AddByte('0');		//기본은 신규
//						pMsg->AddLong(pIOPriceData->data[nIndex].vol);
//					}
///*
//					if(	pIOPriceData->data[nIndex].gubun == 0)	//신규
//						pMsg->AddByte('0');
//					else if(pIOPriceData->data[nIndex].gubun == 1)	//취소
//						pMsg->AddByte('1');
//					else if(pIOPriceData->data[nIndex].gubun >= 2)	//체결
//						pMsg->AddByte('2');
//					else	//기본은 그냥 신규
//						pMsg->AddByte('0');
//
//					pMsg->AddLong(pIOPriceData->data[nIndex].vol);
//*/
//				}
//				else
//				{
//					pMsg->AddByte('0');
//					pMsg->AddLong(0);
//				}
//			}
//			
//			//각 호가별 건수 설정
//			pMsg->AddLong(pIOPriceData->cnt);
//
//			//세력합
//			pMsg->AddLong(PowerData.power[nPowerHoga].power_vol);
//
//			//입출은 값이 없다.
//			pMsg->AddLong(0);
//		}
//		else	//에러도 초기값으로 전달한다. (무조건 자동갱신을 걸어야 함)
//		{
//			//각 호가별 입출 아이템 설정
//			pMsg->AddByte(ucSellBuy);
//			pMsg->AddDouble(0.0);
//			pMsg->AddLong(0);
//
//			for(int nIndex = 0; nIndex < XRAY_IO_NUM; nIndex++)
//			{
//				pMsg->AddByte('0');
//				pMsg->AddLong(0);
//			}
//			
//			//각 호가별 건수 설정
//			pMsg->AddLong(0);
//
//			//세력합
//			pMsg->AddLong(0);
//
//			//입출은 값이 없다.
//			pMsg->AddLong(0);
//		}
//	}
//
//	//매도세력합
//	pMsg->AddLong(PowerData.medo_total_power.power_vol);
//
//	//매수세력합
//	pMsg->AddLong(PowerData.mesu_total_power.power_vol);
//
//	//차이
//	pMsg->AddLong(PowerData.mesu_total_power.power_vol - PowerData.medo_total_power.power_vol);
//
//	//세력강도 KJI 20060422
//	int nVal = fXRayGetPowerRangeRatio(nXRayJCode, nPower, nRange);	//KJI 20060615
//	pMsg->AddLong(nVal);
//	
//	//입출강도
//	nVal = fXRayGetIOPowerRatio(nXRayJCode, nPower, NULL);
//	pMsg->AddLong(nVal);
//
//	//체결강도
//	nVal = fXRayGetChPowerRatio(nXRayJCode, nPower, NULL);
//	pMsg->AddLong(nVal);
//}
//
////물량대 값을 얻어온다.
//void CStockAgent::GetOfferData(CString strCode, int nJongType, int nPower, CServerMsg* pMsg)
//{
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//
//	SHA_DISTRIBUTION OfferData[10];
//	
//	//Unit 값은 10개지만 입력은 9개를 준다.
//	int nCnt = fXRGetOfferData(nXRayJCode, m_nOfferUnit, 9, OfferData);
//
//	//최고 수량이 뭔지 얻어 온다.
//	int nMaxNum = GetMaxOfferNum(nCnt, OfferData);
//
//	for(int nPos = 0; nPos < nCnt; nPos++)
//	{		
//		//물량대 매도 데이터
//		pMsg->AddByte('0');
//		pMsg->AddDouble(CalcRatio(OfferData[nPos].medo_vol, nMaxNum));
//		pMsg->AddLong(OfferData[nPos].medo_vol);
//		pMsg->AddLong(OfferData[nPos].medo_qty);
//		
//		//물량대 매수 데이터
//		pMsg->AddByte('1');
//		pMsg->AddDouble(CalcRatio(OfferData[nPos].mesu_vol, nMaxNum));
//		pMsg->AddLong(OfferData[nPos].mesu_vol);
//		pMsg->AddLong(OfferData[nPos].mesu_qty);
//	}
//}
//
////KJI 20060504 (포착관련 없는 조회를 만들어 가짜 데이터를 준다)
//void CStockAgent::GetFocusData(CString strQryCode, CServerMsg* pMsg)
//{
//	pMsg->ResetData();
//	pMsg->AddString(strQryCode, QRYCODE_LEN);
//	pMsg->AddString("N0000000", 8);
//	pMsg->AddLong(4);
//	pMsg->AddString("0000", 4);	//KJI 20060522
//}
//
//double CStockAgent::CalcRatio(int nUnitVol, int nMaxVol)
//{
//	if(	nMaxVol == 0)
//		return 0.0;
//	else
//	{
//		return ((nUnitVol * 100.0) / nMaxVol) * 0.8;	//최대치는 80%로 본다
//	}
//}
//
////KJI 20060420
//int CStockAgent::GetMaxOfferNum(int nCnt, SHA_DISTRIBUTION *pOfferData)
//{
//	int nMaxNum = 0;
//
//	for(int nPos = 0; nPos < nCnt; nPos++)
//	{
//		nMaxNum = max(nMaxNum, (pOfferData + nPos)->medo_vol);	//KJI 20060602
//		nMaxNum = max(nMaxNum, (pOfferData + nPos)->mesu_vol);
//	}
//
//	return nMaxNum;
//}
//
////KJI 20060530
//int	CStockAgent::GetMaxPowerNum(SHA_POWER* pPowerData)
//{
//	int nMaxNum = 0;
//
//	for(int nPos = 0; nPos < 20; nPos++)
//	{
//		nMaxNum = max(nMaxNum, pPowerData->power[nPos].power_vol);	//KJI 20060602
//	}
//
//	return nMaxNum;
//}
//
//void CStockAgent::GetPowerRealData(CString strCode, int nJongType, int nPower, int nRange, HWND hWnd, CRealData* pData)
//{
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//	
//	SHA_POWER PowerData;
//	SHA_PRICE* pPriceData = NULL;
//
//	memset(&PowerData, 0x00, sizeof(SHA_POWER));
//
//	fXRayGetPowerData(nXRayJCode, nPower, &PowerData);
//	int nMaxVol = GetMaxPowerNum(&PowerData);	//KJI 20060530
//
//	int nVal = 0;
//	int nPowerHoga = 0;
//	int nStdHoga = 0;
//	BYTE ucSellBuy;
//
//	CString strKeyData, strTemp;
//
//	//KJI 20060627
//	strKeyData = strCode;
//	strTemp.Format("%d", nPower);
//	strTemp += "    ";
//	strTemp = strTemp.Left(4);
//	strKeyData += strTemp;
//	strTemp.Format("%d", nRange);
//	strKeyData += strTemp;
//
//	pData->arData[0]->SetAt(strKeyData.GetBuffer(strKeyData.GetLength()), 0, strKeyData.GetLength());
//	pData->arData[1]->SetAt(&nPower, 0);
//	strKeyData.ReleaseBuffer();
//
//	int nRealPos = 0;
//
//	for(int nPos = 0; nPos < HOGA_10_RANGE; nPos++)
//	{
//		XRAY_POWER XRayData;
//		memset(&XRayData, 0x00, sizeof(XRAY_POWER));
//
//		//0:매도, 1:매수
//		nPos < 10 ? ucSellBuy = '0' : ucSellBuy = '1';
//
//		ConvHogaIndex(nPos, &nPowerHoga);		
//
//		pPriceData = fXRayGetPriceData(nXRayJCode, m_aCurPrice.GetAt(nPos));
//		if(	pPriceData != NULL)
//		{
//			//각 호가별 세력 아이템 설정
//			XRayData.ucSellBuy = ucSellBuy;
//			XRayData.dRatio = CalcRatio(PowerData.power[nPowerHoga].power_vol, nMaxVol);	//KJI 20060530
//			XRayData.nCount = pPriceData->qty;
//
//			int nAddCnt = 0;
//			for(int nIndex = 0; nIndex < pPriceData->qty; nIndex++)
//			{
//				if(	pPriceData->detail[nIndex].vol >= nPower)
//				{
//					SHA_MICHE_INFO* pMichInfo = (SHA_MICHE_INFO*)pPriceData->detail[nIndex].order_info;
//					if(	pMichInfo != NULL)
//					{
//						//KJI 20060417
//						if(	pMichInfo->trace != NULL)
//						{
//							if(	pMichInfo->trace->gubun == 1)
//								XRayData.nAData[nAddCnt].ucOrderFlag = '1';
//							else if(pMichInfo->trace->gubun == 2)
//								XRayData.nAData[nAddCnt].ucOrderFlag = '2';
//							else
//								XRayData.nAData[nAddCnt].ucOrderFlag = '0';
//						}
//						else
//							XRayData.nAData[nAddCnt].ucOrderFlag = '0';
//
//						XRayData.nAData[nAddCnt].nVol = pPriceData->detail[nIndex].vol;
//					}
//					else
//					{
//						//만약 미분석 잔량이 있다면
//						if(	pPriceData->not_anal_vol >= nPower && (pPriceData->qty - 1) == nIndex)
//						{
//							XRayData.nAData[nAddCnt].ucOrderFlag = '3';
//							XRayData.nAData[nAddCnt].nVol = pPriceData->not_anal_vol;
//						}
//						else
//						{
//							XRayData.nAData[nAddCnt].ucOrderFlag = '0';
//							XRayData.nAData[nAddCnt].nVol = pPriceData->detail[nIndex].vol;
//						}
//					}
//
//					nAddCnt++;	//추가한 데이터를 증가한다.
//				}
//			}
//
//			/* KJI 20060529 (실제 데이터 건수만큼만 처리하므로 필요 없음)
//			for(nIndex = nAddCnt; nIndex < MAX_DETAIL; nIndex++)
//			{
//				XRayData.nAData[nIndex].ucOrderFlag = '0';
//				XRayData.nAData[nIndex].nVol = 0;
//			}
//			*/
//			XRayData.nCount = nAddCnt;
//
//			nRealPos = (nPos * 4) + 2;
//			pData->arData[nRealPos]->SetAt(&XRayData, 0);
//			pData->arData[nRealPos + 1]->SetAt(&nAddCnt, 0);
//			pData->arData[nRealPos + 2]->SetAt(&PowerData.power[nPowerHoga].power_vol, 0);
//
//			//KJI 20060424 미분석잔량합
//			if(	pPriceData->not_anal_vol >= nPower)
//				pData->arData[nRealPos + 3]->SetAt(&pPriceData->not_anal_vol, 0);
//			else
//				pData->arData[nRealPos + 3]->SetAt(&nVal, 0);
//			nRealPos = nRealPos + 3;
//		}
//		else
//		{	//없으면 기본값으로 셋팅한다.
//			XRayData.ucSellBuy = ucSellBuy;
//			XRayData.dRatio = 0.0;
//			XRayData.nCount = 0;
//
//			for(int nIndex = 0; nIndex < MAX_DETAIL; nIndex++)
//			{
//				XRayData.nAData[nIndex].ucOrderFlag = '0';
//				XRayData.nAData[nIndex].nVol = 0;
//			}
//
//			nRealPos = (nPos * 4) + 2;
//			pData->arData[nRealPos]->SetAt(&XRayData, 0);
//			pData->arData[nRealPos + 1]->SetAt(&nVal, 0);
//			pData->arData[nRealPos + 2]->SetAt(&nVal, 0);
//			pData->arData[nRealPos + 3]->SetAt(&nVal, 0);
//			nRealPos = nRealPos + 3;
//		}
//	}
//
//	pData->arData[nRealPos + 1]->SetAt(&PowerData.medo_total_power.power_vol, 0);
//	pData->arData[nRealPos + 2]->SetAt(&PowerData.mesu_total_power.power_vol, 0);
//
//	int nVal1 = PowerData.mesu_total_power.power_vol - PowerData.medo_total_power.power_vol;
//	pData->arData[nRealPos + 3]->SetAt(&nVal1, 0);
//
//	//KJI 20060422 세력강도
//	nVal = fXRayGetPowerRangeRatio(nXRayJCode, nPower, nRange);	//KJI 20060615
//	pData->arData[nRealPos + 4]->SetAt(&nVal, 0);
//
//	//입출강도
//	nVal = fXRayGetIOPowerRatio(nXRayJCode, nPower, NULL);
//	pData->arData[nRealPos + 5]->SetAt(&nVal, 0);
//
//	//체결강도
//	nVal = fXRayGetChPowerRatio(nXRayJCode, nPower, NULL);
//	pData->arData[nRealPos + 6]->SetAt(&nVal, 0);
//}
//
//void CStockAgent::GetIORealData(CString strCode, int nJongType, int nPower, int nRange, HWND hWnd, CRealData* pData)
//{
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//
//	SHA_POWER PowerData;
//	SHA_IO_PRICE* pIOPriceData = NULL;
//
//	memset(&PowerData, 0x00, sizeof(SHA_POWER));
//
//	fXRayGetPowerData(nXRayJCode, nPower, &PowerData);
//
//	int nPowerHoga = 0;
//	int nStdHoga = 0;
//	BYTE ucSellBuy;
//
//	CString strKeyData, strTemp;
//	
//	//KJI 20060627
//	strKeyData = strCode;
//	strTemp.Format("%d", nPower);
//	strTemp += "    ";
//	strTemp = strTemp.Left(4);
//	strKeyData += strTemp;
//	strTemp.Format("%d", nRange);
//	strKeyData += strTemp;
//
//	pData->arData[0]->SetAt(strKeyData.GetBuffer(strKeyData.GetLength()), 0, strKeyData.GetLength());
//	pData->arData[1]->SetAt(&nPower, 0);
//	strKeyData.ReleaseBuffer();
//
//	int nVal = 0;
//	int nRealPos = 0;
//	for(int nPos = 0; nPos < HOGA_10_RANGE; nPos++)
//	{
//		XRAY_IO XRayData;
//		memset(&XRayData, 0x00, sizeof(XRAY_IO));
//
//		//0:매도, 1:매수
//		nPos < 10 ? ucSellBuy = '0' : ucSellBuy = '1';
//
//		ConvHogaIndex(nPos, &nPowerHoga);
//
//		pIOPriceData = fXRayGetIOPriceData(nXRayJCode, nPower, NULL, m_aCurPrice.GetAt(nPos));
//		if(	pIOPriceData != NULL)
//		{
//			//각 호가별 입출 아이템 설정
//			XRayData.ucSellBuy = ucSellBuy;
//			XRayData.dRatio = 0.0;	//입출일때는 강도가 없다.
//		//	XRayData.dRatio = PowerData.power[nPowerHoga].ratio;
//			XRayData.nCount = pIOPriceData->cnt;
//
//			//KJI 20060529 (실제 데이터 만큼만 처리)
//			for(int nIndex = 0; nIndex < pIOPriceData->cnt; nIndex++)
//			{
//				//KJI 20060425
//				if(	pIOPriceData->cnt > nIndex)
//				{
//					if(	pIOPriceData->data[nIndex].gubun == 2 || pIOPriceData->data[nIndex].gubun == 3)
//					{
//						//매도 체결
//						XRayData.nAData[nIndex].ucVolFlag = '0';
//						XRayData.nAData[nIndex].nVol = abs(pIOPriceData->data[nIndex].vol);
//					}
//					else if(pIOPriceData->data[nIndex].gubun == 1)
//					{
//						//매도신규,취소
//						XRayData.nAData[nIndex].ucVolFlag = '1';
//						XRayData.nAData[nIndex].nVol = pIOPriceData->data[nIndex].vol;
//					}
//					else if(pIOPriceData->data[nIndex].gubun == -1)
//					{
//						//매수신규,취소
//						XRayData.nAData[nIndex].ucVolFlag = '2';
//						XRayData.nAData[nIndex].nVol = pIOPriceData->data[nIndex].vol;
//					}
//					else if(pIOPriceData->data[nIndex].gubun == -2 || pIOPriceData->data[nIndex].gubun == -3)
//					{
//						//매수 체결
//						XRayData.nAData[nIndex].ucVolFlag = '3';
//						XRayData.nAData[nIndex].nVol = abs(pIOPriceData->data[nIndex].vol);
//					}
//					else	
//					{	
//						XRayData.nAData[nIndex].ucVolFlag = '0';
//						XRayData.nAData[nIndex].nVol = pIOPriceData->data[nIndex].vol;
//					}	
//				/*
//					if(	pIOPriceData->data[nIndex].gubun == 0)
//						XRayData.nAData[nIndex].ucVolFlag = '0';
//					else if(pIOPriceData->data[nIndex].gubun == 1)
//						XRayData.nAData[nIndex].ucVolFlag = '1';
//					else if(pIOPriceData->data[nIndex].gubun >= 2)
//						XRayData.nAData[nIndex].ucVolFlag = '2';
//					else	//기본은 그냥 신규
//						XRayData.nAData[nIndex].ucVolFlag = '0';
//
//					XRayData.nAData[nIndex].nVol = pIOPriceData->data[nIndex].vol;
//				*/
//				}
//				else
//				{
//					XRayData.nAData[nIndex].ucVolFlag = '0';
//					XRayData.nAData[nIndex].nVol = 0;
//				}
//			}
//
//			nRealPos = (nPos * 4) + 2;
//			pData->arData[nRealPos]->SetAt(&XRayData, 0);
//			pData->arData[nRealPos + 1]->SetAt(&pIOPriceData->cnt, 0);
//			pData->arData[nRealPos + 2]->SetAt(&PowerData.power[nPowerHoga].power_vol, 0);
//			pData->arData[nRealPos + 3]->SetAt(&nVal, 0);
//			nRealPos = nRealPos + 3;
//		}
//		else
//		{
//			XRayData.ucSellBuy = ucSellBuy;
//			XRayData.dRatio = 0.0;
//			XRayData.nCount = 0;
//
//			for(int nIndex = 0; nIndex < XRAY_IO_NUM; nIndex++)
//			{
//				XRayData.nAData[nIndex].ucVolFlag = '0';
//				XRayData.nAData[nIndex].nVol = 0;
//			}
//
//			nRealPos = (nPos * 4) + 2;
//			pData->arData[nRealPos]->SetAt(&XRayData, 0);
//			pData->arData[nRealPos + 1]->SetAt(&nVal, 0);
//			pData->arData[nRealPos + 2]->SetAt(&nVal, 0);
//			pData->arData[nRealPos + 3]->SetAt(&nVal, 0);
//			nRealPos = nRealPos + 3;
//		}
//
//		//나중에 지워야 함
////		LogIOData(m_aCurPrice.GetAt(nPos), &XRayData);
//	}
//
//	pData->arData[nRealPos + 1]->SetAt(&PowerData.medo_total_power.power_vol, 0);
//	pData->arData[nRealPos + 2]->SetAt(&PowerData.mesu_total_power.power_vol, 0);
//
//	nVal = PowerData.mesu_total_power.power_vol - PowerData.medo_total_power.power_vol;
//	pData->arData[nRealPos + 3]->SetAt(&nVal, 0);
//
//	//KJI 20060422 세력강도
//	nVal = fXRayGetPowerRangeRatio(nXRayJCode, nPower, nRange);	//KJI 20060615
//	pData->arData[nRealPos + 4]->SetAt(&nVal, 0);
//
//	//입출강도
//	nVal = fXRayGetIOPowerRatio(nXRayJCode, nPower, NULL);
//	pData->arData[nRealPos + 5]->SetAt(&nVal, 0);
//
//	//체결강도
//	nVal = fXRayGetChPowerRatio(nXRayJCode, nPower, NULL);
//	pData->arData[nRealPos + 6]->SetAt(&nVal, 0);
//}
//	
//void CStockAgent::GetOfferRealData(CString strCode, int nJongType, int nPower, int nRange, CRealData* pData)
//{
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//
//	SHA_DISTRIBUTION OfferData[10];
//	
//	//Unit 값은 10개지만 입력은 9개를 준다.
//	int nCnt = fXRGetOfferData(nXRayJCode, m_nOfferUnit, 9, OfferData);
//
//	//최고 수량이 뭔지 얻어 온다.
//	int nMaxNum = GetMaxOfferNum(nCnt, OfferData);
//
//	CString strKeyData, strTemp;
//
//	//KJI 20060627
//	strKeyData = strCode;
//	strTemp.Format("%d", nPower);
//	strTemp += "    ";
//	strTemp = strTemp.Left(4);
//	strKeyData += strTemp;
//	strTemp.Format("%d", nRange);
//	strKeyData += strTemp;
//
//	pData->arData[0]->SetAt(strKeyData.GetBuffer(strKeyData.GetLength()), 0, strKeyData.GetLength());
//	pData->arData[1]->SetAt(&nPower, 0);
//	strKeyData.ReleaseBuffer();
//
//	for(int nPos = 0; nPos < nCnt; nPos++)
//	{		
//		//물량대 매도 데이터
//		XRAY_OFFER XRayData;
//		XRayData.ucSellBuy = '0';
//		XRayData.dRatio = CalcRatio(OfferData[nPos].medo_vol, nMaxNum);
//		XRayData.nVol = OfferData[nPos].medo_vol;
//		XRayData.nCount = OfferData[nPos].medo_qty;
//		pData->arData[(nPos * 2) + 2]->SetAt(&XRayData, 0);
//
//		XRayData.ucSellBuy = '1';
//		XRayData.dRatio = CalcRatio(OfferData[nPos].mesu_vol, nMaxNum);
//		XRayData.nVol = OfferData[nPos].mesu_vol;
//		XRayData.nCount = OfferData[nPos].mesu_qty;
//		pData->arData[(nPos * 2) + 3]->SetAt(&XRayData, 0);
//	}
//}
//
//void CStockAgent::SetSiseRealData(CString strCode, int nJongType, CRealData* pData)
//{
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//
//	SHA_SISE_PACKET stSiseData;
//	memset(&stSiseData, 0x00, sizeof(SHA_SISE_PACKET));
//
//	long lTemp;
//
//	stSiseData.code = nXRayJCode;
//
//	pData->GetDataLong(2, lTemp);
//	stSiseData.time = lTemp / 100;
//
//	pData->GetDataLong(3, lTemp);
//	stSiseData.cur_price = lTemp;
//
//	pData->GetDataLong(10, lTemp);
//	stSiseData.volume = lTemp;
//	
//	stSiseData.jang = 3;	//? 확인을 해 봐야 함
//
//	fXRaySetSiseData(&stSiseData);
//}
//
//void CStockAgent::SetHogaRealData(CString strCode, int nJongType, CRealData* pData)
//{
//	m_aCurPrice.RemoveAll();
//
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//
//	SHA_HOGA_PACKET stHogaData;
//	memset(&stHogaData, 0x00, sizeof(SHA_HOGA_PACKET));
//
//	long lTemp;
//
//	stHogaData.code = nXRayJCode;
//	
//	pData->GetDataLong(31, lTemp);
//	stHogaData.time = lTemp / 100;
//
//	stHogaData.seq_no = lTemp / 100;
//	stHogaData.jang = 3;			//? 확인을 해 봐야 함
//
//	pData->GetDataLong(10, lTemp);
//	stHogaData.volume = lTemp;
//
//	//매도1호가
//	pData->GetDataLong(14, lTemp);
//	stHogaData.hoga[0].sell_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(16, lTemp);
//	stHogaData.hoga[0].sell_vol = lTemp;
//
//	//매도2호가
//	pData->GetDataLong(33, lTemp);
//	stHogaData.hoga[1].sell_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(43, lTemp);
//	stHogaData.hoga[1].sell_vol = lTemp;
//
//	//매도3호가
//	pData->GetDataLong(34, lTemp);
//	stHogaData.hoga[2].sell_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(44, lTemp);
//	stHogaData.hoga[2].sell_vol = lTemp;
//
//	//매도4호가
//	pData->GetDataLong(35, lTemp);
//	stHogaData.hoga[3].sell_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(45, lTemp);
//	stHogaData.hoga[3].sell_vol = lTemp;
//
//	//매도5호가
//	pData->GetDataLong(36, lTemp);
//	stHogaData.hoga[4].sell_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(46, lTemp);
//	stHogaData.hoga[4].sell_vol = lTemp;
//
//	//매도6호가
//	pData->GetDataLong(206, lTemp);
//	stHogaData.hoga[5].sell_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(216, lTemp);
//	stHogaData.hoga[5].sell_vol = lTemp;
//
//	//매도7호가
//	pData->GetDataLong(207, lTemp);
//	stHogaData.hoga[6].sell_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(217, lTemp);
//	stHogaData.hoga[6].sell_vol = lTemp;
//
//	//매도8호가
//	pData->GetDataLong(208, lTemp);
//	stHogaData.hoga[7].sell_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(218, lTemp);
//	stHogaData.hoga[7].sell_vol = lTemp;
//
//	//매도9호가
//	pData->GetDataLong(209, lTemp);
//	stHogaData.hoga[8].sell_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(219, lTemp);
//	stHogaData.hoga[8].sell_vol = lTemp;
//
//	//매도10호가
//	pData->GetDataLong(210, lTemp);
//	stHogaData.hoga[9].sell_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(220, lTemp);
//	stHogaData.hoga[9].sell_vol = lTemp;
//
//	//매수1호가
//	pData->GetDataLong(15, lTemp);
//	stHogaData.hoga[0].buy_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(17, lTemp);
//	stHogaData.hoga[0].buy_vol = lTemp;
//
//	//매수2호가
//	pData->GetDataLong(38, lTemp);
//	stHogaData.hoga[1].buy_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(48, lTemp);
//	stHogaData.hoga[1].buy_vol = lTemp;
//
//	//매수3호가
//	pData->GetDataLong(39, lTemp);
//	stHogaData.hoga[2].buy_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(49, lTemp);
//	stHogaData.hoga[2].buy_vol = lTemp;
//
//	//매수4호가
//	pData->GetDataLong(40, lTemp);
//	stHogaData.hoga[3].buy_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(50, lTemp);
//	stHogaData.hoga[3].buy_vol = lTemp;
//
//	//매수5호가
//	pData->GetDataLong(41, lTemp);
//	stHogaData.hoga[4].buy_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(51, lTemp);
//	stHogaData.hoga[4].buy_vol = lTemp;
//
//	//매수6호가
//	pData->GetDataLong(211, lTemp);
//	stHogaData.hoga[5].buy_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(221, lTemp);
//	stHogaData.hoga[5].buy_vol = lTemp;
//
//	//매수7호가
//	pData->GetDataLong(212, lTemp);
//	stHogaData.hoga[6].buy_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(222, lTemp);
//	stHogaData.hoga[6].buy_vol = lTemp;
//
//	//매수8호가
//	pData->GetDataLong(213, lTemp);
//	stHogaData.hoga[7].buy_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(223, lTemp);
//	stHogaData.hoga[7].buy_vol = lTemp;
//
//	//매수9호가
//	pData->GetDataLong(214, lTemp);
//	stHogaData.hoga[8].buy_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(224, lTemp);
//	stHogaData.hoga[8].buy_vol = lTemp;
//
//	//매수10호가
//	pData->GetDataLong(215, lTemp);
//	stHogaData.hoga[9].buy_price = lTemp;
//	m_aCurPrice.Add(lTemp);
//	pData->GetDataLong(225, lTemp);
//	stHogaData.hoga[9].buy_vol = lTemp;
//
//	fXRaySetHogaData(&stHogaData);
//}

//KJI 20060517
//BOOL CStockAgent::GetChekyulXRayData(CString strAcc, CString strCode, CString strOrderNo, CString strOrderOrgNo, CString strJState, CRealData* pData)
//{
//	int nVal = 0;
//	LPTSTR szAcc = strAcc.GetBuffer(strAcc.GetLength());
//	LPTSTR szOrderNo = strOrderNo.GetBuffer(strOrderNo.GetLength());
//
//	//KJI 20060517
//	LPTSTR szOrderOrgNo = strOrderOrgNo.GetBuffer(strOrderOrgNo.GetLength());
//	LPTSTR szCode = strCode.GetBuffer(strCode.GetLength());
//	LPTSTR szJState = strJState.GetBuffer(strJState.GetLength());
//
//	SHA_REMAIN_ORDER_VOL stOrderVol;
//	memset(&stOrderVol, 0x00, sizeof(SHA_REMAIN_ORDER_VOL));
//
//	strOrderNo.TrimLeft();	strOrderNo.TrimRight();
//	nVal = atoi(strOrderNo);
////	if(	fXRayOrderNoToOrderVol(szAcc, atoi(strOrderNo), &stOrderVol) == 0)
////		return FALSE;
//
//	fXRayOrderNoToOrderVol(szAcc, atoi(strOrderNo), &stOrderVol);
//
//	//KJI 20060517
//	pData->arData[0]->SetAt(szAcc, 0, 11);
//	pData->arData[1]->SetAt(szCode, 0, 6);
//	pData->arData[2]->SetAt(szOrderNo, 0, 10);
//	pData->arData[3]->SetAt(szOrderOrgNo, 0, 10);
//	pData->arData[4]->SetAt(szJState, 0, 1);
//	
//	strAcc.ReleaseBuffer();
//	strOrderNo.ReleaseBuffer();
//
//	//KJI 20060517
//	strOrderOrgNo.ReleaseBuffer();
//	strCode.ReleaseBuffer();
//	strJState.ReleaseBuffer();
//
//	pData->arData[5]->SetAt(&stOrderVol.vol, 0);
//	pData->arData[6]->SetAt(&stOrderVol.qty, 0);
//	pData->arData[7]->SetAt(&stOrderVol.price, 0);
//
//	SHA_PRICE* pPriceData = fXRayPriceByOrderNo(szAcc, atoi(strOrderNo));
//
//	XRAY_POWER XRayData;
//	memset(&XRayData, 0x00, sizeof(XRAY_POWER));
//	if(	pPriceData != NULL)
//	{
//		if(	pPriceData->gubun == 1)
//			XRayData.ucSellBuy = '0';
//		else
//			XRayData.ucSellBuy = '1';
//
//		XRayData.dRatio = 0.0;		//여기선 강도가 필요 없다.
//		XRayData.nCount = pPriceData->qty;
//
//		int nAddCnt = 0;
//		for(int nIndex = 0; nIndex < pPriceData->qty; nIndex++)
//		{
//			SHA_MICHE_INFO* pMichInfo = (SHA_MICHE_INFO*)pPriceData->detail[nIndex].order_info;
//			if(	pMichInfo != NULL)
//			{
//				//KJI 20060417
//				if(	pMichInfo->trace != NULL)
//				{
//					if(	pMichInfo->trace->gubun == 1)
//						XRayData.nAData[nIndex].ucOrderFlag = '1';
//					else if(pMichInfo->trace->gubun == 2)
//						XRayData.nAData[nIndex].ucOrderFlag = '2';
//					else
//						XRayData.nAData[nIndex].ucOrderFlag = '0';
//				}
//				else
//					XRayData.nAData[nIndex].ucOrderFlag = '0';
//			}
//			else
//				XRayData.nAData[nIndex].ucOrderFlag = '0';
//				
//			XRayData.nAData[nIndex].nVol = pPriceData->detail[nIndex].vol;
//			nAddCnt++;	//추가한 데이터를 증가한다.
//		}
//
//		//만약 미분석 잔량이 있다면
//		if(	pPriceData->not_anal_vol > 0)
//			XRayData.nAData[pPriceData->qty - 1].ucOrderFlag = '3'; //미분석 처리
//
//		//나머지는 기본값으로 처리 한다.
//		for(nIndex = nAddCnt; nIndex < MAX_DETAIL; nIndex++)
//		{
//			XRayData.nAData[nIndex].ucOrderFlag = '0';
//			XRayData.nAData[nIndex].nVol = 0;
//		}
//	}
//	else
//	{
//		XRayData.ucSellBuy = '1';
//		XRayData.dRatio = 0.0;
//		XRayData.nCount = 0;
//
//		for(int nIndex = 0; nIndex < MAX_DETAIL; nIndex++)
//		{
//			XRayData.nAData[nIndex].ucOrderFlag = '0';
//			XRayData.nAData[nIndex].nVol = 0;
//		}
//	}
//
//	pData->arData[8]->SetAt(&XRayData, 0);
//
//	return TRUE;
//}
//
////KJI 20060517
//BOOL CStockAgent::SetCheyulRealData(CString& strAcc, CString& strCode, CString& strOrderNo, CString& strOrderOrgNo, CString& strJState, int nJongType, CRealData* pData)
//{
//	CString strVal, strBuySell;
//	long lVal = 0;
//
//	pData->GetDataStr(170, strVal);
//	if(	strVal != "1" && strVal != "3")	//장내/코스닥만 처리한다
//		return FALSE;
//
//	pData->GetDataStr(1, strVal);
//	strVal.TrimRight();
//
//	strCode = strVal;	//KJI 20060517
//
//	//KJI 20060523
//	int nXRayJCode = ConvertCode(strVal, nJongType);
//
//	SHA_REAL_INFO stInfo;
//	memset(&stInfo, 0x00, sizeof(SHA_REAL_INFO));
//
//	stInfo.jong_code = nXRayJCode;
//	
//	pData->GetDataStr(173, strVal);
//	strncpy(stInfo.account, strVal.GetBuffer(strVal.GetLength()), 17);
//	strVal.ReleaseBuffer();
//
//	strAcc = strVal;	//계좌 정보를 넘김
//	strAcc.TrimRight();
//
//	pData->GetDataStr(171, strVal);
//	pData->GetDataStr(179, strBuySell);
//	if(	strVal == "5")
//	{
//		strncpy(stInfo.gubun, "접수", 5);
//		if(	strBuySell == "매도")
//			stInfo.order_gubun = 2;
//		else if(strBuySell == "매수")
//			stInfo.order_gubun = 1;
//	}
//	else if(strVal == "1")	//매도,매수
//	{
//		strncpy(stInfo.gubun, "체결", 5);
//		if(	strBuySell == "매도")
//			stInfo.order_gubun = 2;
//		else if(strBuySell == "매수")
//			stInfo.order_gubun = 1;
//	}
//	else if(strVal == "2")	//정정
//	{
//		strncpy(stInfo.gubun, "확인", 5);
//		stInfo.order_gubun = 3;
//	}
//	else if(strVal == "3")	//취소
//	{
//		strncpy(stInfo.gubun, "확인", 5);	//KJI 20060517
//		stInfo.order_gubun = 4;
//	}
//
//	//KJI 20060517
//	strJState = strVal;
//
//	pData->GetDataStr(176, strVal);
//	stInfo.org_ord_no = atoi(strVal);
//
//	strOrderOrgNo = strVal;	//KJI 20060517
//	strOrderOrgNo.TrimRight();
//
//	pData->GetDataStr(78, strVal);
//	stInfo.ord_no = atoi(strVal);
//
//	strOrderNo = strVal;	//주문번호를 넘김
//	strOrderNo.TrimRight();
//	
//	pData->GetDataLong(181, lVal);
//	stInfo.order_price = lVal;
//	pData->GetDataLong(180, lVal);
//	stInfo.order_qty = lVal;
//	
//	pData->GetDataLong(183, lVal);
//	stInfo.che_price = lVal;
//	pData->GetDataLong(182, lVal);
//	stInfo.che_qty = lVal;
//	pData->GetDataLong(186, lVal);
//	stInfo.che_remn_qty = lVal;
//
//	pData->GetDataLong(180, lVal);
//	stInfo.jj_qty = lVal;
//
//	//KJI 20060516
//	pData->GetDataStr(249, strVal);
//	strVal.Replace(":", "");
//	stInfo.rcv_time = atoi(strVal) / 100;
//
//	fXRaySetReal(&stInfo);
//
//	WriteDataLog(strCode, 1);	//KJI 20060629
//
//	return TRUE;
//}
//
////KJI 20060405
//BOOL CStockAgent::SetAccountMicheInfo(BYTE* pBuf, long lSize, CString& strAcc, CString& strPwd, CString& strNextKey)
//{
//	CString strCode, strOrderNo, strTime;
//	CString strOrderOrgNo;	//KJI 20060517
//	int nCount = 0;
//
//	SHA_MICHE_INFO* pInfo = NULL;
//	SHA_MICHE_INFO* pTemp = NULL;
//
//	CServerMsg	Msg;
//	Msg.SetBuffer(pBuf, lSize);
//
//	CString strTrCode = Msg.GetString(QRYCODE_LEN);
//	Msg.GetByte();							
//	BYTE ucPrevNext = Msg.GetByte();		
//	BYTE ucErrCode = Msg.GetByte();			
//	CString strMsgCode = Msg.GetString(MSGCODE_LEN);
//	DWORD dwLength = Msg.GetLong();
//
//	if((strTrCode == "CH479Q01" || strTrCode == "CN070Q01") && ucErrCode == '2')	//KJI 20060414 (나중에 TR코드 확인할것)
//	{
//		Msg.Skip(80);
//	
//		//KJI 20060612 (조회 결과를 가지고 처리)
//		strAcc = Msg.GetString(11);
//		strPwd = Msg.GetString(8);
//
//		strNextKey = Msg.GetString(50);
//		Msg.Skip(20);
//
//		nCount = atoi(Msg.GetString(4));
//		if(	nCount > 0)
//		{
//			pInfo = new SHA_MICHE_INFO[nCount];
//			memset(pInfo, 0x00, sizeof(SHA_MICHE_INFO));
//
//			for(int nPos = 0; nPos < nCount; nPos++)
//			{
//				strncpy((pInfo + nPos)->account, strAcc.GetBuffer(11), 17);
//				strAcc.ReleaseBuffer();
//
//				strOrderNo = Msg.GetString(5);
//				m_aOrderNo.Add(strOrderNo);		//KJI 20060422
//
//				//KJI 20060517
//				strOrderOrgNo = Msg.GetString(5);
//				m_aOrderOrgNo.Add(strOrderOrgNo);
//
//				(pInfo + nPos)->ord_no = atoi(strOrderNo);
//				(pInfo + nPos)->org_ord_no = atoi(strOrderOrgNo);
//
//				strCode = Msg.GetString(12);
//				strCode = strCode.Mid(1);	//KJI 20060512
//				strCode.TrimRight();
//
//				m_aCode.Add(strCode);	//KJI 20060517
//
//				//KJI 20060523
//				CString strName;
//				int nJongType = ::SendMessage(m_hDataMgr, WMU_JONG_PART, (WPARAM)(LPCTSTR)strCode, (LPARAM)&strName);
//				
//				(pInfo + nPos)->jong_code = ConvertCode(strCode, nJongType);
//				
//				Msg.Skip(20);
//				Msg.Skip(20);
//				CString strBuySell = Msg.GetString(4);
//				
//				if(	strBuySell == "매도")
//					(pInfo + nPos)->order_gubun = 2;
//				else if(strBuySell == "매수")
//					(pInfo + nPos)->order_gubun = 1;
//
//				(pInfo + nPos)->order_qty = atoi(Msg.GetString(10));
//				(pInfo + nPos)->order_price = atoi(Msg.GetString(10));
//				(pInfo + nPos)->che_remn_qty = atoi(Msg.GetString(10));
//
//				Msg.Skip(23);
//				
//				//KJI 20060512
//				strTime = Msg.GetString(8);
//				strTime.Replace(":", "");
//				(pInfo + nPos)->rcv_time = atoi(strTime) / 100;
//				(pInfo + nPos)->seq_no = (pInfo + nPos)->rcv_time;
//			}
//		}
//		else
//		{
//			m_nMicheCnt = 0;
//			return FALSE;
//		}
//
//		pTemp = new SHA_MICHE_INFO[m_nMicheCnt + nCount];
//		memset(pTemp, 0x00, sizeof(SHA_MICHE_INFO) * (m_nMicheCnt + nCount));
//
//		if(	m_nMicheCnt > 0)
//		{
//			memcpy(pTemp, m_pInfo, sizeof(SHA_MICHE_INFO) * m_nMicheCnt);
//			delete []m_pInfo;
//			m_pInfo = NULL;
//		}
//
//		//KJI 20060518
//		memcpy(&pTemp[m_nMicheCnt], pInfo, sizeof(SHA_MICHE_INFO) * nCount);
//		delete []pInfo;
//
//		m_pInfo = pTemp;
//		m_nMicheCnt += nCount;
//		m_nAccInfoCnt = m_nMicheCnt;
//
//		if(	ucPrevNext == '2' || ucPrevNext == '3')
//			return TRUE;
//		else
//			strNextKey = "";
//
//		fXRaySetMiche(strAcc.GetBuffer(strAcc.GetLength()), m_nAccInfoCnt, m_pInfo);
//		strAcc.ReleaseBuffer();
//		
//		delete []m_pInfo;
//		m_pInfo = NULL;
//		m_nMicheCnt = 0;
//	}
//
//	return FALSE;
//}
//
////KJI 20060419
//CString	CStockAgent::GetPriceAccInfo(CString strCode, int nJongType, long lPrice)
//{
//	CString strInfo, strAcc, strHead, strMiddle, strTail;
//
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//
//	SHA_PRICE* pPriceData = fXRayGetPriceData(nXRayJCode, lPrice);
//	if(	pPriceData != NULL)
//	{
//		for(int nIndex = 0; nIndex < MAX_DETAIL; nIndex++)
//		{
//			SHA_MICHE_INFO* pMichInfo = (SHA_MICHE_INFO*)pPriceData->detail[nIndex].order_info;
//			if(	pMichInfo != NULL)
//			{
//				strAcc = pMichInfo->account;
//				strAcc.TrimRight();
//				if(	strAcc.GetLength() > 10)
//				{
//					strHead = strAcc.Left(3);
//					strMiddle = strAcc.Mid(3, 2);
//					strTail = strAcc.Right(6);
//					strAcc = strHead + "-" + strMiddle + "-" + strTail + " ";
//
//					strInfo += strAcc;
//				}
//				else
//					strAcc = "";
//			}
//		}
//	}
//
//	return strInfo;
//}
//
////KJI 20060420
//int	CStockAgent::GetMaxFilter(CString strCode, int nJongType, int nShowNum)
//{
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//	return fXRayGetMaxFilter(nXRayJCode, nShowNum);
//}
//
////KJI 20060422
//void CStockAgent::ClearMicheOrderNo()
//{
//	m_aOrderNo.RemoveAll();
//	m_aOrderOrgNo.RemoveAll();
//	m_aCode.RemoveAll();
//}
//	
////KJI 20060422
//BOOL CStockAgent::GetMicheXRayData(CString strAcc, CServerMsg* pMsg)
//{
//	CString strCount;
//
//	pMsg->AddString("XRMICHE0", QRYCODE_LEN);
//	pMsg->AddString("N0000000", 8);
//	pMsg->AddLong(0);
//
//	int nLenIndex = pMsg->GetIndex();
//	int nCount = m_aOrderNo.GetSize();
//	
//	//해당 건수를 조정해야 함
//	pMsg->AddString(strCount, 4);
//	int nStartDataIndex = pMsg->GetIndex();
//	
//	int nInsert = 0;
//	for(int nPos = 0; nPos < nCount; nPos++)
//	{
//		//KJI 20060517
//		if(	GetMicheData(strAcc, m_aCode.GetAt(nPos), m_aOrderOrgNo.GetAt(nPos), m_aOrderNo.GetAt(nPos), pMsg))
//			nInsert++;
//
//		WriteDataLog(m_aCode.GetAt(nPos), 1);	//KJI 20060629
//	}
//
//	int nEndDataIndex = pMsg->GetIndex();
//	int dwLength = nEndDataIndex - nStartDataIndex;
//	pMsg->SetLong(16, dwLength);
//
//	//KJI 20060515(미체결중 해당종목에 분석데이터가 없는 경우는 처리가 안되므로)
//	strCount.Format("%04d", nInsert);
//	pMsg->SetString(20, strCount);
//
//	return TRUE;
//}
//
////KJI 20060422 (조회시 처리됨)
//BOOL CStockAgent::GetMicheData(CString strAcc, CString strCode, CString strOrderOrgNo, CString strOrderNo, CServerMsg* pMsg)
//{
//	int nVal = 0;
//	LPTSTR szAcc = strAcc.GetBuffer(strAcc.GetLength());
//	LPTSTR szOrderNo = strOrderNo.GetBuffer(strOrderNo.GetLength());
//
//	SHA_REMAIN_ORDER_VOL stOrderVol;
//	memset(&stOrderVol, 0x00, sizeof(SHA_REMAIN_ORDER_VOL));
//
//	strOrderNo.TrimLeft();	strOrderNo.TrimRight();
//	if(	fXRayOrderNoToOrderVol(szAcc, atoi(strOrderNo), &stOrderVol) == 0)
//		return FALSE;
//
//	//KJI 20060517
//	pMsg->AddString(strCode, 6);
//	pMsg->AddString(strOrderNo, 10);
//	pMsg->AddString(strOrderOrgNo, 10);
//	pMsg->AddString("0", 1);			//주문 상태값은 조회시에는 모름
//	pMsg->AddLong(stOrderVol.vol);
//	pMsg->AddLong(stOrderVol.qty);
//	pMsg->AddLong(stOrderVol.price);
//
//	SHA_PRICE* pPriceData = fXRayPriceByOrderNo(szAcc, atoi(strOrderNo));
//
//	strAcc.ReleaseBuffer();
//	strOrderNo.ReleaseBuffer();
//
//	XRAY_POWER XRayData;
//	memset(&XRayData, 0x00, sizeof(XRAY_POWER));
//	if(	pPriceData != NULL)
//	{
//		if(	pPriceData->gubun == 1)
//			pMsg->AddByte('0');
//		else
//			pMsg->AddByte('1');
//		
//		pMsg->AddDouble(0.0);
//
//		int nModifyPos = pMsg->GetIndex();
//
//		pMsg->AddLong(pPriceData->qty);
//
//		int nAddCnt = 0;
//
//		//무조건 수량이 있으면 처리 한다.(나중에 확인 필요)
//		for(int nIndex = 0; nIndex < pPriceData->qty; nIndex++)
//		{
//			SHA_MICHE_INFO* pMichInfo = (SHA_MICHE_INFO*)pPriceData->detail[nIndex].order_info;
//			if(	pMichInfo != NULL)
//			{
//				//KJI 20060417
//				if(	pMichInfo->trace != NULL)
//				{
//					if(	pMichInfo->trace->gubun == 1)
//						pMsg->AddByte('1');
//					else if(pMichInfo->trace->gubun == 2)
//						pMsg->AddByte('2');
//					else
//						pMsg->AddByte('0');
//				}
//				else
//					pMsg->AddByte('0');
//			}
//			else
//			{
//				//만약 미분석 잔량이 있다면
//				if(	pPriceData->not_anal_vol > 0 && (pPriceData->qty - 1) == nIndex)
//					pMsg->AddByte('3');
//				else
//					pMsg->AddByte('0');
//			}
//				
//			pMsg->AddLong(pPriceData->detail[nIndex].vol);
//			nAddCnt++;	//추가한 데이터를 증가한다.
//		}
//
//		//나머지는 기본값으로 처리 한다.
//		for(nIndex = nAddCnt; nIndex < MAX_DETAIL; nIndex++)
//		{
//			pMsg->AddByte('0');
//			pMsg->AddLong(0);
//		}
//
//		pMsg->SetLong(nModifyPos, nAddCnt);
//	}
//	else
//	{
//		pMsg->AddByte('1');
//		pMsg->AddDouble(0.0);
//		pMsg->AddLong(0);
//
//		for(int nIndex = 0; nIndex < MAX_DETAIL; nIndex++)
//		{
//			pMsg->AddByte('0');
//			pMsg->AddLong(0);
//		}
//	}
//
//	return TRUE;
//}
//
////KJI 20060422 (스크립트 처리용)
//BOOL CStockAgent::GetMicheInfo(CString strAcc, CString strOrderNo, 
//						int* pVol, int* pQty, int* pPrice, XRAY_POWER* pDetail)
//{
//	int nVal = 0;
//	LPTSTR szAcc = strAcc.GetBuffer(strAcc.GetLength());
//	LPTSTR szOrderNo = strOrderNo.GetBuffer(strOrderNo.GetLength());
//
//	SHA_REMAIN_ORDER_VOL stOrderVol;
//	memset(&stOrderVol, 0x00, sizeof(SHA_REMAIN_ORDER_VOL));
//
//	strOrderNo.TrimLeft();	strOrderNo.TrimRight();
//	if(	fXRayOrderNoToOrderVol(szAcc, atoi(strOrderNo), &stOrderVol) == 0)
//		return FALSE;
//
//	*pVol = stOrderVol.vol;
//	*pQty = stOrderVol.qty;
//	*pPrice = stOrderVol.price;
//
//	SHA_PRICE* pPriceData = fXRayPriceByOrderNo(szAcc, atoi(strOrderNo));
//
//	strAcc.ReleaseBuffer();
//	strOrderNo.ReleaseBuffer();
//
//	if(	pPriceData != NULL)
//	{
//		if(	pPriceData->gubun == 1)
//			pDetail->ucSellBuy = '0';
//		else
//			pDetail->ucSellBuy = '1';
//		
//		pDetail->dRatio = 0.0;
//		pDetail->nCount = pPriceData->qty;
//
//		int nAddCnt = 0;
//		for(int nIndex = 0; nIndex < pPriceData->qty; nIndex++)
//		{
//			SHA_MICHE_INFO* pMichInfo = (SHA_MICHE_INFO*)pPriceData->detail[nIndex].order_info;
//			if(	pMichInfo != NULL)
//			{
//				//KJI 20060417
//				if(	pMichInfo->trace != NULL)
//				{
//					if(	pMichInfo->trace->gubun == 1)
//						pDetail->nAData[nIndex].ucOrderFlag = '1';
//					else if(pMichInfo->trace->gubun == 2)
//						pDetail->nAData[nIndex].ucOrderFlag = '2';
//					else
//						pDetail->nAData[nIndex].ucOrderFlag = '0';
//				}
//				else
//					pDetail->nAData[nIndex].ucOrderFlag = '0';
//			}
//			else
//				pDetail->nAData[nIndex].ucOrderFlag = '0';
//				
//			pDetail->nAData[nIndex].nVol = pPriceData->detail[nIndex].vol;
//			nAddCnt++;	//추가한 데이터를 증가한다.
//		}
//
//		//만약 미분석 잔량이 있다면
//		if(	pPriceData->not_anal_vol > 0)
//			pDetail->nAData[pPriceData->qty - 1].ucOrderFlag = '3'; //미분석 처리
//
//		//나머지는 기본값으로 처리 한다.
//		for(nIndex = nAddCnt; nIndex < MAX_DETAIL; nIndex++)
//		{
//			pDetail->nAData[nIndex].ucOrderFlag = '0';
//			pDetail->nAData[nIndex].nVol = 0;
//		}
//	}
//	else
//	{
//		pDetail->ucSellBuy = '1';
//		pDetail->dRatio = 0.0;
//		pDetail->nCount = 0;
//
//		for(int nIndex = 0; nIndex < MAX_DETAIL; nIndex++)
//		{
//			pDetail->nAData[nIndex].ucOrderFlag = '0';
//			pDetail->nAData[nIndex].nVol = 0;
//		}
//	}	
//
//	return TRUE;
//}
//
////KJI 20060424
//void CStockAgent::DeleteMicheInfo(CString strAcc)
//{
//	fXRayClearMicheInfo(strAcc.GetBuffer(strAcc.GetLength()));
//	strAcc.ReleaseBuffer();
//}
//
////KJI 20060503
//BOOL CStockAgent::CheckFocusData(CString strName, CRealData* pData, CString strKey)
//{
//	if( strKey != m_strFileName )
//		return FALSE;
//
//	//대상시장 and 제외대상
//	
//	if( !CF_MarketValid(pData) || CF_ExceptionValid(pData) )	//cgs 20090406 &&를 ||로 바꿈
//		return FALSE;
//	else
//	{	//포착조건
//		if(	!CF_FocusValid(pData) )
//			return FALSE;
//		else
//		{	// 제외대상
//			if(	CF_CodeValid(pData) )
//				return FALSE;
//			else
//			{	// 종목조건
//				if(	!CF_ConditionValid(pData) )
//					return FALSE;
//				else
//				{
//					ChangeFocusData(strName, pData);
//					return TRUE;
//				}
//			}
//		}
//	}
//}
//
////KJI 20060503
//BOOL CStockAgent::CF_MarketValid(CRealData* pData)
//{
//	BOOL bRet = FALSE;
//	CString strCode;
//
//	int nJongType = 0;
//
//	pData->GetDataStr(360, strCode);
//	strCode = DeConvertCode(strCode, &nJongType);
//
//	if(	nJongType < 0)
//		return bRet;
//
//	switch(m_nMarketType)
//	{
//	case 0:	bRet = TRUE;	break;
//	case 1: 
//		if(	nJongType == 1)
//			bRet = TRUE;
//		else
//			bRet = FALSE;
//		break;	//KJI 20060518
//	case 2:
//		if(	nJongType == 2)
//			bRet = TRUE;
//		else
//			bRet = FALSE;
//		break;
//	case 3:
//		if(	CheckIntrCodeList(m_nIntrPos, strCode))
//			bRet = TRUE;
//
//		break;	
//	}
//
//	return bRet;
//}
//
////KJI 20060503 (제외대상 종목)
//BOOL CStockAgent::CF_CodeValid(CRealData* pData)
//{
//	if(	m_nCodeUse == 0)
//		return FALSE;
//
//	CString strCode;
//	int nJongType = 0;
//
//	pData->GetDataStr(360, strCode);
//	strCode = DeConvertCode(strCode, &nJongType);
//
//	if(	nJongType < 0)
//		return TRUE;
//	
//	for(int nPos = 0; nPos < m_saFCode.GetSize(); nPos++)
//	{
//		if(	strCode == m_saFCode.GetAt(nPos))
//			return TRUE;
//	}
//
//	return FALSE;
//}
//
////KJI 20060503
//BOOL CStockAgent::CF_ExceptionValid(CRealData* pData)
//{
//	CString strVal;
//	CStringArray saData;
//
//	//KJI 20060519
//	for(int nPos = 0; nPos < m_saFExecption.GetSize(); nPos++)
//	{
//		if(	m_saFExecption.GetAt(nPos) == "1")
//		{
//			pData->GetDataStr(374 + nPos, strVal);
//			if(	strVal == "1")
//				return TRUE;
//		}
//	}
//
//	return FALSE;
//}
//
////KJI 20060503
//BOOL CStockAgent::CF_ConditionValid(CRealData* pData)
//{
//	//KJI 20060602
//	CString strFlag;
//	pData->GetDataStr(380, strFlag);
//	if(	strFlag == "1")
//		return TRUE;	//동시구분일 경우는 무조건 처리하자
//
//	BOOL bPrice = TRUE;
//	BOOL bVol = TRUE;
//	BOOL bUpDown = TRUE;
//
//	long lVal = 0;
//	long lPrice = 0;
//	long lVol = 0;
//	double dUpDown = 0.0;
//
//	if(	m_nPUse == 1)
//	{
//		pData->GetDataLong(363, lPrice);
//
//		if(	m_nPriceMin <= lPrice && lPrice <= m_nPriceMax)
//			bPrice = TRUE;
//		else
//			bPrice = FALSE;
//	}
//	else
//		bPrice = TRUE;	
//
//	if(	m_nVUse == 1)
//	{
//		pData->GetDataLong(370, lVol);
//
//		if(	m_nVolMin <= lVol && lVol <= m_nVolMax)
//			bVol = TRUE;
//		else
//			bVol = FALSE;
//	}
//	else
//		bVol = TRUE;
//
//	if(	m_nUDUse == 1)
//	{
//		pData->GetDataLong(373, lVal);
//
//		dUpDown = lVal / 100.0;
//
//		if(	m_dUDMin <= dUpDown && dUpDown <= m_dUDMax)
//			bUpDown = TRUE;
//		else
//			bUpDown = FALSE;
//	}
//	else
//		bUpDown = TRUE;
//
//	if(	bPrice && bVol && bUpDown)
//		return TRUE;
//	else
//		return FALSE;
//}
//
////KJI 20060503
//BOOL CStockAgent::CF_FocusValid(CRealData* pData)
//{
//	long lGubun = 0;
//	long lVal = 0;
//
//	//KJI 20060601
//	CDBItemData* pItem = pData->GetItem(379);
//	if(	pItem == NULL)
//	{
//		pData->arID.Add(379);
//		pItem = new CDBItemData(DT_STRING);
//		pItem->Alloc(1);
//		pData->arData.Add(pItem);
//	}
//
//	pData->GetDataLong(367, lGubun);
//
//	if(	lGubun == 0)	//신규
//	{
//		//호가구분
//		pData->GetDataLong(364, lVal);	//매수:-1, 매도:1
//		if(	m_nFNBuySel == 0 && lVal != 1)	//KJI 20060522
//			return FALSE;
//		else if(m_nFNBuySel == 1 && lVal != -1)
//			return FALSE;
//
//		//호가범위
//		pData->GetDataLong(366, lVal);
//		if(	m_nFNRange != 0 && lVal > m_nFNRange)
//			return FALSE;
//
//		//KJI 20060523
//		CString strGubun;
//		if( lVal < m_nFNRange )
//		{	//ynkim 20060609
//			strGubun.Format("%d호가", lVal + 1);
//			pItem->strBuf[0] = strGubun;
//		}
//		else
//			return FALSE;
//
//		//주문수량
//		pData->GetDataLong(368, lVal);
//		if(	lVal < m_nFNVol)
//			return FALSE;
//
//		//주문금액
//		int nVol = lVal;	//KJI 20060523
//		pData->GetDataLong(365, lVal);
//		lVal = nVol * lVal;
//		if(	lVal < m_nFNAmt)
//			return FALSE;
//	}
//	else if(lGubun == 2)	//체결
//	{
//		//체결구분
//		pData->GetDataLong(364, lVal);
//		if(	m_nFCBuySel == 0 && lVal != 1)	//KJI 20060522
//			return FALSE;
//		else if(m_nFCBuySel == 1 && lVal != -1)
//			return FALSE;
//
//		//KJI 20060523
//		if(	lVal == 1)
//			pItem->strBuf[0] = "매도체결";
//		else
//			pItem->strBuf[0] = "매수체결";
//
//		//체결수량
//		pData->GetDataLong(368, lVal);
//		if(	lVal < m_nFCVol)
//			return FALSE;
//
//		//체결금액
//		int nVol = lVal;	//KJI 20060523
//		pData->GetDataLong(365, lVal);
//		lVal = nVol * lVal;
//		if(	lVal < m_nFCAmt)
//			return FALSE;
//	}
//	else
//		return FALSE;
//
//	return TRUE;
//}
//
////KJI 20060503 (관심파일 종목과 비교한다.)
//BOOL CStockAgent::CheckIntrCodeList(int nIndex, CString strCode)
//{
//	CString strSection;
//	
//	strSection.Format("%d", nIndex);
//	CString strFile = GET_USER_CONCERN_DIR2(m_strMainDir) + "\\" + strSection + ".ini";
//
//	CIniFiles	iniFile(strFile, "Default");
//	iniFile.ReadSection();
//
//	char szCode[256];
//	char szType[256];
//
//	CString strVal;
//
//	for(int nPos = 0; nPos < iniFile.val.GetSize(); nPos++)
//	{
//		memset(szCode, 0x00, sizeof(szCode));
//		memset(szType, 0x00, sizeof(szType));
//
//		sscanf(iniFile.Value(nPos), "%[^|]|%s", szCode, szType);
//		strVal = szCode; strVal.TrimLeft(); strVal.TrimRight();
//
//		if(	strVal == strCode)	//KJI 20060519
//			return TRUE;
//	}
//
//	return FALSE;
//}
//
////KJI 20060508 (종목코드및 대비부호를 화면에 맞게 수정)
//void CStockAgent::ChangeFocusData(CString strName, CRealData* pData)
//{
//	CString strCode, strVal;
//	int nJongType = 0;
//
//	pData->GetDataStr(360, strCode);	
//	strCode = DeConvertCode(strCode, &nJongType);
//
//	CDBItemData* pItem = pData->GetItem(360);
//	pItem->strBuf[0] = strCode;
//
//	//KJI 20060601 (자동갱신 테이블에 존재하지 않지만 값을 넣어준다)
//	pItem = pData->GetItem(378);
//	if(	pItem == NULL)
//	{
//		pData->arID.Add(378);
//		pItem = new CDBItemData(DT_STRING);
//		pItem->Alloc(1);
//		pData->arData.Add(pItem);
//	}
//
//	pItem->strBuf[0] = strName;
//
//	pData->GetDataStr(372, strVal);
//	int nDabeType = atoi(strVal);
//
//	pItem = pData->GetItem(372);
//
//	switch(nDabeType)
//	{
//	case 1:	pItem->strBuf[0] = "7";	break;
//	case 2:	pItem->strBuf[0] = "6";	break;
//	case 3:	pItem->strBuf[0] = "5";	break;
//	case 4:	pItem->strBuf[0] = "3";	break;
//	case 5:	pItem->strBuf[0] = "4";	break;
//	default:	break;
//	}
//}
//
////KJI 20060503
//void CStockAgent::LoadFocusData(CString strFilePath)
//{
//	CString strVal, strPos;
//	CString strMin, strMax;
//	char szBuf[512];
//	
//	memset(szBuf, 0x00, sizeof(szBuf));
//
//	//ynkim 20060912
//	::GetPrivateProfileString("FileName", "Name", "HogaFocusSet", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_strFileName = strVal;
//	//End
//
//	::GetPrivateProfileString("Market", "Type", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nMarketType = atoi(strVal);
//
//	::GetPrivateProfileString("Market", "Intr", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nIntrPos = atoi(strVal);
//
//	::GetPrivateProfileString("Code", "Use", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nCodeUse = atoi(strVal);
//
//	::GetPrivateProfileString("Code", "Cnt", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_saFCode.RemoveAll();
//	int nCnt = atoi(strVal);
//	for(int nPos = 0; nPos < nCnt; nPos++)
//	{
//		strPos.Format("Code%d", nPos + 1);
//		::GetPrivateProfileString("Code", strPos, "", szBuf, 512, strFilePath);
//		strVal = szBuf;	strVal.TrimRight();
//
//		if(	strVal.GetLength() == JONGCODE_LEN)
//			m_saFCode.Add(strVal);
//	}
//
//	m_saFExecption.RemoveAll();
//	memset(szBuf, 0x00, sizeof(szBuf));
//	for(nPos = 0; nPos < 4; nPos++)
//	{
//		strPos.Format("Flag%d", nPos + 1);
//		::GetPrivateProfileString("Exception", strPos, "0", szBuf, 512, strFilePath);
//		strVal = szBuf;	strVal.TrimRight();
//
//		m_saFExecption.Add(strVal);
//	}
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//
//	::GetPrivateProfileString("Condition", "PUse", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nPUse = atoi(strVal);
//
//	::GetPrivateProfileString("Condition", "Price", "", szBuf, 512, strFilePath);
//	strVal = szBuf;	strVal.TrimRight();
//
//	int nFind = strVal.Find(",");
//	
//	if(	nFind > 0)
//	{
//		strMin = strVal.Left(nFind);
//		strMax = strVal.Mid(nFind + 1);
//
//		m_nPriceMin = atoi(strMin);
//		m_nPriceMax = atoi(strMax);
//	}
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//
//	::GetPrivateProfileString("Condition", "VUse", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nVUse = atoi(strVal);
//
//	::GetPrivateProfileString("Condition", "Vol", "", szBuf, 512, strFilePath);
//	strVal = szBuf;	strVal.TrimRight();
//
//	nFind = strVal.Find(",");
//	
//	if(	nFind > 0)
//	{
//		strMin = strVal.Left(nFind);
//		strMax = strVal.Mid(nFind + 1);
//
//		m_nVolMin = atoi(strMin);
//		m_nVolMax = atoi(strMax);
//	}
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//
//	::GetPrivateProfileString("Condition", "UDUse", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nUDUse = atoi(strVal);
//
//	::GetPrivateProfileString("Condition", "UpDown", "", szBuf, 512, strFilePath);
//	strVal = szBuf;	strVal.TrimRight();
//
//	nFind = strVal.Find(",");
//	
//	if(	nFind > 0)
//	{
//		strMin = strVal.Left(nFind);
//		strMax = strVal.Mid(nFind + 1);
//
//		m_dUDMin = atof(strMin);
//		m_dUDMax = atof(strMax);
//	}
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusNew", "BuySel", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFNBuySel = atoi(strVal);
//
//	::GetPrivateProfileString("FocusNew", "Range", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFNRange = atoi(strVal);
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusNew", "Vol", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFNVol = atoi(strVal);
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusNew", "Amt", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFNAmt = atoi(strVal);
//	m_nFNAmt *= 10000;	//KJI 20060519
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusChe", "BuySel", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFCBuySel = atoi(strVal);
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusChe", "Vol", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFCVol = atoi(strVal);
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusChe", "Amt", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFCAmt = atoi(strVal);
//	m_nFCAmt *= 10000;	//KJI 20060519
//}
//////////////// ELW 포착 ///////////////
//BOOL CStockAgent::CheckFocusData_ELW(CString strName, CRealData* pData, CString strKey)
//{
//	if( strKey != m_strFileName_ELW )
//		return FALSE;
//
//	if(	!CF_FocusValid_ELW(pData) )
//		return FALSE;
//	else
//	{	// 제외대상
//		if(	CF_CodeValid_ELW(pData) )
//			return FALSE;
//		else
//		{	// 종목조건
//			if(	!CF_ConditionValid_ELW(pData) )
//				return FALSE;
//			else
//			{
//				ChangeFocusData(strName, pData);
//				return TRUE;
//			}
//		}
//	}
//}
//
//BOOL CStockAgent::CF_MarketValid_ELW(CRealData* pData)
//{
//	BOOL bRet = FALSE;
//	CString strCode;
//
//	int nJongType = 0;
//
//	pData->GetDataStr(360, strCode);
//	strCode = DeConvertCode(strCode, &nJongType);
//
//	if(	nJongType < 0)
//		return bRet;
//
//	switch(m_nMarketType_ELW)
//	{ // case가 늘어날경우를 대비해...
//	case 0:	bRet = TRUE;	break;
//	}
//
//	return bRet;
//}
//
////제외대상 종목
//BOOL CStockAgent::CF_CodeValid_ELW(CRealData* pData)
//{
//	if(	m_nCodeUse_ELW == 0)
//		return FALSE;
//
//	CString strCode;
//	int nJongType = 0;
//
//	pData->GetDataStr(360, strCode);
//	strCode = DeConvertCode(strCode, &nJongType);
//
//	if(	nJongType < 0)
//		return TRUE;
//	
//	for(int nPos = 0; nPos < m_saFCode_ELW.GetSize(); nPos++)
//	{
//		if(	strCode == m_saFCode_ELW.GetAt(nPos))
//			return TRUE;
//	}
//
//	return FALSE;
//}
//
//BOOL CStockAgent::CF_ConditionValid_ELW(CRealData* pData)
//{
//	//KJI 20060602
//	CString strFlag;
//	pData->GetDataStr(380, strFlag);
//	if(	strFlag == "1")
//		return TRUE;	//동시구분일 경우는 무조건 처리하자
//
//	BOOL bPrice = TRUE;
//	BOOL bVol = TRUE;
//	BOOL bUpDown = TRUE;
//
//	long lVal = 0;
//	long lPrice = 0;
//	long lVol = 0;
//	double dUpDown = 0.0;
//
//	if(	m_nPUse_ELW == 1)
//	{
//		pData->GetDataLong(363, lPrice);
//
//		if(	m_nPriceMin_ELW <= lPrice && lPrice <= m_nPriceMax_ELW )
//			bPrice = TRUE;
//		else
//			bPrice = FALSE;
//	}
//	else
//		bPrice = TRUE;	
//
//	if(	m_nVUse_ELW == 1)
//	{
//		pData->GetDataLong(370, lVol);
//
//		if(	m_nVolMin_ELW <= lVol && lVol <= m_nVolMax_ELW )
//			bVol = TRUE;
//		else
//			bVol = FALSE;
//	}
//	else
//		bVol = TRUE;
//
//	if(	m_nUDUse_ELW == 1)
//	{
//		pData->GetDataLong(373, lVal);
//
//		dUpDown = lVal / 100.0;
//
//		if(	m_dUDMin_ELW <= dUpDown && dUpDown <= m_dUDMax_ELW )
//			bUpDown = TRUE;
//		else
//			bUpDown = FALSE;
//	}
//	else
//		bUpDown = TRUE;
//
//	if(	bPrice && bVol && bUpDown)
//		return TRUE;
//	else
//		return FALSE;
//}
//
//BOOL CStockAgent::CF_FocusValid_ELW(CRealData* pData)
//{
//	long lGubun = 0;
//	long lVal = 0;
//
//	//KJI 20060601
//	CDBItemData* pItem = pData->GetItem(379);
//	if(	pItem == NULL)
//	{
//		pData->arID.Add(379);
//		pItem = new CDBItemData(DT_STRING);
//		pItem->Alloc(1);
//		pData->arData.Add(pItem);
//	}
//
//	pData->GetDataLong(367, lGubun);
//
//	CString strTemp, strTemp1, strTemp2;
//	if(	lGubun == 0)	//신규
//	{
//		//호가구분
//		pData->GetDataLong(364, lVal);	//매수:-1, 매도:1
//		strTemp.Format("%d\n",lVal);
//		if(	m_nFNBuySel_ELW == 0 && lVal != 1)
//			return FALSE;
//		else if(m_nFNBuySel_ELW == 1 && lVal != -1)
//			return FALSE;
//
//		//호가범위
//		pData->GetDataLong(366, lVal);
//		if(	m_nFNRange_ELW != 0 && lVal > m_nFNRange_ELW )
//			return FALSE;
//
//		CString strGubun;
//		if( lVal < m_nFNRange_ELW )
//		{	//ynkim 20060609
//			strGubun.Format("%d호가", lVal + 1);
//			pItem->strBuf[0] = strGubun;
//		}
//		else
//			return FALSE;
//
//		//주문수량
//		pData->GetDataLong(368, lVal);
//		if(	lVal < m_nFNVol_ELW )
//			return FALSE;
//
//		//주문금액
//		int nVol = lVal;
//		pData->GetDataLong(365, lVal);
//		lVal = nVol * lVal;
//		if(	lVal < m_nFNAmt_ELW )
//			return FALSE;
//	}
//	else if(lGubun == 2)	//체결
//	{
//		//체결구분
//		pData->GetDataLong(364, lVal);
//		if(	m_nFCBuySel_ELW == 0 && lVal != 1)
//			return FALSE;
//		else if(m_nFCBuySel_ELW == 1 && lVal != -1)
//			return FALSE;
//
//		//KJI 20060523
//		if(	lVal == 1)
//			pItem->strBuf[0] = "매도체결";
//		else
//			pItem->strBuf[0] = "매수체결";
//
//		//체결수량
//		pData->GetDataLong(368, lVal);
//		if(	lVal < m_nFCVol_ELW )
//			return FALSE;
//		//체결금액
//		int nVol = lVal;
//		pData->GetDataLong(365, lVal);
//		lVal = nVol * lVal;
//		if(	lVal < m_nFCAmt_ELW )
//			return FALSE;
//	}
//	else
//		return FALSE;
//
//	return TRUE;
//}
//
////ynkim 20060906
//void CStockAgent::LoadFocusData_ELW(CString strFilePath)
//{
//	CString strVal, strPos;
//	CString strMin, strMax;
//	char szBuf[512];
//	
//	memset(szBuf, 0x00, sizeof(szBuf));
//
//	//ynkim 20060912
//	::GetPrivateProfileString("FileName", "Name", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_strFileName_ELW = strVal;
//	//End
//
//	::GetPrivateProfileString("Market", "Type", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nMarketType_ELW = atoi(strVal);
//
//	::GetPrivateProfileString("Market", "Intr", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nIntrPos_ELW = atoi(strVal);
//
//	::GetPrivateProfileString("Code", "Use", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nCodeUse_ELW = atoi(strVal);
//
//	::GetPrivateProfileString("Code", "Cnt", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_saFCode_ELW.RemoveAll();
//	int nCnt = atoi(strVal);
//	for(int nPos = 0; nPos < nCnt; nPos++)
//	{
//		strPos.Format("Code%d", nPos + 1);
//		::GetPrivateProfileString("Code", strPos, "", szBuf, 512, strFilePath);
//		strVal = szBuf;	strVal.TrimRight();
//
//		if(	strVal.GetLength() == JONGCODE_LEN)
//			m_saFCode_ELW.Add(strVal);
//	}
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//
//	::GetPrivateProfileString("Condition", "PUse", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nPUse_ELW = atoi(strVal);
//
//	::GetPrivateProfileString("Condition", "Price", "", szBuf, 512, strFilePath);
//	strVal = szBuf;	strVal.TrimRight();
//
//	int nFind = strVal.Find(",");
//	
//	if(	nFind > 0)
//	{
//		strMin = strVal.Left(nFind);
//		strMax = strVal.Mid(nFind + 1);
//
//		m_nPriceMin_ELW = atoi(strMin);
//		m_nPriceMax_ELW = atoi(strMax);
//	}
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//
//	::GetPrivateProfileString("Condition", "VUse", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nVUse_ELW = atoi(strVal);
//
//	::GetPrivateProfileString("Condition", "Vol", "", szBuf, 512, strFilePath);
//	strVal = szBuf;	strVal.TrimRight();
//
//	nFind = strVal.Find(",");
//	
//	if(	nFind > 0)
//	{
//		strMin = strVal.Left(nFind);
//		strMax = strVal.Mid(nFind + 1);
//
//		m_nVolMin_ELW = atoi(strMin);
//		m_nVolMax_ELW = atoi(strMax);
//	}
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//
//	::GetPrivateProfileString("Condition", "UDUse", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//	m_nUDUse_ELW = atoi(strVal);
//
//	::GetPrivateProfileString("Condition", "UpDown", "", szBuf, 512, strFilePath);
//	strVal = szBuf;	strVal.TrimRight();
//
//	nFind = strVal.Find(",");
//	
//	if(	nFind > 0)
//	{
//		strMin = strVal.Left(nFind);
//		strMax = strVal.Mid(nFind + 1);
//
//		m_dUDMin_ELW = atof(strMin);
//		m_dUDMax_ELW = atof(strMax);
//	}
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusNew", "BuySel", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFNBuySel_ELW = atoi(strVal);
//
//	::GetPrivateProfileString("FocusNew", "Range", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFNRange_ELW = atoi(strVal);
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusNew", "Vol", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFNVol = atoi(strVal);
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusNew", "Amt", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFNAmt_ELW = atoi(strVal);
//	m_nFNAmt_ELW *= 10000;
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusChe", "BuySel", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFCBuySel_ELW = atoi(strVal);
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusChe", "Vol", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFCVol_ELW = atoi(strVal);
//
//	memset(szBuf, 0x00, sizeof(szBuf));
//	::GetPrivateProfileString("FocusChe", "Amt", "0", szBuf, 512, strFilePath);
//	strVal = szBuf;
//
//	m_nFCAmt_ELW = atoi(strVal);
//	m_nFCAmt_ELW *= 10000;
//}
//
////KJI 20060629
//void CStockAgent::WriteDataLog(CString strCode, int nPower)
//{
////KJI 20060628(컴퓨터에 부하발생을 하므로 필요시만 풀어서 확인을 한다.)
//#ifdef _DEBUG
//	CString strName;
//	int nJongType = ::SendMessage(m_hDataMgr, WMU_JONG_PART, (WPARAM)(LPCTSTR)strCode, (LPARAM)&strName);
//	int nXRayJCode = ConvertCode(strCode, nJongType);
//	fXRayDataLogMode(nXRayJCode, nPower, NULL, 1);
//#endif
////
//}