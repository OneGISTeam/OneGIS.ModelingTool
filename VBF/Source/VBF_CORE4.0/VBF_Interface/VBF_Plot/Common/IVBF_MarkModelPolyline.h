//*******************************************************************
// FileName：IVBF_MarkModelPolyline.h
// Function：实体模型接口：三维空间中的折线，包括不贴地(NMT)和贴地(MT)两种
// Author:   杜莹
// Date:     2013-12-05
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_POLYLINE_H__
#define __IVBF_MARK_MODEL_POLYLINE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <vector>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


class IVBF_MarkModelPolyline : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPolyline() {}

	// 设置/获取数据是否经常变化（默认值为false）
	virtual void SetDataDynamic(bool bDynamic)=0;
	virtual bool IsDataDynamic()=0;

	// 设置/获取是否需要在系统内部沿大圆线插值（默认值为false）
	virtual void SetInterpolatable(bool bInterpolate)=0;
	virtual bool IsInterpolatable()=0;

	// 设置/获取折线的坐标串（地理坐标）
	virtual void                           SetPointsGeo(const std::vector<osg::Vec3d>& vPointsGeo)=0;
	virtual const std::vector<osg::Vec3d>& GetPointsGeo()=0;

	// 添加一个点（地理坐标）
	virtual void AddPointGeo(const osg::Vec3d& ptGeo)=0;

	// 清空折线
	virtual void Clear()=0;

	// 设置/获取折线的样式
	virtual void				 SetLineStyle(const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetLineStyle()=0;
};

// 不贴地折线
class IVBF_MarkModelPolylineNMT : public IVBF_MarkModelPolyline
{
public:
	virtual ~IVBF_MarkModelPolylineNMT() {}

	// 同时设置折线的地理和世界坐标串（此时不在系统内部插值）
	virtual void SetPointsGeoAndWorld(const std::vector<osg::Vec3d>& vPointsGeo, const std::vector<osg::Vec3d>& vPointsWorld)=0;
};


// 贴地折线
class IVBF_MarkModelPolylineMT : public IVBF_MarkModelPolyline
{
public:
	virtual ~IVBF_MarkModelPolylineMT() {}
};

#endif 
