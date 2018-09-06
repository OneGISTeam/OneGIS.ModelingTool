//*******************************************************************
// FileName��IVBF_MarkProTimerTrigger.h
// Function����ʱ�䴥���Ĺ���
// Author:   �����
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_TIMER_TRIGGER_H__
#define __IVBF_MARK_PROCESS_TIMER_TRIGGER_H__


#include <VBF_Plot/IVBF_MarkProcess.h>


//-------------------------------------------------------------------------------
// ����ö�٣�EVBF_TimeType
// ö��������ʱ�����ͣ�����ʱ�䡢D�վ���ʱ�䡢D�����ʱ��
//          ����ʱ��Ҳ��ģ��ʱ�䣬�Ǵӷ��濪ʼ��0�����㣬����Ϊ��λ������Чʱ�����ƣ�tick�㣩
//          D��ʱ��Ϊ��ϰ/��սʱ�䣬�Ǽ���ģ���ʼʱ�����ⲿ�趨
//          D�վ���ʱ���1889�����㣬D�����ʱ���D������
//-------------------------------------------------------------------------------
enum EVBF_TimeType
{
	EVBF_TIME_TYPE_RELATIVE = 0,
	EVBF_TIME_TYPE_ABSOLUTE = 1
};


//-------------------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkProTimerTrigger
// �ӿ���������ĳ��ʱ����ڷ����Ĺ���
//-------------------------------------------------------------------------------
class IVBF_MarkProTimerTrigger : public IVBF_MarkProcess
{
public:
	virtual ~IVBF_MarkProTimerTrigger() {}

	// ����/��ȡ����ʱ������
	virtual void          SetTimeType(EVBF_TimeType TimeType)=0;
	virtual EVBF_TimeType GetTimeType()=0;

	// ����/��ȡ����ִ�е���ֹʱ�䣬������ĳ��ʱ�̷����ļ�̹��̣���ʹ��BeginTime
	virtual void   SetBeginTime(double dTime)=0;
	virtual double GetBeginTime()=0;

	virtual void   SetEndTime(double dTime)=0;
	virtual double GetEndTime()=0;
};

#endif 
