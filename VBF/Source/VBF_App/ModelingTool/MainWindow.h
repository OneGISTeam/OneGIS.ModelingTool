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
	//�½�����
	void newProject();
	//�򿪹���
	void openProject();
	//���湤��
	void saveProject();
	//��湤��Ϊ
	void saveProjectAs();
	//�˳�����
	void exitApp();

	//��������ļ�
	void importObjectFile();
	//����������ļ�
	void importObjectClassFile();
	//���������ļ�
	void exportObjectFile();
	//�����������ļ�
	void exportObjectClassFile();
	//��������
	void createObject();
	//����������
	void createObjectClass();

	// �������Դ
	void importDataSource();
	// �Ƴ�����Դ
	void removeDataSource();
	// ��ӹ��˹���
	void appendFilterRule();
	// ���ӳ�����
	void appendMappingRule();
	// ����ںϹ���
	void appendMergeRule();
	// �༭����
	void editRule();
	// �Ƴ�����
	void removeRule();
	// ִ��ת��
	void executeConversion();

	//������ϵ��
	void createRelationClass();
	//�ֶ�������ϵ
	void createRelationByManual();
	//����������ϵ
	void createRelationByBatch();

	// �鿴��Ϊ�����Ϣ
	void checkBehaviorComponent();
	//��Ϊ����������
	void createBehaviorComponentFrame();
	//��Ϊ����
	void debugBehavior();

	//���÷���ʱ��
	void setSimulationTime();

private:
	Ui::MainWindow ui;
};

#endif // MAINWINDOW_H
