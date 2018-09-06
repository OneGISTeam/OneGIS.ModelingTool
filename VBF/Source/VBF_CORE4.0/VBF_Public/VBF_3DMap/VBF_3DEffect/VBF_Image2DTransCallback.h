#ifndef __VBF_IMAGE2DTRANSCALLBACK_H__
#define __VBF_IMAGE2DTRANSCALLBACK_H__

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include "Types/Vec3f"
#include <VBF_Engine/VBF_SceneGraph/Image>
#include "Types/VBF_Matrixf.h"
#include "VBF_3DCom/VBF_3DEffect/IVBF_3DEffectImage2D.h"

class CVBF_Image2DTransCallback : public osg::NodeCallback
{
public:
	CVBF_Image2DTransCallback(int nElapsFrame, const char* szTransType, const osg::Image* image, osg::Vec2f& position, int width, int height)
    {
		m_ellaspFrame	= nElapsFrame;
		m_CurFrame		= 0;
		m_position		= position;
		m_winwidth		= width;
		m_winheight		= height;

		strcpy(m_szTransType, szTransType);
		m_bTransComputed= false;
		m_TransElta		= osg::Vec3f(0.0,0.0,0.0);
		m_image			= image;
	}
    
    virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv)
    {
		osg::IVBF_SGNodeGroupTransformMatrix* mt = dynamic_cast<osg::IVBF_SGNodeGroupTransformMatrix*>( node );
		if(NULL==mt) return;

		if(!m_bTransComputed)
		{	
			m_matrix = mt->getMatrix();
			CalTransElta();
			m_bTransComputed = true;
		}

		if(m_CurFrame>m_ellaspFrame) return ;
		m_CurFrame++;
       
		m_matrix = mt->getMatrix();
		mt->setMatrix(m_matrix*osg::Matrixf::translate(m_TransElta));

        traverse( node, nv );
    }
    
protected:
	void CalTransElta()
	{
		float x = m_position.x()*m_winwidth;
		float y = m_position.y()*m_winheight;

		float imageX = m_image->s();
		float imageY = m_image->t();

		float deltax = 0.0;
		float deltay = 0.0;

		if( strcmp(m_szTransType, VBF_3DEFFECT_ACTION_DOWNIN)==0 )
		{
			deltay= (-y+ imageY+m_winheight)/(float)m_ellaspFrame;
		}
		else if( strcmp(m_szTransType, VBF_3DEFFECT_ACTION_UPOUT)==0 )
		{
			deltay= (y+ imageY)/(float)m_ellaspFrame;
		}
		else if( strcmp(m_szTransType, VBF_3DEFFECT_ACTION_UPIN)==0)
		{
			deltay= -(y+ imageY)/(float)m_ellaspFrame;
		}
		else if(strcmp(m_szTransType, VBF_3DEFFECT_ACTION_DOWNOUT)==0 )
		{
			deltay= -(-y+ imageY+m_winheight)/(float)m_ellaspFrame;
		}
		else if( strcmp(m_szTransType, VBF_3DEFFECT_ACTION_RIGHTIN)==0 )
		{
			deltax= -(-x+ imageX+m_winwidth)/(float)m_ellaspFrame;
		}
		else if( strcmp(m_szTransType, VBF_3DEFFECT_ACTION_LEFTOUT)==0 )
		{
			deltax= -(x+ imageX)/(float)m_ellaspFrame;
		}
		else if( strcmp(m_szTransType, VBF_3DEFFECT_ACTION_LEFTIN)==0 )
		{
			deltax= (x+ imageX)/(float)m_ellaspFrame;
		}
		else if( strcmp(m_szTransType, VBF_3DEFFECT_ACTION_RIGHTOUT)==0 )
		{
			deltax= (-x+ imageX+m_winwidth)/(float)m_ellaspFrame;
		}
		else if( strcmp(m_szTransType, VBF_3DEFFECT_ACTION_TRANS)==0 )
		{
			osg::Vec3f lastmx = m_matrix.getTrans();
			deltax= (x-lastmx.x())/(float)m_ellaspFrame;
			deltay= (y-lastmx.y())/(float)m_ellaspFrame;
		}
		m_TransElta = osg::Vec3f(deltax, deltay, 0.0);
	}

	int					m_ellaspFrame;
	int					m_CurFrame;
	int					m_winwidth;
	int					m_winheight;
	bool				m_bTransComputed;
	osg::Vec3f			m_TransElta;
	osg::Vec2f			m_position;
	char				m_szTransType[128];
	const osg::Image*	m_image;

	osg::Matrix			m_matrix;
};

#endif
