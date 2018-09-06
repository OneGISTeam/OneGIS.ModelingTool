#ifndef C_VIEWCHARAC_H
#define C_VIEWCHARAC_H
#include "qtpropertybrowser.h"
#include <QDockWidget>
#include <QMap>
#include "IC_ViewWidget.h"

/************************************************************************/
/* 由于现在还缺乏C_STObjec* ,全部使用void*
	
*/
/************************************************************************/


class C_ViewWidgetTraits : public IC_ViewWidget
{
public:
	C_ViewWidgetTraits(QWidget *parent);
	~C_ViewWidgetTraits();
	void showTrait(bool bShow = true);

public:
	class QtTreePropertyBrowser* propertyItemsWidget;        // 特征窗口指针

	class QtVariantPropertyManager *variantPropertyManager;  // 管理特征变量,管理QtVariantProperty

	class QtVariantEditorFactory  *variantFactory;            // 特征变量生产的抽象工厂

	class QtEnumPropertyManager   *enumManager ;               // 管理下拉列表变量
	class QtEnumEditorFactory     *enumPropertyFacory;         // 下拉列表变量抽象工厂

	class QtPathPropertyManager	  *pathPropertyManager;       // 弹出式编辑对话框的值
	class QtPopupEditorFactory    *popUpEditorFactory;        // 弹出对话框

public:
	QtVariantPropertyManager* getVariantPropertyMananger(){return variantPropertyManager;}
	QtTreePropertyBrowser* getPropertyItemWidget(){return propertyItemsWidget;}
	QtVariantEditorFactory* getVariantManager(){return variantFactory;}	

public slots:
	/**
     * @brief 当属性框的属性改变时触发 -- 只针对 QtVariantProperty
     */
	void valueChanged(QtProperty*,const QVariant&);
	/**
     * @brief 当属性框的属性改变时触发 --在形态集合中，所有的值改变触发此函数
     */
	void formValueChanged(QtProperty* ,const QVariant&);
	/**
     * @brief 当属性框的属性改变时触发 --在形态集合中，所有的值改变触发此函数
     */
	void partValueChanged(QtProperty* ,const QVariant&);
	/**
     * @brief 当属性框的属性改变时触发 -- 针对不同的变量分别触发
     */
	void enumPropertyValueChanged(QtProperty*,int val);

	void popUpPropertyValueChanged(QtProperty*,const QString&);

	/**
     * @brief Filter文本框值改变时触发
     */
	void FilterTextChanged(const QString &filterValue);

	/**
     * @brief 移除属性项,注意widget的properties只有其一级的property，如name，oid，位置，属性项等
	 *        要想获得具体的子项，则需再次遍历，
     */
	void removeAttribute();

	/**
     * @brief 移除形态
     */
	void removeForm();
	
	/**
     * @brief 添加属性项         
     */
	void addAttribute();

	/**
     * @brief 添加形态     
     */
	void addForm();

	void showFormModel();


public:

	
	void showCharac(void*);

	/**
     * @brief 清除对象的所有信息
     */
	void ClearInfo();

	/**
     * @brief 展示对象的基本信息
     * @brief 有name ，OID，SRID，TIMEID
     */
	void showBasicInfo(void*);

	/**
     * @brief 编辑对象的基本信息
     */
	void editBasicInfo();

	/**
     * @brief 展示对象的时空位置信息
     *        位置格式（下拉列表）：xyz BLH BL XYZ
	 *        时间位置：字符串（double型、YYYY-mm-dd：hh：mm：ss）
	 *        姿态（alpha，beta，gama）
     */
	void showPosistion(void*);

	/**
     * @brief 展示对象的属性信息
     */
	void showAttribute(void*);

	/**
     * @brief 展示对象的时空位置信息
     *        位置格式（下拉列表）：xyz BLH BL XYZ
	 *        时间位置：字符串（double型、YYYY-mm-dd：hh：mm：ss）
	 *        姿态（alpha，beta，gama）
     */
	void showForm(void*);

	void showStructure(void*);

public:
	virtual void closeEvent(QCloseEvent *event);

	virtual QString name();

	virtual void init();

private:
	bool m_bShowTrait;
	void* currentObj;
	
};

#endif // C_VIEWCHARAC_H
