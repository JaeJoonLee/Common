// SystemInfo.h: interface for the CSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMINFO_H__8CA3C8BE_55F8_4B2A_AE95_C97AEAC8EC99__INCLUDED_)
#define AFX_SYSTEMINFO_H__8CA3C8BE_55F8_4B2A_AE95_C97AEAC8EC99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSystemInfo  
{
public:
	CSystemInfo();
	virtual ~CSystemInfo();

public:
	void	GetSystemInfo();

	CString GetOSName();
	CString GetOSVersion();
	CString GetTotalMem();
	CString GetFreeMem();
	CString GetVtTotalMem();
	CString GetVtFreeMem();
	CString GetTotalDiskSpace();
	CString GetFreeDiskSpace();
	CString GetCPU();
	CString GetSendServerData(int nType=0);

private:
	CString m_strOSName;
	CString m_strOSVersion;
	CString m_strTotalMemory;
	CString m_strFreeMemory;
	CString m_strVTotalMemory;
	CString m_strVFreeMemory;
	CString m_strTotalDiskSpace;
	CString m_strFreeDiskSpace;
	CString m_strCPU;

	void GetOSInfo(OSVERSIONINFO* pOS);
	CString	ByteToStr(double nByteCount);
	void	GetSystemMemory();
	void	GetSystemDisk();
	void	GetSystemCPU();
};

#endif // !defined(AFX_SYSTEMINFO_H__8CA3C8BE_55F8_4B2A_AE95_C97AEAC8EC99__INCLUDED_)
