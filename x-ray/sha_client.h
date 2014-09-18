#ifndef sha_client_h
#define sha_client_h

                 
#include "sha.h"

#define SHA_NEW   	1										/// 매도, 매수 주문
#define SHA_JJ      2										/// 정정 주문
#define SHA_CANCEL  3										/// 취소 주문

#define SHA_MEDO    1										/// 매도
#define SHA_MESU   -1										/// 매수

typedef struct 
{
	int price;							///< 해당 가격
	int vol;							///< 내 주문 앞의 총 주문 수량
	int qty;						    ///< 내주문 앞의 건수
} SHA_REMAIN_ORDER_VOL;

typedef struct
{
	int price;							///< 해당 가격
	int gubun;							///< 매수매도구분
	int org_vol;						///< 호가잔량
	int power_vol;						///< 세력합
	double ratio;						///< 비율 (세력합/잔량 * 100)
} SHA_POWER_SUB ;

typedef struct 
{
	int code;							///< 종목코드
	int filter;							///< 필터
	SHA_POWER_SUB  power[20];			///< 가격대별 세력 강도정보
	SHA_POWER_SUB  medo_total_power;	///< 총매도(10호가)잔량 대비 총 세력정보
	SHA_POWER_SUB  mesu_total_power;	///< 총매수(10호가) 잔량 대비 총 세력정보
} SHA_POWER;

typedef struct 
{
	int 			gubun;				///<매수, 매도구분 (SHA_MEDO, SHA_MESU)
	int				time;				///< 입출 시간
	int				vol;				///<수량 (추가+, 감소 -)
    int             subseq;             ///< 순서 번호
} SHA_IO_PRICE_SUB;

typedef struct
{
    int			code;					///< 종목코드
    int			price;					///< 종목코드
    int			filter;					///< 필터 값
	int 		cnt;					///< 갯수
	SHA_IO_PRICE_SUB	data[100];		///< 입출력 내역
} SHA_IO_PRICE;

typedef struct
{
	int time;							///< 입출시간
	int gubun;							///< 매도, 매수 구분 (SHA_MEDO, SHA_MESU)
	int price;							///< 가격
	int hoga;							///< 호가위치 (1호가 2호가 .. 10호가)
	int vol;							///< 신규수량
    int subseq;                         ///< 순서 번호
} SHA_IO_NEW_SUB;

typedef struct
{
    int			code;					///< 종목코드
    int			filter;					///< 필터 값
	int 		cnt;					///< 갯수
	SHA_IO_NEW_SUB	data[100];			///< 신규 내역
} SHA_IO_NEW;


typedef struct
{
	int time;							///< 입출시간
	int gubun;							///< 매도, 매수 구분 (SHA_MEDO, SHA_MESU)
	int price;							///< 가격
	int hoga;							///< 호가위치 (1호가 2호가 .. 10호가)
	int vol;							///< 취소수량
    int             subseq;             ///< 순서 번호
} SHA_IO_CANCEL_SUB;

typedef struct
{
    int			code;					///< 종목코드
    int			filter;					///< 필터 값
	int 		cnt;					///< 갯수
	SHA_IO_CANCEL_SUB	data[100];		///< 취소 내역
} SHA_IO_CANCEL;


typedef struct 
{
	int time;							///< 입출시간
	int gubun;							///< 매도, 매수 구분 (SHA_MEDO, SHA_MESU)
	int from_price;						///< 정정 전 가격
	int from_hoga;						///< 정정 전 호가위치 (1호가 2호가 .. 10호가)
	int to_price;						///< 정정 후 가격
	int to_hoga;						///< 정정 후 호가위치 (1호가 2호가 .. 10호가)
	int vol;							///< 정정수량
    int subseq;                         ///< 순서 번호
} SHA_IO_JJ_SUB;

typedef struct
{
    int			code;					///< 종목코드
    int			filter;					///< 필터 값
	int 		cnt;					///< 갯수
	SHA_IO_JJ_SUB	data[100];		    ///< 정정 내역
} SHA_IO_JJ;

typedef struct
{
    int				code;					///< 종목코드
    int				filter;					///< 필터 값

	SHA_IO_NEW		sha_io_new;				///< 신규
	SHA_IO_CANCEL	sha_io_cancel;				///<취소
	SHA_IO_JJ		sha_io_jj;					///< 정정
	SHA_IO_PRICE 	price[SHA_RANGE];		///< 각 가격별 입출내역
} SHA_IO;

typedef struct
{
    int medo_sum;       ///< 매도합
    int medo_qty;       ///< 매도 갯수
    int mesu_sum;       ///< 매수합
    int mesu_qty;       ///< 매수 갯수
    double ratio;       ///< 매도합/매수합*100 
} SHA_IO_POWER_SUB;

typedef struct
{
    int				code;					///< 종목코드
    int				filter;					///< 필터 값
    int				range;					///< 영역 (0:전체 1:1호가 2: 1~2호가  3:1~3호가)

    SHA_IO_POWER_SUB          new_power;
    SHA_IO_POWER_SUB          cancel_power;           ///< 매도/매수*100 취소강도
} SHA_IO_POWER;

typedef struct tagSHA_ORDER_TRACE_INFO
{
    int status;         // 0 HogaMudule와 연결되지 않음, 1 : HogaMudule와 연결됨   2: 추적불가능 상황(추적 시작도 하지 않는다....)
    int gubun;          // 0 분석 대기중, 1 위치 추정 2 위치포착, 3 분석불능   4 체결근접
    int start_seq_no;   // 주문시의 호가 시퀀스
    int presumption_seq_no;   // 추정된된 호가 시퀀스 (추정)
    int capture_seq_no;      // 포착된 호가 시퀀스 (포착)

    SHA_DATA *sha_data;

    int filler[5];

} SHA_ORDER_TRACE_INFO;

typedef struct
{
    char account[17];
    int jong_code;			// 종목코드
    int org_ord_no;			// 원주문번호
    int ord_no;				// 주문번호
    int order_gubun;        // 1 매수, 2 매도
    char buy_sell_tp[5];	// 매도매수구분 ("매수", "매도")
    int order_price;		// 주문가격
    int order_qty;			// 주문수량
    int che_remn_qty;   	// 체결잔량
    char rcv_tp[5];			// 접수여부
    int rcv_time;			// 접수시간 mmhhss

    int seq_no;                     // 추적 번호
    SHA_ORDER_TRACE_INFO * trace;   // 주문추적정보
} SHA_MICHE_INFO;

typedef struct
{
    char account[17];
    char gubun[5];          // "접수", "확인", "체결" , "거부"
    int jong_code;			// 종목코드
    int order_gubun;        // 1 매수, 2 매도, 3 정정, 4 취소
    int org_ord_no;			// 원주문번호
    int ord_no;				// 주문번호
    char buy_sell_tp[5];	// 매도매수구분 ("매수", "매도")
    int order_price; 		// 주문(정정)가격
    int order_qty;	 		// 주문(정정, 취소)수량
    int che_price;	 		// 체결가격

    int che_qty; 	 		// 체결수량
    int che_remn_qty;		// 체결잔량

    int org_order_price;	// 원주문 가격
    int org_order_qty;		// 원주문 수량

    int jj_qty;  			// 정정(취소) 확인수량
    char rcv_tp[5];			// 접수여부 ("접수", "체결", "확인", "주문", "거부")
    int rcv_time;			// 접수시간 mmhhss
} SHA_REAL_INFO, SHA_ORDER_INFO, SHA_JUBSU_INFO;

typedef struct
{
    int medo_vol;           // 매도 수량합
    int medo_qty;           // 매도 건수
    int mesu_vol;           // 매수 수량합
    int mesu_qty;           // 매수 건수
} SHA_DISTRIBUTION;


#endif
