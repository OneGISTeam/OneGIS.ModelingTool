#ifndef OSGEARTH_ANNO_LOCAL_GEOMETRY_NODE_H
#define OSGEARTH_ANNO_LOCAL_GEOMETRY_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/LocalizedNode.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_3DMap/VBF_Symbology/Geometry.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    /**
     * Simple node that renders geometry into a scene graph node. The geometry
     * is in a local tangent plane that may be positioned somewhere on the 
     * CVBF_Map's surface.
     */
    class OSGEARTHANNO_EXPORT LocalGeometryNode : public LocalizedNode
    {
    public:
        LocalGeometryNode( CVBFO_SGNodeMap* mapNode, Geometry* geom, const Style& style );
        LocalGeometryNode( CVBFO_SGNodeMap* mapNode,osg::IVBF_SGNode* node,
                                   const Style& style =Style() );

        virtual ~LocalGeometryNode() { }

        // 设置/获取创建节点的Style
        const Style& getStyle() const { return _style; }
        void setStyle(const Style& style);

        // 设置/获取创建节点的geometry
        const Geometry* getGeometry() const { return _geom.get(); }
        void setGeometry( Geometry* geom );

        // 设置/获取关联的外部节点
        osg::IVBF_SGNode* getNode() { return _node; }
        void setNode( osg::IVBF_SGNode* node );

    public:
        LocalGeometryNode(CVBFO_SGNodeMap* mapNode,
            const CVBF_Config& conf,const osgDB::Options* dbOptions );

        virtual CVBF_Config getConfig() const;

    protected: // LocalizedNode

        virtual osg::IVBF_SGNodeGroupTransformMatrix* getTransform() { return _xform.get(); }

    protected:

        Style                        _style;
        ref_ptr<osg::IVBF_SGNode>    _node;
        ref_ptr<Geometry>       _geom;

        ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix> _xform;

        void initNode();
        void initGeometry(const osgDB::Options*);
        void init(const osgDB::Options*);
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNO_LOCAL_GEOMETRY_NODE_H
