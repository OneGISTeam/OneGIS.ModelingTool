#include "C_ViewWidgetRelationCreateManual.h"
#include "C_DialogRelationCreate.h"

C_ViewWidgetRelationCreateManual::C_ViewWidgetRelationCreateManual(QWidget* pParent)
	:IC_ViewWidget(pParent)
{
	setupUi(this);
	connect(this->toolButton_create, SIGNAL(clicked()), this, SLOT(on_createButton_clicked()));
}


C_ViewWidgetRelationCreateManual::~C_ViewWidgetRelationCreateManual(void)
{
}

QString C_ViewWidgetRelationCreateManual::name()
{
	return UI_VIEWWIDGET_RELATIONMANUALCREATE;
}

void C_ViewWidgetRelationCreateManual::init()
{

}

void C_ViewWidgetRelationCreateManual::on_createButton_clicked()
{
	C_DialogRelationCreate dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}
