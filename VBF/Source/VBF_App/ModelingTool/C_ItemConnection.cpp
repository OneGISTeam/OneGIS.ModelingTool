#include "C_ItemConnection.h"
#include <QPen>
#include <QPainter>
#include "QMessageBox"
#include <QDir>
#include "QtXml"
#include "QProgressDialog"
#include "QMessageBox"
#include "C_ItemGroupFeatureSet.h"
#include "C_ItemGroupObjectClass.h"

C_ItemConnection::C_ItemConnection(C_ItemFeatureSet* pFromItem, C_ItemObjectClass* pToItem)
{
	m_pFromDataItem = pFromItem;
	m_pToClassItem = pToItem;
	m_color = Qt::black;

	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setPen(QPen(m_color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	this->setData(0, QVariant(E_ItemType::Connection));
	
	setToolTip("可编辑或删除过滤规则");
	m_bHasfilterRule = false;
	m_pFilterDlg = NULL;
}


C_ItemConnection::~C_ItemConnection(void)
{
	if(m_pFilterDlg != NULL)
	{
		delete m_pFilterDlg;
		m_pFilterDlg = NULL;
	}
	for (int i = 0;i<m_ListMatchLines.size();i++)
	{
		delete m_ListMatchLines[i];
		m_ListMatchLines[i] = NULL;
	}
	for (int i = 0;i<m_ListMapLines.size();i++)
	{
		delete m_ListMapLines[i];
		m_ListMapLines[i] = NULL;
	}
	m_pFromDataItem = NULL;
	m_pToClassItem = NULL;
}

C_ItemGroupFeatureSet* C_ItemConnection::getFeatureSetItemGroup()
{
	return static_cast<C_ItemGroupFeatureSet*>(m_pFromDataItem->parentItem());
}

C_ItemGroupObjectClass* C_ItemConnection::getObjectClassItemGroup()
{
	return static_cast<C_ItemGroupObjectClass*>(m_pToClassItem->parentItem());
}

void C_ItemConnection::setColor( const QColor& color )
{
	m_color = color;
}

QColor C_ItemConnection::getColor() const
{
	return m_color;
}

C_ItemMatch* C_ItemConnection::createMatchItem(C_ItemFeatureSet* pMain, C_ItemFeatureSet* pSecondary)
{
	bool bExisted = false;
	for (int i = 0;i<m_ListMatchLines.size();i++)
	{
		C_ItemFeatureSet* p1 = m_ListMatchLines[i]->getMainDataItem();
		C_ItemFeatureSet* p2 = m_ListMatchLines[i]->getSecondaryDataItem();
		if((p1->getID() == pMain->getID())&&(p2->getID() == pSecondary->getID()))
		{
			bExisted = true;
			break;
		}
	}
	if(bExisted)
		return NULL;
	else
	{
		C_ItemMatch *pMatchItem = new C_ItemMatch(pMain, pSecondary);
		m_ListMatchLines.push_back(pMatchItem);
		return pMatchItem;
	}
}

C_ItemMap* C_ItemConnection::createMapItem(QGraphicsItem* pDataItem, QGraphicsItem* pObjClassItem)
{
	bool bExisted = false;
	E_ItemType eType1 = E_ItemType(pDataItem->data(0).toInt());
	E_ItemType eType2 = E_ItemType(pObjClassItem->data(0).toInt());
	bool bMatched = false;
	if(eType1 == E_ItemType::SubGeometry)
	{
		if((eType2 == E_ItemType::Position)||(eType2 == E_ItemType::SubForm))
			bMatched = true;
	}
	else if((eType1 == E_ItemType::SubAttribute)&&(eType2 == E_ItemType::SubAttribute))
		bMatched = true;
	if(bMatched)
	{
		AC_ItemGraphic* p1 = static_cast<AC_ItemGraphic*>(pDataItem);
		AC_ItemGraphic* p2 = static_cast<AC_ItemGraphic*>(pObjClassItem);
		for (int i = 0;i<m_ListMapLines.size();i++)
		{
			AC_ItemGraphic* p3 = m_ListMapLines[i]->getDataItem();
			AC_ItemGraphic* p4 = m_ListMapLines[i]->getObjClassItem();
			if((p1->getID() == p3->getID())||(p2->getID() == p4->getID()))
			{
				bExisted = true;
				break;
			}
		}
		if(bExisted)
			return NULL;
		else
		{
			C_ItemMap *pMapItem = new C_ItemMap(p1,p2);
			m_ListMapLines.push_back(pMapItem);
			return pMapItem;
		}
	}
	else
		return NULL;
}

void C_ItemConnection::updateLink()
{
	QLineF line(mapFromItem(m_pFromDataItem, 0, 0), mapFromItem(m_pToClassItem, 0, 0));
	setLine(line);
}

void C_ItemConnection::paint( QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *widget /*= 0*/ )
{
	if(m_pFromDataItem->collidesWithItem(m_pToClassItem))
		return;
	QPen linkPen = this->pen();
	if(isSelected()){
		linkPen.setColor(Qt::red);
		pPainter->setBrush(Qt::red);
	}else{
		linkPen.setColor(m_color);
		pPainter->setBrush(m_color);
	}
	qreal arrowSize = 20;
	pPainter->setPen(linkPen);

	// 直接采用垂直边中点
	QPointF p1 = m_pFromDataItem->scenePos();
	QPointF p2 = m_pToClassItem->scenePos();
	int w1 = m_pFromDataItem->boundingRect().width();
	int w2 = m_pToClassItem->boundingRect().width();

	QPointF ptEnd,ptStart;
	if(p1.x()<=p2.x())
	{
		ptStart = QPointF(p1.x() + w1 / 2.0, p1.y());
		ptEnd = QPointF(p2.x() - w2 / 2.0, p2.y());
	}
	else
	{
		ptStart = QPointF(p1.x() - w1 / 2.0, p1.y());
		ptEnd = QPointF(p2.x() + w2 / 2.0, p2.y());
	}
	setLine(QLineF(ptEnd, ptStart));

	// 设置箭头方向
	double angle = ::acos(line().dx() / line().length());
	if (line().dy() >= 0)
		angle = (Pi * 2) - angle;

	QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
		cos(angle + Pi / 3) * arrowSize);
	QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
		cos(angle + Pi - Pi / 3) * arrowSize);

	m_arrowHead.clear();
	m_arrowHead << line().p1() << arrowP1 << arrowP2;

	// 绘制中心圆
	if(m_bHasfilterRule)
		m_centerCircle.setRect(ptStart.x()/2+ptEnd.x()/2-10, ptStart.y()/2+ptEnd.y()/2-10, 20,20);
	else
		m_centerCircle.setRect(ptStart.x()/2+ptEnd.x()/2-0.5, ptStart.y()/2+ptEnd.y()/2-0.5, 1,1);

	pPainter->drawEllipse(m_centerCircle);
	pPainter->drawLine(line());
	pPainter->drawPolygon(m_arrowHead);

}

QRectF C_ItemConnection::boundingRect() const
{
	qreal extra = (pen().width() + 20) / 2.0;

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
		line().p2().y() - line().p1().y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}

QPainterPath C_ItemConnection::shape() const
{
	QPainterPath path = QGraphicsLineItem::shape();
	path.addPolygon(m_arrowHead);
	path.addEllipse(m_centerCircle);
	return path;
}

void C_ItemConnection::showEditDlg()
{
	if(m_pFilterDlg == NULL)
	{
		m_pFilterDlg = new C_DialogFilterRule(m_pFromDataItem->getName());
		C_ItemGroupFeatureSet* itemGroup = static_cast<C_ItemGroupFeatureSet*>(m_pFromDataItem->parentItem());
		m_pFilterDlg->setAttributeList(itemGroup->getAttributeNameList());
	}
	if(m_pFilterDlg->exec() == QDialog::Accepted)
	{
		m_sFilterExpression = m_pFilterDlg->getFilterExpression();
	}

	if (m_sFilterExpression != "")
	{
		m_bHasfilterRule = true;
	}
	else
	{
		m_bHasfilterRule = false;
	}
}


