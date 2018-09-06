
//#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <Types/VBF_BoundingBox.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransform.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupOccluder.h>//？？？？
#include <VBF_Base/VBF_Notify.h>

#include <stdio.h>
#include <math.h>

#include <algorithm>

using namespace osg;

template<class T>
IVBF_SGNodeGroupImpl<T>::IVBF_SGNodeGroupImpl()
{
	T::m_dwTypeID = 0x11000000; //类型标识
}

template<class T>
IVBF_SGNodeGroupImpl<T>::IVBF_SGNodeGroupImpl(const IVBF_SGNodeGroupImpl& group,const CopyOp& copyop): 
                IVBF_SGNodeImpl<T>(group,copyop)
{
	T::m_dwTypeID = 0x11000000; //类型标识

    for(NodeList::const_iterator itr=group._children.begin(); itr!=group._children.end(); ++itr)
    {
        IVBF_SGNode* child = (IVBF_SGNode*)copyop(itr->get());
        if (child) addChild(child);
    }
}

template<class T>
IVBF_SGNodeGroupImpl<T>::~IVBF_SGNodeGroupImpl()
{
    // remove reference to this from children's parent lists.
    for(NodeList::iterator itr=_children.begin(); itr!=_children.end(); ++itr)
    {
        (*itr)->removeParent(this);
    }
}

template<class T>
void IVBF_SGNodeGroupImpl<T>::traverse(NodeVisitor& nv)
{
    for(NodeList::iterator itr=_children.begin(); itr!=_children.end(); ++itr)
    {
        (*itr)->accept(nv);
    }
}


template<class T>
bool IVBF_SGNodeGroupImpl<T>::addChild( IVBF_SGNode *child )
{
    return IVBF_SGNodeGroupImpl<T>::insertChild( _children.size(), child );
}


template<class T>
bool IVBF_SGNodeGroupImpl<T>::insertChild( unsigned int index, IVBF_SGNode *child )
{
    if (!child) return false;
    
#if ENSURE_CHILD_IS_UNIQUE    
    if (containsNode(child))
    {
        OSG_WARN<<"Adding non unique child to osg::Group, ignoring call"<<std::endl;
        return false;
    }
#endif
    
    if (child)
    {
        // note ref_ptr<> automatically handles incrementing child's reference count.
        if (index >= _children.size())
        {
            _children.push_back(child);
        }
        else
        {
            _children.insert(_children.begin()+index, child);
        }

        // register as parent of child.
        child->addParent(this);
        
        // tell any subclasses that a child has been inserted so that they can update themselves.
        childInserted(index);

        _Base::dirtyBound();

        // could now require app traversal thanks to the new subgraph,
        // so need to check and update if required.
        if (child->getNumChildrenRequiringUpdateTraversal()>0 || child->getUpdateCallback())
        {
            _Base::setNumChildrenRequiringUpdateTraversal( _Base::getNumChildrenRequiringUpdateTraversal()+1 );
        }

        // could now require app traversal thanks to the new subgraph,
        // so need to check and update if required.
        if (child->getNumChildrenRequiringEventTraversal()>0 || child->getEventCallback())
        {
            _Base::setNumChildrenRequiringEventTraversal( _Base::getNumChildrenRequiringEventTraversal()+1 );
        }

        // could now require disabling of culling thanks to the new subgraph,
        // so need to check and update if required.
        if (child->getNumChildrenWithCullingDisabled()>0 || !child->getCullingActive())
        {
            _Base::setNumChildrenWithCullingDisabled( _Base::getNumChildrenWithCullingDisabled()+1 );
        }

        // VBF_QT 不过       if (child->getNumChildrenWithOccluderNodes()>0 || dynamic_cast<OccluderNode*>(child))
        if (child->getNumChildrenWithOccluderNodes()>0 || dynamic_cast<IVBF_SGNodeGroupOccluder*>(child))
        {
            _Base::setNumChildrenWithOccluderNodes( _Base::getNumChildrenWithOccluderNodes()+1 );
        }

        return true;
    }
    else return false;
}

template<class T>
bool IVBF_SGNodeGroupImpl<T>::removeChildren(unsigned int pos,unsigned int numChildrenToRemove)
{
    if (pos<_children.size() && numChildrenToRemove>0)
    {
        unsigned int endOfRemoveRange = pos+numChildrenToRemove;
        if (endOfRemoveRange>_children.size())
        {
            OSG_DEBUG<<"Warning: Group::removeChild(i,numChildrenToRemove) has been passed an excessive number"<<std::endl;
            OSG_DEBUG<<"         of chilren to remove, trimming just to end of child list."<<std::endl;
            endOfRemoveRange=_children.size();
        }

        unsigned int updateCallbackRemoved = 0;
        unsigned int eventCallbackRemoved = 0;
        unsigned int numChildrenWithCullingDisabledRemoved = 0;
        unsigned int numChildrenWithOccludersRemoved = 0;

        for(unsigned i=pos;i<endOfRemoveRange;++i)
        {
            osg::IVBF_SGNode* child = _children[i].get();
            // remove this Geode from the child parent list.
            child->removeParent(this);

            if (child->getNumChildrenRequiringUpdateTraversal()>0 || child->getUpdateCallback()) ++updateCallbackRemoved;

            if (child->getNumChildrenRequiringEventTraversal()>0 || child->getEventCallback()) ++eventCallbackRemoved;

            if (child->getNumChildrenWithCullingDisabled()>0 || !child->getCullingActive()) ++numChildrenWithCullingDisabledRemoved;

            //VBF_QT 不过           if (child->getNumChildrenWithOccluderNodes()>0 || dynamic_cast<osg::OccluderNode*>(child)) ++numChildrenWithOccludersRemoved;
            if (child->getNumChildrenWithOccluderNodes()>0 || dynamic_cast<IVBF_SGNodeGroupOccluder*>(child)) ++numChildrenWithOccludersRemoved;

        }

        childRemoved(pos,endOfRemoveRange-pos);

        _children.erase(_children.begin()+pos,_children.begin()+endOfRemoveRange);

        if (updateCallbackRemoved)
        {
            _Base::setNumChildrenRequiringUpdateTraversal(_Base::getNumChildrenRequiringUpdateTraversal()-updateCallbackRemoved);
        }
        
        if (eventCallbackRemoved)
        {
            _Base::setNumChildrenRequiringEventTraversal(_Base::getNumChildrenRequiringEventTraversal()-eventCallbackRemoved);
        }

        if (numChildrenWithCullingDisabledRemoved)
        {
            _Base::setNumChildrenWithCullingDisabled(_Base::getNumChildrenWithCullingDisabled()-numChildrenWithCullingDisabledRemoved);
        }
        
        if (numChildrenWithOccludersRemoved)
        {
            _Base::setNumChildrenWithOccluderNodes(_Base::getNumChildrenWithOccluderNodes()-numChildrenWithOccludersRemoved);
        }
        
        _Base::dirtyBound();
        
        return true;
    }
    else return false;
}


template<class T>
bool IVBF_SGNodeGroupImpl<T>::replaceChild( IVBF_SGNode *origNode, IVBF_SGNode *newNode )
{
    if (newNode==NULL || origNode==newNode) return false;

    unsigned int pos = getChildIndex(origNode);
    if (pos<_children.size())
    {
        return setChild(pos,newNode);
    }
    return false;
}


template<class T>
bool IVBF_SGNodeGroupImpl<T>::setChild( unsigned  int i, IVBF_SGNode* newNode )
{
    if (i<_children.size() && newNode)
    {
    
        ref_ptr<IVBF_SGNode> origNode = _children[i];
    

        // 从原节点的父节点列表中移除this
        origNode->removeParent(this);

        // 智能指针自动处理减少原节点的引用计数，增加新节点的引用计数
        _children[i] = newNode;

        // 在新节点的父节点列表中添加this
        newNode->addParent(this);


		// 设置重新计算包围盒标志
        _Base::dirtyBound();


        // could now require update traversal thanks to the new subgraph,
        // so need to check and update if required.
        int delta_numChildrenRequiringUpdateTraversal = 0;
        if (origNode->getNumChildrenRequiringUpdateTraversal()>0 || origNode->getUpdateCallback())
        {
            --delta_numChildrenRequiringUpdateTraversal;
        }
        if (newNode->getNumChildrenRequiringUpdateTraversal()>0 || newNode->getUpdateCallback())
        {
            ++delta_numChildrenRequiringUpdateTraversal;
        }

        if (delta_numChildrenRequiringUpdateTraversal!=0)
        {
            _Base::setNumChildrenRequiringUpdateTraversal(
                _Base::getNumChildrenRequiringUpdateTraversal()+delta_numChildrenRequiringUpdateTraversal );
        }




        // could now require event traversal thanks to the new subgraph,
        // so need to check and Event if required.
        int delta_numChildrenRequiringEventTraversal = 0;
        if (origNode->getNumChildrenRequiringEventTraversal()>0 || origNode->getEventCallback())
        {
            --delta_numChildrenRequiringEventTraversal;
        }
        if (newNode->getNumChildrenRequiringEventTraversal()>0 || newNode->getEventCallback())
        {
            ++delta_numChildrenRequiringEventTraversal;
        }

        if (delta_numChildrenRequiringEventTraversal!=0)
        {
            _Base::setNumChildrenRequiringEventTraversal(
                _Base::getNumChildrenRequiringEventTraversal()+delta_numChildrenRequiringEventTraversal );
        }




        // could now require disabling of culling thanks to the new subgraph,
        // so need to check and update if required.
        int delta_numChildrenWithCullingDisabled = 0;
        if (origNode->getNumChildrenWithCullingDisabled()>0 || !origNode->getCullingActive())
        {
            --delta_numChildrenWithCullingDisabled;
        }
        if (newNode->getNumChildrenWithCullingDisabled()>0 || !newNode->getCullingActive())
        {
            ++delta_numChildrenWithCullingDisabled;
        }
        
        if (delta_numChildrenWithCullingDisabled!=0)
        {
            _Base::setNumChildrenWithCullingDisabled(
                _Base::getNumChildrenWithCullingDisabled()+delta_numChildrenWithCullingDisabled );
        }



        // could now require disabling of culling thanks to the new subgraph,
        // so need to check and update if required.
        int delta_numChildrenWithOccluderNodes = 0;
        // VBF_QT不过        if (origNode->getNumChildrenWithOccluderNodes()>0 || dynamic_cast<OccluderNode*>(origNode.get()))
        if (origNode->getNumChildrenWithOccluderNodes()>0 || dynamic_cast<IVBF_SGNodeGroupOccluder*>(origNode.get()))
        {
            --delta_numChildrenWithOccluderNodes;
        }
        // VBF_QT不过        if (newNode->getNumChildrenWithOccluderNodes()>0 || dynamic_cast<OccluderNode*>(newNode))
        if (newNode->getNumChildrenWithOccluderNodes()>0 || dynamic_cast<IVBF_SGNodeGroupOccluder*>(newNode))
        {
            ++delta_numChildrenWithOccluderNodes;
        }
        
        if (delta_numChildrenWithOccluderNodes!=0)
        {
            _Base::setNumChildrenWithOccluderNodes(
                _Base::getNumChildrenWithOccluderNodes()+delta_numChildrenWithOccluderNodes );
        }

        return true;
    }
    else return false;

}
template<class T>
BoundingSphere IVBF_SGNodeGroupImpl<T>::computeBound() const
{
    BoundingSphere bsphere;
    if (_children.empty()) 
    {
        return bsphere;
    }

    // 当子节点是Transform时特殊处理，相对于父节点坐标框架的Transforms被处理，相对于绝对坐标框架的Transforms被忽略
 
    BoundingBox bb;
    bb.init();
    NodeList::const_iterator itr;
    for(itr=_children.begin(); itr!=_children.end(); ++itr)
    {
        const osg::IVBF_SGNodeGroupTransform* transform = (*itr)->asTransform();
        if (!transform || transform->getReferenceFrame()==osg::IVBF_SGNodeGroupTransform::RELATIVE_RF)
        {
            bb.expandBy((*itr)->getBound());
        }
    }

    if (!bb.valid()) 
    {
        return bsphere;
    }

    bsphere._center = bb.center();
    bsphere._radius = 0.0f;
    for(itr=_children.begin(); itr!=_children.end(); ++itr)
    {
        const osg::IVBF_SGNodeGroupTransform* transform = (*itr)->asTransform();
        if (!transform || transform->getReferenceFrame()==osg::IVBF_SGNodeGroupTransform::RELATIVE_RF)
        {
            bsphere.expandRadiusBy((*itr)->getBound());
        }
    }

    return bsphere;
}

template<class T>
void IVBF_SGNodeGroupImpl<T>::setThreadSafeRefUnref(bool threadSafe)
{
    IVBF_SGNodeImpl<T>::setThreadSafeRefUnref(threadSafe);

    for(NodeList::const_iterator itr=_children.begin(); itr!=_children.end(); ++itr)
    {
        (*itr)->setThreadSafeRefUnref(threadSafe);
    }
}
template<class T>
void IVBF_SGNodeGroupImpl<T>::resizeGLObjectBuffers(unsigned int maxSize)
{
    IVBF_SGNodeImpl<T>::resizeGLObjectBuffers(maxSize);

    for(NodeList::const_iterator itr=_children.begin(); itr!=_children.end(); ++itr)
    {
        (*itr)->resizeGLObjectBuffers(maxSize);
    }
}

template<class T>
void IVBF_SGNodeGroupImpl<T>::releaseGLObjects(osg::State* state) const
{
    IVBF_SGNodeImpl<T>::releaseGLObjects(state);

    for(NodeList::const_iterator itr=_children.begin(); itr!=_children.end(); ++itr)
    {
        (*itr)->releaseGLObjects(state);
    }
}
