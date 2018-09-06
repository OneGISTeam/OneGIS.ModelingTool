#ifndef OSGEARTH_ENGINE_OSGTERRAIN_DYNAMIC_LOD_SCALE_CALLBACK_H
#define OSGEARTH_ENGINE_OSGTERRAIN_DYNAMIC_LOD_SCALE_CALLBACK_H 1

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Engine/VBF_SceneGraph/CullStack>

// 该回调计算LOD比例，基于瓦片到相机距离和分辨率减低的程度。分辨率降低的越多，远处对象的LOD比例越大。
// A good range for the fall-off number is 0..5.
struct CMP_DynamicLODScaleCallback : public osg::NodeCallback 
{
	CMP_DynamicLODScaleCallback( float fallOff ) : m_fFallOff(fallOff) { }
	virtual ~CMP_DynamicLODScaleCallback() { }

	void operator()( osg::IVBF_SGNode* pINode, osg::NodeVisitor* nv )
	{
		osg::CullStack* cs = dynamic_cast<osg::CullStack*>(nv);
		if ( cs == NULL)
		{
			traverse( pINode, nv );
			return;
		}

		osg::IVBF_SGNodeGroupLOD* pINodeLod = static_cast<osg::IVBF_SGNodeGroupLOD*>( pINode );
		osg::Vec3 vCenter = pINodeLod->getCenter(); 

		osg::Vec3 vEye = nv->getEyePoint();
		osg::Vec3 eyeVec = vEye; eyeVec.normalize();

		float has = osg::clampAbove( vEye.length() - 6356752.3142f, 0.0f );
		float fCenterToEye = nv->getDistanceToViewPoint(vCenter, false);
		float fBoundSphereToEye = fCenterToEye - pINodeLod->getChild(0)->getBound().radius();

		float fScaleAdjust = 1.0f;
		if ( fBoundSphereToEye > has )
		{
			float denom = osg::maximum(0.1f, (1.0f/m_fFallOff)) * 10000.0f;
			fScaleAdjust = osg::clampBetween( log10f(fBoundSphereToEye/denom), 1.0f, 3.0f );
		}

		float fLodScale = cs->getLODScale();
		cs->setLODScale( fLodScale * fScaleAdjust );
		traverse( pINode, nv );
		cs->setLODScale( fLodScale );

	}

	float m_fFallOff;
};


#endif //OSGEARTH_ENGINE_OSGTERRAIN_DYNAMIC_LOD_SCALE_CALLBACK_H
