//*******************************************************************
// FileName：IVBF_MarkAttrCreator.h
// Function：标图实体模型属性创建接口
// Author:   
// Date:     
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_CREATOR_H__
#define __IVBF_MARK_ATTR_CREATOR_H__


// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DPLOT_ATTR_CREATOR[]	= "三维标图模型属性创建接口";	

#include "IVBF_MarkAttr.h"

//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrCreator
// 接口描述：实体模型属性创建接口
//--------------------------------------------------------------------
class IVBF_MarkAttrCreator 
{
public:
	virtual ~IVBF_MarkAttrCreator() {}

public:
	virtual IVBF_MarkAttr* CreateMarkAttr(unsigned int nAttrType)=0;
};


#endif 
