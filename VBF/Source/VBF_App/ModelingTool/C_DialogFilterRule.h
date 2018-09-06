#ifndef C_DialogFilterRule_H
#define C_DialogFilterRule_H

#include <QDialog>
#include "ui_filterRuleDlg.h"

class C_DialogFilterRule : public QDialog, public Ui::C_DialogFilterRule
{
	Q_OBJECT

public:
	C_DialogFilterRule(QString sName, QWidget *parent = 0);
	~C_DialogFilterRule();

	void setAttributeList(QStringList listName);

	QString getFilterExpression(){return m_lineEdit->text();};

private:

	void init();

	private slots:

		void onBtnClear();

		void onBtnSave();

		void onDoubleClickItem(QListWidgetItem*);

		void onClick_1();
		void onClick_2();
		void onClick_3();
		void onClick_4();
		void onClick_5();
		void onClick_6();
		void onClick_7();

};

#endif // C_DialogFilterRule_H
