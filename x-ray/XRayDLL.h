//KJI 20060328
#include "sha_client_Dll.h"

//_sha_create	
typedef int (cdecl *XRCreate)(int code, SHA_DATA * server_sha_data);

//_sha_delete
typedef int (cdecl *XRDelete)(int code);

//_sha_create_by_handle	
typedef int (cdecl *XRCreateH)(int code, void* handle);

//_sha_delete_by_handle
typedef int (cdecl *XRDeleteH)(int code, void *handle);

//_sha_get
typedef SHA_DATA* (cdecl *XRGetStdData)(int code);

//_sha_get_power;
typedef void (cdecl *XRGetPowerData)(int code, int filter, SHA_POWER *sha_power);

//_sha_get_price
typedef SHA_PRICE* (cdecl *XRGetPriceData)(int code, int price);

//_sha_io_create
typedef int (cdecl *XRCreateIO)(int code, int filter, void *handle);

//_sha_io_delete
typedef void (cdecl *XRDeleteIO)(int code, int filter, void *handle);

//_sha_io_get
typedef SHA_IO* (cdecl *XRGetIOData)(int code, int filter, void *handle);

//_sha_io_get_price
typedef SHA_IO_PRICE* (cdecl *XRGetIOPriceData)(int code, int filter, void *handle, int price);

//int DLL_EXPORT _sha_get_distribution
typedef int (cdecl *XRGetOffer)(int code, int *comp_unit, int cnt, SHA_DISTRIBUTION *sha_dist);

//_sha_set_sise
typedef void (cdecl *XRSetSiseData)(SHA_SISE_PACKET *ssp);

//_sha_set_hoga
typedef void (cdecl *XRSetHogaData)(SHA_HOGA_PACKET *shp);

// 표준코드를 숫자형코드로 변환     market_tag :  거래소 '1' 코스닥 '2'
// 예> A005930 -> 10059300
//_sha_code_conv
typedef int (cdecl *XRCodeConv)(char *code_str, char market_tag);

//_sha_get_max_filter
typedef int (cdecl *XRGetMaxFilter)(int code, int num);
//_sha_is_exist
typedef int (cdecl *XRIsExist)(int code);

//_sha_is_exist_by_handle
typedef int (cdecl *XRIsExistH)(int code, void *handle);

//_sha_set_miche
typedef void (cdecl *XRSetMiche)(char *account, int list_cnt, SHA_MICHE_INFO *sha_miche_info);

//_sha_set_real
typedef void (cdecl *XRSetReal)(SHA_REAL_INFO *sha_real_info);

//_sha_get_remain_order_vol
typedef void (cdecl *XRGetPriceToOrderVol)(SHA_PRICE *sha_price, SHA_MICHE_INFO *pMiche, SHA_REMAIN_ORDER_VOL *remain);

//_sha_get_remain_order_vol_array
typedef int (cdecl *XRGetRemainOrderVol)(char *account, int code, SHA_REMAIN_ORDER_VOL *remain);

//_sha_get_remain_order_vol_by_orderno
typedef int (cdecl *XRGetOrderNoToOrderVol)(char *account, int ord_no, SHA_REMAIN_ORDER_VOL *remain);

//_sha_get_price_by_orderno
typedef SHA_PRICE* (cdecl *XRGetPriceByOrderNo)(char *account, int ord_no);

//int DLL_EXPORT _sha_get_power_ratio;
typedef int (cdecl *XRGetPowerRatio)(int code, int filter);

//int _sha_get_power_range_ratio
typedef int (cdecl *XRGetPowerRangeRatio)(int code, int filter, int range);	//KJI 20060615

//int DLL_EXPORT _sha_get_io_power_ratio;
typedef int (cdecl *XRGetIOPowerRatio)(int code, int filter, void *handle);

//int DLL_EXPORT _sha_get_ch_power_ratio;
typedef int (cdecl *XRGetChPowerRatio)(int code, int filter, void *handle);

// 미체결 리스트 삭제
//void DLL_EXPORT _sha_clear_miche;
typedef void (cdecl *XRClearMicheInfo)(char *account);

//디버그 실행 : flag = 1   해제 flag = 0
//DLL_EXPORT void  _sha_set_logging;
typedef void (cdecl *XRDataLogMode)(int code, int filter, void *handle, int flag);

//int DLL_EXPORT _sha_get_handle_list;
typedef int (cdecl *XRGetHandleList)(int code,int *plist);