#include "C_WidgetObjectClassForm.h"
#include "C_DialogFormPart.h"

C_WidgetObjectClassForm::C_WidgetObjectClassForm(QWidget* pParent)
	:QWidget(pParent)
{
	setupUi(this);
	connect(pushButton_editPublicFormPart, SIGNAL(clicked()), this, SLOT(on_editPublicFormPart_clicked()));
	connect(pushButton_editPrivateFormPart, SIGNAL(clicked()), this, SLOT(on_editPrivateFormPart_clicked()));
}


C_WidgetObjectClassForm::~C_WidgetObjectClassForm(void)
{
}

void C_WidgetObjectClassForm::on_editPublicFormPart_clicked()
{
	C_DialogFormPart dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}

void C_WidgetObjectClassForm::on_editPrivateFormPart_clicked()
{
	C_DialogFormPart dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}