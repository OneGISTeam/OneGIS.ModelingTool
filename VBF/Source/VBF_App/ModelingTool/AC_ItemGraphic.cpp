#include "AC_ItemGraphic.h"
#include "QFontMetrics"

AC_ItemGraphic::AC_ItemGraphic()
{
	m_iFontSize = 12;
}

AC_ItemGraphic::~AC_ItemGraphic(void)
{
}

void AC_ItemGraphic::setFontSize(const QString& sName)
{
	while (1)
	{
		QFontMetricsF metrics = QFont("¿¬Ìå", m_iFontSize, QFont::Normal);
		QRectF rect = metrics.boundingRect(sName);
		int iWidth = rect.width();
		if(iWidth>120)
			m_iFontSize--;
		else
			break;
	}
}