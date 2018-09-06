//*******************************************************************
// FileName：IVBF_MarkAttrPatrol.h
// Function：飞机巡逻
// Author:   武玉国
// Date:     2010-9-20
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_PATROL_H__
#define __IVBF_MARK_ATTR_PATROL_H__


#include "VBF_Plot/IVBF_MarkAttr.h"
#include <vector>
#include <Types/Vec3d>


class IVBF_MarkAttrPatrol : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrPatrol() {}

    // 设置/获取路径坐标串
    virtual void                            SetPath(const std::vector<osg::Vec3d>& vGeo)=0;
    virtual const std::vector<osg::Vec3d>&  GetPath()=0;
};


#endif 
