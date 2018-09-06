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
	// 响应时间格式改变
	// 时间格式改变后，要改变编辑框中时间的输入方式
	void cbTimeFormatChanged(int);
	//响应坐标格式改变
	void cbPostionFormatChanged(int);

private:
	void setCoulumnHide(int coulumn);
	
};

#endif // C_WIDGETPOSITION_H
