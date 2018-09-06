#include "C_ViewWidgetRelation.h"


C_ViewWidgetRelation::C_ViewWidgetRelation(QWidget* pParent)
	:IC_ViewWidget(pParent)
{
	m_pSearcherRelation = 0;
}


C_ViewWidgetRelation::~C_ViewWidgetRelation(void)
{
}

QString C_ViewWidgetRelation::name()
{
	return UI_VIEWWIDGET_RELATION;
}

void C_ViewWidgetRelation::init()
{
	this->setWindowTitle(tr("¹ØÏµÊÓÍ¼"));
	this->setWindowIcon(QIcon(":/ModelingTool/Images/relationView.png"));

	m_pSearcherRelation = new C_SearcherRelation(this);
	m_pOperateRelation = new C_OperateRelation(this);
	m_pViewRelation = new C_ViewRelation(this);

	QVBoxLayout* pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pSearcherRelation);
	pVBoxLayout->addWidget(m_pOperateRelation);
	pVBoxLayout->addWidget(m_pViewRelation);

	pVBoxLayout->setSpacing(2);
	pVBoxLayout->setMargin(1);

	QWidget* pWidget = new QWidget;
	pWidget->setLayout(pVBoxLayout);
	setWidget(pWidget);
}
