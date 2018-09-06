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
* @brief 对象视图，QTreeWidget子类
*/
class C_ViewObject: public QTreeWidget
{
	Q_OBJECT
public:
	C_ViewObject(QWidget* pParent = 0);
	virtual ~C_ViewObject(void);

private slots:
	void showRightMenu(QPoint);

private:
	QAction * addChildObjectAction;
	QAction * addObjectAction;
	QAction * editObjectAction;
	QAction * deleteObjectAction;

	QMenu * m_rightMenu_blankArea;
	QMenu * m_rightMenu_atItem;
	
	//QMenu *m_memberMenu;
	//QMenu *m_addAreaMenu;

};

