#include <VBF_Engine/VBF_SceneGraph/VBF_GL.h>
#include <Types/VBF_Matrix.h>
#include <VBF_Common/VBF_Utils/VBF_IOUtils.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOpComputeBounds.h>
//#include <VBF_Display/VBF_Manipulator/VBF_CameraManipulatorImpl.h>
#include <string.h>

using namespace osg;
using namespace osgGA;

template<class T>
IVBF_CameraManipulatorImpl<T>::IVBF_CameraManipulatorImpl()
{
    m_nIntersectTraversalMask = 0xffffffff;

    m_bAutoComputeHomePosition = true;

    m_vHomeEye.set(0.0,-1.0,0.0);
    m_vHomeCenter.set(0.0,0.0,0.0);
    m_vHomeUp.set(0.0,0.0,1.0);

    m_bFixedNearFar = false;
    m_dFixedNear = 100.0;
    m_dFixedFar  = 100000000.0;
}


template<class T>
IVBF_CameraManipulatorImpl<T>::IVBF_CameraManipulatorImpl(const IVBF_CameraManipulatorImpl& mm, const CopyOp& copyOp)
   : GUIEventHandler(mm, copyOp),
     m_nIntersectTraversalMask(mm.m_nIntersectTraversalMask),
     m_bAutoComputeHomePosition(mm.m_bAutoComputeHomePosition),
     m_vHomeEye(mm.m_vHomeEye),
     m_vHomeCenter(mm.m_vHomeCenter),
     m_vHomeUp(mm.m_vHomeUp),
     m_bFixedNearFar(mm.m_bFixedNearFar),
     m_dFixedNear(mm.m_dFixedNear),
     m_dFixedFar(mm.m_dFixedFar),
     _coordinateFrameCallback(dynamic_cast<IVBF_CoordinateFrameCallback*>(copyOp(mm._coordinateFrameCallback.get())))
{
}


template<class T>
IVBF_CameraManipulatorImpl<T>::~IVBF_CameraManipulatorImpl()
{
}

// ��ȡ����ϵ
template<class T>
osg::CoordinateFrame IVBF_CameraManipulatorImpl<T>::getCoordinateFrame(const osg::Vec3d& position) const
{
    if (_coordinateFrameCallback.valid()) return  _coordinateFrameCallback->getCoordinateFrame(position);
    return osg::CoordinateFrame();
}

template<class T>
void IVBF_CameraManipulatorImpl<T>::setHomePosition(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up, bool autoComputeHomePosition)
{
    setAutoComputeHomePosition(autoComputeHomePosition);
    m_vHomeEye = eye;
    m_vHomeCenter = center;
    m_vHomeUp = up;
}

template<class T>
void IVBF_CameraManipulatorImpl<T>::getHomePosition(osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up) const
{
    eye = m_vHomeEye;
    center = m_vHomeCenter;
    up = m_vHomeUp;
}



// ��ȡ������������
template<class T>
std::string IVBF_CameraManipulatorImpl<T>::getManipulatorName() const
{
    const char* className = this->className();
    const char* manipString = strstr(className, "Manipulator");
   
	if (!manipString) return std::string(className);
    else              return std::string(className, manipString-className);
}


template<class T>
bool IVBF_CameraManipulatorImpl<T>::handle(const GUIEventAdapter&,::IVBF_GUIActionAdapter&)
{
    return false;
}



// ����Homeλ�ã��÷�����������ӳ���ģ�͵Ĵ�С��ʹ������ģ�Ϳ�������Ļ����ʾ
template<class T>
void IVBF_CameraManipulatorImpl<T>::computeHomePosition(const osg::IVBF_Camera* camera, bool useBoundingBox)
{
    if (getNode()==NULL) return ;

	OSG_INFO<<" CameraManipulator::computeHomePosition("<<camera<<", "<<useBoundingBox<<")"<<std::endl;
	
	osg::BoundingSphere boundingSphere;

	if (useBoundingBox)
	{
		// �����Χ�У��ð�Χ�м���ģ�����ıȰ�Χ�����ȷ��
		osg::ComputeBoundsVisitor cbVisitor;
		getNode()->accept(cbVisitor);

		osg::BoundingBox &bb = cbVisitor.getBoundingBox();

		if (bb.valid()) boundingSphere.expandBy(bb);
		else boundingSphere = getNode()->getBound();
	}
	else
	{
		boundingSphere = getNode()->getBound(); // �����Χ��
	}

	OSG_INFO<<"    boundingSphere.center() = ("<<boundingSphere.center()<<")"<<std::endl;
	OSG_INFO<<"    boundingSphere.radius() = "<<boundingSphere.radius()<<std::endl;

	double dist = 3.5f * boundingSphere.radius();  // ����Ĭ�Ͼ���

	if (camera)
	{
		double left,right,bottom,top,zNear,zFar;
		if (camera->getProjectionMatrixAsFrustum(left,right,bottom,top,zNear,zFar)) // ����͸�Ӿ���������
		{
			double vertical2 = fabs(right - left) / zNear / 2.;
			double horizontal2 = fabs(top - bottom) / zNear / 2.;
			double dim = horizontal2 < vertical2 ? horizontal2 : vertical2;
			double viewAngle = atan2(dim,1.);
			dist = boundingSphere.radius() / sin(viewAngle);
		}
		else  // �����������������
		{
			if (camera->getProjectionMatrixAsOrtho(left,right,bottom,top,zNear,zFar))
			{
				dist = fabs(zFar - zNear) / 2.;
			}
		}
	}

	setHomePosition(boundingSphere.center() + osg::Vec3d(0.0,-dist,0.0f), boundingSphere.center(),
						        osg::Vec3d(0.0f,0.0f,1.0f), m_bAutoComputeHomePosition);
}
