//***************************************************************************************
// FileName��IVBF_SimulationTimer.h
// Function������ʱ�ӵĽӿ���
// Author:
// Date:
//***************************************************************************************

#ifndef __IVBF_SIMULATIONT_IMER_H__
#define __IVBF_SIMULATIONT_IMER_H__

#include <VBF_Base/VBF_Referenced.h>
// ��Ȼʱ�䣺RealTime�����ɼ����ϵͳʱ���ȡ�ģ�����ϵͳ֡�ٲ��ȶ�����ʱ�������ȳ�
// �߼�ʱ�䣺LogicTime�����Ƶ���Ȼʱ�䣬��֡����أ�ÿ֡����
// ����ʱ�䣺SimulationTime������ִ�е�ʱ�䣬�Ǹ�ʱ�䳤�ȵĸ���
// D��ʱ�䣺Ϊ��ϰ/��սʱ�䣬�Ǽ���ģ���ʼʱ�����ⲿ�趨



// �磺2009��7��3��10ʱ00��00���𣬷���2009��10��1��8ʱ00��00����ı����̣�����ʱ���Ϊ60:1
//     ��D �յ���ʼʱ�䣨m_dDDayTimeBegin�� Ϊ2009��10��1��8ʱ00��00�루ת��Ϊ�룩
//     �߼�ʱ����ʼʱ�䣨m_dLogicTimeBegin��Ϊ2009��7��3��10ʱ00��00�루ת��Ϊ�룩
//     ����10��֮��
//     ��ǰ��D��ʱ��Ϊ ��m_dDDayTimeCurrent��Ϊ2009��10��1��8ʱ10��00��
//     ��ǰ���߼�ʱ��Ϊ��m_dDDayTimeCurrent��Ϊ2009��7��3��10ʱ00��10��
//     ��ǰ�ķ���ʱ��Ϊ600��


class IVBF_SimulationTimer:public CVBF_Referenced
{
public:
    virtual ~IVBF_SimulationTimer() {}

public:
    virtual void   SetLogicTimeBegin(double dTime)=0;
    virtual double GetLogicTimeCurrent()=0;             // ����ʱ�䣬������ʱ���

    virtual double GetDDayTimeCurrent()=0;
    virtual double GetDDayTimeBegin()=0;
    virtual void   SetDDayTimeBegin(double dTime)=0; // ��λ��

    virtual double GetSimulateTimeCurrent()=0; // ���澭����ʱ�䣬����ʱ���
	virtual void SetSimulateTimeCurrent(double dTime)=0;  //���÷���ʱ��ľ���ʱ�䣬����ʱ��ȣ��������

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
