#ifndef OSGEARTH_ANNOTATION_CIRCLE_NODE_H
#define OSGEARTH_ANNOTATION_CIRCLE_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/LocalizedNode.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;
    using namespace osgEarth::Symbology;


    class OSGEARTHANNO_EXPORT CircleNode : public LocalizedNode
    {
    public:
        META_AnnotationNode( VBF_Annotation, CircleNode );

        CircleNode( CVBFO_SGNodeMap* mapNode, const GeoPoint& position,
            const Distance& radius, const Style& style,
            const Angle& arcStart = Angle(0.0, CVBF_Units::DEGREES),
            const Angle& arcEnd = Angle(360.0, CVBF_Units::DEGREES),
            const bool pie = false);

        CircleNode( CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf, const osgDB::Options* dbOptions);
        virtual ~CircleNode() { }


        // 设置半径
        const Distance& getRadius() const;
        void setRadius(const Distance& radius);

        // 设置/获取分段数
        unsigned int getNumSegments() const;
        void setNumSegments(unsigned int numSegments );

        // 设置/获取显示样式
        const Style& getStyle() const;
        void setStyle( const Style& style );

        // 设置/获取起始角度
        const Angle& getArcStart(void) const;
        void setArcStart(const Angle& arcStart);

        // 设置/获取终止角度
        const Angle& getArcEnd(void) const;
        void setArcEnd(const Angle& arcEnd);

        // 是否为Pie
        const bool& getPie(void) const;
        void setPie(const bool& pie);

    public: // LocalizedNode
        osg::IVBF_SGNodeGroupTransformMatrix* getTransform() { return _xform.get(); }

    public: // AnnotationNode overrides
        virtual CVBF_Config getConfig() const;

    private:
        CircleNode() { }
        CircleNode(const CircleNode& rhs, const osg::CopyOp& op) { }

        void rebuild();

        Style           _style;
        bool            _draped;
        unsigned        _numSegments;
        Distance        _radius;
        Angle          _arcStart;
        Angle          _arcEnd;
        bool           _pie;

        ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix> _xform;
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNOTATION_CIRCLE_NODE_H
