#ifndef __VBF_IMAGE2DFADECALLBACK_H__
#define __VBF_IMAGE2DFADECALLBACK_H__

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>

class CVBF_Image2DFadeCallback : public osg::NodeCallback
{
public:
    CVBF_Image2DFadeCallback(int nElapsFrame, bool bIn, float fAlpha)
    {
		m_nElapsFrame	= nElapsFrame;
		m_nCurrFrame	= 0;
		m_bFadeIn		= bIn;
		m_fAlpha		= fAlpha;
		m_bAlphaComputed= false;
		m_colors		= new osg::Vec4Array(1);
		m_geode			= NULL;

		CalAlphaDelta();
	}
    
    virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv)
    {
		if(!m_bAlphaComputed)
		{
			m_geode = dynamic_cast<osg::IVBF_SGNodeGeometry*>(node);
			if(NULL==m_geode) return;
			m_bAlphaComputed = true;
		}

		m_nCurrFrame++;
		if(m_nCurrFrame > m_nElapsFrame) 
		{
			return;
		}

		m_fAlpha += m_fAlphaDelta;
		osg::Geometry* geom = dynamic_cast<osg::Geometry*>( m_geode->getDrawable(0) );
		if(geom)
		{           
			(*m_colors)[0].set(1.0f, 1.0f, 1.0f, m_fAlpha);
			geom->setColorArray(m_colors);
			geom->setColorBinding(osg::Geometry::BIND_OVERALL);
		}
    }
	
protected:

	void CalAlphaDelta()
	{
		if(m_bFadeIn)
		{
			m_fAlphaDelta = (m_fAlpha)/m_nElapsFrame;
			m_fAlpha = 0.0f;
		}
		else 
		{
			m_fAlphaDelta = (0.0-m_fAlpha)/m_nElapsFrame;
		}
	}

protected:	
	int							m_nElapsFrame;
	bool						m_bFadeIn;
	bool						m_bAlphaComputed;
	float						m_fAlphaDelta;
	float						m_fAlpha;
	osg::Vec4Array*				m_colors;
	int							m_nCurrFrame;
	ref_ptr<osg::IVBF_SGNodeGeometry>	m_geode;

};

#endif
