//*******************************************************************
// FileName：IVBF_MarkModelFanGeo.h
// Function：实体模型接口：使用地理坐标的扇形（贴地表）
// Author:   杜莹
// Date:     2014-03-04
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_FAN_H__
#define __IVBF_MARK_MODEL_FAN_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <vector>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


class IVBF_MarkModelFanGeo : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelFanGeo() {}

	// 设置/获取数据是否经常变化（默认值为false）
	virtual void SetDataDynamic(bool bDynamic)=0;
	virtual bool IsDataDynamic()=0;

	// 设置/获取扇形的圆心点，起点和终点（地理坐标）
	virtual void SetTessGeo(const osg::Vec3d& ptCenter, const osg::Vec3d& ptBegin, const osg::Vec3d& ptEnd)=0;
	virtual void GetTessGeo(osg::Vec3d& ptCenter, osg::Vec3d& ptBegin, osg::Vec3d& ptEnd)=0;

	// 获取扇形插值后的所有顶点（地理坐标，从圆心点出发，沿起点到终点结束）
	virtual void GetPointsGeo(std::vector<osg::Vec3d>& vPointsGeo)=0;

	// 设置/获取多边形的边线是否可见
	virtual void SetLineVisible(bool bVisible)=0;
	virtual bool IsLineVisible()=0;

	// 设置/获取边线的样式
	virtual void				 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;

	// 设置/获取多边形的填充样式（当纹理启用时，使用该样式中的Alpha值作为透明度）
	virtual void				      SetPolygonStyle(const VBF_POLYGON3DSTYLE& style)=0;
	virtual const VBF_POLYGON3DSTYLE& GetPolygonStyle()=0;
};



#endif 
