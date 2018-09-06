#ifndef IVBF_EARTH_MANIPULATOR_H
#define IVBF_EARTH_MANIPULATOR_H 1

#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>

class CVBF_Viewpoint;

class IVBF_EarthManipulator : public IVBF_CameraManipulator
{
public:
	// ��ȡ��ǰ���λ��
	virtual CVBF_Viewpoint getViewpoint() const = 0;

	// �������λ�á�duration_s���任����λ�����õ�ʱ��
	virtual void setViewpoint( const CVBF_Viewpoint& vp, double duration_s =0.0 ) = 0;

	// ����Ĭ���ӵ�
	virtual void setHomeViewpoint( const CVBF_Viewpoint& vp, double duration_s = 0.0 ) = 0;

public:
	// ƽ���������������Ļ����
	virtual void pan( double dx, double dy ) = 0;

	// ��ת�����dx = azimuth, dy = pitch����������ת����λ����
	virtual void rotate( double dx, double dy ) = 0;

	// ���ţ������Զ/����������dy
	virtual void zoom( double dx, double dy ) = 0;

public:
	// �������������
	enum EEARTHManip
	{
		MANIP_EARTH = 0,
		MANIP_EARTH_EX,
		MANIP_EARTH_FE
	};
};

#endif /* IVBF_EARTH_MANIPULATOR_H */
