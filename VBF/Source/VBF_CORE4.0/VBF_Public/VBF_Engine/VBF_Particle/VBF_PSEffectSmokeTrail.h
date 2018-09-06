#ifndef OSGPARTICLE_SMOKETRAILEFFECT
#define OSGPARTICLE_SMOKETRAILEFFECT

#include <VBF_Engine/VBF_Particle/VBF_PSEffect.h>
#include <VBF_Engine/VBF_Particle/VBF_PSEmitterModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSProgramFluid.h>

namespace osgParticle
{

    class OSGPARTICLE_EXPORT SmokeTrailEffect : public ParticleEffect
    {
    public:
    
        explicit SmokeTrailEffect(bool automaticSetup=true);    
        SmokeTrailEffect(const osg::Vec3& position, float scale=1.0f, float intensity=1.0f);    
        SmokeTrailEffect(const SmokeTrailEffect& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Node(osgParticle,SmokeTrailEffect);
        
        virtual void setDefaults();
        virtual void setUpEmitterAndProgram();

        virtual Emitter* getEmitter() { return m_ipEmitter.get(); }
        virtual const Emitter* getEmitter() const { return m_ipEmitter.get(); }

        virtual Program* getProgram() { return m_ipProgram.get(); }
        virtual const Program* getProgram() const { return m_ipProgram.get(); }
    
    protected:

        virtual ~SmokeTrailEffect() {}
        
        ref_ptr<ModularEmitter> m_ipEmitter;
        ref_ptr<FluidProgram>   m_ipProgram;

    };
}

#endif
