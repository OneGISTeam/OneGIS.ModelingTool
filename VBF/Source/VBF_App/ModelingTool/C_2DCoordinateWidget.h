#pragma once
#include <QWidget>
#include "ui_2dcoordinatewidget.h"

class C_2DCoordinateWidget: public QWidget, public Ui::CoordinateWidget
{
public:
	C_2DCoordinateWidget(QWidget* pParent = 0);
	~C_2DCoordinateWidget(void);
};

