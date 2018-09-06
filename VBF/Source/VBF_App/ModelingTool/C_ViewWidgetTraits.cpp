#include "C_ViewWidgetTraits.h"
#include "qtvariantproperty.h"
#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include "qteditorfactory.h"
#include "qtpropertybrowser.h"
#include "QMessageBox"
#include "QLineEdit"
#include "QBoxLayout"
#include "QPushButton"
#include "QMenu"
#include <QList>
#include <QFileDialog>

C_ViewWidgetTraits::C_ViewWidgetTraits(QWidget *parent)
	: IC_ViewWidget(parent)
{
 	currentObj = NULL;
 	variantPropertyManager = new QtVariantPropertyManager(this) ;        //管理特征变量
 	propertyItemsWidget = new QtTreePropertyBrowser(this); //特征窗口指针
 	variantFactory = new QtVariantEditorFactory(this);           // 特征变量生产的抽象工厂
 	enumManager = new QtEnumPropertyManager(this);
 	enumPropertyFacory = new QtEnumEditorFactory(this);
 	pathPropertyManager = new QtPathPropertyManager(this);
 	popUpEditorFactory = new QtPopupEditorFactory(this);
 
 
 	propertyItemsWidget->setFactoryForManager(variantPropertyManager,variantFactory);
 	propertyItemsWidget->setFactoryForManager(enumManager,enumPropertyFacory);
 	propertyItemsWidget->setFactoryForManager(pathPropertyManager,popUpEditorFactory);
 
 	//搜索框
 	QWidget *layoutWidget = new QWidget(this);
 	QLayout *vertivalLayout = new QVBoxLayout(layoutWidget);
 	QLineEdit *editControl1 = new QLineEdit(layoutWidget);
 	editControl1->setPlaceholderText(tr("Filter"));
 	connect(editControl1,SIGNAL(textChanged(const QString &)),this,SLOT(FilterTextChanged(const QString &)));
 
 	//移除按钮
 	QPushButton *removeCharac = new QPushButton(layoutWidget);
 	removeCharac->setStyleSheet("background-color: rgb(255, 255, 255);");    
 	removeCharac->setStyleSheet("border:none");   //隐藏边框线
 	removeCharac->setFlat(true);
 	removeCharac->setIcon(QIcon("./images/minus.png"));
 
 	QMenu *removeMenu = new QMenu(layoutWidget);
 
 	QAction *removeAttribute = new QAction(removeMenu);
 	removeAttribute->setText(tr("移除属性"));
 	QAction *removeForm = new QAction(removeMenu);
 	removeForm->setText(tr("移除形态"));
 	removeMenu->addAction(removeAttribute);
 	removeMenu->addAction(removeForm);
 	removeCharac->setMenu(removeMenu);
 	connect(removeAttribute,SIGNAL(triggered()),this,SLOT(removeAttribute()));
 	connect(removeForm,SIGNAL(triggered()),this,SLOT(removeForm()));
 	//添加,添加属性，添加形态
 	QPushButton *addCharac = new QPushButton(layoutWidget);
 	addCharac->setStyleSheet("background-color: rgb(255, 255, 255);");    
 	addCharac->setStyleSheet("border:none");   //隐藏边框线
 	addCharac->setFlat(true);
 	addCharac->setIcon(QIcon("./images/add.png"));
 
 	QMenu *addMenu = new QMenu(layoutWidget);
 	QAction *addAttribute = new QAction(addMenu);
 	addAttribute->setText(tr("添加属性"));
 	QAction *addForm = new QAction(addMenu);
 	addForm->setText(tr("添加形态"));
 	addMenu->addAction(addAttribute);
 	addMenu->addAction(addForm);
 	addCharac->setMenu(addMenu);
 	connect(addAttribute,SIGNAL(triggered()),this,SLOT(addAttribute()));
 	connect(addForm,SIGNAL(triggered()),this,SLOT(addForm()));
 
 	//展示值
 	QPushButton *showForm = new QPushButton(layoutWidget);
 	showForm->setStyleSheet("background-color: rgb(255, 255, 255);");    
 	showForm->setStyleSheet("border:none");   //隐藏边框线
 	showForm->setIcon(QIcon("./images/model.png"));
 	connect(showForm,SIGNAL(clicked()),this,SLOT(showFormModel()));
 	QLayout *horizonLayout = new QHBoxLayout(layoutWidget);
 	horizonLayout->addWidget(editControl1);
 	horizonLayout->addWidget(addCharac);
 	horizonLayout->addWidget(removeCharac);
 	horizonLayout->addWidget(showForm);
 
 	vertivalLayout->addItem(horizonLayout);
 	vertivalLayout->addWidget(propertyItemsWidget);
 	layoutWidget->setLayout(vertivalLayout);
 	setWidget(layoutWidget);
}

C_ViewWidgetTraits::~C_ViewWidgetTraits()
{

}

void C_ViewWidgetTraits::valueChanged( QtProperty*,const QVariant& )
{

}

void C_ViewWidgetTraits::formValueChanged( QtProperty* ,const QVariant& )
{

}

void C_ViewWidgetTraits::partValueChanged( QtProperty* ,const QVariant& )
{

}

void C_ViewWidgetTraits::enumPropertyValueChanged( QtProperty*,int val )
{

}

void C_ViewWidgetTraits::popUpPropertyValueChanged( QtProperty*,const QString& )
{

}

void C_ViewWidgetTraits::FilterTextChanged( const QString &filterValue )
{

}

void C_ViewWidgetTraits::removeAttribute()
{

}

void C_ViewWidgetTraits::removeForm()
{

}

void C_ViewWidgetTraits::addAttribute()
{

}

void C_ViewWidgetTraits::addForm()
{

}

void C_ViewWidgetTraits::showFormModel()
{

}

void C_ViewWidgetTraits::showCharac( void* pObj )
{
	//展示所有特征信息
	ClearInfo();
	if(m_bShowTrait){
			showBasicInfo(pObj);
			showPosistion(pObj);
//			showAttribute(pObj);
//			showForm(pObj);
//			showStructure(pObj);
	}
	connect(variantPropertyManager,SIGNAL(valueChanged(QtProperty*,const QVariant&)),this,SLOT(valueChanged(QtProperty*,const QVariant&)));
	connect(enumManager,SIGNAL(valueChanged(QtProperty* ,int)),this,SLOT(enumPropertyValueChanged(QtProperty*,int)));
	connect(pathPropertyManager,SIGNAL(showEditDialogSignal(QtProperty*,const QString&)),this,SLOT(popUpPropertyValueChanged(QtProperty*,const QString&)));
}

void C_ViewWidgetTraits::ClearInfo()
{
	getVariantPropertyMananger()->clear();
	getPropertyItemWidget()->clear();
}

void C_ViewWidgetTraits::showBasicInfo( void* pObj)
{
	currentObj = pObj; //一个characDock只能有一个currentObj
	QtTreePropertyBrowser* propertyBrowser = getPropertyItemWidget();
	QtVariantPropertyManager* variantPropertyManager = getVariantPropertyMananger();
	//显示 对象的名称
	std::string name ="abc";     //pObj->getName();
	QtVariantProperty* propertyName;
	propertyName = variantPropertyManager->addProperty(QVariant::String,tr("对象名称"));
	QVariant value = QString::fromStdString(name);
	propertyName->setValue(value);
	propertyBrowser->addProperty(propertyName);

	//显示对象OID
	QtVariantProperty* propertyOID;
	propertyOID = variantPropertyManager->addProperty(QVariant::String,tr("OID"));
	propertyOID->setValue(QString::fromStdString("128393232"/*pObj->getOID()*/));
	propertyBrowser->addProperty(propertyOID);
}

void C_ViewWidgetTraits::editBasicInfo()
{

}

void C_ViewWidgetTraits::showPosistion( void* )
{
	QtTreePropertyBrowser* propertyBrowser = getPropertyItemWidget();
	QtVariantPropertyManager* variantPropertyManager = getVariantPropertyMananger();

	//获取C_STObject的位置数据
	//Position* pos = pObj->getPosition();
	//Format posFormat = pos->getPositionFormat();
	//AC_PositionBase::Type posType = pos->getType();
	//C_SpatialReference* PosReference =  pos->getSpatialReference();
	//std::string PosReferenceName = PosReference->GetName().c_str();

	//显示对象的空间位置，第一行先显示format（xyz，BLH，BL，XY）,第二三（四五）行再显示对象的空间位置的值
	QtGroupPropertyManager* groupManager = new QtGroupPropertyManager(propertyBrowser);
	QtProperty *groupSPosition = groupManager->addProperty(tr("空间位置"));

	QStringList sPosTypeNames;
	sPosTypeNames<<"Static"<<"Dynamic"<<"Function"<<"Linker";
	QtProperty* posTypeProperty = enumManager->addProperty(tr("坐标类型"));
	enumManager->setEnumNames(posTypeProperty,sPosTypeNames);
	enumManager->setValue(posTypeProperty,0/*posType*/);
	groupSPosition->addSubProperty(posTypeProperty);


	QStringList sPosFormatNames;
	sPosFormatNames<<"LB"<<"XY"<<"ρθ"<<"LBH"<<"rθΦ"<<"LBRxRy"<<"XYRxRy"<<"LBHRxRyRz"<<"XYZRxRyRz"<<"BL"<<"BLH";
	QtProperty *posFormatProperty = enumManager->addProperty(tr("坐标格式"));
	int index =sPosFormatNames.indexOf(QString::fromStdString("LBH"/*posFormat*/));
	enumManager->setEnumNames(posFormatProperty,sPosFormatNames);
	enumManager->setValue(posFormatProperty,index);
	groupSPosition->addSubProperty(posFormatProperty);



	QtVariantProperty *posReferenceProperty = variantPropertyManager->addProperty(QVariant::String,tr("坐标参考"));
	posReferenceProperty->setValue(QString::fromStdString("WGS84"/*PosReferenceName*/));
	groupSPosition->addSubProperty(posReferenceProperty);

	QtProperty* positionValue = pathPropertyManager->addProperty(tr("坐标值"));
	groupSPosition->addSubProperty(positionValue);
	//得到points的坐标值，
	//将Geometry 转为点
/*	AC_Geometry* geometry = currentObj->getPosition()->getGeometry();
	vector<C_Point> points;
	if ( (geometry->geometryType().compare("Point")==0) )
	{
		C_Point* pPoint = dynamic_cast<C_Point*>((geometry));
		if(pPoint){
			points.push_back(*pPoint);
		}
	}
	else if ( geometry->geometryType().compare("Curve")==0)
	{
		C_Curve* pCurve = dynamic_cast<C_Curve*>(geometry);
		if(pCurve)
			pCurve->points(points);
	}
	else if ( geometry->geometryType().compare("Polygon")==0)
	{
		C_Polygon* pPolygon = dynamic_cast<C_Polygon*>(geometry);
		if(pPolygon){
			pPolygon->exteriorRing()->points(points);
		}
	}
	QString value;
	for (int i=0;i<points.size();i++)
	{
		QString coord = QString("(%1,%2)").arg(points[i].x()).arg(points[i].y());
		value.append(coord);
	}
	*/
	QString value;
	QString coord = QString("(%1,%2)").arg(122.3).arg(32.45);
	value.append(coord);


	pathPropertyManager->setValue(positionValue,value);
	propertyBrowser->addProperty(groupSPosition);
}

void C_ViewWidgetTraits::showAttribute( void* )
{
	QtTreePropertyBrowser* propertyBrowser = getPropertyItemWidget();
	QtVariantPropertyManager* variantPropertyManager = getVariantPropertyMananger();


	QtGroupPropertyManager* PropertyMangager = new QtGroupPropertyManager(propertyBrowser);
	QtProperty* AttributeGroupProperty = PropertyMangager->addProperty(tr("属性项"));

	//C_AttributeSet& attSet = pObj->getAttributeSet();
	//std::vector<AC_Attribute*> attributeVector = attSet.getAllAttributes();
	//for (int i=0;i<attributeVector.size();i++)
	//{
	//	std::string attributeName = attributeVector[i]->getField()->name();
	//	QVariant::Type type = attributeVector[i]->getField()->type();
	//	QtVariantProperty* attributeProperty = variantPropertyManager->addProperty(type,QString::fromStdString(attributeName));
	//	if (type==QVariant::Double)
	//	{
	//		double attributeValue = attributeVector[i]->getVariant()->toDouble();
	//		attributeProperty->setValue(attributeValue);
	//	}

	//	if (type==QVariant::Int)
	//	{
	//		int attributeValue = attributeVector[i]->getVariant()->toInt();
	//		attributeProperty->setValue(attributeValue);
	//	}

	//	if (type==QVariant::Bool)
	//	{
	//		bool attributeValue = attributeVector[i]->getVariant()->toBool();
	//		attributeProperty->setValue(attributeValue);
	//	}

	//	if (type==QVariant::String)
	//	{
	//		std::string attributeValue = attributeVector[i]->getVariant()->toString();
	//		qDebug()<<QString::fromStdString(attributeValue);
	//		attributeProperty->setValue(QString::fromStdString(attributeValue));
	//	}				
	//	AttributeGroupProperty->addSubProperty(attributeProperty);
	//}
	QVariant::Type type1;
	type1=QVariant::Double;
	QtVariantProperty* attributeProperty1 = variantPropertyManager->addProperty(type1,QString::fromStdString("高度"));
	attributeProperty1->setValue(123.22);
	AttributeGroupProperty->addSubProperty(attributeProperty1);




	propertyBrowser->addProperty(AttributeGroupProperty);
}

void C_ViewWidgetTraits::showForm( void* )
{

}

void C_ViewWidgetTraits::showStructure( void* )
{

}

void C_ViewWidgetTraits::closeEvent( QCloseEvent *event )
{

}

QString C_ViewWidgetTraits::name()
{
	return "ui_viewwidget_charac";
}

void C_ViewWidgetTraits::init()
{
	showCharac(NULL);
}
