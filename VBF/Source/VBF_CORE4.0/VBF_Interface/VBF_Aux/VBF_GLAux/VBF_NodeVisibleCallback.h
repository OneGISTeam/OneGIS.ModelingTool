//***************************************************************************************
// FileName：VBF_NodeVisibleCallback.h
// Function：Node可见性Cull回调
// Author:   杜莹
// Date:     2012-04-24
//***************************************************************************************

#ifndef __VBF_NODE_VISIBLE_CALLBACK_H__
#define __VBF_NODE_VISIBLE_CALLBACK_H__

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include "VBF_FadeNode.h"
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>


using namespace osg;

// 设置节点的可见性
class VBF_GLAUX_EXPORT CVBF_NodeVisibleCallback : public osg::NodeCallback
{
public:
	CVBF_NodeVisibleCallback(bool& bVisible);
	virtual ~CVBF_NodeVisibleCallback();

	// 设置可见性
	void SetVisible(bool bVisible);

	virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);   
	
private:
	bool&		m_bVisible;
	bool*		m_pbVisible;
};

// 设置节点的可见性
class VBF_GLAUX_EXPORT CVBF_CullCallbackDrawableVisible : public osg::Drawable::CullCallback
{
public:
	CVBF_CullCallbackDrawableVisible(bool& bVisible);
	virtual ~CVBF_CullCallbackDrawableVisible();

	// 设置可见性
	void SetVisible(bool bVisible);

	virtual bool cull(osg::NodeVisitor* nv, osg::Drawable* drawable, osg::RenderInfo* renderInfo) const;
	
private:
	bool&		m_bVisible;
	bool*		m_pbVisible;
};

#endif
