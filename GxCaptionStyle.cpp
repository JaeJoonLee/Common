// gxCaptionstyle.cpp : implementation of the CGXStyle and supporting classes
//
//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (ÁÖ)ÇÑ±¹¼Ò¸®¸¶Ä¡        
//******************************************************************
//  File Name     : GxCaptionStyle.cpp
//  Function      : 
//  System Name   : RunAccountCombo
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************

#include "stdafx.h"

#ifdef MULTI_CAPTION_USE		// ´Ù±¹¾î »ç¿ë¿É¼Ç 

#ifndef _GXCAPTIONSTYLE_H_
#include "gxcaptionstyle.h"
#endif


#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCAPTIONSTYLE")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_SERIAL(CGXCaptionStyle, CObject, 0 /* schema number*/ )

#define new DEBUG_NEW

const DWORD ExcludeAll = 0;


//******************************************************************
//  Function Name : GetPortable
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : DWORD 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
DWORD CGXCaptionStyle::STYLEBITS::GetPortable() const
{
	if (NoPortableIsEmptyBits())
	{
		return 0;
	}
	return 
	    0x00000001 * value
	  | 0x00000002 * multicaption
	  | 0x00000004 * tooltip
	  | 0x00000008 * choicelist
	  | 0x00000010 * item
	  | 0x00000020 * recordname
	;
}

#if !defined(_DEBUG) && _MFC_VER < 0x0400
#pragma optimize("", on)
#endif

//******************************************************************
//  Function Name : SetPortable
//  Function      : 
//  Param         : DWORD dw
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStyle::STYLEBITS::SetPortable(DWORD dw)
{
	if (dw == 0)
    {
		SetNoPortableBits(dw);
		return;
	}
	value			= (dw & 0x0001) > 0;
	multicaption	= (dw & 0x0002) > 0;
	tooltip			= (dw & 0x0004) > 0;
	choicelist		= (dw & 0x0008) > 0;
	item			= (dw & 0x0010) > 0;
	recordname		= (dw & 0x0020) > 0;
}

#if !defined(_DEBUG) && _MFC_VER < 0x0400
#pragma optimize("", on)
#endif

//******************************************************************
//  Function Name : CGXCaptionStyle
//  Function      : »ý¼ºÀÚ
//  Param         : const CGXCaptionStyle& p
//  Return        : ¾øÀ½ 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CGXCaptionStyle::CGXCaptionStyle(const CGXCaptionStyle& p)
{
	stylebits.SetNoPortableBits(p.stylebits.GetNoPortableBits());
//	memcpy(&boolbits, &p.boolbits, sizeof(boolbits));

	m_lpszValue = NULL;

	// Caption Value
	if (p.GetIncludeCaptionValue())
	{
		SetCaptionValue((LPCTSTR)p.GetCaptionValueBuf());
	}
	
	// MultiCaption
	if (p.GetIncludeMultiCaptionValue())
	{
		SetMultiCaptionValue(p.GetMultiCaptionValueRef());
	}

	// MultiChoice list
	if (p.GetIncludeMultiChoiceListValue())
	{
		SetMultiChoiceListValue(p.GetMultiChoiceListValueRef());
	}

	// Item Name
	if (p.GetIncludeItemNameValue())
	{
		SetItemNameValue(p.GetItemNameValueRef());
	}

	// Record Name
	if (p.GetIncludeRecordNameValue())
	{
		SetRecordNameValue(p.GetRecordNameValueRef());
	}

	// Tooltip Caption
	if (p.GetIncludeMultiTooltipValue())
	{
		SetMultiTooltipValue(p.GetMultiTooltipValueRef());
	}

}

//******************************************************************
//  Function Name : ~CGXCaptionStyle
//  Function      : ¼Ò¸êÀÚ
//  Param         : ¾øÀ½
//  Return        : ¾øÀ½ 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CGXCaptionStyle::~CGXCaptionStyle()
{
	Free();
}

//******************************************************************
//  Function Name : Clone
//  Function      : 
//  Param         : 
//  Return        : CGXCaptionStyle
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CGXCaptionStyle* CGXCaptionStyle::Clone() const
{
	return new CGXCaptionStyle(*this);
}

//******************************************************************
//  Function Name : operator
//  Function      : 
//  Param         : const CGXCaptionStyle& p
//  Return        : const 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
const CGXCaptionStyle& CGXCaptionStyle::operator=(const CGXCaptionStyle& p)
{
	if (&p == this)
		return *this;

	if (!p.stylebits.GetNoPortableBits())
		Free();
	else
	{
		stylebits.SetNoPortableBits(p.stylebits.GetNoPortableBits());
//		memcpy(&boolbits, &p.boolbits, sizeof(boolbits));

		// Caption Value
		if (p.GetIncludeCaptionValue())
		{
			SetCaptionValue((LPCTSTR)p.GetCaptionValueBuf());
		}
		
		// MultiCaption
		if (p.GetIncludeMultiCaptionValue())
		{
			SetMultiCaptionValue(p.GetMultiCaptionValueRef());
		}

		// MultiChoice list
		if (p.GetIncludeMultiChoiceListValue())
		{
			SetMultiChoiceListValue(p.GetMultiChoiceListValueRef());
		}

		// Item Name
		if (p.GetIncludeItemNameValue())
		{
			SetItemNameValue(p.GetItemNameValueRef());
		}

		// Record Name
		if (p.GetIncludeRecordNameValue())
		{
			SetRecordNameValue(p.GetRecordNameValueRef());
		}
		// Tooltip Caption
		if (p.GetIncludeMultiTooltipValue())
		{
			SetMultiTooltipValue(p.GetMultiTooltipValueRef());
		}

	}

	return *this;
}

//******************************************************************
//  Function Name : ChangeStyle
//  Function      : 
//  Param         : const CGXCaptionStyle& p 
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStyle::ChangeStyle(const CGXCaptionStyle& p )
{
	ASSERT(p.IsKindOf(RUNTIME_CLASS(CGXCaptionStyle)));
	ASSERT_VALID(&p);

	ASSERT_VALID(this);

	if ( !stylebits.GetNoPortableBits())
	{
		*this = p;
		return;
	}
	else if (!p.stylebits.GetNoPortableBits())
		return;
	
	// Caption Value
	if (p.GetIncludeCaptionValue())
	{
		SetCaptionValue((LPCTSTR)p.GetCaptionValueBuf());
	}
	
	// MultiCaption
	if (p.GetIncludeMultiCaptionValue())
	{
		SetMultiCaptionValue(p.GetMultiCaptionValueRef());
	}

	// MultiChoice list
	if (p.GetIncludeMultiChoiceListValue())
	{
		SetMultiChoiceListValue(p.GetMultiChoiceListValueRef());
	}

	// Item Name
	if (p.GetIncludeItemNameValue())
	{
		SetItemNameValue(p.GetItemNameValueRef());
	}

	// Record Name
	if (p.GetIncludeRecordNameValue())
	{
		SetRecordNameValue(p.GetRecordNameValueRef());
	}
	// Tooltip Caption
	if (p.GetIncludeMultiTooltipValue())
	{
		SetMultiTooltipValue(p.GetMultiTooltipValueRef());
	}
}

//******************************************************************
//  Function Name : SetDefault
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : CGXCaptionStyle
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CGXCaptionStyle& CGXCaptionStyle::SetDefault()
{
	Free();

	ASSERT_VALID(this);

	return *this;
}

//******************************************************************
//  Function Name : Free
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStyle::Free()
{
	if (stylebits.NoPortableIsEmptyBits())
		return;

	m_strMultiCaption.Empty();
	m_strMultiTooltip.Empty();
	m_strMultiChoiceList.Empty();
	m_strItemName.Empty();
	m_strRecordName.Empty();

	stylebits.SetNoPortableBits(0);

	if( m_lpszValue )
	{
		delete m_lpszValue;
	}
	m_lpszValue = NULL;

}

//******************************************************************
//  Function Name : ConstructStyle
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStyle::ConstructStyle()
{
	stylebits.SetPortable(ExcludeAll);

	m_lpszValue = NULL;
}

//******************************************************************
//  Function Name : SetMultiLangDataValue
//  Function      : 
//  Param         : short nDataType ,CString strValue
//  Return        : CGXCaptionStyle
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CGXCaptionStyle& CGXCaptionStyle::SetMultiLangDataValue( short nDataType ,CString strValue)
{
	BOOL bNoData = strValue.IsEmpty();
	switch ( nDataType )
	{
	//	case dxDataType_Value:                  // Caption Value
		case dxDataType_MultiCaption:			// Multi Caption
			if ( bNoData )
			{
				m_strMultiCaption = strValue;
				return CGXCaptionStyle::SetIncludeMultiCaptionValue(FALSE);
			}
			return SetMultiCaptionValue		( strValue );
		case dxDataType_MultiTooltip:			// MultiTooltip
			if ( bNoData )
			{
				m_strMultiTooltip = strValue;
				return CGXCaptionStyle::SetIncludeMultiTooltipValue(FALSE);
			}
			return SetMultiTooltipValue		( strValue );
		case dxDataType_MultiChoiceList:		// MultiChoiceList
			if ( bNoData )
			{
				m_strMultiChoiceList = strValue;
				return CGXCaptionStyle::SetIncludeMultiChoiceListValue(FALSE);
			}
			return SetMultiChoiceListValue	( strValue );
		case dxDataType_ItemName:				// Item Name
			if ( bNoData )
			{
				m_strItemName = strValue;
				return CGXCaptionStyle::SetIncludeItemNameValue(FALSE);
			}
			return SetItemNameValue			( strValue );
		case dxDataType_RecordName:				// Record Name
			if ( bNoData )
			{
				m_strRecordName = strValue;
				return CGXCaptionStyle::SetIncludeRecordNameValue(FALSE);
			}
			return SetRecordNameValue		( strValue );
		default:
			ASSERT ( FALSE );
			break;
	}
	return *this;
}

#ifdef _DEBUG
//******************************************************************
//  Function Name : AssertValid
//  Function      : 
//  Param         : 
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStyle::AssertValid() const
{
	CObject::AssertValid();
}

//******************************************************************
//  Function Name : Dump
//  Function      : 
//  Param         : CDumpContext& dc
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStyle::Dump(CDumpContext& dc) const
{
	ASSERT_VALID(this);

	CObject::Dump(dc);

	if (GetIncludeCaptionValue())
		dc << "\n Value = " << GetCaptionValueBuf();

	if (GetIncludeMultiCaptionValue())
		dc << "\n strMultiCaption = " << GetMultiCaptionValueRef();

	if (GetIncludeMultiTooltipValue())
		dc << "\n strMultiTooltip = " << GetMultiTooltipValueRef();

	if (GetIncludeMultiChoiceListValue())
		dc << "\n strMultiChoiceList = " << GetMultiChoiceListValueRef();

	if (GetIncludeItemNameValue())
		dc << "\n strItemName = " << GetItemNameValueRef();

	if (GetIncludeRecordNameValue())
		dc << "\n strRecordName = " << GetRecordNameValueRef();

	dc << "\n";
}
#endif // _DEBUG


//******************************************************************
//  Function Name : Serialize
//  Function      : 
//  Param         : CArchive& ar
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/09/30 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CGXCaptionStyle::Serialize(CArchive& ar)
{
#ifndef _WIN64
	static const WORD wVersion = 1;
#else	// WIN64
	// For IA64 serialization, the high-bit of 'wVersion' is always set. This allows us to differentiate between
	// Win32 and Win64 serialized files.
	static const WORD wVersion = (1 | 0x8000);
#endif	// ndef _WIN64

	WORD wActualVersion = wVersion;

	ASSERT_VALID(this);

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion > wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0("Incompatible format while reading CGXStyle" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXStyle object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	if (ar.IsStoring())
	{
		ASSERT_VALID(this);
		DWORD dw = stylebits.GetPortable();
		ar << dw;

		CString s;
		if (GetIncludeMultiCaptionValue())
			ar << (CString)GetMultiCaptionValueRef();
		if (GetIncludeMultiTooltipValue())
			ar << (CString)GetMultiTooltipValueRef();

		if (GetIncludeMultiChoiceListValue())
			ar << (CString)GetMultiChoiceListValueRef();

		if (GetIncludeItemNameValue())
			ar << (CString)GetItemNameValueRef();

		if (GetIncludeRecordNameValue())
			ar << (CString)GetRecordNameValueRef();

	}
	else
	{
		DWORD dw;
		ar >> dw;
		stylebits.SetPortable(dw);
		
		CString s;
		if ( stylebits.multicaption )  ar >> s, SetMultiCaptionValue ( s );

		if ( stylebits.tooltip      )  ar >> s, SetMultiTooltipValue ( s );

		if ( stylebits.choicelist	)  ar >> s, SetMultiChoiceListValue ( s );
		
		if ( stylebits.item )		   ar >> s, SetItemNameValue ( s );

		if ( stylebits.recordname )    ar >> s, SetRecordNameValue ( s );
	}

}

#endif