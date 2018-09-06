#pragma once

#ifndef OSG_FADESWITCH
#define OSG_FADESWITCH 1

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include "VBF_FadeNode.h"

namespace osg {

	class FadeSwitchCallback;

/* ������/����Ч����Switch�ڵ� 
 * ʵ�ֻ��ƣ�����ÿ����ӵ�FadeSwitch�е��ӽڵ㣬ʵ�������ڲ�����ҽӵ�FadeNode�£��ٽ�FadeNode�ҽӵ�FadeSwitch��
 * ����ҽ���������ӽڵ�ʱ��ɵ�
 * ʹ�÷�ʽ��
 * 1. ����ӽڵ�: FadeSwitch::addChild( Node *child )
 * 2. �򿪵����ӽڵ㣨ͬʱ�ر������ӽڵ㣩: FadeSwitch::setSingleChildOn(unsigned int pos)
 * ���ƣ�Ŀǰֻ�����������ӿ��ǿɰ�ȫ���õ�
 * �ڴ��ӽڵ�i�󣬻��Զ���ʼ������̡��ڽ���������ٴδ������ڵ㽫��ֱ�ӷ��أ��������κ�Ч����������һ������
 */
class VBF_GLAUX_EXPORT FadeSwitch : public CVBF_SGNodeGroup
{
    public:
        FadeSwitch();

        /** Copy constructor using CopyOp to manage deep vs shallow copy. */
        FadeSwitch(const FadeSwitch&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        virtual FadeSwitch* asFadeSwitch() { return this; }
        virtual const FadeSwitch* asFadeSwitch() const { return this; }

		virtual bool addChild( IVBF_SGNode *child );

        META_Node(osg, FadeSwitch);

		void setFadeFrames(int fadeInFrames, int fadeOutFrames);
		void getFadeFrames(int& fadeInFrames, int& fadeOutFrames);

		// ����ɵķ������ɰ�ȫ����
        virtual bool addChild( IVBF_SGNode *child, bool value );

		/** Set a single child on, FadeSwitch off all other children. */
		bool setSingleChildOn(unsigned int pos);

		/** Set all the children off (false), and set the new default child
          * value to off (false). */
        bool setAllChildrenOff();
        
        /** Set all the children on (true), and set the new default child
          * value to on (true). */
        bool setAllChildrenOn();      

protected:
		// ��δ��ɵķ�������Ҫ����
        void setValue(unsigned int pos,bool value);

        bool getValue(unsigned int pos) const;
        
        bool getChildValue(const IVBF_SGNode* child) const;  

public:
        typedef std::vector<bool>   ValueList;

        virtual BoundingSphere computeBound() const;

		virtual void traverse(NodeVisitor& nv);

public:
	void enableFadeState(int pos, FadeNode::FadeMode fm);
	void disableFadeState(int pos);
	//bool getFadeStateForAll();

public:
	// ��¼����״̬���ӽڵ��Ƿ���ʾ
	ValueList   _values;

	// ��¼�ӽڵ��Ƿ��ڽ������
	//ValueList	_valuesForFade;
	//std::vector<int> _framesForFade;

	// ÿ�������뵽FadeSwitch���ӽڵ��Ӧһ��FadeNode
    std::vector< ref_ptr<FadeNode> > _fnodeList;

	// ��ǰ�Ƿ��ڽ��������
	// ���ڽ�������У����ô��ӽڵ㷽���Ὺ���������
	// ������̽������ж��ڻص��н��У�����ڻص��л��ڽ�������󽫸�ֵ��Ϊfalse
	bool				_bIsFading;

	// ����/����������֡��
	int					_iFadeFrames;
	// ����������֡��
	int					_iFadeInFrames;
	// ����������֡��
	int					_iFadeOutFrames;

	// ���ڱ�ʶ����͵����ӽڵ�
	std::vector<int>	_valuesForFadeIn;
	std::vector<int>	_valuesForFadeOut;

    protected :
    
        virtual ~FadeSwitch() {}

        // �¼���ڵ�Ŀɼ�״̬��Ĭ��ֵ��ʼ��Ϊfalse
        bool        _newChildDefaultValue;
		// ʵ�ֽ�����̵ĸ��»ص�
		ref_ptr<FadeSwitchCallback> m_fsCallback;
};

// ����FadeSwitch�����е�_framesForFade��_valuesForFade
// ����нڵ��fade�����ã����ж���Ӧ��_framesForFade�Ƿ�ﵽָ��֡���������fade
class FadeSwitchCallback : public NodeCallback
{
public:
	FadeSwitchCallback(FadeSwitch* fs) : m_fadeSwitch(fs), m_iFrameCounter(0) {}
	void operator()(osg::IVBF_SGNode* node, osg::NodeVisitor* nv);
	void resetFrameCounter() { m_iFrameCounter = 0; }
protected:
	observer_ptr<FadeSwitch>	m_fadeSwitch;
	int								m_iFrameCounter;
};

}

// ֻ��׷�ӣ����ܲ��롣��˽�����Щ����
//virtual bool insertChild( unsigned int index, Node *child );

//virtual bool insertChild( unsigned int index, Node *child, bool value );

//virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove);

//void setChildValue(const Node* child,bool value);

#endif
