#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNode.h>
/*
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <VBF_Base/VBF_Notify.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupOccluder.h>
//#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransform.h>
#include <VBF_Engine/VBF_SceneGraph/UserDataContainer>
*/
//#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupOccluder.h>

#include <algorithm>


namespace osg
{
	//extern OSG_EXPORT Matrix computeLocalToWorld(const CVBF_SGNodePath& nodePath, bool ignoreCameras);

    /// 生成NodePathList的辅助类
    class CollectParentPaths : public NodeVisitor
    {
    public:
        CollectParentPaths(const osg::IVBF_SGNode* haltTraversalAtNode=0) : 
                     osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_PARENTS),
                     _haltTraversalAtNode(haltTraversalAtNode)
        {
        }

        virtual void apply(osg::IVBF_SGNode& node)
        {
            if (node.getNumParents()==0 || &node==_haltTraversalAtNode)
            {
                _nodePaths.push_back(getNodePath());
            }
            else
            {
                traverse(node);
            }
       }

        const IVBF_SGNode*     _haltTraversalAtNode;
        osg::CVBF_SGNodePath        _nodePath;
        osg::NodePathList           _nodePaths;
    };


}

template<class T>
osg::IVBF_SGNodeImpl<T>::IVBF_SGNodeImpl() : T(true)	 
{
    _boundingSphereComputed = false;
    _nodeMask = 0xffffffff;
    
    _numChildrenRequiringUpdateTraversal = 0;

    _numChildrenRequiringEventTraversal = 0;

    _cullingActive = true;
    _numChildrenWithCullingDisabled = 0;

    _numChildrenWithOccluderNodes = 0;

    T::m_dwTypeID = 0x10000000; //类型标识
}

template<class T>
osg::IVBF_SGNodeImpl<T>::IVBF_SGNodeImpl(const IVBF_SGNodeImpl& node,const CopyOp& copyop):
        T(node,copyop),
        _initialBound(node._initialBound),
        _boundingSphere(node._boundingSphere),
        _boundingSphereComputed(node._boundingSphereComputed),
        _parents(), // leave empty as parentList is managed by Group.
        _updateCallback((osg::NodeCallback *)copyop(node._updateCallback.get())),
        _numChildrenRequiringUpdateTraversal(0), // assume no children yet.
        _numChildrenRequiringEventTraversal(0), // assume no children yet.
        _cullCallback((osg::NodeCallback *)copyop(node._cullCallback.get())),
        _cullingActive(node._cullingActive),
        _numChildrenWithCullingDisabled(0), // assume no children yet.
        _numChildrenWithOccluderNodes(0),
        _nodeMask(node._nodeMask)
{
    T::m_dwTypeID = 0x10000000; //类型标识

    setStateSet((osg::StateSet *)copyop(node._stateset.get()));
}

template<class T>
osg::IVBF_SGNodeImpl<T>::~IVBF_SGNodeImpl()
{
    // 干净的detatch所有关联的stateset (包括 remove parent links)
    setStateSet(0);   
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::addParent(osg::IVBF_SGNodeGroup* node)
{
    OpenThreads::ScopedPointerLock<OpenThreads::Mutex> lock(CVBF_Referenced::getRefMutex());

    _parents.push_back(node);
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::removeParent(osg::IVBF_SGNodeGroup* node)
{
    OpenThreads::ScopedPointerLock<OpenThreads::Mutex> lock(CVBF_Referenced::getRefMutex());

    CVBF_NodeParentList::iterator pitr = std::find(_parents.begin(),_parents.end(),node);
    if (pitr!=_parents.end()) _parents.erase(pitr);
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::accept(osg::NodeVisitor& nv)
{
    if (nv.validNodeMask(*this)) 
    {
        nv.pushOntoNodePath(this);
        nv.apply(*this);
        nv.popFromNodePath();
    }
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::ascend(NodeVisitor& nv)
{
    std::for_each(_parents.begin(),_parents.end(),NodeAcceptOp(nv));
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::setStateSet(osg::StateSet* stateset)
{
    
    if (_stateset==stateset) return;// 没有变化什么也不做。
    
    // track whether we need to account for the need to do a update or event traversal.
    int delta_update = 0;
    int delta_event = 0;

    // remove this node from the current statesets parent list 
    if (_stateset.valid())
    {
        _stateset->removeParent(this);
        if (_stateset->requiresUpdateTraversal()) --delta_update;
        if (_stateset->requiresEventTraversal()) --delta_event;
    }
    
    // set the stateset.
    _stateset = stateset;
    
    // add this node to the new stateset to the parent list.
    if (_stateset.valid())
    {
        _stateset->addParent(this);
        if (_stateset->requiresUpdateTraversal()) ++delta_update;
        if (_stateset->requiresEventTraversal()) ++delta_event;
    }
    
    if (delta_update!=0)
    {
        setNumChildrenRequiringUpdateTraversal(getNumChildrenRequiringUpdateTraversal()+delta_update);
    }

    if (delta_event!=0)
    {
        setNumChildrenRequiringEventTraversal(getNumChildrenRequiringEventTraversal()+delta_event);
    }
}

template<class T>
osg::StateSet* osg::IVBF_SGNodeImpl<T>::getOrCreateStateSet()
{
    if (!_stateset) setStateSet(new StateSet);
    return _stateset.get();
}

template<class T>
osg::NodePathList osg::IVBF_SGNodeImpl<T>::getParentalNodePaths(osg::IVBF_SGNode* haltTraversalAtNode) const
{
	
    CollectParentPaths cpp(haltTraversalAtNode);
    const_cast<IVBF_SGNodeImpl*>(this)->accept(cpp);
    return cpp._nodePaths;
	
}
template<class T>
osg::MatrixList osg::IVBF_SGNodeImpl<T>::getWorldMatrices(const osg::IVBF_SGNode* haltTraversalAtNode) const
{
	
    CollectParentPaths cpp(haltTraversalAtNode);
    const_cast<IVBF_SGNodeImpl*>(this)->accept(cpp);
    
    MatrixList matrices;
    
    for(NodePathList::iterator itr = cpp._nodePaths.begin(); itr != cpp._nodePaths.end(); ++itr)
    {
        CVBF_SGNodePath& nodePath = *itr;
        if (nodePath.empty())
        {
            matrices.push_back(osg::Matrix::identity());
        }
        else
        {
            matrices.push_back(osg::computeLocalToWorld(nodePath,true));
        }
    }
    
    return matrices;
}





template<class T>
void osg::IVBF_SGNodeImpl<T>::setUpdateCallback(NodeCallback* nc)
{
     if (_updateCallback==nc) return; // 无变化，返回
    
 	 // 更新回调重新设置，既要设置成员变量_updateCallback，又要重新设置numChildrenRequiringAppTraversal


    // 更新父节点的numChildrenRequiringAppTraversal
    // 如果_numChildrenRequiringUpdateTraversal!=0 则父节点不会被影响
    if (_numChildrenRequiringUpdateTraversal==0 && !_parents.empty())
    {
        int delta = 0;

        if (_updateCallback.valid()) --delta;

        if (nc) ++delta;

        if (delta!=0)
        {
            // the number of callbacks has changed, need to pass this on to parents so they know 
			// whether app traversal is required on this subgraph.
            for(CVBF_NodeParentList::iterator itr =_parents.begin(); itr != _parents.end(); ++itr)
            {    
                (*itr)->setNumChildrenRequiringUpdateTraversal( (*itr)->getNumChildrenRequiringUpdateTraversal()+delta );
            }
        }
    }

    _updateCallback = nc; // 设置更新回调
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::setNumChildrenRequiringUpdateTraversal(unsigned int num)
{
    if (_numChildrenRequiringUpdateTraversal==num) return; // 无变化，返回

    if (!_updateCallback && !_parents.empty())
    {   
        int delta = 0;
        if (_numChildrenRequiringUpdateTraversal>0) --delta;
        if (num>0) ++delta;
        if (delta!=0)
        {
            // the number of callbacks has changed, need to pass this on to parents so they know 
			// whether app traversal is required on this subgraph.
            for(CVBF_NodeParentList::iterator itr =_parents.begin(); itr != _parents.end(); ++itr)
            {    
                (*itr)->setNumChildrenRequiringUpdateTraversal( (*itr)->getNumChildrenRequiringUpdateTraversal()+delta );
            }

        }
    }
    
    // finally update this objects value.
    _numChildrenRequiringUpdateTraversal=num;   
}


template<class T>
void osg::IVBF_SGNodeImpl<T>::setEventCallback(NodeCallback* nc)
{
    // if no changes just return.
    if (_eventCallback==nc) return;
    
    // event callback has been changed, will need to Event
    // both _EventCallback and possibly the numChildrenRequiringAppTraversal
    // if the number of callbacks changes.


    // Event the parents numChildrenRequiringAppTraversal
    // note, if _numChildrenRequiringEventTraversal!=0 then the
    // parents won't be affected by any app callback change,
    // so no need to inform them.
    if (_numChildrenRequiringEventTraversal==0 && !_parents.empty())
    {
        int delta = 0;
        if (_eventCallback.valid()) --delta;
        if (nc) ++delta;
        if (delta!=0)
        {
            // the number of callbacks has changed, need to pass this
            // on to parents so they know whether app traversal is
            // required on this subgraph.
            for(CVBF_NodeParentList::iterator itr =_parents.begin(); itr != _parents.end(); ++itr)
            {    
                (*itr)->setNumChildrenRequiringEventTraversal( (*itr)->getNumChildrenRequiringEventTraversal()+delta );
            }

        }
    }

    // set the app callback itself.
    _eventCallback = nc;

}

template<class T>
void osg::IVBF_SGNodeImpl<T>::setNumChildrenRequiringEventTraversal(unsigned int num)
{
    // if no changes just return.
    if (_numChildrenRequiringEventTraversal==num) return;

    // note, if _EventCallback is set then the
    // parents won't be affected by any changes to
    // _numChildrenRequiringEventTraversal so no need to inform them.
    if (!_eventCallback && !_parents.empty())
    {
    
        // need to pass on changes to parents.        
        int delta = 0;
        if (_numChildrenRequiringEventTraversal>0) --delta;
        if (num>0) ++delta;
        if (delta!=0)
        {
            // the number of callbacks has changed, need to pass this
            // on to parents so they know whether app traversal is
            // required on this subgraph.
            for(CVBF_NodeParentList::iterator itr =_parents.begin(); itr != _parents.end(); ++itr)
            {    
                (*itr)->setNumChildrenRequiringEventTraversal( (*itr)->getNumChildrenRequiringEventTraversal()+delta );
            }

        }
    }
    
    // finally Event this objects value.
    _numChildrenRequiringEventTraversal=num;
    
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::setCullingActive(bool active)
{
    // if no changes just return.
    if (_cullingActive == active) return;
    
    // culling active has been changed, will need to update
    // both _cullActive and possibly the parents numChildrenWithCullingDisabled
    // if culling disabled changes.

    // update the parents _numChildrenWithCullingDisabled
    // note, if _numChildrenWithCullingDisabled!=0 then the
    // parents won't be affected by any app callback change,
    // so no need to inform them.
    if (_numChildrenWithCullingDisabled==0 && !_parents.empty())
    {
        int delta = 0;
        if (!_cullingActive) --delta;
        if (!active) ++delta;
        if (delta!=0)
        {
            // the number of callbacks has changed, need to pass this
            // on to parents so they know whether app traversal is
            // required on this subgraph.
            for(CVBF_NodeParentList::iterator itr =_parents.begin(); itr != _parents.end(); ++itr)
            {    
                (*itr)->setNumChildrenWithCullingDisabled( (*itr)->getNumChildrenWithCullingDisabled()+delta );
            }

        }
    }

    // set the cullingActive itself.
    _cullingActive = active;
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::setNumChildrenWithCullingDisabled(unsigned int num)
{
    if (_numChildrenWithCullingDisabled==num) return;

    // note, if _cullingActive is false then the
    // parents won't be affected by any changes to
    // _numChildrenWithCullingDisabled so no need to inform them.
    if (_cullingActive && !_parents.empty())
    {
    
        // need to pass on changes to parents.        
        int delta = 0;
        if (_numChildrenWithCullingDisabled>0) --delta;
        if (num>0) ++delta;
        if (delta!=0)
        {
            // the number of callbacks has changed, need to pass this
            // on to parents so they know whether app traversal is
            // required on this subgraph.
            for(CVBF_NodeParentList::iterator itr =_parents.begin(); itr != _parents.end(); ++itr)
            {    
                (*itr)->setNumChildrenWithCullingDisabled( (*itr)->getNumChildrenWithCullingDisabled()+delta );
            }

        }
    }
    
    // finally update this objects value.
    _numChildrenWithCullingDisabled=num;
}


template<class T>
void osg::IVBF_SGNodeImpl<T>::setNumChildrenWithOccluderNodes(unsigned int num)
{
    if (_numChildrenWithOccluderNodes==num) return;

    // 通知父节点。
	// 如果本节点是OccluderNode，则父节点不会被_numChildrenWithOccluderNodes的变化所影响，不需要通知父节点 。
    if (!dynamic_cast<IVBF_SGNodeGroupOccluder*>(this) && !_parents.empty())
    {
    
        // need to pass on changes to parents.        
        int delta = 0;
        if (_numChildrenWithOccluderNodes>0) --delta;
        if (num>0) ++delta;
        if (delta!=0)
        {
            // the number of callbacks has changed, need to pass this
            // on to parents so they know whether app traversal is
            // required on this subgraph.
            for(CVBF_NodeParentList::iterator itr =_parents.begin(); itr != _parents.end(); ++itr)
            {    
                (*itr)->setNumChildrenWithOccluderNodes( (*itr)->getNumChildrenWithOccluderNodes()+delta );
            }

        }
    }
    
    // finally update this objects value.
    _numChildrenWithOccluderNodes=num;
    
}

template<class T>
bool osg::IVBF_SGNodeImpl<T>::containsOccluderNodes() const
{
    return _numChildrenWithOccluderNodes>0 || dynamic_cast<const IVBF_SGNodeGroupOccluder*>(this);
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::setDescriptions(const IVBF_SGNode::DescriptionList& descriptions)
{
    CVBF_Object::getOrCreateUserDataContainer()->setDescriptions(descriptions);
}

template<class T>
osg::IVBF_SGNode::DescriptionList& osg::IVBF_SGNodeImpl<T>::getDescriptions()
{
    return CVBF_Object::getOrCreateUserDataContainer()->getDescriptions();
}



template<class T>
const osg::IVBF_SGNode::DescriptionList& osg::IVBF_SGNodeImpl<T>::getDescriptions() const
{
    if(T::m_pUserDataContainer) return T::m_pUserDataContainer->getDescriptions();
    //!!!20130715 else return getStaticDescriptionList();
    return T::m_pUserDataContainer->getDescriptions();
}

template<class T>
std::string& osg::IVBF_SGNodeImpl<T>::getDescription(unsigned int i)
{
    return CVBF_Object::getOrCreateUserDataContainer()->getDescriptions()[i];
}

template<class T>
const std::string& osg::IVBF_SGNodeImpl<T>::getDescription(unsigned int i) const
{
    if (T::m_pUserDataContainer) return T::m_pUserDataContainer->getDescriptions()[i];
    //!!!20130715 else return getStaticDescriptionList()[i];
    return T::m_pUserDataContainer->getDescriptions()[i];
}

template<class T>
unsigned int osg::IVBF_SGNodeImpl<T>::getNumDescriptions() const
{
    return T::m_pUserDataContainer ? T::m_pUserDataContainer->getDescriptions().size() : 0;
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::addDescription(const std::string& desc)
{
    CVBF_Object::getOrCreateUserDataContainer()->getDescriptions().push_back(desc);
}

template<class T>
osg::BoundingSphere osg::IVBF_SGNodeImpl<T>::computeBound() const
{
    return BoundingSphere();
}


template<class T>
void osg::IVBF_SGNodeImpl<T>::dirtyBound()
{
    if (_boundingSphereComputed)
    {
        _boundingSphereComputed = false;

        // 节点的包围球变化了，父节点的包围球也会发生变化。
        for(CVBF_NodeParentList::iterator  itr=_parents.begin(); itr!=_parents.end(); ++itr)
        {
            (*itr)->dirtyBound();
        }

    }
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::setThreadSafeRefUnref(bool threadSafe)
{
    T::setThreadSafeRefUnref(threadSafe);
    
    if (_stateset.valid()) _stateset->setThreadSafeRefUnref(threadSafe);
    if (_updateCallback.valid()) _updateCallback->setThreadSafeRefUnref(threadSafe);
    if (_eventCallback.valid()) _eventCallback->setThreadSafeRefUnref(threadSafe);
    if (_cullCallback.valid()) _cullCallback->setThreadSafeRefUnref(threadSafe);
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::resizeGLObjectBuffers(unsigned int maxSize)
{
    if (_stateset.valid()) _stateset->resizeGLObjectBuffers(maxSize);
    if (_updateCallback.valid()) _updateCallback->resizeGLObjectBuffers(maxSize);
    if (_eventCallback.valid()) _eventCallback->resizeGLObjectBuffers(maxSize);
    if (_cullCallback.valid()) _cullCallback->resizeGLObjectBuffers(maxSize);
}

template<class T>
void osg::IVBF_SGNodeImpl<T>::releaseGLObjects(osg::State* state) const
{
    if (_stateset.valid()) _stateset->releaseGLObjects(state);
    if (_updateCallback.valid()) _updateCallback->releaseGLObjects(state);
    if (_eventCallback.valid()) _eventCallback->releaseGLObjects(state);
    if (_cullCallback.valid()) _cullCallback->releaseGLObjects(state);
}




/* !!!20130715
static OpenThreads::Mutex s_mutex_StaticDescriptionList;

static const IVBF_SGNodeImpl::DescriptionList& getStaticDescriptionList()
{
    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(s_mutex_StaticDescriptionList);
    static IVBF_SGNodeImpl::DescriptionList s_descriptionList;
    return s_descriptionList;
}
*/
