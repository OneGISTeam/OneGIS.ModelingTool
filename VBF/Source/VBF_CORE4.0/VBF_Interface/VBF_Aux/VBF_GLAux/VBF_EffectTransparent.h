#ifndef __VBF_EFFECT_TRANSPARENT_H__
#define __VBF_EFFECT_TRANSPARENT_H__

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>


// 定义该特效的名称,可用作VBF_RemoveEffectFromNode()函数的第二个参数
const char VBF_EFFECT_NAME_TRANSPARENT[] = "Transparent Effect";
const char VBF_EFFECT_DESC_TRANSPARENT[] = "Add Transparent Effect To Node";


//-------------------------------------------------------------------------------
// 定义类：CVBF_EffectTransparent
// 类描述：透明特效节点
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
