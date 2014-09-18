/************************************
  REVISION LOG ENTRY
  Revision By: 차정호
  Revised on 99-05-14 오후 4:26:02
  Comments: Xecure Library의 스레드 세이프를 지원하는 헤더 
                        (주의)  스레드 세이프 기능을 사용하기 위해서는 반드시 
                                        USE_THREAD를 기정의 상수로 선언 해야 한다. 
 ************************************/

#ifndef _THREADSAFE_H
#define _THREADSAFE_H

#ifdef  __cplusplus
extern "C" {
#endif

/* type defintions for using type in CRYPTO_CODE[UN]LOCK() macro {{ */
/*      새로운 뮤텍스를 추가할 경우 새로운 정의문을 하나 더쓰고 
        CRYPTO_NUM_LOCKS 숫자를 증가 시킨다.  그리고 ThreadSafe.c에서 
        추가된 뮤텍스 스트링을 등록 한다. (디버깅을 위해 사용됨)        
        그리고 시작은 반드시 0 부터 해야 한다. */
        
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



