#ifndef __VBF_EFFECT_HIGHLIGHT_H__
#define __VBF_EFFECT_HIGHLIGHT_H__


#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_FX/VBF_Effect.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrTexEnv.h>

// �������Ч������,������VBF_RemoveEffectFromNode()�����ĵڶ�������
const char VBF_EFFECT_NAME_HIGHLIGHT[] = "Hightlight Effect";
const char VBF_EFFECT_DESC_HIGHLIGHT[] = "Add Hightlight Effect To Node";

//-------------------------------------------------------------------------------
// �����ࣺCVBF_EffectHighlight
// ��������������Ч�ڵ�
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
	osg::Vec4			m_color[2];		// ����ʱ�л���������ɫ		
	osg::TexEnv::Mode	m_nTexEnvMode;	// ��ɫ�����ǳ�ɫ? (˵������ɫʹģ�ͱ�����������в��ã���ɫʹģ�ͱ䰵��������к�)
	int					m_nCurrIndex;	// ����ʱ�л�����ɫ������ֻ��Ϊ0��1
};

//-------------------------------------------------------------------------------
// �����ࣺCVBF_UpdateCallbackHighlight
// ��������������Ч�ص�
//-------------------------------------------------------------------------------
class VBF_GLAUX_EXPORT CVBF_UpdateCallbackHighlight : public osg::NodeCallback
{
public:
	CVBF_UpdateCallbackHighlight(CVBF_EffectHighlight* pEffect, int nTimes, int nInterval, bool bAlways);

	virtual void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);

protected:
	observer_ptr<CVBF_EffectHighlight>		m_pEffectRef;

	bool		m_bFlickerAlways;	// �Ƿ�ͣ��˸		
	int			m_nFlickerTimes;	// ��˸���ܴ���
	int			m_nFlickerInterval;	// ��˸��֡���		

	int			m_nFrameNumber;		// �Ѿ����Ƶ�֡��
	int			m_nFlickerNumber;	// �Ѿ���˸�Ĵ���
};



#endif
