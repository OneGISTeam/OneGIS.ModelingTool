//*******************************************************************
// FileName��  IMCE_Net.h
// Function��  �������ӽӿ�
// Author: 
// Date:       2005-11-15
//*******************************************************************

#ifndef __IMCE_NET_H__
#define __IMCE_NET_H__

class IMCE_NetMsg;
class IMCE_NetMsgReceiver;
class IMCE_DataBase;


//---------------------------------------------------------------------------
// �оٿ���ʹ�õ����������ɫ����
//---------------------------------------------------------------------------
const char  MCE_NETROLE_NONE[]			= "��";
const char  MCE_NETROLE_CLIENT[]		= "�ͻ�";
const char  MCE_NETROLE_SERVER[]		= "������";
const char  MCE_NETROLE_CLIENTSERVER[]  = "�ͻ��������";


class IMCE_Net
{
public:
	virtual ~IMCE_Net() {}

public:

	virtual bool InitNet()=0;
	virtual bool InitNet(const char* szNetType, UINT unPort, const char* szServerIP="")=0;
	virtual void UnlinkNet()=0;

	virtual void FreeLink()=0;
	virtual bool IsNetInit()=0;

	virtual bool ReplyMsgServer(IMCE_NetMsg* pMsg)=0;
	virtual bool ReplyMsgClient(IMCE_NetMsg* pMsg)=0;
	virtual void SendMsg(IMCE_NetMsg* pMsg)=0;

	virtual bool IsNetFrameVisible()=0;
	virtual void ShowNetProperties()=0;
	virtual void UpdatePage(int nPage)=0;
	virtual void ClearUMTable()=0;

	virtual bool IsOwner(const char* strHostorIP)=0;

	virtual void UpdateReciLog(IMCE_NetMsg* pMsg, int nOpe=0, bool bSuc=true)=0;
	virtual void UpdateSendLog(const char* strIP, IMCE_NetMsg* pMsg, int nOpe=0, bool bSuc=true)=0;
	
	virtual IMCE_NetMsg* CreateNetMsg(UINT uType)=0;

	virtual void SetNetMsgReceiver(IMCE_NetMsgReceiver* pIMsgReceiver)=0;
	virtual void SetNetDB(const char* strNetDBFullPathName, IMCE_DataBase* pINetDB)=0;
	virtual void EnableSend(bool bEnabled)=0;

	// ��ȡ�����ӵĿͻ�������
	virtual int  GetUserCount()=0; 
};

#endif 
