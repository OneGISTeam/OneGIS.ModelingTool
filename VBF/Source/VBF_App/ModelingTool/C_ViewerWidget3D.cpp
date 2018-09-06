#include "C_ViewerWidget3D.h"
#include <QPaintEvent>

C_ViewerWidget3D::C_ViewerWidget3D(QWidget* pParent)
	:GLWidget(pParent)
{
	m_pGlobalGIS = new C_GlobalGIS(this);
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer.start(20);
}


C_ViewerWidget3D::~C_ViewerWidget3D(void)
{
}

void C_ViewerWidget3D::paintEvent( QPaintEvent* event )
{
	//if(m_pGlobalGIS.valid()) m_pGlobalGIS->render();
	//Æô¶¯Ö¡Ñ­»·Ê±ÖÓ
	/*if(!m_pGlobalGIS.valid()){
		m_pGlobalGIS = new C_GlobalGIS(this);
		connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
		m_timer.start(20);
	}	*/
	if(m_pGlobalGIS.valid()) m_pGlobalGIS->render();
}
