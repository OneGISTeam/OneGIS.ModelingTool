#ifndef __VBF_FUNCTION_REGISTER_H__
#define __VBF_FUNCTION_REGISTER_H__


#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>


// ע�ắ�����뺯��ָ��Ķ�Ӧ�������ݲ˵�����ִ����Ӧ�ĺ���ָ��

typedef void (*Function)( IVBF_MainCtrl* pIMainCtrl );// ����ָ�룬������Ӧ�˵�����

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
