#pragma once
#include "AC_ItemGraphic.h"

class C_SubitemAttribute : public AC_ItemGraphic
{
public:
	C_SubitemAttribute(QString sName, E_ItemType eGroupBelong,QString sTag = "");
	~C_SubitemAttribute(void);

	virtual void setItemType(const E_ItemType& eType){setData(0,E_ItemType::SubAttribute);};

	virtual QRectF boundingRect() const;

	double getDiameter() const{return m_dDiameter;};

	void setDiameter(const double& dDiameter){m_dDiameter = dDiameter;};

protected:
	void paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget);

private:
	// 获取文字所占的矩形大小
	virtual QRectF outlineRect() const;

private:
	double m_dDiameter;
	QString m_sTag;
};

