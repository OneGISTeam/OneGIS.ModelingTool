#include "C_WidgetObjectPosition.h"

C_WidgetObjectPosition::C_WidgetObjectPosition(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	connect(cbTimeFormat,SIGNAL(currentIndexChanged(int)),this,SLOT(cbTimeFormatChanged(int)));
	connect(cbSpatialFormat,SIGNAL(currentIndexChanged(int)),this,SLOT(cbPostionFormatChanged(int)));
}

C_WidgetObjectPosition::~C_WidgetObjectPosition()
{

}

void C_WidgetObjectPosition::cbTimeFormatChanged( int index)
{
	switch (index)
	{
	case 0:
		
		break;
	}
}

void C_WidgetObjectPosition::cbPostionFormatChanged( int index )
{
	switch (index)
	{
	case 0: //xyz
		PostionTable->horizontalHeaderItem(1)->setText("X");
		PostionTable->horizontalHeaderItem(2)->setText("Y");
		PostionTable->setColumnHidden(3,false);
		PostionTable->horizontalHeaderItem(3)->setText("Z");
		break;
	case 1: //LBH
		PostionTable->horizontalHeaderItem(1)->setText("L");
		PostionTable->horizontalHeaderItem(2)->setText("B");
		PostionTable->setColumnHidden(3,false);
		PostionTable->horizontalHeaderItem(3)->setText("H");
	break;
	case 2: //LBH
		PostionTable->horizontalHeaderItem(1)->setText("X");
		PostionTable->horizontalHeaderItem(2)->setText("Y");
		PostionTable->setColumnHidden(3,true);
		break;
	case 3: //LBH
		PostionTable->horizontalHeaderItem(1)->setText("L");
		PostionTable->horizontalHeaderItem(2)->setText("B");
		PostionTable->setColumnHidden(3,true);
		break;
	}
}

void C_WidgetObjectPosition::setCoulumnHide( int coulumn)
{
	if (PostionTable->isColumnHidden(coulumn))
	{
		return;
	}
	else
		PostionTable->setColumnHidden(coulumn,true);
}
