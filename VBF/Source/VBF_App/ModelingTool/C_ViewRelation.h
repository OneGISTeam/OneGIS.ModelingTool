#pragma once
#include <QTreeWidget>

/**
* @brief ��ϵ��ͼ��QTreeWidget����
*/
class C_ViewRelation: public QTreeWidget
{
public:
	C_ViewRelation(QWidget* pParent = 0);
	~C_ViewRelation(void);

protected:
	//��������ק
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dragMoveEvent(QDragMoveEvent* event);
};

