//*******************************************************************
// FileName：IVBF_MarkModelCrossQuad.h
// Function：十字交叉模型，可以实现导弹尾焰、十字交叉树等
// Author:   杜莹
// Date:     2014-11-24
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_CROSS_QUAD_H__
#define __IVBF_MARK_MODEL_CROSS_QUAD_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <Types/Vec3f>
#include <string>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelCrossQuad
// 接口描述：十字交叉模型，可以实现导弹尾焰、十字交叉树等
//--------------------------------------------------------------------
class IVBF_MarkModelCrossQuad : public IVBF_MarkModelPoint
{
public:
    virtual ~IVBF_MarkModelCrossQuad() {}

    // 设置/获取单个四边形的宽度和高度（单位：米）
    virtual void SetSize(float fWidth, float fHeight)=0;
    virtual void GetSize(float& fWidth, float& fHeight)=0;

    // 设置/获取中心轴
    virtual void              SetAxis(const osg::Vec3f& vAxis)=0;
    virtual const osg::Vec3f& GetAxis()=0;

	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void        SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;
};


#endif 
