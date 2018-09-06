#ifndef __VBF_FUNCTION_REGISTER_H__
#define __VBF_FUNCTION_REGISTER_H__


#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>


// 注册函数名与函数指针的对应表，并根据菜单命令执行相应的函数指针

typedef void (*Function)( IVBF_MainCtrl* pIMainCtrl );// 函数指针，用于响应菜单命令

class CVBF_RegistryFunction
{
public:
	CVBF_RegistryFunction(const std::string& sFunName,Function fun);
};

#ifdef VBF_QT
#define VBF_REGISTER_FUNCTION(name) \
    void name(IVBF_MainCtrl* pIMainCtrl); \
    static CVBF_RegistryFunction g_RegistryFunction_##name(#name,&name);
#else
#define VBF_REGISTER_FUNCTION(name) \
    void name(IVBF_MainCtrl* pIMainCtrl); \
    static CVBF_RegistryFunction g_RegistryFunction_##name(#name,&##name);
#endif


bool ExecuteFunction(const std::string& sFunctionName,IVBF_MainCtrl* pIMainCtrl);





#endif
