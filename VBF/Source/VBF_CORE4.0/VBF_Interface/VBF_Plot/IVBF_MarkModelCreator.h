//*******************************************************************
// FileName：IVBF_MarkModelCreator.h
// Function：标图实体模型创建接口
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_CREATOR_H__
#define __IVBF_MARK_MODEL_CREATOR_H__

#include <VBF_Plot/IVBF_MarkModel.h>
#include <string>


// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DPLOT_MODEL_CREATOR[]	 = "三维标图模型创建接口";


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelCreator
// 接口描述：实体模型创建器
//--------------------------------------------------------------------
class IVBF_MarkModelCreator
{
public:
	virtual ~IVBF_MarkModelCreator() {}

public:
	virtual IVBF_MarkModel* CreateMarkModel(unsigned int nMarkType, const std::string& strMarkID)=0;
};


#endif 
