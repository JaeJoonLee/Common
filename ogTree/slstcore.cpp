//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (��)�ѱ��Ҹ���ġ        
//******************************************************************
//  File Name     : slstcore.cpp
//  Function      : 
//  System Name   : KSBuilder
//  Create        : 
//  Update        : ������, 2009/10/09 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
///////////////////////////////////////////////////////////////////////////////
// slstcore.cpp
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
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
// 
//  Authors:		Dean Hallman and Justin Rudd

#define _OT_EXPORT_IMPL

#include "stdafx.h"

#if defined(WIN32)

#ifdef _SECDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif //_SECDLL

// statics
static COLORREF rgbNoFocusBk = ::GetSysColor(COLOR_MENU);
static COLORREF rgbNoFocusText = ::GetSysColor(COLOR_MENUTEXT);
static COLORREF rgbBtnFace = ::GetSysColor(COLOR_BTNFACE);
static const int cxVertScroll = ::GetSystemMetrics(SM_CXVSCROLL);
static const int cyHorzScroll = ::GetSystemMetrics(SM_CYHSCROLL);

// *******************************
// implementation for SECListBaseC
#include "toolkit\slstbaseC.h"	// parameter definitions and parameterized class declaration

#undef SEC_LISTCLASS
#undef SEC_LISTBASE
#define SEC_LISTCLASS SECListBaseC
#define SEC_LISTBASE CWnd

#include "toolkit\slstcore.inl"	// parameterized implementation



#ifdef _SECDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif //_SECDLL

#endif // defined(WIN32)
