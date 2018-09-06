#include "C_ItemMap.h"
#include "QPen"
#include "QPainter"

C_ItemMap::C_ItemMap(AC_ItemGraphic* pDataItem, AC_ItemGraphic* pClassItem)
{
	m_pDataItem = pDataItem;
	m_pObjClassItem = pClassItem;
	m_color = Qt::black;
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setData(0,E_ItemType::Map);
	setPen(QPen(m_color,1,Qt::SolidLine));
	setToolTip("可删除映射规则");
}


C_ItemMap::~C_ItemMap(void)
{
	m_pDataItem = NULL;
	m_pObjClassItem = NULL;
}


void C_ItemMap::updateLink()
{
	QLineF line(mapFromItem(m_pDataItem, 0, 0), mapFromItem(m_pObjClassItem, 0, 0));
	setLine(line);
}

void C_ItemMap::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *widget /* = 0 */)
{
	if(m_pDataItem->collidesWithItem(m_pObjClassItem))
		return;
	
	QPen linkPen = this->pen();
	if(isSelected()){
		linkPen.setColor(Qt::red);
		pPainter->setBrush(Qt::red);
	}else{
		linkPen.setColor(m_color);
		pPainter->setBrush(m_color);
	}
	pPainter->setPen(linkPen);
	// 直接采用垂直边中点
	QPointF p1 = m_pDataItem->scenePos();
	QPointF p2 = m_pObjClassItem->scenePos();
	int w1 = m_pDataItem->boundingRect().width();
	int w2 = m_pObjClassItem->boundingRect().width();

	QPointF ptEnd,ptStart;
	if(p1.x()<=p2.x())
	{
		ptStart = QPointF(p1.x() + w1 / 2, p1.y());
		ptEnd = QPointF(p2.x() - w2 / 2, p2.y());
	}
	else
	{
		ptStart = QPointF(p1.x() - w1 / 2, p1.y());
		ptEnd = QPointF(p2.x() + w2 / 2, p2.y());
	}
	setLine(QLineF(ptEnd, ptStart));

	// 设置箭头方向
	qreal arrowSize = 10;
	double angle = ::acos(line().dx() / line().length());
	if (line().dy() >= 0)
		angle = (Pi * 2) - angle;
	QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
		cos(angle + Pi / 3) * arrowSize);
	QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
		cos(angle + Pi - Pi / 3) * arrowSize);

	m_arrowHead.clear();
	m_arrowHead  << arrowP1 << line().p1()<< arrowP2;
	pPainter->drawLine(line());
	pPainter->drawPolyline(m_arrowHead);
}

QRectF C_ItemMap::boundingRect() const
{
	qreal extra = (pen().width() + 10) / 2.0;

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
		line().p2().y() - line().p1().y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}

QPainterPath C_ItemMap::shape() const
{
	QPainterPath path = QGraphicsLineItem::shape();
	path.addPolygon(m_arrowHead);
	return path;
}

void C_ItemMap::changeVisibility()
{
	bool test = m_pDataItem->isVisible()&&m_pObjClassItem->isVisible();
	if(test)
		setVisible(true);
	else
		setVisible(false);
}