//*******************************************************************
// FileName：IVBF_MarkModelSensorRadarJammed.h
// Function：传感器实体模型：被干扰雷达
// Author:   杜莹
// Date:     2016-11-07
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_RADAR_JAMMED_H__
#define __IVBF_MARK_MODEL_SENSOR_RADAR_JAMMED_H__


#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/Shape/IVBF_MarkModelShapeRevoSurface.h>
#include <vector>


class IVBF_MarkModelSensorRadarJammed : public IVBF_MarkModelSensor
{
public:
    virtual ~IVBF_MarkModelSensorRadarJammed() {}

	// 获取传感器中的形状接口，以便设置与几何形状有关的参数
    virtual IVBF_MarkModelShapeRevoSurface* GetShape()=0;

    // 设置/获取雷达被干扰后的包络数据（地理坐标）
    virtual void SetEnvelopePointsGeo(const std::vector<osg::Vec3d>& vPointsGeo)=0;
    virtual const std::vector<osg::Vec3d>& GetEnvelopePointsGeo()=0;
};


#endif
