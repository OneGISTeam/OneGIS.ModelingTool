#pragma once
#include <QWidget>
#include "ui_objectClassReferenceWidget.h"

class C_WidgetObjectClassReference: public QWidget, public Ui::ObjectClassReferenceWidget
{
	Q_OBJECT
public:
	C_WidgetObjectClassReference(QWidget* pParent = 0);
	~C_WidgetObjectClassReference(void);
};
