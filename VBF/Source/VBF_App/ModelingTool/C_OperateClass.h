#pragma once
#include <QWidget>
#include "GeneratedFiles/ui_operateclasswidget.h"

class C_OperateClass: public QWidget,Ui::OperateClassWidget
{
	Q_OBJECT
public:
	C_OperateClass(QWidget* pParent = 0);
	~C_OperateClass(void);
};