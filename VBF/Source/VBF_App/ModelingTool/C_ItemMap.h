#pragma once
#include "AC_ItemGraphic.h"

// 用于连接字段到字段的映射
class C_ItemMap : public QGraphicsLineItem
{
public:
	C_ItemMap(AC_ItemGraphic* pDataItem, AC_ItemGraphic* pClassItem);
	~C_ItemMap(void);

	void setColor(const QColor& color){m_color = color;};

	QColor getColor() const{return m_color;};

	void updateLink();

	QRectF boundingRect() const;

	QPainterPath shape() const;

	AC_ItemGraphic* getDataItem(){return m_pDataItem;};

	AC_ItemGraphic* getObjClassItem(){return m_pObjClassItem;};

	void changeVisibility();

protected:
	void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *widget = 0);

	//void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
	AC_ItemGraphic* m_pDataItem;
	AC_ItemGraphic* m_pObjClassItem;
	QColor m_color;
	QPolygonF m_arrowHead;
};

