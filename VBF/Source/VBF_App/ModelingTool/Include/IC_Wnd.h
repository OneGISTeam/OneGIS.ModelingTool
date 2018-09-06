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
     * @brief ��ȡ��ʾ���ڵ����ƣ���Ϊ������Ψһ��ʶ
     * @return QString ����ʾ���ڵ�����
     */
	virtual QString name() = 0;

	/**
     * @brief �Դ��ڽ��г�ʼ�����ɱ�����̳�
     */
	virtual void init() = 0;

	/**
     * @brief ÿ����ʾ���ڿ��Թ�����ͬ��״̬����ͨ���ýӿڻ�ȡ״̬��
	 * @return ������ʾ������������״̬��
     */
	virtual QWidget* statusWidget() = 0;
};

#endif