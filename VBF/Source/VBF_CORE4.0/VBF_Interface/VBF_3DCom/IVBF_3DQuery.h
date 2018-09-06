//***************************************************************************************
// FileName：IVBF_3DQuery.h
// Function：3D查询接口
// Author:
// Date:
//***************************************************************************************

#ifndef __IVBF_3DQUERY_H__
#define __IVBF_3DQUERY_H__


// 定义该组件的ID号
const char VBF_COMPONENT_3DQUERY[]          = "Component: 3DQuery";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DQUERY[]          = "三维查询接口";

// 定义工具ID号
const char VBF_TOOL_3DQUERY_POINT[]			= "Tool: 3DQuery Point";    // 点选查询
const char VBF_TOOL_3DQUERY_RECT[]			= "Tool: 3DQuery Rect";     // 矩形查询



class IVBF_3DQuery
{
public:
    virtual ~IVBF_3DQuery() {}

public:	

};


#endif
