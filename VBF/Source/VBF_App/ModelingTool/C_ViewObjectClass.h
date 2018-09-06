#pragma once
#include <QTreeWidget>

#include <QStringList>
#include <QMenu>
#include <QContextMenuEvent>
#include <QTreeWidgetItem>
#include <qDebug>
#include <QMessageBox>
#include <QVariant>


/**
* @brief 类视图，QTreeWidget子类
*/
class C_ViewClass: public QTreeWidget
{
	Q_OBJECT
public:
	C_ViewClass(QWidget* pParent = 0);
	virtual ~C_ViewClass(void);

private slots:
	void showRightMenu(QPoint);

protected:
	// 测试类Item的拖拽功能
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	QAction * addChildClassAction;
	QAction * addClassAction;
	QAction * addObjectAction;
	QAction * editClassAction;
	QAction * deleteClassAction;

	QMenu * m_rightMenu_blankArea;
	QMenu * m_rightMenu_atClassItem;
	QMenu * m_rightMenu_atObjectItem;

private:
	QPoint m_dragPosition;
	QTreeWidgetItem* m_dragItem;
};

