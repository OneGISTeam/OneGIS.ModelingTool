#ifndef IVBF_DRIVE_MANIPULATOR_H
#define IVBF_DRIVE_MANIPULATOR_H 1 

#include "IVBF_CameraManipulator.h"

class IVBF_DriveManipulator : public IVBF_CameraManipulator
{
public:
	// ��ȡ�ò��������ͼ��̵��÷�
	virtual void GetUsage(ApplicationUsage& usage) const = 0;

	virtual void setModelScale( double in_ms ) = 0;
	virtual double getModelScale() const = 0;

	// ����/��ȡ�ٶ�
	virtual void setVelocity( double in_vel ) = 0;
	virtual double getVelocity() const = 0;

	// ����/��ȡ�߶�
	virtual void setHeight( double in_h ) = 0;
	virtual double getHeight() const = 0;

	//���º���ΪGGR���
	virtual void GetHPRFromQuat(const osg::Quat& q, double &h, double &p, double &r)= 0;

	// ����/��ȡ��λ�͸���
	virtual osg::Quat getRotation() = 0;		//��ת����
	virtual double GetHeading()= 0;				//��ת�Ƕȣ���λΪDegree
	virtual double GetPitch()= 0;				//�����Ƕȣ���λΪDegree
	virtual void   SetPitch(double in_p)= 0;

};

//�� 3DDisplay ���ƣ�
//VBF_3DDISPLAYSHARED_EXPORT IVBF_DriveManipulator* CreateDriveManipulator();


#endif // IVBF_DRIVE_MANIPULATOR_H

