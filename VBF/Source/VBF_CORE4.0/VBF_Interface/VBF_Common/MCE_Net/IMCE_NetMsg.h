//*******************************************************************
// FileName��  IMCE_NetMsg.h
// Function��  �����е���Ϣ�ӿڣ�ʹ���߿ɸ�����Ҫʵ�ָýӿ�
// Author: 
// Date:       2005-11-16
//*******************************************************************

#ifndef __IMCE_NET_MSG_H__
#define __IMCE_NET_MSG_H__


class CArchive;

// ����������Ϣ���� (�����;���������Ϣ�ӿڵ�ʵ����)
#define  MCE_NETMSG_BASE  1   // ����������Ϣ��������������ӺͶϿ�

class IMCE_NetMsg
{
public:
	virtual ~IMCE_NetMsg() {}

public:	

	// ����	
	virtual IMCE_NetMsg*  Clone()=0;
	virtual void          CloneTo(IMCE_NetMsg* pMsg)=0;

	// ���л�
	virtual void Serialize(CArchive& ar)=0;  
	
	// ��ȡ��Ϣ����
	virtual UINT GetType()=0;

	// ��ȡ��Ա����
	virtual bool		 IsClose()=0;
	virtual bool         IsSendIP()=0;
	virtual const char*  GetHostName()=0;
	virtual const char*  GetIP()=0;

	// ���ó�Ա����
	virtual void     SetClose(bool bClose)=0;
	virtual void     SetSendIP(bool bSendIP)=0;
	virtual void     SetHostName(const char* szName)=0;
	virtual void     SetIP(const char* szIP)=0;	
};

#endif 
