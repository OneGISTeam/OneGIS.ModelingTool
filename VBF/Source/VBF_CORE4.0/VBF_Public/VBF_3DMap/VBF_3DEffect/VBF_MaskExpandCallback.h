//新增：此头文件均为新增

#ifndef __VBF_MASKEXPANDCALLBACK_H__
#define __VBF_MASKEXPANDCALLBACK_H__

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawableGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>

#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_Annotation/FeatureNode.h>

using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Symbology;


class CVBF_MaskExpandCallback : public osg::NodeCallback
{
public:
	CVBF_MaskExpandCallback(int ellaspFrame, bool isEpand)
	{
		m_ellaspFrame	= ellaspFrame;
		m_CurFrame		= 0;
		m_bisEpand		= isEpand;

		CalExpandElta();
		
	}

	virtual void operator()( osg::IVBF_SGNode* node, osg::NodeVisitor* nv )
	{
		m_CurFrame++;
		if(m_CurFrame>m_ellaspFrame) return ;

		osg::IVBF_SGNodeGroupTransformMatrix* pmat = dynamic_cast<osg::IVBF_SGNodeGroupTransformMatrix*>( node );
		if(!pmat) return;

		pmat->setMatrix(osg::Matrixd::scale(m_fExpand,m_fExpand,m_fExpand));	
		m_fExpand+=m_fExpandEla;
		if(m_fExpand <= 0.0) 
			m_fExpand = 0.0;

		traverse( node, nv );
	}

protected:
	//计算蒙版拉伸帧速率
	void CalExpandElta()
	{
		if(m_bisEpand)
		{
			m_fExpandEla = (1.0)/m_ellaspFrame;
			m_fExpand	 = 0.0;
		}
		else 
		{
			//舍入误差计算
			m_fExpandEla = (-1.1)/m_ellaspFrame;
			m_fExpand	 = 1.0;
		}
	}


	int	  m_ellaspFrame;
	int   m_CurFrame;
	bool  m_bisEpand;
	float m_fExpand;
	float m_fExpandEla;

};

#endif

