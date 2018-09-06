//***************************************************************************************
// FileName：IVBF_3DNet.h
// Function：三维显示控制接口，主要用于获取和显示参数有关的信息和对场景进行控制
// Author: 
// Date:     2006-4-22
//***************************************************************************************

#ifndef __IVBF_3DNET_H__
#define __IVBF_3DNET_H__


// 定义该组件的ID号
const char VBF_COMPONENT_3DNET[]			= "Component: 3DNet";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DNET[]			= "三维网络接口";

// 定义消息ID号

// 定义命令ID号
const char VBF_COMMAND_3DNET_CLIENTINFO[]	= "客户机信息";

class IVBF_3DNet
{
public: 	
	virtual ~IVBF_3DNet() {}

public:

	// 传递配置信息
	virtual void   SetNumClientRows(int nRows)=0;
	virtual void   SetNumClientCols(int nCols)=0;	
	virtual void   SetClientResH(int nResH)=0;
	virtual void   SetClientResV(int nResV)=0;

	// 获取配置信息
	virtual int   GetNumClientRows()=0;
	virtual int   GetNumClientCols()=0;
	virtual int   GetClientResH()=0;
	virtual int	  GetClientResV()=0;
	virtual int   GetClientRowNo()=0;
	virtual int   GetClientColNo()=0;

	// 是否在等待客户端结束渲染
	virtual bool  IsWaitingForClient()=0;
};

#endif





















