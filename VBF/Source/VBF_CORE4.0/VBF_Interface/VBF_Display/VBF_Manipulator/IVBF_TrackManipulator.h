#ifndef IVBF_TRACK_MANIPULATOR_H
#define IVBF_TRACK_MANIPULATOR_H 1

#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>

class IVBF_TrackManipulator : public IVBF_CameraManipulator
{
public:

	// 根据眼睛的位置和方向设置操作器
	virtual void setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation ) = 0;

	// 根据眼睛的位置、旋转中心（观察点）、向上向量设置操作器
	virtual void setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up ) = 0;

	// 获取操作器中眼睛的位置和方向
	virtual void getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const = 0;

	// 获取操作器中眼睛的位置、旋转中心（观察点）、向上向量
	virtual void getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const = 0;

	// 设置跟踪的节点
	//virtual void setTrackNode(osg::IVBF_SGNode* node) = 0;
	virtual osg::IVBF_SGNode* getTrackNode() = 0;
	virtual const osg::IVBF_SGNode* getTrackNode() const = 0;


	// 跟踪操作器类型
	enum ETrackManip
	{
		MANIP_TRACK_FIXA = 0,
		MANIP_TRACK_FIXR,
	};

};


// 节点跟踪操作器,从一架飞机看另一架飞机的效果或从地面看飞机的效果
class IVBF_TrackManipulatorFixA : public IVBF_TrackManipulator
{
public:
	enum TrackerMode
	{                  
		CAMERA_POS_FIX,    // 固定相机位置，如站在地面观察一架飞机
		CAMERA_POS_DYNAMIC // 动态相机位置，如在一架飞机上观察另一架飞机
	};

	// 设置跟踪的节点
	virtual void setTrackNode(osg::IVBF_SGNode* node) = 0;

	// 固定相机位置，如站在地面观察一架飞机
	virtual void SetCameraPosition(const osg::Vec3d& vEye) = 0;

	// 动态相机位置，如在一架飞机上观察另一架飞机
	virtual void SetCameraPosition(osg::IVBF_SGNode* pINode) = 0;
};


// 节点跟踪操作器（相对固定），例如把相机绑定在相对于飞机固定的位置，跟踪飞机。位置固定，姿态可以与飞机绑定，也可以不绑定
class IVBF_View;
class IVBF_TrackManipulatorFixR : public IVBF_TrackManipulator
{
public:
	enum TrackerMode
	{                  
		NODE_CENTER,             // 模型中心
		NODE_CENTER_BOUNDINGBOX, // 跟踪包围球的中心，但不与模型一起旋转
		NODE_CENTER_AND_ROTATION // 跟踪包围球的中心，并与模型一起旋转
	};

	// 设置跟踪的节点
	virtual void setTrackNode(osg::IVBF_SGNode* node,IVBF_View* pIView) = 0;

	// 设置跟踪模式
	virtual void setTrackerMode(TrackerMode mode) = 0;
	virtual TrackerMode getTrackerMode() const = 0;
	
	// 设置鼠标滚轮缩放参数
	virtual void  setWheelZoomFactor(double dZoomFactor) = 0;
	virtual double getWheelZoomFactor() const = 0;

	// 设置最小距离
	virtual void setMinimumDistance(const double& dMinDistance, bool bRelativeToModelSize = NULL) = 0;
	virtual void SetDistance(double dis) = 0;
	virtual double GetDistance()  = 0;

	// 设置水平角度
	virtual void SetAngleH(double dAngleH) = 0;
	virtual double GetAngleH()  = 0;

	// 设置垂直角度
	virtual void SetAngleV(double dAngleV) = 0;
	virtual double GetAngleV() = 0;

	virtual void zoomModel( float dy, bool pushForwardIfNeeded = true ) = 0;
};

#endif /* IVBF_TRACK_MANIPULATOR_H */
