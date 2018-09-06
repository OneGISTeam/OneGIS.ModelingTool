#ifndef OSGMANIPULATOR_SCALE2DDRAGGER
#define OSGMANIPULATOR_SCALE2DDRAGGER 1

#include <VBF_Display/VBF_Dragger/Dragger.h>
#include <VBF_Display/VBF_Dragger/Projector.h>

namespace osgManipulator {

/**
 * Dragger for performing 2D scaling.
 */
class OSGMANIPULATOR_EXPORT Scale2DDragger : public Dragger
{
    public:

        enum ScaleMode
        {
            SCALE_WITH_ORIGIN_AS_PIVOT = 0,
            SCALE_WITH_OPPOSITE_HANDLE_AS_PIVOT
        };

        Scale2DDragger(ScaleMode scaleMode=SCALE_WITH_ORIGIN_AS_PIVOT);

        META_OSGMANIPULATOR_Object(osgManipulator,Scale2DDragger)

        /**
         * Handle pick events on dragger and generate TranslateInLine commands.
         */
        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        /** Set/Get min scale for dragger. */
        inline void             setMinScale(const osg::Vec2d& min) { _minScale = min; }
        inline const osg::Vec2d& getMinScale() const               { return _minScale; }

        /** Set/Get the handle nodes for dragger. */
        inline void setTopLeftHandleNode (osg::IVBF_SGNode& node) { _topLeftHandleNode = &node; }
        inline osg::IVBF_SGNode* getTopLeftHandleNode() { return _topLeftHandleNode.get(); }
        inline const osg::IVBF_SGNode* getTopLeftHandleNode() const { return _topLeftHandleNode.get(); }
        inline void setBottomLeftHandleNode (osg::IVBF_SGNode& node) { _bottomLeftHandleNode = &node; }
        inline osg::IVBF_SGNode* getBottomLeftHandleNode() { return _bottomLeftHandleNode.get(); }
        inline const osg::IVBF_SGNode* getBottomLeftHandleNode() const { return _bottomLeftHandleNode.get(); }
        inline void setTopRightHandleNode(osg::IVBF_SGNode& node) { _topRightHandleNode = &node; }
        inline osg::IVBF_SGNode* getTopRightHandleNode() { return _topRightHandleNode.get(); }
        inline const osg::IVBF_SGNode* getTopRightHandleNode() const { return _topRightHandleNode.get(); }
        inline void setBottomRightHandleNode(osg::IVBF_SGNode& node) { _bottomRightHandleNode = &node; }
        inline osg::IVBF_SGNode* getBottomRightHandleNode() { return _bottomRightHandleNode.get(); }
        inline const osg::IVBF_SGNode* getBottomRightHandleNode() const { return _bottomRightHandleNode.get(); }

        /** Set/Get the handle nodes postion for dragger. */
        inline void setTopLeftHandlePosition(const osg::Vec2d& pos) { _topLeftHandlePosition = pos; }
        const osg::Vec2d& getTopLeftHandlePosition() const { return _topLeftHandlePosition; }
        inline void setBottomLeftHandlePosition(const osg::Vec2d& pos) { _bottomLeftHandlePosition = pos; }
        const osg::Vec2d& getBottomLeftHandlePosition() const { return _bottomLeftHandlePosition; }
        inline void setTopRightHandlePosition(const osg::Vec2d& pos) { _topRightHandlePosition = pos; }
        const osg::Vec2d& getTopRightHandlePosition() const { return _topRightHandlePosition; }
        inline void setBottomRightHandlePosition(const osg::Vec2d& pos){ _bottomRightHandlePosition = pos; }
        const osg::Vec2d& getBottomRightHandlePosition() const { return _bottomRightHandlePosition; }

    protected:

        virtual ~Scale2DDragger();

        ref_ptr< PlaneProjector >  _projector;
        osg::Vec3d                      _startProjectedPoint;
        osg::Vec2d                      _scaleCenter;
        osg::Vec2d                      _referencePoint;
        osg::Vec2d                      _minScale;

        ref_ptr< osg::IVBF_SGNode >       _topLeftHandleNode;
        ref_ptr< osg::IVBF_SGNode >       _bottomLeftHandleNode;
        ref_ptr< osg::IVBF_SGNode >       _topRightHandleNode;
        ref_ptr< osg::IVBF_SGNode >       _bottomRightHandleNode;

        osg::Vec2d                      _topLeftHandlePosition;
        osg::Vec2d                      _bottomLeftHandlePosition;
        osg::Vec2d                      _topRightHandlePosition;
        osg::Vec2d                      _bottomRightHandlePosition;

        ScaleMode                       _scaleMode;
};


}

#endif
