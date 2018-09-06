#include "C_DialogMergeRule.h"

C_DialogMergeRule::C_DialogMergeRule(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	connect(m_btn_ok, SIGNAL(clicked()), this,SLOT(onBtnOK()));
	connect(m_btn_cancel, SIGNAL(clicked()),this,SLOT(onBtnCancel()));
}

C_DialogMergeRule::~C_DialogMergeRule()
{

}

void C_DialogMergeRule::onBtnOK()
{
	m_bLocation = m_groupBox_pos->isChecked();
	m_bAttribute = m_groupBox_field->isChecked();
	m_bForm = m_groupBox_form->isChecked();
	m_dRangeH = m_doubleSpinBox_H->value();
	m_dRangeW = m_doubleSpinBox_W->value();
	m_strMainAttr = m_comboBox_main->currentText();
	m_strSecondaryAttr = m_comboBox_ass->currentText();
	m_iSimiAttr = m_spinBox_field->value();
	m_iSimiForm[0] = m_spinBox_ll->value();
	m_iSimiForm[1] = m_spinBox_la->value();
	m_iSimiForm[2] = m_spinBox_aa->value();
	accept();
}

void C_DialogMergeRule::onBtnCancel()
{
	reject();
}

void C_DialogMergeRule::setMainAttribute(QStringList listAttr)
{
	m_comboBox_main->addItems(listAttr);
}

void C_DialogMergeRule::setSecondaryAttribute(QStringList listAttr)
{
	m_comboBox_ass->addItems(listAttr);
}

void C_DialogMergeRule::setDefaultValue()
{
	m_groupBox_pos->setChecked(m_bLocation);
	m_groupBox_field->setChecked(m_bAttribute);
	m_groupBox_form->setChecked(m_bForm);
	m_doubleSpinBox_H->setValue(m_dRangeH);
	m_doubleSpinBox_W->setValue(m_dRangeW);
	m_comboBox_main->setCurrentIndex(m_comboBox_main->findText(m_strMainAttr));
	m_comboBox_ass->setCurrentIndex(m_comboBox_ass->findText(m_strSecondaryAttr));
	m_spinBox_field->setValue(m_iSimiAttr);
	m_spinBox_ll->setValue(m_iSimiForm[0]);
	m_spinBox_la->setValue(m_iSimiForm[1]);
	m_spinBox_aa->setValue(m_iSimiForm[2]);

}