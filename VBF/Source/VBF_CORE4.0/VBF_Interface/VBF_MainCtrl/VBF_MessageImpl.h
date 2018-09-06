//***************************************************************************************
// FileName��VBF_MessageImpl.h
// Function����Ϣ��Ӧ�ӿڵ�ģ��ʵ����
// Author:   ��Ө
// Date:     2012-10-31
//***************************************************************************************

#ifndef __VBF_MESSAGE_IMPL_H__
#define __VBF_MESSAGE_IMPL_H__


#include "VBF_MainCtrl/IVBF_Message.h"
#include <VBF_MainCtrl/IVBF_MainCtrl.h>
#include <vector>
#include <string.h>

class CVBF_MessageImpl : public IVBF_Message
{
public:
	CVBF_MessageImpl(IVBF_MainCtrl* pIMainCtrl);
	virtual ~CVBF_MessageImpl() {}	
	
	virtual int			GetMessageCount()			{ return m_vPubMessagesID.size(); }
	virtual const char* GetMessageID(int nIndex)	{ return ( nIndex>=0 && nIndex<(int)m_vPubMessagesID.size() )? m_vPubMessagesID[nIndex] : NULL; }
    virtual void		OnMessage(void* pSender,const char* szMessage, int nValue, void* pValue) {}
	virtual void		SubscribeMessage();
	
public:
	virtual void Release() { delete this; }

protected:	
	IVBF_MainCtrl*			m_pIMainCtrl;		// ��������ڵ����أ�������3DMainCtrl, Ҳ����������������
	const char*				m_szComponentID;	// �������ID

	std::vector<const char*>		m_vPubMessagesID;	// �������������Ϣ
	std::vector<const char*>		m_vSubMessageID;	// �������������Ϣ
};

//---------------------------------------------------------------------------------
// ������CVBF_MessageImpl()
// ���������캯��
//---------------------------------------------------------------------------------
inline CVBF_MessageImpl::CVBF_MessageImpl(IVBF_MainCtrl* pIMainCtrl)
{
	m_pIMainCtrl    = pIMainCtrl;
	m_szComponentID = "";
}

//---------------------------------------------------------------------------------
// ������SubscribeMessage()
// ������������Ϣ
//---------------------------------------------------------------------------------
inline void CVBF_MessageImpl::SubscribeMessage()
{
	if(NULL==m_pIMainCtrl || strlen(m_szComponentID)==0) return;	

	IVBF_Component* pIComponent = m_pIMainCtrl->GetComponentPtr(m_szComponentID);
	if(NULL==pIComponent) return;

	std::vector<const char*>::iterator iterMessage;
	for(iterMessage=m_vSubMessageID.begin(); iterMessage!=m_vSubMessageID.end(); iterMessage++)
	{
		const char* szMessage = *iterMessage;
		m_pIMainCtrl->SubscribeMessage(szMessage, pIComponent);
	}
}


#endif 
