#pragma once
#include <QDockWidget>
#include "IC_ViewWidget.h"
#include "ui_createRelationManualWidget.h"

class C_ViewWidgetRelationCreateManual: public IC_ViewWidget, public Ui::CreateRelationManualWidget
{
	Q_OBJECT
public:
	C_ViewWidgetRelationCreateManual(QWidget* pParent = 0);
	~C_ViewWidgetRelationCreateManual(void);

	virtual QString name();

	virtual void init();

private slots:
	void on_createButton_clicked();
};

