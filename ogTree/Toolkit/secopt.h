///////////////////////////////////////////////////////////////////////////////
// secopt.h
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
// 
//  Author:			Scot Wingo
//  Description:	secopt.h - optimization header file.
//  Created:		Tue Aug 26 20:48:25 1998
//
//

#ifndef __SECOPT_H__
#define __SECOPT_H__

//
// Check for 32 bit environment
//
#ifndef WIN32
    #error WIN32 is not defined.  This version of Objective Toolkit requires a 32-bit compiler.
#endif

// ***********************************************************
// *
// *  BuildWizard preliminary includes
// *
// ***********************************************************

#if !defined(__SEC_BWDEFINES_H)
#ifdef UNDER_CE
//#include "BWDefCE.h"
#else
#include "BWDef.h"
#endif //UNDER_CE
#endif //__SEC_BWDEFINES_H

// CImageList, etc.
#if !defined(__AFXCMN_H__)
#include <afxcmn.h>
#endif

// Stingray Foundation Library 
// If OT is a DLL, then SFL must also be a DLL

#ifdef _SECDLL
	#ifndef _SFLDLL
		#define _SFLDLL
	#endif
#endif // _SECDLL


// ***********************************************************
// *
// *  Common library components - Now it is Foundation Library
// *
// ***********************************************************

// OT needs 8 byte packing for structures
#if _MFC_VER >= 0x0300
// pshpack8.h saves the current #pragma pack value
#include /* */ "pshpack8.h"
#else
#pragma pack(8)
#endif

//Prevent the ATL related class be included
#define _SFL_NO_ATL


#include "..\Foundation\SflCommon.h"

#ifdef WIN32
//#include "OgTree\foundation\SflDef.h"
#endif

//#include "OgTree\Foundation\SflRes.h"

//#include "OgTree\Foundation\Image.h"

#ifndef _SECDC_H_
#include "..\Foundation\Graphics\MFC\secdc.h"
#endif

// ***********************************************************
// *
// *  SEC CRect Extension 
// *
// ***********************************************************

#ifndef __SEC_RECT_H__
//#include "OgTree\Foundation\Graphics\MFC\secrect.h"
#endif

// ***********************************************************
// *
// *  Bitmap loading
// *
// ***********************************************************

#ifndef __SLOADBMP_H__
//#include "OgTree\Foundation\Graphics\MFC\sloadbmp.h"
#endif // __SLOADBMP_H__

// ***********************************************************
// *
// *  Color Well
// *
// ***********************************************************

// SECColorWell
#ifndef __SECWELL_H__
//#include "OgTree\Foundation\Controls\MFC\secwell.h"
#endif // __SECWELL_H__

// ***********************************************************
// *
// *  Button Classes
// *
// ***********************************************************

// SECBtns
#ifndef __SECBTNS_H__
//#include "OgTree\Foundation\Controls\MFC\secbtns.h"
#endif // __SECBTNS_H__

// ***********************************************************
// *
// *  Design Patterns
// *
// ***********************************************************

#ifndef __SEC_PATTERNS_H
//#include "OgTree\Foundation\patterns.h"
#endif


// ***********************************************************
// *
// *  Version info
// *
// ***********************************************************

#ifndef __SECVER_H__
//#include "OgTree\toolkit\secver.h"
#endif

// ***********************************************************
// *
// *  Objective Toolkit Resources
// *
// ***********************************************************

//#include "OgTree\toolkit\secres.h"

// ***********************************************************
// *
// *  Objective Toolkit PRO Resources
// *
// ***********************************************************

#ifdef OTPRO
//#include "OgTree\toolkit\secres_pro.h"
#endif

// ***********************************************************
// *
// *  Common Classes
// *
// ***********************************************************
#ifdef OT_BLD_COMMON

	#ifndef __SECAUX_H__
	#include "secaux.h"
	#endif // __SECAUX_H__

	// dll support
	#ifndef __SECDLL_H__
//	#include "OgTree\toolkit\secdll.h"
	#endif // __SECDLL_H_

#endif // OT_BLD_COMMON


// ***********************************************************
// *
// *  Internationalization
// *
// ***********************************************************

#ifdef OT_BLD_SLOCALE

	// SECLocale
	#ifndef __SLOCALE_H__
//	#include "OgTree\toolkit\slocale.h"
	#endif // __SLOCALE_H__

#endif // OT_BLD_SLOCALE

#if _MFC_VER >= 0x0300
// poppack.h restores the original #pragma pack value
#include /* */ "poppack.h"
#else
// restore default packing value
#pragma pack()
#endif

#endif // __SECOPT_H__

