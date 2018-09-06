#ifndef __VBF_3DEFFECT_IMAGE3D_H__
#define __VBF_3DEFFECT_IMAGE3D_H__

#include "VBF_3DCom/VBF_3DEffect/IVBF_3DEffectImage3D.h"
#include "VBF_3DEffectImpl.h"
#include <VBF_Display/IVBF_3DDisplay.h>

#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_SGDB/ReadFile>
#include <VBF_Engine/VBF_SceneGraph/VBF_Camera.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Display/VBF_Viewer/VBF_ViewerSimple.h>
#include <VBF_3DMap/VBF_EarthUtil/ObjectLocator>
#include <VBF_3DMap/VBF_Terrain/ElevationQuery.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrDepth.h>
#include <VBF_Engine/VBF_SceneGraph/ValueObject>
#include <VBF_3DMap/VBF_3DEffect/Export>

#include <map>
using namespace std;
using namespace osgEarth::Util;

class VBF_3DEFFECT_EXPORT CVBF_3DEffectImage3D : public CVBF_3DEffectImpl<IVBF_3DEffectImage3D>
{
public:	
	CVBF_3DEffectImage3D(IVBF_3DMainCtrl* pI3DMainCtrl, IVBF_View* pView, osg::IVBF_SGNodeGroup* pParentNode);
	virtual ~CVBF_3DEffectImage3D();	

	// �������ļ���װ����Ч����ĳ�ʼ����Ϣ
	virtual bool LoadFromXML(TiXmlElement* pElemEffect);

	// ִ����Ч����Ķ��������������Ӵ������ļ�Ԫ���л�ȡ
	virtual bool StartFromXML(TiXmlElement* pElemAction);

	// ���õ�������
	virtual void SetGeoPosition(double L, double B, double H, const char* szAltitudeClamp);

	// ���һ��LOD�ӽڵ㣬ͼ���ļ��������ֺ���ʧ�����߾���(��λ����)
	virtual bool AddLodChild(const char* szImgFn, float fRangeMin, float fRangeMax, bool bAutoScaleToScreen, float fSizeInWorld, float fScale);

	// ��ʼִ�ж���
	virtual bool StartAction(const char* szType, int nDurationFrames);	
	
	
private:	
	bool GetHeight(double L, double B, double& H);


private:	
	osgEarth::ElevationQuery		m_ElevQuery;		// ��ȡ�߳�ֵ	

	float							m_fAlpha;
	char							m_szAltitudeClamp[64];	// �߳�ֵ��ȡ��ʽ
	osg::Vec3d						m_vGeoCoord;			// ��������

	// Ϊ�����ǩͼ�������֣�ʹ��LOD�ڵ�
	ref_ptr<osg::IVBF_SGNodeGroup>		m_pNodeLod;			// �����ӵ�߶Ⱦ����ڵ�Ŀ��أ��������������߾���
	ref_ptr<ObjectLocatorNode>	m_pNodePlacer;		
};

class VBF_3DEFFECT_EXPORT CVBF_ImageStateSetUpdateCallback : public osg::StateSet::Callback
{
public:
	CVBF_ImageStateSetUpdateCallback(IVBF_3DDisplay* pI3DDisplay) : m_pI3DDisplay(pI3DDisplay)
	{
	}	
	
    virtual void operator()(osg::StateSet* state, osg::NodeVisitor* nv)
    { 
        if(m_pI3DDisplay && state && nv->getVisitorType()==osg::NodeVisitor::UPDATE_VISITOR)
		{
			// �������ߵĸ����ǣ������Ƿ���z-write��������������洹ֱʱ�������Ʋ������
			osg::Depth* pDepth = dynamic_cast<osg::Depth*>( state->getAttribute(osg::StateAttribute::DEPTH) );
			if(pDepth) 
			{
                //!! �˴����󣡣���
				CVBF_Viewpoint viewpoint = m_pI3DDisplay->GetViewpoint();
				bool bWriteMask = ( fabs(viewpoint.getPitch()) < 50);				

				pDepth->setWriteMask(bWriteMask);  
				pDepth->setFunction(bWriteMask? osg::Depth::LESS : osg::Depth::ALWAYS);
			}
        }
    }

private:
	IVBF_3DDisplay*		m_pI3DDisplay;
};

class VBF_3DEFFECT_EXPORT CVBF_Image3DCullCallback : public osg::NodeCallback
{
public:
	CVBF_Image3DCullCallback(osg::IVBF_Camera* pCamera, CVBF_Map* pMap, IVBF_3DDisplay* pI3DDisplay, bool bBillboard) 
		: m_pCamera(pCamera), m_pMap(pMap), m_pI3DDisplay(pI3DDisplay), m_bBillboard(bBillboard) {}

	virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv)
    { 
		bool bVisible = false;

		if(node && nv->getVisitorType()==osg::NodeVisitor::CULL_VISITOR && m_pCamera.valid() && m_pMap.valid() && m_pI3DDisplay)
        {
			float fRangeMin, fRangeMax;
			if( node->getUserValue<float>("LodRangeMin", fRangeMin) && node->getUserValue<float>("LodRangeMax", fRangeMax) )
			{
				// ��ȡ�ӵ�ĵ������꣬�����ӵ�߶Ⱦ����ڵ�Ŀ��أ��������������߾���
				osg::Vec3d vEyePtWorld, vCenterWorld, vUp;
				osgEarth::GeoPoint vEyePtGeo;
				m_pCamera->getViewMatrixAsLookAt(vEyePtWorld, vCenterWorld, vUp);	
			//	m_pMap->worldPointToMapPoint(vEyePtWorld, vEyePtGeo);	
				vEyePtGeo.fromWorld(m_pMap->getSRS(), vEyePtWorld);

				bVisible = ( vEyePtGeo.z() >= fRangeMin && vEyePtGeo.z() <= fRangeMax ); 

				// �Ƿ�ʹ�ò�����
				osg::IVBF_SGNodeGroupTransformMatrix* pTransform = dynamic_cast<osg::IVBF_SGNodeGroupTransformMatrix*>(node);
				if(m_bBillboard && pTransform)
				{
					CVBF_Viewpoint viewpoint = m_pI3DDisplay->GetViewpoint();
					double dHeading = osg::DegreesToRadians( viewpoint.getHeading() );
					double dPitch   = osg::DegreesToRadians( viewpoint.getPitch() );

					osg::Matrix matOld = pTransform->getMatrix();
					osg::Vec3d  vScale = matOld.getScale();
					
					pTransform->setMatrix( osg::Matrix::scale(vScale.x(), vScale.y(), vScale.z()) * osg::Matrix::rotate(dPitch, 1, 0, 0) * osg::Matrix::rotate(-dHeading, 0, 0, 1) );
				}
			}			
		}

		if(bVisible) traverse(node, nv);
	}

private:
	observer_ptr<osg::IVBF_Camera>		m_pCamera;
	observer_ptr<CVBF_Map>	m_pMap;
	IVBF_3DDisplay*						m_pI3DDisplay;
	bool								m_bBillboard;  // �Ƿ�ʹ�ò�����
};

#endif
