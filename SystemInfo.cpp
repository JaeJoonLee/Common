//******************************************************************/
//******************************************************************/
// All Rights Reserved. Copyright(c)   2006 (주)한국소리마치        /
//******************************************************************/
// File Name     : SystemInfo.cpp
// Function      : 서버에 보낼 사용자 PC정보 클래스	
// System Name   : NexRun
// Create        : BT.Jung , 2007/01/19
// Update        : 
// Comment       : 
//******************************************************************/
// SystemInfo.cpp: implementation of the CSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
typedef BOOL (WINAPI* PFNGETDISKFREESPACEEX)(LPCTSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemInfo::CSystemInfo()
{
	m_strOSName = "";
	m_strOSVersion = "";
	m_strTotalMemory = "";
	m_strFreeMemory = "";
	m_strVTotalMemory = "";
	m_strVFreeMemory = "";
	m_strTotalDiskSpace = "";
	m_strFreeDiskSpace = "";
	m_strCPU = "";
}

CSystemInfo::~CSystemInfo()
{

}

CString CSystemInfo::GetSendServerData(int nType)
{
	GetSystemInfo();

	CString strSystemInfo = _T(""), strTmp;
	switch(nType)
	{
	case 0:
	default:
		{
			strSystemInfo  = GetOSName() + "|";
			strSystemInfo += GetOSVersion() + "|";
			strSystemInfo += GetCPU() + "|";
			strSystemInfo += GetTotalMem() + "|";
			strSystemInfo += GetFreeMem() + "|";
			strSystemInfo += GetVtTotalMem() + "|";
			strSystemInfo += GetVtFreeMem() + "|";
			strSystemInfo += GetTotalDiskSpace() + "|";
			strSystemInfo += GetFreeDiskSpace();
		}
		break;
	}
	return strSystemInfo;
}

void CSystemInfo::GetSystemInfo()
{
	OSVERSIONINFOEX osvi;

	memset(&osvi, 0, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if(GetVersionEx((OSVERSIONINFO*)&osvi))
	{
		GetOSInfo((OSVERSIONINFO*)&osvi);
	}
	else
	{	
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

		if(GetVersionEx((OSVERSIONINFO*)&osvi)) 
		{
			GetOSInfo((OSVERSIONINFO*)&osvi);
		}
	}

	GetSystemMemory();

	GetSystemDisk();

	GetSystemCPU();
}

void CSystemInfo::GetSystemCPU()
{
	char szName[64] = {0};

   __asm
   {
      mov      eax, 0x80000002
      CPUID
      mov      DWORD PTR [szName+0],eax
      mov      DWORD PTR [szName+4],ebx
      mov      DWORD PTR [szName+8],ecx
      mov      DWORD PTR [szName+12],edx
      mov      eax, 0x80000003
      CPUID
      mov      DWORD PTR [szName+16],eax
      mov      DWORD PTR [szName+20],ebx
      mov      DWORD PTR [szName+24],ecx
      mov      DWORD PTR [szName+28],edx
      mov      eax, 0x80000004
      CPUID
      mov      DWORD PTR [szName+32],eax
      mov      DWORD PTR [szName+36],ebx
      mov      DWORD PTR [szName+40],ecx
      mov      DWORD PTR [szName+44],edx
   }

   m_strCPU = szName;
   m_strCPU.TrimLeft();
   m_strCPU.TrimRight();
}

void CSystemInfo::GetOSInfo(OSVERSIONINFO* pOS)
{
	CString strTemp;

	switch(pOS->dwPlatformId)
	{
	case VER_PLATFORM_WIN32_NT:
		if(pOS->dwMajorVersion <= 4)
		{
			m_strOSName += "Microsoft Windows NT";

			strTemp.Format("%d.%d ", pOS->dwMajorVersion, pOS->dwMinorVersion);
			m_strOSVersion += strTemp;
			m_strOSVersion += pOS->szCSDVersion;
			strTemp.Format("%d", (pOS->dwBuildNumber & 0xFFFF));
			m_strOSVersion += " Build(" + strTemp + ")";
		}

		if(pOS->dwMajorVersion == 5)
		{
			if(pOS->dwMinorVersion == 0)
				m_strOSName += "Microsoft Windows 2000";
			else if(pOS->dwMinorVersion == 1)
				m_strOSName += "Microsoft Windows XP";

			strTemp.Format("%d.%d ", pOS->dwMajorVersion, pOS->dwMinorVersion);
			m_strOSVersion += strTemp;
			m_strOSVersion += pOS->szCSDVersion;
			strTemp.Format("%d", (pOS->dwBuildNumber & 0xFFFF));
			m_strOSVersion += " Build(" + strTemp + ")";
		}
		if(pOS->dwMajorVersion == 6)
		{
			m_strOSName += "Microsoft Windows Vista";

			strTemp.Format("%d.%d ", pOS->dwMajorVersion, pOS->dwMinorVersion);
			m_strOSVersion += strTemp;
			m_strOSVersion += pOS->szCSDVersion;
			strTemp.Format("%d", (pOS->dwBuildNumber & 0xFFFF));
			m_strOSVersion += " Build(" + strTemp + ")";
		}
		break;

	case VER_PLATFORM_WIN32_WINDOWS:
		if(pOS->dwMajorVersion == 4 && pOS->dwMinorVersion == 0)
		{
			m_strOSName += "Microsoft Windows 95";

			if(pOS->szCSDVersion[1] == 'C')
				m_strOSVersion += "OSR2";
			else
				m_strOSVersion += pOS->szCSDVersion;

			strTemp.Format("%d.%d ", pOS->dwMajorVersion, pOS->dwMinorVersion);
			m_strOSVersion += strTemp;

			strTemp.Format("%d", (pOS->dwBuildNumber & 0xFFFF));
			m_strOSVersion += " Build(" + strTemp + ")";
		}

		if(pOS->dwMajorVersion == 4 && pOS->dwMinorVersion == 10)
		{
			m_strOSName += "Microsoft Windows 98";

			if(pOS->szCSDVersion[1] == 'A')
				m_strOSVersion += "SE";

			strTemp.Format("%d.%d ", pOS->dwMajorVersion, pOS->dwMinorVersion);
			m_strOSVersion += strTemp;

			strTemp.Format("%d", (pOS->dwBuildNumber & 0xFFFF));
			m_strOSVersion += " Build(" + strTemp + ")";
		}

		if(pOS->dwMajorVersion == 4 && pOS->dwMinorVersion == 90)
		{
			m_strOSName += "Microsoft Windows Me";
			
			strTemp.Format("%d.%d ", pOS->dwMajorVersion, pOS->dwMinorVersion);
			m_strOSVersion += strTemp;

			strTemp.Format("%d", (pOS->dwBuildNumber & 0xFFFF));
			m_strOSVersion += " Build(" + strTemp + ")";
		}
		break;

	case VER_PLATFORM_WIN32s:
		m_strOSName += "Microsoft Win32s";
		strTemp.Format("%d.%d ", pOS->dwMajorVersion, pOS->dwMinorVersion);
		m_strOSVersion += strTemp;

		strTemp.Format("%d", (pOS->dwBuildNumber & 0xFFFF));
		m_strOSVersion += " Build(" + strTemp + ")";
		break;
	}
}

void CSystemInfo::GetSystemMemory()
{
	MEMORYSTATUS m_stMemStatus;

	GlobalMemoryStatus(&m_stMemStatus);

	m_strTotalMemory = ByteToStr(m_stMemStatus.dwTotalPhys);
	m_strFreeMemory = ByteToStr(m_stMemStatus.dwAvailPhys);
	m_strVTotalMemory = ByteToStr(m_stMemStatus.dwTotalVirtual - 0x40000000);
	m_strVFreeMemory = ByteToStr(m_stMemStatus.dwAvailVirtual - 0x40000000);
}

void CSystemInfo::GetSystemDisk()
{
	HINSTANCE hModule = NULL;                     

	if((hModule = LoadLibrary("KERNEL32.DLL")) != NULL)
	{
		PFNGETDISKFREESPACEEX pDiskFreeSpaceEx = NULL;

		if((pDiskFreeSpaceEx = (PFNGETDISKFREESPACEEX)GetProcAddress(hModule, "GetDiskFreeSpaceExA")) == NULL)
		{
			DWORD dwSectorsPerCluster = 0; 
			DWORD dwBytesPerSector = 0;    
			DWORD dwFreeClusters = 0;      
			DWORD dwClusters = 0;          		
			BOOL fResult = GetDiskFreeSpace("C:", &dwSectorsPerCluster, &dwBytesPerSector, 
										 &dwFreeClusters, &dwClusters);

			DWORD dwTotal = fResult ? (dwClusters * dwBytesPerSector * dwSectorsPerCluster) : 0;
			DWORD dwFree = fResult ? (dwFreeClusters * dwBytesPerSector * dwSectorsPerCluster) : 0;

			m_strTotalDiskSpace = ByteToStr(dwTotal);
			m_strFreeDiskSpace = ByteToStr(dwFree);
		}
		else
		{
			ULARGE_INTEGER uliTotalNumBytes;         
			ULARGE_INTEGER uliTotalFreeBytes;        
			ULARGE_INTEGER uliTotalAvailableToCaller;

			BOOL fResult = pDiskFreeSpaceEx("C:", &uliTotalAvailableToCaller, &uliTotalNumBytes, &uliTotalFreeBytes);
			
			LONGLONG ullTemp1 = uliTotalNumBytes.QuadPart;
			LONGLONG ullTemp2 = uliTotalFreeBytes.QuadPart;
			m_strTotalDiskSpace = ByteToStr(fResult ? (double)ullTemp1 : 0);
			m_strFreeDiskSpace = ByteToStr(fResult ? (double)ullTemp2 : 0);
		}
	}
}

CString	CSystemInfo::ByteToStr(double nByteCount)
{
	CString strValue;
	double dTemp = nByteCount;
	int nCount = 0;

	while (dTemp > 1000)
	{
		dTemp /= 1024;
		nCount++;
	}

	strValue.Format("%.2f ", dTemp);

	switch(nCount)
	{
	case 0:
		strValue += "Bytes";
		break;
	case 1:
		strValue += "KB";
		break;
	case 2:
		strValue += "MB";
		break;
	case 3:
		strValue += "GB";
		break;
	case 4:
		strValue += "TB";
		break;
	}

	return strValue;
}

CString CSystemInfo::GetOSName()
{
	return m_strOSName;
}

CString CSystemInfo::GetOSVersion()
{
	return m_strOSVersion;
}

CString CSystemInfo::GetTotalMem()
{
	return m_strTotalMemory;
}

CString CSystemInfo::GetFreeMem()
{
	return m_strFreeMemory;
}

CString CSystemInfo::GetVtTotalMem()
{
	return m_strVTotalMemory;
}

CString CSystemInfo::GetVtFreeMem()
{
	return m_strVFreeMemory;
}

CString CSystemInfo::GetTotalDiskSpace()
{
	return m_strTotalDiskSpace;
}
	
CString CSystemInfo::GetFreeDiskSpace()
{
	return m_strFreeDiskSpace;
}

CString CSystemInfo::GetCPU()
{
	return m_strCPU;
}
