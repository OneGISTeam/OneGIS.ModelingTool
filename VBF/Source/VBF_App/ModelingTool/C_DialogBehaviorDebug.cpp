#include "C_DialogBehaviorDebug.h"


C_DialogBehaviorDebug::C_DialogBehaviorDebug(QWidget* pParent)
	:QDialog(pParent)
{
	setupUi(this);

	//����Ϊ��ģ̬�Ի���
	setModal(false);
	//���öԻ���ر�ʱdelete������ģ̬�Ի���new֮���޷�delete����ڴ�й©
	setAttribute(Qt::WA_DeleteOnClose);

	Qt::WindowFlags flags=Qt::Dialog;
	flags |=Qt::WindowMinimizeButtonHint;
	flags |=Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
}


C_DialogBehaviorDebug::~C_DialogBehaviorDebug(void)
{
}
