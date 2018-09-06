#pragma once

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/StateSet>
#include <VBF_Engine/VBF_SceneGraph/VBFO_StateAttrMaterial.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNodeCallback.h>
#include <VBF_Base/observer_ptr>

class FadeNodeUpdateCallback;

/* ����/�����ڵ�
 * ��FadeNode��Ϊ�����ڵ�ĸ��ڵ㣬�Ϳ���ʵ�ָýڵ����ݵĵ���/����Ч��
 * ʵ�ֻ���Ϊ�����ǣ�OverRide���ӽڵ�Ĳ��ʣ�ͨ���ı���ʵ�Diffuse.alphaֵʵ��͸������Ч��
 * ͨ���ڵ���»ص���̬�ı��ӽڵ�͸���ȣ��Ӷ�ʵ�ֵ���/����Ч��
 * ���ƣ�������Ҫ�����ӽڵ���ʣ���������ڱ���ʹ�ò�����Ϣ��ģ�ͣ�����決��ͼ��ģ�ͣ�
 * �÷���
 * 1. ���ӽڵ�ҽӵ�FadeNode��
 * 2. ���ý���ģʽ��FadeNode::setFadeMode(FadeMode fm);
 * 3. ���ý���: FadeNode::setEnabled(true)
 */
class VBF_GLAUX_EXPORT FadeNode : public osg::CVBF_SGNodeGroup
{
public:
	enum FadeMode
	{
		FADEMODE_IN = 1,	// ����Ч����͸���ȴ�0�䵽1
		FADEMODE_OUT		// ����Ч����͸���ȴ�1�䵽0
	};
	FadeNode();
	FadeNode(int iFrameCount);
	FadeNode(const FadeNode&, const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY);

	META_Node(osg, FadeNode);

	// ����ǰ������ȷ������Fadeģʽ
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
	
	int								m_iFrameCount;	// ʵ�ָý���Ч�����õ�֡������һ��Ӧ�øĳ�ͨ��ʱ�������ƣ�	
	float							m_fAlpha;		// ��ǰ͸���ȣ�ֻ���ڽ����������Ч	
	ref_ptr<osg::Material>		m_mtlBlend;// ͸��Ч�����ò���	
	ref_ptr<osg::StateSet>		m_ssBlend;// ͸��Ч������״̬��

	// �ڲ����û�ϵ������£��Ƿ���Խ��ýڵ�����Ϊû��StateSet��
	// ��Ϊ������StateSet��ʹ״̬��������
	ref_ptr<osg::StateSet>		m_ssDefault;

	// ʵ�ֽ������ø��»ص����ڻص��иı�͸����
	ref_ptr<FadeNodeUpdateCallback>	m_updateCallback;
};

/* ����/�����ڵ��Ӧ�ĸ��»ص�
 * 
 */
class FadeNodeUpdateCallback : public osg::NodeCallback
{
public:
	FadeNodeUpdateCallback(FadeNode* fn, int iTotalFrame) : 
	  m_fnode(fn), m_bEnabled(false),
		  m_fAlpha(0.0), m_fAlphaDelta(0.0),
		m_iFrameTotal(iTotalFrame), m_iFrameCurrent(0)  {}

	  // ����ǰ������ȷ������Fadeģʽ
	  void setEnable(bool bEnabled);
	  bool getEnable() { return m_bEnabled; }

	  void setFrameTotal(int iFrames) { m_iFrameTotal = iFrames; }

	  void Init();

	  void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);

protected:
	observer_ptr<FadeNode>		m_fnode;

	bool		m_bEnabled;
	double		m_fAlpha;			// ����/���������е�ǰ͸����ֵ
	double		m_fAlphaDelta;		// ����/����������͸���ȱ仯��	
	int			m_iFrameTotal;		// ����/�������̳�����֡��	
	int			m_iFrameCurrent;	// ����/���������м�¼��ǰ֡������ɺ�����Ϊ0
};
