// Base64.h: interface for the CBase64 class.
// Author	: Kim Tae Hyun  in Korea
// Date		: 2000/7/26
// tipani@click1004.com     turbo93@daum.net
// 
// example:
// CBase64Enc obj;
// obj.Encode("엔코드할문자");
// CString str = obj.GetResult();
//
// CBase64Dec obj;
// obj.Decode("디코드할문자");
// CString str = obj.GetResult();
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__86352A81_60FD_11D4_AA40_00A024695220__INCLUDED_)
#define AFX_BASE64_H__86352A81_60FD_11D4_AA40_00A024695220__INCLUDED_

const char Base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Base64 방식으로 엔코딩 하는 클래스
class CBase64Enc
{
public:
	CBase64Enc();
	CBase64Enc(const CString str){	Encode(str);}
	virtual ~CBase64Enc();
	
	void Encode(const CString str);
	CString GetResult(){	return m_strResult;}
private:
	CString m_strResult;
};

// Base64 방식으로 디코딩 하는 클래스
class CBase64Dec
{
public:
	CBase64Dec();
	CBase64Dec(const CString str){	Decode(str);}
	virtual ~CBase64Dec();

	void Decode(const CString str);
	CString GetResult(){	return m_strResult;}
private:
	int GetRealValue( const int c );
	CString m_strResult;
};

#endif // !defined(AFX_BASE64_H__86352A81_60FD_11D4_AA40_00A024695220__INCLUDED_)
