#pragma once
#include <QWidget>
#include "ui_objectClassBasicinfoWidget.h"
class C_WidgetObjectClassBasicInfo: public QWidget, public Ui::ObjectClassBasicInfoWidget
{
	Q_OBJECT
public:
	C_WidgetObjectClassBasicInfo(QWidget* pParent = 0);
	~C_WidgetObjectClassBasicInfo(void);
};
