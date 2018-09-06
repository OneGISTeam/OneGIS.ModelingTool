//*******************************************************************
// FileName：VBF_TrailPointInner.h
// Function：模型在运动过程中的轨迹点信息（内部使用，增加了时间信息）
// Author:
// Date:     2009-4-1
//*******************************************************************

#ifndef __VBF_TRAIL_POINT_INNER_H__
#define __VBF_TRAIL_POINT_INNER_H__


#include <VBF_Plot/VBF_3DPlotDataTypes.h>
#include <VBF_Base/VBF_Timer.h>



//--------------------------------------------------------------------------
// 定义结构体：VBF_TRAILPOINTINNER
// 结构体描述：模型在运动过程中的轨迹点信息（内部使用，增加了时间信息）
//--------------------------------------------------------------------------
typedef struct _tagVBFTrailPointInner : public VBF_TRAILPOINT
{
    CVBF_Timer      timer;

    // 构造函数
    _tagVBFTrailPointInner()
    {
        timer.setStartTick();
    }

    // 构造函数
    _tagVBFTrailPointInner(bool bKey, const osg::Vec3d& vGeo, float fRotateX0, float fRotateY0, float fRotateZ0, const std::string& strInfo0="")
        : VBF_TRAILPOINT(bKey, vGeo, fRotateX0, fRotateY0, fRotateZ0, strInfo0)
    {
        timer.setStartTick();
    }

    // 拷贝构造函数
    _tagVBFTrailPointInner(const _tagVBFTrailPoint& src)
    {
        *((VBF_TRAILPOINT*)this) = src;
    }

    // 赋值运算符
    _tagVBFTrailPointInner& operator=(const VBF_TRAILPOINT& src)
    {
        // 防止src=src这样的操作
        if( this==&src )  return *this;

        *((VBF_TRAILPOINT*)this) = src;
        return *this;
    }

    // 赋值运算符
    _tagVBFTrailPointInner& operator=(const _tagVBFTrailPointInner& src)
    {
        // 防止src=src这样的操作
        if( this==&src )  return *this;

        *((VBF_TRAILPOINT*)this) = src;
        this->timer.setStartTick( src.timer.getStartTick() );

        return *this;
    }

} VBF_TRAILPOINTINNER;


#endif 
