//*******************************************************************
// FileName��CVBF_MarkProTimerTriggerImpl.h
// Function  ʱ�䴥�����͵Ĺ��̵�ʵ��
// Author:   �����
// Date:     
//*******************************************************************

#ifndef __VBF_MARK_PROCESS_TIMER_TRIGGER_IMPL_H__
#define __VBF_MARK_PROCESS_TIMER_TRIGGER_IMPL_H__

#include "VBF_Plot/VBF_MarkProcessImpl.h"
#include "VBF_Plot/IVBF_MarkProTimerTrigger.h"
#include <VBF_Aux/VBF_GLAux/VBF_ReadWriteUtils.h>


//--------------------------------------------------------------------
// ����ģ���ࣺCVBF_MarkProTimerTriggerImpl
// ģ������������ĳ��ʱ����ڷ����Ĺ���
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

    // ���л�
    virtual bool WriteToXML(TiXmlElement* pElemProc);
    virtual bool ReadFromXML(TiXmlElement* pElemProc);

	// ִ��json�ű�
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
// ������StatStartTime()
// ���������㿪ʼʱ��
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
// ������WriteToXML()
// ���������л�����������Ϣд��ָ����xml�ڵ�
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
// ������ReadFromXML()
// ���������л�����ָ����xml�ڵ��ȡ������Ϣ
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

    // ������ز���
    SetTimeType(nTimeType);
    SetBeginTime(dBeginTime);
    SetEndTime(dEndTime);

    return true;
}
 
//----------------------------------------------------------------------------
// ������ExecuteScript()
// ������ִ��json�ű�
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
