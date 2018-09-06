#ifndef OSG_BOUNDINGBOX
#define OSG_BOUNDINGBOX 1

#include <VBF_Engine/VBF_SceneGraph/Config>
#include <VBF_Engine/VBF_SceneGraph/Export>
#include <Types/Vec3>
#include <Types/Vec3d>
#include <float.h>

namespace osg {

template<typename VT>
class BoundingSphereImpl;

// �����İ�Χ��
template<typename VT>
class BoundingBoxImpl
{
    public:
        typedef VT vec_type;
        typedef typename VT::value_type value_type;
    
        
        vec_type _min;// ��С��Χ(��������ֵ����СX��Y��Zֵ)      
        vec_type _max;// ���Χ(��������ֵ�����X��Y��Zֵ)

        // Ĭ�Ϲ��캯��������һ���Ƿ��İ�Χ��
        inline BoundingBoxImpl() :
            _min(FLT_MAX, FLT_MAX, FLT_MAX),
            _max(-FLT_MAX, -FLT_MAX, -FLT_MAX)
        {}
    
		// �ø����Ĳ��������Χ�� 
        inline BoundingBoxImpl(value_type xmin, value_type ymin, value_type zmin,
                           value_type xmax, value_type ymax, value_type zmax) :
                           _min(xmin,ymin,zmin),
                           _max(xmax,ymax,zmax) {}

        inline BoundingBoxImpl(const vec_type& min,const vec_type& max) : 
                    _min(min),
                    _max(max) {}

        // ��Χ�г�ʼ�����Ѱ�Χ������Ϊ�Ƿ���Χ��
        inline void init()
        {
            _min.set(FLT_MAX, FLT_MAX, FLT_MAX);
            _max.set(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        }
        
        // �жϰ�Χ���Ƿ���Ч       
        inline bool valid() const
        {
            return _max.x()>=_min.x() &&  _max.y()>=_min.y() &&  _max.z()>=_min.z();
        }

        // ���ð�Χ�еķ�Χ
        inline void set (value_type xmin, value_type ymin, value_type zmin,
                         value_type xmax, value_type ymax, value_type zmax)
        {
            _min.set(xmin,ymin,zmin);
            _max.set(xmax,ymax,zmax);
        }

        inline void set(const vec_type& min,const vec_type& max)
        {
            _min = min;
            _max = max;
        }

		// ��ȡ��Χ�з�Χ����
        inline value_type& xMin() { return _min.x(); }
        inline value_type xMin() const { return _min.x(); }
 
        inline value_type& yMin() { return _min.y(); }
        inline value_type yMin() const { return _min.y(); }
 
        inline value_type& zMin() { return _min.z(); }
        inline value_type zMin() const { return _min.z(); }

        inline value_type& xMax() { return _max.x(); }
        inline value_type xMax() const { return _max.x(); }
 
        inline value_type& yMax() { return _max.y(); }
        inline value_type yMax() const { return _max.y(); }
 
        inline value_type& zMax() { return _max.z(); }
        inline value_type zMax() const { return _max.z(); }

		// ��ȡ��Χ������
        inline const vec_type center() const { return (_min+_max)*0.5; }

		// ��ȡ��Χ�а뾶���Խ��߳��ȵ�һ�룩
        inline value_type radius() const { return sqrt(radius2()); }

        // ��ȡ��Χ�а뾶��ƽ�����ٶȿ죩
        inline value_type radius2() const
        {
            return 0.25*((_max-_min).length2());
        }

		// ��ȡ��Χ�еĽǵ㣬posֵΪ0-7��������ռ��λ��ÿһλΪһ�����С����0��ʾ��С��000����7��ʾ���111��
        inline const vec_type corner(unsigned int pos) const
        {
            return vec_type(pos&1?_max.x():_min.x(),pos&2?_max.y():_min.y(),pos&4?_max.z():_min.z());
        }


		// ��չ��Χ�У�ʹ���ܹ����ɸ����Ķ���v�������Χ��û�г�ʼ�������Χ�е������Сֵ����Ϊv
        inline void expandBy(const vec_type& v)
        {
            if(v.x()<_min.x()) _min.x() = v.x();
            if(v.x()>_max.x()) _max.x() = v.x();

            if(v.y()<_min.y()) _min.y() = v.y();
            if(v.y()>_max.y()) _max.y() = v.y();

            if(v.z()<_min.z()) _min.z() = v.z();
            if(v.z()>_max.z()) _max.z() = v.z();
        }

        inline void expandBy(value_type x,value_type y,value_type z)
        {
            if(x<_min.x()) _min.x() = x;
            if(x>_max.x()) _max.x() = x;

            if(y<_min.y()) _min.y() = y;
            if(y>_max.y()) _max.y() = y;

            if(z<_min.z()) _min.z() = z;
            if(z>_max.z()) _max.z() = z;
        }

		// ��չ��Χ�У�ʹ��������һ����Χ��bb�������Χ��û�г�ʼ��������Ϊbb
        void expandBy(const BoundingBoxImpl& bb)
        {
            if (!bb.valid()) return;

            if(bb._min.x()<_min.x()) _min.x() = bb._min.x();
            if(bb._max.x()>_max.x()) _max.x() = bb._max.x();

            if(bb._min.y()<_min.y()) _min.y() = bb._min.y();
            if(bb._max.y()>_max.y()) _max.y() = bb._max.y();

            if(bb._min.z()<_min.z()) _min.z() = bb._min.z();
            if(bb._max.z()>_max.z()) _max.z() = bb._max.z();
        }

		// ��չ��Χ�У�ʹ������һ����Χ��sh�������Χ��û�г�ʼ���������ð�Χ������sh
        void expandBy(const BoundingSphereImpl<VT>& sh)
        {
            if (!sh.valid()) return;

            if(sh._center.x()-sh._radius<_min.x()) _min.x() = sh._center.x()-sh._radius;
            if(sh._center.x()+sh._radius>_max.x()) _max.x() = sh._center.x()+sh._radius;

            if(sh._center.y()-sh._radius<_min.y()) _min.y() = sh._center.y()-sh._radius;
            if(sh._center.y()+sh._radius>_max.y()) _max.y() = sh._center.y()+sh._radius;

            if(sh._center.z()-sh._radius<_min.z()) _min.z() = sh._center.z()-sh._radius;
            if(sh._center.z()+sh._radius>_max.z()) _max.z() = sh._center.z()+sh._radius;
        }
        
		// ��Χ������һ����Χ���󽻣��������󽻽��
        BoundingBoxImpl intersect(const BoundingBoxImpl& bb) const
        {    return BoundingBoxImpl(osg::maximum(xMin(),bb.xMin()),osg::maximum(yMin(),bb.yMin()),osg::maximum(zMin(),bb.zMin()),
                                     osg::minimum(xMax(),bb.xMax()),osg::minimum(yMax(),bb.yMax()),osg::minimum(zMax(),bb.zMax()));

        }

       // �жϰ�Χ���Ƿ�����һ����Χ���ཻ
        bool intersects(const BoundingBoxImpl& bb) const
        {    return osg::maximum(xMin(),bb.xMin()) <= osg::minimum(xMax(),bb.xMax()) &&
                    osg::maximum(yMin(),bb.yMin()) <= osg::minimum(yMax(),bb.yMax()) &&
                    osg::maximum(zMin(),bb.zMin()) <= osg::minimum(zMax(),bb.zMax());

        }

        /** Returns true if this bounding box contains the specified coordinate. */
        inline bool contains(const vec_type& v) const
        {
            return valid() && 
                   (v.x()>=_min.x() && v.x()<=_max.x()) &&
                   (v.y()>=_min.y() && v.y()<=_max.y()) &&
                   (v.z()>=_min.z() && v.z()<=_max.z());
        }
};

typedef BoundingBoxImpl<Vec3f> BoundingBoxf;
typedef BoundingBoxImpl<Vec3d> BoundingBoxd;

#ifdef OSG_USE_FLOAT_BOUNDINGBOX
typedef BoundingBoxf BoundingBox;
#else
typedef BoundingBoxd BoundingBox;
#endif

}

#endif
