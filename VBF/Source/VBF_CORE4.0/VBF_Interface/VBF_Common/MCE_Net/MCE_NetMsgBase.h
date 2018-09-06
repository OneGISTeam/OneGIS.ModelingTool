//*******************************************************************
// FileName：  MCE_NetMsg.h
// Function：  网络中最基本的消息，用于完成连接和断开
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

	virtual IMCE_NetMsg* Clone() //创建一份消息复制
	{
		CMCE_NetMsgBase* pMsg = new CMCE_NetMsgBase;

		CloneTo(pMsg);
		return pMsg;
	}
	virtual void CloneTo(IMCE_NetMsg* pMsg)//复制到另一个消息
	{
		ASSERT(pMsg);

		CMCE_NetMsgBase* pMsgT = (CMCE_NetMsgBase*)pMsg;

		pMsgT->m_bClose      = m_bClose;
		pMsgT->m_bSendIP     = m_bSendIP;
		pMsgT->m_strHostName = m_strHostName;
		pMsgT->m_strIP       = m_strIP;
	}

	// 获取成员变量
	virtual bool        IsClose()				{ return (m_bClose==1);  }
	virtual bool        IsSendIP()				{ return (m_bSendIP==1); }
	virtual const char* GetHostName()			{ return (const char*)m_strHostName; }
	virtual const char* GetIP()					{ return (const char*)m_strIP; }

	// 设置成员变量
	virtual void     SetClose(bool bClose)               { m_bClose  = bClose;  }
	virtual void     SetSendIP(bool bSendIP)             { m_bSendIP = bSendIP; }
	virtual void     SetHostName(const char* szName)	 { if(szName!=NULL) m_strHostName = szName; }
	virtual void     SetIP(const char* szIP)			 { if(szIP!=NULL)   m_strIP = szIP; }

	// 串行化
	virtual void Serialize(CArchive& ar)
	{
		if (ar.IsStoring())  // 写文件：发送消息
		{
			ar << m_bClose;
			ar << m_bSendIP;
			ar << m_strHostName;
			ar << m_strIP;
		}
		else                 // 读文件：接收消息
		{
			ar >> m_bClose;
			ar >> m_bSendIP;
			ar >> m_strHostName;
			ar >> m_strIP;
		}	
	}
	
	// 获取网络消息类型
	virtual UINT GetType() { return MCE_NETMSG_BASE; }

protected:
	BOOL		m_bClose;       // 由于要串行化，而CArchive又不支持ar>>bool，所以只能使用BOOL
	BOOL		m_bSendIP;
	CString		m_strHostName;
	CString		m_strIP;
};


#endif 
