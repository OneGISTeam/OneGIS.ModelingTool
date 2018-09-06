#ifndef IVBF_VIEWER_VIEW_H
#define IVBF_VIEWER_VIEW_H 1

#include <VBF_Display/VBF_Viewer/Export>

#include <VBF_Engine/VBF_SceneGraph/VBF_CameraSlave.h>
#include <VBF_Engine/VBF_SGUtil/LineSegmentIntersector>
#include <VBF_Engine/VBF_SGDB/DatabasePager>
#include <VBF_Engine/VBF_SGDB/ImagePager>

#include <VBF_Display/VBF_Manipulator/IVBF_CameraManipulator.h>
#include <VBF_Display/VBF_Manipulator/VBF_EventQueue.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_ViewBrief.h>


class IVBF_Viewer;

// 深度分隔：把相机分成多个子相机，使远近的物体分别渲染，每个部分有自己的远近平面，可以避免ZBuffer精度不足的问题。

struct OSGVIEWER_EXPORT CVBF_DepthPartitionSettings : public ::CVBF_Referenced
{
    enum DepthMode
    {
        FIXED_RANGE,
        BOUNDING_VOLUME
    };

    CVBF_DepthPartitionSettings(DepthMode mode=BOUNDING_VOLUME);

    virtual bool getDepthRange(osg::IVBF_ViewBrief& view, unsigned int partition, double& zNear, double& zFar);

    DepthMode _mode;
    double _zNear;
    double _zMid;
    double _zFar;
};


// 视图接口
class IVBF_View : public osg::IVBF_ViewBrief, public ::IVBF_GUIActionAdapter
{
public:
	virtual IVBF_Viewer* GetViewer() = 0;

    // 设置/获取统计对象，用于统计帧相关的时间和场景图数据
    virtual void setStats(CVBF_Stats* stats)=0;
    virtual CVBF_Stats* getStats()=0;
    virtual const CVBF_Stats* getStats() const=0;

	// 设置/获取开始时钟（Tick）
    virtual void setStartTick(CVBF_Timer_t tick)=0;
    virtual CVBF_Timer_t getStartTick() const=0;

	// 设置/获取场景数据
	virtual void setSceneData(osg::IVBF_SGNode* node) = 0;
    virtual osg::IVBF_SGNode* getSceneData() = 0;
    virtual const osg::IVBF_SGNode* getSceneData() const = 0;

	// 设置/获取个分页数据库，用于数据的动态调度
    virtual void setDatabasePager(osgDB::DatabasePager* dp) = 0;
    virtual osgDB::DatabasePager* getDatabasePager() = 0;
    virtual const osgDB::DatabasePager* getDatabasePager() const = 0;

	typedef std::list< ref_ptr<osgGA::GUIEventHandler> > EventHandlers;

    // 添加/移除/获取事件处理器
    virtual void addEventHandler(osgGA::GUIEventHandler* eventHandler) = 0;
    virtual void addEventHandlerToHead(osgGA::GUIEventHandler* eventHandler) = 0;
    virtual void removeEventHandler(osgGA::GUIEventHandler* eventHandler) = 0;
    virtual EventHandlers& getEventHandlers() = 0;
    virtual const EventHandlers& getEventHandlers() const = 0;

    // 是否可去掉？  把CVBF_SGNodePath设置到场景中任何一个激活的CoordinateSystemNode path。
    // CoordinateSystemNode path用于帮助应用程序和相机操作器处理 地心坐标系统
    virtual void setCoordinateSystemNodePath(const osg::CVBF_SGNodePath& nodePath)=0;
    virtual osg::CVBF_SGNodePath getCoordinateSystemNodePath() const =0;


 	// 设置/获取EventQueue，用于和 外部非窗口相关的事件 统一
    virtual void setEventQueue(osgGA::CVBF_EventQueue* eventQueue)=0;
    virtual osgGA::CVBF_EventQueue* getEventQueue()=0;
    virtual const osgGA::CVBF_EventQueue* getEventQueue() const=0;

    // 设置/获取相机操作器。该操作器根据事件（鼠标键盘等）控制主相机的位置。 resetPosition：是否把操作器设为home position
    virtual void setCameraManipulator(IVBF_CameraManipulator* manipulator, bool resetPosition = true)=0;
    virtual IVBF_CameraManipulator* getCameraManipulator()=0;
    virtual const IVBF_CameraManipulator* getCameraManipulator() const=0;

	 // 执行操作器的home函数
    virtual void home()=0;

	// 5、根据显示设备自动创建相机
	virtual void setUpViewAcrossAllScreens()=0;// 在所有的屏幕上创建子相机和相关的GraphicsWindows 	
    virtual void setUpViewInWindow(int x, int y, int width, int height, unsigned int screenNum=0)=0;// 在单窗口上创建一个单相机	
    virtual void setUpViewOnSingleScreen(unsigned int screenNum=0)=0;// 创建一个全屏幕的单相机
	// 用于半球面显示器的工作，使用6个子相机渲染cube map的6个面，第7个相机进行变形校正
    virtual void setUpViewFor3DSphericalDisplay(double radius=1.0, double collar=0.45, unsigned int screenNum=0, osg::Image* intensityMap=0, const osg::Matrixd& projectorMatrix = osg::Matrixd())=0;
    // 在球形显示器上显示主场景to as panoramic 2:1 texture and then doing distortion correction to present onto a spherical display.
    virtual void setUpViewForPanoramicSphericalDisplay(double radius=1.0, double collar=0.45, unsigned int screenNum=0, osg::Image* intensityMap=0, const osg::Matrixd& projectorMatrix = osg::Matrixd())=0;
	// 设置裸眼立体显示的Philips WoWvx显示器
    virtual void setUpViewForWoWVxDisplay(unsigned int screenNum, unsigned char wow_content, unsigned char wow_factor, unsigned char wow_offset, float wow_disparity_Zd, float wow_disparity_vz, float wow_disparity_M, float wow_disparity_C)=0;

	 	
    virtual bool containsCamera(const osg::IVBF_Camera* camera) const=0;// 判断是否包含给定的相机    
    virtual const osg::IVBF_Camera* getCameraContainingPosition(float x, float y, float& local_x, float& local_y) const=0;// 获取包含鼠标位置x,y（在主相机窗口中的坐标）的相机，并返回在该相机对应的局部窗口中的位置。

    virtual bool computeIntersections(float x,float y, osgUtil::LineSegmentIntersector::Intersections& intersections,osg::IVBF_SGNode::NodeMask traversalMask = 0xffffffff)=0;
    virtual bool computeIntersections(float x,float y, const osg::CVBF_SGNodePath& nodePath, osgUtil::LineSegmentIntersector::Intersections& intersections,osg::IVBF_SGNode::NodeMask traversalMask = 0xffffffff)=0;

	virtual void computeActiveCoordinateSystemNodePath()=0;

	// 把相机按深度分为多个子相机
    virtual bool setUpDepthPartitionForCamera(osg::IVBF_Camera* cameraToPartition, CVBF_DepthPartitionSettings* dps=0)=0;
     // 把激活的（active）相机按深度分为多个子相机
	virtual bool setUpDepthPartition(CVBF_DepthPartitionSettings* dsp=0)=0;

	//!!!以下是否优化掉

	// 设置/获取该视图的显示设置
    virtual void setDisplaySettings(osg::DisplaySettings* ds)=0;  
    virtual osg::DisplaySettings* getDisplaySettings()=0;  
    virtual const osg::DisplaySettings* getDisplaySettings() const=0;  

   // 设置/获取空间融合距离模式和值，仅用于双目立体
    virtual void setFusionDistance(osgUtil::SceneView::FusionDistanceMode mode,float value=1.0f)=0;  
    virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const=0;
    virtual float getFusionDistanceValue() const=0;

	// 把场景的数据设置给相机
	virtual void assignSceneDataToCameras()=0;

    virtual osg::IVBF_SGNodeGroup* getNeedIntersectData() = 0;

};
 

OSGVIEWER_EXPORT IVBF_View* VBF_CreateView();
OSGVIEWER_EXPORT IVBF_View* VBF_CreateView(const IVBF_View& view, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

#endif
