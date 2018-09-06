// 利用GPL星历计算空间实体位置

#ifndef __VBF_DE405_H__
#define __VBF_DE405_H__


#include <VBF_Common/VBF_Math/VBF_Export.h>
#include <Types/VBF_Matrix.h>

// J2000 坐标系到地球月球固连坐标系转换，坐标系定义，X 轴指向月球，Z轴为月球轨道面法向，右手法则
VBF_MATH_EXPORT osg::Matrixd VBF_J2000toEarthMoon(double Mjd);

#endif
