//*******************************************************************
// FileName：VBF_ParamSurfaceDemo.h
// Function：几个参数化曲面的示例
// Author:   杜莹
// Date:     2017-04-11
//*******************************************************************

#ifndef __VBF_PARAM_SURFACE_DEMO_H__
#define __VBF_PARAM_SURFACE_DEMO_H__


#include <VBF_Plot/Common/VBF_ParamSurface.h>


//-------------------------------------------------------------------
// 定义类：CVBF_ParamSurfaceSphere
// 类描述：参数曲面：球体
//-------------------------------------------------------------------
class CVBF_ParamSurfaceSphere : public CVBF_ParamSurface
{
public:
    CVBF_ParamSurfaceSphere(double r=1.0) :
        CVBF_ParamSurface(), m_dRadius(r)
    {
        SetMesh(41, 31);
        SetDomain(0,2*osg::PI, 0, osg::PI);
        SetPeriodic(false, false);
    }

    // 用户必须重载该函数，建立(x,y,z)=f(u, v)之间的函数关系
    virtual osg::Vec3d operator()(double u, double v)
    {
        double x = m_dRadius * cos(u) * sin(v);
        double y = m_dRadius * sin(u) * sin(v);
        double z = m_dRadius * cos(v);

        return osg::Vec3d(x, y, z);
    }

private:
    double  m_dRadius;  // 球体半径
};

//-------------------------------------------------------------------
// 定义类：CVBF_ParamSurfaceTorus
// 类描述：参数曲面：圆环
//-------------------------------------------------------------------
class CVBF_ParamSurfaceTorus : public CVBF_ParamSurface
{
public:
    CVBF_ParamSurfaceTorus(double r=1.9) :
        CVBF_ParamSurface(), m_dRadius(r)
    {
        SetMesh(31, 41);
        SetDomain(-2*osg::PI, 0, -2*osg::PI, 0);
        SetPeriodic(true, true);
    }

    // 用户必须重载该函数，建立(x,y,z)=f(u, v)之间的函数关系
    virtual osg::Vec3d operator()(double u, double v)
    {
        double x = (m_dRadius + cos(v)) * cos(u);
        double y = (m_dRadius + cos(v)) * sin(u);
        double z = sin(v) + cos(v);

        return osg::Vec3d(x, y, z);
    }

private:
    double  m_dRadius;
};

//-------------------------------------------------------------------
// 定义类：CVBF_ParamSurfaceSeashell
// 类描述：参数曲面：贝壳
//-------------------------------------------------------------------
class CVBF_ParamSurfaceSeashell : public CVBF_ParamSurface
{
public:
    CVBF_ParamSurfaceSeashell() : CVBF_ParamSurface()
    {
        SetMesh(131, 41);
        SetDomain(0, 2*osg::PI, 0, 2*osg::PI);
        SetPeriodic(true, true);
    }

    // 用户必须重载该函数，建立(x,y,z)=f(u, v)之间的函数关系
    virtual osg::Vec3d operator()(double u, double v)
    {
        double a = 1;
        double b = 6;
        double c = 0.5;
        int n = 3;

        double f = v/(2*osg::PI);

        double x = a*(1-f)*cos(n*v)*(1+cos(u)) + c*cos(n*v) ;
        double y = a*(1-f)*sin(n*v)*(1+cos(u)) + c*sin(n*v) ;
        double z = b*f + a*(1-f)*sin(u);
        return osg::Vec3d(x, y, z);
    }
};

//-------------------------------------------------------------------
// 定义类：CVBF_ParamSurfaceBoy
// 类描述：参数曲面：
//-------------------------------------------------------------------
class CVBF_ParamSurfaceBoy : public CVBF_ParamSurface
{
public:
    CVBF_ParamSurfaceBoy() : CVBF_ParamSurface()
    {
        SetMesh(131, 141);
        SetDomain(0, osg::PI, 0, osg::PI);
        SetPeriodic(true, true);
    }

    // 用户必须重载该函数，建立(x,y,z)=f(u, v)之间的函数关系
    virtual osg::Vec3d operator()(double u, double v)
    {
        double a = 2/3.0;
        double b = sqrt(2.0);

        double x = a*(cos(u)*cos(2*v)+b*sin(u)*cos(v))*cos(u) / (b-sin(2*u)*sin(3*v));
        double y = a*(cos(u)*sin(2*v)-b*sin(u)*sin(v))*cos(u) / (b-sin(2*u)*sin(3*v));
        double z = b*cos(u)*cos(u) / (b-sin(2*u)*sin(2*v));

        return osg::Vec3d(x, y, z);
    }
};

//-------------------------------------------------------------------
// 定义类：CVBF_ParamSurfaceDini
// 类描述：参数曲面：
//-------------------------------------------------------------------
class CVBF_ParamSurfaceDini : public CVBF_ParamSurface
{
public:
    CVBF_ParamSurfaceDini() : CVBF_ParamSurface()
    {
        SetMesh(35, 141);
        SetDomain(0, 5*osg::PI, 0.001, 2);
        SetPeriodic(true, true);
    }

    // 用户必须重载该函数，建立(x,y,z)=f(u, v)之间的函数关系
    virtual osg::Vec3d operator()(double u, double v)
    {
        double a = 5;
        double b = 1;

        double x=a*cos(u)*sin(v);
        double y=a*sin(u)*sin(v);
        double z=a*(cos(v)+log(tan(v/2)))+b*u;

        return osg::Vec3d(x, y, z);
    }
};

#endif
