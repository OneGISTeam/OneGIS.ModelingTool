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
* @brief ������ʱ�ն���ģ������UI
*/
class IC_MainUI: public QObject{

public:
	/**
     * @brief ���캯��
     */
    IC_MainUI() {}

	/**
     * @brief ��������
     */
    virtual ~IC_MainUI() {}

	/**
     * @brief ��ȡ�����ڶ���
     * @return QWidget �����ڶ���ָ��
     */
    virtual QMainWindow* mainWindow() = 0;

	/**
     * @brief ��ʼ�������ڶ��󣬿������������һЩUI��ʼ������
     * @return bool ��ʼ���ɹ����
     */
	virtual bool init() = 0;

	/**
	 * @param �ӿڵ�����
     * @brief �����ӿڵ����ƻ�ȡ�ӿ�
	 * @return IC_ViewWidget* �ӿڵ�ָ��
     */
	virtual IC_ViewWidget* getViewWidget(QString name) = 0;

	/**
	 * @param ���ڵ�����
     * @brief ���ݴ��ڵ����ƻ�ȡ����
	 * @return IC_Wnd* ���ڵ�ָ��
     */
	virtual IC_Wnd* getWnd(QString name) = 0;
};

#endif
