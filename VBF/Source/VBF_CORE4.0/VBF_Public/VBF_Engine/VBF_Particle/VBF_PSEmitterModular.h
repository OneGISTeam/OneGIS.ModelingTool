#ifndef OSGPARTICLE_MODULAREMITTER
#define OSGPARTICLE_MODULAREMITTER 1

#include <VBF_Engine/VBF_Particle/Export>
#include <VBF_Engine/VBF_Particle/VBF_PSEmitter.h>
#include <VBF_Engine/VBF_Particle/VBF_Particle.h>
#include <VBF_Engine/VBF_Particle/VBF_PSCounterRandomRate.h>
#include <VBF_Engine/VBF_Particle/VBF_PSPlacer.h>
#include <VBF_Engine/VBF_Particle/VBF_PSPlacerPoint.h>
#include <VBF_Engine/VBF_Particle/VBF_PSShooter.h>
#include <VBF_Engine/VBF_Particle/VBF_PSShooterRadial.h>
#include <VBF_Engine/VBF_Particle/VBF_ParticleSystem.h>

#include <VBF_Base/ref_ptr>
#include <VBF_Engine/VBF_SceneGraph/CopyOp>
#include <VBF_Engine/VBF_SceneGraph/VBF_Object.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeImpl.h>
#include <VBF_Engine/VBF_SceneGraph/VBF_SGNVisitOp.h>

namespace osgParticle
{

    // ��׼���������ɼ������������������������
    class OSGPARTICLE_EXPORT ModularEmitter: public Emitter
    {
    public:
        ModularEmitter();
        ModularEmitter(const ModularEmitter& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Node(osgParticle,ModularEmitter);
        
        // ����/��ȡ������
        inline Counter* getCounter();
        inline const Counter* getCounter() const;
        inline void setCounter(Counter* c);
        
        /// Get the ratio between number of particle to create in compensation for movement of the emitter
        inline float getNumParticlesToCreateMovementCompensationRatio() const;
        inline void setNumParticlesToCreateMovementCompensationRatio(float r);


        // ����/��ȡ������
        inline Placer* getPlacer();        
        inline const Placer* getPlacer() const;
        inline void setPlacer(Placer* p);
        
        // ����/��ȡ������
        inline Shooter *getShooter();
        inline const Shooter *getShooter() const;
        inline void setShooter(Shooter *s);

        void SetUsingRF(bool bUse){ m_bUsingRF = bUse; }

    protected:
        virtual ~ModularEmitter() {}
        ModularEmitter &operator=(const ModularEmitter &) { return *this; }
        
        virtual void emitParticles(double dt);
        
    private:
    
        float _numParticleToCreateMovementCompensationRatio;
        ref_ptr<Counter>    _counter;
        ref_ptr<Placer>     _placer;
        ref_ptr<Shooter>    _shooter;
        bool m_bUsingRF;
    };

    
    inline Counter* ModularEmitter::getCounter()
    {
        return _counter.get();
    }
    
    inline const Counter* ModularEmitter::getCounter() const
    {
        return _counter.get();
    }

    inline void ModularEmitter::setCounter(Counter* c)
    {
        _counter = c;
    }

    inline float ModularEmitter::getNumParticlesToCreateMovementCompensationRatio() const
    {
        return _numParticleToCreateMovementCompensationRatio;
    }

    inline void ModularEmitter::setNumParticlesToCreateMovementCompensationRatio(float r)
    {
        _numParticleToCreateMovementCompensationRatio = r;
    }

    inline Placer* ModularEmitter::getPlacer()
    {
        return _placer.get();
    }

    inline const Placer* ModularEmitter::getPlacer() const
    {
        return _placer.get();
    }

    inline void ModularEmitter::setPlacer(Placer* p)
    {
        _placer = p;
    }

    inline Shooter *ModularEmitter::getShooter()
    {
        return _shooter.get();
    }

    inline const Shooter *ModularEmitter::getShooter() const
    {
        return _shooter.get();
    }

    inline void ModularEmitter::setShooter(Shooter *s)
    {
        _shooter = s;
    }
    
}

#endif
