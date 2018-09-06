#ifndef VBF_MATH_QUAT
#define VBF_MATH_QUAT 1

#include <VBF_Common/VBF_Math/VBF_Export.h>

#include <Types/Vec3f>
#include <Types/Vec4f>
#include <Types/Vec3d>
#include <Types/Vec4d>

namespace osg {

class Matrixf;
class Matrixd;

// 四元数
class VBF_MATH_EXPORT Quat
{

    public:

        typedef double value_type; // 数据类型为double
        value_type  _v[4];    // 4个分量

		// 构造函数。构造一个没有旋转的四元数
        inline Quat() { _v[0]=0.0; _v[1]=0.0; _v[2]=0.0; _v[3]=1.0; }
		
		// 构造函数。直接设置4个分量
        inline Quat( value_type x, value_type y, value_type z, value_type w )
        {
            _v[0]=x; _v[1]=y; _v[2]=z; _v[3]=w;
        }

        inline Quat( const Vec4f& v )
        {
            _v[0]=v.x(); _v[1]=v.y(); _v[2]=v.z(); _v[3]=v.w();
        }

        inline Quat( const Vec4d& v )
        {
            _v[0]=v.x(); _v[1]=v.y(); _v[2]=v.z(); _v[3]=v.w();
        }

		// 构造函数。沿某个向量轴旋转旋转一定的角度构建四元数
        inline Quat( value_type angle, const Vec3f& axis) 
        {
            makeRotate(angle,axis);
        }
        inline Quat( value_type angle, const Vec3d& axis)
        {
            makeRotate(angle,axis);
        }

		// 构造函数。使四元数（0，0，0，1）沿三个轴各旋转一定的角度来构造四元数。通常三个轴为笛卡尔坐标系的XYZ轴
        inline Quat( value_type angle1, const Vec3f& axis1, 
                     value_type angle2, const Vec3f& axis2,
                     value_type angle3, const Vec3f& axis3)
        {
            makeRotate(angle1,axis1,angle2,axis2,angle3,axis3);
        }

        inline Quat( value_type angle1, const Vec3d& axis1, 
                     value_type angle2, const Vec3d& axis2,
                     value_type angle3, const Vec3d& axis3)
        {
            makeRotate(angle1,axis1,angle2,axis2,angle3,axis3);
        }


        inline Quat& operator = (const Quat& v) { _v[0]=v._v[0];  _v[1]=v._v[1]; _v[2]=v._v[2]; _v[3]=v._v[3]; return *this; }

        inline bool operator == (const Quat& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1] && _v[2]==v._v[2] && _v[3]==v._v[3]; }

        inline bool operator != (const Quat& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1] || _v[2]!=v._v[2] || _v[3]!=v._v[3]; }

        inline bool operator <  (const Quat& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else if (_v[2]<v._v[2]) return true;
            else if (_v[2]>v._v[2]) return false;
            else return (_v[3]<v._v[3]);
        }

        /* ----------------------------------
           Methods to access data members
        ---------------------------------- */

        inline Vec4d asVec4() const
        {
            return Vec4d(_v[0], _v[1], _v[2], _v[3]);
        }

        inline Vec3d asVec3() const
        {
            return Vec3d(_v[0], _v[1], _v[2]);
        }

        inline void set(value_type x, value_type y, value_type z, value_type w)
        {
            _v[0]=x;
            _v[1]=y;
            _v[2]=z;
            _v[3]=w;
        }
        
        inline void set(const osg::Vec4f& v)
        {
            _v[0]=v.x();
            _v[1]=v.y();
            _v[2]=v.z();
            _v[3]=v.w();
        }

        inline void set(const osg::Vec4d& v)
        {
            _v[0]=v.x();
            _v[1]=v.y();
            _v[2]=v.z();
            _v[3]=v.w();
        }
        
        void set(const Matrixf& matrix);
        
        void set(const Matrixd& matrix);
        
        void get(Matrixf& matrix) const;

        void get(Matrixd& matrix) const;
        

        inline value_type & operator [] (int i) { return _v[i]; }
        inline value_type   operator [] (int i) const { return _v[i]; }

        inline value_type & x() { return _v[0]; }
        inline value_type & y() { return _v[1]; }
        inline value_type & z() { return _v[2]; }
        inline value_type & w() { return _v[3]; }

        inline value_type x() const { return _v[0]; }
        inline value_type y() const { return _v[1]; }
        inline value_type z() const { return _v[2]; }
        inline value_type w() const { return _v[3]; }

        /** return true if the Quat represents a zero rotation, and therefore can be ignored in computations.*/
        bool zeroRotation() const { return _v[0]==0.0 && _v[1]==0.0 && _v[2]==0.0 && _v[3]==1.0; } 


    
		// 基本运算，有些和vec4是有很大区别的，如乘法

        // 乘以标量 （二元操作）
        inline const Quat operator * (value_type rhs) const
        {
            return Quat(_v[0]*rhs, _v[1]*rhs, _v[2]*rhs, _v[3]*rhs);
        }

        // 乘以标量（一元操作）
        inline Quat& operator *= (value_type rhs)
        {
            _v[0]*=rhs;
            _v[1]*=rhs;
            _v[2]*=rhs;
            _v[3]*=rhs;
            return *this;        // enable nesting
        }

        // 二元乘法，将两个四元数相称，相当于将两个旋转动作相加
        inline const Quat operator*(const Quat& rhs) const
        {
            return Quat( rhs._v[3]*_v[0] + rhs._v[0]*_v[3] + rhs._v[1]*_v[2] - rhs._v[2]*_v[1],
                 rhs._v[3]*_v[1] - rhs._v[0]*_v[2] + rhs._v[1]*_v[3] + rhs._v[2]*_v[0],
                 rhs._v[3]*_v[2] + rhs._v[0]*_v[1] - rhs._v[1]*_v[0] + rhs._v[2]*_v[3],
                 rhs._v[3]*_v[3] - rhs._v[0]*_v[0] - rhs._v[1]*_v[1] - rhs._v[2]*_v[2] );
        }

        // 一元乘法，将两个四元数相称，相当于将两个旋转动作相加
        inline Quat& operator*=(const Quat& rhs)
        {
            value_type x = rhs._v[3]*_v[0] + rhs._v[0]*_v[3] + rhs._v[1]*_v[2] - rhs._v[2]*_v[1];
            value_type y = rhs._v[3]*_v[1] - rhs._v[0]*_v[2] + rhs._v[1]*_v[3] + rhs._v[2]*_v[0];
            value_type z = rhs._v[3]*_v[2] + rhs._v[0]*_v[1] - rhs._v[1]*_v[0] + rhs._v[2]*_v[3];
            _v[3]   = rhs._v[3]*_v[3] - rhs._v[0]*_v[0] - rhs._v[1]*_v[1] - rhs._v[2]*_v[2];

            _v[2] = z;
            _v[1] = y;
            _v[0] = x;

            return (*this);            // 允许嵌套（连乘）
        }


        /// Divide by scalar 
        inline Quat operator / (value_type rhs) const
        {
            value_type div = 1.0/rhs;
            return Quat(_v[0]*div, _v[1]*div, _v[2]*div, _v[3]*div);
        }

        /// Unary divide by scalar 
        inline Quat& operator /= (value_type rhs)
        {
            value_type div = 1.0/rhs;
            _v[0]*=div;
            _v[1]*=div;
            _v[2]*=div;
            _v[3]*=div;
            return *this;
        }

        /// Binary divide 
        inline const Quat operator/(const Quat& denom) const
        {
            return ( (*this) * denom.inverse() );
        }

        /// Unary divide 
        inline Quat& operator/=(const Quat& denom)
        {
            (*this) = (*this) * denom.inverse();
            return (*this);            // enable nesting
        }

        /// Binary addition 
        inline const Quat operator + (const Quat& rhs) const
        {
            return Quat(_v[0]+rhs._v[0], _v[1]+rhs._v[1],
                _v[2]+rhs._v[2], _v[3]+rhs._v[3]);
        }

        /// Unary addition
        inline Quat& operator += (const Quat& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            _v[3] += rhs._v[3];
            return *this;            // enable nesting
        }

        /// Binary subtraction 
        inline const Quat operator - (const Quat& rhs) const
        {
            return Quat(_v[0]-rhs._v[0], _v[1]-rhs._v[1],
                _v[2]-rhs._v[2], _v[3]-rhs._v[3] );
        }

        /// Unary subtraction 
        inline Quat& operator -= (const Quat& rhs)
        {
            _v[0]-=rhs._v[0];
            _v[1]-=rhs._v[1];
            _v[2]-=rhs._v[2];
            _v[3]-=rhs._v[3];
            return *this;            // enable nesting
        }

        /** Negation operator - returns the negative of the quaternion.
        Basically just calls operator - () on the Vec4 */
        inline const Quat operator - () const { return Quat (-_v[0], -_v[1], -_v[2], -_v[3]); }

        // 模（长度）sqrt( vec . vec )
        value_type length() const { return sqrt( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] + _v[3]*_v[3]); }

        // 模的平方 vec . vec
        value_type length2() const { return _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] + _v[3]*_v[3]; }

        // 计算共轭四元数
        inline Quat conj () const  { return Quat( -_v[0], -_v[1], -_v[2], _v[3] ); }

        // 计算转置四元数q^(-1) = q^*/(q.q^*)
        inline const Quat inverse () const  { return conj() / length2(); }

        // 旋转相关的函数

		// 使四元数沿某个向量轴旋转一定的角度，并据此设置四元数
        void makeRotate( value_type angle, value_type x, value_type y, value_type z );
        void makeRotate ( value_type angle, const Vec3f& vec );
        void makeRotate ( value_type angle, const Vec3d& vec );

		// 使四元数沿三个轴各旋转一定的角度，并据此设置四元数。通常三个轴为笛卡尔坐标系的XYZ轴
        void makeRotate ( value_type angle1, const Vec3f& axis1, 
                          value_type angle2, const Vec3f& axis2,
                          value_type angle3, const Vec3f& axis3);
        void makeRotate ( value_type angle1, const Vec3d& axis1, 
                          value_type angle2, const Vec3d& axis2,
                          value_type angle3, const Vec3d& axis3);

        /** Generally take a dot product to get the angle between these and then use a cross product to get the rotation axis
            Watch out for the two special cases when the vectors are co-incident or opposite in direction.*/
		// 使四元数从向量轴1转到向量轴2，并据此设置四元数
        void makeRotate( const Vec3f& vec1, const Vec3f& vec2 );
        void makeRotate( const Vec3d& vec1, const Vec3d& vec2 );
    
        void makeRotate_original( const Vec3d& vec1, const Vec3d& vec2 );

		// 获取四元数包含的旋转动作内容，即它所依据的旋转轴和旋转角。
		// 注意：返回的值和设置的值可能是不一样的，但是其行为结果相同。
        void getRotate ( value_type & angle, value_type & x, value_type & y, value_type & z ) const;
        void getRotate ( value_type & angle, Vec3f& vec ) const;
        void getRotate ( value_type & angle, Vec3d& vec ) const;

		// 插值（是一种空间的、平滑的球面线性插值，t从0到1，四元数从from到to）
        void slerp ( value_type  t, const Quat& from, const Quat& to);
               

		// 通过此四元数旋转一个向量
        Vec3f operator* (const Vec3f& v) const
        {
            // nVidia SDK implementation
            Vec3f uv, uuv; 
            Vec3f qvec(_v[0], _v[1], _v[2]);
            uv = qvec ^ v;
            uuv = qvec ^ uv; 
            uv *= ( 2.0f * _v[3] ); 
            uuv *= 2.0f; 
            return v + uv + uuv;
        }
               
        Vec3d operator* (const Vec3d& v) const
        {
            // nVidia SDK implementation
            Vec3d uv, uuv; 
            Vec3d qvec(_v[0], _v[1], _v[2]);
            uv = qvec ^ v;
            uuv = qvec ^ uv; 
            uv *= ( 2.0f * _v[3] ); 
            uuv *= 2.0f; 
            return v + uv + uuv;
        }
        
    protected:
    
};    // end of class prototype

}    // end of namespace

#endif 
