#include "C_SubitemGeometry.h"
#include "QPen"
#include "QPainter"
#include "QUuid"

C_SubitemGeometry::C_SubitemGeometry(QString sName, QString sTag)
{
	m_uuID = QUuid::createUuid();
	m_sName = sName;
	m_sTag = sTag;
	m_outlineColor = QColor(255,222,173);
	m_iOutlineWidth = 1;
	setFlags(ItemIsMovable|ItemIsSelectable);
	setItemType(E_ItemType::SubGeometry);
	m_backgroundColor = QColor(255,250,240);
	setToolTip(m_sTag);
	setFontSize(sName);
}


C_SubitemGeometry::~C_SubitemGeometry(void)
{
}

QRectF C_SubitemGeometry::boundingRect()const 
{
	const int iMargin = 1;
	QRectF rect = outlineRect();
	rect.adjust(-iMargin, -iMargin, +iMargin, +iMargin);
	return rect;
}

void C_SubitemGeometry::paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget)
{
	QPen pen(m_outlineColor);
	pen.setWidth(m_iOutlineWidth);
	pPainter->setPen(pen);
	pPainter->setBrush(m_backgroundColor);


	QRectF rect = outlineRect();
	pPainter->drawRect(rect);

	pPainter->setPen(Qt::black);
	pPainter->setFont(QFont("¿¬Ìå", m_iFontSize, QFont::Normal));
	pPainter->drawText(rect, Qt::AlignCenter, m_sName);

	if(isSelected()){
		pPainter->setBrush(QBrush(QColor(0,0,0,0)));
		pPainter->setPen(Qt::red);
		pPainter->drawRect(rect);
	}
}

QRectF C_SubitemGeometry::outlineRect() const
{
	QRectF rect(0,0,120,25);
	rect.translate(-rect.center());
	return rect;
}
