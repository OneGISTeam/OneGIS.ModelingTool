#ifndef OSGMANIPULATOR_CONSTRAINT
#define OSGMANIPULATOR_CONSTRAINT 1

#include <VBF_Display/VBF_Dragger/Export.h>

#include <VBF_Base/observer_ptr>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <Types/VBF_Matrix.h>

namespace osgManipulator {

class MotionCommand;
class TranslateInLineCommand;
class TranslateInPlaneCommand;
class Scale1DCommand;
class Scale2DCommand;
class ScaleUniformCommand;

// 约束：命令执行的约束条件
class OSGMANIPULATOR_EXPORT Constraint : public ::CVBF_Referenced
{
    public:

        virtual bool constrain(MotionCommand&) const                   { return false; }
        virtual bool constrain(TranslateInLineCommand& command) const  { return constrain((MotionCommand&)command); }
        virtual bool constrain(TranslateInPlaneCommand& command) const { return constrain((MotionCommand&)command); }
        virtual bool constrain(Scale1DCommand& command) const          { return constrain((MotionCommand&)command); }
        virtual bool constrain(Scale2DCommand& command) const          { return constrain((MotionCommand&)command); }
        virtual bool constrain(ScaleUniformCommand& command) const     { return constrain((MotionCommand&)command); }

    protected:

        Constraint(osg::IVBF_SGNode& refNode) : _refNode(&refNode) {}
        virtual ~Constraint() {}

        osg::IVBF_SGNode&       getReferenceNode()       { return *_refNode; }
        const osg::IVBF_SGNode& getReferenceNode() const { return *_refNode; }

        const osg::Matrix& getLocalToWorld() const { return _localToWorld; }
        const osg::Matrix& getWorldToLocal() const { return _worldToLocal; }

        void computeLocalToWorldAndWorldToLocal() const;

    private:

        observer_ptr<osg::IVBF_SGNode> _refNode;
        mutable osg::Matrix     _localToWorld;
        mutable osg::Matrix     _worldToLocal;
};

/**
 * Constraint to snap motion commands to a sugar cube grid.
 */
class OSGMANIPULATOR_EXPORT GridConstraint : public Constraint
{
    public:

        GridConstraint(osg::IVBF_SGNode& refNode, const osg::Vec3d& origin, const osg::Vec3d& spacing);

        void setOrigin(const osg::Vec3d& origin)   { _origin = origin; }
        const osg::Vec3d& getOrigin() const  { return _origin; }

        void setSpacing(const osg::Vec3d& spacing) { _spacing = spacing; }
        const osg::Vec3d& getSpacing() const { return _spacing; }

        virtual bool constrain(TranslateInLineCommand& command) const;
        virtual bool constrain(TranslateInPlaneCommand& command) const;
        virtual bool constrain(Scale1DCommand& command) const;
        virtual bool constrain(Scale2DCommand& command) const;
        virtual bool constrain(ScaleUniformCommand& command) const;

    protected:

        virtual ~GridConstraint() {}

    private:

        osg::Vec3d _origin;
        osg::Vec3d _spacing;
        mutable osg::Matrix     _startMatrix;
        mutable osg::Matrix     _matrix;
};

}

#endif
