#pragma once
#include <QWizardPage>
#include "ui_selectRuleWizardPage.h"

class C_WizardPageSelectRule: public QWizardPage, public Ui::SelectRuleWizardPage
{
	Q_OBJECT
public:
	C_WizardPageSelectRule(QWidget* pParent = 0);
	~C_WizardPageSelectRule(void);
};

