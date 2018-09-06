#pragma once
#include "AC_ItemGraphic.h"
class C_SubitemGeometry : public AC_ItemGraphic
{
public:
	C_SubitemGeometry(QString sName, QString sTag = "");
	~C_SubitemGeometry(void);

	virtual void setItemType(const E_ItemType& eType){setData(0,E_ItemType::SubGeometry);};

	virtual QRectF boundingRect() const;

	double getDiameter() const{return m_dDiameter;};

	void setDiameter(const double& dDiameter){m_dDiameter = dDiameter;};

protected:
	void paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget);

private:
	// ��ȡ������ռ�ľ��δ�С
	virtual QRectF outlineRect() const;

private:
	double m_dDiameter;
	QString m_sTag;
};

