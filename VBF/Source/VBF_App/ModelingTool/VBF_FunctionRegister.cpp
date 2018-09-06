
//#include "stdafx.h"

#include <map>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Display/VBF_Viewer/IVBF_Viewer.h>

#include <VBF_FunctionRegister.h>
// 用于静态构建的对象指针

template<typename T>
struct CVBF_StaticPointer
{
    CVBF_StaticPointer(): _ptr(0) { }
    CVBF_StaticPointer(T* ptr): _ptr(ptr) { }

    ~CVBF_StaticPointer()
    {
        SAFE_DELETE(_ptr);
    }
 
    const T* get() const { return _ptr; }
		  T* get() { return _ptr; }
private:
    T* _ptr;
};

// 函数映射表（函数名与函数指针的映射表）
class CVBF_MapFunctions : public CVBF_Referenced
{
public:
	void Insert(const std::string& sFunName,Function func)
	{
		m_mapFunctions.insert(std::pair<std::string,Function>(sFunName,func));
	}
	Function Find(const std::string& sFunName)
	{
		std::map<std::string,Function>::const_iterator iter = m_mapFunctions.find(sFunName);
		if(iter == m_mapFunctions.end()) return NULL;

		return iter->second;
	}
    std::map<std::string,Function>& GetFunction() { return m_mapFunctions; }
private:
	std::map<std::string,Function> m_mapFunctions;
};

// 全局函数，用于获取函数名与函数指针的映射
CVBF_MapFunctions* g_GetMapFunctions()
{
    static CVBF_StaticPointer<CVBF_MapFunctions> s_rpMapFunctions = new CVBF_MapFunctions();
    return s_rpMapFunctions.get();
}

// 注册函数（函数名与函数指针）
CVBF_RegistryFunction::CVBF_RegistryFunction(const std::string& sFunName,Function fun)
{
	CVBF_MapFunctions* pMapFunction = g_GetMapFunctions();
	pMapFunction->Insert(sFunName,fun);

//	std::cout << "注册：" << sFunName << std::endl;
}
void VBF_ExecuteScriptFile(IVBF_MainCtrl* pIMainCtrl,std::string sFilename);

// 根据函数名执行函数指针
bool ExecuteFunction(const std::string& sFunctionName,IVBF_MainCtrl* pIMainCtrl)
{
	if(sFunctionName.empty()) return false;

	if(sFunctionName=="Quit")
	{
		if(pIMainCtrl==NULL) return false; 
		IVBF_3DMainCtrl* pI3DMainCtrl = (IVBF_3DMainCtrl*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DMAIN);
		if(NULL==pI3DMainCtrl) return false;

        IVBF_Viewer* pViewer = pI3DMainCtrl->GetViewer();
        if(pViewer) pViewer->SetDone(true);

		return true;
	} 

	if (sFunctionName.find("Tool:") != -1)
	{
		pIMainCtrl->SelectTool( sFunctionName.c_str() );
		return true;
	}
	else if (sFunctionName.find("Command:") != -1)
	{
		pIMainCtrl->ExecuteCommand(sFunctionName.c_str(), NULL, NULL);
		return true;
	}
    else if (sFunctionName.find("Script:") != -1)
    {
        VBF_ExecuteScriptFile(pIMainCtrl,sFunctionName.substr(7,sFunctionName.length()-7));
        return true;
    }
	CVBF_MapFunctions* pMapFunction = g_GetMapFunctions();
	Function func = pMapFunction->Find(sFunctionName);
	if(func) func(pIMainCtrl);

	return true;
}


class CVBF_AutoTestOperation : public osg::Operation
{
public:
    CVBF_AutoTestOperation(const std::string& name, IVBF_MainCtrl* pIMainCtrl):
        osg::Operation(name, true)
    {
        m_pIMainCtrl = pIMainCtrl;
        m_pMapFunctions = g_GetMapFunctions();
        m_mapFun = m_pMapFunctions->GetFunction();
        m_pIter = m_mapFun.begin();
        m_nCount = 0;
    }
    virtual ~CVBF_AutoTestOperation(){}

    virtual void operator()(osg::CVBF_Object* pObject)
    {
        m_nCount++;
        if(m_nCount<300) return;
        m_nCount = 0;

        if(m_pMapFunctions)
        {
            if(m_pIter==m_mapFun.end())
            {
                m_pIter = m_mapFun.begin();
            }

            std::string sName =  m_pIter->first;
            if(sName!="TestAllFunction")
            {
                Function func  =  m_pIter->second;
                if(func) func(m_pIMainCtrl);
            }

            m_pIter++;
        }
    }
    IVBF_MainCtrl* m_pIMainCtrl;
    CVBF_MapFunctions* m_pMapFunctions;
    std::map<std::string,Function>::iterator m_pIter;
    std::map<std::string,Function> m_mapFun;
    int m_nCount;

};

ref_ptr<CVBF_AutoTestOperation>   g_ipAutoTestOperation;
void TestAllFunction(IVBF_MainCtrl* pIMainCtrl)
{
    IVBF_3DMainCtrl* pI3DMainCtrl = (IVBF_3DMainCtrl*)pIMainCtrl->QueryInterface(VBF_INTERFACE_3DMAIN);
    if(NULL==pI3DMainCtrl) return;


    // 添加一个更新回调，用于完成模型的添加/删除等操作
    IVBF_Viewer* pViewer = pI3DMainCtrl->GetViewer();
    if(NULL==pViewer) return;

    g_ipAutoTestOperation = new CVBF_AutoTestOperation("AutoTest", pIMainCtrl);
    pViewer->addUpdateOperation(g_ipAutoTestOperation.get());



}
// 注册函数
VBF_REGISTER_FUNCTION(TestAllFunction);
