#pragma once

#include "VBF_3DMap/VBF_Terrain/VBF_Map.h"
#include "VBF_Display/VBF_Viewer/IVBF_Viewer.h"
#include "GraphicsWindowQt.h"

using namespace std;

class C_GlobalGIS: public CVBF_Referenced
{
public:
	C_GlobalGIS(GLWidget* pWidget);
	virtual ~C_GlobalGIS(void);

	void createViewer();

	IVBF_Viewer* getViewer() {return m_opViewer.get();}

	void render();

protected:
	void reconfigure(IVBF_View* pView);

private:
	observer_ptr<IVBF_Viewer> m_opViewer;

#ifdef WINDOW_USING_MFC
	HWND m_hWnd;
#endif

#ifdef WINDOW_USING_QT
	GLWidget* m_pGLWidget;
#endif

	ref_ptr<osg::GraphicsContext> m_ipGC;
};

