#if !defined(_COMMSEPDEF_H_)
#define _COMMSEPDEF_H_

// ������ ������ ���Ե� ������ ���� .
#define US						(BYTE)0x1F				// ������ ��Ҹ� �и��ϴ� ����(Unit Separator)
#define FS						(BYTE)0x1E				// ��Ʈ�� ������ �����ڷ� ��� (Field Separator)
#define PS						(BYTE)0x0D				// ������ KEY FID�� ������ �� �����ڷ� ���.
#define RS						(BYTE)0x0A				// ������ ���ڵ尡 ������ �� ROW�����ڷ� ���.
#define IS						(BYTE)0x7F				// FID�� �Է� ������ ������ �����ڷ� ���.

#define	GS						US
#define	CS						PS						// Control������

#define _TCH_US					US
#define _TCH_FS					FS
#define _TCH_PS					PS
#define _TCH_RS					RS
#define _TCH_IS					IS

#endif // !defined(_COMMSEPDEF_H_)
