//*******************************************************************
// FileName：IVBF_MarkProTimerTrigger.h
// Function：由时间触发的过程
// Author:   武玉国
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_TIMER_TRIGGER_H__
#define __IVBF_MARK_PROCESS_TIMER_TRIGGER_H__


#include <VBF_Plot/IVBF_MarkProcess.h>


//-------------------------------------------------------------------------------
// 定义枚举：EVBF_TimeType
// 枚举描述：时间类型：仿真时间、D日绝对时间、D日相对时间
//          仿真时间也称模拟时间，是从仿真开始（0）起算，以秒为单位，按有效时间推移（tick点）
//          D日时间为演习/作战时间，是假想的，起始时间由外部设定
//          D日绝对时间从1889年起算，D日相对时间从D日起算
//-------------------------------------------------------------------------------
enum EVBF_TimeType
{
	EVBF_TIME_TYPE_RELATIVE = 0,
	EVBF_TIME_TYPE_ABSOLUTE = 1
};


//-------------------------------------------------------------------------------
// 定义接口：IVBF_MarkProTimerTrigger
// 接口描述：在某个时间段内发生的过程
//-------------------------------------------------------------------------------
class IVBF_MarkProTimerTrigger : public IVBF_MarkProcess
{
public:
	virtual ~IVBF_MarkProTimerTrigger() {}

	// 设置/获取仿真时间类型
	virtual void          SetTimeType(EVBF_TimeType TimeType)=0;
	virtual EVBF_TimeType GetTimeType()=0;

	// 设置/获取过程执行的起止时间，对于在某个时刻发生的简短过程，仅使用BeginTime
	virtual void   SetBeginTime(double dTime)=0;
	virtual double GetBeginTime()=0;

	virtual void   SetEndTime(double dTime)=0;
	virtual double GetEndTime()=0;
};

#endif 
