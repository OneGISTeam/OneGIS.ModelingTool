#ifndef __VBF_EFFECT_HIGHLIGHT_H__
#define __VBF_EFFECT_HIGHLIGHT_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexEnv.h>

// 定义该特效的名称,可用作VBF_RemoveEffectFromNode()函数的第二个参数
const char VBF_EFFECT_NAME_HIGHLIGHT[] = "Hightlight Effect";
const char VBF_EFFECT_DESC_HIGHLIGHT[] = "Add Hightlight Effect To Node";

//-------------------------------------------------------------------------------
// 定义类：CVBF_EffectHighlight
// 类描述：高亮特效节点
//-------------------------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_EffectHighlight : public osgFX::Effect 
{
public:
	CVBF_EffectHighlight();
	CVBF_EffectHighlight(const CVBF_EffectHighlight& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

	META_Effect(VBF, CVBF_EffectHighlight, VBF_EFFECT_NAME_HIGHLIGHT, VBF_EFFECT_DESC_HIGHLIGHT, "DY");

	void      SetColor(int i, osg::Vec4 c);
	osg::Vec4 GetColor(int i);

	void SetTexEnvMode(osg::TexEnv::Mode nMode);

	void ToggleColor();
	void StopToggling();

protected:
	CVBF_EffectHighlight& operator=(const CVBF_EffectHighlight&) { return *this; }
	virtual ~CVBF_EffectHighlight() {}

	virtual bool define_techniques();

private:
	osg::Vec4			m_color[2];		// 高亮时切换的两种颜色		
	osg::TexEnv::Mode	m_nTexEnvMode;	// 加色，还是乘色? (说明：加色使模型变亮，但整体感不好；乘色使模型变暗，但整体感好)
	int					m_nCurrIndex;	// 高亮时切换的颜色索引，只能为0或1
};

//-------------------------------------------------------------------------------
// 定义类：CVBF_UpdateCallbackHighlight
// 类描述：高亮特效回调
//-------------------------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_UpdateCallbackHighlight : public osg::NodeCallback
{
public:
	CVBF_UpdateCallbackHighlight(CVBF_EffectHighlight* pEffect, int nTimes, int nInterval, bool bAlways);

	virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);

protected:
	observer_ptr<CVBF_EffectHighlight>		m_pEffectRef;

	bool		m_bFlickerAlways;	// 是否不停闪烁		
	int			m_nFlickerTimes;	// 闪烁的总次数
	int			m_nFlickerInterval;	// 闪烁的帧间隔		

	int			m_nFrameNumber;		// 已经绘制的帧数
	int			m_nFlickerNumber;	// 已经闪烁的次数
};



#endif
