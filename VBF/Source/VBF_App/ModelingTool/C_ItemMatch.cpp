#include "C_ItemMatch.h"
#include "QPen"
#include "QPainter"
#include "C_ItemGroupFeatureSet.h"

C_ItemMatch::C_ItemMatch(C_ItemFeatureSet* pMain,C_ItemFeatureSet* pSecondary)
{
	m_pMainData = pMain;
	m_pSecondaryData = pSecondary;
	m_color = Qt::black;
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setData(0,E_ItemType::Match);
	setPen(QPen(m_color,2,Qt::DashLine,Qt::RoundCap, Qt::RoundJoin));
	setToolTip("可编辑或删除融合规则");
	m_pMatchDlg = NULL;
}


C_ItemMatch::~C_ItemMatch(void)
{
	m_pMainData = NULL;
	m_pSecondaryData = NULL;
	if(m_pMatchDlg != NULL)
	{
		delete m_pMatchDlg;
		m_pMatchDlg = NULL;
	}
}

void C_ItemMatch::updateLink()
{
	QLineF line(mapFromItem(m_pSecondaryData, 0, 0), mapFromItem(m_pMainData, 0, 0));
	setLine(line);
}

void C_ItemMatch::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *widget /* = 0 */)
{
	if(m_pMainData->collidesWithItem(m_pSecondaryData))
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
	QPointF p1 = m_pMainData->scenePos();
	QPointF p2 = m_pSecondaryData->scenePos();
	int w1 = m_pMainData->boundingRect().width();
	int w2 = m_pSecondaryData->boundingRect().width();

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
	setLine(QLineF(ptStart, ptEnd));

	// 设置箭头方向
	qreal arrowSize = 20;
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

QRectF C_ItemMatch::boundingRect() const
{
	qreal extra = (pen().width() + 20) / 2.0;

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
		line().p2().y() - line().p1().y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}

QPainterPath C_ItemMatch::shape() const
{
	QPainterPath path = QGraphicsLineItem::shape();
	path.addPolygon(m_arrowHead);
	return path;
}

void C_ItemMatch::showEditDlg()
{
	if(m_pMatchDlg == NULL)
	{
		m_pMatchDlg = new C_DialogMergeRule;
		C_ItemGroupFeatureSet* mainFeature = static_cast<C_ItemGroupFeatureSet*>(m_pMainData->parentItem());
		C_ItemGroupFeatureSet* secondaryFeature = static_cast<C_ItemGroupFeatureSet*>(m_pSecondaryData->parentItem());
		m_pMatchDlg->setMainAttribute(mainFeature->getAttributeNameList());
		m_pMatchDlg->setSecondaryAttribute(secondaryFeature->getAttributeNameList());
	}
	if(m_pMatchDlg->exec()!=QDialog::Accepted)
	{
		m_pMatchDlg->setDefaultValue();
	}
}