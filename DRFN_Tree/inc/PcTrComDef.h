#ifndef _PCTR_STATE_HEADER__20060220__
#define _PCTR_STATE_HEADER__20060220__

// #include "PcTrComDef.h"

// NotifyPCTrState(WPARAM,) 에 들어갈 내용.
enum
{
	NotifyPCTrW_AppState=1,
};

// NotifyPCTrState(,LPARAM) 에 들어갈 내용.
enum 
{
	PCTrMng_InitInstance=0,
	PCTrMng_ExitInstance,
	PCTrMng_MainCreate=20,
	PCTrMng_MainDestroyStart,
	PCTrMng_MainDestroyMiddle,
	PCTrMng_MainDestroyEnd,
	//PCTrMng_MainReCreate,
	PCTrMng_UserState=100,
};

#endif // _PCTR_STATE_HEADER__20060220__
