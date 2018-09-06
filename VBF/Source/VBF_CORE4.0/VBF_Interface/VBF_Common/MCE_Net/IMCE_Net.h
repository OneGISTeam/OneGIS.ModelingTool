//*******************************************************************
// FileName：  IMCE_Net.h
// Function：  网络连接接口
// Author: 
// Date:       2005-11-15
//*******************************************************************

#ifndef __IMCE_NET_H__
#define __IMCE_NET_H__

class IMCE_NetMsg;
class IMCE_NetMsgReceiver;
class IMCE_DataBase;


//---------------------------------------------------------------------------
// 列举可以使用的三种网络角色类型
//---------------------------------------------------------------------------
const char  MCE_NETROLE_NONE[]			= "无";
const char  MCE_NETROLE_CLIENT[]		= "客户";
const char  MCE_NETROLE_SERVER[]		= "服务器";
const char  MCE_NETROLE_CLIENTSERVER[]  = "客户与服务器";


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

	// 获取已连接的客户端总数
	virtual int  GetUserCount()=0; 
};

#endif 
