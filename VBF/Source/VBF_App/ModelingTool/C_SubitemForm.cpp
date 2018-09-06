#include "C_SubitemForm.h"
#include "QPen"
#include "QPainter"
#include "QUuid"

C_SubitemForm::C_SubitemForm(QString sName, QString sTag)
{
	m_uuID = QUuid::createUuid();
	m_sName = sName;
	m_sTag = sTag;
	m_outlineColor = QColor(135,206,235);
	m_iOutlineWidth = 1;
	setFlags(ItemIsMovable|ItemIsSelectable);
	setItemType(E_ItemType::SubForm);
	m_backgroundColor = QColor(240,255,255);
	setToolTip(m_sTag);
	setFontSize(sName);
}


C_SubitemForm::~C_SubitemForm(void)
{
}

QRectF C_SubitemForm::boundingRect()const 
{
	const int iMargin = 1;
	QRectF rect = outlineRect();
	rect.adjust(-iMargin, -iMargin, +iMargin, +iMargin);
	return rect;
}

void C_SubitemForm::paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget)
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

QRectF C_SubitemForm::outlineRect() const
{
	QRectF rect(0,0,120,25);
	rect.translate(-rect.center());
	return rect;
}
