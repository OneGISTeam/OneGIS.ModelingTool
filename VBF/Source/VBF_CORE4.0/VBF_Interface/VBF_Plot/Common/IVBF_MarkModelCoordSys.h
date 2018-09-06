//*******************************************************************
// FileName：IVBF_MarkModelCoordSys.h
// Function：实体模型接口：坐标系
// Author:   杜莹
// Date:     2017-04-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_COORDSYS_H__
#define __IVBF_MARK_MODEL_COORDSYS_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>
#include <Types/Vec4f>
#include <vector>

namespace VBF
{
    //------------------------------------------------------
    // 定义枚举：COORDSTYLE
    // 枚举描述：坐标系的样式
    //------------------------------------------------------
    enum COORDSTYLE
    {
        NOCOORD,        // 不显示坐标系
        BOX,            // 盒状坐标系（类似于模型的包围盒，默认值）
        FRAME           // 框架状坐标系，只有3个轴
    };

    //------------------------------------------------------
    // 定义枚举：AXIS
    // 枚举描述：盒状坐标系的12个轴（即包围盒的12条边）
    //------------------------------------------------------
    enum AXIS
    {
        X1 = 0,
        X2 = 3,
        X3 = 4,
        X4 = 5,
        Y1 = 1,
        Y2 = 8,
        Y3 = 7,
        Y4 = 6,
        Z1 = 2,
        Z2 = 9,
        Z3 = 11,
        Z4 = 10
    };

    //------------------------------------------------------
    // 定义枚举：SIDE
    // 枚举描述：盒状坐标系的6个面
    //------------------------------------------------------
    enum SIDE
    {
        NOSIDEGRID = 0,
        LEFT   = 1 << 0,
        RIGHT  = 1 << 1,
        CEIL   = 1 << 2,
        FLOOR  = 1 << 3,
        FRONT  = 1 << 4,
        BACK   = 1 << 5
    };

    //------------------------------------------------------
    // 定义枚举：SCALETYPE
    // 枚举描述：坐标轴上的刻度方式
    //------------------------------------------------------
    enum SCALETYPE
    {
        LINEARSCALE,    // 线性刻度（默认值）
        LOG10SCALE,     // log10
        USERSCALE       // 用户自定义的刻度
    };

    //------------------------------------------------------
    // 定义枚举：ANCHOR
    // 枚举描述：标签等的定位方式
    //------------------------------------------------------
    enum ANCHOR
    {
        BottomLeft,
        BottomRight,
        BottomCenter,
        TopLeft,
        TopRight,
        TopCenter,
        CenterLeft,
        CenterRight,
        Center
    };

    //------------------------------------------------------
    // 定义枚举：FONTWEIGHT
    // 枚举描述：字体的加粗样式
    //------------------------------------------------------
    enum FONTWEIGHT
    {
        Light    = 25,
        Normal   = 50,
        DemiBold = 63,
        Bold     = 75,
        Black    = 87
    };
}


class IVBF_MarkModelCoordSys : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelCoordSys() {}

    // 设置/获取坐标系的样式（默认为BOX）
    virtual void SetStyle(VBF::COORDSTYLE s, VBF::AXIS frame1=VBF::X1, VBF::AXIS frame2=VBF::Y1, VBF::AXIS frame3=VBF::Z1)=0;
    virtual VBF::COORDSTYLE GetStyle() const=0;

    // 设置/获取坐标系刻度值范围是否从父模型包围盒获取（默认为true，如果为false，用户需要调用SetPostion()函数）
    virtual void SetPositionFromParent(bool bFromParent)=0;
    virtual bool IsPositionFromParent()=0;

    // 设置/获取坐标系的xyz刻度值范围，参数first、second分别表示最小刻度值和最大刻度值所在处
    virtual void SetPosition(osg::Vec3d first, osg::Vec3d second)=0;
    virtual osg::Vec3d  GetPositionFirst()=0;
    virtual osg::Vec3d  GetPositionSecond()=0;


    //========================= 以下函数用于设置所有坐标轴的共同参数 ================================

    // 设置所有坐标轴的颜色（默认为白色）
    virtual void	   SetAxesColor(const osg::Vec4f& val)=0;
	virtual osg::Vec4f GetAxesColor()=0;

    // 设置所有坐标轴刻度值的字体（默认为Courier, 10）
    virtual void SetNumberFont(const std::string& family, int pointSize, int weight=VBF::Normal, bool bItalic=false)=0;
	virtual void GetNumberFont(std::string& family, int& pointSize, int& weight, bool& bItalic)=0;

    // 设置/获取所有坐标轴刻度值的颜色（默认为黄色）
    virtual void	   SetNumberColor(const osg::Vec4f& val)=0;
	virtual osg::Vec4f GetNumberColor()=0;

    // 设置所有坐标轴都使用线性刻度法
    virtual void SetStandardScale()=0;

    // 设置/获取坐标轴与刻度值之间的间隔（单位：像素，默认为0）
    virtual void SetNumberGap(int val)=0;
	virtual int  GetNumberGap()=0;

    // 设置/获取坐标轴与标签之间的间隔（单位：像素，默认为0）
    virtual void SetLabelGap(int val)=0;
	virtual int  GetLabelGap()=0;

    // 设置/获取所有坐标轴标签的字体（默认为Courier, 12）
    virtual void SetLabelFont(const std::string& family, int pointSize, int weight=VBF::Normal, bool bItalic=false)=0;
	virtual void GetLabelFont(std::string& family, int& pointSize, int& weight, bool& bItalic)=0;

    // 设置/获取所有坐标轴标签的颜色（默认为黄色）
    virtual void		SetLabelColor(const osg::Vec4f& val)=0;
	virtual  osg::Vec4f GetLabelColor()=0;

    // 设置/获取所有坐标轴及其刻度的线宽（默认为1.0）
    virtual void   SetLineWidth(double val, double majfac=0.9, double minfac=0.5)=0;
	virtual double GetLineWidth()=0;

    // 设置/获取所有坐标轴是否都能自动标注刻度（默认为true）
    virtual void SetAutoScale(bool val=true)=0;
	virtual bool IsAutoScale()=0;

    // 设置/获取坐标轴是否自动装饰（默认为true）
    virtual void SetAutoDecoration(bool val=true)=0;
    virtual bool IsAutoDecoration() const=0;

    // 设置/获取坐标轴是否启用线光滑（默认为true）
    virtual void SetLineSmooth(bool val=true)=0;
    virtual bool IsLineSmooth() const=0;

    // 设置/获取需要绘制主次网格线的面，可以是多个面的组合（默认为不绘制）
    virtual void SetGridSides(bool majors, bool minors, int sides=VBF::NOSIDEGRID)=0;
    virtual int  GetGridSides() const=0;

    // 设置/获取坐标网格线的颜色（默认为白色）
    virtual void       SetGridLinesColor(const osg::Vec4f& val)=0;
    virtual osg::Vec4f GetGridLinesColor()=0;


    //========================= 以下函数用于设置单个坐标轴的参数 ================================

    // 设置/获取某个坐标轴的刻度是否对称（默认为false）
    virtual void SetSymmetricTics(VBF::AXIS nAxis, bool val)=0;
    virtual bool IsSymmetricTics(VBF::AXIS nAxis)=0;

    // 设置/获取某个坐标轴标签的字体
    virtual void SetLabelFont(VBF::AXIS nAxis, const std::string& family, int pointSize, int weight=VBF::Normal, bool bItalic=false)=0;
    virtual void GetLabelFont(VBF::AXIS nAxis, std::string& family, int& pointSize, int& weight, bool& bItalic)=0;

    // 设置/获取某个坐标轴标签的字符串
    virtual void        SetLabelString(VBF::AXIS nAxis, const std::string& name)=0;
    virtual std::string GetLabelString(VBF::AXIS nAxis)=0;

    // 设置/获取某个坐标轴标签的颜色
    virtual void       SetLabelColor(VBF::AXIS nAxis, const osg::Vec4f& val)=0;
    virtual osg::Vec4f GetLabelColor(VBF::AXIS nAxis)=0;

    // 设置/获取某个坐标轴的标签是否可见（默认为false，如果开启自动装饰，则可能为true）
    virtual void SetLabelVisible(VBF::AXIS nAxis, bool val)=0;
    virtual bool IsLabelVisible(VBF::AXIS nAxis)=0;

    // 设置/获取某个坐标轴与其标签之间的间隔（单位：像素，默认为0）
    virtual void SetLabelGap(VBF::AXIS nAxis, int val)=0;
    virtual int  GetLabelGap(VBF::AXIS nAxis)=0;

    // 设置/获取某个坐标轴的刻度是否可见（默认为false，如果开启自动装饰，则可能为true）
    virtual void SetScaleVisible(VBF::AXIS nAxis, bool val)=0;
    virtual bool IsScaleVisible(VBF::AXIS nAxis) const=0;

    // 设置/获取某个坐标轴的刻度值是否可见（默认为false，如果开启自动装饰，则可能为true）
    virtual void SetNumberVisible(VBF::AXIS nAxis, bool val)=0;
    virtual bool IsNumberVisible(VBF::AXIS nAxis) const=0;

    // 设置/获取某个坐标轴刻度值的颜色
    virtual void       SetNumberColor(VBF::AXIS nAxis, const osg::Vec4f& val)=0;
    virtual osg::Vec4f GetNumberColor(VBF::AXIS nAxis) const=0;

    // 设置/获取某个坐标轴刻度值的字体
    virtual void SetNumberFont(VBF::AXIS nAxis, const std::string& family, int pointSize, int weight=VBF::Normal, bool bItalic=false)=0;
    virtual void GetNumberFont(VBF::AXIS nAxis, std::string& family, int& pointSize, int& weight, bool& bItalic)=0;

    // 设置/获取某个坐标轴刻度值的定位方式（默认为Center）
    virtual void SetNumberAnchor(VBF::AXIS nAxis, VBF::ANCHOR val)=0;
    virtual VBF::ANCHOR GetNumberAnchor(VBF::AXIS nAxis)=0;

    // 设置/获取某个坐标轴与其刻度值之间的间隔（单位：像素，默认为0）
    virtual void SetNumberGap(VBF::AXIS nAxis, int val)=0;
    virtual int  GetNumberGap(VBF::AXIS nAxis)=0;

    // 设置/获取某个坐标轴是否自动标注刻度（单位：像素，默认为true）
    virtual void SetAutoScale(VBF::AXIS nAxis, bool val=true)=0;
    virtual bool IsAutoScale(VBF::AXIS nAxis) const=0;

    // 设置/获取某个坐标轴上的主刻度个数（如果开启自动标注，该值可能会被修改）
    virtual void SetMajorCount(VBF::AXIS nAxis, int val)=0;
    virtual int  GetMajorCount(VBF::AXIS nAxis)=0;

    // 设置/获取某个坐标轴上相邻两个主刻度之间的次刻度个数
    virtual void SetMinorCount(VBF::AXIS nAxis, int val)=0;
    virtual int  GetMinorCount(VBF::AXIS nAxis)=0;

    // 设置/获取某个坐标轴及主次刻度的线宽
    virtual void   SetLineWidth(VBF::AXIS nAxis, double val, double majfac=0.9, double minfac=0.5)=0;
    virtual double GetLineWidth(VBF::AXIS nAxis) const=0;
    virtual double GetMajorLineWidth(VBF::AXIS nAxis) const=0;
    virtual double GetMinorLineWidth(VBF::AXIS nAxis) const=0;
};

#endif 
