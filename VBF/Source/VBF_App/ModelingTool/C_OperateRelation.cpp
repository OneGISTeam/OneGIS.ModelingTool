#include "C_OperateRelation.h"
#include <QMenu>

C_OperateRelation::C_OperateRelation(QWidget* pParent)
{
	setupUi(this);
	QMenu* pMenuCreateRelation = new QMenu();
	pMenuCreateRelation->addAction(new QAction(tr("手动构建关系"), pMenuCreateRelation));
	pMenuCreateRelation->addAction(new QAction(tr("批量构建关系"), pMenuCreateRelation));
	this->toolButton_createrelation->setMenu(pMenuCreateRelation);

	QMenu* pMenuVisualizeRelation = new QMenu();
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/visible.png"), tr("显示所有关系"), pMenuVisualizeRelation));
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/invisible.png"), tr("隐藏所有关系"), pMenuVisualizeRelation));
	pMenuVisualizeRelation->addAction(new QAction(tr("显示选中关系"), pMenuVisualizeRelation));
	pMenuVisualizeRelation->addAction(new QAction(tr("隐藏选中关系"), pMenuVisualizeRelation));
	pMenuVisualizeRelation->addSeparator();
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/2DMap.png"), tr("2D地图可视化"), pMenuCreateRelation));
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/3DMap.png"), tr("3D地图可视化"), pMenuCreateRelation));
	pMenuVisualizeRelation->addSeparator();
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/radar.png"), tr("雷达图可视化"), pMenuCreateRelation));
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/chordVisual.png"), tr("和弦图可视化"), pMenuCreateRelation));
	pMenuVisualizeRelation->addAction(new QAction(QIcon(":/ModelingTool/Images/forceLayout.png"), tr("力导向图可视化"), pMenuCreateRelation));
	this->toolButton_visual->setMenu(pMenuVisualizeRelation);
}


C_OperateRelation::~C_OperateRelation(void)
{
}
