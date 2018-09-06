#ifndef __VBF_SPACE_TIME_H__
#define __VBF_SPACE_TIME_H__

#include <VBF_Common/VBF_Math/VBF_Export.h>
#include <Types/Vec3f>
#include <Types/Vec3d>

// 计算格林威治恒星时角
VBF_MATH_EXPORT double lst(double dTime);// 注意：dTime的时间单位为秒
VBF_MATH_EXPORT double lst(double dYear, double dMonth, double dDay, double dHour, double dMinute, double dSecond);

// 将一个角度转到0到360之间
VBF_MATH_EXPORT double ZeroTo360(double dValue);

// 计算儒略日
VBF_MATH_EXPORT double J0(double dYear, double dMonth, double dDay);


VBF_MATH_EXPORT void EciToEcf(const osg::Vec3d& vEci, const double& dLst, osg::Vec3d& vEcf);
VBF_MATH_EXPORT void EcfToEci(const osg::Vec3d& vEcf, const double& dLst, osg::Vec3d& vEci);
VBF_MATH_EXPORT void EciToEcfUTC(const osg::Vec3d& vEci, double dTimeUTC, osg::Vec3d& vEcf);
VBF_MATH_EXPORT void EcfToEciUTC(const osg::Vec3d& vEcf, double dTimeUTC, osg::Vec3d& vEci);

VBF_MATH_EXPORT double JulianDay(double dYear, double dMonth, double dDay);
VBF_MATH_EXPORT void Sun(double jdate, osg::Vec3d& rsun, double&  rasc, double&  decl);
VBF_MATH_EXPORT osg::Vec3d CalSunPosECF(double dYear, double dMonth, double dDay, double dHour, double dMinute, double dSecond);
VBF_MATH_EXPORT osg::Vec3d CalSunPosECFGeo(double dYear, double dMonth, double dDay, double dHour, double dMinute, double dSecond);


#endif
