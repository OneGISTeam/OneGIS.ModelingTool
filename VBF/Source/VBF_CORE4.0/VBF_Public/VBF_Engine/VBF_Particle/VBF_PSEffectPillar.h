#ifndef VBF_PARTICLE_PILLAR_EFFECT
#define VBF_PARTICLE_PILLAR_EFFECT

#include <VBF_Engine/VBF_Particle/VBF_PSEffect.h>
#include <VBF_Engine/VBF_Particle/VBF_PSEmitterModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSProgramFluid.h>
#include <VBF_Engine/VBF_Particle/VBF_PSProgramModular.h>
namespace osgParticle
{            

    // Á£×ÓÖùÐ§¹û
    class OSGPARTICLE_EXPORT CVBF_PSEffectPillar : public ParticleEffect
    {
    public:    
        explicit CVBF_PSEffectPillar(bool automaticSetup=true);
    
        CVBF_PSEffectPillar(const osg::Vec3& position, float scale=1.0f, float intensity=1.0f);
        CVBF_PSEffectPillar(const CVBF_PSEffectPillar& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Node(osgParticle,CVBF_PSEffectPillar);
        
        virtual void setDefaults();
        virtual void setUpEmitterAndProgram();

        virtual Emitter* getEmitter() { return m_ipEmitter.get(); }
        virtual const Emitter* getEmitter() const { return m_ipEmitter.get(); }

        virtual Program* getProgram() { return m_ipProgram.get(); }
        virtual const Program* getProgram() const { return m_ipProgram.get(); }
    
    protected:

        virtual ~CVBF_PSEffectPillar() {}
        
        ref_ptr<ModularEmitter> m_ipEmitter;
 //       ref_ptr<FluidProgram>   m_ipProgram;
        ref_ptr<ModularProgram>   m_ipProgram;
    };
}

#endif
