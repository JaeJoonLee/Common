#pragma once
/*
구간에 대한 로그를 찍는 함수들.



BEGIN_LOG(test,1); //test = 레이블, 1 = 타이머 아이디(중첩될 수 있음)

BEGIN_LOG(inner_span,2);
END_LOG(inner_span,2);

END_LOG(test,1);

_TIME_LOG 전처리기에 넣으면 작동되며, 전처리기에서 빼면 
#define BEGIN_LOG(name,id) __noop; 식으로 확장되기 때문에 생성되는 코드에는 영향이 없다.

이종희
*/

#define _TIME_LOG_MILLISEC

#ifdef _TIME_LOG

#define _HEADER_ONLY_TIMER
#include "PerfTimer.h"
using namespace std;
#include <vector>

static CString g_logpath_timer = "C:\\TimerLog\\";

typedef struct pair<long,CPerfTimerT*> TIMER_PAIR;
static vector<TIMER_PAIR> g_timerVec;

class CTimerVec
{
public:
	CTimerVec(){};
	//static 오브젝트의 소멸자를 사용해서 클리어 함.
	virtual ~CTimerVec()
	{
		vector<TIMER_PAIR>::const_iterator it = g_timerVec.begin();
		while(it != g_timerVec.end())
		{
			delete (*it).second;
			it++;
		}	
		g_timerVec.clear();
	}

};
static CTimerVec g_vec;


//서로 다른 쓰레드에서 콜을 할 경우를 생각해야 하기 때문에. 
inline CPerfTimerT* get_timer(long id)
{
	vector<TIMER_PAIR>::const_iterator it = g_timerVec.begin();
	while(it != g_timerVec.end())
	{
		if( (*it).first == id)
			return (*it).second;

		it++;
	}

	TIMER_PAIR tPair = make_pair(id,new CPerfTimerT() );
	g_timerVec.push_back(tPair);
	return tPair.second;
}

inline bool close_timer(long id)
{
	vector<TIMER_PAIR>::const_iterator it = g_timerVec.begin();
	while(it != g_timerVec.end())
	{
		if( (*it).first == id)
		{
			delete (*it).second;
			g_timerVec.erase(it);
			return true;
		}
		it++;
	}

	return false;
}

inline void _begin_log(CString logName,int timerID)
{
	CPerfTimerT* pTimer = get_timer(timerID);
	pTimer->Start(TRUE);
}

inline void _end_log(CString logName,int timerID)
{
	CPerfTimerT* pTimer = get_timer(timerID);
	pTimer->Stop();
	//long threadID = ::GetCurrentThreadId();
	CString strLog;
	strLog.Format("%s(%d) = %f 걸림",logName,timerID,pTimer->Elapsed());
	close_timer(timerID);
	
	CString strFilePath;
	CString strLogTime;
	FILE* fp;
	strFilePath.Format("%s%s.log",g_logpath_timer,"timer_log");
	bool bExist = false;
	if (fopen_s(&fp, strFilePath, "r") == 0) //file not exist
	{
		bExist = true;
		fclose(fp);
		fp = NULL;
	}
	if(bExist) //logfile is preExist, write log at the end of the file.
	{
		if (fopen_s(&fp, strFilePath, "a+") != 0)
			return;
	}
	else //logfile is not exist, create new file.
	{
		if (fopen_s(&fp, strFilePath, "w+") != 0)
			return;
	}

#ifdef _TIME_LOG_MILLISEC
	SYSTEMTIME systime;
	GetLocalTime (&systime);
	strLogTime.Format("[%u/%02u/%02u %02u:%02u:%02u-%03u]     ",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);
#else
	COleDateTime time;
	time = COleDateTime::GetCurrentTime();
	strLogTime = time.Format("[%y/%m/%d %H:%M:%S]	");
#endif

	fwrite(strLogTime.GetBuffer(0), sizeof(char), strLogTime.GetLength(), fp);
	fwrite(strLog.GetBuffer(0), sizeof(TCHAR), strLog.GetLength(), fp);
	fwrite("\n", sizeof(char), strlen("\n"), fp);

	fclose(fp);
}

inline void _write_dummy(CString msg,CString logfile = "")
{
	CString strFilePath;
	CString strLogTime;
	FILE* fp;
	
	if(logfile == "")
		strFilePath.Format("%s%s.log",g_logpath_timer,"timer_log");
	else
		strFilePath = logfile;

	bool bExist = false;
	if (fopen_s(&fp, strFilePath, "r") == 0) //file not exist
	{
		bExist = true;
		fclose(fp);
		fp = NULL;
	}
	if(bExist) //logfile is preExist, write log at the end of the file.
	{
		if (fopen_s(&fp, strFilePath, "a+") != 0)
			return;
	}
	else //logfile is not exist, create new file.
	{
		if (fopen_s(&fp, strFilePath, "w+") != 0)
			return;
	}


#ifdef _TIME_LOG_MILLISEC
	SYSTEMTIME systime;
	GetLocalTime (&systime);
	strLogTime.Format("[%u/%02u/%02u %02u:%02u:%02u-%03u]     ",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);
#else
	COleDateTime time;
	time = COleDateTime::GetCurrentTime();
	strLogTime = time.Format("[%y/%m/%d %H:%M:%S]	");
#endif

	fwrite(strLogTime.GetBuffer(0), sizeof(char), strLogTime.GetLength(), fp);
	fwrite(msg.GetBuffer(0), sizeof(TCHAR), msg.GetLength(), fp);
	fwrite("\n", sizeof(char), strlen("\n"), fp);

	fclose(fp);
}

#define BEGIN_LOG(name,id) _begin_log(#name,id);
#define END_LOG(name,id) _end_log(#name,id);
#define DUMMY_LOG(msg) _write_dummy(msg);
#define DUMMY_LOG2(msg,path) _write_dummy(msg,path);
#define SET_PATH_TLOGGER(path) g_logpath_timer = path;
#else

#define BEGIN_LOG(name,id) __noop;
#define END_LOG(name,id) __noop;
#define DUMMY_LOG(msg) __noop;
#define DUMMY_LOG2(msg,path) __noop;
#define SET_PATH_TLOGGER(path) __noop;

#endif