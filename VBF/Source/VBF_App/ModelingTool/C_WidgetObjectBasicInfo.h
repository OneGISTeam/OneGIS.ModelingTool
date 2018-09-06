#pragma once
#include <QWidget>
#include "ui_objectBasicinfoWidget.h"
class C_WidgetObjectBasicInfo: public QWidget, public Ui::ObjectBasicInfoWidget
{
	Q_OBJECT
public:
	C_WidgetObjectBasicInfo(QWidget* pParent = 0);
	~C_WidgetObjectBasicInfo(void);
};

