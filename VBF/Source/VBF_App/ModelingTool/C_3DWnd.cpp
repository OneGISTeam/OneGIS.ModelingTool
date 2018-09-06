#include "C_3DWnd.h"
#include <QIcon>

C_3DWnd::C_3DWnd(QWidget* pParent)
	:IC_Wnd(pParent)
{
	m_p3DStatusWidget = new C_3DCoordinateWidget;
}

C_3DWnd::~C_3DWnd(void)
{
}

QString C_3DWnd::name()
{
	return UI_WND_3D;
}

void C_3DWnd::init()
{
	this->setWindowTitle(tr("3DÏÔÊ¾´°¿Ú"));
	this->setWindowIcon(QIcon(":/ModelingTool/Images/3DMap.png"));

	m_pViewerWidget = new C_ViewerWidget3D;
	this->setWidget(m_pViewerWidget);
}
