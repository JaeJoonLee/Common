#ifndef sha_h
#define sha_h
//---------------------------------------------------------------------------

#define MEDO_DIR    1
#define MESU_DIR    -1
#define NONE_DIR    0


#define STOCK_HOGA_RANGE			10						/// 10호가
#define SHA_RANGE					30						/// 분석 가격버퍼 영역
#define MAX_DETAIL					500


#define SHA_PRICE SHA_INDEX


typedef struct _kos_hoga_data
{
	int sell_price;							 				///< 매도호가 SIGN 부호
	int buy_price;											///< 매수호가 SIGN 부호
	int sell_vol;											///< 매도호가 잔량
	int buy_vol;											///< 매수호가 잔량
} KOS_HOGA_DATA;

typedef struct _sha_packet
{
	int code;												///< 앵커 내부 코드

	int time;												///< 시간       형식:HHMMSS

	short jang;												///< 장구분, 1: 장전 동시호가 3: 장중 5:시간외 종가
															///< 9: 장종료

	int cur_price;											///< 현재가
	int volume;												///< 거래량

	KOS_HOGA_DATA hoga[STOCK_HOGA_RANGE];

	int count;												///< 틱번호
	int seq_no;												///<호가 시퀀스넘버

    int hoga_vol;                                            ///<예상체결수량
    int base_vol;                                           ///<기준 거래량

	int reserved[8];										/// 예약

} KOS_PACKET;

//호가패킷 구조체 정의
typedef struct _sha_hoga_packet
{
	int code;												///< 앵커 내부 코드

	int time;												///< 시간       형식:HHMMSS

	short jang;												///< 장구분, 1: 장전 동시호가 3: 장중 5:시간외 종가
															///< 9: 장종료
	KOS_HOGA_DATA hoga[STOCK_HOGA_RANGE];

	int seq_no;												///<호가 시퀀스넘버

    int exp_price;
    int exp_vol;                                            ///<예상체결가
                                                            ///<예상체결수량
    int volume;                                             ///<누적 거래량
    int filler[4];
} SHA_HOGA_PACKET;

// 체결 패킷 구조체 정의
typedef struct _sha_sise_packet
{
	int code;												///< 앵커 내부 코드

	int time;												///< 시간       형식:HHMMSS

	int cur_price;											///< 현재가
	int volume;												///< 거래량

	short jang;												///< 장구분, 1: 장전 동시호가 3: 장중 5:시간외 종가
    int filler[4];
} SHA_SISE_PACKET;

typedef struct _sha_detail
{
	int vol;
    void *order_info;							        ///< 미체결 주문정보 링크 (주문 추적시 사용) SHA_MICHE_INFO *로 형변환해서 사용
	union {											        ///< 주문잔량
		int seq_no;
    	int time;												///< 시세패킷 시간
	};
} SHA_DETAIL;

typedef struct _sha_index
{
	int price;												///< 가격
	SHA_DETAIL detail[MAX_DETAIL];							///< 개별 호가정보 맵
	int qty;												///< 호가 세부 갯수(건수)
	int vol;												///< 호가 세부 합계(잔량합)
	int chegyul;											///< 체결
	int cancel;												///< 취소
	int add;												///< 추가(신규)
	int gubun;												///< 1:매도호가 -1:매수호가
	int not_anal_flag;										///< 미분석잔량이 있나?
	int not_anal_vol;										///< 미분석잔량
	short update_flag;									   	///< 갱신여부
	short sb_che_flag;									   	///< 갱신여부
	int org_vol;											///< 호가를 잡아먹은 체결일경우 세팅
} SHA_PRICE;

typedef struct _sha_data             
{
	KOS_PACKET kos_packet;
	union {
		int code;
		int acode;
		int m_Code;
	};
    SHA_PRICE sha_price[SHA_RANGE];						///< index
} SHA_DATA;

typedef struct
{
    int	code;							/*//< 종목코드 */
	int time;							/*//< 입출시간 */
	int count;							/*//< Sequence Number*/
	int cur_price;						/*//< 현재가 */
	int gubun;							/*//< 매도, 매수 구분 (SHA_MEDO, SHA_MESU) */
	int price;							/*//< 가격 */
	short hoga;							/*//< 호가위치 (1호가 2호가 .. 10호가) */
	short io_gubun;						/*//< 신규, 취소, 체결구분  (0: 신규  1: 취소 2: 체결) */
	int vol;							/*//< 수량 */
} SHA_EVENT;

#endif


