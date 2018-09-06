#pragma once
#include "C_ItemObjectClass.h"
#include "C_ItemPosition.h"
#include "C_ItemForm.h"
#include "C_SubitemForm.h"
#include "C_ItemAttribute.h"
#include "C_SubitemAttribute.h"
#include "C_ItemConnection.h"

class C_ItemGroupObjectClass: public QGraphicsItemGroup
{
public:
	C_ItemGroupObjectClass(QString sName);
	~C_ItemGroupObjectClass(void);

	// Group名称与ObjectClassItem一致
	QString getName(){return m_sName;};

	QRectF boundingRect() const;

	void setAttributeSubitem(const QMap<QString,QString>& mapAttr);

	void setFormSubitem(const QMap<QString,QString>& mapForm);

	QList<C_ItemConnection*> getConnection(){return m_ListConnection;};

	void addConnection(C_ItemConnection* pConnection);

	bool removeConnection(C_ItemConnection* pConnection){return m_ListConnection.removeOne(pConnection);};

	void clearConnection();

protected:
	virtual void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);

	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
	QString m_sName;
	QList<C_SubitemAttribute*> m_ListAttrItems;
	QList<C_SubitemForm*> m_ListFormItems;
	C_ItemObjectClass* m_pObjClassItem;
	C_ItemPosition* m_pPosItem;
	C_ItemForm* m_pFormItem;
	C_ItemAttribute* m_pAttrItem;
	bool m_bFoldAttr, m_bFoldForm;	// Item是否折叠
	QList<C_ItemConnection*> m_ListConnection;
};

