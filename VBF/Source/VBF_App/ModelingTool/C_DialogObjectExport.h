#pragma once
#include <QDialog>
#include "ui_objectExportDialog.h"

class C_DialogObjectExport: public QDialog, public Ui::ObjectExportDialog
{
	Q_OBJECT
public:
	C_DialogObjectExport(QWidget* pParent = 0);
	~C_DialogObjectExport(void);

};

