#include "C_ViewObject.h"


C_ViewObject::C_ViewObject(QWidget* pParent)
	:QTreeWidget(pParent)
{
	this->setColumnCount(1);
	this->setHeaderHidden(true);
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showRightMenu(QPoint)));

	QTreeWidgetItem *objectItem1 = new QTreeWidgetItem(this, QStringList(QString("歼击机001")));
	objectItem1->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
	objectItem1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	objectItem1->setCheckState(0, Qt::Unchecked);
	QTreeWidgetItem *objectItem1_1 = new QTreeWidgetItem(objectItem1, QStringList(QString("机翼"))); 
	objectItem1_1->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
	objectItem1_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	objectItem1_1->setCheckState(0, Qt::Unchecked);
	objectItem1->addChild(objectItem1_1);
	QTreeWidgetItem *objectItem1_2 = new QTreeWidgetItem(objectItem1, QStringList(QString("机身"))); 
	objectItem1_2->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
	objectItem1_2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	objectItem1_2->setCheckState(0, Qt::Unchecked);
	objectItem1->addChild(objectItem1_2);
	QTreeWidgetItem *objectItem1_3 = new QTreeWidgetItem(objectItem1, QStringList(QString("螺旋桨"))); 
	objectItem1_3->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
	objectItem1_3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	objectItem1_3->setCheckState(0, Qt::Unchecked);
	objectItem1->addChild(objectItem1_3);

	QTreeWidgetItem *objectItem2 = new QTreeWidgetItem(this, QStringList(QString("歼击机002")));
	objectItem2->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
	objectItem2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	objectItem2->setCheckState(0, Qt::Unchecked);
	QTreeWidgetItem *objectItem2_1 = new QTreeWidgetItem(objectItem2, QStringList(QString("机翼"))); 
	objectItem2_1->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
	objectItem2_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	objectItem2_1->setCheckState(0, Qt::Unchecked);
	objectItem2->addChild(objectItem2_1);
	QTreeWidgetItem *objectItem2_2 = new QTreeWidgetItem(objectItem2, QStringList(QString("机身"))); 
	objectItem2_2->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
	objectItem2_2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	objectItem2_2->setCheckState(0, Qt::Unchecked);
	objectItem2->addChild(objectItem2_2);
	QTreeWidgetItem *objectItem2_3 = new QTreeWidgetItem(objectItem2, QStringList(QString("螺旋桨"))); 
	objectItem2_3->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
	objectItem2_3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	objectItem2_3->setCheckState(0, Qt::Unchecked);
	objectItem2->addChild(objectItem2_3);

	QList<QTreeWidgetItem *> objectItemList;  
	objectItemList << objectItem1 << objectItem2;
	this->insertTopLevelItems(0, objectItemList);

	//QVariant var0(0);
	//objectItem1->setData(0,Qt::UserRole,var0);
}


C_ViewObject::~C_ViewObject(void)
{
}

void  C_ViewObject::showRightMenu(QPoint pos)
{
	addObjectAction = new QAction(tr("添加对象"),this);
	addObjectAction->setIcon(QIcon(":/ModelingTool/Images/createObject.png"));
	addChildObjectAction = new QAction(tr("添加子对象"),this);
	addChildObjectAction->setIcon(QIcon(":/ModelingTool/Images/createObject.png"));
	editObjectAction = new QAction(tr("编辑对象"),this);
	editObjectAction->setIcon(QIcon(":/ModelingTool/Images/editObject.png"));
	deleteObjectAction = new QAction(tr("删除对象"),this);
	deleteObjectAction->setIcon(QIcon(":/ModelingTool/Images/removeObject.png"));

	QTreeWidgetItem* curItem=this->itemAt(pos);
	if(curItem)
	{
		m_rightMenu_atItem =new QMenu(this);
		m_rightMenu_atItem->addAction(addChildObjectAction);
		m_rightMenu_atItem->addAction(editObjectAction);
		m_rightMenu_atItem->addAction(deleteObjectAction);
		m_rightMenu_atItem->exec(QCursor::pos());
	}
	else
	{
		m_rightMenu_blankArea =new QMenu(this);
		m_rightMenu_blankArea->addAction(addObjectAction);
		m_rightMenu_blankArea->exec(QCursor::pos());
	}
}