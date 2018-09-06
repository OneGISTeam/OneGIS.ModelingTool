#ifndef IC_VIEWWIDGET_H
#define IC_VIEWWIDGET_H
#include <QDockWidget>

const QString UI_VIEWWIDGET_OBJECT = "ui_viewwidget_object"; 
const QString UI_VIEWWIDGET_RELATION = "ui_viewwidget_relation";
const QString UI_VIEWWIDGET_TIMEAXIS = "ui_viewwidget_timeAxis"; // 时间轴窗口名称
const QString UI_VIEWWIDGET_CHARAC = "ui_viewwidget_charac"; // 特征窗口名称
const QString UI_VIEWWIDGET_RELATIONMANUALCREATE = "ui_viewwidget_relationmanualcreate"; //手动创建关系视图

class IC_ViewWidget: public QDockWidget{
	
public:
	IC_ViewWidget(QWidget* pParent = 0):QDockWidget(pParent) { 
	};
	virtual ~IC_ViewWidget() {};

	/**
     * @brief 获取视图窗口的名称，作为检索的唯一标识
     * @return QString 该视图窗口的名称
     */
	virtual QString name() = 0;

	/**
     * @brief 对窗口进行初始化，可被子类继承
     */
	virtual void init() = 0;
};

#endif