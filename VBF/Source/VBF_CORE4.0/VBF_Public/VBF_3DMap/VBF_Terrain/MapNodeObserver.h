#ifndef OSGEARTH_MAP_NODE_OBSERVER_H
#define OSGEARTH_MAP_NODE_OBSERVER_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>

namespace osgEarth
{
    // ������һ�������ڵ�ı�ʶ�࣬��ʾ�ö���������CVBFO_SGNodeMap
    // ������÷��ǰ�������һ�����ࣨ��Ҫʱ���ö�̳У�����ʵ��set/get CVBFO_SGNodeMap
    // ����뱣��CVBFO_SGNodeMap�����ã�Ҫ��observer_ptr<>
    class MapNodeObserver
    {
    public:
        virtual void setMapNode( CVBFO_SGNodeMap* mapNode ) =0;
        virtual CVBFO_SGNodeMap* GetMapNode() =0;
        virtual ~MapNodeObserver() { }
    };

    // �������Ļ��ࣨ���ڲ�������ͼ�е�MapNodeObserverʵ����
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

    // ���������Գ���ͼ�е�����MapNodeObserver����setMapNode()
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
