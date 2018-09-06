#include "C_DialogBehaviorViewer.h"
#include "QTreeWidgetItem"

C_DialogBehaviorViewer::C_DialogBehaviorViewer(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	init();
}

C_DialogBehaviorViewer::~C_DialogBehaviorViewer()
{

}

void C_DialogBehaviorViewer::init()
{
	connect(m_btn_ok, SIGNAL(clicked()), this, SLOT(onBtnOK()));
	//QTreeWidgetItem* firstItem = new QTreeWidgetItem()
	//QTreeWidgetItem* firstItem = new QTreeWidgetItem()
	//m_treeWidget->addItem(firstItem);
	//firstItem->addChildren()
}

void C_DialogBehaviorViewer::onBtnOK()
{
	accept();
}