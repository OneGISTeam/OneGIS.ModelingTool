#pragma once
#include <vector>
#include <QMdiArea>
#include <QSplashScreen>
#include <QLabel>
#include "Include/IC_MainUI.h"
#include "Include/IC_ViewWidget.h"
#include "Include/IC_Wnd.h"
#include "C_MessageFrame.h"

using namespace std;

class C_MainUI :
	public IC_MainUI
{
	Q_OBJECT
public:
	C_MainUI(QSplashScreen* pSplashScreen, QMainWindow* pMainWnd);
	virtual ~C_MainUI(void);

	/**
     * @brief ��ȡ�����ڶ���
     * @return QWidget �����ڶ���ָ��
     */
	virtual QMainWindow* mainWindow();

	/**
     * @brief ��ʼ��MainUI
     * @return bool ��ʼ��״̬
     */
	virtual bool init();

	virtual IC_ViewWidget* getViewWidget(QString name);

	virtual IC_Wnd* getWnd(QString name);

	static C_MainUI* instance();

private slots:
	void on_subwindow_activated(QMdiSubWindow* window);

private:
	bool initViewWidgets();
	bool initWnds();

private:
	static C_MainUI* m_pInstance;
	QMainWindow* m_pMainWindow;
	vector<IC_ViewWidget*> m_vecViewWidgets;
	vector<IC_Wnd*> m_vecWnds;
	QMdiArea* m_pMdiArea;

	//������������
	QSplashScreen* m_pSpashScreen;

	//������Ϣ��ʾ����������Ϣ��ʾ��������ʱ��ʾ����ʱ��ʾ��statusBar()->showMessage()��
	QLabel* m_pLabel;
};

