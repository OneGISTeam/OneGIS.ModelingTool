//*******************************************************************
// FileName：IVBF_MarkModelRadarEnergyPolar.h
// Function：军标实体模型：电磁方向图（极坐标系）
// Author:   杜莹
// Date:     2015-01-08
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_RADARENERGY_POLAR_H__
#define __IVBF_MARK_MODEL_RADARENERGY_POLAR_H__


#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <VBF_Plot/Common/IVBF_MarkModelGraphics.h>
#include <string>


class IVBF_MarkModelRadarEnergyPolar : public IVBF_MarkModelGraphics
{
public:
    virtual ~IVBF_MarkModelRadarEnergyPolar() {}

    // 设置电磁方向图数据文件名称（完整路径，极坐标系），获取所有包络点集和颜色集合
    virtual void			   SetEnergyFileName(const std::string& strFileName)=0;
	virtual const std::string& GetEnergyFileName()=0;

    virtual void  SetSize(float fSize)=0;
	virtual float GetSize()=0;
};


#endif 
