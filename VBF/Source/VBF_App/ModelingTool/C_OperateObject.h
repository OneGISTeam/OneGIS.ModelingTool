#pragma once
#include <QWidget>
#include "GeneratedFiles/ui_operateobjectwidget.h"

class C_OperateObject: public QWidget,Ui::OperateObjectWidget
{
	Q_OBJECT
public:
	C_OperateObject(QWidget* pParent = 0);
	~C_OperateObject(void);
};

