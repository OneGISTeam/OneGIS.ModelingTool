#ifndef OSG_BOUNDINGSPHERE
#define OSG_BOUNDINGSPHERE 1

#include <VBF_Engine/VBF_SceneGraph/Config>
#include <VBF_Engine/VBF_SceneGraph/Export>
#include <Types/Vec3f>
#include <Types/Vec3d>

namespace osg {

template<typename VT>
class BoundingBoxImpl;


// 包围球，有助于提高场景绘制筛选的效率，不是可绘制的对象，仅是记录必要的数据并提供必要的数学运算（求交）

template<typename VT>
class BoundingSphereImpl
{
    public:
        typedef VT vec_type;
        typedef typename VT::value_type value_type;        

        vec_type    _center;
        value_type  _radius;

        // 默认构造函数，构造一个非法的包围球 
        BoundingSphereImpl() : _center(0.0,0.0,0.0),_radius(-1.0) {}
    
		// 构造函数，传入中心点和半径
        BoundingSphereImpl(const vec_type& center, value_type radius) : _center(center),_radius(radius) {}

        // 从另一个包围球构造
        BoundingSphereImpl(const BoundingSphereImpl& bs) : _center(bs._center),_radius(bs._radius) {}

        // 从包围盒构造
        BoundingSphereImpl(const BoundingBoxImpl<VT>& bb) : _center(0.0,0.0,0.0),_radius(-1.0) { expandBy(bb); }
        BoundingSphereImpl& operator = (const BoundingSphereImpl& bs)
        {
            _center = bs._center;
            _radius = bs._radius;
            return *this;
        }

		// 初始化为无效包围球
        inline void init()
        {
            _center.set(0.0,0.0,0.0);
            _radius = -1.0;
        }

        // 判断是否有效
        inline bool valid() const { return _radius>=0.0; }

        // 设置包围球的中心和半径
        inline void set(const vec_type& center,value_type radius)
        {
            _center = center;
            _radius = radius;
        }

        // 获取包围球的中心
        inline vec_type& center() { return _center; }
        inline const vec_type& center() const { return _center; }

        // 获取包围球的半径
        inline value_type& radius() { return _radius; }
        inline value_type radius() const { return _radius; }
        
		// 返回包围球半径的平方，考虑效率的原因，包围球的有效性由调用者负责
        inline value_type radius2() const { return _radius*_radius; }


		// 扩展包围球，使包围球能够容纳指定的节点，改变球的中心以便半径最小化增长，如果球没初始化，设置中心为该点，半径为0
        template<typename vector_type>
        void expandBy(const vector_type& v);
		
		// 扩展包围球，使包围球能够容纳指定的节点，不改变球的中心。如果球没初始化，设置中心为该点，半径为0
        template<typename vector_type>
        void expandRadiusBy(const vector_type& v);

		// 扩展包围球，使其能容纳另一个包围球。改变球的中心以便半径最小化增长，如果球没初始化，则设置为另一个球的参数
        void expandBy(const BoundingSphereImpl& sh);

  		// 扩展包围球，使其能容纳另一个包围球。不改变球的中心。如果球没初始化，则设置为另一个球的参数
        void expandRadiusBy(const BoundingSphereImpl& sh);

        // 扩展包围球，使其能容纳一个包围盒。改变球的中心以便半径最小化增长
        void expandBy(const BoundingBoxImpl<VT>& bb);

        // 扩展包围球，使其能容纳一个包围盒。不改变球的中心
        void expandRadiusBy(const BoundingBoxImpl<VT>& bb);

		// 判断包围球是否包含某个点
        inline bool contains(const vec_type& v) const
        {
            return valid() && ((v-_center).length2()<=radius2());
        }

		// 判断包围球是否与另一个包围球相交
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
