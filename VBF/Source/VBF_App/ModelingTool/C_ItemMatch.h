#pragma once
#include "C_ItemFeatureSet.h"
#include "C_DialogMergeRule.h"

// 用于连接多个数据项，以便于匹配处理
class C_ItemMatch : public QGraphicsLineItem
{
public:
	C_ItemMatch(C_ItemFeatureSet* pMain,C_ItemFeatureSet* pSecondary);
	~C_ItemMatch(void);

	void setColor(const QColor& color){m_color = color;};

	QColor getColor() const{return m_color;};

	void updateLink();

	QRectF boundingRect() const;

	QPainterPath shape() const;

	C_ItemFeatureSet* getMainDataItem(){return m_pMainData;};

	C_ItemFeatureSet* getSecondaryDataItem(){return m_pSecondaryData;};

	void showEditDlg();

	bool isPositionMatchSet(){return m_pMatchDlg->m_bLocation;};
	bool isAttributeMatchSet(){return m_pMatchDlg->m_bAttribute;};
	bool isFormMatchSet(){return m_pMatchDlg->m_bForm;};
	double getRangeH(){return m_pMatchDlg->m_dRangeW;};
	double getRangeW(){return m_pMatchDlg->m_dRangeH;};
	QString getMainField(){return m_pMatchDlg->m_strMainAttr;};
	QString getSecondaryField(){return m_pMatchDlg->m_strSecondaryAttr;};
	double getFieldSimilarity(){return m_pMatchDlg->m_iSimiAttr;};
	double getLineLineSimilarity(){return m_pMatchDlg->m_iSimiForm[0];};
	double getLineAreaSimilarity(){return m_pMatchDlg->m_iSimiForm[1];};
	double getAreaAreaSimilarity(){return m_pMatchDlg->m_iSimiForm[2];};

protected:
	void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *widget = 0);

	//void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
	C_ItemFeatureSet* m_pMainData;
	C_ItemFeatureSet* m_pSecondaryData;
	QPolygonF m_arrowHead;
	QColor m_color;
	C_DialogMergeRule* m_pMatchDlg;
};

