#ifndef OSGPARTICLE_PARTICLEEFFECT
#define OSGPARTICLE_PARTICLEEFFECT

#include <VBF_Engine/VBF_Particle/VBF_PSEmitter.h>
#include <VBF_Engine/VBF_Particle/VBF_PSProgram.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNodeGroupImpl.h>
#include <VBF_Engine/VBF_SceneGraph/IVBF_SGNode.h>

namespace osgParticle
{
	// 特殊定义的粒子系统的基类
    class OSGPARTICLE_EXPORT ParticleEffect : public osg::IVBF_SGNodeGroupImpl<osg::IVBF_SGNodeGroup>
    {
    public:
    
        explicit ParticleEffect(bool bAutomaticSetup=true):
            m_bAutomaticSetup(bAutomaticSetup),
            m_bUseLocalParticleSystem(true),
            m_fScale(1.0f),
            m_fIntensity(1.0f),
            m_dStartTime(0.0),
            m_dEmitterDuration(1.0),
            m_vWind(0.0f,0.0f,0.0f)
            {}
        
        ParticleEffect(const ParticleEffect& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY);


        virtual const char* libraryName() const { return "osgParticle"; }
        virtual const char* className() const { return "ParticleEffect"; }
        virtual bool isSameKindAs(const osg::CVBF_Object* obj) const { return dynamic_cast<const ParticleEffect*>(obj) != 0; }
        virtual void accept(osg::NodeVisitor& nv) { if (nv.validNodeMask(*this)) { nv.pushOntoNodePath(this); nv.apply(*this); nv.popFromNodePath(); } }

        void setAutomaticSetup(bool flag) { m_bAutomaticSetup = flag; }
        bool getAutomaticSetup() const { return m_bAutomaticSetup; }

        void setUseLocalParticleSystem(bool local);
        bool getUseLocalParticleSystem() const { return m_bUseLocalParticleSystem; }

        void setTextureFileName(const std::string& filename);
        const std::string& getTextureFileName() const { return m_sTextureFileName; }

        void setDefaultParticleTemplate(const Particle& p);
        const Particle& getDefaultParticleTemplate() const { return m_ParticleTemplate; }

        void setPosition(const osg::Vec3& position);
        const osg::Vec3& getPosition() const { return m_vPosition; }

        void setScale(float scale);
        float getScale() const { return m_fScale; }

        void setIntensity(float intensity);
        float getIntensity() const { return m_fIntensity; }
        
        void setStartTime(double startTime);
        double getStartTime() const { return m_dStartTime; }

        void setEmitterDuration(double duration);
        double getEmitterDuration() const { return m_dEmitterDuration; }

        void setParticleDuration(double duration);
        double getParticleDuration() const { return m_ParticleTemplate.getLifeTime(); }

        void setWind(const osg::Vec3& wind);
        const osg::Vec3& getWind() const { return m_vWind; }

        // 获取所有粒子已经死亡
        bool areAllParticlesDead() const { return m_ipPS.valid()?m_ipPS->areAllParticlesDead():true; }

        virtual Emitter* getEmitter() = 0;
        virtual const Emitter* getEmitter() const  = 0;

        virtual Program* getProgram()  = 0;
        virtual const Program* getProgram() const  = 0;
        
        void setParticleSystem(ParticleSystem* ps);
        inline ParticleSystem* getParticleSystem() { return m_ipPS.get(); }
        inline const ParticleSystem* getParticleSystem() const { return m_ipPS.get(); }

        virtual void setDefaults();

        virtual void setUpEmitterAndProgram() = 0;

        virtual void buildEffect();

    protected:
    
        virtual ~ParticleEffect() {}
        
        bool                            m_bAutomaticSetup;

        ref_ptr<ParticleSystem>         m_ipPS; // 粒子系统

        bool                            m_bUseLocalParticleSystem;
        std::string                     m_sTextureFileName;
        Particle                        m_ParticleTemplate; // 默认的粒子模板
        osg::Vec3                       m_vPosition;
        float                           m_fScale;
        float                           m_fIntensity;
        double                          m_dStartTime;
        double                          m_dEmitterDuration;
        osg::Vec3                       m_vWind;
    };

}

#endif
