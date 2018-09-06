//*******************************************************************
// FileName：IVBF_MarkModelShapeSphereAttitude.h
// Function：军标实体模型：姿态球（用于展现飞行器等模型在运动过程中的姿态）
// Author:   杜莹
// Date:     2013-07-12
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_SPHERE_ATTITUDE_H__
#define __IVBF_MARK_MODEL_SHAPE_SPHERE_ATTITUDE_H__


#include <VBF_Plot/Shape/IVBF_MarkModelShapeDome.h>


//-----------------------------------------------------
// 定义枚举：EVBF_AXIS
// 枚举描述：坐标轴
//-----------------------------------------------------
enum EVBF_AXIS
{
	VBF_AXIS_X = 0,
	VBF_AXIS_Y = 1,
	VBF_AXIS_Z = 2
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapeSphereAttitude
// 接口描述：姿态球
//--------------------------------------------------------------------
class IVBF_MarkModelShapeSphereAttitude : public IVBF_MarkModelShapeDome
{
public:
	virtual ~IVBF_MarkModelShapeSphereAttitude() {}

public:

	// 设置/获取球体半径（默认情况下：原点位于球心，半径为1.0）
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;

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
