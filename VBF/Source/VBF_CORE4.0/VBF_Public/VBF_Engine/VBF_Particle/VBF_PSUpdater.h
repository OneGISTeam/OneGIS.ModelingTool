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
	// ����ϵͳ�������������Զ��������ӣ���������ڳ�����ʱ��������ɸѡ�����е�������"���"���ӵ�Update����
    class OSGPARTICLE_EXPORT ParticleSystemUpdater: public osg::IVBF_SGNodeImpl<IVBF_SGNode> 
	{
    public:
        ParticleSystemUpdater();
        ParticleSystemUpdater(const ParticleSystemUpdater& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Node(osgParticle,ParticleSystemUpdater);
        
        // ���/�Ƴ�һ������ϵͳ
        virtual bool addParticleSystem(ParticleSystem* ps);
        virtual bool removeParticleSystem(ParticleSystem* ps);

        // �Ƴ���i������ϵͳ
        virtual bool removeParticleSystem(unsigned int i, unsigned int numParticleSystemsToRemove=1);
        
        // ��һ������ϵͳ�滻��һ������ϵͳ
        virtual bool replaceParticleSystem(ParticleSystem* origPS, ParticleSystem* newPS);

        // ��������ϵͳ
        virtual bool setParticleSystem( unsigned int i, ParticleSystem* ps );

        // ��ȡ����ϵͳ������
        inline unsigned int getNumParticleSystems() const;

        // ��ȡһ������ϵͳ
        inline ParticleSystem* getParticleSystem(unsigned int i);
        inline const ParticleSystem* getParticleSystem(unsigned int i) const;

        // �ж��Ƿ����һ������ϵͳ
        inline bool containsParticleSystem( const ParticleSystem* ps ) const;

        // ����Ż�ȡ����ϵͳ
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
