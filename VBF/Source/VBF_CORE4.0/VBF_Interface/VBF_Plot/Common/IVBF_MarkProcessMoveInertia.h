//*******************************************************************
// FileName：IVBF_MarkProcessInertiaMove.h
// Function：惯性运动
// Author:   武玉国
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_INERTIAMOVE_H__
#define __IVBF_MARK_PROCESS_INERTIAMOVE_H__

#include <VBF_Plot/IVBF_MarkProTimerTrigger.h>

#define VBF_MARK_PROCESS_MOVEINERTIA "InertiaMove"	// 惯性运动

class IVBF_MarkProcessMoveInertia : public IVBF_MarkProTimerTrigger
{
protected:
    virtual ~IVBF_MarkProcessMoveInertia() {}

public:
    /*
    virtual void SetVelocity()=0;       // 设置速度，包括方向和速度值
    virtual void SetAcceleration()=0;   // 设置速度方向加速度（阻力），默认为0
    virtual void SetGravity()=0;        // 设置重力加速度，默认为9.8
    */
	
};


#endif 
