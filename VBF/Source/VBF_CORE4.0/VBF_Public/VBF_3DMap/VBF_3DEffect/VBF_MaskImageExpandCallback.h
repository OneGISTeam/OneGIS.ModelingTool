// 新增2012-04-23：图像蒙版Expand特效

#ifndef __VBF_MASKIMAGEEXPANDCALLBACK_H__
#define __VBF_MASKIMAGEEXPANDCALLBACK_H__

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>

#include <VBF_3DMap/VBF_Annotation/ImageOverlay.h>
#include <VBF_3DMap/VBF_3DEffect/Export>

using namespace osgEarth::Annotation;
using namespace osgEarth::Symbology;

class VBF_3DEFFECT_EXPORT ImageMaskExpandCallback : public osg::NodeCallback
{
public:

	ImageMaskExpandCallback(int ellaspFrame, bool isEpand)
	{
		m_ellaspFrame = ellaspFrame;
		m_CurFrame = 0;
		m_bisEpand = isEpand;
		m_bBoundComputed = false;

		_overlay = NULL;
	}

	virtual void operator()( osg::IVBF_SGNode* node, osg::NodeVisitor* nv )
	{
		if(!m_bBoundComputed)
		{
			_overlay = dynamic_cast<osgEarth::Annotation::ImageOverlay*>( node );
			m_bBoundComputed = true;
			_bounds = _overlay->getBounds();
			CalExpandElta();
		}
		
		if(m_CurFrame>m_ellaspFrame) return ;
		m_CurFrame++;

		_overlay->setBounds( _bounds );

		_bounds.xMin() += (-m_fExpandElaX);
		_bounds.yMin() += (-m_fExpandElaY);
		_bounds.xMax() += (m_fExpandElaX);
		_bounds.yMax() += (m_fExpandElaY);

		traverse( node, nv );
	}

protected:
	//计算蒙版拉伸帧速率
	void CalExpandElta()
	{
		if(m_bisEpand)
		{
			m_fExpandElaX = (_bounds.width()/2)/m_ellaspFrame;
			m_fExpandElaY = (_bounds.height()/2)/m_ellaspFrame;

			m_boundsStart = _bounds.center2d();

			_bounds.xMin() = m_boundsStart.x();
			_bounds.yMin() = m_boundsStart.y();
			_bounds.xMax() = m_boundsStart.x();
			_bounds.yMax() = m_boundsStart.y();

		}
		else 
		{
			//舍入误差计算
			m_fExpandElaX = -(_bounds.width()/2)/m_ellaspFrame;
			m_fExpandElaY = -(_bounds.height()/2)/m_ellaspFrame;
		}
	}

	int	  m_ellaspFrame;
	int   m_CurFrame;

	float m_fExpandElaX;
	float m_fExpandElaY;

	bool  m_bisEpand;

	ref_ptr<osgEarth::Annotation::ImageOverlay> _overlay;
	osgEarth::Bounds _bounds;

	osg::Vec2d m_boundsStart;
	bool	m_bBoundComputed;

};

#endif

