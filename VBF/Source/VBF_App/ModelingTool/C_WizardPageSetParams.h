#pragma once
#include <QWizardPage>
#include "ui_setParamsWizardPage.h"

class C_WizardPageSetParams: public QWizardPage, public Ui::SetParamsWizardPage
{
	Q_OBJECT
public:
	C_WizardPageSetParams(QWidget* pParent = 0);
	~C_WizardPageSetParams(void);
};

