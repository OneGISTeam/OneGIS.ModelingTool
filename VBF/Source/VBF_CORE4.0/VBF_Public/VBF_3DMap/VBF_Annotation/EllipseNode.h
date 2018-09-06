#ifndef OSGEARTH_ANNOTATION_ELLIPSE_NODE_H
#define OSGEARTH_ANNOTATION_ELLIPSE_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/LocalizedNode.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_Common/VBF_Utils/VBF_Units.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>

namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    // 绘制一个可以贴地表的椭圆
    class OSGEARTHANNO_EXPORT EllipseNode : public LocalizedNode
    {
    public:
        META_AnnotationNode( VBF_Annotation, EllipseNode );

        EllipseNode( CVBFO_SGNodeMap* mapNode, const GeoPoint& position,
            const Distance& radiusMajor, const Distance& radiusMinor,
            const Angle& rotationAngle, const Style& style,
            const Angle& arcStart = Angle(0.0, CVBF_Units::DEGREES),
            const Angle& arcEnd = Angle(360.0, CVBF_Units::DEGREES),
            const bool bPie = false);

        virtual ~EllipseNode() { }


        const Distance& getRadiusMajor() const; // 长半径
        const Distance& getRadiusMinor() const; // 短半径
        void setRadiusMajor( const Distance& radiusMajor );
        void setRadiusMinor( const Distance& radiusMinor );

        // 设置长半径和短半径
        void setRadii( const Distance& radiusMajor, const Distance& radiusMinor );

        const Angle& getRotationAngle() const; // 旋转角
        void setRotationAngle(const Angle& rotationAngle);

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

        // 是否贴地表
        bool isDraped() const { return _draped; }

    public:

        EllipseNode(CVBFO_SGNodeMap* mapNode, const CVBF_Config& conf, const osgDB::Options* dbOptions);
        virtual CVBF_Config getConfig() const;


    public: // LocalizedNode

        osg::IVBF_SGNodeGroupTransformMatrix* getTransform() { return _xform.get(); }


    private:
        EllipseNode() { }
        EllipseNode(const EllipseNode& rhs, const osg::CopyOp& op) { }

        void rebuild();
        
        Style _style;
        bool _draped;
        Angle _rotationAngle;
        Distance _radiusMajor;
        Distance _radiusMinor;
        Angle _arcStart;
        Angle _arcEnd;
        bool  _pie;
        unsigned int _numSegments;
        ref_ptr<osg::IVBF_SGNodeGroupTransformMatrix> _xform;
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNOTATION_ELLIPSE_NODE_H
