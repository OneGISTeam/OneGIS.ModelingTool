//*******************************************************************
// FileName：IVBF_MarkAttrSphereAttitude.h
// Function：属性：模型的姿态球
// Author:   杜莹
// Date:     2015-04-28
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_SPHEREATTITUDE_H__
#define __IVBF_MARK_ATTR_SPHEREATTITUDE_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeSphereAttitude.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkAttrSphereAttitude
// 接口描述：属性：模型的姿态球
//--------------------------------------------------------------------
class IVBF_MarkAttrSphereAttitude : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrSphereAttitude() {}

    // 设置/获取两个Lod级别姿态球切换时，模型距离视点的距离（单位：米）
    virtual void  SetToggleDist(float fDist)=0;
    virtual float GetToggleDist()=0;

	// 设置/获取x/y/z坐标轴是否可见
	virtual void SetAxisVisible(EVBF_AXIS nAxis, bool bVisible)=0;
	virtual bool IsAxisVisible(EVBF_AXIS nAxis)=0;

	// 设置/获取x/y/z坐标轴的颜色
	virtual void       SetAxisColor(EVBF_AXIS nAxis, const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetAxisColor(EVBF_AXIS nAxis)=0;

	// 设置/获取x/y/z坐标轴箭头的颜色
	virtual void       SetAxisArrowColor(EVBF_AXIS nAxis, const osg::Vec4f& color)=0;
	virtual osg::Vec4f GetAxisArrowColor(EVBF_AXIS nAxis)=0;

	// 设置/获取x/y/z坐标轴的标签是否可见（默认值为false）
	virtual void SetAxisTextVisible(EVBF_AXIS nAxis, bool bVisible)=0;
	virtual bool IsAxisTextVisible(EVBF_AXIS nAxis)=0;

	// 设置/获取x/y/z坐标轴的标签样式
	virtual void          SetAxisTextStyle(EVBF_AXIS nAxis, const VBF_TEXTSTYLE& style)=0;
	virtual VBF_TEXTSTYLE GetAxisTextStyle(EVBF_AXIS nAxis)=0;

    // 设置/获取赤道和中央经线上的刻度是否可见（默认值为true）
    virtual void SetLabelVisible(bool bVisible)=0;
    virtual bool IsLabelVisible()=0;

    // 设置/获取赤道和中央经线上的刻度样式
    virtual void                 SetLabelStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetLabelStyle()=0;

    // 添加/删除一个附加坐标轴（如果已经存在，不再重复添加，返回false）
    virtual bool AddExtraAxis(const std::string& strAxisID, const osg::Vec3f& vAxisDir)=0;
    virtual void DeleteExtraAxis(const std::string& strAxisID)=0;

    // 设置/获取某个附加坐标轴的朝向（前提是该附加轴已经成功添加）
    virtual void SetExtraAxisDir(const std::string& strAxisID, const osg::Vec3f& vAxisDir)=0;
    virtual bool GetExtraAxisDir(const std::string& strAxisID, osg::Vec3f& vAxisDir)=0;

    // 设置/获取某个附加坐标轴的颜色（前提是该附加轴已经成功添加）
    virtual void SetExtraAxisColor(const std::string& strAxisID, const osg::Vec4f& colorAxis, const osg::Vec4f& colorArrow)=0;
    virtual bool GetExtraAxisColor(const std::string& strAxisID, osg::Vec4f& colorAxis, osg::Vec4f& colorArrow)=0;

    // 设置/获取某个附加坐标轴的文本样式（前提是该附加轴已经成功添加）
    virtual void SetExtraAxisTextStyle(const std::string& strAxisID, const VBF_TEXTSTYLE& TextStyle)=0;
    virtual bool GetExtraAxisTextStyle(const std::string& strAxisID, VBF_TEXTSTYLE& TextStyle)=0;
};


#endif 
