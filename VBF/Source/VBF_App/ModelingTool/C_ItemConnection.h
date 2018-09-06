#pragma once
#include "C_ItemFeatureSet.h"
#include "C_ItemObjectClass.h"
#include "C_ItemMap.h"
#include "C_ItemMatch.h"
#include "C_DialogFilterRule.h"

class C_ItemGroupFeatureSet;
class C_ItemGroupObjectClass;
// 用于连接数据源和对象类，并具有过滤作用
class C_ItemConnection: public QGraphicsLineItem
{
public:
	C_ItemConnection(C_ItemFeatureSet* pFromItem, C_ItemObjectClass* pToItem);
	virtual ~C_ItemConnection(void);

	void setColor(const QColor& color);

	QColor getColor() const;

	C_ItemGroupFeatureSet* getFeatureSetItemGroup();

	C_ItemGroupObjectClass* getObjectClassItemGroup();

	C_ItemMatch* createMatchItem(C_ItemFeatureSet* pMain, C_ItemFeatureSet* pSecondary);

	C_ItemMap* createMapItem(QGraphicsItem* pDataItem, QGraphicsItem* pObjClassItem);

	void updateLink();

	QRectF boundingRect() const;

	QPainterPath shape() const;

	QList<C_ItemMatch*> getMatchItem(){return m_ListMatchLines;};

	QList<C_ItemMap*> getMapItem(){return m_ListMapLines;};

	bool removeMapItem(C_ItemMap* pItemMap){return m_ListMapLines.removeOne(pItemMap);};

	bool removeMatcjItem(C_ItemMatch* pItemMatch){return m_ListMatchLines.removeOne(pItemMatch);};

	void showEditDlg();


protected:
	void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *widget = 0);

	//void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
	C_ItemFeatureSet* m_pFromDataItem;
	C_ItemObjectClass* m_pToClassItem;
	QColor m_color;
	QPolygonF m_arrowHead;		// 连线箭头
	QRectF m_centerCircle;		// 中心圆圈
	QList<C_ItemMap*> m_ListMapLines;
	QList<C_ItemMatch*> m_ListMatchLines;
	bool m_bHasfilterRule;
	C_DialogFilterRule* m_pFilterDlg;
	QString m_sFilterExpression;
};

