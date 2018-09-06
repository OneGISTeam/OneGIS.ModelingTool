#pragma once
#include "Include/IC_Wnd.h"
#include "C_ConvertCanvas.h"

class C_ConvertWnd : public IC_Wnd
{
public:
	C_ConvertWnd(QWidget* pParent = 0);
	~C_ConvertWnd(void);

	virtual QString name();

	virtual void init();

	virtual QWidget* statusWidget() {return NULL;};

	C_ConvertCanvas* getConvertCanvasPtr(){return m_pConvertCanvas;};

private:
	C_ConvertCanvas* m_pConvertCanvas;
};

