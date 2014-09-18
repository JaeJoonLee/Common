// proMDefense.h: interface for the CproMDefense class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROMDEFENSE_H__A50E942B_0DF9_40B4_9684_85588DF847E0__INCLUDED_)
#define AFX_PROMDEFENSE_H__A50E942B_0DF9_40B4_9684_85588DF847E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef BOOL (*PROCPROINIT)();
typedef BOOL (*PROCPROSENDDEVICE)( DWORD Flag , DWORD pid, DWORD dwPolicy, char * szProcName );
typedef DWORD (*DWORDPROCPROINIT)();
typedef DWORD (*DWORDPROCPROSENDDEVICE)( DWORD Flag , DWORD pid, DWORD dwPolicy, char * szProcName );


#define PP_SET_HOOK		  25
#define PP_SET_UNHOOK	  26
#define PP_INSERT_PID		5
#define PP_DELETE_PID		6
#define PP_INSERT_NAME		15
#define PP_DELETE_NAME		16
#define PP_SET_ERRMSG		30
#define PP_SET_THREADCHECK	31

#define ERR_PROM_SUCCESS		0x00000001		// 성공	
#define ERR_PROM_RESOURCE		0x00000002		// ProMDefense 의 Resource 문제
#define ERR_PROM_UNKNOWN_OS		0x00000003		// 알수 없는 OS ( 지원 가능 OS : 2000, 2003, XP, Vista, Win7 32bit )
#define ERR_PROM_AUTH			0x00000004		// 윈도우 권한 에러 ( 프로그램에 권한이 없음 )
#define ERR_PROM_FILE_NOT_FOUND	0x00000005		// 드라이버 파일을 찾지 못함
#define ERR_PROM_NOT_INIT		0x00000006		// 정상적으로 Init 이 완됨

class CproMDefense  
{
public:
	
	DWORD Set_Protect_CheckThread();
	DWORD Set_Protect_MSG(DWORD dwPolicy);
	DWORD Delete_Protect_PID(DWORD dwPID);
	DWORD Insert_Protect_PID(DWORD dwPID);
	DWORD End_ProMDefense();
	DWORD Ready_ProMDefense();
	CproMDefense();
	virtual ~CproMDefense();
protected:
	HMODULE m_hproMDefense;
	PROCPROINIT m_ProcDefense_Init;
	PROCPROSENDDEVICE m_ProcDefense_SendDevice;
	DWORDPROCPROINIT m_dwProcDefense_Init;
	DWORDPROCPROSENDDEVICE m_dwProcDefense_SendDevice;
};

#endif // !defined(AFX_PROMDEFENSE_H__A50E942B_0DF9_40B4_9684_85588DF847E0__INCLUDED_)
