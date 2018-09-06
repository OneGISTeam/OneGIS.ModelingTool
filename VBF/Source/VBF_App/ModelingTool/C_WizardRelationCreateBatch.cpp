#include "C_WizardRelationCreateBatch.h"


C_WizardRelationCreateBatch::C_WizardRelationCreateBatch(QWidget* pParent)
	:QWizard(pParent)
{
	m_pSelectType = new C_WizardPageSelectType(this);
	addPage(m_pSelectType);

	m_pSelectRule = new C_WizardPageSelectRule(this);
	addPage(m_pSelectRule);

	m_pSetParams = new C_WizardPageSetParams(this);
	addPage(m_pSetParams);

	setButtonText(QWizard::FinishButton, "���");
	setButtonText(QWizard::NextButton, "��һ��");
	setButtonText(QWizard::BackButton, "��һ��");
	setButtonText(QWizard::CancelButton, "ȡ��");

	this->setWindowTitle(tr("�����ϵ����������"));
}


C_WizardRelationCreateBatch::~C_WizardRelationCreateBatch(void)
{
}
