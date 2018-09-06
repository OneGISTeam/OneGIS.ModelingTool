#include "C_WidgetObjectBehavior.h"


C_WidgetObjectBehavior::C_WidgetObjectBehavior(QWidget* pParent)
	:QWidget(pParent)
{
	setupUi(this);
	//connect(pushButton_editPublicBehavior, SIGNAL(clicked()), this, SLOT(on_editPublicBehavior_clicked()));
	connect(pushButton_addPrivateBehavior, SIGNAL(clicked()), this, SLOT(on_addPrivateBehavior_clicked()));
}


C_WidgetObjectBehavior::~C_WidgetObjectBehavior(void)
{
}

void C_WidgetObjectBehavior::on_editPublicBehavior_clicked()
{

}

void C_WidgetObjectBehavior::on_addPrivateBehavior_clicked()
{
	C_DialogBehaviorAdd dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}
