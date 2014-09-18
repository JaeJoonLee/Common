#ifndef sha_h
#define sha_h
//---------------------------------------------------------------------------

#define MEDO_DIR    1
#define MESU_DIR    -1
#define NONE_DIR    0


#define STOCK_HOGA_RANGE			10						/// 10ȣ��
#define SHA_RANGE					30						/// �м� ���ݹ��� ����
#define MAX_DETAIL					500


#define SHA_PRICE SHA_INDEX


typedef struct _kos_hoga_data
{
	int sell_price;							 				///< �ŵ�ȣ�� SIGN ��ȣ
	int buy_price;											///< �ż�ȣ�� SIGN ��ȣ
	int sell_vol;											///< �ŵ�ȣ�� �ܷ�
	int buy_vol;											///< �ż�ȣ�� �ܷ�
} KOS_HOGA_DATA;

typedef struct _sha_packet
{
	int code;												///< ��Ŀ ���� �ڵ�

	int time;												///< �ð�       ����:HHMMSS

	short jang;												///< �屸��, 1: ���� ����ȣ�� 3: ���� 5:�ð��� ����
															///< 9: ������

	int cur_price;											///< ���簡
	int volume;												///< �ŷ���

	KOS_HOGA_DATA hoga[STOCK_HOGA_RANGE];

	int count;												///< ƽ��ȣ
	int seq_no;												///<ȣ�� �������ѹ�

    int hoga_vol;                                            ///<����ü�����
    int base_vol;                                           ///<���� �ŷ���

	int reserved[8];										/// ����

} KOS_PACKET;

//ȣ����Ŷ ����ü ����
typedef struct _sha_hoga_packet
{
	int code;												///< ��Ŀ ���� �ڵ�

	int time;												///< �ð�       ����:HHMMSS

	short jang;												///< �屸��, 1: ���� ����ȣ�� 3: ���� 5:�ð��� ����
															///< 9: ������
	KOS_HOGA_DATA hoga[STOCK_HOGA_RANGE];

	int seq_no;												///<ȣ�� �������ѹ�

    int exp_price;
    int exp_vol;                                            ///<����ü�ᰡ
                                                            ///<����ü�����
    int volume;                                             ///<���� �ŷ���
    int filler[4];
} SHA_HOGA_PACKET;

// ü�� ��Ŷ ����ü ����
typedef struct _sha_sise_packet
{
	int code;												///< ��Ŀ ���� �ڵ�

	int time;												///< �ð�       ����:HHMMSS

	int cur_price;											///< ���簡
	int volume;												///< �ŷ���

	short jang;												///< �屸��, 1: ���� ����ȣ�� 3: ���� 5:�ð��� ����
    int filler[4];
} SHA_SISE_PACKET;

typedef struct _sha_detail
{
	int vol;
    void *order_info;							        ///< ��ü�� �ֹ����� ��ũ (�ֹ� ������ ���) SHA_MICHE_INFO *�� ����ȯ�ؼ� ���
	union {											        ///< �ֹ��ܷ�
		int seq_no;
    	int time;												///< �ü���Ŷ �ð�
	};
} SHA_DETAIL;

typedef struct _sha_index
{
	int price;												///< ����
	SHA_DETAIL detail[MAX_DETAIL];							///< ���� ȣ������ ��
	int qty;												///< ȣ�� ���� ����(�Ǽ�)
	int vol;												///< ȣ�� ���� �հ�(�ܷ���)
	int chegyul;											///< ü��
	int cancel;												///< ���
	int add;												///< �߰�(�ű�)
	int gubun;												///< 1:�ŵ�ȣ�� -1:�ż�ȣ��
	int not_anal_flag;										///< �̺м��ܷ��� �ֳ�?
	int not_anal_vol;										///< �̺м��ܷ�
	short update_flag;									   	///< ���ſ���
	short sb_che_flag;									   	///< ���ſ���
	int org_vol;											///< ȣ���� ��Ƹ��� ü���ϰ�� ����
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
    int	code;							/*//< �����ڵ� */
	int time;							/*//< ����ð� */
	int count;							/*//< Sequence Number*/
	int cur_price;						/*//< ���簡 */
	int gubun;							/*//< �ŵ�, �ż� ���� (SHA_MEDO, SHA_MESU) */
	int price;							/*//< ���� */
	short hoga;							/*//< ȣ����ġ (1ȣ�� 2ȣ�� .. 10ȣ��) */
	short io_gubun;						/*//< �ű�, ���, ü�ᱸ��  (0: �ű�  1: ��� 2: ü��) */
	int vol;							/*//< ���� */
} SHA_EVENT;

#endif


