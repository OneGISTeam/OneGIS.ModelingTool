#include "C_WidgetObjectClassBehavior.h"

C_WidgetObjectClassBehavior::C_WidgetObjectClassBehavior(QWidget* pParent)
	:QWidget(pParent)
{
	setupUi(this);
	//connect(pushButton_editPublicBehavior, SIGNAL(clicked()), this, SLOT(on_editPublicBehavior_clicked()));
	connect(pushButton_addPrivateBehavior, SIGNAL(clicked()), this, SLOT(on_addPrivateBehavior_clicked()));
}


C_WidgetObjectClassBehavior::~C_WidgetObjectClassBehavior(void)
{
}

void C_WidgetObjectClassBehavior::on_editPublicBehavior_clicked()
{

}

void C_WidgetObjectClassBehavior::on_addPrivateBehavior_clicked()
{
	C_DialogBehaviorAdd dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}
