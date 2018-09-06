//***************************************************************************************
// FileName��VBF_3DEffectMaskImage.h
// Function��ͼ���ɰ���ӿڵ�ʵ����
//***************************************************************************************

#ifndef __VBF_3DMASKIMAGE_H__
#define __VBF_3DMASKIMAGE_H__

#include "VBF_3DCom/VBF_3DEffect/IVBF_3DEffectMaskImage.h"
#include <VBF_3DMap/VBF_3DEffect/VBF_3DEffectImpl.h>
#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_3DMap/VBF_Annotation/AnnotationNode.h>
#include <VBF_3DMap/VBF_Symbology/GeometryFactory.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>

#include <VBF_Engine/VBF_SGUtil/Optimizer>
#include <VBF_Engine/VBF_SGUtil/DelaunayTriangulator>
#include <VBF_3DMap/VBF_Terrain/VBFO_SGNodeOverlayDrapeable.h>
#include <VBF_3DMap/VBF_Terrain/ElevationQuery.h>
#include <VBF_3DMap/VBF_Symbology/MeshSubdivider.h>
#include <VBF_3DMap/VBF_Annotation/ImageOverlay.h>
#include <VBF_3DMap/VBF_3DEffect/Export>

using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Symbology;


class VBF_3DEFFECT_EXPORT CVBF_3DEffectMaskImage : public CVBF_3DEffectImpl<IVBF_3DEffectMaskImage>
{
public:
	CVBF_3DEffectMaskImage(IVBF_3DMainCtrl* pI3DMainCtrl, IVBF_View* pView, osg::IVBF_SGNodeGroup* pParentNode);
	virtual ~CVBF_3DEffectMaskImage();	

	// �������ļ���װ����Ч����ĳ�ʼ����Ϣ
	virtual bool LoadFromXML(TiXmlElement* pElemEffect);

	// ִ����Ч����Ķ��������������Ӵ������ļ�Ԫ���л�ȡ
	virtual bool StartFromXML(TiXmlElement* pElemAction);
	
	// ����ͼ����ļ���
	virtual bool SetImageFileName(const char* szImgFn);

	// ����ͼ��ĵ���Χ
	virtual bool SetGeoBounds(double xmin, double ymin, double xmax, double ymax);

	// ����͸����
	virtual void SetAlpha(float fAlpha);

	// ������Ե���ĸ߶�
	virtual void SetRelativeHeight(double dheight);	

	//ͼ���ɰ���Чʵ��
	virtual bool StartAction(const char* szEffectType, int nDurationFrames);

private:
	void StartExpand(const char* szEffectType, int nDurationFrames);
	void StartFade(const char* szEffectType, int nDurationFrames);

	double getGeoHeight(double L, double B);
	bool CreateGeometry();

private:	

	// ��γ�ȷ�Χ
	osgEarth::Bounds			m_GeoBounds;
	float						m_fAlpha;
	ref_ptr<osg::Image>	m_pImage;
	bool						m_bGeomCreated;	
	double						m_dHeight;// ��¼ͼ���ɰ�̧��߶�

	ref_ptr<osgEarth::Annotation::ImageOverlay> m_pImageOverlay; 
};


#endif