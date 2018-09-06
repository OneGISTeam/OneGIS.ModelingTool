//***************************************************************************************
// FileName：VBF_CommandImpl.h
// Function：命令接口的模板实现类
// Author:   杜莹
// Date:     2012-10-31
//***************************************************************************************

#ifndef __VBF_COMMAND_IMPL_H__
#define __VBF_COMMAND_IMPL_H__


#include <VBF_MainCtrl/IVBF_Command.h>
#include <vector>


class CVBF_CommandImpl : public IVBF_Command
{
public:
	CVBF_CommandImpl() {}
	virtual ~CVBF_CommandImpl() {}

public:	
	virtual int          GetCommandCount()			{ return m_vPubCommandsID.size(); }
	virtual const char*  GetCommandID(int nIndex)	{ return ( nIndex>=0 && nIndex<(int)m_vPubCommandsID.size() )? m_vPubCommandsID[nIndex] : NULL; }
	virtual bool         ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam) { return false; }

public:
	virtual void Release()	{ delete this; }

protected:	
	std::vector<const char*>	m_vPubCommandsID;	// 该组件公布的命令
};


#endif 