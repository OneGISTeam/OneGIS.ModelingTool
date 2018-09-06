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
     * @brief 获取主窗口对象
     * @return QWidget 主窗口对象指针
     */
	virtual QMainWindow* mainWindow();

	/**
     * @brief 初始化MainUI
     * @return bool 初始化状态
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

	//程序启动界面
	QSplashScreen* m_pSpashScreen;

	//程序信息提示栏（永久信息提示，而非临时提示，临时提示用statusBar()->showMessage()）
	QLabel* m_pLabel;
};

