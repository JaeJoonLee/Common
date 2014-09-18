#include "stdafx.h"
#include "AcctGroup.h"

CAcctGroup::CAcctGroup()
{
}

CAcctGroup::~CAcctGroup()
{
	for (int i = 0; i < arrAcctList.GetSize(); i++)
	{
		delete arrAcctList.GetAt(i);
	}
	arrAcctList.RemoveAll();
}

CAcctGroup & CAcctGroup::operator = (CAcctGroup &theSrc)
{
	strGroupName = theSrc.strGroupName;

	for (int i = 0; i < theSrc.arrAcctList.GetSize(); i++)
	{
		TAcctMap* pAcctMap = new TAcctMap;
		pAcctMap->strAcctNo		= theSrc.arrAcctList.GetAt(i)->strAcctNo;	// °èÁÂ¹øÈ£
		pAcctMap->strMultiple	= theSrc.arrAcctList.GetAt(i)->strMultiple;	// ½Â¼ö
		pAcctMap->nIndex    	= theSrc.arrAcctList.GetAt(i)->nIndex;		// ÀÎµ¦½º

		arrAcctList.Add(pAcctMap);		
	}
	
	return theSrc;
}

void CAcctGroup::Serialize(CArchive &ar)
{
	if (ar.IsLoading()) 
	{
		// Read
		ar >> strGroupName;
		int cnt;
		ar >> cnt;
		for (int  i =0; i < cnt; i++)
		{
			TAcctMap* pAcctMap = new TAcctMap;
			ar >> pAcctMap->strAcctNo;		// °èÁÂ¹øÈ£
			ar >> pAcctMap->strMultiple;	// ½Â¼ö
			ar >> pAcctMap->nIndex;			// ÀÎµ¦½º
		
			arrAcctList.Add(pAcctMap);
		}
	}
	else
	{
		// Write
		ar << strGroupName;
		ar << arrAcctList.GetSize();
		for (int i = 0; i < arrAcctList.GetSize(); i++)
		{
			TAcctMap* pAcctMap = arrAcctList.GetAt(i);
			ar << pAcctMap->strAcctNo;		// °èÁÂ¹øÈ£
			ar << pAcctMap->strMultiple;	// ½Â¼ö
			ar << pAcctMap->nIndex;			// ÀÎµ¦½º
		}
	}
}