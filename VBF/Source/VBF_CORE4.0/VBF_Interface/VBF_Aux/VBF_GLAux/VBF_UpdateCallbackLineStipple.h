//*******************************************************************
// FileName：VBF_UpdateCallbackLineStipple.h
// Function：点划线的更新回调
// Author：  杜莹
// Date：    2013-11-19
//*******************************************************************

#ifndef __VBF_UPDATE_CALLBACK_LINE_STIPPLE_H__
#define __VBF_UPDATE_CALLBACK_LINE_STIPPLE_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/StateAttributeCallback>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrLineStipple.h>


//-----------------------------------------------------------------------------
// 定义类：CVBF_UpdateCallbackLineStipple()
// 类描述：点划线的更新回调
//-----------------------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_UpdateCallbackLineStipple : public osg::StateAttributeCallback
{
public:
	CVBF_UpdateCallbackLineStipple(unsigned short nPattern);

	virtual void operator() (osg::StateAttribute* pAttr, osg::NodeVisitor* nv);
	
private:

	// 用户设置的变量
	unsigned short		m_pnStipplePattern[16];

	// 每帧更新的变量
	int					m_nStippleIndex;
};

#endif
