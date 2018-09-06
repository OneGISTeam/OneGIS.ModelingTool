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

	pSpashScreen->showMessage(tr("������������..."), Qt::AlignBottom|Qt::AlignLeft, Qt::blue);

	//��������ʼ��UI
	IC_MainUI* pMainUi = new C_MainUI(pSpashScreen, this);
	if(!pMainUi->init()) return;

	//��������
	C_MainCtrl* pMainCtrl = new C_MainCtrl();

	createConnections();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createConnections()
{
	//�½�����
	connect(ui.action_newProject, SIGNAL(triggered()), this, SLOT(newProject()));
	//�򿪹���
	connect(ui.action_openProject, SIGNAL(triggered()), this, SLOT(openProject()));
	//���湤��
	connect(ui.action_saveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
	//��湤��Ϊ
	connect(ui.action_saveProjectAs, SIGNAL(triggered()), this, SLOT(saveProjectAs()));
	//�˳�
	connect(ui.action_exit, SIGNAL(triggered()), this, SLOT(exitApp()));

	//��������ļ�
	connect(ui.action_importObjectFile, SIGNAL(triggered()), this, SLOT(importObjectFile()));
	//����������ļ�
	connect(ui.action_importObjectClass, SIGNAL(triggered()), this, SLOT(importObjectClassFile()));
	//���������ļ�
	connect(ui.action_exportObjectFile, SIGNAL(triggered()), this, SLOT(exportObjectFile()));
	//�����������ļ�
	connect(ui.action_exportObjectClass, SIGNAL(triggered()), this, SLOT(exportObjectClassFile()));
	//��������
	connect(ui.action_createObject, SIGNAL(triggered()), this ,SLOT(createObject()));
	//����������
	connect(ui.action_createObjectClass, SIGNAL(triggered()), this, SLOT(createObjectClass()));

	// ��������Դ
	connect(ui.action_importData, SIGNAL(triggered()), this, SLOT(importDataSource()));
	// �Ƴ�����Դ
	connect(ui.action_removeData, SIGNAL(triggered()), this, SLOT(removeDataSource()));
	// ��ӹ��˹���
	connect(ui.action_filterRule, SIGNAL(triggered()), this, SLOT(appendFilterRule()));
	// ���ӳ�����
	connect(ui.action_mappingRule, SIGNAL(triggered()), this, SLOT(appendMappingRule()));
	// ����ںϹ���
	connect(ui.action_mergeRule, SIGNAL(triggered()), this, SLOT(appendMergeRule()));
	// �༭����
	connect(ui.action_editRule, SIGNAL(triggered()), this, SLOT(editRule()));
	// �Ƴ�����
	connect(ui.action_removeRule, SIGNAL(triggered()), this, SLOT(removeRule()));
	// ִ��ת��
	connect(ui.action_convert, SIGNAL(triggered()), this, SLOT(executeConversion()));

	//������ϵ��
	connect(ui.action_createRelationClass, SIGNAL(triggered()), this, SLOT(createRelationClass()));
	//�ֶ�������ϵ
	connect(ui.action_manualCreateRelation, SIGNAL(triggered()), this, SLOT(createRelationByManual()));
	//����������ϵ
	connect(ui.action_batchCreateRelation, SIGNAL(triggered()), this, SLOT(createRelationByBatch()));

	// �鿴��Ϊ�����Ϣ
	connect(ui.action_behaviorComponentInfo, SIGNAL(triggered()), this, SLOT(checkBehaviorComponent()));
	//��Ϊ����������
	connect(ui.action_behaviorComponent, SIGNAL(triggered()), this, SLOT(createBehaviorComponentFrame()));
	//��Ϊ����
	connect(ui.action_behaviorDebug, SIGNAL(triggered()), this, SLOT(debugBehavior()));

	//���÷���ʱ��
	connect(ui.action_simulatorTime, SIGNAL(triggered()), this, SLOT(setSimulationTime()));
}

void MainWindow::newProject()
{

}

void MainWindow::openProject()
{
	QFileDialog::getOpenFileName(this, tr("�򿪹����ļ�"));
}

void MainWindow::saveProject()
{

}

void MainWindow::saveProjectAs()
{
	QFileDialog::getSaveFileName(this, tr("��湤��Ϊ"));
}

void MainWindow::exitApp()
{
	QApplication::exit();
}

void MainWindow::importObjectFile()
{
	/*QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("�򿪶�����ʱ�ն����ļ�"));
	if(fileNames.size() > 0){
		C_MainCtrl::instance()->objectFileAccess()->set3DMainCtrl(G_Get3DMainCtrl());
		C_MainCtrl::instance()->objectFileAccess()->load(fileNames[0].toStdString());
	}*/
}

void MainWindow::importObjectClassFile()
{
	QFileDialog::getOpenFileNames(this, tr("�򿪶�����ʱ�ն������ļ�"));
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
	QFileDialog fileDlg(this,tr("��������Դ"));
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






