#pragma once
#include <QTimer>
#include "GraphicsWindowQt.h"
#include "C_GlobalGIS.h"

class C_ViewerWidget3D: public GLWidget
{
public:
	C_ViewerWidget3D(QWidget* pParent = 0);
	virtual ~C_ViewerWidget3D(void);

protected:
	virtual void paintEvent(QPaintEvent* event);

private:
	QTimer m_timer;
	ref_ptr<C_GlobalGIS> m_pGlobalGIS;
};

