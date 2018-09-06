//***************************************************************************************
// FileName：VBF_Tool.h
// Function：工具响应接口的模板实现类
// Author:   杜莹
// Date:     2012-10-31
//***************************************************************************************

#ifndef __VBF_TOOL_IMPL_H__
#define __VBF_TOOL_IMPL_H__


#include "VBF_MainCtrl/IVBF_Tool.h"
#include <vector>

class CVBF_ToolImpl : public IVBF_Tool
{
public:	
	CVBF_ToolImpl() {}
	virtual ~CVBF_ToolImpl() {}
	
	virtual int			OnToolSelected(const char* szToolID, IVBF_PropertySet* pInParam)	{ return 0; }
	virtual int			OnToolUnSelected(const char* szToolID, IVBF_PropertySet* pOutParam)	{ return 0; }

	virtual int			GetToolCount()			{ return m_vPubToolsID.size(); }
    virtual const char* GetToolID(int nIndex)	{ return ( nIndex>=0 && nIndex<(int)m_vPubToolsID.size() )? m_vPubToolsID[nIndex] : NULL; }
	virtual const char* GetContextMenuName()	{ return ""; }

public:
	virtual void Release() { delete this; }

protected:
	std::vector<const char*>		m_vPubToolsID;			// 该组件公布的工具
};

#endif 
