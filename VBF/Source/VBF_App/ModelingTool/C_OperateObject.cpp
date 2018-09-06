#include "C_OperateObject.h"
#include <QMenu>

C_OperateObject::C_OperateObject(QWidget* pParent)
	:QWidget(pParent)
{
	setupUi(this);

	QMenu* pMenuVisual = new QMenu(this);
	pMenuVisual->addAction(new QAction(QIcon(":/ModelingTool/Images/visible.png"), tr("��ʾ���ж���"), pMenuVisual));
	pMenuVisual->addAction(new QAction(QIcon(":/ModelingTool/Images/invisible.png"), tr("�������ж���"), pMenuVisual));
	pMenuVisual->addAction(new QAction(tr("��ʾѡ�ж���"), pMenuVisual));
	pMenuVisual->addAction(new QAction(tr("����ѡ�ж���"), pMenuVisual));
	this->toolButton_visible->setMenu(pMenuVisual);
}


C_OperateObject::~C_OperateObject(void)
{
}
