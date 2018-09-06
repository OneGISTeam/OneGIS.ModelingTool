//*******************************************************************
// FileName��IVBF_MarkModelSatellite.h
// Function��ʵ��ģ�ͣ����ǣ���������ģ�͡���������µ�켣��
// Author:   ��Ө
// Date:     2013-12-24
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SATELLITE_H__
#define __IVBF_MARK_MODEL_SATELLITE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <VBF_Plot/IVBF_MarkModelPoint.h>
#include <string>
#include <VBF_Plot/Satellite/VBF_3DPlotDataTypes_Satellite.h>
#include <Types/VBF_3DStyles.h>
#include <VBF_Plot/ElecMag/IVBF_MarkModelSensor.h>
#include <VBF_Plot/Shape/IVBF_MarkAttrSphereAttitude.h>

#include <VBF_Plot/Satellite/VBF_OrbitElements.h>

//----------------------------------------------------------------
// ����ö�٣�EVBF_ORBIT_TYPE
// �ӿ��������������
//----------------------------------------------------------------
enum EVBF_ORBIT_TYPE
{
    VBF_ORBIT_TWOBODY,
    VBF_ORBIT_J2,
    VBF_ORBIT_J4
};

// 
//----------------------------------------------------------------
// ����ö�٣�EVBF_SATEDRIVING_MODE
// �ӿ�����������������ʽ
//----------------------------------------------------------------
enum EVBF_SATEDRIVING_MODE	
{
    VBF_SATEDRIVING_ORBITELEMENTS,	// ��������Ĭ��ֵ��
    VBF_SATEDRIVING_ORBITDATA,      // �Ѿ�����õĹ������
    VBF_SATEDRIVING_POS     		// λ������
};

// ���������
struct VBF_ORBITDATA
{
    double	   dTime;   // ʱ�䣬JD
    osg::Vec3d vPos;	// �ع�ϵ�µ�λ��ʸ��
    osg::Vec3d vVel;	// �ع�ϵ�µ��ٶ�ʸ��
};
enum EVBF_ORBIT_DATA_FORMAT
{
    VBF_ORBIT_DATA_FORMAT_CSV, // TLE_ 1000_HPOP_20171213205227To20171221190921.csv :: 010002017121320522706,-7613857.708765,5100227.962408,4230.836080,-3113.494083,-4637.566773,3509.290572
    VBF_ORBIT_DATA_FORMAT_LLA // STK����γ�ߣ�LLA Position :: ͷ + 1 Jun 2004 12:00:00.00  19.600  110.950 -0.000000  -0.000000  -0.000000 0.000000
};

//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelSatellite
// �ӿ����������ǣ���������ģ�͡���������µ�켣��
//--------------------------------------------------------------------
class IVBF_MarkModelSatellite : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelSatellite() {}

    /* ����/��ȡ���������ע�⣺�ú����������ȵ��ã�
            ������orbit		 -- ���ǹ������
            ������dBeginTime -- ���ǿ�ʼ����ʱ�䣨�����գ���λ���죩
            ������dEndTime	 -- ���ǽ�������ʱ�䣨�����գ���λ���죩
            ������dTimeStep   -- ���Ƿ��沽������λ���룩
			������nNumSatellites -- �ù�����ϵ����Ǹ�����Ĭ��ֵΪ1��
    */
    virtual void SetOrbitParams(const VBF_ORBIT_ELEMENTS& orbit, double dBeginTime, double dEndTime, double dTimeStep, int nNumSatellites=1)=0;
    virtual void GetOrbitParams(VBF_ORBIT_ELEMENTS& orbit, double& dBeginTime, double& dEndTime, double& dTimeStep, int& nNumSatellites)=0;
    virtual void SetOrbitData(const std::string& strFileName,EVBF_ORBIT_DATA_FORMAT eFormat,double dPeriod=0.5)=0;// ���ù�����ݣ�dPeriodΪ��ʾ�����ʱ�䣬���Ϊ-1����ȫ����ʾ

	// ��ȡ�ù���ϵ����Ǹ���
	virtual int GetNumSatellites()=0;

    // ����/��ȡ����ģ�͵������ļ�������·����
    // ����ļ�����Ϊģ���ļ�����.3ds, .flt, .dae�ȣ���������ģ������ΪVBF_MARK_MESH
    // ����ļ�����Ϊͼ���ļ�����.tga, .png, .bmp�ȣ���������ģ������ΪVBF_MARK_RASTER
    virtual void               SetModelFileName(const std::string& strFileName)=0;
    virtual const std::string& GetModelFileName()=0;

    // ����/��ȡ����ģ���������ļ�MarkStyle.xml�еı��루�ú����������SetModelFileName()����ֻ��ȡ������ߣ�
    virtual void               SetModelCode(const std::string& strCode)=0;
    virtual const std::string& GetModelCode()=0;

    // ����/��ȡ����ģ���Ƿ��������ù̶���С
    virtual void EnableModelFixedSizeInPixels(bool bEnable)=0;
    virtual bool IsModelFixedSizeInPixelsEnabled()=0;

    // ����/��ȡ����ģ�͵Ĺ̶���С (��λ������)
    virtual void  SetModelFixedSizeInPixels(float fFixedSize)=0;
    virtual float GetModelFixedSizeInPixels()=0;

    // ����/��ȡ����ģ�͵����ű�
    virtual void SetModelScale(float fScaleX, float fScaleY, float fScaleZ)=0;
    virtual void GetModelScale(float& fScaleX, float& fScaleY, float& fScaleZ)=0;

    // ����/��ȡ����Ƿ�ɼ�����������ߺ͹�����ߣ�Ĭ��ֵΪtrue��
    virtual void SetOrbitVisible(bool bVisible)=0;
    virtual bool IsOrbitVisible()=0;

    // ����/��ȡ����ߵ���ʽ
    virtual void                 SetOrbitLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetOrbitLineStyle()=0;

	// ����/��ȡ����ϸ�����㼰����Ϣ�Ƿ�ɼ�������ص㡢Զ�ص�ȣ�Ĭ��ֵΪfalse��
	virtual void SetOrbitSpecialPointsVisible(bool bVisible)=0;
	virtual bool IsOrbitSpecialPointsVisible()=0;

	// ����/��ȡ��ǰ���������ǵ������ţ�Ĭ�ϱ��������ǵ�������Ϊ0�� 
	// ע�⣺ֻ�����Ǳ�����󣬲�����ʾ�䴹�ߺ����µ�켣
	virtual void SetActiveSatellite(int nSatelliteIndex)=0;
	virtual int  GetActiveSatellite()=0;

    // ����/��ȡ��ǰ���������ǵĴ����Ƿ�ɼ����ô���ָ�����µ�켣��Ĭ��ֵΪtrue��
    virtual void SetVertLineVisible(bool bVisible)=0;
    virtual bool IsVertLineVisible()=0;

    // ����/��ȡ��ǰ���������Ǵ��ߵ���ʽ
    virtual void				 SetVertLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetVertLineStyle()=0;

    // ����/��ȡ��ǰ���������ǵ����µ�켣�Ƿ�ɼ���Ĭ��ֵΪfalse��
    virtual void SetGroundTrackVisible(bool bVisible)=0;
    virtual bool IsGroundTrackVisible()=0;

    // ����/��ȡ��ǰ���������ǵ����µ�켣����ʽ
    virtual void                 SetGroundTrackLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetGroundTrackLineStyle()=0;

    // ����/��ȡ�Ƿ���ʾ������Ϣ��Ĭ��ֵΪfalse��
    virtual void SetInfoVisible(bool bVisible)=0;
    virtual bool IsInfoVisible()=0;

    // ����/��ȡ������Ϣ���ı���ʽ
    virtual void                 SetInfoTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetInfoTextStyle()=0;

    // ����/��ȡ������Ϣ�ı�������ʽ
    virtual void                      SetInfoFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetInfoFrameStyle()=0;

    // ����/��ȡ������̬���Ƿ�ɼ���ֻ��Meshģ������̬��Ĭ��ֵΪfalse��
    virtual void SetSphereAttitudeVisible(bool bVisible)=0;
	virtual bool IsSphereAttitudeVisible()=0;

    // ��ȡ������̬��ֻ��Meshģ������̬��
    virtual IVBF_MarkAttrSphereAttitude* GetSphereAttitude(int nSatelliteIndex)=0;

    // ��ȡ����ģ��
    virtual IVBF_MarkModelPoint* GetSatelliteModel()=0;

    // ��������̽��������
    virtual void SetSensorVisible(bool bVisible)=0;

    // ����n���������һ��������������nSatelliteIndex��ʾ���ǵ�������
    virtual void AddSensor(int nSatelliteIndex, IVBF_MarkModelSensor* pISensor)=0;

	// �Ƴ���n�����ǵ����д�����������nSatelliteIndex��ʾ���ǵ�������
    virtual void RemoveSensors(int nSatelliteIndex)=0;

    // ����/�ر�̽����������ཻ, ע�⣺�ನ����Ŀָ�״�Ŀǰû�д˹���
    virtual void EnableSensorCal(bool bEnable)=0;

	// ����/��ȡ����������ʽ��Ĭ��ֵΪVBF_SATEDRIVING_ORBITSIMUTIME��
	virtual void SetDrivingMode(EVBF_SATEDRIVING_MODE nMode)=0;
	virtual EVBF_SATEDRIVING_MODE GetDrivingMode()=0;

    // ����/��ȡĳ�����ǵ�λ�ã�ע�⣺ǰ��������Ϊλ��������ʽ��
    virtual void SetGeoPos(int nSatelliteIndex, const osg::Vec3d& vGeoPos)=0;
    virtual void StepGeoPos(int nSatelliteIndex, const osg::Vec3d& vGeoPos, float fRotateX, float fRotateY, float fRotateZ, const std::string& strInfo="")=0;
	virtual const osg::Vec3d& GetGeoPos(int nSatelliteIndex)=0;
};


#endif
