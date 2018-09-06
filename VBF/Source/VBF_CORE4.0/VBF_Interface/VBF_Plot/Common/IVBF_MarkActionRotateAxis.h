//*******************************************************************
// FileName：IVBF_MarkActionRotateAxis.h
// Function：模型行为接口，在某个支点处绕轴旋转（如：飞机螺旋桨的转动）
// Author:
// Date:     2017-12-28
//*******************************************************************

#ifndef __IVBF_MARK_ACTION_ROTATEAXIS_H__
#define __IVBF_MARK_ACTION_ROTATEAXIS_H__


#include <VBF_Plot/IVBF_MarkAction.h>
#include <Types/VBF_3DStyles.h>


class IVBF_MarkActionRotateAxis : public IVBF_MarkAction
{
public:
    virtual ~IVBF_MarkActionRotateAxis() {}
    virtual void SetPivot(const osg::Vec3d& vPivot)=0; // 支点
    virtual void SetAxis(const osg::Vec3d& vAxis)=0; // 旋转轴
    virtual void SetSpeed(float fSpeed)=0; // 旋转速度（单位：度/秒）

};


#endif 
