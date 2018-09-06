//*******************************************************************
// FileName：IVBF_MarkProcessCreator.h
// Function：标图实体模型属性创建接口
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_ENTITY_MODEL_PROCESS_CREATOR_H__
#define __IVBF_MARK_ENTITY_MODEL_PROCESS_CREATOR_H__


// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DPLOT_PROCESS_CREATOR[]				= "三维标图模型过程创建接口";	

#include <VBF_Plot/IVBF_MarkProcess.h>

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkEntityModelProcessCreator
// 接口描述：实体模型属性
//--------------------------------------------------------------------
class IVBF_MarkProcessCreator 
{
public:
	virtual ~IVBF_MarkProcessCreator() {}

public:
    virtual IVBF_MarkProcess* CreateMarkProcess(const std::string& strProcessType)=0;
};


#endif 
