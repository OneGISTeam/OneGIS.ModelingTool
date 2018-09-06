//*******************************************************************
// FileName：IVBF_MarkModelSphereLight.h
// Function：实体模型：地球光影
// Author：  杜莹
// Date：    2015-04-14
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SPHERE_LIGHT_H__
#define __IVBF_MARK_MODEL_SPHERE_LIGHT_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <Types/Vec3d>
#include <VBF_Plot/Aviation/VBF_3DPlotDataTypes_Aviation.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelSphereLight
// 接口描述：实体模型：地球光影
//--------------------------------------------------------------------
class IVBF_MarkModelSphereLight : public IVBF_MarkModelPoint
{
public:
	virtual ~IVBF_MarkModelSphereLight() {}

	// 设置/获轴向，其实是设置Z轴的指向
	virtual void              SetAxis(const osg::Vec3d& vAxis)=0;
	virtual const osg::Vec3d& GetAxis()=0;

	// 设置/获取光影的厚度（单位：米，默认值为30000米）
	virtual void  SetThickness(float hThickness)=0;
	virtual float GetThickness()=0;

	// 设置纵横方向的分割数
	virtual void SetNumSplit(int nNumSplitRow, int nNumSplitCol)=0;
	virtual void GetNumSplit(int& nNumSplitRow, int& nNumSplitCol)=0;
};


#endif 
