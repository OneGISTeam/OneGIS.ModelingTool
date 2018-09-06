//***************************************************************************************
// FileName：IVBF_XXX.h
// Function：
// Author:
// Date:
//***************************************************************************************

#ifndef __IVBF_MODELINGTOOL_H__
#define __IVBF_MODELINGTOOL_H__


// 定义该组件的ID号
const char VBF_COMPONENT_MODELINGTOOL[]          = "Component: ModelingTool";

// 定义专有接口的ID号
const char VBF_INTERFACE_MODELINGTOOL[]          = "ModelingTool接口";

// 定义命令ID号
const char VBF_COMMAND_MODELINGTOOL_SHOWOBJECTMANAGERWND[]       = "Command: ModelingTool Show ObjectManagerWnd";     // 显示对象管理对话框



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
