//***************************************************************************************
// FileName： VBF_3DMotion.h
// Function： 运动模拟中运动物体，运动路线
// Author:    w00024
// Date:      2016-05-28
//***************************************************************************************

#ifndef __IVBF_3DMOTION_H__
#define __IVBF_3DMOTION_H__

#include <VBF_3DCom/VBF_3DMotion/IVBF_3DMotionControl.h>

// 定义该组件的ID号
const char VBF_COMPONENT_3DMOTION[]				= "Component: 3DMotion";

// 定义3D模块中专有接口的ID号
const char VBF_INTERFACE_3DMOTION[]	= "运动模拟";

// 定义消息ID号
const char VBF_MESSAGE_MOTION_PICK_POINT[]	= "Message: Motion PickPoint";			// void* pValue: bool


// HDR灯光效果显示
const char VBF_COMMAND_HDR_LIGHTING[] = "Command: HDR Lighting";

class IVBF_3DMotionCtrlFactory
{
public:
    virtual ~IVBF_3DMotionCtrlFactory() {}

    enum CMotionControlType
    {
        MOTION_FLIGHT, // 代表空中模拟
        MOTION_LAND,   // 代表路面模拟
        MOTION_OCEAN,   // 代表海上模拟
        MOTION_LANDCOLLISION,   // 通视分析用
        MOTION_NULL
    };
public:
    virtual IVBF_3DMotionControl* GetMotionControl(CMotionControlType eType) = 0;
};

#endif
