#ifndef sha_client_h
#define sha_client_h

                 
#include "sha.h"

#define SHA_NEW   	1										/// �ŵ�, �ż� �ֹ�
#define SHA_JJ      2										/// ���� �ֹ�
#define SHA_CANCEL  3										/// ��� �ֹ�

#define SHA_MEDO    1										/// �ŵ�
#define SHA_MESU   -1										/// �ż�

typedef struct 
{
	int price;							///< �ش� ����
	int vol;							///< �� �ֹ� ���� �� �ֹ� ����
	int qty;						    ///< ���ֹ� ���� �Ǽ�
} SHA_REMAIN_ORDER_VOL;

typedef struct
{
	int price;							///< �ش� ����
	int gubun;							///< �ż��ŵ�����
	int org_vol;						///< ȣ���ܷ�
	int power_vol;						///< ������
	double ratio;						///< ���� (������/�ܷ� * 100)
} SHA_POWER_SUB ;

typedef struct 
{
	int code;							///< �����ڵ�
	int filter;							///< ����
	SHA_POWER_SUB  power[20];			///< ���ݴ뺰 ���� ��������
	SHA_POWER_SUB  medo_total_power;	///< �Ѹŵ�(10ȣ��)�ܷ� ��� �� ��������
	SHA_POWER_SUB  mesu_total_power;	///< �Ѹż�(10ȣ��) �ܷ� ��� �� ��������
} SHA_POWER;

typedef struct 
{
	int 			gubun;				///<�ż�, �ŵ����� (SHA_MEDO, SHA_MESU)
	int				time;				///< ���� �ð�
	int				vol;				///<���� (�߰�+, ���� -)
    int             subseq;             ///< ���� ��ȣ
} SHA_IO_PRICE_SUB;

typedef struct
{
    int			code;					///< �����ڵ�
    int			price;					///< �����ڵ�
    int			filter;					///< ���� ��
	int 		cnt;					///< ����
	SHA_IO_PRICE_SUB	data[100];		///< ����� ����
} SHA_IO_PRICE;

typedef struct
{
	int time;							///< ����ð�
	int gubun;							///< �ŵ�, �ż� ���� (SHA_MEDO, SHA_MESU)
	int price;							///< ����
	int hoga;							///< ȣ����ġ (1ȣ�� 2ȣ�� .. 10ȣ��)
	int vol;							///< �űԼ���
    int subseq;                         ///< ���� ��ȣ
} SHA_IO_NEW_SUB;

typedef struct
{
    int			code;					///< �����ڵ�
    int			filter;					///< ���� ��
	int 		cnt;					///< ����
	SHA_IO_NEW_SUB	data[100];			///< �ű� ����
} SHA_IO_NEW;


typedef struct
{
	int time;							///< ����ð�
	int gubun;							///< �ŵ�, �ż� ���� (SHA_MEDO, SHA_MESU)
	int price;							///< ����
	int hoga;							///< ȣ����ġ (1ȣ�� 2ȣ�� .. 10ȣ��)
	int vol;							///< ��Ҽ���
    int             subseq;             ///< ���� ��ȣ
} SHA_IO_CANCEL_SUB;

typedef struct
{
    int			code;					///< �����ڵ�
    int			filter;					///< ���� ��
	int 		cnt;					///< ����
	SHA_IO_CANCEL_SUB	data[100];		///< ��� ����
} SHA_IO_CANCEL;


typedef struct 
{
	int time;							///< ����ð�
	int gubun;							///< �ŵ�, �ż� ���� (SHA_MEDO, SHA_MESU)
	int from_price;						///< ���� �� ����
	int from_hoga;						///< ���� �� ȣ����ġ (1ȣ�� 2ȣ�� .. 10ȣ��)
	int to_price;						///< ���� �� ����
	int to_hoga;						///< ���� �� ȣ����ġ (1ȣ�� 2ȣ�� .. 10ȣ��)
	int vol;							///< ��������
    int subseq;                         ///< ���� ��ȣ
} SHA_IO_JJ_SUB;

typedef struct
{
    int			code;					///< �����ڵ�
    int			filter;					///< ���� ��
	int 		cnt;					///< ����
	SHA_IO_JJ_SUB	data[100];		    ///< ���� ����
} SHA_IO_JJ;

typedef struct
{
    int				code;					///< �����ڵ�
    int				filter;					///< ���� ��

	SHA_IO_NEW		sha_io_new;				///< �ű�
	SHA_IO_CANCEL	sha_io_cancel;				///<���
	SHA_IO_JJ		sha_io_jj;					///< ����
	SHA_IO_PRICE 	price[SHA_RANGE];		///< �� ���ݺ� ���⳻��
} SHA_IO;

typedef struct
{
    int medo_sum;       ///< �ŵ���
    int medo_qty;       ///< �ŵ� ����
    int mesu_sum;       ///< �ż���
    int mesu_qty;       ///< �ż� ����
    double ratio;       ///< �ŵ���/�ż���*100 
} SHA_IO_POWER_SUB;

typedef struct
{
    int				code;					///< �����ڵ�
    int				filter;					///< ���� ��
    int				range;					///< ���� (0:��ü 1:1ȣ�� 2: 1~2ȣ��  3:1~3ȣ��)

    SHA_IO_POWER_SUB          new_power;
    SHA_IO_POWER_SUB          cancel_power;           ///< �ŵ�/�ż�*100 ��Ұ���
} SHA_IO_POWER;

typedef struct tagSHA_ORDER_TRACE_INFO
{
    int status;         // 0 HogaMudule�� ������� ����, 1 : HogaMudule�� �����   2: �����Ұ��� ��Ȳ(���� ���۵� ���� �ʴ´�....)
    int gubun;          // 0 �м� �����, 1 ��ġ ���� 2 ��ġ����, 3 �м��Ҵ�   4 ü�����
    int start_seq_no;   // �ֹ����� ȣ�� ������
    int presumption_seq_no;   // �����ȵ� ȣ�� ������ (����)
    int capture_seq_no;      // ������ ȣ�� ������ (����)

    SHA_DATA *sha_data;

    int filler[5];

} SHA_ORDER_TRACE_INFO;

typedef struct
{
    char account[17];
    int jong_code;			// �����ڵ�
    int org_ord_no;			// ���ֹ���ȣ
    int ord_no;				// �ֹ���ȣ
    int order_gubun;        // 1 �ż�, 2 �ŵ�
    char buy_sell_tp[5];	// �ŵ��ż����� ("�ż�", "�ŵ�")
    int order_price;		// �ֹ�����
    int order_qty;			// �ֹ�����
    int che_remn_qty;   	// ü���ܷ�
    char rcv_tp[5];			// ��������
    int rcv_time;			// �����ð� mmhhss

    int seq_no;                     // ���� ��ȣ
    SHA_ORDER_TRACE_INFO * trace;   // �ֹ���������
} SHA_MICHE_INFO;

typedef struct
{
    char account[17];
    char gubun[5];          // "����", "Ȯ��", "ü��" , "�ź�"
    int jong_code;			// �����ڵ�
    int order_gubun;        // 1 �ż�, 2 �ŵ�, 3 ����, 4 ���
    int org_ord_no;			// ���ֹ���ȣ
    int ord_no;				// �ֹ���ȣ
    char buy_sell_tp[5];	// �ŵ��ż����� ("�ż�", "�ŵ�")
    int order_price; 		// �ֹ�(����)����
    int order_qty;	 		// �ֹ�(����, ���)����
    int che_price;	 		// ü�ᰡ��

    int che_qty; 	 		// ü�����
    int che_remn_qty;		// ü���ܷ�

    int org_order_price;	// ���ֹ� ����
    int org_order_qty;		// ���ֹ� ����

    int jj_qty;  			// ����(���) Ȯ�μ���
    char rcv_tp[5];			// �������� ("����", "ü��", "Ȯ��", "�ֹ�", "�ź�")
    int rcv_time;			// �����ð� mmhhss
} SHA_REAL_INFO, SHA_ORDER_INFO, SHA_JUBSU_INFO;

typedef struct
{
    int medo_vol;           // �ŵ� ������
    int medo_qty;           // �ŵ� �Ǽ�
    int mesu_vol;           // �ż� ������
    int mesu_qty;           // �ż� �Ǽ�
} SHA_DISTRIBUTION;


#endif
