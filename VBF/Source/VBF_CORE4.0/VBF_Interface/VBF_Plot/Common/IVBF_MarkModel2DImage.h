//*******************************************************************
// FileName：IVBF_MarkModel2DImage.h
// Function：实体模型接口：2D图像，使用屏幕坐标
// Author:   杜莹
// Date:     2014-02-25
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_IMAGE2D_H__
#define __IVBF_MARK_MODEL_IMAGE2D_H__


#include <VBF_Plot/Common/IVBF_MarkModel2D.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <string>
#include <VBF_Engine/VBF_SceneGraph/Image>



//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModel2DImage
// 接口描述：2D图像，使用屏幕坐标
//--------------------------------------------------------------------
class IVBF_MarkModel2DImage : public IVBF_MarkModel2D
{
public:
    virtual ~IVBF_MarkModel2DImage() {}

	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// 设置/获取纹理的透明度（值域为[0.0, 1.0]，默认值为0.6）
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;

	// 设置/获取是否锁定图片原有的纵横比，默认为true
    virtual void SetLockAspect(bool bLockAspect)=0;
    virtual bool IsLockAspect()=0;

};


#endif 
