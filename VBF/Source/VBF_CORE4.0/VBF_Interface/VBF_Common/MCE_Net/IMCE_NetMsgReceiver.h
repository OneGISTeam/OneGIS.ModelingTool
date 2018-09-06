//*******************************************************************
// FileName��  IMCE_NetMsgReceiver.h
// Function��  �����е���Ϣ�����ߣ������Ϣ�Ĵ����ͽ��պ�Ĵ���
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
	// ������Ϣ
	virtual IMCE_NetMsg*  CreateNetMsg(UINT uType)=0;

	// ������Ϣ
	virtual bool  ProcessNetMsg(IMCE_NetMsg* pMsg)=0;
};

#endif 
