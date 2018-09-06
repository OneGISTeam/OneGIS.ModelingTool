#pragma once
#include <QWidget>
#include "ui_objectAttributeWidget.h"

class C_WidgetObjectAttribute: public QWidget, public Ui::ObjectAttributeWidget
{
	Q_OBJECT
public:
	C_WidgetObjectAttribute(QWidget* pParent = 0);
	~C_WidgetObjectAttribute(void);
};
