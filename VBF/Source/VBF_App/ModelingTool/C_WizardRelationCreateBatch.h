#pragma once
#include <QWizard>
#include "C_WizardPageSelectType.h"
#include "C_WizardPageSelectRule.h"
#include "C_WizardPageSetParams.h"

class C_WizardRelationCreateBatch: public QWizard
{
	Q_OBJECT
public:
	C_WizardRelationCreateBatch(QWidget* pParent = 0);
	~C_WizardRelationCreateBatch(void);

private:
	C_WizardPageSelectType* m_pSelectType;
	C_WizardPageSelectRule* m_pSelectRule;
	C_WizardPageSetParams* m_pSetParams;
};

