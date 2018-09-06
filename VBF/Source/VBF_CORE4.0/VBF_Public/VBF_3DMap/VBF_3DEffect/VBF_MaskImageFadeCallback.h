// 新增2012-04-23：图像蒙版Expand特效

#ifndef __VBF_MASKIMAGEFADECALLBACK_H__
#define __VBF_MASKIMAGEFADECALLBACK_H__

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>

#include <VBF_3DMap/VBF_Annotation/ImageOverlay.h>
#include <VBF_3DMap/VBF_3DEffect/Export>

using namespace osgEarth::Annotation;
using namespace osgEarth::Symbology;

class VBF_3DEFFECT_EXPORT ImageMaskFadeCallback : public osg::NodeCallback
{
public:

	ImageMaskFadeCallback(int ellaspFrame, bool isIn)
	{
		m_ellaspFrame	= ellaspFrame;
		m_CurFrame		= 0;
		m_isIn			= isIn;
		m_bAlphaComputed = false;		
	}

	virtual void operator()( osg::IVBF_SGNode* node, osg::NodeVisitor* nv )
	{
		osgEarth::Annotation::ImageOverlay* pOverlay = dynamic_cast<osgEarth::Annotation::ImageOverlay*>(node);
		if(!pOverlay) return;

		if(!m_bAlphaComputed)
		{
			m_Alpha = pOverlay->getAlpha();
			CalAlphaDelta();

			m_bAlphaComputed = true;
		}
		
		if(m_CurFrame > m_ellaspFrame) return;

		m_CurFrame++;

		pOverlay->setAlpha(m_Alpha);

		m_Alpha += m_alphadEla;

		traverse(node, nv);
	}

protected:

	// 计算蒙版渐入帧速率
	void CalAlphaDelta()
	{
		if(m_isIn)
		{
			m_alphadEla = (m_Alpha)/m_ellaspFrame;
			m_Alpha     = 0.0f;
		}
		else 
		{
			m_alphadEla = (0.0-m_Alpha)/m_ellaspFrame;
		}
	}

	int		m_ellaspFrame;
	int		m_CurFrame;
	float	m_Alpha;
	float	m_alphadEla;
	bool	m_bAlphaComputed;
	bool	m_isIn;	
};

#endif

