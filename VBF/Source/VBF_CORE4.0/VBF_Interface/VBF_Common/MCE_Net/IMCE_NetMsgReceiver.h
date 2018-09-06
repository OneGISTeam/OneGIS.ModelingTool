//*******************************************************************
// FileName：  IMCE_NetMsgReceiver.h
// Function：  网络中的消息接收者，完成消息的创建和接收后的处理
// Author: 
// Date:       2005-11-16
//*******************************************************************

#ifndef __IMCE_NET_MSG_RECEIVER_H__
#define __IMCE_NET_MSG_RECEIVER_H__

class IMCE_NetMsg;

class IMCE_NetMsgReceiver
{
public:
	virtual ~IMCE_NetMsgReceiver() {}

public:	
	// 创建消息
	virtual IMCE_NetMsg*  CreateNetMsg(UINT uType)=0;

	// 处理消息
	virtual bool  ProcessNetMsg(IMCE_NetMsg* pMsg)=0;
};

#endif 
