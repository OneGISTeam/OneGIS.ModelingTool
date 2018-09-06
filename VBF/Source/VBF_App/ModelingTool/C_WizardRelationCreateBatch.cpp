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

	setButtonText(QWizard::FinishButton, "完成");
	setButtonText(QWizard::NextButton, "下一步");
	setButtonText(QWizard::BackButton, "上一步");
	setButtonText(QWizard::CancelButton, "取消");

	this->setWindowTitle(tr("对象关系批量创建向导"));
}


C_WizardRelationCreateBatch::~C_WizardRelationCreateBatch(void)
{
}
