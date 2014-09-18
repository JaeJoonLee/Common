//******************************************************************/
// All Rights Reserved. Copyright(c)   2005 (��)�ѱ��Ҹ���ġ        /
//******************************************************************/
/*! File Name     : CommDef.h
/*! Function      :	������� �������� 
/*! System Name   : TrBuilder
/*! Create        : ��â�� , 2006/03/15
/*! Update        : 
/*! Comment       : 
//******************************************************************/

#ifndef _COMMDEF_H_
#define _COMMDEF_H_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
  
// --> [Edit]  ������ 2006/05/04
/*
	������ ���Ͽ��� ���������� ���Ǵ� �κи� ���ܵΰ� 
	TrBuilder������ ���Ǵ� �κ��� '../Builder/TrBuidler/TrBuilderDef.h'
	���Ϸ� �̵� ��Ŵ.   
*/
// <-- [Edit]  ������ 2006/05/04

//====================================================================
// Tran Info Read/Write  
// By miru 2006.03.20 

#define SNULL		_T("")		// NULL ��Ʈ��

#define BEGIN_FUNCTION_MAP		_T("BEGIN_FUNCTION_MAP")	// TR ����
#define END_FUNCTION_MAP		_T("END_FUNCTION_MAP")		// TR ��

#define BEGIN_DATA_MAP			_T("BEGIN_DATA_MAP")	// TR DATA ����
#define END_DATA_MAP			_T("END_DATA_MAP")		// TR DATA ��

#define BEGIN					_T("begin")				// TR ������ ����
#define END						_T("end")				// TR ������ ��


// Tran Info ������ �ε���
enum TR_INDEX{ 
	TR_CODE=0,		// 1. Ʈ���ڵ� 
	TR_NAME,		// 2. Ʈ����
	TR_SERVER,		// 3. ���������� ���� 
	TR_TYPE,		// 4. ������ Ÿ�� 
	TR_ENCODE,		// 5. ��ȣȭ 
	TR_COMPRESS,	// 6. ���� 
	TR_CERTIFICATE,	// 7. ��������  
	TR_DESC,		// 8. ���� 
	TR_DBTYPE,		// 9. DB������ Ÿ�� 
}; 

// --> [Edit]  ������ 2006/06/16
// ���� Ÿ�� ����Ʈ�� ���� 'TranConfig.ini'���� �ε�
/*
// Tran ���� Ÿ�� �ε��� 
enum TR_SERVER_TYPE{
	LOCAL_SERVER=0,		//1. Local ����('1')
	TRAN_SERVER,		//2. Tr ����('2')
	MASTER_SERVER,		//3. Master ����('3')
	SYSTEM_SERVER,		//4. Tr ����('4')
};

// Tran ���� Ÿ�� ���ڿ�  
#define SZ_LOCAL_SERVER		_T("local")
#define SZ_TRAN_SERVER		_T("tran")
#define SZ_MASTER_SERVER	_T("master")
#define SZ_SYSTEM_SERVER	_T("system")
*/
// <-- [Edit]  ������ 2006/06/16

// Tran ������ Ÿ�� �ε��� 
enum TR_DATA_TYPE{
	STRUCTURED_DATA=0,		//1. Structured Data 
	STRING_FID,				//2. String FID
}; 

// Tran ������ Ÿ�� ���ڿ� 
// --> [Edit]  �̿��� 2008/03/05
//#define SZ_STRUCTURED_DATA	_T("structured data")
//#define SZ_STRING_FID		_T("string fid")
#define SZ_STRUCTURED_DATA	_T("TR ")
#define SZ_STRING_FID		_T("FID")
// <-- [Edit]  �̿��� 2008/03/05

// Tran ��ȣȭ Ÿ�� �ε��� 
enum TR_ENCODE_TYPE{
	ENCODE_NO=0,	//1. ��ȣȭ ��� ���� 
	ENCODE_YES,		//2. ��ȣȭ ��� 	
}; 
	
// Tran ��ȣȭ Ÿ�� ���ڿ� 
#define SZ_ENCODE_YES		_T("encode_yes")
#define SZ_ENCODE_NO		_T("encode_no")

// Tran ���� Ÿ�� �ε��� 
enum TR_COMPRESS_TYPE{
	COMPRESS_NO=0,	//1. ���� ��� ���� 
	COMPRESS_YES,	//2. ���� ���  
}; 
	
// Tran ���� Ÿ�� ���ڿ� 
#define SZ_COMPRESS_YES		_T("compress_yes")
#define SZ_COMPRESS_NO		_T("compress_no")

// Tran �������� Ÿ�� �ε��� 
enum TR_CERTIFICATE_TYPE{
	CERTIFICATE_NO=0,	//1. �������� ��� ���� 
	CERTIFICATE_YES		//2. �������� ��� 	
}; 
	
// Tran �������� Ÿ�� ���ڿ� 
#define SZ_CERTIFICATE_YES		_T("certificate_yes")
#define SZ_CERTIFICATE_NO		_T("certificate_no")

// Tran ���ڵ� ������ �ε���
enum TR_RECORD_INDEX{ 
	TR_RECORD_NAME=0,		// 1. ���ڵ� �� 
	TR_RECORD_DESC,			// 2. ���ڵ� ���� 
	TR_RECORD_IO,			// 3. ����� 
	TR_RECORD_ARRAY,		// 4. �迭  
	// --> [Edit]  ������ 2006/06/12
	TR_RECORD_ARRAY_INFO,	// 5. �迭 ����  
	// <-- [Edit]  ������ 2006/06/12
	TR_RECORD_BINARY		// 6. ���ڵ� ������ ���� 
};

// Tran ���ڵ� ����� Ÿ�� �ε���  
enum RECORD_IO_TYPE{
	IN_RECORD=0,		//1. �Է� 
	OUT_RECORD			//2. ��� 
}; 

// Tran ���ڵ� ����� Ÿ�� ���ڿ� 
#define SZ_IN_RECORD		_T("input") 
#define SZ_OUT_RECORD		_T("output") 

// Tran ���ڵ� ����� Ÿ�� ���ڿ�(�ѱ�) 
#define SZ_KOR_IN_RECORD		_T("�Է�") 
#define SZ_KOR_OUT_RECORD		_T("���") 


// Tran ���ڵ� �迭 Ÿ�� �ε��� 
enum TR_ARRAY_TYPE{
	SINGLE_RECORD   =0,	//1. 'Single'	 = 0x00
	ARRAY_TYPE_CHAR =1,	//1:���ڱ⺻
	ARRAY_TYPE_LONG =2,	//2:���ڱ⺻ 
	ARRAY_TYPE_ITEM =3,	//3:Item����, 
	ARRAY_TYPE_FIXED=4,	//4:����
}; 

// Tran ���ڵ� �迭 Ÿ�� ���ڿ� 
#define SZ_SINGLE_RECORD		_T("single") 
#define SZ_ARRAY_RECORD			_T("array") 

// Tran ���ڵ� �迭 Ÿ�� ���ڿ�(�ѱ�)  
#define SZ_KOR_SINGLE_RECORD	_T("����") 
#define SZ_KOR_ARRAY_RECORD		_T("�迭") 
  
// --> [Edit]  ������ 2006/05/18
// Tran ���ڵ� ������ ��� 
enum TR_RECORD_COMM_TYPE
{
	CHARACTER_BASE_RECORD = 0, // Charecter-base
	BINARY_BASE_RECORD		   // Binary-base 
};

// Tran ���ڵ� ������ ��� ���ڿ� 
#define SZ_CHARACTER_BASE_RECORD	_T("character-base")
#define SZ_BINARY_BASE_RECORD		_T("binary-base")

// <-- [Edit]  ������ 2006/05/18
 

// --> [Edit]  ������ 2006/05/18
// Tran ������ ������ �ε���
enum TR_ITEM_INDEX{ 	
	ITEM_TITLE=0,		// 1. Ÿ��Ʋ 
	ITEM_NAME,			// 2. Tran ������ �� 
	ITEM_ENGTITLE,		// 3. ����Ÿ��Ʋ  
	ITEM_FID,			// 4. FID 	
	ITEM_DATATYPE,		// 5. ������ ��   
	ITEM_DATALEN,		// 6. ������ ���� 
	ITEM_DECIAMLPOINT,	// 7. ������ ��(�Ҽ��� ����)  	
	ITEM_CONTROL,		// 8. ��Ʈ�� 
	ITEM_ATTRIBUTE,		// 9. ������ 
	ITEM_DESC,			//10. ���� 	
// --> [Edit]  �� �� �� 2006/07/19
	ITEM_DBDATATYPE,	//11. DB������ ��   
	ITEM_DBDATALEN,		//12. DB������ ���� 
	ITEM_DBDECIAMLPOINT//13. DB������ ��(�Ҽ��� ����)  	
// <-- [Edit]  �� �� �� 2006/07/19
};
// <-- [Edit]  ������ 2006/05/18


// Tran ������ ������ �� �ε��� 
enum TR_ITEM_DATA_TYPE{	
	FT_BYTE=0,			// unsigned char(8bit)
	FT_SHORT,			// int16
	FT_USHORT,			// unsigned int16 
	FT_LONG,			// int32
	FT_ULONG,			// unsigned int32 
	FT_FLOAT,			// float  (4 bytes)
	FT_DOUBLE,			// double (8 bytes) 
	FT_LONGLONG,		// int64  (8 bytes)   
	FT_STRING,			// �Ϲ� �ؽ�Ʈ 
	FT_STRINGNUM,		// ������ ���ڿ�
	FT_DATE,			// ������ 
	FT_DAY,				// ������ 
	FT_TIME				// �ð��� 
}; 

// Tran ������ ������ �� ���ڿ�  
#define SZ_BYTE			_T("byte")			// unsigned char(8bit)
#define SZ_SHORT		_T("short")			// int16
#define SZ_USHORT		_T("ushort")		// unsigned int16
#define SZ_LONG			_T("long")			// int32
#define SZ_ULONG		_T("ulong")			// unsigned int32 
#define SZ_FLOAT		_T("float")			// float  (4 bytes)
#define SZ_DOUBLE		_T("double")		// double (8 bytes) 
#define SZ_LONGLONG		_T("longlong")		// int64  (8 bytes)   
#define SZ_STRING		_T("string")		// �Ϲ� �ؽ�Ʈ 
#define SZ_STRINGNUM	_T("string num")	// �Ϲ� �ؽ�Ʈ -> ��ȣ�ִ�  string num
#define SZ_DATE			_T("string nsnum")	// ��¥�� -> ��ȣ����  string num
#define SZ_DAY			_T("day")			// ������ 
#define SZ_TIME			_T("time")			// �ð��� 
 

// --> [Edit]  ������ 2006/05/11
// Tran ������ ��Ʈ�� �� ��� 
// '../SrShare/sd_global.h'�� ��Ʈ�� ���� ��� ���  

// Tran ������ ��Ʈ�� �� ���ڿ� 
#define SZ_CT_NULL		_T("nouse")
#define SZ_KOR_CT_NULL	_T("������")
/*
// '../SrShare/sd_global.h'�� ��Ʈ�� ���ڿ� ���  
// --> ���ڿ� ����Ʈ�� m_GControlName�� ���� �� 
*/  	
// <-- [Edit]  ������ 2006/05/11


// Tran ������ ������ 
enum TR_ITEM_ATTRIBUTE_TYPE
{
	ATTRIBUTE_NO = 0,	// ������ ���� 
	ATTRIBUTE_YES		// ������ ���� 
}; 

// Tran ������ ������ ���ڿ�  
#define SZ_ATTRIBUTE_NO		_T("no")
#define SZ_ATTRIBUTE_YES	_T("yes")

// Tran ������ ������ �ѱ� ���ڿ� 
#define SZ_KOR_ATTRIBUTE_NO		_T("����")
#define SZ_KOR_ATTRIBUTE_YES	_T("����")  

// --> [Edit]  ������ 2006/03/23   
// DD ������ �巡�� �� ��� 
#define DDITEM_DRAG_DROP _T("DDItem_DragDrop")
// <-- [Edit]  ������ 2006/03/23



// --> [Edit]  ������ 2006/03/30
// Tran ������ �巡�� 
#define TRANINFO_DRAG_DROP _T("Tran_DragDrop")  

// Tran ������ �巡�� ���� 
enum TRANINFO_DRAG_TYPE{
						TRAN_DRAG_UNKNOWN = 0,	//������ ����
						TRAN_DRAG_QUERY,
						TRAN_DRAG_TRANINFO,		//Tran ��ü���� 
						TRAN_DRAG_TRANRECORD,	//Tran ���ڵ� 
						TRAN_DRAG_TRANITEM,		//Tran ������  
						TRAN_DRAG_MULTIITEM,	//Tran ���� ������  
						TRAN_DRAG_DB_TRANINFO,	//Tran ����(���ڵ� �� ������ ����Ʈ ������ ����)
						FID_DRAG_QUERY,
						FID_DRAG_INOUTBLOCK,
						FID_DRAG_GID,
						FID_DRAG_FID,
						REAL_DRAG_QUERY,
						REAL_DRAG_TRANINFO,		//Tran ��ü���� 
						REAL_DRAG_TRANRECORD,	//Tran ���ڵ� 
						REAL_DRAG_TRANITEM		//Tran ������ 
						}; 
// <-- [Edit]  ������ 2006/03/30


// --> [Edit]  ������ 2006/04/14
// üũ �ƿ�/�� ���ڿ�  
#define SZ_CHECK_IN		_T("CheckIn")
#define SZ_CHECK_OUT	_T("CheckOut")
// <-- [Edit]  ������ 2006/04/14

// üũ �ƿ�/�� ���ڿ�  
#define SZ_KOR_CHECK_IN		_T("üũ��(&I)")
#define SZ_KOR_CHECK_OUT	_T("üũ�ƿ�(&O)")

// --> [Edit]  ������ 2006/04/21
// ������ ���� Ʈ�� ���� ��� 
#define SZ_DGN_TRAN_FOLDER _T("\\dgn\\tran")
// <-- [Edit]  ������ 2006/04/21

// --> [Edit]  ������ 2006/04/25
#define UD_TRAN_DRAG_FILE_POS 512
// <-- [Edit]  ������ 2006/04/25
 

// --> [Edit]  ������ 2006/05/04


// --> [Edit]  ������ 2006/05/26
//=================================================================== 
// FID ������ ������ �巡�� 
#define FIDINFO_DRAG_DROP	_T("{{FID_DragDrop}}")  
  
// FID �巡�� Ÿ�� 
enum FID_DRAG_TYPE
{
	FIDINFO_DRAG_UNKNOWN = 0,		// Unknown FID ������ �巡��  
	FIDINFO_DRAG_TABLE,			// �ڵ����� ���̺� 	 
	FIDINFO_DRAG_ITEM,				// �ڵ����� ������ 

	FID_DRAG_UNKNOWN = 0,		// Unknown FID ������ �巡��  
	FID_DRAG_GIDFID_ITEM,		// GID�� FID ������ �巡��
	FID_DRAG_FID_ITEM,			// FID ������ �巡��
	FID_DRAG_DD_ITEM			// DD ������ �巡��


};
// <-- [Edit]  ������ 2006/05/26


//=================================================================== 
// Tran Ŭ������ ������ ���� �ĺ��� 
#define SZ_TRAN_CLIPBRD_MULTI_ITEM _T("{{FN_TranClipboard_MultiItem}}") 

#define SZ_TRAN_CLIPBRD_TRAN_CODE  _T("{{TranCode}}") 


//=================================================================== 
// �ڵ����� ���̺� �巡�� 
#define REALINFO_DRAG_DROP	_T("{{RealTable_DragDrop}}")  

// �ڵ����� ���̺� Ÿ�� 
enum REALINFO_DRAG_TYPE
{
	REALINFO_DRAG_UNKNOWN = 0,		// Unknown FID ������ �巡��  
	REALINFO_DRAG_TABLE,			// �ڵ����� ���̺� 	 
	REALINFO_DRAG_ITEM,				// �ڵ����� ������ 
};

//=================================================================== 
// Ʈ������ ȯ�� ���� 
#define SZ_TRAN_CONFIG_FILE		_T("\\dgn\\TranConfig.ini")


#endif//_COMMDEF_H_
