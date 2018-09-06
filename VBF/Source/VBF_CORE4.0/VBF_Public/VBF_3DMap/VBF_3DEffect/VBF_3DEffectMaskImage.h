//***************************************************************************************
// FileName：VBF_3DEffectMaskImage.h
// Function：图像蒙板类接口的实现类
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

	// 从配置文件中装载特效对象的初始化信息
	virtual bool LoadFromXML(TiXmlElement* pElemEffect);

	// 执行特效对象的动作，动作参数从从配置文件元素中获取
	virtual bool StartFromXML(TiXmlElement* pElemAction);
	
	// 设置图像的文件名
	virtual bool SetImageFileName(const char* szImgFn);

	// 设置图像的地理范围
	virtual bool SetGeoBounds(double xmin, double ymin, double xmax, double ymax);

	// 设置透明度
	virtual void SetAlpha(float fAlpha);

	// 设置相对地面的高度
	virtual void SetRelativeHeight(double dheight);	

	//图像蒙板特效实现
	virtual bool StartAction(const char* szEffectType, int nDurationFrames);

private:
	void StartExpand(const char* szEffectType, int nDurationFrames);
	void StartFade(const char* szEffectType, int nDurationFrames);

	double getGeoHeight(double L, double B);
	bool CreateGeometry();

private:	

	// 经纬度范围
	osgEarth::Bounds			m_GeoBounds;
	float						m_fAlpha;
	ref_ptr<osg::Image>	m_pImage;
	bool						m_bGeomCreated;	
	double						m_dHeight;// 记录图像蒙版抬起高度

	ref_ptr<osgEarth::Annotation::ImageOverlay> m_pImageOverlay; 
};


#endif