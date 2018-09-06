#include "C_ItemForm.h"
#include "QPen"
#include "QPainter"
#include "QUuid"

C_ItemForm::C_ItemForm(QString sName)
{
	m_uuID = QUuid::createUuid();
	m_sName = sName;
	m_iOutlineWidth = 1;
	setFlags(ItemIsMovable|ItemIsSelectable);
	setItemType(E_ItemType::Form);
	m_backgroundColor = QColor(224,255,255);
	m_outlineColor = QColor(135,206,235);
	m_bFolded = false;
	setFontSize(sName);
}


C_ItemForm::~C_ItemForm(void)
{
}


QRectF C_ItemForm::boundingRect()const 
{
	const int iMargin = 1;
	QRectF rect = outlineRect();
	rect.adjust(-iMargin, -iMargin, +iMargin, +iMargin);
	return rect;
}

void C_ItemForm::paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget)
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

	m_triangle.clear();
	QPointF centerPt(0,0);
	if(m_bFolded)
	{
		QPointF p1(centerPt.x() - 55,centerPt.y());
		QPointF p2(p1.x() - 5, p1.y() - 5);
		QPointF p3(p2.x(), p2.y() + 10);
		m_triangle<<p1<<p2<<p3;
		pPainter->setBrush(Qt::white);
	}
	else
	{
		QPointF p1(centerPt.x() - 55,centerPt.y());
		QPointF p2(p1.x() - 5, p1.y());
		QPointF p3(p1.x(), p1.y() - 5);
		m_triangle<<p1<<p2<<p3;
		pPainter->setBrush(Qt::black);
	}
	pPainter->drawPolygon(m_triangle);

	if(isSelected()){
		pPainter->setBrush(QBrush(QColor(0,0,0,0)));
		pPainter->setPen(Qt::red);
		pPainter->drawRect(rect);
	}
}

QRectF C_ItemForm::outlineRect() const
{
	QRectF rect(0,0,120,25);
	rect.translate(-rect.center());
	return rect;
}

void C_ItemForm::changeFoldState()
{
	if(m_bFolded == false)
		m_bFolded = true;
	else
		m_bFolded = false;
}