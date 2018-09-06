#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QSplashScreen>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QSplashScreen* pSpashScreen, QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	void createConnections();

private slots:
	//新建工程
	void newProject();
	//打开工程
	void openProject();
	//保存工程
	void saveProject();
	//另存工程为
	void saveProjectAs();
	//退出程序
	void exitApp();

	//导入对象文件
	void importObjectFile();
	//导入对象类文件
	void importObjectClassFile();
	//导出对象文件
	void exportObjectFile();
	//导出对象类文件
	void exportObjectClassFile();
	//创建对象
	void createObject();
	//创建对象类
	void createObjectClass();

	// 添加数据源
	void importDataSource();
	// 移除数据源
	void removeDataSource();
	// 添加过滤规则
	void appendFilterRule();
	// 添加映射规则
	void appendMappingRule();
	// 添加融合规则
	void appendMergeRule();
	// 编辑规则
	void editRule();
	// 移除规则
	void removeRule();
	// 执行转换
	void executeConversion();

	//创建关系类
	void createRelationClass();
	//手动创建关系
	void createRelationByManual();
	//批量创建关系
	void createRelationByBatch();

	// 查看行为组件信息
	void checkBehaviorComponent();
	//行为组件框架生成
	void createBehaviorComponentFrame();
	//行为调试
	void debugBehavior();

	//设置仿真时间
	void setSimulationTime();

private:
	Ui::MainWindow ui;
};

#endif // MAINWINDOW_H
