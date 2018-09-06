#ifndef IC_MAINUI_H
#define IC_MAINUI_H

#include <QString>
#include <QWidget>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QDockWidget>
#include <QActionGroup>
#include <QStatusBar>
#include <QMainWindow>

#include "IC_ViewWidget.h"
#include "IC_Wnd.h"

/**
* @brief 多粒度时空对象建模工具主UI
*/
class IC_MainUI: public QObject{

public:
	/**
     * @brief 构造函数
     */
    IC_MainUI() {}

	/**
     * @brief 析构函数
     */
    virtual ~IC_MainUI() {}

	/**
     * @brief 获取主窗口对象
     * @return QWidget 主窗口对象指针
     */
    virtual QMainWindow* mainWindow() = 0;

	/**
     * @brief 初始化主窗口对象，可以在这里进行一些UI初始化工作
     * @return bool 初始化成功与否
     */
	virtual bool init() = 0;

	/**
	 * @param 视口的名称
     * @brief 根据视口的名称获取视口
	 * @return IC_ViewWidget* 视口的指针
     */
	virtual IC_ViewWidget* getViewWidget(QString name) = 0;

	/**
	 * @param 窗口的名称
     * @brief 根据窗口的名称获取窗口
	 * @return IC_Wnd* 窗口的指针
     */
	virtual IC_Wnd* getWnd(QString name) = 0;
};

#endif
