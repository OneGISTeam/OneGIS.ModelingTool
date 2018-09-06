#ifndef OSGEARTH_NODE_UTILS_H
#define OSGEARTH_NODE_UTILS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_CameraSlave.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroup.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupLODPaged.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>
#include <VBF_Engine/VBF_SGUtil/LineSegmentIntersector>
#include <VBF_Common/VBF_Utils/VBF_ThreadingUtils.h>
#include <set>
#include <vector>

//!! 移走
namespace osgEarth
{
	// 对节点进行操作
    struct NodeOperation : public ::CVBF_Referenced
    {
        virtual void operator()( osg::IVBF_SGNode* node ) =0;
    };

    typedef std::vector< ref_ptr<NodeOperation> > NodeOperationVector;

	// 对节点的一系列操作
    struct CVBF_NodeOperations : public ::CVBF_Referenced, public NodeOperationVector 
	{ 
	};

	// 分页LOD节点，当它把新节点合并到场景图时会激发对节点操作的回调
    class OSGEARTH_EXPORT PagedLODWithNodeOperations : public osg::PagedLOD
    {
    public:
        PagedLODWithNodeOperations( CVBF_NodeOperations* postMergeOps );

    public: // osg::Group

        virtual bool addChild( osg::IVBF_SGNode* child );
        virtual bool insertChild( unsigned index, osg::IVBF_SGNode* child );
        virtual bool replaceChild( osg::IVBF_SGNode* origChild, osg::IVBF_SGNode* newChild );

    protected:
        observer_ptr<CVBF_NodeOperations> _postMergeOps;
        
        void runPostMerge( osg::IVBF_SGNode* node );
    };


    // 访问器，查找空节点并从场景图中移除，如果入口节点为空则不工作
    class OSGEARTH_EXPORT RemoveEmptyGroupsVisitor : public osg::NodeVisitor
    {
    public:
        static void run( osg::IVBF_SGNode* pINodeEntry )
        {
            if ( pINodeEntry )
            {
                RemoveEmptyGroupsVisitor v;
                pINodeEntry->accept( v );
            }
        }

    public:
        RemoveEmptyGroupsVisitor();
        void apply(osg::IVBF_SGNodeGroup& group); //override
    };


    // 统计场景图中的点线面图元的数量
    class OSGEARTH_EXPORT PrimitiveSetTypeCounter : public osg::NodeVisitor
    {
    public:
        PrimitiveSetTypeCounter();
        virtual ~PrimitiveSetTypeCounter() { }

        void apply(class osg::IVBF_SGNodeGeometry&);

        unsigned _point;
        unsigned _line;
        unsigned _polygon;
    };

    /**
     * Visitor that finds all the parental Camera Views, and calls an operator
     * on each one.
     */
    template<typename T>
    class ViewVisitor : public osg::NodeVisitor, public T
    {
    public:
        ViewVisitor() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_PARENTS) { }
        virtual ~ViewVisitor() { }
        
		void apply(osg::IVBF_Camera& cam) 
		{
            osg::IVBF_ViewBrief* view = cam.getView();
            if ( view ) this->operator()( view );
            traverse(cam);
        }
    };

    /**
     * Functor (for use with ViewVisitor) that notifies a view that it needs to
     * redraw the scene because something has changed
     * Usage: ViewVisitor<RequestRedraw> vis; node->accept(vis);
     */
    struct RequestRedraw 
    {
        void operator()(osg::IVBF_ViewBrief* view) 
		{
            ::IVBF_GUIActionAdapter* aa = dynamic_cast< ::IVBF_GUIActionAdapter* >(view);
            if ( aa ) aa->requestRedraw();
        }
    };

    /**
     * Visitor that locates a node by its type
     */
    template<typename T>
    class FindTopMostNodeOfTypeVisitor : public osg::NodeVisitor
    {
    public:
        FindTopMostNodeOfTypeVisitor():
          osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
              _foundNode(0)
          {}

          void apply(osg::IVBF_SGNode& node)
          {
              T* result = dynamic_cast<T*>(&node);
              if (result)
              {
                  _foundNode = result;
              }
              else
              {
                  traverse(node);
              }
          }

          T* _foundNode;
    };

    /** 
     * Collects all the nodes of type "T"
     */
    template<typename T>
    struct FindNodesVisitor : public osg::NodeVisitor
    {
        FindNodesVisitor() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) { }

        void apply(osg::IVBF_SGNode& node)
        {
            T* result = dynamic_cast<T*>( &node );
            if ( result )
                _results.push_back( result );
            traverse(node);
        }

        std::vector<T*> _results;
    };

    /**
     * Searchs the scene graph downward starting at [node] and returns the first node found
     * that matches the template parameter type.
     */
    template<typename T>
    T* findTopMostNodeOfType(osg::IVBF_SGNode* node, unsigned traversalMask =~0)
    {
        if (!node) return 0;

        FindTopMostNodeOfTypeVisitor<T> fnotv;
        fnotv.setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
        fnotv.setTraversalMask(traversalMask);
        node->accept(fnotv);

        return fnotv._foundNode;
    }    

    /**
     * Searchs the scene graph upward starting at [node] and returns the first node found
     * that matches the template parameter type.
     */
    template<typename T>
    T* findFirstParentOfType(osg::IVBF_SGNode* node, unsigned traversalMask =~0)
    {
        if (!node) return 0;

        FindTopMostNodeOfTypeVisitor<T> fnotv;
        fnotv.setTraversalMode(osg::NodeVisitor::TRAVERSE_PARENTS);
        fnotv.setTraversalMask(traversalMask);
        node->accept(fnotv);

        return fnotv._foundNode;
    }

    /**
     * Searchs the scene graph starting at [node] and returns the first node found
     * that matches the template parameter type. First searched upward, then downward.
     */
    template<typename T>
    T* findRelativeNodeOfType(osg::IVBF_SGNode* node, unsigned traversalMask =~0)
    {
        if ( !node ) return 0;
        T* result = findFirstParentOfType<T>( node, traversalMask );
        if ( !result )
            result = findTopMostNodeOfType<T>( node, traversalMask );
        return result;
    }

    /**
     * Replace one group with another
     */
    inline void replaceGroup( osg::IVBF_SGNodeGroup* oldGroup, osg::IVBF_SGNodeGroup* newGroup )
    {
        if ( oldGroup && newGroup && oldGroup->getNumParents() > 0 )
        {
            for(unsigned i=0; i<oldGroup->getNumChildren(); ++i)
            {
                newGroup->addChild( oldGroup->getChild(0) );
            }

            osg::CVBF_NodeParentList parents = oldGroup->getParents();
            for(osg::CVBF_NodeParentList::iterator i = parents.begin(); i != parents.end(); ++i )
            {
                (*i)->replaceChild( oldGroup, newGroup );
            }
        }
    }

    /**
     * Remove all a group's children.
     */
    inline void clearChildren( osg::IVBF_SGNodeGroup* group )
    {
        if ( group )
            group->removeChildren( 0, group->getNumChildren() );
    }

    /**
     * OSG Group that keeps its children as observer_ptrs instead of ref_ptrs, and
     * removes them when they deref.
     */
    class OSGEARTH_EXPORT ObserverGroup : public osg::CVBF_SGNodeGroup
    {
    public:
        ObserverGroup();
        virtual void traverse( osg::NodeVisitor& nv );
        std::set<osg::IVBF_SGNode*> _orphans;
    };

    
    /**
     * Group that acts like a normal group but also notifies another
     * object when a change occurs.
     */
    template<typename T>
    class NotifierGroup : public osg::CVBF_SGNodeGroup
    {
    public:
        NotifierGroup(T* listener) : _listener(listener)
        {
            setName("Notifier Group");
        }

        virtual bool addChild( osg::IVBF_SGNode* child ) {
            bool ok = osg::CVBF_SGNodeGroup::addChild(child);
            if ( ok && _listener.valid() ) _listener->onGroupChanged(this);
            return ok;
        }
        virtual bool insertChild( unsigned index, osg::IVBF_SGNode* child ) {
            bool ok = osg::CVBF_SGNodeGroup::insertChild(index, child);
            if ( ok && _listener.valid() ) _listener->onGroupChanged(this);
            return ok;
        }
        virtual bool removeChild( osg::IVBF_SGNode* child ) {
            bool ok = osg::CVBF_SGNodeGroup::removeChild( child );
            if ( ok && _listener.valid() ) _listener->onGroupChanged(this);
            return ok;
        }
        virtual bool replaceChild( osg::IVBF_SGNode* origChild, osg::IVBF_SGNode* newChild ) {
            bool ok = osg::CVBF_SGNodeGroup::replaceChild(origChild, newChild);
            if ( ok && _listener.valid() ) _listener->onGroupChanged(this);
            return ok;
        }

    protected:
        virtual ~NotifierGroup() { }
        observer_ptr<T> _listener;
    };


    /**
     * Adjusts a node's update traversal count by a delta.
     * Only safe to call from the UPDATE thread
     */
#define ADJUST_UPDATE_TRAV_COUNT( NODE, DELTA ) \
    { \
        int oldCount = NODE ->getNumChildrenRequiringUpdateTraversal(); \
        if ( oldCount + DELTA >= 0 ) \
            NODE ->setNumChildrenRequiringUpdateTraversal( (unsigned int)(oldCount + DELTA ) ); \
    }

    /**
     * Adjusts a node's event traversal count by a delta.
     * Only safe to call from the main/event/update threads
     */
#define ADJUST_EVENT_TRAV_COUNT( NODE, DELTA ) \
    { \
        int oldCount = NODE ->getNumChildrenRequiringEventTraversal(); \
        if ( oldCount + DELTA >= 0 ) \
            NODE ->setNumChildrenRequiringEventTraversal( (unsigned int)(oldCount + DELTA ) ); \
    }
}

#endif // OSGEARTH_CACHING_H
