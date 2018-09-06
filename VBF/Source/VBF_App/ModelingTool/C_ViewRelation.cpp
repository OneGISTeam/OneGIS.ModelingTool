#include "C_ViewRelation.h"
#include <QTreeWidgetItem>
#include <QDragMoveEvent>
#include <QPainter>

C_ViewRelation::C_ViewRelation(QWidget* pParent)
	:QTreeWidget(pParent)
{
	this->setHeaderHidden(true);

	QTreeWidgetItem* pRelationClass = new QTreeWidgetItem;
	pRelationClass->setText(0, tr("协同关系"));
	pRelationClass->setCheckState(0, Qt::Checked);
	pRelationClass->setIcon(0, QIcon(":/ModelingTool/Images/network.png"));

	QTreeWidgetItem* pRelation = new QTreeWidgetItem;
	pRelation->setText(0, tr("直95001->直95003"));
	pRelation->setCheckState(0, Qt::Checked);
	pRelation->setIcon(0, QIcon(":/ModelingTool/Images/relation.png"));
	QTreeWidgetItem* pFrom = new QTreeWidgetItem;
	pFrom->setText(0, tr("起始对象：直95001"));
	pFrom->setIcon(0, QIcon(":/ModelingTool/Images/object.png"));
	pRelation->addChild(pFrom);
	QTreeWidgetItem* pEnd = new QTreeWidgetItem;
	pEnd->setText(0, tr("终止对象：直95001"));
	pEnd->setIcon(0, QIcon(":/ModelingTool/Images/object.png"));
	pRelation->addChild(pEnd);

	QTreeWidgetItem* pRelation2 = new QTreeWidgetItem;
	pRelation2->setText(0, tr("直95004->直95003"));
	pRelation2->setCheckState(0, Qt::Checked);
	pRelation2->setIcon(0, QIcon(":/ModelingTool/Images/relation.png"));
	QTreeWidgetItem* pFrom2 = new QTreeWidgetItem;
	pFrom2->setText(0, tr("起始对象：直95001"));
	pFrom2->setIcon(0, QIcon(":/ModelingTool/Images/object.png"));
	pRelation2->addChild(pFrom2);
	QTreeWidgetItem* pEnd2 = new QTreeWidgetItem;
	pEnd2->setText(0, tr("起始对象：直95001"));
	pEnd2->setIcon(0, QIcon(":/ModelingTool/Images/object.png"));
	pRelation2->addChild(pEnd2);

	pRelationClass->addChild(pRelation);
	pRelationClass->addChild(pRelation2);

	this->addTopLevelItem(pRelationClass);
	
	this->setDragEnabled(true);
	this->setDropIndicatorShown(true);
	//设置拖放模式为移动项目，否则为复制项目
	this->setDragDropMode(QAbstractItemView::InternalMove);
	this->setAttribute(Qt::WA_PaintOutsidePaintEvent);
}


C_ViewRelation::~C_ViewRelation(void)
{
}

void C_ViewRelation::dragMoveEvent( QDragMoveEvent* event )
{
	/*QTreeWidgetItem* pHitItem = itemAt(event->pos());
	event->setDropAction(Qt::MoveAction);

	if(pHitItem){
		QPainter painter(this);
		painter.save();

		QPen pen(palette().base().color());
		pen.setColor(Qt::green);
		painter.setPen(pen);
		painter.drawEllipse(event->pos(), 20, 20);
	}*/
}

void C_ViewRelation::dragEnterEvent( QDragEnterEvent *event )
{

}
