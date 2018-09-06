#ifndef VBF_MATH_MATRIXD
#define VBF_MATH_MATRIXD 1

#include <VBF_Common/VBF_Math/VBF_Export.h>


#include <Types/Vec3d>
#include <Types/Vec4d>
#include <Types/VBF_Quat.h>

namespace osg {

class Matrixf;

class VBF_MATH_EXPORT Matrixd
{
    public:
    
        typedef double value_type; // 数据类型为double

		// 构造函数
        inline Matrixd() { makeIdentity(); }
        inline Matrixd( const Matrixd& mat) { set(mat.ptr()); }
        Matrixd( const Matrixf& mat );
        inline explicit Matrixd( float const * const ptr ) { set(ptr); }
        inline explicit Matrixd( double const * const ptr ) { set(ptr); }
        inline explicit Matrixd( const Quat& quat ) { makeRotate(quat); }

        Matrixd(value_type a00, value_type a01, value_type a02, value_type a03,
                value_type a10, value_type a11, value_type a12, value_type a13,
                value_type a20, value_type a21, value_type a22, value_type a23,
                value_type a30, value_type a31, value_type a32, value_type a33);

        ~Matrixd() {}

		// 逻辑运算
        int compare(const Matrixd& m) const;

        bool operator < (const Matrixd& m) const { return compare(m)<0; }
        bool operator == (const Matrixd& m) const { return compare(m)==0; }
        bool operator != (const Matrixd& m) const { return compare(m)!=0; }

		// 获取矩阵元素
        inline value_type& operator()(int row, int col) { return _mat[row][col]; }
        inline value_type operator()(int row, int col) const { return _mat[row][col]; }

		// 有效性判断
        inline bool valid() const { return !isNaN(); }
        inline bool isNaN() const { return osg::isNaN(_mat[0][0]) || osg::isNaN(_mat[0][1]) || osg::isNaN(_mat[0][2]) || osg::isNaN(_mat[0][3]) ||
                                                 osg::isNaN(_mat[1][0]) || osg::isNaN(_mat[1][1]) || osg::isNaN(_mat[1][2]) || osg::isNaN(_mat[1][3]) ||
                                                 osg::isNaN(_mat[2][0]) || osg::isNaN(_mat[2][1]) || osg::isNaN(_mat[2][2]) || osg::isNaN(_mat[2][3]) ||
                                                 osg::isNaN(_mat[3][0]) || osg::isNaN(_mat[3][1]) || osg::isNaN(_mat[3][2]) || osg::isNaN(_mat[3][3]); }

		// 赋值操作
        inline Matrixd& operator = (const Matrixd& rhs)
        {
            if( &rhs == this ) return *this;
            set(rhs.ptr());
            return *this;
        }
        
        Matrixd& operator = (const Matrixf& other);

        inline void set(const Matrixd& rhs) { set(rhs.ptr()); }

        void set(const Matrixf& rhs);

        inline void set(float const * const ptr)
        {
            value_type* local_ptr = (value_type*)_mat;
            for(int i=0;i<16;++i) local_ptr[i]=(value_type)ptr[i];
        }
        
        inline void set(double const * const ptr)
        {
            value_type* local_ptr = (value_type*)_mat;
            for(int i=0;i<16;++i) local_ptr[i]=(value_type)ptr[i];
        }

        void set(value_type a00, value_type a01, value_type a02,value_type a03,
                 value_type a10, value_type a11, value_type a12,value_type a13,
                 value_type a20, value_type a21, value_type a22,value_type a23,
                 value_type a30, value_type a31, value_type a32,value_type a33);
              

		// 获取矩阵的起始地址指针，在传递给OpenGL函数时十分有用
        value_type * ptr() { return (value_type*)_mat; }
        const value_type * ptr() const { return (const value_type *)_mat; }

		// 判断是否为单位阵
        bool isIdentity() const
        {
            return _mat[0][0]==1.0 && _mat[0][1]==0.0 && _mat[0][2]==0.0 &&  _mat[0][3]==0.0 &&
                   _mat[1][0]==0.0 && _mat[1][1]==1.0 && _mat[1][2]==0.0 &&  _mat[1][3]==0.0 &&
                   _mat[2][0]==0.0 && _mat[2][1]==0.0 && _mat[2][2]==1.0 &&  _mat[2][3]==0.0 &&
                   _mat[3][0]==0.0 && _mat[3][1]==0.0 && _mat[3][2]==0.0 &&  _mat[3][3]==1.0;
        }

		// 设置为单位阵
        void makeIdentity();
        
		// 缩放
        void makeScale( const Vec3f& );
        void makeScale( const Vec3d& );
        void makeScale( value_type, value_type, value_type );
        
        void makeTranslate( const Vec3f& );
        void makeTranslate( const Vec3d& );
        void makeTranslate( value_type, value_type, value_type );
        
		// 旋转
        void makeRotate( const Vec3f& from, const Vec3f& to );
        void makeRotate( const Vec3d& from, const Vec3d& to );
        void makeRotate( value_type angle, const Vec3f& axis );
        void makeRotate( value_type angle, const Vec3d& axis );
        void makeRotate( value_type angle, value_type x, value_type y, value_type z );
        void makeRotate( const Quat& );
        void makeRotate( value_type angle1, const Vec3f& axis1, 
                         value_type angle2, const Vec3f& axis2,
                         value_type angle3, const Vec3f& axis3);
        void makeRotate( value_type angle1, const Vec3d& axis1, 
                         value_type angle2, const Vec3d& axis2,
                         value_type angle3, const Vec3d& axis3);


		// 分解矩阵，获取其平移分量、旋转分量、缩放分量、以及缩放方向分量
        void decompose( osg::Vec3f& translation, osg::Quat& rotation, osg::Vec3f& scale, osg::Quat& so ) const;     
        void decompose( osg::Vec3d& translation, osg::Quat& rotation, osg::Vec3d& scale, osg::Quat& so ) const;

		// 设置正射投影矩阵（详见glOrtho）
        void makeOrtho(double left, double right, double bottom, double top, double zNear,  double zFar);

		// 获取正射投影参数（如果矩阵不是正射投影矩阵，返回无效值）
        bool getOrtho(double& left,double& right, double& bottom, double& top, double& zNear,  double& zFar) const;
		
		// 设置正射投影矩阵（详见glOrtho）
        inline void makeOrtho2D(double left, double right, double bottom, double top)
        {
            makeOrtho(left,right,bottom,top,-1.0,1.0);
        }

		// 设置视景体矩阵（详见glFrustum）
        void makeFrustum(double left, double right, double bottom, double top, double zNear,  double zFar);

        // 获取视景体参数（如果矩阵不是视景体矩阵，返回无效值）
        bool getFrustum(double& left,   double& right, double& bottom, double& top, double& zNear,  double& zFar) const;

		// 设置对称的透视投影矩阵（详见gluPerspective） 方向比（aspectRatio）为width/height
        void makePerspective(double fovy,  double aspectRatio, double zNear, double zFar);


		// 获取对称的透视投影矩阵参数（如果矩阵不是透视投影矩阵，返回false，参数值为定义）
		// 如果矩阵不是对称的透视投影矩阵，则斜切变换丢失
		// 不对称的矩阵被stereo、power walls、caves和 reality center display所使用，此时，使用AsFrustum
		bool getPerspective(double& fovy,  double& aspectRatio, double& zNear, double& zFar) const;

		// 给观察矩阵（视口变换矩阵（view matrix））设置位置和方向，使用与gluLookAt一致的约定
        void makeLookAt(const Vec3d& eye,const Vec3d& center,const Vec3d& up);

		// 从模型视口（modelview）矩阵，获取 位置和方向，使用与gluLookAt一致的约定
        void getLookAt(Vec3f& eye,Vec3f& center,Vec3f& up, value_type lookDistance=1.0f) const;
        void getLookAt(Vec3d& eye,Vec3d& center,Vec3d& up, value_type lookDistance=1.0f) const;

		// 生成逆矩阵并传递给当前矩阵，自动选择invert_4x3或invert_4x4
        inline bool invert( const Matrixd& rhs)
        {
            bool is_4x3 = (rhs._mat[0][3]==0.0 && rhs._mat[1][3]==0.0 &&  rhs._mat[2][3]==0.0 && rhs._mat[3][3]==1.0);
            return is_4x3 ? invert_4x3(rhs) :  invert_4x4(rhs);
        }

        /** 4x3 matrix invert, not right hand column is assumed to be 0,0,0,1. */
        bool invert_4x3( const Matrixd& rhs);

        /** full 4x4 matrix invert. */
        bool invert_4x4( const Matrixd& rhs);

        /** ortho-normalize the 3x3 rotation & scale matrix */ 
        void orthoNormalize(const Matrixd& rhs); 

		// 创建新矩阵的剧基本工具函数
        inline static Matrixd identity( void );
        inline static Matrixd scale( const Vec3f& sv);
        inline static Matrixd scale( const Vec3d& sv);
        inline static Matrixd scale( value_type sx, value_type sy, value_type sz);
        inline static Matrixd translate( const Vec3f& dv);
        inline static Matrixd translate( const Vec3d& dv);
        inline static Matrixd translate( value_type x, value_type y, value_type z);
        inline static Matrixd rotate( const Vec3f& from, const Vec3f& to);
        inline static Matrixd rotate( const Vec3d& from, const Vec3d& to);
        inline static Matrixd rotate( value_type angle, value_type x, value_type y, value_type z);
        inline static Matrixd rotate( value_type angle, const Vec3f& axis);
        inline static Matrixd rotate( value_type angle, const Vec3d& axis);
        inline static Matrixd rotate( value_type angle1, const Vec3f& axis1, 
                                      value_type angle2, const Vec3f& axis2,
                                      value_type angle3, const Vec3f& axis3);
        inline static Matrixd rotate( value_type angle1, const Vec3d& axis1, 
                                      value_type angle2, const Vec3d& axis2,
                                      value_type angle3, const Vec3d& axis3);
        inline static Matrixd rotate( const Quat& quat);
        inline static Matrixd inverse( const Matrixd& matrix);
        inline static Matrixd orthoNormal(const Matrixd& matrix); 
        /** Create an orthographic projection matrix.
          * See glOrtho for further details.
        */
        inline static Matrixd ortho(double left,   double right,
                                    double bottom, double top,
                                    double zNear,  double zFar);

        /** Create a 2D orthographic projection.
          * See glOrtho for further details.
        */
        inline static Matrixd ortho2D(double left,   double right,
                                      double bottom, double top);

        /** Create a perspective projection.
          * See glFrustum for further details.
        */
        inline static Matrixd frustum(double left,   double right,
                                      double bottom, double top,
                                      double zNear,  double zFar);

        /** Create a symmetrical perspective projection.
          * See gluPerspective for further details.
          * Aspect ratio is defined as width/height.
        */
        inline static Matrixd perspective(double fovy,  double aspectRatio,
                                          double zNear, double zFar);

        /** Create the position and orientation as per a camera,
          * using the same convention as gluLookAt.
        */
        inline static Matrixd lookAt(const Vec3f& eye,
                                     const Vec3f& center,
                                     const Vec3f& up);

        /** Create the position and orientation as per a camera,
          * using the same convention as gluLookAt.
        */
        inline static Matrixd lookAt(const Vec3d& eye,
                                     const Vec3d& center,
                                     const Vec3d& up);

        inline Vec3f preMult( const Vec3f& v ) const;
        inline Vec3d preMult( const Vec3d& v ) const;
        inline Vec3f postMult( const Vec3f& v ) const;
        inline Vec3d postMult( const Vec3d& v ) const;
        inline Vec3f operator* ( const Vec3f& v ) const;
        inline Vec3d operator* ( const Vec3d& v ) const;
        inline Vec4f preMult( const Vec4f& v ) const;
        inline Vec4d preMult( const Vec4d& v ) const;
        inline Vec4f postMult( const Vec4f& v ) const;
        inline Vec4d postMult( const Vec4d& v ) const;
        inline Vec4f operator* ( const Vec4f& v ) const;
        inline Vec4d operator* ( const Vec4d& v ) const;

        void setRotate(const Quat& q);
        /** Get the matrix rotation as a Quat. Note that this function
          * assumes a non-scaled matrix and will return incorrect results
          * for scaled matrixces. Consider decompose() instead.
          */
        Quat getRotate() const;

        void setTrans( value_type tx, value_type ty, value_type tz );
        void setTrans( const Vec3f& v );
        void setTrans( const Vec3d& v );
        
        inline Vec3d getTrans() const { return Vec3d(_mat[3][0],_mat[3][1],_mat[3][2]); } 
        
        inline Vec3d getScale() const {
          Vec3d x_vec(_mat[0][0],_mat[1][0],_mat[2][0]); 
          Vec3d y_vec(_mat[0][1],_mat[1][1],_mat[2][1]); 
          Vec3d z_vec(_mat[0][2],_mat[1][2],_mat[2][2]); 
          return Vec3d(x_vec.length(), y_vec.length(), z_vec.length()); 
        }
        
        /** apply a 3x3 transform of v*M[0..2,0..2]. */
        inline static Vec3f transform3x3(const Vec3f& v,const Matrixd& m);

        /** apply a 3x3 transform of v*M[0..2,0..2]. */
        inline static Vec3d transform3x3(const Vec3d& v,const Matrixd& m);

        /** apply a 3x3 transform of M[0..2,0..2]*v. */
        inline static Vec3f transform3x3(const Matrixd& m,const Vec3f& v);

        /** apply a 3x3 transform of M[0..2,0..2]*v. */
        inline static Vec3d transform3x3(const Matrixd& m,const Vec3d& v);

        // basic Matrixd multiplication, our workhorse methods.
        void mult( const Matrixd&, const Matrixd& );
        void preMult( const Matrixd& );
        void postMult( const Matrixd& );

        /** Optimized version of preMult(translate(v)); */
        inline void preMultTranslate( const Vec3d& v );
        inline void preMultTranslate( const Vec3f& v );
        /** Optimized version of postMult(translate(v)); */
        inline void postMultTranslate( const Vec3d& v );
        inline void postMultTranslate( const Vec3f& v );

        /** Optimized version of preMult(scale(v)); */
        inline void preMultScale( const Vec3d& v );
        inline void preMultScale( const Vec3f& v );
        /** Optimized version of postMult(scale(v)); */
        inline void postMultScale( const Vec3d& v );
        inline void postMultScale( const Vec3f& v );

        /** Optimized version of preMult(rotate(q)); */
        inline void preMultRotate( const Quat& q );
        /** Optimized version of postMult(rotate(q)); */
        inline void postMultRotate( const Quat& q );

        inline void operator *= ( const Matrixd& other ) 
        {    if( this == &other ) {
                Matrixd temp(other);
                postMult( temp );
            }
            else postMult( other ); 
        }

        inline Matrixd operator * ( const Matrixd &m ) const
        {
            osg::Matrixd r;
            r.mult(*this,m);
            return  r;
        }

    protected:
        value_type _mat[4][4];

};


// static utility methods
inline Matrixd Matrixd::identity(void)
{
    Matrixd m;
    m.makeIdentity();
    return m;
}

inline Matrixd Matrixd::scale(value_type sx, value_type sy, value_type sz)
{
    Matrixd m;
    m.makeScale(sx,sy,sz);
    return m;
}

inline Matrixd Matrixd::scale(const Vec3f& v )
{
    return scale(v.x(), v.y(), v.z() );
}

inline Matrixd Matrixd::scale(const Vec3d& v )
{
    return scale(v.x(), v.y(), v.z() );
}

inline Matrixd Matrixd::translate(value_type tx, value_type ty, value_type tz)
{
    Matrixd m;
    m.makeTranslate(tx,ty,tz);
    return m;
}

inline Matrixd Matrixd::translate(const Vec3f& v )
{
    return translate(v.x(), v.y(), v.z() );
}

inline Matrixd Matrixd::translate(const Vec3d& v )
{
    return translate(v.x(), v.y(), v.z() );
}

inline Matrixd Matrixd::rotate( const Quat& q )
{
    return Matrixd(q);
}
inline Matrixd Matrixd::rotate(value_type angle, value_type x, value_type y, value_type z )
{
    Matrixd m;
    m.makeRotate(angle,x,y,z);
    return m;
}
inline Matrixd Matrixd::rotate(value_type angle, const Vec3f& axis )
{
    Matrixd m;
    m.makeRotate(angle,axis);
    return m;
}
inline Matrixd Matrixd::rotate(value_type angle, const Vec3d& axis )
{
    Matrixd m;
    m.makeRotate(angle,axis);
    return m;
}
inline Matrixd Matrixd::rotate( value_type angle1, const Vec3f& axis1, 
                                value_type angle2, const Vec3f& axis2,
                                value_type angle3, const Vec3f& axis3)
{
    Matrixd m;
    m.makeRotate(angle1,axis1,angle2,axis2,angle3,axis3);
    return m;
}
inline Matrixd Matrixd::rotate( value_type angle1, const Vec3d& axis1, 
                                value_type angle2, const Vec3d& axis2,
                                value_type angle3, const Vec3d& axis3)
{
    Matrixd m;
    m.makeRotate(angle1,axis1,angle2,axis2,angle3,axis3);
    return m;
}
inline Matrixd Matrixd::rotate(const Vec3f& from, const Vec3f& to )
{
    Matrixd m;
    m.makeRotate(from,to);
    return m;
}
inline Matrixd Matrixd::rotate(const Vec3d& from, const Vec3d& to )
{
    Matrixd m;
    m.makeRotate(from,to);
    return m;
}

inline Matrixd Matrixd::inverse( const Matrixd& matrix)
{
    Matrixd m;
    m.invert(matrix);
    return m;
}

inline Matrixd Matrixd::orthoNormal(const Matrixd& matrix)
{
  Matrixd m;
  m.orthoNormalize(matrix);
  return m; 
}

inline Matrixd Matrixd::ortho(double left,   double right,
                              double bottom, double top,
                              double zNear,  double zFar)
{
    Matrixd m;
    m.makeOrtho(left,right,bottom,top,zNear,zFar);
    return m;
}

inline Matrixd Matrixd::ortho2D(double left,   double right,
                                double bottom, double top)
{
    Matrixd m;
    m.makeOrtho2D(left,right,bottom,top);
    return m;
}

inline Matrixd Matrixd::frustum(double left,   double right,
                                double bottom, double top,
                                double zNear,  double zFar)
{
    Matrixd m;
    m.makeFrustum(left,right,bottom,top,zNear,zFar);
    return m;
}

inline Matrixd Matrixd::perspective(double fovy,  double aspectRatio,
                                    double zNear, double zFar)
{
    Matrixd m;
    m.makePerspective(fovy,aspectRatio,zNear,zFar);
    return m;
}

inline Matrixd Matrixd::lookAt(const Vec3f& eye,
                               const Vec3f& center,
                               const Vec3f& up)
{
    Matrixd m;
    m.makeLookAt(eye,center,up);
    return m;
}

inline Matrixd Matrixd::lookAt(const Vec3d& eye,
                               const Vec3d& center,
                               const Vec3d& up)
{
    Matrixd m;
    m.makeLookAt(eye,center,up);
    return m;
}

inline Vec3f Matrixd::postMult( const Vec3f& v ) const
{
    value_type d = 1.0f/(_mat[3][0]*v.x()+_mat[3][1]*v.y()+_mat[3][2]*v.z()+_mat[3][3]) ;
    return Vec3f( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3])*d,
        (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3])*d,
        (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3])*d) ;
}

inline Vec3d Matrixd::postMult( const Vec3d& v ) const
{
    value_type d = 1.0f/(_mat[3][0]*v.x()+_mat[3][1]*v.y()+_mat[3][2]*v.z()+_mat[3][3]) ;
    return Vec3d( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3])*d,
        (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3])*d,
        (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3])*d) ;
}

inline Vec3f Matrixd::preMult( const Vec3f& v ) const
{
    value_type d = 1.0f/(_mat[0][3]*v.x()+_mat[1][3]*v.y()+_mat[2][3]*v.z()+_mat[3][3]) ;
    return Vec3f( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0])*d,
        (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1])*d,
        (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2])*d);
}

inline Vec3d Matrixd::preMult( const Vec3d& v ) const
{
    value_type d = 1.0f/(_mat[0][3]*v.x()+_mat[1][3]*v.y()+_mat[2][3]*v.z()+_mat[3][3]) ;
    return Vec3d( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0])*d,
        (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1])*d,
        (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2])*d);
}

inline Vec4f Matrixd::postMult( const Vec4f& v ) const
{
    return Vec4f( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3]*v.w()),
        (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3]*v.w()),
        (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3]*v.w()),
        (_mat[3][0]*v.x() + _mat[3][1]*v.y() + _mat[3][2]*v.z() + _mat[3][3]*v.w())) ;
}
inline Vec4d Matrixd::postMult( const Vec4d& v ) const
{
    return Vec4d( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3]*v.w()),
        (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3]*v.w()),
        (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3]*v.w()),
        (_mat[3][0]*v.x() + _mat[3][1]*v.y() + _mat[3][2]*v.z() + _mat[3][3]*v.w())) ;
}

inline Vec4f Matrixd::preMult( const Vec4f& v ) const
{
    return Vec4f( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0]*v.w()),
        (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1]*v.w()),
        (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2]*v.w()),
        (_mat[0][3]*v.x() + _mat[1][3]*v.y() + _mat[2][3]*v.z() + _mat[3][3]*v.w()));
}

inline Vec4d Matrixd::preMult( const Vec4d& v ) const
{
    return Vec4d( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0]*v.w()),
        (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1]*v.w()),
        (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2]*v.w()),
        (_mat[0][3]*v.x() + _mat[1][3]*v.y() + _mat[2][3]*v.z() + _mat[3][3]*v.w()));
}

inline Vec3f Matrixd::transform3x3(const Vec3f& v,const Matrixd& m)
{
    return Vec3f( (m._mat[0][0]*v.x() + m._mat[1][0]*v.y() + m._mat[2][0]*v.z()),
                 (m._mat[0][1]*v.x() + m._mat[1][1]*v.y() + m._mat[2][1]*v.z()),
                 (m._mat[0][2]*v.x() + m._mat[1][2]*v.y() + m._mat[2][2]*v.z()));
}
inline Vec3d Matrixd::transform3x3(const Vec3d& v,const Matrixd& m)
{
    return Vec3d( (m._mat[0][0]*v.x() + m._mat[1][0]*v.y() + m._mat[2][0]*v.z()),
                 (m._mat[0][1]*v.x() + m._mat[1][1]*v.y() + m._mat[2][1]*v.z()),
                 (m._mat[0][2]*v.x() + m._mat[1][2]*v.y() + m._mat[2][2]*v.z()));
}

inline Vec3f Matrixd::transform3x3(const Matrixd& m,const Vec3f& v)
{
    return Vec3f( (m._mat[0][0]*v.x() + m._mat[0][1]*v.y() + m._mat[0][2]*v.z()),
                 (m._mat[1][0]*v.x() + m._mat[1][1]*v.y() + m._mat[1][2]*v.z()),
                 (m._mat[2][0]*v.x() + m._mat[2][1]*v.y() + m._mat[2][2]*v.z()) ) ;
}
inline Vec3d Matrixd::transform3x3(const Matrixd& m,const Vec3d& v)
{
    return Vec3d( (m._mat[0][0]*v.x() + m._mat[0][1]*v.y() + m._mat[0][2]*v.z()),
                 (m._mat[1][0]*v.x() + m._mat[1][1]*v.y() + m._mat[1][2]*v.z()),
                 (m._mat[2][0]*v.x() + m._mat[2][1]*v.y() + m._mat[2][2]*v.z()) ) ;
}

inline void Matrixd::preMultTranslate( const Vec3d& v )
{
    for (unsigned i = 0; i < 3; ++i)
    {
        double tmp = v[i];
        if (tmp == 0)
            continue;
        _mat[3][0] += tmp*_mat[i][0];
        _mat[3][1] += tmp*_mat[i][1];
        _mat[3][2] += tmp*_mat[i][2];
        _mat[3][3] += tmp*_mat[i][3];
    }
}

inline void Matrixd::preMultTranslate( const Vec3f& v )
{
    for (unsigned i = 0; i < 3; ++i)
    {
        float tmp = v[i];
        if (tmp == 0)
            continue;
        _mat[3][0] += tmp*_mat[i][0];
        _mat[3][1] += tmp*_mat[i][1];
        _mat[3][2] += tmp*_mat[i][2];
        _mat[3][3] += tmp*_mat[i][3];
    }
}

inline void Matrixd::postMultTranslate( const Vec3d& v )
{
    for (unsigned i = 0; i < 3; ++i)
    {
        double tmp = v[i];
        if (tmp == 0)
            continue;
        _mat[0][i] += tmp*_mat[0][3];
        _mat[1][i] += tmp*_mat[1][3];
        _mat[2][i] += tmp*_mat[2][3];
        _mat[3][i] += tmp*_mat[3][3];
    }
}

inline void Matrixd::postMultTranslate( const Vec3f& v )
{
    for (unsigned i = 0; i < 3; ++i)
    {
        float tmp = v[i];
        if (tmp == 0)
            continue;
        _mat[0][i] += tmp*_mat[0][3];
        _mat[1][i] += tmp*_mat[1][3];
        _mat[2][i] += tmp*_mat[2][3];
        _mat[3][i] += tmp*_mat[3][3];
    }
}

inline void Matrixd::preMultScale( const Vec3d& v )
{
    _mat[0][0] *= v[0]; _mat[0][1] *= v[0]; _mat[0][2] *= v[0]; _mat[0][3] *= v[0];
    _mat[1][0] *= v[1]; _mat[1][1] *= v[1]; _mat[1][2] *= v[1]; _mat[1][3] *= v[1];
    _mat[2][0] *= v[2]; _mat[2][1] *= v[2]; _mat[2][2] *= v[2]; _mat[2][3] *= v[2];
}

inline void Matrixd::preMultScale( const Vec3f& v )
{
    _mat[0][0] *= v[0]; _mat[0][1] *= v[0]; _mat[0][2] *= v[0]; _mat[0][3] *= v[0];
    _mat[1][0] *= v[1]; _mat[1][1] *= v[1]; _mat[1][2] *= v[1]; _mat[1][3] *= v[1];
    _mat[2][0] *= v[2]; _mat[2][1] *= v[2]; _mat[2][2] *= v[2]; _mat[2][3] *= v[2];
}

inline void Matrixd::postMultScale( const Vec3d& v )
{
    _mat[0][0] *= v[0]; _mat[1][0] *= v[0]; _mat[2][0] *= v[0]; _mat[3][0] *= v[0];
    _mat[0][1] *= v[1]; _mat[1][1] *= v[1]; _mat[2][1] *= v[1]; _mat[3][1] *= v[1];
    _mat[0][2] *= v[2]; _mat[1][2] *= v[2]; _mat[2][2] *= v[2]; _mat[3][2] *= v[2];
}

inline void Matrixd::postMultScale( const Vec3f& v )
{
    _mat[0][0] *= v[0]; _mat[1][0] *= v[0]; _mat[2][0] *= v[0]; _mat[3][0] *= v[0];
    _mat[0][1] *= v[1]; _mat[1][1] *= v[1]; _mat[2][1] *= v[1]; _mat[3][1] *= v[1];
    _mat[0][2] *= v[2]; _mat[1][2] *= v[2]; _mat[2][2] *= v[2]; _mat[3][2] *= v[2];
}

inline void Matrixd::preMultRotate( const Quat& q )
{
    if (q.zeroRotation())
        return;
    Matrixd r;
    r.setRotate(q);
    preMult(r);
}

inline void Matrixd::postMultRotate( const Quat& q )
{
    if (q.zeroRotation())
        return;
    Matrixd r;
    r.setRotate(q);
    postMult(r);
}

inline Vec3f operator* (const Vec3f& v, const Matrixd& m )
{
    return m.preMult(v);
}

inline Vec3d operator* (const Vec3d& v, const Matrixd& m )
{
    return m.preMult(v);
}

inline Vec4f operator* (const Vec4f& v, const Matrixd& m )
{
    return m.preMult(v);
}

inline Vec4d operator* (const Vec4d& v, const Matrixd& m )
{
    return m.preMult(v);
}

inline Vec3f Matrixd::operator* (const Vec3f& v) const
{
    return postMult(v);
}

inline Vec3d Matrixd::operator* (const Vec3d& v) const
{
    return postMult(v);
}

inline Vec4f Matrixd::operator* (const Vec4f& v) const
{
    return postMult(v);
}

inline Vec4d Matrixd::operator* (const Vec4d& v) const
{
    return postMult(v);
}


} //namespace osg


#endif
