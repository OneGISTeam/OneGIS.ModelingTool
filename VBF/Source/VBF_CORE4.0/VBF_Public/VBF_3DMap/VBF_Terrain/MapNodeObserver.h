#ifndef OSGEARTH_MAP_NODE_OBSERVER_H
#define OSGEARTH_MAP_NODE_OBSERVER_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>

namespace osgEarth
{
    // 该类是一个对象或节点的标识类，表示该对象引用了CVBFO_SGNodeMap
    // 该类的用法是把它当成一个基类（需要时可用多继承），并实现set/get CVBFO_SGNodeMap
    // 如果想保存CVBFO_SGNodeMap的引用，要用observer_ptr<>
    class MapNodeObserver
    {
    public:
        virtual void setMapNode( CVBFO_SGNodeMap* mapNode ) =0;
        virtual CVBFO_SGNodeMap* GetMapNode() =0;
        virtual ~MapNodeObserver() { }
    };

    // 遍历器的基类（用于操作场景图中的MapNodeObserver实例）
    class MapNodeObserverVisitor : public osg::NodeVisitor
    {
    public:
        MapNodeObserverVisitor(osg::NodeVisitor::TraversalMode mode =osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
            : osg::NodeVisitor( mode ) { }
        
        virtual void apply( MapNodeObserver* m ) = 0;
        void tryApply( MapNodeObserver* m )
        {
            if ( m ) apply( m );
        }

        void apply(osg::IVBF_SGNode& node )
        {
            tryApply( dynamic_cast<MapNodeObserver*>(&node) );
            tryApply( dynamic_cast<MapNodeObserver*>(node.getEventCallback()) );
            tryApply( dynamic_cast<MapNodeObserver*>(node.getUpdateCallback()) );
            tryApply( dynamic_cast<MapNodeObserver*>(node.getCullCallback()) );
            traverse( node );
        }

        void apply(osg::IVBF_SGNodeGeometry& geode)
        {
            for(unsigned d=0; d<geode.getNumDrawables(); ++d )
            {
                osg::Drawable* drawable = geode.getDrawable(d);
                tryApply( dynamic_cast<MapNodeObserver*>(drawable->getEventCallback()) );
                tryApply( dynamic_cast<MapNodeObserver*>(drawable->getUpdateCallback()) );
                tryApply( dynamic_cast<MapNodeObserver*>(drawable->getCullCallback()) );
            }
            traverse( geode );
        }
    };

    // 遍历器，对场景图中的所有MapNodeObserver调用setMapNode()
    class MapNodeReplacer : public MapNodeObserverVisitor
    {
    public:
        MapNodeReplacer( CVBFO_SGNodeMap* mapNode ) : _mapNode(mapNode) { }

        void apply( MapNodeObserver* m )
        {
            m->setMapNode( _mapNode.get() );
        }

    private:
        observer_ptr<CVBFO_SGNodeMap> _mapNode;
    };

} // namespace osgEarth

#endif // OSGEARTH_MAP_NODE_OBSERVER_H
