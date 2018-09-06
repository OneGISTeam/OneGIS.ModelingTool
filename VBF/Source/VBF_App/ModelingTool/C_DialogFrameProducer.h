#pragma once
#include <QDialog>
#include "ui_frameProducerDialog.h"

class C_DialogFrameProducer: public QDialog, public Ui::FrameProducerDialog
{
	Q_OBJECT
public:
	C_DialogFrameProducer(QWidget* pParent = 0);
	~C_DialogFrameProducer(void);
};

