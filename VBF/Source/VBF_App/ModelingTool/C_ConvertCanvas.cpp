#include "C_ConvertCanvas.h"
#include "QMouseEvent"
#include "C_ItemGroupFeatureSet.h"
#include "C_ItemGroupObjectClass.h"
#include "QFileDialog"
#include "QMessageBox"

C_ConvertCanvas::C_ConvertCanvas(QWidget* pParent)
	:QGraphicsView(pParent)
{
	setScene(new QGraphicsScene(pParent));
	m_mode = Select;
	m_pStartPt = 0;
	m_pCursor = new QCursor(QPixmap(":/ModelingTool/Images/deleteItem.png"));
	setAcceptDrops(true);
	m_bDragMode = false;
}

C_ConvertCanvas::~C_ConvertCanvas()
{
	QList<QGraphicsItem*> listItem = scene()->items();
	for (int i = 0;i<listItem.size();i++)
	{
		scene()->removeItem(listItem[i]);
		if(listItem[i]->data(0).toInt() == Connection)
			delete static_cast<C_ItemConnection*>(listItem[i]);
		else if(listItem[i]->data(0).toInt() == FeatureSetGroup)
			delete static_cast<C_ItemGroupFeatureSet*>(listItem[i]);
		else if(listItem[i]->data(0).toInt() == ObjectClassGroup)
			delete static_cast<C_ItemGroupObjectClass*>(listItem[i]);
	}
}

void C_ConvertCanvas::importDataByFileName(QStringList sFileName)
{
	QMap<QString, QString> mapForm,mapClassAttr,mapGeo_1,mapFeatureAttr_1,mapGeo_2,mapFeatureAttr_2;
	mapClassAttr.insert("对象类属性_1","int");
	mapClassAttr.insert("对象类属性_2","string");
	mapForm.insert("对象类形态_1","Vector_2D");
	mapGeo_1.insert("wkbPoint","");
	mapFeatureAttr_1.insert("数据源属性_1","int");
	mapGeo_2.insert("wkbLine","");
	mapFeatureAttr_2.insert("数据源属性_1","string");

	C_ItemGroupObjectClass* pClass = new C_ItemGroupObjectClass("对象类_1");
	pClass->setAttributeSubitem(mapClassAttr);
	pClass->setFormSubitem(mapForm);
	pClass->setPos(100,100);
	scene()->addItem(pClass);
	//m_listGroupObjClass.push_back(pClass);

	C_ItemGroupFeatureSet* pFeatureSet_1 = new C_ItemGroupFeatureSet("数据源_1");
	pFeatureSet_1->setAttributeSubitem(mapFeatureAttr_1);
	pFeatureSet_1->setGeometrySubitem(mapGeo_1);
	pFeatureSet_1->setPos(300,300);
	scene()->addItem(pFeatureSet_1);
	//m_listGroupFeatureSet.push_back(pFeatureSet_1);

	C_ItemGroupFeatureSet* pFeatureSet_2 = new C_ItemGroupFeatureSet("数据源_2");
	pFeatureSet_2->setAttributeSubitem(mapFeatureAttr_2);
	pFeatureSet_2->setGeometrySubitem(mapGeo_2);
	pFeatureSet_2->setPos(500,500);
	scene()->addItem(pFeatureSet_2);
	//m_listGroupFeatureSet.push_back(pFeatureSet_2);
}

void C_ConvertCanvas::removeData()
{
	setCursor(*m_pCursor);
	m_mode = RemoveData;
}

void C_ConvertCanvas::appendFilterRule()
{
	setCursor(Qt::CrossCursor);
	m_mode = InsertFilterRule;
}

void C_ConvertCanvas::appendMappingRule()
{
	setCursor(Qt::CrossCursor);
	m_mode = InsertMappingRule;
}

void C_ConvertCanvas::appendMergeRule()
{
	setCursor(Qt::CrossCursor);
	m_mode = InsertMergeRule;
}

void C_ConvertCanvas::editRule()
{
	setCursor(Qt::PointingHandCursor);
	m_mode = EditRule;
}

void C_ConvertCanvas::removeRule()
{
	setCursor(*m_pCursor);
	m_mode = RemoveRule;
}

void C_ConvertCanvas::convert()
{
	QMessageBox::information(this,"通知","批量导出成功！",QMessageBox::Ok);
}

void C_ConvertCanvas::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::RightButton)
	{
		m_mode = Select;
		setCursor(Qt::ArrowCursor);
	}
	else if(event->button() == Qt::LeftButton)
	{
		QPointF mousePos = mapToScene(event->pos());
		if(m_mode == Select)
		{
			QGraphicsView::mousePressEvent(event);
		}
		else if(m_mode == RemoveData)
		{
			QGraphicsItem* pItem = scene()->itemAt(mousePos);
			if(!pItem)
				return;
			if(pItem->parentItem()->data(0).toInt() != FeatureSetGroup)
				return;
			C_ItemGroupFeatureSet* pItemGroupfea = static_cast<C_ItemGroupFeatureSet*>(pItem->parentItem());
			C_ItemConnection* pConnection = pItemGroupfea->getConnectionItem();
			// 删除与数据有关的连接
			if(pConnection)
			{
				QList<C_ItemMatch*> listMatch = pConnection->getMatchItem();
				QList<C_ItemMap*> listMap = pConnection->getMapItem();
				C_ItemGroupObjectClass* pItemGroupObjClass = pConnection->getObjectClassItemGroup();
				pItemGroupObjClass->removeConnection(pConnection);
				for (int i = 0;i<listMap.size();i++)
				{
					scene()->removeItem(listMap[i]);
				}
				for (int i = 0;i<listMatch.size();i++)
				{
					scene()->removeItem(listMatch[i]);
				}
				pItemGroupfea->setConnection(NULL);
				scene()->removeItem(pConnection);
				delete pConnection;
			}
			scene()->removeItem(pItemGroupfea);
			delete pItemGroupfea;

		}
		else if(m_mode == RemoveRule)
		{
			QGraphicsItem* pItem = scene()->itemAt(mousePos);
			if(!pItem)
				return;
			E_ItemType eType = E_ItemType(pItem->data(0).toInt());
			if(eType == Map)
			{
				C_ItemMap* pItemMap = static_cast<C_ItemMap*>(pItem);
				C_ItemGroupObjectClass* pItemGroupObjClass = static_cast<C_ItemGroupObjectClass*>(pItemMap->getObjClassItem()->parentItem());
				QList<C_ItemConnection*> listConnection = pItemGroupObjClass->getConnection();
				for (int i = 0;i<listConnection.size();i++)
				{
					if(listConnection[i]->removeMapItem(pItemMap))
						break;
				}
				scene()->removeItem(pItemMap);
				delete pItemMap;
			}
			else if(eType == Match)
			{
				C_ItemMatch* pItemMatch = static_cast<C_ItemMatch*>(pItem);
				C_ItemGroupFeatureSet* pItemGroupFea = static_cast<C_ItemGroupFeatureSet*>(pItemMatch->getMainDataItem()->parentItem());
				QList<C_ItemMap*> listMap = pItemGroupFea->getConnectionItem()->getMapItem();
				for (int i = 0;i<listMap.size();i++)
				{
					scene()->removeItem(listMap[i]);
					pItemGroupFea->getConnectionItem()->removeMapItem(listMap[i]);
					delete listMap[i];
				}
				pItemGroupFea->getConnectionItem()->removeMatcjItem(pItemMatch);
				scene()->removeItem(pItemMatch);
				delete pItemMatch;
			}
			else if(eType == Connection)
			{
				C_ItemConnection* pConnection = static_cast<C_ItemConnection*>(pItem);
				C_ItemGroupFeatureSet* pItemGroupFeaSet = pConnection->getFeatureSetItemGroup();
				C_ItemGroupObjectClass* pItemGroupObjClass = pConnection->getObjectClassItemGroup();
				pItemGroupFeaSet->setConnection(NULL);
				pItemGroupObjClass->removeConnection(pConnection);
				QList<C_ItemMatch*> listMatch = pConnection->getMatchItem();
				QList<C_ItemMap*> listMap = pConnection->getMapItem();
				for (int i = 0;i<listMap.size();i++)
				{
					scene()->removeItem(listMap[i]);
				}
				for (int i = 0;i<listMatch.size();i++)
				{
					scene()->removeItem(listMatch[i]);
				}
				scene()->removeItem(pConnection);
				delete pConnection;
			}
		}
		else if(m_mode == EditRule)
		{
			QGraphicsItem* pItem = scene()->itemAt(mousePos);
			if(!pItem)
				return;
			E_ItemType eType = E_ItemType(pItem->data(0).toInt());
			if(eType == Match)
			{
				C_ItemMatch* pItemMatch = static_cast<C_ItemMatch*>(pItem);
				pItemMatch->showEditDlg();
			}
			else if(eType == Connection)
			{
				C_ItemConnection* pItemConnection = static_cast<C_ItemConnection*>(pItem);
				pItemConnection->showEditDlg();
			}
		}
		else
		{
			m_pStartPt = new QPointF(mousePos);
			m_pRubberLine = new QGraphicsLineItem();
			scene()->addItem(m_pRubberLine);
		}
	}
	
}

void C_ConvertCanvas::mouseMoveEvent(QMouseEvent *event)
{
	QPointF mousePos = mapToScene(event->pos());
	if(m_mode == Select)
	{
		QGraphicsView::mouseMoveEvent(event);
	}
	if(m_mode == RemoveRule)
	{
		
	}
	else if((m_mode == InsertFilterRule)||(m_mode == InsertMergeRule)||(m_mode == InsertMappingRule))
	{
		if(m_pStartPt == 0)
			return;
		m_pRubberLine->setLine(QLineF(*m_pStartPt, mousePos));
		if(m_mode == InsertFilterRule)
			m_pRubberLine->setPen(QPen(Qt::black,2));
		else if(m_mode == InsertMergeRule)
			m_pRubberLine->setPen(QPen(Qt::black,2,Qt::DashLine));
		else if(m_mode == InsertMappingRule)
			m_pRubberLine->setPen(QPen(Qt::black,1));
	}
	
}

void C_ConvertCanvas::mouseReleaseEvent(QMouseEvent *event)
{
	if(m_mode == Select)
	{
		QGraphicsView::mouseReleaseEvent(event);
	}
	if(m_pRubberLine != 0)
	{
		if((m_mode == InsertFilterRule)||(m_mode == InsertMappingRule)||(m_mode == InsertMergeRule))
		{
			QList<QGraphicsItem*> startItems = scene()->items(m_pRubberLine->line().p1());
			if(startItems.count() && startItems.first() == m_pRubberLine)
				startItems.removeFirst();
			QList<QGraphicsItem*> endItems = scene()->items(m_pRubberLine->line().p2());
			if(endItems.count() && endItems.first() == m_pRubberLine)
				endItems.removeFirst();
			scene()->removeItem(m_pRubberLine);
			delete m_pRubberLine;
			delete m_pStartPt;

			if(startItems.count()>0 && endItems.count()>0 && startItems.first() != endItems.first())
			{
				E_ItemType eTypeFrom = E_ItemType(startItems.first()->data(0).toInt());
				E_ItemType eTypeTo = E_ItemType(endItems.first()->data(0).toInt());
				// 插入连接（过滤规则）
				if(m_mode == InsertFilterRule)
				{
					if((eTypeFrom == FeatureSet)&&(eTypeTo == ObjectClass))
					{
						C_ItemFeatureSet* pItemFea = static_cast<C_ItemFeatureSet*>(startItems.first());
						C_ItemObjectClass* pItemObj = static_cast<C_ItemObjectClass*>(endItems.first());
						C_ItemGroupFeatureSet* pItemGroupFea = static_cast<C_ItemGroupFeatureSet*>(pItemFea->parentItem());
						if(!pItemGroupFea->getConnectionItem())
						{
							C_ItemConnection* pConnection = new C_ItemConnection(pItemFea, pItemObj);
							C_ItemGroupObjectClass* pItemGroupObj = static_cast<C_ItemGroupObjectClass*>(pItemObj->parentItem());
							pItemGroupFea->setConnection(pConnection);
							pItemGroupObj->addConnection(pConnection);
							scene()->addItem(pConnection);
						}
					}
				}
				// 插入映射
				else if(m_mode == InsertMappingRule)
				{
					QGraphicsItem* pItemFrom = startItems.first();
					QGraphicsItem* pItemTo = endItems.first();
					if((pItemFrom->parentItem()->data(0).toInt()==FeatureSetGroup)&&(pItemTo->parentItem()->data(0).toInt()==ObjectClassGroup))
					{

						C_ItemGroupFeatureSet* pItemGroupFea = static_cast<C_ItemGroupFeatureSet*>(pItemFrom->parentItem());
						C_ItemGroupObjectClass* pItemGroupObj = static_cast<C_ItemGroupObjectClass*>(pItemTo->parentItem());
						C_ItemConnection* pConnection = pItemGroupFea->getConnectionItem();
						if(pConnection)
						{
							if(pConnection->getObjectClassItemGroup() == pItemGroupObj)
							{
								C_ItemMap* pItemMap = pConnection->createMapItem(pItemFrom,pItemTo);
								if(pItemMap)
									scene()->addItem(pItemMap);
							}
						}
						
						else
						{
							QList<C_ItemConnection*> listConnection = pItemGroupObj->getConnection();
							bool bQualified = false;
							for (int i = 0;i<listConnection.size();i++)
							{
								QList<C_ItemMatch*> listMatch = listConnection[i]->getMatchItem();
								for (int j = 0;j<listMatch.size();j++)
								{
									C_ItemGroupFeatureSet* pItemGroupFea_2 = static_cast<C_ItemGroupFeatureSet*>(listMatch[j]->getSecondaryDataItem()->parentItem());
									if(pItemGroupFea_2 == pItemGroupFea)
									{
										C_ItemMap* pItemMap = listConnection[i]->createMapItem(pItemFrom,pItemTo);
										if(pItemMap)
											scene()->addItem(pItemMap);
										bQualified = true;
										break;
									}
								}
								if(bQualified)
									break;
							}
						}
					}
				}
				// 插入匹配融合规则线
				else
				{
					if((eTypeFrom == FeatureSet)&&(eTypeTo == FeatureSet))
					{
						C_ItemFeatureSet* pItemFeaFrom = static_cast<C_ItemFeatureSet*>(startItems.first());
						C_ItemFeatureSet* pItemFeaTo = static_cast<C_ItemFeatureSet*>(endItems.first());
						C_ItemConnection* pConnection = (static_cast<C_ItemGroupFeatureSet*>(pItemFeaTo->parentItem()))->getConnectionItem();
						if(pConnection)
						{
							C_ItemMatch* pItemMatch = pConnection->createMatchItem(pItemFeaTo,pItemFeaFrom);
							if(pItemMatch)
								scene()->addItem(pItemMatch);
						}
					}
				}
			}
			m_pStartPt = 0;
			m_pRubberLine = 0;
		}
	}
}

void C_ConvertCanvas::mouseDoubleClickEvent(QMouseEvent *event)
{
	QPointF mousePos = mapToScene(event->pos());
	QGraphicsItem* pItem = scene()->itemAt(mousePos);
	if(pItem)
	{
		bool bMapItemStateChanged = true;
		E_ItemType eType = E_ItemType(pItem->data(0).toInt());
		if(eType == Attribute)
		{
			C_ItemAttribute* pItemAttr = static_cast<C_ItemAttribute*>(pItem);
			pItemAttr->changeFoldState();
		}
		else if(eType == Geometry)
		{
			C_ItemGeometry* pItemGeo = static_cast<C_ItemGeometry*>(pItem);
			pItemGeo->changeFoldState();
		}
		else if(eType == Form)
		{
			C_ItemForm* pItemForm = static_cast<C_ItemForm*>(pItem);
			pItemForm->changeFoldState();
		}
		else
			bMapItemStateChanged = false;

		if(!bMapItemStateChanged)
			return;

		QGraphicsView::mouseDoubleClickEvent(event);
		QList<QGraphicsItem*> listItem = scene()->items();
		for (int i = 0;i<listItem.size();i++)
		{
			if(listItem[i]->data(0).toInt() == Map)
			{
				C_ItemMap* pItemMap = static_cast<C_ItemMap*>(listItem[i]);
				pItemMap->changeVisibility();
			}
		}
		/*E_ItemType eTypeGroup = E_ItemType(pItem->parentItem()->data(0).toInt());
		if(eTypeGroup == FeatureSetGroup)
		{
			C_ItemConnection* pConnection = (static_cast<C_ItemGroupFeatureSet*>(pItem->parentItem()))->getConnectionItem();
			if(pConnection == NULL)
				return;
			QList<C_ItemMap*> listMap = pConnection->getMapItem();
			for (int i = 0;i<listMap.size();i++)
			{
				listMap[i]->changeVisibility();
			}
		}
		else
		{
			QList<C_ItemConnection*> listConnection = (static_cast<C_ItemGroupObjectClass*>(pItem->parentItem())->getConnection());
			for (int i = 0;i<listConnection.size();i++)
			{
				QList<C_ItemMap*> listMap = listConnection[i]->getMapItem();
				for (int j = 0;j<listMap.size();j++)
				{
					listMap[j]->changeVisibility();
				}
			}
		}*/
	}
	
}

void C_ConvertCanvas::dragEnterEvent(QDragEnterEvent *event)
{
	if(event->mimeData()->hasFormat("itemObjectClass"))
	{
		m_bDragMode = true;
		event->acceptProposedAction();
	}
	else
	{
		event->ignore();
		QGraphicsView::dragEnterEvent(event);
	}
}

void C_ConvertCanvas::dragMoveEvent(QDragMoveEvent *event)
{
	if(event->mimeData()->hasFormat("itemObjectClass"))
	{
		event->acceptProposedAction();
		return;
	}
	event->ignore();
	QGraphicsView::dragMoveEvent(event);
}

void C_ConvertCanvas::dragLeaveEvent(QDragLeaveEvent *event)
{
	m_bDragMode = false;
	QGraphicsView::dragLeaveEvent(event);
}

void C_ConvertCanvas::dropEvent(QDropEvent *event)
{
	if(event->mimeData()->hasFormat("itemObjectClass"))
	{
		QByteArray dataArray = event->mimeData()->data("itemObjectClass");
		QDataStream dataStream(&dataArray,QIODevice::ReadOnly);
		QString sObjClassName;
		dataStream>>sObjClassName;

		// 画布添加对象类
		C_ItemGroupObjectClass* pItemObjClass = new C_ItemGroupObjectClass(sObjClassName);
		QMap<QString, QString> mapForm,mapClassAttr;
		mapForm.insert("Form_1","3DModel");
		mapClassAttr.insert("Attribute_1","double");
		pItemObjClass->setAttributeSubitem(mapClassAttr);
		pItemObjClass->setFormSubitem(mapForm);
		scene()->addItem(pItemObjClass);
		pItemObjClass->setPos(mapToScene(event->pos()));
		//m_listGroupObjClass.push_back(pItemObjClass);

		m_bDragMode = false;
		event->acceptProposedAction();
		return;
	}
	event->ignore();
	QGraphicsView::dropEvent(event);
}