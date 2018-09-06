#ifndef OSG_BOUNDINGSPHERE
#define OSG_BOUNDINGSPHERE 1

#include <VBF_Engine/VBF_SceneGraph/Config>
#include <VBF_Engine/VBF_SceneGraph/Export>
#include <Types/Vec3f>
#include <Types/Vec3d>

namespace osg {

template<typename VT>
class BoundingBoxImpl;


// ��Χ����������߳�������ɸѡ��Ч�ʣ����ǿɻ��ƵĶ��󣬽��Ǽ�¼��Ҫ�����ݲ��ṩ��Ҫ����ѧ���㣨�󽻣�

template<typename VT>
class BoundingSphereImpl
{
    public:
        typedef VT vec_type;
        typedef typename VT::value_type value_type;        

        vec_type    _center;
        value_type  _radius;

        // Ĭ�Ϲ��캯��������һ���Ƿ��İ�Χ�� 
        BoundingSphereImpl() : _center(0.0,0.0,0.0),_radius(-1.0) {}
    
		// ���캯�����������ĵ�Ͱ뾶
        BoundingSphereImpl(const vec_type& center, value_type radius) : _center(center),_radius(radius) {}

        // ����һ����Χ����
        BoundingSphereImpl(const BoundingSphereImpl& bs) : _center(bs._center),_radius(bs._radius) {}

        // �Ӱ�Χ�й���
        BoundingSphereImpl(const BoundingBoxImpl<VT>& bb) : _center(0.0,0.0,0.0),_radius(-1.0) { expandBy(bb); }
        BoundingSphereImpl& operator = (const BoundingSphereImpl& bs)
        {
            _center = bs._center;
            _radius = bs._radius;
            return *this;
        }

		// ��ʼ��Ϊ��Ч��Χ��
        inline void init()
        {
            _center.set(0.0,0.0,0.0);
            _radius = -1.0;
        }

        // �ж��Ƿ���Ч
        inline bool valid() const { return _radius>=0.0; }

        // ���ð�Χ������ĺͰ뾶
        inline void set(const vec_type& center,value_type radius)
        {
            _center = center;
            _radius = radius;
        }

        // ��ȡ��Χ�������
        inline vec_type& center() { return _center; }
        inline const vec_type& center() const { return _center; }

        // ��ȡ��Χ��İ뾶
        inline value_type& radius() { return _radius; }
        inline value_type radius() const { return _radius; }
        
		// ���ذ�Χ��뾶��ƽ��������Ч�ʵ�ԭ�򣬰�Χ�����Ч���ɵ����߸���
        inline value_type radius2() const { return _radius*_radius; }


		// ��չ��Χ��ʹ��Χ���ܹ�����ָ���Ľڵ㣬�ı���������Ա�뾶��С�������������û��ʼ������������Ϊ�õ㣬�뾶Ϊ0
        template<typename vector_type>
        void expandBy(const vector_type& v);
		
		// ��չ��Χ��ʹ��Χ���ܹ�����ָ���Ľڵ㣬���ı�������ġ������û��ʼ������������Ϊ�õ㣬�뾶Ϊ0
        template<typename vector_type>
        void expandRadiusBy(const vector_type& v);

		// ��չ��Χ��ʹ����������һ����Χ�򡣸ı���������Ա�뾶��С�������������û��ʼ����������Ϊ��һ����Ĳ���
        void expandBy(const BoundingSphereImpl& sh);

  		// ��չ��Χ��ʹ����������һ����Χ�򡣲��ı�������ġ������û��ʼ����������Ϊ��һ����Ĳ���
        void expandRadiusBy(const BoundingSphereImpl& sh);

        // ��չ��Χ��ʹ��������һ����Χ�С��ı���������Ա�뾶��С������
        void expandBy(const BoundingBoxImpl<VT>& bb);

        // ��չ��Χ��ʹ��������һ����Χ�С����ı��������
        void expandRadiusBy(const BoundingBoxImpl<VT>& bb);

		// �жϰ�Χ���Ƿ����ĳ����
        inline bool contains(const vec_type& v) const
        {
            return valid() && ((v-_center).length2()<=radius2());
        }

		// �жϰ�Χ���Ƿ�����һ����Χ���ཻ
        inline bool intersects( const BoundingSphereImpl& bs ) const
        {
            return valid() && bs.valid() &&
                   ((_center - bs._center).length2() <= (_radius + bs._radius)*(_radius + bs._radius));
        }
        
};


template<typename VT>
 template<typename vector_type>
void BoundingSphereImpl<VT>::expandBy(const vector_type& v)
{
    if (valid())
    {
        vec_type dv = v-_center;
        value_type r = dv.length();
        if (r>_radius)
        {
            value_type dr = (r-_radius)*0.5;
            _center += dv*(dr/r);
            _radius += dr;
        } // else do nothing as vertex is within sphere.
    }
    else
    {
        _center = v;
        _radius = 0.0;
    }
}

template<typename VT>
 template<typename vector_type>
void BoundingSphereImpl<VT>::expandRadiusBy(const vector_type& v)
{
    if (valid())
    {
        value_type r = (v-_center).length();
        if (r>_radius) _radius = r;
        // else do nothing as vertex is within sphere.
    }
    else
    {
        _center = v;
        _radius = 0.0;
    }
}

template<typename VT>
void BoundingSphereImpl<VT>::expandBy(const BoundingSphereImpl& sh)
{
    // ignore operation if incomming BoundingSphere is invalid.
    if (!sh.valid()) return;

    // This sphere is not set so use the inbound sphere
    if (!valid())
    {
        _center = sh._center;
        _radius = sh._radius;

        return;
    }
    
    
    // Calculate d == The distance between the sphere centers   
    double d = ( _center - sh.center() ).length();

    // New sphere is already inside this one
    if ( d + sh.radius() <= _radius )  
    {
        return;
    }

    //  New sphere completely contains this one 
    if ( d + _radius <= sh.radius() )  
    {
        _center = sh._center;
        _radius = sh._radius;
        return;
    }

    
    // Build a new sphere that completely contains the other two:
    //
    // The center point lies halfway along the line between the furthest
    // points on the edges of the two spheres.
    //
    // Computing those two points is ugly - so we'll use similar triangles
    double new_radius = (_radius + d + sh.radius() ) * 0.5;
    double ratio = ( new_radius - _radius ) / d ;

    _center[0] += ( sh.center()[0] - _center[0] ) * ratio;
    _center[1] += ( sh.center()[1] - _center[1] ) * ratio;
    _center[2] += ( sh.center()[2] - _center[2] ) * ratio;

    _radius = new_radius;

}

template<typename VT>
void BoundingSphereImpl<VT>::expandRadiusBy(const BoundingSphereImpl& sh)
{
    if (sh.valid())
    {
        if (valid())
        {
            value_type r = (sh._center-_center).length()+sh._radius;
            if (r>_radius) _radius = r;
            // else do nothing as vertex is within sphere.
        }
        else
        {
            _center = sh._center;
            _radius = sh._radius;
        }
    }
}

template<typename VT>        
void BoundingSphereImpl<VT>::expandBy(const BoundingBoxImpl<VT>& bb)
{
    if (bb.valid())
    {
        if (valid())
        {
            BoundingBoxImpl<vec_type> newbb(bb);

            for(unsigned int c=0;c<8;++c)
            {
                vec_type v = bb.corner(c)-_center; // get the direction vector from corner
                v.normalize(); // normalise it.
                v *= -_radius; // move the vector in the opposite direction distance radius.
                v += _center; // move to absolute position.
                newbb.expandBy(v); // add it into the new bounding box.
            }
            
            _center = newbb.center();
            _radius = newbb.radius();
            
        }
        else
        {
            _center = bb.center();
            _radius = bb.radius();
        }
    }
}

template<typename VT>
void BoundingSphereImpl<VT>::expandRadiusBy(const BoundingBoxImpl<VT>& bb)
{
    if (bb.valid())
    {
        if (valid())
        {
            for(unsigned int c=0;c<8;++c)
            {
                expandRadiusBy(bb.corner(c));
            }
        }
        else
        {
            _center = bb.center();
            _radius = bb.radius();
        }
    }
}

typedef BoundingSphereImpl<Vec3f> BoundingSpheref;
typedef BoundingSphereImpl<Vec3d> BoundingSphered;

#ifdef OSG_USE_FLOAT_BOUNDINGSPHERE
        typedef BoundingSpheref BoundingSphere;
#else
        typedef BoundingSphered BoundingSphere;        
#endif
}

#endif
