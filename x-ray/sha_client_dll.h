#ifndef sha_client_dll_h
#define sha_client_dll_h

                 
#include "sha_client.h"

#define DLL_EXPORT   __declspec(dllimport)

namespace sha_client
{

extern "C"
{
// �ش� ������ ȣ���м� ����
DLL_EXPORT int  _sha_create(int code, SHA_DATA * server_sha_data);

// �ش� ������ ȣ���м� ����
DLL_EXPORT int  _sha_create_dummy(int code);

// �ش� ������ ȣ���м� ����
DLL_EXPORT int  _sha_create_by_handle(int code, void *handle);

//������ ���� �޾ƿ� ȣ���м� �ڷḦ ����
DLL_EXPORT void  _sha_set(int code, SHA_DATA *server_sha_data);

//���� ȣ���м� ����
DLL_EXPORT int  _sha_delete(int code);

//�ش� �ڵ��� ���� ȣ���м� ����
DLL_EXPORT int  _sha_delete_by_handle(int code, void *handle);

//�ش� ������ ȣ���м��� �����ϴ��� ���� ( 0 ����, 1 ����)
 DLL_EXPORT int  _sha_is_exist(int code);

//�ش� ������ ȣ���м��� �����ϴ��� ���� ( 0 ����, 1 ����)
 DLL_EXPORT int  _sha_is_exist_by_handle(int code, void *handle);

//���� ȣ���м� �����͸� ������ �Լ�
 DLL_EXPORT SHA_DATA * _sha_get(int code);

//���� ȣ���м� �����͸� ������ �Լ� (���� : ����Ʈ ����)
 DLL_EXPORT int  _sha_get_handle_list(int code,int *plist);

//������ Ư�������� ȣ���м� ����
 DLL_EXPORT SHA_PRICE  * _sha_get_price(int code, int price);

//���͵� ������ ȣ������ ����
 DLL_EXPORT void  _sha_get_power(int code, int filter, SHA_POWER *sha_power);

 DLL_EXPORT void  _sha_get_power_range(int code, int filter, int range, SHA_POWER *sha_power);

//����ü���� ������ ȣ���м� ����
 DLL_EXPORT int  _sha_get_prv_chegyul_detail(int code, int filter, int gubun, SHA_DETAIL  *sha_detail);


//���� ���� ���
 DLL_EXPORT int  _sha_io_create(int code, int filter, void *handle);

//���� ���� ����
 DLL_EXPORT void  _sha_io_delete(int code, int filter, void *handle);

//���� ���� ������ �ޱ�
 DLL_EXPORT SHA_IO *  _sha_io_get(int code, int filter, void *handle);

//Ư�� ������ ���� ���� ������ �ޱ�
 DLL_EXPORT SHA_IO_PRICE *  _sha_io_get_price(int code, int filter, void *handle, int price);

//���� ���� �� �ű� �ֹ��� ����Ʈ ������ �ޱ�
 DLL_EXPORT SHA_IO_NEW *  _sha_io_get_new(int code, int filter, void *handle);

//���� ���� �� ��� �ֹ��� ����Ʈ ������ �ޱ�
 DLL_EXPORT SHA_IO_CANCEL *  _sha_io_get_cancel(int code, int filter, void *handle);

//���� ���� �� ���� �ֹ��� ����Ʈ ������ �ޱ�
 DLL_EXPORT SHA_IO_JJ *  _sha_io_get_jj(int code, int filter, void *handle);

//���� ���� �� �ű԰����� ��Ұ��� ����..
//sha_io_power�� filter�� range�� �� ä���� �־���Ѵ�...
//range�� 0�̸� ��ü �������� �ν�
DLL_EXPORT int  _sha_io_get_power(int code, int filter, void *handle, SHA_IO_POWER *sha_io_power);



//ü������ �Է�
 DLL_EXPORT void  _sha_set_sise(SHA_SISE_PACKET *ssp);

//ȣ������ �Է�
 DLL_EXPORT void  _sha_set_hoga(SHA_HOGA_PACKET *shp);

// ǥ���ڵ带 �������ڵ�� ��ȯ     market_tag :  �ŷ��� '1' �ڽ��� '2'
// ��> A005930 -> 10059300
 DLL_EXPORT int  _sha_code_conv(char *code_str, char market_tag);



// ��ü�� ����Ʈ �Է�
 DLL_EXPORT void  _sha_set_miche(char *account, int list_cnt, SHA_MICHE_INFO *sha_miche_info);

// ��ü�� ����Ʈ ������ ����
 DLL_EXPORT SHA_MICHE_INFO *  _sha_get_miche(char *account, int order_no);

// �ش� ������ ��ü�� ����Ʈ ������ ���� (������ ��ũ)(�ִ� 100��)
 DLL_EXPORT int  _sha_get_miche_account(char *account, SHA_MICHE_INFO **miche_info_list);


// �ǽð� ����, ü�� Ȯ�� �Է�
 DLL_EXPORT void  _sha_set_real(SHA_REAL_INFO *sha_real_info);
// �ֹ����� �Է� (�ֹ���)
 DLL_EXPORT void  _sha_set_order(SHA_ORDER_INFO *sha_order_info);
// �ֹ���ȣ �Է� (�ֹ���ȣ ������)
 DLL_EXPORT void  _sha_set_jubsu(SHA_JUBSU_INFO *sha_jubsu_info);


// ����� ���� : flag = 1   ���� flag = 0
 DLL_EXPORT void  _sha_set_debug(int code, int flag);
 DLL_EXPORT void  _sha_set_logging(int code, int filter, void *handle, int flag);

// �ֹ���ȣ�� �̿��� �ش� SHA_PRICE*�� �޴´�.
// trace���� ���
 DLL_EXPORT SHA_PRICE *  _sha_get_price_by_orderno(char *account, int ord_no);

// �ֹ���ȣ�� �̿��� �ش� SHA_DETAIL*�� �޴´�.
// trace���� ���
 DLL_EXPORT SHA_DETAIL *   _sha_get_detail_by_orderno(char *account, int ord_no);

// �־��� ������ ǥ���� �� �ִ� �ִ� ���Ͱ��� �����Ѵ�.
// num�� �ִ��  10
 DLL_EXPORT int  _sha_get_max_filter(int code, int num);


// ü���� ǥ�ø� ���� (���ֹ����� ���ֹ� ��������)
// remain ��  SHA_REMAIN_ORDER_VOL remain���� �����Ͽ� &remain���� �Է°����� �Ѱ��ش�.
// remain�� ������ ä���� ����
DLL_EXPORT void  _sha_get_remain_order_vol(SHA_PRICE *sha_price, SHA_MICHE_INFO *pMiche, SHA_REMAIN_ORDER_VOL *remain);

// ü���� ǥ�ø� ���� (���ֹ����� ���ֹ� ��������)
// remain ��  SHA_REMAIN_ORDER_VOL remain[20]���� �����Ͽ� �Է°����� �Ѱ��ش�.
// remain�� ������ ä���� ����
DLL_EXPORT int  _sha_get_remain_order_vol_array(char *account, int code, SHA_REMAIN_ORDER_VOL *remain);

// remain ��  SHA_REMAIN_ORDER_VOL remain���� �����Ͽ� &remain���� �Է°����� �Ѱ��ش�.
// remain�� ������ ä���� ����
DLL_EXPORT int  _sha_get_remain_order_vol_by_orderno(char *account, int ord_no, SHA_REMAIN_ORDER_VOL *remain);


// compare�� �� ����(��:100, 300, 700, 1000), �ݵ�� ������������  �����ؼ� ���� ��
// cnt�� �񱳼��� ���� (��:4)
// ������ sha_dist�� ä���� ������
// cnt+1���� ���ϵ� cnt+���� �� �̻��� ����
// ���ϰ��� sdis�� ������ (cnt+1), �����ϰ�� 0����
DLL_EXPORT int  _sha_get_distribution(int code, int *comp_unit, int cnt, SHA_DISTRIBUTION *sha_dist);


// list�� ������������... �� �ֽ��� 0����.
// �ݵ�� sha_io_create �Ŀ� �ٷ� ����ؾ���... (�����Ⱑ �� ������ ����)
// ������ ������ ������ ������� ����...(�űԿ� ��ҷ� ��)
// code�� filter�� ������ ���� �������� ���õ�....
DLL_EXPORT void   _sha_io_set(int code, int filter, int cnt, SHA_EVENT * plist);

// ���°��� ���� (%�� ����)
DLL_EXPORT int  _sha_get_power_ratio(int code, int filter);
DLL_EXPORT int	_sha_get_power_range_ratio(int code, int filter, int range);

//  ���Ⱝ�� ���� (%�� ����)
DLL_EXPORT int  _sha_get_io_power_ratio(int code, int filter, void *handle);

// ü�ᰭ�� ���� (%�� ����)
DLL_EXPORT int  _sha_get_ch_power_ratio(int code, int filter, void *handle);

// ��ü�� ����Ʈ ����
DLL_EXPORT void  _sha_clear_miche(char *account);


}
}

using namespace sha_client;

#endif
