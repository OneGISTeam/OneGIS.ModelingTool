#include "C_ItemObjectClass.h"
#include "QPen"
#include "QPainter"
#include "QUuid"

C_ItemObjectClass::C_ItemObjectClass(QString sName)
{
	m_uuID = QUuid::createUuid();
	m_sName = sName;
	m_outlineColor = QColor(135,206,235);
	m_iOutlineWidth = 1;
	setFlags(ItemIsMovable|ItemIsSelectable);
	setItemType(E_ItemType::ObjectClass);
	m_backgroundColor = QColor(135,206,235);
	setFontSize(sName);
}


C_ItemObjectClass::~C_ItemObjectClass(void)
{
}

void C_ItemObjectClass::paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget)
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

QRectF C_ItemObjectClass::boundingRect() const
{
	const int iMargin = 1;
	QRectF rect = outlineRect();
	rect.adjust(-iMargin, -iMargin, +iMargin, +iMargin);
	return rect;
}

QRectF C_ItemObjectClass::outlineRect() const
{
	QRectF rect(0,0,120,28);
	rect.translate(-rect.center());
	return rect;
}
