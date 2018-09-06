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


 
/** CVBF_ViewBrief - ά����һ���������һ�������������������������б�
  * ע�⣺ ���û�����������������ͼ��������ȿ��ƣ�control����ʵ�ֳ�������Ⱦ��
  *       �����������ڣ�����������Ƴ�����CVBF_ViewBrief���������ʵ�ֳ�������Ⱦ��
*/
class CVBF_ViewBrief : public IVBF_View
{
    public :
        CVBF_ViewBrief();
        CVBF_ViewBrief(const CVBF_ViewBrief& view, const osg::CopyOp& copyop=CopyOp::SHALLOW_COPY);

//        META_Object(osgViewer,CVBF_ViewBrief);
        
        // �Ӵ����CVBF_ViewBrief�л�ȡ���е����á����/����������ÿ�
        virtual void take(IVBF_ViewBrief& rhs);

        // ����/��ȡͳ�ƶ�������ͳ��֡��ص�ʱ��ͳ���ͼ����
        void setStats(CVBF_Stats* stats) { _stats = stats; }
        CVBF_Stats* getStats() { return _stats.get(); }
        const CVBF_Stats* getStats() const { return _stats.get(); }

        
        // ����/��ȡ��ͼ��ȫ�ֹ�ѡ�Ĭ����HEADLIGHT
        void setLightingMode(LightingMode lightingMode);
        LightingMode getLightingMode() const { return _lightingMode; }

        // ����/��ȡ��ͼ��ȫ�ֹ�
        void setLight(osg::Light* light) { _light = light; }
        osg::Light* getLight() { return _light.get(); }
        const osg::Light* getLight() const { return _light.get(); }

		// ����/��ȡ�����
        virtual void setCamera(osg::IVBF_Camera* camera);
        virtual osg::IVBF_Camera* getCamera() { return _camera.get(); }
        virtual const osg::IVBF_Camera* getCamera() const { return _camera.get(); } // ��ȡ�����

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





/** ��ͼ����1��������������ɣ� �����ݣ�����������ͼ 
    ÿ���Ӿ�����Viewer����1��������ͼ��View����ÿ����ͼ��һ���ӿڣ�Viewport��*/
class CVBF_View : public CVBF_ViewBrief
{
public:

    CVBF_View();
    CVBF_View(const CVBF_View& view, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

    META_Object(osgViewer,CVBF_View);

    virtual osg::IVBF_ViewBrief* asView() { return this; }

    IVBF_Viewer* GetViewer() { return dynamic_cast<IVBF_Viewer*>(m_opViewer.get()); }

    /** �Ӵ����View�л�ȡ���е����á����/����������ÿ�  */
    virtual void take(osg::IVBF_ViewBrief& rhs);


	// ����/��ȡ��ʼʱ�ӣ�Tick��
    virtual void setStartTick(CVBF_Timer_t tick);
    CVBF_Timer_t getStartTick() const { return _startTick; }

	// ����/��ȡ��ͼ�ĳ�������
    Scene* getScene() { return m_ipScene.get(); }
    const Scene* getScene() const { return m_ipScene.get(); }
   
	// ����/��ȡ��������
	virtual void setSceneData(osg::IVBF_SGNode* node);
    osg::IVBF_SGNode* getSceneData() { return m_ipScene.valid() ? m_ipScene->getSceneData() : 0; }
    const osg::IVBF_SGNode* getSceneData() const { return m_ipScene.valid() ? m_ipScene->getSceneData() : 0; }


	// ����/��ȡ����ҳ���ݿ⣬�������ݵĶ�̬����
    void setDatabasePager(osgDB::DatabasePager* dp);
    osgDB::DatabasePager* getDatabasePager();
    const osgDB::DatabasePager* getDatabasePager() const;


	// ����/��ȡ��ҳͼ��⣬����ͼ��Ķ�̬����
    void setImagePager(osgDB::ImagePager* ip);
    osgDB::ImagePager* getImagePager();
    const osgDB::ImagePager* getImagePager() const;


 	// ����/��ȡEventQueue�����ں� �ⲿ�Ǵ�����ص��¼� ͳһ
    void setEventQueue(osgGA::CVBF_EventQueue* eventQueue) { _eventQueue = eventQueue; }
    osgGA::CVBF_EventQueue* getEventQueue() { return _eventQueue.get(); }
    const osgGA::CVBF_EventQueue* getEventQueue() const { return _eventQueue.get(); }

    // ����/��ȡ������������ò����������¼��������̵ȣ������������λ�á� resetPosition���Ƿ�Ѳ�������Ϊhome position
    void setCameraManipulator(IVBF_CameraManipulator* manipulator, bool resetPosition = true);
    IVBF_CameraManipulator* getCameraManipulator() { return m_ipCameraManipulator.get(); }
    const IVBF_CameraManipulator* getCameraManipulator() const { return m_ipCameraManipulator.get(); }

    // ִ�в�������home����
    void home();

    // ���/�Ƴ�/��ȡ�¼�������
    void addEventHandler(osgGA::GUIEventHandler* eventHandler);
    void addEventHandlerToHead(osgGA::GUIEventHandler* eventHandler);
    void removeEventHandler(osgGA::GUIEventHandler* eventHandler);
    EventHandlers& getEventHandlers() { return _eventHandlers; }
    const EventHandlers& getEventHandlers() const { return _eventHandlers; }


    /** ��CVBF_SGNodePath���õ��������κ�һ�������CoordinateSystemNode path��
        CoordinateSystemNode path���ڰ���Ӧ�ó����������������� ��������ϵͳ */
    void setCoordinateSystemNodePath(const osg::CVBF_SGNodePath& nodePath);
    osg::CVBF_SGNodePath getCoordinateSystemNodePath() const;

    /** Compute the CVBF_SGNodePath to any active CoordinateSystemNode present in the Scene.*/
    void computeActiveCoordinateSystemNodePath();


	// ����/��ȡ����ͼ����ʾ����
    void setDisplaySettings(osg::DisplaySettings* ds) { _displaySettings = ds; }
    osg::DisplaySettings* getDisplaySettings() { return _displaySettings.get(); }
    const osg::DisplaySettings* getDisplaySettings() const { return _displaySettings.get(); }

    // ����/��ȡ�ռ��ںϾ���ģʽ��ֵ��������˫Ŀ����
    void setFusionDistance(osgUtil::SceneView::FusionDistanceMode mode,float value=1.0f)
    {
        _fusionDistanceMode = mode;
        _fusionDistanceValue = value;
    }
    osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const { return _fusionDistanceMode; }
    float getFusionDistanceValue() const { return _fusionDistanceValue; }



     
	// 5��������ʾ�豸�Զ��������

	void setUpViewAcrossAllScreens();// �����е���Ļ�ϴ������������ص�GraphicsWindows 	
    void setUpViewInWindow(int x, int y, int width, int height, unsigned int screenNum=0);// �ڵ������ϴ���һ�������	
    void setUpViewOnSingleScreen(unsigned int screenNum=0);// ����һ��ȫ��Ļ�ĵ����
	// ���ڰ�������ʾ���Ĺ�����ʹ��6���������Ⱦcube map��6���棬��7��������б���У��
    void setUpViewFor3DSphericalDisplay(double radius=1.0, double collar=0.45, unsigned int screenNum=0, osg::Image* intensityMap=0, const osg::Matrixd& projectorMatrix = osg::Matrixd());
    // ��������ʾ������ʾ������to as panoramic 2:1 texture and then doing distortion correction to present onto a spherical display.*/
    void setUpViewForPanoramicSphericalDisplay(double radius=1.0, double collar=0.45, unsigned int screenNum=0, osg::Image* intensityMap=0, const osg::Matrixd& projectorMatrix = osg::Matrixd());
	// ��������������ʾ��Philips WoWvx��ʾ��
    void setUpViewForWoWVxDisplay(unsigned int screenNum, unsigned char wow_content, unsigned char wow_factor, unsigned char wow_offset, float wow_disparity_Zd, float wow_disparity_vz, float wow_disparity_M, float wow_disparity_C);






 	// ���������ȷ�Ϊ��������
    bool setUpDepthPartitionForCamera(osg::IVBF_Camera* cameraToPartition, CVBF_DepthPartitionSettings* dps=0);

     // �Ѽ���ģ�active���������ȷ�Ϊ��������
	bool setUpDepthPartition(CVBF_DepthPartitionSettings* dsp=0);


 	// �ж��Ƿ�������������
    bool containsCamera(const osg::IVBF_Camera* camera) const;

    // ��ȡ�������λ��x,y��������������е����꣩��������������ڸ������Ӧ�ľֲ������е�λ�á�
    const osg::IVBF_Camera* getCameraContainingPosition(float x, float y, float& local_x, float& local_y) const;

    /** ���������볡���ڵ�Ľ��㡣���ߴ���Ļ�ϵĵ�x,y�����������/eye���꣩������Ļ��
        * ˵�����������������������Լ�û���ӿ�ʱ����������Ϊ�ü��ռ�i.e. -1,-1 ��1,1,��
        * while if its has a viewport the coordintates will be relative to its viewport dimensions.
        * ����¼����������Զ�������ת�������������/clip ���꣬��˿���ֱ�Ӵ���computeIntersections���� */
    bool computeIntersections(float x,float y, osgUtil::LineSegmentIntersector::Intersections& intersections,osg::IVBF_SGNode::NodeMask traversalMask = 0xffffffff);

    /** Compute intersections between a ray through the specified master cameras window/eye coords and a specified nodePath's subgraph. */
    bool computeIntersections(float x,float y, const osg::CVBF_SGNodePath& nodePath, osgUtil::LineSegmentIntersector::Intersections& intersections,osg::IVBF_SGNode::NodeMask traversalMask = 0xffffffff);

	// ʵ��GUIActionAdapter�ӿ�
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

    observer_ptr<CVBF_Viewer>          m_opViewer;      // ��ͼ���ڵ��Ӿ���

    CVBF_Timer_t                            _startTick;        // ��ʼʱ��

    ref_ptr<osgViewer::Scene>          m_ipScene;			// �����������ĵ�
    ref_ptr<osgGA::CVBF_EventQueue>         _eventQueue;        // �¼�����
    ref_ptr< ::IVBF_CameraManipulator >  m_ipCameraManipulator; // ����������������������Ҳ��һ���¼�������
    EventHandlers                           _eventHandlers;     // �¼��������б�

    osg::ObserverNodePath                   _coordinateSystemNodePath; // ����ϵͳ�ڵ�·��

    ref_ptr<osg::DisplaySettings>      _displaySettings;    // ��ʾ����
    osgUtil::SceneView::FusionDistanceMode  _fusionDistanceMode; // �ռ��ںϾ���ģʽ������˫Ŀ���壩
    float                                   _fusionDistanceValue;// �ռ��ںϾ���ֵ������˫Ŀ���壩

    //h00017
    ref_ptr<osg::IVBF_SGNodeGroup> m_needIntersectData;
    //h00017

};

#endif
