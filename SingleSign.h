
#ifndef __SINGLE_SIGN__
#define __SINGLE_SIGN__

#include <afxinet.h>
#include ".\Base64\Base64.h"	//KJI 20100813
#include "../Builder\LinkInfoMng\KSLinkInfoMng.h"
#include "CommStructDef.h"	//KJI 20120405

BOOL SetSingleSign(LONG nType, LPCTSTR strData)
{
	// TODO: 여기에 디스패치 처리기를 추가합니다.
	// HTS용 일반 홈페이지
	CString	 strHtmlFilePath = GetRunTimePath() + "\\system\\html.ini";
	char szBuf[1024];
	int nIsHts = atoi(KSLink_GetLoginInfo(ISHTS));
	if (nType == 0)
	{
		CString strSUrl, strCUrl, strCName, strCData, strTemp;

		GetPrivateProfileString("SINGLE", "Home", "http://www.koreastock.co.kr", szBuf, 512, strHtmlFilePath);
		strCUrl = szBuf;
		strCUrl.TrimRight();

		strCName = "HTS_LOGIN";

		strCData = KSLink_GetLoginInfo("USER_ID") + "|";

		if (nIsHts == 1)
		{
			//KJI 20070704 (싱글사인)
			GetPrivateProfileString("SINGLE", "HomeCma", "http://www.smartcma.co.kr", szBuf, 512, strHtmlFilePath);
			strSUrl = szBuf;
			strSUrl.TrimRight();

			//KJI 20120425 (모의투자)
			if(	KSLink_GetLoginInfo(ISSIMULATION) != "1")
			{
				strTemp = KSLink_GetLoginInfo(USER_LEVEL);
				if(	strTemp != "6" && strTemp != "9")
					strCData += "Y|";	//개인, 기관
				else
					strCData += "N|";	//준회원, Guest

				if(	KSLink_GetLoginInfo(SIGNON_ERROR) == "Y")
					strCData +=  "N|";	//인증서 비정상
				else
					strCData +=  "Y|";	//인증서 정상

				if( KSLink_GetLoginInfo(SIGNON) == "N")
				{
					strCData += KSLink_GetLoginInfo(USER_PASSWORD);
				}
				else
				{
					strCData += KSLink_GetLoginInfo(USER_PASSWORD) + "|";
					strCData += KSLink_GetLoginInfo(PUBLIC_KEY)  + "|";
					strCData += strTemp + "|";
					strCData += KSLink_GetLoginInfo(CERT_DN);
				}
			}
			else
			{
				strCData += "N|";	//준회원, Guest
				strCData += "N|";	//인증서 비정상
				strCData += KSLink_GetLoginInfo(USER_PASSWORD);
			}

			//KJI 20070704 (싱글사인)
			strCData += "|";
			strTemp.Format("%s", KSLink_GetLoginInfo(CERT_DATA));

			//KJI 20120405 
			int nLoginSize = sizeof(LOGIN_IN);
			if(	strTemp.GetLength() > nLoginSize)
			{
				strCData += strTemp.Left(nLoginSize);
				strCData += "|";
				strCData += strTemp.Mid(nLoginSize);
			}
			else
			{
				//KJI 20120425 (모의투자)
				if(	KSLink_GetLoginInfo(ISSIMULATION) != "1")
				{
					if (KSLink_GetLoginInfo(USE_ORDERCERT) == "1")
					{
						strTemp = "Y";
					}
					else
					{
						strTemp = "N";
					}
				}
				else
					strTemp = "N";

				strCData += strTemp;
			}
		}
		else
		{
			strCData += KSLink_GetLoginInfo(USER_PASSWORD);
		}

		//KJI 20081229 (파일방식으로 쿠키생성 변경)
		CString strCDataEx, strTime, strBSData;

		CBase64Enc Encoder;
		Encoder.Encode(strCData);
		strBSData = Encoder.GetResult();

		CTime tCurTime = CTime::GetCurrentTime();
		tCurTime = tCurTime + CTimeSpan( 1, 0, 0, 0 );
		strTime = tCurTime.FormatGmt("expires = %a, %d-%b-%Y 00:00:00 GMT");

		strCDataEx.Format("%s; %s", strBSData, strTime);

		BOOL bRet;
		DWORD dwErrno;
		bRet = InternetSetCookie(strSUrl, "HTS_LOGIN", strCDataEx);
		dwErrno = GetLastError();
		bRet = InternetSetCookie(strCUrl, "HTS_LOGIN", strCDataEx);
		dwErrno = GetLastError();
	}
	else if (nType == 1)	// 스마트오피스용
	{
		CString strUrl, strUrlTemp, strCName, sData, sEnCodeData, strSmartOfficeUserId, strSmartOfficeUserPw;
		strSmartOfficeUserId = KSLink_GetLoginInfo("SMARTOFFICE_USERID");
		strSmartOfficeUserPw = KSLink_GetLoginInfo("SMARTOFFICE_PASSWD");
		strCName = "SOFFICE_SSO";
		if(strSmartOfficeUserId != "" && strSmartOfficeUserPw != "")
		{
			CString sField = " ";
			sData.Format("%s|%s|%s", strSmartOfficeUserId, strSmartOfficeUserPw, sField);

			CBase64Enc Encoder;
			Encoder.Encode(sData);

			CString sCUrl;
			GetPrivateProfileString("SINGLE", "smartoffice", "http://smartoffice.co.kr", szBuf, sizeof(szBuf), strHtmlFilePath);
			sCUrl = szBuf;
			sData = Encoder.GetResult();
			CInternetSession::SetCookie(sCUrl, strCName, sData);
		}
	}
	return VARIANT_TRUE;
}



#endif