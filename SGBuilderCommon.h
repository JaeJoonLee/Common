#ifndef _SCREENTOGRIDBUILER_H_
#define _SCREENTOGRIDBUILER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma pack(push, 1)

typedef struct tagTranInfo
{
	HWND    hTargetWnd;
	CPoint	pt;
	char	szTrCode[MAX_PATH];
} TRANINFO, *LPTRANINFO;

#pragma pack(pop)

#endif//__SCREENTOGRIDBUILER_H_