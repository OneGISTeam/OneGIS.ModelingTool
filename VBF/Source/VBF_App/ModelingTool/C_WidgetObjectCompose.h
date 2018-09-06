#pragma once
#include <QWidget>
#include "ui_objectComposeWidget.h"

class C_WidgetObjectCompose: public QWidget, public Ui::ObjectComposeWidget
{
	Q_OBJECT
public:
	C_WidgetObjectCompose(QWidget* pParent = 0);
	~C_WidgetObjectCompose(void);
};

