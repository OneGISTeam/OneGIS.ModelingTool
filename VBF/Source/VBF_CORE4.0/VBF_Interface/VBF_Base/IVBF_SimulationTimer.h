//***************************************************************************************
// FileName：IVBF_SimulationTimer.h
// Function：仿真时钟的接口类
// Author:
// Date:
//***************************************************************************************

#ifndef __IVBF_SIMULATIONT_IMER_H__
#define __IVBF_SIMULATIONT_IMER_H__

#include <VBF_Base/VBF_Referenced.h>
// 自然时间：RealTime，是由计算机系统时间获取的，由于系统帧速不稳定，改时间间隔不等长
// 逻辑时间：LogicTime，近似的自然时间，与帧数相关，每帧定长
// 仿真时间：SimulationTime，仿真执行的时间，是个时间长度的概念
// D日时间：为演习/作战时间，是假想的，起始时间由外部设定



// 如：2009年7月3日10时00分00秒起，仿真2009年10月1日8时00分00秒的阅兵过程，仿真时间比为60:1
//     则D 日的起始时间（m_dDDayTimeBegin） 为2009年10月1日8时00分00秒（转换为秒）
//     逻辑时的起始时间（m_dLogicTimeBegin）为2009年7月3日10时00分00秒（转换为秒）
//     经过10秒之后
//     当前的D日时间为 （m_dDDayTimeCurrent）为2009年10月1日8时10分00秒
//     当前的逻辑时间为（m_dDDayTimeCurrent）为2009年7月3日10时00分10秒
//     当前的仿真时间为600秒


class IVBF_SimulationTimer:public CVBF_Referenced
{
public:
    virtual ~IVBF_SimulationTimer() {}

public:
    virtual void   SetLogicTimeBegin(double dTime)=0;
    virtual double GetLogicTimeCurrent()=0;             // 仿真时间，不考虑时间比

    virtual double GetDDayTimeCurrent()=0;
    virtual double GetDDayTimeBegin()=0;
    virtual void   SetDDayTimeBegin(double dTime)=0; // 单位天

    virtual double GetSimulateTimeCurrent()=0; // 仿真经过的时间，考虑时间比
	virtual void SetSimulateTimeCurrent(double dTime)=0;  //设置仿真时间的经过时间，考虑时间比，张政添加

    virtual double GetSimulateTimeRatio()=0;
    virtual void   SetSimulateTimeRatio(double dRatio )=0;


    virtual void Start()=0;
    virtual void Stop()=0;
    virtual void Pause()=0;
    virtual void Continue()=0;
    virtual bool IsPause()=0;

    virtual void Tick()=0;
    virtual void Reverse()=0;
};

VBF_BASE_EXPORT IVBF_SimulationTimer* VBF_GetSimulationTimer();

#endif
