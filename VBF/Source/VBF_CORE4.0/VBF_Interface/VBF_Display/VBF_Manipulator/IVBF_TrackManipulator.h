#ifndef IVBF_TRACK_MANIPULATOR_H
#define IVBF_TRACK_MANIPULATOR_H 1

#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>

class IVBF_TrackManipulator : public IVBF_CameraManipulator
{
public:

	// �����۾���λ�úͷ������ò�����
	virtual void setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation ) = 0;

	// �����۾���λ�á���ת���ģ��۲�㣩�������������ò�����
	virtual void setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up ) = 0;

	// ��ȡ���������۾���λ�úͷ���
	virtual void getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const = 0;

	// ��ȡ���������۾���λ�á���ת���ģ��۲�㣩����������
	virtual void getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const = 0;

	// ���ø��ٵĽڵ�
	//virtual void setTrackNode(osg::IVBF_SGNode* node) = 0;
	virtual osg::IVBF_SGNode* getTrackNode() = 0;
	virtual const osg::IVBF_SGNode* getTrackNode() const = 0;


	// ���ٲ���������
	enum ETrackManip
	{
		MANIP_TRACK_FIXA = 0,
		MANIP_TRACK_FIXR,
	};

};


// �ڵ���ٲ�����,��һ�ܷɻ�����һ�ܷɻ���Ч����ӵ��濴�ɻ���Ч��
class IVBF_TrackManipulatorFixA : public IVBF_TrackManipulator
{
public:
	enum TrackerMode
	{                  
		CAMERA_POS_FIX,    // �̶����λ�ã���վ�ڵ���۲�һ�ܷɻ�
		CAMERA_POS_DYNAMIC // ��̬���λ�ã�����һ�ܷɻ��Ϲ۲���һ�ܷɻ�
	};

	// ���ø��ٵĽڵ�
	virtual void setTrackNode(osg::IVBF_SGNode* node) = 0;

	// �̶����λ�ã���վ�ڵ���۲�һ�ܷɻ�
	virtual void SetCameraPosition(const osg::Vec3d& vEye) = 0;

	// ��̬���λ�ã�����һ�ܷɻ��Ϲ۲���һ�ܷɻ�
	virtual void SetCameraPosition(osg::IVBF_SGNode* pINode) = 0;
};


// �ڵ���ٲ���������Թ̶���������������������ڷɻ��̶���λ�ã����ٷɻ���λ�ù̶�����̬������ɻ��󶨣�Ҳ���Բ���
class IVBF_View;
class IVBF_TrackManipulatorFixR : public IVBF_TrackManipulator
{
public:
	enum TrackerMode
	{                  
		NODE_CENTER,             // ģ������
		NODE_CENTER_BOUNDINGBOX, // ���ٰ�Χ������ģ�������ģ��һ����ת
		NODE_CENTER_AND_ROTATION // ���ٰ�Χ������ģ�����ģ��һ����ת
	};

	// ���ø��ٵĽڵ�
	virtual void setTrackNode(osg::IVBF_SGNode* node,IVBF_View* pIView) = 0;

	// ���ø���ģʽ
	virtual void setTrackerMode(TrackerMode mode) = 0;
	virtual TrackerMode getTrackerMode() const = 0;
	
	// �������������Ų���
	virtual void  setWheelZoomFactor(double dZoomFactor) = 0;
	virtual double getWheelZoomFactor() const = 0;

	// ������С����
	virtual void setMinimumDistance(const double& dMinDistance, bool bRelativeToModelSize = NULL) = 0;
	virtual void SetDistance(double dis) = 0;
	virtual double GetDistance()  = 0;

	// ����ˮƽ�Ƕ�
	virtual void SetAngleH(double dAngleH) = 0;
	virtual double GetAngleH()  = 0;

	// ���ô�ֱ�Ƕ�
	virtual void SetAngleV(double dAngleV) = 0;
	virtual double GetAngleV() = 0;

	virtual void zoomModel( float dy, bool pushForwardIfNeeded = true ) = 0;
};

#endif /* IVBF_TRACK_MANIPULATOR_H */
