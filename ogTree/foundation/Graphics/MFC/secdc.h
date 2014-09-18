///////////////////////////////////////////////////////////////////////////////
// secdc.h
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

//  Authors:		Dean Hallman and Justin Rudd


#ifdef WIN32

#if!defined _SFL_SECDC_H_
#define _SFL_SECDC_H_

//
// Header include diagnostics
//
#if defined(WIN32) && defined(SEC_DBG_HEADER_DIAGNOSTICS)
	#pragma message ( __TIME__ ":  include " __FILE__ )
#endif


//
// CMN Extension DLL
// Initialize declaration context
//
#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL

#include "..\StingrayExportDefs.h"


namespace stingray {
namespace foundation {

class SECMemDC : public CDC  
{
	FOUNDATION_DECLARE_DYNAMIC(SECMemDC)
public:
	FOUNDATION_API SECMemDC( CDC& dcSrc, CRect rcSrc, BOOL bInit = TRUE, BOOL bUpdateCoords = TRUE);
	FOUNDATION_API SECMemDC( CDC* pdcSrc, CRect rcSrc, BOOL bInit = TRUE, BOOL bUpdateCoords = TRUE);

	FOUNDATION_API virtual ~SECMemDC();

	// QA: 32569
	FOUNDATION_API BOOL DoCreateCompatibleDC();
	FOUNDATION_API BOOL DoCreateCompatibleBitmap();
	FOUNDATION_API void DoSelectBitmap();


protected:
	FOUNDATION_API void InitDC();

	CDC* m_pSrcDC;
	CBitmap m_bmp, *m_pOldBitmap;
	CRect m_rcSrc;

	CPoint m_ptVp, m_ptWnd;
	CSize m_szVp, m_szWnd;
	BOOL m_bUpdateCoords; // QA: 32569
};

};  // namespace stingray::foundation
};  // namespace stingray

//
// CMN Extension DLL
// Reset declaration context
//
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // _SFL_SECDC_H_

#endif // WIN32


