#ifndef C_CONVERTCANVAS_H
#define C_CONVERTCANVAS_H
#include "QGraphicsView"
#include "C_ItemConnection.h"

class C_ConvertCanvas: public QGraphicsView
{
	Q_OBJECT
public:
	C_ConvertCanvas(QWidget* pParent = 0);
	~C_ConvertCanvas();

	enum Mode{Select, RemoveData, InsertFilterRule, InsertMappingRule, InsertMergeRule, EditRule, RemoveRule};


	// 功能函数
	void importDataByFileName(QStringList sFileName);
	void removeData();
	void appendFilterRule();
	void appendMappingRule();
	void appendMergeRule();
	void editRule();
	void removeRule();
	void convert();

protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	
	// 拖入部件需重写函数
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dragLeaveEvent(QDragLeaveEvent *event);
	virtual void dragMoveEvent(QDragMoveEvent *event);
	virtual void dropEvent(QDropEvent *event);

private:
	Mode m_mode;
	QGraphicsLineItem *m_pRubberLine;
	QPointF *m_pStartPt;
	QCursor *m_pCursor;
	// 以下三个List仅用于检查并清楚内存，实际以scene调用Item
	//QList<C_ItemConnection*> m_ListConnection;
	//QList<C_ItemGroupObjectClass*> m_listGroupObjClass;
	//QList<C_ItemGroupFeatureSet*> m_listGroupFeatureSet;
	bool m_bDragMode;
};

#endif // C_CONVERTCANVAS_H
