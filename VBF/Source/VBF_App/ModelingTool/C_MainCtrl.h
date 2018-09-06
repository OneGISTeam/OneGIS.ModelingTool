#pragma once
#include "C_ManagerSTObject.h"
#include "C_Broadcaster.h"
#include "C_AccessFileSTObject.h"

class C_MainCtrl
{
public:
	C_MainCtrl(void);
	~C_MainCtrl(void);

	static C_MainCtrl* instance();

	IC_ManagerSTObject* objectManager() {return m_pObjectManager;}; 

	C_Broadcaster* broadCaster() {return m_pBroadCaster;};

private:
	static C_MainCtrl* m_sInstance;

	//对象管理器
	IC_ManagerSTObject* m_pObjectManager;

	//广播站
	C_Broadcaster* m_pBroadCaster;

	//C_AccessFileSTObject* m_pAccessObject;
};

