#ifndef OSGEARTH_BOUNDS_H
#define OSGEARTH_BOUNDS_H 1

#include <VBF_3DMap/VBF_Terrain/Common.h>
#include <Types/VBF_BoundingBox.h>

class CVBF_SpatialReference;

namespace osgEarth
{  
    // 一个无名的包围盒（如，没有空间参考信息）
    class OSGEARTH_EXPORT Bounds : public osg::BoundingBoxImpl<osg::Vec3d>
    {
    public:
        Bounds();
        Bounds(double xmin, double ymin, double xmax, double ymax );
        Bounds& operator = (const Bounds& rhs);
        virtual ~Bounds();

        double width() const;
        double height() const;
        double depth() const;
        bool contains(double x, double y ) const;
        bool contains(const Bounds& rhs) const;
        Bounds unionWith(const Bounds& rhs) const; 
        Bounds intersectionWith(const Bounds& rhs) const;
        void expandBy( double x, double y );
        void expandBy( double x, double y, double z );
        void expandBy( const Bounds& rhs );
        osg::Vec2d center2d() const;
        double radius2d() const;
        double area2d() const;
        std::string VBF_toString() const;
        bool isValid() const;
        bool isEmpty() const { return !isValid(); }
        void transform( const CVBF_SpatialReference* fromSRS, const CVBF_SpatialReference* toSRS );
    };
}

#endif // OSGEARTH_BOUNDS_H
