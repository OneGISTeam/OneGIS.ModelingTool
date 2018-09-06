#ifndef __IVBF_MARK_MODEL_NOT_POINT_H__
#define __IVBF_MARK_MODEL_NOT_POINT_H__


#include <VBF_Plot/IVBF_MarkModel.h>


//--------------------------------------------------------------------
// 定义接口：IVBF_MarkModelNotPoint
// 接口描述：非点状实体模型
//--------------------------------------------------------------------
class IVBF_MarkModelNotPoint : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelNotPoint() {}

public:
    // 设置/获取控制点的地理坐标，用于编辑
    virtual void SetCtrlPointsGeo(const std::vector<osg::Vec3d>& vPointsGeo) = 0;
    virtual std::vector<osg::Vec3d>& GetCtrlPointsGeo() = 0;

    virtual bool IsSameHeight() = 0;
    virtual void setHeight(double dHeight)=0;// 对于需要设置整体高度的模型来说，需要这个接口
    virtual double getHeight()=0;


    // 获得全局编辑的控制点（经纬度坐标）
    virtual osg::Vec3d GetLocationGeoPoint()=0;

};


#endif 
