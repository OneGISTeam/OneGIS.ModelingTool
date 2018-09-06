#include "C_DialogFilterRule.h"

C_DialogFilterRule::C_DialogFilterRule(QString sName, QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	m_label_set->setText(m_label_set->text() + sName + " Where");
	init();
}

C_DialogFilterRule::~C_DialogFilterRule()
{

}

void C_DialogFilterRule::init()
{
	connect(m_btn_clear, SIGNAL(clicked()), this, SLOT(onBtnClear()));
	connect(m_btn_save, SIGNAL(clicked()), this, SLOT(onBtnSave()));
	connect(m_listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onDoubleClickItem(QListWidgetItem*)));
	connect(m_btn_1,SIGNAL(clicked()),this,SLOT(onClick_1()));
	connect(m_btn_2,SIGNAL(clicked()),this,SLOT(onClick_2()));
	connect(m_btn_3,SIGNAL(clicked()),this,SLOT(onClick_3()));
	connect(m_btn_4,SIGNAL(clicked()),this,SLOT(onClick_4()));
	connect(m_btn_5,SIGNAL(clicked()),this,SLOT(onClick_5()));
	connect(m_btn_6,SIGNAL(clicked()),this,SLOT(onClick_6()));
	connect(m_btn_7,SIGNAL(clicked()),this,SLOT(onClick_7()));
}

void C_DialogFilterRule::setAttributeList(QStringList listName)
{
	m_listWidget->addItems(listName);
}

void C_DialogFilterRule::onBtnClear()
{
	m_lineEdit->setText("");
	accept();
}

void C_DialogFilterRule::onBtnSave()
{
	accept();
}

void C_DialogFilterRule::onDoubleClickItem(QListWidgetItem* item)
{
	m_lineEdit->insert('['+item->text()+']');
}

void C_DialogFilterRule::onClick_1()
{
	m_lineEdit->insert("=");
}

void C_DialogFilterRule::onClick_2()
{
	m_lineEdit->insert(">");
}

void C_DialogFilterRule::onClick_3()
{
	m_lineEdit->insert("<");
}

void C_DialogFilterRule::onClick_4()
{
	m_lineEdit->insert(">=");
}

void C_DialogFilterRule::onClick_5()
{
	m_lineEdit->insert("<=");
}

void C_DialogFilterRule::onClick_6()
{
	m_lineEdit->insert("&&");
}

void C_DialogFilterRule::onClick_7()
{
	m_lineEdit->insert("||");
}