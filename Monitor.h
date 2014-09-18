// Monitor.h: interface for the CMonitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITOR_H__88E2D2C5_26EC_43F8_BD44_1EEB49D5AE09__INCLUDED_)
#define AFX_MONITOR_H__88E2D2C5_26EC_43F8_BD44_1EEB49D5AE09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMonitor  
{
public:
	CMonitor();
	virtual ~CMonitor();

public:
	CRect GetDesktopRect( LPPOINT ppt );
	CRect GetDesktopRect( LPRECT prc );
	CRect GetMonitorRect(CPoint& point);
	CRect GetMonitorRect(int index);
	int	GetMonitorCount();
	int GetDualPosition(CPoint point);
	int  GetWorkArea(CRect *rc);
};

#endif // !defined(AFX_MONITOR_H__88E2D2C5_26EC_43F8_BD44_1EEB49D5AE09__INCLUDED_)
