//*******************************************************************
// FileName��IVBF_MarkProcessInertiaMove.h
// Function�������˶�
// Author:   �����
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_INERTIAMOVE_H__
#define __IVBF_MARK_PROCESS_INERTIAMOVE_H__

#include <VBF_Plot/IVBF_MarkProTimerTrigger.h>

#define VBF_MARK_PROCESS_MOVEINERTIA "InertiaMove"	// �����˶�

class IVBF_MarkProcessMoveInertia : public IVBF_MarkProTimerTrigger
{
protected:
    virtual ~IVBF_MarkProcessMoveInertia() {}

public:
    /*
    virtual void SetVelocity()=0;       // �����ٶȣ�����������ٶ�ֵ
    virtual void SetAcceleration()=0;   // �����ٶȷ�����ٶȣ���������Ĭ��Ϊ0
    virtual void SetGravity()=0;        // �����������ٶȣ�Ĭ��Ϊ9.8
    */
	
};


#endif 
