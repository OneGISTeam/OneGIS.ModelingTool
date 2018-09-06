//***************************************************************************************
// FileName��VBF_MainCtrlImpl.h
// Function��ͼ�μ��ɿ�ܽӿڵ�ģ��ʵ���ࡣ
//           �ýӿ����ϵͳ����ӿ����ݣ�����ؼ�ע�ᡢ����ַ����¼�������ͼ������
// Author:   ��Ө
// Date:     2012-10-31
//***************************************************************************************

#ifndef __VBF_MAIN_CTRL_IMPL_H__
#define __VBF_MAIN_CTRL_IMPL_H__


// ��׼�ӿ�
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
	// ���������
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

	// ��Ϣ
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
	IVBF_MainCtrl*					m_pIParent;					// �����صĽӿ�ָ�룬����ΪNULL
	bool							m_bComponentReleased;		// ��������Ƿ����ͷ� (���������ͷŵ����������Ϣ)

	// ����������Ҫ�Զ����صĶ�̬�⣬��Щ��̬���������صĺ������������Ҫͨ��.cfg�����ļ�����
        std::vector<std::string>                    m_vAutoLoadDllNames;

	char							m_szCfgFileName[256];		// cfg�����ļ����ļ���������·����.cfg��׺����"RegisterComponents"	
	bool							m_bActive;

	char							m_szAppPath[MAX_PATH];		// ϵͳ·��
	char							m_szSysSetPath[MAX_PATH];

	char							m_szSelectedToolID[256];	// ��ǰѡ�е�Tool	
	
	CObserverList					m_ObserverList;				// �¼��۲����б�

    map<string, string>                 m_mapComponentDllNames;		// ��Ҫע��Ķ�̬������� (�����ظ�ע��ͬһ����̬�⣬��Ө��ӣ�2011-03-29)
    std::vector<IVBF_Component*>		m_vRegComPtr;	// ע��ɹ������ָ���б�
    std::vector<VBF_DynamicLibrary*>	m_vRegComDll;	// ע��ɹ������DLL�б�

    std::vector<IVBF_Command*>		m_vCommandIPtr;				// Command�¼��۲����б�
	vector<IVBF_Message*>			m_vMessageIPtr;				// Message�¼��۲����б�
	vector<IVBF_Tool*>				m_vToolIPtr;				// Tool�¼��۲����б�
	vector<IVBF_UIProcessor*>		m_vUIProcessorIPtr;			// UIProcessor�¼��۲����б�

	// ��������Ϣ
	CMessageMap					m_mapSubscribedMessageIPtr;	// ������ָ����Ϣ���û�


	int  m_lID ;          // ���ض���Ψһֵ   
	char m_szPurpose[32]; // ������;
	char m_szType[32];    // ��������
};

template<class T>
CVBF_MainCtrlImpl<T>::CVBF_MainCtrlImpl(IVBF_MainCtrl* pIParent)
{
	m_pIParent	= pIParent;

	// ��������Ƿ����ͷ� (���������ͷŵ����������Ϣ)
	m_bComponentReleased = false;

	// ��������Ƿ񼤻�
	m_bActive			= true;

	// �������л�ȡ��ǰѡ�е�Tool
	m_szSelectedToolID[0] = '\0';	

	// cfg�����ļ����ļ���������·����.cfg��׺����"RegisterComponents"
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

    // �ͷŶ�����Message�б�
    for(CMessageMapIter iterMsg=m_mapSubscribedMessageIPtr.begin(); iterMsg!=m_mapSubscribedMessageIPtr.end(); iterMsg++)
    {
        vector<IVBF_Message*>* pvMessageIPtr = iterMsg->second;
        SAFE_DELETE(pvMessageIPtr);
    }
    m_mapSubscribedMessageIPtr.clear();

    // �����ע��������ͷ� (��Ө�޸ģ�2009-4-10)

    // �ͷ�ָ���ͬʱ����vector���������������������г�ΪҰָ�� (��Ө�޸ģ�2010-02-05)
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

    // �ͷŶ�̬��
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
// ������Release()
// �������ͷŽӿڱ���
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::Release()
{
    ReleaseComponent();
	delete this;
}

//-----------------------------------------------------------------------------------
// ������SetAppPath()
// ����������Ӧ�ó����·��
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::SetAppPath(const char* szPath)
{
    VBF_strcpy(m_szAppPath, szPath);

	// ������־�ļ�(�ı���ʽ)���Ա�������������д�������Ϣ (�������Ϣ)
	char szLogPath[MAX_PATH];
    VBF_sprintf(szLogPath, "%s/VBF_3DLog", m_szAppPath);
}

//-----------------------------------------------------------------------------------
// ������OnEvent()
// ��������Ӧ�¼�
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::OnEvent(const char* szMessage, int nValue, void* pValue)
{
}

//-----------------------------------------------------------------------------------
// ������Attach()
// ���������һ���¼��۲���(IVBF_Subject�еĴ��麯��)
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::Attach(IVBF_Observer* pIObserver)
{
	// ��������ӿ�ָ��
    if(NULL==pIObserver) return;

	// �������ظ����
    CObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
    if(pIter==m_ObserverList.end()) m_ObserverList.push_back(pIObserver);
}

//-----------------------------------------------------------------------------------
// ������Detach()
// �������ͷ�һ���¼��۲���(IVBF_Subject�еĴ��麯��)
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::Detach(IVBF_Observer* pIObserver)
{
    // ��������ӿ�ָ��
    if(NULL==pIObserver) return;

    CObserverList::iterator pIter = std::find(m_ObserverList.begin(), m_ObserverList.end(), pIObserver);
	if(pIter!=m_ObserverList.end()) m_ObserverList.erase(pIter);
}

//-----------------------------------------------------------------------------------
// ������DetachAll()
// �������ͷ������¼��۲���(IVBF_Subject�еĴ��麯��)
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::DetachAll()
{
	m_ObserverList.clear();
}

//-----------------------------------------------------------------------------------
// ������Notify()
// �������������¼��۲��߷����¼�
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
// ������RegisterComponentFile()
// ����������ָ���������̬���ļ���ע�����
// ������szComponentFile -- ������ڶ�̬����ļ�·��(����·������·����.dll��׺)
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::RegisterComponentFile(const char* szComponentFile)
{
    map<string, string>::iterator pIter = m_mapComponentDllNames.find(szComponentFile);
    if(pIter!=m_mapComponentDllNames.end())
    {
        OSG_NOTICE<<"�Ѿ�ע���"<< szComponentFile << std::endl;
        return true;
    }

    OSG_NOTICE<<"ע��"<< szComponentFile << std::endl;


    IVBF_Component* pIComponent = RegisterComponentFile_(szComponentFile);
    if(pIComponent==NULL) return false;

    string sComID = pIComponent->GetComponentID();
    m_mapComponentDllNames.insert( map<string, string>::value_type(szComponentFile, sComID) );


    // ��ʼ�������
    if(!pIComponent->Init()) return false;

    // ��¼Command�¼��۲��߽ӿ�
    IVBF_Command* pICommand = (IVBF_Command*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_COMMAND);
    if(pICommand!=NULL) m_vCommandIPtr.push_back(pICommand);

    // ��¼Message�¼��۲��߽ӿ�
    IVBF_Message* pIMessage = (IVBF_Message*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_MESSAGE);
    if(pIMessage!=NULL) m_vMessageIPtr.push_back(pIMessage);

    // ��¼Tool�¼��۲��߽ӿ�
    IVBF_Tool* pITool = (IVBF_Tool*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_TOOL);
    if(pITool!=NULL) m_vToolIPtr.push_back(pITool);

    // ��¼UIProcessor�¼��۲��߽ӿ�
    IVBF_UIProcessor* pIUIProcessor = (IVBF_UIProcessor*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_UIPROCESSOR);
    if(pIUIProcessor!=NULL) m_vUIProcessorIPtr.push_back(pIUIProcessor);

    return true;
}

//-----------------------------------------------------------------------------------
// ������RegisterComponentFile_()
// ����������ָ���������̬���ļ���ע�����
// ������szComponentFile -- ������ڶ�̬����ļ�·��(����·������·����.dll��׺)
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

    // װ�ض�̬��
    VBF_DynamicLibrary* pLib = VBF_DynamicLibrary::loadLibrary(szComponentFile);
    if(NULL==pLib)
    {
        char szErr[256];
        VBF_sprintf(szErr, "%s װ�ز��ɹ�!", szComponentFile);
        //std::cout << szErr << std::endl;
        OSG_NOTICE<< szErr <<std::endl;

        return NULL;
	}
		
	// ��������ӿ�
    VBF_CreateComponentObjectProc CreateComponentObject = (VBF_CreateComponentObjectProc)pLib->getProcAddress("VBF_CreateComponentObject");
	if(NULL==CreateComponentObject)
	{
        delete pLib;  // ע�⣺�����ͷŸö�̬��ľ��

		char szErr[256];
        VBF_sprintf(szErr, "%s û�е���VBF_CreateComponentObject()����!", szComponentFile);

		std::cout << szErr << std::endl;
        return NULL;
	}

	IVBF_Component* pIComponent = CreateComponentObject( (IVBF_MainCtrl*)this );
    if(NULL==pIComponent) return NULL;

	// ��¼�����̬�����ͽӿ�ָ�룬�Ա��ͷ�
    m_vRegComDll.push_back(pLib);
    m_vRegComPtr.push_back(pIComponent);

    return pIComponent;
}

//-----------------------------------------------------------------------------------
// ������RegisterComponentCfgFileDefault()
// ������ע���Ѽ���ϵͳ�е�ȫ�����
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::RegisterComponentCfgFileDefault()
{
	if( strlen(m_szCfgFileName)==0 ) return;

	// �����ظ�ע��ͬһ����̬�� (��Ө��ӣ�2011-03-29)
	m_mapComponentDllNames.clear();

	// ��ע����Ҫ�Զ����صĶ�̬�⣬��Щ��̬���������صĺ������������Ҫͨ��.cfg�����ļ�����
	for(unsigned int i=0; i<m_vAutoLoadDllNames.size(); i++)
	{
		string strDllName = m_vAutoLoadDllNames[i];
		if(strDllName=="") continue;

		char szComponentFile[MAX_PATH];
        VBF_sprintf(szComponentFile, "%s", strDllName.c_str());

        IVBF_Component* pIComponent = RegisterComponentFile_(szComponentFile);
        if(pIComponent==NULL) continue;

        string sComID = pIComponent->GetComponentID();

		// �����ظ�ע��ͬһ����̬��
        m_mapComponentDllNames.insert( map<string, string>::value_type(strDllName, sComID) );
	}

	// ע������صĻ������ 	
	char szComponentConfigFn[MAX_PATH];
#ifdef _DEBUG
    VBF_sprintf(szComponentConfigFn, "%s/3DMap/%sD.cfg", GetSysSetPath(), m_szCfgFileName);
#else
    VBF_sprintf(szComponentConfigFn, "%s/3DMap/%s.cfg", GetSysSetPath(), m_szCfgFileName);
#endif

	RegisterComponentCfgFile(szComponentConfigFn);

	// ��ʼ���������
	InitComponent();
}

//-----------------------------------------------------------------------------------
// ������RegisterComponentCfgFile_Path()
// ����������ָ������������ļ���ע�����
//       ��������ļ��а���Ҫע���һ�������̬������
// ������szDllPath          -- ��̬���ļ����ڵ�·��
//       szComponentCfgFile -- ������������ļ���ȫ·���� (��Ө�޸ģ�2011-03-28)
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::RegisterComponentCfgFile_Path(const char* szComponentCfgFile, const char* szDllPath)
{
	//�������ļ��л�ȡ��Ҫע��Ķ�̬����	
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
		//HG �޸�
#ifdef _DEBUG
		::VBF_sprintf(szComFileName, "%sd.dll",szTemp);
#else
		::VBF_sprintf(szComFileName, "%s.dll",szTemp);
#endif
#else
        char szComFileName[MAX_PATH] = {0};
        ::VBF_sprintf(szComFileName, "lib%s.so",szTemp);
#endif
		// �����ظ�ע��ͬһ����̬�� (��Ө��ӣ�2011-03-29)
        map<string, string>::iterator pIter = m_mapComponentDllNames.find(szComFileName);
        if(pIter!=m_mapComponentDllNames.end() || strlen(szComFileName)==0) continue;

        m_mapComponentDllNames.insert( map<string, string>::value_type(szComFileName, szComFileName) );
        asComponentDllNames.push_back(string(szComFileName));
	}
	fclose(fp);

	// ע���������	
    int numComponents = asComponentDllNames.size();
    for(int i=0; i<numComponents; i++)
	{
		char sComponentDllName[MAX_PATH];
		VBF_sprintf(sComponentDllName, "%s/%s", szDllPath, asComponentDllNames[i].c_str());
		if(strlen(sComponentDllName)==0) continue;		

		// ע�ᵥ�����
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
// ������RegisterComponentCfgFile()
// ����������ָ������������ļ���ע�����
//       ��������ļ��а���Ҫע���һ�������̬������
// ������szComponentCfgFile -- ������������ļ���ȫ·���� (��Ө�޸ģ�2011-03-28)
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::RegisterComponentCfgFile(const char* szComponentCfgFile)
{
	return RegisterComponentCfgFile_Path(szComponentCfgFile, GetAppPath());
}

//-----------------------------------------------------------------------------------
// ������InitComponent()
// ��������ʼ���������
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::InitComponent()
{
	vector<IVBF_Component*>::iterator pIter;
	for(pIter=m_vRegComPtr.begin(); pIter!=m_vRegComPtr.end(); pIter++)
	{
		IVBF_Component* pIComponent = *pIter;
		if(NULL==pIComponent) continue;

		// ��ʼ�������
		if(!pIComponent->Init()) continue;
	
		// ��¼Command�¼��۲��߽ӿ�
		IVBF_Command* pICommand = (IVBF_Command*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_COMMAND);
		if(pICommand!=NULL) m_vCommandIPtr.push_back(pICommand);

		// ��¼Message�¼��۲��߽ӿ�
		IVBF_Message* pIMessage = (IVBF_Message*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_MESSAGE);
		if(pIMessage!=NULL) m_vMessageIPtr.push_back(pIMessage);

		// ��¼Tool�¼��۲��߽ӿ�
		IVBF_Tool* pITool = (IVBF_Tool*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_TOOL);
		if(pITool!=NULL) m_vToolIPtr.push_back(pITool);

		// ��¼UIProcessor�¼��۲��߽ӿ�
		IVBF_UIProcessor* pIUIProcessor = (IVBF_UIProcessor*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_UIPROCESSOR);
		if(pIUIProcessor!=NULL) m_vUIProcessorIPtr.push_back(pIUIProcessor);
	}	

	return true;
}

//-----------------------------------------------------------------------------------
// ������RemoveComponent()
// ������ɾ��ָ�����
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
    // ��֪ͨж���������Ϣ
    SendMessage(this,VBF_MESSAGE_UNREGIST_COM,0,&sComponentID);

    SAFE_RELEASE(pIComponent);

    VBF_DynamicLibrary* pLib = m_vRegComDll[idx];
    m_vRegComDll.erase(m_vRegComDll.begin() + idx);
    SAFE_DELETE(pLib);


    vector<IVBF_Component*>::iterator iterIComponentPtr;
    for(iterIComponentPtr=m_vRegComPtr.begin(); iterIComponentPtr!=m_vRegComPtr.end(); iterIComponentPtr++)

    m_mapComponentDllNames.erase(szComponentFile);

    OSG_NOTICE<<"ж��"<< szComponentFile << std::endl;



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
    // ��֪ͨж���������Ϣ
    SendMessage(this,VBF_MESSAGE_UNREGIST_COM,0,&sComponentID);

    SAFE_RELEASE(pIComponent);

    VBF_DynamicLibrary* pLib = m_vRegComDll[idx];
    m_vRegComDll.erase(m_vRegComDll.begin() + idx);

    vector<IVBF_Component*>::iterator iterIComponentPtr;
    for(iterIComponentPtr=m_vRegComPtr.begin(); iterIComponentPtr!=m_vRegComPtr.end(); iterIComponentPtr++)

    m_mapComponentDllNames.erase(szComponentFile);

    OSG_NOTICE<<"ж��"<< szComponentFile << std::endl;

    return pLib;
}
//-----------------------------------------------------------------------------------
// ������GetComponentPtr()
// ���������������ID����ȡ����Ľӿ�ָ��
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
// ������QueryInterface()
// ��������ȡĳ���ӿڵ�ָ��
//-----------------------------------------------------------------------------------
template<class T>
void* CVBF_MainCtrlImpl<T>::QueryInterface(const char* szInterfaceID, const char* szComponentID)
{
	if(NULL==szInterfaceID || strlen(szInterfaceID)==0) return NULL;	

	// �������
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
// ������ExecuteCommand()
// ������ִ������
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
// ������SelectTool()
// ���������õ�ǰʹ�õĹ���
//-----------------------------------------------------------------------------------
template<class T>
bool CVBF_MainCtrlImpl<T>::SelectTool(const char* szToolID)
{
	// �����ǰ���߷����ı䣬��֪ͨ�������ȡ���ϴεĹ��� (��Ө��ӣ�2006-5-21)
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
// ������GetCurrentTool()
// ��������ȡ��ǰʹ�õĹ���
//-----------------------------------------------------------------------------------
template<class T>
const char* CVBF_MainCtrlImpl<T>::GetCurrentTool()
{
	return m_szSelectedToolID;
}

//-----------------------------------------------------------------------------------
// ������UpdateUI()
// ����������UI
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
// ������SubscribeMessage()
// ������������Ϣ
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::SubscribeMessage(const char* szMessage, IVBF_Component* pIComponent)
{
	vector<IVBF_Message*>* pvMessageIPtr = NULL;

	CMessageMapIter pIterator = m_mapSubscribedMessageIPtr.find(szMessage);
	if( pIterator!=m_mapSubscribedMessageIPtr.end() )  // �ҵ�
	{
		pvMessageIPtr = pIterator->second;
	}
	else                                     // û�ҵ�
	{
		pvMessageIPtr = new vector<IVBF_Message*>;
		m_mapSubscribedMessageIPtr.insert( CMessageMap::value_type(szMessage, pvMessageIPtr) );
	}

	IVBF_Message* pIMessage = (IVBF_Message*)pIComponent->QueryInterface(VBF_INTERFACE_MAIN_MESSAGE);
	if(pIMessage!=NULL) pvMessageIPtr->push_back( pIMessage );
}

//-----------------------------------------------------------------------------------
// ������UnSubscribeMessage()
// ������ȡ����������Ϣ
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
// ������SendMessage()
// ��������ÿһ��ע���Component������Ϣ
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::SendMessage(void* pSender,const char* szMessage, int nValue, void* pValue)
{
	// ���������ͷŵ����������Ϣ
	if(m_bComponentReleased) return;

	Notify(szMessage,nValue,pValue);	
	
	// ��ÿ�������˸���Ϣ��Component������Ϣ
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
// ������SetActive()
// ���������������
//-----------------------------------------------------------------------------------
template<class T>
void CVBF_MainCtrlImpl<T>::SetActive(bool bActive)
{
	m_bActive = bActive;
}


#endif 
