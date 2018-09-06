//*******************************************************************
// FileName��VBF_UpdateCallbackLineStipple.h
// Function���㻮�ߵĸ��»ص�
// Author��  ��Ө
// Date��    2013-11-19
//*******************************************************************

#ifndef __VBF_UPDATE_CALLBACK_LINE_STIPPLE_H__
#define __VBF_UPDATE_CALLBACK_LINE_STIPPLE_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/StateAttributeCallback>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLineStipple.h>


//-----------------------------------------------------------------------------
// �����ࣺCVBF_UpdateCallbackLineStipple()
// ���������㻮�ߵĸ��»ص�
//-----------------------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_UpdateCallbackLineStipple : public osg::StateAttributeCallback
{
public:
	CVBF_UpdateCallbackLineStipple(unsigned short nPattern);

	virtual void operator() (osg::StateAttribute* pAttr, osg::NodeVisitor* nv);
	
private:

	// �û����õı���
	unsigned short		m_pnStipplePattern[16];

	// ÿ֡���µı���
	int					m_nStippleIndex;
};

#endif
