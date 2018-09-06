#pragma once
#include "Include/IC_Wnd.h"
#include "C_ViewerWidget3D.h"
#include "C_3DCoordinateWidget.h"

class C_3DWnd: public IC_Wnd
{
public:
	C_3DWnd(QWidget* pParent = 0);
	~C_3DWnd(void);

	virtual QString name();

	virtual void init();

	virtual QWidget* statusWidget() {return m_p3DStatusWidget;};

	C_ViewerWidget3D* viewerWidget() { return m_pViewerWidget;};

private:
	C_ViewerWidget3D* m_pViewerWidget;
	C_3DCoordinateWidget* m_p3DStatusWidget;
};

