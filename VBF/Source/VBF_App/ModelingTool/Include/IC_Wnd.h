#ifndef IC_WND_H
#define IC_WND_H
#include <QString>
#include <QMdiSubWindow>

const QString UI_WND_2D = "ui_wnd_2d";
const QString UI_WND_3D = "ui_wnd_3d";
const QString UI_WND_CONVERT = "ui_wnd_convert";

class IC_Wnd: public QMdiSubWindow{

public:
	IC_Wnd(QWidget* pParent = 0):QMdiSubWindow(pParent) {};
	virtual ~IC_Wnd() {};

	/**
     * @brief 获取显示窗口的名称，作为检索的唯一标识
     * @return QString 该显示窗口的名称
     */
	virtual QString name() = 0;

	/**
     * @brief 对窗口进行初始化，可被子类继承
     */
	virtual void init() = 0;

	/**
     * @brief 每个显示窗口可以关联不同的状态栏，通过该接口获取状态栏
	 * @return 返回显示窗口所关联的状态栏
     */
	virtual QWidget* statusWidget() = 0;
};

#endif