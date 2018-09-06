#include "C_WidgetObjectForm.h"
#include "C_DialogFormPart.h"

C_WidgetObjectForm::C_WidgetObjectForm(QWidget* pParent)
	:QWidget(pParent)
{
	setupUi(this);
	connect(pushButton_editPublicFormPart, SIGNAL(clicked()), this, SLOT(on_editPublicFormPart_clicked()));
	connect(pushButton_editPrivateFormPart, SIGNAL(clicked()), this, SLOT(on_editPrivateFormPart_clicked()));
}


C_WidgetObjectForm::~C_WidgetObjectForm(void)
{
}

void C_WidgetObjectForm::on_editPublicFormPart_clicked()
{
	C_DialogFormPart dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}

void C_WidgetObjectForm::on_editPrivateFormPart_clicked()
{
	C_DialogFormPart dialog(this);
	if(dialog.exec() == QDialog::Accepted){

	}
}
