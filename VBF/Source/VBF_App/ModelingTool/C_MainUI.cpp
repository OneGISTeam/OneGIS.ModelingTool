#include "C_MainUI.h"
#include "C_ViewWidgetObject.h"
#include "C_ViewWidgetClass.h"
#include "C_ViewWidgetRelation.h"
#include "C_3DWnd.h"
#include "C_2DWnd.h"
#include "C_ConvertWnd.h"
#include "C_ViewWidgetTimeAxis.h"
#include "C_ViewWidgetTraits.h"
#include "C_ViewWidgetRelationCreateManual.h"
#include "VBF_Base/IVBF_SimulationTimer.h"
#include "VBF_Common/VBF_Math/VBF_TimeConverter.h"

C_MainUI* C_MainUI::m_pInstance = NULL;

C_MainUI::C_MainUI(QSplashScreen* pSplashScreen, QMainWindow* pMainWnd)
{
	m_pInstance = this;

	m_pSpashScreen = pSplashScreen;
	m_pMainWindow = pMainWnd;
	m_pMdiArea = new QMdiArea;

	m_pLabel = new QLabel(tr("就绪"));
	m_pLabel->setMinimumSize(m_pLabel->sizeHint()); 
	m_pLabel->setAlignment(Qt::AlignHCenter); 
	m_pMainWindow->statusBar()->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
}


C_MainUI::~C_MainUI(void)
{
}

QMainWindow* C_MainUI::mainWindow()
{
	return m_pMainWindow;
}

bool C_MainUI::init()
{
	m_pSpashScreen->showMessage(tr("正在初始化显示窗口..."), Qt::AlignBottom|Qt::AlignLeft, Qt::blue);
	initWnds();
	m_pSpashScreen->showMessage(tr("正在初始化视口..."), Qt::AlignBottom|Qt::AlignLeft, Qt::blue);
	initViewWidgets();
	return true;
}

bool C_MainUI::initViewWidgets()
{
	C_ViewWidgetObject* pViewWidgetObject = new C_ViewWidgetObject(m_pMainWindow);
	pViewWidgetObject->init();
	m_vecViewWidgets.push_back(pViewWidgetObject);
	m_pMainWindow->addDockWidget(Qt::LeftDockWidgetArea, pViewWidgetObject);

	C_ViewWidgetClass* pViewWidgetClass = new C_ViewWidgetClass(m_pMainWindow);
	pViewWidgetClass->init();
	m_vecViewWidgets.push_back(pViewWidgetClass);
	m_pMainWindow->addDockWidget(Qt::LeftDockWidgetArea, pViewWidgetClass);

	C_ViewWidgetRelation* pViewWidgetRelation = new C_ViewWidgetRelation(m_pMainWindow);
	pViewWidgetRelation->init();
	m_vecViewWidgets.push_back(pViewWidgetRelation);
	m_pMainWindow->addDockWidget(Qt::LeftDockWidgetArea, pViewWidgetRelation);

	m_pMainWindow->tabifyDockWidget(pViewWidgetObject, pViewWidgetClass);
	m_pMainWindow->tabifyDockWidget(pViewWidgetClass, pViewWidgetRelation);

	//创建时间轴视图停靠窗口
	C_ViewWidgetTimeAxis* pViewWidgetTimeAxis = new C_ViewWidgetTimeAxis(m_pMainWindow);
	pViewWidgetTimeAxis->init();
	m_vecViewWidgets.push_back(pViewWidgetTimeAxis);
	m_pMainWindow->addDockWidget(Qt::BottomDockWidgetArea,pViewWidgetTimeAxis);

	//创建特征视图
	C_ViewWidgetTraits* pViewWidgetCharac = new C_ViewWidgetTraits(m_pMainWindow);
	pViewWidgetCharac->init();
	m_vecViewWidgets.push_back(pViewWidgetCharac);
	m_pMainWindow->addDockWidget(Qt::RightDockWidgetArea,pViewWidgetCharac);

	//创建手动创建关系视图，并隐藏
	C_ViewWidgetRelationCreateManual* pViewWidgetManualCreateRelation = new C_ViewWidgetRelationCreateManual(m_pMainWindow);
	pViewWidgetManualCreateRelation->init();
	m_vecViewWidgets.push_back(pViewWidgetManualCreateRelation);
	m_pMainWindow->addDockWidget(Qt::TopDockWidgetArea, pViewWidgetManualCreateRelation);
	pViewWidgetManualCreateRelation->hide();

	return true;
}

bool C_MainUI::initWnds()
{
	//m_pMdiArea->setViewMode(QMdiArea::TabbedView);

	// 创建批量转换工作画布
	C_ConvertWnd* pConvertWnd = new C_ConvertWnd(m_pMdiArea);
	pConvertWnd->init();
	m_pMdiArea->addSubWindow(pConvertWnd);
	pConvertWnd->showMaximized();
	m_vecWnds.push_back(pConvertWnd);

	//创建二维可视窗口
	C_2DWnd* p2DWnd2 = new C_2DWnd(m_pMdiArea);
	p2DWnd2->init();
	m_pMdiArea->addSubWindow(p2DWnd2);
	p2DWnd2->showMaximized();
	m_vecWnds.push_back(p2DWnd2);

	//创建三维可视窗口
	C_3DWnd* p3DWnd = new C_3DWnd(m_pMdiArea);
	p3DWnd->init();
	m_pMdiArea->addSubWindow(p3DWnd);
	p3DWnd->showMaximized();
	m_vecWnds.push_back(p3DWnd);

	m_pMainWindow->setCentralWidget(m_pMdiArea);

	connect(m_pMdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(on_subwindow_activated(QMdiSubWindow*)));

	return true;
}

void C_MainUI::on_subwindow_activated( QMdiSubWindow* window )
{
	if(window){
		QWidget* pWidget = dynamic_cast<QWidget*>(window);

		IC_Wnd* pWnd = dynamic_cast<IC_Wnd*>(window);
		vector<IC_Wnd*>::iterator iter = m_vecWnds.begin();
		while(iter != m_vecWnds.end()){
			m_pMainWindow->statusBar()->removeWidget((*iter)->statusWidget());
			iter++;
		}
		m_pMainWindow->statusBar()->addWidget(m_pLabel);
		if(pWnd->statusWidget()){
			m_pMainWindow->statusBar()->addPermanentWidget(pWnd->statusWidget());
			pWnd->statusWidget()->show();
		}
	}
}

IC_ViewWidget* C_MainUI::getViewWidget( QString name )
{
	vector<IC_ViewWidget*>::iterator iter = m_vecViewWidgets.begin();
	while(iter != m_vecViewWidgets.end()){
		if((*iter)->name() == name){
			return (*iter);
		}
		iter++;
	}
}

IC_Wnd* C_MainUI::getWnd( QString name )
{
	vector<IC_Wnd*>::iterator iter = m_vecWnds.begin();
	while(iter != m_vecWnds.end()){
		if((*iter)->name() == name){
			return (*iter);
		}
		iter++;
	}
}

C_MainUI* C_MainUI::instance()
{
	return m_pInstance;
}
