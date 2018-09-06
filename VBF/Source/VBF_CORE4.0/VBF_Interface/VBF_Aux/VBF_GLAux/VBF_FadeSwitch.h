#pragma once

#ifndef OSG_FADESWITCH
#define OSG_FADESWITCH 1

#include <VBF_Aux/VBF_GLAux/VBF_GLAuxExport.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include "VBF_FadeNode.h"

namespace osg {

	class FadeSwitchCallback;

/* 带淡出/淡出效果的Switch节点 
 * 实现机制：对于每个添加到FadeSwitch中的子节点，实际上在内部将其挂接到FadeNode下，再将FadeNode挂接到FadeSwitch下
 * 这个挂接是在添加子节点时完成的
 * 使用方式：
 * 1. 添加子节点: FadeSwitch::addChild( Node *child )
 * 2. 打开单个子节点（同时关闭其他子节点）: FadeSwitch::setSingleChildOn(unsigned int pos)
 * 限制：目前只有上面两个接口是可安全调用的
 * 在打开子节点i后，会自动开始渐变过程。在渐变过程中再次打开其他节点将会直接返回，不产生任何效果，留待下一步完善
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

		// 已完成的方法，可安全调用
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
		// 尚未完成的方法，不要调用
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
	// 记录正常状态下子节点是否显示
	ValueList   _values;

	// 记录子节点是否处于渐变过程
	//ValueList	_valuesForFade;
	//std::vector<int> _framesForFade;

	// 每个被加入到FadeSwitch的子节点对应一个FadeNode
    std::vector< ref_ptr<FadeNode> > _fnodeList;

	// 当前是否处在渐变过程中
	// 不在渐变过程中，调用打开子节点方法会开启渐变过程
	// 渐变过程结束的判断在回调中进行，因此在回调中会在渐变结束后将该值设为false
	bool				_bIsFading;

	// 淡入/淡出所用总帧数
	int					_iFadeFrames;
	// 淡入所用总帧数
	int					_iFadeInFrames;
	// 淡出所用总帧数
	int					_iFadeOutFrames;

	// 用于标识淡入和淡出子节点
	std::vector<int>	_valuesForFadeIn;
	std::vector<int>	_valuesForFadeOut;

    protected :
    
        virtual ~FadeSwitch() {}

        // 新加入节点的可见状态的默认值，始终为false
        bool        _newChildDefaultValue;
		// 实现渐变过程的更新回调
		ref_ptr<FadeSwitchCallback> m_fsCallback;
};

// 遍历FadeSwitch中所有的_framesForFade和_valuesForFade
// 如果有节点的fade被启用，则判断相应的_framesForFade是否达到指定帧数，则禁用fade
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

// 只能追加，不能插入。因此禁用这些方法
//virtual bool insertChild( unsigned int index, Node *child );

//virtual bool insertChild( unsigned int index, Node *child, bool value );

//virtual bool removeChildren(unsigned int pos,unsigned int numChildrenToRemove);

//void setChildValue(const Node* child,bool value);

#endif
