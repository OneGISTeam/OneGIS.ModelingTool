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

    // ����һ���������ر����Բ
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


        const Distance& getRadiusMajor() const; // ���뾶
        const Distance& getRadiusMinor() const; // �̰뾶
        void setRadiusMajor( const Distance& radiusMajor );
        void setRadiusMinor( const Distance& radiusMinor );

        // ���ó��뾶�Ͷ̰뾶
        void setRadii( const Distance& radiusMajor, const Distance& radiusMinor );

        const Angle& getRotationAngle() const; // ��ת��
        void setRotationAngle(const Angle& rotationAngle);

        // ����/��ȡ�ֶ���
        unsigned int getNumSegments() const;
        void setNumSegments(unsigned int numSegments );

        // ����/��ȡ��ʾ��ʽ
        const Style& getStyle() const;
        void setStyle( const Style& style );

        // ����/��ȡ��ʼ�Ƕ�
        const Angle& getArcStart(void) const;
        void setArcStart(const Angle& arcStart);

        // ����/��ȡ��ֹ�Ƕ�
        const Angle& getArcEnd(void) const;
        void setArcEnd(const Angle& arcEnd);

        // �Ƿ�ΪPie
        const bool& getPie(void) const;
        void setPie(const bool& pie);

        // �Ƿ����ر�
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
