#ifndef OSGEARTH_ANNOTATION_TRACK_NODE_H
#define OSGEARTH_ANNOTATION_TRACK_NODE_H 1

#include <VBF_3DMap/VBF_Annotation/OrthoNode.h>
#include <VBF_3DMap/VBF_Symbology/Style.h>
#include <VBF_Common/VBF_Utils/VBF_STLContainers.h>
#include <VBF_Engine/VBF_SceneGraph/Image>
#include <VBF_Engine/VBF_Text/String>


class CVBFO_SGNodeMap;

    
namespace osgEarth { namespace Annotation
{	
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    /**
     * Defines for a labeling field associated with a TrackNode. A TrackNode
     * can have zero or more "fields", each being a text label rendered 
     * along with the node's icon.
     */
    struct /*no-export*/ TrackNodeField
    {
        /**
         * Constructs a new field definition.
         * @param symbol  Text symbol describing the field's appearance and placement
         * @param dynamic Whether the text label will be dynamic; i.e. whether the user
         *                intends to update it at runtime. Setting this to "false" for a
         *                static label yields better performance in a multithreaded app.
         */
        TrackNodeField( const TextSymbol* symbol, bool dynamic =true )
            : _symbol(symbol), _dynamic(dynamic) { }

        /** other constructors (internal) */
        TrackNodeField()
            : _dynamic(true) { }

        TrackNodeField( const TrackNodeField& rhs ) 
            : _symbol(rhs._symbol.get()), _dynamic(rhs._dynamic) { }

        ref_ptr<const TextSymbol> _symbol;
        bool                           _dynamic;
    };

    /**
     * Schema that maps field names to field definitions.
     */
    typedef CVBF_MapFast<std::string, TrackNodeField> TrackNodeFieldSchema;

    /** 
     * TrackNode是可移动的、由icon表示的单点，可选项包括：可放置的文字标注、局部的几何体
     *
     * TrackNode不会自动支持地形固定（terrain clamping），因为
     * its intention is for use as a trackable entity marker, and
     * presumably the entity itself will be responsible for its own absolute
     * positioning (and clamping, if applicable).
     */
    class OSGEARTHANNO_EXPORT TrackNode : public OrthoNode
    {
    public:
        META_AnnotationNode(VBF_Annotation, TrackNode);

        /**
         * Constructs a new track node
         * @param mapNode     CVBF_Map node under which this track will live
         * @param position    Initial position
         * @param image       Icon image to use
         * @param fieldSchema Schema for track label fields
         */
        TrackNode( CVBFO_SGNodeMap* mapNode, const GeoPoint& position, osg::Image* image, const TrackNodeFieldSchema& fieldSchema );

        /**
         * Constructs a new track node
         * @param mapNode     CVBF_Map node under which this track will live
         * @param position    Initial position
         * @param style       Style containing an IconSymbol for the image
         * @param fieldSchema Schema for track label fields
         */
        TrackNode( CVBFO_SGNodeMap* mapNode,const GeoPoint& position, const Style& style, const TrackNodeFieldSchema& fieldSchema );

        /** 
         * Sets the value of one of the field labels.
         * @param name  Field name as identified in the field schema.
         * @param value Value to which to set the field label.
         */
        void setFieldValue( const std::string& name, const std::string& value ) { setFieldValue(name, osgText::String(value)); }
        void setFieldValue( const std::string& name, const osgText::String& value );

        /**
         * Adds an arbitrary drawable to this track node. Useful for adding
         * user-defined graphics.
         * @param name     Name of the drawable (for later retrieval). The namespace
         *                 should not conflict with that of the field schema.
         * @param drawable Drawable to add.
         */
        void addDrawable( const std::string& name, osg::Drawable* drawable );

        /**
         * Gets a drawable (as previously added with addDrawable). 
         * Note: Make sure that if you are modifying a drawable, mark it with a 
         * DYNAMIC data variance so it will be thread-safe.
         */
        osg::Drawable* getDrawable( const std::string& name ) const;

    public: // override

        virtual void setAnnotationData( AnnotationData* data );

    protected:

        virtual ~TrackNode() { }

        Style             _style;
        class osg::IVBF_SGNodeGeometry* _geode;

        typedef CVBF_MapFast<std::string, osg::Drawable*> NamedDrawables;
        NamedDrawables _namedDrawables;

        void init( const TrackNodeFieldSchema& schema );

    private:
        // required by META_Node, but this object is not cloneable
        TrackNode() { }
        TrackNode(const TrackNode& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL) { }

    };

} } // namespace osgEarth::Annotation

#endif //OSGEARTH_ANNOTATION_TRACK_NODE_H
