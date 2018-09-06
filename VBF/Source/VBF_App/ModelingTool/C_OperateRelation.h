#pragma once
#include <QWidget>
#include "ui_operaterelationwidget.h"

class C_OperateRelation: public QWidget, public Ui::OperateRelationWidget
{
public:
	C_OperateRelation(QWidget* pParent = 0);
	~C_OperateRelation(void);
};

