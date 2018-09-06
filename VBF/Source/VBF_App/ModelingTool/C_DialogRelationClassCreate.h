#pragma once
#include <QDialog>
#include "ui_createRelationClassDialog.h"

class C_DialogRelationClassCreate: public QDialog, public Ui::CreateRelationClassDialog
{
	Q_OBJECT
public:
	C_DialogRelationClassCreate(QWidget* pParent = 0);
	~C_DialogRelationClassCreate(void);
};

