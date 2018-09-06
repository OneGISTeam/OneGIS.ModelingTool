//*******************************************************************
// FileName：IVBF_MarkModelChaff.h
// Function：实体模型：箔条云（由金属箔等制成，用以对敌方雷达实施无源干扰）
// Author:   杜莹
// Date:     2014-01-09
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_CHAFF_H__
#define __IVBF_MARK_MODEL_CHAFF_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>
#include <Types/VBF_3DStyles.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelChaff
// 接口描述：箔条云
//--------------------------------------------------------------------
class IVBF_MarkModelChaff : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelChaff() {}

	// 设置/获取箔条云的半径（单位：米）
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;
};


#endif 
