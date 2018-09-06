//*******************************************************************
// FileName：IVBF_MarkModelShapePoint3D.h
// Function：军标实体模型接口：单个点（使用三维空间中的坐标）
// Author:   杜莹
// Date:     2014-01-07
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SHAPE_POINT3D_H__
#define __IVBF_MARK_MODEL_SHAPE_POINT3D_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShape.h>
#include <Types/VBF_3DStyles.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelShapePoint3D
// 接口描述：单个点（使用三维空间中的坐标）
//--------------------------------------------------------------------
class IVBF_MarkModelShapePoint3D : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelShapePoint3D() {}

    // 设置/获取点的样式
    virtual void                  SetPointStyle(const VBF_POINTSTYLE& style)=0;
    virtual const VBF_POINTSTYLE& GetPointStyle()=0;

	// 设置/获取点的着色方式，默认为：只使用颜色
	virtual void             SetShadeStyle(EVBF_SHADE_STYLE nStyle)=0;
	virtual EVBF_SHADE_STYLE GetShadeStyle()=0;

	// 设置/获取纹理图像
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// 设置/获取纹理的透明度（值域为[0.0, 1.0]，默认值为1.0）
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;
};


#endif 
