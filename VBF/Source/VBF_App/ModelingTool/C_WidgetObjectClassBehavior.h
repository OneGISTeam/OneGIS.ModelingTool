#pragma once
#include <QWidget>
#include "ui_objectClassBehaviorWidget.h"
#include "C_DialogBehaviorAdd.h"

class C_WidgetObjectClassBehavior: public QWidget, public Ui::ObjectClassBehaviorWidget
{
	Q_OBJECT
public:
	C_WidgetObjectClassBehavior(QWidget* pParent = 0);
	~C_WidgetObjectClassBehavior(void);

private slots:
	void on_editPublicBehavior_clicked();
	void on_addPrivateBehavior_clicked();
};