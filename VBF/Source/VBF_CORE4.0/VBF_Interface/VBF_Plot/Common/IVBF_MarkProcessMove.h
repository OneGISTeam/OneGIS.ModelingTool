//*******************************************************************
// FileName：IVBF_MarkProcessMove.h
// Function：运动过程（如飞行）
// Author:   武玉国
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_PROCESS_MOVE_H__
#define __IVBF_MARK_PROCESS_MOVE_H__


#include "VBF_Plot/IVBF_MarkProTimerTrigger.h"
#include <vector>
#include <Types/Vec3d>

#define VBF_MARK_PROCESS_MOVE        "PathMove"      // 路径运动
#define VBF_MARK_PROCESS_MOVESIX     "PathMoveSix"   // 六自由度路径运动


class IVBF_MarkProcessMove : public IVBF_MarkProTimerTrigger
{
public:
    virtual ~IVBF_MarkProcessMove() {}

    // 设置/获取路径坐标串(注意：需要在AddMarkProcess之后调用，否则无效！)
    virtual void SetPath(const std::vector<osg::Vec3d>& vGeo,bool bNeedSmooth=false,int numInterPoints=0)=0;
    virtual const std::vector<osg::Vec3d>&  GetPath()=0;
};


#endif 
