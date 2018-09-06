//*******************************************************************
// FileName��  MCE_NetMsg.h
// Function��  ���������������Ϣ������������ӺͶϿ�
// Author:     
// Date:       
//*******************************************************************

#ifndef __MCE_NET_MSG_BASE_H__
#define __MCE_NET_MSG_BASE_H__

#include "VBF_Common/MCE_Net/IMCE_NetMsg.h"

#define VBF_NETMSG_CAMERA  (MCE_NETMSG_BASE + 1)
#define VBF_NETMSG_EVENT   (MCE_NETMSG_BASE + 2)
#define VBF_NETMSG_MODEL   (MCE_NETMSG_BASE + 3)

class CMCE_NetMsgBase : public IMCE_NetMsg
{
public:
	CMCE_NetMsgBase()
	{
		m_bClose		= FALSE;
		m_bSendIP		= FALSE;
		m_strHostName	= "";
		m_strIP			= "";
	}
	virtual ~CMCE_NetMsgBase(){}

	virtual IMCE_NetMsg* Clone() //����һ����Ϣ����
	{
		CMCE_NetMsgBase* pMsg = new CMCE_NetMsgBase;

		CloneTo(pMsg);
		return pMsg;
	}
	virtual void CloneTo(IMCE_NetMsg* pMsg)//���Ƶ���һ����Ϣ
	{
		ASSERT(pMsg);

		CMCE_NetMsgBase* pMsgT = (CMCE_NetMsgBase*)pMsg;

		pMsgT->m_bClose      = m_bClose;
		pMsgT->m_bSendIP     = m_bSendIP;
		pMsgT->m_strHostName = m_strHostName;
		pMsgT->m_strIP       = m_strIP;
	}

	// ��ȡ��Ա����
	virtual bool        IsClose()				{ return (m_bClose==1);  }
	virtual bool        IsSendIP()				{ return (m_bSendIP==1); }
	virtual const char* GetHostName()			{ return (const char*)m_strHostName; }
	virtual const char* GetIP()					{ return (const char*)m_strIP; }

	// ���ó�Ա����
	virtual void     SetClose(bool bClose)               { m_bClose  = bClose;  }
	virtual void     SetSendIP(bool bSendIP)             { m_bSendIP = bSendIP; }
	virtual void     SetHostName(const char* szName)	 { if(szName!=NULL) m_strHostName = szName; }
	virtual void     SetIP(const char* szIP)			 { if(szIP!=NULL)   m_strIP = szIP; }

	// ���л�
	virtual void Serialize(CArchive& ar)
	{
		if (ar.IsStoring())  // д�ļ���������Ϣ
		{
			ar << m_bClose;
			ar << m_bSendIP;
			ar << m_strHostName;
			ar << m_strIP;
		}
		else                 // ���ļ���������Ϣ
		{
			ar >> m_bClose;
			ar >> m_bSendIP;
			ar >> m_strHostName;
			ar >> m_strIP;
		}	
	}
	
	// ��ȡ������Ϣ����
	virtual UINT GetType() { return MCE_NETMSG_BASE; }

protected:
	BOOL		m_bClose;       // ����Ҫ���л�����CArchive�ֲ�֧��ar>>bool������ֻ��ʹ��BOOL
	BOOL		m_bSendIP;
	CString		m_strHostName;
	CString		m_strIP;
};


#endif 
