#include "C_SubitemAttribute.h"
#include "QPen"
#include "QPainter"
#include "QUuid"

C_SubitemAttribute::C_SubitemAttribute(QString sName, E_ItemType eGroupBelong, QString sTag)
{
	m_uuID = QUuid::createUuid();
	m_sName = sName;
	m_sTag = sTag;
	QColor color[2];
	if(eGroupBelong == E_ItemType::FeatureSetGroup)
	{
		color[0].setRgb(255,250,240);
		color[1].setRgb(255,222,173);
	}
	else
	{
		color[0].setRgb(240,255,255);
		color[1].setRgb(135,206,235);
	}
	m_backgroundColor = color[0];
	m_outlineColor = color[1];
	m_iOutlineWidth = 1;
	setFlags(ItemIsMovable|ItemIsSelectable);
	setItemType(E_ItemType::SubAttribute);
	setFontSize(sName);
	setToolTip(m_sTag);
}


C_SubitemAttribute::~C_SubitemAttribute(void)
{
}

QRectF C_SubitemAttribute::boundingRect()const 
{
	const int iMargin = 1;
	QRectF rect = outlineRect();
	rect.adjust(-iMargin, -iMargin, +iMargin, +iMargin);
	return rect;
}

void C_SubitemAttribute::paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget)
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

QRectF C_SubitemAttribute::outlineRect() const
{
	QRectF rect(0,0,120,25);
	rect.translate(-rect.center());
	return rect;
}

