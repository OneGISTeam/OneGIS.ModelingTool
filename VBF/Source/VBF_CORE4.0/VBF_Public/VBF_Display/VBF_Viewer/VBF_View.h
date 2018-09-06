#ifndef OSGVIEWER_VIEW
#define OSGVIEWER_VIEW 1

#include <VBF_Display/VBF_Viewer/IVBF_View.h>
#include <VBF_Display/VBF_Viewer/IVBF_Viewer.h>
#include <VBF_Display/VBF_Viewer/VBF_Viewer.h>
#include <VBF_Display/VBF_Manipulator/VBF_EventVisitor.h>
#include <VBF_Display/VBF_Viewer/VBF_Scene.h>

class CVBF_ViewerSimple;
class CVBF_ViewerComposite;

using namespace osgViewer;


 
/** CVBF_ViewBrief - 维护了一个主相机和一个与该主相机相关连的子相机的列表。
  * 注意： 如果没有子相机关联到该视图，主相机既控制（control）又实现场景的渲染，
  *       如果子相机存在，则主相机控制场景到CVBF_ViewBrief，而子相机实现场景的渲染。
*/
class CVBF_ViewBrief : public IVBF_View
{
    public :
        CVBF_ViewBrief();
        CVBF_ViewBrief(const CVBF_ViewBrief& view, const osg::CopyOp& copyop=CopyOp::SHALLOW_COPY);

//        META_Object(osgViewer,CVBF_ViewBrief);
        
        // 从传入的CVBF_ViewBrief中获取所有的设置、相机/子相机，并置空
        virtual void take(IVBF_ViewBrief& rhs);

        // 设置/获取统计对象，用于统计帧相关的时间和场景图数据
        void setStats(CVBF_Stats* stats) { _stats = stats; }
        CVBF_Stats* getStats() { return _stats.get(); }
        const CVBF_Stats* getStats() const { return _stats.get(); }

        
        // 设置/获取视图的全局光选项，默认是HEADLIGHT
        void setLightingMode(LightingMode lightingMode);
        LightingMode getLightingMode() const { return _lightingMode; }

        // 设置/获取视图的全局光
        void setLight(osg::Light* light) { _light = light; }
        osg::Light* getLight() { return _light.get(); }
        const osg::Light* getLight() const { return _light.get(); }

		// 设置/获取主相机
        virtual void setCamera(osg::IVBF_Camera* camera);
        virtual osg::IVBF_Camera* getCamera() { return _camera.get(); }
        virtual const osg::IVBF_Camera* getCamera() const { return _camera.get(); } // 获取主相机

        // Set the frame stamp of the view.     
        void setFrameStamp(::CVBF_FrameStamp* fs) { _frameStamp = fs; }
        ::CVBF_FrameStamp* getFrameStamp() { return _frameStamp.get(); }
        const ::CVBF_FrameStamp* getFrameStamp() const { return _frameStamp.get(); }


        bool addSlave(osg::IVBF_Camera* camera, bool useMastersSceneData=true) { return addSlave(camera, osg::Matrix::identity(), osg::Matrix::identity(), useMastersSceneData); }
        bool addSlave(osg::IVBF_Camera* camera, const osg::Matrix& projectionOffset, const osg::Matrix& viewOffset, bool useMastersSceneData=true);

        bool removeSlave(unsigned int pos);

        unsigned int getNumSlaves() const { return static_cast<unsigned int>(_slaves.size()); }

        IVBF_Slave& getSlave(unsigned int pos) { return _slaves[pos]; }
        const IVBF_Slave& getSlave(unsigned int pos) const { return _slaves[pos]; }

        unsigned int findSlaveIndexForCamera(osg::IVBF_Camera* camera) const;

        IVBF_Slave* findSlaveForCamera(osg::IVBF_Camera* camera);

        void updateSlaves();

    protected :

        virtual ~CVBF_ViewBrief();

        virtual osg::GraphicsOperation* createRenderer(osg::IVBF_Camera*) { return 0; }

        ref_ptr<CVBF_Stats>        _stats;

        LightingMode               _lightingMode;
        ref_ptr<osg::Light>        _light;

        ref_ptr<osg::IVBF_Camera>   _camera;
        
        typedef std::vector<Slave>      Slaves;
        Slaves                          _slaves;

        ref_ptr< ::CVBF_FrameStamp >   _frameStamp;
};





/** 视图：由1个或多个子相机构成， 是数据（场景）的视图 
    每个视景器（Viewer）有1个或多个视图（View），每个视图有一个视口（Viewport）*/
class CVBF_View : public CVBF_ViewBrief
{
public:

    CVBF_View();
    CVBF_View(const CVBF_View& view, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

    META_Object(osgViewer,CVBF_View);

    virtual osg::IVBF_ViewBrief* asView() { return this; }

    IVBF_Viewer* GetViewer() { return dynamic_cast<IVBF_Viewer*>(m_opViewer.get()); }

    /** 从传入的View中获取所有的设置、相机/子相机，并置空  */
    virtual void take(osg::IVBF_ViewBrief& rhs);


	// 设置/获取开始时钟（Tick）
    virtual void setStartTick(CVBF_Timer_t tick);
    CVBF_Timer_t getStartTick() const { return _startTick; }

	// 设置/获取视图的场景数据
    Scene* getScene() { return m_ipScene.get(); }
    const Scene* getScene() const { return m_ipScene.get(); }
   
	// 设置/获取场景数据
	virtual void setSceneData(osg::IVBF_SGNode* node);
    osg::IVBF_SGNode* getSceneData() { return m_ipScene.valid() ? m_ipScene->getSceneData() : 0; }
    const osg::IVBF_SGNode* getSceneData() const { return m_ipScene.valid() ? m_ipScene->getSceneData() : 0; }


	// 设置/获取个分页数据库，用于数据的动态调度
    void setDatabasePager(osgDB::DatabasePager* dp);
    osgDB::DatabasePager* getDatabasePager();
    const osgDB::DatabasePager* getDatabasePager() const;


	// 设置/获取分页图像库，用于图像的动态加载
    void setImagePager(osgDB::ImagePager* ip);
    osgDB::ImagePager* getImagePager();
    const osgDB::ImagePager* getImagePager() const;


 	// 设置/获取EventQueue，用于和 外部非窗口相关的事件 统一
    void setEventQueue(osgGA::CVBF_EventQueue* eventQueue) { _eventQueue = eventQueue; }
    osgGA::CVBF_EventQueue* getEventQueue() { return _eventQueue.get(); }
    const osgGA::CVBF_EventQueue* getEventQueue() const { return _eventQueue.get(); }

    // 设置/获取相机操作器。该操作器根据事件（鼠标键盘等）控制主相机的位置。 resetPosition：是否把操作器设为home position
    void setCameraManipulator(IVBF_CameraManipulator* manipulator, bool resetPosition = true);
    IVBF_CameraManipulator* getCameraManipulator() { return m_ipCameraManipulator.get(); }
    const IVBF_CameraManipulator* getCameraManipulator() const { return m_ipCameraManipulator.get(); }

    // 执行操作器的home函数
    void home();

    // 添加/移除/获取事件处理器
    void addEventHandler(osgGA::GUIEventHandler* eventHandler);
    void addEventHandlerToHead(osgGA::GUIEventHandler* eventHandler);
    void removeEventHandler(osgGA::GUIEventHandler* eventHandler);
    EventHandlers& getEventHandlers() { return _eventHandlers; }
    const EventHandlers& getEventHandlers() const { return _eventHandlers; }


    /** 把CVBF_SGNodePath设置到场景中任何一个激活的CoordinateSystemNode path。
        CoordinateSystemNode path用于帮助应用程序和相机操作器处理 地心坐标系统 */
    void setCoordinateSystemNodePath(const osg::CVBF_SGNodePath& nodePath);
    osg::CVBF_SGNodePath getCoordinateSystemNodePath() const;

    /** Compute the CVBF_SGNodePath to any active CoordinateSystemNode present in the Scene.*/
    void computeActiveCoordinateSystemNodePath();


	// 设置/获取该视图的显示设置
    void setDisplaySettings(osg::DisplaySettings* ds) { _displaySettings = ds; }
    osg::DisplaySettings* getDisplaySettings() { return _displaySettings.get(); }
    const osg::DisplaySettings* getDisplaySettings() const { return _displaySettings.get(); }

    // 设置/获取空间融合距离模式和值，仅用于双目立体
    void setFusionDistance(osgUtil::SceneView::FusionDistanceMode mode,float value=1.0f)
    {
        _fusionDistanceMode = mode;
        _fusionDistanceValue = value;
    }
    osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const { return _fusionDistanceMode; }
    float getFusionDistanceValue() const { return _fusionDistanceValue; }



     
	// 5、根据显示设备自动创建相机

	void setUpViewAcrossAllScreens();// 在所有的屏幕上创建子相机和相关的GraphicsWindows 	
    void setUpViewInWindow(int x, int y, int width, int height, unsigned int screenNum=0);// 在单窗口上创建一个单相机	
    void setUpViewOnSingleScreen(unsigned int screenNum=0);// 创建一个全屏幕的单相机
	// 用于半球面显示器的工作，使用6个子相机渲染cube map的6个面，第7个相机进行变形校正
    void setUpViewFor3DSphericalDisplay(double radius=1.0, double collar=0.45, unsigned int screenNum=0, osg::Image* intensityMap=0, const osg::Matrixd& projectorMatrix = osg::Matrixd());
    // 在球形显示器上显示主场景to as panoramic 2:1 texture and then doing distortion correction to present onto a spherical display.*/
    void setUpViewForPanoramicSphericalDisplay(double radius=1.0, double collar=0.45, unsigned int screenNum=0, osg::Image* intensityMap=0, const osg::Matrixd& projectorMatrix = osg::Matrixd());
	// 设置裸眼立体显示的Philips WoWvx显示器
    void setUpViewForWoWVxDisplay(unsigned int screenNum, unsigned char wow_content, unsigned char wow_factor, unsigned char wow_offset, float wow_disparity_Zd, float wow_disparity_vz, float wow_disparity_M, float wow_disparity_C);






 	// 把相机按深度分为多个子相机
    bool setUpDepthPartitionForCamera(osg::IVBF_Camera* cameraToPartition, CVBF_DepthPartitionSettings* dps=0);

     // 把激活的（active）相机按深度分为多个子相机
	bool setUpDepthPartition(CVBF_DepthPartitionSettings* dsp=0);


 	// 判断是否包含给定的相机
    bool containsCamera(const osg::IVBF_Camera* camera) const;

    // 获取包含鼠标位置x,y（在主相机窗口中的坐标）的相机，并返回在该相机对应的局部窗口中的位置。
    const osg::IVBF_Camera* getCameraContainingPosition(float x, float y, float& local_x, float& local_y) const;

    /** 计算射线与场景节点的交点。射线从屏幕上的点x,y（主相机窗口/eye坐标）射向屏幕。
        * 说明，当主相机有子相机并且自己没有视口时，它的坐标为裁剪空间i.e. -1,-1 到1,1,。
        * while if its has a viewport the coordintates will be relative to its viewport dimensions.
        * 鼠标事件处理器会自动把坐标转换到主相机窗口/clip 坐标，因此可以直接传给computeIntersections函数 */
    bool computeIntersections(float x,float y, osgUtil::LineSegmentIntersector::Intersections& intersections,osg::IVBF_SGNode::NodeMask traversalMask = 0xffffffff);

    /** Compute intersections between a ray through the specified master cameras window/eye coords and a specified nodePath's subgraph. */
    bool computeIntersections(float x,float y, const osg::CVBF_SGNodePath& nodePath, osgUtil::LineSegmentIntersector::Intersections& intersections,osg::IVBF_SGNode::NodeMask traversalMask = 0xffffffff);

	// 实现GUIActionAdapter接口
    virtual void requestRedraw();
    virtual void requestContinuousUpdate(bool needed=true);
    virtual void requestWarpPointer(float x,float y);

    //h00017
    virtual osg::IVBF_SGNodeGroup* getNeedIntersectData()
    {
        return m_needIntersectData.get();
    }
    //h00017

public:
    void assignSceneDataToCameras();
    void init();

protected:
    friend class CVBF_ViewerComposite;
    friend class CVBF_ViewerSimple;

    virtual ~CVBF_View();

    virtual osg::GraphicsOperation* createRenderer(osg::IVBF_Camera* camera);

    observer_ptr<CVBF_Viewer>          m_opViewer;      // 视图所在的视景器

    CVBF_Timer_t                            _startTick;        // 起始时钟

    ref_ptr<osgViewer::Scene>          m_ipScene;			// 场景：数据文档
    ref_ptr<osgGA::CVBF_EventQueue>         _eventQueue;        // 事件队列
    ref_ptr< ::IVBF_CameraManipulator >  m_ipCameraManipulator; // 场景漫游器（操作器），也是一种事件处理器
    EventHandlers                           _eventHandlers;     // 事件处理器列表

    osg::ObserverNodePath                   _coordinateSystemNodePath; // 坐标系统节点路径

    ref_ptr<osg::DisplaySettings>      _displaySettings;    // 显示设置
    osgUtil::SceneView::FusionDistanceMode  _fusionDistanceMode; // 空间融合距离模式（用于双目立体）
    float                                   _fusionDistanceValue;// 空间融合距离值（用于双目立体）

    //h00017
    ref_ptr<osg::IVBF_SGNodeGroup> m_needIntersectData;
    //h00017

};

#endif
