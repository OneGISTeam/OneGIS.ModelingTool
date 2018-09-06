//*******************************************************************
// FileName：IVBF_MarkModelAirLine.h
// Function：实体模型：航线
// Author:   杜莹
// Date:     2014-01-07
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_AIRLINE_H__
#define __IVBF_MARK_MODEL_AIRLINE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>



//------------------------------------------------------------------
// 定义枚举：EVBF_AIRLINE_PART
// 枚举描述：航线的各个部分
//------------------------------------------------------------------
enum EVBF_AIRLINE_PART
{
	VBF_AIRLINE_PART_ORIGN		= 0,	// 原始航线
	VBF_AIRLINE_PART_SMOOTH		= 1,	// 光滑后的航线
	VBF_AIRLINE_PART_HINT		= 2,	// 高度指示线
	VBF_AIRLINE_PART_PIPE		= 3,	// 航线通道（闭合环）
	VBF_AIRLINE_PART_COUNT				// 总数
};


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelAirLine
// 接口描述：航线
//--------------------------------------------------------------------
class IVBF_MarkModelAirLine : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelAirLine() {}

	// 设置/获取航线的坐标串（地理坐标），参数nNumInterPoints表示插值点数
	virtual void SetPointsGeo(const std::vector<osg::Vec3d>& vPointsGeo, int nNumInterPoints=100)=0;
	virtual void GetPointsGeo(std::vector<osg::Vec3d>& vPointsGeo, int& nNumInterPoints)=0;

	// 获取航线光滑后的坐标串（地理坐标）
	virtual const std::vector<osg::Vec3d>& GetSmoothPointsGeo()=0;

	// 设置/获取航线通道的宽度（单位：米）
	virtual void  SetPipeWidth(float fWidth)=0;
	virtual float GetPipeWidth()=0;

	// 设置/获取航线通道的高度（单位：米）
	virtual void  SetPipeHeight(float fHeight)=0;
	virtual float GetPipeHeight()=0;

	// 设置/获取某个部分的可见性
	virtual void SetPartVisible(EVBF_AIRLINE_PART nPart, bool bVisible)=0;
	virtual bool IsPartVisible(EVBF_AIRLINE_PART nPart)=0;

	// 设置/获取某个部分的折线样式
	virtual void                 SetPartLineStyle(EVBF_AIRLINE_PART nPart, const VBF_LINESTYLE& style)=0;
	virtual const VBF_LINESTYLE& GetPartLineStyle(EVBF_AIRLINE_PART nPart)=0;

	// 设置/获取原始航线点是否可见（默认值为true）
	virtual void SetOrignPointVisible(bool bVisible)=0;
	virtual bool IsOrignPointVisible()=0;

    // 设置/获取原始航线点的样式（点的默认尺寸为6.0）
    virtual void                  SetOrignPointStyle(const VBF_POINTSTYLE& style)=0;
    virtual const VBF_POINTSTYLE& GetOrignPointStyle()=0;

    // 设置/获取原始航线点的标签是否可见（默认为可见）
    virtual void  SetOrignPointLabelVisible(bool bVisible)=0;
    virtual bool  IsOrignPointLabelVisible()=0;

	// 设置/获取原始航线点的标签样式
	virtual void                 SetOrignPointLabelStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetOrignPointLabelStyle()=0;
};


#endif 
