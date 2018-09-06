//*******************************************************************
// FileName：IVBF_MarkAttrMissileFire.h
// Function：模型属性接口：导弹尾焰
// Author:   杜莹
// Date:     2014-12-02
//*******************************************************************

#ifndef __IVBF_MARK_ATTR_MISSILE_FIRE_H__
#define __IVBF_MARK_ATTR_MISSILE_FIRE_H__


#include <VBF_Plot/IVBF_MarkAttr.h>
#include <VBF_Engine/VBF_SceneGraph/Image>


class IVBF_MarkAttrMissileFire : public IVBF_MarkAttr
{
public:
    virtual ~IVBF_MarkAttrMissileFire() {}

    // 设置/获取尾焰的宽度和高度（单位：米）
    virtual void SetSize(float fWidth, float fHeight)=0;
    virtual void GetSize(float& fWidth, float& fHeight)=0;

    // 设置/获取尾焰的动态缩放值（默认值为0.2）
    virtual void  SetRandomScale(float fScale)=0;
    virtual float GetRandomScale()=0;

    // 设置/获取尾焰的中心轴
    virtual void              SetAxis(const osg::Vec3f& vAxis)=0;
    virtual const osg::Vec3f& GetAxis()=0;

	// 设置尾焰起点相对于模型中心点的偏移量（默认值为(0, 0, 0)）
	virtual void SetOffset(float fOffsetX, float fOffsetY, float fOffsetZ)=0;
	virtual void GetOffset(float& fOffsetX, float& fOffsetY, float& fOffsetZ)=0;

	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;
};


#endif 
