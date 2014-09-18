#pragma once


interface IFrmInterface
{
public:
	~IFrmInterface(){};

	virtual void FormMsgBox(long nMsgID, LPCTSTR strText, LPCTSTR strCaption, short nType, short nIconType) = 0;

};


class IRunFormCtl;
template<class baseWnd>
class CFrmInterface : public IFrmInterface
{
public:
	CFrmInterface() : m_pFormCtrl(NULL)
	{

	}
	virtual void FormMsgBox(long nMsgID, LPCTSTR strText, LPCTSTR strCaption, short nType, short nIconType)
	{
		if(m_pFormCtrl != NULL)
			return m_pFormCtrl->FormMsgBox(nMsgID,strText,strCaption,nType,nIconType);
	}
protected:
	IRunFormCtl* m_pFormCtrl;
};