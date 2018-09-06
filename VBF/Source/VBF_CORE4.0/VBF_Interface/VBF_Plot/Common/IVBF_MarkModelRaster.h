//*******************************************************************
// FileName：IVBF_MarkModelRaster.h
// Function：栅格型军标实体模型接口
// Author:
// Date:     2009-4-10
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RASTER_H__
#define __IVBF_MARK_MODEL_RASTER_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <string>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelRaster
// 接口描述：栅格型军标实体模型
//--------------------------------------------------------------------
class IVBF_MarkModelRaster : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelRaster() {}
	
	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

    // 设置/获取纹理的透明度（默认值为1.0）
    virtual void  SetTexAlpha(float fAlpha)=0;
    virtual float GetTexAlpha()=0;
    virtual void  SetTexColor(osg::Vec4f color)=0;

	// 设置/获取纹理原点在位图中的相对位置 (相对于左下角，值域为[0.0, 1.0])
	virtual void SetTexOrign(float fTexOrignX, float fTexOrignY)=0;
    virtual void GetTexOrign(float& fTexOrignX, float& fTexOrignY)=0;

	// 设置/获取图像经过缩放后的实际尺寸（单位：米），仅适用于EnableFixedSizeInPixels(false)的情况
	// 注意：如果此处设置的长宽比不等于原始长宽比，会导致图像变形
	virtual void SetSizeInMeters(float fWidth, float fHeight)=0;
	virtual void GetSizeInMeters(float& fWidth, float& fHeight)=0;

	virtual void  SetAutoEnlarge(float fScaleMax, float fDelta, bool bMultify)=0;
};


#endif 
