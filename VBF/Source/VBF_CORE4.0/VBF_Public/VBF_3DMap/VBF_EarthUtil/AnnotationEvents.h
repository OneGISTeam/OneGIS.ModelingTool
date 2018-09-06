
#ifndef OSGEARTH_UTIL_ANNOTATION_EVENTS_H
#define OSGEARTH_UTIL_ANNOTATION_EVENTS_H 1

#include <VBF_3DMap/VBF_EarthUtil/Common>
#include <VBF_3DMap/VBF_Annotation/AnnotationNode.h>
#include <set>

namespace osgEarth { namespace Util
{	
    using namespace osgEarth::Util;
    using namespace osgEarth::Annotation;

 	// ע���¼�������������������AnnotationEventCallback���¼�
    struct AnnotationEventHandler : public ::CVBF_Referenced
    {
        struct EventArgs
        {
            float x, y;
            int   buttons;   // see osgGA::GUIEventAdapter::MouseButtonMask
            int   modkeys;   // see osgGA::GUIEventAdapter::ModKeyMask
        };

        virtual void onClick( AnnotationNode* node, const EventArgs& details ) { }

        virtual void onHoverEnter( AnnotationNode* node, const EventArgs& details ) { }

        virtual void onHoverLeave( AnnotationNode* node, const EventArgs& details ) { }

        virtual ~AnnotationEventHandler() { }
    };




    // Event-traversal node callback ���ڴ����û���ע�Ƕ���Ľ���
 
    class OSGEARTHUTIL_EXPORT AnnotationEventCallback : public osg::NodeCallback
    {
    public:
        AnnotationEventCallback( AnnotationEventHandler* handler =0L );

        /** 
         * Adds an event handler whose events will fire upon user actions
         */
        void addHandler( AnnotationEventHandler* handler );

        /**
         * Sets whether "hovering" events will fire. By default they do. But you 
         * can disable this (if you're not using hovering) and get a small
         * performance improvement.
         */
        void setHoverEnabled( bool hoverEnabled );

    public: // osg::NodeCallback

        virtual void operator()( osg::IVBF_SGNode* node, osg::NodeVisitor* nv );

    protected:

        virtual ~AnnotationEventCallback() { }

        AnnotationEventHandler::EventArgs _args;
        bool  _mouseDown;
        bool _hoverEnabled;
        std::set<AnnotationNode*> _hovered;

        typedef std::vector< ref_ptr<AnnotationEventHandler> > Handlers;
        Handlers _handlers;

        typedef void (AnnotationEventHandler::*EventHandlerMethodPtr)(AnnotationNode*,const AnnotationEventHandler::EventArgs&);
        void fireEvent(EventHandlerMethodPtr mp, AnnotationNode* node);
    };

} } // namespace osgEarth::Annotation

#endif // OSGEARTH_ANNO_ANNOTATION_NODE_H
