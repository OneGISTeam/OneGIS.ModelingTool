#ifndef OSGEARTHANNO_ANNOTATION_EDITING_H
#define OSGEARTHANNO_ANNOTATION_EDITING_H 1

#include <VBF_3DMap/VBF_Annotation/Common>
#include <VBF_3DMap/VBF_Annotation/LocalizedNode.h>
#include <VBF_3DMap/VBF_Annotation/CircleNode.h>
#include <VBF_3DMap/VBF_Annotation/EllipseNode.h>
#include <VBF_3DMap/VBF_Annotation/RectangleNode.h>
#include <VBF_3DMap/VBF_Terrain/Draggers.h>
#include <VBF_3DMap/VBF_Terrain/VBF_MapNode.h>

namespace osgEarth { namespace Annotation {

     /**
     * An editor node that allows you to move the position of LocalizedNode annotations    
     */
    class OSGEARTHANNO_EXPORT LocalizedNodeEditor : public osg::CVBF_SGNodeGroup
    {
    public:
        /**
         * Create a new LocalizedAnnotationEditor
         * @param localizedNode
         *        The LocalizedNode to edit
         */
        LocalizedNodeEditor(LocalizedNode* localizedNode);    
        
        virtual ~LocalizedNodeEditor();    

        virtual void updateDraggers();

        Dragger* getPositionDragger() { return _dragger; }

        void setPosition( const GeoPoint& pos );

    protected:
        ref_ptr< LocalizedNode > _node;
        Dragger* _dragger;
    };

    class OSGEARTHANNO_EXPORT CircleNodeEditor : public LocalizedNodeEditor
    {
    public:
        /**
         * Create a new CircleEditor
         * @param circleNode
         *        The CircleNode to edit
         */
        CircleNodeEditor(CircleNode* circleNode);    
        
        virtual ~CircleNodeEditor();    

        void computeBearing();

        void setBearing( const Angle& value );

        virtual void updateDraggers();

        Dragger* getRadiusDragger() { return _radiusDragger; }

        double _bearing;

        Dragger* _radiusDragger;
    };

    class OSGEARTHANNO_EXPORT EllipseNodeEditor : public LocalizedNodeEditor
    {
    public:
        /**
         * Create a new EllipseNodeEditor
         * @param ellipseNode
         *        The EllipseNodeEditor to edit
         */
        EllipseNodeEditor(EllipseNode* ellipseNode);    
        
        virtual ~EllipseNodeEditor();    

        virtual void updateDraggers();

        Dragger* _majorDragger;
        Dragger* _minorDragger;
    };

    class OSGEARTHANNO_EXPORT RectangleNodeEditor : public LocalizedNodeEditor
    {
    public:
        /**
         * Create a new RectangleNodeEditor
         * @param rectangleNode
         *        The RectangleNodeEditor to edit
         */
        RectangleNodeEditor(RectangleNode* rectangleNode);    
        
        virtual ~RectangleNodeEditor();    

        virtual void updateDraggers();

        Dragger* _llDragger;
        Dragger* _lrDragger;
        Dragger* _urDragger;
        Dragger* _ulDragger;
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTHANNO_FEATURE_EDITING_H
