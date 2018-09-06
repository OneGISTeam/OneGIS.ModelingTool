//新增：此头文件均为新增

#ifndef __VBF_MASKSPARKCALLBACK_H__
#define __VBF_MASKSPARKCALLBACK_H__

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>

#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Annotation/FeatureNode.h>

using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Symbology;


class CVBF_MaskFlickerCallback : public osg::NodeCallback
{
public:

	CVBF_MaskFlickerCallback(int ellaspFrame, osg::Vec4f& color)
	{
		m_ellaspFrame = ellaspFrame;
		m_CurFrame = 0;
		m_is = true;
		m_interval = 30;
	}

	virtual void operator()( osg::IVBF_SGNode* node, osg::NodeVisitor* nv )
	{
		m_CurFrame++;
		if(m_CurFrame>m_ellaspFrame) return ;

		FeatureNode* pfeaturenode = dynamic_cast<FeatureNode*>( node );

		if (m_is == true)
		{
			pfeaturenode->setDecoration("highlight");

		}
		else 
		{
			pfeaturenode->clearDecoration();
		}

		static int iCount = 10;
		iCount--;
		if(iCount == 0)
		{
			m_is = !m_is;
			iCount = m_interval;
		}
	
		traverse( node, nv );
	}

protected:

	int	  m_ellaspFrame;
	int	  m_interval;
	int   m_CurFrame;
	bool  m_is;

};

#endif

