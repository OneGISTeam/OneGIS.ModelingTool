#pragma once
#include <QDialog>
#include "ui_createObjectClassDialog.h"
#include "C_WidgetObjectClassCompose.h"
#include "C_WidgetObjectAttribute.h"
#include "C_WidgetObjectClassBasicInfo.h"
#include "C_WidgetObjectClassReference.h"
#include "C_WidgetObjectClassForm.h"
#include "C_WidgetObjectClassBehavior.h"

class QHBoxLayout;

class C_DialogObjectClassCreate: public QDialog, public Ui::CreateObjectClassDialog
{
	Q_OBJECT
public:
	C_DialogObjectClassCreate(QWidget* pParent = 0);
	~C_DialogObjectClassCreate(void);

private slots:
	void on_currentRow_changed(int rowCount);

private:
	void clearWidgets();

private:
	C_WidgetObjectClassCompose* m_pWidgetObjectClassCompose;
	C_WidgetObjectClassBasicInfo* m_pWidgetObjectClassBasicInfo;
	C_WidgetObjectClassReference* m_pWidgetObjectClassReference;
	C_WidgetObjectClassForm* m_pWidgetObjectClassForm;
	C_WidgetObjectAttribute* m_pWidgetObjectClassAttribute;
	C_WidgetObjectClassBehavior* m_pWidgetObjectClassBehavior;
	QHBoxLayout* m_pHBoxLayout;
};

