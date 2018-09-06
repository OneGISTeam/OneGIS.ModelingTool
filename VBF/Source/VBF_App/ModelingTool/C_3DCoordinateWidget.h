#pragma once
#include "ui_3dcoordinatewidget.h"

class C_3DCoordinateWidget: public QWidget, public Ui::CoordinateWidget3D
{
public:
	C_3DCoordinateWidget(QWidget* pParent = 0);
	~C_3DCoordinateWidget(void);
};

