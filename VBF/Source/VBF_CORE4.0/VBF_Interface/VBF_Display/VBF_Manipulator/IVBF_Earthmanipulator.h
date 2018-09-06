#ifndef IVBF_EARTH_MANIPULATOR_H
#define IVBF_EARTH_MANIPULATOR_H 1

#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>

class CVBF_Viewpoint;

class IVBF_EarthManipulator : public IVBF_CameraManipulator
{
public:
	// 获取当前相机位置
	virtual CVBF_Viewpoint getViewpoint() const = 0;

	// 设置相机位置。duration_s：变换到新位置所用的时间
	virtual void setViewpoint( const CVBF_Viewpoint& vp, double duration_s =0.0 ) = 0;

	// 设置默认视点
	virtual void setHomeViewpoint( const CVBF_Viewpoint& vp, double duration_s = 0.0 ) = 0;

public:
	// 平移相机，增量，屏幕坐标
	virtual void pan( double dx, double dy ) = 0;

	// 旋转相机（dx = azimuth, dy = pitch），增量旋转，单位弧度
	virtual void rotate( double dx, double dy ) = 0;

	// 缩放：相机拉远/拉近，仅用dy
	virtual void zoom( double dx, double dy ) = 0;

public:
	// 地球操作器类型
	enum EEARTHManip
	{
		MANIP_EARTH = 0,
		MANIP_EARTH_EX,
		MANIP_EARTH_FE
	};
};

#endif /* IVBF_EARTH_MANIPULATOR_H */
