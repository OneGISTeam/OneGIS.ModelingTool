//*******************************************************************
// FileName：IVBF_MarkAttrTrailSmoke.h
// Function：模型属性接口：模型的运动轨迹（烟雾状，使用粒子系统实现）
// Author:   杜莹
// Date:     2015-11-03
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_TRAIL_SMOKE_H__
#define __IVBF_MARK_ATTR_TRAIL_SMOKE_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <Types/VBF_3DStyles.h>


class IVBF_MarkAttrTrailSmoke : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrTrailSmoke() {}

    // 设置/获取尾烟宽度（默认值为20，单位：米）
    virtual void  SetWidth(float fWidth)=0;
    virtual float GetWidth()=0;
};


#endif 
