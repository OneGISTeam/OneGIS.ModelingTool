#include "C_DialogObjectClassCreate.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

C_DialogObjectClassCreate::C_DialogObjectClassCreate(QWidget* pParent)
	:QDialog(pParent)
{
	setupUi(this);
	m_pWidgetObjectClassBasicInfo = new C_WidgetObjectClassBasicInfo;
	m_pWidgetObjectClassReference = new C_WidgetObjectClassReference;
	m_pWidgetObjectClassAttribute = new C_WidgetObjectAttribute;
	m_pWidgetObjectClassForm = new C_WidgetObjectClassForm;
	m_pWidgetObjectClassCompose = new C_WidgetObjectClassCompose;
	m_pWidgetObjectClassBehavior = new C_WidgetObjectClassBehavior;

	connect(this->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(on_currentRow_changed(int)));
	//默认第0页是“基本信息”
	this->listWidget->setCurrentRow(0);
	
}


C_DialogObjectClassCreate::~C_DialogObjectClassCreate(void)
{

}

void C_DialogObjectClassCreate::on_currentRow_changed( int rowCount )
{
	clearWidgets();
	switch (rowCount)
	{
	case 0:
		horizontalLayout->addWidget(m_pWidgetObjectClassBasicInfo);
		break;
	case 1:
		horizontalLayout->addWidget(m_pWidgetObjectClassReference);
		break;
	case 2:
		horizontalLayout->addWidget(m_pWidgetObjectClassAttribute);
		break;
	case 3: 
		horizontalLayout->addWidget(m_pWidgetObjectClassForm);
		break;
	case 4:
		horizontalLayout->addWidget(m_pWidgetObjectClassCompose);
		break;
	case 5:
		horizontalLayout->addWidget(m_pWidgetObjectClassBehavior);
		break;
	}
}

void C_DialogObjectClassCreate::clearWidgets()
{
	while(horizontalLayout->count()){
		QWidget *p=this->horizontalLayout->itemAt(0)->widget();
		p->setParent (NULL);
		this->horizontalLayout->removeWidget(p);
	};
	horizontalLayout->addWidget(listWidget);
}
