#pragma once
#include "Include/IC_Wnd.h"
#include "qgsmapcanvasmap.h"
#include "qgsmapcanvas.h"
#include "C_2DCoordinateWidget.h"
class C_2DWnd: public IC_Wnd
{
public:
	C_2DWnd(QWidget* pParent = 0);
	~C_2DWnd(void);

	virtual QString name();

	virtual void init();

	virtual QWidget* statusWidget() {return m_p2DStatusWidget;};

private:
	bool load2DMaps();

private:
	QgsMapCanvas* m_pMapCanvas;
	C_2DCoordinateWidget* m_p2DStatusWidget;
};

