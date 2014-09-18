// gxCaptionstyle.cpp : implementation of the CGXStyle and supporting classes
//
#include "stdafx.h"


#ifndef _GXGRIDCELLSTYLE_H_
#include "gxgridCellstyle.h"
#endif


#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXGRIDCELLSTYLE")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_SERIAL(CGXGridCellStyle, CObject, 0 /* schema number*/ )

#define new DEBUG_NEW

const DWORD ExcludeAll = 0;

DWORD CGXGridCellStyle::STYLEBITS::GetPortable() const
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

void CGXGridCellStyle::STYLEBITS::SetPortable(DWORD dw)
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

CGXGridCellStyle::CGXGridCellStyle(const CGXGridCellStyle& p)
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

CGXGridCellStyle::~CGXGridCellStyle()
{
	Free();
}

CGXGridCellStyle* CGXGridCellStyle::Clone() const
{
	return new CGXGridCellStyle(*this);
}

const CGXGridCellStyle& CGXGridCellStyle::operator=(const CGXGridCellStyle& p)
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

void CGXGridCellStyle::ChangeStyle(const CGXGridCellStyle& p )
{
	ASSERT(p.IsKindOf(RUNTIME_CLASS(CGXGridCellStyle)));
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

CGXGridCellStyle& CGXGridCellStyle::SetDefault()
{
	Free();

	ASSERT_VALID(this);

	return *this;
}

void CGXGridCellStyle::Free()
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

void CGXGridCellStyle::ConstructStyle()
{
	stylebits.SetPortable(ExcludeAll);

	m_lpszValue = NULL;
}

CGXGridCellStyle& CGXGridCellStyle::SetMultiLangDataValue( short nDataType ,CString strValue)
{
	BOOL bNoData = strValue.IsEmpty();
	switch ( nDataType )
	{
	//	case dxGridDataType_Value:                  // Caption Value
		case dxGridDataType_MultiCaption:			// Multi Caption
			if ( bNoData )
			{
				m_strMultiCaption = strValue;
				return CGXGridCellStyle::SetIncludeMultiCaptionValue(FALSE);
			}
			return SetMultiCaptionValue		( strValue );
		case dxGridDataType_MultiTooltip:			// MultiTooltip
			if ( bNoData )
			{
				m_strMultiTooltip = strValue;
				return CGXGridCellStyle::SetIncludeMultiTooltipValue(FALSE);
			}
			return SetMultiTooltipValue		( strValue );
		case dxGridDataType_MultiChoiceList:		// MultiChoiceList
			if ( bNoData )
			{
				m_strMultiChoiceList = strValue;
				return CGXGridCellStyle::SetIncludeMultiChoiceListValue(FALSE);
			}
			return SetMultiChoiceListValue	( strValue );
		case dxGridDataType_ItemName:				// Item Name
			if ( bNoData )
			{
				m_strItemName = strValue;
				return CGXGridCellStyle::SetIncludeItemNameValue(FALSE);
			}
			return SetItemNameValue			( strValue );
		case dxGridDataType_RecordName:				// Record Name
			if ( bNoData )
			{
				m_strRecordName = strValue;
				return CGXGridCellStyle::SetIncludeRecordNameValue(FALSE);
			}
			return SetRecordNameValue		( strValue );
		default:
			ASSERT ( FALSE );
			break;
	}
	return *this;
}

#ifdef _DEBUG
void CGXGridCellStyle::AssertValid() const
{
	CObject::AssertValid();
}

void CGXGridCellStyle::Dump(CDumpContext& dc) const
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


void CGXGridCellStyle::Serialize(CArchive& ar)
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
