//*******************************************************************
// FileName：IVBF_MarkModelPolygon.h
// Function：实体模型接口：三维空间中的多边形（分为贴地和不贴地两种）
// Author:   杜莹
// Date:     2014-01-10
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_POLYGON_H__
#define __IVBF_MARK_MODEL_POLYGON_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <vector>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>
#include <Types/Vec3s>
#include <VBF_Engine/VBF_SceneGraph/Image>


class IVBF_MarkModelPolygon : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPolygon() {}

	// 设置/获取数据是否经常变化（默认值为false）
	virtual void SetDataDynamic(bool bDynamic)=0;
	virtual bool IsDataDynamic()=0;

	// 设置/获取折线的坐标串（地理坐标）
	virtual void						   SetPointsGeo(const std::vector<osg::Vec3d>& vPointsGeo)=0;
	virtual const std::vector<osg::Vec3d>& GetPointsGeo()=0;

	// 设置/获取折线的坐标串（地理坐标）与第0遍纹理坐标
	// 注意：这两组坐标数必须相等且顺序一致
	virtual void SetPointsGeoAndTexCoords(const std::vector<osg::Vec3d>& vPointsGeo, const std::vector<osg::Vec2f>& vTexCoords)=0;
	virtual void GetPointsGeoAndTexCoords(std::vector<osg::Vec3d>& vPointsGeo, std::vector<osg::Vec2f>& vTexCoords)=0;

	// 设置/获取多边形的边线是否可见
	virtual void SetLineVisible(bool bVisible)=0;
	virtual bool IsLineVisible()=0;

	// 设置/获取边线的样式
	virtual void				 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;

	// 设置/获取多边形顶部的填充样式（当纹理启用时，该样式无效）
	virtual void				      SetPolygonStyle(const VBF_POLYGON3DSTYLE& style)=0;
	virtual const VBF_POLYGON3DSTYLE& GetPolygonStyle()=0;

	// 设置/获取多边形对应的纹理图像指针
	// 参数：bTexToCache -- 是否需要将创建的纹理放入缓存，默认为false
	virtual void		SetTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual osg::Image* GetTexImage()=0;

	// 设置/获取顶部纹理的透明度（值域为[0.0, 1.0]，默认值为0.6）
	virtual void  SetTexAlpha(float fAlpha)=0;
	virtual float GetTexAlpha()=0;

	// 设置/获取是否使用淡入效果
	virtual void EnableFadeIn(bool bEnabled)=0;
	virtual bool IsFadeInEnable()=0;

	// 设置/获取淡入的持续时间（单位：秒，默认值为1.0秒）
	virtual void  SetFadeTime(float fTime)=0;
	virtual float GetFadeTime()=0;
};



// 贴地多边形：Match Terrain
class IVBF_MarkModelPolygonMT : public IVBF_MarkModelPolygon
{
public:
	virtual ~IVBF_MarkModelPolygonMT() {}
};



// 不贴地多边形：Not Match Terrain
class IVBF_MarkModelPolygonNMT : public IVBF_MarkModelPolygon
{
public:
	virtual ~IVBF_MarkModelPolygonNMT() {}

	// 设置/获取多边形侧面的填充样式（当侧面纹理启用时，该样式无效）
	virtual void				      SetSideStyle(const VBF_POLYGON3DSTYLE& style)=0;
	virtual const VBF_POLYGON3DSTYLE& GetSideStyle()=0;

	// 设置/获取多边形所有侧面的纹理文件名（一旦调用该函数，将忽略SetSideStyle()函数）
	// 参数：bTexToCache -- 纹理是否需要放入缓存，默认为false
	virtual void			  SetSideTexImage(osg::Image* pImage, bool bTexToCache)=0;
	virtual const osg::Image* GetSideTexImage()=0;

	// 设置/获取多边形每个侧面的纹理文件名（一旦调用该函数，将忽略SetSideStyle()函数）
	// 参数：nSideIndex  -- 侧面的索引号，必须与SetPointsGeo()函数中的顶点顺序保持一致
	//      strFileName -- 侧面使用的纹理文件
	//      nNumRows, nNumCols -- 纹理在该侧面纵横方向的重复次数
	//      bTexToCache -- 纹理是否需要放入缓存，默认为false
	virtual void SetSideTexImage(int nSideIndex, osg::Image*  pImage, int nNumRows,  int nNumCols, bool bTexToCache)=0;
	virtual bool GetSideTexImage(int nSideIndex, osg::Image*& pImage, int& nNumRows, int& nNumCols)=0;

	// 设置/获取多边形侧面纹理的透明度（值域为[0.0, 1.0]，默认值为1.0）
	virtual void  SetSideTexAlpha(float fAlpha)=0;
	virtual float GetSideTexAlpha()=0;

	// 设置/获取是否使用多边形厚度，以及厚度（单位：米）
	virtual void SetThickness(bool bHasThickness, float fThickness)=0;
	virtual void GetThickness(bool& bHasThickness, float& fThickness)=0;

	// 设置/获取是否使用挤出效果
	virtual void EnableExtrusion(bool bEnable)=0;
	virtual bool IsExtrusionEnabled()=0;

	// 设置/获取挤出的持续时间
	virtual void  SetExtrusionTime(float fTime)=0;
	virtual float GetExtrusionTime()=0;

	// 设置/获取有厚度时底部是否可见（默认值为false）
	virtual void SetBottomVisible(bool bVisible)=0;
	virtual bool IsBottomVisible()=0;
};

#endif 
