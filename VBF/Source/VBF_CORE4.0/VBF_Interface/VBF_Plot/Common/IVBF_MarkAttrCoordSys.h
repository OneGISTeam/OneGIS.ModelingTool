//*******************************************************************
// FileName：IVBF_MarkAttrCoordSys.h
// Function：模型属性接口：点状模型的局部坐标系
// Author:   杜莹
// Date:     2017-04-06
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_COORDSYS_H__
#define __IVBF_MARK_ATTR_COORDSYS_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Plot/Common/IVBF_MarkModelCoordSys.h>


class IVBF_MarkAttrCoordSys : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrCoordSys() {}

    // 设置/获取坐标系的样式（默认为BOX）
    virtual void SetStyle(VBF::COORDSTYLE s, VBF::AXIS frame1=VBF::X1, VBF::AXIS frame2=VBF::Y1, VBF::AXIS frame3=VBF::Z1)=0;
    virtual VBF::COORDSTYLE GetStyle() const=0;


    //========================= 以下函数用于设置所有坐标轴的共同参数 ================================

    // 设置/获取所有坐标轴的颜色（默认为白色）
    virtual void       SetAxesColor(const osg::Vec4f& val)=0;
	virtual osg::Vec4f GetAxesColor()=0;

    // 设置/获取所有坐标轴刻度值的字体（默认为Courier, 10）
    virtual void SetNumberFont(const std::string& family, int pointSize, int weight=VBF::Normal, bool bItalic=false)=0;
	virtual void GetNumberFont(std::string& family, int& pointSize, int& weight, bool& bItalic)=0;

    // 设置/获取所有坐标轴刻度值的颜色（默认为黄色）
    virtual void SetNumberColor(const osg::Vec4f& val)=0;
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
    virtual void       SetLabelColor(const osg::Vec4f& val)=0;
	virtual osg::Vec4f GetLabelColor()=0;

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
