#ifndef OSGGA_EVENTVISITOR
#define OSGGA_EVENTVISITOR 1

#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometryBillboard.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupLODImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupSwitch.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupLightSource.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupTransform.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupProjection.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupOccluder.h>

#include <VBF_Display/VBF_Manipulator/VBF_GUIEventAdapter.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>
#include <VBF_Display/VBF_Manipulator/VBF_EventQueue.h>

namespace osgGA {

/**
 * Basic EventVisitor implementation for animating a scene.
 * This visitor traverses the scene graph, calling each nodes appCallback if
 * it exists. 
 */
class OSGGA_EXPORT EventVisitor : public osg::NodeVisitor
{
    public:

        EventVisitor();
        virtual ~EventVisitor();
        
        META_NodeVisitor("osgGA","EventVisitor")
        
        void setActionAdapter(::IVBF_GUIActionAdapter* actionAdapter) { _actionAdapter=actionAdapter; }
        
        ::IVBF_GUIActionAdapter* getActionAdapter() { return _actionAdapter; }

        const ::IVBF_GUIActionAdapter* getActionAdapter() const { return _actionAdapter; }


        typedef std::list< ref_ptr<GUIEventAdapter> > EventList;
        
        void addEvent(GUIEventAdapter* pEvent);
        void removeEvent(GUIEventAdapter* pEvent);
        
        void setEventHandled(bool handled) { _handled = handled; }
        bool getEventHandled() const { return _handled; }
        

        void setEvents(const CVBF_EventQueue::Events& events) { _events = events; }
        CVBF_EventQueue::Events& getEvents() { return _events; }
        const CVBF_EventQueue::Events& getEvents() const { return _events; }
        
    public:
    
        virtual void reset();

        /** During traversal each type of node calls its callbacks and its children traversed. */
        virtual void apply(osg::IVBF_SGNode& node)         { handle_callbacks_and_traverse(node); }
        
        virtual void apply(osg::IVBF_SGNodeGeometry& node)        { handle_geode_callbacks(node); }
        virtual void apply(osg::IVBF_SGNodeGeometryBillboard& node)    { handle_geode_callbacks(node); }
        
        virtual void apply(osg::IVBF_SGNodeGroupLightSource& node)  { handle_callbacks_and_traverse(node); }
        
        virtual void apply(osg::IVBF_SGNodeGroup& node)        { handle_callbacks_and_traverse(node); }
        virtual void apply(osg::IVBF_SGNodeGroupTransform& node)    { handle_callbacks_and_traverse(node); }
        virtual void apply(osg::IVBF_SGNodeGroupProjection& node)   { handle_callbacks_and_traverse(node); }
        virtual void apply(osg::IVBF_SGNodeGroupSwitch& node)       { handle_callbacks_and_traverse(node); }
        virtual void apply(osg::IVBF_SGNodeGroupLOD& node)          { handle_callbacks_and_traverse(node); }
        virtual void apply(osg::IVBF_SGNodeGroupOccluder& node) { handle_callbacks_and_traverse(node); }


    protected:
        EventVisitor& operator = (const EventVisitor&) { return *this; } // ·ÀÖ¹¿½±´²Ù×÷
        
        inline void handle_callbacks(osg::StateSet* stateset)
        {
            if (stateset && stateset->requiresEventTraversal())
            {
                stateset->runEventCallbacks(this);
            }
        }

        inline void handle_callbacks_and_traverse(osg::IVBF_SGNode& node)
        {
            handle_callbacks(node.getStateSet());

            osg::NodeCallback* callback = node.getEventCallback();
            if (callback) (*callback)(&node,this);
            else if (node.getNumChildrenRequiringEventTraversal()>0) traverse(node);
        }

        inline void handle_geode_callbacks(osg::IVBF_SGNodeGeometry& node)
        {
            handle_callbacks(node.getStateSet());

            osg::NodeCallback* callback = node.getEventCallback();
            if (callback) (*callback)(&node,this);
            /*else if (node.getNumChildrenRequiringEventTraversal()>0)*/ 
            traverseGeode(node);
        }
        
        inline void traverseGeode(osg::IVBF_SGNodeGeometry& geode)
        {
            traverse((osg::IVBF_SGNode&)geode);
            
            // Call the app callbacks on the drawables.
            for(unsigned int i=0;i<geode.getNumDrawables();++i)
            {
                osg::Drawable::EventCallback* callback = geode.getDrawable(i)->getEventCallback();
                if (callback) callback->event(this,geode.getDrawable(i));

                handle_callbacks(geode.getDrawable(i)->getStateSet());
            }
        }
        
        ::IVBF_GUIActionAdapter*        _actionAdapter;
        
        ref_ptr<GUIEventAdapter>   _accumulateEventState;
        
        bool                            _handled;
        CVBF_EventQueue::Events              _events;
    
};

}

#endif

