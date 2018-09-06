#ifndef __VBF_STO_GEOMETRY_H__
#define __VBF_STO_GEOMETRY_H__ 1

#include <VBF_Common/VBF_STObject/VBF_Export.h>
#include <VBF_Common/VBF_Utils/VBF_STLContainers.h>
#include <vector>
#include <stack>
#include <string>
#include <Types/VBF_BoundingBox.h>
#include <VBF_Base/VBF_Referenced.h>
#include <VBF_Base/ref_ptr>

class CVBF_Bounds : public osg::BoundingBoxImpl<osg::Vec3d>
{
public:
    CVBF_Bounds();
    CVBF_Bounds(double xmin, double ymin, double xmax, double ymax );
    CVBF_Bounds& operator = (const CVBF_Bounds& rhs);
    virtual ~CVBF_Bounds();

    double width() const;
    double height() const;
    double depth() const;
    bool contains(double x, double y ) const;
    bool contains(const CVBF_Bounds& rhs) const;
    CVBF_Bounds unionWith(const CVBF_Bounds& rhs) const;
    CVBF_Bounds intersectionWith(const CVBF_Bounds& rhs) const;
    void expandBy( double x, double y );
    void expandBy( double x, double y, double z );
    void expandBy( const CVBF_Bounds& rhs );
    osg::Vec2d center2d() const;
    double radius2d() const;
    double area2d() const;
    std::string VBF_toString() const;
    bool isValid() const;
    bool isEmpty() const { return !isValid(); }
 //   void transform( const CVBF_SpatialReference* fromSRS, const CVBF_SpatialReference* toSRS );
};

typedef std::vector<osg::Vec3d> VBFVec3dVector;


// CVBF_Geometry对象的基类
class VBF_STOBJECT_EXPORT CVBF_Geometry : public CVBF_VectorMixin2<osg::Vec3d,CVBF_Referenced>
{
public:
    CVBF_Geometry( int capacity =0 );
    CVBF_Geometry( const CVBF_Geometry& rhs );
    CVBF_Geometry( const VBFVec3dVector* toCopy );

   virtual ~CVBF_Geometry();

public:
    enum Type
    {
        TYPE_UNKNOWN,
        TYPE_POINTSET,
        TYPE_LINESTRING,
        TYPE_RING,
        TYPE_POLYGON,
        TYPE_MULTI
    };

    enum Orientation
    {
        ORIENTATION_CCW,
        ORIENTATION_CW,
        ORIENTATION_DEGENERATE
    };

    static std::string VBF_toString( Type t )
    {
        return
            t == TYPE_POINTSET ?   "pointset" :
            t == TYPE_LINESTRING ? "linestring" :
            t == TYPE_RING ?       "ring" :
            t == TYPE_POLYGON ?    "polygon" :
            t == TYPE_MULTI ?      "multi" :
            "unknown";
    }

    // 从vector数组创建
    static CVBF_Geometry* create( Type type, const VBFVec3dVector* toCopy );


public:
    // 获取总的点数
    virtual int getTotalPointCount() const;

    // 获取部件的总数
    virtual unsigned getNumComponents() const { return 1; }

    // 获取几何体的总数，是所有组成的所有部分的总数，也可被看做是full CVBF_GeometryIterator返回的几何对象的数量
    virtual unsigned getNumGeometries() const { return 1; }

    // 把此Geometry转换为另一种类型，如果类型相同则会返回"this"，如果不能转换则返回NULL
    virtual CVBF_Geometry* cloneAs( const CVBF_Geometry::Type& newType ) const;


//    osg::Vec3Array* toVec3Array() const;
//    osg::Vec3dArray* toVec3dArray() const;

    virtual CVBF_Bounds getBounds() const;

    // 几何对象是否为线
    bool isLinear() const { return getComponentType() == TYPE_LINESTRING || getComponentType() == TYPE_RING; }

    // 局部化，变换到相对于几何中心，并返回偏移量
    osg::Vec3d localize();

    // 反局部化
    void delocalize( const osg::Vec3d& offset );

    // 如果最后点与第一个点是相连的，则按指定的方向重新记录点列
    virtual void rewind( Orientation ori );

    /**
     * Get the winding orientation of the geometry (if you consider the last point
     * to connect back to the first in a ring.)
     */
    Orientation getOrientation() const;

public:
    virtual Type getType() const { return TYPE_UNKNOWN; }
    virtual Type getComponentType() const { return getType(); }
    virtual bool isValid() const { return size() >= 1; }

    virtual CVBF_Geometry* clone() const { return cloneAs(getType()); }

    void push_back(const osg::Vec3d& v ) {
        CVBF_VectorMixin2<osg::Vec3d,CVBF_Referenced>::push_back(v); }
    void push_back(double x, double y) {
        CVBF_VectorMixin2<osg::Vec3d,CVBF_Referenced>::push_back(osg::Vec3d(x,y,0.)); }
    void push_back(double x, double y, double z) {
        CVBF_VectorMixin2<osg::Vec3d,CVBF_Referenced>::push_back(osg::Vec3d(x,y,z)); }

protected:
};

typedef std::vector< ref_ptr<CVBF_Geometry> > CVBF_GeometryCollection;


// 无序点集
class VBF_STOBJECT_EXPORT CVBF_PointSet : public CVBF_Geometry
{
public:
    CVBF_PointSet( int capacity =0 );
    CVBF_PointSet( const VBFVec3dVector* toCopy );
    CVBF_PointSet( const CVBF_PointSet& rhs );

    virtual ~CVBF_PointSet();

public:
    virtual Type getType() const { return CVBF_Geometry::TYPE_POINTSET; }
};

// 有序点集组成的单一连续的线
class VBF_STOBJECT_EXPORT CVBF_LineString : public CVBF_Geometry
{
public:
    CVBF_LineString( int capacity =0 );
    CVBF_LineString( const CVBF_LineString& rhs );
    CVBF_LineString( const VBFVec3dVector* toCopy );

    virtual ~CVBF_LineString();

    double getLength() const;
    bool getSegment(double length, osg::Vec3d& start, osg::Vec3d& end);

public:
    virtual Type getType() const { return CVBF_Geometry::TYPE_LINESTRING; }
    virtual bool isValid() const { return size() >= 2; }
};


// 环形，一个闭合的区域，第一个点与最后一个点不相同，具有方向
class VBF_STOBJECT_EXPORT CVBF_Ring : public CVBF_Geometry
{
public:
    CVBF_Ring( int capacity =0 ) ;
    CVBF_Ring( const CVBF_Ring& ring );
    CVBF_Ring( const VBFVec3dVector* toCopy );

    virtual ~CVBF_Ring();

    // override
    virtual CVBF_Geometry* cloneAs( const CVBF_Geometry::Type& newType ) const;

    // 测试点是否在该环形内
    virtual bool contains2D( double x, double y ) const;

    // 获取有符号的面积
    virtual double getSignedArea2D() const;

    // 确保第一个点与最后一个点不同
    virtual void open();

    // 打开（确保第一个点与最后一个点不同），并按指定的方向排列点集
    virtual void rewind( Orientation ori );

public:
    virtual Type getType() const { return CVBF_Geometry::TYPE_RING; }
    virtual bool isValid() const { return size() >= 3; }
};

typedef std::vector<ref_ptr<CVBF_Ring> > CVBF_RingCollection;


// 多边形由一个边界环和0个或多个内部环（孔）组成，边界环为逆时针方向，内部的孔为顺时针方向
class VBF_STOBJECT_EXPORT CVBF_Polygon : public CVBF_Ring
{
public:
    CVBF_Polygon( int capacity =0 );
    CVBF_Polygon( const CVBF_Polygon& rhs );
    CVBF_Polygon( const VBFVec3dVector* toCopy );

    virtual ~CVBF_Polygon();

public:
    virtual Type getType() const { return CVBF_Geometry::TYPE_POLYGON; }
    virtual int getTotalPointCount() const;

    virtual unsigned getNumGeometries() const { return 1 + _holes.size(); }

    // 检测点是否在多边形内（但不在孔内）
    virtual bool contains2D( double x, double y ) const;

    virtual void open();

public:
    CVBF_RingCollection& getHoles() { return _holes; }
    const CVBF_RingCollection& getHoles() const { return _holes; }

protected:
    CVBF_RingCollection _holes;
};
// 多个CVBF_Geometry的集合
class VBF_STOBJECT_EXPORT CVBF_MultiGeometry : public CVBF_Geometry
{
public:
    CVBF_MultiGeometry();
    CVBF_MultiGeometry( const CVBF_GeometryCollection& parts );
    CVBF_MultiGeometry( const CVBF_MultiGeometry& rhs );

    virtual ~CVBF_MultiGeometry();

public:
    virtual Type getType() const { return CVBF_Geometry::TYPE_MULTI; }
    virtual Type getComponentType() const;
    virtual int getTotalPointCount() const;
    virtual unsigned getNumComponents() const { return _parts.size(); }

    virtual unsigned getNumGeometries() const;

    // override
    virtual CVBF_Geometry* cloneAs( const CVBF_Geometry::Type& newType ) const;
    virtual bool isValid() const;
    virtual CVBF_Bounds getBounds() const;
    virtual void rewind( Orientation ori );

public:
    CVBF_GeometryCollection& getComponents() { return _parts; }
    const CVBF_GeometryCollection& getComponents() const { return _parts; }

    CVBF_Geometry* add( CVBF_Geometry* geom ) { _parts.push_back(geom); return geom; }

protected:
    CVBF_GeometryCollection _parts;
};


// 集合体迭代器，依次返回每个几何体部件。该迭代器自动遍历MultiCVBF_Geometry对象，返回它的部件，而不会返回MultiCVBF_Geometry对象本身
class VBF_STOBJECT_EXPORT CVBF_GeometryIterator
{
public:
    // 参数traversePolyHoles为true时返回多边形和孔，为false时仅返回多边形（外环）
    CVBF_GeometryIterator( CVBF_Geometry* geom, bool traversePolygonHoles = true );
    virtual ~CVBF_GeometryIterator();
    bool hasMore() const;
    CVBF_Geometry* next();

private:
    CVBF_Geometry* _next;
    std::stack<CVBF_Geometry*> _stack;
    bool _traverseMulti;
    bool _traversePolyHoles;

    void fetchNext();
};

class VBF_STOBJECT_EXPORT CVBF_ConstGeometryIterator
{
public:
    CVBF_ConstGeometryIterator( const CVBF_Geometry* geom, bool traversePolygonHoles =true );
    virtual ~CVBF_ConstGeometryIterator();

    bool hasMore() const;
    const CVBF_Geometry* next();

private:
    const CVBF_Geometry* _next;
    std::stack<const CVBF_Geometry*> _stack;
    bool _traverseMulti;
    bool _traversePolyHoles;

    void fetchNext();
};

typedef std::pair<osg::Vec3d, osg::Vec3d> VBFSegment;

class VBF_STOBJECT_EXPORT CVBF_ConstSegmentIterator
{
public:
    CVBF_ConstSegmentIterator( const CVBF_Geometry* verts, bool forceClosedLoop =false );
    virtual ~CVBF_ConstSegmentIterator();
    bool hasMore() const { return !m_bDone; }
    VBFSegment next();

private:
    const VBFVec3dVector* _verts;
    VBFVec3dVector::const_iterator _iter;
    bool m_bDone;
    bool _closeLoop;
};

typedef std::vector<ref_ptr<CVBF_Geometry> > CVBF_GeometryList;


#endif
