#include "C_MainCtrl.h"

C_MainCtrl* C_MainCtrl::m_sInstance = NULL;

C_MainCtrl::C_MainCtrl(void)
{
	m_sInstance = this;

	m_pBroadCaster = new C_Broadcaster;

	m_pObjectManager = new C_ManagerSTObject();	

	//m_pAccessObject = new C_AccessFileSTObject();
}


C_MainCtrl::~C_MainCtrl(void)
{
}

C_MainCtrl* C_MainCtrl::instance()
{
	if(!m_sInstance){
		m_sInstance = new C_MainCtrl;
	}
	return m_sInstance;
}
