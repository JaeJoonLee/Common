#if !defined (_HEADERFILE_DEFINE_OF_CODE_H)
#define _HEADERFILE_DEFINE_OF_CODE_H


// #include "../../_include/DefineCode.h"


typedef struct
{
    char gb             ;       /* '1':�ֽ�, '2':�ڽ���    */
								//���� ���� 							= "1";
								//�ڽ��� ���� 						= "2";
								//�������� 							= "3";
								//����, �������� 						= "4";
								//�ɼ� 								= "5";
								//ä�� 								= "8";
								//�������� 							= "9";
								//ETF�ڵ� 							= "A";
								//KOSPI 200 ����, KOSPI 100 ����, �峻����, KRX, KRX���� = "B";
								//�ڽ��� ����, �ڽ��� 50 				= "C";
								//�����ֽĿɼ�  						= "G";
								//����������� 						= "L";
								//��Ÿ���� 							= "M";
								//�ֽĿ���Ʈ ELW 						= "N";
	char code       [ 10];      /* �����ڵ�                */
} TR_CODEINFO;
#define  TR_CODEINFO_SIZE sizeof(TR_CODEINFO)

typedef struct : public TR_CODEINFO
{
    char codeName       [40+1];	/* �����                */
} TR_CODEINFOEX;

typedef CList<TR_CODEINFOEX, TR_CODEINFOEX>		LIST_TR_CODEINFO;
//typedef CList<TR_CODEINFO, TR_CODEINFO>		LIST_TR_CODEINFO; //�������� ����.


#endif // _HEADERFILE_DEFINE_OF_CODE_H
