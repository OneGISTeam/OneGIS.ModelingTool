#ifndef __VBF_MASKFADECALLBACK_H__
#define __VBF_MASKFADECALLBACK_H__

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>

#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Annotation/FeatureNode.h>

using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Symbology;

class CVBF_MaskFadeCallback : public osg::NodeCallback
{
public:
	CVBF_MaskFadeCallback(Feature* pFeature, int nDurationFrames, bool isIn, float alpha, float extrusionHeight)
		: m_pFeature(pFeature), m_ellaspFrame(nDurationFrames), m_isIn(isIn), m_Alpha(alpha), m_Height(extrusionHeight)
	{
		m_CurFrame = 0;

		CalAlphadElta();
		CalHeightElta();
	}

	virtual void operator()( osg::IVBF_SGNode* node, osg::NodeVisitor* nv )
	{		
		FeatureNode* pFeatureNode = dynamic_cast<FeatureNode*>( node );	
		if(!pFeatureNode) return;

		m_CurFrame++;
		if(m_CurFrame>m_ellaspFrame) return;		

		Style& FeatureStyle = (Style&)(*m_pFeature->style());

		FeatureStyle.getOrCreate<ExtrusionSymbol>()->height()          = m_Height;
		FeatureStyle.getOrCreate<PolygonSymbol>()->fill()->color().w() = m_Alpha;
		FeatureStyle.getOrCreate<LineSymbol>()->stroke()->color().w()  = m_Alpha;

		pFeatureNode->setFeature(m_pFeature.get());
	
		m_Alpha  += m_alphadEla;
		m_Height += m_HeightEla;

		traverse( node, nv );
	}

protected:
	//计算蒙版渐入帧速率
	void CalAlphadElta()
	{
		if(m_isIn)
		{
			m_alphadEla = (m_Alpha)/m_ellaspFrame;
			m_Alpha = 0.0f;
		}
		else 
		{
			m_alphadEla = (0.0-m_Alpha)/m_ellaspFrame;
		}
	}
	//计算蒙版挤出高度帧速率
	void CalHeightElta()
	{
		if(m_isIn)
		{
			m_HeightEla = (m_Height)/m_ellaspFrame;
			m_Height = 0.0f;
		}
		else 
		{
			m_HeightEla = (0.0-m_Height)/m_ellaspFrame;
		}
	}
	int	  m_ellaspFrame;
	int   m_CurFrame;
	bool  m_isIn;
	float m_alphadEla;
	float m_Alpha;
	float m_Height;
	float m_HeightEla;
	
	observer_ptr<Feature> m_pFeature;
};

#endif
