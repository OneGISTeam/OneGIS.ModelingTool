#include "MainWindow.h"
#include <QFileDialog>
#include "C_DialogObjectCreate.h"
#include "C_DialogObjectExport.h"
#include "C_DialogObjectClassExport.h"
#include "C_DialogObjectClassCreate.h"
#include "C_DialogRelationClassCreate.h"
#include "C_DialogSimulationTimeSet.h"
#include "C_ConvertWnd.h"
#include "C_DialogBehaviorViewer.h"
#include "C_WizardRelationCreateBatch.h"
#include "C_DialogFrameProducer.h"
#include "C_DialogBehaviorDebug.h"
#include "C_MainUI.h"
#include "C_MainCtrl.h"

//#include "VBF_ViewerWidget.h"

MainWindow::MainWindow(QSplashScreen* pSpashScreen, QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	pSpashScreen->showMessage(tr("正在启动程序..."), Qt::AlignBottom|Qt::AlignLeft, Qt::blue);

	//构建并初始化UI
	IC_MainUI* pMainUi = new C_MainUI(pSpashScreen, this);
	if(!pMainUi->init()) return;

	//构建主控
	C_MainCtrl* pMainCtrl = new C_MainCtrl();

	createConnections();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createConnections()
{
	//新建工程
	connect(ui.action_newProject, SIGNAL(triggered()), this, SLOT(newProject()));
	//打开工程
	connect(ui.action_openProject, SIGNAL(triggered()), this, SLOT(openProject()));
	//保存工程
	connect(ui.action_saveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
	//另存工程为
	connect(ui.action_saveProjectAs, SIGNAL(triggered()), this, SLOT(saveProjectAs()));
	//退出
	connect(ui.action_exit, SIGNAL(triggered()), this, SLOT(exitApp()));

	//导入对象文件
	connect(ui.action_importObjectFile, SIGNAL(triggered()), this, SLOT(importObjectFile()));
	//导入对象类文件
	connect(ui.action_importObjectClass, SIGNAL(triggered()), this, SLOT(importObjectClassFile()));
	//导出对象文件
	connect(ui.action_exportObjectFile, SIGNAL(triggered()), this, SLOT(exportObjectFile()));
	//导出对象类文件
	connect(ui.action_exportObjectClass, SIGNAL(triggered()), this, SLOT(exportObjectClassFile()));
	//创建对象
	connect(ui.action_createObject, SIGNAL(triggered()), this ,SLOT(createObject()));
	//创建对象类
	connect(ui.action_createObjectClass, SIGNAL(triggered()), this, SLOT(createObjectClass()));

	// 导入数据源
	connect(ui.action_importData, SIGNAL(triggered()), this, SLOT(importDataSource()));
	// 移除数据源
	connect(ui.action_removeData, SIGNAL(triggered()), this, SLOT(removeDataSource()));
	// 添加过滤规则
	connect(ui.action_filterRule, SIGNAL(triggered()), this, SLOT(appendFilterRule()));
	// 添加映射规则
	connect(ui.action_mappingRule, SIGNAL(triggered()), this, SLOT(appendMappingRule()));
	// 添加融合规则
	connect(ui.action_mergeRule, SIGNAL(triggered()), this, SLOT(appendMergeRule()));
	// 编辑规则
	connect(ui.action_editRule, SIGNAL(triggered()), this, SLOT(editRule()));
	// 移除规则
	connect(ui.action_removeRule, SIGNAL(triggered()), this, SLOT(removeRule()));
	// 执行转换
	connect(ui.action_convert, SIGNAL(triggered()), this, SLOT(executeConversion()));

	//创建关系类
	connect(ui.action_createRelationClass, SIGNAL(triggered()), this, SLOT(createRelationClass()));
	//手动创建关系
	connect(ui.action_manualCreateRelation, SIGNAL(triggered()), this, SLOT(createRelationByManual()));
	//批量创建关系
	connect(ui.action_batchCreateRelation, SIGNAL(triggered()), this, SLOT(createRelationByBatch()));

	// 查看行为组件信息
	connect(ui.action_behaviorComponentInfo, SIGNAL(triggered()), this, SLOT(checkBehaviorComponent()));
	//行为组件框架生成
	connect(ui.action_behaviorComponent, SIGNAL(triggered()), this, SLOT(createBehaviorComponentFrame()));
	//行为调试
	connect(ui.action_behaviorDebug, SIGNAL(triggered()), this, SLOT(debugBehavior()));

	//设置仿真时间
	connect(ui.action_simulatorTime, SIGNAL(triggered()), this, SLOT(setSimulationTime()));
}

void MainWindow::newProject()
{

}

void MainWindow::openProject()
{
	QFileDialog::getOpenFileName(this, tr("打开工程文件"));
}

void MainWindow::saveProject()
{

}

void MainWindow::saveProjectAs()
{
	QFileDialog::getSaveFileName(this, tr("另存工程为"));
}

void MainWindow::exitApp()
{
	QApplication::exit();
}

void MainWindow::importObjectFile()
{
	/*QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("打开多粒度时空对象文件"));
	if(fileNames.size() > 0){
		C_MainCtrl::instance()->objectFileAccess()->set3DMainCtrl(G_Get3DMainCtrl());
		C_MainCtrl::instance()->objectFileAccess()->load(fileNames[0].toStdString());
	}*/
}

void MainWindow::importObjectClassFile()
{
	QFileDialog::getOpenFileNames(this, tr("打开多粒度时空对象类文件"));
}

void MainWindow::exportObjectFile()
{
	C_DialogObjectExport dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}

void MainWindow::exportObjectClassFile()
{
	C_DialogObjectClassExport dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}

void MainWindow::createObject()
{
	C_DialogObjectCreate dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}

void MainWindow::createObjectClass()
{
	C_DialogObjectClassCreate dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}

void MainWindow::importDataSource()
{
	QFileDialog fileDlg(this,tr("导入数据源"));
	if(fileDlg.exec() == QDialog::Accepted)
	{
		C_ConvertWnd* pWnd = static_cast<C_ConvertWnd*>(C_MainUI::instance()->getWnd(UI_WND_CONVERT));
		pWnd->getConvertCanvasPtr()->importDataByFileName(fileDlg.selectedFiles());
	}
}

void MainWindow::removeDataSource()
{
	C_ConvertWnd* pWnd = static_cast<C_ConvertWnd*>(C_MainUI::instance()->getWnd(UI_WND_CONVERT));
	pWnd->getConvertCanvasPtr()->removeData();
}

void MainWindow::appendFilterRule()
{
	C_ConvertWnd* pWnd = static_cast<C_ConvertWnd*>(C_MainUI::instance()->getWnd(UI_WND_CONVERT));
	pWnd->getConvertCanvasPtr()->appendFilterRule();
}

void MainWindow::appendMappingRule()
{
	C_ConvertWnd* pWnd = static_cast<C_ConvertWnd*>(C_MainUI::instance()->getWnd(UI_WND_CONVERT));
	pWnd->getConvertCanvasPtr()->appendMappingRule();
}

void MainWindow::appendMergeRule()
{
	C_ConvertWnd* pWnd = static_cast<C_ConvertWnd*>(C_MainUI::instance()->getWnd(UI_WND_CONVERT));
	pWnd->getConvertCanvasPtr()->appendMergeRule();
}

void MainWindow::editRule()
{
	C_ConvertWnd* pWnd = static_cast<C_ConvertWnd*>(C_MainUI::instance()->getWnd(UI_WND_CONVERT));
	pWnd->getConvertCanvasPtr()->editRule();
}

void MainWindow::removeRule()
{
	C_ConvertWnd* pWnd = static_cast<C_ConvertWnd*>(C_MainUI::instance()->getWnd(UI_WND_CONVERT));
	pWnd->getConvertCanvasPtr()->removeRule();
}

void MainWindow::executeConversion()
{
	C_ConvertWnd* pWnd = static_cast<C_ConvertWnd*>(C_MainUI::instance()->getWnd(UI_WND_CONVERT));
	pWnd->getConvertCanvasPtr()->convert();
}

void MainWindow::createRelationClass()
{
	C_DialogRelationClassCreate dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}

void MainWindow::createRelationByManual()
{
	IC_ViewWidget* pViewWidget = C_MainUI::instance()->getViewWidget(UI_VIEWWIDGET_RELATIONMANUALCREATE);
	if(pViewWidget){
		pViewWidget->show();
	}
}

void MainWindow::setSimulationTime()
{
	C_DialogSimulationTimeSet dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}

void MainWindow::checkBehaviorComponent()
{
	C_DialogBehaviorViewer dialog(this);
	if(dialog.exec() != QDialog::Accepted)
	{

	}
}

void MainWindow::createRelationByBatch()
{
	C_WizardRelationCreateBatch wizard(this);
	wizard.exec();
}

void MainWindow::createBehaviorComponentFrame()
{
	C_DialogFrameProducer dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}

void MainWindow::debugBehavior(){
	C_DialogBehaviorDebug* pDialog = new C_DialogBehaviorDebug(this);
	pDialog->show();
}






