//*******************************************************************
// FileName：  IMCE_NetMsg.h
// Function：  网络中的消息接口，使用者可根据需要实现该接口
// Author: 
// Date:       2005-11-16
//*******************************************************************

#ifndef __IMCE_NET_MSG_H__
#define __IMCE_NET_MSG_H__


class CArchive;

// 定义网络消息类型 (该类型决定网络消息接口的实现类)
#define  MCE_NETMSG_BASE  1   // 基本网络消息，用于网络的连接和断开

class IMCE_NetMsg
{
public:
	virtual ~IMCE_NetMsg() {}

public:	

	// 复制	
	virtual IMCE_NetMsg*  Clone()=0;
	virtual void          CloneTo(IMCE_NetMsg* pMsg)=0;

	// 串行化
	virtual void Serialize(CArchive& ar)=0;  
	
	// 获取消息类型
	virtual UINT GetType()=0;

	// 获取成员变量
	virtual bool		 IsClose()=0;
	virtual bool         IsSendIP()=0;
	virtual const char*  GetHostName()=0;
	virtual const char*  GetIP()=0;

	// 设置成员变量
	virtual void     SetClose(bool bClose)=0;
	virtual void     SetSendIP(bool bSendIP)=0;
	virtual void     SetHostName(const char* szName)=0;
	virtual void     SetIP(const char* szIP)=0;	
};

#endif 
