#ifndef OSGEARTHSYMBOLOGY_GEOMETRY_H
#define OSGEARTHSYMBOLOGY_GEOMETRY_H 1

#include <VBF_3DMap/VBF_Symbology/Common>
#include <VBF_3DMap/VBF_Terrain/GeoData.h>
#include <VBF_Common/VBF_Utils/VBF_STLContainers.h>
#include <vector>
#include <stack>

namespace osgEarth { namespace Symbology 
{
    using namespace osgEarth;

    // 缓冲区操作的参数
    class BufferParameters
    {
    public:
        enum CapStyle  { CAP_DEFAULT, CAP_SQUARE, CAP_ROUND, CAP_FLAT };
        enum JoinStyle { JOIN_ROUND, JOIN_MITRE, JOIN_BEVEL};
        BufferParameters( CapStyle capStyle =CAP_DEFAULT, JoinStyle joinStyle = JOIN_ROUND, int cornerSegs =0, bool singleSided=false, bool leftSide=false )
            : _capStyle(capStyle), _joinStyle(joinStyle),_cornerSegs(cornerSegs), _singleSided(singleSided), _leftSide(leftSide) { }
        CapStyle  _capStyle;
        JoinStyle _joinStyle;
        int       _cornerSegs; // # of line segment making up a rounded corner
        bool      _singleSided; //Whether or not to do a single sided buffer
        bool      _leftSide;    //If doing a single sided buffer are we buffering to the left?  If false, buffer to the right
    };

    typedef std::vector<osg::Vec3d> Vec3dVector;


    // Geometry对象的基类
    class OSGEARTHSYMBOLOGY_EXPORT Geometry : public CVBF_VectorMixin2<osg::Vec3d,CVBF_Referenced>
    {
    public:
        Geometry( int capacity =0 );
        Geometry( const Geometry& rhs );
        Geometry( const Vec3dVector* toCopy );

       virtual ~Geometry();

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
        static Geometry* create( Type type, const Vec3dVector* toCopy );

        // true if osgEarth is compiled for buffering
        static bool hasBufferOperation();

    public:
 		// 获取总的点数
        virtual int getTotalPointCount() const;

 		// 获取部件的总数
        virtual unsigned getNumComponents() const { return 1; }

        // 获取几何体的总数，是所有组成的所有部分的总数，也可被看做是full GeometryIterator返回的几何对象的数量
        virtual unsigned getNumGeometries() const { return 1; }

        /**
         * Converts this geometry to another type. This function will return "this" if
         * the type is the same, and will return NULL if the conversion is impossible.
         */
        virtual Geometry* cloneAs( const Geometry::Type& newType ) const;

        /**
         * Creates a new Vec3Array (single-precision), copies the part into it, and
         * returns the new object. 
         */
        osg::Vec3Array* toVec3Array() const;

        /**
         * Creates a new Vec3dArray (double-precision), copies the part into it, and
         * returns the new object.
         */
        osg::Vec3dArray* toVec3dArray() const;

        /**
         * Gets the bounds of this geometry
         */
        virtual Bounds getBounds() const;


        // 几何对象是否为线
        bool isLinear() const { return getComponentType() == TYPE_LINESTRING || getComponentType() == TYPE_RING; }

        /**
         * Runs a buffer (dialate/erode) operation on this geometry and returns the
         * result in the output parameter. Returns true if the op succeeded.
         */
        bool buffer( double distance, ref_ptr<Geometry>& output, const BufferParameters& bp =BufferParameters() ) const;

        /**
         * Crops this geometry to the region represented by the crop polygon, returning
         * the result in the output parameter. Returns true if the op succeeded.
         */
        bool crop( const class Polygon* cropPolygon, ref_ptr<Geometry>& output ) const;

        /**
         * Boolean difference - subtracts diffPolygon from this geometry, and put the
         * result in output.
         */
        bool difference( const class Polygon* diffPolygon, ref_ptr<Geometry>& output ) const;

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

        virtual Geometry* clone() const { return cloneAs(getType()); }

        void push_back(const osg::Vec3d& v ) {
            CVBF_VectorMixin2<osg::Vec3d,CVBF_Referenced>::push_back(v); }
        void push_back(double x, double y) { 
            CVBF_VectorMixin2<osg::Vec3d,CVBF_Referenced>::push_back(osg::Vec3d(x,y,0.)); }
        void push_back(double x, double y, double z) { 
            CVBF_VectorMixin2<osg::Vec3d,CVBF_Referenced>::push_back(osg::Vec3d(x,y,z)); }

    protected:
    };

    typedef std::vector< ref_ptr<Geometry> > GeometryCollection;


	// 无序点集
    class OSGEARTHSYMBOLOGY_EXPORT PointSet : public Geometry
    {
    public:
        PointSet( int capacity =0 );
        PointSet( const Vec3dVector* toCopy );
        PointSet( const PointSet& rhs );

        virtual ~PointSet();

    public:
        virtual Type getType() const { return Geometry::TYPE_POINTSET; }
    };

  	// 有序点集组成的单一连续的线
    class OSGEARTHSYMBOLOGY_EXPORT LineString : public Geometry
    {
    public:
        LineString( int capacity =0 );
        LineString( const LineString& rhs );
        LineString( const Vec3dVector* toCopy );

        virtual ~LineString();

        double getLength() const;
        bool getSegment(double length, osg::Vec3d& start, osg::Vec3d& end);

    public:
        virtual Type getType() const { return Geometry::TYPE_LINESTRING; }
        virtual bool isValid() const { return size() >= 2; }
    };


	// 环形，一个闭合的区域，第一个点与最后一个点不相同，具有方向
    class OSGEARTHSYMBOLOGY_EXPORT Ring : public Geometry
    {
    public:
        Ring( int capacity =0 ) ;
        Ring( const Ring& ring );
        Ring( const Vec3dVector* toCopy );

        virtual ~Ring();

        // override
        virtual Geometry* cloneAs( const Geometry::Type& newType ) const;

        // 测试点是否在该环形内
        virtual bool contains2D( double x, double y ) const;

        // 获取有符号的面积
        virtual double getSignedArea2D() const;

		// 确保第一个点与最后一个点不同
        virtual void open();

		// 打开（确保第一个点与最后一个点不同），并按指定的方向排列点集
        virtual void rewind( Orientation ori );

    public:
        virtual Type getType() const { return Geometry::TYPE_RING; }
        virtual bool isValid() const { return size() >= 3; }
    };

    typedef std::vector<ref_ptr<Ring> > RingCollection;

  
	// 多边形由一个边界环和0个或多个内部环（孔）组成，边界环为逆时针方向，内部的孔为顺时针方向
    class OSGEARTHSYMBOLOGY_EXPORT Polygon : public Ring
    {
    public:
        Polygon( int capacity =0 );
        Polygon( const Polygon& rhs );
        Polygon( const Vec3dVector* toCopy );

        virtual ~Polygon();
        
    public:
        virtual Type getType() const { return Geometry::TYPE_POLYGON; }
        virtual int getTotalPointCount() const;
        
        virtual unsigned getNumGeometries() const { return 1 + _holes.size(); }

		// 检测点是否在多边形内（但不在孔内）
        virtual bool contains2D( double x, double y ) const;

        virtual void open();

    public:
        RingCollection& getHoles() { return _holes; }
        const RingCollection& getHoles() const { return _holes; }

    protected:
        RingCollection _holes;
    };
	// 多个Geometry的集合
    class OSGEARTHSYMBOLOGY_EXPORT MultiGeometry : public Geometry
    {
    public:
        MultiGeometry();
        MultiGeometry( const GeometryCollection& parts );
        MultiGeometry( const MultiGeometry& rhs );

        virtual ~MultiGeometry();

    public:
        virtual Type getType() const { return Geometry::TYPE_MULTI; }        
        virtual Type getComponentType() const;
        virtual int getTotalPointCount() const;        
        virtual unsigned getNumComponents() const { return _parts.size(); }
        
        virtual unsigned getNumGeometries() const;

        // override
        virtual Geometry* cloneAs( const Geometry::Type& newType ) const;
        virtual bool isValid() const;
        virtual Bounds getBounds() const;
        virtual void rewind( Orientation ori );

    public:
        GeometryCollection& getComponents() { return _parts; }
        const GeometryCollection& getComponents() const { return _parts; }

        Geometry* add( Geometry* geom ) { _parts.push_back(geom); return geom; }

    protected:
        GeometryCollection _parts;
    };


	// 集合体迭代器，依次返回每个几何体部件。该迭代器自动遍历MultiGeometry对象，返回它的部件，而不会返回MultiGeometry对象本身
    class OSGEARTHSYMBOLOGY_EXPORT GeometryIterator
    {
    public:
		// 参数traversePolyHoles为true时返回多边形和孔，为false时仅返回多边形（外环）
        GeometryIterator( Geometry* geom, bool traversePolygonHoles = true );
        virtual ~GeometryIterator();
        bool hasMore() const;
        Geometry* next();

    private:
        Geometry* _next;
        std::stack<Geometry*> _stack;
        bool _traverseMulti;
        bool _traversePolyHoles;

        void fetchNext();
    };

    class OSGEARTHSYMBOLOGY_EXPORT ConstGeometryIterator
    {
    public:
        ConstGeometryIterator( const Geometry* geom, bool traversePolygonHoles =true );
        virtual ~ConstGeometryIterator();

        bool hasMore() const;
        const Geometry* next();

    private:
        const Geometry* _next;
        std::stack<const Geometry*> _stack;
        bool _traverseMulti;
        bool _traversePolyHoles;

        void fetchNext();
    };

    typedef std::pair<osg::Vec3d, osg::Vec3d> Segment;

    class OSGEARTHSYMBOLOGY_EXPORT ConstSegmentIterator
    {
    public:
        ConstSegmentIterator( const Geometry* verts, bool forceClosedLoop =false );        
        virtual ~ConstSegmentIterator();
        bool hasMore() const { return !m_bDone; }
        Segment next();

    private:
        const Vec3dVector* _verts;
        Vec3dVector::const_iterator _iter;
        bool m_bDone;
        bool _closeLoop;
    };

    typedef std::vector<ref_ptr<Geometry> > GeometryList;

} } // namespace osgEarth::Symbology


#endif // OSGEARTHSYMBOLOGY_GEOMETRY_H

