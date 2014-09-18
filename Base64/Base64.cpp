// Base64.cpp: implementation of the CBase64Enc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Base64.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CBase64Enc Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBase64Enc::CBase64Enc()
{
	m_strResult = "";
}

CBase64Enc::~CBase64Enc()
{

}

void CBase64Enc::Encode(const CString str)
{
	int nSourceCharCount=0;
	int length = str.GetLength();
	m_strResult = "";

	while( nSourceCharCount < length )
	{
		m_strResult += Base64Table[((str[nSourceCharCount] & 0xFC)>>2)];	// 1
		if(nSourceCharCount+1 >= length)
		{
			m_strResult += Base64Table[((str[nSourceCharCount] & 0x03)<<4)];	// 2
			m_strResult += '=';		// 3
			m_strResult += '=';		// 4
			break;
		}
		else 
		{
			m_strResult += Base64Table[
				((str[nSourceCharCount] & 0x03)<<4) | ((str[nSourceCharCount+1] & 0xF0)>>4)	];	// 2
		}
		
		if(nSourceCharCount+2 >= length)
		{
			m_strResult += Base64Table[((str[nSourceCharCount+1] & 0x0F)<<2)];	// 3
			m_strResult += '=';		// 4
			break;
		}
		else
		{
			m_strResult += Base64Table[
				((str[nSourceCharCount+1] & 0x0F)<<2) | ((str[nSourceCharCount+2] & 0xC0)>>6)	];	// 3
			m_strResult += Base64Table[((str[nSourceCharCount+2] & 0x3F))];	// 4
		}
		nSourceCharCount+=3;
	}
	m_strResult+='\0';	
	
}


///////////////////////////////////////////////////////////////////////
// CBase64Dec Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBase64Dec::CBase64Dec()
{
	m_strResult = "";
}

CBase64Dec::~CBase64Dec()
{

}

int CBase64Dec::GetRealValue( const int c )
{
	if( 'A' <= c && c <= 'Z' )
		return c-'A';
	if( 'a' <= c && c <= 'z' )
		return c - 'a' + 26;
	if( '0' <= c && c <= '9' )
		return c - '0' + 52;
	if( c == '+' )
		return 62;
	if( c == '/' )
		return 63;
	if( c == '=' )	// end of line
		return -1;
	return -2;	// non value;
}


void CBase64Dec::Decode(const CString str)
{
	int nCount=0, i=0, r, result;
	int length = str.GetLength();
	char szDest[5]="";

	m_strResult = "";
	while(nCount < length)
	{
		i=0;
		strcpy(szDest, "");
		while(nCount<length && i<4)	// 4개의 바이트를 얻는다.
		{			
			r = str[nCount++];
			result = GetRealValue(r);
			if(result!=-2)
			{
				if(result!=-1)
					szDest[i++] = (char)result;
				else szDest[i++] = '@';	// It's end  (64번은 디코딩시 사용되지 않기 때문)
			}
		}

		if(i==4)	// 4개의 소스를 모두 얻어냈다. 디코드 시작
		{	
			if( nCount+3 >= length )	// 데이터의 끝에 도달했다.
			{
				if( szDest[1] == '@' ){
					m_strResult+=(char)( szDest[0]<<2 );		break;}// exit while loop
				else m_strResult+=(char)( (szDest[0]<<2 | szDest[1]>>4) );	// 1 Byte

				if( szDest[2] == '@' ){
					m_strResult+=(char)( szDest[1]<<4 );		break;}
				else m_strResult+=(char)( (szDest[1]<<4 | szDest[2]>>2) );	// 2 Byte				

				if( szDest[3] == '@' ){
					m_strResult+=(char)( szDest[2]<<6 );		break;}
				else m_strResult+=(char)( (szDest[2]<<6 | szDest[3]) );	// 3 Byte				
			}
			else
			{
				m_strResult+=(char)( (szDest[0]<<2 | szDest[1]>>4) );	// 1 Byte
				m_strResult+=(char)( (szDest[1]<<4 | szDest[2]>>2) );	// 2 Byte				
				m_strResult+=(char)( (szDest[2]<<6 | szDest[3]) );	// 3 Byte
			}
		}
		
	}// end of while
}