//***************************************************************************************
// FileName：IVBF_Command.h
// Function：命令处理接口，系统调用每个组件的该接口来完成命令处理。
//	         一个命令处理不需要鼠标键盘操作，完成一个单独的功能。
// Author:   武玉国
// Date:     2006-4-22
//***************************************************************************************

#ifndef __IVBF_COMMAND_H__
#define __IVBF_COMMAND_H__

class IVBF_PropertySet;


class IVBF_Command
{
public:
	virtual ~IVBF_Command() {}

public:

	//---------------------------------------------------------------
	// ExecuteCommand:执行指定命令。
	// szCommandID:命令ID。
	// pInParam: 输入参数，其含义有命令本身决定。
	// pOutParam:输出参数，其含义有命令本身决定。
	// return 如果执行成功返回true，否则返回false。
	//---------------------------------------------------------------
	virtual bool ExecuteCommand(const char* szCommandID, IVBF_PropertySet* pInParam, IVBF_PropertySet* pOutParam) = 0;

	//---------------------------------------------------------------
	// GetCommandCount:获取组件支持的命令数目。
	// return 组件支持的命令数目。
	//---------------------------------------------------------------
	virtual int GetCommandCount() = 0;

	//---------------------------------------------------------------
	// 获取组件所支持的指定命令ID，返回命令ID，与次序无关。
	// nIndex ：命令ID索引号，用于遍历命令ID。
	// return 命令ID。
	//---------------------------------------------------------------
	virtual const char* GetCommandID(int nIndex) = 0;
};

#endif
