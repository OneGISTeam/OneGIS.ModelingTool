#pragma once
#include <QDialog>
#include "ui_formPartDialog.h"

class C_DialogFormPart: public QDialog, public Ui::FormPartDialog
{
	Q_OBJECT
public:
	C_DialogFormPart(QWidget* pParent = 0);
	~C_DialogFormPart(void);
};

