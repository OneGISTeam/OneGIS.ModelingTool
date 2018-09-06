//***************************************************************************************
// FileName��VBF_ComponentImpl.h
// Function������ӿڵ�ģ��ʵ��
// Author:   ��Ө
// Date:     2012-11-01
//***************************************************************************************

#ifndef __VBF_COMPONENT_IMPL_H__
#define __VBF_COMPONENT_IMPL_H__

#include "VBF_MainCtrl/IVBF_Component.h"
#include <VBF_Macros.h>

class CVBF_ComponentImpl : public IVBF_Component 
{
public:
	CVBF_ComponentImpl(IVBF_MainCtrl* pIMainCtrl) { m_pIMainCtrl = pIMainCtrl; }
	virtual ~CVBF_ComponentImpl() {}
	
	virtual void         Release()					{ delete this; }
	virtual bool         Init()						{ return true; }
	virtual bool		 Finish()					{ return true; }

	virtual int          GetInterfaceCount()		{ return 0; }
	virtual const char*  GetInterfaceID(int nIndex)	{ return NULL; }
	virtual void*        QueryInterface(const char* szInterfaceID) { return NULL; }

	virtual const char*  GetComponentID()			{ return NULL; }
    virtual const char*  GetComponentDesc()			{ return NULL; }

    virtual bool   SetCopyRight(const char* szUser,const char* szPassword) { return true; }

protected:
	IVBF_MainCtrl*		m_pIMainCtrl;		// ��������ڵ����أ�������3DMainCtrl, Ҳ����������������
};



#endif 
