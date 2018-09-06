#include "C_DialogObjectCreate.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

C_DialogObjectCreate::C_DialogObjectCreate(QWidget* pParent)
	:QDialog(pParent)
{
	setupUi(this);
	m_pWidgetBasicInfo = new C_WidgetObjectBasicInfo;
	m_pWidgetReference = new C_WidgetObjectReference;
	m_pWidgetPostion = new C_WidgetObjectPosition;
	m_pWidgetAttribute = new C_WidgetObjectAttribute;
	m_pWidgetForm = new C_WidgetObjectForm;
	m_pWidgetCompose = new C_WidgetObjectCompose;
	m_pWidgetRelation = new C_WidgetObjectRelation;
	m_pWidgetBehavior = new C_WidgetObjectBehavior;
	connect(this->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(on_currentRow_changed(int)));
	//默认第0页是“基本信息”
	this->listWidget->setCurrentRow(0);
	
}


C_DialogObjectCreate::~C_DialogObjectCreate(void)
{

}

void C_DialogObjectCreate::on_currentRow_changed( int rowCount )
{
	clearWidgets();
	switch (rowCount)
	{
	case 0:
		horizontalLayout->addWidget(m_pWidgetBasicInfo);
		break;
	case 1:
		horizontalLayout->addWidget(m_pWidgetReference);
		break;
	case 2:
		horizontalLayout->addWidget(m_pWidgetPostion);
		break;
	case 3: 
		horizontalLayout->addWidget(m_pWidgetAttribute);
		break;
	case 4:
		horizontalLayout->addWidget(m_pWidgetForm);
		break;
	case 5:
		horizontalLayout->addWidget(m_pWidgetCompose);
		break;
	case 6:
		horizontalLayout->addWidget(m_pWidgetBehavior);
		break;
	case 7:
		horizontalLayout->addWidget(m_pWidgetRelation);
		break;
	}
}

void C_DialogObjectCreate::clearWidgets()
{
	while(horizontalLayout->count()){
		QWidget *p=this->horizontalLayout->itemAt(0)->widget();
		p->setParent (NULL);
		this->horizontalLayout->removeWidget(p);
	};
	horizontalLayout->addWidget(listWidget);
}
