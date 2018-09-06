#ifndef OSGPARTICLE_EXPLOSIONDEBRISEFFECT
#define OSGPARTICLE_EXPLOSIONDEBRISEFFECT

#include <VBF_Engine/VBF_Particle/VBF_PSEffect.h>
#include <VBF_Engine/VBF_Particle/VBF_PSEmitterModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSProgramFluid.h>

namespace osgParticle
{
	// ±¬Õ¨ËéÆ¬Ð§¹û
    class OSGPARTICLE_EXPORT ExplosionDebrisEffect : public ParticleEffect
    {
    public:
    
        explicit ExplosionDebrisEffect(bool automaticSetup=true);

        ExplosionDebrisEffect(const osg::Vec3& position, float scale=1.0f, float intensity=1.0f);
        
        ExplosionDebrisEffect(const ExplosionDebrisEffect& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Node(osgParticle,ExplosionDebrisEffect);
        
        virtual void setDefaults();

        virtual void setUpEmitterAndProgram();
    
        virtual Emitter* getEmitter() { return _emitter.get(); }
        virtual const Emitter* getEmitter() const { return _emitter.get(); }

        virtual Program* getProgram() { return _program.get(); }
        virtual const Program* getProgram() const { return _program.get(); }

    protected:

        virtual ~ExplosionDebrisEffect() {}

        ref_ptr<ModularEmitter> _emitter;
        ref_ptr<FluidProgram> _program;

    };
}

#endif
