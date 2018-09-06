#pragma once
#include <QWizardPage>
#include "ui_selectTypeWizardPage.h"

class C_WizardPageSelectType: public QWizardPage, public Ui::SelectTypeWizardPage
{
	Q_OBJECT
public:
	C_WizardPageSelectType(QWidget* pParent = 0);
	~C_WizardPageSelectType(void);
};

