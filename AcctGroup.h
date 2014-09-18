#ifndef	__ACCT_GROUP
#define __ACCT_GROUP

#include <afxtempl.h>


typedef struct 
{
	CString strAcctNo;		// ���¹�ȣ
	CString strMultiple;	// �¼�
	int     nIndex;			// �ε���
} TAcctMap;

class CAcctGroup
{
public:
	CAcctGroup();
	~CAcctGroup();
	CAcctGroup & operator = (CAcctGroup &theSrc);
	void Serialize(CArchive &ar);
	
	CString			strGroupName;	// �׷��
	CArray <TAcctMap*, TAcctMap*>	arrAcctList;
};

#endif
