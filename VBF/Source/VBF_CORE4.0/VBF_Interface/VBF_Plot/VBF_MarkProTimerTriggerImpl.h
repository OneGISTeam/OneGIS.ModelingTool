//*******************************************************************
// FileName：CVBF_MarkProTimerTriggerImpl.h
// Function  时间触发类型的过程的实现
// Author:   武玉国
// Date:     
//*******************************************************************

#ifndef __VBF_MARK_PROCESS_TIMER_TRIGGER_IMPL_H__
#define __VBF_MARK_PROCESS_TIMER_TRIGGER_IMPL_H__

#include "VBF_Plot/VBF_MarkProcessImpl.h"
#include "VBF_Plot/IVBF_MarkProTimerTrigger.h"
#include <VBF_Aux/VBF_GLAux/VBF_ReadWriteUtils.h>


//--------------------------------------------------------------------
// 定义模板类：CVBF_MarkProTimerTriggerImpl
// 模板类描述：在某个时间段内发生的过程
//--------------------------------------------------------------------
template<class T>
class CVBF_MarkProTimerTriggerImpl : public CVBF_MarkProcessImpl<T>
{
private:
    typedef CVBF_MarkProcessImpl<T> BaseClass;

public:
    CVBF_MarkProTimerTriggerImpl(const std::string& strType);
    CVBF_MarkProTimerTriggerImpl(const CVBF_MarkProTimerTriggerImpl<T>& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
    virtual ~CVBF_MarkProTimerTriggerImpl();

	virtual void		  SetTimeType(EVBF_TimeType TimeType)	{ m_nTimeType = TimeType; }
	virtual EVBF_TimeType GetTimeType()							{ return m_nTimeType; }

	virtual void   SetBeginTime(double dTime)	{ m_dBeginTime = dTime; }
	virtual double GetBeginTime()				{ return m_dBeginTime; }

	virtual void   SetEndTime(double dTime)		{ m_dEndTime = dTime; }
	virtual double GetEndTime()					{ return m_dEndTime; }

	virtual double  GetSimulateTimeCurrent(IVBF_SimulationTimer* pSimulationTimer);

	virtual void StatStartTime(double& dStartTime);

    // 串行化
    virtual bool WriteToXML(TiXmlElement* pElemProc);
    virtual bool ReadFromXML(TiXmlElement* pElemProc);

	// 执行json脚本
    virtual void ExecuteScript(const CVBF_Config& conf);

protected:
	EVBF_TimeType	m_nTimeType;
	double			m_dBeginTime;
	double			m_dEndTime;
};

template<class T>
CVBF_MarkProTimerTriggerImpl<T>::CVBF_MarkProTimerTriggerImpl(const std::string& strType)
                                : BaseClass(strType)
{
	m_nTimeType		= EVBF_TIME_TYPE_RELATIVE;
	m_dBeginTime	= 0.0;
	m_dEndTime		= 0.0;
}

template<class T>
CVBF_MarkProTimerTriggerImpl<T>::~CVBF_MarkProTimerTriggerImpl()
{
}

template<class T>
double CVBF_MarkProTimerTriggerImpl<T>::GetSimulateTimeCurrent(IVBF_SimulationTimer* pSimulationTimer)
{
	if(m_nTimeType == EVBF_TIME_TYPE_RELATIVE)
	{
		return  pSimulationTimer->GetSimulateTimeCurrent();
	}
	else if(m_nTimeType == EVBF_TIME_TYPE_ABSOLUTE)
	{
		return  pSimulationTimer->GetDDayTimeCurrent();
	}
	return 0.0;
}

//-----------------------------------------------------------------------------
// 函数：StatStartTime()
// 描述：计算开始时间
//-----------------------------------------------------------------------------
template<class T>
void CVBF_MarkProTimerTriggerImpl<T>::StatStartTime(double& dStartTime)
{
	if(m_nTimeType == EVBF_TIME_TYPE_ABSOLUTE)
	{
		if(m_dBeginTime < dStartTime) dStartTime = m_dBeginTime;
	}
}

//-----------------------------------------------------------------------------
// 函数：WriteToXML()
// 描述：串行化，将过程信息写入指定的xml节点
//-----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkProTimerTriggerImpl<T>::WriteToXML(TiXmlElement* pElemProc)
{
	if( !BaseClass::WriteToXML(pElemProc)) return false;

	::VBF_SetAttribute(pElemProc, "TimeType",	GetTimeType());
	::VBF_SetAttribute(pElemProc, "BeginTime",	GetBeginTime());
	::VBF_SetAttribute(pElemProc, "EndTime",	GetEndTime());
	
    return true;
}

//----------------------------------------------------------------------------
// 函数：ReadFromXML()
// 描述：串行化，从指定的xml节点读取过程信息
//----------------------------------------------------------------------------
template<class T>
bool CVBF_MarkProTimerTriggerImpl<T>::ReadFromXML(TiXmlElement* pElemProc)
{
    if( !BaseClass::ReadFromXML(pElemProc)) return false;

    EVBF_TimeType nTimeType     = GetTimeType();
    double        dBeginTime    = GetBeginTime();
    double        dEndTime      = GetEndTime();

    ::VBF_QueryAttribute(pElemProc, "TimeType",     (int&)nTimeType);
    ::VBF_QueryAttribute(pElemProc, "BeginTime",    dBeginTime);
    ::VBF_QueryAttribute(pElemProc, "EndTime",      dEndTime);

    // 更新相关参数
    SetTimeType(nTimeType);
    SetBeginTime(dBeginTime);
    SetEndTime(dEndTime);

    return true;
}
 
//----------------------------------------------------------------------------
// 函数：ExecuteScript()
// 描述：执行json脚本
//----------------------------------------------------------------------------
template<class T>
void CVBF_MarkProTimerTriggerImpl<T>::ExecuteScript(const CVBF_Config& conf)
{
	BaseClass::ExecuteScript(conf);

	EVBF_TimeType nTimeType	 = GetTimeType();
    double        dBeginTime = GetBeginTime();
    double        dEndTime   = GetEndTime();

    if( conf.getIfSet("TimeType", (int&)nTimeType) )
	{
		SetTimeType(nTimeType);
	}
    if( conf.getIfSet("BeginTime", dBeginTime) )
	{
		SetBeginTime(dBeginTime);
	}
    if( conf.getIfSet("EndTime", dEndTime) )
	{
		SetEndTime(dEndTime);
	}
}

#endif 
