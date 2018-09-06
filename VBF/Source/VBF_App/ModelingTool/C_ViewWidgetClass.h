#pragma once
#include <QDockWidget>
#include "Include/IC_ViewWidget.h"
#include "C_ViewObjectClass.h"
#include "C_SearchClass.h"
#include "C_OperateClass.h"

/**
* @brief ¿‡ ”ÕºÕ£øø¥∞
*/
class C_ViewWidgetClass: public IC_ViewWidget
{
public:
	C_ViewWidgetClass(QWidget* pParent = 0);
	virtual ~C_ViewWidgetClass(void);

	virtual QString name();

	virtual void init();

private:
	C_ViewClass* m_pViewClass;
	C_SearchClass* m_pSearchClass;
	C_OperateClass* m_pOperateClass;
};