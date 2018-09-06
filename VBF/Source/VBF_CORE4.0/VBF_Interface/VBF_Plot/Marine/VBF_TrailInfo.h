//*******************************************************************
// FileName：VBF_TrailInfo.h
// Function：与航迹信息有关的公共数据类型
// Author:   杜莹
// Date:     2016-11-09
//*******************************************************************

#ifndef __VBF_TRAIL_INFO_INFO_H__
#define __VBF_TRAIL_INFO_INFO_H__


#include <VBF_OS.h>
#include <Types/Vec3d>
#include <string>
#include <vector>


//--------------------------------------------------------
// 定义结构体：VBF_TRAIL_POINTINFO
// 结构体描述：航迹点信息
//--------------------------------------------------------
struct VBF_TRAIL_POINTINFO
{
    osg::Vec3d  ptGeo;      // 地理坐标
    double      dSpeed;     // 对地速度
    long        nUTC;       // UTC时间（单位：秒）

    VBF_TRAIL_POINTINFO()
    {
        ptGeo   = osg::Vec3d(0.0, 0.0, 0.0);
        dSpeed  = 0.0;
        nUTC    = 0;
    }

    // 拷贝构造函数
    VBF_TRAIL_POINTINFO& operator=(const VBF_TRAIL_POINTINFO& src)
    {
        if(this==&src) return *this;

        ptGeo   = src.ptGeo;
        dSpeed  = src.dSpeed;
        nUTC    = src.nUTC;

        return *this;
    }
};


//--------------------------------------------------------
// 定义结构体：VBF_TRAIL_INFO
// 结构体描述：航迹信息
//--------------------------------------------------------
struct VBF_TRAIL_INFO
{
    int                              nCode;      // 航迹的唯一编码
    std::vector<VBF_TRAIL_POINTINFO> vPoints;    // 航迹上的所有点

    VBF_TRAIL_INFO()
    {
        nCode  = -1;
    }

    // 拷贝构造函数
    VBF_TRAIL_INFO& operator=(const VBF_TRAIL_INFO& src)
    {
        if(this==&src) return *this;

        nCode = src.nCode;
        if(src.vPoints.size()>0)
        {
            vPoints.clear();
            vPoints.assign(src.vPoints.begin(), src.vPoints.end());
        }

        return *this;
    }
};


typedef std::vector<std::string>   CVBF_UserValueVector;


//-------------------------------------------------------------------------------
// 定义结构体：VBF_TRAIL_EXTINFO
// 结构体描述：航迹的扩展信息，需要向外部模块请求（避免在系统内部存储，占用内存，该信息通常用于展示信息气泡）
//-------------------------------------------------------------------------------
struct VBF_TRAIL_EXTINFO
{
public:
    int                                 nCode;              // 唯一编码（由系统内部提供）
    CVBF_UserValueVector                vValuesStatic;      // 静态扩展信息（需要外部模块赋值）
    std::vector<CVBF_UserValueVector>   vValuesDynamic;     // 动态扩展信息（即每个航迹点的扩展信息，需要外部模块赋值）

    // 拷贝构造函数
    VBF_TRAIL_EXTINFO& operator=(const VBF_TRAIL_EXTINFO& src)
    {
        if(this==&src) return *this;

        nCode         = src.nCode;
        vValuesStatic = src.vValuesStatic;

        vValuesDynamic.clear();
        for(int i=0; i<src.vValuesDynamic.size(); i++)
        {
            vValuesDynamic.push_back( src.vValuesDynamic[i] );
        }

        return *this;
    }

    // 清空数据
    void Clear()
    {
        vValuesStatic.clear();
        vValuesDynamic.clear();
    }
};


#endif
