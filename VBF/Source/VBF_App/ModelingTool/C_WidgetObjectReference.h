#pragma once
#include <QWidget>
#include "ui_objectReferenceWidget.h"

class C_WidgetObjectReference: public QWidget, public Ui::ObjectReferenceWidget
{
	Q_OBJECT
public:
	C_WidgetObjectReference(QWidget* pParent = 0);
	~C_WidgetObjectReference(void);
};

