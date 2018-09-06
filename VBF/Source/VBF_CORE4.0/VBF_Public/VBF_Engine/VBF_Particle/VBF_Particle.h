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

    /** ���ӣ�������ϵͳ�Ļ�����Ԫ������ͬʱ�����������Ժ�ͼ�����ԡ�������״�����������
		�㣨POINT�����ı��Σ�QUAD�����ı��δ���QUAD_TRIPSTRIP���������Σ�HEXAGON�����ߣ�LINE����
		ÿ�����Ӷ����Լ����������ڣ���������Ϊ���������ӿ��Դ�����޳���ʱ�䡣���е����Ӷ�����
		��С��SIZE����Alphaֵ����ɫ��COLOR�����ԣ�ÿһ�����Զ�����ָ���������Сֵ����ǰֵͨ��
		����ʱ���������С֮���ֵ������t==0ʱcurr_value = min��t==lifeTimeʱcurr_value = max��
		����������Ϊ��ʱ������ֵ��ͳһ������Сֵ
    */
    class OSGPARTICLE_EXPORT Particle 
	{
        friend class ParticleSystem;
    public:
        
        enum
        {
            INVALID_INDEX = -1
        };


        //���ӵ���״�� LINE ����FIXED alignmentģʽ���ʹ��    
        enum Shape 
		{
            POINT,				// ��GL_POINTS��ΪͼԪ
            QUAD,				// ��GL_QUADS��ΪͼԪ
            QUAD_TRIANGLESTRIP, // ��GL_TRI_angleSTRIP��ΪͼԪ����ÿ��������ҪglBegin/glEnd��
            HEXAGON,			// may save some filling time, but uses more triangles
            LINE,				// uses GL_LINES to draw line segments that point to the direction of motion   
            USER				// uses a user-defined drawable as primitive
        };
        
        Particle();

        // ����/��ȡ���ӵ���״
        inline Shape getShape() const;
        inline void setShape(Shape s);

        // �����Ƿ����
        inline bool isAlive() const;
        
        // ��ȡ���ӵ��������� (��).
        inline double getLifeTime() const;
        
        // ��ȡ���ӵ�����(��).
        inline double getAge() const;
        
        // ��ȡSize��Alpha����ɫ�������Сֵ
        inline const rangef& getSizeRange() const;
        inline const rangef& getAlphaRange() const;
        inline const rangev4& getColorRange() const;
        
		// ��ȡ����SIZE�Ĳ�ֵ��
        inline const Interpolator* getSizeInterpolator() const;
        
        // ��ȡ����ALPHA�Ĳ�ֵ��
        inline const Interpolator* getAlphaInterpolator() const;
        
        // ��ȡ������ɫ�Ĳ�ֵ��
        inline const Interpolator* getColorInterpolator() const;

		// ��ȡ���ӵ�����뾶��Ϊ���ڽ��Ĳ����ܹ���ȷ���������ȵ�λ�������ױ�ʾ
        inline float getRadius() const;
        
 		// ��ȡ���ӵ�����(mass)��Ϊ���ڽ��Ĳ����ܹ���ȷ������mass��λ������kg��ʾ
        inline float getMass() const;

        inline float getMassInv() const;
        
        // ��ȡλ������
        inline const osg::Vec3& getPosition() const;
  
		// ��ȡ�ٶ�������Ϊ���ڽ��Ĳ����ܹ���ȷ�������ٶȵ�λ��������/���ʾ
        inline const osg::Vec3& getVelocity() const;        
        
		// ��ȡǰһ��λ�ã��ϴθ���ǰ��λ�ã����ϴθ��µ�λ�ü��ǵ�ǰ��λ��
        inline const osg::Vec3& getPreviousPosition() const;

        // ��ȡ�Ƕ�����
        inline const osg::Vec3& getAngle() const;
        
		// ��ȡ���ٶ�����
        inline const osg::Vec3& getAngularVelocity() const;
        
        // ��ȡǰһ���Ƕ�����
        inline const osg::Vec3& getPreviousAngle() const;
        
        // ��ȡ��ǰ����ɫ
        inline const osg::Vec4& getCurrentColor() const { return _current_color; }

        // ��ȡ��ǰ��Alpha
        inline float getCurrentAlpha() const { return _current_alpha; }
        
        // ��ȡ���½ǵ����������s��t����
        inline float getSTexCoord() const { return _s_coord; }
        inline float getTTexCoord() const { return _t_coord; }

        // ��ȡ�����Ŀ�͸�
        inline int getTileS() const;
        inline int getTileT() const;
        
        /// Get number of texture tiles
        inline int getNumTiles() const { return _end_tile - _start_tile + 1; }
        
        // �´θ���ʱɱ�����ӡ� ע��: ���øú�����isAlive()������Ȼ����true��ֱ�����ӱ��ٴθ��£�update��
        inline void kill();
        
        // �������ӵ���������
        inline void setLifeTime(double t);
        
        // ����SIZE�������Сֵ
        inline void setSizeRange(const rangef& r);
        
        // ����Alpha�������Сֵ
        inline void setAlphaRange(const rangef& r);
        
        // ������ɫ�������Сֵ
        inline void setColorRange(const rangev4& r);
        
        // ���ü�������SIZE�Ĳ�ֵ��
		inline void setSizeInterpolator(Interpolator* ri);
        
        // ���ü�������Alpha�Ĳ�ֵ��      
        inline void setAlphaInterpolator(Interpolator* ai);
        
        // ���ü���������ɫ�Ĳ�ֵ��
        inline void setColorInterpolator(Interpolator* ci);

        // �������ӵ�����뾶��Ϊ���ڽ��Ĳ����ܹ���ȷ���������ȵ�λ�������ױ�ʾ
        inline void setRadius(float r);
        
        // �������ӵ�����(mass)��Ϊ���ڽ��Ĳ����ܹ���ȷ������mass��λ������kg��ʾ
        inline void setMass(float m);
        
        // �������ӵ�λ������
        inline void setPosition(const osg::Vec3& p);
        
        // �����ٶ�������Ϊ���ڽ��Ĳ����ܹ���ȷ�������ٶȵ�λ��������/���ʾ
        inline void setVelocity(const osg::Vec3& v);
        
        // �����ٶ�����
        inline void addVelocity(const osg::Vec3& dv);
        
        // ͨ������任�ٶȺ�λ������
        inline void transformPositionVelocity(const osg::Matrix& xform);

        /// Transform position and velocity vectors by a combination of two matrices
        void transformPositionVelocity(const osg::Matrix& xform1, const osg::Matrix& xform2, float r);

        // ���ýǶ�����
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
        
        // ��ȡ��ǰ��SIZE (��ֵ��)����һ�ε���update()֮�����Ч
        inline float getCurrentSize() const;
        
        // ָ���������ƽ��
        /// All tiles in the given range are sequentially displayed during the lifetime
        /// of the particle. When no range is given, all tiles are displayed during the lifetime.
        inline void setTextureTileRange(int sTile, int tTile, int startTile, int endTile);

        // �����溯����ͬ����Χ��0��ʼ����end����
        inline void setTextureTile(int sTile, int tTile, int end = -1);

        // ����/��ȡǰһ������
        inline void setPreviousParticle(int previous) { _previousParticle = previous; }
        inline int getPreviousParticle() const { return _previousParticle; }

        // ����/��ȡ��һ������
        inline void setNextParticle(int next) { _nextParticle = next; }
        inline int getNextParticle() const { return _nextParticle; }
        
        // ����/��ȡ���ӵ���ȣ�depth������������
        inline void setDepth(double d) { _depth = d; }
        inline double getDepth() const { return _depth; }
        
		// ����/��ȡ�û��Զ��������drawable
        inline void setDrawable(osg::Drawable* d) { _drawable = d; }
        inline osg::Drawable* getDrawable() const { return _drawable.get(); }
        
        // �������
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

