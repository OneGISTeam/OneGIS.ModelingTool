//*******************************************************************
// FileName：CVBF_MarkProcessImpl.h
// Function：标图实体模型过程接口实现
// Author:
// Date:     
//*******************************************************************

#ifndef __VBF_MARK_PROCESS_IMPL_H__
#define __VBF_MARK_PROCESS_IMPL_H__

#include <VBF_Base/observer_ptr>
#include "VBF_Plot/IVBF_MarkModel.h"
#include <VBF_Plot/IVBF_MarkProcess.h>
#include <VBF_Aux/VBF_GLAux/VBF_ReadWriteUtils.h>
#include <VBF_Aux/VBF_GLAux/VBF_JsonReader.h>


//--------------------------------------------------------------------
// 定义接口：CVBF_MarkProcessImpl
// 接口描述：标图过程的实现
//--------------------------------------------------------------------
template<class T>
class CVBF_MarkProcessImpl : public T
{
public:
    CVBF_MarkProcessImpl(const std::string& strType);
    CVBF_MarkProcessImpl(const CVBF_MarkProcessImpl& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}

    virtual ~CVBF_MarkProcessImpl();

public:
    virtual void ReSet() { m_bExecuted = false; }

    // 复制
    virtual IVBF_MarkProcess* Clone() { return NULL; }

    // 获取过程的类型
    virtual const std::string& GetType()	{ return m_strType; }

    // 获取过程的类型描述
    virtual const std::string& GetTypeDesc()	{ return m_strTypeDesc; }

    // 设置过程所绑定的实体模型
    virtual void SetMarkModel(IVBF_MarkModel* pIMarkModel) { m_opIMarkModel = pIMarkModel; }

    // 过程数据的保存与读取 (二进制格式)，以便实现场景的记录与播放
    virtual void ProcessSimulate(IVBF_SimulationTimer* pSimulationTimer)=0; // 过程模拟
    virtual void StatStartTime(double& dStartTime) { }

    // 串行化
    virtual bool WriteToXML(TiXmlElement* pElemProc);
    virtual bool ReadFromXML(TiXmlElement* pElemProc);

	// 执行json脚本
    virtual void ExecuteScript(const CVBF_Config& conf);

protected:
    std::string  	m_strType;            // 该过程的类型
    std::string     m_strTypeDesc;      // 该过程的类型描述
    bool            m_bExecuted;		// 是否已被执行

    // 该过程对应的军标实体模型
    observer_ptr<IVBF_MarkModel> m_opIMarkModel;
};


//-----------------------------------------------------------------------------
// 函数：CVBF_MarkProcessImpl()
// 描述：构造函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkProcessImpl<T>::CVBF_MarkProcessImpl(const std::string& strType)
{
    m_strType       = strType;
    m_strTypeDesc   = "";
    m_bExecuted     = false;
}


//-----------------------------------------------------------------------------
// 函数：~CVBF_MarkProcessImpl()
// 描述：析构函数
//-----------------------------------------------------------------------------
template<class T>
CVBF_MarkProcessImpl<T>::~CVBF_MarkProcessImpl()
{
}

//-----------------------------------------------------------------------------
// 函数：WriteToXML()
// 描述：串行化，将过程信息写入指定的xml节点
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkProcessImpl<T>::WriteToXML(TiXmlElement* pElemProc)
{
    if(NULL==pElemProc) return false;

    // 写入：类别
    ::VBF_SetAttribute(pElemProc, "Type",     m_strType);
    ::VBF_SetAttribute(pElemProc, "TypeDesc", m_strTypeDesc);

    return true;
}

//----------------------------------------------------------------------------
// 函数：ReadFromXML()
// 描述：串行化，从指定的xml节点读取过程信息
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkProcessImpl<T>::ReadFromXML(TiXmlElement* pElemProc)
{
    if(NULL==pElemProc) return false;

    return true;
}

//----------------------------------------------------------------------------
// 函数：ExecuteScript()
// 描述：执行json脚本
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkProcessImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
}

#endif 
