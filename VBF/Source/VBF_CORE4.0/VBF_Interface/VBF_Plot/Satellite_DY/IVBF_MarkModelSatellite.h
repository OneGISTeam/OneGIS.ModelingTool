//*******************************************************************
// FileName��IVBF_MarkModelSatellite.h
// Function��ʵ��ģ�ͣ����ǣ���������ģ�͡���������µ�켣��
// Author:   ��Ө
// Date:     2013-12-24
//*******************************************************************

#ifndef __IVBF_MARK_MODEL_SATELLITE_H__
#define __IVBF_MARK_MODEL_SATELLITE_H__


#include <VBF_Plot/IVBF_MarkModel.h>
#include <string>
#include <VBF_Plot/Satellite/VBF_3DPlotDataTypes_Satellite.h>
#include <Types/VBF_3DStyles.h>


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

//----------------------------------------------------------------
// ����ṹ�壺VBF_ORBIT_ELEMENTS
// �ṹ�����������ǹ������
//----------------------------------------------------------------
typedef struct _tagVBFOrbitElements
{
    std::string		strNoradNo;

    // �������״����
    double			da;			// �볤�ᣨ�������״��������λ��km��
    double			de;			// ƫ���ʣ��������״������

    // �����λ�ò���
    double			dIncl;		// �����ǣ����������Ķ���ǣ���λ���Ƕȣ�
    double			dRAAN;		// ������ྭ�����ֵ㡢���ġ������������ڵ��Ĺ��ɵļнǣ���λ���Ƕȣ�
    double			dw;			// ���ص���ǣ�������ص㡢���ġ������������ڵ��Ĺ��ɵļнǣ���λ���Ƕȣ�

    // �����ڹ���ϵ�λ��
    double			dTA;		// �����ص�ʱ��

    _tagVBFOrbitElements()
    {
            strNoradNo	= "0000";
            da			= 6878.145;
            de			= 0.0;
            dIncl		= 40.0;
            dRAAN		= 0.0;
            dw			= 0.0;
            dTA			= 0.0;
    }

    _tagVBFOrbitElements& operator=(const _tagVBFOrbitElements& src)
    {
            if(this==&src) return *this;

            strNoradNo	= src.strNoradNo;
            da			= src.da;
            de			= src.de;
            dIncl		= src.dIncl;
            dRAAN		= src.dRAAN;
            dw			= src.dw;
            dTA			= src.dTA;

            return *this;
    }

} VBF_ORBIT_ELEMENTS;


//--------------------------------------------------------------------
// ����ӿڣ�IVBF_MarkModelSatellite
// �ӿ����������ǣ���������ģ�͡���������µ�켣��
//--------------------------------------------------------------------
class IVBF_MarkModelSatellite : public IVBF_MarkModel
{
public:
    virtual ~IVBF_MarkModelSatellite() {}

    /* ����/��ȡ�������
            ������orbit		 -- ���ǹ������
            ������dBeginTime -- ���ǿ�ʼ����ʱ��
            ������dEndTime	 -- ���ǽ�������ʱ��
            ������dTimeStep   -- ���Ƿ��沽��
    */
    virtual void SetOrbitParams(const VBF_ORBIT_ELEMENTS& orbit, double dBeginTime, double dEndTime, double dTimeStep)=0;
    virtual void GetOrbitParams(VBF_ORBIT_ELEMENTS& orbit, double& dBeginTime, double& dEndTime, double& dTimeStep)=0;

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

    // ����/��ȡ����ģ�͵İ�Χ���Ƿ�ɼ���������������ģ�͵�����ΪMeshʱ��Ĭ��ֵΪtrue��
    virtual void SetModelBoundingSphereVisible(bool bVisible)=0;
    virtual bool IsModelBoundingSphereVisible()=0;

    // ����/��ȡ����ģ�͵İ�Χ����ɫ��������������ģ�͵�����ΪMeshʱ��Ĭ��ֵΪ��ɫ��
    virtual void              SetModelBoundingSphereColor(const osg::Vec4f& color)=0;
    virtual const osg::Vec4f& GetModelBoundingSphereColor()=0;

    // ����/��ȡ����ģ�͵İ�Χ���ڲ�ͬLod�����µ�������Ϣ��������������ģ�͵�����ΪMeshʱ��
    // ������nLod -- ��Χ���Lod����ֻ��ȡֵ0,1,2��LodԽС��ʾ�����ӵ�ԽԶ����Χ��Խ����
    //      fDistMin, fDistMax -- ��Lod�����°�Χ�����С���ɼ�����
    //      nNumSplitRow, nNumSplitCol -- ��Lod�����°�Χ��ĺ��������ָ���
    virtual void SetModelBoundingSphereInfo(int nLod, float fDistMin, float fDistMax, int nNumSplitRow, int nNumSplitCol)=0;
    virtual bool GetModelBoundingSphereInfo(int nLod, float& fDistMin, float& fDistMax, int& nNumSplitRow, int& nNumSplitCol)=0;

    // ����/��ȡ����Ƿ�ɼ�����������ߺ͹�����ߣ�Ĭ��ֵΪtrue��
    virtual void SetOrbitVisible(bool bVisible)=0;
    virtual bool IsOrbitVisible()=0;

    // ����/��ȡ����ߵ���ʽ
    virtual void                 SetOrbitLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetOrbitLineStyle()=0;

    // ����/��ȡ��������Ƿ�ɼ���Ĭ��ֵΪfalse��
    virtual void SetVertLineVisible(bool bVisible)=0;
    virtual bool IsVertLineVisible()=0;

    // ����/��ȡ������ߵ���ʽ
    virtual void				 SetVertLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetVertLineStyle()=0;

    // ����/��ȡ������ߵļ����������ÿ�����������һ�����ߣ�Ĭ��ֵΪ5��
    virtual void SetNumVertLineInterval(int num)=0;
    virtual int  GetNumVertLineInterval()=0;

    // ����/��ȡ���µ�켣�Ƿ�ɼ���Ĭ��ֵΪfalse��
    virtual void SetGroundTrackVisible(bool bVisible)=0;
    virtual bool IsGroundTrackVisible()=0;

    // ����/��ȡ���µ�켣����ʽ
    virtual void                 SetGroundTrackLineStyle(const VBF_LINESTYLE& style)=0;
    virtual const VBF_LINESTYLE& GetGroundTrackLineStyle()=0;

    // ����/��ȡ�Ƿ���ʾ������Ϣ
    virtual void SetInfoVisible(bool bVisible)=0;
    virtual bool IsInfoVisible()=0;

    // ����/��ȡ������Ϣ���ı���ʽ
    virtual void                 SetInfoTextStyle(const VBF_TEXTSTYLE& style)=0;
    virtual const VBF_TEXTSTYLE& GetInfoTextStyle()=0;

    // ����/��ȡ������Ϣ�ı�������ʽ
    virtual void                      SetInfoFrameStyle(const VBF_POLYGON2DSTYLE& style)=0;
    virtual const VBF_POLYGON2DSTYLE& GetInfoFrameStyle()=0;

    // �������Ǹ���̽����
    virtual void SetDomeSensor(double dRadius, double dAngleV, osg::Vec4f domeClr, osg::Vec4f coneClr) = 0;

    virtual void SetFrustumDomeSensor(double dRadius, double dAngleH, double dAngleV, osg::Vec4f domeClr, osg::Vec4f coneClr) = 0;

    virtual void SetFrustumFlatSensor(double dRadius, double dAngleH, double dAngleV, osg::Vec4f domeClr, osg::Vec4f coneClr) = 0;

    virtual void SetRingSensor(double dRadius, double dAngleV1, double dAngleV2, osg::Vec4f domeClr, osg::Vec4f coneClr) = 0;

    // ��������̽��������
    virtual void SetSensorVisible(bool bVisible) = 0;
};


#endif
