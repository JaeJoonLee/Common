#ifndef sha_client_dll_h
#define sha_client_dll_h

                 
#include "sha_client.h"

#define DLL_EXPORT   __declspec(dllimport)

namespace sha_client
{

extern "C"
{
// 해당 종목의 호가분석 생성
DLL_EXPORT int  _sha_create(int code, SHA_DATA * server_sha_data);

// 해당 종목의 호가분석 생성
DLL_EXPORT int  _sha_create_dummy(int code);

// 해당 종목의 호가분석 생성
DLL_EXPORT int  _sha_create_by_handle(int code, void *handle);

//서버로 부터 받아온 호가분석 자료를 복사
DLL_EXPORT void  _sha_set(int code, SHA_DATA *server_sha_data);

//종목 호가분석 삭제
DLL_EXPORT int  _sha_delete(int code);

//해당 핸들의 종목 호가분석 삭제
DLL_EXPORT int  _sha_delete_by_handle(int code, void *handle);

//해당 종목의 호가분석이 존재하는지 여부 ( 0 없음, 1 있음)
 DLL_EXPORT int  _sha_is_exist(int code);

//해당 종목의 호가분석이 존재하는지 여부 ( 0 없음, 1 있음)
 DLL_EXPORT int  _sha_is_exist_by_handle(int code, void *handle);

//종목 호가분석 포인터를 얻어오는 함수
 DLL_EXPORT SHA_DATA * _sha_get(int code);

//종목 호가분석 포인터를 얻어오는 함수 (리턴 : 리스트 갯수)
 DLL_EXPORT int  _sha_get_handle_list(int code,int *plist);

//종목의 특정가격의 호가분석 정보
 DLL_EXPORT SHA_PRICE  * _sha_get_price(int code, int price);

//필터된 종목의 호가세력 정보
 DLL_EXPORT void  _sha_get_power(int code, int filter, SHA_POWER *sha_power);

 DLL_EXPORT void  _sha_get_power_range(int code, int filter, int range, SHA_POWER *sha_power);

//직전체결의 종목의 호가분석 정보
 DLL_EXPORT int  _sha_get_prv_chegyul_detail(int code, int filter, int gubun, SHA_DETAIL  *sha_detail);


//입출 정보 등록
 DLL_EXPORT int  _sha_io_create(int code, int filter, void *handle);

//입출 정보 삭제
 DLL_EXPORT void  _sha_io_delete(int code, int filter, void *handle);

//입출 정보 포인터 받기
 DLL_EXPORT SHA_IO *  _sha_io_get(int code, int filter, void *handle);

//특정 가격의 입출 정보 포인터 받기
 DLL_EXPORT SHA_IO_PRICE *  _sha_io_get_price(int code, int filter, void *handle, int price);

//입출 정보 중 신규 주문의 리스트 포인터 받기
 DLL_EXPORT SHA_IO_NEW *  _sha_io_get_new(int code, int filter, void *handle);

//입출 정보 중 취소 주문의 리스트 포인터 받기
 DLL_EXPORT SHA_IO_CANCEL *  _sha_io_get_cancel(int code, int filter, void *handle);

//입출 정보 중 정정 주문의 리스트 포인터 받기
 DLL_EXPORT SHA_IO_JJ *  _sha_io_get_jj(int code, int filter, void *handle);

//입출 정보 의 신규강도와 취소강도 리턴..
//sha_io_power의 filter와 range를 꼭 채워서 넣어야한다...
//range가 0이면 전체 영역으로 인식
DLL_EXPORT int  _sha_io_get_power(int code, int filter, void *handle, SHA_IO_POWER *sha_io_power);



//체결정보 입력
 DLL_EXPORT void  _sha_set_sise(SHA_SISE_PACKET *ssp);

//호가정보 입력
 DLL_EXPORT void  _sha_set_hoga(SHA_HOGA_PACKET *shp);

// 표준코드를 숫자형코드로 변환     market_tag :  거래소 '1' 코스닥 '2'
// 예> A005930 -> 10059300
 DLL_EXPORT int  _sha_code_conv(char *code_str, char market_tag);



// 미체결 리스트 입력
 DLL_EXPORT void  _sha_set_miche(char *account, int list_cnt, SHA_MICHE_INFO *sha_miche_info);

// 미체결 리스트 가지고 오기
 DLL_EXPORT SHA_MICHE_INFO *  _sha_get_miche(char *account, int order_no);

// 해당 계좌의 미체결 리스트 가지고 오기 (포인터 링크)(최대 100개)
 DLL_EXPORT int  _sha_get_miche_account(char *account, SHA_MICHE_INFO **miche_info_list);


// 실시간 접수, 체결 확인 입력
 DLL_EXPORT void  _sha_set_real(SHA_REAL_INFO *sha_real_info);
// 주문정보 입력 (주문시)
 DLL_EXPORT void  _sha_set_order(SHA_ORDER_INFO *sha_order_info);
// 주문번호 입력 (주문번호 접수시)
 DLL_EXPORT void  _sha_set_jubsu(SHA_JUBSU_INFO *sha_jubsu_info);


// 디버그 실행 : flag = 1   해제 flag = 0
 DLL_EXPORT void  _sha_set_debug(int code, int flag);
 DLL_EXPORT void  _sha_set_logging(int code, int filter, void *handle, int flag);

// 주문번호를 이용해 해당 SHA_PRICE*를 받는다.
// trace에서 사용
 DLL_EXPORT SHA_PRICE *  _sha_get_price_by_orderno(char *account, int ord_no);

// 주문번호를 이용해 해당 SHA_DETAIL*를 받는다.
// trace에서 사용
 DLL_EXPORT SHA_DETAIL *   _sha_get_detail_by_orderno(char *account, int ord_no);

// 주어진 갯수를 표시할 수 있는 최대 필터값을 리턴한다.
// num의 최대는  10
 DLL_EXPORT int  _sha_get_max_filter(int code, int num);


// 체결전 표시를 위해 (내주문앞의 총주문 수량정보)
// remain 은  SHA_REMAIN_ORDER_VOL remain으로 선언하여 &remain으로 입력값으로 넘겨준다.
// remain의 내용을 채워서 리턴
DLL_EXPORT void  _sha_get_remain_order_vol(SHA_PRICE *sha_price, SHA_MICHE_INFO *pMiche, SHA_REMAIN_ORDER_VOL *remain);

// 체결전 표시를 위해 (내주문앞의 총주문 수량정보)
// remain 은  SHA_REMAIN_ORDER_VOL remain[20]으로 선언하여 입력값으로 넘겨준다.
// remain의 내용을 채워서 리턴
DLL_EXPORT int  _sha_get_remain_order_vol_array(char *account, int code, SHA_REMAIN_ORDER_VOL *remain);

// remain 은  SHA_REMAIN_ORDER_VOL remain으로 선언하여 &remain으로 입력값으로 넘겨준다.
// remain의 내용을 채워서 리턴
DLL_EXPORT int  _sha_get_remain_order_vol_by_orderno(char *account, int ord_no, SHA_REMAIN_ORDER_VOL *remain);


// compare는 비교 수량(예:100, 300, 700, 1000), 반드시 오름차순으로  소팅해서 넣을 것
// cnt는 비교수량 갯수 (예:4)
// 리턴은 sha_dist에 채워서 리턴함
// cnt+1개가 리턴됨 cnt+개는 그 이상인 물량
// 리턴값은 sdis의 갯수임 (cnt+1), 오류일경우 0리턴
DLL_EXPORT int  _sha_get_distribution(int code, int *comp_unit, int cnt, SHA_DISTRIBUTION *sha_dist);


// list는 내림차순으로... 즉 최신이 0번임.
// 반드시 sha_io_create 후에 바로 사용해야함... (쓰레기가 들어갈 여지가 있음)
// 입출중 정정은 별도로 계산하지 않음...(신규와 취소로 들어감)
// code와 filter가 동일한 입출 정보에만 세팅됨....
DLL_EXPORT void   _sha_io_set(int code, int filter, int cnt, SHA_EVENT * plist);

// 세력강도 리턴 (%값 리턴)
DLL_EXPORT int  _sha_get_power_ratio(int code, int filter);
DLL_EXPORT int	_sha_get_power_range_ratio(int code, int filter, int range);

//  입출강도 리턴 (%값 리턴)
DLL_EXPORT int  _sha_get_io_power_ratio(int code, int filter, void *handle);

// 체결강도 리턴 (%값 리턴)
DLL_EXPORT int  _sha_get_ch_power_ratio(int code, int filter, void *handle);

// 미체결 리스트 삭제
DLL_EXPORT void  _sha_clear_miche(char *account);


}
}

using namespace sha_client;

#endif
