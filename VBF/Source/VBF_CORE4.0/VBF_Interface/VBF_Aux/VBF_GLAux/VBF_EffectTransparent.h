#ifndef __VBF_EFFECT_TRANSPARENT_H__
#define __VBF_EFFECT_TRANSPARENT_H__

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>


// �������Ч������,������VBF_RemoveEffectFromNode()�����ĵڶ�������
const char VBF_EFFECT_NAME_TRANSPARENT[] = "Transparent Effect";
const char VBF_EFFECT_DESC_TRANSPARENT[] = "Add Transparent Effect To Node";


//-------------------------------------------------------------------------------
// �����ࣺCVBF_EffectTransparent
// ��������͸����Ч�ڵ�
//-------------------------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_EffectTransparent : public osgFX::Effect 
{
public:
	CVBF_EffectTransparent();
	CVBF_EffectTransparent(const CVBF_EffectTransparent& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

	META_Effect(osg, CVBF_EffectTransparent, VBF_EFFECT_NAME_TRANSPARENT, VBF_EFFECT_DESC_TRANSPARENT, "DY");

	static void			SetColorAmbient(const osg::Vec4& c);
	static osg::Vec4	GetColorAmbient()	{ return ms_colorAmbient; }

	static void			SetColorDiffuse(const osg::Vec4& c);
	static osg::Vec4	GetColorDiffuse()	{ return ms_colorDiffuse; }

protected:
	CVBF_EffectTransparent& operator=(const CVBF_EffectTransparent&) { return *this; }
	virtual ~CVBF_EffectTransparent() {}

	virtual bool define_techniques();

private:
	static osg::Vec4		ms_colorAmbient;
	static osg::Vec4		ms_colorDiffuse;
};	


#endif
