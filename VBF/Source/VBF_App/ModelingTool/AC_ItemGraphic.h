#pragma once
#include <QGraphicsItem>

enum E_ItemType{ObjectClass, FeatureSet, Geometry, SubGeometry, 
	Attribute, SubAttribute, Position, Form, 
	SubForm, FeatureSetGroup, ObjectClassGroup, Connection,
	Map, Match};

const qreal Pi = 3.1415926;

class AC_ItemGraphic: public QGraphicsItem
{
public:
	AC_ItemGraphic();
	virtual ~AC_ItemGraphic(void);

	// 获取Item唯一ID
	virtual QString getID(){return m_uuID;};
	// 设置Item名称
	virtual void setName(const QString& sName){m_sName = sName;};
	// 获取Item名称
	virtual QString getName() const{return m_sName;};
	// 设置Item类型
	virtual void setItemType(const E_ItemType& eType){setData(0,eType);};
	// 获取Item类型（也可通过基类的“Data（0）”方法获取）
	virtual E_ItemType getItemType(){return E_ItemType(data(0).toInt());};
	// 设置边界线的颜色
	virtual void setOutlineColor(const QColor& color){m_outlineColor = color;};
	// 获取边界线的颜色
	virtual QColor getOutlineColor() const{return m_outlineColor;};
	// 设置边界线的宽度
	virtual void setOutlineWidth(const int& iWidth){m_iOutlineWidth = iWidth;};
	// 获取边界线的宽度
	virtual int getOutlineWidth() const{return m_iOutlineWidth;};
	// 设置填充背景颜色
	virtual void setBackgroundColor(const QColor& color){m_backgroundColor = color;};
	// 获取填充背景颜色
	virtual QColor getBackgroundColor() const{return m_backgroundColor;};

protected:

	void setFontSize(const QString& sName);

protected:
	QString m_uuID;
	QString m_sName;
	QColor m_outlineColor;
	int m_iOutlineWidth;
	QColor m_backgroundColor;
	int m_iFontSize;
};

