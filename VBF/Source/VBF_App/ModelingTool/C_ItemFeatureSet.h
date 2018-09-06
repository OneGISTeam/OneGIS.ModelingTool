#pragma once
#include "AC_ItemGraphic.h"
class C_ItemFeatureSet : public AC_ItemGraphic
{
public:
	C_ItemFeatureSet(QString sName);
	~C_ItemFeatureSet(void);

	virtual void setItemType(const E_ItemType& eType){setData(0,E_ItemType::FeatureSet);};

	virtual QRectF boundingRect() const;

	double getDiameter() const{return m_dDiameter;};

	void setDiameter(const double& dDiameter){m_dDiameter = dDiameter;};

protected:
	void paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget);

private:
	// 获取文字所占的矩形大小
	virtual QRectF outlineRect() const;

	int roundness(double dSize);

private:
	double m_dDiameter;
};

