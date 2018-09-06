
#ifndef OSGPARTICLE_FIREEFFECT
#define OSGPARTICLE_FIREEFFECT

#include <VBF_Engine/VBF_Particle/VBF_PSEffect.h>
#include <VBF_Engine/VBF_Particle/VBF_PSEmitterModular.h>
#include <VBF_Engine/VBF_Particle/VBF_PSProgramFluid.h>

namespace osgParticle
{
	// ���Ч��
    class OSGPARTICLE_EXPORT FireEffect : public ParticleEffect
    {
    public:
    
        explicit FireEffect(bool automaticSetup=true);  
        FireEffect(const osg::Vec3& position, float scale=1.0f, float intensity=1.0f);       
        FireEffect(const FireEffect& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);

        META_Node(osgParticle,FireEffect);
        
		// ����ΪĬ�ϲ���
        virtual void setDefaults();
    
		// �����緢���ͱ����
        virtual void setUpEmitterAndProgram();

        virtual Emitter* getEmitter() { return m_ipEmitter.get(); }
        virtual const Emitter* getEmitter() const { return m_ipEmitter.get(); }

        virtual Program* getProgram() { return m_ipProgram.get(); }
        virtual const Program* getProgram() const { return m_ipProgram.get(); }
    
    protected:
    
        virtual ~FireEffect() {}

        ref_ptr<ModularEmitter> m_ipEmitter;
        ref_ptr<FluidProgram> m_ipProgram;


    };
}

#endif
