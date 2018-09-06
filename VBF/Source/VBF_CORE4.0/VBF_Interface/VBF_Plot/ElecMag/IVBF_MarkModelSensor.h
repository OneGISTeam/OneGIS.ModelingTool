//*******************************************************************
// FileName��IVBF_MarkModelSensor.h
// Function������ʵ��ģ�ͣ�������
// Author:
// Date:    
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SENSOR_H__
#define __IVBF_MARK_MODEL_SENSOR_H__


#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <VBF_Plot/ElecMag/VBF_3DPlotDataTypes_ElecMag.h>
#include <VBF_Plot/Common/IVBF_MarkModelGraphics.h>
#include <VBF_Aux/VBF_GLAux/IVBF_GraphicsAppearance.h>


#define VBF_POINT_FLAG_IN			0
#define VBF_POINT_FLAG_OUT			1
#define VBF_POINT_FLAG_INTERSECT	2
#define VBF_POINT_FLAG_DEL			4

class CVBF_IntersectTriangle  
{
public:
	std::vector<osg::Vec3d>  m_aPoints;
	std::vector<BYTE>        m_aPointFlags;
};

class IVBF_MarkModelSensor : public IVBF_MarkModelGraphics
{
public:
	virtual ~IVBF_MarkModelSensor() {}

	// ����/��ȡ�������İ뾶
	virtual void  SetRadius(float fRadius)=0;
	virtual float GetRadius()=0;
	
	// ����/�ر�̽�⹦�ܣ�����������̽�����е�Ŀ�꣬����̽��ָ����һ��Ŀ��
	virtual void EnableDetect(bool bEnable)=0;
	virtual bool IsDetectEnabled()=0;

	// ���/�Ƴ���Ҫ̽���Ŀ��
	virtual bool AddDetectObj(IVBF_MarkModelPoint* pMark)=0;
	virtual void RemoveDetectObj(IVBF_MarkModelPoint* pMark)=0;
	virtual void RemoveAllDetectObjs()=0;

	// �Ƿ���̽�⵽��pt������ϵ��IVBF_MarkModelPoint->GetWorldPos()����ֵһ��
	virtual bool Detect(const osg::Vec3d& ptWorld)=0; 
	virtual bool IntersectCal(IVBF_MarkModelSensor* pIMarkModelB)=0;


	//=========================== ���º������ڲ�ʹ�� ======================================
	virtual void SetTraceObj(IVBF_MarkModelPoint* pMark)=0;
	virtual IVBF_MarkModelPoint* GetTraceObj()=0;

	// ���������������ܴ�����
	virtual bool TraceObj(const osg::Vec3d& ptWorld, osg::Matrixd& matRotate, double& dDist)=0; 
	virtual bool TraceObj(const osg::Vec3d& ptWorld, double& dAngleX, double& dAngleY, double& dAngleZ, double& dDist)=0;

	virtual void CalIntersectTriangles(IVBF_MarkModelSensor* pIMarkModelB, std::vector<CVBF_IntersectTriangle>& aIntersectTriangles)=0;

    virtual int GetTraceSensorsNum()=0;
    virtual IVBF_MarkModelSensor* GetTraceSensor(int idx)=0;

    // ����/��ȡģ�͵����
    virtual void SetTraceSensorAppearance(IVBF_GraphicsAppearance* pAppearance)=0;

};

#endif
