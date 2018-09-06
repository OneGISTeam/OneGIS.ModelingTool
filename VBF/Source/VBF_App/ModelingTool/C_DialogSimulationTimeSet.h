#include <QDialog>
#include "ui_setSimulationTimeDialog.h"

class C_DialogSimulationTimeSet: public QDialog, public Ui::setSimulationTimeDialog
{
	Q_OBJECT
public:
	C_DialogSimulationTimeSet(QWidget* pParent = 0);
	~C_DialogSimulationTimeSet(void);
};
