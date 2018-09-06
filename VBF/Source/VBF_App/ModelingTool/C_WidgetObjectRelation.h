#pragma once
#include <QWidget>
#include "ui_objectRelationWidget.h"

class C_WidgetObjectRelation: public QWidget, public Ui::ObjectRelationWidget
{
	Q_OBJECT
public:
	C_WidgetObjectRelation(QWidget* pParent = 0);
	~C_WidgetObjectRelation(void);
};

