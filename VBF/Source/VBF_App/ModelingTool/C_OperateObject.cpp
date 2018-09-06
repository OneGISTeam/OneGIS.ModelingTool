#include "C_OperateObject.h"
#include <QMenu>

C_OperateObject::C_OperateObject(QWidget* pParent)
	:QWidget(pParent)
{
	setupUi(this);

	QMenu* pMenuVisual = new QMenu(this);
	pMenuVisual->addAction(new QAction(QIcon(":/ModelingTool/Images/visible.png"), tr("显示所有对象"), pMenuVisual));
	pMenuVisual->addAction(new QAction(QIcon(":/ModelingTool/Images/invisible.png"), tr("隐藏所有对象"), pMenuVisual));
	pMenuVisual->addAction(new QAction(tr("显示选中对象"), pMenuVisual));
	pMenuVisual->addAction(new QAction(tr("隐藏选中对象"), pMenuVisual));
	this->toolButton_visible->setMenu(pMenuVisual);
}


C_OperateObject::~C_OperateObject(void)
{
}
