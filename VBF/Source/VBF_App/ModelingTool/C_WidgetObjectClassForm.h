#pragma once
#include <QWidget>
#include "ui_objectClassFormWidget.h"

class C_WidgetObjectClassForm: public QWidget, public Ui::ObjectClassFormWidget
{
	Q_OBJECT
public:
	C_WidgetObjectClassForm(QWidget* pParent = 0);
	~C_WidgetObjectClassForm(void);

private slots:
	void on_editPublicFormPart_clicked();
	void on_editPrivateFormPart_clicked();
};