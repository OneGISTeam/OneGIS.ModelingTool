#ifndef C_VIEWCHARAC_H
#define C_VIEWCHARAC_H
#include "qtpropertybrowser.h"
#include <QDockWidget>
#include <QMap>
#include "IC_ViewWidget.h"

/************************************************************************/
/* �������ڻ�ȱ��C_STObjec* ,ȫ��ʹ��void*
	
*/
/************************************************************************/


class C_ViewWidgetTraits : public IC_ViewWidget
{
public:
	C_ViewWidgetTraits(QWidget *parent);
	~C_ViewWidgetTraits();
	void showTrait(bool bShow = true);

public:
	class QtTreePropertyBrowser* propertyItemsWidget;        // ��������ָ��

	class QtVariantPropertyManager *variantPropertyManager;  // ������������,����QtVariantProperty

	class QtVariantEditorFactory  *variantFactory;            // �������������ĳ��󹤳�

	class QtEnumPropertyManager   *enumManager ;               // ���������б����
	class QtEnumEditorFactory     *enumPropertyFacory;         // �����б�������󹤳�

	class QtPathPropertyManager	  *pathPropertyManager;       // ����ʽ�༭�Ի����ֵ
	class QtPopupEditorFactory    *popUpEditorFactory;        // �����Ի���

public:
	QtVariantPropertyManager* getVariantPropertyMananger(){return variantPropertyManager;}
	QtTreePropertyBrowser* getPropertyItemWidget(){return propertyItemsWidget;}
	QtVariantEditorFactory* getVariantManager(){return variantFactory;}	

public slots:
	/**
     * @brief �����Կ�����Ըı�ʱ���� -- ֻ��� QtVariantProperty
     */
	void valueChanged(QtProperty*,const QVariant&);
	/**
     * @brief �����Կ�����Ըı�ʱ���� --����̬�����У����е�ֵ�ı䴥���˺���
     */
	void formValueChanged(QtProperty* ,const QVariant&);
	/**
     * @brief �����Կ�����Ըı�ʱ���� --����̬�����У����е�ֵ�ı䴥���˺���
     */
	void partValueChanged(QtProperty* ,const QVariant&);
	/**
     * @brief �����Կ�����Ըı�ʱ���� -- ��Բ�ͬ�ı����ֱ𴥷�
     */
	void enumPropertyValueChanged(QtProperty*,int val);

	void popUpPropertyValueChanged(QtProperty*,const QString&);

	/**
     * @brief Filter�ı���ֵ�ı�ʱ����
     */
	void FilterTextChanged(const QString &filterValue);

	/**
     * @brief �Ƴ�������,ע��widget��propertiesֻ����һ����property����name��oid��λ�ã��������
	 *        Ҫ���þ������������ٴα�����
     */
	void removeAttribute();

	/**
     * @brief �Ƴ���̬
     */
	void removeForm();
	
	/**
     * @brief ���������         
     */
	void addAttribute();

	/**
     * @brief �����̬     
     */
	void addForm();

	void showFormModel();


public:

	
	void showCharac(void*);

	/**
     * @brief ��������������Ϣ
     */
	void ClearInfo();

	/**
     * @brief չʾ����Ļ�����Ϣ
     * @brief ��name ��OID��SRID��TIMEID
     */
	void showBasicInfo(void*);

	/**
     * @brief �༭����Ļ�����Ϣ
     */
	void editBasicInfo();

	/**
     * @brief չʾ�����ʱ��λ����Ϣ
     *        λ�ø�ʽ�������б���xyz BLH BL XYZ
	 *        ʱ��λ�ã��ַ�����double�͡�YYYY-mm-dd��hh��mm��ss��
	 *        ��̬��alpha��beta��gama��
     */
	void showPosistion(void*);

	/**
     * @brief չʾ�����������Ϣ
     */
	void showAttribute(void*);

	/**
     * @brief չʾ�����ʱ��λ����Ϣ
     *        λ�ø�ʽ�������б���xyz BLH BL XYZ
	 *        ʱ��λ�ã��ַ�����double�͡�YYYY-mm-dd��hh��mm��ss��
	 *        ��̬��alpha��beta��gama��
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
