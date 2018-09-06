//***************************************************************************************
// FileName： VBF_3DEnvironment.h
// Function： 3D标图接口，负责管理标图的文档
// Author:    武玉国
// Date:      2013-07-04
//***************************************************************************************

#ifndef __VBF_3DENVIRONMENT_H__
#define __VBF_3DENVIRONMENT_H__


#include <VBF_MainCtrl/IVBF_3DMainCtrl.h>
#include <VBF_Display/IVBF_3DDisplay.h>
#include <VBF_Plot/IVBF_3DPlot.h>

class CVBF_3DEnvironment;

// 全局函数
CVBF_3DEnvironment& VBF_Get3DEnvironment();

class CVBF_3DEnvironment  
{
public:
	CVBF_3DEnvironment()
	{
		m_pI3DMainCtrl	= NULL;
		m_pI3DDisplay	= NULL;
		m_pI3DPlot		= NULL;
	}

	virtual ~CVBF_3DEnvironment()
	{
		Release();
	}

public:
	void Init(IVBF_3DMainCtrl* pI3DMainCtrl)
	{
		if(NULL==pI3DMainCtrl) return;
		
		m_pI3DMainCtrl	= pI3DMainCtrl;
		m_pI3DDisplay   = (IVBF_3DDisplay*)m_pI3DMainCtrl->QueryInterface(VBF_INTERFACE_3DDISPLAY);
		m_pI3DPlot      = (IVBF_3DPlot*)m_pI3DMainCtrl->QueryInterface(VBF_INTERFACE_3DPLOT);
	}

	void Release()
	{
		m_pI3DMainCtrl	= NULL;
		m_pI3DDisplay	= NULL;
		m_pI3DPlot		= NULL;
	}

public:
	IVBF_3DMainCtrl*	m_pI3DMainCtrl;
	IVBF_3DDisplay*		m_pI3DDisplay;
	IVBF_3DPlot*		m_pI3DPlot;
};



#define VBF_DYNCREATE_ENVIRONMENT  \
	CVBF_3DEnvironment g_3DEnvironment; \
	CVBF_3DEnvironment& VBF_Get3DEnvironment() { return g_3DEnvironment; }

#endif
