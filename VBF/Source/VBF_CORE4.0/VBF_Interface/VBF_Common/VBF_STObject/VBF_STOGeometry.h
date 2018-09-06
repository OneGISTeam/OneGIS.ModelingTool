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


// CVBF_Geometry����Ļ���
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

    // ��vector���鴴��
    static CVBF_Geometry* create( Type type, const VBFVec3dVector* toCopy );


public:
    // ��ȡ�ܵĵ���
    virtual int getTotalPointCount() const;

    // ��ȡ����������
    virtual unsigned getNumComponents() const { return 1; }

    // ��ȡ���������������������ɵ����в��ֵ�������Ҳ�ɱ�������full CVBF_GeometryIterator���صļ��ζ��������
    virtual unsigned getNumGeometries() const { return 1; }

    // �Ѵ�Geometryת��Ϊ��һ�����ͣ����������ͬ��᷵��"this"���������ת���򷵻�NULL
    virtual CVBF_Geometry* cloneAs( const CVBF_Geometry::Type& newType ) const;


//    osg::Vec3Array* toVec3Array() const;
//    osg::Vec3dArray* toVec3dArray() const;

    virtual CVBF_Bounds getBounds() const;

    // ���ζ����Ƿ�Ϊ��
    bool isLinear() const { return getComponentType() == TYPE_LINESTRING || getComponentType() == TYPE_RING; }

    // �ֲ������任������ڼ������ģ�������ƫ����
    osg::Vec3d localize();

    // ���ֲ���
    void delocalize( const osg::Vec3d& offset );

    // ����������һ�����������ģ���ָ���ķ������¼�¼����
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


// ����㼯
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

// ����㼯��ɵĵ�һ��������
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


// ���Σ�һ���պϵ����򣬵�һ���������һ���㲻��ͬ�����з���
class VBF_STOBJECT_EXPORT CVBF_Ring : public CVBF_Geometry
{
public:
    CVBF_Ring( int capacity =0 ) ;
    CVBF_Ring( const CVBF_Ring& ring );
    CVBF_Ring( const VBFVec3dVector* toCopy );

    virtual ~CVBF_Ring();

    // override
    virtual CVBF_Geometry* cloneAs( const CVBF_Geometry::Type& newType ) const;

    // ���Ե��Ƿ��ڸû�����
    virtual bool contains2D( double x, double y ) const;

    // ��ȡ�з��ŵ����
    virtual double getSignedArea2D() const;

    // ȷ����һ���������һ���㲻ͬ
    virtual void open();

    // �򿪣�ȷ����һ���������һ���㲻ͬ��������ָ���ķ������е㼯
    virtual void rewind( Orientation ori );

public:
    virtual Type getType() const { return CVBF_Geometry::TYPE_RING; }
    virtual bool isValid() const { return size() >= 3; }
};

typedef std::vector<ref_ptr<CVBF_Ring> > CVBF_RingCollection;


// �������һ���߽绷��0�������ڲ������ף���ɣ��߽绷Ϊ��ʱ�뷽���ڲ��Ŀ�Ϊ˳ʱ�뷽��
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

    // �����Ƿ��ڶ�����ڣ������ڿ��ڣ�
    virtual bool contains2D( double x, double y ) const;

    virtual void open();

public:
    CVBF_RingCollection& getHoles() { return _holes; }
    const CVBF_RingCollection& getHoles() const { return _holes; }

protected:
    CVBF_RingCollection _holes;
};
// ���CVBF_Geometry�ļ���
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


// ����������������η���ÿ�������岿�����õ������Զ�����MultiCVBF_Geometry���󣬷������Ĳ����������᷵��MultiCVBF_Geometry������
class VBF_STOBJECT_EXPORT CVBF_GeometryIterator
{
public:
    // ����traversePolyHolesΪtrueʱ���ض���κͿף�Ϊfalseʱ�����ض���Σ��⻷��
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
