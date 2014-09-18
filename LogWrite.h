#pragma once
/*
������ ���� �α׸� ��� �Լ���.



BEGIN_LOG(test,1); //test = ���̺�, 1 = Ÿ�̸� ���̵�(��ø�� �� ����)

BEGIN_LOG(inner_span,2);
END_LOG(inner_span,2);

END_LOG(test,1);

_TIME_LOG ��ó���⿡ ������ �۵��Ǹ�, ��ó���⿡�� ���� 
#define BEGIN_LOG(name,id) __noop; ������ Ȯ��Ǳ� ������ �����Ǵ� �ڵ忡�� ������ ����.

������
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
	//static ������Ʈ�� �Ҹ��ڸ� ����ؼ� Ŭ���� ��.
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


//���� �ٸ� �����忡�� ���� �� ��츦 �����ؾ� �ϱ� ������. 
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
	strLog.Format("%s(%d) = %f �ɸ�",logName,timerID,pTimer->Elapsed());
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