#ifndef IVBF_CAMERA_MANIPULATOR_H
#define IVBF_CAMERA_MANIPULATOR_H 1 

#include <Types/VBF_Matrixd.h>

#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupCoordSys.h>
#include <VBF_Engine/VBF_SGUtil/SceneView>

#include <VBF_Display/VBF_Manipulator/Export>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventAdapter.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>


// ����ϵ�ص������ھ����������ȡ�ϡ�����������
class IVBF_CoordinateFrameCallback : public ::CVBF_Referenced
{
public:
	virtual osg::CoordinateFrame getCoordinateFrame(const osg::Vec3d& position) const = 0;
protected:
	virtual ~IVBF_CoordinateFrameCallback() {}
};

// �������ص������ڲ����������ⲿ���ܻ����⴫����Ϣ���綨λ���
class IVBF_ManipulatorCB:public CVBF_Referenced
{
public:
    IVBF_ManipulatorCB()
    {
    }
    virtual void operator()(const osg::Matrixd& matrix,double dAngleH,double dAngleV)=0;
protected:
    virtual ~IVBF_ManipulatorCB() {}
};

class IVBF_CameraManipulator  : virtual public osgGA::GUIEventHandler
{
public:
	virtual ~IVBF_CameraManipulator() {}

	// 1������ϵ��ؽӿ�

    // ����/��ȡ"����ϵ�ص�"���ûص����߲������ϡ�����������
    virtual void setCoordinateFrameCallback(IVBF_CoordinateFrameCallback* cb)=0;
    virtual IVBF_CoordinateFrameCallback* getCoordinateFrameCallback()=0;
    virtual const IVBF_CoordinateFrameCallback* getCoordinateFrameCallback() const=0;

    virtual void SetCallback(IVBF_ManipulatorCB* cb)=0;

    // ��ȡ����ϵ
    virtual osg::CoordinateFrame getCoordinateFrame(const osg::Vec3d& position) const =0;
  
	
	// ��ȡ���ϡ���ǰ����෽�������
    virtual osg::Vec3d getSideVector(const osg::CoordinateFrame& cf) const =0;
    virtual osg::Vec3d getFrontVector(const osg::CoordinateFrame& cf) const =0;
    virtual osg::Vec3d getUpVector(const osg::CoordinateFrame& cf) const =0;


	// 2��������ؽӿ�
	virtual void setByMatrix(const osg::Matrixd& matrix) = 0;		// ͨ���������ò�����
	virtual void setByInverseMatrix(const osg::Matrixd& matrix) = 0;// ͨ������������ò�����
	virtual osg::Matrixd getMatrix() const = 0;			// ��ȡ�������ľ���
    virtual osg::Matrixd getInverseMatrix() const = 0;	// ��ȡ�������������,���͵�ʹ�÷�ʽ����Ϊmodel view matrix


	// 3���ռ��ںϾ��룬����˫Ŀ����
	virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const= 0;
	virtual float getFusionDistanceValue() const= 0;


	// 4������/��ȡ�󽻱���������      
	virtual void setIntersectTraversalMask(unsigned int mask)= 0;
	virtual unsigned int getIntersectTraversalMask() const= 0;


	// 5����ڵ���صĺ�������Щ��������Ҫ������٣�����Щ����Ҫ��
	virtual void setNode(osg::IVBF_SGNode*)= 0;
	virtual const osg::IVBF_SGNode* getNode() const= 0;
	virtual osg::IVBF_SGNode* getNode()= 0;



	// 6����Ĭ��λ����صĺ���

	// �˹����ò�������Ĭ��λ��
	virtual void setHomePosition(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up, bool autoComputeHomePosition=false)= 0;	
	virtual void getHomePosition(osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up) const= 0;

	virtual void setAutoComputeHomePosition(bool flag)= 0; // �����Ƿ��Զ������������Ĭ��λ��
	virtual bool getAutoComputeHomePosition() const= 0;	   // ��ȡ�Ƿ��Զ������������Ĭ��λ��

	virtual void computeHomePosition(const osg::IVBF_Camera* camera = NULL, bool useBoundingBox = false)=0;// ����Ĭ��λ��
	
	virtual void home(const osgGA::GUIEventAdapter&, ::IVBF_GUIActionAdapter&)=0; // ������Ƶ�Ĭ��λ��
	virtual void home(double /*currentTime*/)=0;					     // ������Ƶ�Ĭ��λ��

	virtual void init(const osgGA::GUIEventAdapter& ,::IVBF_GUIActionAdapter&)=0;    // ���ã���ʼ����
	virtual bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us)=0;// �����¼�

    // �Ƿ�̶�Զ���ü��棬����ٲ���������һ�˳����β���������ʻ��������
    virtual bool IsFixedNearFar()=0;
    virtual void SetFixedNearFar(bool bFixed)=0;
    virtual double GetFixedNear()=0;
    virtual void   SetFixedNear(double dNear)=0;
    virtual double GetFixedFar()=0;
    virtual void   SetFixedFar (double dFar )=0;

};

#endif

