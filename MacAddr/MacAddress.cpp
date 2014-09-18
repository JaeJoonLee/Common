//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (��)�ѱ��Ҹ���ġ        
//******************************************************************
//  File Name     : MacAddress.cpp
//  Function      : �ƾ�巹�� ��� Ŭ����	
//  System Name   : CommApi
//  Create        : 
//  Update        : ��ȣ��, 2009/10/08 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//*****************************************************************
// MacAddress.cpp: implementation of the CMacAddress class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "HardDisk.h"
#include "MacAddress.h"

#include "nb30.h"
//#include "winsock2.h"

#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "ws2_32.lib")


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

typedef struct _tagADAPTER
{
  ADAPTER_STATUS adapt;
  NAME_BUFFER    NameBuff [256];
}ADAPTER, *LPADAPTER;

ADAPTER adapter;

#define MAX_MAC_ADDRESS_IN_BYTE    6
#define MAX_MAC_ADDRESS_IN_STRING  12
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//******************************************************************
//  Function Name : CMacAddress
//  Function      : ������
//  Param         : ����
//  Return        : ���� 
//  Create        : 
//  Update        : ��ȣ��, 2009/10/08 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CMacAddress::CMacAddress()
{

}

//******************************************************************
//  Function Name : ~CMacAddress
//  Function      : �Ҹ���
//  Param         : ����
//  Return        : ���� 
//  Create        : 
//  Update        : ��ȣ��, 2009/10/08 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CMacAddress::~CMacAddress()
{

}

//******************************************************************
//  Function Name : GetMacAddress
//  Function      : �ش� �����ǿ� �ش��ϴ� �ƾ�巹���� ����Ѵ�
//  Param         : CString strIP
//  Return        : CString 
//  Create        : BT.Jung , 2008/02/20
//  Update        : ��ȣ��, 2009/10/08 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString CMacAddress::GetMacAddress(CString strIP) 
{
	strIP.TrimRight();
	if(strIP.IsEmpty())
	{
		strIP = getIP();
	//	strIP = KSLink_GetLoginInfo(REMOTE_ADDR);	// ����IP
	//	strIP = KSLink_GetLoginInfo(LOCAL_ADDR);	// �����IP(�缳IP)
	}

    NCB Ncb;
    UCHAR uRetCode;
    LANA_ENUM lenum;
    CString strOutput;

    memset( &Ncb, 0, sizeof(Ncb) );
    Ncb.ncb_command = NCBENUM;
    Ncb.ncb_buffer = (UCHAR *)&lenum;
    Ncb.ncb_length = sizeof(lenum);
    uRetCode = Netbios( &Ncb );
	TRACE( "The NCBENUM return code is: 0x%x \n", uRetCode );

    for(int i=0; i < lenum.length ;i++)
    {
        memset( &Ncb, 0, sizeof(Ncb) );
        Ncb.ncb_command = NCBRESET;
        Ncb.ncb_lana_num = lenum.lana[i];

        uRetCode = Netbios( &Ncb );
		TRACE( "The NCBRESET on LANA %d return code is: 0x%x \n", lenum.lana[i], uRetCode );

        memset( &Ncb, 0, sizeof (Ncb) );
        Ncb.ncb_command = NCBASTAT;
        Ncb.ncb_lana_num = lenum.lana[i];

        strcpy( (char*)Ncb.ncb_callname,strIP ); 
        Ncb.ncb_buffer = (unsigned char *) &adapter;
        Ncb.ncb_length = sizeof(ADAPTER);

        uRetCode = Netbios( &Ncb );
		TRACE( "The NCBASTAT on LANA %d return code is: 0x%x \n", lenum.lana[i], uRetCode );
        if ( uRetCode == NRC_GOODRET )
        {
			strOutput.Format("%02X%02X%02X%02X%02X%02X",
				adapter.adapt.adapter_address[0],
				adapter.adapt.adapter_address[1],
				adapter.adapt.adapter_address[2],
				adapter.adapt.adapter_address[3],
				adapter.adapt.adapter_address[4],
				adapter.adapt.adapter_address[5] );

		 	return strOutput;
       }
    }
    
	return strOutput;
}

//******************************************************************
//  Function Name : GetMacAddress
//  Function      : �ش� �����ǿ� �ش��ϴ� �ƾ�巹���� ����Ѵ�
//  Param         : BYTE* byteMacAddress(0), CString strIP(i)
//  Return        : BOOL 
//  Create        : BT.Jung , 2008/02/21
//  Update        : ��ȣ��, 2009/10/08 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
BOOL CMacAddress::GetMacAddress(BYTE* byteMacAddress, CString strIP) 
{
	if(byteMacAddress == NULL)
	{
		return FALSE;
	}
	
	strIP.TrimRight();
	if(strIP.IsEmpty())
	{
		strIP = getIP();
	//	strIP = KSLink_GetLoginInfo(REMOTE_ADDR);	// ����IP
	//	strIP = KSLink_GetLoginInfo(LOCAL_ADDR);	// �����IP(�缳IP)
	}

    NCB Ncb;
    UCHAR uRetCode;
    LANA_ENUM lenum;
    
	memset(byteMacAddress, 0, MAX_MAC_ADDRESS_IN_BYTE);

    memset( &Ncb, 0, sizeof(Ncb) );
    Ncb.ncb_command = NCBENUM;
    Ncb.ncb_buffer = (UCHAR *)&lenum;
    Ncb.ncb_length = sizeof(lenum);
    uRetCode = Netbios( &Ncb );
	TRACE( "The NCBENUM return code is: 0x%x \n", uRetCode );

    for(int i=0; i < lenum.length ;i++)
    {
        memset( &Ncb, 0, sizeof(Ncb) );
        Ncb.ncb_command = NCBRESET;
        Ncb.ncb_lana_num = lenum.lana[i];

        uRetCode = Netbios( &Ncb );
		TRACE( "The NCBRESET on LANA %d return code is: 0x%x \n", lenum.lana[i], uRetCode );

        memset( &Ncb, 0, sizeof (Ncb) );
        Ncb.ncb_command = NCBASTAT;
        Ncb.ncb_lana_num = lenum.lana[i];

        strcpy( (char*)Ncb.ncb_callname, strIP ); 
        Ncb.ncb_buffer = (unsigned char *) &adapter;
        Ncb.ncb_length = sizeof(ADAPTER);

        uRetCode = Netbios( &Ncb );
		TRACE( "The NCBASTAT on LANA %d return code is: 0x%x \n", lenum.lana[i], uRetCode );
        if ( uRetCode == NRC_GOODRET )
        {
			memcpy(byteMacAddress, adapter.adapt.adapter_address, MAX_MAC_ADDRESS_IN_BYTE);
		 	return TRUE;
       }
    }
    
	return FALSE;
}

//******************************************************************
//  Function Name : GetMacAddress
//  Function      : �ƾ�巹���� 2���̻��ϰ�� 
//  Param         : ����
//  Return        : CString 
//  Create        : BT.Jung , 2008/02/20
//  Update        : ��ȣ��, 2009/10/08 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString CMacAddress::GetMacAddress()
{
	CString string;
    CString strOutput =_T("");

	NCB Ncb;
	UCHAR uRetCode;
	LANA_ENUM   lenum;

	memset( &Ncb, 0, sizeof(Ncb) );
	Ncb.ncb_command = NCBENUM;
	Ncb.ncb_buffer = (UCHAR *)&lenum;
	Ncb.ncb_length = sizeof(lenum);
	
	uRetCode = Netbios( &Ncb );

	TRACE( "The NCBENUM return code is: 0x%x \n", uRetCode );
	TRACE( "The NCBENUM lenum.length is: 0x%x \n", lenum.length );

	for(int i=0; i < lenum.length ;i++)
	{
		memset( &Ncb, 0, sizeof(Ncb) );
		Ncb.ncb_command = NCBRESET;
		Ncb.ncb_lana_num = lenum.lana[i];

		uRetCode = Netbios( &Ncb );
		TRACE( "The NCBRESET on LANA %d return code is: 0x%x \n",
		lenum.lana[i], uRetCode );

		memset( &Ncb, 0, sizeof (Ncb) );
		Ncb.ncb_command = NCBASTAT;
		Ncb.ncb_lana_num = lenum.lana[i];

		memset(&Ncb.ncb_callname, ' ', NCBNAMSZ);
		Ncb.ncb_callname[0] = '*';
		Ncb.ncb_buffer = (unsigned char *)&adapter;
		Ncb.ncb_length = sizeof(ADAPTER);

		uRetCode = Netbios( &Ncb );
		TRACE( "The NCBASTAT on LANA %d return code is: 0x%x \n", lenum.lana[i], uRetCode );
		if( uRetCode == NRC_GOODRET )
		{
			string.Format("%02X%02X%02X%02X%02X%02X",
				adapter.adapt.adapter_address[0],
				adapter.adapt.adapter_address[1],
				adapter.adapt.adapter_address[2],
				adapter.adapt.adapter_address[3],
				adapter.adapt.adapter_address[4],
				adapter.adapt.adapter_address[5] );
           
			strOutput += string;
		}
	}

	return strOutput;
}

//******************************************************************
//  Function Name : getIP
//  Function      : 
//  Param         : ����
//  Return        : CString 
//  Create        : BT.Jung , 2006/10/12
//  Update        : ��ȣ��, 2009/10/08 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString CMacAddress::getIP()
{
	WORD wVersionRequested;
    WSADATA wsaData;
    char name[255];
	CString ip;
    PHOSTENT hostinfo;
    wVersionRequested = MAKEWORD( 2, 0 );

    if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
    {
            if( gethostname ( name, 255) == 0)
			{
                  if((hostinfo = gethostbyname(name)) != NULL)
                  {
                        ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
				  }
				  else
				  {
						ip = RegGetIP();
				  }
	         }
		     else
			 {
					ip = RegGetIP();
			 }
		WSACleanup( );
	} 
	else
	{
		ip = RegGetIP();
	}
	return ip;
}

//******************************************************************
//  Function Name : RegGetIP
//  Function      : 
//  Param         : ����
//  Return        : CString 
//  Create        : 
//  Update        : ��ȣ��, 2009/10/08 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString CMacAddress::RegGetIP()
{
	int i;
	BOOL bEscape = FALSE;
	CString ip;
	for(i=0;(i<=8) && (bEscape == FALSE);)
	{
		CString strPath, strKey;
		ip.Format("%s", " ");
		strPath = "System\\CurrentControlSet\\Services\\Class\\NetTrans";
		strKey.Format("%s\\%04d", strPath, i );
		ip = GetStrValue(HKEY_LOCAL_MACHINE, strKey, "IPAddress", ip);
		if(ip.CompareNoCase(" ") == 0 || ip.CompareNoCase("0.0.0.0") == 0 || ip.CompareNoCase("127.0.0.1")==0) 
			i++;
		else  
			bEscape = TRUE;
	}
	return ip;
}

//******************************************************************
//  Function Name : GetStrValue
//  Function      : 
//  Param         : HKEY Hkey,CString strkey, CString strsubkey,CString strRValue
//  Return        : CString 
//  Create        : 
//  Update        : ��ȣ��, 2009/10/08 VS 2008 Upgrade�� ���� �۾�
//  Comment       : 
//******************************************************************
CString CMacAddress::GetStrValue(HKEY Hkey,CString strkey, CString strsubkey,CString strRValue)
{
   LONG err;
   HKEY openKey;
   BYTE Data[128];
   DWORD type;
   DWORD size=sizeof(Data);

   err=::RegOpenKey(Hkey,strkey,&openKey);

   if(ERROR ==err)
	 err=::RegQueryValueEx(openKey,strsubkey,0,&type,Data,&size);

	if(err==ERROR_SUCCESS)
	{
	 ::RegCloseKey(openKey);
	 CString str(Data);
	 return str;
	}
	::RegCloseKey(openKey);

	return strRValue;
}