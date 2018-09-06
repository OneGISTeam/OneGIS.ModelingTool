#include "C_ItemGroupObjectClass.h"
#include "QPen"
#include "QPainter"

C_ItemGroupObjectClass::C_ItemGroupObjectClass(QString sName)
{
	setFlags(ItemIsMovable|ItemIsSelectable);
	// 当设置为false时，允许子Item处理自己的响应事件
	// setHandlesChildEvents(false);
	m_sName = sName;
	m_pObjClassItem = new C_ItemObjectClass(sName);
	m_pPosItem = new C_ItemPosition("Position");
	m_pAttrItem = new C_ItemAttribute("Attribute",E_ItemType::ObjectClassGroup);
	m_pFormItem = new C_ItemForm("Form");
	addToGroup(m_pObjClassItem);
	addToGroup(m_pPosItem);
	addToGroup(m_pFormItem);
	addToGroup(m_pAttrItem);
	m_bFoldForm = m_bFoldAttr = false;
	setData(0,E_ItemType::ObjectClassGroup);
}


C_ItemGroupObjectClass::~C_ItemGroupObjectClass(void)
{
	for (int i = 0;i<m_ListAttrItems.size();i++)
	{
		delete m_ListAttrItems[i];
		m_ListAttrItems[i] = NULL;
	}
	m_ListAttrItems.clear();
	for (int i = 0;i<m_ListFormItems.size();i++)
	{
		delete m_ListFormItems[i];
		m_ListFormItems[i] = NULL;
	}
	m_ListFormItems.clear();
	for (int i = 0;i<m_ListConnection.size();i++)
	{
		m_ListConnection[i] = NULL;
	}
	m_ListConnection.clear();
	delete m_pAttrItem;
	m_pAttrItem = NULL;
	delete m_pFormItem;
	m_pFormItem = NULL;
	delete m_pPosItem;
	m_pPosItem = NULL;
}

void C_ItemGroupObjectClass::setAttributeSubitem(const QMap<QString,QString>& mapAttr)
{
	if(m_ListAttrItems.size())
		return;

	QMap<QString,QString>::const_iterator it;
	for (it = mapAttr.begin(); it!=mapAttr.end(); it++)
	{
		C_SubitemAttribute* pSubitem = new C_SubitemAttribute(it.key(),E_ItemType::ObjectClassGroup,it.value());
		m_ListAttrItems.push_back(pSubitem);
		addToGroup(pSubitem);
	}
}


void C_ItemGroupObjectClass::setFormSubitem(const QMap<QString,QString>& mapForm)
{
	if(m_ListFormItems.size())
		return;

	QList<QGraphicsItem*> listItems = childItems();
	for (int i = 0;i<listItems.size();i++)
	{
		removeFromGroup(listItems[i]);
	}
	QMap<QString,QString>::const_iterator it;
	int index = 3;
	for (it = mapForm.begin();it!=mapForm.end();it++)
	{
		C_SubitemForm* pSubitem = new C_SubitemForm(it.key(),it.value());
		m_ListFormItems.push_back(pSubitem);
		listItems.insert(index,pSubitem);
		index++;
	}
	for (int i = 0;i<listItems.size();i++)
	{
		addToGroup(listItems[i]);
	}
}


void C_ItemGroupObjectClass::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	QList<QGraphicsItem*> pListItem = childItems();
	
	for (int i = 0;i<pListItem.size()-1;i++)
	{
		QPointF center = pListItem[i]->pos();
		int h = pListItem[i]->boundingRect().height();
		pListItem[i+1]->setPos(center.x(), center.y() + h);
	}
	/*if(isSelected()){
	QRectF rect = boundingRect();
	pPainter->setBrush(QBrush(QColor(0,0,0,0)));
	pPainter->setPen(Qt::red);
	pPainter->drawRect(rect);
	}*/
}

void C_ItemGroupObjectClass::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	if(m_bFoldAttr != m_pAttrItem->getFoldState())
	{
		if(m_bFoldAttr == true)	//属性列表打开
		{
			for(int i = 0;i<m_ListAttrItems.size();i++)
			{
				addToGroup(m_ListAttrItems[i]);
				m_ListAttrItems[i]->setVisible(true);
			}
		}
		else	//属性列表关闭
		{
			for (int i = 0;i<m_ListAttrItems.size();i++)
			{
				m_ListAttrItems[i]->setVisible(false);
				removeFromGroup(m_ListAttrItems[i]);
			}
		}
		m_bFoldAttr = m_pAttrItem->getFoldState();
	}

	if(m_bFoldForm != m_pFormItem->getFoldState())
	{
		if(m_bFoldForm == true) //形态类型列表展开
		{
			QList<QGraphicsItem*> listItems = childItems();
			for (int i = 0;i<listItems.size();i++)
				removeFromGroup(listItems[i]);
			for(int i = 0,index = 3;i<m_ListFormItems.size();i++,index++)
			{
				listItems.insert(index,m_ListFormItems[i]);
				m_ListFormItems[i]->setVisible(true);
			}
			for (int i = 0;i<listItems.size();i++)
				addToGroup(listItems[i]);
		}
		else	//形态列表关闭
		{
			for(int i = 0;i<m_ListFormItems.size();i++)
			{
				m_ListFormItems[i]->setVisible(false);
				removeFromGroup(m_ListFormItems[i]);
			}
		}
		m_bFoldForm = m_pFormItem->getFoldState();
	}
}

QRectF C_ItemGroupObjectClass::boundingRect() const
{
	return childrenBoundingRect();
}

void C_ItemGroupObjectClass::addConnection(C_ItemConnection* pConnection)
{
	if(pConnection!=NULL)
		m_ListConnection.push_back(pConnection);
}

void C_ItemGroupObjectClass::clearConnection()
{
	for (int i = 0;i<m_ListConnection.size();i++)
	{
		if(m_ListConnection[i] == NULL)
			m_ListConnection.removeAt(i);
	}
}