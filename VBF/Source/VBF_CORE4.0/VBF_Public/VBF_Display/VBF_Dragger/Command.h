#ifndef OSGMANIPULATOR_COMMAND
#define OSGMANIPULATOR_COMMAND 1

#include <VBF_Base/ref_ptr>
#include <VBF_Display/VBF_Dragger/Export.h>

#include <VBF_Engine/VBF_SceneGraph/LineSegment>
#include <Types/VBF_Plane.h>
#include <Types/Vec2>

#include <vector>

namespace osgManipulator {

class Constraint;
class Dragger;  // ��Ө��ӣ�2013-09-16

// ���ģʽ�е�����ĸ��һ��������������Ҫ��ִ�е�Ԫ�������ߣ�Receiver����ִ������ı������״̬��
//  	�����ߣ�Invoker�����������������������������Command����

class OSGMANIPULATOR_EXPORT MotionCommand : public ::CVBF_Referenced
{
    public:

        /**
         * Motion command are based on click-drag-release actions. So each
         * command needs to indicate which stage of the motion the command
         * represents.
         */
        enum Stage
        {
            NONE,
            /** Click or pick start. */
            START,  
            /** Drag or pick move. */
            MOVE,
            /** Release or pick finish. */
            FINISH
        };

        MotionCommand();

        /** create a MotionCommand that is the inverse of this command, and if applied will undo this commands changes. */
        virtual MotionCommand* createCommandInverse() = 0;

        /**
         * Gets the matrix for transforming the object being dragged. This matrix is in the
         * command's coordinate systems. 
         */
        virtual osg::Matrix getMotionMatrix() const = 0;

        /**
         * Sets the matrix for transforming the command's local coordinate
         * system to the world/object coordinate system.
         */
        void setLocalToWorldAndWorldToLocal(const osg::Matrix& localToWorld, const osg::Matrix& worldToLocal)
        {
            _localToWorld = localToWorld;
            _worldToLocal = worldToLocal;
        }

        /**
         * Gets the matrix for transforming the command's local coordinate
         * system to the world/object coordinate system.
         */
        inline const osg::Matrix& getLocalToWorld() const { return _localToWorld; }

        /**
         * Gets the matrix for transforming the command's world/object
         * coordinate system to the command's local coordinate system. 
         */
        inline const osg::Matrix& getWorldToLocal() const { return _worldToLocal; }

        void setStage(const Stage s) { _stage = s; }
        Stage getStage() const { return _stage; }

		// ����/��ȡ���Ͷ�����Ϣ��Dragger������ǰ�����϶���Dragger����Ө��ӣ�2013-09-11��
		void SetSender(osgManipulator::Dragger* pSender) { m_pSender = pSender; }
		osgManipulator::Dragger* GetSender() { return m_pSender; }

    protected:

        virtual ~MotionCommand();
        
    private:
        osg::Matrix     _localToWorld;
        osg::Matrix     _worldToLocal;

        Stage           _stage;

		// ��¼���Ͷ�����Ϣ��Dragger������ǰ�����϶���Dragger����Ө��ӣ�2013-09-11��
		// ע�⣺�˴�ʹ��observer_ptr�ᵼ���໥���������벻ͨ��
		osgManipulator::Dragger* m_pSender;
};


/**
 * Command for translating in a line.
 */
class OSGMANIPULATOR_EXPORT TranslateInLineCommand : public MotionCommand
{
    public:

        TranslateInLineCommand();

        TranslateInLineCommand(const osg::LineSegment::vec_type& s, const osg::LineSegment::vec_type& e);

        virtual MotionCommand* createCommandInverse();

        inline void setLine(const osg::LineSegment::vec_type& s, const osg::LineSegment::vec_type& e) { _line->start() = s; _line->end() = e; }
        inline const osg::LineSegment::vec_type& getLineStart() const { return _line->start(); }
        inline const osg::LineSegment::vec_type& getLineEnd() const { return _line->end(); }

        inline void setTranslation(const osg::Vec3& t) { _translation = t; }
        inline const osg::Vec3d& getTranslation() const { return _translation; }

        virtual osg::Matrix getMotionMatrix() const 
        {
            return osg::Matrix::translate(_translation);
        }

    protected:

        virtual ~TranslateInLineCommand();

    private:
        ref_ptr<osg::LineSegment>  _line;
        osg::Vec3d                      _translation;
};

/**
 * Command for translating in a plane.
 */
class OSGMANIPULATOR_EXPORT TranslateInPlaneCommand : public MotionCommand
{
    public:

        TranslateInPlaneCommand();

        TranslateInPlaneCommand(const osg::Plane& plane);

        virtual MotionCommand* createCommandInverse();

        inline void setPlane(const osg::Plane& plane) { _plane = plane; }
        inline const osg::Plane& getPlane() const { return _plane; }

        inline void setTranslation(const osg::Vec3d& t) { _translation = t; }
        inline const osg::Vec3d& getTranslation() const { return _translation; }

        /** ReferencePoint is used only for snapping. */
        inline void setReferencePoint(const osg::Vec3d& rp) { _referencePoint = rp; }
        inline const osg::Vec3d& getReferencePoint() const { return _referencePoint; }

        virtual osg::Matrix getMotionMatrix() const 
        {
            return osg::Matrix::translate(_translation);
        }

    protected:

        virtual ~TranslateInPlaneCommand();

    private:
        osg::Plane _plane;
        osg::Vec3d _translation;
        osg::Vec3d _referencePoint;
};

/**
 * Command for 1D scaling.
 */
class OSGMANIPULATOR_EXPORT Scale1DCommand : public MotionCommand
{
    public:

        Scale1DCommand();

        virtual MotionCommand* createCommandInverse();

        inline void setScale(double s) { _scale = s; }
        inline double getScale() const { return _scale; }

        inline void  setScaleCenter(double center) { _scaleCenter = center; }
        inline double getScaleCenter() const       { return _scaleCenter; }

        /** ReferencePoint is used only for snapping. */
        inline void  setReferencePoint(double rp) { _referencePoint = rp; }
        inline double getReferencePoint() const   { return _referencePoint; }

        inline void  setMinScale(double min) { _minScale = min; }
        inline double getMinScale() const    { return _minScale; }

        virtual osg::Matrix getMotionMatrix() const 
        {
            return (osg::Matrix::translate(-_scaleCenter,0.0,0.0)
                    * osg::Matrix::scale(_scale,1.0,1.0)
                    * osg::Matrix::translate(_scaleCenter,0.0,0.0));
        }

    protected:

        virtual ~Scale1DCommand();

    private:
        double     _scale;
        double     _scaleCenter;
        double     _referencePoint;
        double     _minScale;
};

/**
 * Command for 2D scaling.
 */
class OSGMANIPULATOR_EXPORT Scale2DCommand : public MotionCommand
{
    public:

        Scale2DCommand();

        virtual MotionCommand* createCommandInverse();

        inline void setScale(const osg::Vec2d& s) { _scale = s; }
        inline const osg::Vec2d& getScale() const { return _scale; }

        inline void setScaleCenter(const osg::Vec2d& center) { _scaleCenter = center; }
        inline const osg::Vec2d& getScaleCenter() const { return _scaleCenter; }

        /** ReferencePoint is used only for snapping. */
        inline void  setReferencePoint(const osg::Vec2d& rp) { _referencePoint = rp; }
        inline const osg::Vec2d& getReferencePoint() const   { return _referencePoint; }

        inline void             setMinScale(const osg::Vec2d& min) { _minScale = min; }
        inline const osg::Vec2d& getMinScale() const               { return _minScale; }

        virtual osg::Matrix getMotionMatrix() const 
        {
            return (osg::Matrix::translate(-_scaleCenter[0],0.0,-_scaleCenter[1])
                    * osg::Matrix::scale(_scale[0],1.0,_scale[1])
                    * osg::Matrix::translate(_scaleCenter[0],0.0,_scaleCenter[1]));
        }

    protected:

        virtual ~Scale2DCommand();

    private:
        osg::Vec2d   _scale;
        osg::Vec2d   _scaleCenter;
        osg::Vec2d   _referencePoint;
        osg::Vec2d   _minScale;
};

/**
 * Command for uniform 3D scaling.
 */
class OSGMANIPULATOR_EXPORT ScaleUniformCommand : public MotionCommand
{
    public:

        ScaleUniformCommand();

        virtual MotionCommand* createCommandInverse();

        inline void setScale(double s) { _scale = s; }
        inline double getScale() const { return _scale; }

        inline void setScaleCenter(const osg::Vec3d& center) { _scaleCenter = center; }
        inline const osg::Vec3d& getScaleCenter() const { return _scaleCenter; }

        virtual osg::Matrix getMotionMatrix() const 
        {
            return (osg::Matrix::translate(-_scaleCenter) 
                    * osg::Matrix::scale(_scale,_scale,_scale)
                    * osg::Matrix::translate(_scaleCenter));
        }

    protected:

        virtual ~ScaleUniformCommand();

    private:
        double     _scale;
        osg::Vec3d _scaleCenter;
};

/**
 * Command for rotation in 3D.
 */
class OSGMANIPULATOR_EXPORT Rotate3DCommand : public MotionCommand
{
    public:

        Rotate3DCommand();

        virtual MotionCommand* createCommandInverse();

        inline void setRotation(const osg::Quat& rotation) { _rotation = rotation; }
        inline const osg::Quat& getRotation() const { return _rotation; }

        virtual osg::Matrix getMotionMatrix() const 
        {
            return osg::Matrix::rotate(_rotation);
        }

    protected:

        virtual ~Rotate3DCommand();

    private:
        osg::Quat _rotation;
};


}

#endif
