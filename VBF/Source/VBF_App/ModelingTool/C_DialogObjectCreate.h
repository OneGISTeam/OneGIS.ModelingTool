#pragma once
#include <QDialog>
#include "ui_createObjectDialog.h"
#include "C_WidgetObjectBasicInfo.h"
#include "C_WidgetObjectReference.h"
#include "C_WidgetObjectPosition.h"
#include "C_WidgetObjectAttribute.h"
#include "C_WidgetObjectForm.h"
#include "C_WidgetObjectCompose.h"
#include "C_WidgetObjectRelation.h"
#include "C_WidgetObjectBehavior.h"

class QHBoxLayout;

class C_DialogObjectCreate: public QDialog, public Ui::CreateObjectDialog
{
	Q_OBJECT
public:
	C_DialogObjectCreate(QWidget* pParent = 0);
	~C_DialogObjectCreate(void);

private slots:
	void on_currentRow_changed(int rowCount);

private:
	void clearWidgets();

private:
	C_WidgetObjectBasicInfo* m_pWidgetBasicInfo;
	C_WidgetObjectReference* m_pWidgetReference;
	C_WidgetObjectPosition* m_pWidgetPostion;
	C_WidgetObjectAttribute* m_pWidgetAttribute;
	C_WidgetObjectForm* m_pWidgetForm;
	C_WidgetObjectCompose* m_pWidgetCompose;
	C_WidgetObjectRelation* m_pWidgetRelation;
	QHBoxLayout* m_pHBoxLayout;
	C_WidgetObjectBehavior* m_pWidgetBehavior;
};

