#include "C_MessageFrame.h"
#include <QHBoxLayout>

C_MessageFrame::C_MessageFrame(QWidget* pParent)
	:QFrame(pParent)
{
	m_pLabel = new QLabel;
	m_pLabel->setText(tr("¾ÍÐ÷"));
	m_pLabel->setMinimumWidth(300);

	QHBoxLayout* pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->addWidget(m_pLabel);
	pHBoxLayout->setSpacing(0);
	pHBoxLayout->setMargin(0);
	this->setLayout(pHBoxLayout);
}


C_MessageFrame::~C_MessageFrame(void)
{
}

void C_MessageFrame::setMessage( QString msg )
{
	m_msg = msg;
	m_pLabel->setText(m_msg);
}
