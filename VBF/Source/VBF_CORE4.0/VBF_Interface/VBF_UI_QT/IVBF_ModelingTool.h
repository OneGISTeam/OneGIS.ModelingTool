//***************************************************************************************
// FileName��IVBF_XXX.h
// Function��
// Author:
// Date:
//***************************************************************************************

#ifndef __IVBF_MODELINGTOOL_H__
#define __IVBF_MODELINGTOOL_H__


// ����������ID��
const char VBF_COMPONENT_MODELINGTOOL[]          = "Component: ModelingTool";

// ����ר�нӿڵ�ID��
const char VBF_INTERFACE_MODELINGTOOL[]          = "ModelingTool�ӿ�";

// ��������ID��
const char VBF_COMMAND_MODELINGTOOL_SHOWOBJECTMANAGERWND[]       = "Command: ModelingTool Show ObjectManagerWnd";     // ��ʾ�������Ի���



class IVBF_ModelingTool
{
public:
    virtual ~IVBF_ModelingTool() {}

public:	
    virtual void LoadSTObjectDoc(const std::string& sFn)=0;
    virtual void SaveSTObjectDoc(const std::string& sFn)=0;
    virtual void Clear()=0;
};


#endif
