#pragma once
#include <QWidget>
#include "ui_objectBehaviorWidget.h"
#include "C_DialogBehaviorAdd.h"

class C_WidgetObjectBehavior: public QWidget, public Ui::ObjectBehaviorWidget
{
	Q_OBJECT
public:
	C_WidgetObjectBehavior(QWidget* pParent = 0);
	~C_WidgetObjectBehavior(void);

private slots:
	void on_editPublicBehavior_clicked();
	void on_addPrivateBehavior_clicked();
};