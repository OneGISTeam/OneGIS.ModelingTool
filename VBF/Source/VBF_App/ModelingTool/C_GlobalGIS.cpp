#include "C_GlobalGIS.h"

#include "VBF_3DMap/VBF_EarthUtil/EarthManipulator"
#include "VBF_3DMap/VBF_EarthUtil/AutoClipPlaneHandler.h"

#include "VBF_Display/VBF_Manipulator/VBF_ManipulatorStateSet.h"

#include "VBF_Display/VBF_Viewer/IVBF_Viewer.h"
#include "VBF_Display/VBF_Viewer/VBF_EventHandlerStats.h"
#include "VBF_Display/VBF_Viewer/VBF_ViewerEventHandlers.h"
#include "VBF_Display/VBF_Viewer/VBF_GraphicsWindow.h"
#include "VBF_Display/VBF_Viewer/api/Win32/GraphicsWindowWin32"

#include "VBF_Display/VBF_Manipulator/VBF_ManipulatorFlight.h"
#include "VBF_Display/VBF_Manipulator/VBF_ManipulatorDrive.h"
#include "VBF_Display/VBF_Manipulator/VBF_ManipulatorTrackball.h"
#include "VBF_Display/VBF_Manipulator/VBF_ManipulatorTerrain.h"
#include "VBF_Display/VBF_Manipulator/VBF_ManipulatorKeySwitchMatrix.h"
#include "VBF_3DMap/VBF_EarthUtil/AutoClipPlaneHandler.h"
#include "VBF_3DMap/VBF_Terrain/VBF_MapNode.h"

#include "VBF_Aux/VBF_GLAux/VBF_TextUtils.h"
#include "VBF_3DCom/IVBF_3DOcean.h"
#include "VBF_3DCom/IVBF_3DSky.h"
#include "VBF_3DCom/IVBF_3DWeather.h"
#include "VBF_3DMap/VBF_EarthUtil/DetailTexture"

#include "VBF_Base/IVBF_System.h"
#include "VBF_MainCtrl/VBF_MainCtrlUtil.h"
#include "VBF_MainCtrl/IVBF_3DMainCtrl.h"

#include "VBF_Engine/VBF_SGDB/WriteFile"
#include "VBF_3DMap/VBF_Terrain/XmlUtils.h"

#include "VBF_UpdateOperation.h"

#include <QApplication>
#include <QTextCodec>

// 全局变量
IVBF_MainCtrl*              g_pIMainCtrl        = NULL;
IVBF_3DMainCtrl*            g_pI3DMainCtrl      = NULL;
VBF_DynamicLibrary*         g_pMainCtrlDll      = NULL;
//CVBF_UpdateOperation*       g_pUpdateOperation  = NULL;

observer_ptr<CVBF_UpdateEpochOperation> g_opUpdateEpochOperation;

// 观察者，负责接收主控发送的各类消息
//CVBF_Observer       g_observer;
std::string         g_sDataPath;

// 有些初始化工作必须经过一帧之后才可以，bs.valid()是经过一帧之后的一个标志
class CVBF_InitOperation : public osg::Operation
{
public:
	CVBF_InitOperation(const std::string& name, IVBF_MainCtrl* pIMainCtrl,IVBF_Viewer* pIViewer):
	  osg::Operation(name, true)
	  {
		  m_pIMainCtrl = pIMainCtrl;
		  m_ipViewer = pIViewer;
	  }
	  virtual ~CVBF_InitOperation(){}

	  virtual void operator()(osg::CVBF_Object* pObject)
	  {
		  if( !m_ipViewer.valid() ) return;

		  osg::IVBF_SGNodeGroup* pRoot = g_pI3DMainCtrl->GetSceneGraph();

		  const BoundingSphere& bs = pRoot->getBound();
		  if(bs.valid())
		  {
			  // 为了海洋的雾化
			  IVBF_3DWeather* pI3DWeather = (IVBF_3DWeather*)g_pIMainCtrl->QueryInterface(VBF_INTERFACE_3DWEATHER);
			  if(pI3DWeather)
			  {
				  IVBF_Fog* pIFog = pI3DWeather->GetFog();
				  if(pIFog) pIFog->Enable(false);
			  }

			  CVBFO_SGNodeMap* pMapNode = CVBFO_SGNodeMap::findMapNode(pRoot);
			  if(pMapNode==NULL) return;

			  osgEarth::Util::DetailTexture dt;
			  std::string filename( g_sDataPath + "/noise3.png" );
			  //std::string filename( "D:/VBF/SysSet/3DMap/VBF_3DOceanConfig/UnderWaterLight1.png" );

			  osg::Image* image = URI(filename).getImage();
			  if ( image )
			  {
				  dt.setImage( image );
				  dt.setBaseLOD(8);
			  }

			  //dt.setTerrainNode( pMapNode->getTerrainEngine() );

			  setKeep(false);//!!!

		  }
	  }
	  IVBF_MainCtrl* m_pIMainCtrl;
	  observer_ptr<IVBF_Viewer> m_ipViewer;
};

void SetSystemPath()
{
	string sAppPath = VBF_GetExePath();
	string sSysSetPath = sAppPath + "/../../../../SysSet";
	string sDataPath = sSysSetPath + "/TestData";   // 测试使用的数据路径

	// 从配置文件读路径
	ref_ptr<XmlDocument> ipDocConfig = XmlDocument::load( sAppPath + "/VBF_Config.xml" );
	if ( ipDocConfig.valid() )
	{
		CVBF_Config confDoc = ipDocConfig->getConfig();
		if(confDoc.hasChild("root"))
		{
			CVBF_Config confRoot = confDoc.child("root");

			// GlobalGIS路径
			CVBF_Optional<std::string> optGlobalGISPath;
			confRoot.getIfSet("globalgispath",optGlobalGISPath);
			if(optGlobalGISPath.isSet())
			{
				sAppPath = *optGlobalGISPath;
			}
			// SysSet路径
			CVBF_Optional<std::string> optSysSetPath;
			confRoot.getIfSet("syssetpath",optSysSetPath);
			if(optSysSetPath.isSet())
			{
				sSysSetPath = *optSysSetPath;
			}

			// 应用与测试数据路径
			CVBF_Optional<std::string> optDataPath;
			confRoot.getIfSet("datapath",optDataPath);
			if(optDataPath.isSet())
			{
				sDataPath = *optDataPath;
			}
		}
	}
	ipDocConfig = NULL;

	IVBF_System* pISystem = VBF_GetSystem();
	pISystem->SetApplicationPath(sAppPath);
	pISystem->SetSyssetPath(sSysSetPath);
	pISystem->SetDataPath(sDataPath);
}

C_GlobalGIS::C_GlobalGIS( GLWidget* pWidget )
{
	m_pGLWidget = pWidget;
}

C_GlobalGIS::~C_GlobalGIS(void)
{
}

void C_GlobalGIS::createViewer()
{
	SetSystemPath();

	IVBF_System* pISystem = VBF_GetSystem();
	string sSysSetPath = pISystem->GetSyssetPath();
	string sAppPath = pISystem->GetApplicationPath();

	//解决读取json脚本乱码问题
	QApplication::instance()->addLibraryPath(sAppPath.c_str());
	QString sCodecsPath = sAppPath.c_str();
	sCodecsPath += "/codecs";
	QApplication::instance()->addLibraryPath(sCodecsPath);

	// 解决中文问题
	setlocale(LC_ALL, "zh_CN.gb2312");
#ifdef WIN32
	QTextCodec *codec = QTextCodec::codecForName("GB2312");
#else
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
#endif // WIN32

	QTextCodec::setCodecForLocale(codec);
#ifdef QT4_FOUND
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
#endif

	// 添加数据路径
	osgDB::FilePathList& listFilePath = osgDB::Registry::instance()->getDataFilePathList();
	listFilePath.push_back(sAppPath + "/data");
	listFilePath.push_back(sSysSetPath);
	listFilePath.push_back(sSysSetPath+"/fonts");// 添加字体文件路径

	// 初始化3D主控
	if( !::VBF_CreateMainCtrl("VBF_MainCtrl", g_pIMainCtrl, g_pMainCtrlDll, sAppPath.c_str(), sSysSetPath.c_str()) ) return;
	if(NULL==g_pIMainCtrl) return;

	// 选择默认工具
	g_pIMainCtrl->SelectTool("");

	// 获取3D主控
	g_pI3DMainCtrl = (IVBF_3DMainCtrl*)g_pIMainCtrl->QueryInterface(VBF_INTERFACE_3DMAIN);
	if(NULL==g_pI3DMainCtrl) return;

	IVBF_Viewer* pIViewer = g_pI3DMainCtrl->GetViewer();
	if(NULL==pIViewer) return;

	m_opViewer = pIViewer;

	pIViewer->addUpdateOperation(new CVBF_InitOperation("Init",g_pIMainCtrl,pIViewer));

	IVBF_View* pIView = g_pI3DMainCtrl->GetView(0);
	if(NULL==pIView) return;

	reconfigure(pIView);

	pIViewer->SetThreadingModel(enumCullDrawThreadPerContext);
	pIViewer->SetEndBarrierPosition(enumBeforeSwapBuffers);

	pIView->addEventHandler( new osgGA::StateSetManipulator(pIView->getCamera()->getOrCreateStateSet()) );

	// 更新纪元
	ref_ptr<CVBF_UpdateEpochOperation> ipUpdateEpochOperation = new CVBF_UpdateEpochOperation(g_pIMainCtrl);

	double dEpochUTC = CVF_TimeConverter::convertDTtoJD(2012, 3, 25, 6, 43, 22.702);

	IVBF_SimulationTimer* pISimulationTimer = VBF_GetSimulationTimer();
	pISimulationTimer->SetDDayTimeBegin(dEpochUTC);
	//pISimulationTimer->Start();
	pISimulationTimer->SetSimulateTimeRatio(1000);

	pIViewer->addUpdateOperation(ipUpdateEpochOperation.get());
	g_opUpdateEpochOperation = ipUpdateEpochOperation.get();

	// 提高绘制质量
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	ds->setNumMultiSamples(4);
	pIView->setDisplaySettings(ds);

	// 如果有空间组件，使用该组件中的太阳、月亮和星空，关闭Sky组件中的相关内容
	IVBF_SpaceEnv* pISpaceEnv = (IVBF_SpaceEnv*)g_pI3DMainCtrl->QueryInterface(VBF_INTERFACE_SPACEENV);
	if(pISpaceEnv)
	{
		IVBF_3DSky* pI3DSky = (IVBF_3DSky*)g_pI3DMainCtrl->QueryInterface(VBF_INTERFACE_3DSKY);
		if(pI3DSky)
		{
			pI3DSky->setSunVisible(false);
			pI3DSky->setMoonVisible(false);
			pI3DSky->setStarsVisible(false);
		}
	}
}

void C_GlobalGIS::reconfigure( IVBF_View* pView )
{
	if ( !m_ipGC.valid() )
	{

#ifdef WINDOW_USING_MFC
		if(m_hWnd==NULL) return;
		RECT rect;
		::GetWindowRect(m_hWnd, &rect);
		double dX0 = rect.left;
		double dY0 = rect.top;
		double dWidth  = rect.right - rect.left;
		double dHeight = rect.bottom - rect.top;
		ref_ptr<CVBF_Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(m_hWnd);
		ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
		traits->x = dX0;
		traits->y = dY0;
		traits->width  = dWidth;
		traits->height = dHeight;
		traits->windowDecoration = false;
		traits->doubleBuffer = true;
		traits->sharedContext = 0;
		traits->setInheritedWindowPixelFormat = true;
		traits->inheritedWindowData = windata;
		m_ipGC = osg::GraphicsContext::createGraphicsContext(traits);

#endif

#ifdef WINDOW_USING_QT
		if(m_pGLWidget==NULL) return;
		double dX0 = m_pGLWidget->x();
		double dY0 = m_pGLWidget->y();
		double dWidth  = m_pGLWidget->width();
		double dHeight = m_pGLWidget->height();
		//       ref_ptr<CVBF_Referenced> windata = new GraphicsWindowQt::WindowData(m_pWidget);
		osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
		ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits(ds);

		traits->readDISPLAY();
		if (traits->displayNum<0) traits->displayNum = 0;

		traits->windowName = m_pGLWidget->accessibleName().toStdString();
		traits->windowDecoration = false;
		traits->x = dX0;
		traits->y = dY0;
		traits->width  = dWidth;
		traits->height = dHeight;
		traits->doubleBuffer = true;
		traits->inheritedWindowData = new GraphicsWindowQt::WindowData(m_pGLWidget);

		m_ipGC = new GraphicsWindowQt( traits.get() );
#endif
	}

	osg::IVBF_Camera* pICamera = pView->getCamera();
	if( pICamera!=NULL && pICamera->getGraphicsContext()!=m_ipGC.get() )
	{
		pICamera->setGraphicsContext( m_ipGC.get() );

		Viewport* pViewport = pICamera->getViewport();
		if(NULL==pViewport)
		{
			pViewport = new osg::Viewport(0, 0, m_ipGC->getTraits()->width, m_ipGC->getTraits()->height);
			pICamera->setViewport(pViewport);
		}
		pICamera->setProjectionMatrixAsPerspective(30.0f, pViewport->width()/pViewport->height(), 1.0f, 10000.0f);
	}
}

void C_GlobalGIS::render()
{
	if(!m_opViewer.valid())
	{
		createViewer();// 创建一个单视口的视景器
		return;
	}
	
	if (m_opViewer->getRunFrameScheme() == IVBF_Viewer::CONTINUOUS ||
		m_opViewer->checkNeedToDoFrame() )
	{
		m_opViewer->frame();
	}
}


