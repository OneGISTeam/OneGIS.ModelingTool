#include "C_ViewObjectClass.h"
#include "QApplication"
#include "QMouseEvent"

C_ViewClass::C_ViewClass(QWidget* pParent)
	:QTreeWidget(pParent)
{
	this->setColumnCount(1);
	this->setHeaderHidden(true);
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	// 设置Item可拖动
	setDragEnabled(true);

	connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showRightMenu(QPoint)));

	QTreeWidgetItem *classItem1 = new QTreeWidgetItem(this, QStringList(QString("飞机")));
	classItem1->setIcon(0,QIcon(":/ModelingTool/Images/class.png"));
	classItem1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	classItem1->setCheckState(0, Qt::Unchecked);
	QTreeWidgetItem *classItem1_1 = new QTreeWidgetItem(classItem1, QStringList(QString("歼击机"))); 
	classItem1_1->setIcon(0,QIcon(":/ModelingTool/Images/class.png"));
	classItem1_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	classItem1_1->setCheckState(0, Qt::Unchecked);
	for (int i = 1; i < 4; i++)
	{
		QString str_tmp = QString::number(i);
		QTreeWidgetItem *classItem1_1_1 = new QTreeWidgetItem(classItem1_1, QStringList(QString("歼击机00").append(str_tmp))); 
		classItem1_1_1->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
		classItem1_1_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
		classItem1_1_1->setCheckState(0, Qt::Unchecked);
		classItem1_1->addChild(classItem1_1_1);
	}
	classItem1->addChild(classItem1_1);

	QTreeWidgetItem *classItem1_2 = new QTreeWidgetItem(classItem1, QStringList(QString("预警机"))); 
	classItem1_2->setIcon(0,QIcon(":/ModelingTool/Images/class.png"));
	classItem1_2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	classItem1_2->setCheckState(0, Qt::Unchecked);
	for (int i = 1; i < 4; i++)
	{
		QString str_tmp = QString::number(i);
		QTreeWidgetItem *classItem1_2_1 = new QTreeWidgetItem(classItem1_2, QStringList(QString("预警机00").append(str_tmp))); 
		classItem1_2_1->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
		classItem1_2_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
		classItem1_2_1->setCheckState(0, Qt::Unchecked);
		classItem1_2->addChild(classItem1_2_1);
	}
	classItem1->addChild(classItem1_2);

	QTreeWidgetItem *classItem1_3 = new QTreeWidgetItem(classItem1, QStringList(QString("轰炸机"))); 
	classItem1_3->setIcon(0,QIcon(":/ModelingTool/Images/class.png"));
	classItem1_3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	classItem1_3->setCheckState(0, Qt::Unchecked);
	for (int i = 1; i < 4; i++)
	{
		QString str_tmp = QString::number(i);
		QTreeWidgetItem *classItem1_3_1 = new QTreeWidgetItem(classItem1_3, QStringList(QString("轰炸机00").append(str_tmp))); 
		classItem1_3_1->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
		classItem1_3_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
		classItem1_3_1->setCheckState(0, Qt::Unchecked);
		classItem1_3->addChild(classItem1_3_1);
	}
	classItem1->addChild(classItem1_3);

	QTreeWidgetItem *classItem2 = new QTreeWidgetItem(this, QStringList(QString("舰船")));
	classItem2->setIcon(0,QIcon(":/ModelingTool/Images/class.png"));
	classItem2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	classItem2->setCheckState(0, Qt::Unchecked);
	QTreeWidgetItem *classItem2_1 = new QTreeWidgetItem(classItem2, QStringList(QString("战列舰"))); 
	classItem2_1->setIcon(0,QIcon(":/ModelingTool/Images/class.png"));
	classItem2_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	classItem2_1->setCheckState(0, Qt::Unchecked);
	for (int i = 1; i < 4; i++)
	{
		QString str_tmp = QString::number(i);
		QTreeWidgetItem *classItem2_1_1 = new QTreeWidgetItem(classItem2_1, QStringList(QString("战列舰00").append(str_tmp))); 
		classItem2_1_1->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
		classItem2_1_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
		classItem2_1_1->setCheckState(0, Qt::Unchecked);
		classItem2_1->addChild(classItem2_1_1);
	}
	classItem2->addChild(classItem2_1);
	QTreeWidgetItem *classItem2_2 = new QTreeWidgetItem(classItem2, QStringList(QString("航空母舰潜艇"))); 
	classItem2_2->setIcon(0,QIcon(":/ModelingTool/Images/class.png"));	
	classItem2_2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	classItem2_2->setCheckState(0, Qt::Unchecked);
	for (int i = 1; i < 4; i++)
	{
		QString str_tmp = QString::number(i);
		QTreeWidgetItem *classItem2_2_1 = new QTreeWidgetItem(classItem2_2, QStringList(QString("航空母舰潜艇00").append(str_tmp))); 
		classItem2_2_1->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
		classItem2_2_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
		classItem2_2_1->setCheckState(0, Qt::Unchecked);
		classItem2_2->addChild(classItem2_2_1);
	}
	classItem2->addChild(classItem2_2);

	QTreeWidgetItem *classItem2_3 = new QTreeWidgetItem(classItem2, QStringList(QString("护卫舰"))); 
	classItem2_3->setIcon(0,QIcon(":/ModelingTool/Images/class.png"));
	classItem2_3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
	classItem2_3->setCheckState(0, Qt::Unchecked);
	for (int i = 1; i < 4; i++)
	{
		QString str_tmp = QString::number(i);
		QTreeWidgetItem *classItem2_3_1 = new QTreeWidgetItem(classItem2_3, QStringList(QString("护卫舰00").append(str_tmp))); 
		classItem2_3_1->setIcon(0,QIcon(":/ModelingTool/Images/object.png"));
		classItem2_3_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
		classItem2_3_1->setCheckState(0, Qt::Unchecked);
		classItem2_3->addChild(classItem2_3_1);
	}
	classItem2->addChild(classItem2_3);

	QList<QTreeWidgetItem *> classItemList;  
	classItemList << classItem1 << classItem2;
	this->insertTopLevelItems(0, classItemList);

}


C_ViewClass::~C_ViewClass(void)
{
	// action 从menu 中remove

/*	delete addChildClassAction;
	delete addClassAction;
	delete editClassAction;
	delete deleteClassAction;
	delete addObjectAction;

	delete m_rightMenu_blankArea;
	delete m_rightMenu_atClassItem;
	delete m_rightMenu_atObjectItem;*/
}

void C_ViewClass::showRightMenu( QPoint pos)
{
	addClassAction = new QAction(tr("添加类"),this);
	addClassAction->setIcon(QIcon(":/ModelingTool/Images/createObjectClass.png"));
	addChildClassAction = new QAction(tr("添加子类"),this);
	addChildClassAction->setIcon(QIcon(":/ModelingTool/Images/createObjectClass.png"));
	addObjectAction = new QAction(tr("添加对象"),this);
	addObjectAction->setIcon(QIcon(":/ModelingTool/Images/createObject.png"));
	editClassAction = new QAction(tr("编辑类"),this);
	editClassAction->setIcon(QIcon(":/ModelingTool/Images/editObjectClass.png"));
	deleteClassAction = new QAction(tr("删除类"),this);
	deleteClassAction->setIcon(QIcon(":/ModelingTool/Images/removeObjectClass.png"));

	QTreeWidgetItem* curItem=this->itemAt(pos);
	if(curItem)
	{
		m_rightMenu_atClassItem =new QMenu(this);
		m_rightMenu_atClassItem->addAction(addChildClassAction);
		m_rightMenu_atClassItem->addAction(addObjectAction);
		m_rightMenu_atClassItem->addAction(editClassAction);
		m_rightMenu_atClassItem->addAction(deleteClassAction);
		m_rightMenu_atClassItem->exec(QCursor::pos());
	}
	else
	{
		m_rightMenu_blankArea =new QMenu(this);
		m_rightMenu_blankArea->addAction(addClassAction);
		m_rightMenu_blankArea->addAction(addObjectAction);
		m_rightMenu_blankArea->exec(QCursor::pos());
	}
}

void C_ViewClass::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		m_dragPosition = event->pos();
		m_dragItem = itemAt(m_dragPosition);
	}
	QTreeWidget::mousePressEvent(event);
}

void C_ViewClass::mouseMoveEvent(QMouseEvent *event)
{
	if(!(event->buttons()&Qt::LeftButton))
		return;
	if((event->pos() - m_dragPosition).manhattanLength() < QApplication::startDragDistance())
		return;
	if(m_dragItem == NULL)
		return;
	QDrag* drag = new QDrag(this);
	QMimeData* mimaData = new QMimeData;
	QByteArray itemData;
	QDataStream dataStream(&itemData,QIODevice::WriteOnly);
	dataStream<<m_dragItem->text(0);
	mimaData->setData("itemObjectClass", itemData);
	drag->setMimeData(mimaData);

	Qt::DropAction resultAction = drag->exec(Qt::MoveAction);
	if(resultAction == Qt::MoveAction)
	{

	}
	QTreeWidget::mouseMoveEvent(event);
}