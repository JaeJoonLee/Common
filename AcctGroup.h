#ifndef	__ACCT_GROUP
#define __ACCT_GROUP

#include <afxtempl.h>


typedef struct 
{
	CString strAcctNo;		// °èÁÂ¹øÈ£
	CString strMultiple;	// ½Â¼ö
	int     nIndex;			// ÀÎµ¦½º
} TAcctMap;

class CAcctGroup
{
public:
	CAcctGroup();
	~CAcctGroup();
	CAcctGroup & operator = (CAcctGroup &theSrc);
	void Serialize(CArchive &ar);
	
	CString			strGroupName;	// ±×·ì¸í
	CArray <TAcctMap*, TAcctMap*>	arrAcctList;
};

#endif
