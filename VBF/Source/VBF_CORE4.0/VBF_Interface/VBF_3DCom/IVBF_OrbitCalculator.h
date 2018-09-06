#ifndef __IVBF_ORBIT_CALCULATOR_H__
#define __IVBF_ORBIT_CALCULATOR_H__

#include "VBF_Base/VBF_Referenced.h"
#include <Types/Vec3d>

// 轨道计算器接口
class IVBF_OrbitCalculator: public CVBF_Referenced
{
public:
    // 计算给定时间的轨道位置和速度，（t为时间）
    virtual int getOrbitPV(double t, osg::Vec3d& pos, osg::Vec3d& vel) = 0;
    virtual double getEpoch() const=0;// 获取纪元（时间），是数据的起始时间
    virtual const char* getSscID() const=0;// 获取卫星的编号
};
#endif 
