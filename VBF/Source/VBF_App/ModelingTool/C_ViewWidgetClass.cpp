#include "C_ViewWidgetClass.h"
#include <QVBoxLayout>

C_ViewWidgetClass::C_ViewWidgetClass(QWidget* pParent)
	:IC_ViewWidget(pParent)
{
	m_pViewClass = NULL;
	m_pSearchClass = NULL;
	m_pOperateClass = NULL;
}

C_ViewWidgetClass::~C_ViewWidgetClass(void)
{
}

void C_ViewWidgetClass::init()
{
	this->setWindowTitle(tr("ÀàÊÓÍ¼"));
	this->setWindowIcon(QIcon(":/ModelingTool/Images/objectClassView.png"));

	m_pSearchClass = new C_SearchClass(this);
	m_pViewClass = new C_ViewClass(this);
	m_pOperateClass = new C_OperateClass(this);

	QVBoxLayout* pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pSearchClass);
	pVBoxLayout->addWidget(m_pOperateClass);
	pVBoxLayout->addWidget(m_pViewClass);
	pVBoxLayout->setSpacing(2);
	pVBoxLayout->setMargin(1);
	QWidget* pWidget = new QWidget;
	pWidget->setLayout(pVBoxLayout);
	setWidget(pWidget);
}

QString C_ViewWidgetClass::name()
{
	return UI_VIEWWIDGET_OBJECT;
}

