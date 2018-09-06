#pragma once
#include <QWidget>
#include "ui_objectFormWidget.h"

class C_WidgetObjectForm: public QWidget, public Ui::ObjectFormWidget
{
	Q_OBJECT
public:
	C_WidgetObjectForm(QWidget* pParent = 0);
	~C_WidgetObjectForm(void);

private slots:
	void on_editPublicFormPart_clicked();
	void on_editPrivateFormPart_clicked();
};

