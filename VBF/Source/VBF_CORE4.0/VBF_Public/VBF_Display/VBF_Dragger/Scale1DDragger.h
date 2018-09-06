#ifndef OSGMANIPULATOR_SCALE1DDRAGGER
#define OSGMANIPULATOR_SCALE1DDRAGGER 1

#include <VBF_Display/VBF_Dragger/Dragger.h>
#include <VBF_Display/VBF_Dragger/Projector.h>

namespace osgManipulator {


// 1维缩放，即沿一个轴缩放
class OSGMANIPULATOR_EXPORT Scale1DDragger : public Dragger
{
    public:

        enum ScaleMode
        {
            SCALE_WITH_ORIGIN_AS_PIVOT = 0,
            SCALE_WITH_OPPOSITE_HANDLE_AS_PIVOT
        };

        Scale1DDragger(ScaleMode scaleMode=SCALE_WITH_ORIGIN_AS_PIVOT);

        META_OSGMANIPULATOR_Object(osgManipulator,Scale1DDragger)

		// 处理选择（pick）事件，并生成Scale1DCommand命令
        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& us);

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

		// 设置/获取最小缩放比
        inline void   setMinScale(double min) { _minScale = min; }
        inline double getMinScale() const    { return _minScale; }

        /** Set/Get left and right handle nodes for dragger. */
        inline void setLeftHandleNode (osg::IVBF_SGNode& node) { _leftHandleNode = &node; }
        inline void setRightHandleNode(osg::IVBF_SGNode& node) { _rightHandleNode = &node; }
        inline osg::IVBF_SGNode* getLeftHandleNode()  { return _leftHandleNode.get(); }
        inline const osg::IVBF_SGNode* getLeftHandleNode() const  { return _leftHandleNode.get(); }
        inline osg::IVBF_SGNode* getRightHandleNode() { return _rightHandleNode.get(); }
        inline const osg::IVBF_SGNode* getRightHandleNode() const { return _rightHandleNode.get(); }

        /** Set left/right handle position. */
        inline void  setLeftHandlePosition(double pos)  { _projector->getLineStart() = osg::Vec3d(pos,0.0,0.0); }
        inline double getLeftHandlePosition() const     { return _projector->getLineStart()[0]; }
        inline void  setRightHandlePosition(double pos) { _projector->getLineEnd() = osg::Vec3d(pos,0.0,0.0); }
        inline double getRightHandlePosition() const    { return _projector->getLineEnd()[0]; }

    protected:

        virtual ~Scale1DDragger();

        ref_ptr< LineProjector >		_projector;
        osg::Vec3d                      _startProjectedPoint;
        double                          _scaleCenter;
        double                          _minScale;

        ref_ptr< osg::IVBF_SGNode >       _leftHandleNode;
        ref_ptr< osg::IVBF_SGNode >       _rightHandleNode;

        ScaleMode                       _scaleMode;
};


}

#endif
