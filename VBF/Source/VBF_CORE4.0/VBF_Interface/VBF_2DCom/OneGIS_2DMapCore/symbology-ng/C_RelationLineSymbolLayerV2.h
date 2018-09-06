#pragma once
#include "qgssymbollayerv2.h"
#include <QPainter>

class CORE_EXPORT C_RelationLineSymbolLayerV2: public QgsLineSymbolLayerV2
{
public:
	C_RelationLineSymbolLayerV2();
	virtual ~C_RelationLineSymbolLayerV2();
	void renderPolyline( const QPolygonF& points, QgsSymbolV2RenderContext& context ) override;

	virtual QString layerType() const override;

	virtual void startRender( QgsSymbolV2RenderContext& context ) override;
	virtual void stopRender( QgsSymbolV2RenderContext& context ) override;

	virtual QgsSymbolLayerV2* clone() const override;

	virtual QgsStringMap properties() const override;

	virtual void drawPreviewIcon( QgsSymbolV2RenderContext& context, QSize size ) override;

	double getArrowSize() {return m_dArrowSize;}
	void setArrowSize(double dSize) {m_dArrowSize = dSize;}

	double getPieSize() {return m_dPieSize;}
	void setPieSize(double dPieSize) {m_dPieSize = dPieSize;}

	QBrush getBrush() {return m_brush;}
	void setBrush(QBrush brush) {m_brush = brush;}

	QPen getPen() {return m_pen;}
	void setPen(QPen pen) {m_pen = pen;}

private:
	double m_dArrowSize;
	double m_dPieSize;
	QBrush m_brush;
	QPen m_pen;
};