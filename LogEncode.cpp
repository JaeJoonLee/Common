//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (��)�ѱ��Ҹ���ġ        
//******************************************************************
//  File Name     : LogEncode.cpp
//  Function      : �α׳��� ��ȣȭ/��ȣȭ ó���� Ŭ����
//  System Name   : JumunLib
//  Create        : �̿��� , 2008/05/25
//  Update        : ��ȣ��, 2009/09/23 VS 2008 Upgrade�� ���� �۾�
//  Comment       : ��Ÿ UACó��
//******************************************************************

// LogMsg.cpp: implementation of the CLogMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogEncode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//******************************************************************
//  Function Name : CLogEncode
//  Function      : �ʱ� ������
//  Param         : ����
//  Return        : ���� 
//  Create        : 
//  Update        : ��ȣ��, 2009/09/23 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CLogEncode::CLogEncode()
{
	memset(EncOldPass, 0, 10);
	memset(EncNewPass, 0, 10);

//	char cEncOldPass[5] = "�a��"; // ������������� "�ڵ�" 
	memcpy(EncOldPass, "�a��", 4);
}
//******************************************************************
//  Function Name : ~CLogEncode
//  Function      : �Ҹ���
//  Param         : ����
//  Return        : ���� 
//  Create        : 
//  Update        : ��ȣ��, 2009/09/23 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CLogEncode::~CLogEncode()
{

}
//******************************************************************
//  Function Name : GenNewPassword
//  Function      : 
//  Param         :	int StrLen
//  Return        :	void 
//  Create        : 
//  Update        : ��ȣ��, 2009/09/23 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
void CLogEncode::GenNewPassword(int StrLen)
{
	unsigned char countL, countH;

	countL = StrLen-1;
	countH = (StrLen-1)>>8;

	EncNewPass[0] = EncOldPass[1] ^ EncOldPass[3] ^ countL;
	EncNewPass[1] = EncOldPass[0] ^ EncOldPass[2] ^ countH;
}
//******************************************************************
//  Function Name : EncryptStr
//  Function      : 
//  Param         :	char *pStr, int StrLen
//  Return        :	void 
//  Create        : 
//  Update        : ��ȣ��, 2009/09/23 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
void CLogEncode::EncryptStr(char *pStr, int StrLen)
{
	int i;

	char cTmp;
	for(i = 0; i < StrLen; i++)
	{
		cTmp = *(pStr+i);
		*(pStr+i) = i%2 == 0 ? *(pStr+i) ^ EncOldPass[0] ^ EncOldPass[1] ^ EncNewPass[0]
							 : *(pStr+i) ^ EncOldPass[2] ^ EncOldPass[3] ^ EncNewPass[1];
		if(*(pStr+i) == 0x0D || *(pStr+i) == 0x0A || *(pStr+i) == 0x00 || cTmp == 0x0D || cTmp == 0x0A || cTmp == 0x00)
			*(pStr+i) = cTmp;
	}
}
//******************************************************************
//  Function Name : DecryptStr
//  Function      : 
//  Param         :	char *pStr, int StrLen
//  Return        :	void 
//  Create        : 
//  Update        : ��ȣ��, 2009/09/23 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
void CLogEncode::DecryptStr(char *pStr, int StrLen)
{
	int i;

	for(i = 0; i < StrLen; i++)
	{
		*(pStr+i) = i%2 == 0 ? *(pStr+i) ^ EncOldPass[0] ^ EncOldPass[1] ^ EncNewPass[0]
							 : *(pStr+i) ^ EncOldPass[2] ^ EncOldPass[3] ^ EncNewPass[1];
	}
}
