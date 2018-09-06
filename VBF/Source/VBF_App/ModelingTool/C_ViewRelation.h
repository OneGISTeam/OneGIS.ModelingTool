#pragma once
#include <QTreeWidget>

/**
* @brief 关系视图，QTreeWidget子类
*/
class C_ViewRelation: public QTreeWidget
{
public:
	C_ViewRelation(QWidget* pParent = 0);
	~C_ViewRelation(void);

protected:
	//测试项拖拽
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dragMoveEvent(QDragMoveEvent* event);
};

