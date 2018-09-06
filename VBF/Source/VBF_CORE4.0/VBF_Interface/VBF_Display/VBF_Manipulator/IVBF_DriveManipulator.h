#ifndef IVBF_DRIVE_MANIPULATOR_H
#define IVBF_DRIVE_MANIPULATOR_H 1 

#include "IVBF_CameraManipulator.h"

class IVBF_DriveManipulator : public IVBF_CameraManipulator
{
public:
	// 获取该操作器鼠标和键盘的用法
	virtual void GetUsage(ApplicationUsage& usage) const = 0;

	virtual void setModelScale( double in_ms ) = 0;
	virtual double getModelScale() const = 0;

	// 设置/获取速度
	virtual void setVelocity( double in_vel ) = 0;
	virtual double getVelocity() const = 0;

	// 设置/获取高度
	virtual void setHeight( double in_h ) = 0;
	virtual double getHeight() const = 0;

	//以下函数为GGR添加
	virtual void GetHPRFromQuat(const osg::Quat& q, double &h, double &p, double &r)= 0;

	// 设置/获取方位和俯仰
	virtual osg::Quat getRotation() = 0;		//旋转参数
	virtual double GetHeading()= 0;				//旋转角度，单位为Degree
	virtual double GetPitch()= 0;				//俯仰角度，单位为Degree
	virtual void   SetPitch(double in_p)= 0;

};

//由 3DDisplay 控制？
//VBF_3DDISPLAYSHARED_EXPORT IVBF_DriveManipulator* CreateDriveManipulator();


#endif // IVBF_DRIVE_MANIPULATOR_H

