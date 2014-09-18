/************************************
  REVISION LOG ENTRY
  Revision By: ����ȣ
  Revised on 99-05-14 ���� 4:26:02
  Comments: Xecure Library�� ������ �������� �����ϴ� ��� 
                        (����)  ������ ������ ����� ����ϱ� ���ؼ��� �ݵ�� 
                                        USE_THREAD�� ������ ����� ���� �ؾ� �Ѵ�. 
 ************************************/

#ifndef _THREADSAFE_H
#define _THREADSAFE_H

#ifdef  __cplusplus
extern "C" {
#endif

/* type defintions for using type in CRYPTO_CODE[UN]LOCK() macro {{ */
/*      ���ο� ���ؽ��� �߰��� ��� ���ο� ���ǹ��� �ϳ� ������ 
        CRYPTO_NUM_LOCKS ���ڸ� ���� ��Ų��.  �׸��� ThreadSafe.c���� 
        �߰��� ���ؽ� ��Ʈ���� ��� �Ѵ�. (������� ���� ����)        
        �׸��� ������ �ݵ�� 0 ���� �ؾ� �Ѵ�. */
        
#define CRYPTO_LOCK_RAND                                0
#define CRYPTO_LOCK_RC5                                 1
#define	CRYPTO_LOCK_RAND_SEED							2
/* }} */

#define CRYPTO_NUM_LOCKS                                3

#define CRYPTO_LOCK                                     1
#define CRYPTO_UNLOCK                                   2

#ifdef USE_THREAD
#define CRYPTO_CODE_LOCK(type)  CRYPTO_lock(CRYPTO_LOCK,type,__FILE__,__LINE__)
#define CRYPTO_CODE_UNLOCK(type)        CRYPTO_lock(CRYPTO_UNLOCK,type,__FILE__,__LINE__)
#else
#define CRYPTO_CODE_LOCK(type)  
#define CRYPTO_CODE_UNLOCK(type)
#endif /* USE_THREAD  */

#ifdef USE_THREAD
void CRYPTO_lock(int mode, int type,char *file,int line);

void thread_setup();
void thread_cleanup();

/* kichang yang */
#ifdef WIN32
#define THREAD_STRTOK
#else
#define THREAD_STRTOK   char * track100605
#define strtok(a, b) strtok_r(a, b, &track100605)
#endif
/* end of kichang yang */

#else
#define thread_setup()
#define thread_cleanup()
#define THREAD_STRTOK
#endif /* USE_THREAD  */

#ifdef  __cplusplus
}
#endif

#endif /* _THREADSAFE_H */



