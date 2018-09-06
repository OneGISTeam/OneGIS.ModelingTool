#pragma once
#include <QFrame>
#include <QLabel>

class C_MessageFrame: public QFrame
{
public:
	enum MessageLevel
	{
		INFO = 0,
		WARNING = 1,
		CRITICAL = 2
	};

	C_MessageFrame(QWidget* pParent = 0);
	~C_MessageFrame(void);

	void setMessage(QString msg);

private:
	QString m_msg;
	QLabel* m_pLabel;
};

