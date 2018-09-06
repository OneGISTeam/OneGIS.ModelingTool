#ifndef IC_VIEWWIDGET_H
#define IC_VIEWWIDGET_H
#include <QDockWidget>

const QString UI_VIEWWIDGET_OBJECT = "ui_viewwidget_object"; 
const QString UI_VIEWWIDGET_RELATION = "ui_viewwidget_relation";
const QString UI_VIEWWIDGET_TIMEAXIS = "ui_viewwidget_timeAxis"; // ʱ���ᴰ������
const QString UI_VIEWWIDGET_CHARAC = "ui_viewwidget_charac"; // ������������
const QString UI_VIEWWIDGET_RELATIONMANUALCREATE = "ui_viewwidget_relationmanualcreate"; //�ֶ�������ϵ��ͼ

class IC_ViewWidget: public QDockWidget{
	
public:
	IC_ViewWidget(QWidget* pParent = 0):QDockWidget(pParent) { 
	};
	virtual ~IC_ViewWidget() {};

	/**
     * @brief ��ȡ��ͼ���ڵ����ƣ���Ϊ������Ψһ��ʶ
     * @return QString ����ͼ���ڵ�����
     */
	virtual QString name() = 0;

	/**
     * @brief �Դ��ڽ��г�ʼ�����ɱ�����̳�
     */
	virtual void init() = 0;
};

#endif