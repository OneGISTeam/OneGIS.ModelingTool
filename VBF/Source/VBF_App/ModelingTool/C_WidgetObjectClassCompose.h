#pragma once
#include "ui_objectClassComposeWidget.h"
#include <QWidget>

class C_WidgetObjectClassCompose: public QWidget, public Ui::ObjectClassComposeWidget
{
	Q_OBJECT
public:
	C_WidgetObjectClassCompose(QWidget* pParent = 0);
	~C_WidgetObjectClassCompose(void);
};

