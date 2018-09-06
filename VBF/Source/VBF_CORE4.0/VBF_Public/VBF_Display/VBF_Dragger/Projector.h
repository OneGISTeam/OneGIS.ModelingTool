#ifndef OSGMANIPULATOR_PROJECTOR
#define OSGMANIPULATOR_PROJECTOR 1

#include <VBF_Display/VBF_Dragger/Export.h>

#include <VBF_Engine/VBF_SceneGraph/LineSegment>
#include <VBF_Engine/VBF_SGUtil/SceneView>

#include <VBF_Display/VBF_Dragger/Dragger.h>

namespace osgManipulator {

// 投影仪。把鼠标的二维运动映射到三维的运动（三维中的一部分） 
class OSGMANIPULATOR_EXPORT Projector : public ::CVBF_Referenced
{
    public:

        Projector();

        /**
         * Calculates the object/world coordinates (projectedPoint) of a window
         * coordinate (pointToProject) when projected onto some shape or 
         * geometry (implemented in derived classes). SceneView in used for i
         * projecting window coordinates into object coordinates and vice versa.
         * Returns true on successful projection.
         */
        virtual bool project(const PointerInfo& pi, osg::Vec3d& projectedPoint) const = 0;

        /**
         * Sets the matrix for transforming the projector's local coordinate
         * system to the world/object coordinate system.
         */
        void setLocalToWorld(const osg::Matrix& localToWorld)
        {
            _localToWorld = localToWorld;
            _worldToLocalDirty = true;
        }

        /**
         * Gets the matrix for transforming the projector's local coordinate
         * system to the world/object coordinate system.
         */
        inline const osg::Matrix& getLocalToWorld() const { return _localToWorld; }

        /**
         * Gets the matrix for transforming the world/object coordinate
         * system to the command's local coordinate system.
         */
        inline const osg::Matrix& getWorldToLocal() const 
        {
            if (_worldToLocalDirty)
            {
                _worldToLocal.invert(_localToWorld);
                _worldToLocalDirty = false;
            }
            return _worldToLocal;
        }

    protected:

        virtual ~Projector();

        osg::Matrix         _localToWorld;
        mutable osg::Matrix _worldToLocal;

        mutable bool        _worldToLocalDirty;
};


// 投影到线。把鼠标点投影到线（外部指定）上的最近点
class OSGMANIPULATOR_EXPORT LineProjector : public Projector
{
    public:

        LineProjector();

        LineProjector(const osg::LineSegment::vec_type& s, const osg::LineSegment::vec_type& e);

        inline void setLine(const osg::LineSegment::vec_type& s, const osg::LineSegment::vec_type& e) { _line->start() = s; _line->end() = e; }

        inline const osg::LineSegment::vec_type& getLineStart() const { return _line->start(); }
        inline osg::LineSegment::vec_type& getLineStart() { return _line->start(); }

        inline const osg::LineSegment::vec_type& getLineEnd() const { return _line->end(); }
        inline osg::LineSegment::vec_type& getLineEnd() { return _line->end(); }

        /**
         * Calculates the object coordinates (projectedPoint) of a window 
         * coordinate (pointToProject) when projected onto the given line. 
         * Returns true on successful projection.
         */
        virtual bool project(const PointerInfo& pi, osg::Vec3d& projectedPoint) const;

    protected:

        virtual ~LineProjector();

        ref_ptr<osg::LineSegment> _line;
};


// 投影到面。把鼠标点投影到面（外部指定）上的最近点
class OSGMANIPULATOR_EXPORT PlaneProjector : public Projector
{
    public:
        PlaneProjector();
        PlaneProjector(const osg::Plane& plane);

        inline void setPlane(const osg::Plane& plane) { _plane = plane; }
        inline const osg::Plane& getPlane() const { return _plane; }

        /**
         * Calculates the object coordinates (projectedPoint) of a window 
         * coordinate (pointToProject) when projected onto the given plane. 
         * Returns true on successful projection.
         */
        virtual bool project(const PointerInfo& pi, osg::Vec3d& projectedPoint) const;

    protected:

        virtual ~PlaneProjector();

        osg::Plane _plane;
};

/**
 * SphereProjector projects points onto the given sphere.
 */
class OSGMANIPULATOR_EXPORT SphereProjector : public Projector
{
    public:

        SphereProjector();

        SphereProjector(osg::Sphere* sphere);

        inline void setSphere(osg::Sphere* sphere) { _sphere = sphere; }
        inline const osg::Sphere* getSphere() const { return _sphere.get(); }

        /**
         * Calculates the object coordinates (projectedPoint) of a window 
         * coordinate (pointToProject) when projected onto the given sphere. 
         * Returns true on successful projection.
         */
        virtual bool project(const PointerInfo& pi, osg::Vec3d& projectedPoint) const;

        /**
         * Returns true is the point is in front of the cylinder given the eye
         * direction.
         */
        bool isPointInFront(const PointerInfo& pi, const osg::Matrix& localToWorld) const;

        void setFront(bool front) { _front = front; }

    protected:

        virtual ~SphereProjector();

        ref_ptr<osg::Sphere> _sphere;
        bool                      _front;
};

/**
 * SpherePlaneProjector projects points onto a sphere, failing which it project
 * onto a plane oriented to the viewing direction.
 */
class OSGMANIPULATOR_EXPORT SpherePlaneProjector : public SphereProjector
{
    public:

        SpherePlaneProjector();

        SpherePlaneProjector(osg::Sphere* sphere);

        /**
         * Calculates the object coordinates (projectedPoint) of a window 
         * coordinate (pointToProject) when projected onto the given sphere. 
         * Returns true on successful projection.
         */
        virtual bool project(const PointerInfo& pi, osg::Vec3d& projectedPoint) const;

        /**
         * Returns true if the previous projection was on the sphere and false 
         * if the projection was on the plane.
         */
        bool isProjectionOnSphere() const { return _onSphere; }

        osg::Quat getRotation(const osg::Vec3d& p1, bool p1OnSphere, 
                              const osg::Vec3d& p2, bool p2OnSphere,
                              float radialFactor = 0.0f) const;

    protected:

        virtual ~SpherePlaneProjector();

        mutable osg::Plane _plane;
        mutable bool       _onSphere;
};

/**
 * CylinderProjector projects points onto the given cylinder.
 */
class OSGMANIPULATOR_EXPORT CylinderProjector : public Projector
{
    public:

        CylinderProjector();

        CylinderProjector(osg::Cylinder* cylinder);

        inline void setCylinder(osg::Cylinder* cylinder)
        {
            _cylinder = cylinder;
            _cylinderAxis = osg::Vec3d(0.0,0.0,1.0) * osg::Matrix(cylinder->getRotation());
            _cylinderAxis.normalize();
        }
        inline const osg::Cylinder* getCylinder() const { return _cylinder.get(); }

        /**
         * Calculates the object coordinates (projectedPoint) of a window 
         * coordinate (pointToProject) when projected onto the given plane. 
         * Returns true on successful projection.
         */
        virtual bool project(const PointerInfo& pi, osg::Vec3d& projectedPoint) const;

        
        /**
         * Returns true is the point is in front of the cylinder given the eye 
         * direction.
         */
        bool isPointInFront(const PointerInfo& pi, const osg::Matrix& localToWorld) const;

        void setFront(bool front) { _front = front; }

    protected:

        virtual ~CylinderProjector();

        ref_ptr<osg::Cylinder> _cylinder;
        osg::Vec3d                  _cylinderAxis;
        bool                        _front;
};

/**
 * CylinderPlaneProjector projects points onto the given cylinder.
 */
class OSGMANIPULATOR_EXPORT CylinderPlaneProjector : public CylinderProjector
{
    public:

        CylinderPlaneProjector();

        CylinderPlaneProjector(osg::Cylinder* cylinder);

        /**
         * Calculates the object coordinates (projectedPoint) of a window 
         * coordinate (pointToProject) when projected onto the given plane. 
         * Returns true on successful projection.
         */
        virtual bool project(const PointerInfo& pi, osg::Vec3d& projectedPoint) const;

        /**
         * Returns true if the previous projection was on the cylinder and 
         * false if the projection was on the plane.
         */
        bool isProjectionOnCylinder() const { return _onCylinder; }

        osg::Quat getRotation(const osg::Vec3d& p1, bool p1OnCyl, const osg::Vec3d& p2, bool p2OnCyl) const;

    protected:

        virtual ~CylinderPlaneProjector();

        mutable osg::Plane _plane;
        mutable bool       _onCylinder;
        mutable osg::Vec3d _planeLineStart, _planeLineEnd;
};

}

#endif
