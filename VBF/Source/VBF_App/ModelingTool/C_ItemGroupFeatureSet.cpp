#include "C_ItemGroupFeatureSet.h"
#include "QPen"
#include "QPainter"

C_ItemGroupFeatureSet::C_ItemGroupFeatureSet(QString sName)
{
	setFlags(ItemIsMovable|ItemIsSelectable);
	// 当设置为false时，允许子Item处理自己的响应事件
	// setHandlesChildEvents(false);
	m_sName = sName;
	m_pFeatureItem = new C_ItemFeatureSet(sName);
	m_pAttrItem = new C_ItemAttribute("Attribute",E_ItemType::FeatureSetGroup);
	m_pGeoItem = new C_ItemGeometry("Geometry");
	addToGroup(m_pFeatureItem);
	addToGroup(m_pGeoItem);
	addToGroup(m_pAttrItem);
	m_bFoldGeo = m_bFoldAttr = false;
	m_pConnection = NULL;
	setData(0,E_ItemType::FeatureSetGroup);
}


C_ItemGroupFeatureSet::~C_ItemGroupFeatureSet(void)
{
	for (int i = 0;i<m_ListAttrItems.size();i++)
	{
		delete m_ListAttrItems[i];
		m_ListAttrItems[i] = NULL;
	}
	m_ListAttrItems.clear();
	for (int i = 0;i<m_ListGeoItems.size();i++)
	{
		delete m_ListGeoItems[i];
		m_ListGeoItems[i] = NULL;
	}
	m_ListGeoItems.clear();
	delete m_pFeatureItem;
	m_pFeatureItem = NULL;
	delete m_pAttrItem;
	m_pAttrItem = NULL;
	delete m_pGeoItem;
	m_pGeoItem = NULL;
	m_pConnection = NULL;
}

void C_ItemGroupFeatureSet::setAttributeSubitem(const QMap<QString,QString>& mapAttr)
{
	if(m_ListAttrItems.size())
		return;

	QMap<QString,QString>::const_iterator it;
	for (it = mapAttr.begin(); it!=mapAttr.end(); it++)
	{
		C_SubitemAttribute* pSubitem = new C_SubitemAttribute(it.key(),E_ItemType::FeatureSetGroup,it.value());
		m_ListAttrItems.push_back(pSubitem);
		addToGroup(pSubitem);
	}
}

QStringList C_ItemGroupFeatureSet::getAttributeNameList()
{
	QStringList nameList;
	for (int i = 0;i<m_ListAttrItems.size();i++)
	{
		nameList.push_back(m_ListAttrItems[i]->getName());
	}
	return nameList;
}

void C_ItemGroupFeatureSet::setGeometrySubitem(const QMap<QString,QString>& mapGeo)
{
	if(m_ListGeoItems.size())
		return;

	QList<QGraphicsItem*> listItems = childItems();
	for (int i = 0;i<listItems.size();i++)
	{
		removeFromGroup(listItems[i]);
	}
	QMap<QString,QString>::const_iterator it;
	int index = 2;
	for (it = mapGeo.begin();it!=mapGeo.end();it++)
	{
		C_SubitemGeometry* pSubitem = new C_SubitemGeometry(it.key(),it.value());
		m_ListGeoItems.push_back(pSubitem);
		listItems.insert(index,pSubitem);
		index++;
	}
	for (int i = 0;i<listItems.size();i++)
	{
		addToGroup(listItems[i]);
	}
}


void C_ItemGroupFeatureSet::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
	QList<QGraphicsItem*> pListItem = childItems();
	for (int i = 0;i<pListItem.size()-1;i++)
	{
		QPointF center = pListItem[i]->pos();
		int h = pListItem[i]->boundingRect().height();
		pListItem[i+1]->setPos(center.x(), center.y() + h);
	}
	
}

void C_ItemGroupFeatureSet::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
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

	if(m_bFoldGeo != m_pGeoItem->getFoldState())
	{
		if(m_bFoldGeo == true) //形态类型列表展开
		{
			QList<QGraphicsItem*> listItems = childItems();
			for (int i = 0;i<listItems.size();i++)
				removeFromGroup(listItems[i]);
			for(int i = 0,index = 2;i<m_ListGeoItems.size();i++,index++)
			{
				listItems.insert(index,m_ListGeoItems[i]);
				m_ListGeoItems[i]->setVisible(true);
			}
			for (int i = 0;i<listItems.size();i++)
				addToGroup(listItems[i]);
		}
		else	//形态列表关闭
		{
			for(int i = 0;i<m_ListGeoItems.size();i++)
			{
				m_ListGeoItems[i]->setVisible(false);
				removeFromGroup(m_ListGeoItems[i]);
			}
		}
		m_bFoldGeo = m_pGeoItem->getFoldState();
	}
}

QRectF C_ItemGroupFeatureSet::boundingRect() const
{
	return childrenBoundingRect();
}

void C_ItemGroupFeatureSet::setConnection(C_ItemConnection* pConnection)
{
	m_pConnection = pConnection;
}

void C_ItemGroupFeatureSet::clearConnection()
{
	if(m_pConnection != NULL)
	{
		delete m_pConnection;
		m_pConnection = NULL;
	}
}