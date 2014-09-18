#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef WIN32
#ifndef  WINAPI
#define WINAPI __stdcall
#endif
#ifdef __XECURELIB__
#define XECURE_API __declspec(dllexport)
#else
#define XECURE_API __declspec(dllimport)
#endif
#else
#define WINAPI
#define XECURE_API 
#endif

#define XECURE_DUMP				1  /* data_dump() 함수 동작 시킴 */
#define XECURE_DEBUG			2  /* debug_out() 함수 동작 시킴 */	
#define XECURE_LOG				4  /* log_out() 함수 동작 시킴  */ 

#ifdef  __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 함수이름 : TurnOnDefenceOption
 설명     : 데이터 덤프 옵션을 켜거나 끈다. 
			Xecure 함수의 입력 값을 조사하기 위해 사용하는 함수 
			최초 상태는 데이터 덤프 옵션이 꺼진 상태 
			한번 호출 시마다 데이터 덤프 옵션이 바뀐다. 
			이 함수는 data_dump()함수와 함께 사용된다. 
			(참고) 스레프 세이프 하지 않음 
 리턴 값  : void 
 입력     : int fOpt
				XECURE_DUMP				1  - data_dump() 함수 동작 시킴 
				XECURE_DEBUG			2  - debug_out() 함수 동작 시킴 	
				XECURE_LOG				4  - log_out() 함수 동작 시킴   
 입력     : char *pPath -  XECURE_LOG 옵션 선택시 로그 파일의 패스
						   XecureGate Log File Path+name 
------------------------------------------------------------------------- */
XECURE_API void WINAPI TurnOnDefenceOption(int fOpt, const char *pPath);


/* -------------------------------------------------------------------------
 함수이름 : data_dump
 설명     : 데이터를 덤프 출력하는 함수 
			ToggleDump() 함수를 켠 경우 입력 데이터를 플랫폼에 따라 
			DBWIN 또는 stdout에 출력한다. 
 리턴 값  : void 
 입력     : char *pDataName - 입력한데이터의 이름 
 입력     : unsigned char *pData - 덤프하고자 하는 데이터의 포인터 
 입력     : int nLen - 덤프하고자 하는 데이터의 크기 
------------------------------------------------------------------------- */
XECURE_API void WINAPI data_dump(char *pDataName, unsigned char *pData, int nLen);

/* -------------------------------------------------------------------------
 함수이름 : debug_out
 설명     : 디버그를 위한 함수, 
			플랫폼에 따라 DBWIN 또는 stdout에 데이터를 출력한다. 
 리턴 값  : void 
 입력     : char* lpszFmt
 입력     : ...
------------------------------------------------------------------------- */
XECURE_API void debug_out(char* lpszFmt, ...);
XECURE_API void log_out(char* lpszFmt, ...);

#ifdef  __cplusplus
}
#endif


#endif  /* _DEBUG_H */



