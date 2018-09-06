#pragma once
#include <QDialog>
#include "ui_createRelationDialog.h"

class C_DialogRelationCreate: public QDialog, public Ui::CreateRelationDialog
{
	Q_OBJECT
public:
	C_DialogRelationCreate(QWidget* pParent = 0);
	~C_DialogRelationCreate(void);
};

