#ifndef OSGEARTH_ANNOTATION_PLACE_NODE_H
#define OSGEARTH_ANNOTATION_PLACE_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/OrthoNode.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>

namespace osgEarth { namespace Annotation
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    // PlaceNodeÓÉ2D icon¡¢label×é³É
    class OSGEARTHANNO_EXPORT PlaceNode : public OrthoNode
    {
    public:
        META_AnnotationNode(VBF_Annotation, PlaceNode);

        /**
         * Constructs a new place node
         *
         * @param mapNode   CVBFO_SGNodeMap that helps position this annotation
         * @param position  Initial location of the annotation
         * @param iconImage Image of the place icon
         * @param labelText Text to place next to the icon
         * @param style     Optional style settings.
         */
        PlaceNode( CVBFO_SGNodeMap* mapNode, const GeoPoint&    position,
            osg::Image*        iconImage,
            const std::string& labelText,
            const Style&       style =Style() );

        /**
         * Constructs a new place node. You can specify an icon marker by
         * adding a IconSymbol to the Style.
         *
         * @param mapNode   CVBFO_SGNodeMap that helps position this annotation
         * @param position  Initial location of the annotation
         * @param labelText Text to place next to the icon
         * @param style     Optional style settings.
         */
        PlaceNode(
            CVBFO_SGNodeMap*           mapNode,
            const GeoPoint&    position,
            const std::string& labelText,
            const Style&       style =Style() );

        /**
         * Constuct a new place node entirely from symbology
         *
         * @param mapNode   CVBFO_SGNodeMap that helps position this annotation
         * @param position  Initial location of the annotation
         * @param style     Style settings.
         * @param dbOptions I/O options for embedded resource loading
         */
        PlaceNode(
            CVBFO_SGNodeMap*              mapNode,
            const GeoPoint&       position,
            const Style&          style,
            const osgDB::Options* dbOptions);

        /**
         * Deserializes a place node from CVBF_Config data. (internal method)
         */
        PlaceNode(
            CVBFO_SGNodeMap*              mapNode,
            const CVBF_Config&         conf,
            const osgDB::Options* dbOptions );

        /**
         * Image to use for the icon
         */
        void setIconImage(osg::Image* image);
        osg::Image* getIconImage() const { return _image.get(); }

        /**
         * Text label content
         */
        void setText( const std::string& text );
        const std::string& getText() const { return _text; }

        /**
         * Style (for text and placement)
         */
        void setStyle( const Style& style );
        const Style& getStyle() const { return _style; }


    public: // OrthoNode override

        virtual void setAnnotationData( AnnotationData* data );
        virtual void setDynamic( bool value );
        virtual CVBF_Config getConfig() const;

    protected:

        virtual ~PlaceNode() { }
        
    private:
        ref_ptr<osg::Image>           _image;
        std::string                        _text;
        Style                              _style;
        class osg::IVBF_SGNodeGeometry*                  _geode;
        ref_ptr<const osgDB::Options> _dbOptions;

        void init();

        // required by META_Node, but this object is not cloneable
        PlaceNode() { }
        PlaceNode(const PlaceNode& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL) { }
    };

} } // namespace osgEarth::Annotation

#endif //OSGEARTH_ANNOTATION_PLACE_NODE_H
