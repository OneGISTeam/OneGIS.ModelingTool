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

	// ��ȡItemΨһID
	virtual QString getID(){return m_uuID;};
	// ����Item����
	virtual void setName(const QString& sName){m_sName = sName;};
	// ��ȡItem����
	virtual QString getName() const{return m_sName;};
	// ����Item����
	virtual void setItemType(const E_ItemType& eType){setData(0,eType);};
	// ��ȡItem���ͣ�Ҳ��ͨ������ġ�Data��0����������ȡ��
	virtual E_ItemType getItemType(){return E_ItemType(data(0).toInt());};
	// ���ñ߽��ߵ���ɫ
	virtual void setOutlineColor(const QColor& color){m_outlineColor = color;};
	// ��ȡ�߽��ߵ���ɫ
	virtual QColor getOutlineColor() const{return m_outlineColor;};
	// ���ñ߽��ߵĿ��
	virtual void setOutlineWidth(const int& iWidth){m_iOutlineWidth = iWidth;};
	// ��ȡ�߽��ߵĿ��
	virtual int getOutlineWidth() const{return m_iOutlineWidth;};
	// ������䱳����ɫ
	virtual void setBackgroundColor(const QColor& color){m_backgroundColor = color;};
	// ��ȡ��䱳����ɫ
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

