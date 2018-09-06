//*******************************************************************
// FileName：IVBF_MarkModelPolylineTex.h
// Function：实体模型接口：三维空间中的折线，且沿线重复贴纹理
// Author:   杜莹
// Date:     2015-08-25
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_POLYLINE_TEXT_H__
#define __IVBF_MARK_MODEL_POLYLINE_TEXT_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <vector>
#include <VBF_Plot/Common/VBF_3DPlotDataTypes_Common.h>


class IVBF_MarkModelPolylineTex : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelPolylineTex() {}

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

	// 设置/获取折线的纹理样式
	virtual void                    SetTextureStyle(const VBF_LINETEXSTYLE& style)=0;
	virtual const VBF_LINETEXSTYLE& GetTextureStyle()=0;
};

#endif 
