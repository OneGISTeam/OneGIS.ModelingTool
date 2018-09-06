//***************************************************************************************
// FileName��IVBF_3DDisplay.h
// Function����ά��ʾ���ƽӿڣ���Ҫ���ڻ�ȡ����ʾ�����йص���Ϣ�ͶԳ������п���
// Author:   ��Ө
// Date:     2006-4-22
//***************************************************************************************
#ifndef __IVBF_3DDISPLAY_H__
#define __IVBF_3DDISPLAY_H__


#include <Types/Vec3d>
#include <VBF_3DMap/VBF_Terrain/VBF_Viewpoint.h>
#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>

// ����������ID��
const char VBF_COMPONENT_3DDISPLAY[]			= "Component: 3DDisplay";

// ����3Dģ����ר�нӿڵ�ID��
const char VBF_INTERFACE_3DDISPLAY[]			= "��ά��ʾ���ƹ���";

// ����3Dģ������Ϣ��ID��
const char VBF_MESSAGE_3DVIEWPORT_INITED[]		= "Message: 3DViewport Inited";
const char VBF_MESSAGE_3DVIEWPORT_RESIZED[]		= "Message: 3DViewport Resized";



//-----------------------------------------------------------------------------
// ö�ٵĸ��ֲ�������ʽ
//-----------------------------------------------------------------------------
enum VBF_MANIPULATOR_TYPE
{
	// ���β�����
	VBF_MANIP_EARTH_VBF = 0,
	VBF_MANIP_EARTH_FE,

	// ȫ�ֲ�����
	VBF_MANIP_TRACKBALL,
	VBF_MANIP_ANIMATION, 
    VBF_MANIP_SPHERICAL,

	// ��ʻ������
	VBF_MANIP_DRIVE,
	VBF_MANIP_FIRST_PERSON,
	VBF_MAINP_FLY,

	// ����
	VBF_MANIP_TRACK_FIXA,
	VBF_MANIP_TRACK_FIXR,
	VBF_MAINP_TRACK_NODE,

	// ���������������������٣�Ҳ������ʻ
	VBF_MANIP_FE_LOCK,

	// �������β�����
	VBF_MANIP_INDOOR_ROAMING
};


class IVBF_View;
class IVBF_AutoAnimCompleteCB : public CVBF_Referenced
{
public:
    virtual void completed() = 0;
};

class IVBF_CameraManipulatorChangeCB : public CVBF_Referenced
{
public:

	virtual void CameraManiChanged(IVBF_CameraManipulator* manipulator) = 0;
};


class IVBF_3DDisplay
{
public: 	
	virtual ~IVBF_3DDisplay() {}

public:

	// ѡ�������
 	virtual IVBF_CameraManipulator* SetAndGetManipulator(VBF_MANIPULATOR_TYPE manipulatorType)= 0;
 	virtual VBF_MANIPULATOR_TYPE GetManipulatorType()=0;
    virtual void SetCameraManiChangeCallback(IVBF_CameraManipulatorChangeCB*) = 0;
	// ��ȡ������
	virtual IVBF_CameraManipulator* GetManipulator(VBF_MANIPULATOR_TYPE manipulatorType)= 0;

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





















