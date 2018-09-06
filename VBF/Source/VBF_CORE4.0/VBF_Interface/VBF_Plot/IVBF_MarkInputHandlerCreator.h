//*******************************************************************
// FileName：IVBF_MarkInputHandlerCreator.h
// Function：标图实体模型输入处理器创建接口
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_INPUTHANDLERCREATOR_H__
#define __IVBF_MARK_INPUTHANDLERCREATOR_H__


// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DPLOT_INPUTHANDLER_CREATOR[]	= "三维标图输入处理器创建接口";

#include "IVBF_MarkInputHandler.h"

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkInputHandlerCreator
// 接口描述：实体模型输入处理器创建接口
//--------------------------------------------------------------------
class IVBF_MarkInputHandlerCreator
{
public:
    virtual ~IVBF_MarkInputHandlerCreator() {}

public:
    virtual IVBF_MarkInputHandler* CreateMarkInputHandler(unsigned int nType,const std::string& strCode)=0;
};


#endif 
