#ifndef __VBF_IMAGE2DSCALECALLBACK_H__
#define __VBF_IMAGE2DSCALECALLBACK_H__

#include "VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h"
#include "VBF_Engine/VBF_SceneGraph/Array"
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <Types/Vec3f>
#include "Types/VBF_Matrix.h"
#include "VBF_3DCom/VBF_3DEffect/IVBF_3DEffectImage2D.h"

class CVBF_Image2DScaleCallback : public osg::NodeCallback
{
public:
	CVBF_Image2DScaleCallback(int nElapsFrame, const char* szScaleType, float scale)
    {
		strcpy(m_szScaleType, szScaleType);

		m_ellaspFrame	= nElapsFrame;
		m_Scale			= scale;
		m_CurFrame		= 0;
		m_ScaleElta		= 0.0;

		m_bScaleComputed = false;
		m_OrigScale      = osg::Vec3d(1.0, 1.0, 1.0);
		//m_matrix       = osg::Matrixd(1,0,0,0,1,0,0,0,1);
		_mt				 = NULL;
	}
    
    virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv)
    {
		if(!m_bScaleComputed)
		{
			_mt = dynamic_cast<osg::IVBF_SGNodeGroupTransformMatrix*>( node );
			m_matrix =_mt->getMatrix();
			m_OrigScale = m_matrix.getScale();

			CalScaleElta();
			m_bScaleComputed = true;
		}

		if(m_CurFrame>m_ellaspFrame) return ;
		m_CurFrame++;
			
        if ( _mt )
        { 
			_mt->setMatrix(osg::Matrixd::scale(m_Scale,m_Scale,m_Scale)*m_matrix); //
        }
		m_Scale+=m_ScaleElta;

        traverse( node, nv );
    }
    
protected:
	void CalScaleElta()
	{

		if( strcmp(m_szScaleType, VBF_3DEFFECT_ACTION_SCALEIN)==0 )
		{
			m_ScaleElta = m_Scale/m_ellaspFrame;
			m_Scale	 = 0.0;
		}
		else if( strcmp(m_szScaleType, VBF_3DEFFECT_ACTION_SCALEOUT)==0 )
		{
			m_ScaleElta = (-m_Scale)/m_ellaspFrame;
		}
		else if( strcmp(m_szScaleType, VBF_3DEFFECT_ACTION_SCALE)==0 )
		{
			m_ScaleElta = (m_Scale-m_OrigScale.x())/m_ellaspFrame;
			m_Scale		= m_OrigScale.x();
			//m_Scale = m_Scale-m_OrigScale.x();
		}
	}

	int					m_ellaspFrame;
	int					m_CurFrame;

	float				m_Scale;
	float				m_ScaleElta;

	bool				m_bScaleComputed;

//	const char*			m_szScaleType;
	char				m_szScaleType[128];

	osg::Vec3d			m_OrigScale;

	osg::Matrixd		m_matrix;
	
	ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix> _mt;

};

#endif
