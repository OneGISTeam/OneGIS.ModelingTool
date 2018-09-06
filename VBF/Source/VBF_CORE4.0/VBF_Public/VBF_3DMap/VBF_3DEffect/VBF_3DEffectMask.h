//***************************************************************************************
// FileName：VBF_3DMask.h
// Function：蒙板接口的实现类
//***************************************************************************************

#ifndef __VBF_3DMASK_H__
#define __VBF_3DMASK_H__

#include "VBF_3DCom/VBF_3DEffect/IVBF_3DEffectMask.h"
#include <VBF_3DMap/VBF_3DEffect/VBF_3DEffectImpl.h>
#include <VBF_Aux/VBF_MapAux/VBF_LabelNode.h>

#include <VBF_Engine/VBF_SceneGraph/Array>
#include <VBF_3DMap/VBF_Annotation/FeatureNode.h>
#include <VBF_3DMap/VBF_Symbology/VBF_SymbolPolygon.h>
#include <VBF_3DMap/VBF_Annotation/AnnotationNode.h>
#include <VBF_3DMap/VBF_Annotation/LabelNode.h>
#include <VBF_3DMap/VBF_Symbology/GeometryFactory.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Features/Feature.h>
#include <VBF_3DMap/VBF_3DEffect/Export>

using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Symbology;

//  多边形效果，可实现挤出、闪烁等效果，
class VBF_3DEFFECT_EXPORT CVBF_3DEffectMask : public CVBF_3DEffectImpl<IVBF_3DEffectMask>
{
public:
	CVBF_3DEffectMask(IVBF_3DMainCtrl* pI3DMainCtrl, IVBF_View* pView, osg::IVBF_SGNodeGroup* pParentNode);
	virtual ~CVBF_3DEffectMask();	

	// 从配置文件中装载特效对象的初始化信息
	virtual bool LoadFromXML(TiXmlElement* pElemEffect);

	// 执行特效对象的动作，动作参数从从配置文件元素中获取
	virtual bool StartFromXML(TiXmlElement* pElemAction);	

    // 多边形
    virtual bool SetGeoVertices(osg::Vec3dArray* pVertices);// 设置地理坐标串
    virtual bool SetStyle(VBF_3DMASKSTYLE* pStyle);// 设置样式

	// 设置标签
	virtual bool SetLabel(const char* szLabel);

	//蒙板特效实现
	virtual bool StartAction(const char* szEffectType, int nDurationFrames, float fAlpha);

private:
	void StartFlicker(int nDurationFrames, osg::Vec4f color);
	void StartExpand(const char* szEffectType, int nDurationFrames);

	bool CreateGeometry();
	bool CreateLabel();

private:	
	bool							m_bGeomCreated;
	bool							m_bLabelCreated;

	ref_ptr<Feature>			m_pFeature;
	ref_ptr<FeatureNode>		m_pFeatureNode;	
	ref_ptr<CVBF_LabelNode>		m_pLabelNode;

	//淡出时的高度下降值强制转换为0.0, 不然与非挤出蒙版有冲突
	float							m_fExtrusionHeight;	
	VBF_3DMASKSTYLE					m_Style;
	ref_ptr<osg::Vec3dArray>		m_pGeoVertices;
	char							m_szLabel[256];

	osgEarth::Symbology::Style		m_MaskStyle;
};


#endif
