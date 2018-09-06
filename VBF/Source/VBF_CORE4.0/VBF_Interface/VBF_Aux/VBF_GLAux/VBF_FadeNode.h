#pragma once

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Base/observer_ptr>

class FadeNodeUpdateCallback;

/* 淡入/淡出节点
 * 将FadeNode作为其他节点的父节点，就可以实现该节点内容的淡入/淡出效果
 * 实现机制为：覆盖（OverRide）子节点的材质，通过改变材质的Diffuse.alpha值实现透明绘制效果
 * 通过节点更新回调动态改变子节点透明度，从而实现淡入/淡出效果
 * 限制：由于需要覆盖子节点材质，因此适用于本身不使用材质信息的模型（如带烘焙贴图的模型）
 * 用法：
 * 1. 将子节点挂接到FadeNode下
 * 2. 设置渐变模式：FadeNode::setFadeMode(FadeMode fm);
 * 3. 启用渐变: FadeNode::setEnabled(true)
 */
class VBF_GLAUX_EXPORT FadeNode : public osg::CVBF_SGNodeGroup
{
public:
	enum FadeMode
	{
		FADEMODE_IN = 1,	// 淡入效果，透明度从0变到1
		FADEMODE_OUT		// 淡出效果，透明度从1变到0
	};
	FadeNode();
	FadeNode(int iFrameCount);
	FadeNode(const FadeNode&, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY);

	META_Node(osg, FadeNode);

	// 启用前必须正确设置了Fade模式
	void setEnabled(bool bEnable);
	bool getEnabled() { return m_bEnabled; }
	void setFadeMode(FadeMode fm) { m_fadeMode = fm; }
	FadeMode getFadeMode() { return m_fadeMode; }
	void setAlpha(float fAlpha);
	float getAlpha() { return m_fAlpha; }
	void setFadeFrames(int iFrames);
	int getFadeFrames() { return m_iFrameCount; }

	
protected:
	void createStateSet();
	void createUpdateCallback();

protected:
	bool							m_bEnabled;
	FadeMode						m_fadeMode;
	
	int								m_iFrameCount;	// 实现该渐变效果所用的帧数（下一步应该改成通过时间来控制）	
	float							m_fAlpha;		// 当前透明度，只有在渐变过程中有效	
	ref_ptr<osg::Material>		m_mtlBlend;// 透明效果所用材质	
	ref_ptr<osg::StateSet>		m_ssBlend;// 透明效果所用状态集

	// 在不启用混合的条件下，是否可以将该节点设置为没有StateSet？
	// 因为设置了StateSet会使状态树更复杂
	ref_ptr<osg::StateSet>		m_ssDefault;

	// 实现渐变所用更新回调，在回调中改变透明度
	ref_ptr<FadeNodeUpdateCallback>	m_updateCallback;
};

/* 淡入/淡出节点对应的更新回调
 * 
 */
class FadeNodeUpdateCallback : public osg::NodeCallback
{
public:
	FadeNodeUpdateCallback(FadeNode* fn, int iTotalFrame) : 
	  m_fnode(fn), m_bEnabled(false),
		  m_fAlpha(0.0), m_fAlphaDelta(0.0),
		m_iFrameTotal(iTotalFrame), m_iFrameCurrent(0)  {}

	  // 启用前必须正确设置了Fade模式
	  void setEnable(bool bEnabled);
	  bool getEnable() { return m_bEnabled; }

	  void setFrameTotal(int iFrames) { m_iFrameTotal = iFrames; }

	  void Init();

	  void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);

protected:
	observer_ptr<FadeNode>		m_fnode;

	bool		m_bEnabled;
	double		m_fAlpha;			// 淡入/淡出过程中当前透明度值
	double		m_fAlphaDelta;		// 淡入/淡出过程中透明度变化率	
	int			m_iFrameTotal;		// 淡入/淡出过程持续总帧数	
	int			m_iFrameCurrent;	// 淡入/淡出过程中记录当前帧数，完成后被重置为0
};
