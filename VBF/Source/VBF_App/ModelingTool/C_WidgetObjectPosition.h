#ifndef C_WIDGETPOSITION_H
#define C_WIDGETPOSITION_H

#include <QDialog>
#include "ui_objectPositionWidget.h"

class C_WidgetObjectPosition : public QDialog, public Ui::ObjectPositionWidget
{
	Q_OBJECT

public:
	C_WidgetObjectPosition(QWidget *parent = 0);
	~C_WidgetObjectPosition();

public slots:
	// ��Ӧʱ���ʽ�ı�
	// ʱ���ʽ�ı��Ҫ�ı�༭����ʱ������뷽ʽ
	void cbTimeFormatChanged(int);
	//��Ӧ�����ʽ�ı�
	void cbPostionFormatChanged(int);

private:
	void setCoulumnHide(int coulumn);
	
};

#endif // C_WIDGETPOSITION_H
