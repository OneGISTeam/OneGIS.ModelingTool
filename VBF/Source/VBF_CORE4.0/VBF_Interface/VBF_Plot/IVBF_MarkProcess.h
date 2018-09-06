//*******************************************************************
// FileName：IVBF_MarkProcess.h
// Function：标图实体模型的过程接口
// Author:
// Date:     2010-9-19
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_H__
#define __IVBF_MARK_PROCESS_H__

#include <VBF_Base/IVBF_SimulationTimer.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>

class IVBF_MarkModel;
class TiXmlElement;
class CVBF_Config;


class IVBF_MarkProcess : public osg::CVBF_Object
{
public:
	virtual ~IVBF_MarkProcess() {}

public:

    virtual void ReSet()=0;

    // 获取过程类型
    virtual const std::string& GetType()=0;

    // 获取过程的类型描述
    virtual const std::string& GetTypeDesc()=0;

    // 设置过程所绑定的实体模型
    virtual void SetMarkModel(IVBF_MarkModel* pIMarkModel)=0;

    virtual void ProcessSimulate(IVBF_SimulationTimer* pSimulationTimer)=0; // 过程模拟

	//统计起始时间,为了统计最早的过程的时间，仅统计绝对时间而且仅统计时间区段，相对时间时返回0
	virtual void StatStartTime(double& dStartTime)=0;

    // 串行化
    virtual bool WriteToXML(TiXmlElement* pElemProc)=0;    // 写入：将模型过程信息写入指定的xml节点
    virtual bool ReadFromXML(TiXmlElement* pElemProc)=0;   // 读取：从指定的xml节点读取模型过程信息

	// 执行json脚本
    virtual void ExecuteScript(const CVBF_Config& conf)=0;
};


#endif 
