//***************************************************************************************
// FileName��IVBF_3DDisplay.h
// Function����ά��ʾ���ƽӿڣ���Ҫ���ڻ�ȡ����ʾ�����йص���Ϣ�ͶԳ������п���
// Author:   ��Ө
// Date:     2006-4-22
//***************************************************************************************
#ifndef __IVBF_3DDISPLAY_H__11
#define __IVBF_3DDISPLAY_H__11


#include <Types/Vec3d>
#include <VBF_3DMap/VBF_Terrain/VBF_Viewpoint.h>
#include <VBF_Display/VBF_Manipulator/IVBF_DriveManipulator.h>
#include <VBF_Display/VBF_Manipulator/IVBF_TrackManipulator.h>


// ����������ID��
const char VBF_COMPONENT_3DMANIPULATOR[]			= "Component: 3DManipulator";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DMANIPULATOR[]			= "��ά�������������";

// ����3Dģ������Ϣ��ID��
extern const char VBF_MESSAGE_3DVIEWPORT_INITED[];//		= "Message: 3DViewport Inited";
extern const char VBF_MESSAGE_3DVIEWPORT_RESIZED[];//		= "Message: 3DViewport Resized";




class IVBF_View;

class IVBF_3DManipulator
{
public: 	
	virtual ~IVBF_3DManipulator() {}

public:
	// �л���ʻ������
	virtual IVBF_DriveManipulator* SetAndGetDriveManipulator(int nTypeDriveManip) = 0;
	
	// �л����ٲ�����
	virtual IVBF_TrackManipulator* SetAndGetTrackManipulator(IVBF_TrackManipulator::ETrackManip nTypeTrackManip) = 0;



    // ����/��ȡ��ǰ�ӵ�
    virtual void SetViewpoint( const CVBF_Viewpoint& vp, double duration_s=0.0, bool bAutoRotate=false ,IVBF_ManipulatorCB* pCB = NULL) = 0;
    virtual CVBF_Viewpoint GetViewpoint()=0;

    // ��λ��ָ�����귶Χ��
    // ������dL0, dB0, dL1, dB1 -- �����������С��γ�ȣ���λ���ȣ�
    //     dHeading -- ��λ��ĺ���ǣ���λ���Ƕȣ�
    //     dPitch   -- ��λ��ĸ����ǣ���λ���Ƕȣ�
    //     dDuration -- ��λ����Ҫ��ʱ�䣨��λ���룩
    //     bAutoRotate -- ��λ���Ƿ��Զ���ת
    virtual void Locate(double dL0, double dB0, double dL1, double dB1, double dHeading=0.0,
                        double dPitch=-90.0, double dDuration=0.0, bool bAutoRotate=false, IVBF_ManipulatorCB* pCB=NULL)=0;

    virtual void  StartAutoAnimPath( const char* szName )=0;
    virtual void  EndAutoAnimPath()=0;
//!!
    /*
	// ��ȡ��ǰ�ӵ����������
	virtual const osg::Vec3d& GetEyePtInWorld()=0;

	virtual double GetEyeHeight()=0;


	virtual double  GetAngleH()=0;				// ��ȡˮƽ�ӽ� (����λ�ǣ���λ���Ƕ�)
	virtual double  GetAngleV()=0;				// ��ȡ��ֱ�ӽ� (��λ���Ƕȣ�ˮƽΪ0������Ϊ-90������Ϊ90)

    // ��ȡ��ʾ�ֱ���(��/����)��������
    virtual double GetResolution(IVBF_View* pIView=NULL)=0;
    virtual double GetScale(IVBF_View* pIView=NULL,unsigned int DPI = 96)=0;
    virtual void   SetScale(double dL,double dB,double dScale,IVBF_View* pIView=NULL,unsigned int DPI=96)=0;

    // ��ȡ��ʾ�ֱ��ʵ�����(��/����)���÷�Ϊ��float fPixelSize = ptWorld * GetPixelSizeVector()
    virtual const osg::Vec4& GetPixelSizeVector()=0;
*/
    // ���浱ǰ�ӵ㵽xml�ļ��У�����ֵΪfalse��ʾ����ʧ��
    // ������strXmlFileName -- xml�ļ���������·����
    //      strViewpointName -- �ӵ�����ƣ�����Ϊ���ַ���
    //      bAppend        -- ����ļ��Ѵ��ڣ��Ƿ����׷��ģʽ
    virtual bool SaveViewpoint(const std::string& strXmlFileName, const std::string& strViewpointName, bool bAppend=true)=0;

    // ���ӵ�xml�ļ��л�ȡĳ���ӵ㣬����ֵΪfalse��ʾ��ȡʧ��
    // ������strXmlFileName -- xml�ļ���������·����
    //      strViewpointName -- �ӵ�����ƣ�����Ϊ���ַ���
    virtual bool GetViewpointFromFile(const std::string& strXmlFileName, const std::string& strViewpointName, CVBF_Viewpoint& viewpoint)=0;
};


#endif





















