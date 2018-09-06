#ifndef OSG_SHAPE
#define OSG_SHAPE 1

//#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <Types/Vec3>
#include <Types/VBF_Quat.h>
#include <Types/VBF_Plane.h>
#include <VBF_Engine/VBF_SceneGraph/Array>

namespace osg {


class ShapeVisitor;
class ConstShapeVisitor;


#define META_Shape(library,name) \
        virtual osg::CVBF_Object* cloneType() const { return new name(); } \
        virtual osg::CVBF_Object* clone(const osg::CopyOp& copyop) const { return new name (*this,copyop); } \
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
        virtual const char* libraryName() const { return #library; } \
        virtual const char* className() const { return #name; } \
        virtual void accept(osg::ShapeVisitor& sv) { sv.apply(*this); } \
        virtual void accept(osg::ConstShapeVisitor& csv) const { csv.apply(*this); }

/** Base class for all shape types. 
  * Shapes are used to either for culling and collision detection or
  * to define the geometric shape of procedurally generate Geometry.
*/
class OSG_EXPORT Shape : public CVBF_Object
{
    public:

        Shape();       
        Shape(const Shape& sa,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
        
        /** Clone the type of an attribute, with CVBF_Object* return type.
            Must be defined by derived classes.*/
        virtual CVBF_Object* cloneType() const = 0;

        /** Clone an attribute, with CVBF_Object* return type.
            Must be defined by derived classes.*/
        virtual CVBF_Object* clone(const CopyOp&) const = 0;


        /** return true if this and obj are of the same kind of object.*/
        virtual bool isSameKindAs(const CVBF_Object* obj) const { return dynamic_cast<const Shape*>(obj)!=NULL; }

        /** return the name of the attribute's library.*/
        virtual const char* libraryName() const { return "osg"; }

        /** return the name of the attribute's class type.*/
        virtual const char* className() const { return "Shape"; }

        /** accept a non const shape visitor which can be used on non const shape objects.
            Must be defined by derived classes.*/
        virtual void accept(ShapeVisitor&)=0;

        /** accept a const shape visitor which can be used on const shape objects.
            Must be defined by derived classes.*/
        virtual void accept(ConstShapeVisitor&) const =0;

    protected:
    
        virtual ~Shape();
};

// forward declarations of Shape types.
class Sphere;
class Box;
class Cone;
class Cylinder;
class Capsule;
class InfinitePlane;

class TriangleMesh;
class ConvexHull;
class HeightField;

class CompositeShape;

class OSG_EXPORT ShapeVisitor
{
    public:
    
        ShapeVisitor() {}
        virtual ~ShapeVisitor();

        virtual void apply(Shape&) {}
        virtual void apply(Sphere&) {}
        virtual void apply(Box&) {}
        virtual void apply(Cone&) {}
        virtual void apply(Cylinder&) {}
        virtual void apply(Capsule&) {}
        virtual void apply(InfinitePlane&) {}

        virtual void apply(TriangleMesh&) {}
        virtual void apply(ConvexHull&) {}
        virtual void apply(HeightField&) {}

        virtual void apply(CompositeShape&) {}
};

class OSG_EXPORT ConstShapeVisitor
{
    public:
    
        ConstShapeVisitor() {}
        virtual ~ConstShapeVisitor();

        virtual void apply(const Shape&) {}
        virtual void apply(const Sphere&) {}
        virtual void apply(const Box&) {}
        virtual void apply(const Cone&) {}
        virtual void apply(const Cylinder&) {}
        virtual void apply(const Capsule&) {}
        virtual void apply(const InfinitePlane&) {}

        virtual void apply(const TriangleMesh&) {}
        virtual void apply(const ConvexHull&) {}
        virtual void apply(const HeightField&) {}

        virtual void apply(const CompositeShape&) {}
};

// ����
class OSG_EXPORT Sphere : public Shape
{
    public:
// IE���ܴ���
        Sphere():
            _center(0.0f,0.0f,0.0f),
            _radius(1.0f) {}

        Sphere(const osg::Vec3& center,float radius):
            _center(center),
            _radius(radius) {}

        Sphere(const Sphere& sphere,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            Shape(sphere,copyop),
            _center(sphere._center),
            _radius(sphere._radius) {}

        META_Shape(osg, Sphere);

        inline bool valid() const { return _radius>=0.0f; }

        inline void set(const Vec3& center,float radius)
        {
            _center = center;
            _radius = radius;
        }

        inline void setCenter(const Vec3& center) { _center = center; }
        inline const Vec3& getCenter() const { return _center; }

        inline void setRadius(float radius) { _radius = radius; }
        inline float getRadius() const { return _radius; }

    protected:

        virtual ~Sphere();

        Vec3    _center;
        float   _radius;

};

// ������
class OSG_EXPORT Box : public Shape
{
    public:
// IE���ܴ���
        Box():
            _center(0.0f,0.0f,0.0f),
            _halfLengths(0.5f,0.5f,0.5f) {}

        Box(const osg::Vec3& center,float width):
            _center(center),
            _halfLengths(width*0.5f,width*0.5f,width*0.5f) {}

        Box(const osg::Vec3& center,float lengthX,float lengthY, float lengthZ):
            _center(center),
            _halfLengths(lengthX*0.5f,lengthY*0.5f,lengthZ*0.5f) {}

        Box(const Box& box,const CopyOp& copyop=CopyOp::SHALLOW_COPY): 
            Shape(box,copyop),
            _center(box._center),
            _halfLengths(box._halfLengths),
            _rotation(box._rotation) {}

        META_Shape(osg, Box);

        inline bool valid() const { return _halfLengths.x()>=0.0f; }

        inline void set(const Vec3& center,const Vec3& halfLengths)
        {
            _center = center;
            _halfLengths = halfLengths;
        }

        inline void setCenter(const Vec3& center) { _center = center; }
        inline const Vec3& getCenter() const { return _center; }

        inline void setHalfLengths(const Vec3& halfLengths) { _halfLengths = halfLengths; }
        inline const Vec3& getHalfLengths() const { return _halfLengths; }

        inline void setRotation(const Quat& quat) { _rotation = quat; }
        inline const Quat&  getRotation() const { return _rotation; }
        inline Matrix computeRotationMatrix() const { return Matrix(_rotation); }
        inline bool zeroRotation() const { return _rotation.zeroRotation(); } 

    protected:
    
        virtual ~Box();
    
        Vec3    _center;
        Vec3    _halfLengths;
        Quat    _rotation;

};


// Բ׶��
class OSG_EXPORT Cone : public Shape
{
    public:
// IE���ܴ���
        Cone():
            _center(0.0f,0.0f,0.0f),
            _radius(1.0f),
            _height(1.0f) {}

        Cone(const osg::Vec3& center,float radius,float height):
            _center(center),
            _radius(radius),
            _height(height) {}

        Cone(const Cone& cone,const CopyOp& copyop=CopyOp::SHALLOW_COPY): 
            Shape(cone,copyop),
            _center(cone._center),
            _radius(cone._radius),
            _height(cone._height),
            _rotation(cone._rotation) {}

        META_Shape(osg, Cone);

        inline bool valid() const { return _radius>=0.0f; }

        inline void set(const Vec3& center,float radius, float height)
        {
            _center = center;
            _radius = radius;
            _height = height;
        }

        inline void setCenter(const Vec3& center) { _center = center; }
        inline const Vec3& getCenter() const { return _center; }

        inline void setRadius(float radius) { _radius = radius; }
        inline float getRadius() const { return _radius; }

        inline void setHeight(float height) { _height = height; }
        inline float getHeight() const { return _height; }

        inline void setRotation(const Quat& quat) { _rotation = quat; }
        inline const Quat& getRotation() const { return _rotation; }
        inline Matrix computeRotationMatrix() const { return Matrix(_rotation); }
        inline bool zeroRotation() const { return _rotation.zeroRotation(); } 

        inline float getBaseOffsetFactor() const { return 0.25f; } 
        inline float getBaseOffset() const { return -getBaseOffsetFactor()*getHeight(); } 

    protected:
    
        virtual ~Cone();
    
        Vec3    _center;
        float   _radius;
        float   _height;

        Quat    _rotation;
};

// Բ����
class OSG_EXPORT Cylinder : public Shape
{
    public:
// IE���ܴ���
        Cylinder():
            _center(0.0f,0.0f,0.0f),
            _radius(1.0f),
            _height(1.0f) {}

        Cylinder(const osg::Vec3& center,float radius,float height):
            _center(center),
            _radius(radius),
            _height(height) {}

        Cylinder(const Cylinder& cylinder,const CopyOp& copyop=CopyOp::SHALLOW_COPY): 
            Shape(cylinder,copyop),
            _center(cylinder._center),
            _radius(cylinder._radius),
            _height(cylinder._height),
            _rotation(cylinder._rotation) {}

        META_Shape(osg, Cylinder);

        inline bool valid() const { return _radius>=0.0f; }

        inline void set(const Vec3& center,float radius, float height)
        {
            _center = center;
            _radius = radius;
            _height = height;
        }

        inline void setCenter(const Vec3& center) { _center = center; }
        inline const Vec3& getCenter() const { return _center; }

        inline void setRadius(float radius) { _radius = radius; }
        inline float getRadius() const { return _radius; }

        inline void setHeight(float height) { _height = height; }
        inline float getHeight() const { return _height; }

        inline void setRotation(const Quat& quat) { _rotation = quat; }
        inline const Quat& getRotation() const { return _rotation; }
        inline Matrix computeRotationMatrix() const { return Matrix(_rotation); }
        bool zeroRotation() const { return _rotation.zeroRotation(); } 

    protected:
    
        virtual ~Cylinder();

        Vec3    _center;
        float   _radius;
        float   _height;
        Quat    _rotation;
};

// ̫�ղ�
class OSG_EXPORT Capsule : public Shape
{
    public:
// IE���ܴ���
        Capsule():
            _center(0.0f,0.0f,0.0f),
            _radius(1.0f),
            _height(1.0f) {}

        Capsule(const osg::Vec3& center,float radius,float height):
            _center(center),
            _radius(radius),
            _height(height) {}

        Capsule(const Capsule& capsule,const CopyOp& copyop=CopyOp::SHALLOW_COPY): 
            Shape(capsule,copyop),
            _center(capsule._center),
            _radius(capsule._radius),
            _height(capsule._height),
            _rotation(capsule._rotation) {}

        META_Shape(osg, Capsule);

        inline bool valid() const { return _radius>=0.0f; }

        inline void set(const Vec3& center,float radius, float height)
        {
            _center = center;
            _radius = radius;
            _height = height;
        }

        inline void setCenter(const Vec3& center) { _center = center; }
        inline const Vec3& getCenter() const { return _center; }

        inline void setRadius(float radius) { _radius = radius; }
        inline float getRadius() const { return _radius; }

        inline void setHeight(float height) { _height = height; }
        inline float getHeight() const { return _height; }

        inline void setRotation(const Quat& quat) { _rotation = quat; }
        inline const Quat& getRotation() const { return _rotation; }
        inline Matrix computeRotationMatrix() const { return Matrix(_rotation); }
        bool zeroRotation() const { return _rotation.zeroRotation(); } 

    protected:
    
        virtual ~Capsule();
    
        Vec3    _center;
        float   _radius;
        float   _height;
        Quat    _rotation;
};

// ����ƽ��
class OSG_EXPORT InfinitePlane : public Shape, public Plane
{
    public:
        InfinitePlane() {}
// IE���ܴ���
        InfinitePlane(const InfinitePlane& plane,const CopyOp& copyop=CopyOp::SHALLOW_COPY): 
            Shape(plane,copyop),
            Plane(plane) {}

        META_Shape(osg, InfinitePlane);

     protected:
     
        virtual ~InfinitePlane();
};

// ����������Ϊ����ײ��⣬��������Ⱦ
class OSG_EXPORT TriangleMesh : public Shape
{
    public:
    // IE���ܴ���
        TriangleMesh() {}

        TriangleMesh(const TriangleMesh& mesh,const CopyOp& copyop=CopyOp::SHALLOW_COPY): 
            Shape(mesh,copyop),
            _vertices(mesh._vertices),
            _indices(mesh._indices) {}

        META_Shape(osg, TriangleMesh);


        void setVertices(Vec3Array* vertices) { _vertices = vertices; }
        Vec3Array* getVertices() { return _vertices.get(); }
        const Vec3Array* getVertices() const { return _vertices.get(); }


        void setIndices(IndexArray* indices) { _indices = indices; }
        IndexArray* getIndices() { return _indices.get(); }
        const IndexArray* getIndices() const { return _indices.get(); }

    protected:
    
        virtual ~TriangleMesh();

        ref_ptr<Vec3Array> _vertices;
        ref_ptr<IndexArray> _indices;

};

// ͹����
class OSG_EXPORT ConvexHull : public TriangleMesh
{
    public:
    // IE���ܴ���
        ConvexHull() {}

        ConvexHull(const ConvexHull& hull,const CopyOp& copyop=CopyOp::SHALLOW_COPY): 
            TriangleMesh(hull,copyop) {}

        META_Shape(osg, TriangleMesh);

    protected:
    
        virtual ~ConvexHull();
};

// �߳�ͼ
class OSG_EXPORT HeightField : public Shape
{
    public:
    
        HeightField();

        HeightField(const HeightField& mesh,const CopyOp& copyop=CopyOp::SHALLOW_COPY);
        
        META_Shape(osg, HeightField);

        typedef std::vector<float> HeightList;

        void allocate(unsigned int numColumns,unsigned int numRows);

        inline unsigned int getNumColumns() const { return _columns; }
        inline unsigned int getNumRows() const { return _rows; }

        inline void setOrigin(const osg::Vec3& origin) { _origin = origin; }
        inline const osg::Vec3& getOrigin() const { return _origin; }

        inline void setXInterval(float dx) { _dx = dx; }
        inline float getXInterval() const { return _dx; }

        inline void setYInterval(float dy) { _dy = dy; }
        inline float getYInterval() const { return _dy; }
    
        /** Get the FloatArray height data.*/
        osg::FloatArray* getFloatArray() { return _heights.get(); }

        /** Get the const FloatArray height data.*/
        const osg::FloatArray* getFloatArray() const { return _heights.get(); }

        HeightList& getHeightList() { return _heights->asVector(); }

        const HeightList& getHeightList() const { return _heights->asVector(); }

        /** Set the height of the skirt to render around the edge of HeightField.
          * The skirt is used as a means of disguising edge boundaries between adjacent HeightField, 
          * particularly of ones with different resolutions.*/
        void setSkirtHeight(float skirtHeight) { _skirtHeight = skirtHeight; }

        /** Get the height of the skirt to render around the edge of HeightField.*/
        float getSkirtHeight() const { return _skirtHeight; }

        /** Set the width in number of cells in from the edge that the height field should be rendered from.
          * This exists to allow gradient and curvature continutity to be maintained between adjacent HeightField, where
          * the border cells will overlap adjacent HeightField.*/
        void setBorderWidth(unsigned int borderWidth) { _borderWidth = borderWidth; }

        /** Get the width in number of cells in from the edge that the height field should be rendered from.*/
        unsigned int getBorderWidth() const { return _borderWidth; }

        inline void setRotation(const Quat& quat) { _rotation = quat; }
        inline const Quat& getRotation() const { return _rotation; }
        inline Matrix computeRotationMatrix() const { return Matrix(_rotation); }
        inline bool zeroRotation() const { return _rotation.zeroRotation(); } 

        /* set a single height point in the height field */
        inline void setHeight(unsigned int c,unsigned int r,float value)
        {
           (*_heights)[c+r*_columns] = value;
        }

        /* Get address of single height point in the height field, allows user to change. */
        inline float& getHeight(unsigned int c,unsigned int r)
        {
           return (*_heights)[c+r*_columns];
        }

        /* Get value of single height point in the height field, not editable. */
        inline float getHeight(unsigned int c,unsigned int r) const
        {
           return (*_heights)[c+r*_columns];
        }

        inline Vec3 getVertex(unsigned int c,unsigned int r) const
        {
            return Vec3(_origin.x()+getXInterval()*(float)c,
                        _origin.y()+getYInterval()*(float)r,
                        _origin.z()+(*_heights)[c+r*_columns]);  
        }

        Vec3 getNormal(unsigned int c,unsigned int r) const;

        Vec2 getHeightDelta(unsigned int c,unsigned int r) const;

    protected:
    
        virtual ~HeightField();

        unsigned int                    _columns,_rows;

        osg::Vec3                       _origin; // _origin is the min value of the X and Y coordinates.
        float                           _dx;
        float                           _dy;

        float                           _skirtHeight;
        unsigned int                    _borderWidth;

        Quat                            _rotation;
        ref_ptr<osg::FloatArray>   _heights;

};

typedef HeightField Grid;

// ���
class OSG_EXPORT CompositeShape : public Shape
{
    public:


    
        typedef std::vector< ref_ptr<Shape> > ChildList;
// IE���ܴ���
        CompositeShape() {}

        CompositeShape(const CompositeShape& cs,const CopyOp& copyop=CopyOp::SHALLOW_COPY): 
            Shape(cs,copyop),
            _children(cs._children) {}

        META_Shape(osg, CompositeShape);

        /** Set the shape that encloses all of the children.*/
        void setShape(Shape* shape) { _shape = shape; }

        /** Get the shape that encloses all of the children.*/
        Shape* getShape() { return _shape.get(); }

        /** Get the const shape that encloses all of the children.*/
        const Shape* getShape() const { return _shape.get(); }

        /** Get the number of children of this composite shape.*/
        unsigned int getNumChildren() const { return static_cast<unsigned int>(_children.size()); }

        /** Get a child.*/
        Shape* getChild(unsigned int i) { return _children[i].get(); }

        /** Get a const child.*/
        const Shape* getChild(unsigned int i) const { return _children[i].get(); }

        /** Add a child to the list.*/
        void addChild(Shape* shape) { _children.push_back(shape); }

        /** remove a child from the list.*/
        void removeChild(unsigned int i) { _children.erase(_children.begin()+i); }

        /** find the index number of child, if child is not found then it returns getNumChildren(),
          * so should be used in similar style to STL's result!=end().*/ 
        unsigned int findChildNo(Shape* shape) const
        { 
            for (unsigned int childNo=0;childNo<_children.size();++childNo)
            {
                if (_children[childNo]==shape) return childNo;
            }
            return static_cast<unsigned int>(_children.size()); // node not found.

        }

    protected:
    
        virtual ~CompositeShape();

        ref_ptr<Shape>  _shape;
        ChildList       _children;

};

}

#endif
