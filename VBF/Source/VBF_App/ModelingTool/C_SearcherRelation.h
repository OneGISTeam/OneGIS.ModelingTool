#pragma once
#include <QWidget>
#include "ui_searcherrelationwidget.h"

class C_SearcherRelation: public QWidget, public Ui::SearcherRelation
{
public:
	C_SearcherRelation(QWidget* pParent = 0);
	~C_SearcherRelation(void);

private:

};

