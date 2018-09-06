#ifndef OSGPARTICLE_PARTICLESYSTEMUPDATER
#define OSGPARTICLE_PARTICLESYSTEMUPDATER 1

#include <VBF_Engine/VBF_Particle/Export>
#include <VBF_Engine/VBF_Particle/VBF_ParticleSystem.h>

#include <vector>

#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGeometry.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>

#include <VBF_Engine/VBF_SGUtil/CullVisitor>

namespace osgParticle
{
	// 粒子系统更新器：用于自动更新粒子，将其放置于场景中时，它会在筛选遍历中调用所有"存活"粒子的Update函数
    class OSGPARTICLE_EXPORT ParticleSystemUpdater: public osg::IVBF_SGNodeImpl<IVBF_SGNode> 
	{
    public:
        ParticleSystemUpdater();
        ParticleSystemUpdater(const ParticleSystemUpdater& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Node(osgParticle,ParticleSystemUpdater);
        
        // 添加/移除一个粒子系统
        virtual bool addParticleSystem(ParticleSystem* ps);
        virtual bool removeParticleSystem(ParticleSystem* ps);

        // 移除第i个粒子系统
        virtual bool removeParticleSystem(unsigned int i, unsigned int numParticleSystemsToRemove=1);
        
        // 用一个粒子系统替换另一个粒子系统
        virtual bool replaceParticleSystem(ParticleSystem* origPS, ParticleSystem* newPS);

        // 设置粒子系统
        virtual bool setParticleSystem( unsigned int i, ParticleSystem* ps );

        // 获取粒子系统的数量
        inline unsigned int getNumParticleSystems() const;

        // 获取一个粒子系统
        inline ParticleSystem* getParticleSystem(unsigned int i);
        inline const ParticleSystem* getParticleSystem(unsigned int i) const;

        // 判断是否包含一个粒子系统
        inline bool containsParticleSystem( const ParticleSystem* ps ) const;

        // 按序号获取粒子系统
        inline unsigned int getParticleSystemIndex( const ParticleSystem* ps ) const;
        
        virtual void traverse(osg::NodeVisitor& nv);
        
        virtual osg::BoundingSphere computeBound() const;        

    protected:
        virtual ~ParticleSystemUpdater() {}
        ParticleSystemUpdater &operator=(const ParticleSystemUpdater &) { return *this; }
        
    private:
        typedef std::vector<ref_ptr<ParticleSystem> > ParticleSystem_Vector;
        
        ParticleSystem_Vector _psv;
        double _t0;
        
        //added 1/17/06- bgandere@nps.edu
        //a var to keep from doing multiple updates per frame
        unsigned int _frameNumber;
    };
    
    // INLINE FUNCTIONS
    
    inline unsigned int ParticleSystemUpdater::getNumParticleSystems() const
    {
        return static_cast<int>(_psv.size());
    }
    
    inline ParticleSystem* ParticleSystemUpdater::getParticleSystem(unsigned int i)
    {
        return _psv[i].get();
    }

    inline const ParticleSystem* ParticleSystemUpdater::getParticleSystem(unsigned int i) const
    {
        return _psv[i].get();
    }

    inline bool ParticleSystemUpdater::containsParticleSystem( const ParticleSystem* ps ) const
    {
       for( ParticleSystem_Vector::const_iterator itr=_psv.begin();
            itr!=_psv.end();
            ++itr )
       {
          if( itr->get() == ps ) return true;
       }
       return false;
    }

    inline unsigned int ParticleSystemUpdater::getParticleSystemIndex( const ParticleSystem* ps ) const
    {
       for( unsigned int particleSystemNum=0; particleSystemNum<_psv.size(); ++particleSystemNum )
       {
          if( _psv[particleSystemNum] == ps ) return particleSystemNum;
       }
       return _psv.size(); // node not found.
    }

}

#endif
