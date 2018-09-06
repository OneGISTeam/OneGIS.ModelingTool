#pragma once
#include "AC_ItemGraphic.h"

class C_ItemAttribute : public AC_ItemGraphic
{
public:
	C_ItemAttribute(QString sName, E_ItemType eGroupBelong);
	~C_ItemAttribute(void);

	virtual void setItemType(const E_ItemType& eType){setData(0,E_ItemType::Attribute);};

	virtual QRectF boundingRect() const;

	double getDiameter() const{return m_dDiameter;};

	void setDiameter(const double& dDiameter){m_dDiameter = dDiameter;};

	bool getFoldState(){return m_bFolded;};

	void changeFoldState();

protected:
	void paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget);

private:
	// 获取文字所占的矩形大小
	virtual QRectF outlineRect() const;

private:
	double m_dDiameter;
	bool m_bFolded;
	QPolygonF m_triangle;
};

