//***************************************************************************************
// FileName：VBF_MainCtrlImpl.h
// Function：图形集成框架接口的模板实现类。
//           该接口完成系统主框接口内容，负责控件注册、命令分发、事件处理、绘图等任务。
// Author:   杜莹
// Date:     2012-10-31
//***************************************************************************************

#ifndef __VBF_MAIN_CTRL_IMPL_H__
#define __VBF_MAIN_CTRL_IMPL_H__


// 标准接口
#include <VBF_OS.h>
#include <VBF_MainCtrl/IVBF_MainCtrl.h>
#include <VBF_MainCtrl/IVBF_Command.h>
#include <VBF_MainCtrl/IVBF_Message.h>
#include <VBF_MainCtrl/IVBF_Tool.h>
#include <VBF_MainCtrl/IVBF_UIProcessor.h>
#include <VBF_Common/VBF_Utils/VBF_DynamicLibrary.h>
#include <VBF_Base/ref_ptr>
#include <VBF_Base/observer_ptr>

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class CVBF_MainCtrlImpl : public T
{
	// 定义迭代器
	typedef std::map<std::string, std::vector<IVBF_Message*>*>	CMessageMap;
	typedef CMessageMap::iterator								CMessageMapIter;
//    typedef std::vector< observer_ptr<IVBF_Observer> >			CObserverList;
    typedef std::vector< IVBF_Observer*>			CObserverList;
public:
	CVBF_MainCtrlImpl(IVBF_MainCtrl* pIParent);
	virtual ~CVBF_MainCtrlImpl();

	virtual char* GetType() { return m_szType ; }

	virtual long  GetID() { return m_lID ; }
	virtual void  SetID(long lID) { m_lID = lID ; }

	virtual void  SetPurpose( const char* pPurpose ) { strcpy(m_szPurpose,pPurpose); }
	virtual char* GetPurpose( ) { return m_szPurpose ; }

	//---------------------------------------------------------------------------
	// IVBF_Observer
	//---------------------------------------------------------------------------
    virtual void OnEvent(const char* szMessage, int nValue = 0, void* pValue = NULL);


	//---------------------------------------------------------------------------
	// IVBF_Subject
	//---------------------------------------------------------------------------
    virtual void Attach(IVBF_Observer* pIObserver);
    virtual void Detach(IVBF_Observer* pIObserver);
    virtual void DetachAll();
    virtual void Notify(const char* szMessage, int nValue = 0, void* pValue = NULL);


	//---------------------------------------------------------------------------
	// IVBF_MainCtrl
	//---------------------------------------------------------------------------
	virtual void Release();
	virtual bool RemoveComponent(const char* szComponentID);
    virtual void* PreRemoveComponent(const char* szComponentFile);

    virtual bool RegisterComponentFile(const char* szComponentFile);
 	virtual bool RegisterComponentCfgFile(const char* szComponentCfgFile);
    virtual void RegisterComponentCfgFileDefault();
	virtual IVBF_Component* GetComponentPtr(const char* szComponentID);		

	virtual void* QueryInterface(const char* szInterfaceID,const char* szComponentID = NULL);	
	
	virtual bool ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam);
	virtual bool SelectTool(const char* szToolID);
	virtual const char* GetCurrentTool();
	
	virtual bool OnMouseEvent(int nMouseEvent, int nKeyStatus, int nX, int nY, int nDelta) { return true; }
	virtual bool OnKeyEvent(int nKeyEvent, int nChar, int nRepCount, int nFlag)  { return true; }

	virtual bool UpdateUI(const char* szCommandID, int* pEnable, int* pCheck, int* pRadio, char* szText);

	// 消息
	virtual void SubscribeMessage(const char* szMessage, IVBF_Component* pIComponent);
	virtual void UnSubscribeMessage(const char* szMessage, IVBF_Component* pIComponent);
    virtual void SendMessage(void* pSender,const char* szMessage, int nValue, void* pValue);

	virtual void SetActive(bool bActive); 

	virtual void  SetAppPath(const char* szPath);
	virtual char* GetAppPath()						{ return (m_pIParent!=NULL)? m_pIParent->GetAppPath(): m_szAppPath; }
    virtual void  SetSysSetPath(const char* szPath)	{ VBF_strcpy(m_szSysSetPath, szPath); }
	virtual char* GetSysSetPath()					{ return (m_pIParent!=NULL)? m_pIParent->GetSysSetPath(): m_szSysSetPath; }	


protected:
	bool RegisterComponentCfgFile_Path(const char* szComponentCfgFile, const char* szDllPath);	
	virtual bool InitComponent();
    virtual void ReleaseComponent();
    virtual IVBF_Component* RegisterComponentFile_(const char* szComponentFile);

protected:	
	IVBF_MainCtrl*					m_pIParent;					// 父主控的接口指针，可以为NULL
	bool							m_bComponentReleased;		// 所有组件是否都已释放 (避免向已释放的组件发送消息)

	// 该主控中需要自动加载的动态库，这些动态库属于主控的核心组件，不需要通过.cfg配置文件加载
        std::vector<std::string>                    m_vAutoLoadDllNames;

	char							m_szCfgFileName[256];		// cfg配置文件的文件名，不含路径和.cfg后缀，如"RegisterComponents"	
	bool							m_bActive;

	char							m_szAppPath[MAX_PATH];		// 系统路径
	char							m_szSysSetPath[MAX_PATH];

	char							m_szSelectedToolID[256];	// 当前选中的Tool	
	
	CObserverList					m_ObserverList;				// 事件观察器列表

    map<string, string>                 m_mapComponentDllNames;		// 需要注册的动态库的名字 (避免重复注册同一个动态库，杜莹添加：2011-03-29)
    std::vector<IVBF_Component*>		m_vRegComPtr;	// 注册成功的组件指针列表
    std::vector<VBF_DynamicLibrary*>	m_vRegComDll;	// 注册成功的组件DLL列表

    std::vector<IVBF_Command*>		m_vCommandIPtr;				// Command事件观察者列表
	vector<IVBF_Message*>			m_vMessageIPtr;				// Message事件观察者列表
	vector<IVBF_Tool*>				m_vToolIPtr;				// Tool事件观察者列表
	vector<IVBF_UIProcessor*>		m_vUIProcessorIPtr;			// UIProcessor事件观察者列表

	// 订购的消息
	CMessageMap					m_mapSubscribedMessageIPtr;	// 订购了指定消息的用户


	int  m_lID ;          // 主控对象唯一值   
	char m_szPurpose[32]; // 主控用途
	char m_szType[32];    // 主控类型
};

template<class T>
CVBF_MainCtrlImpl<T>::CVBF_MainCtrlImpl(IVBF_MainCtrl* pIParent)
{
	m_pIParent	= pIParent;

	// 所有组件是否都已释放 (避免向已释放的组件发送消息)
	m_bComponentReleased = false;

	// 主控组件是否激活
	m_bActive			= true;

	// 从主控中获取当前选中的Tool
	m_szSelectedToolID[0] = '\0';	

	// cfg配置文件的文件名，不含路径和.cfg后缀，如"RegisterComponents"
	m_szCfgFileName[0]	= '\0';
	m_szAppPath[0]		= '\0';
	m_szSysSetPath[0]	= '\0';

	m_vAutoLoadDllNames.clear();
}

template<class T>
CVBF_MainCtrlImpl<T>::~CVBF_MainCtrlImpl()
{
}
template<class T>
void CVBF_MainCtrlImpl<T>::ReleaseComponent()
{
    m_bComponentReleased = true;

    // 释放订购的Message列表
    for(CMessageMapIter iterMsg=m_mapSubscribedMessageIPtr.begin(); iterMsg!=m_mapSubscribedMessageIPtr.end(); iterMsg++)
    {
        vector<IVBF_Message*>* pvMessageIPtr = iterMsg->second;
        SAFE_DELETE(pvMessageIPtr);
    }
    m_mapSubscribedMessageIPtr.clear();

    // 按组件注册的逆序释放 (杜莹修改：2009-4-10)

    // 释放指针的同时，从vector中清除，避免在其它组件中成为野指针 (杜莹修改：2010-02-05)
    vector<IVBF_Component*>::reverse_iterator pIterCom = m_vRegComPtr.rbegin();
    while(pIterCom!=m_vRegComPtr.rend())
    {
        IVBF_Component* pIComponent = *pIterCom;
        SAFE_RELEASE(pIComponent);

        int nIndex = m_vRegComPtr.rend() - pIterCom - 1;
        vector<IVBF_Component*>::iterator pIterCurr = m_vRegComPtr.begin() + nIndex;
        m_vRegComPtr.erase(pIterCurr);

        pIterCom = m_vRegComPtr.rbegin();
    }
    m_vRegComPtr.clear();

    // 释放动态库
    std::vector<VBF_DynamicLibrary*>::reverse_iterator  pIterComDll;
    for(pIterComDll=m_vRegComDll.rbegin(); pIterComDll!=m_vRegComDll.rend(); pIterComDll++)
    {
        VBF_DynamicLibrary* pLib = *pIterComDll;
        SAFE_DELETE(pLib);
    }
    m_vRegComDll.clear();
    m_mapComponentDllNames.clear();
}
//-----------------------------------------------------------------------------------
// 函数：Release()
// 描述：释放接口本身
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::Release()
{
    ReleaseComponent();
	delete this;
}

//-----------------------------------------------------------------------------------
// 函数：SetAppPath()
// 描述：设置应用程序的路径
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::SetAppPath(const char* szPath)
{
    VBF_strcpy(m_szAppPath, szPath);

	// 创建日志文件(文本格式)，以便各个组件向其中写入相关信息 (如出错信息)
	char szLogPath[MAX_PATH];
    VBF_sprintf(szLogPath, "%s/VBF_3DLog", m_szAppPath);
}

//-----------------------------------------------------------------------------------
// 函数：OnEvent()
// 描述：响应事件
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::OnEvent(const char* szMessage, int nValue, void* pValue)
{
}

//-----------------------------------------------------------------------------------
// 函数：Attach()
// 描述：添加一个事件观察者(IVBF_Subject中的纯虚函数)
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::Attach(IVBF_Observer* pIObserver)
{
	// 不允许添加空指针
    if(NULL==pIObserver) return;

	// 不允许重复添加
    CObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
    if(pIter==m_ObserverList.end()) m_ObserverList.push_back(pIObserver);
}

//-----------------------------------------------------------------------------------
// 函数：Detach()
// 描述：释放一个事件观察者(IVBF_Subject中的纯虚函数)
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::Detach(IVBF_Observer* pIObserver)
{
    // 不允许添加空指针
    if(NULL==pIObserver) return;

    CObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
	if(pIter!=m_ObserverList.end()) m_ObserverList.erase(pIter);
}

//-----------------------------------------------------------------------------------
// 函数：DetachAll()
// 描述：释放所有事件观察者(IVBF_Subject中的纯虚函数)
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::DetachAll()
{
	m_ObserverList.clear();
}

//-----------------------------------------------------------------------------------
// 函数：Notify()
// 描述：向所有事件观察者发送事件
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::Notify(const char* szMessage, int nValue, void* pValue)
{
    for(CObserverList::iterator pIter=m_ObserverList.begin(); pIter!=m_ObserverList.end(); pIter++)
    {
        //observer_ptr<IVBF_Observer>& pIObserver = *pIter;
		//if(pIObserver.valid()) pIObserver->OnEvent(szMessage, nValue, pValue);
		IVBF_Observer* pIObserver = *pIter;
        if(pIObserver) pIObserver->OnEvent(szMessage, nValue, pValue);
	}
}

//-----------------------------------------------------------------------------------
// 函数：RegisterComponentFile()
// 描述：根据指定的组件动态库文件，注册组件
// 参数：szComponentFile -- 组件所在动态库的文件路径(完整路径，含路径和.dll后缀)
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::RegisterComponentFile(const char* szComponentFile)
{
    map<string, string>::iterator pIter = m_mapComponentDllNames.find(szComponentFile);
    if(pIter!=m_mapComponentDllNames.end())
    {
        OSG_NOTICE<<"已经注册过"<< szComponentFile << std::endl;
        return true;
    }

    OSG_NOTICE<<"注册"<< szComponentFile << std::endl;


    IVBF_Component* pIComponent = RegisterComponentFile_(szComponentFile);
    if(pIComponent==NULL) return false;

    string sComID = pIComponent->GetComponentID();
    m_mapComponentDllNames.insert( map<string, string>::value_type(szComponentFile, sComID) );


    // 初始化各组件
    if(!pIComponent->Init()) return false;

    // 记录Command事件观察者接口
    IVBF_Command* pICommand = (IVBF_Command*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_COMMAND);
    if(pICommand!=NULL) m_vCommandIPtr.push_back(pICommand);

    // 记录Message事件观察者接口
    IVBF_Message* pIMessage = (IVBF_Message*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_MESSAGE);
    if(pIMessage!=NULL) m_vMessageIPtr.push_back(pIMessage);

    // 记录Tool事件观察者接口
    IVBF_Tool* pITool = (IVBF_Tool*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_TOOL);
    if(pITool!=NULL) m_vToolIPtr.push_back(pITool);

    // 记录UIProcessor事件观察者接口
    IVBF_UIProcessor* pIUIProcessor = (IVBF_UIProcessor*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_UIPROCESSOR);
    if(pIUIProcessor!=NULL) m_vUIProcessorIPtr.push_back(pIUIProcessor);

    return true;
}

//-----------------------------------------------------------------------------------
// 函数：RegisterComponentFile_()
// 描述：根据指定的组件动态库文件，注册组件
// 参数：szComponentFile -- 组件所在动态库的文件路径(完整路径，含路径和.dll后缀)
//-----------------------------------------------------------------------------------
template<class T>
IVBF_Component* CVBF_MainCtrlImpl<T>::RegisterComponentFile_(const char* szComponentFile)
{
    if(strlen(szComponentFile)==0) return NULL;

#ifdef WIN32
    typedef IVBF_Component* (__cdecl *VBF_CreateComponentObjectProc) ( IVBF_MainCtrl* );
#else
    typedef IVBF_Component* (*VBF_CreateComponentObjectProc) ( IVBF_MainCtrl* );
#endif

    // 装载动态库
    VBF_DynamicLibrary* pLib = VBF_DynamicLibrary::loadLibrary(szComponentFile);
    if(NULL==pLib)
    {
        char szErr[256];
        VBF_sprintf(szErr, "%s 装载不成功!", szComponentFile);
        //std::cout << szErr << std::endl;
        OSG_NOTICE<< szErr <<std::endl;

        return NULL;
	}
		
	// 创建组件接口
    VBF_CreateComponentObjectProc CreateComponentObject = (VBF_CreateComponentObjectProc)pLib->getProcAddress("VBF_CreateComponentObject");
	if(NULL==CreateComponentObject)
	{
        delete pLib;  // 注意：立即释放该动态库的句柄

		char szErr[256];
        VBF_sprintf(szErr, "%s 没有导出VBF_CreateComponentObject()函数!", szComponentFile);

		std::cout << szErr << std::endl;
        return NULL;
	}

	IVBF_Component* pIComponent = CreateComponentObject( (IVBF_MainCtrl*)this );
    if(NULL==pIComponent) return NULL;

	// 记录组件动态库句柄和接口指针，以便释放
    m_vRegComDll.push_back(pLib);
    m_vRegComPtr.push_back(pIComponent);

    return pIComponent;
}

//-----------------------------------------------------------------------------------
// 函数：RegisterComponentCfgFileDefault()
// 描述：注册已加入系统中的全部组件
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::RegisterComponentCfgFileDefault()
{
	if( strlen(m_szCfgFileName)==0 ) return;

	// 避免重复注册同一个动态库 (杜莹添加：2011-03-29)
	m_mapComponentDllNames.clear();

	// 先注册需要自动加载的动态库，这些动态库属于主控的核心组件，不需要通过.cfg配置文件加载
	for(unsigned int i=0; i<m_vAutoLoadDllNames.size(); i++)
	{
		string strDllName = m_vAutoLoadDllNames[i];
		if(strDllName=="") continue;

		char szComponentFile[MAX_PATH];
        VBF_sprintf(szComponentFile, "%s", strDllName.c_str());

        IVBF_Component* pIComponent = RegisterComponentFile_(szComponentFile);
        if(pIComponent==NULL) continue;

        string sComID = pIComponent->GetComponentID();

		// 避免重复注册同一个动态库
        m_mapComponentDllNames.insert( map<string, string>::value_type(strDllName, sComID) );
	}

	// 注册该主控的基本组件 	
	char szComponentConfigFn[MAX_PATH];
#ifdef _DEBUG
    VBF_sprintf(szComponentConfigFn, "%s/3DMap/%sD.cfg", GetSysSetPath(), m_szCfgFileName);
#else
    VBF_sprintf(szComponentConfigFn, "%s/3DMap/%s.cfg", GetSysSetPath(), m_szCfgFileName);
#endif

	RegisterComponentCfgFile(szComponentConfigFn);

	// 初始化所有组件
	InitComponent();
}

//-----------------------------------------------------------------------------------
// 函数：RegisterComponentCfgFile_Path()
// 描述：根据指定的组件配置文件，注册组件
//       组件配置文件中包含要注册的一组组件动态库名称
// 参数：szDllPath          -- 动态库文件所在的路径
//       szComponentCfgFile -- 组件所在配置文件的全路径名 (杜莹修改：2011-03-28)
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::RegisterComponentCfgFile_Path(const char* szComponentCfgFile, const char* szDllPath)
{
	//从配置文件中获取需要注册的动态库名	
	FILE* fp = NULL;
	if( !::VBF_fopen(szComponentCfgFile, "rt", fp) )
	{
		return false;
	}
	
	vector<string> asComponentDllNames;

	char szTemp[MAX_PATH] = {'\0'};
	while( !feof(fp) )
	{
		szTemp[0] = '\0';
		::VBF_fscanf(fp, "%s", szTemp, MAX_PATH);

		if(strlen(szTemp)==0) continue;
#ifdef WIN32
        char szComFileName[MAX_PATH] = {0};
		//HG 修改
#ifdef _DEBUG
		::VBF_sprintf(szComFileName, "%sd.dll",szTemp);
#else
		::VBF_sprintf(szComFileName, "%s.dll",szTemp);
#endif
#else
        char szComFileName[MAX_PATH] = {0};
        ::VBF_sprintf(szComFileName, "lib%s.so",szTemp);
#endif
		// 避免重复注册同一个动态库 (杜莹添加：2011-03-29)
        map<string, string>::iterator pIter = m_mapComponentDllNames.find(szComFileName);
        if(pIter!=m_mapComponentDllNames.end() || strlen(szComFileName)==0) continue;

        m_mapComponentDllNames.insert( map<string, string>::value_type(szComFileName, szComFileName) );
        asComponentDllNames.push_back(string(szComFileName));
	}
	fclose(fp);

	// 注册所有组件	
    int numComponents = asComponentDllNames.size();
    for(int i=0; i<numComponents; i++)
	{
		char sComponentDllName[MAX_PATH];
		VBF_sprintf(sComponentDllName, "%s/%s", szDllPath, asComponentDllNames[i].c_str());
		if(strlen(sComponentDllName)==0) continue;		

		// 注册单个组件
        IVBF_Component* pIComponent = RegisterComponentFile_(sComponentDllName);
        if(pIComponent==NULL) continue;

        string sComID = pIComponent->GetComponentID();

        map<string, string>::iterator pIter = m_mapComponentDllNames.find(asComponentDllNames[i].c_str());
        if(pIter!=m_mapComponentDllNames.end())
        {
            (*pIter).second = sComID;
        }
	}

	return true;
}


//-----------------------------------------------------------------------------------
// 函数：RegisterComponentCfgFile()
// 描述：根据指定的组件配置文件，注册组件
//       组件配置文件中包含要注册的一组组件动态库名称
// 参数：szComponentCfgFile -- 组件所在配置文件的全路径名 (杜莹修改：2011-03-28)
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::RegisterComponentCfgFile(const char* szComponentCfgFile)
{
	return RegisterComponentCfgFile_Path(szComponentCfgFile, GetAppPath());
}

//-----------------------------------------------------------------------------------
// 函数：InitComponent()
// 描述：初始化所有组件
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::InitComponent()
{
	vector<IVBF_Component*>::iterator pIter;
	for(pIter=m_vRegComPtr.begin(); pIter!=m_vRegComPtr.end(); pIter++)
	{
		IVBF_Component* pIComponent = *pIter;
		if(NULL==pIComponent) continue;

		// 初始化各组件
		if(!pIComponent->Init()) continue;
	
		// 记录Command事件观察者接口
		IVBF_Command* pICommand = (IVBF_Command*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_COMMAND);
		if(pICommand!=NULL) m_vCommandIPtr.push_back(pICommand);

		// 记录Message事件观察者接口
		IVBF_Message* pIMessage = (IVBF_Message*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_MESSAGE);
		if(pIMessage!=NULL) m_vMessageIPtr.push_back(pIMessage);

		// 记录Tool事件观察者接口
		IVBF_Tool* pITool = (IVBF_Tool*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_TOOL);
		if(pITool!=NULL) m_vToolIPtr.push_back(pITool);

		// 记录UIProcessor事件观察者接口
		IVBF_UIProcessor* pIUIProcessor = (IVBF_UIProcessor*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_UIPROCESSOR);
		if(pIUIProcessor!=NULL) m_vUIProcessorIPtr.push_back(pIUIProcessor);
	}	

	return true;
}

//-----------------------------------------------------------------------------------
// 函数：RemoveComponent()
// 描述：删除指定组件
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::RemoveComponent(const char* szComponentFile)
{
    string sComponentID;
    map<string, string>::iterator pIter = m_mapComponentDllNames.find(szComponentFile);
    if(pIter==m_mapComponentDllNames.end()) return false;
    {
        sComponentID = (*pIter).second;
    }


    if(m_vRegComPtr.size()!=m_vRegComDll.size()) return false;

    IVBF_Component* pIComponent = GetComponentPtr(sComponentID.c_str());

    int idx=0;
    for(idx=0;idx<m_vRegComPtr.size();idx++)
    {
        if(pIComponent==m_vRegComPtr[idx])
        {
            m_vRegComPtr.erase(m_vRegComPtr.begin() + idx);
            break;
        }
    }
    // 先通知卸载组件的消息
    SendMessage(this,VBF_MESSAGE_UNREGIST_COM,0,&sComponentID);

    SAFE_RELEASE(pIComponent);

    VBF_DynamicLibrary* pLib = m_vRegComDll[idx];
    m_vRegComDll.erase(m_vRegComDll.begin() + idx);
    SAFE_DELETE(pLib);


    vector<IVBF_Component*>::iterator iterIComponentPtr;
    for(iterIComponentPtr=m_vRegComPtr.begin(); iterIComponentPtr!=m_vRegComPtr.end(); iterIComponentPtr++)

    m_mapComponentDllNames.erase(szComponentFile);

    OSG_NOTICE<<"卸载"<< szComponentFile << std::endl;



	return true;
}
template<class T>
void* CVBF_MainCtrlImpl<T>::PreRemoveComponent(const char* szComponentFile)
{
    string sComponentID;
    map<string, string>::iterator pIter = m_mapComponentDllNames.find(szComponentFile);
    if(pIter==m_mapComponentDllNames.end()) return NULL;
    {
        sComponentID = (*pIter).second;
    }

    if(m_vRegComPtr.size()!=m_vRegComDll.size()) return false;

    IVBF_Component* pIComponent = GetComponentPtr(sComponentID.c_str());

    int idx=0;
    for(idx=0;idx<m_vRegComPtr.size();idx++)
    {
        if(pIComponent==m_vRegComPtr[idx])
        {
            m_vRegComPtr.erase(m_vRegComPtr.begin() + idx);
            break;
        }
    }
    // 先通知卸载组件的消息
    SendMessage(this,VBF_MESSAGE_UNREGIST_COM,0,&sComponentID);

    SAFE_RELEASE(pIComponent);

    VBF_DynamicLibrary* pLib = m_vRegComDll[idx];
    m_vRegComDll.erase(m_vRegComDll.begin() + idx);

    vector<IVBF_Component*>::iterator iterIComponentPtr;
    for(iterIComponentPtr=m_vRegComPtr.begin(); iterIComponentPtr!=m_vRegComPtr.end(); iterIComponentPtr++)

    m_mapComponentDllNames.erase(szComponentFile);

    OSG_NOTICE<<"卸载"<< szComponentFile << std::endl;

    return pLib;
}
//-----------------------------------------------------------------------------------
// 函数：GetComponentPtr()
// 描述：根据组件的ID，获取组件的接口指针
//-----------------------------------------------------------------------------------
template<class T>
IVBF_Component* CVBF_MainCtrlImpl<T>::GetComponentPtr(const char* szComponentID)
{
	vector<IVBF_Component*>::iterator iterIComponentPtr;
	for(iterIComponentPtr=m_vRegComPtr.begin(); iterIComponentPtr!=m_vRegComPtr.end(); iterIComponentPtr++)
	{
		IVBF_Component* pIComponent = *iterIComponentPtr;
		if(NULL==pIComponent) continue;

		if( strcmp(pIComponent->GetComponentID(), szComponentID)==0 ) return pIComponent;
	}
	return NULL;
}

//-----------------------------------------------------------------------------------
// 函数：QueryInterface()
// 描述：获取某个接口的指针
//-----------------------------------------------------------------------------------
template<class T>
void* CVBF_MainCtrlImpl<T>::QueryInterface(const char* szInterfaceID, const char* szComponentID)
{
	if(NULL==szInterfaceID || strlen(szInterfaceID)==0) return NULL;	

	// 查找组件
	vector<IVBF_Component*>::iterator iterIComponentPtr;
	for(iterIComponentPtr=m_vRegComPtr.begin(); iterIComponentPtr!=m_vRegComPtr.end(); iterIComponentPtr++)
	{
		IVBF_Component* pIComponent = *iterIComponentPtr;
		if(pIComponent==NULL) return NULL;

		void* pIInterface = pIComponent->QueryInterface(szInterfaceID);
		if(pIInterface!=NULL) return pIInterface;
	}
	
	return NULL;
}

//-----------------------------------------------------------------------------------
// 函数：ExecuteCommand()
// 描述：执行命令
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam)
{
	vector<IVBF_Command*>::iterator iterCommandIPtr;
	for(iterCommandIPtr=m_vCommandIPtr.begin(); iterCommandIPtr!=m_vCommandIPtr.end(); iterCommandIPtr++)
	{
		IVBF_Command* pICommand = *iterCommandIPtr;
		if(pICommand->ExecuteCommand(szCommandID, pInParam, pOutParam)) return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------
// 函数：SelectTool()
// 描述：设置当前使用的工具
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::SelectTool(const char* szToolID)
{
	// 如果当前工具发生改变，先通知各个组件取消上次的工具 (杜莹添加：2006-5-21)
	if( strlen(m_szSelectedToolID)>0 && strcmp(m_szSelectedToolID, szToolID)!=0 )
	{
		vector<IVBF_Tool*>::iterator iterToolIPtr;
		for(iterToolIPtr = m_vToolIPtr.begin();iterToolIPtr!=m_vToolIPtr.end();iterToolIPtr++)
		{
			IVBF_Tool* pITool = *iterToolIPtr;
			if(pITool->OnToolUnSelected(m_szSelectedToolID, NULL)!=0) break;
		}
	}

    ::VBF_strcpy(m_szSelectedToolID, szToolID);

	vector<IVBF_Tool*>::iterator pIter;
	for(pIter=m_vToolIPtr.begin();pIter!=m_vToolIPtr.end();pIter++)
	{
		IVBF_Tool* pITool = *pIter;
		if(pITool->OnToolSelected(szToolID, NULL)!=0) return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------
// 函数：GetCurrentTool()
// 描述：获取当前使用的工具
//-----------------------------------------------------------------------------------
template<class T>
const char* CVBF_MainCtrlImpl<T>::GetCurrentTool()
{
	return m_szSelectedToolID;
}

//-----------------------------------------------------------------------------------
// 函数：UpdateUI()
// 描述：更新UI
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::UpdateUI(const char* szCommandID, int* pEnable, int* pCheck, int* pRadio, char* szText)
{
	vector<IVBF_UIProcessor*>::iterator iterUIProcessorIPtr;
	for(iterUIProcessorIPtr=m_vUIProcessorIPtr.begin(); iterUIProcessorIPtr!=m_vUIProcessorIPtr.end(); iterUIProcessorIPtr++)
	{
		IVBF_UIProcessor* pIUIProcessor = *iterUIProcessorIPtr;
		if(pIUIProcessor->UpdateUI(szCommandID, pEnable, pCheck, pRadio, szText)) return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------
// 函数：SubscribeMessage()
// 描述：订购消息
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::SubscribeMessage(const char* szMessage, IVBF_Component* pIComponent)
{
	vector<IVBF_Message*>* pvMessageIPtr = NULL;

	CMessageMapIter pIterator = m_mapSubscribedMessageIPtr.find(szMessage);
	if( pIterator!=m_mapSubscribedMessageIPtr.end() )  // 找到
	{
		pvMessageIPtr = pIterator->second;
	}
	else                                     // 没找到
	{
		pvMessageIPtr = new vector<IVBF_Message*>;
		m_mapSubscribedMessageIPtr.insert( CMessageMap::value_type(szMessage, pvMessageIPtr) );
	}

	IVBF_Message* pIMessage = (IVBF_Message*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_MESSAGE);
	if(pIMessage!=NULL) pvMessageIPtr->push_back( pIMessage );
}

//-----------------------------------------------------------------------------------
// 函数：UnSubscribeMessage()
// 描述：取消订购的消息
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::UnSubscribeMessage(const char* szMessage, IVBF_Component* pIComponent)
{
	vector<IVBF_Message*>* pvMessageIPtr = NULL;

	CMessageMapIter pIterator = m_mapSubscribedMessageIPtr.find(szMessage);
	if(pIterator==m_mapSubscribedMessageIPtr.end()) return;

	pvMessageIPtr = pIterator->second;

	IVBF_Message* pIMessageDel = (IVBF_Message*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_MESSAGE);
	if(pIMessageDel!=NULL) 
	{
		vector<IVBF_Message*>::iterator iterMessageIPtr;
		for(iterMessageIPtr=pvMessageIPtr->begin(); iterMessageIPtr!=pvMessageIPtr->end(); iterMessageIPtr++)
		{
			IVBF_Message* pIMessage = *iterMessageIPtr;
			if(pIMessage==pIMessageDel) pvMessageIPtr->erase( iterMessageIPtr );
		}
	}
}

//-----------------------------------------------------------------------------------
// 函数：SendMessage()
// 描述：向每一个注册的Component发送消息
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::SendMessage(void* pSender,const char* szMessage, int nValue, void* pValue)
{
	// 避免向已释放的组件发送消息
	if(m_bComponentReleased) return;

	Notify(szMessage,nValue,pValue);	
	
	// 向每个订购了该消息的Component发送消息
	vector<IVBF_Message*>* pvMessageIPtr = NULL;
	CMessageMapIter pIterator = m_mapSubscribedMessageIPtr.find(szMessage);
	if(pIterator==m_mapSubscribedMessageIPtr.end()) return;

	pvMessageIPtr = pIterator->second;
	
	vector<IVBF_Message*>::iterator iterMessageIPtr;
	for(iterMessageIPtr=pvMessageIPtr->begin(); iterMessageIPtr!=pvMessageIPtr->end(); iterMessageIPtr++)
	{
		IVBF_Message* pIMessage = *iterMessageIPtr;
		pIMessage->OnMessage(pSender,szMessage, nValue, pValue);	
	}
}

//-----------------------------------------------------------------------------------
// 函数：SetActive()
// 描述：激活该主控
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::SetActive(bool bActive)
{
	m_bActive = bActive;
}


#endif 
