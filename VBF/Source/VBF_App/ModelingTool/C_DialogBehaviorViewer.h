#ifndef C_DialogBehaviorViewer_H
#define C_DialogBehaviorViewer_H

#include <QDialog>
#include "ui_behaviorViewerDlg.h"

class C_DialogBehaviorViewer : public QDialog, public Ui::C_DialogBehaviorViewer
{
	Q_OBJECT

public:
	C_DialogBehaviorViewer(QWidget *parent = 0);
	~C_DialogBehaviorViewer();

private:
	void init();

	private slots:
		void onBtnOK();
};

#endif // C_DialogBehaviorViewer_H
