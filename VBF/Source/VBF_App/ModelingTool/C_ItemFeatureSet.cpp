#include "C_ItemFeatureSet.h"
#include "QPen"
#include "QPainter"
#include "QUuid"

C_ItemFeatureSet::C_ItemFeatureSet(QString sName)
{
	m_uuID = QUuid::createUuid();
	m_sName = sName;
	m_outlineColor = QColor(255,222,173);
	m_iOutlineWidth = 1;
	setFlags(ItemIsMovable|ItemIsSelectable);
	setItemType(E_ItemType::FeatureSet);
	m_backgroundColor = QColor(255,222,173);
	setFontSize(sName);
}


C_ItemFeatureSet::~C_ItemFeatureSet(void)
{
}


QRectF C_ItemFeatureSet::boundingRect() const
{
	const int iMargin = 3;
	QRectF rect = outlineRect();
	rect.adjust(1, -iMargin, 1, 1);
	return rect;
}

void C_ItemFeatureSet::paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget)
{
	QPen pen(m_outlineColor);
	pen.setWidth(m_iOutlineWidth);
	pPainter->setPen(pen);
	pPainter->setBrush(m_backgroundColor);


	QRectF rect = outlineRect();
	pPainter->drawRoundRect(rect);
	QPointF ptEllipseCenter(0,-12);
	pPainter->setPen(QColor(255,255,255));
	pPainter->drawEllipse(ptEllipseCenter, 60, 6);
	pPainter->setPen(Qt::black);
	pPainter->setFont(QFont("¿¬Ìå", m_iFontSize, QFont::Normal));
	pPainter->drawText(rect, Qt::AlignCenter, m_sName);

	if(isSelected()){
		pPainter->setBrush(QBrush(QColor(0,0,0,0)));
		pPainter->setPen(Qt::red);
		rect.adjust(0,-3,0,0);
		pPainter->drawRect(rect);
	}
}

QRectF C_ItemFeatureSet::outlineRect() const
{
	QRectF rect(0,0,120,25);
	rect.translate(-rect.center());
	return rect;
}

int C_ItemFeatureSet::roundness(double dSize)
{
	return 100*m_dDiameter/int(dSize);
}