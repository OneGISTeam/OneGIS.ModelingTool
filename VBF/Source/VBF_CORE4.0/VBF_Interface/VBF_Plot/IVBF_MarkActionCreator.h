//*******************************************************************
// FileName：IVBF_MarkActionCreator.h
// Function：标图实体模型行为创建接口
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_ACTION_CREATOR_H__
#define __IVBF_MARK_ACTION_CREATOR_H__


// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DPLOT_ACTION_CREATOR[]	= "三维标图模型行为创建接口";

#include "IVBF_MarkAction.h"
#include <string>
//--------------------------------------------------------------------
// 定义接口：IVBF_MarkActionCreator
// 接口描述：实体模型行为创建接口
//--------------------------------------------------------------------
class IVBF_MarkActionCreator
{
public:
    virtual ~IVBF_MarkActionCreator() {}

public:
    virtual IVBF_MarkAction* CreateMarkAction(const std::string& strActionType)=0;
};


#endif 
