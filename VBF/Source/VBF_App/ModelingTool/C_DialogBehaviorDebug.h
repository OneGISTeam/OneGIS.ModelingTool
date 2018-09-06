#pragma once
#include <QDialog>
#include "ui_behaviorDebugDialog.h"

class C_DialogBehaviorDebug: public QDialog, public Ui::BehaviorDebugDialog
{
	Q_OBJECT
public:
	C_DialogBehaviorDebug(QWidget* pParent = 0);
	~C_DialogBehaviorDebug(void);
};

