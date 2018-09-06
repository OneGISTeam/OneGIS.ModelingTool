//*******************************************************************
// FileName：IVBF_MarkModelLink.h
// Function：实体模型接口：连通线
// Author:   杜莹
// Date:     2013-11-13
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_LINK_H__
#define __IVBF_MARK_MODEL_LINK_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <Types/VBF_Optional.h>
#include <Types/VBF_3DStyles.h>
#include <Types/Vec4f>
#include <string>



//-------------------------------------------------------------------
// 定义接口：IVBF_MarkModelLink
// 接口描述：连通线
//-------------------------------------------------------------------
class IVBF_MarkModelLink : public IVBF_MarkModel
{
public:
	virtual ~IVBF_MarkModelLink() {}

	// 设置/获取连通状态：连通?断开
	virtual void SetLinked(bool bLinked)=0;
	virtual bool IsLinked()=0;

	// 设置/获取源连通点的模型，优先于函数SetGeoSrc()
	virtual void			SetMarkSrc(IVBF_MarkModel* pIMarkSrc)=0;
	virtual IVBF_MarkModel*	GetMarkSrc()=0;

	// 设置/获取目标连通点的模型，优先于函数SetGeoDst()
	virtual void			SetMarkDst(IVBF_MarkModel* pIMarkDst)=0;
	virtual IVBF_MarkModel*	GetMarkDst()=0;

	// 设置/获取源连通点的地理坐标
	virtual void				SetGeoSrc(const osg::Vec3d& ptGeo)=0;
	virtual const osg::Vec3d&	GetGeoSrc()=0;

	// 设置/获取目标连通点的地理坐标
	virtual void			  SetGeoDst(const osg::Vec3d& ptGeo)=0;
	virtual const osg::Vec3d& GetGeoDst()=0;


    // 设置路径中间点（经过点，检查点）
    virtual void SetCheckPointGeo(const std::vector<osg::Vec3d>& vPointsGeo)=0;


    // 设置/获取源和目标连通点之间的自定义插值个数（两个点之间），含起点和终点，最小值为2（如果未设置，系统内部将自动计算）
	virtual void SetNumInterpolatePoints(int num)=0;
	virtual int  GetNumInterpolatePoints()=0;

    virtual const std::vector<osg::Vec3d>& GetInterPointsGeo() = 0;

    // 设置/获取弧段的最大高度，默认值为0
    virtual void   SetArcMaxHeight(double dHeight) = 0;
    virtual double GetArcMaxHeight() = 0;
};

#endif 
