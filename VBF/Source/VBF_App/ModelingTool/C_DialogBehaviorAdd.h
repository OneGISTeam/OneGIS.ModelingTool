#pragma once
#include <QDialog>
#include "ui_addBehaviorDialog.h"

class C_DialogBehaviorAdd: public QDialog, public Ui::addBehaviorDialog
{
	Q_OBJECT
public:
	C_DialogBehaviorAdd(QWidget* pParent = 0);
	~C_DialogBehaviorAdd(void);
};