//*******************************************************************
// FileName：IVBF_MarkAttrTrailStrip.h
// Function：模型属性接口：模型属性：模型的运动轨迹（条带形，如飞机的尾迹）
//           注意：只允许Mesh类实体模型使用条带形轨迹
// Author:   杜莹
// Date:     2013-12-16
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_TRAIL_STRIP_H__
#define __IVBF_MARK_ATTR_TRAIL_STRIP_H__


#include <VBF_Plot/Common/IVBF_MarkAttrTrail.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Engine/VBF_SceneGraph/Image>


class IVBF_MarkAttrTrailStrip : public IVBF_MarkAttrTrail
{
public:
	virtual ~IVBF_MarkAttrTrailStrip() {}
	
	// 设置/获取条带的颜色（注意：如果启用纹理，该颜色的RGBA分量分别与纹理的对应分量相乘）
	virtual void			  SetStripColor(const osg::Vec4f& color)=0;
	virtual const osg::Vec4f& GetStripColor()=0;

	// 设置/获取条带使用的纹理图像
	virtual void		SetStripTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetStripTexImage()=0;

	// 设置/获取尾迹条带的宽度（单位：米）
	virtual void  SetStripWidth(float fWidth)=0;
	virtual float GetStripWidth()=0;

	// 设置条带起点相对于模型尾部中心点的偏移量（默认值为(0, -1, 0)）
	virtual void SetStripOffset(float fOffsetX, float fOffsetY, float fOffsetZ)=0;
    virtual void GetStripOffset(float& fOffsetX, float& fOffsetY, float& fOffsetZ)=0;
};


#endif 
