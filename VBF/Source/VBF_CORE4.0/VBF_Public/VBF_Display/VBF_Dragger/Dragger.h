#ifndef OSGMANIPULATOR_DRAGGER
#define OSGMANIPULATOR_DRAGGER 1

#include <VBF_Display/VBF_Dragger/Constraint.h>
#include <VBF_Display/VBF_Dragger/Command.h>

#include <Types/VBF_BoundingSphere.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGNodeGroupTransformMatrix.h>
#include <VBF_Engine/VBF_SGUtil/SceneView>
#include <VBF_Engine/VBF_SGUtil/IntersectVisitor>
#include <VBF_Display/VBF_Manipulator/VBF_GUIEventAdapter.h>
#include <VBF_Display/VBF_Manipulator/IVBF_GUIActionAdapter.h>
#include <VBF_Display/VBF_Viewer/VBF_GraphicsWindow.h>


namespace osgManipulator
{

class CompositeDragger;
class MotionCommand;
class TranslateInLineCommand;
class TranslateInPlaneCommand;
class Scale1DCommand;
class Scale2DCommand;
class ScaleUniformCommand;
class Rotate3DCommand;

/** Computes the nodepath from the given node all the way upto the root. */
extern OSGMANIPULATOR_EXPORT void computeNodePathToRoot(osg::IVBF_SGNode& node, osg::CVBF_SGNodePath& np);

class DraggerCallback : virtual public osg::CVBF_Object
{
    public:
        DraggerCallback(): osg::CVBF_Object(true) {}

        DraggerCallback(const DraggerCallback&, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY):
            osg::CVBF_Object(true) {}

        META_Object(osgManipulator, DraggerCallback);

		// 接收并处理命令，如果成功返回true
        virtual bool receive(const MotionCommand&) { return false; }
        virtual bool receive(const TranslateInLineCommand& command)  { return receive((MotionCommand&)command); }
        virtual bool receive(const TranslateInPlaneCommand& command) { return receive((MotionCommand&)command); }
        virtual bool receive(const Scale1DCommand& command)          { return receive((MotionCommand&)command); }
        virtual bool receive(const Scale2DCommand& command)          { return receive((MotionCommand&)command); }
        virtual bool receive(const ScaleUniformCommand& command)     { return receive((MotionCommand&)command); }
        virtual bool receive(const Rotate3DCommand& command)         { return receive((MotionCommand&)command); }
};

class OSGMANIPULATOR_EXPORT DraggerTransformCallback : public DraggerCallback
{
    public:

        DraggerTransformCallback(osg::IVBF_SGNodeGroupTransformMatrix* transform);

        virtual bool receive(const MotionCommand&);

        osg::IVBF_SGNodeGroupTransformMatrix* getTransform() { return _transform.get(); }
        const osg::IVBF_SGNodeGroupTransformMatrix* getTransform() const { return _transform.get(); }

    protected:

        observer_ptr<osg::IVBF_SGNodeGroupTransformMatrix> _transform;
        osg::Matrix _startMotionMatrix;

        osg::Matrix _localToWorld;
        osg::Matrix _worldToLocal;
};


class OSGMANIPULATOR_EXPORT PointerInfo
{
public:
    PointerInfo();
    PointerInfo(const PointerInfo& rhs):
        _hitList(rhs._hitList),
        _nearPoint(rhs._nearPoint),
        _farPoint(rhs._farPoint),
        _eyeDir(rhs._eyeDir)
    {
        _hitIter = _hitList.begin();
    }

    void reset()
    {
        _hitList.clear();
        _hitIter = _hitList.begin();
        setCamera(0);
    }

    bool completed() const { return _hitIter==_hitList.end(); }

    void next()
    {
        if (!completed()) ++_hitIter;
    }

    typedef std::pair<osg::CVBF_SGNodePath, osg::Vec3d> NodePathIntersectionPair;
    typedef std::list< NodePathIntersectionPair> IntersectionList;

    osg::Vec3d getLocalIntersectPoint() const { return _hitIter->second; }

    void setNearFarPoints (osg::Vec3d nearPoint, osg::Vec3d farPoint)
    {
        _nearPoint = nearPoint;
        _farPoint=farPoint;
        _eyeDir = farPoint - nearPoint;
    }

    const osg::Vec3d& getEyeDir() const {return _eyeDir;}

    void getNearFarPoints( osg::Vec3d& nearPoint, osg::Vec3d& farPoint) const
    {
        nearPoint = _nearPoint;
        farPoint = _farPoint;
    }

    bool contains(const osg::IVBF_SGNode* node) const;
    bool containsMulti(const osg::IVBF_SGNode* node) const;

    void setCamera(osg::IVBF_Camera* camera)
    {
        if (camera)
        {
            _MVPW = camera->getViewMatrix() * camera->getProjectionMatrix();
            if (camera->getViewport()) _MVPW.postMult(camera->getViewport()->computeWindowMatrix());
            _inverseMVPW.invert(_MVPW);
            osg::Vec3d eye, center, up;
            camera->getViewMatrix().getLookAt(eye, center, up);
            _eyeDir = eye - center;

        }
        else
        {
            _MVPW.makeIdentity();
            _inverseMVPW.makeIdentity();
            _eyeDir = osg::Vec3d(0,0,1);
        }

    }

    void addIntersection(const osg::CVBF_SGNodePath& nodePath, const osg::Vec3d& intersectionPoint)
    {
        bool needToResetHitIter = _hitList.empty();
        _hitList.push_back(NodePathIntersectionPair(nodePath, intersectionPoint));
        if (needToResetHitIter) _hitIter = _hitList.begin();
    }

    void setMousePosition(float pixel_x, float pixel_y)
    {
        projectWindowXYIntoObject(osg::Vec2d(pixel_x, pixel_y), _nearPoint, _farPoint);
    }

protected:
    bool projectWindowXYIntoObject(const osg::Vec2d& windowCoord, osg::Vec3d& nearPoint, osg::Vec3d& farPoint) const;

public:
    IntersectionList _hitList;
    IntersectionList::const_iterator _hitIter;

protected:

    osg::Vec3d _nearPoint,_farPoint;
    osg::Vec3d _eyeDir;

    osg::Matrix _MVPW;
    osg::Matrix _inverseMVPW;
};


// 拖放器的基类，实现选取并生成motion命令（移动、旋转、缩放等）
class OSGMANIPULATOR_EXPORT Dragger : public osg::MatrixTransform
{
    public:
        META_Node(osgManipulator,Dragger)

        // 设置/获取父拖放器
        virtual void setParentDragger(Dragger* parent) { _parentDragger = parent; }
        Dragger* getParentDragger() { return _parentDragger; }
        const Dragger* getParentDragger() const { return _parentDragger; }

        // 如果该拖放器不是CompositeDragger，返回0
        virtual const CompositeDragger* getComposite() const { return 0; }
        virtual CompositeDragger* getComposite() { return 0; }


        void setHandleEvents(bool flag);
        bool getHandleEvents() const { return _handleEvents; }

        void setActivationModKeyMask(unsigned int mask) { _activationModKeyMask = mask; }
        unsigned int getActivationModKeyMask() const { return _activationModKeyMask; }

        void setActivationKeyEvent(int key) { _activationKeyEvent = key; }
        int getActivationKeyEvent() const { return _activationKeyEvent; }


        virtual void traverse(osg::NodeVisitor& nv);

        virtual bool handle(const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);
        virtual bool handle(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);


        typedef std::vector< ref_ptr<Constraint> > Constraints;

        void addConstraint(Constraint* constraint);
        void removeConstraint(Constraint* constraint);

        Constraints& getConstraints() { return _constraints; }
        const Constraints& getConstraints() const { return _constraints; }


        typedef std::vector< ref_ptr<DraggerCallback> > DraggerCallbacks;

        void addDraggerCallback(DraggerCallback* dc);
        void removeDraggerCallback(DraggerCallback* dc);

        DraggerCallbacks& getDraggerCallbacks() { return _draggerCallbacks; }
        const DraggerCallbacks& getDraggerCallbacks() const { return _draggerCallbacks; }

        void addTransformUpdating(IVBF_SGNodeGroupTransformMatrix* transform);
        void removeTransformUpdating(IVBF_SGNodeGroupTransformMatrix* transform);

        // 设置拖放器默认的几何形状
        virtual void setupDefaultGeometry() {}

        virtual bool receive(const MotionCommand& command);
        void dispatch(MotionCommand& command);

        void setDraggerActive(bool active) { _draggerActive = active; }
        bool getDraggerActive() const { return _draggerActive; }

        // 设置/获取Dragger被拣选时的光标形状
        void SetPickCursor(osgViewer::GraphicsWindow::MouseCursor nCursor) { m_nCursorPick = nCursor; }
        osgViewer::GraphicsWindow::MouseCursor GetPickCursor()  { return m_nCursorPick; }

        // 设置/获取颜色
        virtual void setColor(const osg::Vec4& color);
        virtual const osg::Vec4& getColor() const { return _color; }

        // 设置/获取选中时的颜色
        virtual void setPickColor(const osg::Vec4& color) { _pickColor = color; }
        virtual const osg::Vec4& getPickColor() const { return _pickColor; }

        // 响应鼠标进入/离开该Dragger事件，只要求单一型Dragger重载该函数（杜莹添加：2014-12-29）
        virtual void OnEnter(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa) {}
        virtual void OnLeave(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa) {}
    protected:

        Dragger();
        Dragger(const Dragger& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        virtual ~Dragger();


        bool                            _handleEvents;
        bool                            _draggerActive;

        unsigned int                    _activationModKeyMask;
        int                             _activationKeyEvent;
        bool                            _activationPermittedByModKeyMask;
        bool                            _activationPermittedByKeyEvent;

        osgManipulator::PointerInfo     _pointer;

        Dragger*                        _parentDragger;

        ref_ptr<DraggerCallback>        _selfUpdater;
        Constraints                     _constraints;
        DraggerCallbacks                _draggerCallbacks;

        osg::Vec4                       _color;		// 颜色
        osg::Vec4                       _pickColor;	// 选中时的颜色

        // Dragger被拣选时的光标形状
        osgViewer::GraphicsWindow::MouseCursor	m_nCursorPick;
};


/**
 * CompositeDragger allows to create complex draggers that are composed of a
 * hierarchy of Draggers.
 */
class OSGMANIPULATOR_EXPORT CompositeDragger : public Dragger
{
    public:

        META_Node(osgManipulator,CompositeDragger)

        typedef std::vector< ref_ptr<Dragger> > DraggerList;

        virtual const CompositeDragger* getComposite() const { return this; }
        virtual CompositeDragger* getComposite() { return this; }

        virtual void setParentDragger(Dragger* parent);

        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, ::IVBF_GUIActionAdapter& aa);

        // Composite-specific methods below
        virtual bool addDragger(Dragger* dragger);
        virtual bool removeDragger(Dragger* dragger);
        unsigned int getNumDraggers() const { return _draggerList.size(); }
        Dragger* getDragger(unsigned int i) { return _draggerList[i].get(); }
        const Dragger* getDragger(unsigned int i) const { return _draggerList[i].get(); }
        bool containsDragger(const Dragger* dragger) const;
        DraggerList::iterator findDragger(const Dragger* dragger);

    protected:

        CompositeDragger() {}
        CompositeDragger(const CompositeDragger& rhs, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        virtual ~CompositeDragger() {}

        DraggerList _draggerList;
};

/**
 * Culls the drawable all the time. Used by draggers to have invisible geometry
 * around lines and points so that they can be picked. For example, a dragger
 * could have a line with an invisible cylinder around it to enable picking on
 * that line.
 */
void OSGMANIPULATOR_EXPORT setDrawableToAlwaysCull(osg::Drawable& drawable);

/**
 * Convenience function for setting the material color on a node.
 */
void OSGMANIPULATOR_EXPORT setMaterialColor(const osg::Vec4& color, osg::IVBF_SGNode& node);

}

#endif
