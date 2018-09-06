#pragma once
#include <QDialog>
#include "ui_objectClassExportDialog.h"

class C_DialogObjectClassExport: public QDialog, public Ui::ObjectClassExportDialog
{
	Q_OBJECT
public:
	C_DialogObjectClassExport(QWidget* pParent = 0);
	~C_DialogObjectClassExport(void);
};

