#pragma once
#include <QDockWidget>
#include "Include/IC_ViewWidget.h"
#include "C_ViewObject.h"
#include "C_SearcherObject.h"
#include "C_OperateObject.h"

/**
* @brief ∂‘œÛ ”ÕºÕ£øø¥∞
*/
class C_ViewWidgetObject: public IC_ViewWidget
{
public:
	C_ViewWidgetObject(QWidget* pParent = 0);
	virtual ~C_ViewWidgetObject(void);

	virtual QString name();

	virtual void init();

private:
	C_ViewObject* m_pViewObject;
	C_SearcherObject* m_pSearcherObject;
	C_OperateObject* m_pOperatorObject;
};

