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

// ��ȷָ���������ֳɶ���������ʹԶ��������ֱ���Ⱦ��ÿ���������Լ���Զ��ƽ�棬���Ա���ZBuffer���Ȳ�������⡣

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


// ��ͼ�ӿ�
class IVBF_View : public osg::IVBF_ViewBrief, public ::IVBF_GUIActionAdapter
{
public:
	virtual IVBF_Viewer* GetViewer() = 0;

    // ����/��ȡͳ�ƶ�������ͳ��֡��ص�ʱ��ͳ���ͼ����
    virtual void setStats(CVBF_Stats* stats)=0;
    virtual CVBF_Stats* getStats()=0;
    virtual const CVBF_Stats* getStats() const=0;

	// ����/��ȡ��ʼʱ�ӣ�Tick��
    virtual void setStartTick(CVBF_Timer_t tick)=0;
    virtual CVBF_Timer_t getStartTick() const=0;

	// ����/��ȡ��������
	virtual void setSceneData(osg::IVBF_SGNode* node) = 0;
    virtual osg::IVBF_SGNode* getSceneData() = 0;
    virtual const osg::IVBF_SGNode* getSceneData() const = 0;

	// ����/��ȡ����ҳ���ݿ⣬�������ݵĶ�̬����
    virtual void setDatabasePager(osgDB::DatabasePager* dp) = 0;
    virtual osgDB::DatabasePager* getDatabasePager() = 0;
    virtual const osgDB::DatabasePager* getDatabasePager() const = 0;

	typedef std::list< ref_ptr<osgGA::GUIEventHandler> > EventHandlers;

    // ���/�Ƴ�/��ȡ�¼�������
    virtual void addEventHandler(osgGA::GUIEventHandler* eventHandler) = 0;
    virtual void addEventHandlerToHead(osgGA::GUIEventHandler* eventHandler) = 0;
    virtual void removeEventHandler(osgGA::GUIEventHandler* eventHandler) = 0;
    virtual EventHandlers& getEventHandlers() = 0;
    virtual const EventHandlers& getEventHandlers() const = 0;

    // �Ƿ��ȥ����  ��CVBF_SGNodePath���õ��������κ�һ�������CoordinateSystemNode path��
    // CoordinateSystemNode path���ڰ���Ӧ�ó����������������� ��������ϵͳ
    virtual void setCoordinateSystemNodePath(const osg::CVBF_SGNodePath& nodePath)=0;
    virtual osg::CVBF_SGNodePath getCoordinateSystemNodePath() const =0;


 	// ����/��ȡEventQueue�����ں� �ⲿ�Ǵ�����ص��¼� ͳһ
    virtual void setEventQueue(osgGA::CVBF_EventQueue* eventQueue)=0;
    virtual osgGA::CVBF_EventQueue* getEventQueue()=0;
    virtual const osgGA::CVBF_EventQueue* getEventQueue() const=0;

    // ����/��ȡ������������ò����������¼��������̵ȣ������������λ�á� resetPosition���Ƿ�Ѳ�������Ϊhome position
    virtual void setCameraManipulator(IVBF_CameraManipulator* manipulator, bool resetPosition = true)=0;
    virtual IVBF_CameraManipulator* getCameraManipulator()=0;
    virtual const IVBF_CameraManipulator* getCameraManipulator() const=0;

	 // ִ�в�������home����
    virtual void home()=0;

	// 5��������ʾ�豸�Զ��������
	virtual void setUpViewAcrossAllScreens()=0;// �����е���Ļ�ϴ������������ص�GraphicsWindows 	
    virtual void setUpViewInWindow(int x, int y, int width, int height, unsigned int screenNum=0)=0;// �ڵ������ϴ���һ�������	
    virtual void setUpViewOnSingleScreen(unsigned int screenNum=0)=0;// ����һ��ȫ��Ļ�ĵ����
	// ���ڰ�������ʾ���Ĺ�����ʹ��6���������Ⱦcube map��6���棬��7��������б���У��
    virtual void setUpViewFor3DSphericalDisplay(double radius=1.0, double collar=0.45, unsigned int screenNum=0, osg::Image* intensityMap=0, const osg::Matrixd& projectorMatrix = osg::Matrixd())=0;
    // ��������ʾ������ʾ������to as panoramic 2:1 texture and then doing distortion correction to present onto a spherical display.
    virtual void setUpViewForPanoramicSphericalDisplay(double radius=1.0, double collar=0.45, unsigned int screenNum=0, osg::Image* intensityMap=0, const osg::Matrixd& projectorMatrix = osg::Matrixd())=0;
	// ��������������ʾ��Philips WoWvx��ʾ��
    virtual void setUpViewForWoWVxDisplay(unsigned int screenNum, unsigned char wow_content, unsigned char wow_factor, unsigned char wow_offset, float wow_disparity_Zd, float wow_disparity_vz, float wow_disparity_M, float wow_disparity_C)=0;

	 	
    virtual bool containsCamera(const osg::IVBF_Camera* camera) const=0;// �ж��Ƿ�������������    
    virtual const osg::IVBF_Camera* getCameraContainingPosition(float x, float y, float& local_x, float& local_y) const=0;// ��ȡ�������λ��x,y��������������е����꣩��������������ڸ������Ӧ�ľֲ������е�λ�á�

    virtual bool computeIntersections(float x,float y, osgUtil::LineSegmentIntersector::Intersections& intersections,osg::IVBF_SGNode::NodeMask traversalMask = 0xffffffff)=0;
    virtual bool computeIntersections(float x,float y, const osg::CVBF_SGNodePath& nodePath, osgUtil::LineSegmentIntersector::Intersections& intersections,osg::IVBF_SGNode::NodeMask traversalMask = 0xffffffff)=0;

	virtual void computeActiveCoordinateSystemNodePath()=0;

	// ���������ȷ�Ϊ��������
    virtual bool setUpDepthPartitionForCamera(osg::IVBF_Camera* cameraToPartition, CVBF_DepthPartitionSettings* dps=0)=0;
     // �Ѽ���ģ�active���������ȷ�Ϊ��������
	virtual bool setUpDepthPartition(CVBF_DepthPartitionSettings* dsp=0)=0;

	//!!!�����Ƿ��Ż���

	// ����/��ȡ����ͼ����ʾ����
    virtual void setDisplaySettings(osg::DisplaySettings* ds)=0;  
    virtual osg::DisplaySettings* getDisplaySettings()=0;  
    virtual const osg::DisplaySettings* getDisplaySettings() const=0;  

   // ����/��ȡ�ռ��ںϾ���ģʽ��ֵ��������˫Ŀ����
    virtual void setFusionDistance(osgUtil::SceneView::FusionDistanceMode mode,float value=1.0f)=0;  
    virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const=0;
    virtual float getFusionDistanceValue() const=0;

	// �ѳ������������ø����
	virtual void assignSceneDataToCameras()=0;

    virtual osg::IVBF_SGNodeGroup* getNeedIntersectData() = 0;

};
 

OSGVIEWER_EXPORT IVBF_View* VBF_CreateView();
OSGVIEWER_EXPORT IVBF_View* VBF_CreateView(const IVBF_View& view, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

#endif
