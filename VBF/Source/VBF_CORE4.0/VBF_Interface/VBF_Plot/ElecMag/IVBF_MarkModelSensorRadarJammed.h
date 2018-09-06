//*******************************************************************
// FileName��IVBF_MarkModelSensorRadarJammed.h
// Function��������ʵ��ģ�ͣ��������״�
// Author:   ��Ө
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

	// ��ȡ�������е���״�ӿڣ��Ա������뼸����״�йصĲ���
    virtual IVBF_MarkModelShapeRevoSurface* GetShape()=0;

    // ����/��ȡ�״ﱻ���ź�İ������ݣ��������꣩
    virtual void SetEnvelopePointsGeo(const std::vector<osg::Vec3d>& vPointsGeo)=0;
    virtual const std::vector<osg::Vec3d>& GetEnvelopePointsGeo()=0;
};


#endif
