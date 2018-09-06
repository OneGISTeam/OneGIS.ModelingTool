#pragma once
#include <QDockWidget>
#include "Include/IC_ViewWidget.h"
#include "C_SearcherRelation.h"
#include "C_OperateRelation.h"
#include "C_ViewRelation.h"

/**
* @brief πÿœµ ”ÕºÕ£øø¥∞
*/
class C_ViewWidgetRelation: public IC_ViewWidget
{
public:
	C_ViewWidgetRelation(QWidget* pParent = 0);
	~C_ViewWidgetRelation(void);

	virtual QString name();

	virtual void init();

private:
	C_SearcherRelation* m_pSearcherRelation;
	C_OperateRelation* m_pOperateRelation;
	C_ViewRelation* m_pViewRelation;
};

