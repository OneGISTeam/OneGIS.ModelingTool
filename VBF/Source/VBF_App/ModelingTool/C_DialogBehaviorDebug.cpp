#include "C_DialogBehaviorDebug.h"


C_DialogBehaviorDebug::C_DialogBehaviorDebug(QWidget* pParent)
	:QDialog(pParent)
{
	setupUi(this);

	//设置为非模态对话框
	setModal(false);
	//设置对话框关闭时delete，避免模态对话框new之后无法delete造成内存泄漏
	setAttribute(Qt::WA_DeleteOnClose);

	Qt::WindowFlags flags=Qt::Dialog;
	flags |=Qt::WindowMinimizeButtonHint;
	flags |=Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
}


C_DialogBehaviorDebug::~C_DialogBehaviorDebug(void)
{
}
