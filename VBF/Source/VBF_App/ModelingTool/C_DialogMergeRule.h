#ifndef C_DialogMergeRule_H
#define C_DialogMergeRule_H

#include <QDialog>
#include "ui_mergeRuleDlg.h"

class C_DialogMergeRule : public QDialog, public Ui::C_DialogMergeRule
{
	Q_OBJECT

public:
	C_DialogMergeRule(QWidget *parent = 0);
	~C_DialogMergeRule();

	void setMainAttribute(QStringList listAttr);

	void setSecondaryAttribute(QStringList listAttr);

	void setDefaultValue();

	private slots:
		void onBtnOK();

		void onBtnCancel();

public:
	bool m_bLocation, m_bAttribute, m_bForm;
	QString m_strMainAttr, m_strSecondaryAttr;
	int m_iSimiAttr,m_iSimiForm[3];
	double m_dRangeW, m_dRangeH;
};

#endif // C_DialogMergeRule_H
