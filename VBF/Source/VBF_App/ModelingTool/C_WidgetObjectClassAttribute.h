#pragma once
#include <QWidget>
#include "ui_objectClassAttributeWidget.h"

class C_WidgetObjectClassAttribute: public QWidget, public Ui::ObjectClassAttributeWidget
{
	Q_OBJECT
public:
	C_WidgetObjectClassAttribute(QWidget* pParent = 0);
	~C_WidgetObjectClassAttribute(void);
};
