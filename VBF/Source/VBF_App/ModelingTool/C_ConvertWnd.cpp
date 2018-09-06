#include "C_ConvertWnd.h"
#include "QIcon"

C_ConvertWnd::C_ConvertWnd(QWidget* pParent)
	:IC_Wnd(pParent)
{
	m_pConvertCanvas = new C_ConvertCanvas(this);
	setWidget(m_pConvertCanvas);
}


C_ConvertWnd::~C_ConvertWnd(void)
{
}

QString C_ConvertWnd::name()
{
	return UI_WND_CONVERT;
}

void C_ConvertWnd::init()
{
	this->setWindowTitle(tr("批量转换窗口"));
	this->setWindowIcon(QIcon(":/ModelingTool/Images/conversionMap.png"));
}