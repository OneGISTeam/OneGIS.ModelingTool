#include "C_OperateRelation.h"
#include <QMenu>

C_OperateRelation::C_OperateRelation(QWidget* pParent)
{
	setupUi(this);
	QMenu* pMenuCreateRelation = new QMenu();
	pMenuCreateRelation->addAction(new QAction(tr("�ֶ�������ϵ"), pMenuCreateRelation));
	pMenuCreateRelation->addAction(new QAction(tr("����������ϵ"), pMenuCreateRelation));
	this->toolButton_createrelation->setMenu(pMenuCreateRelation);

	QMenu* pMenuVisualizeRelation = new QMenu();
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/visible.png"), tr("��ʾ���й�ϵ"), pMenuVisualizeRelation));
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/invisible.png"), tr("�������й�ϵ"), pMenuVisualizeRelation));
	pMenuVisualizeRelation->addAction(new QAction(tr("��ʾѡ�й�ϵ"), pMenuVisualizeRelation));
	pMenuVisualizeRelation->addAction(new QAction(tr("����ѡ�й�ϵ"), pMenuVisualizeRelation));
	pMenuVisualizeRelation->addSeparator();
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/2DMap.png"), tr("2D��ͼ���ӻ�"), pMenuCreateRelation));
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/3DMap.png"), tr("3D��ͼ���ӻ�"), pMenuCreateRelation));
	pMenuVisualizeRelation->addSeparator();
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/radar.png"), tr("�״�ͼ���ӻ�"), pMenuCreateRelation));
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/chordVisual.png"), tr("����ͼ���ӻ�"), pMenuCreateRelation));
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/forceLayout.png"), tr("������ͼ���ӻ�"), pMenuCreateRelation));
	this->toolButton_visual->setMenu(pMenuVisualizeRelation);
}


C_OperateRelation::~C_OperateRelation(void)
{
}
