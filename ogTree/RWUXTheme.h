///////////////////////////////////////////////////////////////////////////////
// RWUXTheme.h
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __RWUXTHEME_H
#define __RWUXTHEME_H

#if _MSC_VER > 1000
	#pragma once
#endif

// Definition for _RWUXTHEME_STATIC_LINK is defined in 
// <StingrayInstallDir>\Src\CompilerMSVC*.mak, define it to 
// force a static link of RWUXTheme into the Stingray Foundation Library.
#if !defined _RWUXTHEME_STATIC_LINK
	#ifndef _RWUXTHEMELIB
		#ifdef _SECDLL
			#define _RWOSDLL
		#else
			#ifdef _SFLDLL
				#define _RWOSDLL
			#else
				#ifdef _OBJCHART_DLL
					#define _RWOSDLL
				#else
					#ifdef _SECEDITDLL
						#define _RWOSDLL
					#else
						#ifdef _GXDLL
							#define _RWOSDLL
						#else
							#ifdef _OVDLL
								#define _RWOSDLL
							#endif
						#endif
					#endif
				#endif
			#endif
		#endif
	#endif //_RWUXTHEMELIB
#endif //_RWUXTHEME_STATIC_LINK

#undef _RWUXTHEMEAUTOLIBNAME

#ifndef RWTHEMEPROXYBUILD
#if	_MSC_VER > 1400 //VC9 and higher
		#ifndef _UNICODE
			#if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeD90.lib"
			#elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXTheme90.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAD90.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeA90.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSD90.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeS90.lib"
			#elif  defined(_RWOSDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#else
			#if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeUD90.lib"
			#elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeU90.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAUD90.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAU90.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSUD90.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSU90.lib"
			#elif  defined(_RWOSDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#endif
	#elif _MSC_VER == 1400 //VC8 and higher
		#ifndef _UNICODE
			#if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeD80.lib"
			#elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXTheme80.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAD80.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeA80.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSD80.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeS80.lib"
			#elif  defined(_RWOSDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#else
			#if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeUD80.lib"
			#elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeU80.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAUD80.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAU80.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSUD80.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSU80.lib"
			#elif  defined(_RWOSDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#endif
	#elif	_MSC_VER == 1310 //VC71 
		#ifndef _UNICODE
			#if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeD71.lib"
			#elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXTheme71.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAD71.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeA71.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSD71.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeS71.lib"
			#elif  defined(_RWOSDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#else
			#if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeUD71.lib"
			#elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeU71.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAUD71.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAU71.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSUD71.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSU71.lib"
			#elif  defined(_RWOSDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#endif
	#else //VC6 or VC5
		#ifndef _UNICODE
			#if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeD60.lib"
			#elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXTheme60.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAD60.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeA60.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSD60.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeS60.lib"
			#elif  defined(_RWOSDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#else
			#if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeUD60.lib"
			#elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeU60.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAUD60.lib"
			#elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAU60.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSUD60.lib"
			#elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _RWUXTHEMEDLL
				#define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSU60.lib"
			#elif  defined(_RWOSDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#endif
	#endif
#endif //RWTHEMEPROXYBUILD

#ifdef _RWUXTHEMEAUTOLIBNAME	
	#pragma comment(lib, _RWUXTHEMEAUTOLIBNAME)
	#pragma message( "Automatically linking with " _RWUXTHEMEAUTOLIBNAME)
#endif

#ifdef _RWUXTHEMEDLL
	#ifdef RWTHEMEPROXYBUILD // We're building the libraries. ;)
		// Global Functions
		#define RWTHEMEAPI(rettype)	extern "C" rettype __declspec(dllexport)
		// Non-Global Functions
		#define RWTHEME_API __declspec(dllexport) 
		// Global Variables
		#define RWTHEMEVAR_API RWTHEME_API 
		
	#else // Somebody else is building the libraries. ;)
		// Global Functions
		#define RWTHEMEAPI(rettype)	extern "C" rettype __declspec(dllimport) 
		// Non-Global Functions
		#define RWTHEME_API __declspec(dllimport) 
		// Global Variables
		#define RWTHEMEVAR_API RWTHEME_API

	#endif // RWTHEMEPROXYBUILD
#else //_RWUXTHEMEDLL
	// Global Functions
	#define RWTHEMEAPI(rettype) extern "C" rettype
	// Non-Global Functions
	#define RWTHEME_API 

	// Global Variables
	#ifdef RWTHEMEPROXYBUILD // We're building the libraries.
		#define RWTHEMEVAR_API 
	#else
		#define RWTHEMEVAR_API extern
	#endif
#endif

//We need this section to allow applications to compile without including uxtheme.h
#if !defined RWTHEMEPROXYBUILD
	#if (_MSC_VER <= 1200) || (NTDDI_VERSION < NTDDI_WINXP)
		#include "VC6PlatDefs.h"
	#endif
#endif
// Function to control XP Theming Behavior
RWTHEMEAPI(BOOL) __cdecl RWEnableXPThemesDrawing( BOOL enable = TRUE );


// Funcitons forwarded to UXThemeAPI
// For information on these functions look for function names without RW prefix in MSDN 
RWTHEMEAPI(HTHEME)	RWOpenThemeData(HWND hwnd, LPCWSTR pszClassList);
RWTHEMEAPI(HRESULT) RWCloseThemeData(HTHEME hTheme);
RWTHEMEAPI(HRESULT) RWDrawThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, const RECT *pClipRect);
RWTHEMEAPI(HRESULT) RWDrawThemeText(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, DWORD dwTextFlags2, const RECT *pRect);
RWTHEMEAPI(HRESULT) RWGetThemeBackgroundContentRect(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,  const RECT *pBoundingRect, RECT *pContentRect);
RWTHEMEAPI(HRESULT) RWGetThemeBackgroundExtent(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pContentRect, RECT *pExtentRect);
RWTHEMEAPI(HRESULT) RWGetThemePartSize(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, RECT *prc, enum THEMESIZE eSize, OUT SIZE *psz);
RWTHEMEAPI(HRESULT) RWGetThemeTextExtent(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, const RECT *pBoundingRect, RECT *pExtentRect);
RWTHEMEAPI(HRESULT) RWGetThemeTextMetrics(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, TEXTMETRIC* ptm);
RWTHEMEAPI(HRESULT) RWGetThemeBackgroundRegion(HTHEME hTheme, HDC hdc,  int iPartId, int iStateId, const RECT *pRect, HRGN *pRegion);
RWTHEMEAPI(HRESULT) RWHitTestThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, DWORD dwOptions, const RECT *pRect, HRGN hrgn, POINT ptTest, WORD *pwHitTestCode);
RWTHEMEAPI(HRESULT) RWDrawThemeEdge(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pDestRect, UINT uEdge, UINT uFlags, RECT *pContentRect);
RWTHEMEAPI(HRESULT) RWDrawThemeIcon(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex);
RWTHEMEAPI(BOOL)	RWIsThemePartDefined(HTHEME hTheme, int iPartId, int iStateId);
RWTHEMEAPI(BOOL)	RWIsThemeBackgroundPartiallyTransparent(HTHEME hTheme, int iPartId, int iStateId);
RWTHEMEAPI(HRESULT) RWGetThemeColor(HTHEME hTheme, int iPartId, int iStateId, int iPropId, COLORREF *pColor);
RWTHEMEAPI(HRESULT) RWGetThemeMetric(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, int *piVal);
RWTHEMEAPI(HRESULT) RWGetThemeString(HTHEME hTheme, int iPartId, int iStateId, int iPropId, LPWSTR pszBuff, int cchMaxBuffChars);
RWTHEMEAPI(HRESULT) RWGetThemeBool(HTHEME hTheme, int iPartId, int iStateId, int iPropId, BOOL *pfVal);
RWTHEMEAPI(HRESULT) RWGetThemeInt(HTHEME hTheme, int iPartId, int iStateId, int iPropId, int *piVal);
RWTHEMEAPI(HRESULT) RWGetThemeEnumValue(HTHEME hTheme, int iPartId, int iStateId, int iPropId, int *piVal);
RWTHEMEAPI(HRESULT) RWGetThemePosition(HTHEME hTheme, int iPartId, int iStateId, int iPropId, POINT *pPoint);
RWTHEMEAPI(HRESULT) RWGetThemeFont(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, LOGFONT *pFont);
RWTHEMEAPI(HRESULT) RWGetThemeRect(HTHEME hTheme, int iPartId, int iStateId, int iPropId, RECT *pRect);
RWTHEMEAPI(HRESULT) RWGetThemeMargins(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, RECT *prc, MARGINS *pMargins);
RWTHEMEAPI(HRESULT) RWGetThemeIntList(HTHEME hTheme, int iPartId, int iStateId, int iPropId, INTLIST *pIntList);
RWTHEMEAPI(HRESULT) RWGetThemePropertyOrigin(HTHEME hTheme, int iPartId, int iStateId, int iPropId, enum PROPERTYORIGIN *pOrigin);
RWTHEMEAPI(HRESULT) RWSetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);
RWTHEMEAPI(HRESULT) RWGetThemeFilename(HTHEME hTheme, int iPartId, int iStateId, int iPropId, LPWSTR pszThemeFileName, int cchMaxBuffChars);
RWTHEMEAPI(COLORREF) RWGetThemeSysColor(HTHEME hTheme, int iColorId);
RWTHEMEAPI(HBRUSH)	RWGetThemeSysColorBrush(HTHEME hTheme, int iColorId);
RWTHEMEAPI(BOOL)	RWGetThemeSysBool(HTHEME hTheme, int iBoolId);
RWTHEMEAPI(int)		RWGetThemeSysSize(HTHEME hTheme, int iSizeId);
RWTHEMEAPI(HRESULT) RWGetThemeSysFont(HTHEME hTheme, int iFontId, LOGFONT *plf);
RWTHEMEAPI(HRESULT) RWGetThemeSysString(HTHEME hTheme, int iStringId, LPWSTR pszStringBuff, int cchMaxStringChars);
RWTHEMEAPI(HRESULT) RWGetThemeSysInt(HTHEME hTheme, int iIntId, int *piValue);
RWTHEMEAPI(BOOL)	RWIsThemeActive();
RWTHEMEAPI(BOOL)	RWIsAppThemed();
RWTHEMEAPI(HTHEME)	RWGetWindowTheme(HWND hwnd);
RWTHEMEAPI(HRESULT) RWEnableThemeDialogTexture(HWND hwnd, DWORD dwFlags);
RWTHEMEAPI(BOOL)	RWIsThemeDialogTextureEnabled(HWND hwnd);
RWTHEMEAPI(DWORD)	RWGetThemeAppProperties();
RWTHEMEAPI(void)	RWSetThemeAppProperties(DWORD dwFlags);
RWTHEMEAPI(HRESULT) RWGetCurrentThemeName( LPWSTR pszThemeFileName, int cchMaxNameChars, LPWSTR pszColorBuff, int cchMaxColorChars, LPWSTR pszSizeBuff, int cchMaxSizeChars);
RWTHEMEAPI(HRESULT) RWGetThemeDocumentationProperty(LPCWSTR pszThemeName, LPCWSTR pszPropertyName, LPWSTR pszValueBuff, int cchMaxValChars);
RWTHEMEAPI(HRESULT) RWDrawThemeParentBackground(HWND hwnd, HDC hdc, RECT* prc);
RWTHEMEAPI(HRESULT) RWEnableTheming(BOOL fEnable);

// Color manipulation functions
RWTHEMEAPI(COLORREF) RWBlendColors( COLORREF dstClr, COLORREF srcClr, BYTE blendVal );
RWTHEMEAPI(COLORREF) RWLightenColor( COLORREF srcClr, BYTE lightAmount );
RWTHEMEAPI(BOOL)	 RWIsDarkColor( COLORREF tstClr, DWORD threshold );
RWTHEMEAPI(COLORREF) RWSetContrast( COLORREF clr1, COLORREF clr2, int threshold );

// Defines to use in RWGetDNETColor
#define RW_TOOLBAR			0x00
#define RW_TOOLBARSEP		0x01
#define RW_TOOLBARTEXT		0x02
#define RW_TBBTNFACENORM	0x03
#define RW_TBBTNFRMNORM		0x04
#define RW_TBBTNFACEHOT		0x05
#define RW_TBBTNFRMHOT		0x06
#define RW_TBBTNFACEPRESS	0x07
#define	RW_TBBTNFRMPRESS	0x08
#define RW_TBBTNFACEDIS		0x09
#define RW_TBBTNFRMDIS		0x0A
#define RW_TBBTNFACECHK		0x0B
#define RW_TBBTNFRMCHK		0x0C
#define RW_TBBTNFACECHKHOT	0x0D
#define RW_TBBTNFRMCHKHOT	0x0E
#define RW_MENU				0x0F
#define RW_MENUTXT			0x10
#define RW_MENUDIS			0x11
#define RW_MENUTXTDIS		0x12
#define RW_MENUHOT			0x13
#define RW_MENUFRMHOT		0x14
#define RW_MENUTXTHOT		0x15
#define RW_MENUDISHOT		0x16
#define RW_MENUTXTDISHOT	0x17
#define RW_MENUFRMDISHOT	0x18
#define RW_MENUBAND			0x19
#define	RW_MENUFRAME		0x1A
#define RW_MENUSEP			0x1B
#define RW_MENUBAR			0x1C
#define RW_MENUBARTXT		0x1D
#define RW_ICONSHADOW		0x1E
#define RW_DISTEXT			0x1F
#define RW_GRIPPER			0x20

// OFFICE 2003 LOOK AND FEEL COLORS
#define RW_O2K3_THEMEGRADIENT1		0x00	// Darker Gradient Color
#define RW_O2K3_THEMEGRADIENT2		0x01	// Lighter Gradient Color
#define RW_O2K3_THEMEBACKGROUND		0x02	// Blend of RW_O2K3_THEMEGRADIENT1 and RW_O2K3_THEMEGRADIENT2
#define RW_O2K3_THEMETBHOT			0x03	// Toolbar Hot, usually orange
#define RW_O2K3_THEMETBHOTDARK		0x04	// Toolbar Hot Dark, a darker orange
#define RW_O2K3_THEMEMENUHOT		0x05	// Menu Hot, a light orange
#define RW_O2K3_THEMEEDGEFILL		0x06	// Edge color, usually used for grippers
#define RW_O2K3_THEMEEDGEDARK       0x07    // Edge dark color

// Internal color map functions
RWTHEMEAPI(void)	 RWResetColors();
RWTHEMEAPI(void)	 RWResetO2K3Colors(HWND hwnd);
RWTHEMEAPI(COLORREF) RWGetDNETColor( DWORD colorId );
RWTHEMEAPI(COLORREF) RWGetO2K3Color( DWORD colorId );
RWTHEMEAPI(COLORREF) RWAdjustHSL(COLORREF color, float percentH, float percentS, float percentL);

// Imagelist manipulation functions
RWTHEMEAPI(void) RWDrawImage( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, BOOL isHiContrast );
RWTHEMEAPI(void) RWDrawHighlightedImage( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF highlightingColor, BYTE amount );
RWTHEMEAPI(void) RWDrawFullImageShadow( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF shadowColor );
RWTHEMEAPI(void) RWDrawFlatImageShadow( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF shadowColor );

// Pre-drawn bitmaps manipulation functions
RWTHEMEAPI(void) RWDrawDCImage( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, BOOL isHiContrast );
RWTHEMEAPI(void) RWDrawDCHighlightedImage( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, COLORREF highlightingColor, BYTE amount );
RWTHEMEAPI(void) RWDrawDCFullImageShadow( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, COLORREF shadowColor );
RWTHEMEAPI(void) RWDrawDCFlatImageShadow( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, COLORREF shadowColor );

// Drawing functions - if possible - they rely on WinAPI functions - otherwise - internal implementation
RWTHEMEAPI(BOOL) RWTransparentBlt( HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent );
RWTHEMEAPI(BOOL) RWBlendBlt( HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidth, int nHeight, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, BYTE alphaConst );
RWTHEMEAPI(BOOL) RWPaintGradientRect(HDC hdcDest, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF color1, COLORREF color2, BOOL vertical);

// Helper functions
RWTHEMEAPI(HRESULT) RWDrawThemedBMPItem( HWND hWnd, HDC hDC, HBITMAP hBMP, LPCWSTR pszClassList, int iPartId, int iStateId, int x, int y, int cx, int cy, int bmpX, int bmpY, int bmpCX, int bmpCY, unsigned int transColor = 0x00C0C0C0 );

//Some functions not present on older operating system
RWTHEMEAPI(BOOL)	 RWTrackMouseEvent( LPTRACKMOUSEEVENT lpEventTrack );

// Look and Feel
static BOOL g_IsWindowsClassicStyleEnabled;
static BOOL	g_IsDotNetStyleEnabled;
static BOOL g_IsOfc2003StyleEnabled;
static BOOL g_IsVistaClassicStyleEnabled;
static BOOL g_IsVistaAeroGlassStyleEnabled;

enum eRWVisualStyle
{
	RW_VISUALSTYLE_INVALID = 0,
	RW_VISUALSTYLE_WINDOWSCLASSIC,
	RW_VISUALSTYLE_DOTNET,
	RW_VISUALSTYLE_OFFICE2003, 
	RW_VISUALSTYLE_VISTACLASSIC,
	RW_VISUALSTYLE_VISTAAEROGLASS
};

RWTHEMEAPI(BOOL) RWSetVisualStyle(eRWVisualStyle iStyle = RW_VISUALSTYLE_WINDOWSCLASSIC);
RWTHEMEAPI(eRWVisualStyle)  RWGetVisualStyle();

RWTHEMEAPI(BOOL) RWIsDotNetStyleEnabled();
RWTHEMEAPI(BOOL) RWSetDotNetStyle( BOOL bEnable = TRUE );

RWTHEMEAPI(BOOL) RWIsOfc2003StyleEnabled();
RWTHEMEAPI(BOOL) RWSetOfc2003Style(BOOL bEnable = TRUE);

RWTHEMEAPI(BOOL) RWIsVistaClassicStyleEnabled();
RWTHEMEAPI(BOOL) RWSetVistaClassicStyle(BOOL bEnable = TRUE);

RWTHEMEAPI(BOOL) RWIsVistaAeroGlassStyleEnabled();
RWTHEMEAPI(BOOL) RWSetVistaAeroGlassStyle(BOOL bEnable = TRUE);

RWTHEMEAPI(HWND) RWGetSafeHwnd();

#define CX_BORDER       1
#define CY_BORDER       1

#pragma warning(disable: 4005)

/////////////////////////////////////////////////////////////////////////////
// OT Auxiliary System/Screen metrics

struct RWTHEME_API SEC_AUX_DATA
{
public:
	// system metrics
	int cxBorder2, cyBorder2;

	// color values of system colors used for CToolBar
	COLORREF clrBtnFace, clrBtnShadow, clrBtnHilite;
	COLORREF clrWindowFrame, clr3DLight, clr3DDkShadow;
	COLORREF clrText, clrWindow, clrHighlight, clrHighlightText;

	// standard cursors
	HCURSOR hcurArrow;
	HCURSOR hcurHSplit, hcurVSplit, hCurCrossHairs;

	// other system information
	BOOL    bWin4;          // TRUE if Windows 4.0

	// Implementation
	SEC_AUX_DATA();
	virtual ~SEC_AUX_DATA();
	void UpdateSysColors();
	static BOOL m_bUpdateSysColorsCalled;
};
RWTHEMEAPI(SEC_AUX_DATA)& RWGetSecData();

#endif // __RWUXTHEME_H
