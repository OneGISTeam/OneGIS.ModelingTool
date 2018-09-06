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

// 2009.2.9 关闭使用ReadWriteMutex，OSGPARTICLE_USE_ReadWriteMutex可能导致线程问题due to threading problems in OpenThreads::ReadWriteMutex.
// #define OSGPARTICLE_USE_ReadWriteMutex

#ifdef OSGPARTICLE_USE_ReadWriteMutex
    #include <OpenThreads/ReadWriteMutex>
#else
    #include <OpenThreads/Mutex>
    #include <OpenThreads/ScopedLock>
#endif

namespace osgParticle
{
	// 该库的核心类，维护并管理一系列粒子的生成、更新、渲染和销毁。与其他的Drawable类似。
    // 创建粒子由Emitter完成，控制粒子运动Program完成，筛选粒子由Updater完成
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
        
		// 获取/设置粒子的Alignment类型
        inline Alignment getParticleAlignment() const;
        inline void setParticleAlignment(Alignment a);
        
        // 获取/设置X-axis的Alignment向量
        inline const osg::Vec3& getAlignVectorX() const;
        inline void setAlignVectorX(const osg::Vec3& v);

        // 获取/设置Y-axis的Alignment向量
        inline const osg::Vec3& getAlignVectorY() const;
        inline void setAlignVectorY(const osg::Vec3& v);
        
		// 设置Alignment向量
        inline void setAlignVectors(const osg::Vec3& X, const osg::Vec3& Y);



        enum ParticleScaleReferenceFrame
        {
            LOCAL_COORDINATES,
            WORLD_COORDINATES
        };

 		// 设置/获取是根据世界坐标系还是局部坐标系缩放粒子
        void setParticleScaleReferenceFrame(ParticleScaleReferenceFrame rf) { _particleScaleReferenceFrame = rf; }
        ParticleScaleReferenceFrame getParticleScaleReferenceFrame() const { return _particleScaleReferenceFrame; }



        // 获取包围盒
        inline const osg::BoundingBox& getDefaultBoundingBox() const;        

		// 设置默认的包围盒，用于实际的包围盒无法计算的情况，如还没有粒子的时候
        inline void setDefaultBoundingBox(const osg::BoundingBox& bbox);

		// 设置/获取是否使用顶点数组渲染粒子。使用顶点数组时，很多变量会被忽略，如形状、是否存活、可视距离等
		// 因此，渲染的效果不够好（比glBegin/glEnd速度快）。
        // 对于GLSL着色器最好使用顶点数组, 此时，粒子的参数被保存为uniforms。 该方法被setDefaultAttributesUsingShaders()自动调用     
		bool getUseVertexArray() const { return _useVertexArray; }
		void setUseVertexArray(bool v) { _useVertexArray = v; }



			
		// 设置/获取是否使用着色器渲染粒子
        /** Particles' parameters will be used as shader attribute arrays, and necessary variables, including
            the visibility distance, texture, etc, will be used and updated as uniforms.*/		
		bool getUseShaders() const { return _useShaders; }
		void setUseShaders(bool v) { _useShaders = v; _dirty_uniforms = true; }


		// 获取/设置是否使用double pass渲染粒子，两遍渲染可以避免粒子系统和不透明对象之间的overdraw问题
		// 如果所有的粒子系统都在不透明对象之后绘制，则不需要两遍渲染，可以关掉（这也是最好的选择）
		// 如果调用setDefaultAttributes设置了默认的属性，粒子系统将被放入transparent bin。
		inline bool getDoublePassRendering() const;
		inline void setDoublePassRendering(bool v);

		// 设置/获取/判断粒子系统是否被冻结，粒子系统被冻结后，emitters和programs将什么都不做
        bool getFrozen() const { return _frozen; }
        inline bool isFrozen() const;
        inline void setFrozen(bool v);

		// 获取分配的粒子数（包括活的和死亡的）
        inline int numParticles() const;
        
		// 获取死亡的粒子数
        inline int numDeadParticles() const;
  
		// 是否所有的粒子都已死亡
        inline bool areAllParticlesDead() const { return numDeadParticles()==numParticles(); }
        
		// 获取第i个粒子
        inline Particle* getParticle(int i);
        inline const Particle* getParticle(int i) const;
        
		// 使用特定的模板创建一个新粒子(或模板为null).
        inline virtual Particle* createParticle(const Particle* ptemplate);
        
        // 销毁第i个粒子
        inline virtual void destroyParticle(int i);
        
        // 重用第i个粒子
        inline virtual void reuseParticle(int i) { _deadparts.push(&(m_vParticles[i])); }

        // 获取上一个帧号
        inline unsigned int getLastFrameNumber() const;
        
		// 获取粒子发射和更新的时间增量
        inline double& getDeltaTime( double currentTime );


		// 设置/获取默认的粒子模板
		inline Particle& getDefaultParticleTemplate();
		inline const Particle& getDefaultParticleTemplate() const;
		inline void setDefaultParticleTemplate(const Particle& p);

		// 设置/获取筛选时（cull）粒子系统是否可以冻结（默认为true）
        inline bool getFreezeOnCull() const;
        inline void setFreezeOnCull(bool v);
        
 		// 设置最常用的StateAttribute，如果texturefile为空则关闭纹理
        void setDefaultAttributes(const std::string& texturefile = "", bool emissive_particles = true, bool lighting = false, int texture_unit = 0);
        
        // 设置最常用的StateAttribute，使用GLSL着色器绘制粒子。当使用着色器时，用户定义的shapes被忽略。如果texturefile为空则关闭纹理
        void setDefaultAttributesUsingShaders(const std::string& texturefile = "", bool emissive_particles = true, int texture_unit = 0);
        
		// 获取/设置LOD值，该值必须大于0。粒子的总数本该值除，以便获得实际渲染的粒子数
		inline int GetLOD() const;
		inline void SetLOD(int v);

        enum SortMode
        {
            NO_SORT,			// 不排
            SORT_FRONT_TO_BACK,	// 从前到后
            SORT_BACK_TO_FRONT	// 从后到前
        };
        

		// 设置/获取排序模式，强制对粒子的列表按照view coordinates的Z方向重新排序，用于透明渲染或设置可视距离（setVisibilityDistance)
        inline SortMode getSortMode() const;
        inline void setSortMode(SortMode mode);
  

		// 获取/设置可视距离，仅渲染depth在可视距离内的粒子
		// 使用着色器时，可以很好的工作。 否则，必须设置排序模式（SortMode）预先计算深度（depth）。
		inline double getVisibilityDistance() const;
		inline void setVisibilityDistance(double distance);

        // 更新粒子，不要直接调用该函数，而是使用ParticleSystemUpdater。
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

        Particle_vector m_vParticles; // 记录所有的粒子。真正使用的粒子是由一个隐含的链表实现的（每个粒子记录了前一个和后一个粒子）
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
        // 是否还有已死（可重用）的粒子?
        if (!_deadparts.empty())
        {
            // 从已死的粒子中获取一个指针
            Particle* P = _deadparts.top();

            // 在相同的位置创建一个新的(活的) 粒子
            *P = ptemplate? *ptemplate: _def_ptemp;

            // remove the pointer from the death stack
            _deadparts.pop();
            return P;
        }
        else
        {
            // 创建一个新粒子并加入数组
            m_vParticles.push_back(ptemplate? *ptemplate: _def_ptemp);
            return &m_vParticles.back();
        }
    }


}

#endif
