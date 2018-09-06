#ifndef OSGPARTICLE_PARTICLE
#define OSGPARTICLE_PARTICLE 1

#include <VBF_Engine/VBF_Particle/Export>
#include <VBF_Engine/VBF_Particle/Interpolator>
#include <VBF_Engine/VBF_Particle/range>

#include <VBF_Base/ref_ptr>
#include <Types/Vec3>
#include <Types/Vec4>
#include <Types/VBF_Matrix.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_GL.h>
#include <VBF_Engine/VBF_SceneGraph/GLBeginEndAdapter>

namespace osgParticle
{

     class ParticleSystem;

    /** 粒子，是粒子系统的基本单元。粒子同时具有物理属性和图形属性。它的形状可以是任意的
		点（POINT）、四边形（QUAD）、四边形带（QUAD_TRIPSTRIP）、六角形（HEXAGON）或线（LINE）。
		每个粒子都有自己的生命周期，生命周期为负数的粒子可以存活无限长的时间。所有的粒子都具有
		大小（SIZE）、Alpha值和颜色（COLOR）属性，每一个属性都可以指定其最大最小值，当前值通过
		生存时间在最大最小之间插值得来。t==0时curr_value = min，t==lifeTime时curr_value = max。
		当生命周期为负时，不插值，统一采用最小值
    */
    class OSGPARTICLE_EXPORT Particle 
	{
        friend class ParticleSystem;
    public:
        
        enum
        {
            INVALID_INDEX = -1
        };


        //粒子的形状， LINE 型与FIXED alignment模式结合使用    
        enum Shape 
		{
            POINT,				// 用GL_POINTS作为图元
            QUAD,				// 用GL_QUADS作为图元
            QUAD_TRIANGLESTRIP, // 用GL_TRI_angleSTRIP作为图元，但每个粒子需要glBegin/glEnd对
            HEXAGON,			// may save some filling time, but uses more triangles
            LINE,				// uses GL_LINES to draw line segments that point to the direction of motion   
            USER				// uses a user-defined drawable as primitive
        };
        
        Particle();

        // 设置/获取粒子的形状
        inline Shape getShape() const;
        inline void setShape(Shape s);

        // 粒子是否活着
        inline bool isAlive() const;
        
        // 获取粒子的生命周期 (秒).
        inline double getLifeTime() const;
        
        // 获取粒子的年龄(秒).
        inline double getAge() const;
        
        // 获取Size、Alpha、颜色的最大最小值
        inline const rangef& getSizeRange() const;
        inline const rangef& getAlphaRange() const;
        inline const rangev4& getColorRange() const;
        
		// 获取计算SIZE的插值器
        inline const Interpolator* getSizeInterpolator() const;
        
        // 获取计算ALPHA的插值器
        inline const Interpolator* getAlphaInterpolator() const;
        
        // 获取计算颜色的插值器
        inline const Interpolator* getColorInterpolator() const;

		// 获取粒子的物理半径，为了内建的操作能够正确工作，长度单位必须用米表示
        inline float getRadius() const;
        
 		// 获取粒子的质量(mass)，为了内建的操作能够正确工作，mass单位必须用kg表示
        inline float getMass() const;

        inline float getMassInv() const;
        
        // 获取位置向量
        inline const osg::Vec3& getPosition() const;
  
		// 获取速度向量，为了内建的操作能够正确工作，速度单位必须用米/秒表示
        inline const osg::Vec3& getVelocity() const;        
        
		// 获取前一个位置（上次更新前的位置），上次更新的位置即是当前的位置
        inline const osg::Vec3& getPreviousPosition() const;

        // 获取角度向量
        inline const osg::Vec3& getAngle() const;
        
		// 获取角速度向量
        inline const osg::Vec3& getAngularVelocity() const;
        
        // 获取前一个角度向量
        inline const osg::Vec3& getPreviousAngle() const;
        
        // 获取当前的颜色
        inline const osg::Vec4& getCurrentColor() const { return _current_color; }

        // 获取当前的Alpha
        inline float getCurrentAlpha() const { return _current_alpha; }
        
        // 获取左下角点纹理坐标的s，t坐标
        inline float getSTexCoord() const { return _s_coord; }
        inline float getTTexCoord() const { return _t_coord; }

        // 获取纹理块的宽和高
        inline int getTileS() const;
        inline int getTileT() const;
        
        /// Get number of texture tiles
        inline int getNumTiles() const { return _end_tile - _start_tile + 1; }
        
        // 下次更新时杀死粒子。 注意: 调用该函数后，isAlive()方法仍然返回true，直到粒子被再次更新（update）
        inline void kill();
        
        // 设置粒子的生命周期
        inline void setLifeTime(double t);
        
        // 设置SIZE的最大最小值
        inline void setSizeRange(const rangef& r);
        
        // 设置Alpha的最大最小值
        inline void setAlphaRange(const rangef& r);
        
        // 设置颜色的最大最小值
        inline void setColorRange(const rangev4& r);
        
        // 设置计算粒子SIZE的插值器
		inline void setSizeInterpolator(Interpolator* ri);
        
        // 设置计算粒子Alpha的插值器      
        inline void setAlphaInterpolator(Interpolator* ai);
        
        // 设置计算粒子颜色的插值器
        inline void setColorInterpolator(Interpolator* ci);

        // 设置粒子的物理半径，为了内建的操作能够正确工作，长度单位必须用米表示
        inline void setRadius(float r);
        
        // 设置粒子的质量(mass)，为了内建的操作能够正确工作，mass单位必须用kg表示
        inline void setMass(float m);
        
        // 设置粒子的位置向量
        inline void setPosition(const osg::Vec3& p);
        
        // 设置速度向量，为了内建的操作能够正确工作，速度单位必须用米/秒表示
        inline void setVelocity(const osg::Vec3& v);
        
        // 增加速度向量
        inline void addVelocity(const osg::Vec3& dv);
        
        // 通过矩阵变换速度和位置向量
        inline void transformPositionVelocity(const osg::Matrix& xform);

        /// Transform position and velocity vectors by a combination of two matrices
        void transformPositionVelocity(const osg::Matrix& xform1, const osg::Matrix& xform2, float r);

        // 设置角度向量
        inline void setAngle(const osg::Vec3& a);
        
        /**
          Set the angular velocity vector. 
          Components x, y and z are angles of rotation around the respective axis (in radians).
        */
        inline void setAngularVelocity(const osg::Vec3& v);
        
        /// Add a vector to the angular velocity vector.
        inline void addAngularVelocity(const osg::Vec3& dv);
        
        /// Transform angle and angularVelocity vectors by a matrix.
        inline void transformAngleVelocity(const osg::Matrix& xform);
        
        /** Update the particle (don't call this method manually).
            This method is called automatically by <CODE>ParticleSystem::update()</CODE>; it
            updates the graphical properties of the particle for the current time,
            checks whether the particle is still alive, and then updates its position
            by computing <I>P = P + V * dt</I> (where <I>P</I> is the position and <I>V</I> is the velocity).
        */
        bool update(double dt, bool onlyTimeStamp);

        /// Perform some pre-rendering tasks. Called automatically by particle systems.
        inline void beginRender(osg::GLBeginEndAdapter* gl) const;
        
        /// Render the particle. Called automatically by particle systems.
        void render(osg::GLBeginEndAdapter* gl, const osg::Vec3& xpos, const osg::Vec3& px, const osg::Vec3& py, float scale = 1.0f) const;
        
        /// Render the particle with user-defined drawable
        void render(osg::RenderInfo& renderInfo, const osg::Vec3& xpos, const osg::Vec3& xrot) const;
        
        /// Perform some post-rendering tasks. Called automatically by particle systems.
        inline void endRender(osg::GLBeginEndAdapter* gl) const;
        
        // 获取当前的SIZE (插值的)，第一次调用update()之后才有效
        inline float getCurrentSize() const;
        
        // 指定纹理如何平铺
        /// All tiles in the given range are sequentially displayed during the lifetime
        /// of the particle. When no range is given, all tiles are displayed during the lifetime.
        inline void setTextureTileRange(int sTile, int tTile, int startTile, int endTile);

        // 与上面函数相同，范围从0开始，到end结束
        inline void setTextureTile(int sTile, int tTile, int end = -1);

        // 设置/获取前一个粒子
        inline void setPreviousParticle(int previous) { _previousParticle = previous; }
        inline int getPreviousParticle() const { return _previousParticle; }

        // 设置/获取下一个粒子
        inline void setNextParticle(int next) { _nextParticle = next; }
        inline int getNextParticle() const { return _nextParticle; }
        
        // 设置/获取粒子的深度（depth），用于排序
        inline void setDepth(double d) { _depth = d; }
        inline double getDepth() const { return _depth; }
        
		// 设置/获取用户自定义的粒子drawable
        inline void setDrawable(osg::Drawable* d) { _drawable = d; }
        inline osg::Drawable* getDrawable() const { return _drawable.get(); }
        
        // 排序操作
        bool operator<(const Particle &P) const { return _depth < P._depth; }

        /// Method for initializing a particles texture coords as part of a connected particle system.
        void setUpTexCoordsAsPartOfConnectedParticleSystem(ParticleSystem* ps);
        void SetCount(unsigned int nCount) { m_nCount = nCount; }
        inline unsigned int GetCount() const { return m_nCount; }
    protected:
    
        Shape _shape;

        rangef _sr;
        rangef _ar;
        rangev4 _cr;

        ref_ptr<Interpolator> _si;
        ref_ptr<Interpolator> _ai;
        ref_ptr<Interpolator> _ci;

        bool _mustdie;
        double _lifeTime;

        float _radius;
        float _mass;
        float _massinv;
        osg::Vec3 _prev_pos;
        osg::Vec3 _position;
        osg::Vec3 _velocity;

        osg::Vec3 _prev_angle;
        osg::Vec3 _angle;
        osg::Vec3 _angul_arvel;

        double _t0;        

        float _alive;
        float _current_size;
        float _current_alpha;
        osg::Vec3 _base_prop;  // [0] _alive [1] _current_size [2] _current_alpha
        osg::Vec4 _current_color;
        
        float _s_tile;
        float _t_tile;
        int _start_tile;
        int _end_tile;
        int _cur_tile;
        float _s_coord;
        float _t_coord;
        
        // previous and next Particles are only used in ConnectedParticleSystems
        int _previousParticle;
        int _nextParticle;
        
        // the depth of the particle is used only when sorting is enabled
        double _depth;
        
        // the particle drawable is used only when USER shape is enabled
        ref_ptr<osg::Drawable> _drawable;
        unsigned int m_nCount;
    };

    // INLINE FUNCTIONS

    inline Particle::Shape Particle::getShape() const
    {
        return _shape;
    }

    inline void Particle::setShape(Shape s)
    {
        _shape = s;
    }

    inline bool Particle::isAlive() const
    {
        return _alive>0.0f;
    }

    inline double Particle::getLifeTime() const
    {
        return _lifeTime;
    }
    
    inline double Particle::getAge() const
    {
        return _t0;
    }
    
    inline float Particle::getRadius() const
    {
        return _radius;
    }
    
    inline void Particle::setRadius(float r)
    {
        _radius = r;
    }

    inline const rangef& Particle::getSizeRange() const
    {
        return _sr;
    }

    inline const rangef& Particle::getAlphaRange() const
    {
        return _ar;
    }

    inline const rangev4& Particle::getColorRange() const
    {
        return _cr;
    }

    inline const Interpolator* Particle::getSizeInterpolator() const
    {
        return _si.get();
    }

    inline const Interpolator* Particle::getAlphaInterpolator() const
    {
        return _ai.get();
    }

    inline const Interpolator* Particle::getColorInterpolator() const
    {
        return _ci.get();
    }

    inline const osg::Vec3& Particle::getPosition() const
    {
        return _position;
    }

    inline const osg::Vec3& Particle::getVelocity() const
    {
        return _velocity;
    }
    
    inline const osg::Vec3& Particle::getPreviousPosition() const
    {
        return _prev_pos;
    }

    inline const osg::Vec3& Particle::getAngle() const
    {
        return _angle;
    }
    
    inline const osg::Vec3& Particle::getAngularVelocity() const
    {
        return _angul_arvel;
    }
    
    inline const osg::Vec3& Particle::getPreviousAngle() const
    {
        return _prev_angle;
    }
    
    inline int Particle::getTileS() const
    {
        return (_s_tile>0.0f) ? static_cast<int>(1.0f / _s_tile) : 1;
    }

    inline int Particle::getTileT() const
    {
        return (_t_tile>0.0f) ? static_cast<int>(1.0f / _t_tile) : 1;
    }
    
    inline void Particle::kill()
    {
        _mustdie = true;
    }

    inline void Particle::setLifeTime(double t)
    {
        _lifeTime = t;
    }

    inline void Particle::setSizeRange(const rangef& r)
    {
        _sr = r;
    }

    inline void Particle::setAlphaRange(const rangef& r)
    {
        _ar = r;
    }

    inline void Particle::setColorRange(const rangev4& r)
    {
        _cr = r;
    }

    inline void Particle::setSizeInterpolator(Interpolator* ri)
    {
        _si = ri;
    }

    inline void Particle::setAlphaInterpolator(Interpolator* ai)
    {
        _ai = ai;
    }

    inline void Particle::setColorInterpolator(Interpolator* ci)
    {
        _ci = ci;
    }

    inline void Particle::setPosition(const osg::Vec3& p)
    {
        _position = p;
    }

    inline void Particle::setVelocity(const osg::Vec3& v)
    {
        _velocity = v;
    }

    inline void Particle::addVelocity(const osg::Vec3& dv)
    {
        _velocity += dv;
    }

    inline void Particle::transformPositionVelocity(const osg::Matrix& xform)
    {
        _position = xform.preMult(_position);
        _velocity = osg::Matrix::transform3x3(_velocity, xform);
    }
    
    inline void Particle::transformPositionVelocity(const osg::Matrix& xform1, const osg::Matrix& xform2, float r)
    {
        osg::Vec3 position1 = xform1.preMult(_position);
        osg::Vec3 velocity1 = osg::Matrix::transform3x3(_velocity, xform1);
        osg::Vec3 position2 = xform2.preMult(_position);
        osg::Vec3 velocity2 = osg::Matrix::transform3x3(_velocity, xform2);
        float one_minus_r = 1.0f-r;
        _position = position1*r + position2*one_minus_r;
        _velocity = velocity1*r + velocity2*one_minus_r;
    }
    
    inline void Particle::setAngle(const osg::Vec3& a)
    {
        _angle = a;
    }
    
    inline void Particle::setAngularVelocity(const osg::Vec3& v)
    {
        _angul_arvel = v;
    }
    
    inline void Particle::addAngularVelocity(const osg::Vec3& dv)
    {
        _angul_arvel += dv;
    }
    
    inline void Particle::transformAngleVelocity(const osg::Matrix& xform)
    {
        // this should be optimized!
        
        osg::Vec3 a1 = _angle + _angul_arvel;
        
        _angle = xform.preMult(_angle);
        a1 = xform.preMult(a1);
        
        _angul_arvel = a1 - _angle;
    }
            
    inline float Particle::getMass() const
    {
        return _mass;
    }
    
    inline float Particle::getMassInv() const
    {
        return _massinv;
    }
    
    inline void Particle::setMass(float m)
    {
        _mass = m;
        _massinv = 1 / m;
    }
    
    inline void Particle::beginRender(osg::GLBeginEndAdapter* gl) const
    {
        switch (_shape)
        {
        case POINT:
            gl->Begin(GL_POINTS);
            break;
        case QUAD:
            gl->Begin(GL_QUADS);
            break;
        case LINE:
            gl->Begin(GL_LINES);
            break;
        default: ;
        }
    }

    inline void Particle::endRender(osg::GLBeginEndAdapter* gl) const
    {
        switch (_shape)
        {
        case POINT:
        case QUAD:
        case LINE:
            gl->End();
            break;
        default: ;
        }
    }

    inline float Particle::getCurrentSize() const
    {
        return _current_size;
    }


    inline void Particle::setTextureTile(int sTile, int tTile, int end)
    {
        setTextureTileRange(sTile, tTile, -1, end);
    }

    inline void Particle::setTextureTileRange(int sTile, int tTile, int startTile, int endTile)
    {
       _s_tile = (sTile>0) ? 1.0f / static_cast<float>(sTile) : 1.0f;
       _t_tile = (tTile>0) ? 1.0f / static_cast<float>(tTile) : 1.0f;
       
       if(startTile == -1)
       {
          _start_tile = 0;
       }
       else
       {
          _start_tile = startTile;
       }

       if(endTile == -1)
       {
          _end_tile = sTile * tTile;
       }
       else
       {
          _end_tile = endTile;
       }
    }

}

#endif

