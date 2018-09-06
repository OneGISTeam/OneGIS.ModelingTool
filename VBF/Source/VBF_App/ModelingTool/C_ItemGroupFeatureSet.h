#pragma once
#include "C_ItemFeatureSet.h"
#include "C_SubitemAttribute.h"
#include "C_SubitemGeometry.h"
#include "C_ItemAttribute.h"
#include "C_ItemGeometry.h"
#include "C_ItemConnection.h"


class C_ItemGroupFeatureSet : public QGraphicsItemGroup
{
public:
	C_ItemGroupFeatureSet(QString sName);
	~C_ItemGroupFeatureSet(void);

	QString getName(){return m_sName;};

	QRectF boundingRect() const;

	void setAttributeSubitem(const QMap<QString,QString>& mapAttr);

	QStringList getAttributeNameList();

	void setGeometrySubitem(const QMap<QString,QString>& mapGeo);

	C_ItemConnection* getConnectionItem(){return m_pConnection;};

	void setConnection(C_ItemConnection* pConnection);

	void clearConnection();

protected:
	virtual void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);

	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
	QString m_sName;
	QList<C_SubitemAttribute*> m_ListAttrItems;
	QList<C_SubitemGeometry*> m_ListGeoItems;
	C_ItemFeatureSet* m_pFeatureItem;
	C_ItemGeometry* m_pGeoItem;
	C_ItemAttribute* m_pAttrItem;
	bool m_bFoldAttr, m_bFoldGeo;	// Item «∑Ò’€µ˛
	C_ItemConnection* m_pConnection;	
};

