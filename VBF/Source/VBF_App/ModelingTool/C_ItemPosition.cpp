#include "C_ItemPosition.h"
#include "QPen"
#include "QPainter"
#include "QUuid"

C_ItemPosition::C_ItemPosition(QString sName)
{
	m_uuID = QUuid::createUuid();
	m_sName = sName;
	m_outlineColor = QColor(135,206,235);
	m_iOutlineWidth = 1;
	setFlags(ItemIsMovable|ItemIsSelectable);
	setItemType(E_ItemType::Position);
	m_backgroundColor = QColor(224,255,255);
	setFontSize(sName);
}


C_ItemPosition::~C_ItemPosition(void)
{
}


QRectF C_ItemPosition::boundingRect()const 
{
	const int iMargin = 1;
	QRectF rect = outlineRect();
	rect.adjust(-iMargin, -iMargin, +iMargin, +iMargin);
	return rect;
}

void C_ItemPosition::paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget)
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

QRectF C_ItemPosition::outlineRect() const
{
	QRectF rect(0,0,120,25);
	rect.translate(-rect.center());
	return rect;
}

