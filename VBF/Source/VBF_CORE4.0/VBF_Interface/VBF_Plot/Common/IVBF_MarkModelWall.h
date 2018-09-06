//*******************************************************************
// FileName：IVBF_MarkModelWall.h
// Function：实体模型接口：三维空间中的直立墙
// Author:   杜莹
// Date:     2014-08-15
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_WALL_H__
#define __IVBF_MARK_MODEL_WALL_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3d>
#include <Types/Vec4>
#include <vector>


class IVBF_MarkModelWall : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelWall() {}

    // 设置/获取墙顶部折线的坐标串（地理坐标）
    // 参数：vPointsGeo -- 地理坐标中前两维表示经度和纬度，第三维表示墙顶部的高程值，第四维表示墙底部的高程值
    // 参数：bNeedInterpolate -- 是否需要在系统内部沿大圆线插值
    virtual void SetPointsGeo(const std::vector<osg::Vec4d>& vPointsGeo, bool bNeedInterpolate)=0;
    virtual void GetPointsGeo(std::vector<osg::Vec4d>& vPointsGeo, bool& bNeedInterpolate)=0;

    // 设置/获取墙的顶部曲线是否可见
    virtual void SetLineVisible(bool bVisible)=0;
    virtual bool IsLineVisible()=0;

    // 设置/获取墙的顶部曲线样式
    virtual void                 SetLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetLineStyle()=0;

    // 设置/获取墙面的渐变色
    virtual void SetColor(const osg::Vec4f& colorTop, const osg::Vec4f& colorBottom)=0;
    virtual void GetColor(osg::Vec4f& colorTop, osg::Vec4f& colorBottom)=0;

	// 设置/获取纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// 设置/获取纹理在纵横方向的重复次数，默认值均为1
	virtual void SetNumTexRepeats(int nNumRows, int nNumCols)=0;
	virtual void GetNumTexRepeats(int& nNumRows, int& nNumCols)=0;

	// 设置/获取墙面纹理的透明度（值域为[0.0, 1.0]，默认值为1.0）
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;
};

#endif 
