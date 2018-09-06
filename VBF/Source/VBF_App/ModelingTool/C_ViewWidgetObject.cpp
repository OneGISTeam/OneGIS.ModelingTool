#include "C_ViewWidgetObject.h"
#include <QVBoxLayout>

C_ViewWidgetObject::C_ViewWidgetObject(QWidget* pParent)
	:IC_ViewWidget(pParent)
{
	m_pViewObject = NULL;
	m_pSearcherObject = NULL;
	m_pOperatorObject = NULL;
}


C_ViewWidgetObject::~C_ViewWidgetObject(void)
{
}

void C_ViewWidgetObject::init()
{
	this->setWindowTitle(tr("¶ÔÏóÊÓÍ¼"));
	this->setWindowIcon(QIcon(":/ModelingTool/Images/objectView.png"));

	m_pSearcherObject = new C_SearcherObject(this);
	m_pViewObject = new C_ViewObject(this);
	m_pOperatorObject = new C_OperateObject(this);

	QVBoxLayout* pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pSearcherObject);
	pVBoxLayout->addWidget(m_pOperatorObject);
	pVBoxLayout->addWidget(m_pViewObject);
	pVBoxLayout->setSpacing(2);
	pVBoxLayout->setMargin(1);
	QWidget* pWidget = new QWidget;
	pWidget->setLayout(pVBoxLayout);
	setWidget(pWidget);
}

QString C_ViewWidgetObject::name()
{
	return UI_VIEWWIDGET_OBJECT;
}
