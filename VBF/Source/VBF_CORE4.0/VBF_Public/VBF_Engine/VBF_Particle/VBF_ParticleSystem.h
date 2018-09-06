#ifndef OSGPARTICLE_PARTICLESYSTEM
#define OSGPARTICLE_PARTICLESYSTEM 1

#include <VBF_Engine/VBF_Particle/Export>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>

#include <vector>
#include <stack>
#include <algorithm>
#include <string>

#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SceneGraph/VBFO_SGDrawable.h>
#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_StateMachine.h>
#include <Types/Vec3>
#include <Types/VBF_BoundingBox.h>

// 2009.2.9 �ر�ʹ��ReadWriteMutex��OSGPARTICLE_USE_ReadWriteMutex���ܵ����߳�����due to threading problems in OpenThreads::ReadWriteMutex.
// #define OSGPARTICLE_USE_ReadWriteMutex

#ifdef OSGPARTICLE_USE_ReadWriteMutex
    #include <OpenThreads/ReadWriteMutex>
#else
    #include <OpenThreads/Mutex>
    #include <OpenThreads/ScopedLock>
#endif

namespace osgParticle
{
	// �ÿ�ĺ����࣬ά��������һϵ�����ӵ����ɡ����¡���Ⱦ�����١���������Drawable���ơ�
    // ����������Emitter��ɣ����������˶�Program��ɣ�ɸѡ������Updater���
    class OSGPARTICLE_EXPORT ParticleSystem: public osg::Drawable 
	{
    public:
    
        enum Alignment 
		{
            BILLBOARD,
            FIXED
        };

        ParticleSystem();
        ParticleSystem(const ParticleSystem& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Object(osgParticle, ParticleSystem);
        
		// ��ȡ/�������ӵ�Alignment����
        inline Alignment getParticleAlignment() const;
        inline void setParticleAlignment(Alignment a);
        
        // ��ȡ/����X-axis��Alignment����
        inline const osg::Vec3& getAlignVectorX() const;
        inline void setAlignVectorX(const osg::Vec3& v);

        // ��ȡ/����Y-axis��Alignment����
        inline const osg::Vec3& getAlignVectorY() const;
        inline void setAlignVectorY(const osg::Vec3& v);
        
		// ����Alignment����
        inline void setAlignVectors(const osg::Vec3& X, const osg::Vec3& Y);



        enum ParticleScaleReferenceFrame
        {
            LOCAL_COORDINATES,
            WORLD_COORDINATES
        };

 		// ����/��ȡ�Ǹ�����������ϵ���Ǿֲ�����ϵ��������
        void setParticleScaleReferenceFrame(ParticleScaleReferenceFrame rf) { _particleScaleReferenceFrame = rf; }
        ParticleScaleReferenceFrame getParticleScaleReferenceFrame() const { return _particleScaleReferenceFrame; }



        // ��ȡ��Χ��
        inline const osg::BoundingBox& getDefaultBoundingBox() const;        

		// ����Ĭ�ϵİ�Χ�У�����ʵ�ʵİ�Χ���޷������������绹û�����ӵ�ʱ��
        inline void setDefaultBoundingBox(const osg::BoundingBox& bbox);

		// ����/��ȡ�Ƿ�ʹ�ö���������Ⱦ���ӡ�ʹ�ö�������ʱ���ܶ�����ᱻ���ԣ�����״���Ƿ�����Ӿ����
		// ��ˣ���Ⱦ��Ч�������ã���glBegin/glEnd�ٶȿ죩��
        // ����GLSL��ɫ�����ʹ�ö�������, ��ʱ�����ӵĲ���������Ϊuniforms�� �÷�����setDefaultAttributesUsingShaders()�Զ�����     
		bool getUseVertexArray() const { return _useVertexArray; }
		void setUseVertexArray(bool v) { _useVertexArray = v; }



			
		// ����/��ȡ�Ƿ�ʹ����ɫ����Ⱦ����
        /** Particles' parameters will be used as shader attribute arrays, and necessary variables, including
            the visibility distance, texture, etc, will be used and updated as uniforms.*/		
		bool getUseShaders() const { return _useShaders; }
		void setUseShaders(bool v) { _useShaders = v; _dirty_uniforms = true; }


		// ��ȡ/�����Ƿ�ʹ��double pass��Ⱦ���ӣ�������Ⱦ���Ա�������ϵͳ�Ͳ�͸������֮���overdraw����
		// ������е�����ϵͳ���ڲ�͸������֮����ƣ�����Ҫ������Ⱦ�����Թص�����Ҳ����õ�ѡ��
		// �������setDefaultAttributes������Ĭ�ϵ����ԣ�����ϵͳ��������transparent bin��
		inline bool getDoublePassRendering() const;
		inline void setDoublePassRendering(bool v);

		// ����/��ȡ/�ж�����ϵͳ�Ƿ񱻶��ᣬ����ϵͳ�������emitters��programs��ʲô������
        bool getFrozen() const { return _frozen; }
        inline bool isFrozen() const;
        inline void setFrozen(bool v);

		// ��ȡ�������������������ĺ������ģ�
        inline int numParticles() const;
        
		// ��ȡ������������
        inline int numDeadParticles() const;
  
		// �Ƿ����е����Ӷ�������
        inline bool areAllParticlesDead() const { return numDeadParticles()==numParticles(); }
        
		// ��ȡ��i������
        inline Particle* getParticle(int i);
        inline const Particle* getParticle(int i) const;
        
		// ʹ���ض���ģ�崴��һ��������(��ģ��Ϊnull).
        inline virtual Particle* createParticle(const Particle* ptemplate);
        
        // ���ٵ�i������
        inline virtual void destroyParticle(int i);
        
        // ���õ�i������
        inline virtual void reuseParticle(int i) { _deadparts.push(&(m_vParticles[i])); }

        // ��ȡ��һ��֡��
        inline unsigned int getLastFrameNumber() const;
        
		// ��ȡ���ӷ���͸��µ�ʱ������
        inline double& getDeltaTime( double currentTime );


		// ����/��ȡĬ�ϵ�����ģ��
		inline Particle& getDefaultParticleTemplate();
		inline const Particle& getDefaultParticleTemplate() const;
		inline void setDefaultParticleTemplate(const Particle& p);

		// ����/��ȡɸѡʱ��cull������ϵͳ�Ƿ���Զ��ᣨĬ��Ϊtrue��
        inline bool getFreezeOnCull() const;
        inline void setFreezeOnCull(bool v);
        
 		// ������õ�StateAttribute�����texturefileΪ����ر�����
        void setDefaultAttributes(const std::string& texturefile = "", bool emissive_particles = true, bool lighting = false, int texture_unit = 0);
        
        // ������õ�StateAttribute��ʹ��GLSL��ɫ���������ӡ���ʹ����ɫ��ʱ���û������shapes�����ԡ����texturefileΪ����ر�����
        void setDefaultAttributesUsingShaders(const std::string& texturefile = "", bool emissive_particles = true, int texture_unit = 0);
        
		// ��ȡ/����LODֵ����ֵ�������0�����ӵ���������ֵ�����Ա���ʵ����Ⱦ��������
		inline int GetLOD() const;
		inline void SetLOD(int v);

        enum SortMode
        {
            NO_SORT,			// ����
            SORT_FRONT_TO_BACK,	// ��ǰ����
            SORT_BACK_TO_FRONT	// �Ӻ�ǰ
        };
        

		// ����/��ȡ����ģʽ��ǿ�ƶ����ӵ��б���view coordinates��Z����������������͸����Ⱦ�����ÿ��Ӿ��루setVisibilityDistance)
        inline SortMode getSortMode() const;
        inline void setSortMode(SortMode mode);
  

		// ��ȡ/���ÿ��Ӿ��룬����Ⱦdepth�ڿ��Ӿ����ڵ�����
		// ʹ����ɫ��ʱ�����ԺܺõĹ����� ���򣬱�����������ģʽ��SortMode��Ԥ�ȼ�����ȣ�depth����
		inline double getVisibilityDistance() const;
		inline void setVisibilityDistance(double distance);

        // �������ӣ���Ҫֱ�ӵ��øú���������ʹ��ParticleSystemUpdater��
        virtual void update(double dt, osg::NodeVisitor& nv);

        virtual void drawImplementation(osg::RenderInfo& renderInfo) const;

        virtual osg::BoundingBox computeBound() const;
        
#ifdef OSGPARTICLE_USE_ReadWriteMutex
        typedef OpenThreads::ReadWriteMutex ReadWriterMutex;
        typedef OpenThreads::ScopedReadLock ScopedReadLock;
        typedef OpenThreads::ScopedWriteLock ScopedWriteLock;
#else
        typedef OpenThreads::Mutex ReadWriterMutex;
        typedef OpenThreads::ScopedLock<OpenThreads::Mutex> ScopedReadLock;
        typedef OpenThreads::ScopedLock<OpenThreads::Mutex> ScopedWriteLock;
#endif

        ReadWriterMutex* getReadWriteMutex() const { return &_readWriteMutex; }

    protected:

        virtual ~ParticleSystem();

        ParticleSystem& operator=(const ParticleSystem&) { return *this; }

        inline void update_bounds(const osg::Vec3& p, float r);
        void single_pass_render(osg::RenderInfo& renderInfo, const osg::Matrix& modelview) const;
        void render_vertex_array(osg::RenderInfo& renderInfo) const;

        typedef std::vector<Particle> Particle_vector;
        typedef std::stack<Particle*> Death_stack;

        Particle_vector m_vParticles; // ��¼���е����ӡ�����ʹ�õ���������һ������������ʵ�ֵģ�ÿ�����Ӽ�¼��ǰһ���ͺ�һ�����ӣ�
        Death_stack _deadparts;
        
        osg::BoundingBox _def_bbox;
        
        Alignment _alignment;
        osg::Vec3 _align_X_axis;
        osg::Vec3 _align_Y_axis;
        ParticleScaleReferenceFrame _particleScaleReferenceFrame;
        
        bool _useVertexArray;
        bool _useShaders;
        bool _dirty_uniforms;
        
        bool _doublepass;
        bool _frozen;

        osg::Vec3 _bmin;
        osg::Vec3 _bmax;

        bool _reset_bounds_flag;
        bool _bounds_computed;

        Particle _def_ptemp;
        mutable unsigned int _last_frame;
        mutable bool _dirty_dt;
        bool _freeze_on_cull;
        
        double _t0;
        double _dt;
        
        int _detail;
        SortMode _sortMode;
        double _visibilityDistance;
        
        mutable int _draw_count;
        
        mutable ReadWriterMutex _readWriteMutex;
    };
    
    // INLINE FUNCTIONS
    
    inline ParticleSystem::Alignment ParticleSystem::getParticleAlignment() const
    {
        return _alignment;
    }
    
    inline void ParticleSystem::setParticleAlignment(Alignment a)
    {
        _alignment = a;
    }
    
    inline const osg::Vec3& ParticleSystem::getAlignVectorX() const
    {
        return _align_X_axis;
    }
    
    inline void ParticleSystem::setAlignVectorX(const osg::Vec3& v)
    {
        _align_X_axis = v;
    }

    inline const osg::Vec3& ParticleSystem::getAlignVectorY() const
    {
        return _align_Y_axis;
    }
    
    inline void ParticleSystem::setAlignVectorY(const osg::Vec3& v)
    {
        _align_Y_axis = v;
    }
    
    inline void ParticleSystem::setAlignVectors(const osg::Vec3& X, const osg::Vec3& Y)
    {
        _align_X_axis = X;
        _align_Y_axis = Y;
    }

    inline bool ParticleSystem::isFrozen() const
    {
        return _frozen;
    }
    
    inline void ParticleSystem::setFrozen(bool v)
    {
        _frozen = v;
    }
    
    inline const osg::BoundingBox& ParticleSystem::getDefaultBoundingBox() const
    {
        return _def_bbox;
    }
    
    inline void ParticleSystem::setDefaultBoundingBox(const osg::BoundingBox& bbox)
    {
        _def_bbox = bbox;
    }

    inline bool ParticleSystem::getDoublePassRendering() const
    {
        return _doublepass;
    }

    inline void ParticleSystem::setDoublePassRendering(bool v)
    {
        _doublepass = v;
    }

    inline int ParticleSystem::numParticles() const
    {
        return static_cast<int>(m_vParticles.size());
    }

    inline int ParticleSystem::numDeadParticles() const
    {
        return static_cast<int>(_deadparts.size());
    }

    inline Particle* ParticleSystem::getParticle(int i)
    {
        return &m_vParticles[i];
    }

    inline const Particle* ParticleSystem::getParticle(int i) const
    {
        return &m_vParticles[i];
    }

    inline void ParticleSystem::destroyParticle(int i)
    {
        m_vParticles[i].kill();
    }
    
    inline unsigned int ParticleSystem::getLastFrameNumber() const
    {
        return _last_frame;
    }
    
    inline double& ParticleSystem::getDeltaTime( double currentTime )
    {
        if ( _dirty_dt )
        {
            _dt = currentTime - _t0;
            if ( _dt<0.0 ) _dt = 0.0;
            
            _t0 = currentTime;
            _dirty_dt = false;
        }
        return _dt;
    }

    inline void ParticleSystem::update_bounds(const osg::Vec3& p, float r)
    {
        if (_reset_bounds_flag) {
            _reset_bounds_flag = false;
            _bmin = p - osg::Vec3(r,r,r);
            _bmax = p + osg::Vec3(r,r,r);
        } else {
            if (p.x() - r < _bmin.x()) _bmin.x() = p.x() - r;
            if (p.y() - r < _bmin.y()) _bmin.y() = p.y() - r;
            if (p.z() - r < _bmin.z()) _bmin.z() = p.z() - r;
            if (p.x() + r > _bmax.x()) _bmax.x() = p.x() + r;
            if (p.y() + r > _bmax.y()) _bmax.y() = p.y() + r;
            if (p.z() + r > _bmax.z()) _bmax.z() = p.z() + r;
        }
        if (!_bounds_computed) 
            _bounds_computed = true;
    }

    inline Particle& ParticleSystem::getDefaultParticleTemplate()
    {
        return _def_ptemp;
    }

    inline const Particle& ParticleSystem::getDefaultParticleTemplate() const
    {
        return _def_ptemp;
    }

    inline void ParticleSystem::setDefaultParticleTemplate(const Particle& p)
    {
        _def_ptemp = p;
    }
    
    inline bool ParticleSystem::getFreezeOnCull() const
    {
        return _freeze_on_cull;
    }
    
    inline void ParticleSystem::setFreezeOnCull(bool v)
    {
        _freeze_on_cull = v;
    }
    
    inline int ParticleSystem::GetLOD() const
    {
        return _detail;
    }
    
    inline void ParticleSystem::SetLOD(int v)
    {
        if (v < 1) v = 1;
        _detail = v;
    }
    
    inline ParticleSystem::SortMode ParticleSystem::getSortMode() const
    {
        return _sortMode;
    }
    
    inline void ParticleSystem::setSortMode(SortMode mode)
    {
        _sortMode = mode;
    }
    
    inline double ParticleSystem::getVisibilityDistance() const
    {
        return _visibilityDistance;
    }
    
    inline void ParticleSystem::setVisibilityDistance(double distance)
    {
        _visibilityDistance = distance;
        if (_useShaders) _dirty_uniforms = true;
    }
    
    // I'm not sure this function should be inlined...     
    inline Particle* ParticleSystem::createParticle(const Particle* ptemplate)
    {
        // �Ƿ��������������ã�������?
        if (!_deadparts.empty())
        {
            // �������������л�ȡһ��ָ��
            Particle* P = _deadparts.top();

            // ����ͬ��λ�ô���һ���µ�(���) ����
            *P = ptemplate? *ptemplate: _def_ptemp;

            // remove the pointer from the death stack
            _deadparts.pop();
            return P;
        }
        else
        {
            // ����һ�������Ӳ���������
            m_vParticles.push_back(ptemplate? *ptemplate: _def_ptemp);
            return &m_vParticles.back();
        }
    }


}

#endif
