#ifndef IVBF_CAMERA_MANIPULATOR_H
#define IVBF_CAMERA_MANIPULATOR_H 1 

#include <Types/VBF_Matrixd.h>

#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupCoordSys.h>
#include <VBF_Engine/VBF_SGUtil/SceneView>

#include <VBF_Display/VBF_Manipulator/Export>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventHandler.h>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventAdapter.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>


// 坐标系回调，用于矩阵操作器获取上、东、北方向
class IVBF_CoordinateFrameCallback : public ::CVBF_Referenced
{
public:
	virtual osg::CoordinateFrame getCoordinateFrame(const osg::Vec3d& position) const = 0;
protected:
	virtual ~IVBF_CoordinateFrameCallback() {}
};

// 操作器回调，用于操作器调用外部功能或向外传递信息，如定位完成
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

	// 1、坐标系相关接口

    // 设置/获取"坐标系回调"，该回调告诉操作器上、东、北方向
    virtual void setCoordinateFrameCallback(IVBF_CoordinateFrameCallback* cb)=0;
    virtual IVBF_CoordinateFrameCallback* getCoordinateFrameCallback()=0;
    virtual const IVBF_CoordinateFrameCallback* getCoordinateFrameCallback() const=0;

    virtual void SetCallback(IVBF_ManipulatorCB* cb)=0;

    // 获取坐标系
    virtual osg::CoordinateFrame getCoordinateFrame(const osg::Vec3d& position) const =0;
  
	
	// 获取向上、向前、向侧方向的向量
    virtual osg::Vec3d getSideVector(const osg::CoordinateFrame& cf) const =0;
    virtual osg::Vec3d getFrontVector(const osg::CoordinateFrame& cf) const =0;
    virtual osg::Vec3d getUpVector(const osg::CoordinateFrame& cf) const =0;


	// 2、矩阵相关接口
	virtual void setByMatrix(const osg::Matrixd& matrix) = 0;		// 通过矩阵设置操作器
	virtual void setByInverseMatrix(const osg::Matrixd& matrix) = 0;// 通过矩阵的逆设置操作器
	virtual osg::Matrixd getMatrix() const = 0;			// 获取操作器的矩阵
    virtual osg::Matrixd getInverseMatrix() const = 0;	// 获取操作器矩阵的逆,典型的使用方式是作为model view matrix


	// 3、空间融合距离，用于双目立体
	virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const= 0;
	virtual float getFusionDistanceValue() const= 0;


	// 4、设置/获取求交遍历的掩码      
	virtual void setIntersectTraversalMask(unsigned int mask)= 0;
	virtual unsigned int getIntersectTraversalMask() const= 0;


	// 5、与节点相关的函数（有些操作器需要（如跟踪），有些不需要）
	virtual void setNode(osg::IVBF_SGNode*)= 0;
	virtual const osg::IVBF_SGNode* getNode() const= 0;
	virtual osg::IVBF_SGNode* getNode()= 0;



	// 6、与默认位置相关的函数

	// 人工设置操作器的默认位置
	virtual void setHomePosition(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up, bool autoComputeHomePosition=false)= 0;	
	virtual void getHomePosition(osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up) const= 0;

	virtual void setAutoComputeHomePosition(bool flag)= 0; // 设置是否自动计算操作器的默认位置
	virtual bool getAutoComputeHomePosition() const= 0;	   // 获取是否自动计算操作器的默认位置

	virtual void computeHomePosition(const osg::IVBF_Camera* camera = NULL, bool useBoundingBox = false)=0;// 计算默认位置
	
	virtual void home(const osgGA::GUIEventAdapter&, ::IVBF_GUIActionAdapter&)=0; // 把相机移到默认位置
	virtual void home(double /*currentTime*/)=0;					     // 把相机移到默认位置

	virtual void init(const osgGA::GUIEventAdapter& ,::IVBF_GUIActionAdapter&)=0;    // 重置（初始化）
	virtual bool handle(const osgGA::GUIEventAdapter& ea,::IVBF_GUIActionAdapter& us)=0;// 处理事件

    // 是否固定远近裁剪面，如跟踪操作器、第一人称漫游操作器、驾驶操作器等
    virtual bool IsFixedNearFar()=0;
    virtual void SetFixedNearFar(bool bFixed)=0;
    virtual double GetFixedNear()=0;
    virtual void   SetFixedNear(double dNear)=0;
    virtual double GetFixedFar()=0;
    virtual void   SetFixedFar (double dFar )=0;

};

#endif

